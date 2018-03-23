///////////////////////////////////////////////////////////////////////////////
// GXDAO.h
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

#ifndef _GXDAO_H_
#define _GXDAO_H_

//#if ! ( defined(_GX_VER) && _GX_VER >= 0x01000 )
//#pragma message( "Please make sure that you include Objective Grid 10.00 header files")
//#pragma message( "or a later version and not an older version header files!")
//Fatal error!
//#endif

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

// Disable warnings for deprecated functions
#pragma warning (push)
#pragma warning (disable: 4995)

// include decls for base class

#include /* */ <afxdao.h>           // MFC DAO database classes

#ifndef _GXBROWSE_H_
#include "gxbrowse.h"
#endif

// #include <StingrayExportDefs.h>

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

// initialization of DAO support (obsolete)
inline void GXInitDAO(UINT uiMfcVersion) { uiMfcVersion; } 
inline void GXInitDAO() { GXInitDAO(_MFC_VER); }

// Other global helper methods

GRID_API void GXGetDaoFieldString(CString& strRet, CDaoRecordset* pRecordset, int nField, BOOL bConvertMemo = TRUE);
GRID_API CString GXGetFieldName(DAOField* pDAOField);
GRID_API CString GXGetFieldName(CDaoRecordset* pRecordset, int nIndex);
GRID_API void GXFillChoiceList(CDaoRecordset* pSet, CString& strChoiceList, BOOL bDisplayHeader);

/////////////////////////////////////////////////////////////////////////////

class CGXDaoGrid;
class CDaoRecordset;
class CGXOlePreview;


/////////////////////////////////////////////////////////////////////////////
// CGXDaoParam
//

class CGXDaoParam: public CGXBrowseParam
{
	GRID_DECLARE_SERIAL(CGXDaoParam)

public:
// Attributes - Base styles
	WORD
		m_bsBoolean,
		m_bsNumeric,
		m_bsCurrency,
		m_bsDate,
		m_bsText,
		m_bsBinary,
		m_bsMemo,
		m_bsGUID;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

	// display Memo fields (default: TRUE)
	BOOL
		m_bDisplayMemo;

	GRID_API virtual void SetIgnoreBinary(BOOL b); 
	GRID_API virtual BOOL GetIgnoreBinary() const;


// Implementation
public:
	GRID_API CGXDaoParam();
	GRID_API virtual ~CGXDaoParam();
	GRID_API virtual void Serialize(CArchive& ar);

	GRID_API virtual CGXDaoParam& operator=(const CGXDaoParam& p);
//protected:
	BOOL m_bIgnoreBinaryData;
};

// for Dao Blob data
class CGXDaoBlob : public CGXAbstractBlob
{
public:
	GRID_API CGXDaoBlob();
	GRID_API virtual ~CGXDaoBlob();
	GRID_API virtual void Cleanup(BOOL bDestruct = FALSE);
//access
	GRID_API const COleVariant* GetOleVariant();
	GRID_API void SetOleVariant(const COleVariant* pVariant);

protected:
	const COleVariant* m_pOleVariant;
};



/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid
//
// base class which provides base functionailty for sql-query-browser-grids

class CGXDaoGrid : public CGXBrowserGrid
{
// Construction
public:
	GRID_API CGXDaoGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	// Atributes - DAO Specific
	GRID_API CGXDaoParam* GetDaoParam();

	GRID_API virtual CDaoRecordset* OnGetRecordset();
	GRID_API void SetRecordset(CDaoRecordset* pSet);
	GRID_API void AttachForeignTable(ROWCOL nCol, CDaoRecordset* pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

// Overridables - DAO specific
public:
	GRID_API virtual BOOL CanUseRecordCount();
	GRID_API virtual void OpenRecordset();
	GRID_API virtual void ConvertValueToString(ROWCOL nCol, CString& sResult);

protected:
	GRID_API virtual void OnInitColInfo(ROWCOL nCol, const CDaoFieldInfo& fieldInfo, CString& strName,
		                                long& cbLength, WORD& wBaseStyle, BOOL* pbColumnSettingsLocked = NULL);
	GRID_API virtual long GetDisplaySize(const CDaoFieldInfo& fieldInfo);

// CGXBrowserGrid Overridables

public:
	// Overridables - State members
	GRID_API virtual BOOL CanUpdate();
	GRID_API virtual BOOL CanAppend();
	GRID_API virtual long OnGetRecordCount();

	// Overridables - Operations
	GRID_API virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess = NULL); 
	GRID_API virtual void Requery();
	GRID_API virtual BOOL MoveTo(ROWCOL nRow);

	// Overridables - Sorting 
	GRID_API virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

	// Wrapper methods for DeleteRows (not overridable)
	GRID_API void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API void DeleteRows(const CGXRange& range);
	
	// Handle binary data
	GRID_API virtual BOOL CheckForBinary(ROWCOL nRow, ROWCOL nCol, CGXStyle& style);
	GRID_API virtual BOOL IsPreviewField(ROWCOL nCol, const CGXStyle& style) const;
	GRID_API virtual void GetOleViewerRowCol(ROWCOL nRow, ROWCOL nCol, DWORD dwId, CGXOleViewer*& pViewer) const;
	GRID_API virtual BOOL CanHandleFieldAsBinary(int nType) const;
	GRID_API virtual void GetPreviewString(int nType, CString& strPreview) const;
	GRID_API virtual BOOL SetBinaryFlags(const CGXStyle* pStyle, int nField);

	//cache related
	GRID_API virtual BOOL OnGetBitmapHandleRowCol(ROWCOL nRow, ROWCOL nCol, HANDLE& hBitmap);
	GRID_API virtual BOOL OnUseBitmapHandleRowCol(ROWCOL nRow, ROWCOL nCol, HANDLE hBitmap);

protected:
	GRID_API virtual void OnFillCache();

	// Overridables - Events
	GRID_API virtual void OnAddedNewRecord();

	// Overridables - Load cell styles and flush values
	GRID_API virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	GRID_API virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);
	GRID_API virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL);
	GRID_API virtual void OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute);
	GRID_API virtual void PreUpdateRecordset(ROWCOL nRow);

		// NOTE: You should override the previous members instead
		// of GetStyleRowCol/StoreStyleRowCol. They provide a better
		// abstraction for loading/storing cell values in a CGXBrowserGrid

		// The methods will be called appropriately from within CGXBrowserGrid::Update(),
		// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
		// CGXBrowserGrid::SetStyleRange

// CGXGridCore Overridables
protected:
	// they are called from overridden On... method in CGXRecordWnd and CGXRecordView
	GRID_API virtual void OnGridInitialUpdate();
	GRID_API virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);

	GRID_API virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);

	// Transactions
public:
	GRID_API virtual void BeginTrans(LPCTSTR pszDescription);
	GRID_API virtual void CommitTrans();
	GRID_API virtual void Rollback();

protected:
	GRID_API virtual ~CGXDaoGrid();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation - Attributes
	GRID_API long SyncPosition();
	GRID_API void MoveToPosition(long nRecord, BOOL bSync = TRUE);

private:
	CDaoRecordset* m_pRecordset;    // You should call OnGetRecordset to access this pointer!

protected:
	COleVariant m_varLastRecord;
	long m_nLastRecord;
	CString m_strBinDescrip;
};

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordView view

class CGXDaoRecordView : public CGXView, public CGXDaoGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXDaoRecordView();
	GRID_DECLARE_DYNCREATE(CGXDaoRecordView)

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXDaoRecordView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDaoRecordView)
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
	//{{AFX_MSG(CGXDaoRecordView)
	GRID_API afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	GRID_API afx_msg BOOL OnMove(UINT nIDMoveCommand);
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
	//}}AFX_MSG
	GRID_API afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndorecord();
	GRID_API afx_msg void OnRecordDelete();
	GRID_API afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnView100();
	GRID_API afx_msg void OnViewZoomin();
	GRID_API afx_msg void OnViewZoomout();
	GRID_API afx_msg void OnFormatFreezecols();
	GRID_API afx_msg void OnFormatUnfreezecols();
	GRID_API afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXDaoGrid
public:
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void Invalidate(BOOL bErase = TRUE);
	GRID_API void UpdateWindow();
	GRID_API int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC* GetDC();
	GRID_API int ReleaseDC(CDC* pDC);
	GRID_API void GetClientRect(LPRECT lpRect);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	GRID_API void ScreenToClient(LPRECT lpRect);
	GRID_API BOOL OpenClipboard();

// resolve ambiguity between CGXGridCore and CGXView
	GRID_API CString GetTabName();
	GRID_API void SetTabName(CString s);
};


/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd window

class CGXDaoRecordWnd : public CWnd, public CGXDaoGrid
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXDaoRecordWnd)

// Construction
public:
	GRID_API CGXDaoRecordWnd();
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	GRID_API void Initialize();

	// Support for tabwnds
public:
	GRID_API static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);
	GRID_API CScrollBar* GetScrollBarCtrl(int nBar) const;

// Attributes
public:

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

	//{{AFX_MSG(CGXDaoRecordWnd)
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
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnEditUndorecord();
	GRID_API afx_msg void OnRecordDelete();
	GRID_API afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	GRID_API afx_msg BOOL OnMove(UINT nIDMoveCommand);
	GRID_API afx_msg void OnView100();
	GRID_API afx_msg void OnViewZoomin();
	GRID_API afx_msg void OnViewZoomout();
	GRID_API afx_msg void OnFormatFreezecols();
	GRID_API afx_msg void OnFormatUnfreezecols();
	GRID_API afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXDaoGrid
public:
	GRID_API void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	GRID_API void Invalidate(BOOL bErase = TRUE);
	GRID_API void UpdateWindow();
	GRID_API int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	GRID_API CDC* GetDC();
	GRID_API int ReleaseDC(CDC* pDC);
	GRID_API void GetClientRect(LPRECT lpRect);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	GRID_API CWnd* SetCapture();
	GRID_API CWnd* GetCapture();
	GRID_API void ScreenToClient(LPPOINT lpPoint);
	GRID_API void ScreenToClient(LPRECT lpRect);
	GRID_API BOOL OpenClipboard();
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxdao.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

#pragma warning (pop) //4995

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif

//

#endif // _GXDAO_H_
