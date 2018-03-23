///////////////////////////////////////////////////////////////////////////////
// gxwgseldrg.h
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

#ifndef _GXWGSELDRG_H_
#define _GXWGSELDRG_H_

template<class T>
BOOL CGXWrappedGrid<T>::UserDragSelectRangeImp_OnLButtonDown(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	GX_UNUSED_ALWAYS(ht);
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);

	ROWCOL nLogRow, nLogCol;
	GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogCol == GX_INVALID)
		nLogCol = nCol <= (ROWCOL)m_patternMap->GetRowHeaderWidth() ? 0 : nLogCol;
	if(nLogCol == GX_INVALID)
		return FALSE;

	// Some useful attributes
	CGXRangeList* pSelList = pGrid->GetParam()->GetRangeList();
	ROWCOL nhRow = pGrid->GetHeaderRows();
	ROWCOL nhCol = pGrid->GetHeaderCols();
	BOOL bSel = pSelList->IsCellInList(nLogRow, nLogCol);
	BOOL bTable = pSelList->IsCellInList(0, 0);
	BOOL bSelCol = nRow <= nhRow && nCol > nhCol && pSelList->IsCellInList(0, nLogCol);
	BOOL bSelRow = nCol <= nhCol && nRow > nhRow && pSelList->IsCellInList(nLogRow, 0);

	// If the user hit a selected row or column,
	// the grid is changed to dragging-mode.
	//
	// The programmer can inhibit this bahviour by specifying
	// GetParam()->EnableMoveCols(FALSE) and GetParam()->EnableMoveRows(FALSE)
	//
	// When dragging, there will be no calls to OnLButtonHitRowCol.
	//
	if (!bTable && bSel && bSelCol && pGrid->m_pParam->IsEnableMoveCols()
		|| !bTable && bSel && bSelRow && pGrid->m_pParam->IsEnableMoveRows())
	{
		// start dragging

		// OnSelDragStart can be overriden by the programmer
		// for changing the default behaviour
		//
		// If OnSelDragStart returns FALSE, dragging-mode is canceled
		//
		pGrid->m_bSelDrag = TRUE;

		if (pGrid->OnSelDragStart(bSelRow ? nLogRow : 0, bSelCol ? nLogCol : 0))
		{
			// Check if programmer has called GetCapture
			if (pGrid->GetCapture() != pGrid->m_pGridWnd && pGrid->m_bSelDrag)
			{
				// No, I do initialize it myself (default processing)
				if (pGrid->m_bAutoScroll)
					// I am using AutoScroll until WM_LBUTTONUP Message
					pGrid->AutoScroll(FALSE,
						bSelRow && !pGrid->IsFrozenRow(nRow),
						bSelCol && !pGrid->IsFrozenCol(nCol));

				pGrid->SetCapture();
			}

			return TRUE;
		}
		else
		{
			pGrid->m_nSelDragMode = 0;
			pGrid->m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
		}

		// Fall through !!!
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::OnSelDragStart(ROWCOL nLogRow, ROWCOL nLogCol)
{
	m_nSelDragRow = max(nLogRow, 1);
	m_nSelDragCol = max(nLogCol, 1);
	m_bCurInsertToTheRight = FALSE;

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	// find the Selection Rectangle
	POSITION posRect = pSelList->FindRange(nLogRow, nLogCol);
	ASSERT(posRect);

	CGXRange* pRange = pSelList->GetAt(posRect);

	// trigger selection dragging event
	// the programmer can override OnSelDragRowsStart / OnSelDragColsStart.
	// if the methods returns FALSE, dragging will not be processed

	if (nLogRow > 0)
	{
		m_nSelDragMode = GX_SELDRAG_ROW;

		if (!OnSelDragRowsStart(pRange->top, pRange->bottom))
			return FALSE;
	}
	else if (nLogCol > 0)
	{
		m_nSelDragMode = GX_SELDRAG_COL;

		if (!OnSelDragColsStart(pRange->left, pRange->right))
			return FALSE;
	}
	else
		return FALSE;

	m_SelRectId = posRect;

	// Set Cursor
	SetGridCursor(GX_IDC_SELDRAG);

	m_bLockEvalFloatCells = TRUE;
	m_bLockEvalMergeCells = TRUE;

	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::UserDragSelectRangeImp_OnMouseMove(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags)
{
	GX_UNUSED_ALWAYS(flags);
	ROWCOL nLogRow, nLogCol;

	m_bInsertToTheRight = FALSE;
	if (pGrid->m_bSelDrag)
	{
		// I am currently moving cells or columns
		ROWCOL nRow, nCol;
		nRow = pGrid->CalcClientRowFromPt(point);
		nRow = (nRow == GX_INVALID) ? pGrid->GetRowCount()+1 : pGrid->GetRow(max(nRow, 1));
		if (pGrid->m_nSelDragMode == GX_SELDRAG_ROW)
		{
			nLogRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
			nLogCol = 0;
			nCol = 0;
		}
		else
		{
			nCol = pGrid->CalcClientColFromPt(point);
			// Calculate the rect of the right most cell.
			BOOL bDummy;
			ROWCOL nRightCol = pGrid->CalcRightColFromRect(GetGridRect(), bDummy);
			// If moving below the headers?
			if(point.y > pGrid->CalcRectFromRowCol(m_patternMap->GetRowSpan()-1, nRightCol).BottomRight().y)
			{
				// Then create a new row below the last wrapped row.
				pGrid->OnSelDragMove(pGrid->m_nSelDragRow, pGrid->m_nSelDragCol, 0, m_patternMap->GetColCount()+1);	// colcount+1 indicates new wrapped row.
				return TRUE;
			}

			CRect rRightMostCell;
			rRightMostCell = pGrid->CalcRectFromRowCol(nRow, nRightCol);
			// If invalid, Is it to the right of the grid?
			if(nCol == GX_INVALID && point.x > rRightMostCell.BottomRight().x)
			{
				// Hint that the cols have to be moved to the right.
				m_bInsertToTheRight = TRUE;
				point.x = rRightMostCell.BottomRight().x;	// Reset it to a valid point.
				nCol = nRightCol;
			}
			else if(nCol != GX_INVALID)
				nCol = pGrid->GetCol(max(nCol, 1));

			if(nCol != GX_INVALID)
			{
				ROWCOL nDummyRow;
				GetLogCellFromAbsCell(nRow, nCol, nDummyRow, nLogCol);
				if(nLogCol == GX_INVALID)	// If to the right of the row, then set nLogCol to the right-most cell in the row.
				{
					nRow = min(nRow, m_patternMap->GetRowSpan());
					nLogCol = m_patternMap->GetRowBreaks()->GetAt((nRow-1)/2)+1;
					m_bInsertToTheRight = TRUE;
				}
			}
			else 
				nLogCol = GX_INVALID;
//			if(nLogCol == GX_INVALID)
//				return TRUE;
			nLogRow = 0;
			nRow = 0;
		}

		// OnSelDragMove can be overriden by the programmer
		// for changing the default behaviour

		pGrid->OnSelDragMove(pGrid->m_nSelDragRow, pGrid->m_nSelDragCol, nLogRow, nLogCol);

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::OnSelDragMove(ROWCOL nLogRow1, ROWCOL nLogCol1, ROWCOL nLogRow, ROWCOL nLogCol)
{
	GX_UNUSED_ALWAYS(nLogCol1);
	GX_UNUSED_ALWAYS(nLogRow1);

	CGXRange* pRange = GetParam()->GetRangeList()->GetAt(m_SelRectId);

	nLogCol = max(1, nLogCol);
	nLogRow = max(1, nLogRow);

	CRect rectGrid = GetGridRect();

	// check, if nothing changed
	if (m_nSelDragMode == GX_SELDRAG_ROW && nLogRow == m_nSelDragRow
		|| m_nSelDragMode == GX_SELDRAG_COL && nLogCol == m_nSelDragCol && m_bInsertToTheRight == m_bCurInsertToTheRight)
		return TRUE;

	// hide dragging line
	if (m_pWndDrag != NULL)
		m_pWndDrag->ShowWindow(SW_HIDE);

	m_nSelDragRow = nLogRow;
	m_nSelDragCol = nLogCol;
	m_bCurInsertToTheRight = m_bInsertToTheRight;

	// trigger selection dragging event
	// the programmer can override OnSelDragRowsMove / OnSelDragColsMove.
	// if the method return FALSE, dragging will not be processed

	if (m_nSelDragMode == GX_SELDRAG_ROW
			&& !OnSelDragRowsMove(pRange->top, pRange->bottom, nLogRow)
		|| m_nSelDragMode == GX_SELDRAG_COL
			&& !OnSelDragColsMove(pRange->left, pRange->right, nLogCol))
	{
		SetGridCursor(GX_IDC_NODROPCRSR);
		return TRUE;
	}

	// Set Cursor
	SetGridCursor(GX_IDC_SELDRAG);

	ASSERT(m_nSelDragRow > 0 && m_nSelDragCol > 0);

	UpdateWindow();

	{
		// Create drag line
		if (m_pWndDrag == NULL)
		{
			m_pWndDrag = new CGXDragLineWnd(this);
			m_pWndDrag->CreateWnd(m_pGridWnd);
			m_pWndDrag->m_pen
				.SetStyle(PS_SOLID)
				.SetWidth(1)
				.SetColor(GetParam()->GetProperties()->GetColor(gxnPropDraggingLines));
		}

		ROWCOL nAbsRow, nAbsCol;
		
		// Move the drag line
		CRect rect;
		if (m_nSelDragMode == GX_SELDRAG_ROW)
		{
			nAbsRow = m_nSelDragRow * m_patternMap->GetRowSpan();
			rect = CalcGridLineRect(GX_HORZLINE, GetClientRow(nAbsRow));
		}
		else
		{
			// If move to the bottom of the header, creating a new wrapped-row
			if(m_nSelDragCol > (ROWCOL)m_patternMap->GetColCount())
			{
				rect = CalcRectFromRowColExEx(m_patternMap->GetRowSpan()-1, m_patternMap->GetRowHeaderWidth()+m_patternMap->m_nPMButtonCellWidth+1, m_patternMap->GetRowSpan()-1, GetColCount());
				rect.SetRect(rect.TopLeft().x, rect.BottomRight().y, rect.BottomRight().x, rect.BottomRight().y+1);
			}
			else	// Move to the right or left of a col.
			{
				GetAbsCellFromLogCell(0, m_nSelDragCol, nAbsRow, nAbsCol);
				rect = CalcRectFromRowColExEx(nAbsRow, nAbsCol);
				if(m_bCurInsertToTheRight == FALSE)
					rect.SetRect(rect.TopLeft().x, rect.TopLeft().y, rect.TopLeft().x+1, rect.BottomRight().y);
				else
					rect.SetRect(rect.BottomRight().x, rect.TopLeft().y, rect.BottomRight().x+1, rect.BottomRight().y);
	//			rect = CalcGridLineRect(GX_VERTLINE, GetClientCol(nAbsCol));
			}
		}

		m_pWndDrag->MoveWindow(rect);
		m_pWndDrag->ShowWindow(SW_SHOW);
		m_pWndDrag->UpdateWindow();
	}

	return TRUE;
}


template<class T>
BOOL CGXWrappedGrid<T>::UserDragSelectRangeImp_OnLButtonUp(CGXWrappedGrid<T>* pGrid, CPoint& point, UINT& flags)
{
	GX_UNUSED_ALWAYS(flags);
	ROWCOL nLogRow, nLogCol;

	if (pGrid->m_bSelDrag)
	{
		// Release Mouse Capture
		if (pGrid->m_pGridWnd->GetCapture() == pGrid->m_pGridWnd)
			ReleaseCapture();

		// User is dragging Rows or colums
		ROWCOL    nRow, nCol;
		nRow = pGrid->CalcClientRowFromPt(point);
		nRow = (nRow == GX_INVALID) ? pGrid->GetRowCount()+1 : pGrid->GetRow(max(nRow, 1));

		if (pGrid->m_nSelDragMode == GX_SELDRAG_ROW)
		{
			ROWCOL nTopMostValidRow = m_patternMap->GetRowSpan() + 1;
			nRow = (nRow == GX_INVALID) ? pGrid->GetRowCount()+1 : pGrid->GetRow(max(nRow, nTopMostValidRow));
			nLogRow = (ROWCOL)((nRow-1)/m_patternMap->GetRowSpan()) + 1 - m_patternMap->m_bIsHeaders;
			nLogCol = 0;
			nCol = 0;
		}
		else
		{
			ROWCOL nLeftMostValidCol = m_patternMap->GetRowHeaderWidth() + m_patternMap->m_nPMButtonCellWidth + 1;
			nCol = pGrid->CalcClientColFromPt(point);

			// Calculate the rect of the right most cell.
			BOOL bDummy;
			ROWCOL nRightCol = pGrid->CalcRightColFromRect(GetGridRect(), bDummy);
			// If moving below the headers?
			if(point.y > pGrid->CalcRectFromRowCol(m_patternMap->GetRowSpan()-1, nRightCol).BottomRight().y)
			{
				// Then create a new row below the last wrapped row.
				CGXRange* pRange = pGrid->GetParam()->GetRangeList()->GetAt(pGrid->m_SelRectId);
				pGrid->OnSelDragDrop(pRange->top, pRange->left, 0, m_patternMap->GetColCount()+1);	// colcount+1 indicates new wrapped row.
				pGrid->m_bSelDrag = FALSE;
				return TRUE;
			}

			CRect rRightMostCell;
			rRightMostCell = pGrid->CalcRectFromRowCol(nRow, nRightCol);
			// If invalid, Is it to the right of the grid?
			if(nCol == GX_INVALID && point.x > rRightMostCell.BottomRight().x)
			{
				// Hint that the cols have to be moved to the right.
				m_bInsertToTheRight = TRUE;
				point.x = rRightMostCell.BottomRight().x;	// Reset it to a valid point.
				nCol = nRightCol;
			}
			else if(nCol != GX_INVALID)
				nCol = pGrid->GetCol(max(nCol, nLeftMostValidCol));
			
			if(nCol != GX_INVALID)
			{
				ROWCOL nDummyRow;
				GetLogCellFromAbsCell(nRow, nCol, nDummyRow, nLogCol);
				if(nLogCol == GX_INVALID)	// If to the right of the row, then set nLogCol to the right-most cell in the row.
				{
					nRow = min(nRow, m_patternMap->GetRowSpan());
					nLogCol = m_patternMap->GetRowBreaks()->GetAt((nRow-1)/2)+1;
					m_bInsertToTheRight = TRUE;
				}
			}
			else 
				nLogCol = GX_INVALID;

			nLogRow = 0;
			nRow = 0;
		}

		// OnSelDragDrop can be overriden by the programmer
		// for changing the default behaviour.
		//
		// The base class version will call MoveRows or MoveCols.

		CGXRange* pRange = pGrid->GetParam()->GetRangeList()->GetAt(pGrid->m_SelRectId);

		pGrid->OnSelDragDrop(pRange->top, pRange->left, nLogRow, nLogCol);

		pGrid->m_bSelDrag = FALSE;

		return TRUE;
	}

	return FALSE;
}

template<class T>
BOOL CGXWrappedGrid<T>::OnSelDragDrop(ROWCOL nLogRow1, ROWCOL nLogCol1, ROWCOL nLogRow, ROWCOL nLogCol)
{
	GX_UNUSED_ALWAYS(nLogCol1);
	GX_UNUSED_ALWAYS(nLogRow1);

	m_bLockEvalFloatCells = FALSE;
	m_bLockEvalMergeCells = FALSE;

	SetGridCursor(0);

	CRect rectGrid = GetGridRect();

	if (m_nSelDragMode == GX_SELDRAG_ROW && nLogRow == 0)
		return FALSE;

	if (m_nSelDragMode == GX_SELDRAG_COL && nLogCol == 0)
		return FALSE;

	nLogCol = max(1, nLogCol);
	nLogRow = max(1, nLogRow);

	// Reset Drag Line
	if (m_pWndDrag)
	{
		m_pWndDrag->DestroyWindow();
		delete m_pWndDrag;
		m_pWndDrag = NULL;
	}

	// trigger selection dragging event
	// the programmer can override OnSelDragRowsMove / OnSelDragColsMove.
	// if the methods returns FALSE, dragging will not be processed

	CGXRange* pRange = GetParam()->GetRangeList()->GetAt(m_SelRectId);

	if (m_nSelDragMode == GX_SELDRAG_ROW
			&& (!OnSelDragRowsMove(pRange->top, pRange->bottom, nLogRow)
			|| !OnSelDragRowsDrop(pRange->top, pRange->bottom, nLogRow))
		|| m_nSelDragMode == GX_SELDRAG_COL
			&& (!OnSelDragColsMove(pRange->left, pRange->right, nLogCol)
			|| !OnSelDragColsDrop(pRange->left, pRange->right, nLogCol)))
	{
		return FALSE;
	}

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	m_nSelDragRow = max(nLogRow, 1);
	m_nSelDragCol = max(nLogCol, 1);
	CGXRange* r = pSelList->GetAt(m_SelRectId);

	if (r->IsCellInRange(m_nSelDragRow, m_nSelDragCol)
		// If m_nSelDragCol == colCount+1 then don't bother validating drop.
		|| ((m_nSelDragCol != (ROWCOL)m_patternMap->GetColCount()+1) && r->IsCellInRange(max(m_nSelDragRow,1)-1, max(m_nSelDragCol,1)-(!m_bCurInsertToTheRight))))
		return FALSE;

	if (m_nSelDragMode == GX_SELDRAG_ROW)
		MoveWGRows(r->top, r->bottom, m_nSelDragRow > r->top ? m_nSelDragRow - r->GetHeight() : m_nSelDragRow);
	else
	{
		ROWCOL nFromCol = r->left;
		ROWCOL nToCol = r->right;
		// If move to the bottom of the header, creating a new wrapped-row
		if(m_nSelDragCol == (ROWCOL)m_patternMap->GetColCount() + 1)
			MoveWGCols(nFromCol, nToCol, m_nSelDragCol);
		else
		{
			ROWCOL nDestCol = m_nSelDragCol > r->left ? m_nSelDragCol - r->GetWidth() : m_nSelDragCol;
			MoveWGCols(nFromCol, nToCol, nDestCol, m_bCurInsertToTheRight);
	//		MoveWGCols(r->left, r->right, m_nSelDragCol);
		}
	}

	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::OnSelDragColsMove(ROWCOL /*nFirstCol*/, ROWCOL /*nLastCol*/, ROWCOL nDestCol)
{
	if(nDestCol == GX_INVALID)
		return FALSE;
	return TRUE;
}

template<class T>
BOOL CGXWrappedGrid<T>::OnSelDragRowsMove(ROWCOL /*nFirstRow*/, ROWCOL /*nLastRow*/, ROWCOL nDestRow)
{
	if(nDestRow == 0 || nDestRow == GX_INVALID)
		return FALSE;
	return TRUE;
}

#endif//_GXWGSELDRG_H_
