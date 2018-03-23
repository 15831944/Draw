///////////////////////////////////////////////////////////////////////////////
// gxdbegrid.h
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
// Author: Praveen Ramesh
//

#ifndef _GXDBEGRID
#define _GXDBEGRID

//
// GridMFC Extension DLL
// initialize declaration context
//

#if defined( _GXDLL)
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _GXDBENGINE
#include "grid\dbe\gxdbEngine.h"
#endif

#ifndef _GXMESMACROS_H
#include "grid\gxmesmac.h"
#endif

#ifndef __AFXADV_H__
#include "afxadv.h"
#endif

#ifndef _GXDBEPARAM
#include "grid\dbe\gxdbeprm.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#pragma warning(disable: 4193 4267 4706)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

//const int gxnFirstCtrl = 101;

template<class GRID>
class CGXDBEGrid;
/////////////////////////////////////////////////////////////////////////////
// CGXBrowseGridArrowRowHeader control

template <class GRID>
class CGXDBEGridArrowRowHeader : public CGXControl
{
public:
	CGXDBEGridArrowRowHeader(CGXDBEGrid<GRID>* pDBEGrid);

	// event handler
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

// Attributes
public:
	CBitmap m_bmPencil;
	CBitmap m_bmStar;
	CBitmap m_bmArrow;
	CGXDBEGrid<GRID>* m_pDBEGrid;
	BOOL m_bWin95Look;
};



template <class GRID> class CGXBrowserLayoutManager;
//typedef void (*GXInitDBEGridFromEngine) (CGXDBEGrid<GRID>*, CGXDBEngine*);

template <class GRID>
class CGXDBEGrid : public GRID 
{
protected: // create from serialization only
	//DECLARE_DYNCREATE(CGXDBEGrid)

public:
	CGXDBEGrid();
	virtual ~CGXDBEGrid();
// Attributes
public:
	CGXDBEngine* m_pEngine;
	
// Operations

// The following operations are based on the assumption that one database record
// corresponds to one row in the grid which is the default layout set by the CGXBrowserLayoutManager
// Instead, if a custom layout manager is used that, say, wraps a database record between 
// multiple rows then the meaning of the following functions may change or functions might
// become irrelevant.
// These operations are provided for convenience sake to operate on the data source directly
// via the grid when the above assumption is true. A better approach is to operate on the CGXDBEngine 
// associated with the grid when you need to get/set data programatically.
// Beginning of operations based on 1 record == 1 row layout assumption->
public:
	// maximum col width
	void SetMaxColWidth(int nChar);
	int GetMaxColWidth();

	// records
	ROWCOL GetFirstRow();

	ROWCOL GetFirstCol();

	BOOL IsOnLastRecord();
	BOOL IsOnFirstRecord();

	virtual BOOL IsDBValueCell(ROWCOL nRow, ROWCOL nCol);

	long GetRecordFromRow(ROWCOL nRow);

	// Fields
	short GetFieldFromCol(ROWCOL nCol);

	virtual long OnGetRecordCount();

	// The append row: could be the last row or the last but one (if currently being edited)
	virtual ROWCOL GetAppendRow();
	virtual ROWCOL GetLastRow();

	// Overridables - Operations
	virtual void DeleteRecords();
	virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd);

	virtual void Requery();

	// Wrapper methods for DeleteRows (not overridable)
	void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
	void DeleteRows(const CGXRange& range);

	// Overridables - Row/Column dereferencing
	virtual ROWCOL GetRowIndex(ROWCOL nRow);
	virtual ROWCOL GetColIndex(ROWCOL nCol);

	void AttachForeignTable(ROWCOL nCol, CString& strChoiceList, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

	// Overridables - Changing records
	virtual void Edit(ROWCOL nRow);
	virtual ROWCOL AddNew();
	virtual BOOL Update(CString* ps = NULL);

// End of operations based on 1 record == 1 row layout assumption->

	void SetCanAppend(BOOL b);

	virtual BOOL CanUpdate();
	virtual BOOL CanAppend();

	virtual void CancelRecord();
	virtual void UndoRecord();

	//added for initialization 
	void SetupUserAttributes();
	CGXDBEParam* GetDBEParam();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDBEGrid)
	public:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	protected:
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	friend class CGXBrowserLayoutManager<GRID>;
	CGXBrowserLayoutManager<GRID>* m_pLayoutManager;	// Implements the logic for the layout of the browser grid
												// and the update logic...
	// Default layout manager creation. Override this for binding custom layout manager.
	virtual void CreateLayoutManager(CGXDBEngine* pEngine);
	// Bind an engine to the grid. Mandatory to call this before initializing the grid
	void SetEngine(CGXDBEngine* pEngine, CGXBrowserLayoutManager<GRID>* pLayoutManager = NULL, BOOL bMustDelete  = TRUE);
	// Initializes the grid based on the engine parameters
	void InitFromEngine();
	virtual CGXDBEngine* GetEngine();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Overridables - Events
	virtual void OnAddedNewRecord();

	virtual void OnFillCache();
	virtual void InitBrowserSettings();

	// Overridables - Load cell styles and flush values
	virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	// CancelRecord if necessary
	virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);

// Overridables - Sorting 
public:
	virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	virtual void SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

protected:
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);


public:
	// called when text is pasted into cell
	virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);


// Implementation - CGXGridCore Overridables
public:
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);
	virtual void OnGridInitialUpdate();
	virtual void OnGridDraw(CDC* pDC);
	virtual ROWCOL GetRowCount();
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	virtual BOOL CanChangeSelection(CGXRange* range, BOOL bIsDragging, BOOL bKey);
	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	virtual BOOL Undo();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();

	virtual void OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);

	#if _MFC_VER >= 0x0400
	BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	#endif

	BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue);
	BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);

// Implementation - Rearrange the column indexes when one of the following events happen
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);

	// Rearrange the row indexes when one of the following events happen
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);

	// These special RemoveRows / RemoveCols implementations do not support undo!
	virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);

	// Implementation
protected:
	BOOL m_bUpdateDone;
	BOOL m_bCanAppend;		// Set by SetCanAppend
	BOOL m_bMustDeleteEngine; // Delete the 

// Generated message map functions
protected:
#ifdef _WINDU_SOURCE
 public:
#endif
	afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	afx_msg void OnEditUndorecord();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg BOOL OnMove(UINT nIDMoveCommand);
	afx_msg void OnFormatFreezecols();
	afx_msg void OnFormatUnfreezecols();
	afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
#ifdef _WINDU_SOURCE
 protected:
#endif
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//{{AFX_MSG(CGXDBEGrid)
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	afx_msg void OnView100();
	afx_msg LRESULT OnRequery( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

// CGXBrowserLayoutManager

// Implements the logic for the layout of the browser grid
// and the update logic...

template <class GRID>
class CGXBrowserLayoutManager
{
public:
	// Create with a grid and engine
	CGXBrowserLayoutManager(CGXDBEGrid<GRID>* pDBEGrid, CGXDBEngine* pEngine);

	//empty virtual destructor
	virtual ~CGXBrowserLayoutManager() {}
	
	// Function defenition for the function that will initilaize the layout of the 
	// grid from the engine parameters.
	// There will one implementation of this function for each implemenation of CGXDBEngine
	typedef void (*GXInitDBEGridFromEngine) (CGXDBEGrid<GRID>*, CGXDBEngine*);
	// Function pointer for the above function type
	GXInitDBEGridFromEngine m_pfInitFunction;

//Attributes
public:
	CGXDBEGrid<GRID>* m_pDBEGrid;
	CGXDBEngine* m_pEngine;
	ROWCOL m_nRecordSpan;

	// Member functions
	// Provides implementation for the layout and update logic for a browser grid.

	// Overridables - Changing records
	virtual void Edit(ROWCOL nRow);
	virtual ROWCOL AddNew();
	virtual BOOL Update(CString* ps = NULL);
	virtual void CancelRecord();
	virtual BOOL CanUpdate();
	virtual BOOL CanAppend();
	CGXDBEGrid<GRID>* Grid();
	virtual CGXDBEngine* GetEngine();
	virtual BOOL CanChangeSelection(CGXRange* range, BOOL bIsDragging, BOOL bKey);
	virtual BOOL CanCut();
	virtual BOOL CanPaste();
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue);
	virtual BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);
	virtual void DeleteRecords();
	virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd);
	virtual ROWCOL GetAppendRow();
	virtual ROWCOL GetColIndex(ROWCOL nCol);
	virtual ROWCOL GetFirstCol();
	virtual short GetFieldFromCol(ROWCOL nCol);
	virtual ROWCOL GetFirstRow();
	virtual ROWCOL GetLastRow();
	virtual long GetRecordFromRow(ROWCOL nRow);
	virtual void InitBrowserSettings();
	virtual void InitFromEngine();
	virtual BOOL IsOnFirstRecord();
	virtual BOOL IsOnLastRecord();
	virtual BOOL IsDBValueCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnAddedNewRecord();
	virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);
	virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);	
	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);
	virtual BOOL CanRecordDelete();
	virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);
	virtual void SetMaxColWidth(int nChar);
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);
	virtual ROWCOL GetRowIndex(ROWCOL nRow);
	virtual long OnGetRecordCount();
	virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);
};

// This class draws a transparant arrow bitmap in the headers.
template <class GRID>
CGXDBEGridArrowRowHeader<GRID>::CGXDBEGridArrowRowHeader(CGXDBEGrid<GRID>* pDBEGrid)
	: CGXControl(pDBEGrid)
{
	m_bmPencil.LoadBitmap(GX_IDB_PENCIL);
	m_bmStar.LoadBitmap(GX_IDB_STAR);
	m_bmArrow.LoadBitmap(GX_IDB_ARROW);

	m_pDBEGrid = pDBEGrid;

	m_bWin95Look = FALSE;
}

template <class GRID>
void CGXDBEGridArrowRowHeader<GRID>::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	// no arrow needed when printing
	if (Grid()->IsPrinting())
		return;

	// Is it the current row?
	BOOL bCurrentRow = nRow > 0 && Grid()->IsCurrentCell(nRow);

	// Is current row in edit mode?
	BOOL bPencil = m_pDBEGrid->GetEngine()->m_nEditMode != CGXDBEngine::noMode;

	// Is it the append row?
	BOOL bAppendRow = m_pDBEGrid->CanAppend()&&
			(nRow == m_pDBEGrid->GetAppendRow()                     // is it the append row?
			|| bPencil && nRow-1 == m_pDBEGrid->GetAppendRow());    // is it the row after if append row is in edit mode

	// Background
	DrawBackground(pDC, rect, style);

	// Draw button look (if not printing and not
	// explicitly specified as raised or sunken)
	if (!Grid()->IsPrinting()
		&& Grid()->GetParam()->GetProperties()->GetDisplay3dButtons()
		&& (style.GetIncludeDraw3dFrame() || style.GetDraw3dFrame() == gxFrameNormal))
	{

		if (m_bWin95Look)
		{
			// Draw Raised with better 3d-effect (looks better
			// if grid lines are turned off)
			GXDrawEdge(pDC, rect, BDR_RAISEDOUTER | BDR_RAISEDINNER);
		}
		else
		{
			COLORREF rgb3dDkShadow = RGB(0, 0, 0);
			COLORREF rgb3dHilight = GXGetSysData()->GetSysColor(COLOR_BTNHIGHLIGHT);

			// Draw Raised like a normal CGXHeader (looks better
			// when grid lines are turned on)
			GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
				rgb3dHilight, rgb3dDkShadow);
		}
	}

	// choose bitmap for the header
	CBitmap* pBitmap = NULL;

	if (bCurrentRow && bPencil)
		pBitmap = &m_bmPencil;
	else if (bAppendRow)
		pBitmap = &m_bmStar;
	else if (bCurrentRow)
		pBitmap = &m_bmArrow;

	if (pBitmap)
	{
		// Bitmap size
		BITMAP     bm;
		pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

		CPoint     ptSize;
		ptSize.x = bm.bmWidth;            // Get width of bitmap
		ptSize.y = bm.bmHeight;           // Get height of bitmap
		pDC->DPtoLP(&ptSize, 1);      // Convert from device to logical points

		// Draw bitmap
		if (rect.Width() >= ptSize.x && rect.Height() >= ptSize.x)
		{
			// must have at least the first bitmap loaded before calling DrawItem
			ASSERT(pBitmap->m_hObject != NULL);     // required

			int x = rect.left + ((1 > ((rect.Width()-ptSize.x)/2)) ? 1 : ((rect.Width()-ptSize.x)/2));
			int y = rect.top + ((1 > ((rect.Height()-ptSize.y)/2)) ? 1 : ((rect.Height()-ptSize.y)/2));

			GXDrawTransparentBitmap(pDC, // The destination DC.
				pBitmap, // The bitmap to be drawn.
				x,        // X coordinate.
				y,        // Y coordinate.
				RGB(192,192,192)); // The color for transparent
								   // pixels (white grey).

		}
	}

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}


/////////////////////////////////////////////////////////////////////////////
// CGXDBEGrid
//
// Grid bound to CGXDBEngine
//

CCEBEGIN_MESSAGE_MAP(CGXDBEGrid, GRID)
	//{{AFX_MSG_MAP(CGXDBEGrid)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND_EX(ID_RECORD_FIRST, OnMove)
	ON_COMMAND_EX(ID_RECORD_PREV, OnMove)
	ON_COMMAND_EX(ID_RECORD_NEXT, OnMove)
	ON_COMMAND_EX(ID_RECORD_LAST, OnMove)
	ON_MESSAGE(WM_GX_REQUERY, OnRequery)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDBEGrid construction/destruction

template<class GRID>
CGXDBEGrid<GRID>::CGXDBEGrid()
{
	m_bUpdateDone = FALSE;
	m_bCacheCurrentCell = TRUE;
	m_nClipboardFlags = GX_DNDTEXT; // limit clipboard support to CF_TEXT
	m_pEngine = NULL;
	m_pLayoutManager = NULL;
	m_bCanAppend = TRUE;
	m_bMustDeleteEngine = TRUE;
}

template<class GRID>
CGXDBEGrid<GRID>::~CGXDBEGrid()
{
	if(m_pEngine && m_bMustDeleteEngine)
	{
		delete m_pEngine;
		m_pEngine = NULL;
	}
		
	if(m_pLayoutManager)
		delete m_pLayoutManager;
}

template <class GRID>
BOOL CGXDBEGrid<GRID>::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return GRID::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// CGXDBEGrid<GRID> drawing

template<class GRID>
void CGXDBEGrid<GRID>::OnDraw(CDC* pDC)
{
	OnGridDraw(pDC);
}


template<class GRID>
void CGXDBEGrid<GRID>::OnInitialUpdate()
{
	// Call SetEngine in the derived class before calling the base class OnInitialUpdate...
	GRID::OnInitialUpdate();		
}

template<class GRID>
void CGXDBEGrid<GRID>::SetupUserAttributes()
{
		CGXStylesMap* stylesmap = GetParam()->GetStylesMap();
	
		// Register user attributes for the CGXStyleSheet-User Attributes page.
		// (control objects will be created on demand in CGXControlFactory).
		stylesmap->RegisterDefaultUserAttributes();
}

/////////////////////////////////////////////////////////////////////////////
// CGXDBEGrid<GRID> printing

template<class GRID>
void CGXDBEGrid<GRID>::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GRID::OnBeginPrinting(pDC, pInfo);
	// TODO: add extra initialization before printing
}

template<class GRID>
void CGXDBEGrid<GRID>::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GRID::OnEndPrinting(pDC, pInfo);

	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGXDBEGrid<GRID> diagnostics

#ifdef _DEBUG
template<class GRID>
void CGXDBEGrid<GRID>::AssertValid() const
{
	GRID::AssertValid();
}

template<class GRID>
void CGXDBEGrid<GRID>::Dump(CDumpContext& dc) const
{
	GRID::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

// Always call this before initializing the grid.
template<class GRID>
void CGXDBEGrid<GRID>::SetEngine(CGXDBEngine* pEngine, CGXBrowserLayoutManager<GRID>* pLayoutManager /* = NULL*/, BOOL bMustDelete /* = TRUE*/)
{
	if(m_pEngine && m_bMustDeleteEngine)
		delete m_pEngine;
	m_pEngine = pEngine;
	m_bMustDeleteEngine = bMustDelete;
	// Create the default LayoutManager
	if(pLayoutManager == NULL)
		CreateLayoutManager(pEngine);
	else
	{
		// Delete existing manager
		if(m_pLayoutManager)
			delete m_pLayoutManager;
		m_pLayoutManager = pLayoutManager;
	}
}

// Called to create the default LayoutManager

template<class GRID>
void CGXDBEGrid<GRID>::CreateLayoutManager(CGXDBEngine* pEngine)
{
	if(m_pLayoutManager)
		delete m_pLayoutManager;
	// Create the default LayoutManager
	m_pLayoutManager = new CGXBrowserLayoutManager<GRID>(this, pEngine);
}

template<class GRID>
CGXDBEngine* CGXDBEGrid<GRID>::GetEngine()
{
	return m_pEngine;
}

template<class GRID>
CGXDBEParam* CGXDBEGrid<GRID>::GetDBEParam()
{
	return (CGXDBEParam*)GetParam();
}
// OnGetRecordCount()
//

template<class GRID>
long CGXDBEGrid<GRID>::OnGetRecordCount()
{
	return m_pLayoutManager->OnGetRecordCount();
}

// GetRowCount()
//
// This method is called to determine the number of rows in the
// grid. The default is to return the record count and add an
// extra row if the user can append rows (marked with an asterisk '*')
// and another extra row it the user is currently adding a new record.
//
// FAQ:
// If you want that the grid fills up the entire view with
// empty cells, as for example Borland DBase does, you can
// override this method and return a bigger value.
//
// Example:
//
// ROWCOL CMyBrowserGrid::GetRowCount()
// {
//     return CGXDBEGrid<GRID>::GetRowCount()
//          + GetGridRect().Height()/GetDefaultRowHeight());
// }

template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetRowCount()
{
	return GetLastRow();
}

// GetLastRow
//
// Returns the row number for the last row.

template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetLastRow()
{
	return m_pLayoutManager->GetLastRow();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnFillCache()
{
	// Override this method if you want to add some enhanced caching.
	//
	// The first visible row in the grid can be determined with
	// ROWCOL nFirstRow = GetTopRow();
	// The last visible row can be determined with
	// ROWCOL nLastRow = CalcBottomRowFromRect(GetGridRect());
}

template<class GRID>
void CGXDBEGrid<GRID>::OnGridInitialUpdate()
{
	// check parameter object
	CGXGridParam* pParam = GetParam();

	BOOL bIsInit = FALSE;
		// bIsInit = TRUE if data need to be initialized
		// bIsInit = FALSE if this is only a new view on the same cursor

	if (pParam == NULL)
		SetParam(pParam = new CGXDBEParam);
	else
		// parameter object has already been attached in derived class, so
		// we only need to check if we must initialize it
		bIsInit = pParam->IsInit();
			// CGXGridCore::OnGridInitialUpdate() will set pParam->IsInit() = TRUE
			// So, if OnGridInitialUpdate is called for a new view on the same data,
			// bIsInit will be TRUE

//  ASSERTs improperly for DLL Debug, commented out for beta...
//	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXDBEParam)));

	CGXDBEParam* pDBEParam = GetDBEParam();
	// ASSERTION-> This is not a CGXDBEParam object.
	// You did probably use a CGXGridParam object instead. ->END

	GRID::OnGridInitialUpdate();

	BOOL bHints = m_bHintsEnabled;
	m_bHintsEnabled = FALSE;

	InitBrowserSettings();

	// Initialize pointer to some objects
	CGXStylesMap* pStyMap = pParam->GetStylesMap();
	ASSERT_VALID(pStyMap);

	CGXProperties* pProp = pParam->GetProperties();
	ASSERT_VALID(pProp);

	// Register user-defined attributes

	// Checkbox: "TRUE" is checked, "FALSE" is unchecked
	pStyMap->AddUserAttribut(GX_IDS_UA_CHECKBOX_CHECKED);
	pStyMap->AddUserAttribut(GX_IDS_UA_CHECKBOX_UNCHECKED);

	StandardStyle().SetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, _T("TRUE"));
	StandardStyle().SetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, _T("FALSE"));

	// Arrow headers should be drawn as in OG 1.0
	CGXDBEGridArrowRowHeader<GRID>* pArrowControl = (CGXDBEGridArrowRowHeader<GRID>*)
		GetRegisteredControl(GX_IDS_CTRL_BROWSEARROWHEADER);
	pArrowControl->m_bWin95Look = FALSE;

	if (!bIsInit)
	{
		// Register individual base style for any database field type
		// each database field type will have its own base style, so that
		// a field types special appearance or control type can be easily
		// changed through the base style.
		//
		// If you want for example change all dbByte columns to be associated with
		// a spin-edit control, simply call
		//      BaseStyle(pDBEParam->m_bsByte).SetControl(GX_IDS_CTRL_SPINEDIT);
		//
		// Table of base styles:
		//
		// Database Field Type  Base Style Id             String Resource Id
		// ------------------------------------------------------------------------
		// dbBoolean:           pDBEParam->m_bsBoolean     GX_IDS_STYLE_DBBOOLEAN
		// dbByte:              pDBEParam->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbInteger:           pDBEParam->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbLong:              pDBEParam->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbSingle:            pDBEParam->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbDouble:            pDBEParam->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbCurrency:          pDBEParam->m_bsCurrency    GX_IDS_STYLE_DBCURRENCY
		// dbDate:              pDBEParam->m_bsDate        GX_IDS_STYLE_DBDATE
		// dbText:              pDBEParam->m_bsText        GX_IDS_STYLE_DBTEXT
		// dbLongBinary:        pDBEParam->m_bsBinary      GX_IDS_STYLE_DBBINARY
		// dbMemo:              pDBEParam->m_bsMemo        GX_IDS_STYLE_DBMEMO
		// dbGUID:              pDBEParam->m_bsGUID        GX_IDS_STYLE_DBGUID
		//

		CGXStyle styleDefault;

		// Boolean fiels will be displayed with horizontally centered checkboxes
		pDBEParam->m_bsBoolean = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DBBOOLEAN,
						CGXStyle()
							.SetControl(GX_IDS_CTRL_CHECKBOX3D)
							.SetHorizontalAlignment(DT_CENTER)
							.SetVerticalAlignment(DT_VCENTER),
						TRUE);

		// All other field types will be displayed with the standard style settings
		pDBEParam->m_bsNumeric = pStyMap->RegisterStyle(GX_IDS_STYLE_DBNUMERIC, styleDefault, TRUE);
		pDBEParam->m_bsCurrency = pStyMap->RegisterStyle(GX_IDS_STYLE_DBCURRENCY, styleDefault, TRUE);
		pDBEParam->m_bsDate = pStyMap->RegisterStyle(GX_IDS_STYLE_DBDATE, styleDefault, TRUE);
		pDBEParam->m_bsText = pStyMap->RegisterStyle(GX_IDS_STYLE_DBTEXT, styleDefault, TRUE);
		pDBEParam->m_bsBinary = pStyMap->RegisterStyle(GX_IDS_STYLE_DBBINARY, styleDefault, TRUE);
		pDBEParam->m_bsMemo = pStyMap->RegisterStyle(GX_IDS_STYLE_DBMEMO, styleDefault, TRUE);
		pDBEParam->m_bsGUID = pStyMap->RegisterStyle(GX_IDS_STYLE_DBGUID, styleDefault, TRUE);
		pDBEParam->m_bsChapter = pStyMap->RegisterStyle(GX_IDS_STYLE_CHAPTER, styleDefault, TRUE);

		// Style for appearance of deleted rows
		pDBEParam->m_bsDeletedRows = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DELETEDROWS,
						CGXStyle()
							.SetTextColor(RGB(192,192,192))
							.SetInterior(CGXBrush().SetPattern(4))
							.SetEnabled(FALSE),
						TRUE);
		InitFromEngine();
	}

	m_bHintsEnabled = bHints;
}

// InitBrowserSettings()
//
// Call this method from your derived OnGridInitialUpdate() or
// OnInitialUpdate() routine to initialize the default browser
// grid appearance.

template<class GRID>
void CGXDBEGrid<GRID>::InitBrowserSettings()
{
	m_pLayoutManager->InitBrowserSettings();
}

// SetMaxColWidth
//
// Loops through all columns and limits its
// size to nChar characters.

template<class GRID>
void CGXDBEGrid<GRID>::SetMaxColWidth(int nChar)
{
	return m_pLayoutManager->SetMaxColWidth(nChar);
}

// GetFieldFromCol
//
// Returns the zero-based field index associated with a column.
// Performs well even if columns have been moved.
//
// Headers will return -1 !

template<class GRID>
short CGXDBEGrid<GRID>::GetFieldFromCol(ROWCOL nCol)
{
	return m_pLayoutManager->GetFieldFromCol(nCol);
}

// GetRecordFromRow
//
// Returns the zero-based row index associated with a row
// Performs well even if rows have been sorted.
//
// Headers will return -1 !
//
// NOTE: If you always take care that you use
// GetRecordFromRow/GetRowIndex before reading data out of your
// data source, you can later easyly add support for
// sorting rows (see also dbfbrows sample). You will then only
// need to rearrange the m_awRowIndex array.

template<class GRID>
long CGXDBEGrid<GRID>::GetRecordFromRow(ROWCOL nRow)
{
	return m_pLayoutManager->GetRecordFromRow(nRow);
}

// GetRowIndex
//
// GetRowIndex is usefull for sorted rows so that
// the original pointer can be dereferenced

template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetRowIndex(ROWCOL nRow)
{
	return m_pLayoutManager->GetRowIndex(nRow);
}

// GetColIndex
//
// GetColIndex is usefull for moved columns so that
// the original pointer can be dereferenced

template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetColIndex(ROWCOL nCol)
{
	return m_pLayoutManager->GetColIndex(nCol);
}

// GetFirstCol
//
// Returns the row number for the first row.
template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetFirstCol()
{
	return m_pLayoutManager->GetFirstCol();
}

template<class GRID>
int CGXDBEGrid<GRID>::GetMaxColWidth()
	{ return GetDBEParam()->m_nMaxColWidth; }


// StoreMoveCols
//
// StoreMoveCols rearranges the internal m_awColIndex
// array, when columns have been moved. If you always
// take care to call GetColIndex or GetFieldFromCol
// before acessing values, you will easily have
// support for moving columns in your browser.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed)
{
	return m_pLayoutManager->StoreMoveCols(nFromCol, nToCol, nDestCol, bProcessed);
}

// StoreRemoveCols
//
// see Note below.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed)
{
	return m_pLayoutManager->StoreRemoveCols(nFromCol, nToCol, bProcessed);
}

// StoreInsertCols
//
// see Note below.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed)
{
	return m_pLayoutManager->StoreInsertCols(nCol, nCount, bProcessed);
}

// StoreMoveRows
//
// See notes under LayoutManager Imp.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed)
{
	return m_pLayoutManager->StoreMoveRows(nFromRow, nToRow, nDestRow, bProcessed);
}

// StoreRemoveRows
//
// see Note below.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed)
{
	return m_pLayoutManager->StoreRemoveRows(nFromRow, nToRow, bProcessed);
}

// StoreInsertRows
//
// see Note below.

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed)
{
	return m_pLayoutManager->StoreInsertRows(nRow, nCount, bProcessed);
}


// RemoveCols
//
// special handling for the CGXGridCore::RemoveCols method
// as we do not support undoing this action. This would
// get too complex with external data sources.
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	// RemoveCols does not support undo!

	// Turn off undo creation
	BOOL bEnableUndo = GetParam()->IsEnableUndo();
	GetParam()->EnableUndo(FALSE);

	// Execute the command
	BOOL bSuccess =
		GRID::RemoveCols(nFromCol, nToCol, flags, ctCmd);

	// If command was succesfull, empty undo/redo list
	// so that nothing gets messed up
	if (bSuccess)
	{
		GetParam()->EmptyUndoList();
		GetParam()->EmptyRedoList();
	}

	// reenable undo support
	GetParam()->EnableUndo(bEnableUndo);

	return bSuccess;
}

// RemoveRows
//
// special handling for the CGXGridCore::RemoveRows method
// as we do not support undoing this action. This would
// get too complex with external data sources.
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	return m_pLayoutManager->RemoveRows(nFromRow, nToRow, flags, ctCmd); 
}

// GetAppendRow
//
// Returns the row number for the append row.
// GX_INVALID if not supported.
template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetAppendRow()
{
	return m_pLayoutManager->GetAppendRow();
}


// GetFirstRow
//
// Returns the row number for the first row.
template<class GRID>
ROWCOL CGXDBEGrid<GRID>::GetFirstRow()
{
	return m_pLayoutManager->GetFirstRow();
}

// IsOnFirstRecord
//
template<class GRID>
BOOL CGXDBEGrid<GRID>::IsOnFirstRecord()
{
	return m_pLayoutManager->IsOnFirstRecord();
}

// IsOnLastRecord
//
template<class GRID>
BOOL CGXDBEGrid<GRID>::IsOnLastRecord()
{
	return m_pLayoutManager->IsOnLastRecord();
}

// DeleteRecords
//
// Called to delete selected records from the data souce.
//

extern "C" static int __cdecl __gxcomparelong(const void* p1, const void* p2)
{
	long l = *(long*) p1 - *(long*) p2;

	return (l>0) ? 1 : (l<0) ? -1 : 0;
}

template<class GRID>
void CGXDBEGrid<GRID>::DeleteRecords()
{
	m_pLayoutManager->DeleteRecords();
}

template<class GRID>
void CGXDBEGrid<GRID>::DeleteRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, nFromRow);
	awRowEnd.SetAtGrow(0, nToRow);

	DeleteRows(awRowStart, awRowEnd);
}

template<class GRID>
void CGXDBEGrid<GRID>::DeleteRows(const CGXRange& range)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, range.top);
	awRowEnd.SetAtGrow(0, range.bottom);

	DeleteRows(awRowStart, awRowEnd);
}

// Using with DBTools requires turning on NOMINMAX and min/max 
// may not be available...

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

template<class GRID>
void CGXDBEGrid<GRID>::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd)
{
	m_pLayoutManager->DeleteRows(awRowStart, awRowEnd);
}


// SetCurrentCell
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags /* = GX_UPDATENOW */)
{
	if (nCol < GetFirstCol())
	{
		nCol = (GetFirstCol() < GetColCount()) ? GetFirstCol() : GetColCount();
	}

	return GRID::SetCurrentCell(nRow, nCol, flags);
}

// Requery
//
template<class GRID>
void CGXDBEGrid<GRID>::Requery()
{
	// Reset current cell's data
	TransferCurrentCell(FALSE);
	GetEngine()->Requery();
}

// Overridables - Load cell styles and flush values

// OnLoadCellStyle
//
// give the programmer the chance to load the value from data source
// or apply additional formattings at runtime
//
// NOTE: You should override the following members instead
// of GetStyleRowCol/StoreStyleRowCol. They provide a better
// abstraction for loading/storing cell values in a CGXDBEGrid

// The methods will be called when needed from 
// CGXDBEGrid<GRID>::GetStyleRowCol, CGXDBEGrid<GRID>::StoreStyleRowCol and
// CGXDBEGrid<GRID>::SetStyleRange

template<class GRID>
BOOL CGXDBEGrid<GRID>::OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue)
{
	return m_pLayoutManager->OnLoadCellStyle(nRow, nCol, style, pszExistingValue);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnCanceledEditing(ROWCOL nRow, ROWCOL nCol)
{
	m_pLayoutManager->OnCanceledEditing(nRow, nCol);
}



/////////////////////////////////////////////////////////////////////////////
// CGXGridCore overridables
template<class GRID>
void CGXDBEGrid<GRID>::OnGridDraw(CDC* pDC)
{
	// Caching
	OnFillCache();

	GRID::OnGridDraw(pDC);
}

// Check if the cell displays a DB value and not a row/col header, etc.
template<class GRID>
BOOL CGXDBEGrid<GRID>::IsDBValueCell(ROWCOL nRow, ROWCOL nCol)
{
	return m_pLayoutManager->IsDBValueCell(nRow, nCol);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	return m_pLayoutManager->GetStyleRowCol(nRow, nCol, style, mt, nType);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	return m_pLayoutManager->StoreStyleRowCol(nRow, nCol, pStyle, mt, nType);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnModifyCell(ROWCOL nRow, ROWCOL nCol)
{
	m_pLayoutManager->OnModifyCell(nRow, nCol);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	return m_pLayoutManager->CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	// Is the grid in a special mode (tracking, dragging, selecting)?
	if (GetCapture() == m_pGridWnd)
	{
		// ... give user a chance to abort this mode
		if (nChar == VK_ESCAPE)
			m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);

		// otherwise, keys cannot be processed

		return TRUE;
	}

	BOOL bRetVal = TRUE;

	if (nMessage == WM_KEYDOWN && nChar == VK_ESCAPE)
	{
		Undo();
	}

	else if (pSender == GridWnd() && nMessage == WM_KEYDOWN && nChar == VK_DELETE
		&& GetParam()->GetRangeList()->IsAnyCellFromCol(0))

		DeleteRecords();

	else if (nMessage == WM_KEYDOWN)
	{
		bRetVal = FALSE;

		BOOL bAlt = GetKeyState(VK_MENU) & 0x8000;
		BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
		BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
		WORD nAction = GetParam()->GetEnterKeyAction();

		switch (nChar)
		{
		case VK_RETURN:     // Enter
			if (nAction != GX_RIGHT)
			{
				if (!bAlt && !bCtl && !bShift && nAction != 0)
				{
					TransferCurrentCell(TRUE, GX_INVALIDATE);
					MoveCurrentCellEx(nAction, 1);
					bRetVal = TRUE;
				}
				else
					bRetVal = FALSE;
				break;
			}

			// FALL THROUGH if GX_RIGHT

		case VK_TAB:        // Tab-Key
			{
				ROWCOL nRow = 1, nCol = 1;
				GetCurrentCell(nRow, nCol);
				if (nChar == VK_RETURN || !bShift)

				{
					// Determine last column (and take care on hidden columns)
					ROWCOL ncRow = nRow, ncCol = nCol+1;
					if (!FindNextCell(GX_RIGHT, ncRow, ncCol))
						ncCol = nCol;

					// Jump to the right cell or move down a row,
					// if cell positioned at last cell
					if (nCol < ncCol)
						MoveCurrentCell(GX_RIGHT);
					else if (nRow < GetRowCount())
					{
						if (MoveCurrentCell(GX_MOSTLEFT))
							MoveCurrentCell(GX_DOWN);
					}
				}
				else
				{
					// Jump to the left cell or move up a row

					// Determine first column (and take care on hidden columns)
					ROWCOL ncRow = nRow, ncCol = (nCol > 1) ? nCol : 1 - 1;
					if (!FindNextCell(GX_LEFT, ncRow, ncCol))
					{
						ncCol = nCol;
						ncRow = (nRow > 1)?nRow:1-1;
						if (!FindNextCell(GX_UP, ncRow, ncCol))
							ncRow = nRow;
					}

					if (nCol > ncCol)
						MoveCurrentCell(GX_LEFT);
					else if (nRow > ncRow)
					{
						if (MoveCurrentCell(GX_MOSTRIGHT))
							MoveCurrentCell(GX_UP);
					}
					else
					{
						MoveCurrentCell(GX_BOTTOMRIGHT);
					}
				}
				bRetVal = TRUE;
			}
		}
	}
	else
		bRetVal = FALSE;

	if (!bRetVal)
		bRetVal = GRID::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);

	return bRetVal;
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::Undo()
{
	//CGXDBEParam* pDBEParam = GetDBEParam();

	// If the current cell has been modified and changes have not
	// been stored, Undo() simply cancels the changes.  No redo is possible

	if(GetEngine()->m_nEditMode == CGXDBEngine::addNew &&
		GetParam()->GetUndoList().IsEmpty())
	{
		CancelRecord();
		return TRUE;
	}

    if (!GetParam()->GetUndoList().GetCount())
		GetEngine()->m_bDirty = FALSE;

	return GRID::Undo();
}

// UndoRecord
//
// Cancels any pending changes in the current record and
// resets the edit- or append-mode and empties the undo/redo-list

template<class GRID>
void CGXDBEGrid<GRID>::UndoRecord()
{
	CancelRecord();

	// empty undo and redo list
	if (GetParam()->IsEnableUndo())
	{
		if (GetParam()->GetUndoList().GetCount() > 1)
			GetParam()->EmptyRedoList();
		GetParam()->EmptyUndoList();
	}
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::Update(CString* ps)
{
	return m_pLayoutManager->Update(ps);
}

template<class GRID>
ROWCOL CGXDBEGrid<GRID>::AddNew()
{
	return m_pLayoutManager->AddNew();
}

template<class GRID>
void CGXDBEGrid<GRID>::Edit(ROWCOL nRow)
{
	m_pLayoutManager->Edit(nRow);
}

template<class GRID>
void CGXDBEGrid<GRID>::SetCanAppend(BOOL bCanAppend)
{
	m_bCanAppend = bCanAppend;
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanAppend()
{
	if(!m_bCanAppend)
		return FALSE;
	else
		return m_pLayoutManager->CanAppend();
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanUpdate()
{
	return m_pLayoutManager->CanUpdate();
}


// CancelRecord
//
// Cancels any pending changes in the current record and
// resets the edit- or append-mode

template<class GRID>
void CGXDBEGrid<GRID>::CancelRecord()
{
	m_pLayoutManager->CancelRecord();
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType, const CObArray* pCellsArray, UINT flags, GXCmdType ctCmd)
{
	return m_pLayoutManager->SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnAddedNewRecord()
{
	m_pLayoutManager->OnAddedNewRecord();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol)
{
	m_pLayoutManager->OnMovedCurrentCell(nRow, nCol);
}

// OnLeftCell
//
// OnLeftCell is called after the old current cell has been deactivated.
// So, at the time this event is called, there is no current cell in
// the grid.
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol)
{
	return m_pLayoutManager->OnLeftCell(nRow, nCol, nNewRow, nNewCol);
}

//
// Cut and Paste
//
// CGXDBEGrid provides its own Cut() and Paste()
// routines as their functionality is limited.
//
//

// Cut()
// Cut() differs from the original CGXGridCore implementation
// the way that it only works cuts text form the current cell
// and not on selected ranges of cells
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanCut()
{
	return m_pLayoutManager->CanCut();
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::Cut()
{
	if (!CanUpdate())
		return FALSE;

	// make sure that there is no range selected
	if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
		return FALSE;

	// check current cell
	ROWCOL nRow, nCol;
	if (!GetCurrentCell(nRow, nCol))
		return FALSE;

	// process current cell
	CGXControl* pControl = GetControl(nRow, nCol);
	CString s;
	pControl->GetSelectedText(s);

	// copy string to clipboard (CF_TEXT format)

	CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

	clipb.Write(s, _tcslen(s) * sizeof(TCHAR));
	clipb.Write(_T("\0"), sizeof(TCHAR));
	HGLOBAL hData = clipb.Detach();

	if (hData)
	{
		if (!GridWnd()->OpenClipboard())
			return FALSE;

		if (!EmptyClipboard())
		{
			TRACE0("Failed to empty clipboard in CGXDaoGrid::Cut()\n");
			VERIFY(CloseClipboard());
			return FALSE;
		}

#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hData);
#else
		SetClipboardData(CF_TEXT, hData);
#endif
		VERIFY(CloseClipboard());

		if (pControl->IsActive())
			// replace selected text
			pControl->ReplaceSel(_T(""));
		else
			// ... or entire content of current cell
			SetControlTextRowCol(nRow, nCol, _T(""), GX_UPDATENOW);

		return TRUE;
	}

	return TRUE;
}

//
// Paste()
// Paste() differs from the original CGXGridCore implementation
// the way that it only works pastes text into the current cell
// and not on selected ranges of cells
//

template<class GRID>
BOOL CGXDBEGrid<GRID>::Paste()
{
	if (!CanUpdate() || IsReadOnly())
		return FALSE;

	CGXDBEParam* pDBEParam = GetDBEParam();

	if (pDBEParam->m_bAllowPasteMultiCells)
	{
		// make sure that there is no range selected
		if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
			return FALSE;

		// check current cell
		ROWCOL nRow, nCol;
		if (!GetCurrentCell(nRow, nCol))
			return FALSE;

		// do not use GX_DNDSTYLES
		m_nClipboardFlags = m_nClipboardFlags & ~GX_DNDSTYLES; 

		BOOL bSuccess = GRID::Paste();

		if (GetEngine()->m_nEditMode == CGXDBEngine::noMode)
			Update();

		SetCurrentCell(nRow, nCol);

		return bSuccess; 
	}
	else
	{
		// make sure that there is no range selected
		if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
		{
			if(GetParam()->GetRangeList()->GetCount() == 1 && GetParam()->GetExcelLikeCurrentCell())
			{
				//check if range is a single cell
				CGXRange* pRange = (CGXRange*)GetParam()->GetRangeList()->GetTail();
				if(!((pRange->GetWidth() == 1)&&(pRange->GetHeight() == 1)))
				{
					//more than one cell in range so disable
					return FALSE;
				}
			}
			else //More than one range so disable paste
				return FALSE;
		}

		// check current cell
		ROWCOL nRow, nCol;
		if (!GetCurrentCell(nRow, nCol))
			return FALSE;

		const CGXStyle& style = LookupStyleRowCol(nRow, nCol);
		if (style.GetIncludeReadOnly() && style.GetReadOnly())
			return FALSE;

		CGXControl* pControl = GetRegisteredControl(style.GetControl());

		if (!GridWnd()->OpenClipboard())
		{
			TRACE0("Failed to open Clipboard in CGXDaoGrid::Paste()\n");
			return FALSE;
		}

		HGLOBAL handle = 0;
	#ifdef _UNICODE
		handle = GetClipboardData(CF_UNICODETEXT);
	#else
		handle = GetClipboardData(CF_TEXT);
	#endif

		LPTSTR psz = NULL;

		if (handle && (psz = (LPTSTR) GlobalLock(handle)) != NULL)
		{
			// make sure control is active
			if (!pControl->IsActive())
				pControl->SetActive(TRUE);

			// replace selected text
			// ReplaceSel also ensures that text is not too long.
			pControl->ReplaceSel(psz);
			// redraw the cell with new text
			pControl->Refresh();

			GlobalUnlock(handle);
		}

		CloseClipboard();

		return TRUE;
	}
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanPaste()
{
	return m_pLayoutManager->CanPaste();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase,
		LPCTSTR lpszReplace)
{
	CGXDBEParam* pDBEParam = GetDBEParam();

	if (!CanUpdate())
		return;

	// Force updating row after change
	pDBEParam->m_bUpdateOnStore = TRUE;
		// SetStyleRange will later check and reset this flag

	GRID::OnReplaceSel(lpszFind, bNext, bCase, lpszReplace);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase)
{
	m_pLayoutManager->OnReplaceAll(lpszFind, lpszReplace, bCase);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey)
{
	//CGXDBEParam* pDBEParam = GetDBEParam();

	if(!m_pLayoutManager->CanChangeSelection(pRange, bIsDragging, bKey))
		return FALSE;

	return GRID::CanChangeSelection(pRange, bIsDragging, bKey);
}

// OnMove
//
// Move the current cell

template<class GRID>
BOOL CGXDBEGrid<GRID>::OnMove(UINT nIDMoveCommand)
{
	switch (nIDMoveCommand)
	{
		case ID_RECORD_PREV:
			MoveCurrentCell(GX_UP);
			break;

		case ID_RECORD_FIRST:
			MoveCurrentCell(GX_TOP);
			break;

		case ID_RECORD_NEXT:
			MoveCurrentCell(GX_DOWN);
			break;

		case ID_RECORD_LAST:
			MoveCurrentCell(GX_BOTTOM);
			break;

		default:
			// Unexpected case value
			ASSERT(FALSE);
	}

	return TRUE;
}

template<class GRID>
LRESULT CGXDBEGrid<GRID>::OnRequery(WPARAM , LPARAM )
{
	BOOL bLock = LockUpdate();

	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);

	Requery();

	LockUpdate(bLock);
	Redraw();
	return 0;
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	if (GetParam() == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// enable if opened, can scroll backwards,
	pCmdUI->Enable(!IsOnFirstRecord());
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	OnUpdateRecordFirst(pCmdUI);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	if (GetParam() == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	OnUpdateRecordLast(pCmdUI);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	if (GetParam() == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// enable if opened and not already on last record
	pCmdUI->Enable(!IsOnLastRecord());
}

template<class GRID>
void CGXDBEGrid<GRID>::OnRecordDelete()
{
	DeleteRecords();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	if (GetParam() == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	pCmdUI->Enable(m_pLayoutManager->CanRecordDelete());
}


// Undo current record
template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXDBEParam* pDBEParam = GetDBEParam();

	pCmdUI->Enable(GetParam() && GetEngine()->m_nEditMode != CGXDBEngine::noMode);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnEditUndorecord()
{
	CGXDBEParam* pDBEParam = GetDBEParam();

	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
		UndoRecord();
}

// Sorting

template<class GRID>
void CGXDBEGrid<GRID>::SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	m_pLayoutManager->SortRows(sortRange, sortInfo, flags);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	return m_pLayoutManager->StoreMoveDataRows(sortRange, awRowIndex);
}

template<class GRID>
void CGXDBEGrid<GRID>::SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Sort the grid with the columns specified in awCols.

	OnTestGridDimension(0, GX_MAXROWCOL);

	if (sortRange.IsTable())
		sortRange.SetCols(GetFirstCol(), GetColCount());

	GRID::SortCols(sortRange, sortInfo, flags);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex)
{
	return m_pLayoutManager->StoreMoveDataCols(sortRange, awColIndex);
}

#if _MFC_VER >= 0x0400

template<class GRID>
BOOL CGXDBEGrid<GRID>::OnGridDrop(CGXNoOleDataObjectProxy* pDataObject,
	DROPEFFECT dropEffect, CPoint point)
{
	if (!GetDBEParam()->m_bCanStoreGridCellInCGXData
		&& (m_dwDndDropTargetFlags & GX_DNDSTYLES) != 0)
	{
		ASSERT(0);
		// ASSERT-> Pasting style information is not supported
		// with browser grids unless m_bCanStoreGridCellInCGXData is TRUE ->END
	
		return FALSE;
	}

	if (dropEffect == DROPEFFECT_COPY)
		// OnGridDrop will efficiently redraw the grid
		return GRID::OnGridDrop(pDataObject, dropEffect, point);
	else
	{
		// We have to redraw the whole grid
		BOOL bLock = LockUpdate(TRUE);
		BOOL bRet = GRID::OnGridDrop(pDataObject, dropEffect, point);
		LockUpdate(bLock);
		Redraw(GX_INVALIDATE);
		
		return bRet;
	}
}

#endif

template<class GRID>
void CGXDBEGrid<GRID>::AttachForeignTable(ROWCOL nCol, CString& strChoiceList, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader)
{
	ASSERT(nCol > 0 && nCol <= GetColCount());

	CGXWaitCursor theWait;

	TransferCurrentCell();

	CGXTabbedComboBox::ResetChoiceMap(GetParam(), (int) nCol);

	SetStyleRange(CGXRange().SetCols(nCol),
		CGXStyle()
			.SetControl(GX_IDS_CTRL_TABBED_COMBOBOX)
			.SetChoiceList(strChoiceList)
			.SetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL, (LONG) nKeyCol)
			.SetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL, (LONG) nDispCol)
			.SetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS, (LONG) bDispAllCols)
			.SetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW, (LONG) bDisplayHeader)
			.SetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID, nCol)
		);

	// Reinit current cell
	TransferCurrentCell(FALSE);
}


template<class GRID>
BOOL CGXDBEGrid<GRID>::ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue)
{
	return m_pLayoutManager->ClearCells(selList, bStyleOrValue);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range)
{
	return m_pLayoutManager->PasteTextFromBuffer(psz, size, range);
}

template<class GRID>
BOOL CGXDBEGrid<GRID>::SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	return m_pLayoutManager->SetControlTextRowCol(nRow, nCol, str, nFlags, pOldStyle);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol)
{
	m_pLayoutManager->OnTestGridDimension(nLastRow, nLastCol);
}

template<class GRID>
void CGXDBEGrid<GRID>::InitFromEngine()
{
	m_pLayoutManager->InitFromEngine();
}

template<class GRID>
//P make it inline
BOOL CGXDBEGrid<GRID>::SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt, int nType, UINT flags)
	{ return SetStyleRange(range, &style, mt, nType, NULL, flags); }


/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions

template<class GRID>
void CGXDBEGrid<GRID>::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	OnGridPrepareDC(pDC, pInfo);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	OnGridUpdate(pSender, lHint, pHint);
}


template<class GRID>
void CGXDBEGrid<GRID>::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers
template<class GRID>
void CGXDBEGrid<GRID>::OnFormatFreezecols()
{
	FreezeCols();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnViewZoomin() 
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);	
	
}

template<class GRID>
void CGXDBEGrid<GRID>::OnViewZoomout() 
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

template<class GRID>
void CGXDBEGrid<GRID>::OnView100() 
{
	SetZoom(100);
}


/////////////////////////////////////////////////////////////////////////////


// Create with grid and engine
template<class GRID>
CGXBrowserLayoutManager<GRID>::CGXBrowserLayoutManager(CGXDBEGrid<GRID>* pDBEGrid, CGXDBEngine* pEngine)
{
	m_pDBEGrid = pDBEGrid;
	m_pEngine = pEngine;
	m_nRecordSpan = 1;
}

// Accessor functions
template<class GRID>
CGXDBEGrid<GRID>* CGXBrowserLayoutManager<GRID>::Grid()
{
	ASSERT(m_pDBEGrid != NULL);
	return m_pDBEGrid;
}

template<class GRID>
CGXDBEngine* CGXBrowserLayoutManager<GRID>::GetEngine()
{
//	ASSERT(m_pEngine != NULL);
	return m_pEngine;
}


template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::Update(CString* ps)
{
	int editMode = GetEngine()->m_nEditMode;
	if(editMode == CGXDBEngine::noMode)
	{
		TRACE0("Error: must enter Edit or AddNew mode before updating.\n");
		if (ps)
			*ps = _T("Error: must enter Edit or AddNew mode before updating.");
		return FALSE;
	}

	if (!Grid()->TransferCurrentCell())
		return FALSE;

	BOOL bUpdate = GetEngine()->Update(ps);
	// If successful and if new row added
	if(bUpdate && editMode == CGXDBEngine::addNew)
		Grid()->OnAddedNewRecord();

	// Reset internal edit mode
	Grid()->m_bUpdateDone = TRUE;

	// Redraw the whole record
	Grid()->RedrawRowCol(CGXRange().SetRows(Grid()->GetDBEParam()->m_nCurrentRow), GX_INVALIDATE);
	return bUpdate;
}

template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::AddNew()
{
	if (!Grid()->CanAppend())
		AfxThrowNotSupportedException();

	// empty edit buffer, change edit mode
	Grid()->CancelRecord();

	// Make sure all records are fetched.
	GetEngine()->FetchRecords(GX_MAXROWCOL);

	ROWCOL nAppendRow = Grid()->GetAppendRow();

	if (!Grid()->IsCurrentCell(nAppendRow, GX_INVALID))
		Grid()->SetCurrentCell(nAppendRow, Grid()->GetFirstCol());

	long lAppendRow = GetEngine()->AddRow();

	ASSERT((ROWCOL)lAppendRow == (ROWCOL)Grid()->GetRecordFromRow(nAppendRow));
	Grid()->GetDBEParam()->m_nCurrentRow = nAppendRow;

	// if last row is not completely visible, scroll down one row
	BOOL bLastRowVisible;
	ROWCOL nBottomRow = Grid()->CalcBottomRowFromRect(Grid()->GetGridRect(), bLastRowVisible);

	ROWCOL nCurrentRow, nCurrentCol;
	Grid()->GetCurrentCell(nCurrentRow, nCurrentCol);
	BOOL bScroll = (!bLastRowVisible && nBottomRow >= nCurrentRow - 1);

	// avoid flickering because of possible scrollbar interactions
	Grid()->LockScrollbars(TRUE);

	// update the screen with an appended row
	Grid()->UpdateInsertRows(nCurrentRow + m_nRecordSpan, m_nRecordSpan, GX_INVALIDATE, TRUE);
	Grid()->RedrawRowCol(nCurrentRow, 0, GX_UPDATENOW, TRUE);

	if (bScroll)
		Grid()->OnScrollBecauseOfEdit(GX_DOWN, 1);

	// reenable scrollbars and update them
	Grid()->LockScrollbars(FALSE);
	return lAppendRow;
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::Edit(ROWCOL nRow)
{
	CancelRecord();

	GetEngine()->FetchRecords(GetRecordFromRow(nRow) + 1);
	
	if (!Grid()->IsCurrentCell(nRow, GX_INVALID))
		Grid()->SetCurrentCell(nRow, Grid()->GetFirstCol());

	// Check if we could succesfully intiate an edit mode.
	if(!GetEngine()->Edit(Grid()->GetRecordFromRow(nRow)))
	{
		TRACE0("Failed to initiate edit mode in CGXDBEngine.\n");
		return;
	}
	Grid()->GetDBEParam()->m_nCurrentRow = nRow;

	Grid()->RedrawRowCol(nRow, 0, GX_INVALIDATE);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanAppend()
{
	return GetEngine()->CanAppend();
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanUpdate()
{
	return GetEngine()->CanUpdate();
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::CancelRecord()
{
	CGXDBEngine* pEngine = GetEngine();

	if (pEngine->m_nEditMode == CGXDBEngine::addNew)
	{
		ROWCOL nNewRow = Grid()->GetDBEParam()->m_nCurrentRow;
		pEngine->CancelRecord();

		// Turn off updating for smoother drawing when grid
		// needs to be scrolled.
		BOOL bLockUpdate = FALSE;
		BOOL bLock = (Grid()->GetTopRow() >= Grid()->GetFirstRow());

		if (bLock)
			bLockUpdate = Grid()->LockUpdate(TRUE);

		Grid()->LockScrollbars(TRUE);
		ROWCOL nStart = nNewRow + m_nRecordSpan;
		Grid()->UpdateRemoveRows(nStart, nStart + m_nRecordSpan - 1, NULL, GX_UPDATENOW, TRUE);
		Grid()->TransferCurrentCell(FALSE, GX_UPDATENOW, FALSE);
		nStart = nNewRow;
		Grid()->RedrawRowCol(CGXRange().SetRows(nStart, nStart + m_nRecordSpan - 1));
		Grid()->LockScrollbars(FALSE);

		if (bLock)
		{
			// Redraw whole screen and update scrollbars all at once
			Grid()->LockUpdate(bLockUpdate);
			Grid()->Redraw();
		}
		else
			// refresh formula cells 
			Grid()->RefreshViews();

	}
	else if (pEngine->m_nEditMode == CGXDBEngine::edit)
	{
		pEngine->CancelRecord();
		Grid()->TransferCurrentCell(FALSE, GX_UPDATENOW, FALSE);
		ROWCOL nStart = Grid()->GetDBEParam()->m_nCurrentRow;
		Grid()->RedrawRowCol(CGXRange().SetRows(nStart, nStart + m_nRecordSpan - 1), GX_INVALIDATE);
	}
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanChangeSelection(CGXRange* pRange, BOOL /*bIsDragging*/, BOOL /*bKey*/)
{
	// update current row if user selects a new range

	// skip if user is selecting columns or has not changed
	// data in current row

	if (pRange != NULL && !pRange->IsCols() && GetEngine()->m_nEditMode != CGXDBEngine::noMode)
	{
		Grid()->TransferCurrentCell();
		CString s;
		BOOL bOK = Grid()->Update(&s);
		// Update will catch exception
		if (!s.IsEmpty())
			Grid()->SetWarningText(s);

		if (!bOK)
			return FALSE;
	}

	return TRUE;
}


template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanCut()
{
	if (!(GetEngine() && Grid()->CanUpdate()))
		return FALSE;

	// make sure that there is no range selected
	if (Grid()->GetParam() && Grid()->GetParam()->GetRangeList()->GetCount() > 0)
		return FALSE;

	return Grid()->IsCurrentCell();
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanPaste()
{
	if (!(GetEngine() && Grid()->CanUpdate()) || Grid()->IsReadOnly())
		return FALSE;

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();
	if (pDBEParam->m_bAllowPasteMultiCells)
		// don't call CGXDBEGrid
		return Grid()->GRID::CanPaste(); 

	else
	{
		// make sure that there is no range selected
		if (Grid()->GetParam() && Grid()->GetParam()->GetRangeList()->GetCount() > 0)
		{
			if(Grid()->GetParam()->GetRangeList()->GetCount() == 1 && Grid()->GetParam()->GetExcelLikeCurrentCell())
			{
				//check if range is a single cell
				CGXRange* pRange = (CGXRange*)Grid()->GetParam()->GetRangeList()->GetTail();
				if(!((pRange->GetWidth() == 1)&&(pRange->GetHeight() == 1)))
				{
					//more than one cell in range so disable
					return FALSE;
				}
			}
			else //More than one range so disable paste
				return FALSE;
		}
		return IsClipboardFormatAvailable(CF_TEXT);
	}
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	if (!Grid()->GRID::CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol))
		return FALSE;

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	pDBEParam->m_bUpdateOnStore = FALSE;

	ROWCOL nCurRow, nCurCol;

	// If current row has been changed and current cell is positioned to a new row
	if (!bSelect && GetEngine()->m_nEditMode != CGXDBEngine::noMode && dwSelectRow && dwSelectRow != dwOldRow)
	{
		Grid()->m_bUpdateDone = FALSE;

		// ... and if current cell is active
		if (Grid()->GetCurrentCell(nCurRow, nCurCol) && Grid()->GetControl(nCurRow, nCurCol)->GetModify())
			// set a flag which tells StoreStyleRowCol to update the cursor
			pDBEParam->m_bUpdateOnStore = TRUE;
		else
		{
			CString s;
			if (!Grid()->Update(&s))
			{
				if (!s.IsEmpty())
					Grid()->SetWarningText(s);
				return FALSE;
			}
		}
	}

	return TRUE;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue)
{
	if (!Grid()->GetDBEParam()->m_bCanStoreGridCellInCGXData && bStyleOrValue)
	{
		ASSERT(0);
		// ASSERT-> Clearing out style information is not supported
		// with browser grids unless m_bCanStoreGridCellInCGXData is TRUE ->END
	
		return FALSE;
	}

	// determine affected rows for efficient redrawing
	ROWCOL nTop = GX_INVALID, nBottom = GX_INVALID;

	if (selList.GetCount() == 1)
	{
		ROWCOL nRow, nCol;
		Grid()->GetCurrentCell(nRow, nCol);

		nTop = (nRow < selList.GetHead()->top) ? nRow : selList.GetHead()->top;
		nBottom = (nRow > selList.GetHead()->bottom) ? nRow : selList.GetHead()->bottom;
	}

	// CGXGridCore::ClearCells screen update is too optimized - with
	// CGXDBEGrid we always have to redraw complete rows
	// and not individual cells

	BOOL bLock = Grid()->LockUpdate(TRUE);
	BOOL bRet = Grid()->GRID::ClearCells(selList, FALSE);
	Grid()->LockUpdate(bLock);

	// Our own update of the screen
	if (nTop != GX_INVALID)
	{
		Grid()->RedrawRowCol(CGXRange().SetRows(nTop, nBottom), GX_INVALIDATE);
		// refresh formula cells 
		Grid()->RefreshViews();
	}
	else
		Grid()->Redraw(GX_INVALIDATE);

	return bRet;
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::DeleteRecords()
{
	CGXRangeList* pSelList = Grid()->GetParam()->GetRangeList();

	if (!Grid()->CanUpdate() || Grid()->IsReadOnly())
		return;

	// check that whole rows are selected and that "new row" is not selected
	if (!pSelList->IsAnyCellFromCol(0)
		|| pSelList->IsAnyCellFromRow( GetAppendRow() )
		)
		return;

	CRowColArray awRowStart, awRowEnd;
	Grid()->GetSelectedRows(awRowStart, awRowEnd, TRUE, FALSE);

	Grid()->DeleteRows(awRowStart, awRowEnd);
}

template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetAppendRow()
{
	if (!Grid()->CanAppend() || !GetEngine()->IsEOFSeen())
		return GX_INVALID;

	return (ROWCOL) (Grid()->OnGetRecordCount() * m_nRecordSpan) + Grid()->GetFirstRow();
}

// GetFirstCol
//
// Returns the col number for the first DB Value holding col.
template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetFirstCol()
{
	return Grid()->GetHeaderCols()+1;
}


template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetColIndex(ROWCOL nCol)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	if (nCol >= (ROWCOL) INT_MAX)
		return nCol;

	int n = (int) nCol;

	// if there is no reference stored, simply
	// return the passed reference

	// as long as a column has not been moved
	// to another place, it will be zero and
	// therefore this method will return the
	// original column id.

	if (n <= pDBEParam->m_awColIndex.GetUpperBound()
		&& pDBEParam->m_awColIndex[n] != 0)
	{
		return pDBEParam->m_awColIndex[n];
	}

	return nCol;
}

template<class GRID>
short CGXBrowserLayoutManager<GRID>::GetFieldFromCol(ROWCOL nCol)
{
	return (short) (GetColIndex(nCol) - Grid()->GetFirstCol());	// return value is 0 based.
}


template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetFirstRow()
{
	return Grid()->GetHeaderRows()+1;
}

template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetLastRow()
{
	// estimate record count (if not yet known)

	long lCount = Grid()->OnGetRecordCount();

	if (GetEngine() && GetEngine()->IsEOFSeen())
	{
		if (!Grid()->IsPrinting())
		{
			if (Grid()->CanAppend())
				lCount++;

			if (GetEngine()->m_nEditMode == CGXDBEngine::addNew)
				lCount++;
		}
	}

	return (lCount*m_nRecordSpan) + Grid()->GetFirstRow() - 1;
}

template<class GRID>
long CGXBrowserLayoutManager<GRID>::GetRecordFromRow(ROWCOL nRow)
{
	return (long) Grid()->GetRowIndex(nRow) - (long) Grid()->GetFirstRow();
}

template<class GRID>
ROWCOL CGXBrowserLayoutManager<GRID>::GetRowIndex(ROWCOL nRow)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	if (nRow >= (ROWCOL) INT_MAX)
		return nRow;

	int n = (int) nRow;

	// if there is no reference stored, simply
	// return the passed reference

	// as long as a row has not been moved
	// to another place, it will be zero and
	// therefore this method will return the
	// original row id.

	if (n <= pDBEParam->m_awRowIndex.GetUpperBound()
		&& pDBEParam->m_awRowIndex[n] != 0)
	{
		return pDBEParam->m_awRowIndex[n];
	}

	return nRow;
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::InitBrowserSettings()
{
	// Initialize pointer to some objects
	CGXGridParam* pParam = Grid()->GetParam();
	ASSERT_VALID(pParam);

	CGXStylesMap* pStyMap = pParam->GetStylesMap();
	ASSERT_VALID(pStyMap);

	CGXProperties* pProp = pParam->GetProperties();
	ASSERT_VALID(pProp);

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();
	ASSERT_VALID(pDBEParam);

	// Register user-defined controls
	Grid()->RegisterControl(
			GX_IDS_CTRL_BROWSEARROWHEADER,
			new CGXDBEGridArrowRowHeader<GRID>(Grid())
		);

	if (!pDBEParam->m_bIsBrowseInit)
	{
		BOOL bUndo = Grid()->GetParam()->IsEnableUndo();
		Grid()->GetParam()->EnableUndo(FALSE);

		// Following settings should only be initialized the first
		// time OnInitialUpdate is called. This is especially
		// usefull if the parameter-object is shared among
		// several views (MFC doc/view support) because OnInitialUpdate
		// is called for every new view.

		// Row and column headers
		Grid()->ColHeaderStyle()
					.SetReadOnly(FALSE)
					.SetEnabled(FALSE); // Current cell cannot be moved to header

		Grid()->RowHeaderStyle()
					.SetEnabled(FALSE)
					.SetControl(GX_IDS_CTRL_BROWSEARROWHEADER); // use previously registered header control

		// Special grid settings
		pParam->EnableMoveRows(FALSE);                  // rows cannot be dragged
		pParam->EnableMoveCols(TRUE);                   // columns can be dragged
		pParam->EnableTrackRowHeight(GX_TRACK_ALL);     // all rows have the same height.
		pParam->EnableThumbTrack(FALSE);                // thumb-tracking is disabled

		pParam->SetNumberedRowHeaders(FALSE);
		pParam->SetNumberedColHeaders(FALSE);

		// Do not allow selecting range of cells in the table
		// pParam->EnableSelection(GX_SELTABLE | GX_SELROW | GX_SELCOL);

		// set focus to control when moving current cell
		// pParam->SetActivateCellFlags(GX_CAFOCUS_SETCURRENT);

		// removing rows is not undoable for this kind of grid
		pParam->SetRemoveColsFlags(FALSE);
		pParam->SetRemoveRowsFlags(FALSE);

		pProp->SetMarkColHeader(FALSE);                 // Turn off pressed button effect for column headers
		pProp->SetPrintRowHeaders(FALSE);               // Don't print column headers

		pDBEParam->m_bIsBrowseInit = TRUE;
		Grid()->GetParam()->EnableUndo(bUndo);
	}
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::InitFromEngine()
{
	CGXDBEParam* pParam = Grid()->GetDBEParam();

	CGXDBEngine* pEngine = GetEngine();
	// CGXDBEngine must be allocated already
	if (pEngine == NULL)
	{
		TRACE0("Warning: InitFromEngine is called without a valid CGXDBEngine object.\n");
		TRACE0("No data will be displayed in the grid.\n");
	}

	if(pEngine && !pEngine->IsInit())
	{
		AfxMessageBox(_T("DBEngine not initialized properly...\nNo data will be displayed in the grid."));
		return;
	}
	// Reset the current cell
	Grid()->ResetCurrentCell();
	Grid()->SetCurrentCell(0,0);
	Grid()->StandardStyle().SetReadOnly(!(GetEngine() && Grid()->CanUpdate()));
	// but make sure titles and default values can be set
	// while initializing the grid

	BOOL bLock = pParam->IsLockReadOnly();
	pParam->SetLockReadOnly(FALSE);
	
	// Empty undo and redo list
	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	// Initialize cells
	BOOL bOldEnableUndo = pParam->IsEnableUndo();
	pParam->EnableUndo(FALSE);

	Grid()->OnTestGridDimension(1, 1);

	// Disable any drawing for the following operations
	BOOL bOldLockUpdate = Grid()->LockUpdate();

	// Determine field information:
	// a) determine field information: name, base style, length
	// b) store the field name with SetStyleRange()
	// c) store the column width with SetColWidth()

	(*m_pfInitFunction)(Grid(), GetEngine());

	// set row header width to 22 pixels
	Grid()->SetColWidth(0, 0, 22);

		// Reposition current cell
	Grid()->OnTestGridDimension(Grid()->GetFirstRow()+1, 0); // check at least
		// one additional row so that record status beam
		// "Next Record" buttons are not greyed
	if (Grid()->GetRowCount() >= Grid()->GetFirstRow() && Grid()->GetColCount() >= Grid()->GetFirstCol())
		Grid()->SetCurrentCell(Grid()->GetFirstRow(), Grid()->GetFirstCol());

	// reset LockUpdate state
	Grid()->LockUpdate(bOldLockUpdate);

	// reset EnableUndo state
	pParam->EnableUndo(bOldEnableUndo);

	// reset LockReadOnly state
	pParam->SetLockReadOnly(bLock);

	// readraw the grid (if LockUpdate != TRUE)
	Grid()->Redraw(GX_INVALIDATE);

//	SetColCount(GetEngine()->GetFieldCount());
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::IsOnFirstRecord()
{
	ROWCOL nRow, nCol;
	return Grid()->GetCurrentCell(nRow, nCol) && nRow <= Grid()->GetFirstRow();
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::IsOnLastRecord()
{
	ROWCOL nRow, nCol;
	if (!Grid()->GetCurrentCell(nRow, nCol))
		return FALSE;

	// Never TRUE as long as we have not seen the last record

	return nRow == Grid()->GetLastRow();
}

template<class GRID>
long CGXBrowserLayoutManager<GRID>::OnGetRecordCount()
{
	CGXDBEngine* pEngine = GetEngine();

	if (pEngine == NULL || !pEngine->IsInit())
		return 0;

	return GetEngine()->GetRecordCount();
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol)
{
	// Unused:
	nRow, nCol, nNewCol;

	if (Grid()->m_bUpdateDone && nNewRow != Grid()->GetDBEParam()->m_nCurrentRow)
	{
		Grid()->RedrawRowCol(CGXRange().SetRows(Grid()->GetDBEParam()->m_nCurrentRow));
			// no further redrawing of current cell necessary

		Grid()->m_bUpdateDone = FALSE;

		return FALSE;
	}

	return TRUE;    // SetCurrentCell will redraw current cell
}

// Check if the cell displays a DB value and not a row/col header, etc.
template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::IsDBValueCell(ROWCOL nRow, ROWCOL nCol)
{
	if(nRow < Grid()->GetFirstRow() || nCol < Grid()->GetFirstCol())
		return FALSE;
	else
		return TRUE;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	//CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ASSERT(nRow + Grid()->GetHeaderRows() <= LONG_MAX);

	// load style from the CGXData object, if something specific is stored there
	// (this call will normally only have effect for column headers and column styles).

	CGXData* pData = Grid()->GetParam()->GetData();

	BOOL bSuccess = nRow <= pData->GetRowCount()
			&& nCol <= pData->GetColCount()
			&& pData->GetStyleRowCol(nRow, nCol, style, mt, nType);

	// no further processing for the following conditions

	if (mt == gxRemove
		|| nType == -1)
		return bSuccess;

	if (nRow > Grid()->GetHeaderRows() && nCol > Grid()->GetHeaderCols())
	{
		// look in CGXData object
		pData->GetStyleRowCol(nRow, nCol, style, gxOverride, 0);

		// If you want to change the appearance of specific cells,
		// you have several options:
		// 1) You change the base style for the specific type of cell, e.g.
		//    use a spin edit control for dbByte values.
		// 2) You override GetStyleRowCol() and pass your specific cell attributes
		//    to the style object.
		// 3) You call SetStyleRange(CGXRange().SetCols(nCol), yourstyle) and change
		//    the column style settings for the specific column
		//
		// Note: You can determine the zero-based field index from a given
		// column by calling GetFieldFromCol(nCol) !
		//

		bSuccess = TRUE;
	}

	// give the programmer the chance to load value from data source
	// or apply additional formattings at runtime

	bSuccess |= Grid()->OnLoadCellStyle(nRow, nCol, style, NULL);

	return bSuccess;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue)
{
	// NOTE: if pszExistingValue is not NULL, it contains
	// the already existing value of the current buffer. You should
	// then only initialize specific formattings here, but
	// not change the cell value.
	//
	// if pszExistingValue is NULL, you should load the value
	// from your external data source.
	//
	// Currently, pszExistingValue is not NULL when the value has
	// been changed for the current record. In a future version
	// pszExistingValue may also be not NULL if the value is
	// cached somewhere else.

	// Unused:
	pszExistingValue;

	CString strValue;
	if(Grid()->IsDBValueCell(nRow, nCol))
	{
		TRY
		{
			if(GetEngine()->GetValue(Grid()->GetRecordFromRow(nRow), Grid()->GetFieldFromCol(nCol), strValue))
				style.SetValue(strValue);
			else if (GetEngine()->IsEOFSeen() && nRow > Grid()->GetLastRow())
				style.SetEnabled(FALSE);

			return TRUE;
		}
		CATCH(CUserException, e)
		{
			//Typically occrs when records have been deleted in the source by someother app 
			// Requery in a new message, otherwise ASSERT in LookupStyleRowCol
			// Also remove the exisiting WM_GX_REQUERY entries in the queue.
			MSG msg;
			while (PeekMessage(&msg, Grid()->GridWnd()->m_hWnd, WM_GX_REQUERY, WM_GX_REQUERY, PM_REMOVE));
			::PostMessage(Grid()->GridWnd()->m_hWnd, WM_GX_REQUERY, 0, 0);
			/*Requery();
			OpenRecordset();
			Redraw();*/
			// TRACE0("Posted WM_GX_REQUERY\n");
			return FALSE;	
		}
		END_CATCH
	}
	return FALSE;   // return TRUE if you have changed the style object!
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnCanceledEditing(ROWCOL /*nRow*/, ROWCOL /*nCol*/)
{
	// Can I reset the edit mode for the record?
	if(!GetEngine()->m_bDirty)
		Grid()->CancelRecord();

	//GX_UNUSED(nRow);
	//GX_UNUSED(nCol);
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnModifyCell(ROWCOL nRow, ROWCOL nCol)
{
	//CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ASSERT(GetEngine()->m_nEditMode == CGXDBEngine::noMode || (ROWCOL)GetEngine()->m_nEditRecord == (ROWCOL)Grid()->GetRecordFromRow(nRow));

	if (Grid()->m_bDropDownCell)
		return;

	if (GetEngine()->m_nEditMode == CGXDBEngine::noMode)
	{
		if (nRow == Grid()->GetAppendRow())
		{
			Grid()->AddNew();	//P use the returned value...?
		}
		else
			Grid()->Edit(nRow);
	}

	// if AddNew or Edit was succesfull
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
		Grid()->GRID::OnModifyCell(nRow, nCol);
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol)
{
	CGXDBEngine* pEngine = GetEngine();

	if (nRow != Grid()->GetDBEParam()->m_nCurrentRow)
	{
		// Redraw the header if MarkRowHeader is turned off, which would 
		// otherwise force a redraw on the row header
		if(!Grid()->GetDBEParam()->GetProperties()->GetMarkRowHeader())
			Grid()->RedrawRowCol( Grid()->GetDBEParam()->m_nCurrentRow, 0, GX_INVALIDATE);

		if (pEngine->m_nEditMode != CGXDBEngine::noMode)
			pEngine->Update();

		ASSERT(pEngine->m_nEditMode == CGXDBEngine::noMode);

		Grid()->GetDBEParam()->m_nCurrentRow = nRow;

		if(!Grid()->GetDBEParam()->GetProperties()->GetMarkRowHeader())
			Grid()->RedrawRowCol(nRow, 0, GX_INVALIDATE);
	}

	Grid()->GRID::OnMovedCurrentCell(nRow, nCol);
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	if (!Grid()->CanUpdate())
		return;

	if (Grid()->GetRowCount() == 0 || Grid()->GetColCount() == 0)
		return;

	// active cell coordinates
	ROWCOL nRow, nCol;
	if (!Grid()->GetCurrentCell(&nRow, &nCol))
		return;

	ROWCOL nEditRow = nRow, nEditCol = nCol;
	// Disable undo creation
	BOOL bEnableUndo = Grid()->GetParam()->IsEnableUndo();

	pDBEParam->m_bDoReplaceAll = TRUE;
		// StoreStyleRowCol checks GetEngine()->m_bDoReplaceAll
		// If it is TRUE, the row will immediately get updated

	// Save current cell's data
	Grid()->TransferCurrentCell();

	Grid()->BeginTrans(Grid()->m_pAppData->strmReplaceAll);

	BOOL bOldLock = Grid()->LockUpdate(TRUE);

	TRY
	{
		GX_FR_STATE* pState = GXGetLastFRState();

		pState->bTransaction = FALSE;

		// initialize searchparameter structure
		pState->strFind = lpszFind;
		pState->strReplace = lpszReplace;
		pState->bCase = bCase;
		pState->bNext = TRUE;
		pState->PrepareFindReplace();

		CGXLongOperation theOp;
//		theOp.SetStatusText(m_pAppData->strmReplacingAll, FALSE);
		theOp.SetLockedState(TRUE);
		theOp.SetCanRollback(TRUE);

		Grid()->m_bCanceled = FALSE;

		// check active cell and replace

		Grid()->m_nFirstRow = nRow;

		ROWCOL dwStartRow = nRow;
		ROWCOL dwRowCount = nRow;
		ROWCOL dwRows = 0;

		BOOL bFound = FALSE;

		ROWCOL nRowCount = (ROWCOL) Grid()->OnGetRecordCount() + Grid()->GetFirstRow() - 1;

		while (nRow <= nRowCount && nRow > 0)
		{
			dwRows++;
			if (theOp.NeedMessages())
			{
				if (pState->bNext)
					dwRowCount = Grid()->GetRowCount()-dwStartRow;
				theOp.SetPercentDone((int) (dwRows*100 / dwRowCount));
				theOp.DoMessages(Grid()->m_bCanceled);
				if (Grid()->m_bCanceled)
					break;
			}

			CGXStyle* pStyle = Grid()->CreateStyle();
			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
			CGXControl* pControl = Grid()->GetRegisteredControl(pStyle->GetControl());
			ASSERT(pControl != 0);

			pState->m_pStyle = pStyle; // cache style object so that ReplaceAll can resuse it

			if (pControl->ReplaceAll(*pState, nRow, nCol))
				bFound = TRUE;

			pState->m_pStyle = NULL;

			// free style object
			Grid()->RecycleStyle(pStyle);

			if (pState->bNext)
			{
				Grid()->OnTestGridDimension(++nRow, 0);
				nRowCount = (ROWCOL) Grid()->OnGetRecordCount() + Grid()->GetFirstRow() - 1;
			}
			else
				nRow--;
		}

		theOp.SetPercentDone(-1);
		theOp.SetLockedState(FALSE);

		if (Grid()->m_bCanceled && !pState->bTransaction)
		{
			AfxThrowUserException();
		}
		else if (Grid()->m_bCanceled && theOp.GetRollbackConfirmedState())
		{
			if (pState->bTransaction)
				Grid()->Rollback();
		}
		else
		{
			if (!bFound)
				Grid()->OnTextNotFound(GXGetLastFRState()->strFind);
		}

#ifdef _UNICODE
		// Clean up non UNICODE text buffer
		delete[] pState->lpszMultiByteFindString;
		pState->lpszMultiByteFindString = NULL;
#endif

		// update last row
		if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
			Grid()->Update();

		Grid()->CommitTrans();

		// Requery
		Grid()->Requery();
	}
	CATCH(CException, e)
	{
		pDBEParam->m_bDoReplaceAll = FALSE;
		Grid()->Rollback();
		Grid()->Requery();
		GX_THROW_LAST
	}
	END_CATCH

	pDBEParam->m_bDoReplaceAll = FALSE;

	Grid()->LockUpdate(bOldLock);

	Grid()->Redraw();

	// Reenable undo mechanism
	Grid()->GetParam()->EnableUndo(bEnableUndo);

	Grid()->SetCurrentCell(nEditRow, nEditCol, GX_SMART | GX_NOSETFOCUS);
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnTestGridDimension(ROWCOL nLastRow, ROWCOL /*nLastCol*/)
{
	if(!GetEngine() || !GetEngine()->IsInit())
		return;
	if(!GetEngine()->IsEOFSeen())
		GetEngine()->FetchRecords(nLastRow);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::CanRecordDelete()
{
	CGXRangeList* pSelList = Grid()->GetParam()->GetRangeList();

	// check that whole rows are selected and that "new row" is not selected
	return Grid()->CanUpdate()
		// and not already on last record
		&& pSelList->IsAnyCellFromCol(0)
		&& !pSelList->IsAnyCellFromRow( Grid()->GetAppendRow());
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	// RemoveCols does not support undo!

	// Turn off undo creation
	BOOL bEnableUndo = Grid()->GetParam()->IsEnableUndo();
	Grid()->GetParam()->EnableUndo(FALSE);

	// Execute the command
	BOOL bSuccess =
		Grid()->GRID::RemoveCols(nFromCol, nToCol, flags, ctCmd);

	// If command was succesfull, empty undo/redo list
	// so that nothing gets messed up
	if (bSuccess)
	{
		Grid()->GetParam()->EmptyUndoList();
		Grid()->GetParam()->EmptyRedoList();
	}

	// reenable undo support
	Grid()->GetParam()->EnableUndo(bEnableUndo);

	return bSuccess;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	// RemoveRows does not support undo!

	// Turn off undo creation
	BOOL bEnableUndo = Grid()->GetParam()->IsEnableUndo();
	Grid()->GetParam()->EnableUndo(FALSE);

	// Execute the command
	BOOL bSuccess =
		Grid()->GRID::RemoveRows(nFromRow, nToRow, flags, ctCmd);

	bSuccess = Grid()->GetEngine()->DeleteRows(nFromRow-1, nToRow-1);
	// If command was succesfull, empty undo/redo list
	// so that nothing gets messed up
	if (bSuccess)
	{
		Grid()->GetParam()->EmptyUndoList();
		Grid()->GetParam()->EmptyRedoList();
	}

	// reenable undo support
	Grid()->GetParam()->EnableUndo(bEnableUndo);

	return bSuccess;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range)
{
	ROWCOL nRow1, nRow2, nCol;
	Grid()->GetCurrentCell(nRow1, nCol);

	// CGXGridCore::PasteTextFromBuffer screen update is too optimized - with
	// CGXDBEGrid we always have to redraw complete rows
	// and not individual cells

	BOOL bLock = Grid()->LockUpdate(TRUE);

	// make sure CGXGridCore::PasteTextFromBuffer does not try to append
	// rows when CanAppend() returns FALSE
	DWORD nClipboardFlags = Grid()->m_nClipboardFlags;
	if (!Grid()->CanAppend())
		Grid()->m_nClipboardFlags |= GX_DNDNOAPPENDROWS;

	BOOL bRet = Grid()->GRID::PasteTextFromBuffer(psz, size, range);

	// restore original setting 
	Grid()->m_nClipboardFlags = nClipboardFlags;

	Grid()->LockUpdate(bLock);
	
	Grid()->GetCurrentCell(nRow2, nCol);

	// Redraw all rows between old and new current row
	Grid()->RedrawRowCol(CGXRange().SetRows(nRow1, nRow2), GX_INVALIDATE);

	// refresh formula cells 
	Grid()->RefreshViews();

	return bRet;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	//CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	BOOL	bSuccess = FALSE;

	// check if there are pending changes in another record
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && nRow !=  Grid()->GetDBEParam()->m_nCurrentRow)
	{
		CString sErrorDesc;

		// flush them to the data source
		if (!Grid()->Update(&sErrorDesc))
			return FALSE;   // could not update previous record
	}

	// check if cell isn't readonly
	CGXStyle* pStyle = NULL;
	
	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// will cancel ops
	if (pOldStyle->GetIncludeReadOnly() && pOldStyle->GetReadOnly())
		// TODO: set or display a notification that operation could not be performed
		// ano not only return silently
 		return FALSE;   

	// ensure that the current row is in edit mode
	if (GetEngine()->m_nEditMode == CGXDBEngine::noMode)
	{
		if (nRow != GetAppendRow())
			Grid()->Edit(nRow);
		else
			Grid()->AddNew();
	}

	// if AddNew or Edit was succesfull
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
		bSuccess = Grid()->GRID::SetControlTextRowCol(nRow, nCol, str, nFlags, pOldStyle);

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::SetMaxColWidth(int nChar)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ASSERT(pDBEParam);
	// ASSERTION-> You should first initalize the grid
	// before you call this method. Please make sure
	// that OnInitialUpdate has been called or at that
	// you did at least attach the parameter object! ->END

	// save setting
	pDBEParam->m_nMaxColWidth = nChar;

	// loop through columns
	ROWCOL nCount = Grid()->GetColCount();
	int nWidth = Grid()->Width_LPtoDP( nChar * GX_NXAVGWIDTH );

	BOOL bLock = Grid()->LockUpdate(TRUE);

	for (ROWCOL nCol = Grid()->GetFirstCol(); nCol <= nCount; nCol++)
	{
		if (Grid()->GetColWidth(nCol) > nWidth)
			Grid()->SetColWidth(nCol, nCol, nWidth);
	}

	Grid()->LockUpdate(bLock);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType, const CObArray* pCellsArray, UINT flags, GXCmdType ctCmd)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	// determine if a cell in the grid shall be changed
	// assign FALSE if it is a row/column style, a header or several rows
	BOOL bIsGridCell =
		range.IsCells()
		&& range.GetHeight() == 1
		&& Grid()->IsDBValueCell(range.top, range.left);

	// let the base class version do the work if not a cell in the grid
	if (!bIsGridCell)
		return Grid()->GRID::SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);

	// make sure current row is in edit mode

	ROWCOL nRow = range.top;

	CString sErrorDesc; 

	// check if there are pending changes in another record
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && ((ROWCOL)Grid()->GetRecordFromRow(nRow) != (ROWCOL)GetEngine()->m_nEditRecord))
	{
		// flush them to the data source
		if (!Grid()->Update(&sErrorDesc))
			return FALSE;   // could not update previous record
	}

	BOOL bAddNew = FALSE;
	// ensure that the current row is in edit mode
	if (GetEngine()->m_nEditMode == CGXDBEngine::noMode)
	{
		if (bAddNew = (nRow == Grid()->GetAppendRow())) // Intentional Assignment???
			Grid()->AddNew();
		else
			Grid()->Edit(nRow);
	}

	BOOL bSuccess = FALSE;

	// if AddNew or Edit was succesfull
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
		bSuccess = Grid()->GRID::SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);

	// Shall I check for dirty fields?
	BOOL bCheckDirtyBits = (ctCmd == gxUndo) || !bSuccess && GetEngine()->m_nEditMode != CGXDBEngine::noMode;

	if (bCheckDirtyBits)
	{
		// remove unnecceary dirty bits from current record
/*
		CGXStyle* pStyle = CreateStyle();
		ROWCOL nRow = range.top;
		for (ROWCOL nCol = range.left; nCol <= range.right; nCol++)
		{
			short nField = GetFieldFromCol(nCol);

			// compare value
				// force GetStyleRowCol to look in data source (e.g. CDaoRecordset)
				// for the value
			GetEngine()->m_paDirtyFieldStruct[nField].bDirty = FALSE;

			pStyle->SetIncludeValue(FALSE);
			GetStyleRowCol(nRow, nCol, *pStyle);

				// set or reset dirty bit
			GetEngine()->m_paDirtyFieldStruct[nField].bDirty = pStyle->GetIncludeValue()
				&& _tcscmp(pStyle->GetValueRef(), GetEngine()->m_paDirtyFieldStruct[nField].sValue) != 0;
		}
		RecycleStyle(pStyle);
*/
		// Can I reset the edit mode for the record?
		if (!GetEngine()->m_bDirty)
			Grid()->CancelRecord();
	}

	if (bSuccess && bAddNew)
	{
		// ensure that current cell displays correct value
		// when redoing a previously abondened record
		ROWCOL nRow, nCol;
		CGXControl* pControl;
		if (Grid()->GetCurrentCell(nRow, nCol))
		{
			CString s;
			pControl = Grid()->GetControl(nRow, nCol);
			pControl->GetCurrentText(s);
			if (s.IsEmpty())
				Grid()->TransferCurrentCell(FALSE, FALSE);
		}
	}

	// Was SetStyleRange called from OnReplaceAll and therefore
	// I have to update the current record immediately?

	if (bSuccess && pDBEParam->m_bDoReplaceAll)
	{
		ASSERT(ctCmd == gxDo);

		// try to write the current row back to data source
		Grid()->Update(NULL);
			// Update possible throws an exception
			// which will be catched in OnReplaceAll()
	}

	// Was SetStyleRange called because user wants to move current cell
	// to a new record and therefore I have to update the current record?

	else if (bSuccess && pDBEParam->m_bUpdateOnStore)
	{
		ASSERT(ctCmd == gxDo);
		ASSERT(range.IsCells() && range.GetHeight() == 1 && range.GetWidth() == 1);

		//ROWCOL nRow = range.top;
		//ROWCOL nCol = range.left;
		//short nField = Grid()->GetFieldFromCol(nCol);

		pDBEParam->m_bUpdateOnStore = FALSE;

		// try to write the current row back to data source
		CString s;

		if (!Grid()->Update(&s))  // Update() will catch possible exceptions and
						 // store the description info in s. If an
						 // exception occurs Update() returns FALSE.
		{
			Grid()->GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);

			//CGXControl* pControl = Grid()->GetControl(nRow, nCol);
//			pControl->SetCurrentText(GetEngine()->m_paDirtyFieldStruct[nField].sValue);

			// Reset dirty flag for current column
//			GetEngine()->m_paDirtyFieldStruct[nField].sValue.Empty();
//			GetEngine()->m_paDirtyFieldStruct[nField].bDirty = FALSE;

			// Remove the command from undo list
			CObList& undoList = Grid()->GetParam()->GetUndoList();
			if (Grid()->GetParam()->IsEnableUndo() && undoList.GetCount() > 0)
			{
//				Grid()->RemoveCommand(ctCmd);
				Grid()->Undo();
			}

			// Message box text (will be displayed later)
			if (!s.IsEmpty())
				Grid()->SetWarningText(s);

			// failed, ...
			return FALSE;
		}
	}

	return bSuccess;
}
/*
template<class GRID>
void CGXBrowserLayoutManager<GRID>::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd)
{
#ifdef _DEBGUG
	for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		ASSERT(awRowEnd[index] >= awRowStart[index]);
		// ASSERTION -> DeleteRows assumes that awRowEnd[index] is
		// always greater or equal to awRowStart[index]. Make sure
		// you specify this arrays correctly. ->END
	}
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();
	ROWCOL nEditRow, nEditCol;
	BOOL bCCell = Grid()->GetCurrentCell(nEditRow, nEditCol);

	// Save current cell's data
	Grid()->TransferCurrentCell();

	// check if row to be deleted is in edit mode
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
	{
		// Compute the current row... default 
		ROWCOL nCurRow = pDBEParam->m_nCurrentRow;
		for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if (nCurRow >= awRowStart[index] &&
				nCurRow <= awRowEnd[index])
			{
				Grid()->CancelRecord();
				break;
			}
		}
	}

	// check if row (not to be deleted) is in edit mode
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
	{
		CString s;

		// cannot proceed if row cannot be saved
		if (!Grid()->Update(&s))
			return;
	}

	// Now, it is sure that m_nEditMode is reset.
	ASSERT(GetEngine()->m_nEditMode == CGXDBEngine::noMode);
	BOOL bLockUpdate = Grid()->LockUpdate(TRUE);

	// Empty undo/redo list
	BOOL bOldUndo = pDBEParam->IsEnableUndo();
	pDBEParam->EmptyUndoList();
	pDBEParam->EmptyRedoList();
	pDBEParam->EnableUndo(FALSE);

	// First, sort the array of records
	ROWCOL nCount = 0;
	for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
		nCount += awRowEnd[index]-awRowStart[index]+1;

	int nIndex = 0;
	long* alRecords = new long[nCount];

	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		ROWCOL nRecords = awRowEnd[index]-awRowStart[index]+1;
		for (ROWCOL n = 0; n < nRecords; n++)
			alRecords[nIndex++] = Grid()->GetRecordFromRow(awRowStart[index]+n);
	}

	qsort(alRecords, (size_t) nCount, sizeof(long), __gxcomparelong);

	for (index = (int) nCount-1; index >= 0; index--)
	{
		GetEngine()->DeleteRows(alRecords[index],alRecords[index]);
		int n = 0;

		// First, make sure all rows have an index
		for (n = 0; n <= pDBEParam->m_awRowIndex.GetUpperBound(); n++)
		{
			if (pDBEParam->m_awRowIndex[n] == 0)
				pDBEParam->m_awRowIndex[n] = (ROWCOL) n;
		}

		for (n = 0; n <= pDBEParam->m_awRowIndex.GetUpperBound(); n++)
		{
			if (pDBEParam->m_awRowIndex[n] > alRecords[index]+Grid()->GetFirstRow())
				pDBEParam->m_awRowIndex[n]--;
		}
	}
	
	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		if ((int) awRowStart[index] < pDBEParam->m_awRowIndex.GetSize())
			pDBEParam->m_awRowIndex.RemoveAt((int) awRowStart[index],
				min((int) awRowEnd[index], pDBEParam->m_awRowIndex.GetUpperBound())
				-(int) awRowStart[index]+1);
	}

	// Remove selection
	Grid()->SetSelection(0);

	if (bCCell && nEditRow >= awRowStart[0])
	{
		// Sync current cell
			// First, mark as invalid
		Grid()->StoreCurrentCell(FALSE);

		// Next, position again
		nEditRow = max(1, min(awRowStart[0], Grid()->GetRowCount()));
	}

//	for (int nIndex = awRowStart.GetUpperBound(); nIndex >= 0; nIndex--)
//		RemoveRows(awRowStart[nIndex], awRowEnd[nIndex]);

	for (int i = awRowEnd.GetUpperBound(); i >= 0; i--)
		Grid()->GRID::StoreRemoveRows(awRowStart[i],awRowEnd[i]);

	delete[] alRecords;

	pDBEParam->EnableUndo(bOldUndo);

	Grid()->LockUpdate(bLockUpdate);
//	CommitTrans();
	Grid()->Redraw();

	// User can undo this action, but as soon as he starts editing a
	// row, undo information will be lost again!
}
*/

template<class GRID>
void CGXBrowserLayoutManager<GRID>::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd)
{
#ifdef _DEBGUG
	for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		ASSERT(awRowEnd[index] >= awRowStart[index]);
		// ASSERTION -> DeleteRows assumes that awRowEnd[index] is
		// always greater or equal to awRowStart[index]. Make sure
		// you specify this arrays correctly. ->END

		ASSERT(((awRowStart[index] - 1) % m_nRecordSpan) == 0 && (awRowEnd[index] % m_nRecordSpan) == 0)
		// ASSERTION -> Make sure that the rows to be deleted are in multiples of m_nRecordSpan with appropriate boundaries.
	}
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();
	ROWCOL nEditRow, nEditCol;
	BOOL bCCell = Grid()->GetCurrentCell(nEditRow, nEditCol);

	// Save current cell's data
	Grid()->TransferCurrentCell();

	// check if row to be deleted is in edit mode
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
	{
		// Compute the current row... default 
		ROWCOL nCurRow = pDBEParam->m_nCurrentRow;
		for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if (nCurRow >= awRowStart[index] &&
				nCurRow <= awRowEnd[index])
			{
				Grid()->CancelRecord();
				break;
			}
		}
	}

	// check if row (not to be deleted) is in edit mode
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode)
	{
		CString s;

		// cannot proceed if row cannot be saved
		if (!Grid()->Update(&s))
			return;
	}

	// Now, it is sure that m_nEditMode is reset.
	ASSERT(GetEngine()->m_nEditMode == CGXDBEngine::noMode);
	BOOL bLockUpdate = Grid()->LockUpdate(TRUE);

	// Empty undo/redo list
	BOOL bOldUndo = pDBEParam->IsEnableUndo();
	pDBEParam->EmptyUndoList();
	pDBEParam->EmptyRedoList();
	pDBEParam->EnableUndo(FALSE);

	GetEngine()->BeginTrans(_T("Deleting Rows"));

	// First, sort the array of records
	ROWCOL nRowCount = 0, nRecCount = 0;
	int index = 0;
	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
		nRowCount += awRowEnd[index]-awRowStart[index]+1;

	nRecCount = nRowCount / m_nRecordSpan;

	int nIndex = 0;
	long* alRecords = new long[nRecCount];

	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		ROWCOL nRows = awRowEnd[index]-awRowStart[index]+1;
		for (ROWCOL n = 0; n < nRows; n += m_nRecordSpan)
			alRecords[nIndex++] = Grid()->GetRecordFromRow(awRowStart[index]+n);
	}

	qsort(alRecords, (size_t) nRecCount, sizeof(long), __gxcomparelong);

	BOOL bDeleted = TRUE/*, bDone = TRUE*/;

	for (index = (int) nRecCount-1; index >= 0; index--)
	{
		bDeleted &= GetEngine()->DeleteRows(alRecords[index],alRecords[index]);
		if(!bDeleted)
			goto ErrorExit;

		int n = 0;

		// First, make sure all rows have an index
		for (n = 0; n <= pDBEParam->m_awRowIndex.GetUpperBound(); n++)
		{
			if (pDBEParam->m_awRowIndex[n] == 0)
				pDBEParam->m_awRowIndex[n] = (ROWCOL) n;
		}

		for (n = 0; n <= pDBEParam->m_awRowIndex.GetUpperBound(); n++)
		{
			if ((pDBEParam->m_awRowIndex[n] - Grid()->GetFirstRow()) / m_nRecordSpan > (ROWCOL)alRecords[index])
				pDBEParam->m_awRowIndex[n] -= m_nRecordSpan;
		}
	}

	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		if ((int) awRowStart[index] < pDBEParam->m_awRowIndex.GetSize())
			pDBEParam->m_awRowIndex.RemoveAt((int) awRowStart[index],
				min((int) awRowEnd[index], pDBEParam->m_awRowIndex.GetUpperBound())
				-(int) awRowStart[index]+1);
	}

	GetEngine()->CommitTrans();

	GetEngine()->OnDeletedRecords();

	// Remove selection
	Grid()->SetSelection(0);

	if (bCCell && nEditRow >= awRowStart[0])
	{
		// Sync current cell
			// First, mark as invalid
		Grid()->StoreCurrentCell(FALSE);

		// Next, position again
		nEditRow = max(1, min(awRowStart[0], Grid()->GetRowCount()));
	}

//	for (int nIndex = awRowStart.GetUpperBound(); nIndex >= 0; nIndex--)
//		RemoveRows(awRowStart[nIndex], awRowEnd[nIndex]);

	for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
		Grid()->GRID::StoreRemoveRows(awRowStart[index],awRowEnd[index]);

ErrorExit:
	if(!bDeleted)
		GetEngine()->Rollback();

	delete[] alRecords;

	pDBEParam->EnableUndo(bOldUndo);

	Grid()->LockUpdate(bLockUpdate);
//	CommitTrans();
	Grid()->Redraw();

	// User can undo this action, but as soon as he starts editing a
	// row, undo information will be lost again!
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed)
{
#ifdef _DEBUG
	ASSERT(nCol >= Grid()->GetFirstCol());
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && GetEngine()->m_bDirty)
	{
		CString s;
		if(!Grid()->Update(&s))
			return FALSE;
	}

	int nIndex = (int) nCol;
	int nInsert = (int) nCount;
	int nColCount = (int) Grid()->GetColCount();

	if (pDBEParam->m_awColIndex.GetUpperBound() < nColCount)
		pDBEParam->m_awColIndex.SetSize(nColCount+1);

	// initialize columns after the insertion point
	int n;
	for (n = nIndex; n <= nColCount; n++)
	{
		if (pDBEParam->m_awColIndex[n] == 0)
			pDBEParam->m_awColIndex[n] = (ROWCOL) n;
	}

	pDBEParam->m_awColIndex.InsertAt(nIndex, 0, nInsert);

	// Note:
	// This method makes the assumption that if you insert
	// columns, the real columns will be appended in
	// your data structure you are broswing with this grid.
	//
	// Example:
	// You have 5 columns. GetColIndex(n) returns 1 2 3 4 5 for n = 1..5
	// Now, you insert two column at column 2:
	// Then GetColIndex returns 1 6 7 3 4 5 for n = 1..7
	// If you need a different behavior, you have to override this
	// method.

	// initialize the new columns
	for (n = 0; n < nInsert; n++)
		pDBEParam->m_awColIndex[nIndex+n] = ++nColCount;

	BOOL b = Grid()->GRID::StoreInsertCols(nCol, nCount, bProcessed);

	// reinitialize current record buffer with the new column count
//P	EmptyEditBuffer();

	return b;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed)
{
#ifdef _DEBUG
	ASSERT(((nRow - 1) % m_nRecordSpan) == 0 && (nCount % m_nRecordSpan) == 0);
	// ASSERTION -> Make sure that the rows to be inserted are in multiples of m_nRecordSpan with appropriate boundaries.
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && GetEngine()->m_bDirty)
	{
		CString s;
		if (!Grid()->Update(&s))
			return FALSE;
	}

	int nIndex = (int) nRow;
	int nInsert = (int) nCount;
	int nRowCount = (int) Grid()->GetRowCount();

	if (pDBEParam->m_awRowIndex.GetUpperBound() < nRowCount)
		pDBEParam->m_awRowIndex.SetSize(nRowCount+1);

	// initialize the rows after the insertion point
        int n;
	for (n = nIndex; n <= nRowCount; n++)
	{
		if (pDBEParam->m_awRowIndex[n] == 0)
			pDBEParam->m_awRowIndex[n] = (ROWCOL) n;
	}

	pDBEParam->m_awRowIndex.InsertAt(nIndex, 0, nInsert);

	// Note:
	// This method makes the assumption that if you insert
	// rows, the real rows will be appended in
	// your data structure that you are broswing with this grid.

	// initialize the new columns
	for (n = 0; n < nInsert; n++)
		pDBEParam->m_awRowIndex[nIndex+n] = ++nRowCount;

	BOOL b = Grid()->GRID::StoreInsertRows(nRow, nCount, bProcessed);

	return b;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed)
{
#ifdef _DEBUG
	ASSERT(nFromCol >= Grid()->GetFirstCol() && nDestCol >= Grid()->GetFirstCol());
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	// rearrange the array with column indexes

	int nIndex = (int) nFromCol;
	int nCount = (int) nToCol - (int) nFromCol + 1;
	int nDest = (int) nDestCol;

	int nFirst = (nIndex < nDest) ? nIndex : nDest;
	int nLast = (nIndex+nCount > nDest+nCount) ? nIndex+nCount : nDest+nCount;

	bProcessed = FALSE;

	// easiest case: nothing to do
	if (nDest == nIndex || nCount == 0)
		NULL;

	// move columns to the left
	else if (nDest < nIndex)
	{
		nIndex += nCount;
		bProcessed = TRUE;
	}

	// move columns to the right
	else if (nDest > nIndex)
	{
		nDest += nCount;
		bProcessed = TRUE;
	}

	// do the job
	if (bProcessed)
	{
		// First, assign column ids to the entries in the range
		// which not yet have a valid column id.

		int n;

		if (pDBEParam->m_awColIndex.GetUpperBound() < nLast)
			pDBEParam->m_awColIndex.SetSize(nLast+1);

		for (n = nFirst; n < nLast; n++)
		{
			if (pDBEParam->m_awColIndex[n] == 0)
				pDBEParam->m_awColIndex[n] = (ROWCOL) n;
		}

		pDBEParam->m_awColIndex.InsertAt(nDest, 0, nCount);

		// initialize the new columns
		for (n = 0; n < nCount; n++)
			pDBEParam->m_awColIndex[nDest+n] = pDBEParam->m_awColIndex[nIndex+n];

		pDBEParam->m_awColIndex.RemoveAt(nIndex, nCount);
	}

	return Grid()->GRID::StoreMoveCols(nFromCol, nToCol, nDestCol, bProcessed);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex)
{
	ASSERT(sortRange.IsCols());
	// ASSERTION-> Only full cols supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	CRowColArray newColIndex;

	newColIndex.SetSize(awColIndex.GetSize());

	// First, replace col ids with existing GetColIndex ids
        int nIndex;
	for (nIndex = 0; nIndex < awColIndex.GetSize(); nIndex++)
		newColIndex[nIndex] = Grid()->GetColIndex(awColIndex[nIndex]+sortRange.left);

	// Now, copy row ids to m_awColIndex
	if ((ROWCOL) Grid()->GetDBEParam()->m_awColIndex.GetSize() <= sortRange.right)
		Grid()->GetDBEParam()->m_awColIndex.SetSize((int) sortRange.right+1);

	// fill first ids
	for (nIndex = 0; (ROWCOL) nIndex < sortRange.left; nIndex++)
		Grid()->GetDBEParam()->m_awColIndex[nIndex] = (ROWCOL) nIndex;

	for (nIndex = 0; nIndex < awColIndex.GetSize(); nIndex++)
		Grid()->GetDBEParam()->m_awColIndex[nIndex+(int) sortRange.left] = newColIndex[nIndex];

	// also give CGXData a chance
	Grid()->GetParam()->GetData()->StoreMoveDataCols(sortRange, awColIndex);

	return TRUE;
}

// Sorting

template<class GRID>
void CGXBrowserLayoutManager<GRID>::SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Sort the grid with the columns specified in awCols.

	Grid()->OnTestGridDimension(GX_MAXROWCOL, 0);

	if (sortRange.IsTable())
		sortRange.SetRows(Grid()->GetFirstRow(), (ROWCOL) Grid()->GetRowCount() - m_nRecordSpan);	// The last row(s) is always for the append row.

	Grid()->GRID::SortRows(sortRange, sortInfo, flags);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	ASSERT(sortRange.IsRows());
	// ASSERTION-> Only full rows supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

#ifdef _DEBUG
	ASSERT(((sortRange.top - 1) % m_nRecordSpan) == 0 && (sortRange.bottom % m_nRecordSpan) == 0);
	// ASSERTION -> Make sure that the rows to be moved are in multiples of m_nRecordSpan with appropriate boundaries.
#endif

	CRowColArray newRowIndex;

	newRowIndex.SetSize(awRowIndex.GetSize());

	// First, replace row ids with existing GetRowIndex ids
        int nIndex = 0;
	for (nIndex = 0; nIndex < awRowIndex.GetSize(); nIndex++)
		newRowIndex[nIndex] = Grid()->GetRowIndex(awRowIndex[nIndex]+sortRange.top);

	// Now, copy row ids to m_awRowIndex
	if ((ROWCOL) Grid()->GetDBEParam()->m_awRowIndex.GetSize() <= sortRange.bottom)
		Grid()->GetDBEParam()->m_awRowIndex.SetSize((int) sortRange.bottom+1);

	// fill first ids
	for (nIndex = Grid()->GetDBEParam()->m_awRowIndex.GetSize(); (ROWCOL) nIndex < sortRange.top; nIndex++)
		Grid()->GetDBEParam()->m_awRowIndex[nIndex] = (ROWCOL) nIndex;

	for (nIndex = 0; nIndex < awRowIndex.GetSize(); nIndex++)
		Grid()->GetDBEParam()->m_awRowIndex[nIndex+(int) sortRange.top] = newRowIndex[nIndex];

	return Grid()->GRID::StoreMoveDataRows(sortRange, awRowIndex);
	// also give CGXData a chance
//	Grid()->GetParam()->GetData()->StoreMoveDataRows(sortRange, awRowIndex);

//	return TRUE;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed)
{
	ASSERT(nFromCol >= Grid()->GetFirstCol());

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ROWCOL nColCount = Grid()->GetColCount();
	if (nFromCol > nColCount)
		return FALSE;

	nToCol = (nToCol < nColCount) ? nToCol : nColCount;

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && GetEngine()->m_bDirty)
	{
		CString s;
		if (!Grid()->Update(&s))
			return FALSE;
	}

	int nIndex = (int) nFromCol;
	int nCount = (int) nToCol - (int) nFromCol + 1;

	// First, make sure all columns have an index
	pDBEParam->m_awColIndex.SetSize((int) nColCount+1);
	for (ROWCOL nCol = nFromCol; nCol <= nColCount; nCol++)
	{
		if (pDBEParam->m_awColIndex[(int) nCol] == 0)
			pDBEParam->m_awColIndex[(int) nCol] = nCol;
	}

	// Now, we can remove columns
	if (nIndex <= pDBEParam->m_awColIndex.GetUpperBound())
		pDBEParam->m_awColIndex.RemoveAt(nIndex,
		(nCount < pDBEParam->m_awColIndex.GetUpperBound()-nIndex+1) ? nCount : pDBEParam->m_awColIndex.GetUpperBound()-nIndex+1);

	// Note:
	// This method makes the assumption that if you delete
	// columns, the real columns will not be deleted in
	// the data structure that you are broswing with this grid.
	// They only will not be visible any more in the grid.
	//
	// Example:
	// You have 5 columns. GetColIndex(n) returns 1 2 3 4 5 for n = 1..5
	// Now, you remove column 2:
	// Then GetColIndex returns 1 3 4 5 for n = 1..4
	// If you need a different behavior, you have to override this
	// method.

	BOOL b = Grid()->GRID::StoreRemoveCols(nFromCol, nToCol, bProcessed);

	// reinitialize current record buffer with the new column count
//P	EmptyEditBuffer();

	return b;
}

// StoreMoveRows rearranges the internal m_awRowIndex
// array, when rows have been moved. If you always
// take care to call GetRowIndex or GetRecordFromRow
// before acessing values, you will easily have
// support for moving Rows in your browser.

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	// rearrange the array with row indices

	int nIndex = (int) nFromRow;
	int nCount = (int) nToRow - (int) nFromRow + 1;
	int nDest = (int) nDestRow;

	int nFirst = (nIndex < nDest) ? nIndex : nDest;
	int nLast = (nIndex+nCount > nDest+nCount) ? nIndex+nCount : nDest+nCount;

	bProcessed = FALSE;

	// easiest case: nothing to do
	if (nDest == nIndex || nCount == 0)
		NULL;

	// move rows to the top
	else if (nDest < nIndex)
	{
		nIndex += nCount;
		bProcessed = TRUE;
	}

	// move rows to the bottom
	else if (nDest > nIndex)
	{
		nDest += nCount;
		bProcessed = TRUE;
	}

	// do the job
	if (bProcessed)
	{
		// First, assign row ids to the entries in the range
		// which not yet have a valid row id.

		int n;

		if (pDBEParam->m_awRowIndex.GetUpperBound() < nLast)
			pDBEParam->m_awRowIndex.SetSize(nLast+1);

		for (n = nFirst; n < nLast; n++)
		{
			if (pDBEParam->m_awRowIndex[n] == 0)
				pDBEParam->m_awRowIndex[n] = (ROWCOL) n;
		}

		pDBEParam->m_awRowIndex.InsertAt(nDest, 0, nCount);

		// initialize the new columns
		for (n = 0; n < nCount; n++)
			pDBEParam->m_awRowIndex[nDest+n] = pDBEParam->m_awRowIndex[nIndex+n];

		pDBEParam->m_awRowIndex.RemoveAt(nIndex, nCount);
	}

	return Grid()->GRID::StoreMoveRows(nFromRow, nToRow, nDestRow, bProcessed);
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed)
{
#ifdef _DEBUG
	ASSERT((nFromRow-1 % m_nRecordSpan) == 0 && (nToRow % m_nRecordSpan) == 0);
	// ASSERTION -> Make sure that the rows to be moved are in multiples of m_nRecordSpan with appropriate boundaries.
#endif

	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ROWCOL nRowCount = Grid()->GetRowCount();
	if (nFromRow > nRowCount)
		return FALSE;

	nToRow = (nToRow < nRowCount) ? nToRow : nRowCount;

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	if (GetEngine()->m_nEditMode != CGXDBEngine::noMode && GetEngine()->m_bDirty)
	{
		CString s;
		if (!Grid()->Update(&s))
			return FALSE;
	}

	int nIndex = (int) nFromRow;
	int nCount = (int) nToRow - (int) nFromRow + 1;

	// First, make sure all rows have an index
	pDBEParam->m_awRowIndex.SetSize((int) nRowCount+1);
	for (ROWCOL nRow = nFromRow; nRow <= nRowCount; nRow++)
	{
		if (pDBEParam->m_awRowIndex[(int) nRow] == 0)
			pDBEParam->m_awRowIndex[(int) nRow] = nRow;
	}

	// Now, we can remove rows
	if (nIndex <= pDBEParam->m_awRowIndex.GetUpperBound())
		pDBEParam->m_awRowIndex.RemoveAt(nIndex,
		(nCount < pDBEParam->m_awRowIndex.GetUpperBound()-nIndex+1) ? nCount :pDBEParam->m_awRowIndex.GetUpperBound()-nIndex+1);

	// Note:
	// This method makes the assumption that if you delete
	// rows, the real rows will not be deleted in
	// the data structure that you are broswing with this grid.
	// They only will not be visible any more in the grid.

	BOOL b = Grid()->GRID::StoreRemoveRows(nFromRow, nToRow, bProcessed);

	return b;
}

template<class GRID>
BOOL CGXBrowserLayoutManager<GRID>::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
//	Store it in the engine...
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	BOOL bValue = pStyle && pStyle->GetIncludeValue()  // (change value)
		|| pStyle && pStyle->GetStyleBits() == 0 && mt == gxCopy; // (empty value)

	if (nType != -1         // no row/column base style
		&& mt != gxRemove   // no clear command
		&& bValue    // value must be included
		&& GetEngine()->m_nEditMode != CGXDBEngine::noMode   // grid is in edit mode
		&& (ROWCOL)GetEngine()->m_nEditRecord == (ROWCOL)Grid()->GetRecordFromRow(nRow)   // this row is in edit mode
		&& nCol >= Grid()->GetFirstCol()
		)
	{
		// If all the previous conditions are TRUE,
		// store the value into the current record buffer.

		int nField = Grid()->GetFieldFromCol(nCol);

		CString strValue = pStyle->GetValue();
		GetEngine()->SetValue(Grid()->GetRecordFromRow(nRow), nField, &strValue);

		return TRUE;
	}

	else // store it in CGXData
	{
		BOOL bIsGridCell =
			(nRow >= Grid()->GetFirstRow() && nCol >= Grid()->GetFirstCol());

		// Sometimes it makes no sense to store grid cells into
		// CGXData, for example CGXDaoGrid and CGXODBCGrid should
		// load cell data from or store them in the data source.

		if (!pDBEParam->m_bCanStoreGridCellInCGXData && bIsGridCell)
		{
			TRACE0("Warning: Trying to store a grid cell directly into CGXData\n");
			TRACE0("You should call Edit() / AddNew() before you try to change\n");
			TRACE0("data for a new row\n");

			TRACE0("Could it be that you have called SetStyleRange for a range\n");
			TRACE0("of several rows? SetStyleRange must not span over several rows\n");
			TRACE0("Or did you enable copy and paste or drag and drop with the\n");
			TRACE0("GX_DNDSTYLES flag? Only GX_DNDTEXT is possible with browser grids.\n");

			ASSERT(0);

			return FALSE;
		}

		CGXData* pData = Grid()->GetParam()->GetData();

		return pData->StoreStyleRowCol(nRow, nCol, pStyle, mt, nType);
	}
}

template<class GRID>
void CGXBrowserLayoutManager<GRID>::OnAddedNewRecord()
{
}

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//
#endif //_GXDBEGrid
