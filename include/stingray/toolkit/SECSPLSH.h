///////////////////////////////////////////////////////////////////////////////
// SECSPLSH.h
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
//  Author:		Scot Wingo
//  Description:	SECSplashWnd (Splash Window) declaration
//  Created:		Mon Jun 29 21:18:15 1995
//
//  CHANGELOG: 
//    MSW     9/30/95   Code Review, repaired minor bugs.
//	  SAD     10/5/97	32 bit Implementation merged

#ifndef __SECSPLSH_H__
#define __SECSPLSH_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECBIB_H__
#include "Foundation\Image\MFC\secdib.h"
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

#ifndef WIN32
// 16 bit Implementation of SECSplashWnd

#define IDT_SPLASHTIMER 1245


class  SECSplashWnd : public CWnd
{
// Construction
public:
    TOOLKIT_API SECSplashWnd(UINT nNewBitmapID, UINT nNewDuration = 2500);
    
// Attributes
public:
    TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd = NULL, 
		                DWORD dwStyle = WS_POPUP|WS_VISIBLE, 
						DWORD dwExStyle = WS_EX_TOPMOST);

// Implementation
    TOOLKIT_API virtual ~SECSplashWnd();
    TOOLKIT_API virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:
	TOOLKIT_API BOOL CreateDIBPalette (LPBITMAPINFO lpbmi, LPINT lpiNumColors, CPalette *pPal);


protected:
    CBitmap m_bmSplash;
    int     m_nWndWidth;
    int     m_nWndHeight;
    UINT    m_nBitmapID;
    UINT    m_nSplashTimer;
    UINT    m_nSplashDuration;
	CPalette m_Pal; 
    
// Message map functions
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg void OnTimer(SEC_UINT nTimerID);
    
    TOOLKIT_DECLARE_MESSAGE_MAP()
};
#else // End Win16 SECSplashWnd

//////////////////////////////////////////////////
// 32 bit Implementation of SECSplashWnd
// SAD 10/5/97

// SECSplashWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SECSplashWnd window

/////////////////////////////
// AutoDuck tag block block for SECSplashWnd 

// adinsert AutoDuck insertion point for SECSplashWnd 
//@doc SECSplashWnd 
//@class The SECSplashWnd class is derived from the CWnd class. It gives a ready to use
// splash window for your applications. SECSplashWnd implements a self initializing and 
// destroying splash window.  To use the splash window, the developer creates the bitmap
// and then creates an instance of SECSplashWnd.  The splash window self destructs after a 
// specified duration or if/when the user presses the mouse button on the splash window.
//@comm The SPLASH51 sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\SPLASH51 directory demonstrates how to create a
// splash window. 
//@ex Splash Window | The following example from that sample shows a typical usage of SECSplashWnd.
//Create the Splash Window first
//SECSplashWnd * pSplashWnd = new SECSplashWnd(IDB_SPLASHWND,3500);
//pSplashWnd->Create();
//pSplashWnd->ShowWindow(SW_SHOW);
//pSplashWnd->UpdateWindow();
//ASSERT(pSplashWnd != NULL);
//@BASE public|CWnd
class SECSplashWnd : public CWnd
{
// Construction

//@access Public Members
public:
	//@cmember
	/* The SECSplashWnd constructor creates an instance of the SECSplashWnd object.*/
	TOOLKIT_API SECSplashWnd(UINT nNewBitmapID, 
			     UINT nNewDuration = 2500,
			     BOOL bWaitForTimer = FALSE,
			     BOOL bAlwaysOnTop = FALSE);

	// Called after the new SECSplashWnd is instantiated. Recommended to be called
	// with default parameters.
	//@cmember
	/* This function creates the actual Splash Screen object.*/
	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd = NULL, 
						DWORD dwStyle = WS_POPUP|WS_VISIBLE, 
						DWORD dwExStyle = NULL);

	// Call before you call Create if desired
	//@cmember
	/* This function can be called to add a taskbar entry for the Splash Screen.*/
	TOOLKIT_API virtual void SetTaskbarTitle(CString strText);
	//@cmember
	/* This function may be called to dismiss the Splash Screen.*/
	TOOLKIT_API virtual void Dismiss();
	// When m_bWaitForTimer is true, the timer does not start until this function is called
	// Sets new duration for timer
	//@cmember
	/* This function is called to enable/set the Splash Screen timer.*/
	TOOLKIT_API virtual BOOL EnableTimer(UINT nNewDuration); 
	//@cmember
	/* Called to enable the Splash Screen timer.*/
	TOOLKIT_API virtual BOOL EnableTimer();	
	// Uses original timer duration
	//@cmember
	/* The Splash Screen parent may be disabled. Default: Parent enabled.*/
	TOOLKIT_API virtual void DisableParent(BOOL bDisable = TRUE);
	//@cmember
	/* The splash screent is set with the WS_EX_TOPMOST style.*/
	TOOLKIT_API virtual void SetAlwaysOnTop(BOOL bAlwaysOnTop = TRUE);
	//@cmember
	/* Sets whether the user may be allowed to dismiss the Splash Screen.*/
	TOOLKIT_API virtual void AllowUserDismiss(BOOL bAllow = FALSE);

// Attributes
protected:
	HWND	m_hWndHiddenParentWnd;
	CWnd*	m_pOwnerParentWnd;
	BOOL	m_bAllowDismiss;
	BOOL	m_bDisableParent;
	SEC_UINT	m_nSplashTimer;
	BOOL	m_bAlwaysOnTop;
	int		m_nWndHeight;
	int		m_nWndWidth;
	BOOL	m_bWaitForTimer;
	UINT	m_nSplashDuration;
	UINT	m_nBitmapID;
	BOOL	m_bWantTaskbarEntry;
	CString	m_strTaskbarTitle;
#ifndef UNDER_CE
	stingray::foundation::SECDib	m_dib;
#else
	CBitmap m_dib;
#endif
	CPalette*	m_pPalette;

	TOOLKIT_API CPalette* SetPalette(CPalette* pPalette);

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECSplashWnd)
public:
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	TOOLKIT_API virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:
	// Called after the screen is rendered in OnPaint
	TOOLKIT_API virtual void PostSplashDraw(CDC* pDC, CRect* pRect);

// Implementation
public:
	TOOLKIT_API virtual ~SECSplashWnd();

protected:

	// Generated message map functions
	//{{AFX_MSG(SECSplashWnd)
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	TOOLKIT_API afx_msg BOOL OnQueryNewPalette();
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	TOOLKIT_API afx_msg void OnClose();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // End 32 bit Implementation of SECSplashWnd

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECSPLSH_H__

