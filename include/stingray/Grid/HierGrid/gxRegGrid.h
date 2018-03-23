///////////////////////////////////////////////////////////////////////////////
// gxRegularGrid.h : Regular grid with hierarchical layouts enabled.
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

#ifndef _GX_REGULAR_GRID
#define _GX_REGULAR_GRID

#ifndef _GX_COVERED_PATTERN
#include "grid\HierGrid\gxCvrdPattn.h"
#endif

#ifndef _GX_HIERARCHY_GRID
#include "grid\HierGrid\gxHierGrid.h"
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

/////////////////////////////////////////////////////////////////////////////
// CGXRegularGrid<T> 
template <class T>
class CGXRegularGrid : public CGXHierarchyGrid<T>
{
public:
	CGXRegularGrid();           // protected constructor used by dynamic creation

	// IGXHierarchyGrid virtuals
	virtual gxHierGridType GetGridType();		// Returns the grid type of this grid

	virtual BOOL SetLogRowCount(ROWCOL nRows, UINT flags = GX_UPDATENOW);
	virtual ROWCOL GetLogRowCount();
	virtual BOOL SetLogColCount(ROWCOL nCols, UINT flags = GX_UPDATENOW);
	virtual ROWCOL GetLogColCount();

	virtual BOOL GetAbsCellFromLogCell(ROWCOL nLogRow, ROWCOL nLogCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol);	// Convert the logical cell to the absolute cell in the grid. 
	virtual void GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nLogRow, ROWCOL& nLogCol); // Convert the absolute cell in the grid to the logical cell
	virtual void GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol);

	// Child Grid related APIs
	virtual WORD CreateAndRegisterControl(IGXHierarchyGrid* pHierGrid, WORD id  =0 );
	virtual BOOL IsChildGridIndentCell(ROWCOL nRow, ROWCOL nCol);	// not supported
	virtual void SetIndentWidthForChildGrids(WORD nIndentWidth);	// not supported
	virtual void OnShowChildAt(ROWCOL nLogRow, BOOL bShow);
	virtual BOOL IsChildShown(ROWCOL nLogRow);
	virtual BOOL GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId);
	virtual void OnChangedChildColWidth(ROWCOL nChildId);

	virtual BOOL IsPMCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol);
	virtual BOOL GetPMValueAt(ROWCOL nRow);
	virtual void HidePMExpanderColumn(BOOL bHide = TRUE, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);	// Hide/Show the Plus-Minus-button-expander column

	// CGXGridCore virtuals...
	virtual BOOL IsColHidden(ROWCOL nCol);
	virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	virtual void MergeCoveredCells(CGXRange& range);
	virtual int HitTest(CPoint& pt, ROWCOL* pnRow = NULL, ROWCOL* pnCol = NULL, CRect* rectHit = NULL);
	virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);
	
	virtual BOOL IsRowHidden(ROWCOL nRow);
	virtual int GetRowHeight(ROWCOL nRow);
	virtual int GetColWidth(ROWCOL nCol);

	virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual BOOL OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual void OnGetSortRowsKey(ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys);

protected:
	virtual BOOL RecalcDummyColWidth();

	virtual void SelectRange(const CGXRange& range, BOOL bSelect = TRUE, BOOL bUpdate = TRUE);
	virtual void SetSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);

	virtual void OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	virtual void OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);

	virtual BOOL OnSelDragColsMove(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);

	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual void UpdateInsertCols(ROWCOL nCol, ROWCOL nCount, UINT flags, BOOL bCreateHint = FALSE );
	virtual void UpdateChangedColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidth, UINT flags, BOOL bCreateHint= FALSE);
	virtual void UpdateRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags, BOOL bCreateHint = FALSE);

	virtual void OnGridInitialUpdate( );
	virtual BOOL OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point);

public:	
	// Class members
	BOOL m_nDummyColsWidth;		// Have a dummy col at the right 
								// to accomodate a larger child width.
};

template<class T>
CGXRegularGrid<T>::CGXRegularGrid()
{
	m_nDummyColsWidth = 0;
}

template<class T>
gxHierGridType CGXRegularGrid<T>::GetGridType()
{
	return gxRegularGrid;
}

template<class T>
BOOL CGXRegularGrid<T>::SetLogRowCount(ROWCOL nRows, UINT flags /* = GX_UPDATENOW */)
{
	return SetRowCount((nRows+1)*2, flags);	// One additional row for every log row for child grids.
}

template<class T>
ROWCOL CGXRegularGrid<T>::GetLogRowCount()
{
	return (ROWCOL) (GetRowCount()/2) - 1;
}

template<class T>
BOOL CGXRegularGrid<T>::SetLogColCount(ROWCOL nCols, UINT flags /* = GX_UPDATENOW */)
{
	return SetColCount(nCols+2, flags);	// 1 additional col for the Plus-Minus button.
										// and another one for the dummy col at the right to accomodate 
										// a larger child grid width.
}

template<class T>
ROWCOL CGXRegularGrid<T>::GetLogColCount()
{
	return (ROWCOL) GetColCount()-2;
}

template<class T>
void CGXRegularGrid<T>::GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol)
{
	ASSERT(nChildId <= GetLogRowCount());
	nChildRow = (nChildId+1)*2;
	nChildCol = 2;
}

template<class T>
BOOL CGXRegularGrid<T>::GetAbsCellFromLogCell(ROWCOL nLogRow, ROWCOL nLogCol, ROWCOL& nOrigRow, ROWCOL& nOrigCol)
{
	ASSERT(nLogRow != GX_INVALID);
	ASSERT(nLogCol != GX_INVALID);

	nOrigRow = nOrigCol = GX_INVALID;
	
	nOrigRow = (nLogRow+1)*2 - 1;
	
	nOrigCol = nLogCol + 1;

	if(nOrigRow != GX_INVALID && nOrigCol != GX_INVALID)
		return TRUE;

	return FALSE;
}

template<class T>
void CGXRegularGrid<T>::GetLogCellFromAbsCell(ROWCOL nOrigRow, ROWCOL nOrigCol, ROWCOL& nLogRow, ROWCOL& nLogCol)
{
	nLogRow = nLogCol = GX_INVALID;
	if(nOrigRow != GX_INVALID )
		nLogRow = (nOrigRow-1) / 2;

	// If child row then just set the col to be invalid
	if((nOrigRow % 2) == 0)
		nLogCol = GX_INVALID;
	// Only if nOrigCol is not the Plus-Minus button col or the right most col(the dummy m_nDummyColsWidth col)
	else if(nOrigCol != GX_INVALID && nOrigCol > 1 && nOrigCol != GetColCount())
		nLogCol = nOrigCol - 1;
}

template<class T>
BOOL CGXRegularGrid<T>::GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId)
{
	if((nRow % 2) == 0 && nCol >= 2)
	{
		nChildId = nRow/2 - 1;
		return TRUE;
	}
	return FALSE;
}

template<class T>
BOOL CGXRegularGrid<T>::IsChildGridIndentCell(ROWCOL /*nRow*/, ROWCOL /*nCol*/)
{
	return FALSE;
}

template<class T>
void CGXRegularGrid<T>::SetIndentWidthForChildGrids(WORD /*nIndentWidth*/)
{
	ASSERT(FALSE);
		// not supported
}

template<class T>
CGXRange* CGXRegularGrid<T>::GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range)
{
	// Check if child grid cell.
	if(nRow && (nCol == 1 || nCol == 0))
	{
		range.top = (nRow % 2) ? nRow : nRow-1;
		range.bottom = range.top + 1;
		if(GetPMValueAt((nRow % 2) ? nRow : nRow-1) == 2)	// collapsed
			range.bottom--;
		range.left = range.right = nCol;
		return &range;
	}
	// Child grid cell.
	else if(nRow && (nRow % 2) == 0 && nCol >= 2)
	{
		range.top = range.bottom = nRow;
		range.left = 2;
		range.right = GetColCount();
		return &range;
	}
	else 
		return CGXHierarchyGrid<T>::GetCoveredCellsRowCol(nRow, nCol, range);
}

template<class T>
void CGXRegularGrid<T>::MergeCoveredCells(CGXRange& area)
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
int CGXRegularGrid<T>::HitTest(CPoint &pt, ROWCOL* pnRow, ROWCOL* pnCol, CRect* pRectHit)
{
	return CGXHierarchyGrid<T>::HitTest(pt, pnRow, pnCol, pRectHit);
}

template<class T>
int CGXRegularGrid<T>::OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint & pt, CRect & rect)
{
	return CGXHierarchyGrid<T>::OnExtHitTest(ncRow, ncCol, pt, rect);
}

template<class T>
void CGXRegularGrid<T>::OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize & size)
{
	CGXHierarchyGrid<T>::OnEndTracking(nRow, nCol, nTrackingMode, size);
}


template<class T>
void CGXRegularGrid<T>::OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize &size)
{
	CGXHierarchyGrid<T>::OnMoveTracking(nRow, nCol, nTrackingMode, size);
}

template<class T>
BOOL CGXRegularGrid<T>::OnSelDragColsMove(ROWCOL /*nFirstCol*/, ROWCOL /*nLastCol*/, ROWCOL nDestCol)
{
	// Cannot drop to the left of the expander column.
	if(nDestCol <= 1)
		return FALSE;
	else
		return TRUE;
}

template<class T>
int CGXRegularGrid<T>::GetRowHeight(ROWCOL nRow)
{
	if(!IsRowHidden(nRow) && nRow && (nRow % 2) == 0)
	{
		int nHeight = GetOptimalChildHeightAt((nRow-1)/2);
		if(nHeight >= 0)
			return nHeight;
	}
	return CGXHierarchyGrid<T>::GetRowHeight(nRow);
}

template<class T>
int CGXRegularGrid<T>::GetColWidth(ROWCOL nCol)
{
	if (IsColHidden(nCol))
		return 0;

	if(nCol == GetColCount())
		return m_nDummyColsWidth;
	return CGXHierarchyGrid<T>::GetColWidth(nCol);
}

template<class T>
BOOL CGXRegularGrid<T>::IsColHidden(ROWCOL nCol)
{
	if(IsPrinting())
	{
		if(nCol <= 1 || nCol == GetColCount())
			return TRUE;
	}
	if(nCol == GetColCount())
		return m_nDummyColsWidth == 0;
	else return CGXHierarchyGrid<T>::IsColHidden(nCol);
}

template<class T>
WORD CGXRegularGrid<T>::CreateAndRegisterControl(IGXHierarchyGrid* pChildHierGrid, WORD id /* =0 */)
{
	WORD wControlId = IGXHierarchyGrid::CreateAndRegisterControl(pChildHierGrid, id);
	int nAvailableWidthForChild = CalcSumOfColWidths(2, GetColCount()) - 3;
	// Increase the dummy col's width if not big enough...
	if(nAvailableWidthForChild < GetMaxChildWidth())
		m_nDummyColsWidth += (GetMaxChildWidth() - nAvailableWidthForChild);

	return wControlId;
}

template<class T>
void CGXRegularGrid<T>::OnChangedChildColWidth(ROWCOL nChildId)
{
	CGXHierarchyGrid<T>::OnChangedChildColWidth(nChildId);
	if(RecalcDummyColWidth())
		Redraw();
}

template<class T>
BOOL CGXRegularGrid<T>::RecalcDummyColWidth()
{
	// Adjust dummy col's width
	// The left border of the child grid coincides with the left border of the parent's 2nd column.
	BOOL bOldLimit = m_bLimitColWidth;
	m_bLimitColWidth = FALSE;
	int nAvailableWidthForChild = CalcSumOfColWidths(2, GetColCount()) - 3;		// 3 for borders, etc.
	m_bLimitColWidth = bOldLimit;
						
	int nDiff = GetMaxChildWidth() - nAvailableWidthForChild;

	m_nDummyColsWidth += nDiff;

	m_nDummyColsWidth = max(0, m_nDummyColsWidth);

	return nDiff;		// TRUE if there is change, FALSE if not.
}

template<class T>
void CGXRegularGrid<T>::ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard)
{
	CGXHierarchyGrid<T>::ComposeStyleRowCol(nRow, nCol, pStyle, bApplyStandard);
	// the right most col is just a dummy col to accomodate holding larger child grids.
	if(nCol == GetColCount())
	{
		pStyle->SetControl(GX_IDS_CTRL_STATIC)
			.SetIncludeValue(FALSE)
			.SetInterior(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND));
		if(!IsPrinting())
			pStyle->SetBorders(gxBorderRight, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)))
				.SetBorders(gxBorderBottom, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)));

		else
			pStyle->SetBorders(gxBorderRight, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)))
			.SetBorders(gxBorderBottom, CGXPen().SetColor(GetParam()->GetProperties()->GetColor(GX_COLOR_BACKGROUND)));
	}
}

#pragma warning (push)
#pragma warning (disable: 4706)

template<class T>
BOOL CGXRegularGrid<T>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	if(nType >= 0 && nRow != 0 && nCol != 0)
	{
		ROWCOL nLogRow = (nRow-1) / 2;
		WORD wControlId;
		if((nRow % 2) == 1 && nCol == 1)
		{
			// If row header...
			if(nRow == 1)
			{
				style.SetIncludeValue(FALSE);
				if(IsPrinting())
					style.SetBorders(gxBorderRight, CGXPen().SetColor(RGB(255,255,255)))
						.SetBorders(gxBorderBottom, CGXPen().SetColor(RGB(255,255,255)));
				return TRUE;
			}
			// Expander Col
			BOOL bRet = CGXHierarchyGrid<T>::GetStyleRowCol(nRow, nCol, style, mt, nType);
			style.SetControl(GX_IDS_PMBUTTON_CONTROL);
			style.SetValue((UINT)GetPMValueAt(nRow));
			return bRet;
		}
		// Intentional Assignment???
		if((nRow % 2) == 0 && nCol >= 2	// Child grid...
			&& (wControlId = GetChildControlAt(nLogRow)))
		{
			style.SetControl(wControlId);
			return TRUE;
		}
	}
	return CGXHierarchyGrid<T>::GetStyleRowCol(nRow, nCol, style, mt, nType);
}

#pragma warning (pop) //4706

template<class T>
BOOL CGXRegularGrid<T>::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	ASSERT(nCol != GetColCount());
		// The right most col is a dummy col to accomodate the child grid width.
		// do not set styles for this column.
		// Use GetAbsCellFromLogCell to convert from logical cell to absolute cell parameters if necessary.
	return CGXHierarchyGrid<T>::StoreStyleRowCol(nRow, nCol, pStyle, mt, nType);
}

template<class T>
BOOL CGXRegularGrid<T>::StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed /*= FALSE*/)
{
	ASSERT((nCount % 2) == 0 && (nRow % 2) == 1);
		// Insert in pairs to account for child grids.
	BOOL bRet = CGXHierarchyGrid<T>::StoreInsertRows(nRow, nCount, bProcessed);
	if(bRet)
	{
		m_abRowHidden.InsertBits((nRow+1)/2, nCount/2);
/*		ROWCOL nStartRow = (nRow+1)/2;
		for(ROWCOL i=0; i < nCount/2; i++)
			m_abRowHidden.SetBitAt(nStartRow+i, 1);
*/
		InsertLogRows((nRow-1)/2, nCount/2);
	}
	
	return bRet;
}

template<class T>
BOOL CGXRegularGrid<T>::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed /*= FALSE*/)
{
	ASSERT((nFromRow % 2) == 1 && (nToRow % 2) == 0);
		// Always remove rows in pairs (logical rows along with child rows)

	BOOL bRet = CGXHierarchyGrid<T>::StoreRemoveRows(nFromRow, nToRow, bProcessed);
	if(bRet)
	{
		m_abRowHidden.RemoveBits((nFromRow+1)/2, (nToRow+1)/2);

		//RemoveLogRows((nFromRow-1)/2, (nToRow-1)/2);
	}
	return bRet;
}


template<class T>
BOOL CGXRegularGrid<T>::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed /*= FALSE*/)
{
	ASSERT((nFromRow % 2) == 1 && (nToRow % 2) == 0 && (nDestRow % 2) == 1);
		// Always move rows in pairs (logical rows along with child rows)

	BOOL bRet = CGXHierarchyGrid<T>::StoreMoveRows(nFromRow, nToRow, nDestRow, bProcessed);
	if(bRet)
	{
		// Make sure the m_abRowHidden array's size is inited properly.
		m_abRowHidden.SetBitAt((nFromRow+1)/2, m_abRowHidden.GetBitAt((nFromRow+1)/2));
		m_abRowHidden.SetBitAt((nToRow+1)/2, m_abRowHidden.GetBitAt((nToRow+1)/2));
		m_abRowHidden.SetBitAt((nDestRow+1)/2, m_abRowHidden.GetBitAt((nDestRow+1)/2));

		m_abRowHidden.MoveBits((nFromRow+1)/2, (nToRow+1)/2, (nDestRow+1)/2);
		MoveLogRows((nFromRow-1)/2, (nToRow-1)/2, (nDestRow-1)/2);
	}
	return bRet;
}

template<class T>
BOOL CGXRegularGrid<T>::StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	ASSERT(sortRange.IsRows() && (sortRange.GetHeight() % 2) == 0);
	BOOL bRet = CGXHierarchyGrid<T>::StoreMoveDataRows(sortRange, awRowIndex);

	// Convert to logical rows;
	CGXRange sortRangeOut;
	CDWordArray awRowIndexOut;
	sortRangeOut.top = (sortRange.top-1)/2;
	sortRangeOut.bottom = (sortRange.bottom-1)/2;
	sortRangeOut.rtType = CGXRange::rtRows;

	awRowIndexOut.SetSize(awRowIndex.GetSize()/2);
	for(int i=0; i < awRowIndexOut.GetSize(); i++)
		awRowIndexOut.SetAt(i, awRowIndex.GetAt(i*2)/2);

	// Adjust the child grid indices.
	RearrangeChildren(sortRangeOut, awRowIndexOut);

	return bRet;
}

template<class T>
void CGXRegularGrid<T>::UpdateChangedColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* nOldWidths, UINT flags, BOOL bCreateHint)
{
	BOOL bRedraw = FALSE;
	// Redraw completely if change in col width and GX_UPDATENOW
	if(RecalcDummyColWidth() && flags & GX_UPDATENOW)
	{
		bRedraw = TRUE;
		flags = GX_INVALIDATE;
	}
	CGXHierarchyGrid<T>::UpdateChangedColWidths(nFromCol, nToCol, nOldWidths, flags, bCreateHint);
	if(bRedraw && !IsLockUpdate())
		Redraw();
}

template<class T>
void CGXRegularGrid<T>::UpdateInsertCols(ROWCOL nCol, ROWCOL nCount, UINT flags, BOOL bCreateHint /* = FALSE */)
{
	BOOL bRedraw = FALSE;
	// Redraw completely if change in col width and GX_UPDATENOW
	if(RecalcDummyColWidth() && flags & GX_UPDATENOW)
	{
		bRedraw = TRUE;
		flags = GX_INVALIDATE;
	}
	CGXHierarchyGrid<T>::UpdateInsertCols(nCol, nCount, flags, bCreateHint);
	if(bRedraw && !IsLockUpdate())
		Redraw();
}

template<class T>
void CGXRegularGrid<T>::UpdateRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths /*= NULL*/, UINT flags, BOOL bCreateHint /*= FALSE*/)
{
	BOOL bRedraw = FALSE;
	// Redraw completely if change in col width and GX_UPDATENOW
	if(RecalcDummyColWidth() && flags & GX_UPDATENOW)
	{
		bRedraw = TRUE;
		flags = GX_INVALIDATE;
	}
	CGXHierarchyGrid<T>::UpdateRemoveCols(nFromCol, nToCol, anOldWidths, flags, bCreateHint);
	if(bRedraw && !IsLockUpdate())
		Redraw();
}

template<class T>
BOOL CGXRegularGrid<T>::IsPMCell(ROWCOL nRow, ROWCOL nCol)
{
	if(nRow && nCol == 1)	
		return TRUE;
	else return FALSE;
}

template<class T>
BOOL CGXRegularGrid<T>::OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	if((nRow-1)/2 && IsPMCell(nRow, nCol)) // Ignore PMCell in row header.
	{
		OnClickedPMCell(nRow, nCol);
		return TRUE;
	}
	return CGXHierarchyGrid<T>::OnLButtonClickedRowCol(nRow, nCol, nFlags, pt);
}

template<class T>
BOOL CGXRegularGrid<T>::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	if(dwSelectCol == 1 || dwSelectCol == GetColCount())
		return FALSE;
	return CGXHierarchyGrid<T>::CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol);
}


template<class T>
void CGXRegularGrid<T>::OnGridInitialUpdate() 
{
	// Set the row count and intialize the pattern before calling the base class...
	CGXHierarchyGrid<T>::OnGridInitialUpdate();
	BOOL bHints = m_bHintsEnabled;
	m_bHintsEnabled = FALSE;
	GetParam()->SetNumberedRowHeaders(FALSE);
	SetFrozenRows(2,2);	// For headers.
	HideRows(0, 0);
	m_bHintsEnabled = bHints;
}

template<class T>
void CGXRegularGrid<T>::OnClickedPMCell(ROWCOL nAbsRow, ROWCOL /*nAbsCol*/)
{
	BOOL bCurState = m_abRowHidden.GetBitAt((nAbsRow+1)/2);	// m_abRowHidden is 1based while nLogRow is 0 based. 0 LogRow is row header.
	bCurState = !bCurState;
	if(bCurState == 1)
		ShowChildAt((nAbsRow-1)/2, TRUE);
	else
		ShowChildAt((nAbsRow-1)/2, FALSE);
}

template<class T>
void CGXRegularGrid<T>::OnShowChildAt(ROWCOL nLogRow, BOOL bShow)
{
	m_abRowHidden.SetBitAt(nLogRow+1, bShow);
	if(!bShow)
	{
		ROWCOL nCurRow, nCurCol;
		if(GetCurrentCell(nCurRow, nCurCol) && (nCurRow % 2) == 0)
		{
			TransferCurrentCell();
			MoveCurrentCell(GX_UP, 1);
		}
	}
	Redraw();
}

template<class T>
BOOL CGXRegularGrid<T>::IsChildShown(ROWCOL nLogRow)
{
	if(GetPMValueAt((nLogRow + 1) * 2) == 2)
		return FALSE;
	else 
		return TRUE;
}

template<class T>
BOOL CGXRegularGrid<T>::GetPMValueAt(ROWCOL nRow)
{
	ASSERT(nRow > 0);

	// Expanded: 1
	// Collapsed: 2

	if((nRow+1)/2 == 1)	//header child.
	{
		if(m_bCommonChildGridHeader && !m_bPrintInProgress)
			return 1;
		else
			return 2;
	}
	if(m_abRowHidden.GetBitAt((nRow+1)/2))	// 0-collapsed, 1-expanded
		return 1;
	else
		return 2;
}

template<class T>
void CGXRegularGrid<T>::HidePMExpanderColumn(BOOL bHide /*= TRUE*/, UINT flags /*= GX_UPDATENOW*/, GXCmdType ctCmd /*= gxDo*/)
{
	CGXHierarchyGrid<T>::HideCols(1, 1, bHide, NULL, flags, ctCmd);
}

template<class T>
BOOL CGXRegularGrid<T>::IsRowHidden(ROWCOL nRow)
{
	// The standard col header should always be hidden.
	if(nRow == 0)
		return TRUE;
	if(nRow && (nRow % 2) == 0)
	{
		int state = GetPMValueAt((nRow % 2) ? nRow : nRow-1);
		if(state == 1)
			return FALSE;
		else 
			return TRUE;
	}
	return CGXHierarchyGrid<T>::IsRowHidden(nRow);	
}

template<class T>
BOOL CGXRegularGrid<T>::OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point)
{
	// If PM Cell header cells or child-grid header row
	if((nCol == 1 && nRow == 1) || nRow == 2)
		return FALSE;
	else return CGXHierarchyGrid<T>::OnStartSelection(nRow, nCol, flags, point);
}

// Make sure rows are selected in pairs.
template<class T>
void CGXRegularGrid<T>::SelectRange(const CGXRange& range, BOOL bSelect /*= TRUE*/, BOOL bUpdate /*= TRUE*/)
{
	CGXRange rg = range;
	if(rg.IsRows())
	{
		if((rg.top % 2) == 0)
			rg.top--;
		if((rg.bottom % 2) == 1)
			rg.bottom++;
	}
	CGXHierarchyGrid<T>::SelectRange(rg, bSelect, bUpdate);
}

// Make sure rows are selected in pairs.
template<class T>
void CGXRegularGrid<T>::SetSelection(POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight)
{
	// Make sure row selections are made in pairs.
	if(pos && (nLeft == 0 || nRight == 0))
	{
		if((nTop % 2) == 0)
			nTop--;
		if((nBottom % 2) == 1)
			nBottom++;
	}
	CGXHierarchyGrid<T>::SetSelection(pos, nTop, nLeft, nBottom, nRight);
}

template<class T>
BOOL CGXRegularGrid<T>::OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	nRow, nCol, nFlags, pt;

	CGXGridParam* pParam = GetParam();

	if (nRow == 1 && nCol > 1 && pParam->GetSortRowsOnDblClk())
	{
		// user double-clicked on a column header

		// fill up array with sort order
		CGXSortInfoArray sortInfo;
		sortInfo.SetSize(1); // only 1 column (you can also sort by several columns)
		sortInfo[0].nRC = nCol;
		sortInfo[0].sortType = CGXSortInfo::autodetect;

		if (pParam->m_nLastSortedCol != nCol || !pParam->m_bSortAscending)
			sortInfo[0].sortOrder = CGXSortInfo::ascending;
		else
			sortInfo[0].sortOrder = CGXSortInfo::descending;

		SortRows(CGXRange().SetTable(), sortInfo);

		MoveCurrentCell(GX_TOP);

		return TRUE;
	}

	return CGXHierarchyGrid<T>::OnLButtonDblClkRowCol(nRow, nCol, nFlags, pt);
}

template<class T>
void CGXRegularGrid<T>::OnGetSortRowsKey(ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys)
{
	// Get the same keys for the child row and the parent row.
	if(nRow % 2 == 0)
		nRow--;
	CGXHierarchyGrid<T>::OnGetSortRowsKey(nRow, sortInfo, keys);
}

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //_GX_REGULAR_GRID
