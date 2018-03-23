///////////////////////////////////////////////////////////////////////////////
// gxWrapGrid.h
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

#ifndef _GX_WRAPPED_GRID
#define _GX_WRAPPED_GRID

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif

#ifndef _GX_COVERED_PATTERN
#include "grid\HierGrid\gxCvrdPattn.h"
#endif

#ifndef _GX_HIERARCHY_GRID
#include "grid\HierGrid\gxHierGrid.h"
#endif

#ifndef _GX_WRAPPED_GRID_CORE
#include "grid\HierGrid\gxwgcore.h"
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

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXWrappedGrid<T> view
template <class T>
class CGXWrappedGrid : public CGXWrappedGridCore<T>
{
public:
	CGXWrappedGrid();           

	virtual gxHierGridType GetGridType();		// Returns the grid type of this grid
	virtual void OnShowChildAt(ROWCOL nLogRow, BOOL bShow);
	virtual BOOL IsChildShown(ROWCOL nLogRow);
	virtual void OnRowBreaksChanged(int nPrevBreaksCount);

// Attributes
public:

	// WG APIs
	// Set the logical col counts.
	virtual BOOL SetWGColCount(ROWCOL nCols, UINT flags = GX_UPDATENOW);	
	// Set the logical row counts.
	virtual BOOL SetWGRowCount(ROWCOL nRows, UINT flags = GX_UPDATENOW);

	virtual ROWCOL GetLogRowCount();
	virtual ROWCOL GetLogColCount();

	// Set the row-breaks and the indent for the wrapped rows if necessary..
	virtual BOOL SetWGRowBreaks(CDWordArray& aRowBreaks, CWordArray* panIndentWidths = NULL, UINT flags = GX_UPDATENOW);

	BOOL SetWGColWidth(ROWCOL nFromCol, ROWCOL nToCol, int nWidth, int* anWidthArray = NULL, UINT flags =GX_UPDATENOW, GXCmdType ctCmd =gxDo);
	virtual void SetPatternMap(CGXCoveredCellPatternMap* map, BOOL bMustDelete = TRUE);	// Optional; Use it to share the map between multiple grids.

	virtual BOOL ResizeWGColWidthsToFit(CGXRange& range, UINT nFlags = GX_UPDATENOW);
	virtual BOOL ResizeWGRowHeightsToFit(CGXRange& range, UINT nFlags = GX_UPDATENOW);

	virtual BOOL InsertWGCols(ROWCOL nCol,	ROWCOL nCount, int* anWidthArray =NULL,	UINT flags = GX_UPDATENOW);
	virtual BOOL InsertWGRows(ROWCOL nRow, ROWCOL nCount, UINT flags = GX_UPDATENOW);
	virtual BOOL RemoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags  = GX_UPDATENOW);
	virtual BOOL RemoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags  = GX_UPDATENOW);
	virtual BOOL MoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL MoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bInsertToTheRight = FALSE, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	virtual BOOL SetWGColBaseStyle(ROWCOL nFromWGCol, ROWCOL nToWGCol, const CGXStyle& style, GXModifyType mt = gxOverride, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetWGRowBaseStyle(ROWCOL nFromWGRow, ROWCOL nToWGRow, const CGXStyle& style, GXModifyType mt = gxOverride, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	// Internal APIs...
	virtual BOOL StoreWGColWidth(ROWCOL nCol, int nWidth = 0);
	
	virtual BOOL StoreRowBreaks(CDWordArray& aRowBreaks, CWordArray* panIndentWidths, BOOL bProcessed  = FALSE );

	virtual void InitWrappedGridSettings();		// Will be called whenever the WG schema changes (for ex. the row-breaks).

	// IGXHierarchyGrid APIs
	virtual void OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol);
	virtual BOOL GetPMValueAt(ROWCOL nRow);
	virtual BOOL GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId);
	virtual void GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol);
	virtual BOOL GetAbsCellFromLogCell(ROWCOL nWGRow, ROWCOL nWGCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol);	// Convert the logical cell to the absolute cell in the grid. 
	virtual void GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nWGRow, ROWCOL& nWGCol); // Convert the absolute cell in the grid to the logical cell
	virtual void UpdateHintFromPeer(CGXGridHint* pHint);

public:
	
	virtual BOOL StoreInsertWGCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);

	virtual BOOL StoreRemoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);
	
	virtual BOOL StoreInsertWGRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);

	virtual BOOL StoreRemoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);

	virtual BOOL StoreMoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual void UpdateMoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, BOOL bCreateHint = FALSE);

	virtual BOOL StoreMoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bInsertToTheRight, BOOL bProcessed = FALSE);
	virtual void UpdateMoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, BOOL bCreateHint = FALSE);

//	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
//	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
protected:
	// Overrides for selection, dragging and moving rows/cols
	virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);
	virtual BOOL DoLButtonDown(UINT flags, CPoint point);
	virtual BOOL DoMouseMove(UINT flags, CPoint point);
	virtual BOOL DoLButtonUp(UINT flags, CPoint point);
	virtual BOOL StoreWGSelectRange(const CGXRange& range, BOOL bSelect = TRUE);
	virtual void PrepareChangeWGSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0, BOOL bCreateHint = FALSE);
	virtual BOOL OnSelDragStart(ROWCOL nLogRow, ROWCOL nLogCol);
	virtual BOOL OnSelDragMove(ROWCOL nLogRow1, ROWCOL nLogCol1, ROWCOL nLogRow, ROWCOL nLogCol);
	virtual BOOL OnSelDragDrop(ROWCOL nLogRow1, ROWCOL nLogCol1, ROWCOL nLogRow, ROWCOL nLogCol);
	virtual void DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem);
	virtual BOOL OnSelDragColsMove(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);
	virtual BOOL OnSelDragRowsMove(ROWCOL nFirstRow, ROWCOL nLastRow, ROWCOL nDestRow);

public:
	// CGXGridCore overrides.
	virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);
	virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	virtual BOOL IsRowHidden(ROWCOL nRow);
	virtual BOOL GetInvertStateRowCol(ROWCOL nRow, ROWCOL nCol, const CGXRangeList* pSelList);
	virtual CString GetCopyTextRowCol(ROWCOL nLogRow, ROWCOL nLogCol);
	virtual BOOL CopyRangeList(CGXRangeList& list, BOOL bEdit);
	virtual BOOL CopyRange(const CGXRange& range);
//	virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& strDisplay, UINT flags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);

	virtual void SelectWGRange(const CGXRange& range, BOOL bSelect = TRUE, BOOL bUpdate = TRUE);
	void SetWGSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0);


public:

// Override
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXWrappedGrid<T>)
	public:
	virtual void OnGridInitialUpdate();
	//}}AFX_VIRTUAL

public:
	// Utility Functions
	void SelectRangeImp_OnLButtonDown(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	BOOL UserDragSelectRangeImp_OnLButtonDown(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	BOOL SelectRangeImp_OnMouseMove(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol);
	BOOL UserDragSelectRangeImp_OnMouseMove(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags);
	void SelectRangeImp_OnLButtonUp(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags);
	BOOL UserDragSelectRangeImp_OnLButtonUp(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags);

	// Members
	// To maintain some transient state
	ROWCOL m_nAbsHitRow;			
	ROWCOL m_nAbsHitCol;
	// The new InsertToTheRight state while the user drags cols
	ROWCOL m_bInsertToTheRight;		// Just used as an argument to pass to OnSelDragMove
									// Use it only within your override of OnSelDragMove
	// The current InsertToTheRight state while the user drags cols
	ROWCOL m_bCurInsertToTheRight;
};
/////////////////////////////////////////////////////////////////////////////
// CGXWrappedGrid<T>

template<class T>
CGXWrappedGrid<T>::CGXWrappedGrid()
{
	m_nAbsHitRow = 0;
	m_nAbsHitCol = 0;
}


template<class T>
gxHierGridType CGXWrappedGrid<T>::GetGridType()
{
	return gxWrappedGrid;
}

template<class T>
int CGXWrappedGrid<T>::OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint & pt, CRect & rect)
{
	int nFrame = m_nHitTestFrame;
	int nRet = CGXGridCore::OnExtHitTest(ncRow, ncCol, pt, rect);
	// If no headers then don't do any hittest

	CPoint  ptTest(
		max(0, pt.x),
		max(0, pt.y));

	int x = 0,
	y = 0;

	// Calculate ClientRow/pnCol
	ROWCOL nRow = GetRow(CalcClientRowFromPt(ptTest, &y));
	ROWCOL nCol = GetCol(CalcClientColFromPt(ptTest, &x));
//	CRect rect;
	BOOL bValid = nRow != GX_INVALID && nCol != GX_INVALID;
	if (bValid)
	{
		rect = CalcRectFromRowColExEx(nRow, nCol);
//		rect.SetRect(x, y, x+GetColWidth(GetCol(nCol)), y+GetRowHeight(GetRow(nRow)));
	}
	CGXRange range;
	ROWCOL nPattern;
	m_patternMap->GetSpanCellsRowCol(ncRow, ncCol, range, &nPattern);
	BOOL bTrackCol =  m_patternMap->m_bIsHeaders && nPattern != GX_INVALID && ncRow <= m_patternMap->GetRowSpan() && ncCol ==  range.right;
	if (bTrackCol && bValid && nCol > GetHeaderCols() && abs(rect.right-ptTest.x) <= nFrame/2)
		return GX_VERTLINE;

	BOOL bTrackRow = ncCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth();
	if (bTrackRow && bValid && abs(rect.bottom-ptTest.y) <= nFrame/2)
	{
		return GX_HORZLINE;
	}

	return nRet;
}

template<class T>
CGXRange* CGXWrappedGrid<T>::GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range)
{
	CGXRange* pRange = CGXWrappedGridCore<T>::GetCoveredCellsRowCol(nRow, nCol, range);
	if(pRange && IsPMCell(nRow, nCol))
	{
		ROWCOL nTopRow = (((nRow-1) / m_patternMap->GetRowSpan()) * m_patternMap->GetRowSpan()) + 1;
		ROWCOL nBottomRow = nTopRow + (m_patternMap->GetRowSpan() - 1);
		// The border for a covered cell is drawn only if the cell adjacent to that border is visible.
		// So, adjust the covered cell such all borders will be visible.
		if(m_bCommonChildGridHeader && ((nBottomRow-1)/m_patternMap->GetRowSpan()) == 0)// header
			;	// Do not decrement if common header
		else if(m_abRowHidden.GetBitAt(nBottomRow / 2))
			nBottomRow--;
		pRange->SetCells(nTopRow, range.left, nBottomRow, range.right);
	}
	return pRange;
}

/////////////////////////////////////////////////////////////////////////////
// CGXWrappedGrid<T> message handlers

template<class T>
void CGXWrappedGrid<T>::OnGridInitialUpdate() 
{
	// Set the row count and intialize the pattern before calling the base class...
	CGXWrappedGridCore<T>::OnGridInitialUpdate();
	BOOL bHints = m_bHintsEnabled;
	m_bHintsEnabled = FALSE;

	SetCellWidthPrecision(4);
	GetParam()->EnableSelection(GX_SELSHIFT | GX_SELCELL | GX_SELCOL | GX_SELROW | GX_SELMULTIPLE);
	HideRows(0, 0);
	HideCols(0, 0);
	GetParam()->EnableTrackColWidth(GX_TRACK_INDIVIDUAL | GX_TRACK_NOMARKTRACKLINE);
	GetParam()->EnableTrackRowHeight(GX_TRACK_INDIVIDUAL | GX_TRACK_NOMARKTRACKLINE);
	GetParam()->GetProperties()->SetMarkRowHeader(FALSE);
	GetParam()->GetProperties()->SetMarkColHeader(FALSE);
	InitWrappedGridSettings();
//	GetParam()->SetHideCurrentCell(GX_HIDE_ALWAYS);
	m_bHintsEnabled = bHints;
}

template<class T>
void CGXWrappedGrid<T>::InitWrappedGridSettings()
{
	// Set the style for the headers...

	SetStyleRange(CGXRange().SetRows(1, m_patternMap->GetRowSpan()),
		CGXStyle()
		.SetFont(CGXFont().SetBold(TRUE))
		.SetInterior(GXSYSCOLOR(COLOR_BTNFACE))
		.SetHorizontalAlignment(DT_CENTER)
		.SetVerticalAlignment(DT_VCENTER)
		.SetControl(GX_IDS_CTRL_HEADER)
		.SetEnabled(FALSE)
		);

	SetFrozenRows(m_patternMap->GetRowSpan(), m_patternMap->GetRowSpan());

	SetRowHeaderWidth(32);
	// There will be col headers for this grid.
	m_patternMap->m_bIsHeaders = TRUE;

//	m_abRowHidden.InsertBits(1, 1);	// For headers
	m_abRowHidden.SetBitAt(1, 1);
}

template<class T>
void CGXWrappedGrid<T>::SetPatternMap(CGXCoveredCellPatternMap* pMap, BOOL bMustDelete /*= TRUE*/)
{
	CGXWrappedGridCore<T>::SetPatternMap(pMap, bMustDelete);
	InitWrappedGridSettings();
#ifdef _WIN64 //RW64
	INT_PTR nRowBreaks = pMap->GetRowBreaks()->GetSize();
#else
	int nRowBreaks = pMap->GetRowBreaks()->GetSize();
#endif //_WIN64

	for(int i=1; i<=nRowBreaks; i++)
		m_abRowHidden.SetBitAt(i, 1);
	SetFrozenRows(m_patternMap->GetRowSpan(), m_patternMap->GetRowSpan());	
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGColWidth(ROWCOL nFromCol, ROWCOL nToCol, int nWidth, int* anWidthArray /*NULL*/, UINT flags /*=GX_UPDATENOW*/, GXCmdType /*ctCmd*/ /*=gxDo*/)
{
	if (nToCol == 0)
		nToCol = nFromCol;

	ASSERT(nToCol >= nFromCol);

#ifdef _DEBUG
	ASSERT(anWidthArray == NULL || nWidth == 0);
	// ASSERTION-> Ambigous command call ->END

	if (anWidthArray)
		ASSERT(AfxIsValidAddress(anWidthArray, (UINT) (sizeof(int)*(nToCol-nFromCol+1))));
	// ASSERTION-> anWidthArray is not valid, perhaps too small? ->END
#endif

	CGXLongOperation theOp;

	BOOL b = FALSE;
	for (ROWCOL nCol = nFromCol; nCol <= nToCol; nCol++)
	{
		// Store the width in the param as well for use by other (regular) grids.
		if (anWidthArray)
		{
			b |= StoreColWidth(nCol, anWidthArray[nCol-nFromCol]);
			b |= StoreWGColWidth(nCol, anWidthArray[nCol-nFromCol]);
		}
		else
		{
			b |= StoreColWidth(nCol, nWidth);
			b |= StoreWGColWidth(nCol, nWidth);
		}

		theOp.DoMessages();
	}

	if (b)
	{
		m_nLastVisibleCol = GX_INVALID;

		ResetCurrentCell();
		if(!IsLockUpdate())
			Redraw(flags);

		// Create Hint
		if (m_pUpdateHintImp && m_bHintsEnabled)
			m_pUpdateHintImp->HintUpdateChangedColWidths(this, nFromCol, nToCol, NULL, flags);

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGRowBreaks(CDWordArray& aRowBreaks, CWordArray* panIndentWidths, UINT flags /*= GX_UPDATENOW*/)
{
	if(panIndentWidths)
		ASSERT(aRowBreaks.GetSize() == panIndentWidths->GetSize());
		
	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;

	// Get the current cell and reset it after changing the row breaks.
	ROWCOL nEditRow=0, nEditCol=0, nLogRow=0, nLogCol=0;
	BOOL bResetCurrentCell = FALSE;	// If TRUE move the current cell after insertion.
	if(GetCurrentCell(nEditRow, nEditCol))
	{
		GetLogCellFromAbsCell(nEditRow, nEditCol, nLogRow, nLogCol);
		bResetCurrentCell = TRUE;
	}

	if(aRowBreaks.GetSize() < m_patternMap->GetRowBreaks()->GetSize() && m_patternMap->m_bIsHeaders)
		// Remove current header styles for header rows.
		SetStyleRange(CGXRange().SetRows(1, m_patternMap->GetRowSpan()),
			NULL, gxRemove);

#ifdef _WIN64 //RW64	
	INT_PTR nOldBreaksSize = m_patternMap->GetRowBreaks()->GetSize();
#else
	int nOldBreaksSize = m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64

	StoreRowBreaks(aRowBreaks, panIndentWidths);
		
	// Move the current cell to it's new position
	if(bResetCurrentCell)
	{
		ROWCOL nAbsRow, nAbsCol;
		GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
		// Store in grid
		StoreCurrentCell(TRUE, nAbsRow, nAbsCol);
		// Sync control
		GetCurrentCell(nEditRow, nEditCol);
		CGXControl* pControl = GetControl(nEditRow, nEditCol);
		if (pControl->IsInit())
			pControl->Init(nEditRow, nEditCol);
	}

	if (!IsLockUpdate())
	{
		BOOL bLock = LockScrollbars(TRUE);

		Redraw(flags, FALSE);

		LockScrollbars(bLock);

		if (flags & GX_UPDATENOW || flags & GX_SMART)
			UpdateScrollbars(FALSE);
	}

	if (m_pTooltipProxy)
		m_pTooltipProxy->Reset();

	// Send a hint before changing the row breaks.
	if (m_bHintsEnabled)
	{
		CGXGridHint hint(gxHintChangingRowBreaks, m_nViewID);
		
#ifdef _WIN64 //RW64
		hint.lParam  = static_cast<LONG>(nOldBreaksSize);
#else
		hint.lParam  = nOldBreaksSize;
#endif //_WIN64
		
		hint.vptr = (void*)m_patternMap->GetRowBreaks();	// New breaks
		hint.flags = flags;
		UpdateAllViews(m_pGridWnd, 0, &hint);
	}

	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreRowBreaks(CDWordArray& aRowBreaks, CWordArray* panIndentWidths, BOOL bProcessed /* = FALSE */)
{
	bProcessed = TRUE;
#ifdef _WIN64 //RW64
	INT_PTR nPrevBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#else
	int nPrevBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64
	
	// Convert widths in terms of pixels to multiple of absolute cells.
	if(panIndentWidths)
	{
		for(int i=0; i < panIndentWidths->GetSize(); i++)
        {
			panIndentWidths->SetAt(i, panIndentWidths->GetAt(i)/Width_LPtoDP(m_patternMap->m_nCellWidthPrecision));
		}
	}

	// Modifiy the stored breaks array.
	m_patternMap->SetRowBreaks(&aRowBreaks, panIndentWidths);

//	InitWrappedGridSettings();
#ifdef _WIN64 //RW64
	// Loss of data.
	OnRowBreaksChanged(static_cast<int>(nPrevBreaksCount));
#else
	OnRowBreaksChanged(nPrevBreaksCount);
#endif //_WIN64

	return TRUE;
}

template<class T>
void CGXWrappedGrid<T>::OnRowBreaksChanged(int nPrevBreaksCount)
{
	// Set the style for the headers...
	if(m_patternMap->m_bIsHeaders)
	{
		SetStyleRange(CGXRange().SetRows(1, m_patternMap->GetRowSpan()),
			CGXStyle()
			.SetFont(CGXFont().SetBold(TRUE))
			.SetInterior(GXSYSCOLOR(COLOR_BTNFACE))
			.SetHorizontalAlignment(DT_CENTER)
			.SetVerticalAlignment(DT_VCENTER)
			.SetControl(GX_IDS_CTRL_HEADER)
			.SetEnabled(FALSE)
			);

		SetFrozenRows(m_patternMap->GetRowSpan(), m_patternMap->GetRowSpan());
	}
#ifdef _WIN64 //RW64
	INT_PTR nNewBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#else
	int nNewBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64

	if(nPrevBreaksCount != nNewBreaksCount)
	{
		// Adjust the m_abRowHidden array.
		CGXBitArray abNewRowHiddenArray;

#ifdef _WIN64 //RW64
		INT_PTR nTotalRows = m_nRowCount;
#else
		ROWCOL nTotalRows = m_nRowCount;
#endif //_WIN64
		nTotalRows += (m_patternMap->m_bIsHeaders ? 1 : 0);
		
#ifdef _WIN64 //RW64
		// Loss of data.
		abNewRowHiddenArray.InsertBits(1, static_cast<DWORD>(nNewBreaksCount*nTotalRows));
#else
		abNewRowHiddenArray.InsertBits(1, nNewBreaksCount*nTotalRows);
#endif //_WIN64
		int i;
		for(i = 1; i <= nNewBreaksCount*(int)nTotalRows; i++)
			abNewRowHiddenArray.SetBitAt(i, 1);

		for(i = 1; i <= (int)nTotalRows; i++)
		{
#ifdef _WIN64 //RW64
			// Loss of data.
			abNewRowHiddenArray.SetBitAt(static_cast<DWORD>(i*nNewBreaksCount), m_abRowHidden.GetBitAt(i*nPrevBreaksCount));
#else
			abNewRowHiddenArray.SetBitAt(i*nNewBreaksCount, m_abRowHidden.GetBitAt(i*nPrevBreaksCount));
#endif //_WIN64
		}

		m_abRowHidden.RemoveAll();
		m_abRowHidden.Copy(abNewRowHiddenArray);
	}
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGColCount(ROWCOL nCols, UINT flags /*= GX_UPDATENOW*/)
{
	// TRACE1("CGXGridCore: BEGIN SetColCount(%u)\n", nCols);
	ROWCOL nOldCols = m_patternMap->GetColCount();
	if (nCols < nOldCols)
		return RemoveWGCols(nCols+1, nOldCols, flags);
	else if (nCols > nOldCols)
		return InsertWGCols(nOldCols+1, nCols-nOldCols, NULL, flags);
	// TRACE1("CGXGridCore: END   SetColCount(%u)\n", nCols);
	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGRowCount(ROWCOL nRows, UINT flags /* = GX_UPDATENOW*/)
{
	// TRACE1("CGXGridCore: BEGIN SetRowCount(%u)\n", nRows);
	if (nRows < m_nRowCount)
		return RemoveWGRows(nRows+1, m_nRowCount, flags);
	else if (nRows > m_nRowCount)
		return InsertWGRows(m_nRowCount+1, nRows-m_nRowCount, flags);
	// TRACE1("CGXGridCore: END   SetRowCount(%u)\n", nRows);
	return TRUE;
}

template<class T>
ROWCOL CGXWrappedGrid<T>::GetLogRowCount()
{
	return m_nRowCount;
}

template<class T>
ROWCOL CGXWrappedGrid<T>::GetLogColCount()
{
	return m_patternMap->GetColCount();
}

template<class T>
BOOL CGXWrappedGrid<T>::InsertWGCols(ROWCOL nCol, ROWCOL nCount, int* anWidthArray /*=NULL*/,
	UINT flags /*= GX_UPDATENOW*/)
{
#ifdef _DEBUG
	if (anWidthArray)
		ASSERT(AfxIsValidAddress(anWidthArray, (UINT) (sizeof(int)*nCount)));
	// ASSERTION-> anWidthArray is not valid, perhaps too small? ->END
#endif

	CGXLongOperation theOp;

	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;

	CGXLockSelectionFrame tmpLockSelFrame(this);

	// Check if the current cell has to be moved after insertion.
	ROWCOL nEditRow=0, nEditCol=0, nLogRow=0, nLogCol=0;
	BOOL bResetCurrentCell = FALSE;	// If TRUE move the current cell after insertion.
	if(GetCurrentCell(nEditRow, nEditCol))
	{
		GetLogCellFromAbsCell(nEditRow, nEditCol, nLogRow, nLogCol);
		if(nLogCol >= nCol)					// Inserted before the current current-cell, so reset the current cell after insertion.
			bResetCurrentCell = TRUE;
	}

	BOOL bDone = StoreInsertWGCols(nCol, nCount);

	if (bDone)
	{
		if (anWidthArray)
		{
			for (ROWCOL n = 0; n < nCount; n++)
			{
				StoreColWidth(nCol+n, anWidthArray[n]);	// Store into the param just so it can be used by normal grids
				StoreWGColWidth(nCol+n, anWidthArray[n]);	// Store into m_patternMap->
			}
		}

		// Update the display...
		m_nLastVisibleCol = GX_INVALID;
		if(bResetCurrentCell)
		{
			ROWCOL nAbsRow=0, nAbsCol=0;
			GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
			// Store in grid
			StoreCurrentCell(TRUE, nAbsRow, nAbsCol);
			// Sync control
			GetCurrentCell(nEditRow, nEditCol);
			CGXControl* pControl = GetControl(nEditRow, nEditCol);
			if (pControl->IsInit())
				pControl->Init(nEditRow, nEditCol);
		}
		if (!IsLockUpdate())
		{
			BOOL bLock = LockScrollbars(TRUE);

			Redraw(flags, FALSE);

			LockScrollbars(bLock);

			if (flags & GX_UPDATENOW || flags & GX_SMART)
				UpdateScrollbars(FALSE);
		}

		if (m_pTooltipProxy)
			m_pTooltipProxy->Reset();

		return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::InsertWGRows(
	ROWCOL nRow,
	ROWCOL nCount,
	UINT flags /*= GX_UPDATENOW*/)
{
	CGXLongOperation theOp;

	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;

	CGXLockSelectionFrame tmpLockSelFrame(this);

	//BOOL bRefresh = FALSE;

	ROWCOL nEditRow=0, nEditCol=0, nLogRow=0, nLogCol=0;
	BOOL bResetCurrentCell = FALSE;	// If TRUE move the current cell after insertion.
	if(GetCurrentCell(nEditRow, nEditCol))
	{
		GetLogCellFromAbsCell(nEditRow, nEditCol, nLogRow, nLogCol);
		if(nLogRow >= nRow)					// Inserted before the current current-cell, so reset the current cell after insertion.
			bResetCurrentCell = TRUE;
	}

	BOOL bDone = StoreInsertWGRows(nRow, nCount);

	if (bDone)
	{
		// UpdateInsertWGRows(nRow, nCount, flags, TRUE);
		m_nLastVisibleRow = GX_INVALID;
		if(bResetCurrentCell)
		{
			ROWCOL nAbsRow=0, nAbsCol=0;
			GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
			// Store in grid
			StoreCurrentCell(TRUE, nAbsRow, nAbsCol);
			// Sync control
			GetCurrentCell(nEditRow, nEditCol);
			CGXControl* pControl = GetControl(nEditRow, nEditCol);
			if (pControl->IsInit())
				pControl->Init(nEditRow, nEditCol);
		}
		if (!IsLockUpdate())
		{
			BOOL bLock = LockScrollbars(TRUE);

			Redraw(flags, FALSE);

			LockScrollbars(bLock);

			if (flags & GX_UPDATENOW || flags & GX_SMART)
				UpdateScrollbars(FALSE);
		}
		if (m_pTooltipProxy)
			m_pTooltipProxy->Reset();

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreInsertWGCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed)
{
	// check if grid is read-only
	if (GetParam()->m_bLockReadOnly && IsReadOnly())
		return FALSE;

	if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreInsertCols(nCol, nCount);

	if (bProcessed)
	{
		m_patternMap->InsertCols(nCol, nCount);

		// hidden state
		if (m_pHideCellsImp)
			m_pHideCellsImp->InsertCols(this, nCol, nCount);

		// size
		m_pParam->m_ColWidths.Insert(nCol, nCount);

		return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreInsertWGRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed)
{
	// check if grid is read-only
	if (GetParam()->m_bLockReadOnly && IsReadOnly())
		return FALSE;

	// ... now, I can store the data
	if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreInsertRows(nRow, nCount);

	if (bProcessed)
	{
		m_nRowCount += nCount;
		// Adjust the m_abRowHidden array:
		int nInsertFrom = (int)(nRow-1)*m_patternMap->GetRowSpan()/2 + 1;
		// Adjust for col headers.
		nInsertFrom += (m_patternMap->m_bIsHeaders ? m_patternMap->GetRowSpan()/2 : 0);
		int nInsertCount = (int)(nCount * m_patternMap->GetRowSpan()/2);
		
		m_abRowHidden.InsertBits(nInsertFrom, nInsertCount);
		for(int i = nInsertFrom; i<=nInsertFrom+nInsertCount-1; i++)
		{
			m_abRowHidden.SetBitAt(i, 1);
		}

		InsertLogRows(nRow, nCount);

		SetModifiedFlag();

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::RemoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags /* = GX_UPDATENOW*/)
{
	ASSERT(nFromCol > 0 && nToCol >= nFromCol);
	
	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;

	// Check if the current cell has to be moved after removal.
	ROWCOL nEditRow=0, nEditCol=0, nLogRow=0, nLogCol=0;
	BOOL bResetCurrentCell = FALSE;	// If TRUE move the current cell after removal.
	if(GetCurrentCell(nEditRow, nEditCol))
	{
		GetLogCellFromAbsCell(nEditRow, nEditCol, nLogRow, nLogCol);
		if (nLogCol >= nFromCol && nLogCol <= nToCol)
			bResetCurrentCell = FALSE;
		else	// Reset the current cell to nEditRow, nFromCol since both the current row&col could be affected after removal.
		{
			nLogCol = nFromCol;
			bResetCurrentCell = TRUE;
		}
	}

	CGXLockSelectionFrame tmpLockSelFrame(this);
	CGXLongOperation theOp;
	theOp.SetStatusText(m_pAppData->strmRemoveCols, FALSE);

	BOOL bDone = StoreRemoveWGCols(nFromCol, nToCol);
	if (bDone)
	{
		// Update the display...
		m_nLastVisibleCol = GX_INVALID;
		
		if(bResetCurrentCell && (nLogCol <= (ROWCOL)m_patternMap->GetColCount() || nLogCol-- <= (ROWCOL)m_patternMap->GetColCount()))
		{
			ROWCOL nAbsRow, nAbsCol;
			GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
			// Store in grid
			StoreCurrentCell(TRUE, nAbsRow, nAbsCol);
			// Sync control
			GetCurrentCell(nEditRow, nEditCol);
			CGXControl* pControl = GetControl(nEditRow, nEditCol);
			if (pControl->IsInit())
				pControl->Init(nEditRow, nEditCol);
		}
		else 
			StoreCurrentCell(FALSE);
	}
	
	SetSelection(0);
	if (!IsLockUpdate())
	{
		BOOL bLock = LockScrollbars(TRUE);

		Redraw(flags, FALSE);

		LockScrollbars(bLock);

		if (flags)
			UpdateScrollbars(!(flags & GX_UPDATENOW));

	}

	if (m_pTooltipProxy)
		m_pTooltipProxy->Reset();
	
	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::RemoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags /* = GX_UPDATENOW*/)
{
	ASSERT(nFromRow > 0 && nToRow >= nFromRow);

	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;
	
	CGXLockSelectionFrame tmpLockSelFrame(this);
	
	CGXLongOperation theOp;

	theOp.SetStatusText(m_pAppData->strmRemoveRows, FALSE);

	// Check if the current cell has to be moved after removal.
	ROWCOL nEditRow=0, nEditCol=0, nLogRow=0, nLogCol=0;
	BOOL bResetCurrentCell = FALSE;	// If TRUE move the current cell after removal.
	if(GetCurrentCell(nEditRow, nEditCol))
	{
		GetLogCellFromAbsCell(nEditRow, nEditCol, nLogRow, nLogCol);
		if (nLogRow >= nFromRow && nLogRow <= nToRow)
			bResetCurrentCell = FALSE;
		else if (nLogRow > nToRow)
		{
			nLogRow -= (nToRow - nFromRow + 1);
			bResetCurrentCell = TRUE;
		}
	}


	BOOL bDone = StoreRemoveWGRows(nFromRow, nToRow);

	if (bDone)
	{
		// Update the display...
		m_nLastVisibleRow = GX_INVALID;
		if(bResetCurrentCell)
		{
			ROWCOL nAbsRow=0, nAbsCol=0;
			GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
			// Move current cell there if it's not already there.
			if(!(GetCurrentCell(nEditRow, nEditCol) && nEditRow == nAbsRow && nEditCol == nAbsCol))
			{
				StoreCurrentCell(TRUE, nAbsRow, nAbsCol);
				GetCurrentCell(nEditRow, nEditCol);
				CGXControl* pControl = GetControl(nEditRow, nEditCol);
				if (pControl->IsInit())
					pControl->Init(nEditRow, nEditCol);
			}
		}
		else
			StoreCurrentCell(FALSE);
		
	}

	SetSelection(0);

	if (!IsLockUpdate())
	{
		BOOL bLock = LockScrollbars(TRUE);

		Redraw(flags, FALSE);

		LockScrollbars(bLock);

		if (flags)
			UpdateScrollbars(!(flags & GX_UPDATENOW));

	}

	if (m_pTooltipProxy)
		m_pTooltipProxy->Reset();

	
	return TRUE;
}


template<class T>
BOOL CGXWrappedGrid<T>::StoreRemoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed /*= FALSE*/)
{
	// check if grid is read-only
	if (GetParam()->m_bLockReadOnly && IsReadOnly())
		return FALSE;

	// ... now, I can store the data
	ASSERT(nFromRow > 0 && nToRow >= nFromRow);

	if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreRemoveRows(nFromRow, nToRow);

	if (bProcessed)
	{
		m_nRowCount -= (nToRow - nFromRow + 1);

		// Adjust the m_abRowHidden array:
		ROWCOL nFrom, nTo;
		nFrom = (nFromRow - 1)*m_patternMap->GetRowSpan()/2 + 1;
		nFrom += (m_patternMap->m_bIsHeaders ? m_patternMap->GetRowSpan()/2 : 0);

		nTo = nToRow*m_patternMap->GetRowSpan()/2;
		nTo += (m_patternMap->m_bIsHeaders ? m_patternMap->GetRowSpan()/2 : 0);

		m_abRowHidden.RemoveBits(nFrom, nTo);

		SetModifiedFlag();

		// hidden state
		if (m_pHideCellsImp)
			m_pHideCellsImp->RemoveRows(this, nFromRow, nToRow);

		//RemoveLogRows(nFromRow, nToRow);

		return TRUE;
	}
	return FALSE;
}


template<class T>
BOOL CGXWrappedGrid<T>::MoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags /* = GX_UPDATENOW */, GXCmdType /*ctCmd*/ /*= gxDo*/)
{
	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;

	CGXLockSelectionFrame tmpLockSelFrame(this);

	ROWCOL nCount = nToRow-nFromRow+1;
	ROWCOL nDest  = nDestRow;
	if (nDest > nFromRow)
		nDest += nCount;

	ROWCOL nLogEditCol, nLogEditRow;
	GetLogCellFromAbsCell(m_nEditRow, m_nEditCol, nLogEditRow, nLogEditCol);

	if (nLogEditRow >= nFromRow && nLogEditRow <= nToRow && nLogEditRow >= nDest)
		nLogEditRow = nDest + (nLogEditRow - nFromRow);
	else if (nLogEditRow >= nFromRow && nLogEditRow <= nToRow && nLogEditRow < nDest)
		nLogEditRow = nDest - nCount + (nLogEditRow - nFromRow);
	else if (nLogEditRow >= nFromRow && nLogEditRow <= nDest)
		nLogEditRow = nLogEditRow - nCount;
	else if (nLogEditRow <= nFromRow && nLogEditRow >= nDest)
		nLogEditRow = nLogEditRow + nCount;

	BOOL bDone = StoreMoveWGRows(nFromRow, nToRow, nDestRow);
	
	if (bDone)
	{
		if (IsCurrentCell())
		{
			ROWCOL nEditRow, nEditCol;
			GetAbsCellFromLogCell(nLogEditRow, nLogEditCol, nEditRow, nEditCol);
			// Store in grid
			StoreCurrentCell(TRUE, nEditRow, nEditCol);

			// Sync control
			CGXControl* pControl = GetControl(nEditRow, nEditCol);
			if (pControl->IsInit())
				pControl->Init(nEditRow, nEditCol);
		}

		UpdateMoveWGRows(nFromRow, nToRow, nDestRow, flags, TRUE);

		return TRUE;
	}
	// TRACE3("CGXGridCore: END   MoveRows(%u, %u, %u)\n", nFromRow, nToRow, nDestRow);
	return FALSE;

}

template<class T>
BOOL CGXWrappedGrid<T>::MoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bInsertToTheRight /*= FALSE*/, UINT flags /* = GX_UPDATENOW */, GXCmdType /*ctCmd*/ /*= gxDo*/)
{
	// Transfer Current Cell's Data to grid
	if (!TransferCurrentCell())
		return FALSE;	

	CGXLockSelectionFrame tmpLockSelFrame(this);
	BOOL bOldInsertToTheRight = bInsertToTheRight;
	ROWCOL nCount = nToCol-nFromCol+1;
	ROWCOL nDest=0;

	// nDestCol == colcount+1 means move the cols into a new wrapped row.
	BOOL bAddNewRow = nDestCol == ((ROWCOL)m_patternMap->GetColCount() + 1);
	// bOnlyAddNewRow == TRUE means nothing to move, only update the breaks.
	BOOL bOnlyAddNewRow = bAddNewRow && nToCol == (ROWCOL)m_patternMap->GetColCount();

	int nRowOfFromCol, nRowOfToCol;
	m_patternMap->GetRowOfCol(nFromCol, nRowOfFromCol);
	m_patternMap->GetRowOfCol(nToCol, nRowOfToCol);
	// Check if trying to move all cols of the last row to a new row below it.
	if(bOnlyAddNewRow && nRowOfFromCol == nRowOfToCol && nRowOfFromCol != 1	
		&& m_patternMap->GetRowBreaks()->GetAt(nRowOfFromCol-2) == m_patternMap->GetRowBreaks()->GetAt(nRowOfFromCol-1)-nCount)
	return FALSE;

	if(bAddNewRow)
	{
		nDest = nDestCol - 1 - nCount;	// Deal with-it here as if moving to the right of the last col.
		bInsertToTheRight = TRUE;
	}
	else
		nDest = nDestCol;

	if (nDest + bInsertToTheRight + bOnlyAddNewRow > nFromCol)
		nDest += nCount;

	if(bInsertToTheRight)
	{
		// Check if nDestCol is a right-most cell in a wrapped row
		BOOL bRightMost = FALSE;
		const CDWordArray* rowBreaks = m_patternMap->GetRowBreaks();
		for(int i=0; i<rowBreaks->GetSize(); i++)
		{
			if(rowBreaks->GetAt(i) == nDest-1)
			{
				bRightMost = TRUE;
				break;
			}
			if(rowBreaks->GetAt(i) > nDest-1)
				break;
		}
		// if not the right-most then it is same as inserting to the left of the adjacent col on the right.
		if(!bRightMost)
		{
			nDestCol++;
			nDest++;
			bInsertToTheRight = FALSE;
		}
	}


	// Store the logical top/left cell.
	ROWCOL nLogTopRow, nDummyCol;
	GetLogCellFromAbsCell(GetTopRow(), GetLeftCol(), nLogTopRow, nDummyCol);
	
	// Store the logical current cell.
	ROWCOL nLogEditCol, nLogEditRow;
	GetLogCellFromAbsCell(m_nEditRow, m_nEditCol, nLogEditRow, nLogEditCol);

	if (nLogEditCol >= nFromCol && nLogEditCol <= nToCol && nLogEditCol >= nDest)
		nLogEditCol = nDest + (nLogEditCol - nFromCol) + bInsertToTheRight;
	else if (nLogEditCol >= nFromCol && nLogEditCol <= nToCol && nLogEditCol < nDest)
		nLogEditCol = nDest - (nToCol - nFromCol + 1) + (nLogEditCol - nFromCol) + bInsertToTheRight;
	else if (nLogEditCol >= nFromCol && nLogEditCol <= nDest)
		nLogEditCol = nLogEditCol - (nToCol - nFromCol + 1);
	else if (nLogEditCol <= nFromCol && nLogEditCol >= nDest)
		nLogEditCol = nLogEditCol + (nToCol - nFromCol + 1);

	BOOL bDone = StoreMoveWGCols(nFromCol, nToCol, nDestCol, bOldInsertToTheRight);

	if (bDone)
	{
		// Move the current cell to the current abs position of the existing logical current cell.
		if (IsCurrentCell())
		{
			ROWCOL nEditRow, nEditCol;
			if(nLogEditCol == GX_INVALID)	// Probably the child cell.
			{
#ifdef _WIN64
				nEditRow = static_cast<ROWCOL>((nLogEditRow + m_patternMap->m_bIsHeaders)*(m_patternMap->GetRowBreaks()->GetSize()*2) - 1);
#else
				nEditRow = (nLogEditRow + m_patternMap->m_bIsHeaders)*(m_patternMap->GetRowBreaks()->GetSize()*2) - 1;
#endif //_WIN64
				nEditCol = GetColCount();
			}
			else
				GetAbsCellFromLogCell(nLogEditRow, nLogEditCol, nEditRow, nEditCol);
			// Store in grid
			StoreCurrentCell(TRUE, nEditRow, nEditCol);

			// Sync control
			CGXControl* pControl = GetControl(nEditRow, nEditCol);
			if (pControl->IsInit())
				pControl->Init(nEditRow, nEditCol);

		}
		// Set the top row to the exisiting logical top row.
		SetTopRow((nLogTopRow + m_patternMap->m_bIsHeaders - 1) * m_patternMap->GetRowSpan() + 1);

		UpdateMoveWGCols(nFromCol, nToCol, nDestCol, flags, TRUE);
		return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreMoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed)
{
	if (nFromRow == nDestRow)
		// nothing to do!
		return FALSE;

	// ... now, I can store the data
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	// ... now, I can store the data
//	CGXRangeList* pSelList = pGrid->GetParam()->GetRangeList();

	if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreMoveRows(nFromRow, nToRow, nDestRow);

	if (bProcessed)
	{
		SetModifiedFlag();

		// hidden state
//		if (m_pHideCellsImp)
//			m_pHideCellsImp->MoveRows(this, nFromRow, nToRow, nDestRow);

		ROWCOL nAbsFromRow, nAbsToRow, nAbsDestRow;
		nAbsFromRow = nFromRow * m_patternMap->GetRowSpan() + 1;
		nAbsToRow = (nToRow + 1) * m_patternMap->GetRowSpan();
		nAbsDestRow = nDestRow * m_patternMap->GetRowSpan() + 1;

		// size
		ROWCOL nRowCount = GetRowCount();
		m_pParam->m_RowHeights.Move(nAbsFromRow, nAbsToRow, nAbsDestRow);

		// Update selection list.
		pSelList->MoveRows(nFromRow, nToRow, nDestRow, nRowCount);

		return TRUE;
	}

//	TRACE2("CGXGridMoveRowsColsImp::StoreMoveRows(%ld, %ld", nFromRow, nToRow);
//	TRACE1(", %ld) is not overriden!\n", nDestRow);

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreMoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bInsertToTheRight, BOOL bProcessed)
{
//	if (nFromCol + bInsertToTheRight == nDestCol)
		// nothing to do!
//		return FALSE;

	ROWCOL nCount = nToCol-nFromCol+1;
	ROWCOL nDest;
	//BOOL bOldInsertToTheRight = bInsertToTheRight;

	// nDestCol == colcount+1 means move the cols into a new wrapped row.
	BOOL bAddNewRow = nDestCol == ((ROWCOL)m_patternMap->GetColCount() + 1);
	// bOnlyAddNewRow == TRUE means nothing to move, only update the breaks.
	BOOL bOnlyAddNewRow = bAddNewRow && nToCol == (ROWCOL)m_patternMap->GetColCount();

	if(bAddNewRow)
	{
		nDestCol = nDestCol - 1 - nCount;	// Deal with-it here as if moving to the right of the last col.
		bInsertToTheRight = TRUE;
	}

	nDest = nDestCol;
	if (nDest + bInsertToTheRight + bOnlyAddNewRow > nFromCol)
		nDest += nCount;

	// ... now, I can store the data
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if(bOnlyAddNewRow)	// Nothing to move in CGXData.
		bProcessed = TRUE;
	else if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreMoveCols(nFromCol, nToCol, nDestCol + bInsertToTheRight);
	
	if (bProcessed)
	{
		if(!bOnlyAddNewRow)	// if bOnlyAddNewRow == TRUE then you don't have anything to move.
		{
			// Update Col Widths.
			m_pParam->m_ColWidths.Move(nFromCol, nToCol, nDestCol + bInsertToTheRight);
			// MoveCols in 2 shots if inserting to the right of the right-most cell in a row.
			// First insert to the left of the dest col.
			m_patternMap->MoveColWidth(nFromCol, nToCol, nDest);
			// Then move the dest col before the inserted cols.
			if(bInsertToTheRight)
			{
				if(nFromCol > nDest)
					m_patternMap->MoveColWidth(nDest + (nToCol - nFromCol + 1), nDest + (nToCol - nFromCol + 1), nDest);
				else if(nToCol < nDest)
					m_patternMap->MoveColWidth(nDest, nDest, nDest - (nToCol - nFromCol + 1));
			}
		}
#ifdef _WIN64 //RW64
		INT_PTR nPrevBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#else
		int nPrevBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64
		// 
		if(bAddNewRow)
		{
			// Temp indent widths.
			CWordArray aTempIndentWidths;
			aTempIndentWidths.Copy(m_patternMap->m_indentWidths);

			// Temp breaks array
			CDWordArray aTempBreaksArray;
			aTempBreaksArray.Copy(*m_patternMap->GetRowBreaks());

			if(bOnlyAddNewRow)	// 
			{
				int nRowOfFromCol;
				m_patternMap->GetRowOfCol(nFromCol, nRowOfFromCol);
				nRowOfFromCol--;	// 1 to 0 based.
				aTempBreaksArray.SetAt(nRowOfFromCol, nFromCol - 2);
				aTempBreaksArray.SetAtGrow(nRowOfFromCol+1, m_patternMap->GetColCount()-1);
				aTempBreaksArray.SetSize(nRowOfFromCol+2);
				aTempIndentWidths.SetSize(nRowOfFromCol+2);	
			}
			else
			{
				aTempBreaksArray.SetAt(nPrevBreaksCount-1, m_patternMap->GetColCount() - 1 - nCount);
				aTempBreaksArray.Add(m_patternMap->GetColCount()-1);
				aTempIndentWidths.Add(0);	// For the newly added row.
			}
			m_patternMap->SetRowBreaks(&aTempBreaksArray, &aTempIndentWidths);
		}

		// If breaks count changes due to adding a new row or removing an empty row, then update certain members.
		if(m_patternMap->PurgeEmptyRows() || nPrevBreaksCount != m_patternMap->GetRowBreaks()->GetSize())
		{
			BOOL bOldLock = LockUpdate(TRUE);
#ifdef _WIN64 //RW64
			OnRowBreaksChanged(static_cast<int>(nPrevBreaksCount));
#else
			OnRowBreaksChanged(nPrevBreaksCount);
#endif //_WIN64
			LockUpdate(bOldLock);
		}

		// Send a hint before changing the row breaks.
		if (m_bHintsEnabled)
		{
			CGXGridHint hint(gxHintChangingRowBreaks, m_nViewID);
#ifdef _WIN64 //RW64
			// Loss of data.
			hint.lParam  = static_cast<LONG>(nPrevBreaksCount);
#else
			hint.lParam  = nPrevBreaksCount;
#endif //_WIN64
			hint.vptr = (void*)m_patternMap->GetRowBreaks();	// New breaks
			hint.flags = GX_UPDATENOW;
			UpdateAllViews(m_pGridWnd, 0, &hint);
		}
		
		// Update selection list.
		pSelList->MoveCols(nFromCol, nToCol, nDestCol + bInsertToTheRight, GetColCount());

		SetModifiedFlag();
		return TRUE;
	}
	return FALSE;
}

template<class T>
void CGXWrappedGrid<T>::UpdateMoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL /*nDestCol*/, UINT flags, BOOL /*bCreateHint*/ /* = FALSE */)
{
	m_nLastVisibleCol = GX_INVALID;

	ASSERT(nToCol >= nFromCol);

	if (!IsLockUpdate())
		Redraw(flags, FALSE);

	#if _MFC_VER >= 0x0400
		if (m_pTooltipProxy)
			m_pTooltipProxy->Reset();
	#endif

	// Same as changed col widths.
	if (m_pUpdateHintImp && m_bHintsEnabled)
		m_pUpdateHintImp->HintUpdateChangedColWidths(this, nFromCol, nToCol, NULL, flags);
}

template<class T>
void CGXWrappedGrid<T>::UpdateMoveWGRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL /*nDestRow*/, UINT flags, BOOL /*bCreateHint*/)
{
	m_nLastVisibleRow = GX_INVALID;

	// TRACE3("CGXGridCore: BEGIN UpdateMoveRows(%u, %u, %u)\n", nFromRow, nToRow, nDestRow);
	// ASSERT(!m_bPrintInProgress);
	ASSERT(nToRow >= nFromRow);

	// Update excel selection frame only
//	pGrid->m_rgLastSelectionFrame.m_bValid = FALSE;
//	if (!pGrid->GetParam()->GetRangeList()->IsEmpty())
//		pGrid->DrawSelectionFrame(NULL, FALSE, pGrid->GetParam()->GetRangeList()->GetTail());

	if (!IsLockUpdate())
		Redraw(flags, FALSE);

#if _MFC_VER >= 0x0400
	if (m_pTooltipProxy)
		m_pTooltipProxy->Reset();
#endif

	// TRACE3("CGXGridCore: END   UpdateMoveRows(%u, %u, %u)\n", nFromRow, nToRow, nDestRow);
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreRemoveWGCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed /*= FALSE*/)
{
	// check if grid is read-only
	if (GetParam()->m_bLockReadOnly && IsReadOnly())
		return FALSE;

	// ... now, I can store the data
	ASSERT(nToCol >= nFromCol && nFromCol > 0);
	if (m_pParam->m_pData)
		bProcessed |= m_pParam->m_pData->StoreRemoveCols(nFromCol, nToCol);

	if (bProcessed)
	{
		m_patternMap->RemoveCols(nFromCol, nToCol-nFromCol+1);
		SetModifiedFlag();

		// hidden state
		if (m_pHideCellsImp)
			m_pHideCellsImp->RemoveCols(this, nFromCol, nToCol);

		// size
		ROWCOL nColCount = GetColCount();
		m_pParam->m_ColWidths.Remove(nFromCol, nToCol);

		return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreWGColWidth(ROWCOL nCol, int nWidth /* = 0 */)
{
	int nOldWidth, nNewWidth;
	nOldWidth = m_patternMap->GetColWidth(nCol);
	if (nWidth >= 0)
		nNewWidth = Width_DPtoLP(nWidth)/m_patternMap->m_nCellWidthPrecision;
	else
		nNewWidth = m_patternMap->m_nDefaultCellWidth;

	m_patternMap->SetColWidth(nCol, nNewWidth);
	if(m_gridParent)
		m_gridParent->OnChangedChildColWidth(m_nChildId);

	SetModifiedFlag();
	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGColBaseStyle(ROWCOL nFromWGCol, ROWCOL nToWGCol, const CGXStyle& style, GXModifyType mt /*= gxOverride*/, const CObArray* pCellsArray/* = NULL*/, UINT flags /*= GX_UPDATENOW*/, GXCmdType ctCmd /*= gxDo*/)
{
	// Change the type to -2. 
	// -2 means logical columns in the range param.
	return SetStyleRange(CGXRange().SetCols(nFromWGCol, nToWGCol), &style, mt, -2, pCellsArray, flags, ctCmd);
}

template<class T>
BOOL CGXWrappedGrid<T>::SetWGRowBaseStyle(ROWCOL nFromWGRow, ROWCOL nToWGRow, const CGXStyle& style, GXModifyType mt /* = gxOverride */, const CObArray* pCellsArray /* = NULL */, UINT flags /*= GX_UPDATENOW */, GXCmdType ctCmd /* = gxDo */)
{
	ROWCOL nAbsFromRow, nAbsToRow, nDummyCol;	// Just calculate one of the absolute rows in the logical row.
	GetAbsCellFromLogCell(nFromWGRow, 1, nAbsFromRow, nDummyCol);
	GetAbsCellFromLogCell(nToWGRow, 1, nAbsToRow, nDummyCol);
	return SetStyleRange(CGXRange().SetRows(nAbsFromRow, nAbsToRow), &style, mt, -1, pCellsArray, flags, ctCmd);

}

template<class T>
int CGXWrappedGrid<T>::GetPMValueAt(ROWCOL nRow)
{
	if(nRow == 0 && m_bPrintInProgress)
		return 2;

	// Calculate the absolute bottom row in this logical row.
	ROWCOL nBottomRow = ((nRow / m_patternMap->GetRowSpan()) + 1) * m_patternMap->GetRowSpan();
	// Expanded: 1
	// Collapsed: 2
	if(m_abRowHidden.GetBitAt((nBottomRow+1)/2) != 1)	// 1-collapsed, 0-expanded
		return 1;	// Expanded
	else
		return 2;	// Collpased
}

/*
template<class T>
BOOL CGXWrappedGrid<T>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	if(nType >= 0 && nRow != 0 && nCol != 0)
	{
		CGXRange range;
		ROWCOL nPatternCol;
		m_patternMap->GetSpanCellsRowCol(nRow, nCol, range, &nPatternCol);
		if(nPatternCol == GX_INVALID)
		{
			if(nRow == GetRowCount())
				style.SetBorders(gxBorderBottom, CGXPen().SetColor(GXSYSCOLOR(COLOR_BTNFACE)));
			if((nRow % 2) == 0)
			{
				style.SetValue(_T("Child Grid"));
				return TRUE;
			}
			// Set the border colors such that the grid merges into its background smoothly...
			style.SetControl(GX_IDS_CTRL_STATIC).SetIncludeValue(FALSE).SetInterior(GXSYSCOLOR(COLOR_BTNFACE)).SetBorders(gxBorderRight, CGXPen().SetColor(GXSYSCOLOR(COLOR_BTNFACE)));
			return TRUE;
		}
		else
		{
			// Assuming row header will always be col 1.
			if(nCol == 1 && m_patternMap->GetRowHeaderWidth() > 0)
				style.SetBaseStyle(GetParam()->GetStylesMap()->m_wStyleColHeader);
			else 
			{
//			ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan());
				ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
				return T::GetStyleRowCol(nPatternRow, nPatternCol, style, mt, nType);
			}
		}
	}
	else if(nType == -1)	// Applicable only for row base styles
	{
		ASSERT(nCol == 0);
		if((nRow % 2) == 0)	// Child grid row, do nothing
			return TRUE;
//		ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan());
		ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
		return T::GetStyleRowCol(nPatternRow, nCol, style, mt, nType);
	}
	else if(nType == -2)	// For WG Col base style.
	{
		return T::GetStyleRowCol(0, nCol, style, mt, -1);
	}
//	else ASSERT (FALSE);
	return FALSE;
}*/

/*
template<class T>
BOOL CGXWrappedGrid<T>::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
	if(nType == 0 || nType == 1)
	{
		// Row header value...
		if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth())
			return CGXWrappedGridCore<T>::StoreStyleRowCol(nPatternRow, 0, pStyle, mt, nType);
		CGXRange range;
		ROWCOL nPatternCol;
		m_patternMap->GetSpanCellsRowCol(nRow, nCol, range, &nPatternCol);
		if(!(nPatternCol == GX_INVALID))
		{
			return CGXWrappedGridCore<T>::StoreStyleRowCol(nPatternRow, nPatternCol, pStyle, mt, nType);
		}
		return FALSE;
	}
	else if(nType == -1)	// Applicable only for row base styles
	{
//		ASSERT((nRow % 2) != 0);	// Child grid cell.
		return CGXWrappedGridCore<T>::StoreStyleRowCol(nPatternRow, 0, pStyle, mt, nType);
	}
	else if(nType == -2)	// Applicable for col base styles. nCol should already be the logical col.
	{
		return T::StoreStyleRowCol(0, nCol, pStyle, mt, -1);
	}
	else ASSERT(FALSE);
	return FALSE;
}
*/

template<class T>
BOOL CGXWrappedGrid<T>::IsRowHidden(ROWCOL nRow)
{
	// Is child grid header?
	if((nRow == m_patternMap->GetRowSpan()) && m_bCommonChildGridHeader && !m_bPrintInProgress)
		return FALSE;

	return CGXWrappedGridCore<T>::IsRowHidden(nRow);
}


template<class T>
void CGXWrappedGrid<T>::OnClickedPMCell(ROWCOL nAbsRow, ROWCOL /*nAbsCol*/)
{
	// Calculate the absolute bottom row in this logical row.
	ROWCOL nBottomRow = ((nAbsRow / m_patternMap->GetRowSpan()) + 1) * m_patternMap->GetRowSpan();
	// 1 means collapsed, 0 means expanded
	BOOL bHide = FALSE;
	bHide = m_abRowHidden.GetBitAt((nBottomRow+1)/2);
	bHide = !bHide;

	ROWCOL nLogRow, nLogCol;
	GetLogCellFromAbsCell(nAbsRow, 1, nLogRow, nLogCol);
	if(!bHide)
		ShowChildAt(nLogRow, TRUE);
	else
		ShowChildAt(nLogRow, FALSE);
}

template<class T>
void CGXWrappedGrid<T>::OnShowChildAt(ROWCOL nLogRow, BOOL bShow)
{
	ROWCOL nPatRow = ((nLogRow+m_patternMap->m_bIsHeaders) * m_patternMap->GetRowSpan())/2;
	// 1 for hidden, 0 for show.
	m_abRowHidden.SetBitAt(nPatRow, !bShow);
	if(!bShow)
	{
		ROWCOL nCurRow, nCurCol;
		// Check if current cell is in child grid
		if(GetCurrentCell(nCurRow, nCurCol) && nCurRow == (nPatRow*2))
		{
			TransferCurrentCell();
			MoveCurrentCell(GX_UP, 1);
		}
	}
	// Update could be more efficient.
	Redraw();
}

template<class T>
BOOL CGXWrappedGrid<T>::IsChildShown(ROWCOL nLogRow)
{
	if(GetPMValueAt(nLogRow * m_patternMap->GetRowSpan()) == 2) // Collapsed
		return FALSE;
	else 
		return TRUE;
//	ROWCOL nPatRow = ((nLogRow+m_patternMap->m_bIsHeaders) * m_patternMap->GetRowSpan())/2;
//	return m_abRowHidden.GetBitAt(nPatRow);
}

template<class T>
void CGXWrappedGrid<T>::GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol)
{
	ASSERT(nChildId <= GetLogRowCount());
	nChildRow = (nChildId+1)*m_patternMap->GetRowSpan();
	nChildCol = m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth
					+ m_patternMap->m_wChildIndentWidth + 1;
}

template<class T>
BOOL CGXWrappedGrid<T>::GetAbsCellFromLogCell(ROWCOL nWGRow, ROWCOL nWGCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol)
{
	return m_patternMap->GetAbsRangeFromPatternCell(nWGRow, nWGCol, nOrigRow, nOrigCol);
}

template<class T>
void CGXWrappedGrid<T>::GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nWGRow, ROWCOL& nWGCol)
{
	CGXRange range;
	m_patternMap->GetSpanCellsRowCol(nOrigRow, nOrigCol, range, &nWGCol);
	nWGRow = (ROWCOL)((nOrigRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
}

template<class T>
BOOL CGXWrappedGrid<T>::GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId)
{
	if(nRow && (nRow % m_patternMap->GetRowSpan()) == 0)
	{
		if((int)nCol > (m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + m_patternMap->m_wChildIndentWidth))
		{
			ROWCOL nDummyCol;
			GetLogCellFromAbsCell(nRow, nCol, nChildId, nDummyCol);
			return TRUE;
		}
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::ResizeWGColWidthsToFit(CGXRange& range, UINT nFlags)
{
	CClientDC dc(m_pGridWnd);
	OnGridPrepareDC(&dc);

	// select default font into device context
	CGXStyle* pStyleStandard = &StandardStyle();
	CFont* pOldFont = LoadFont(&dc, *pStyleStandard);

	// Get the HFONT handle because pOldFont is only a temporary CGdiObject object 
	// and is only valid until the next time the application has idle time in its 
	// event loop.
	HFONT hOldFont = (HFONT) pOldFont->GetSafeHandle();

	range.ExpandRange(0, 0, m_nRowCount, m_patternMap->GetColCount());

	CGXLongOperation theOp;
	theOp.SetStatusText(m_pAppData->strmResizeCols);
	BeginTrans(m_pAppData->strmResizeCols);

	int nMaxWidth;
	ASSERT(range.left >= 1);
//	ROWCOL nfr = GetFrozenCols();
	CRect rectGrid = GetGridRect();

	if (rectGrid.Width() == NULL)
	{
		TRACE(
			_T("Warning: ResizeWGColWidthsToFit called for a GridWnd whose client area is CSize(0,0)\n")
			_T("It is possible that sized columns do not fit into the grid area\n"));
		CWnd* pWnd = m_pGridWnd->GetParent();
		if (pWnd == NULL)
			pWnd = m_pGridWnd->GetTopWindow();
		if (pWnd)
			pWnd->GetClientRect(&rectGrid);
		else
			rectGrid.SetRect(0,0,32767,32767);
	}

	TRY
	{
		BOOL bAbort(FALSE);
		CGXRange rgCovered;
		for (ROWCOL nCol = range.left; nCol <= range.right; nCol++)
		{
			nMaxWidth = max(0, rectGrid.Width() - CalcSumOfColWidths(0, m_patternMap->GetRowHeaderWidth()+m_patternMap->m_nPMButtonCellWidth) - 1);

			int nWidth;
			nWidth = 0;
			for (ROWCOL nRow = range.top; nRow <= range.bottom; nRow++)
			{
				// Skip invisible rows
				BOOL bCanResize = GetRowHeight(nRow) > 0;
				
				if (bCanResize)
				{
					CGXStyle* pStyle = CreateStyle();

					CSize size;

					ROWCOL nAbsRow, nAbsCol;
					GetAbsCellFromLogCell(nRow, nCol, nAbsRow, nAbsCol);
					ComposeStyleRowCol(nAbsRow, nAbsCol, pStyle);
					CGXControl* pControl = GetRegisteredControl(pStyle->GetControl());
					pControl->LoadStyle(nAbsRow, nAbsCol, pStyle);

					size = pControl->CalcSize(&dc, nAbsRow, nAbsCol, *pStyle, pStyleStandard, FALSE);

					nWidth = max(nWidth, size.cx);

					// Style object recycling (CreateStyle will use this style-object again)
					RecycleStyle(pStyle);
				}

				theOp.DoMessages(bAbort);
				if (bAbort)
					AfxThrowUserException();
			}

			nWidth = min(nMaxWidth, nWidth);

			if (nFlags & GX_NOSHRINKSIZE)
			{
				if (nWidth > GetColWidth(nCol))
					SetWGColWidth(nCol, nCol, nWidth, NULL, nFlags);
			}
			else
			{
				if (nWidth != GetColWidth(nCol) && nWidth > 0)
					SetWGColWidth(nCol, nCol, nWidth, NULL, nFlags);
			}
		}

		if (hOldFont)
			dc.SelectObject(CFont::FromHandle(hOldFont));

		CommitTrans();
	}
	CATCH(CUserException, e)
	{
		if (hOldFont)
			dc.SelectObject(CFont::FromHandle(hOldFont));

		Rollback();
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::ResizeWGRowHeightsToFit(CGXRange& range, UINT nFlags)
{
	CClientDC dc(m_pGridWnd);
	OnGridPrepareDC(&dc);

	// select default font into device context
	CGXStyle* pStyleStandard = &StandardStyle();
	CFont* pOldFont = LoadFont(&dc, *pStyleStandard);

	// Get the HFONT handle because pOldFont is only a temporary CGdiObject object 
	// and is only valid until the next time the application has idle time in its 
	// event loop.
	HFONT hOldFont = (HFONT) pOldFont->GetSafeHandle();

	range.ExpandRange(0, 0, m_nRowCount, m_patternMap->GetColCount());
	if(range.left == 0)range.left ++;

	CGXLongOperation theOp;
	theOp.SetStatusText(m_pAppData->strmResizeRows);
	BeginTrans(m_pAppData->strmResizeRows);

	ROWCOL nfr = GetFrozenRows();
	// Convert nfr to logical row
	nfr = nfr / m_patternMap->GetRowSpan();
	m_patternMap->m_bIsHeaders ? nfr : nfr++;

	CRect rectGrid = GetGridRect();

	if (rectGrid.Height() == 0)
	{
		TRACE(
			_T("Warning: ResizeWGRowHeightsToFit called for a GridWnd which client's area is CSize(0,0)\n")
			_T("It is possible that sized rows do not fit into the grid area\n"));
		CWnd* pWnd = m_pGridWnd->GetParent();
		if (pWnd == NULL)
			pWnd = m_pGridWnd->GetTopWindow();
		if (pWnd)
			pWnd->GetClientRect(&rectGrid);
		else
			rectGrid.SetRect(0,0,32767,32767);
	}

	TRY
	{
		BOOL bAbort(FALSE);
		CGXRange rgCovered;
		for (ROWCOL nLogRow = range.top; nLogRow <= range.bottom; nLogRow++)
		{
			ROWCOL nAbsRow, nAbsCol;
			int nHeight;
			nHeight = 0;
			for (ROWCOL nLogCol = range.left; nLogCol <= range.right; nLogCol++)
			{
				GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);
				// Skip invisible columns
				BOOL bCanResize = FALSE;

				// skip invisible columns
				bCanResize = m_patternMap->GetColWidth(nLogCol) > 0;

				if (bCanResize)
				{
					CGXStyle* pStyle = CreateStyle();

					CSize size;

					ComposeStyleRowCol(nAbsRow, nAbsCol, pStyle);
					CGXControl* pControl = GetRegisteredControl(pStyle->GetControl());
					pControl->LoadStyle(nAbsRow, nAbsCol, pStyle);

					size = pControl->CalcSize(&dc, nAbsRow, nAbsCol, *pStyle, pStyleStandard, TRUE);

					nHeight = max(nHeight, size.cy);

					// Style object recycling (CreateStyle will use this style-object again)
					RecycleStyle(pStyle);
				}

				theOp.DoMessages(bAbort);
				if (bAbort)
					AfxThrowUserException();

			}

//			nHeight = min(nMaxHeight, nHeight);

			ROWCOL nAbsTopRow, nAbsBottomRow;
			GetAbsCellFromLogCell(nLogRow, 1, nAbsTopRow, nAbsCol);
			GetAbsCellFromLogCell(nLogRow, m_patternMap->GetColCount(), nAbsBottomRow, nAbsCol);
			// Adjust the height of all the wrapped rows to the new height.
			for(nAbsRow = nAbsTopRow; nAbsRow <= nAbsBottomRow; nAbsRow += 2)
			{
				if (nHeight != GetRowHeight(nAbsRow) && nHeight > 0)
					SetRowHeight(nAbsRow, nAbsRow, nHeight, NULL, nFlags);
			}
		}

		if (hOldFont)
			dc.SelectObject(CFont::FromHandle(hOldFont));

		CommitTrans();
	}
	CATCH(CUserException, e)
	{
		if (hOldFont)
			dc.SelectObject(CFont::FromHandle(hOldFont));

		Rollback();
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

// Changed the logic sligtly for calling GetStyleRowCol for col base styles.
template<class T>
void CGXWrappedGrid<T>::ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard)
{
	ASSERT(nRow <= GetRowCount() && nCol <= GetColCount());
	// -> ASSERTION Coordinates out of range ->END

//  TRACE2("ComposeStyleRowCol(%ld, %ld)\n", nRow, nCol);

	_TC_(DWORD ti2 = GetTickCount());
	GetStyleRowCol(nRow, nCol, *pStyle, gxCopy, 0);
	_TC_(tick2 += GetTickCount()-ti2);

	// Check if you only need the value
	if (m_bOnlyValueNeeded && pStyle->GetIncludeValue())
		return;

	_TC_(DWORD ti3 = GetTickCount());

	ROWCOL nhCols = GetHeaderCols(),
		   nhRows = GetHeaderRows();

	// Row and Column styles

	// Apply Row style
	if (nCol > nhCols)
		GetStyleRowCol(nRow, 0, *pStyle, gxApplyNew, -1);   // -1 defines range instead of cell value

	// Apply Column style
	// Change in logic for wrapped grid:
	// Call with the logical col. This is b'cos the logical col can only be computed
	// from both nRow and nCol of the absolute cell.
	if (nRow > nhRows)
	{
		ROWCOL nWGRow, nWGCol;
		GetLogCellFromAbsCell(nRow, nCol, nWGRow, nWGCol );
		GetStyleRowCol(0, nWGCol, *pStyle, gxApplyNew, -2);
	}

	// Apply table style
	if (nRow > nhRows && nCol > nhCols)
		GetStyleRowCol(0, 0, *pStyle, gxApplyNew, -1);

	_TC_(tick3 += GetTickCount()-ti3);

	// inherit attributes from base styles
	_TC_(DWORD ti4 = GetTickCount());
	pStyle->LoadBaseStyle(*m_pParam->m_pStylesMap);
	_TC_(tick4 += GetTickCount()-ti4);

	_TC_(DWORD ti5 = GetTickCount());
	// column headers and row headers
	if (nRow <= nhRows)
		pStyle->ChangeStyle(*m_pStyleColHeader, gxApplyNew);

	if (nCol <= nhCols)
		pStyle->ChangeStyle(*m_pStyleRowHeader, gxApplyNew);
	_TC_(tick5 += GetTickCount()-ti5);

	_TC_(DWORD ti6 = GetTickCount());
	// set value, if column or row header
	if ((nRow == 0 || nCol == 0) && !pStyle->GetIncludeValue())
	{
		if (nRow == 0 && nCol > 0 && GetParam()->IsNumberedColHeaders())
		{
			// Column header in format A, B, ..., AA, ..., AAA, ... ZZZZZ
			
			TCHAR s[10], t[10];
                        int n;
			for (n = 0; n < 9; n++)
			{
				nCol--;
				s[n] = (TCHAR) ((nCol%26) + _T('A'));
				if ((nCol = nCol/26) == 0)
					break;
			}
			
			// reverse string
                        int i;
			for (i = 0; i < n+1; i++)
				t[i] = s[n-i];
			t[i] = 0;
			
			pStyle->SetValue(t);
		}
		else if (nCol == 0 && nRow > 0 && GetParam()->IsNumberedRowHeaders())
		{
			// Row header is simple a number
			pStyle->SetValue(nRow);
		}
	}
	_TC_(tick6 += GetTickCount()-ti6);

	_TC_(DWORD ti7 = GetTickCount());
	if (bApplyStandard)
		pStyle->ChangeStyle(*m_pStyleStandard, gxApplyNew);

	if (GetParam()->m_bDirectCutPaste && GetParam()->m_bCut && GetParam()->m_CopyRangeList.IsCellInList(nRow, nCol))
	{
		pStyle->SetInterior(CGXBrush().SetPattern(17).SetColor(RGB(192,192,192)));
	}

	if(!(IsCurrentCell(nRow, nCol) && pStyle->GetIncludeControl() && GetRegisteredControl(pStyle->GetControl())->IsActive()))
	{
		if(pStyle->GetIncludeValue() 
			&& pStyle->GetIncludeNegativeStateColor() 
			&& _gxttof(pStyle->GetValue()) < 0  
			)
		{
			DWORD csColor ;
			csColor = pStyle->GetNegativeStateColor();
			pStyle->SetTextColor(csColor);
		}
	}

	_TC_(tick7 += GetTickCount()-ti7);
}

template<class T>
void CGXWrappedGrid<T>::UpdateHintFromPeer(CGXGridHint* pHint)
{
	switch (pHint->m_id)
	{
	case gxHintChangingRowBreaks:
		{
			// Adjust only the rowhidden array. I assume breaks will be automatically updated
			// since child-peers use a common patternMap.
#ifdef _WIN64 //RW64
			INT_PTR nNewBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#else
			int nNewBreaksCount = m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64
			int nPrevBreaksCount = pHint->lParam;
			
			if(nPrevBreaksCount != nNewBreaksCount)
				OnRowBreaksChanged(nPrevBreaksCount);
		}
		break;
	
	case gxHintPrepareChangeSelection:
		PrepareChangeWGSelection(
			(POSITION) pHint->vptr,
			pHint->nRow1,
			pHint->nCol1,
			pHint->nRow2,
			pHint->nCol2,
			FALSE);
		break;
	default:
		CGXWrappedGridCore<T>::UpdateHintFromPeer(pHint);
	}
}

template<class T>
BOOL CGXWrappedGrid<T>::CopyRangeList(CGXRangeList& List, BOOL bCanUseCurrentCell)
{
	BOOL bRet = CGXWrappedGridCore<T>::CopyRangeList(List, bCanUseCurrentCell);
	// If only current cell is selected then convert it to logical cell.
	if(bRet && bCanUseCurrentCell)
	{
		// If Only one range and only one cell in that range
		if(List.GetCount() == 1 && ((CGXRange*)List.GetHead())->GetWidth() * ((CGXRange*)List.GetHead())->GetHeight() == 1)
		{
			ROWCOL nAbsRow, nAbsCol, nLogRow, nLogCol;
			((CGXRange*)List.GetHead())->GetFirstCell(nAbsRow, nAbsCol);
			GetLogCellFromAbsCell(nAbsRow, nAbsCol, nLogRow, nLogCol);
			ASSERT(nLogRow != GX_INVALID && nLogCol != GX_INVALID);
				// Selection could only be made on valid logical cells.
				// If you changed the selection behavior, override this function and modify the code.
			List.DeleteAll();
			List.AddTail(new CGXRange(nLogRow, nLogCol));
		}
	}
	return bRet;
}

template<class T>
CString CGXWrappedGrid<T>::GetCopyTextRowCol(ROWCOL nLogRow, ROWCOL nLogCol)
{
	// Convert to Abs. co-ords.
	ROWCOL nAbsRow, nAbsCol;
	GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);

	// Get text from control (and give control the chance
	// to convert value into unformatted text or vice versa).
	CString sText;
	CGXStyle* pStyle = CreateStyle();

	ComposeStyleRowCol(nAbsRow, nAbsCol, pStyle);

	CGXControl* pControl = GetRegisteredControl(pStyle->GetControl());
	if (pControl)
		pControl->GetControlText(sText, nAbsRow, nAbsCol, NULL, *pStyle);
	else
		sText = pStyle->GetValueRef();

	RecycleStyle(pStyle);

	return sText;
}
/*
template<class T>
BOOL CGXWrappedGrid<T>::SetControlTextRowCol(ROWCOL nLogRow, ROWCOL nLogCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	// nLogRow and nLogCol are logical co-ords. Convert them into abs. values before pasting them into the grid.
	ROWCOL nAbsRow, nAbsCol;
	if(!GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol))
		return FALSE;
	 
	return CGXWrappedGridCore<T>::SetControlTextRowCol(nAbsRow, nAbsCol, str, nFlags, pOldStyle);
}

template<class T>
BOOL CGXWrappedGrid<T>::CopyRange(const CGXRangeList& list)
{
	// If only one cell in the range it's called by CGXControl::Copy with absoute values.
	// Convert the absolute to logical values.
	if(list.GetCount() == 1 && ((CGXRange*)list.GetHead())->GetWidth() * ((CGXRange*)list.GetHead())->GetHeight() == 1)
	{
		ROWCOL nAbsRow, nAbsCol, nLogRow, nLogCol;
		((CGXRange*)list.GetHead())->GetFirstCell(nAbsRow, nAbsCol);
		GetLogCellFromAbsCell(nAbsRow, nAbsCol, nLogRow, nLogCol);
		ASSERT(nLogRow != GX_INVALID && nLogCol != GX_INVALID);
			// Selection could only be made on valid logical cells.
			// If you changed the selection behavior, override this function and modify the code.
		CGXRangeList tempList;
		tempList.DeleteAll();
		tempList.AddTail(new CGXRange(nLogRow, nLogCol));
		return CGXWrappedGridCore<T>::CopyRange(tempList);
	}
	return CGXWrappedGridCore<T>::CopyRange(list);
}
*/

template<class T>
BOOL CGXWrappedGrid<T>::CopyRange(const CGXRange& range)
{
	if(range.GetWidth() * range.GetHeight() == 1)
	{
		ROWCOL nAbsRow, nAbsCol, nLogRow, nLogCol;
		range.GetFirstCell(nAbsRow, nAbsCol);
		GetLogCellFromAbsCell(nAbsRow, nAbsCol, nLogRow, nLogCol);
		ASSERT(nLogRow != GX_INVALID && nLogCol != GX_INVALID);
			// Selection could only be made on valid logical cells.
			// If you changed the selection behavior, override this function and modify the code.
		(const_cast<CGXRange*>(&range))->SetCells(nLogRow, nLogCol);
	}
	return CGXWrappedGridCore<T>::CopyRange(range);
}

#include "gxwgsel.h"
#include "gxwgseldrg.h"

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//
#endif //_GX_WRAPPED_GRID
