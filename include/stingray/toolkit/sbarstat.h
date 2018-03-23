///////////////////////////////////////////////////////////////////////////////
// sbarstat.h
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
//  Description:	Declarations for SECStatusBar
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __SBARSTAT_H__
#define __SBARSTAT_H__

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
// SECStatusBar control

// Forward Declarations
class CStatusBarCtrl;   // forward reference (see afxcmn.h for definition)
struct AFX_STATUSPANE;  // private to implementation

/////////////////////////////
// AutoDuck tag block block for SECStatusBar 
// adinsert AutoDuck insertion point for SECStatusBar 
//@doc SECStatusBar 
//@class SECStatusBar is an interface equivalent replacement for CStatusBar and serves as the 
// base class for your application’s status bar.  
//@comm 
// SECStatusBar does nothing more than rederive from SECControlBar, so that all member variables 
// and implementation details exist as the extended control bar architecture expects.  
// No public member variables or functions are introduced by this class.  (NOTE: Any status bar 
// formally derived from CStatusBar must be rederived from SECStatusBar.  No CStatusBars are allowed 
// when using Objective Toolkit’s docking window enhancements as they lack the expected member 
// variables.)
//
// See the VIZ sample in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ directory for a demonstration of this class.
//@xref <c SECControlBar> <c SECDialogBar>

// Exported through base class. 
class SECStatusBar : public SECControlBar
{
	TOOLKIT_DECLARE_DYNAMIC(SECStatusBar)

// Construction
public:
	TOOLKIT_API SECStatusBar();
	TOOLKIT_API BOOL Create(CWnd* pParentWnd,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
		UINT nID = AFX_IDW_STATUS_BAR);
	TOOLKIT_API BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = 0,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
		UINT nID = AFX_IDW_STATUS_BAR);

	TOOLKIT_API BOOL SetIndicators(const UINT* lpIDArray, int nIDCount);

// Attributes
public:
	// standard control bar things
	TOOLKIT_API int CommandToIndex(UINT nIDFind) const;
	TOOLKIT_API UINT GetItemID(int nIndex) const;
	TOOLKIT_API void GetItemRect(int nIndex, LPRECT lpRect) const;

	// specific to SECStatusBar
	TOOLKIT_API void GetPaneText(int nIndex, CString& rString) const;
	TOOLKIT_API CString GetPaneText(int nIndex) const;
	TOOLKIT_API BOOL SetPaneText(int nIndex, LPCTSTR lpszNewText, BOOL bUpdate = TRUE);
	TOOLKIT_API void GetPaneInfo(int nIndex, UINT& nID, UINT& nStyle, int& cxWidth) const;
	TOOLKIT_API void SetPaneInfo(int nIndex, UINT nID, UINT nStyle, int cxWidth);
	TOOLKIT_API UINT GetPaneStyle(int nIndex) const;
	TOOLKIT_API void SetPaneStyle(int nIndex, UINT nStyle);
	TOOLKIT_API BOOL SetPaneWidth(int nIndex,int cxWidth);

	// for direct access to the underlying common control
	inline CStatusBarCtrl& GetStatusBarCtrl() const
		{ return *(CStatusBarCtrl*)this; }

// Overridable
	TOOLKIT_API virtual void DrawItem(LPDRAWITEMSTRUCT);

// Implementation
public:
	TOOLKIT_API virtual ~SECStatusBar();
	TOOLKIT_API virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	TOOLKIT_API BOOL PreCreateWindow(CREATESTRUCT& cs);
	TOOLKIT_API BOOL AllocElements(int nElements, int cbElement);
	TOOLKIT_API void CalcInsideRect(CRect& rect, BOOL bHorz) const;
	TOOLKIT_API virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
	// status bars do not support docking
	inline void EnableDocking(DWORD /*dwDockStyle*/) { ASSERT(FALSE); }
#endif
	TOOLKIT_API virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

protected:
	int m_nMinHeight;

	TOOLKIT_API AFX_STATUSPANE* _GetPanePtr(int nIndex) const;
	TOOLKIT_API void UpdateAllPanes(BOOL bUpdateRects, BOOL bUpdateText);
	TOOLKIT_API virtual BOOL OnChildNotify(UINT message, WPARAM, LPARAM, LRESULT*);

	//{{AFX_MSG(SECStatusBar)
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
#ifndef UNDER_CE
	TOOLKIT_API afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
#endif //UNDER_CE (WindowsCE)
	TOOLKIT_API afx_msg void OnNcPaint();
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnWindowPosChanging(LPWINDOWPOS);
	TOOLKIT_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnSetMinHeight(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SBARSTAT_H__

#else // WIN32

#define SECStatusBar CStatusBar

#endif // WIN32
