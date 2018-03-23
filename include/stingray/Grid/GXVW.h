///////////////////////////////////////////////////////////////////////////////
// GXVW.h : Interface of the CGXGridView class
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

#ifndef _GXVW_H_
#define _GXVW_H_

#ifndef _GXVIEW_H_
#include "gxview.h"
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

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXGridView

class CGXGridView : public CGXView, public CGXGridCore
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXGridView();
	GRID_DECLARE_DYNCREATE(CGXGridView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXGridView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXGridView)
public:
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	GRID_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	GRID_API virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	GRID_API virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	GRID_API virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	GRID_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridView)
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnMouseMove(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT flags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCopy();
	GRID_API afx_msg void OnEditPaste();
	GRID_API afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCut();
	GRID_API afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndo();
	GRID_API afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditRedo();
	GRID_API afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditFind();
	GRID_API afx_msg void OnEditReplace();
	GRID_API afx_msg void OnEditRepeat();
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXGridCore
public:
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void Invalidate(BOOL bErase = TRUE);
	GRID_API void UpdateWindow();
	GRID_API int ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC* GetDC();
	GRID_API int ReleaseDC(CDC* pDC);
	GRID_API void GetClientRect(LPRECT lpRect);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	GRID_API void ScreenToClient(LPRECT lpRect);
	GRID_API BOOL OpenClipboard();

// remove ambiguity between CGXGridCore and CGXView
	GRID_API CString GetTabName();
	GRID_API void SetTabName(CString s);

	friend class CGXPageBreakPlugin;
};


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXGridHandleView

class CGXGridHandleView : public CGXView
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXGridHandleView();
	GRID_DECLARE_DYNCREATE(CGXGridHandleView)

	GRID_API void AttachGrid(CGXGridCore* pGrid);

protected:
	CGXGridCore*   m_pGrid; // this the object which contains the implementation
							// of the grid functionality

// Attributes:
public:
	GRID_API CGXGridCore* GetGrid();

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXGridHandleView();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXGridHandleView)
public:
	GRID_API virtual void OnInitialUpdate();
	GRID_API virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	GRID_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	GRID_API virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	GRID_API virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	GRID_API virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	GRID_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	GRID_API virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	GRID_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	GRID_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridHandleView)
	GRID_API afx_msg void OnDestroy();
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnMouseMove(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT flags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT flags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	GRID_API afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCopy();
	GRID_API afx_msg void OnEditPaste();
	GRID_API afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditCut();
	GRID_API afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndo();
	GRID_API afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditRedo();
	GRID_API afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditFind();
	GRID_API afx_msg void OnEditReplace();
	GRID_API afx_msg void OnEditRepeat();
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	GRID_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxvw.inl"
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

#endif // _GXVW_H_
