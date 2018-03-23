///////////////////////////////////////////////////////////////////////////////
// TabBarController.h : interface for the SECTabBarController class.
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Authors:      Prakash Surendra and Jay Gopalakrishnan
// Description:  ShortcutBar - MVCController implementation
//

#ifndef __TABBAR_CNTRLR_H__
#define __TABBAR_CNTRLR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Foundation\Mvc\MvcController.h"
#include "Foundation\events\mouselistener.h"
#include "Foundation\events\keyboardlistener.h"
#include "Foundation\events\windowlistener.h"
#include "BarViewport.h"
#include <StingrayExportDefs.h>

namespace stingray {

// User-defined message for extending the ShortcutBar's context menu
#define WM_TABBAR_CNTXTMENU	(WM_APP+0x0101) 

// Forward declarations.
class SECTabBarPresModel;
class SECBarViewport;

class SECTabBarController  : public CMvcController<SECTabBarPresModel,SECBarViewport>, public CMouseAdapter, 
						public CWindowAdapter, public CKeyboardAdapter
{
public:
	inline SECTabBarController()
	{
		AddListener(static_cast<IWindowListener*>(this));
		AddListener(static_cast<IMouseListener*>(this));
		AddListener(static_cast<IKeyboardListener*>(this));

		m_nHitIndex = -1;
		m_pCurrEvent = NULL;
	}

	inline virtual ~SECTabBarController()	{}

protected:
// Message handlers
	inline virtual bool OnEraseBkgnd(HDC hDC)
	{
		if(hDC != NULL)
		{
			CGraphicsContext CGC;
			CGC.Attach(hDC);
			GetViewport()->EraseBkgndVP(&CGC);
			CGC.Detach();
		}
		else
			GetViewport()->EraseBkgndVP(NULL);
		return false;
	}

	inline virtual bool OnPaint(HDC hDC)
	{
		if(hDC != NULL)
		{
			CGraphicsContext CGC;
			CGC.Attach(hDC);
			GetViewport()->Draw(&CGC);
			CGC.Detach();
		}
		else
			GetViewport()->Draw(NULL);
		return false;
	}

	inline virtual bool OnSize(UINT nFlag, int cx, int cy)
	{
		GetViewport()->	SetSize(cx, cy);
		return false;
	}

	inline virtual bool OnLButtonDown(UINT nFlags, POINT pt)
	{
		UINT nHitTestCode;
		int nHitIndex;
		GetViewport()->HitTest(CHitTest::WMLBtnDown, pt, nHitTestCode, nHitIndex);

		if(nHitTestCode == CHitTest::htItem)
			m_nHitIndex = nHitIndex;
		else if(nHitTestCode == CHitTest::htClient)
		{
			SECTabBarBase* pTabBar = GetModel()->GetTabBarAt(nHitIndex);
			if(pTabBar->IsVisualComp())
				RouteEventtoClient(pTabBar);
		}
		return true;
	}

	inline virtual bool OnLButtonUp(UINT nFlags, POINT pt)
	{
		UINT nHitTestCode;
		int nHitIndex;
		GetViewport()->HitTest(CHitTest::WMLBtnUp, pt, nHitTestCode, nHitIndex);

		if(nHitTestCode == CHitTest::htItem && nHitIndex == m_nHitIndex)
			GetModel()->ActivateTabBar(m_nHitIndex);
		else if(nHitTestCode == CHitTest::htClient)
		{
			SECTabBarBase* pTabBar = GetModel()->GetTabBarAt(nHitIndex);
			if(pTabBar->IsVisualComp())
				RouteEventtoClient(pTabBar);
		}

		m_nHitIndex = -1;

		return true;
	}

	inline virtual bool OnRButtonUp(UINT nFlags, POINT pt)
	{
		if(!(GetModel()->GetTabBarStyle() & SEC_TABBAR_CNTXTMENU))
		return false;

		UINT nHitTestCode;
		int nHitIndex;
		GetViewport()->HitTest(CHitTest::WMRBtnUp, pt, nHitTestCode, nHitIndex);

		if(nHitTestCode == CHitTest::htClient || nHitTestCode == CHitTest::htItem)
		{
			HMENU hMenu = CreatePopupMenu();
			assert(hMenu != NULL);
			// If the handler returns true then display the popup menu. Else simply destroy the menu resource.
			if( ::SendMessage(GetModel()->GetNotifyWnd(), WM_TABBAR_CNTXTMENU, (WPARAM)nHitIndex, (LPARAM)&hMenu) )
			{
				::ClientToScreen(GetViewport()->GetHostImpl()->GetWindowHandle(), &pt);
				::TrackPopupMenu(hMenu, TPM_RIGHTBUTTON|TPM_LEFTALIGN, pt.x, pt.y, 0, GetModel()->GetNotifyWnd(), 0);
			}
			::DestroyMenu(hMenu);
		}

		return true;
	}

	inline virtual bool OnMouseMove(UINT nFlags, POINT pt)
	{
		UINT nHitTestCode;
		int nHitIndex;
		GetViewport()->HitTest(CHitTest::WMMouseMove, pt, nHitTestCode, nHitIndex);

		if(nHitTestCode == CHitTest::htClient)
		{
			SECTabBarBase* pTabBar = GetModel()->GetTabBarAt(nHitIndex);
			if(pTabBar->IsVisualComp())
				RouteEventtoClient(pTabBar);
		}

		return true;
	}

	inline virtual bool OnTimer(SEC_UINT nIDEvent)
	{
		GetViewport()->OnViewportTimer(nIDEvent);
		return true;
	}

	inline virtual bool OnSetCursor( HWND hWnd, UINT nHitTest, UINT message )
	{
		GetViewport()->OnViewportSetCursor(hWnd, nHitTest, message);
		return true;
	}	

public:
	// Ideally this temporary event cache should not be needed at this level. The current event should be cached and 
	// available from somewhere higher up in the events model. Till then...
	inline virtual bool RouteEvent(IEvent* pIEvent)
	{
		if(pIEvent != NULL)	
			m_pCurrEvent = pIEvent;

		return CMvcController<SECTabBarPresModel,SECBarViewport>::RouteEvent(pIEvent);
	}

protected:
	// MvcViewports that subscribe to the WTL events model will implement the IEventRouter interface.
	// Based on this premise, if this visual component is an MVC viewport, then route the current event
	// through the viewport
	inline void RouteEventtoClient(SECTabBarBase* pTabBar)
	{
		IEventRouter* pEventRouter;
		if(pTabBar->QueryGuid(__uuidof(IEventRouter), (void**)&pEventRouter))
			pEventRouter->RouteEvent(m_pCurrEvent);	
	}

protected:
	int m_nHitIndex;
	IEvent* m_pCurrEvent;	// Temporary cache for the current event.
};

};	// namespace stingray

#endif //__TABBAR_CNTRLR_H__

