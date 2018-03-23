///////////////////////////////////////////////////////////////////////////////
// sdockfrm.h
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

#ifdef WIN32

#ifndef __SDOCKFRM_H__
#define __SDOCKFRM_H__

#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
#endif

#ifndef __SMSGFILT_H__
#include "toolkit\smsgfilt.h"
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

/////////////////////////////////////////////////////////////////////////////
// SECDockableFrame frame

class SECDockableFrame : public SECFrameWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECDockableFrame)
protected:
	TOOLKIT_API SECDockableFrame();           // protected constructor used by dynamic creation

// Creation
public:

	// dynamic creation - load frame and associated resources
	TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource,
				DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
				CWnd* pParentWnd = NULL,
				CCreateContext* pContext = NULL);

// Implementation
protected:
	HMENU m_hMenuShared;        // menu when we are active

public:
	TOOLKIT_API virtual void OnUpdateFrameMenu(BOOL bActivate, CWnd* pActivateWnd,	HMENU hMenuAlt);
	TOOLKIT_API virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	TOOLKIT_API virtual BOOL DestroyWindow();

// Attributes
public:
     TOOLKIT_API virtual BOOL IsFloating() const; // returns whether parent SECControlBar is in a floating state

// operation:  enabling handler for WM_SYSCOMMANDEX
//   WM_SYSCOMMANDEX is an OTPRO extension to WM_SYSCOMMAND that allows the
//   frame type to change dynamically (mdi child, docking, floating).  An extra
//   caption button is used to automatically generate WM_SYSCOMMANDEX messages
//   for the user.  Turn on WM_SYSCOMMANDEX handling with flag SCXOPT_ENABLED.
//   Turn off the caption button with SCXOPT_ENABLED|SCXOPT_NO_CAPTION_BUTTON.  
//   Similarly, use the flag SCXOPT_NO_HANDLE_RDBLCLK to disable right double
//   click firing of WM_SYSCOMMANDEX.
//   All flags are ignored unless SCXOPT_ENABLED is used.
//   The SCXOPT_ constants are from the namespace nsSysCommandEx.
public:
     TOOLKIT_API virtual void EnableSysCommandEx(DWORD dwScxFlags);

// advanced properties:  message handling filter
//   m_pMsgFilter               -- a generic container that can have multiple sub-filters added.
//   m_pScxMsgFilterDescriptors -- table of descriptors for the msg filters needed for the WM_SYSCOMMANDEX handler
//                                 See implementation of EnableSysCommandEx() for example usage.
public:
     SECMsgFilter * m_pMsgFilter;
     SECMsgFilter::DescriptorTable m_pScxMsgFilterDescriptors;
     
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECDockableFrame)
	TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );
	//}}AFX_VIRTUAL
     #ifdef OTPRO
     // overridden to provide default handling for WM_SYSCOMMANDEX
     TOOLKIT_API virtual LRESULT DefWindowProc(UINT uiMsg, WPARAM wParam, LPARAM lParam); 
     #endif // #ifdef OTPRO

// Implementation
protected:
	TOOLKIT_API virtual ~SECDockableFrame();

	// Generated message map functions
	//{{AFX_MSG(SECDockableFrame)
	TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	TOOLKIT_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    TOOLKIT_API afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg BOOL OnNcActivate(BOOL bActive);
    TOOLKIT_API afx_msg void OnParentNotify( UINT message, LPARAM lParam );
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnNcPaint();
    TOOLKIT_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnNcRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////

#endif __SDOCKFRM_H__

#endif WIN32
