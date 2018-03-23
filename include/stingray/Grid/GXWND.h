///////////////////////////////////////////////////////////////////////////////
// GXWND.h
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
// Author: Stefan Hoenig
//

#ifndef _GXWND_H_
#define _GXWND_H_

#ifndef _GXEXT_H_
#include "gxext.h"
#endif

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file

class CGXTabWnd;
class CGXGridWnd;
class CGXGridHandleWnd;
class CGXRecordInfoWnd;

/////////////////////////////////////////////////////////////////////////////
// CGXGridWnd support for dialog validation

GRID_API void AFXAPI DDV_GXGridWnd(CDataExchange* pDX, CGXGridCore* pGrid);
GRID_API void AFXAPI DDV_GXGridHandleWnd(CDataExchange* pDX, CGXGridHandleWnd* pGrid);

/////////////////////////////////////////////////////////////////////////////
// CGXGridWnd window

class CGXGridWnd : public CWnd, public CGXGridCore
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXGridWnd)

// Construction
public:
	GRID_API CGXGridWnd();
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	GRID_API void Initialize();

	// Support for tabwnds
public:
	GRID_API static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);
	GRID_API CScrollBar* GetScrollBarCtrl(int nBar) const;

// Attributes
public:
	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

// Operations
public:
	// CView Printing support
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Implementation
public:
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CGXGridWnd)
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnNcPaint();
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXGridCore
public:
	GRID_API void  InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void  Invalidate(BOOL bErase = TRUE);
	GRID_API void  UpdateWindow();
	GRID_API int   ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC*  GetDC();
	GRID_API int   ReleaseDC(CDC* pDC);
	GRID_API void  GetClientRect(LPRECT lpRect);
	GRID_API void  ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void  ScreenToClient(LPPOINT lpPoint);
	GRID_API void  ScreenToClient(LPRECT lpRect);
	GRID_API BOOL  OpenClipboard();
};

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd window

class CGXGridHandleWnd : public CWnd
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXGridHandleWnd)

// Construction
public:
	GRID_API CGXGridHandleWnd();
	GRID_API virtual ~CGXGridHandleWnd();
	GRID_API BOOL CreateGrid(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	GRID_API void Initialize();

	GRID_API void AttachGrid(CGXGridCore* pGrid);

protected:
	CGXGridCore*   m_pGrid; // this the object which contains the implementation
							// of the grid functionality

// Attributes:
public:
	GRID_API CGXGridCore* GetGrid();

	// Support for tabwnds
public:
	GRID_API static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);

// Attributes
public:
	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

// Operations
public:
	// CView Printing support
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Implementation
public:
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	GRID_API virtual void OnInitialUpdate();
	GRID_API CScrollBar* GetScrollBarCtrl(int nBar) const;
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CGXGridHandleWnd)
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg UINT OnGetDlgCode();
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnNcPaint();
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxwnd.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXWND_H_
