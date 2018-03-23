///////////////////////////////////////////////////////////////////////////////
// gxmrtGrid.h
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

#ifndef _GX_MRTGRID
#define _GX_MRTGRID

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

#define Colwidth  5


/////////////////////////////////////////////////////////////////////////////
// CGXMRTGrid<T> view

template <class T>
class CGXMRTGrid : public CGXWrappedGridCore<T>
{
public:
	CGXMRTGrid();           

public:
	//	MRTGrid APIs
	// Set the col count in a row... the row count will be automatically updated
	// if the current row count is smaller than nRow.
	BOOL SetMRTColCountInRow(ROWCOL nRow, ROWCOL nCols, UINT flags = GX_UPDATENOW);
	ROWCOL GetMRTColCountInRow(ROWCOL nLogRow);

	virtual ROWCOL GetLogRowCount();
	virtual ROWCOL GetLogColCount();

	virtual gxHierGridType GetGridType();	// Returns the grid type of this grid
	virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	void InitMRTGridSettings();

	virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);

	virtual void GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol);
	virtual BOOL GetAbsCellFromLogCell(ROWCOL nMRTRow, ROWCOL nMRTCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol);	// Convert the logical cell to the absolute cell in the grid. 
	virtual void GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nMRTRow, ROWCOL& nMRTCol); // Convert the absolute cell in the grid to the logical cell
	virtual BOOL GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId);

	virtual void OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol);
	virtual void OnShowChildAt(ROWCOL nLogRow, BOOL bShow);
	virtual BOOL IsChildShown(ROWCOL nLogRow);
// Override
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXMRTGrid<T>)
	public:
	virtual void OnGridInitialUpdate();
	//}}AFX_VIRTUAL
protected:
	virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);
	virtual void OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	virtual BOOL OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode);
	virtual void OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);

};

/////////////////////////////////////////////////////////////////////////////
// CGXMRTGrid<T>

template<class T>
CGXMRTGrid<T>::CGXMRTGrid()
{
	m_nTrackingRow = 0;
	m_nRowCount = 1;
}

template<class T>
gxHierGridType CGXMRTGrid<T>::GetGridType()
{
	return gxMRTGrid;
}

template<class T>
int CGXMRTGrid<T>::OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint & pt, CRect & rect)
{
	int nFrame = m_nHitTestFrame;
	int nRet = CGXGridCore::OnExtHitTest(ncRow, ncCol, pt, rect);
	CPoint  ptTest(
		max(0, pt.x),
		max(0, pt.y));

	int x = 0,
	y = 0;

	// Calculate ClientRow/pnCol
	ROWCOL nRow = CalcClientRowFromPt(ptTest, &y);
	ROWCOL nCol = CalcClientColFromPt(ptTest, &x);
//	CRect rect;
	BOOL bValid = nRow != GX_INVALID && nCol != GX_INVALID;
	if (bValid)
		rect.SetRect(x, y, x+GetColWidth(GetCol(nCol)), y+GetRowHeight(GetRow(nRow)));
	CGXRange range;
	ROWCOL nPattern;
	m_patternMap->GetSpanCellsRowCol(ncRow, ncCol, range, &nPattern);
	BOOL bTrackCol =  nPattern != GX_INVALID && ncRow <= m_patternMap->GetRowSpan() && ncCol ==  range.right;
	if (bTrackCol && bValid && abs(rect.right-ptTest.x) <= nFrame/2)	// Also chekc for nCol > GetHeaderCols() to disable resizing cells.
		return GX_VERTLINE;

	BOOL bTrackRow = ncCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth();
	if (bTrackRow && bValid && abs(rect.bottom-ptTest.y) <= nFrame/2)
	{
		return GX_HORZLINE;
	}

	return nRet;
}

template<class T>
void CGXMRTGrid<T>::OnGridInitialUpdate() 
{
	// Set the row count and intialize the pattern before calling the base class...
	CGXWrappedGridCore<T>::OnGridInitialUpdate();
	SetCellWidthPrecision(4);
	InitMRTGridSettings();
	//	GetParam()->SetNumberedColHeaders(FALSE);
//	GetParam()->EnableTrackColWidth(FALSE);
	GetParam()->EnableSelection(GX_SELNONE);
	HideRows(0, 0);
	HideCols(0, 0);
	GetParam()->GetProperties()->SetMarkRowHeader(FALSE);
	GetParam()->GetProperties()->SetMarkColHeader(FALSE);
	GetParam()->GetData()->StoreRowCount(1);
}

template<class T>
void CGXMRTGrid<T>::InitMRTGridSettings()
{
	SetRowHeaderWidth(32);
	// No row headers...
	m_patternMap->m_bIsHeaders = FALSE;
//	m_abRowHidden.InsertBits(1, 1);
//	m_abRowHidden.SetBitAt(1, 1);

/*  m_abRowHidden.InsertBits(1,m_patternMap->GetRowSpan()/2);
	int count = m_patternMap->GetRowSpan()/2;
	for(int i = 1; i<=count; i++)
	{
		m_abRowHidden.SetBitAt(i, 1);	// Hide all child grid rows by default
	}
	*/
	
}

template<class T>
ROWCOL CGXMRTGrid<T>::GetMRTColCountInRow(ROWCOL nLogRow)
{
	ASSERT(nLogRow <= GetLogRowCount());
	ROWCOL nLogCols;
	if(nLogRow - 1 == 0)
		return m_patternMap->GetRowBreaks()->GetAt(0) + 1;
	else
		// Row break in this row - Row break in the previous row.
		return m_patternMap->GetRowBreaks()->GetAt(nLogRow-1) - m_patternMap->GetRowBreaks()->GetAt(nLogRow - 2);
}

template<class T>
BOOL CGXMRTGrid<T>::SetMRTColCountInRow(ROWCOL nRow, ROWCOL nCols, UINT /*flags*/ /*= GX_UPDATENOW*/)
{
	// Adjust the breaks array in m_pattern to reflect the new layout.
	CDWordArray breaksArray ;
	breaksArray.Copy(*m_patternMap->GetRowBreaks());
#ifdef _WIN64 //RW64
	INT_PTR nBreaks = breaksArray.GetSize();
#else
	ROWCOL nBreaks = breaksArray.GetSize();
#endif //_WIN64
	long nLastBreak = (nBreaks /*&& m_patternMap->GetColCount()*/) ? breaksArray.GetAt(nBreaks-1) : -1;
	// If exisiting row count less than nRow, then add more rows with appropriate col counts...
	if(nBreaks < nRow)
	{
		while(nBreaks < nRow)
		{
			breaksArray.Add(nLastBreak);
			nBreaks++;
		}
		breaksArray.SetAt(nBreaks-1, (DWORD)(nLastBreak+nCols)	);
		m_patternMap->InsertCols(m_patternMap->GetColCount()+1, nCols);
		// Modify col width array to reflect the newly added cells

#ifdef _WIN64 //RW64
		INT_PTR nArraySize = m_patternMap->m_colWidths.GetSize();
#else
		UINT nArraySize = m_patternMap->m_colWidths.GetSize();
#endif //_WIN64
		m_patternMap->m_colWidths.InsertAt(nArraySize, 15, nCols);
		m_patternMap->SetRowBreaks(&breaksArray);
		m_patternMap->CalcColCount();
		// Adjust the hidden row array:
		nArraySize = m_abRowHidden.GetSize();
#ifdef _WIN64 //RW64
		m_abRowHidden.InsertBits(static_cast<DWORD>(nArraySize+1), nCols);
#else
		m_abRowHidden.InsertBits(nArraySize+1, nCols);
#endif //_WIN64
		// Initialize the header once. (this will never be reset)
		if(nArraySize == 0)
			m_abRowHidden.SetBitAt(0, 1);
		for(int i=1; i<=(int)nCols; i++)
		{
#ifdef _WIN64 //RW64
			// Loss of data.
			m_abRowHidden.SetBitAt(static_cast<DWORD>(i+nArraySize), 1);
#else
			m_abRowHidden.SetBitAt(i+nArraySize, 1);
#endif //_WIN64
		}

		ROWCOL nTotalCols = m_patternMap->GetRowBreaks()->GetAt(m_patternMap->GetRowBreaks()->GetSize() - 1);
		// Modify col count in CGXData appropriately.
		GetParam()->GetData()->StoreColCount(nTotalCols);
	}
	// Need to modify an exisiting row's col count setting...
	else if(nBreaks >= nRow)
	{
		// Get the current no. of cols in the row.
		ROWCOL nCurCols = (nRow - 1) ? breaksArray.GetAt(nRow - 1) - breaksArray.GetAt(nRow - 2) : breaksArray.GetAt(nRow - 1);
		// Check for dummy initiaiziation.
//		if(nCurCols == 1 && !m_patternMap->GetColCount()) nCurCols = 0;
		if(nCurCols != nCols)
		{
			int nDiff = nCols - nCurCols;
			ROWCOL nRowCopy = nRow;
			// For adjusting col width array later...
			UINT nAPos = breaksArray.GetAt(nRow - 1);
			// Adjust the break index in nRow and in the subsequent rows
			while(nRowCopy <= nBreaks)
			{
				ROWCOL nCurBreak = breaksArray.GetAt(nRowCopy-1);
				breaksArray.SetAt(nRowCopy-1, nCurBreak + nDiff);
				nRowCopy++;
			}
			m_patternMap->SetColCount(m_patternMap->GetColCount() + nDiff);
			// Modify col width array here...
			if(nDiff > 0)
			{
				m_patternMap->m_colWidths.InsertAt(nAPos+1, 15, nDiff);	// 0 based col index
				GetParam()->GetData()->StoreInsertCols(nAPos+2, nDiff);	// CGXData takes 1 based col index
			}
			else // -ve
			{
				m_patternMap->m_colWidths.RemoveAt(nAPos - (abs(nDiff)) + 1, abs(nDiff));	// 0 based col index
				ROWCOL nFromCol = nAPos - (abs(nDiff)) + 2;
				ROWCOL nToCol = nFromCol + abs(nDiff)-1;
				GetParam()->GetData()->StoreRemoveCols(nFromCol, nToCol);	// CGXData takes 1 based col index
			}
			m_patternMap->SetRowBreaks(&breaksArray);
			m_patternMap->CalcColCount();
		}
	}
	return TRUE;
}

template<class T>
ROWCOL CGXMRTGrid<T>::GetLogRowCount()
{
#ifdef _WIN64 //RW64
	return static_cast<ROWCOL>(m_patternMap->GetRowBreaks()->GetSize());
#else
	return m_patternMap->GetRowBreaks()->GetSize();
#endif //_WIN64
}

template<class T>
ROWCOL CGXMRTGrid<T>::GetLogColCount()
{
#ifdef _WIN64 //RW64
	return static_cast<ROWCOL>(GX_INVALID);	// Use GetMRTColCountInRow instead.
#else
	return GX_INVALID;	// Use GetMRTColCountInRow instead.
#endif //_WIN64
}


/*
template<class T>
ROWCOL CGXMRTGrid<T>::GetColCount()
{
	return m_patternMap->GetEffectiveColCount();
}

template<class T>
int CGXMRTGrid<T>::GetColWidth(ROWCOL nCol)
{
	if (IsColHidden(nCol))
		return 0;

	if(nCol != 0)
		return Colwidth;
	return CGXGridCore::GetColWidth(nCol);
}

template<class T>
ROWCOL CGXMRTGrid<T>::GetRowCount()
{
	return m_patternMap->GetRowSpan();
}
*/
template<class T>
CGXRange* CGXMRTGrid<T>::GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range)
{
	if(nRow == 0 || nCol == 0)
		return &range.SetCells(nRow, nCol);
	// If row header cell
	if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth())
	{
		range.SetCells((nRow % 2) ? nRow : nRow-1, 1, (nRow % 2) ? nRow+1 : nRow, m_patternMap->GetRowHeaderWidth());
		return &range;
	}
	CGXRange* pRange = CGXWrappedGridCore<T>::GetCoveredCellsRowCol(nRow, nCol, range);
	if(pRange && IsPMCell(nRow, nCol))
	{
		ROWCOL nBottomRow = range.bottom;
		// The border for a covered cell is drawn only if the cell adjacent to that border is visible.
		// So, adjust the covered cell such all borders will be visible.
		if(m_abRowHidden.GetBitAt(nBottomRow / 2))
			nBottomRow--;
		pRange->SetCells(range.top, range.left, nBottomRow, range.right);
	}
	return pRange;
}
/*
template<class T>
void CGXMRTGrid<T>::MergeCoveredCells(CGXRange& area)
{
	CGXRange rgCovered;

	ROWCOL nCount = GetRowCount();

	for (ROWCOL nRow = area.top; nRow <= area.bottom && nRow <= nCount; nRow++)
	{
		for (ROWCOL nCol = area.left; nCol <= area.right; nCol++)
		{
			if (GetCoveredCellsRowCol(nRow, nCol, rgCovered))
			{
				nCol = rgCovered.right+1;
				area.UnionRange(rgCovered, area);
			}
		}
	}
}


template<class T>
int CGXMRTGrid<T>::OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint & pt, CRect & rect)
{
	int nFrame = m_nHitTestFrame;
	int nRet = CGXGridCore::OnExtHitTest(ncRow, ncCol, pt, rect);
	CPoint  ptTest(
		max(0, pt.x),
		max(0, pt.y));

	int x = 0,
		y = 0;

	// Calculate ClientRow/pnCol
	ROWCOL nRow = CalcClientRowFromPt(ptTest, &y);
	ROWCOL nCol = CalcClientColFromPt(ptTest, &x);
//	CRect rect;
	BOOL bValid = nRow != GX_INVALID && nCol != GX_INVALID;
	if (bValid)
		rect.SetRect(x, y, x+GetColWidth(GetCol(nCol)), y+GetRowHeight(GetRow(nRow)));
	CGXRange range;
	ROWCOL nPattern;
	m_patternMap->GetSpanCellsRowCol(ncRow, ncCol, range, &nPattern);
	BOOL bTrackCol = ncRow <= m_patternMap->GetRowSpan() && ncCol ==  range.right && nPattern != -1; 
	if (bTrackCol && bValid && abs(rect.right-ptTest.x) <= nFrame/2)
	{
		if (nCol > GetHeaderCols())
			nRet = GX_VERTLINE;
	}
	return nRet;
}
*/
template<class T>
void CGXMRTGrid<T>::OnEndTracking(ROWCOL /*nRow*/, ROWCOL nCol, int nTrackingMode, CSize & size)
{
	if (m_bTrackMove)
		OnMoveTracking(m_nRowTracking, m_nColTracking, m_nTrackingMode, size);

	// Redraw the marked grid line
	if (m_pWndDrag)
	{
		m_pWndDrag->DestroyWindow();
		delete m_pWndDrag;
		m_pWndDrag = NULL;
	}

	CPoint   point = m_rectBoundTrack.TopLeft()+size;
	CRect rectGrid = GetGridRect();

	CClientDC dc(m_pGridWnd);
	OnGridPrepareDC(&dc);

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	m_bTracking = FALSE;

	// Undo previous inversion
	if (m_bTrackInvertLine && m_rectInvertBar != m_rectTrack)
		dc.InvertRect(m_rectInvertBar);

	//GXDrawingTechnique dt = gxDrawUsingMemDC;

	//UINT nUpdateFlags = GX_UPDATENOW;

	if (m_nTrackingMode & GX_TRACKWIDTH)
	{
		// Change the column widths and update the display
		//int dx = m_rectInvertBar.left - m_rectTrack.left;

		UpdateWindow();

		ScrollCellInView(GetTopRow(), m_nColTracking);

		UpdateScrollbars(FALSE);
	}

	ROWCOL nEditRow, nEditCol;
	if (m_pGridWnd->GetFocus() == m_pGridWnd && GetCurrentCell(nEditRow, nEditCol))
	{
		CGXControl* pControl = GetControl(nEditRow, nEditCol);
		if (pControl->IsActive())
			pControl->Refresh();
	}

	UpdateScrollbars();

	if(nTrackingMode == GX_TRACKWIDTH )
	{
		CGXRange range;
		ROWCOL nPatternCol;
		m_patternMap->GetSpanCellsRowCol(m_nTrackingRow, nCol, range, &nPatternCol);
		int nChange = (size.cx - Colwidth) / Colwidth;
		int nNewColWidthUnits = nChange + m_patternMap->GetColWidth(nPatternCol);
		m_patternMap->SetColWidth(nPatternCol, nNewColWidthUnits);
	}
	Redraw();
}


template<class T>
BOOL CGXMRTGrid<T>::OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode)
{
	m_nTrackingRow = nRow;
	return CGXGridCore::OnStartTracking(nRow, nCol, nTrackingMode);
}

// Tracking
template<class T>
void CGXMRTGrid<T>::OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize &size)
{
	if(size.cx == -5)
		nRow = nRow;

	GX_UNUSED_ALWAYS(nTrackingMode);

	m_bTrackMove = TRUE;    // indicates that user has moved the cursor

	BOOL b = FALSE;

	// trigger events
	if (m_nTrackingMode == GX_TRACKWIDTH)
	{
		b = OnTrackColWidthMove(nCol, size.cx);
	}
	else if (m_nTrackingMode == GX_TRACKHEIGHT)
	{
		b = OnTrackRowHeightMove(nRow, size.cy);
	}

	if (!b)
		return;

	BOOL bLock = m_bLockedScrollbars;
	m_bLockedScrollbars = TRUE;

	CRect    rectGrid = GetGridRect();
	CPoint   point = m_rectBoundTrack.TopLeft()+size;

	CClientDC dc(m_pGridWnd);
	OnGridPrepareDC(&dc);

	ASSERT(GetCapture() == m_pGridWnd);

	CRect oldRect = m_rectInvertBar;

	if (m_nTrackingMode & GX_TRACKWIDTH)
	{
		// Compute new grid line
		m_rectInvertBar.SetRect(
			min(rectGrid.right-7, point.x),
			m_rectTrack.top,
			min(rectGrid.right-6, point.x+1),
			m_rectTrack.bottom);

		if (oldRect != m_rectInvertBar)
		{
			// Undo previous inversion
			if (m_bTrackInvertLine && oldRect != m_rectTrack)
				dc.InvertRect(oldRect);

			// Show new size
			if (m_bTrackInvertLine && m_rectInvertBar != m_rectTrack)
				dc.InvertRect(m_rectInvertBar);

			// Draw the cells (using MemDC)
			if (m_bTrackSmoothCells)
			{
				int dx = m_rectInvertBar.left - m_rectTrack.left;

				// Store drawing technique and column width
				GXDrawingTechnique dt = SetDrawingTechnique(gxDrawUsingMemDC);
				int nNewWidth = (dx + m_sizeTrackStart.cx);
				int nOldWidth = GetColWidth(nCol);
				StoreColWidth(nCol, nNewWidth);

				// Draw the cells
				UpdateChangedColWidths(nCol, nCol, &nOldWidth, GX_UPDATENOW, FALSE);

				// Reset drawing technique and column width
				SetDrawingTechnique(dt);
			}
			// Draw the headers (using MemDC)
			else if (m_bTrackSmoothHeader)
			{
				int dx = m_rectInvertBar.left - m_rectTrack.left;

				// Store drawing technique and column width
				GXDrawingTechnique dt = SetDrawingTechnique(gxDrawUsingMemDC);
				int nNewWidth = (dx + GetColWidth(nCol));
				long nWidth = 0;
				m_pParam->m_ColWidths.Lookup(nCol, nWidth);
				int nOldWidth = GetColWidth(nCol);
				StoreColWidth(nCol, nNewWidth);

				// Draw the headers
				CRect rect = CalcRectFromRowColExEx(0, nCol, GetHeaderRows(), nCol);
				rect.right = rectGrid.right;
				InvalidateRect(rect);
				UpdateWindow();

				// Reset drawing technique and column width
				StoreColWidth(nCol, nOldWidth);
				if (!nWidth)
					m_pParam->m_ColWidths.RemoveKey(nCol);
				SetDrawingTechnique(dt);
			}
		}
	}
	else if (m_nTrackingMode & GX_TRACKHEIGHT)
	{
		// Compute new grid line
		m_rectInvertBar.SetRect(
			m_rectTrack.left,
			min(rectGrid.bottom-7, max(point.y, m_rectBoundTrack.top)),
			m_rectTrack.right,
			min(rectGrid.bottom-6, max(point.y+1, m_rectBoundTrack.bottom)));

		if (oldRect != m_rectInvertBar)
		{
			// Undo previous inversion
			if (m_bTrackInvertLine && oldRect != m_rectTrack)
				dc.InvertRect(oldRect);

			// Show new size
			if (m_bTrackInvertLine && m_rectInvertBar != m_rectTrack)
				dc.InvertRect(m_rectInvertBar);

			// Draw the cells (using MemDC)
			if (m_bTrackSmoothCells)
			{
				int dy = m_rectInvertBar.top - m_rectTrack.top;

				// Store drawing technique and column width
				GXDrawingTechnique dt = SetDrawingTechnique(gxDrawUsingMemDC);
				int nNewHeight = (dy + m_sizeTrackStart.cy);
				int nOldHeight = GetRowHeight(nRow);
				StoreRowHeight(nRow, nNewHeight);

				// Draw the cells
				UpdateChangedRowHeights(nRow, nRow, &nOldHeight, GX_UPDATENOW, FALSE);

				// Reset drawing technique and row height
				SetDrawingTechnique(dt);
			}
			// Draw the headers (using MemDC)
			else if (m_bTrackSmoothHeader)
			{
				int dy = m_rectInvertBar.top - m_rectTrack.top;

				// Store drawing technique and column width
				GXDrawingTechnique dt = SetDrawingTechnique(gxDrawUsingMemDC);
				int nNewHeight = (dy + m_sizeTrackStart.cy);
				StoreRowHeight(nRow, nNewHeight);

				// Draw the headers
				CRect rect = CalcRectFromRowColExEx(nRow, 0, nRow, GetHeaderCols());
				rect.bottom = rectGrid.bottom;
				InvalidateRect(rect);
				UpdateWindow();

				// Reset drawing technique and row height
				SetDrawingTechnique(dt);
			}
		}
	}

	m_bLockedScrollbars = bLock;
}


template<class T>
BOOL CGXMRTGrid<T>::GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId)
{
	if(nRow && (nRow % 2) == 0)
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
void CGXMRTGrid<T>::GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol)
{
	ASSERT(nChildId <= GetLogRowCount());
	nChildRow = nChildId * 2;
	nChildCol = m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth
					+ m_patternMap->m_indentWidths.GetAt(nChildId-1) + 1;
}

template<class T>
BOOL CGXMRTGrid<T>::GetAbsCellFromLogCell(ROWCOL nMRTRow, ROWCOL nMRTCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol)
{
	const CDWordArray* pArrayBreaks = m_patternMap->GetRowBreaks();
	ROWCOL nPatCol;
	if(nMRTRow == 1)	// First row
	{
		ASSERT(nMRTCol <= (pArrayBreaks->GetAt(0)+1));
			// nMRTCol not available in nMRTRow.
		nPatCol = nMRTCol;
	}
	else
	{
		ASSERT(nMRTCol <= (pArrayBreaks->GetAt(nMRTRow - 1) - pArrayBreaks->GetAt(nMRTRow - 2) + 1));
				// nMRTCol not available in nMRTRow.
		nPatCol = pArrayBreaks->GetAt(nMRTRow - 2) + nMRTCol + 1;
	}

	return m_patternMap->GetAbsRangeFromPatternCell(1, nPatCol, nOrigRow, nOrigCol);
}

template<class T>
void CGXMRTGrid<T>::GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nMRTRow, ROWCOL& nMRTCol)
{
	CGXRange range;
	ROWCOL nPatternCol;
	m_patternMap->GetSpanCellsRowCol(nOrigRow, nOrigCol, range, &nPatternCol);
	nMRTCol = GX_INVALID;
	if(nPatternCol != GX_INVALID)
	{
		const CDWordArray* aBreaks = m_patternMap->GetRowBreaks();
		ROWCOL nParseCol=0;
		int i;
		for(i=0; i<aBreaks->GetSize(); i++)
		{
			nParseCol += aBreaks->GetAt(i);
			if(nParseCol >= nPatternCol)
				break;
		}
		if(nParseCol >= nPatternCol)	// Found the right row..
		{
			if(i==0)
				nMRTCol = nPatternCol;
			else
				nMRTCol = nPatternCol - aBreaks->GetAt(i-1);
		}
	}
	nMRTRow = (nOrigRow+1) / 2;
}

template<class T>
void CGXMRTGrid<T>::OnClickedPMCell(ROWCOL nAbsRow, ROWCOL /*nAbsCol*/)
{
	// Update could be more efficient.
	// 1 means collapsed, 0 means expanded
	BOOL bHidden = m_abRowHidden.GetBitAt((nAbsRow+1)/2);
	bHidden = !bHidden;
	if(bHidden)
		ShowChildAt((nAbsRow+1)/2, FALSE);
	else
		ShowChildAt((nAbsRow+1)/2, TRUE);

	Redraw();
}

template<class T>
void CGXMRTGrid<T>::OnShowChildAt(ROWCOL nLogRow, BOOL bShow)
{
	ROWCOL nPatRow = nLogRow+m_patternMap->m_bIsHeaders;
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
BOOL CGXMRTGrid<T>::IsChildShown(ROWCOL nLogRow)
{
	ROWCOL nPatRow = nLogRow+m_patternMap->m_bIsHeaders;
	if(m_abRowHidden.GetBitAt(nPatRow) != 1)	// 1-collapsed, 0-expanded
		return TRUE;	// Expanded
	else
		return FALSE;	// Collpased

}

// No column base styles.
template<class T>
void CGXMRTGrid<T>::ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard)
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

	// No Column base style...

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

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif
