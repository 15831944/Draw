///////////////////////////////////////////////////////////////////////////////
// gxhiergrid.h : Base class for Wrapped grid and MRT grid.
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

#ifndef _GX_HIERARCHY_GRID
#define _GX_HIERARCHY_GRID

#ifndef _GX_COVERED_PATTERN
#include "grid\HierGrid\gxCvrdpattn.h"
#endif

#ifndef GX_PMCONTROL
#include "grid\HierGrid\gxpmctrl.h"
#endif

#ifndef GX_HGFRIMP_H
#include "grid\HierGrid\gxhgfr.h"
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

#include <StingrayExportDefs.h>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define _GX_GRID_WND_WRAPPER_BASE	20300


// GridWnd Wrapper:
class CGXHierGridWrapper : public CGXWndWrapper
{
public:
	GRID_API CGXHierGridWrapper(CGXGridCore* pGrid, CWnd* pWnd, BOOL bNeedDestroy, BOOL bCanActivate, BOOL bInvertBorders);
	GRID_API CGXHierGridWrapper(CGXGridCore* pGrid);
	GRID_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
//	GRID_API virtual void OnNotifyMsg(MSG* pMsg);
	GRID_API virtual BOOL IsActiveAlways();
};

class CMyGrid: public CGXGridWnd
{
	friend class CGXHierGridWrapper;
};


// Hierarchy APIs
enum gxHierGridType
{
	gxNone		  = 0,
	gxRegularGrid = 1,
	gxMRTGrid = 2,
	gxWrappedGrid = 3
};

#define gxHintChangingRowBreaks gxLastHint+1
////////////////////////////////////////////////////////////////////////
class IGXHierarchyGrid
{
public:

	//Constructor
	GRID_API IGXHierarchyGrid(gxHierGridType commonChildGridType  =gxNone , BOOL bCommonChildGridHeader  = FALSE );
	GRID_API virtual ~IGXHierarchyGrid();

	// Hierarchy Grid API...
	virtual gxHierGridType GetGridType()=0;		// Returns the grid type of THIS grid
	GRID_API CRuntimeClass* GetGridClass(gxHierGridType type);	// Returns the runtime class associated with the gridtype.

	// Convert the logical cell to the absolute cell in the grid. 
	virtual BOOL GetAbsCellFromLogCell(ROWCOL nLogRow, ROWCOL nLogCol, ROWCOL& nAbsRow, ROWCOL& nAbsCol) = 0;	
	// Convert the absolute cell in the grid to the logical cell
	virtual void GetLogCellFromAbsCell(ROWCOL nAbsRow, ROWCOL nAbsCol, ROWCOL& nLogRow, ROWCOL& nLogCol) = 0; 
	virtual void GetAbsCellContainingChild(ROWCOL nChildId, ROWCOL& nChildRow, ROWCOL& nChildCol)=0;

	virtual ROWCOL GetLogRowCount()=0;
	virtual ROWCOL GetLogColCount()=0;

	GRID_API IGXHierarchyGrid* GetParent(); // Returns the parent grid
	GRID_API CGXGridCore* GetParentGrid(); // Returns the parent grid as a CGXGridCore*
	GRID_API virtual IGXHierarchyGrid* GetChildAt(ROWCOL nRow, BOOL bForceCreation = FALSE); // Returns the child grid at the logical nRow	
	GRID_API WORD GetChildControlAt(ROWCOL nRow, BOOL bForceCreation = FALSE);		// Returns the child grid wrapper at the logical nRow
	GRID_API IGXHierarchyGrid* GetGridFromControlId(WORD wControlId);


	GRID_API void SetChildGridTemplate(gxHierGridType gridType, CRuntimeClass* pRuntimeGridClass);
	GRID_API void SetCommonChildGridType(gxHierGridType gridType, CRuntimeClass* pRuntimeGridClass, BOOL bCommonChildGridHeader = FALSE);

	GRID_API void InsertLogRows(ROWCOL nLogRow, ROWCOL nCount);
	GRID_API void RemoveLogRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API void MoveLogRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API void RearrangeChildren(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	
	GRID_API virtual void InsertChildAt(ROWCOL nRow, gxHierGridType gridType);	// Insert this particular grid as a child of nRow.
	GRID_API void InsertChildAt(ROWCOL nRow, IGXHierarchyGrid* pGrid);	// Insert this 
		// particular grid as a child of nRow. Use this for customized grid classes.
		// Insert the child after calling Create on it.
	GRID_API void DeleteChildAt(ROWCOL nLogRow);
	GRID_API void DeleteChildren(ROWCOL nFromLogRow, ROWCOL nToLogRow);

	GRID_API virtual void SetIndentWidthForChildGrids(WORD nIndentWidth)=0;	// in pixels.

	GRID_API virtual void HidePMExpanderColumn(BOOL bHide = TRUE, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo)=0;	// Hide/Show the Plus-Minus-button-expander column
	GRID_API void ShowChildAt(ROWCOL nLogRow, BOOL bShow=TRUE);		// Show/Hide the child at a logical row.
	virtual void OnShowChildAt(ROWCOL nLogRow, BOOL bShow)=0;
	virtual BOOL IsChildShown(ROWCOL nLogRow)=0;			// Is it collapsed or expanded.
	GRID_API virtual BOOL IsChildGridCellVisible(ROWCOL nChildId);	// Is the child grid within the current visible area?

	GRID_API virtual WORD CreateAndRegisterControl(IGXHierarchyGrid* pHierGrid, WORD id  =0 );
	GRID_API virtual void OnChildGridInitializing(IGXHierarchyGrid* pChildGrid);	// Called before initializing the child
	GRID_API virtual void OnRegisterChildGrid(IGXHierarchyGrid* pChildHierGrid);	// Called just before registering the wrapper 
																	// containing child grid...
	// Messages from the child...
	GRID_API virtual void OnChangedChildColWidth(ROWCOL nChildId);
	virtual void OnChangedChildRowHeight(ROWCOL nChildId)=0;
	GRID_API virtual void UpdateHintFromChild(ROWCOL nChildId, CGXGridHint* pHint);	// Called by child to pass a hint.
	virtual void UpdateHintFromPeer(CGXGridHint* pHint)=0;	// Called by parent to pass on a hint from a peer
	virtual BOOL MoveCurrentCellFromChild(ROWCOL nChildId, int direction, int xCenterOfCurrentCell) = 0;
	virtual void MoveCurrentCellFromParent(int direction, int xCenterOfCurrentCell)=0;

	// APIs used internally...
	GRID_API int GetOptimalChildHeightAt(ROWCOL nPatternRow);	// Used internally for calculating the child grid row height.
	GRID_API int GetMaxChildWidth();	// Get the width of child that is the broadest.
	GRID_API virtual void OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol)=0;

	// Data members for Hierarchy grid logic.
	GRID_API static WORD		m_nUsedUpControlIds;	// Control Ids for CGXHierWrapper controls.
	int				m_nMaxChildWidth;			// Largest of the child widths.
	ROWCOL			m_nChildId;				// Indicating the row where it is inserted within the parent.
	gxHierGridType	m_CommonChildGridType;	// The common child grid type. 
											// gxNone if no common child grid type.
	IGXHierarchyGrid* m_gridParent;			// Pointer to parent.
	BOOL			m_bScrollChildGridContainerCell;	

	virtual BOOL GetChildFromAbsCell(ROWCOL nRow, ROWCOL nCol, ROWCOL& nChildId)=0;

protected:
	
	BOOL m_bCommonChildGridHeader;			// One common header for all children
											// just below the parent header.
	BOOL m_bProcessingPaint;				// This flag will be TRUE when the grid is processing a paint message.


	// Templates to store the runtime class for the different grid types
	// Can be used irrespective of whether or not there is a common child grid type.
	CRuntimeClass* m_pRegularGridClass;		
	CRuntimeClass* m_pMRTGridClass;			
	CRuntimeClass* m_pWrappedGridClass;

	CWordArray m_wChildGrids;	// Array containing child controls ids.
	// End of Hierarchy APIs

	// Data accessors:
	virtual BOOL IsPMCell(ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL IsChildGridIndentCell(ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL GetPMValueAt(ROWCOL nRow)=0;
};

template <class T>
class CGXHierarchyGrid : public T, public IGXHierarchyGrid
{
public:
	CGXHierarchyGrid(gxHierGridType commonChildGridType = gxNone, BOOL bCommonChildGridHeader = FALSE);
	virtual ~CGXHierarchyGrid();

	// CGXGridCore overrides.
	virtual void OnGridDraw(CDC* pDC);
	virtual void PrepareDCAttribs(CDC* pDC);
	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	virtual BOOL ScrollCellInView(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bFloatCell = FALSE);
	virtual BOOL MoveCurrentCell(int direction, UINT nCell = 1 , BOOL bCanSelectRange = TRUE);
	virtual void UpdateAllViews(CWnd* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnTextNotFound(LPCTSTR lpszFind);
	virtual BOOL DoScroll(int direction, ROWCOL nCell);
	
	// IGXHierarchyGrid interfaces...
	virtual void UpdateHintFromPeer(CGXGridHint* pHint);	// Called by parent to pass on a hint from a peer
	virtual void OnChangedChildRowHeight(ROWCOL nChildId);
	virtual BOOL MoveCurrentCellFromChild(ROWCOL nChildId, int direction, int xCenterOfCurrentCell);
	virtual void MoveCurrentCellFromParent(int direction, int xCenterOfCurrentCell);

	// Called by default to enable sending certain hints between the child/parent.
	void EnableHintsToParent(BOOL bHintsToParent=TRUE, BOOL bRegularHints = FALSE);

	// Utility functions used while moving between logical rows/cols.
	BOOL GetNearestSelectableCellInRow(ROWCOL nRowIndex, int xSearchStart, ROWCOL& nResultCol, BOOL bLeftFirst);
	virtual BOOL SearchForSelectableCellToTheLeftInRow(ROWCOL nRowIndex, ROWCOL nColIndex, ROWCOL& nResultCol);
	BOOL SearchForSelectableCellToTheRightInRow(ROWCOL nRowIndex, ROWCOL nColIndex, ROWCOL& nResultCol);

	// Used to make sure child grids within a rect are hidden before the rect gets repainted.
	void HideChildGridsInRect(CRect& rcHide);
	
	// Used while printing to determine if the child spans more pages than the parent.
	ROWCOL GetMaxChildPageSpanInCurrentRowRange(CDC* pDC, CPrintInfo* pInfo);
	// 	Initialize the font metrics for all the visible children.
	void GetChildFontMetrics(CDC* pDC);

	// Other CGXGridCore Printing overrides.
	virtual void OnGridBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnGridPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnGridPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void SetPrinting(BOOL b, BOOL bClientToRect = FALSE);


protected:
	// More CGXGridCore overrides.
	virtual void OnGridInitialUpdate( );
	virtual void OnGridKillFocus(CWnd* pNewWnd);

	BOOL m_bHideChildGridsWhileRedraw;

public:
	// Member variables
	BOOL m_bRegularHints;
	BOOL m_bHintsToParent;
	CGXBitArray m_abRowHidden;	// To store PMButton state.

	friend class CGXHierarchyGrid<CGXGridWnd>;
	friend class CGXHierarchyGrid<CGXGridView>;
};

// Callback function while enumerating children.
GRID_API BOOL CALLBACK HideChildWndInRect(HWND hwnd,  LPARAM lParam);

// Workaround to access protected members.
template <class T>
class CFriendlyGridTemplate : public CGXGridCore
{
	friend class CGXHierarchyGridFindReplaceImp;
	friend class CGXHierarchyGrid<T>;
	friend IGXHierarchyGrid;
};

class CFriendlyGridWnd : public CGXGridWnd
{
	friend class IGXHierarchyGrid;
};

template<class T>
CGXHierarchyGrid<T>::CGXHierarchyGrid(gxHierGridType commonChildGridType /* =0 */, BOOL bCommonChildGridHeader /* = FALSE */)
:IGXHierarchyGrid(commonChildGridType, bCommonChildGridHeader)
{
	m_bHintsToParent = FALSE;
	m_bRegularHints = FALSE;
	//Do not set m_pFindReplaceImp = NULL here.
	
	// QA: 31521 Removal from AutoDeletePtr
	//AutoDeletePtr(m_pFindReplaceImp = new CGXHierarchyGridFindReplaceImp);
	// The existing F/R Imp instance will be deleted while the grid gets destroyed.
	if(NULL == m_pFindReplaceImp)
	{
		m_pFindReplaceImp = new CGXHierarchyGridFindReplaceImp;
	}
	
	m_bHideChildGridsWhileRedraw = TRUE;
}

template<class T>
CGXHierarchyGrid<T>::~CGXHierarchyGrid()
{
}

template<class T>
void CGXHierarchyGrid<T>::EnableHintsToParent(BOOL bHintsToParent/*=TRUE*/, BOOL bRegularHints /*= FALSE*/)
{
	m_bHintsToParent = bHintsToParent;
	m_bRegularHints = bRegularHints;
	EnableHints(bHintsToParent);
}

template<class T>
void CGXHierarchyGrid<T>::UpdateAllViews(CWnd* pSender, LPARAM lHint, CObject* pHint)
{
	if(m_bRegularHints)
		T::UpdateAllViews(pSender, lHint, pHint);

	if(m_bHintsToParent)
	{
		ASSERT(m_gridParent);
		// ASSERTION-> Do not enable hints to parent (via EnableHintsToParent) unless this is a child grid.
		m_gridParent->UpdateHintFromChild(m_nChildId, (CGXGridHint*)pHint);
	}
}

template<class T>
void CGXHierarchyGrid<T>::UpdateHintFromPeer(CGXGridHint* pHint)
{
	T::OnGridUpdate(NULL, 0, pHint);
}

template<class T>
void CGXHierarchyGrid<T>::OnGridInitialUpdate()
{
	T::OnGridInitialUpdate();
	
	// Force Enable hints to parent if common child type.
	if(m_gridParent && m_gridParent->m_CommonChildGridType)
		EnableHintsToParent();

	CGXPMControl* pPMCtrl = new CGXPMControl(this);
	if(pPMCtrl->CreateControl(GX_IDS_PMBUTTON_CONTROL))
		RegisterControl(GX_IDS_PMBUTTON_CONTROL, pPMCtrl);
	
	// Default behavior allows only direct copy/paste and cut/paste.
	// You can override the default behavior in your derived class's OnInitialUpdate.
	m_nClipboardFlags &= ~(GX_DNDSTYLES | GX_DNDTEXT);
	GetParam()->m_bDirectCopyPaste = TRUE;
	GetParam()->m_bDirectCutPaste = TRUE;
}

template<class T>
void CGXHierarchyGrid<T>::OnChangedChildRowHeight(ROWCOL /*nChildId*/)
{
	// Redraw the corresponding child grid row.
	// nChildId is nothing but the logical row.
	Redraw();
}

template<class T>
BOOL CGXHierarchyGrid<T>::SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags /*= GX_SCROLLINVIEW | GX_UPDATENOW*/)
{
	ROWCOL nChildId;
	// If the cell containing the child grid is becomming the current cell..
	if(GetChildFromAbsCell(nRow, nCol, nChildId))
		flags |= GX_DISPLAYEDITWND;
	return T::SetCurrentCell(nRow, nCol, flags);
}

template<class T>
BOOL CGXHierarchyGrid<T>::ScrollCellInView(ROWCOL nRow, ROWCOL nCol, UINT flags /*= GX_UPDATENOW*/, BOOL bFloatCell /*= FALSE*/)
{
	// The current scroll position is controled by the top most parent grid.
	// Hence, if this is a child grid then determine the nearest parent grid cell
	// that when scrolled into view will make this child grid cell in turn scroll into view.
	if(m_gridParent)
	{
		CGXGridCore* pParentGrid = dynamic_cast<CGXGridCore*>(m_gridParent);

		// If the child grid is not visible
		if(GetGridRect().Width() == 0 && GetGridRect().Height() == 0)
		{
			// Scroll the parent container cell to view.
			ROWCOL nParCurCol, nParCurRow;
			pParentGrid->GetCurrentCell(&nParCurRow, &nParCurCol);
			m_gridParent->m_bScrollChildGridContainerCell = TRUE;
			pParentGrid->ScrollCellInView(nParCurRow, nParCurCol);
			m_gridParent->m_bScrollChildGridContainerCell = FALSE;
			return TRUE;
		}

		// The child cell rect in child co-ords
		CRect rcChildCell = CalcRectFromRowColEx(nRow, nCol, nRow, nCol);

		// child cell rect in screen co-ords
		ClientToScreen(&rcChildCell);
		// child cell rect in parent co-ords
		pParentGrid->GridWnd()->ScreenToClient(&rcChildCell);
		
		CRect rcParClientRect = pParentGrid->GetGridRect();

		// Parent row that coincides with the child cell.
		ROWCOL nParentRow=0, nParentCol=0;

		// Pass a valid point (positive values) to the CalcClientRowFromPt call.
		CRect rcTemp = rcChildCell;
		if(rcTemp.left < 0)
			rcTemp.left = 1;
		nParentRow = pParentGrid->GetRow(pParentGrid->CalcClientRowFromPt(rcTemp.TopLeft()));
		
		// Parent needs to scroll to the left.
		if(rcChildCell.left <= pParentGrid->CalcSumOfColWidths(0, pParentGrid->GetFrozenCols()))
		{
			// Start from the parent client col that is immediately to the right of the parent frozen cols 
			// and keep going left until you find the parent col whose left border is to the left of the child col.
			nParentCol = pParentGrid->GetCol(pParentGrid->GetFrozenCols()+1);

			CRect rcParentCell = pParentGrid->CalcRectFromRowCol(nParentRow, nParentCol);
			while(rcParentCell.TopLeft().x > rcChildCell.TopLeft().x && --nParentCol > pParentGrid->GetFrozenCols())
				rcParentCell.left -= pParentGrid->GetColWidth(nParentCol);
		}
		// Parent needs to scroll to the right
		else if(rcChildCell.left > rcParClientRect.right)
		{
			// Start from the right most parent client col and keep moving to the right 
			// until you find the parent col whose right border is to the right of the child col.
			nParentCol = pParentGrid->CalcRightColFromRect(rcParClientRect);
			CRect rcParentCell = pParentGrid->CalcRectFromRowCol(nParentRow, nParentCol);
			while(rcParentCell.BottomRight().x < rcChildCell.TopLeft().x && ++nParentCol < pParentGrid->GetColCount())
				rcParentCell.right += pParentGrid->GetColWidth(nParentCol);
		}
		// Parent needs to scroll down or up
		else if(rcChildCell.bottom > rcParClientRect.bottom || rcChildCell.bottom < rcParClientRect.top)
			nParentCol = pParentGrid->GetLeftCol();

		if(nParentCol /*&& nParentCol != pParentGrid->GetCol(pParentGrid->GetFrozenCols()+1)*/)
		{
			m_gridParent->m_bScrollChildGridContainerCell = TRUE;
			pParentGrid->ScrollCellInView(nParentRow, nParentCol);
			m_gridParent->m_bScrollChildGridContainerCell = FALSE;
		}
	}

	ROWCOL nChildId;
	// If parent, don't scroll child grid container cell to view.
	if(!m_bScrollChildGridContainerCell && GetChildFromAbsCell(nRow, nCol, nChildId))
		return FALSE;

	return T::ScrollCellInView(nRow, nCol, flags, bFloatCell);
}


// Code to move between parent and child grids.
template<class T>
BOOL CGXHierarchyGrid<T>::MoveCurrentCell(int direction, UINT nCell /*= 1*/ , BOOL bCanSelectRange /*= TRUE*/)
{
	ROWCOL nCurRowBeforeMove, nCurColBeforeMove, nCurRowAfterMove, nCurColAfterMove;
	GetCurrentCell(nCurRowBeforeMove, nCurColBeforeMove);

	//BOOL bRet = 
	T::MoveCurrentCell(direction, nCell, bCanSelectRange);
	GetCurrentCell(nCurRowAfterMove, nCurColAfterMove);

	// Unable to move and at the top/bottom rows? (as a child grid)
	if(nCurRowBeforeMove == nCurRowAfterMove && nCurColBeforeMove == nCurColAfterMove)
	{
		// Scroll the expander col into view if the user tried to move there via keyboard.
		if(direction == GX_LEFT && nCell == 1 && (GetFrozenCols()+1 == nCurColAfterMove-1))
			ScrollCellInView(nCurRowAfterMove, nCurColAfterMove-1);

		ROWCOL nCurRow = nCurRowAfterMove;
		ROWCOL nCurCol = nCurColAfterMove;
		// Check if the current cell has to be moved to the parent.
		if(m_gridParent && GetCurrentCell(nCurRow, nCurCol) && (direction == GX_UP || direction == GX_DOWN))
		{
			int xCenterOfCurrentCell;
			// Get the center point
			CPoint ptCenter = CalcRectFromRowColEx(nCurRow, nCurCol).CenterPoint().x;
			// Convert to screen and then parent-client co-ords
			ClientToScreen(&ptCenter);
			CGXGridCore* pParent = dynamic_cast<CGXGridCore*>(m_gridParent);
			pParent->GridWnd()->ScreenToClient(&ptCenter);
			xCenterOfCurrentCell = ptCenter.x;

			BOOL bMoveToParent = FALSE;
			if(direction == GX_UP)
			{
				ROWCOL nTopRow;
				nTopRow = GetHeaderRows()+1;
				while(nTopRow && IsRowHidden(nTopRow) && ++nTopRow <= GetRowCount());
				// Current cell is on top-most visible row, so move to the parent.
				if(nCurRow == nTopRow && TransferCurrentCell())
					bMoveToParent = TRUE;
			}
			else if (direction == GX_DOWN)
			{
				ROWCOL nLastRow = GetRowCount();
				while(nLastRow && IsRowHidden(nLastRow) && --nLastRow > GetHeaderRows());
				
				// Current cell is on bottom-most visible row, so move to the parent.
				if(nCurRow == nLastRow && TransferCurrentCell())
					bMoveToParent = TRUE;
			}
			if(bMoveToParent && m_gridParent->MoveCurrentCellFromChild(m_nChildId, direction, xCenterOfCurrentCell))
			{
				// No more current cell in the child.
				SetCurrentCell(GX_INVALID, GX_INVALID);
				return TRUE;
			}
		}
	}
	// Check if moved to a child grid cell in the parent grid.
	else 
	{
		ROWCOL nChildId;
		// Is the new cell a child grid container cell?
		if(GetChildFromAbsCell(nCurRowAfterMove, nCurColAfterMove, nChildId))
		{
			// If the cell is not visible first make it visible.
			if(!IsChildGridCellVisible(nChildId))
				// Scrolling might make it visible.
				DoScroll(direction, nCell);

//			RedrawRowCol(nCurRowAfterMove, nCurColAfterMove);

			// Get the center of the previous current cell.
			int xCenterOfCurrentCell;
			CPoint ptCenter = CalcRectFromRowColEx(nCurRowBeforeMove, nCurColBeforeMove).CenterPoint();
//			xCenterOfCurrentCell -= CalcRectFromRowColEx(nCurRowAfterMove, nCurColAfterMove).TopLeft().x;
//			GetControl(nCurRowAfterMove, nCurColAfterMove)->SetActive(TRUE);
			IGXHierarchyGrid* pChild = GetChildAt(nChildId);
			if(pChild)
			{
				// Convert center point to child co-ords.
				CGXGridWnd* pChildAsWnd = dynamic_cast<CGXGridWnd*>(pChild);
				ClientToScreen(&ptCenter);
				pChildAsWnd->ScreenToClient(&ptCenter);
				xCenterOfCurrentCell = ptCenter.x;

				pChild->MoveCurrentCellFromParent(direction, xCenterOfCurrentCell);
			}
		}
		return TRUE;
	}
	return FALSE;
}

// Called by the parent to move the current cell to the appropriate cell in the child.
template<class T>
void CGXHierarchyGrid<T>::MoveCurrentCellFromParent(int direction, int xCenterOfCurrentCell)
{
	ROWCOL nResultRow=0, nResultCol=0;
	BOOL bFound = FALSE;
	if(direction == GX_UP)
	{
		nResultRow = GetRowCount();
		// Get the bottom-most visible row.
		while(IsRowHidden(nResultRow) && --nResultRow > GetHeaderRows());
		if(IsRowHidden(nResultRow))
			return;
		while(!bFound)
		{
			if(GetNearestSelectableCellInRow(nResultRow, xCenterOfCurrentCell, nResultCol, TRUE))
			{
				bFound = TRUE;
				break;
			}
			// Move to the next visible row.
			while(--nResultRow > GetHeaderRows() && IsRowHidden(nResultRow));
			if(nResultRow <= GetHeaderRows())
				return;
		}
		if(bFound)
		{
			SetFocus();
			SetCurrentCell(nResultRow, nResultCol);
			return ;
		}
		else
			return ;
	}
	else if(direction == GX_DOWN)
	{
		nResultRow = GetTopRow();
		// Start with the top-most visible row.
		while(IsRowHidden(nResultRow) && ++nResultRow <= GetRowCount());
		if(nResultRow > GetRowCount())
			return ;

		while(!bFound)
		{
			if(GetNearestSelectableCellInRow(nResultRow, xCenterOfCurrentCell, nResultCol, FALSE))
			{
				bFound = TRUE;
				break;
			}
			// Try in the next visible row.
			while(++nResultRow <= GetRowCount() && IsRowHidden(nResultRow));
			if(nResultRow > GetRowCount())
				return;
		}
		if(bFound)
		{
			SetFocus();
			SetCurrentCell(nResultRow, nResultCol);
			return;
		}
		else
			return;
	}
}

// Called by the child to move the current cell to an appropriate cell in the parent.
// xCenterOfCurrentCell is in the parent's co-ords.
template<class T>
BOOL CGXHierarchyGrid<T>::MoveCurrentCellFromChild(ROWCOL nChildId, int direction, int xCenterOfCurrentCell)
{
	ROWCOL nChildRow, nChildCol;
	GetAbsCellContainingChild(nChildId, nChildRow, nChildCol);
	// Calculate the point from where to start the search.
	int xSearchNear = xCenterOfCurrentCell;
	
	ROWCOL nSearchRow=0, nResultCol=0;
	BOOL bFound = FALSE;
	
	if(direction == GX_UP)
	{
		nSearchRow = nChildRow;
		// Make sure to start search in a visible row.
		while(--nSearchRow > GetHeaderRows() && IsRowHidden(nSearchRow));
		if(nSearchRow <= GetHeaderRows())
			return FALSE;
		while(!bFound)
		{
			if(GetNearestSelectableCellInRow(nSearchRow, xSearchNear, nResultCol, TRUE))
			{
				bFound = TRUE;
				break;
			}
			// Move to the next visible row.
			while(--nSearchRow > GetHeaderRows() && IsRowHidden(nSearchRow));
			if(nSearchRow <= GetHeaderRows())
				return FALSE;
		}
		if(bFound)
		{
			SetCurrentCell(nSearchRow, nResultCol);
			return TRUE;
		}
		else
			return FALSE;
	}
	if(direction == GX_DOWN)
	{
		nSearchRow = nChildRow;
		// Make sure to start search in a visible row.
		while(++nSearchRow <= GetRowCount() && IsRowHidden(nSearchRow));
		if(nSearchRow > GetRowCount())
			return FALSE;

		while(!bFound)
		{
			if(GetNearestSelectableCellInRow(nSearchRow, xSearchNear, nResultCol, FALSE))
			{
				bFound = TRUE;
				break;
			}
			// Move to the next visible row.
			while(++nSearchRow <= GetRowCount() && IsRowHidden(nSearchRow));
			if(nSearchRow > GetRowCount())
				return FALSE;
		}
		if(bFound)
		{
			SetCurrentCell(nSearchRow, nResultCol);
			return TRUE;
		}
		else
			return FALSE;
	}
	return FALSE;
}

// Find the nearest selectable cell to the left of the given cell.
template<class T>
BOOL CGXHierarchyGrid<T>::SearchForSelectableCellToTheLeftInRow(ROWCOL nRowIndex, ROWCOL nColIndex, ROWCOL& nResultCol)
{
	ROWCOL nCurRow, nCurCol;
	GetCurrentCell(nCurRow, nCurCol);

	BOOL bFound = FALSE;
	nColIndex--;
	CGXRange rgCovered;
	while(!bFound)
	{
		if(!nColIndex)
			return FALSE;
		if(GetCoveredCellsRowCol(nRowIndex, nColIndex, rgCovered))
			nColIndex = rgCovered.left;
		if(CanSelectCurrentCell(TRUE, nRowIndex, nColIndex, nCurRow, nCurCol))
		{
			bFound = TRUE;
			break;
		}
		nColIndex--;
	}
	if(bFound)
	{
		nResultCol = nColIndex;
		return TRUE;
	}
	return FALSE;
}

// Find the nearest selectable cell to the right of the given cell.
template<class T>
BOOL CGXHierarchyGrid<T>::SearchForSelectableCellToTheRightInRow(ROWCOL nRowIndex, ROWCOL nColIndex, ROWCOL& nResultCol)
{
	ROWCOL nCurRow, nCurCol;
	GetCurrentCell(nCurRow, nCurCol);

	BOOL bFound = FALSE;
	nColIndex++;
	CGXRange rgCovered;
	while(!bFound)
	{
		if(nColIndex > GetColCount())
			return FALSE;
		if(GetCoveredCellsRowCol(nRowIndex, nColIndex, rgCovered))
			nColIndex += rgCovered.left;
		if(CanSelectCurrentCell(TRUE, nRowIndex, nColIndex, nCurRow, nCurCol))
		{
			bFound = TRUE;
			break;
		}
		nColIndex++;
	}
	if(bFound)
	{
		nResultCol = nColIndex;
		return TRUE;
	}
	return FALSE;
}


template<class T>
BOOL CGXHierarchyGrid<T>::GetNearestSelectableCellInRow(ROWCOL nRowIndex, int xSearchStart, ROWCOL& nResultCol, BOOL bLeftFirst)
{
	ROWCOL nCurRow, nCurCol;
	GetCurrentCell(nCurRow, nCurCol);
	int ySearchStart = CalcRectFromRowColEx(nRowIndex, GetCol(1)).CenterPoint().y;

	// Search at xSearchStart first
	ROWCOL nColIndex=0;
	CPoint pt(xSearchStart, ySearchStart);
	nColIndex = CalcClientColFromPt(pt);
	if(nColIndex == GX_INVALID)
		return FALSE;
	nColIndex = GetCol(nColIndex);	// Convert to absolute col index.
	CGXRange rgCovered;
	if(GetCoveredCellsRowCol(nRowIndex, nColIndex, rgCovered))
	{
		nRowIndex = rgCovered.top;
		nColIndex = rgCovered.left;
	}
	if(CanSelectCurrentCell(TRUE, nRowIndex, nColIndex, nCurRow, nCurCol))
	{
		nResultCol = nColIndex;
		return TRUE;
	}

	// If not found then search to the LeftFirst or RightFirst.
	if(bLeftFirst)
	{
		if(SearchForSelectableCellToTheLeftInRow(nRowIndex, nColIndex, nResultCol))
			return TRUE;
		if(SearchForSelectableCellToTheRightInRow(nRowIndex, nColIndex, nResultCol))
			return TRUE;
	}
	else
	{
		if(SearchForSelectableCellToTheRightInRow(nRowIndex, nColIndex, nResultCol))
			return TRUE;
		if(SearchForSelectableCellToTheLeftInRow(nRowIndex, nColIndex, nResultCol))
			return TRUE;
	}
	return FALSE;
}

template<class T>
void CGXHierarchyGrid<T>::OnGridKillFocus(CWnd* pNewWnd)
{
	T::OnGridKillFocus(pNewWnd);
	IGXHierarchyGrid* pHrFocus = dynamic_cast<IGXHierarchyGrid*>(pNewWnd);

	// See if focus is being set on a child grid.
	if(pHrFocus && pHrFocus->m_gridParent == this)
	{
		ROWCOL nChildRow, nChildCol;
		ROWCOL nChildId = pHrFocus->m_nChildId;
		GetAbsCellContainingChild(nChildId, nChildRow, nChildCol);
		// The cell containing the child grid that gets the focus should also be the current cell.
		if(!IsCurrentCell(nChildRow, nChildCol))
			T::SetCurrentCell(nChildRow, nChildCol, GX_SCROLLINVIEW | GX_UPDATENOW | GX_NOSETFOCUS);	// Don't call own version of SetCurrentCell;
																										// NoFocus b'cos the child should get the focus.	
	}
/*
	// If I am a child of another grid then 
	// there should be no current cell after losing focus
	if(m_gridParent && m_gridParent == pHrFocus && !m_bIgnoreFocus)
	{
		SetCurrentCell(GX_INVALID, GX_INVALID);
		SetSelection(NULL);			
	}
*/
}


template<class T>
void CGXHierarchyGrid<T>::OnGridDraw(CDC* pDC)
{
	// drawing rectangle
	CRect rcClip;
	VERIFY(pDC->GetClipBox(&rcClip) != ERROR);

	if (rcClip.IsRectEmpty())
		return;

	// Hide the visible child grids in the current clipping region.
	// Otherwise, if the corresponding cell doesn't get redrawn the child remains in it's 
	// old rect.
	HideChildGridsInRect(rcClip);

	PrepareDCAttribs(pDC);

	T::OnGridDraw(pDC);
}

template<class T>
void CGXHierarchyGrid<T>::PrepareDCAttribs(CDC* pDC)
{
	// If a child grid, exclude the portion in the clipping rect where the parent grid headers are drawn
	if(m_gridParent)
	{
		CGXGridCore* pParentGrid = dynamic_cast<CGXGridCore*>(m_gridParent);
		
		// Get the current clip box and convert it to the parent's client co-ords.
		CRect rcClip;
		VERIFY(pDC->GetClipBox(&rcClip) != ERROR);
		if (rcClip.IsRectEmpty()
			// Probably a DC created with a call to CreateCompatibleDC
			|| rcClip.Width() == 1 && rcClip.Height() == 1)
			return;

		CRect rcNewClipRect = rcClip;
		ClientToScreen(&rcNewClipRect);
		pParentGrid->GridWnd()->ScreenToClient(&rcNewClipRect);
		
		// Get the x dist. of the right border of the parent's frozen cols.
		int xRightOfFrozenCols = pParentGrid->CalcSumOfColWidths(0, pParentGrid->GetFrozenCols());
		// Does the clip rect fall to the left of the above right-border?
		// If yes, then adjust the clip rect.
		if(rcNewClipRect.left < xRightOfFrozenCols)
		{
			// Adjust the current clip rect's left to exclude the parent grid's headers.
			rcNewClipRect.left = xRightOfFrozenCols;
			rcNewClipRect.right = max(rcNewClipRect.left, rcNewClipRect.right);
			pParentGrid->GridWnd()->ClientToScreen(&rcNewClipRect);
	 		ScreenToClient(&rcNewClipRect);
			
			// Apply the new clip-rect
			pDC->IntersectClipRect(&rcNewClipRect);
		}
	}
}

template<class T>
void CGXHierarchyGrid<T>::HideChildGridsInRect(CRect& rcHide)
{
	CRect rcParam = rcHide;
	ClientToScreen(&rcParam);
	LPARAM lParam;
	if(!m_bHideChildGridsWhileRedraw)
		lParam = NULL;
	else
		lParam = (LPARAM)&rcParam;

	// HideChildWndInRect will hide the child windows if they intersect with rcHide.
	::EnumChildWindows(GridWnd()->m_hWnd, &HideChildWndInRect, lParam);
}

template<class T>
void CGXHierarchyGrid<T>::OnTextNotFound(LPCTSTR)
{
	// Beep only if not a child.
	if(!m_gridParent)
		MessageBeep(0);
}

template<class T>
BOOL CGXHierarchyGrid<T>::DoScroll(int direction, ROWCOL nCell)
{
	if(!(direction == GX_LEFT || direction == GX_RIGHT))
		return T::DoScroll(direction, nCell);

	// No need to hide children while redrawing due to horizontal scrolling.
	BOOL bOldFlag = m_bHideChildGridsWhileRedraw;
	m_bHideChildGridsWhileRedraw = FALSE;

	BOOL bRet = T::DoScroll(direction, nCell);

	m_bHideChildGridsWhileRedraw = bOldFlag;
	return bRet;
}

// Parse through the cells in this rect and if any of the cells hosts a child grid, hide
// it. It's assumed that as soon as you call this function, the grid will be redrawn 
// in portion rcHide.
/*
template<class T>
void CGXHierarchyGrid<T>::HideChildGridsInRect(CRect& rcHide)
{
	CGXRange rgCovered;
	ROWCOL nTop, nBottom, nLeft, nRight , nChildId;
	nTop = GetRow(CalcClientRowFromPt(rcHide.TopLeft()));
	nLeft = GetCol(CalcClientColFromPt(rcHide.TopLeft()));
	rcHide.right--;
	rcHide.bottom--;;
	nBottom = CalcBottomRowFromRect(rcHide);
	nRight = CalcRightColFromRect(rcHide);

	ROWCOL nCount = GetRowCount();

	for (ROWCOL nRow = nTop; nRow <= nBottom && nRow <= nCount; nRow++)
	{
		for (ROWCOL nCol = nLeft; nCol <= nRight; nCol++)
		{
			// Check if covered.
		if (!GetCoveredCellsRowCol(nRow, nCol, rgCovered))
				rgCovered.SetCells(nRow, nCol, nRow, nCol);
	
			nCol = rgCovered.right;
			if(!(nRow > nTop && rgCovered.top < nRow) && GetChildFromAbsCell(nRow, nCol, nChildId))
			{
				// Hide the child grid.
				CGXHierGridWrapper* pWrapper = (CGXHierGridWrapper*)dynamic_cast<CGXGridCore*>(this)->GetRegisteredControl(GetChildControlAt(nChildId));
				if(pWrapper)
					pWrapper->Hide();
			}
		}
	}
}
*/


#include "gxhgprint.h"

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GX_HIERARCHY_GRID
