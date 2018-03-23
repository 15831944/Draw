///////////////////////////////////////////////////////////////////////////////
// GXODBC.h
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

#ifndef _GXODBC_H_
#define _GXODBC_H_

//#if ! ( defined(_GX_VER) && _GX_VER >= 0x01000 )
//#pragma message( "Please make sure that you include Objective Grid 10.00 header files")
//#pragma message( "or a later version and not an older version header files!")
//Fatal error!
//#endif

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "gxctrl.h"
#endif

#ifndef _GXBROWSE_H_
#include "gxbrowse.h"
#endif

#include <afxdb.h>
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

// initialization of ODBC support
GRID_API void GXInitODBC(UINT uiMfcVersion);
	// when using GridMFC extension DLL with ODBC support under 16 Bit
	// you have to link your application with gxd6116d.lib import library
	// and call this method in OnInitInstance.
	// Otherwise, calling this method has no effect.

inline void GXInitODBC() { GXInitODBC(_MFC_VER); }

/////////////////////////////////////////////////////////////////////////////
// Win16 libraries

#ifndef _GXNOODBCAUTOLIB

#if !defined(_GXNOMSG) && _MFC_VER < 0x0300		// 16 bit
	#if !(defined(_GXDLL) || defined(_GXEXT))
		#ifndef _AFXDLL
			#ifdef _DEBUG
				#define _GXODBCLIBNAME "gxd16d.lib"
			#else
				#define _GXODBCLIBNAME "gxd16r.lib"
			#endif
		#else
			#ifdef _DEBUG
				#define _GXODBCLIBNAME "gxad16d.lib"
			#else
				#define _GXODBCLIBNAME "gxad16r.lib"
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#define _GXODBCLIBNAME "gxd6116d.lib"
		#else
			#define _GXODBCLIBNAME "gxd6116r.lib"
		#endif
	#endif

	#pragma message( "Objective Grid requires linking with " _GXODBCLIBNAME  )

#endif // !defined(_GXNOMSG) && _MFC_VER < 0x0300		// 16 bit

#endif // _GXNOODBCAUTOLIB


#if _MFC_VER < 0x0400

// see gxodbc.cpp for info on this method

#define AFX_RFX_TIMESTAMP_PSEUDO_NULL 99

GRID_API void GX_RFX_Date(CFieldExchange* pFX, const char *szName,
	TIMESTAMP_STRUCT& value);

#else

// MFC version 3.1 and greater already define this method

#define GX_RFX_Date RFX_Date

#endif

// helper routine which converts a recordset value into a string
GRID_API BOOL GXGetODBCValueString(CString& strRet, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, BOOL bConvertMemo = TRUE);
GRID_API BOOL GXWriteODBCValueString(LPCTSTR pszValue, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, CString* psWarning = NULL, BOOL bConvertMemo = TRUE);

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset recordset

class CGXODBCGrid;

// CGXFieldDesc structure
//
// provides storage buffer + some additional info for result
// columns in CGXDynamicRecordset

struct CGXFieldDesc
{
	CString strName;    // column names
	SWORD fSqlType;     // SQL type
#ifdef _WIN64
	UINT64 cbColDef;
#else	// WIN32
	UDWORD cbColDef;    // Precision
#endif	// _WIN64
	SWORD ibScale;      // scale
	SWORD fNullable;    // is column nullable
	SDWORD cbValue;
	BOOL bDirty;        // field has been changed, need update
	void* pv;           // value
	UINT nDataType;     // AFX_ SQL type

	GRID_API CGXFieldDesc();
	GRID_API ~CGXFieldDesc();
};

// CGXDynamicRecordset class
//
// enhances CRecordset class with possibility to specify
// SQL-Select-Statements at runtime.

class CGXDynamicRecordset : public CRecordset
{
	GRID_DECLARE_DYNAMIC(CGXDynamicRecordset)

public:
// Construction
	GRID_API CGXDynamicRecordset(CDatabase* pDatabase = NULL);

public:
// Attributes
	GRID_API void SetSqlQuery(LPCTSTR szSQLQuery);
	GRID_API const CString& GetSqlQuery() const;

	GRID_API void SetConnectString(LPCTSTR szConnectString);
	GRID_API const CString& GetConnectString() const;

// Values
	GRID_API BOOL GetFieldData(int nField, CString& strRet, BOOL bDisplayMemo = TRUE);
	GRID_API BOOL SetFieldData(int nField, LPCTSTR pszValue, CString* psWarning = NULL, BOOL bDisplayMemo = TRUE);
	GRID_API void FillChoiceList(CString& strChoiceList, BOOL bDisplayHeader);

// Implementation
public:
	GRID_API virtual ~CGXDynamicRecordset();

	GRID_API CGXFieldDesc& GetField(UINT nField) const;

protected:
	UINT m_nQueryFields;        // no. of result columns
	struct GRID_API CGXFieldDesc  *m_aFieldDesc;
	CString m_sSqlQuery;        // query string
	CString m_sConnectString;   // connect string

	// Cursor data

// Field/Param Data
	//{{AFX_FIELD(CGXDynamicRecordset, CRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDynamicRecordset)
public:
	GRID_API virtual CString GetDefaultConnect();    // Default connection string
	GRID_API virtual CString GetDefaultSQL();    // Default SQL for Recordset
	GRID_API virtual void PreBindFields();
	GRID_API virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
	GRID_API virtual void Close();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXDbParam
//

#if _MFC_VER >= 0x0420

// MS did change the CFieldInfo structure. I have
// to emulate it, so that I can still can access
// the information.

// For returning field info on RFX fields
struct CGXFieldInfo
{
	// For ID'ing field
	UINT nField;        // Field number
	CString strName;    // Field name
	void* pv;       // Address of value for field

	// Return info GetFieldInfo
	UINT nDataType;     // data type of field (BOOL, BYTE, etc)

	// dwSize cannot be determined in MFC 4.2 anymore
	//  DWORD dwSize;       // Max size for field data

	GRID_API CGXFieldInfo();
};

#else

#define CGXFieldInfo CFieldInfo

#endif

class CGXDbParam: public CGXBrowseParam
{
	GRID_DECLARE_SERIAL(CGXDbParam)

public:
// Attributes - Base styles
	WORD
		m_bsBoolean,
		m_bsNumeric,
		m_bsDate,
		m_bsText,
		m_bsBinary;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

	// display Memo fields (default: TRUE)
	BOOL
		m_bDisplayMemo;

	int m_nTransactionPending; // only 1 transaction allowed with ODBC

#if _MFC_VER >= 0x0420
	CGXFieldInfo* m_apFieldInfo;
#endif

// Implementation
public:
	GRID_API CGXDbParam();
	GRID_API virtual ~CGXDbParam();
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXDbParam& operator=(const CGXDbParam& p);
};

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid
//
// base class which provides base functionailty for sql-query-browser-grids

class CGXODBCGrid : public CGXBrowserGrid
{
public:
// Compatibility with 1.0
	GRID_API UINT GetFieldCol(ROWCOL nCol);

// Changed:
// virtual void Edit(long nRecord);
// virtual void Update();

// Construction
public:
	GRID_API CGXODBCGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	// Atributes - ODBC Specific
	GRID_API CGXDbParam* GetDbParam();

	GRID_API virtual CRecordset* OnGetRecordset();
	GRID_API void SetRecordset(CRecordset* pRecordset);
	GRID_API void AttachForeignTable(ROWCOL nCol, CGXDynamicRecordset* pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

// Overridables - ODBC specific
public:
	GRID_API virtual void OpenRecordset();
	GRID_API virtual void ConvertValueToString(ROWCOL nCol, CString& sResult);
	GRID_API long GetColSize(ROWCOL nCol);
	GRID_API void GetFieldData(int nField, CString& strRet);
	GRID_API void SetFieldData(int nField, LPCTSTR pszChangedValue);

protected:
	GRID_API virtual void OnInitColInfo(ROWCOL nCol, const CGXFieldInfo& fieldInfo, CString& strName,
		long& cbLength, WORD& wBaseStyle, BOOL* pbColumnSettingsLocked = NULL);
	GRID_API virtual long GetDisplaySize(const CGXFieldInfo& fieldInfo, long cbColDef);

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

protected:
	GRID_API virtual void OnFillCache();

	// Overridables - Events
	GRID_API virtual void OnAddedNewRecord();

	// Overridables - Load cell styles and flush values
	GRID_API virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	GRID_API virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);
	GRID_API virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL);
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

	GRID_API virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase);

	GRID_API virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);

	// Transactions
public:
	GRID_API virtual void BeginTrans(LPCTSTR pszDescription);
	GRID_API virtual void CommitTrans();
	GRID_API virtual void Rollback();

protected:
	GRID_API virtual ~CGXODBCGrid();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation - Attributes
protected:
	BOOL m_bRecordAppended;

private:
	CRecordset* m_pRecordset;   // You should call OnGetRecordset to access this pointer!

#if _MFC_VER >= 0x0420
	void LoadFieldInfo();
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView view

class CGXRecordView : public CGXView, public CGXODBCGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXRecordView();
	GRID_DECLARE_DYNCREATE(CGXRecordView)

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXRecordView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRecordView)
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
#ifdef _WINDU_SOURCE
public:
#endif
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
#ifdef _WINDU_SOURCE
protected:
#endif
	//{{AFX_MSG(CGXRecordView)
	GRID_API afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	GRID_API afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
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

// CWnd functions used in CGXODBCGrid
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

// remove ambiguity between CGXODBCGrid and CGXView
	GRID_API CString GetTabName();
	GRID_API void SetTabName(CString s);
};


/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd window

class CGXRecordWnd : public CWnd, public CGXODBCGrid
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXRecordWnd)

// Construction
public:
	GRID_API CGXRecordWnd();
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

	//{{AFX_MSG(CGXRecordWnd)
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

// CWnd functions used in CGXODBCGrid
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
#include "gxodbc.inl"
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

#endif // _GXODBC_H_
