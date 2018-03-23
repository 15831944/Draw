///////////////////////////////////////////////////////////////////////////////
// secotlxmacs.h
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
// Author: Daniel Jebaraj

#ifndef __SEC_TXMACS__H__
#define __SEC_TXMACS__H__

#include "atlctl.h"

// SECOTComControl class.
// This template assumes that class T is an MFC CWnd based class.
// This will not work with anything else.
template<class T, class TOuter, class WinBase =  CWindowImpl<TOuter>  >
class SECOTComControl : public CComControl<TOuter, WinBase>
{
// to get at protected CWnd member functions
	class CFriendWnd : public CWnd
	{
		friend class SECOTComControl<T, TOuter, WinBase>;
	};
// some typdefs that make it a little easier
public:
	typedef T SECMFCBaseClass; // template arg1
	typedef TOuter __SECOuterClass; // template arg2
	typedef SECOTComControl<T, TOuter, WinBase>	secthisClass;

public:
	// will initialize the control. Called after the
	// control window is created
	// You have to implement this in a control specific manner
	virtual void InitControl() = 0;

	virtual bool CanCallOnCreate()
	{
		return true;
	}

	virtual bool CanSetWindowProc()
	{
		return true;
	}

	virtual HWND CreateControlWindow(HWND hWndParent, RECT& rcPos)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		HWND hRetval = CComControl<__SECOuterClass>::CreateControlWindow(hWndParent, rcPos);
		
		if(hRetval)
		{
			m_wndClassImpl.Attach(hRetval);
			WNDPROC proc = (WNDPROC) m_pfnSuperWindowProc;
			m_pfnSuperWindowProc = (WNDPROC) (void*)StingWndProc;
			
			if(CanSetWindowProc() == true)
				SetNewDefWindowProc(proc);
			
			InitControl();
		}
		if(CanCallOnCreate() == true)
		{
			/*Fake a call to OnCreate*/
			CWndClassInfo& cInfo = GetWndClassInfo();
			CREATESTRUCT cs;
			memset(&cs, 0, sizeof(cs));
			cs.lpszClass = cInfo.m_wc.lpszClassName;
			cs.style = (DWORD)m_wndClassImpl.GetStyle() ;
			cs.dwExStyle = (DWORD)m_wndClassImpl.GetExStyle() ;
			cs.hMenu = (HMENU)(SEC_INT)::GetDlgCtrlID(hRetval);
			cs.hInstance = cInfo.m_wc.hInstance;
			cs.hwndParent = hWndParent;
			/* call OnCreate with cooked up CREATESTRUCT*/
			CallOnCreate(&cs);
		}

		return hRetval;	
	}

	inline BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& /*hRet*/)
	{
		return ((CFriendWnd*)(&m_wndClassImpl))->PreTranslateMessage(pMsg);
	}

	
	// sets the correct DefWindowProc for the MFC window. For some controls
	// that have a special window procedure this step is essential. For most
	// others not. The default is that we will assign the ATL super procedure
	// as the DefWindowProc that will be called by AfxWndProc. This is allows
	// a top down approach without breaking anything. 
	inline void SetNewDefWindowProc(WNDPROC proc)
	{
		((CFriendWnd*)(&m_wndClassImpl))->m_pfnSuper = proc;	
	};
	

	// implementation of CallOnCreate
	virtual int CallOnCreate(CREATESTRUCT* pCs)
	{
		return ((CFriendWnd*)&m_wndClassImpl)->OnCreate(pCs);
	}

	// special window procedure that calls AfxWndProc as required
	static LRESULT CALLBACK StingWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if(hWnd == NULL)
			return 0;
		
		return AfxGetAfxWndProc()(hWnd, nMsg, wParam, lParam);
	}

	inline LRESULT OnNcDestroy(UINT /* nMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* bHandled */)
	{
		((CFriendWnd*)&m_wndClassImpl)->OnNcDestroy();
		return FALSE;
	}

	// message map that takes care of the WM_NCDESTROY message	
	BEGIN_MSG_MAP(secthisClass)
		MESSAGE_HANDLER(WM_NCDESTROY, OnNcDestroy)
		CHAIN_MSG_MAP(thisClass) // chain with base class map
	END_MSG_MAP()

// attributes
	
	SECMFCBaseClass* GetMFCWindow(){
		return &m_wndClassImpl;
	}

	// the lone data member
	// This is the actual class that you will normally use to make all calls
	// to your MFC based class. This instance can be seen as the control's
	// instance inside your ATL control
	SECMFCBaseClass m_wndClassImpl;
};

// Important Notes:
// ----------------

// It is important to note that your MFC control will not receive an OnCreate call until
// the window has been created and you explicitly make this call (refer CanCallOnCreate())
// If you do any intialization in OnCreate set the last parameter return true.
// This will generate a 'fake' OnCreateCall that should work for most controls.
// If your control does not do any initialization you can return false
// If you change any data (styles etc) in your OnCreate handler make sure that the ATL
// data structures that cache these values are updated (CWndClassInfo mostly)

// Also none of the precreation/creation function (like PreCreateWindow will be called)

// Your CWnd create will NOT be called

// PreTranslateMessage will also NOT be called except when handling ::TranslateAccelerator

#endif //__SEC_TXMACS__H__
