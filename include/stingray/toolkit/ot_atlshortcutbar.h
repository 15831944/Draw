///////////////////////////////////////////////////////////////////////////////
// ot_atlshortcutbar.h
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
// Author:      Prakash Surendra
// Description:  SECATLShortcutBarWnd and SECATLShortcutBarHosted implementations
//

#ifndef __ATLSHORTCUTBAR_H__
#define __ATLSHORTCUTBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (_ATL_VER < 0x0300)		
	#error The SECATLShortcutBarWnd and SECATLShortcutBarHosted classes require ATL version 3.0 or higher. Stopping Compilation!
#endif // _ATL_VER < 0x0300

#if (_ATL_VER < 0x0700)
#define hAppInstance	_Module.GetModuleInstance()
#define hResInstance	_Module.GetResourceInstance()
#else
#define hAppInstance	_AtlBaseModule.GetModuleInstance()
#define hResInstance	_AtlBaseModule.GetResourceInstance()
#endif

#include "foundation\SflDef.h"
#include "Foundation\SflRes.h"
#include "foundation\graphics\gccore.h"
#include "Foundation\String\SflString.h"
#include "Foundation\events\event.h"
#include "Foundation\events\eventfactory.h"
#include "Foundation\events\eventroutermap.h"
#include "toolkit\ShortcutBar.h"

namespace stingray {

using namespace foundation;

/////////////////////////////////////////////////////////////////////////////
// SECATLShortcutBarWnd

/////////////////////////////
// AutoDuck tag block block for SECATLShortcutBarWnd

//@doc SECATLShortcutBarWnd
//@mfunc BOOL  | SECATLShortcutBarWnd | Create | Creates the shortcutbar control and initializes it with the styles set in dwStyle.
//@parm HWND | hWndParent | The parent window of the shortcutbar.
//@parm RECT& | rcPos | The initial position of the window.
//@parm DWORD | dwStyle | Specifies the initial styles for the shortcutbar.
//@parm UINT | nID | The ID of the child window.
//@rdesc If the creation is successful, TRUE is returned. Else FALSE.
//@xref<mf SECATLShortcutBarWnd::Create>
//@xref<c SECATLShortcutBarWnd>

// adinsert AutoDuck insertion point for SECATLShortcutBarWnd
//@doc SECATLShortcutBarWnd
//@class The SECATLShortcutBarWnd class implements a windowed version of the Shortcutbar for use with the ATL framework. SECATLShortcutBarWnd 
// derives from SECShortcutBarComp and thus inherits the native shortcutbar API exposed by that class. Additionally, SECATLShortcutBarWnd 
// implements only the Create() function for constructing the windowed control. The rest of the API is fully documented under SECShortcutBarComp. 
//@comm To use SECATLShortcutBarWnd/SECATLShortcutBarWnd, include the 'ot_atlshortcutbar.h' header in your ATL application.
// Please refer to the ATLSHORTCUTBAR sample for a demonstration of SECATLShortcutBarWnd.
//@base public | SECShortcutBarComp
//@base public | CWindowImpl<lt>SECATLShortcutBarWnd<gt>
//@base public | CEventRouterMap<lt>SECATLShortcutBarWnd<gt>
//@base public | IVisualWindow
//@xref <c SECShortcutBarComp>
//@xref <c SECATLShortcutBarWnd>
class SECATLShortcutBarWnd : public SECShortcutBarComp, 
	                         public CEventRouterMap<SECATLShortcutBarWnd>,
						     public CWindowImpl<SECATLShortcutBarWnd>, 
						     public IVisualWindow
{
typedef CEventRouterMap<SECATLShortcutBarWnd> routerBase;
typedef CWindowImpl<SECATLShortcutBarWnd>	   ClassWindowBase;

	BEGIN_MSG_MAP(SECATLShortcutBarWnd)
        CHAIN_MSG_MAP(routerBase)
    END_MSG_MAP()

public:
	// Constructors/Destructor
	inline SECATLShortcutBarWnd()	{};		
	inline virtual ~SECATLShortcutBarWnd()	{};

	// IQueryGuid
	inline virtual bool QueryGuid(REFGUID guid, void **ppvObj)
	{
		if( guid == __uuidof(IVisualWindow) )
		{
			*ppvObj = static_cast<IVisualWindow*>(this);
			return true;
		}
		return false;
	}

	// IVisualWindow implementation
	inline virtual HWND GetWindowHandle()
	{
		return m_hWnd;
	}

	//@cmember
	/* Creates the windowed shortcutbar control.*/
	inline virtual BOOL Create( HWND hWndParent, RECT& rcPos, DWORD dwStyle = WS_CHILD|WS_VISIBLE|SEC_TABBAR_BARCURSOR, UINT nID = 0 )
	{
		DWORD dwBarStyle = dwStyle & SEC_TABBAR_STYLES;
		dwStyle &= ~SEC_TABBAR_STYLES;
		SetHostImpl(static_cast<IVisualWindow*>(this));
		if( !ClassWindowBase::Create(hWndParent,rcPos,NULL,dwStyle,WS_EX_CLIENTEDGE,nID) )
		{
			ATLTRACE(_T("Failed to create the ShortcutBar Window.\n"));
			return FALSE;
		}
		CRect rcClient;
		GetClientRect(&rcClient);
		if( !SECShortcutBarComp::Create(rcClient) )
			return FALSE;
		SetBarStyle(dwBarStyle);
		// The ShortcutBar's parent window is made the default notification target
		SetNotifyWnd(::GetParent(m_hWnd));
		
		return TRUE;
	}
};

/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// SECATLShortcutBarHosted:

/////////////////////////////
// AutoDuck tag block block for SECATLShortcutBarHosted

//@doc SECATLShortcutBarHosted
//@mfunc BOOL  | SECATLShortcutBarHosted | Create | Creates the shortcutbar component and initializes it with the host implementation
// (IVisualWindow*) provided by the parent window.
//@parm IVisualWindow* | pHost | An IVisualWindow interface pointer. The host window is expected to implement this SFL interface.
//@parm RECT& | rcPos | The initial position/size of the control with respect to it's parent.
//@parm DWORD | dwStyle | Specifies the initial styles for the shortcutbar.
//@rdesc If the creation is successful, TRUE is returned. Else FALSE.
//@xref<mf SECATLShortcutBarHosted::Create>
//@xref<c SECATLShortcutBarHosted>

// adinsert AutoDuck insertion point for SECATLShortcutBarHosted
//@doc SECATLShortcutBarHosted
//@class The SECATLShortcutBarHosted class implements a non-windowed version of the Shortcutbar for use with ATL. SECATLShortcutBarHosted 
// derives from SECShortcutBarComp and thus inherits the native shortcutbar API exposed by that class. Additionally, SECATLShortcutBarHosted 
// implements only the Create() function for constructing the control and providing it with a host interface pointer. The rest of the API 
// is fully documented under SECShortcutBarComp. 
//@comm To use SECATLShortcutBarWnd/SECATLShortcutBarWnd, include the 'ot_atlshortcutbar.h' header in your ATL application.
// Please refer to the ATLSHORTCUTBAR sample for a demonstration of SECATLShortcutBarHosted.
//@base public | SECShortcutBarComp
//@base public | CEventRouterMap<lt>SECATLShortcutBarHosted<gt>
//@xref <c SECShortcutBarComp>
//@xref <c SECATLShortcutBarWnd>
class SECATLShortcutBarHosted : public SECShortcutBarComp, 
	                            public CEventRouterMap<SECATLShortcutBarHosted> 
{
typedef CEventRouterMap<SECATLShortcutBarHosted> routerBase;

	BEGIN_MSG_MAP(SECATLShortcutBarHosted)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
        CHAIN_MSG_MAP(routerBase)
    END_MSG_MAP()

public:
	inline SECATLShortcutBarHosted() {}
	inline virtual ~SECATLShortcutBarHosted() {}
	
	//@cmember
	/* Creates and initializes the non-windowed shortcutbar.*/
	inline virtual BOOL Create( IVisualWindow* pHost, RECT& rcPos, DWORD dwStyle = SEC_TABBAR_BARCURSOR)
	{
		SetHostImpl(pHost);		
		if( !SECShortcutBarComp::Create(rcPos) )
			return FALSE;
		SetBarStyle(dwStyle);
		// The IHost implementor is the default notification target for the Shortcut Bar
		SetNotifyWnd(pHost->GetWindowHandle());
		
		return TRUE;
	}

	inline CSize GetSize() const { return m_pViewport->GetSize(); }
	inline CSize SetSize(int cx, int cy) { return m_pViewport->SetSize(cx, cy); }
	inline CRect GetBounds() const { return m_pViewport->GetBounds(); }
	inline CPoint GetOrigin() const { return m_pViewport->GetOrigin();	}
	inline CPoint SetOrigin(int x, int y) { return m_pViewport->SetOrigin(x,y); }
	inline CPoint MoveOrigin(int xOff,int yOff) { return m_pViewport->MoveOrigin(xOff, yOff); }

// Message Handlers
	// A do-nothing handler for WM_SIZE, as all bound-rect changes should be made only through SECATLShortcutBarHosted's API.
	inline LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL& bHandled)
	{
		bHandled = TRUE;
		return 0L;
	}

};

}; //namespace stingray

/////////////////////////////////////////////////////////////////////////////


#endif //__ATLSHORTCUTBAR_H__
