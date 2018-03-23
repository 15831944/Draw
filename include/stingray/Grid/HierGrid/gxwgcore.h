///////////////////////////////////////////////////////////////////////////////
// gxwgcore.h
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

#ifndef _GX_WRAPPED_GRID_CORE
#define _GX_WRAPPED_GRID_CORE

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


template <class T>
class CGXWrappedGridCore : public CGXHierarchyGrid<T>
{

public:
//	CGXWrappedGridCore();
	CGXWrappedGridCore(gxHierGridType commonChildGridType = gxNone, BOOL bCommonChildGridHeader = FALSE);           // protected constructor used by dynamic creation
	virtual ~CGXWrappedGridCore();
	virtual BOOL IsIndentCell(ROWCOL nRow, ROWCOL nCol);
	void SetRowHeaderWidth(int nWidth);		// in pixels

	// Implementation specific APIs...
	// Since we use covered cells as the backbone to the hierarchy grid (wrapped and MRT grid),
	// each visible cell is actually a covering of N no. of basic grid cells.
	// Hence the width of a visible cell can only be a whole-multiple of the
	// basic grid cell's width, which is set to 4 pixels by default.
	// You can decrease the width of this basic cell using the API below for better precision.
	void SetCellWidthPrecision(UINT nCellWidthPrecision);	// in pixels.


	// IGXHierarchyGrid virtuals.
	virtual void OnRegisterChildGrid(IGXHierarchyGrid* pChildHierGrid);
	virtual BOOL GetPMValueAt(ROWCOL nRow);
	virtual BOOL IsPMCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL IsChildGridIndentCell(ROWCOL nRow, ROWCOL nCol);
	virtual void SetIndentWidthForChildGrids(WORD nIndentWidth);	// in pixels.
	virtual void SetPatternMap(CGXCoveredCellPatternMap* map, BOOL bMustDelete = TRUE);
	virtual void OnChangedChildColWidth(ROWCOL nChildId);
	virtual void HidePMExpanderColumn(BOOL bHide = TRUE, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);	// Hide/Show the Plus-Minus-button-expander column

	// Data members
	CGXCoveredCellPatternMap* m_patternMap;	// Does the mapping between the logical and absolute cells.
	BOOL m_bMustDelete;						// Delete the patternmap when the grid is destroyed.
	ROWCOL m_nRowCount;

protected:

	// Support for drag-resizing...
	ROWCOL m_nTrackingRow;
	virtual int HitTest(CPoint& pt, ROWCOL* pnRow = NULL, ROWCOL* pnCol = NULL, CRect* rectHit = NULL);
	virtual void OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	virtual BOOL OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode);
	virtual void OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);

	// Overridden grid virtuals for hierarchy functionality
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual void MergeCoveredCells(CGXRange& range);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);

	BOOL IsValidAdjacentLogCell(ROWCOL nRow, ROWCOL nCol, int nDir);

public:
	virtual void OnGridInitialUpdate();
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	virtual BOOL FindNextCell(int direction, ROWCOL& nSetRow, ROWCOL& nSetCol);

	virtual ROWCOL GetRowCount( );
	virtual ROWCOL GetColCount( );
	virtual int GetColWidth(ROWCOL nCol);
	virtual int GetRowHeight(ROWCOL nRow);
	virtual BOOL IsRowHidden(ROWCOL nRow);
	virtual BOOL IsColHidden(ROWCOL nCol);
};


template<class T>
CGXWrappedGridCore<T>::CGXWrappedGridCore(gxHierGridType commonChildGridType /* =0 */, BOOL bCommonChildGridHeader /* = FALSE */)
:CGXHierarchyGrid<T>(commonChildGridType, bCommonChildGridHeader)
{
	m_nRowCount = 0;
	m_nTrackingRow = 0;
	m_bMustDelete = TRUE;
	m_patternMap = NULL;
}

template<class T>
CGXWrappedGridCore<T>::~CGXWrappedGridCore()
{
	if(m_bMustDelete && m_patternMap)
	{
		delete m_patternMap;
		m_patternMap = NULL;
	}
}

template<class T>
void CGXWrappedGridCore<T>::OnGridInitialUpdate()
{
	if(m_patternMap == NULL)
		m_patternMap = new CGXCoveredCellPatternMap();

	CGXHierarchyGrid<T>::OnGridInitialUpdate();
}

template<class T>
void CGXWrappedGridCore<T>::SetPatternMap(CGXCoveredCellPatternMap* pMap, BOOL bMustDelete /*= TRUE*/)
{
	if(m_patternMap && m_bMustDelete)
		delete m_patternMap;

	m_patternMap = pMap;
	m_bMustDelete = bMustDelete;
}

template<class T>
void CGXWrappedGridCore<T>::OnRegisterChildGrid(IGXHierarchyGrid* pChildHierGrid)
{
	// Child should have the same cell width precsion as the parent...
	if(pChildHierGrid->GetGridType() != gxRegularGrid)
	{
		CGXWrappedGridCore<CGXGridWnd>* pChild = dynamic_cast<CGXWrappedGridCore<CGXGridWnd>*>(pChildHierGrid);
		pChild->SetCellWidthPrecision(Width_LPtoDP(m_patternMap->m_nCellWidthPrecision));
	}
}

template<class T>
void CGXWrappedGridCore<T>::SetCellWidthPrecision(UINT nCellWidthPrecision)
{
	m_patternMap->m_nCellWidthPrecision = dynamic_cast<CGXGridCore*>(this)->Width_DPtoLP(nCellWidthPrecision);
}

template<class T>
BOOL CGXWrappedGridCore<T>::GetPMValueAt(ROWCOL nRow)
{
	// Expanded: 1
	// Collapsed: 2
	if(m_abRowHidden.GetBitAt((nRow+1)/2)) // 1-collapsed, 0-expanded
		return 2;
	else
		return 1;
}

template<class T>
BOOL CGXWrappedGridCore<T>::IsPMCell(ROWCOL /*nRow*/, ROWCOL nCol)
{
	if((int)nCol > m_patternMap->GetRowHeaderWidth() && (int)nCol <= m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth)
		return TRUE;
	else return FALSE;
}

template<class T>
BOOL CGXWrappedGridCore<T>::IsChildGridIndentCell(ROWCOL nRow, ROWCOL nCol)
{
	if(nRow && (nRow % 2) == 0)
	{
		if((int)nCol > (m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth)
			&& (int)nCol < (m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + m_patternMap->m_wChildIndentWidth))
			return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXWrappedGridCore<T>::IsIndentCell(ROWCOL nRow, ROWCOL nCol)
{
	DWORD nIndentWidth;
	ROWCOL nWrappedRow = (nRow-1) % m_patternMap->GetRowSpan();
	if(nWrappedRow % 2)return FALSE;		// Child grid row...
	nIndentWidth = m_patternMap->m_indentWidths.GetSize() ? m_patternMap->m_indentWidths.GetAt(nWrappedRow/2) : 0;
	if( nIndentWidth
		&& ((int)nCol > m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth)
		&& ((int)nCol <= m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + nIndentWidth)
		)
		return TRUE;
	else return FALSE;
}

template<class T>
void CGXWrappedGridCore<T>::SetIndentWidthForChildGrids(WORD nIndentWidth)
{
	CGXGridCore* pThisAsGridCore = dynamic_cast<CGXGridCore*>(this);
	ASSERT(pThisAsGridCore);

    // [VC7] Supress cast warning from one type to other
	m_patternMap->m_wChildIndentWidth = (WORD)(pThisAsGridCore->Width_DPtoLP(nIndentWidth)/m_patternMap->m_nCellWidthPrecision);
}

template<class T>
void CGXWrappedGridCore<T>::SetRowHeaderWidth(int nWidth)
{
	int nWidthInTermsOfCols = Width_DPtoLP(nWidth)/m_patternMap->m_nCellWidthPrecision;
	m_patternMap->SetRowHeaderWidth(nWidthInTermsOfCols);

	SetFrozenCols(nWidthInTermsOfCols, nWidthInTermsOfCols);
}

template<class T>
int CGXWrappedGridCore<T>::HitTest(CPoint &pt, ROWCOL* pnRow, ROWCOL* pnCol, CRect* pRectHit)
{
	WORD wColTrackFlags = GetParam()->m_wAllowTrackColWidth;
	GetParam()->EnableTrackColWidth(FALSE);

	WORD wRowTrackFlags = GetParam()->m_wAllowTrackRowHeight;
	GetParam()->EnableTrackRowHeight(FALSE);

	int nRet = CGXHierarchyGrid<T>::HitTest(pt, pnRow, pnCol, pRectHit);

	GetParam()->EnableTrackColWidth(wColTrackFlags);
	GetParam()->EnableTrackRowHeight(wRowTrackFlags);

	return nRet;
}

template<class T>
void CGXWrappedGridCore<T>::OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize & size)
{
	// Just call the base class for MRT grid types.
	if(GetGridType() == gxMRTGrid)
	{
		CGXHierarchyGrid<T>::OnEndTracking(nRow, nCol, nTrackingMode, size);
		return;
	}

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

	GXDrawingTechnique dt = gxDrawUsingMemDC;

	UINT nUpdateFlags = GX_UPDATENOW;

	if (m_nTrackingMode & GX_TRACKWIDTH)
	{
		// Change the column widths and update the display
		int dx = m_rectInvertBar.left - m_rectTrack.left;

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
		int nColWidth = Width_LPtoDP(m_patternMap->m_nCellWidthPrecision);
		m_patternMap->GetSpanCellsRowCol(m_nTrackingRow, nCol, range, &nPatternCol);
		int nChange = (size.cx - nColWidth) / nColWidth;
		int nNewColWidthUnits = nChange + m_patternMap->GetColWidth(nPatternCol);
		if(nNewColWidthUnits > 0)
		{
			m_patternMap->SetColWidth(nPatternCol, nNewColWidthUnits);
			// Create Hint
			if (m_pUpdateHintImp && m_bHintsEnabled)
				m_pUpdateHintImp->HintUpdateChangedColWidths(this, nPatternCol, nPatternCol, NULL, GX_UPDATENOW);
			Redraw();
		}
	}
	else if(nTrackingMode == GX_TRACKHEIGHT)
	{
		ROWCOL nLogRow, nAbsTopRow;
		nLogRow = (m_nTrackingRow-1) / m_patternMap->GetRowSpan();
//		m_patternMap->m_bIsHeaders ? nLogRow : nLogRow++;
		nAbsTopRow = nLogRow * m_patternMap->GetRowSpan() + 1;
		int nChange = size.cy - GetRowHeight(m_nTrackingRow);
		// If resultant size > 0
		if((CalcSumOfRowHeights(nAbsTopRow, (nLogRow+1)*m_patternMap->GetRowSpan()) + nChange) > 0)
		{
			int nNewHeight = GetRowHeight(nAbsTopRow) + nChange/(int)(m_patternMap->GetRowSpan()/2);
			for(int i=0;i<(int)m_patternMap->GetRowSpan()/2; i++)
				SetRowHeight(nAbsTopRow+(i*2), nAbsTopRow+(i*2), nNewHeight);
		}
	}
}

template<class T>
BOOL CGXWrappedGridCore<T>::OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode)
{
	// Just call the base class for MRT grid types.
	if(GetGridType() == gxMRTGrid)
		return CGXHierarchyGrid<T>::OnStartTracking(nRow, nCol, nTrackingMode);

	m_nTrackingRow = nRow;
	return CGXGridCore::OnStartTracking(nRow, nCol, nTrackingMode);
}

// Tracking
template<class T>
void CGXWrappedGridCore<T>::OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize &size)
{
	// Just call the base class for MRT grid types.
	if(GetGridType() == gxMRTGrid)
	{
		CGXHierarchyGrid<T>::OnMoveTracking(nRow, nCol, nTrackingMode, size);
		return;
	}

	int nTest = GetRowHeight(m_nTrackingRow);

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
			min(rectGrid.bottom-7, point.y),
			m_rectTrack.right,
			min(rectGrid.bottom-6, point.y+1));

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
CGXRange* CGXWrappedGridCore<T>::GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range)
{
	if(nRow == 0 || nCol == 0)
		return &range.SetCells(nRow, nCol);
	ROWCOL nPattern;
	m_patternMap->GetSpanCellsRowCol(nRow, nCol, range, &nPattern);
	// Adjust right border for blank cells (to take care of col count due to bigger child grids.
	if(nPattern == GX_INVALID && range.right > m_patternMap->GetEffectiveColCount())
		range.right = GetColCount();
	// Check if child grid cell.
	if(nRow && (nRow % 2) == 0 && nCol > ((ROWCOL)m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + m_patternMap->m_wChildIndentWidth))
		range.right = GetColCount();
	return &range;
}

template<class T>
void CGXWrappedGridCore<T>::MergeCoveredCells(CGXRange& area)
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
ROWCOL CGXWrappedGridCore<T>::GetRowCount()
{
	ROWCOL nTotalRowCount = m_nRowCount;
	nTotalRowCount += m_patternMap->m_bIsHeaders ? 1 : 0;
	return nTotalRowCount*m_patternMap->GetRowSpan();
}

template<class T>
int CGXWrappedGridCore<T>::GetColWidth(ROWCOL nCol)
{
	if (IsColHidden(nCol))
		return 0;

	if(nCol != 0)
		return Width_LPtoDP(m_patternMap->m_nCellWidthPrecision);
	return CGXGridCore::GetColWidth(nCol);
}

template<class T>
int CGXWrappedGridCore<T>::GetRowHeight(ROWCOL nRow)
{
	if(!IsRowHidden(nRow) && nRow && (nRow % 2) == 0)
	{
		ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
//		if(!nPatternRow) return -1;
		int nHeight = GetOptimalChildHeightAt(nPatternRow);
		if(nHeight >= 0)
			return nHeight;
	}
	return CGXHierarchyGrid<T>::GetRowHeight(nRow);
}

template<class T>
ROWCOL CGXWrappedGridCore<T>::GetColCount()
{
	ROWCOL nColCount = m_patternMap->GetEffectiveColCount();
	return max((long)nColCount, m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + m_patternMap->m_wChildIndentWidth + (GetMaxChildWidth()/Width_LPtoDP(m_patternMap->m_nCellWidthPrecision)));
}

template<class T>
void CGXWrappedGridCore<T>::OnChangedChildColWidth(ROWCOL nChildId)
{
	int nMaxWidth = m_nMaxChildWidth;
	CGXHierarchyGrid<T>::OnChangedChildColWidth(nChildId);
	if(nMaxWidth != m_nMaxChildWidth)
		Redraw();
}

template<class T>
void CGXWrappedGridCore<T>::HidePMExpanderColumn(BOOL bHide /*= TRUE*/, UINT flags /*= GX_UPDATENOW*/, GXCmdType ctCmd /*= gxDo*/)
{
	ROWCOL nLeft, nRight;
	nLeft = m_patternMap->GetRowHeaderWidth() + 1;
	nRight = nLeft + m_patternMap->m_nPMButtonCellWidth - 1;
	CGXHierarchyGrid<T>::HideCols(nLeft, nRight, bHide, NULL, flags, ctCmd);
}

template<class T>
BOOL CGXWrappedGridCore<T>::IsRowHidden(ROWCOL nRow)
{
	if(nRow && (nRow % 2) == 0)
		return m_abRowHidden.GetBitAt(nRow / 2);
	return CGXHierarchyGrid<T>::IsRowHidden(nRow);
}

template<class T>
BOOL CGXWrappedGridCore<T>::IsColHidden(ROWCOL nCol)
{
	if(IsPrinting())
	{
		if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth)
			return TRUE;
	}
	return CGXHierarchyGrid<T>::IsColHidden(nCol);
}

template<class T>
BOOL CGXWrappedGridCore<T>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	if(nType >= 0 && nRow != 0 && nCol != 0)
	{
		CGXRange range;
		ROWCOL nLogCol, nLogRow, nPatternRow, nPatternCol;
		// nPatternXXX == nLogXXX for WrappedGrid but different for MRTGrid.
		nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
		m_patternMap->GetSpanCellsRowCol(nRow, nCol, range, &nPatternCol);

		GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
		if(nLogCol == GX_INVALID)
		{
			if(IsPMCell(nRow, nCol))
			{
				if(nPatternRow != 0)
					style.SetControl(GX_IDS_PMBUTTON_CONTROL);
				if(!(m_patternMap->m_bIsHeaders && !(nRow / m_patternMap->GetRowSpan())))
					style.SetValue((UINT)GetPMValueAt(nRow));
				else
					style.SetInterior(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND));
				return TRUE;
			}

			// if(IsIndentCell(nRow, nCol))

//			if(nRow == GetRowCount())
//				if(!IsPrinting())
//					style.SetBorders(gxBorderBottom, CGXPen().SetColor(GXSYSCOLOR(COLOR_BTNFACE)));
//				else
//					style.SetBorders(gxBorderBottom, CGXPen().SetColor(RGB(255,255,255)));

			// Assuming row headers are always on col 1.
			if(nCol == 1 && m_patternMap->GetRowHeaderWidth() > 0)
				return CGXHierarchyGrid<T>::GetStyleRowCol(nPatternRow, 0, style, mt, nType);
			else if((nRow % 2) == 0)
			{
				WORD nControlId;
				ROWCOL nChildId;
				// Indent for child grid?
				if(IsChildGridIndentCell(nRow, nCol))
					style.SetInterior(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND));
				// Draw the child grid if it exists.
				else if(GetChildFromAbsCell(nRow, nCol, nChildId) && (nControlId = GetChildControlAt(nLogRow)) != 0)
					style.SetControl(nControlId);

				return TRUE;
			}
			else
			{
				// Set the border colors such that the grid merges into its background smoothly...
				style.SetControl(GX_IDS_CTRL_STATIC)
					.SetIncludeValue(FALSE)
					.SetInterior(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND));

				if(!IsPrinting())
				{
						style.SetBorders(gxBorderRight, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)))
						.SetBorders(gxBorderBottom, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)));
				}
				else
				{
					if(!IsValidAdjacentLogCell(nRow, nCol,0))	// Is valid cell to the right?
						style.SetBorders(gxBorderRight, CGXPen().SetStyle(PS_NULL));
					else
					{
						if(nRow <= GetHeaderRows())
							style.SetBorders(gxBorderRight, CGXPen().SetStyle(PS_SOLID));
						else
							style.SetBorders(gxBorderRight, CGXPen().SetStyle(PS_DOT));
					}
					if(!IsValidAdjacentLogCell(nRow, nCol,1))	// Is valid cell to the bottom?
						style.SetBorders(gxBorderBottom, CGXPen().SetStyle(PS_NULL));
					else
					{
						if(nRow <= GetHeaderRows())
							style.SetBorders(gxBorderBottom, CGXPen().SetStyle(PS_SOLID));
						else
							style.SetBorders(gxBorderBottom, CGXPen().SetStyle(PS_DOT));
					}
				}

				return TRUE;
			}
		}
		else
		{
			BOOL bRet = CGXHierarchyGrid<T>::GetStyleRowCol(nPatternRow, nPatternCol, style, mt, nType);
			return bRet;
		}
	}
	else if(nType == -1)	// Applicable only for row base styles
	{
		ASSERT(nCol == 0);
		if((nRow % 2) == 0)	// Child grid row, do nothing
			return TRUE;
		ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
			// No col base styles in MRT grid
		return CGXHierarchyGrid<T>::GetStyleRowCol(nPatternRow, nCol, style, mt, nType);
	}
	else if(nType == -2)	// For WG Col base style.
	{
		return CGXHierarchyGrid<T>::GetStyleRowCol(0, nCol, style, mt, -1);
	}
//	else ASSERT (FALSE);
	return FALSE;
}

// nDir values: 0-right; 1-bottom;
template<class T>
BOOL CGXWrappedGridCore<T>::IsValidAdjacentLogCell(ROWCOL nRow, ROWCOL nCol, int nDir)
{
	CGXRange rgCovered;
	if(!GetCoveredCellsRowCol(nRow, nCol, rgCovered))
		rgCovered.SetCells(nRow, nCol);

	ROWCOL nLogAdjRow, nLogAdjCol=GX_INVALID;
	BOOL bValid = FALSE;
	switch(nDir)
	{
	case 0:
		GetLogCellFromAbsCell(rgCovered.top, rgCovered.right + 1, nLogAdjRow, nLogAdjCol);
		if(nLogAdjCol != GX_INVALID)
			bValid = TRUE;
		break;
	case 1:
		// Find the next visible row below nRow;
		ROWCOL nBottom = rgCovered.bottom;
		while(nBottom++ < GetRowCount() && IsRowHidden(nBottom));
		if(nBottom >= GetRowCount() || IsRowHidden(nBottom))
		{
			bValid = FALSE;
			break;
		}

		for(ROWCOL nCol = rgCovered.left; nCol <= rgCovered.right; nCol++)
		{
			GetLogCellFromAbsCell(nBottom, nCol, nLogAdjRow, nLogAdjCol);
			if(nLogAdjCol != GX_INVALID)
			{	// Found a valid log cell at the bottom; just break;
				bValid = TRUE;
				break;
			}
		}

		break;
	}
	return bValid;
}

template<class T>
BOOL CGXWrappedGridCore<T>::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	ROWCOL nPatternRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
	if(nType == 0 || nType == 1)
	{
		// Row header value...
		if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth())
			return CGXHierarchyGrid<T>::StoreStyleRowCol(nPatternRow, 0, pStyle, mt, nType);
		CGXRange range;
		ROWCOL nPatternCol;
		m_patternMap->GetSpanCellsRowCol(nRow, nCol, range, &nPatternCol);
		if(!(nPatternCol == GX_INVALID))
		{
			return CGXHierarchyGrid<T>::StoreStyleRowCol(nPatternRow, nPatternCol, pStyle, mt, nType);
		}
		return FALSE;
	}
	else if(nType == -1)	// Applicable only for row base styles
	{
//		ASSERT((nRow % 2) != 0);	// Child grid cell.
		return CGXHierarchyGrid<T>::StoreStyleRowCol(nPatternRow, 0, pStyle, mt, nType);
	}
	else if(nType == -2)	// Applicable for col base styles. nCol should already be the logical col.
	{
		return CGXHierarchyGrid<T>::StoreStyleRowCol(0, nCol, pStyle, mt, -1);
	}
	else ASSERT(FALSE);
	return FALSE;
}


template<class T>
BOOL CGXWrappedGridCore<T>::OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	if(!(m_patternMap->m_bIsHeaders && nRow <= m_patternMap->GetRowSpan()) && // Ignore PMCell in row header.
		IsPMCell(nRow, nCol))
	{
		OnClickedPMCell(nRow, nCol);
		return TRUE;
	}
	return CGXHierarchyGrid<T>::OnLButtonClickedRowCol(nRow, nCol, nFlags, pt);
}


template<class T>
BOOL CGXWrappedGridCore<T>::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	CGXRange range;
	ROWCOL nPatternCol;
	m_patternMap->GetSpanCellsRowCol(dwSelectRow, dwSelectCol, range, &nPatternCol);
	if(bSelect && nPatternCol == GX_INVALID)
	{
		// If not a child grid cell.
		if(!(dwSelectRow && (dwSelectRow % 2) == 0 &&
			dwSelectCol > ((ROWCOL)m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + m_patternMap->m_wChildIndentWidth)))
//			!(dwSelectCol == 1 && m_patternMap->GetRowHeaderWidth() > 0)))
			return FALSE;
	}
	return CGXHierarchyGrid<T>::CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol);
}
template<class T>
BOOL CGXWrappedGridCore<T>::FindNextCell(int direction, ROWCOL& nSetRow, ROWCOL& nSetCol)
{
	// Disregard the incoming nSetRow, nSetCol and compute a new set of values.
	ROWCOL nCurRow=0, nCurCol=0;
	if((direction == GX_UP || direction == GX_DOWN) && GetCurrentCell(nCurRow, nCurCol))
	{
		CGXRange rgCovered;
		CRect rCurrentCell = CalcRectFromRowColEx(nCurRow, nCurCol);
		int nxCenterOfCurrentCell = rCurrentCell.CenterPoint().x;
		if(direction == GX_UP)
		{
			int xSearchPoint = nxCenterOfCurrentCell;
			int ySearchPoint = rCurrentCell.TopLeft().y-1;

			// Row where the search is to be done.
			ROWCOL nRowIndex=0;
			nRowIndex = nCurRow;
			while(--nRowIndex > GetHeaderRows() && IsRowHidden(nRowIndex));
			if(nRowIndex <= GetHeaderRows())
				return FALSE;

			BOOL bFound = FALSE;
			ROWCOL nResultCol=0;
			while(!bFound)
			{
				if(GetNearestSelectableCellInRow(nRowIndex, xSearchPoint, nResultCol, TRUE))	// search left side first
				{
					bFound = TRUE;
					break;
				}
				while(--nRowIndex > GetHeaderRows() && IsRowHidden(nRowIndex));
				if(nRowIndex <= GetHeaderRows())
					return FALSE;
			}
			if(bFound)
			{
				nSetRow = nRowIndex;
				nSetCol = nResultCol;
				return TRUE;
			}
			else
				return FALSE;
		}
		else if(direction == GX_DOWN)
		{
			int xSearchPoint = nxCenterOfCurrentCell;
			int ySearchPoint = rCurrentCell.BottomRight().y+1;

			// Row where the search is to be done.
			ROWCOL nRowIndex;
			nRowIndex = nCurRow;
			while(++nRowIndex <= GetRowCount() && IsRowHidden(nRowIndex));
			if(nRowIndex > GetRowCount())
				return FALSE;

			BOOL bFound = FALSE;
			ROWCOL nResultCol=0;
			while(!bFound)
			{
				if(GetNearestSelectableCellInRow(nRowIndex, xSearchPoint, nResultCol, FALSE))	// search left side first
				{
					bFound = TRUE;
					break;
				}
				while(++nRowIndex <= GetRowCount() && IsRowHidden(nRowIndex));
				if(nRowIndex > GetRowCount())
					return FALSE;
			}
			if(bFound)
			{
				nSetRow = nRowIndex;
				nSetCol = nResultCol;
				return TRUE;
			}
			else
				return FALSE;
		}
	}
	return CGXHierarchyGrid<T>::FindNextCell(direction, nSetRow, nSetCol);
}

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_GX_WRAPPED_GRID_CORE
