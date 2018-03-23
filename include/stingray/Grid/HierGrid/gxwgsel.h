///////////////////////////////////////////////////////////////////////////////
// gxwgsel.h
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

#ifndef _GXWGSEL_H_
#define _GXWGSEL_H_

static BOOL AFXAPI _doButtonDown1(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	if (!pGrid->m_bInitDone)
		return FALSE;

	// Process middle mouse click

	pGrid->m_nMouseFlags = flags;
	pGrid->m_bActiveFrame = TRUE;

	// If the grid is already in a special mode, cancel the current mode
	// and return without further processing.

	if (pGrid->GetCapture() == pGrid->m_pGridWnd || flags & xflags)
	{
		// If the grid is already in a special mode, cancel the current mode.
		pGrid->m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
		pGrid->DoCancelMode();
		return FALSE;
	}

	// Be sure, all grid contents are up to date

	pGrid->UpdateWindow();

	// determine context of click

	ht = pGrid->HitTest(point, &nRow, &nCol);

	return TRUE;
}

template<class T>
void CGXWrappedGrid<T>::SelectRangeImp_OnLButtonDown(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	GX_UNUSED_ALWAYS(ht);

	CGXRangeList* pSelList = pGrid->GetParam()->GetRangeList();

	// If clicked on top-left cell.	
	if (nRow == 0 && nCol == 0)
	{
		// selecting cells
		if (pGrid->m_pParam->IsEnableSelection(GX_SELTABLE) && pGrid->OnStartSelection(0, 0, flags, point))
		{
			// ... yes, select/deselect table

			pGrid->SelectWGRange(
				CGXRange().SetTable(),
				!pSelList->IsCellInList(0, 0));

			// ... SelectWGRange will trigger OnChangedSelection event
		}

		return;
	}

	ROWCOL nhRow = pGrid->GetHeaderRows();
	ROWCOL nhCol = pGrid->GetHeaderCols();

	BOOL bCol = (nRow <= pGrid->GetHeaderRows( ) && nCol > nhCol);
	BOOL bRow = (nCol <= pGrid->GetHeaderCols( ) && nRow > nhRow);
	BOOL bCell = (nRow > nhRow && nCol > nhCol);
	BOOL bCtl = flags & MK_CONTROL && pGrid->m_pParam->IsEnableSelection(GX_SELMULTIPLE);
	BOOL bShift = flags & MK_SHIFT && pGrid->m_pParam->IsEnableSelection(GX_SELSHIFT);

	// Convert nRow, nCol to logical values.
	ROWCOL nLogRow, nLogCol;
	GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogCol == GX_INVALID)
		nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
	if(nLogCol == GX_INVALID)
		return;

	if (pGrid->m_pParam->IsEnableSelection(GX_SELFULL) && pGrid->OnStartSelection(nRow, nCol, flags, point))
	{
		ROWCOL ncRow, ncCol;

		// First, remove all selections
		if(!bShift && !bCtl)	
		{
			if (pGrid->CanChangeSelection(0, TRUE, FALSE))
			{
				pGrid->SetWGSelection(0);
				pGrid->OnChangedSelection(0, TRUE, FALSE);
			}
		}
		// If user pressed CTRL-Key while no range was selected
		// but the current cell was visible, select the current
		// cell.
		else if (bCtl && !bShift && pSelList->IsEmpty() && pGrid->GetCurrentCell(ncRow, ncCol)
			&& !pGrid->IsCurrentCell(nRow, nCol))
		{
			GetLogCellFromAbsCell(ncRow, ncCol, ncRow, ncCol);
			CGXRange range(ncRow, ncCol);
			if (pGrid->CanChangeSelection(&range, TRUE, FALSE))
			{
				pGrid->SelectWGRange(range, TRUE);
				pGrid->OnChangedSelection(&range, TRUE, FALSE);
			}
		}
		// Check, if selection is allowed
		if (bRow && pGrid->m_pParam->IsEnableSelection(GX_SELROW)
			|| bCol && pGrid->m_pParam->IsEnableSelection(GX_SELCOL)
			|| bCell && pGrid->m_pParam->IsEnableSelection(GX_SELCELL))
		{
			// start selection

			// if user pressed <SHIFT>, extend last used range

			if (bShift)
			{
				if (pSelList->IsEmpty())
				{
					// select cells starting from current cell
					pGrid->m_SelRectId = pSelList->AddTail(new CGXRange);
					pGrid->m_dwButtonDownRow = 1;
					pGrid->m_dwButtonDownCol = 1;
					pGrid->GetCurrentCell(pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol);
					GetAbsCellFromLogCell(pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol, pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol);
				}
				else
					// last used range
					pGrid->m_SelRectId = pSelList->GetTailPosition();

				CGXRange* pRange = pSelList->GetAt(pGrid->m_SelRectId);
				CGXRange range  =  *pRange;
				range.top = pGrid->m_dwButtonDownRow;
				range.left = pGrid->m_dwButtonDownCol;
				range.bottom = nLogRow;
				range.right = nLogCol;
				
				// allow programmer to change the range
				if (pGrid->CanChangeSelection(&range, TRUE, FALSE))
				//if (CanChangeSelection(pSelList->GetAt(m_SelRectId), TRUE, FALSE))
				{

					pGrid->SetWGSelection(pGrid->m_SelRectId,
						pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol,
						nLogRow, nLogCol);

					// trigger OnChangedSelection event
					pGrid->OnChangedSelection(pGrid->m_SelRectId?pSelList->GetAt(pGrid->m_SelRectId):NULL, TRUE, FALSE);
				}

				pGrid->m_nHitState |= GX_SELECT;
			}
			// Otherwise, add a new range
			else
			{
				pGrid->m_SelRectId = pSelList->AddTail(new CGXRange);

				// m_dwButtonDownRow and m_dwButtonDownCol
				// will be used for further selection,
				// (e.g. when shift key was pressed, or user
				// selects rows with arrow-keys.)

				pGrid->m_dwButtonDownRow = nLogRow;
				pGrid->m_dwButtonDownCol = nLogCol;

				pGrid->m_nHitState |= GX_SELECT;

				// If the user hit a row or column header, the whole
				// row/column will be selected immediately.

				if (bRow || bCol)
				{
					// allow programmer to change the range	
					CGXRange range;

					// single selection listbox
					if (pGrid->m_dwButtonDownRow == 0)
						range.SetCols(min(pGrid->m_dwButtonDownCol, nLogCol), max(pGrid->m_dwButtonDownCol, nLogCol));
					else if (pGrid->m_dwButtonDownCol == 0)
						range.SetRows(min(pGrid->m_dwButtonDownRow, nLogRow), max(pGrid->m_dwButtonDownRow, nLogRow));
										// allow programmer to change the range
					if (pGrid->CanChangeSelection(&range, TRUE, FALSE))
					{

						pGrid->SetWGSelection(pGrid->m_SelRectId, range.top, range.left, range.bottom, range.right);

						// trigger OnChangedSelection event
						pGrid->OnChangedSelection(pGrid->m_SelRectId?pSelList->GetAt(pGrid->m_SelRectId):NULL, TRUE, FALSE);
					}
				}
			}
		}
	}
}

template <class T>
BOOL CGXWrappedGrid<T>::SelectRangeImp_OnMouseMove(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol)
{
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);

	if (pGrid->m_pParam->IsEnableSelection(GX_SELFULL) // selecting cells enabled?
		&& pGrid->m_nHitState & GX_SELECT)
	{
		CGXRangeList* pSelList = pGrid->GetParam()->GetRangeList();

		ROWCOL  nhRow = pGrid->GetHeaderRows();
			//	nhCol = pGrid->GetHeaderCols();

//		if(nRow > nhRow && nCol > nhCol)
//			return TRUE;

		nhRow = (nhRow-1)/m_patternMap->GetRowSpan();

		CGXRange range;

		// single selection listbox

		ROWCOL nLogRow, nLogCol;
		GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
		if(nLogCol == GX_INVALID)
			nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
//		if(nLogCol == GX_INVALID)
//			return TRUE;

		if (pGrid->m_dwButtonDownRow <= nhRow)
		{
			if(nLogCol == GX_INVALID)
				return TRUE;
			range.SetCols(min(pGrid->m_dwButtonDownCol, nLogCol), max(pGrid->m_dwButtonDownCol, nLogCol));
		}
		else if (pGrid->m_dwButtonDownCol == 0)	// Header col
			range.SetRows(min(pGrid->m_dwButtonDownRow, nLogRow), max(pGrid->m_dwButtonDownRow, nLogRow));
		else
		{
			if(nLogCol == GX_INVALID)
				return TRUE;
			nLogRow = max(nLogRow, nhRow+1);
			nLogCol = max(nLogCol, 1);
			range.SetCells(min(pGrid->m_dwButtonDownRow, nLogRow),
				min(pGrid->m_dwButtonDownCol, nLogCol),
				max(pGrid->m_dwButtonDownRow, nLogRow),
				max(pGrid->m_dwButtonDownCol, nLogCol));
		}

		// allow programmer to change the range
		if (pGrid->m_SelRectId && pGrid->CanChangeSelection(&range, TRUE, FALSE))
		{
			pGrid->SetWGSelection(pGrid->m_SelRectId, range.top, range.left, range.bottom, range.right);

			// trigger OnChangedSelection event
			pGrid->OnChangedSelection(pGrid->m_SelRectId?pSelList->GetAt(pGrid->m_SelRectId):NULL, TRUE, FALSE);
		}

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::DoLButtonDown(UINT flags, CPoint point)
{
	TRY
	{
		ROWCOL  nRow, nCol; //, nLogRow, nLogCol;
		int ht;
		if (!_doButtonDown1(this, flags, point, MK_MBUTTON | MK_RBUTTON, ht, nRow, nCol))
			return FALSE;

		BOOL bShift = flags & MK_SHIFT;

		if(ht == GX_CELLHIT || ht == GX_HEADERHIT)
		{
			if(nRow == 0 && nCol == 0)
			{
				// ... select/deselect whole table
				
				m_nHitState = GX_HIT;
				m_nHitRow   = nRow;
				m_nHitCol   = nCol;
				
				if (IsCurrentCell(m_nHitRow, m_nHitCol))
					m_nHitState |= GX_HITCURRENTCELL;
				
				SelectRangeImp_OnLButtonDown(this, point, flags, ht, nRow, nCol);
				
				m_dwLastMoveRow   = nRow;
				m_dwLastMoveCol   = nCol;
				
				// OnLButtonHitRowCol will process application specific behaviour
				// for dragging cells. When OnLButtonHitRowCol returns FALSE,
				// the current mouse action will be canceled.
				//
				if (OnLButtonHitRowCol(nRow, nCol, nRow, nCol, point, flags,
					(WORD) (m_nHitState | GX_HITSTART | GX_HITINCELL)))
				{
					// The programmer can initialize autoscrolling or mouse capturing
					// in OnLButtonHitRowCol.
					//
					// If he did not I will do it myself (this is the default).
					//
					if (GetCapture() != m_pGridWnd && m_nHitState)
						SetCapture();
				}
				else
					m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
			}
			else
			{
				if(UserDragSelectRangeImp_OnLButtonDown(this, point, flags, ht, nRow, nCol))
					return TRUE;

				// Otherwise, the grid is changed into hit-mode.
				// The programmer can modify the default behaviour by
				// specifiying GetParam()->EnableSelection() and/or
				// overriding OnLButtonHitRowCol
				//

				{
					ROWCOL nLogRow, nLogCol;
					GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
					if(nLogCol == GX_INVALID)
						nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
					// If still invalid then do not start the hit state.
//					if(nLogCol == GX_INVALID)
//						return FALSE;
					// Hit normal Cell or fixed Cell
					
					BOOL bCtl = flags & MK_CONTROL;
					
					m_nHitState = GX_HIT;
					m_nHitRow   = nLogRow;
					m_nHitCol   = nLogCol;
					m_nAbsHitRow = nRow;
					m_nAbsHitCol = nCol;
					
					CGXRange rgCovered(nRow, nCol);
					ROWCOL nCovRow, nCovCol;
					nCovRow = nRow;
					nCovCol = nCol;
					if (GetCoveredCellsRowCol(nRow, nCol, rgCovered))
					{
						if(GetControl(rgCovered.top, rgCovered.left)->IsWindowlessControl())
						{
							nCovRow = rgCovered.top;
							nCovCol = rgCovered.left;
						}
					}
					
					if (IsCurrentCell(nCovRow, nCovCol) && GetControl(nCovRow, nCovCol)->IsInit())
						m_nHitState |= GX_HITCURRENTCELL;		

					if (bCtl)
						m_nHitState |= GX_CTRLPRESSED;
					
					// Next block contains functionality for selecting cells.
					//
					// The programmer can inhibit this behaviour by specifying
					// GetParam()->EnableSelection(FALSE).
					//
					if(m_nHitCol != GX_INVALID)
						SelectRangeImp_OnLButtonDown(this, point, flags, ht, nRow, nCol);

					m_dwLastMoveRow   = nLogRow;
					m_dwLastMoveCol   = nLogCol;

					// OnLButtonHitRowCol will process application specific behaviour
					// for dragging cells. When OnLButtonHitRowCol returns FALSE,
					// the current mouse action will be canceled.
					//
					if (OnLButtonHitRowCol(nRow, nCol, nRow, nCol, point, flags,
						(WORD) (m_nHitState | GX_HITSTART | GX_HITINCELL)))
					{
						// The programmer can initialize autoscrolling or mouse capturing
						// in OnLButtonHitRowCol.
						//
						// If he did not, I will do it myself (this is the default),
						//
						
						if (GetCapture() != m_pGridWnd && m_nHitState)
						{
							// Catch all Mouse events
							if (m_bAutoScroll)
								// I am using AutoScroll until WM_LBUTTONUP Message
								AutoScroll(FALSE,
								nRow > 0 && !IsFrozenRow(nRow),
								nCol > 0 && !IsFrozenCol(nCol));
							
							SetCapture();
						}
					}
					else
						m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
				}
			}
		}

		// check, if user clicked on a vertical line to resize the column
		// ... (behaviour can be changed with GetParam()->EnableTrackColWidth(...)
		// and GetParam()->SetRowHeaderLines(...)
		
		else if (m_pUserResizeCellsImp
			&& m_pUserResizeCellsImp->OnLButtonDown(this, point, flags, ht, nRow, nCol))
			return TRUE;
		
		// user clicked outside the grid
		
		else
			return FALSE;

	}
	CATCH(CException, e)
	{
		m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
	}
	END_CATCH
	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::GetInvertStateRowCol(ROWCOL nRow, ROWCOL nCol, const CGXRangeList* pSelList)
{
	ROWCOL nLogRow, nLogCol;
	GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogRow == GX_INVALID && nLogCol != GX_INVALID)	// Col Header
		nLogRow = 0;
	if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth())	// Row Header.
		nLogCol = 0;
	if(nLogRow == GX_INVALID || nLogCol == GX_INVALID)
		return FALSE;
	return pSelList->IsCellInList(nLogRow, nLogCol);
}

template<class T>
void CGXWrappedGrid<T>::SelectWGRange(const CGXRange& range, BOOL bSelect /* = TRUE */, BOOL bUpdate )
{
	// Save old state
	CGXRangeList oldRangeList;
	CopyRangeList(oldRangeList, FALSE);

	// Store new range
	if (StoreWGSelectRange(range, bSelect))
	{
		OnChangedSelection((CGXRange*) &range, FALSE, FALSE);
		if (bUpdate)
		//	UpdateSelectRange(range, &oldRangeList, TRUE);
			Redraw();
	}
}

template<class T>
BOOL CGXWrappedGrid<T>::StoreWGSelectRange(const CGXRange& range, BOOL bSelect)
{
	// Check
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if (bSelect)
	{
		// Simply add it to the list of selections
		pSelList->AddTail(new CGXRange(range));
	}
	else
	{
		// Remove it from the list of selections
		CGXRange* pRangeItem;
		CGXRange r;
		CGXRange rangeEx = range;
		rangeEx.ExpandRange(1, 1, m_nRowCount, m_patternMap->GetColCount());
		POSITION pos = pSelList->GetHeadPosition();
		POSITION posOld;
		while (pos)
		{
			posOld = pos;
			pRangeItem = pSelList->GetNext(pos);
			CGXRange rangeItemEx = pRangeItem;
			rangeItemEx.ExpandRange(1, 1, m_nRowCount, m_patternMap->GetColCount());
			if (r.IntersectRange(rangeItemEx, rangeEx))
			{
				// check if is a interior rectangle of a given range
				// if yes, exclude the area from the existing range and
				// break the existing range into max. 4 pieces

				if (r.top > rangeItemEx.top)
				{
					CGXRange* pNewRange = new CGXRange;

					if (range.IsRows() && (pRangeItem->IsRows() || pRangeItem->IsTable()))
						pNewRange->SetRows(rangeItemEx.top, r.top-1);

					pSelList->AddTail(pNewRange);
				}

				if (r.bottom < rangeItemEx.bottom)
				{
					CGXRange* pNewRange = new CGXRange;

					if (range.IsRows() && (pRangeItem->IsRows() || pRangeItem->IsTable()))
						pNewRange->SetRows(r.bottom+1, rangeItemEx.bottom);

					pSelList->AddTail(pNewRange);
				}

				if (r.left > rangeItemEx.left)
				{
					CGXRange* pNewRange = new CGXRange;

					if (range.IsCols() && (pRangeItem->IsCols() || pRangeItem->IsTable()))
						pNewRange->SetCols(rangeItemEx.left, r.left-1);

					pSelList->AddTail(pNewRange);
				}

				if (r.right < rangeItemEx.right)
				{
					CGXRange* pNewRange = new CGXRange;

					if (range.IsCols() && (pRangeItem->IsCols() || pRangeItem->IsTable()))
						pNewRange->SetCols(r.right+1, rangeItemEx.right);

					pSelList->AddTail(pNewRange);
				}

				// remove the original range
				delete pRangeItem;
				pSelList->RemoveAt(posOld);
			}
		}
	}

	return TRUE;
}

template<class T>
void CGXWrappedGrid<T>::SetWGSelection(POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight)
{
	// ASSERT(!m_bPrintInProgress);
	// TRACE(_T("CGXGridCore: BEGIN SetSelection(%u,%u,%u,%u)\n"),
	//  nTop, nLeft, nBottom, nRight);

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if (pos == NULL)
	{
		// Clear all Selection
		if (!pSelList->IsEmpty())
			PrepareClearSelection(TRUE);
		pSelList->DeleteAll();
		m_SelRectId = NULL;
	}
	else
	{
		// Change the actual Selection
		UpdateWindow();

		ROWCOL l;

		if (nTop > nBottom)
			l = nTop, nTop = nBottom, nBottom = l;

		if (nLeft > nRight)
			l = nLeft, nLeft = nRight, nRight = l;

		PrepareChangeWGSelection(pos, nTop, nLeft, nBottom, nRight, TRUE);

		CGXRange* pRange = pSelList->GetAt(pos);

		if (nTop == 0 && nLeft == 0)
			pRange->SetTable();
		else if (nLeft == 0)
			pRange->SetRows(nTop, nBottom);
		else if (nTop == 0)
			pRange->SetCols(nLeft, nRight);
		else
			pRange->SetCells(nTop, nLeft, nBottom, nRight);
	}
	// TRACE0("CGXGridCore: END   SetSelection()\n");
}

template<class T>
void CGXWrappedGrid<T>::PrepareChangeWGSelection(POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right, BOOL bCreateHint)
{
	if(IsLockUpdate())
		return;

	// ASSERT(!m_bPrintInProgress);
	ROWCOL bottomRow = GetLastVisibleRow();
	ROWCOL rightCol = GetLastVisibleCol();

	ROWCOL nTop = top, nLeft = left, nBottom = bottom, nRight = right;
	BOOL bCol = FALSE, bRow = FALSE;
	BOOL bMultipleAbsRows = FALSE;

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if(nTop == 0 && nBottom == 0)
		bCol = TRUE;
	if(nLeft == 0 && nRight == 0)
		bRow = TRUE;
	// Find out if the selection spans multiple absolute rows.
	if(!bRow)
	{
		// If selected columns wrap between multiple absolute rows then you need to update the whole grid.
		ROWCOL nRowTop, nRowBottom, nTempCol;
		GetAbsCellFromLogCell(0, nLeft, nRowTop, nTempCol);
		GetAbsCellFromLogCell(0, nRight, nRowBottom, nTempCol);
		if(nRowTop != nRowBottom)
			bMultipleAbsRows = TRUE;
		if(oldPos && !bMultipleAbsRows)	// Check if old position had multiple logical rows selected
		{
			CGXRange oldRange;
			oldRange = *(pSelList->GetAt(oldPos));
			if(oldRange.IsValid())
			{
				GetAbsCellFromLogCell(0, oldRange.left, nRowTop, nTempCol);
				GetAbsCellFromLogCell(0, oldRange.right, nRowBottom, nTempCol);
				if(nRowTop != nRowBottom)
					bMultipleAbsRows = TRUE;
			}
		}
	}

	m_bLockEvalMergeCells = TRUE;
	m_bLockEvalFloatCells = TRUE;           // Don't evaluate float cell state

	ROWCOL nRowCount = m_nRowCount;
	ROWCOL nColCount = m_patternMap->GetColCount();

	// Get current rectangle (to be changed)
	CGXRange oldRect;
	if (oldPos)
		oldRect = *(pSelList->GetAt(oldPos));
	if (oldRect.IsValid())
		oldRect.ExpandRange(0, 0, nRowCount, nColCount);
	else
		oldPos = NULL;

// Freezing cols is not allowed with wrapped rows. (Except for row header cells, which is done by default).
//	ROWCOL nFrozenCols = GetFrozenCols(); 
	ROWCOL nFrozenRows = GetFrozenRows();
	// Convert to logical rows.
	nFrozenRows = (nFrozenRows-1)/m_patternMap->GetRowSpan();

	// Expand fixed Cols and Rows (..Ex are absolute index in Grid)
	// and sort them (left < right, top < bottom)
	ROWCOL nTopEx    = min(nTop, nBottom);
	ROWCOL nLeftEx   = min(nLeft, nRight);
	ROWCOL nBottomEx = (nTopEx>0)?max(nTop, nBottom):nRowCount;
	ROWCOL nRightEx  = (nLeftEx>0)?max(nLeft, nRight):nColCount;

	// Union both Rectangles (absolute index)
	nTop    = oldPos?min(nTopEx,    oldRect.top)   :nTopEx;
	nLeft   = oldPos?min(nLeftEx,   oldRect.left)  :nLeftEx;
	nBottom = oldPos?max(nBottomEx, oldRect.bottom):nBottomEx;
	nRight  = oldPos?max(nRightEx,  oldRect.right) :nRightEx;

	// TRACE(_T("OldRect %d => %u,%u,%u,%u\n"), oldPos?1:0, oldRect);

	// Get Client Rows and Cols (relative Index to TopLeft)
//	nTop    = GetClientRow(nTop);
//	nLeft   = GetClientCol(nLeft);
//	nBottom = GetClientRow(nBottom);
//	nRight  = GetClientCol(nRight);
	
	// Convert to absolute indices.
	if(bCol)
	{
		ROWCOL nLogRight = nRight;
		GetAbsCellFromLogCell(nTop, nLeft, nTop, nLeft);
		GetAbsCellFromLogCell(nBottom, nRight, nBottom, nRight);
		ASSERT(nLeft != GX_INVALID && nRight != GX_INVALID);
		nTop = 1;
		nBottom = GetLastVisibleRow(NULL);
		if(bMultipleAbsRows)	// Parse through the whole grid.
		{
			nLeft = m_patternMap->GetRowHeaderWidth() + 1;
			nRight = GetLastVisibleCol(NULL);
		}
		else 
			nRight = nRight + m_patternMap->GetColWidth(nLogRight) - 1;
	}
	else if(bRow)
	{
		nTop = ((nTop + m_patternMap->m_bIsHeaders - 1)* m_patternMap->GetRowSpan()) + 1;
		nBottom = (nBottom + m_patternMap->m_bIsHeaders) * m_patternMap->GetRowSpan();
		nLeft = 1;
		nRight = GetLastVisibleCol(NULL);
	}
	else	// Multiple cells selection
	{
		ROWCOL nLogRight = nRight;
		GetAbsCellFromLogCell(nTop, nLeft, nTop, nLeft);
		GetAbsCellFromLogCell(nBottom, nRight, nBottom, nRight);
		if(bMultipleAbsRows)
		{
			nLeft = m_patternMap->GetRowHeaderWidth() + 1;
			nRight = GetLastVisibleCol(NULL);
		}
		else
			nRight = nRight + m_patternMap->GetColWidth(nLogRight) - 1;
	}

	// Intersect with displayable Rect  (absolute Index)
//	nTop    = (nTop<=nFrozenRows) ? nTop : max(nTop, GetTopRow());
//	nLeft   = (nLeft<=nFrozenCols) ? nLeft : max(nLeft, GetLeftCol());
	nBottom = min(nBottom, bottomRow);
	nRight  = min(nRight, rightCol);

	nTop    = GetClientRow(nTop);
	nLeft   = GetClientCol(nLeft);
	nBottom = GetClientRow(nBottom);
	nRight  = GetClientCol(nRight);

//	if (nBottom == 0)
//		nBottom = GetFrozenRows();

//	if (nRight == 0)
//		nRight = GetFrozenCols();

	CClientDC dc(m_pGridWnd);
	OnGridPrepareDC(&dc);
	dc.IntersectClipRect(GetGridRect());

	CRect rectItem = CalcRectFromClientRowCol(0, 0);

	// Erase old and draw new rectangle
//	CGXRange rgNew(top, left, bottom, right);

//	DrawSelectionFrame(&dc, TRUE, &rgNew);

	// Check each cell if it should be inverted
	for (ROWCOL nClientRow = nTop; nClientRow <= nBottom; nClientRow++)
	{
		for (ROWCOL nClientCol = nLeft; nClientCol <= nRight; nClientCol++)
		{
			ROWCOL nCol = GetCol(nClientCol), // absolute Index
				 nRow = GetRow(nClientRow);

			BOOL bIsSel = GetInvertStateRowCol(nRow, nCol, pSelList);

			ROWCOL nLogRow, nLogCol;
			GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
			if(nLogRow == GX_INVALID && nLogCol != GX_INVALID)	// Col Header
				nLogRow = 0;
			if(nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth())	// Row Header.
				nLogCol = 0;

			BOOL bNewSel =
				((nLogCol >= nLeftEx && nLogCol <= nRightEx
				&& nLogRow >= nTopEx && nLogRow <= nBottomEx) // True, if should be inverted
				|| pSelList->IsCellInList(nLogRow, nLogCol, oldPos))
				;
			//&& (!IsCurrentCell(nRow, nCol)
			//          || GetParam()->GetHideCurrentCell() == GX_HIDE_ALWAYS);

			// TRACE(_T("PrepareChangeSelection: %d/%d IsSel=%d, NewSel=%d\n"),
			//  nRow, nCol, bIsSel, bNewSel);
			if (bNewSel != bIsSel)
			{
				rectItem = CalcNextRectFromClientRowCol(nClientRow, nClientCol);
				DrawInvertCell(&dc, nRow, nCol, rectItem);
				// dc.InvertRect(rectItem);
			}
		}
	}

	// Create Hint
	if (m_pUpdateHintImp && bCreateHint && m_bHintsEnabled)
		m_pUpdateHintImp->HintPrepareChangeSelection(this, oldPos, top, left, bottom, right);

	m_bLockEvalMergeCells = FALSE;
	m_bLockEvalFloatCells = FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::DoMouseMove(UINT flags, CPoint point)
{
	if (!m_bInitDone)
		return FALSE;
	
	// Process mouse move
	TRY
	{
		CRect rectGrid = GetGridRect();
		
#if _MFC_VER >= 0x0400
		// Forward MouseMove to ToolTip
		if (m_bTtnIsEnabled && m_pTooltipProxy && GetCapture() != m_pGridWnd)
			m_pTooltipProxy->OnMouseMove(flags, point);
#endif
		
		CPoint ptOrg = point;
		
		// Convert to valid point
		point.x = min(max(point.x, rectGrid.left), rectGrid.right-m_dyFrame);
		point.y = min(max(point.y, rectGrid.top), rectGrid.bottom-m_dyFrame);
		
		// If the user hit a selected row or column,
		// the grid was changed to dragging-mode.
		//
		// When dragging-mode, there will be no calls to OnLButtonHitRowCol.
		//
		
		if (UserDragSelectRangeImp_OnMouseMove(this, point, flags))
			return TRUE;
		
		// Check, if grid is in hit-mode.
		//
		// The programmer can modify the default behaviour by
		// specifiying GetParam()->EnableSelection() and/or
		// overriding OnLButtonHitRowCol
		//
		
		else if (m_nHitState)
		{
			ROWCOL nAbsHitRow, nAbsHitCol;
/*			if(m_nHitCol == 0)
			{
				nAbsHitRow = m_nHitRow * m_patternMap->GetRowSpan() + 1;
				nAbsHitCol = 0;
			}
			else 
				GetAbsCellFromLogCell(m_nHitRow, m_nHitCol, nAbsHitRow, nAbsHitCol);
*/
			nAbsHitRow = m_nAbsHitRow;
			nAbsHitCol = m_nAbsHitCol;

			ASSERT(GetCapture() == m_pGridWnd);
			
			if (GetCapture() != m_pGridWnd)
				return FALSE;
			
			ROWCOL nRow, nCol, nLogRow, nLogCol;
			
			// Get actual coordinates
			int ht;
			ht = HitTest(point, &nRow, &nCol);
			
			//nRow = min(max(1, nRow), GetRowCount());
			//nCol = min(max(1, nCol), GetColCount());
			// Restrict hit below header rows only if selection started below header rows.
			if(nAbsHitRow > GetHeaderRows())
				nRow = min(max(GetRow(GetHeaderRows()+1), nRow), GetRowCount());
			else
				nRow = min(GetHeaderRows(), nRow);
			nCol = min(max(GetCol(GetHeaderCols()+1), nCol), GetColCount());
			
			// OnLButtonHitRowCol will process application specific behaviour
			// for dragging cells (and call the control's MouseMove method)
			//
			GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
			if(nLogCol == GX_INVALID)
				nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
//			if(nLogCol == GX_INVALID)
//				return TRUE;

			
			WORD w = (WORD) (m_nHitState | GX_HITMOVE);
			
			if (nLogRow == m_nHitRow && nLogCol == m_nHitCol)
				w |= GX_HITINCELL;
			else if (m_dwLastMoveRow == m_nHitRow && m_dwLastMoveCol == m_nHitCol)
				w |= GX_HITLEAVE;
			
			
			if (m_nMouseFlags & MK_LBUTTON)
				OnLButtonHitRowCol(nAbsHitRow, nAbsHitCol, nRow, nCol, point, flags, w);
			else if (m_nMouseFlags & MK_MBUTTON)
				OnMButtonHitRowCol(nAbsHitRow, nAbsHitCol, nRow, nCol, point, flags, w);
			else if (m_nMouseFlags & MK_RBUTTON)
				OnRButtonHitRowCol(nAbsHitRow, nAbsHitCol, nRow, nCol, point, flags, w);
			
			// if coordinates do not have changed, return FALSE
			
			if (nLogRow == m_dwLastMoveRow && nLogCol == m_dwLastMoveCol)
				return TRUE;
			
			// Next block contains functionality for selecting cells.
			//
			// The programmer can inhibit this behaviour by specifying
			// GetParam()->EnableSelection(FALSE).
			//
//			if(ht == GX_HEADERHIT)
				SelectRangeImp_OnMouseMove(this, point, flags, nRow, nCol);
			
			// save current coordinates
			m_dwLastMoveRow = nLogRow;
			m_dwLastMoveCol = nLogCol;
			
			// ... they will be checked in next MouseMove call
			
			return TRUE;
		}
		
		// check, if grid is in tracking mode
		//
		
		else if (m_pUserResizeCellsImp
			&& m_pUserResizeCellsImp->OnMouseMove(this, point, flags))
			return TRUE;
		
		else if (rectGrid.PtInRect(ptOrg) && !m_bDisableMouseMoveOver)
		{
			ROWCOL nRow, nCol;
			
			// Get actual coordinates
			HitTest(point, &nRow, &nCol);
			
			nRow = min(nRow, GetRowCount());
			nCol = min(nCol, GetColCount());
			
			// Give the control the chance to hand mouse movement
			// e.g. change cursor
			
			CGXRange rgCovered;
			if (GetCoveredCellsRowCol(nRow, nCol, rgCovered))
			{
				nRow = rgCovered.top;
				nCol = rgCovered.left;
			}
			
			CGXControl* pControl = GetControl(nRow, nCol);
			
			if (!pControl->MouseMoveOver(nRow, nCol, flags, point))
				ShowContextCursor(point);
			
			return TRUE;
		}
		
		else 
		{
			ShowContextCursor(ptOrg);
			
			return TRUE;
		}
		
	}
	CATCH(CException, e)
	{
		m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
	}
	END_CATCH

	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::DoLButtonUp(UINT flags, CPoint point)
{
	m_bAutoScrollStop = TRUE;

	if (!(GetCapture() == m_pGridWnd)) {
		return FALSE;
	}

	// TRACE2("CGXGridCore: OnLButtonUp(%u, (%d,%d))\n", flags, point);

	TRY
	{
		CRect rectGrid = GetGridRect();
		point.x = min(max(point.x, 0), rectGrid.right-m_dyFrame);
		point.y = min(max(point.y, 0), rectGrid.bottom-m_dyFrame);

		// If the user hit a selected row or column,
		// the grid was changed to dragging-mode.
		//
		// When dragging-mode, there will be no call to OnLButtonHitRowCol.
		//

		if(UserDragSelectRangeImp_OnLButtonUp(this, point, flags))
			return TRUE;

		// Check, if grid is in hit-mode.
		//

		else if (m_nHitState)
		{
			ROWCOL nAbsHitRow, nAbsHitCol;
/*			if(m_nHitCol == 0)
			{
				nAbsHitRow = m_nHitRow * m_patternMap->GetRowSpan() + 1;
				nAbsHitCol = 0;
			}
			else 
				GetAbsCellFromLogCell(m_nHitRow, m_nHitCol, nAbsHitRow, nAbsHitCol);
*/
			nAbsHitRow = m_nAbsHitRow;
			nAbsHitCol = m_nAbsHitCol;

			// Release Mouse Capture
			if (m_pGridWnd->GetCapture() == m_pGridWnd)
				ReleaseCapture();

			// for Excel Like Auto Fill
//			if (GetParam()->m_nExcelLikeFillFlags && m_pExcelLikeFillImp)
//				m_pExcelLikeFillImp->OnLButtonUp(this, point, flags);

			// Next block contains functionality for selecting cells.
			//
			// The programmer can inhibit this behaviour by specifying
			// GetParam()->EnableSelection(FALSE).
			//

			SelectRangeImp_OnLButtonUp(this, point, flags);

			// OnLButtonHitRowCol will process application specific behaviour
			// for dragging cells (and call the control's LButtonUp method)
			//

			ROWCOL nRow, nCol, nLogRow, nLogCol;
			HitTest(point, &nRow, &nCol);

			GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
			if(nLogCol == GX_INVALID)
				nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
			
			WORD w = (WORD) (m_nHitState | GX_HITEND);
			if (nLogRow == m_nHitRow && nLogCol == m_nHitCol)
				w |= GX_HITINCELL;
			else if (m_dwLastMoveRow == nAbsHitRow && m_dwLastMoveCol == nAbsHitCol)
				w |= GX_HITLEAVE;

			// it is important to use min(GetRowCount(), nRow) because
			// HitTest returns nRow+1 if user released the mouse button
			// outside the grid.

			OnLButtonHitRowCol(nAbsHitRow, nAbsHitCol, min(GetRowCount(), nRow), min(GetColCount(), nCol), point, flags, w);

			// reset semaphor for "hit-mode"

			m_nHitState = 0;
		}

		else if (m_pUserResizeCellsImp
			&& m_pUserResizeCellsImp->OnLButtonUp(this, point, flags))
			return TRUE;

	}
	CATCH(CException, e)
	{
		m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
	}
	END_CATCH
		
	return TRUE;
}

template<class T>
void CGXWrappedGrid<T>::SelectRangeImp_OnLButtonUp(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags)
{
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);

	CGXRangeList* pSelList = pGrid->GetParam()->GetRangeList();

	if (pGrid->m_pParam->IsEnableSelection(GX_SELFULL)
		&& pGrid->m_nHitState & GX_SELECT
		&& (pGrid->m_dwButtonDownCol != 0 || pGrid->m_dwButtonDownRow != 0))
	{
		if (pGrid->m_dwButtonDownCol == pGrid->m_dwLastMoveCol
			&& pGrid->m_dwButtonDownRow == pGrid->m_dwLastMoveRow
			&& pGrid->m_dwButtonDownRow > 0 && pGrid->m_dwButtonDownCol > 0)
		{
			if (pGrid->m_nHitState & GX_CTRLPRESSED)
			{
				// allow programmer to change the range
				if (pGrid->m_SelRectId && pGrid->CanChangeSelection(pSelList->GetAt(pGrid->m_SelRectId), FALSE, FALSE))
				{
					// User pressed ctrl-key. I do select the current cell
					pGrid->SetSelection(pGrid->m_SelRectId,
						pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol,
						pGrid->m_dwButtonDownRow, pGrid->m_dwButtonDownCol);

					// trigger OnChangedSelection event
					pGrid->OnChangedSelection(pGrid->m_SelRectId?pSelList->GetAt(pGrid->m_SelRectId):NULL, FALSE, FALSE);
				}
			}
			else
			{
				// User did move the current cell but didn't select any cells.
				// EXCELCURCELL
				if (!pGrid->GetParam()->GetExcelLikeCurrentCell())
				{
					pGrid->SetSelection(NULL);
					/*
					PrepareClearSelection(TRUE);
					m_SelRectId = NULL;
					if (!pSelList->IsEmpty())
						pSelList->DeleteTail();
					*/
				}
				pGrid->m_nHitState &= (WORD) ~GX_SELECT;
			}
		}
		else
		{
			// trigger OnChangedSelection event to let user know that selection
			// ended.
			if (pGrid->m_SelRectId)
				pGrid->OnChangedSelection(pSelList->GetAt(pGrid->m_SelRectId), FALSE, FALSE);
			else
				pGrid->OnChangedSelection(NULL, FALSE, FALSE);

			pGrid->m_nHitState &= (WORD) ~GX_SELECT;
		}
	}
}

template<class T>
void CGXWrappedGrid<T>::DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem)
{
	// Invert cell (selected cells)

	// Don't invert current cell when m_bInvertRect is FALSE. SetCurrentCell
	// will set m_bInvertRect = FALSE

	CGXRange rgCov;
	if(GetCoveredCellsRowCol(nRow, nCol, rgCov))
	{
		nRow = rgCov.top;
		nCol = rgCov.left;
	}

	BOOL bCCell = IsCurrentCell(nRow, nCol);

	if (!bCCell || m_bInvertRect || m_pParam->GetHideCurrentCell() == GX_HIDE_ALWAYS)
		pDC->InvertRect(&rectItem);

	if (bCCell && GetParam()->GetExcelLikeCurrentCell())
	{
		// TRACE(_T("m_bExcelLikeCurrentCell\n"));
		CRect r = rectItem;

		if (GetParam()->GetNewGridLineMode())
		{
			pDC->InvertRect(CRect(r.left, r.top, r.right, r.top+2));
			pDC->InvertRect(CRect(r.left, r.top+2, r.left+2, r.bottom));
			pDC->InvertRect(CRect(r.right-3, r.top+2, r.right, r.bottom-3));
			pDC->InvertRect(CRect(r.left+2, r.bottom-3, r.right, r.bottom));
		}
		else
		{
			pDC->InvertRect(CRect(r.left, r.top, r.right-2, r.top+3));
			pDC->InvertRect(CRect(r.left, r.top+3, r.left+3, r.bottom-2));
			pDC->InvertRect(CRect(r.left, r.bottom-2, r.right-2, r.bottom));
			pDC->InvertRect(CRect(r.right-2, r.top, r.right, r.bottom));
		}
	}

	m_bInvertRect = FALSE;
}

#endif//_GXWGSEL_H_
