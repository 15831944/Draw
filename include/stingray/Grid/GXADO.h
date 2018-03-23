///////////////////////////////////////////////////////////////////////////////
// GXADO.h
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
// Authors: Praveen Ramesh, Stefan Hoenig
//

#ifndef _GXADO_H_
#define _GXADO_H_

//#if ! ( defined(_GX_VER) && _GX_VER >= 0x01000 )
//#pragma message( "Please make sure that you include Objective Grid 10.00 header files")
//#pragma message( "or a later version and not an older version header files!")
//Fatal error!
//#endif

// compile this file only if ADO is supported
#if _MFC_VER >= 0x0400 && !defined(_GX_NO_ADO_SUPPORT)

// include decls for base class
#if _MSC_VER >= 1400
	#include <adoguids.h>	// VC++ 8.0 ADO C++ header
#elif _MSC_VER <= 1310
	#include <adoid.h>		// VC++ 7.1/6.0 ADO C++ header	 
#endif

#include <adoint.h>			// ADO C++ header

#ifndef _GXMSG_H
#include "gxmsg.h"
#endif

#ifndef _GXBROWSE_H_
#include "gxbrowse.h"
#endif

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

// initialization of ADO support (obsolete)
inline void GXInitAdo(UINT uiMfcVersion) { uiMfcVersion; }  
inline void GXInitAdo() { GXInitAdo(_MFC_VER); }

// Other global helper methods
// QA 32218: Fixes crash and prevents memory leaks

GRID_API void GXGetAdoFieldString(CString& strRet, CComPtr<ADORecordset> pRecordset, int nField);
GRID_API CString GXGetFieldName(CComPtr<ADOField> pAdoField);
GRID_API CString GXGetFieldName(CComPtr<ADORecordset> pRecordset, int nIndex);
GRID_API void GXFillChoiceList(CComPtr<ADORecordset> pSet, CString& strChoiceList, BOOL bDisplayHeader);


// We do not link to adoid.lib anymore as of OG 6.1
// force linking with adoid.lib

//#ifndef _GXNOADOIDAUTOLIB
//#pragma comment(lib, "adoid.lib")
//#endif

// Replica of adoid.lib, but without the debug problem in adoid.lib...
// link to the correct version of adoid.lib
/*
#ifdef _UNICODE
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidusd.lib")
			#pragma comment(lib, "gxadoidusd.lib")
		#else
			#pragma message("gxadoidud.lib")
			#pragma comment(lib, "gxadoidud.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoidus.lib")
			#pragma comment(lib, "gxadoidus.lib")
		#else
			#pragma message("gxadoidu.lib")
			#pragma comment(lib, "gxadoidu.lib")
		#endif //_AFXDLL
	#endif//_DEBUG
#else
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidsd.lib")
			#pragma comment(lib, "gxadoidsd.lib")
		#else
			#pragma message("gxadoidd.lib")
			#pragma comment(lib, "gxadoidd.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoids.lib")
			#pragma comment(lib, "gxadoids.lib")
		#else
			#pragma message("gxadoid.lib")
			#pragma comment(lib, "gxadoid.lib")
		#endif //_AFXDLL
	#endif //_DEBUG
#endif //_UNICODE
*/
/////////////////////////////////////////////////////////////////////////////

// Some defines

#define ISOPEN(precordset)	\
	TRUE \

//statement is the statement to be executed
//recordset is a pointer to recordset to retrieve the errors if any occured
//succeded is the output param that would have true or false.
// QA 32218: Fixes crash and prevents memory leaks
#define GX_ADO_CHECK(exp, recordset, succeded)	\
	{							\
		HRESULT hr;					\
		succeded = TRUE;			\
		if(FAILED(hr = exp))		\
		{							\
			succeded = FALSE;				\
			CComPtr<ADOConnection> piConnection;	\
			CComVariant var;                       \
			recordset->get_ActiveConnection(&var);\
			piConnection = (ADOConnection *) V_DISPATCH(&var);\
			CComPtr<ADOErrors> piErrors;	\
			piConnection->get_Errors(&piErrors);	\
			long lCount;		\
			piErrors->get_Count(&lCount);	\
			CComPtr<ADOError> piError;				\
			for(int i=0; i<(int)lCount; i++)		\
			{										\
				CComVariant varIndex;				\
				varIndex.vt = VT_INT;				\
				varIndex.intVal = i;				\
				piErrors->get_Item(varIndex, &piError);	\
				CComBSTR error;							\
				piError->get_Description(&error);	\
				AfxMessageBox(CString(error));		\
			}										\
			piErrors->Clear();						\
		}							\
	}							\


/////////////////////////////////////////////////////////////////////////////
// CGXAdoParam
//
//@doc
//@class
//@base public | CGXBrowseParam
//@rem
//<c CGXAdoParam> holds specific data for the <c CGXAdoGrid>. It can be shared among several views (works the same way as < cCGXGridParam>). You can embed it in a document if you want to support several browse views on the same data, as for example in a dynamic splitter window.
//The AdoQuery sample shows you how to embed a <c CGXAdoParam> in a document, add support for opening several views on the same data, and serialize scheme information.<nl>
//<nl>
//CGXAdoParam holds the following base style ids for the named database field types: 
//<ul>
//<li>m_bsBoolean: adBoolean<eli>
//<li>m_bsNumeric: adInteger, adBigInt, adSingle, adDouble<eli>
//<li>m_bsCurrency: adCurrency<eli>
//<li>m_bsDate: adDate<eli>
//<li>m_bsText: adVarChar<eli>
//<li>m_bsBinary: adLongVarBinary<eli>
//<li>m_bsGUID: adGUID<eli>
//<li>m_bsDeletedRows for deleted rows appearance.<eli>
//<eul>
//@xref <c CGXAdoParam> <c GXBrowserGrid> <c GXAdoGrid> 
class CGXAdoParam: public CGXBrowseParam
{
	GRID_DECLARE_SERIAL(CGXAdoParam)

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
		m_bsGUID,
		m_bsChapter;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

// Implementation
public:
	int m_nTransPending;
	//@access Construction
	//@cmember 
	//Constructs a <c CGXAdoParam> object.
	GRID_API CGXAdoParam();
	GRID_API virtual ~CGXAdoParam();
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXAdoParam& operator=(const CGXAdoParam& p);
protected:
	long m_nLastRecord;
	friend class CGXAdoGrid;
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid
//
// base class which provides base functionailty for sql-query-browser-grids
//@doc
//@class
//The <c CGXAdoGrid> class provides functionality for browsing databases 
//that can be accessed through any Microsoft OLE DB provider. 
//This uses ADODB, an implementation of ADO optimized for use with Microsoft OLE DB providers. 
//Only adOpenKeyset type cursor is supported. As for any <c CGXBrowserGrid>-derived class, 
//this class lets you create MS-Query-like views where you can browse these databases.<nl>
//<nl>
//The <c CGXBrowserGrid> class maintains one current record with the current cell.  
//When the user edits data in the current record, all changes are stored in an internal buffer.
//When the user moves the current cell to another record, 
//changes for the current record are written to the attached <c ADORecordset>
//before the current cell is positioned to a new record.
//When the user clicks on the last row, a new record will be added to the <c ADORecordset>
//(if it supports appending records).<nl>
//<nl>
//The state information of the <c CGXAdoGrid> class is stored in the <c CGXAdoParam> class. 
//<c CGXAdoParam> can be shared among several views (works the same way as <c CGXGridParam>). 
//You can embed it in a document if you want to support several browse 
//views on the same data, as for example in a dynamic splitter window. 
//The AdoQuery sample provides a sample for deriving a view from <c CGXAdoGrid> and 
//shows how to add support for serializing the scheme information of the grid.<nl>
//<nl>
//CGXAdoGrid is not derived from <c CWnd>. The <c CGXAdoRecordView> class represents 
//the <c CGXAdoGrid> as view.
//The CGXAdoRecordWnd class represents the CGXAdoGrid as control.
//@base public | CGXBrowserGrid
class CGXAdoGrid : public CGXBrowserGrid
{

// Construction
public:
	//@access Construction
	//@cmember Constructs an ADO grid object.
	GRID_API CGXAdoGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	// Atributes - Ado Specific
	//@access Attributes
	//@cmember Returns a pointer to the associated <c CGXAdoParam> object. 
	GRID_API CGXAdoParam* GetAdoParam();

	//@cmember Returns a pointer to the associated <c CGXAdoParam> object. 
	GRID_API void SetRecordset(CComPtr<ADORecordset> pRecordset, BOOL bOpen = TRUE);
	GRID_API void AttachForeignTable(ROWCOL nCol, CComPtr<ADORecordset> pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

	//@access Overridables
	//@cmember Returns a pointer to the attached ADORecordset object.
	GRID_API virtual CComPtr<ADORecordset> OnGetRecordset();
	//@cmember This is a utility function that helps you create a recordset
	//pointer given the source and SQL. It creates the recordset 
	//with an adOpenKeyset-type cursor.
	GRID_API virtual CComPtr<ADORecordset> CreateRecordset(CComBSTR bstrSource,CComBSTR bstrSQL);


// Overridables - Ado specific
public:
	//@cmember Opens the recordset (only if not yet opened), 
	//initializes the columns (width, field name, length, base style) and redraws the grid.
	GRID_API virtual void OpenRecordset();
	//@cmember Called to retrieve a string with the value 
	//for the <c ADOField> bound to the specified column.
	//The string will be displayed in the grid. 
	GRID_API virtual void ConvertValueToString(ROWCOL nCol, CString& sResult);

protected:
	//@cmember
	//Called from <mf OpenRecordset> to determine the default settings for columns 
	//based on their data types. The method associates the columns with a base style, 
	//determines the column title and width.
	GRID_API virtual void OnInitColInfo(ROWCOL nCol, CComPtr<ADOField> fieldInfo, CString& strName,
		long& cbLength, WORD& wBaseStyle, BOOL* pbColumnSettingsLocked = NULL);
	//@cmember
	//This method is called from <mf OnInitColInfo> 
	//to determine the default column width in characters 
	//for the specified field type. You may override this method 
	//if you want to change the initial widths for specific data types.
	GRID_API virtual long GetDisplaySize(CComPtr<ADOField> piField);

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
	GRID_API virtual void SortRows(CGXRange sortRange, const CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

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
	
	//@cmember
	//This overridable is called from OnFlushRecord after all changed 
	//values have been flushed to the ADORecordset and just before the 
	//ADORecordset::Update method is called. 
	//You may override it if you want to do any changes in the current record of 
	//the ADORecordset before it is updated to the database
	GRID_API virtual void PreUpdateRecordset(ROWCOL nRow);

		// NOTE: You should override the previous members instead
		// of GetStyleRowCol/StoreStyleRowCol. They provide a better
		// abstraction for loading/storing cell values in a CGXBrowserGrid

		// The methods will be called appropriately from within CGXBrowserGrid::Update(),
		// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
		// CGXBrowserGrid::SetStyleRange

// CGXGridCore Overridables
protected:
	// they are called from overridden On... method in CGXAdoRecordWnd and CGXAdoRecordView
	GRID_API virtual void OnGridInitialUpdate();
	GRID_API virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);
	GRID_API virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	GRID_API virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);

	// Transactions
public:
	GRID_API virtual BOOL IsRecordsetOpen();
	GRID_API void CloseRecordset(CComPtr<ADORecordset>);
	GRID_API virtual void BeginTrans(LPCTSTR pszDescription);
	GRID_API virtual void CommitTrans();
	GRID_API virtual void Rollback();
	
	CComPtr<ADOFields> m_piFields;

protected:
	GRID_API virtual ~CGXAdoGrid();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation - Attributes
	GRID_API long SyncPosition();
	GRID_API void MoveToPosition(long nRecord, BOOL bSync = TRUE);
protected:
	BOOL m_bIsOpen;

private:
	CComPtr<ADORecordset> m_piRecordset;   // You should call OnGetRecordset to access this pointer!
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView view
//@doc
//@class
//@base public | CGXView
//@base public | CGXAdoGrid
//@rem
//The <c CGXAdoRecordView> represents the <c CGXAdoGrid> as a view for browsing and changing recordsets.<nl> 
//<nl>
//<c CGXAdoRecordView> can be used either associated with a document or stand-alone.<nl>
//<nl>
//All MFC features are supported:<nl>
//<nl>
//<np>- using the grid view in dynamic splitter windows.<enp>
//<np>- printing and print preview<enp>
//<np>- find and replace<enp>
//<np>- synchronizing several views when attached to the same document<enp>
//As <c CGXAdoRecordView> does not declare any new functions, no methods are 
//listed below by intention. Refer to the <c CGXAdoGrid>, <c CGXBrowserGrid> and <c CGXGridCore> 
//classes for information about grid methods.
//@xref <c CGXAdoGrid> <c CGXBrowserGrid> <c CGXGridCore> 
class CGXAdoRecordView : public CGXView, public CGXAdoGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	GRID_API CGXAdoRecordView();
	GRID_DECLARE_DYNCREATE(CGXAdoRecordView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	GRID_API virtual ~CGXAdoRecordView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXAdoRecordView)
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
	//{{AFX_MSG(CGXAdoRecordView)
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
	//}} AFX_MSG
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
	GRID_API afx_msg LRESULT OnAdoRequery( WPARAM wParam, LPARAM lParam );

	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXAdoGrid
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

	// resolve ambiguity between CGXGridCore and CGXView
	GRID_API CString GetTabName();
	GRID_API void SetTabName(CString s);
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd window
//@doc
//@class
//@base public | CWnd
//@base public | CGXAdoGrid
//@rem
//The <c CGXAdoRecordWnd> class represents the ADO grid browser as child control. 
//<c CGXAdoRecordWnd> can be easily used as dialog control or in a workbook window.<nl>
//<nl>
//As <c CGXAdoRecordWnd> is implemented exactly the same way as the <c CGXGridWnd> class, 
//no methods are listed below by intention. Refer to the <c CGXGridWnd> and <c CGXAdoGrid> 
//classes for information about grid window methods.
//@xref <c CGXGridWnd> <c CGXAdoGrid> <c GXBrowserGrid>
class CGXAdoRecordWnd : public CWnd, public CGXAdoGrid
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXAdoRecordWnd)

// Construction
public:
	GRID_API CGXAdoRecordWnd();
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

	//{{AFX_MSG(CGXAdoRecordWnd)
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
	GRID_API afx_msg LRESULT OnAdoRequery( WPARAM wParam, LPARAM lParam );

	GRID_DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXAdoGrid
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
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxado.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GX_NO_ADO_SUPPORT

#endif // _GXADO_H_
