///////////////////////////////////////////////////////////////////////////////
// OtlLayoutPlugin.h
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

#ifndef __OTLLAYOUTPLUGIN_H__
#define __OTLLAYOUTPLUGIN_H__

#ifndef __OTLBASE_H__
	#error otllayoutplugin.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otllayoutnode.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlLayoutPlugin
class COtlLayoutPlugin : public CMessageMap
{
	
public:

	inline COtlLayoutPlugin() :	m_hWndWatch(0), 
							m_pLayoutNode(0), 
							m_bUseWindowRect(FALSE),
							m_bOnSizeRecalc(TRUE) {}

	virtual BOOL AutoInit(	COtlLayoutNode* pRootNode,
							HWND hwndParent,
							BOOL bDoRecalc=TRUE,
							BOOL bInitUsingWindowRect=FALSE)
	{

		OTLASSERT(hwndParent);
		if(!hwndParent) return FALSE;

		// Calc appropriate initial rectangle
		RECT rect;
		m_bUseWindowRect = bInitUsingWindowRect;
		if(bInitUsingWindowRect) 
		{
			::GetWindowRect(hwndParent, &rect);
			::OffsetRect(&rect, -rect.left, -rect.top);
		}
		else ::GetClientRect(hwndParent, &rect);
		
		// Use overload to complete processing
		return AutoInit(pRootNode,hwndParent,rect,bDoRecalc);

	}

	virtual BOOL AutoInit(	COtlLayoutNode* pRootNode,
							HWND hwndParent,
							const RECT& rectNodeInitial,
							BOOL bDoRecalc=TRUE )
	{
		OTLASSERT(pRootNode && hwndParent);
		m_hWndWatch = hwndParent;

		// First default initial rect
		pRootNode->SetInitialRect(rectNodeInitial);

		// Recursively recalculate the appropriate Z-Order (necessary to 
		// avoid stepping on child control tab order, while still 
		// allowing nested splitters to coeexist)
		pRootNode->RecalcZOrder();

		m_pLayoutNode = pRootNode;

		// kick off an initial recalc and refresh
		if(bDoRecalc) 
		{
			RECT r;
			pRootNode->RecalcLayout(&r, rectNodeInitial,FALSE,TRUE);
			pRootNode->RealizeNode();

			// Manually pump the first invalidation to insure
			// all child nodes initialize properly.
			pRootNode->PerformInvalidation(FALSE);
		}

		return TRUE;
	}

////////// messages
	BEGIN_MSG_MAP(COtlLayoutPlugin)
		MESSAGE_HANDLER(WM_SIZE, OnSizeLayout)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
	END_MSG_MAP()


	inline LRESULT OnSizeLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(!m_hWndWatch || !m_pLayoutNode || !m_bOnSizeRecalc)	
		{
			bHandled = FALSE;
			return 0;
		}
		int cx = LOWORD(lParam);  // width of client area 
		int cy = HIWORD(lParam);  // height of client area  

		LRESULT lr =  ::DefWindowProc(m_hWndWatch, uMsg, wParam, lParam);

		// New size, peform all necessary size/position recalculations
		RECT rectNode;
		m_pLayoutNode->GetCurrentRect(&rectNode);
		if(m_bUseWindowRect && m_hWndWatch) 
		{
			RECT rcWindow;
			if(::GetWindowRect(m_hWndWatch, &rcWindow))
			{
				rectNode.right=rectNode.left+OtlRectWidth(rcWindow);
				rectNode.bottom=rectNode.top+OtlRectHeight(rcWindow);
			}
		}
		else 
		{
			rectNode.right=rectNode.left+cx;
			rectNode.bottom=rectNode.top+cy;
		}

		// Parent has sized, force a strict recalc of all children
		// Top level can not allow child negotiation (since window
		// size must be fixed, but children of top level can negotiate
		// size within that top level (and so on down the tree).
		RECT r;
		m_pLayoutNode->RecalcLayout(&r, rectNode, FALSE, TRUE);	

		m_pLayoutNode->RealizeNode();
		
		return lr;
	}


	inline LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		if(!m_pLayoutNode || !m_hWndWatch) 
		{
			bHandled = FALSE;
			return 0;
		}

		LPMINMAXINFO lpmmi = (LPMINMAXINFO) lParam;
		// Query configured min/max settings	
		SIZE sizeMin,sizeMax;
		DWORD dwFlags=0;

		try { m_pLayoutNode->GetMinMaxSize(sizeMin,sizeMax,dwFlags); }
		catch(...) 
		{
			// If an exception was triggered, make sure your layout node
			// object has not been deleted. If the node was created using a
			// layout node factory object, make sure that object has not
			// gone out of scope.
			// If the node was intentionally deleted, you must also delete 
			// this layout listener (preferably before node deletion)
			OTLASSERT(FALSE);
			return 0;
		}

		// Min/Max width/height settings
		// Account for extra frame size (if present)
		RECT clientSize, windowSize;
		::GetClientRect(m_hWndWatch, &clientSize);
		::GetWindowRect(m_hWndWatch, &windowSize);
		int frameWidth = OtlRectWidth(windowSize) - OtlRectWidth(clientSize);
		OTLASSERT(frameWidth>=0);
		int frameHeight = OtlRectHeight(windowSize) - OtlRectHeight(clientSize);
		OTLASSERT(frameHeight>=0);
		if(!(dwFlags & OTL_LNODE_NO_MINSIZE)) 
		{
			// Set the min/max
			lpmmi->ptMinTrackSize.x=sizeMin.cx + frameWidth;
			lpmmi->ptMinTrackSize.y=sizeMin.cy + frameHeight;
		}
		if(!(dwFlags & OTL_LNODE_NO_MAXSIZE)) 
		{
			lpmmi->ptMaxTrackSize.x=sizeMax.cx + frameWidth;
			lpmmi->ptMaxTrackSize.y=sizeMax.cy + frameHeight;
		}
		return 0;
	}

protected:
	HWND m_hWndWatch;
	COtlLayoutNode* m_pLayoutNode;
	BOOL m_bUseWindowRect;
	BOOL m_bOnSizeRecalc;
};

};	// namespace StingrayOTL

#endif // __OTLLAYOUTPLUGIN_H__
