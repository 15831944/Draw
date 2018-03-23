///////////////////////////////////////////////////////////////////////////////
// SBartool.h
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
//  Author:			Dean Hallman
//  Description:	Declarations for SECToolBar
//  Created:		May 1996
//

#ifdef WIN32

#ifndef __SBARTOOL_H__
#define __SBARTOOL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
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
// SECToolBar control

//HBITMAP AFXAPI AfxLoadSysColorBitmap(HINSTANCE hInst, HRSRC hRsrc, BOOL bMono = FALSE);

// Forward declarations
class CToolBarCtrl; // (see afxcmn.h for definition)

/////////////////////////////
// AutoDuck tag block block for SECToolBar 
// adinsert AutoDuck insertion point for SECToolBar 
//@doc SECToolBar 
//@class SECToolBar is an interface equivalent replacement for CToolBar and serves as the base class for 
// all of your tool bars.  
//@comm
// SECToolBar does nothing more than rederive from SECControlBar, so that all 
// member variables and implementation details exist to facilitate sizing while docked, etc.  No member 
// variables or functions are introduced by this class. (NOTE: All tool bars formally derived from CToolBar 
// must be rederived from SECToolBar.  No CToolBars are allowed when using Objective Toolkit’s docking window 
// enhancements as they lack the expected member variables required to perform the sizing calculations.)
//
// See the VIZ sample in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ directory for a demonstration of this class.
//@xref <c SECControlBar> <c SECDialogBar>
class SECToolBar : public SECControlBar
{
	TOOLKIT_DECLARE_DYNAMIC(SECToolBar)

// Construction
public:
	TOOLKIT_API SECToolBar();
	TOOLKIT_API BOOL Create(CWnd* pParentWnd,
		                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		                    UINT nID = AFX_IDW_TOOLBAR);
	TOOLKIT_API BOOL Create(CWnd* pParentWnd, LPCTSTR lpszWindowName,
		                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		                    DWORD dwExStyle = CBRS_EX_UNIDIRECTIONAL,
		                    UINT nID = AFX_IDW_TOOLBAR,	CCreateContext* pContext = NULL);

	TOOLKIT_API BOOL CreateEx(CWnd* pParentWnd, 
#if _MFC_VER >= 0x0600
					          DWORD dwCtrlStyle = TBSTYLE_FLAT,
#else
					          DWORD dwCtrlStyle = 0,
#endif
					          DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
					          CRect rcBorders = CRect(0, 0, 0, 0),
					          UINT nID = AFX_IDW_TOOLBAR);


	TOOLKIT_API void SetSizes(SIZE sizeButton, SIZE sizeImage);
		// button size should be bigger than image
	TOOLKIT_API void SetHeight(int cyHeight);
		// call after SetSizes, height overrides bitmap size
	TOOLKIT_API BOOL LoadToolBar(LPCTSTR lpszResourceName);
	inline BOOL LoadToolBar(UINT nIDResource) { return LoadToolBar(MAKEINTRESOURCE(nIDResource)); };
	TOOLKIT_API BOOL LoadBitmap(LPCTSTR lpszResourceName);
	inline BOOL LoadBitmap(UINT nIDResource) { return LoadBitmap(MAKEINTRESOURCE(nIDResource)); };
	TOOLKIT_API BOOL SetBitmap(HBITMAP hbmImageWell);
	TOOLKIT_API BOOL SetButtons(const UINT* lpIDArray, int nIDCount);
		// lpIDArray can be NULL to allocate empty buttons

// Attributes
public:
	// standard control bar things
	TOOLKIT_API int CommandToIndex(UINT nIDFind) const;
	TOOLKIT_API UINT GetItemID(int nIndex) const;
	TOOLKIT_API virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
	TOOLKIT_API UINT GetButtonStyle(int nIndex) const;
	TOOLKIT_API void SetButtonStyle(int nIndex, UINT nStyle);

	// for changing button info
	TOOLKIT_API void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const;
	TOOLKIT_API void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);
	TOOLKIT_API BOOL SetButtonText(int nIndex, LPCTSTR lpszText);
	TOOLKIT_API CString GetButtonText(int nIndex) const;
	TOOLKIT_API void GetButtonText(int nIndex, CString& rString) const;

	// for direct access to the underlying common control
	inline CToolBarCtrl& GetToolBarCtrl() const { return *(CToolBarCtrl*)this; };

// Implementation
public:
	TOOLKIT_API virtual ~SECToolBar();
	TOOLKIT_API virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
#ifdef _WIN64 //RW64
	TOOLKIT_API virtual LRESULT OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#endif //_WIN64
	TOOLKIT_API virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	TOOLKIT_API void SetOwner(CWnd* pOwnerWnd);
	TOOLKIT_API BOOL AddReplaceBitmap(HBITMAP hbmImageWell);
	TOOLKIT_API virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

#ifdef _MAC
	TOOLKIT_API virtual BOOL CheckMonochrome();
#endif

#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HRSRC		m_hRsrcImageWell; // handle to loaded resource for image well
	HINSTANCE	m_hInstImageWell; // instance handle to load image well from
	HBITMAP		m_hbmImageWell; // contains color mapped button images
	BOOL		m_bDelayedButtonLayout; // used to manage when button layout should be done
	BOOL		m_bFloatSizeUnknown;
	BOOL		m_bHorzDockSizeUnknown;
	BOOL		m_bVertDockSizeUnknown;
	CSize		m_sizeImage;  // current image size
	CSize		m_sizeButton; // current button size
	CMapStringToPtr* m_pStringMap;  // used as CMapStringToUInt

	// implementation helpers
	TOOLKIT_API void _GetButton(int nIndex, TBBUTTON* pButton) const;
	TOOLKIT_API void _SetButton(int nIndex, TBBUTTON* pButton);
	TOOLKIT_API CSize CalcLayout(DWORD nMode, int nLength = -1);
	TOOLKIT_API CSize CalcSize(TBBUTTON* pData, int nCount);
	TOOLKIT_API int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
	TOOLKIT_API void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
	TOOLKIT_API void Layout(); // called for for delayed button layout

	//{{AFX_MSG(SECToolBar)
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif	
    TOOLKIT_API afx_msg void OnNcPaint();
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
	TOOLKIT_API afx_msg void OnWindowPosChanging(LPWINDOWPOS);
	TOOLKIT_API afx_msg void OnSysColorChange();
	TOOLKIT_API afx_msg LRESULT OnSetButtonSize(WPARAM, LPARAM);
	TOOLKIT_API afx_msg LRESULT OnSetBitmapSize(WPARAM, LPARAM);
	TOOLKIT_API afx_msg LRESULT OnPreserveZeroBorderHelper(WPARAM, LPARAM);
	TOOLKIT_API afx_msg BOOL OnNcCreate(LPCREATESTRUCT);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API LRESULT OnSetSizeHelper(CSize& size, LPARAM lParam);

};

// Styles for toolbar buttons
#define TBBS_BUTTON     MAKELONG(TBSTYLE_BUTTON, 0) // this entry is button
#define TBBS_SEPARATOR  MAKELONG(TBSTYLE_SEP, 0)    // this entry is a separator
#define TBBS_CHECKBOX   MAKELONG(TBSTYLE_CHECK, 0)  // this is an auto check button
#define TBBS_GROUP      MAKELONG(TBSTYLE_GROUP, 0)  // marks the start of a group
#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
#if _MFC_VER >= 0x0600
#define TBBS_DROPDOWN   MAKELONG(TBSTYLE_DROPDOWN, 0) // drop down style
#define TBBS_AUTOSIZE   MAKELONG(TBSTYLE_AUTOSIZE, 0) // autocalc button width
#define TBBS_NOPREFIX   MAKELONG(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
#endif

// styles for display states
#define TBBS_CHECKED    MAKELONG(0, TBSTATE_CHECKED)    // button is checked/down
#define TBBS_PRESSED    MAKELONG(0, TBSTATE_PRESSED)    // button is being depressed
#define TBBS_DISABLED   MAKELONG(0, TBSTATE_ENABLED)    // button is disabled
#define TBBS_INDETERMINATE  MAKELONG(0, TBSTATE_INDETERMINATE)  // third state
#define TBBS_HIDDEN     MAKELONG(0, TBSTATE_HIDDEN) // button is hidden
#define TBBS_WRAPPED    MAKELONG(0, TBSTATE_WRAP)   // button is wrapped at this point
#if _MFC_VER >= 0x0600
#define TBBS_ELLIPSES   MAKELONG(0, TBSTATE_ELIPSES)
#define TBBS_MARKED     MAKELONG(0, TBSTATE_MARKED)
#endif
//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SBARTOOL_H__

#else // WIN32

#define SECToolBar CToolBar

#endif // WIN32
