///////////////////////////////////////////////////////////////////////////////
// gxhgprint.h
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

#ifndef _GXHGPRINT_H_
#define _GXHGPRINT_H_

#include "gxhiergrid.h"

template<class T>
void CGXHierarchyGrid<T>::OnGridBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
	// For some grids, the row or column count is not known in advance. 
	// (e.g. a CRecordSet query only knows the exact record count only 
	// when the cursor has been moved after the last record).

	// Printing works fine even if the record count is not
	// known. While printing the pages or stepping through
	// the pages with print preview the record count will
	// automatically adjusted until the last record in the
	// recordset has been seen.

	// However, if you want to print the page count in the footer
	// in your print outs, OnTestGridDimension should be called.
	// With the m_nPrintHandleRecordCount you can specify if
	// you need to know the page count
	// a) gxCountPrint - Only when printing but not for print preview (default)
	// b) gxCountAlways - Both for printing and print preview 
	// c) gxCountNever - Never

	if(!m_gridParent)
	{
		switch (m_nPrintHandleRecordCount)
		{
		case gxCountAlways: 
			OnTestGridDimension(GX_MAXROWCOL, GX_MAXROWCOL); 
			break;

		case gxCountPrint: 
			if (!pInfo->m_bPreview)
				 OnTestGridDimension(GX_MAXROWCOL, GX_MAXROWCOL); 
			break;

		default:
			;
			// no count
		}
	}

	CGXGridParam* pParam = GetParam();
	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXGridParam)));

	CGXProperties* pProp = pParam->GetProperties();
	ASSERT(pProp->IsKindOf(RUNTIME_CLASS(CGXProperties)));

	// Check for custom page breaks
	CDWordArray& awRowBreaks = pProp->GetRowBreakArray();
	CDWordArray& awColBreaks = pProp->GetColBreakArray();
	
	BOOL bCustCols =  awColBreaks.GetSize();
	BOOL bCustRows =  awRowBreaks.GetSize(); 

	// for custom page breaks
	int nArrIndex = 0;
	int nArrColIndex = 0;

	if(!m_gridParent)
	{
		CGXWaitCursor theWait;

		OnGridPrepareDC(pDC, pInfo);
	}

	m_awPageFirstRow.RemoveAll();
	m_awPageFirstCol.RemoveAll();

	// TRACE0("CGXGridPrintImp::OnBeginPrinting()\n");

	CFont* pOldFont = NULL;

	ROWCOL      nCurRow = GetTopRow(),
				nCurCol = GetLeftCol();

	m_bPrintPaintMsg = FALSE;

	// Let only the top-level grid set the printing flag, it will recursiviely call the children.
	if(!m_gridParent)
		SetPrinting(TRUE);

	// Float Cells
/*	CGXAppData* pApp = GXGetAppData();
	CGXAbstractDelayedRangePoolImp* pDelayPool = (CGXAbstractDelayedRangePoolImp*) pApp->m_pDelayedRangePoolImp;
	CGXAbstractSpanCellPoolImp* pSpanPool = (CGXAbstractSpanCellPoolImp*) pApp->m_pSpanCellPoolImp;

	if (pSpanPool && pParam->m_pPrintFloatCells == NULL)
		pParam->m_pPrintFloatCells = pSpanPool->CreateSpanCellPool();

	if (pDelayPool && pParam->m_pDelayedPrintFloatCells == NULL)
		pParam->m_pDelayedPrintFloatCells = pDelayPool->CreateDelayedRangePool();

	DelayFloatCells(CGXRange().SetTable());
*/

	TRY
	{
		// Free all cached fonts, pens, brushes and styles
		FreeObjectCache();

		// select default font into device context
		pOldFont = LoadFont(pDC, StandardStyle());

		// Default font metrics
		GetFontMetrics(pDC, m_dxPrintWidth, m_dyPrintHeight);
		GetChildFontMetrics(pDC);

		if(!m_gridParent)
		{
			// Get rectangle to be drawn
			pInfo->m_rectDraw.SetRect(0, 0, pDC->GetDeviceCaps(HORZRES),
									  pDC->GetDeviceCaps(VERTRES));
			pDC->DPtoLP(&pInfo->m_rectDraw);
			OnAdjustPrintRectangle(pDC, pInfo);
		}

		// m_rectPrint gets returned by GetGridRect() while m_bPrintInProgress is TRUE
		m_rectPrint = pInfo->m_rectDraw;
		CRect rectGrid = GetGridRect();

		// compute page breaks

		CGXRangeList* pSelList = pParam->GetRangeList();

		BOOL bCurPageOnly = pInfo->m_pPD->PrintSelection() && pSelList->GetCount() == 0;
		BOOL bCurSelOnly = pInfo->m_pPD->PrintSelection() && pSelList->GetCount() > 0;

/*		if (bCurPageOnly)
		{
			ROWCOL      bottomRow,
						rightCol;

			// just use top left cell
			m_nPrintTopRow = m_nTopRow;
			m_nPrintLeftCol = m_nLeftCol;
			m_awPageFirstCol.SetAtGrow(0, m_nPrintLeftCol);
			m_awPageFirstRow.SetAtGrow(0, m_nPrintTopRow);

			// ... and calculate boottom right cell
			rightCol = CalcClientColFromPt(rectGrid.BottomRight());
			ROWCOL nCol = (rightCol == GX_INVALID)
				? GetColCount()
				: GetCol(rightCol);

			bottomRow = CalcClientRowFromPt(rectGrid.BottomRight());
			ROWCOL nRow = (bottomRow == GX_INVALID)
				? GetRowCount()
				: GetRow(bottomRow);

			m_awPageFirstCol.SetAtGrow(1, nCol);
			m_awPageFirstRow.SetAtGrow(1, nRow);
			pInfo->SetMaxPage(1);
		}
		else
*/
		{

			CGXRange rangePrint;

			// ExpandRange is necessary if user wants to
			// print selected rows or columns
/*			if (bCurSelOnly)
				rangePrint = *pSelList->GetTail();
			else
*/
				rangePrint.SetTable();

			rangePrint.ExpandRange(
					GetFrozenRows()+1,
					GetFrozenCols()+1,
					GetRowCount(),
					GetColCount());

			ROWCOL      bottomRow,
						rightCol;
			int         index;

			// I must take care of frozen rows and columns
			m_nPrintTopRow = max(GetFrozenRows()+1, rangePrint.top);
			m_nPrintLeftCol = max(GetFrozenCols()+1, rangePrint.left);
			m_bPrintCurSelOnly = bCurSelOnly; 
			m_awPageFirstCol.SetAtGrow(0, m_nPrintLeftCol);
			m_nCurrentPageColIndex = 0;
			m_nCurrentPageRowIndex = 0;

			// compute left column for each page
			BOOL bCustPageColInit(FALSE);
			
			// Here for col
/*			if(bCustCols && (CalcClientColFromPt(rectGrid.BottomRight())) == GX_INVALID)		
			{
				HandleSinglePageColHelper(this, awColBreaks, rightCol, 0, rangePrint);
				bCustPageColInit = TRUE;
			}
*/
			
			for (index = 1;
				(rightCol = CalcClientColFromPt(rectGrid.BottomRight())) != GX_INVALID;
				index++)
			{
				ROWCOL nCol = max(GetCol(rightCol), m_nPrintLeftCol+1);
				if (nCurCol < nCol && nCurCol >= m_nPrintLeftCol)
					m_nCurrentPageColIndex = index-1;
				
				ASSERT(bCustPageColInit == FALSE);
				
				// Check if can put our break in. Our break will have to
				// wait if it is higher than the grid calculated break
				// We cannot force the grid to print more columns on one page
				// than it normally will
				if (nArrColIndex <= awColBreaks.GetUpperBound() && awColBreaks[nArrColIndex] < nCol )
				{
					nCol = awColBreaks[nArrColIndex];
					nArrColIndex++;
				}

				m_awPageFirstCol.SetAtGrow(index, nCol);
				if (nCol > rangePrint.right)
				{
					rightCol = GX_INVALID;
					break;
				}
				m_nPrintLeftCol = nCol;

/*				if(bCustCols && (CalcClientColFromPt(rectGrid.BottomRight())) == GX_INVALID)
				{
					HandleSinglePageColHelper(this, awColBreaks, rightCol, nArrColIndex, rangePrint);
					bCustPageColInit = TRUE;
				}
*/

			}
			
			if(!bCustPageColInit)
				m_awPageFirstCol.SetAtGrow(index, (rightCol == GX_INVALID)
					? rangePrint.right+1
					: GetCol(rightCol));

			m_nPrintTopRow = max(GetFrozenRows()+1, rangePrint.top);
			m_nPrintLeftCol = max(GetFrozenCols()+1, rangePrint.left);
			m_awPageFirstRow.SetAtGrow(0, m_nPrintTopRow);

			ROWCOL nMaxChildPageCount=0;

			if(!m_gridParent)
			{
				nMaxChildPageCount = GetMaxChildPageSpanInCurrentRowRange(pDC, pInfo);
				//m_dwChildPageSpan.SetAtGrow(0, nMaxChildPageCount);
			}

			// compute top row for each page
			BOOL bCustPageRowInit(FALSE);
/*			if(bCustRows && (bottomRow = CalcClientRowFromPt(rectGrid.BottomRight())) == GX_INVALID)
				// here for row
			{
				HandleSinglePageRowHelper(this, awRowBreaks, bottomRow, 0, rangePrint);
				bCustPageRowInit = TRUE;
			}
*/
//			int nAdditionalPagesForChildren = 0;

			for (index = 1;
				(bottomRow = CalcClientRowFromPt(rectGrid.BottomRight())) != GX_INVALID;
				index++)
			{
				ROWCOL nRow = max(GetRow(bottomRow), m_nPrintTopRow+1);
				if (nCurRow < nRow && nCurRow >= m_nPrintTopRow)
					m_nCurrentPageRowIndex = index-1;
				
				ASSERT(bCustPageRowInit == FALSE);

				// Check if can put our break in. Our break will have to
				// wait if it is higher than the grid calculated break
				// We cannot force the grid to print more rows on one page
				// than it normally will
				if (nArrIndex <= awRowBreaks.GetUpperBound() && awRowBreaks[nArrIndex] < nRow )
				{
					nRow = awRowBreaks[nArrIndex];
					nArrIndex++;
				}

				m_awPageFirstRow.SetAtGrow(index, nRow);

				m_nPrintTopRow = nRow;

				if(!m_gridParent)
				{
					ROWCOL nTempMaxChildPageCount=0;
					nTempMaxChildPageCount = GetMaxChildPageSpanInCurrentRowRange(pDC, pInfo);
					nMaxChildPageCount = max(nMaxChildPageCount, nTempMaxChildPageCount);
					// Store the MaxChildPageCounts in an array.
					//m_dwChildPageSpan.SetAtGrow(index-1, nTempMaxChildPageCount);
				}

				if (nRow > rangePrint.bottom)
				{
					bottomRow = GX_INVALID;
					break;
				}
			
/*				if(bCustRows && (bottomRow = CalcClientRowFromPt(rectGrid.BottomRight())) == GX_INVALID)
				{
					HandleSinglePageRowHelper(this, awRowBreaks, bottomRow, nArrIndex, rangePrint);
					bCustPageRowInit = TRUE;
				}
*/
			}

			if(!m_gridParent)
			{
				while(nMaxChildPageCount > (ROWCOL)m_awPageFirstCol.GetSize()-1)
				{
#ifdef _WIN64 //RW64
					INT_PTR nCurSize = m_awPageFirstCol.GetSize();
#else
					int nCurSize = m_awPageFirstCol.GetSize();
#endif //_WIN64
					m_awPageFirstCol.InsertAt(nCurSize-1, m_awPageFirstCol.GetAt(nCurSize-1)-1, nMaxChildPageCount - nCurSize + 1);
				}
			}

			if(!bCustPageRowInit)
			{
				m_awPageFirstRow.SetAtGrow(index, (bottomRow == GX_INVALID)
				? rangePrint.bottom+1
				: GetRow(bottomRow));
			}

			// set no of pages
#ifdef _WIN64 //RW64
			pInfo->SetMaxPage(static_cast<UINT>((m_awPageFirstRow.GetSize()-1)*(m_awPageFirstCol.GetSize()-1)) /*+ nAdditionalPagesForChildren*/);
#else
			pInfo->SetMaxPage((m_awPageFirstRow.GetSize()-1)*(m_awPageFirstCol.GetSize()-1) /*+ nAdditionalPagesForChildren*/);
#endif //_WIN64

			// page string gets displayed in the status line of the print preview
			CString s;
			wsprintf(s.GetBuffer(10), _T(" / %u"), pInfo->GetMaxPage());
			s.ReleaseBuffer();
			pInfo->m_strPageDesc += s;

			if (pInfo->m_bPreview)
			{
				if (pProp->GetPageOrder() == 0)
				{
#ifdef _WIN64 //RW64
					pInfo->m_nCurPage = static_cast<UINT>(m_nCurrentPageRowIndex*(m_awPageFirstCol.GetSize()-1) + m_nCurrentPageColIndex + 1);
#else
					pInfo->m_nCurPage = m_nCurrentPageRowIndex*(m_awPageFirstCol.GetSize()-1) + m_nCurrentPageColIndex + 1;
#endif //_WIN64
				}else
				{
#ifdef _WIN64 //RW64
					pInfo->m_nCurPage = static_cast<UINT>(m_nCurrentPageColIndex*(m_awPageFirstRow.GetSize()-1) + m_nCurrentPageRowIndex + 1);
#else
					pInfo->m_nCurPage = m_nCurrentPageColIndex*(m_awPageFirstRow.GetSize()-1) + m_nCurrentPageRowIndex + 1;
#endif //_WIN64
				}
			}
		}

		// restore old font
		if (pOldFont)
			pDC->SelectObject(pOldFont);

		// Reset printing mode
		// Let only the top-level grid set the printing flag, it will recursiviely call the children.
		if(!m_gridParent)
			SetPrinting(FALSE);
	}
	CATCH_ALL(e)
	{
		// restore old font
		if (pOldFont)
			pDC->SelectObject(pOldFont);

		// Reset printing mode
		// Let only the top-level grid set the printing flag, it will recursiviely call the children.
		if(!m_gridParent)
			SetPrinting(FALSE);

		THROW_LAST();
	}
	END_CATCH_ALL
}

template<class T>
void CGXHierarchyGrid<T>::OnGridPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CGXGridParam* pParam = GetParam();
	CGXProperties* pProp = pParam->GetProperties();

	ROWCOL      bottomRow,
				rightCol;

	// TRACE1("CGXGridCore: OnPrint(%u)\n", pInfo->m_nCurPage);

	m_bPrintPaintMsg = FALSE;
	// Let only the top-level grid set the printing flag, it will recursiviely call the children.
	if(!m_gridParent)
		SetPrinting(TRUE);

	int nDC = 0;
	HFONT hOldFont = NULL;

	TRY
	{
		// Free all cached fonts, pens, brushes and styles
		FreeObjectCache();

		// select default font into device context
		CFont* pOldFont = LoadFont(pDC, StandardStyle());

		// Get the HFONT handle because pOldFont is only a temporary CGdiObject object
		// and is only valid until the next time the application has idle time in its
		// event loop.
		hOldFont = (HFONT) pOldFont->GetSafeHandle();

		// Default font metrics
		GetFontMetrics(pDC, m_dxPrintWidth, m_dyPrintHeight);
		GetChildFontMetrics(pDC);

		// check page brak array
		if (m_awPageFirstRow.GetSize() == 0
			|| m_awPageFirstCol.GetSize() == 0)
		{
			TRACE0("Warning! You must call OnBeginPrinting and OnEndPrinting from your derived class!\n");
			ASSERT(0);
		}

		if(!m_gridParent)
		{
			OnAdjustPrintRectangle(pDC, pInfo);
			m_rectPrint = pInfo->m_rectDraw;
		}

		// page order
#ifdef _WIN64
		INT_PTR nPageRowIndex = 0;
		INT_PTR nPageColIndex = 0;
#else
		int nPageRowIndex = 0;
		int nPageColIndex = 0;
#endif //_WIN64

		// Page order
		if (pProp->GetPageOrder() == 0)
		{
			nPageRowIndex = (pInfo->m_nCurPage-1)/(m_awPageFirstCol.GetSize()-1);
			nPageColIndex = (pInfo->m_nCurPage-1)%(m_awPageFirstCol.GetSize()-1);
		}
		else
		{
			nPageRowIndex = (pInfo->m_nCurPage-1)%(m_awPageFirstRow.GetSize()-1);
			nPageColIndex = (pInfo->m_nCurPage-1)/(m_awPageFirstRow.GetSize()-1);
		}

		// top left cell
		m_nPrintTopRow = m_awPageFirstRow[nPageRowIndex];
		m_nPrintLeftCol = m_awPageFirstCol[nPageColIndex];

		CRect rectGrid = GetGridRect();

		//BOOL bAgain = FALSE;

		CGXRangeList* pSelList = pParam->GetRangeList();
		BOOL bCurPageOnly = pInfo->m_pPD->PrintSelection() && pSelList->GetCount() == 0;
		BOOL bCurSelOnly = pInfo->m_pPD->PrintSelection() && pSelList->GetCount() > 0;
/*
		if (!bCurPageOnly && !bCurSelOnly)
		{
			// All pages shall be printed ...

			//
			// Lets check if row or column count did increase. 
			OnTestGridDimension(m_nPrintTopRow+2*rectGrid.Height()/GetDefaultRowHeight(), 
				m_nPrintLeftCol+4*rectGrid.Width()/GetDefaultColWidth());

			// Row count
			if (m_awPageFirstRow[m_awPageFirstRow.GetSize()-1] <= GetRowCount())
			{
				int nPage = m_awPageFirstRow.GetSize()-2;
				m_nPrintTopRow = m_awPageFirstRow[nPage];

				bottomRow = GetClientRow(GetRowCount());

				// compute top rows for next pages
				BOOL bEOF = FALSE;
				while (!bEOF)
				{
					bottomRow = CalcBottomRowFromRect(rectGrid, bEOF);
					m_awPageFirstRow.SetAtGrow(++nPage, bottomRow + bEOF);
					m_nPrintTopRow = bottomRow+1;
				}

				bAgain = TRUE;  // check Page order again
			}

			// Column count
			if (m_awPageFirstCol[m_awPageFirstCol.GetSize()-1] <= GetColCount())
			{
				int nPage = m_awPageFirstCol.GetSize()-2;
				m_nPrintLeftCol = m_awPageFirstCol[nPage];

				rightCol = GetClientCol(GetColCount());

				// compute left cols for next pages
				BOOL bEOF = FALSE;
				while (!bEOF)
				{
					rightCol = CalcRightColFromRect(rectGrid, bEOF);
					m_awPageFirstCol.SetAtGrow(++nPage, rightCol + bEOF);
					m_nPrintLeftCol = rightCol+1;
				}

				bAgain = TRUE;  // check Page order again
			}
		}

		if (bAgain)
		{
			pInfo->SetMaxPage((m_awPageFirstRow.GetSize()-1)*(m_awPageFirstCol.GetSize()-1));

			// Page order
			if (pProp->GetPageOrder() == 0)
			{
				nPageRowIndex = (pInfo->m_nCurPage-1)/(m_awPageFirstCol.GetSize()-1);
				nPageColIndex = (pInfo->m_nCurPage-1)%(m_awPageFirstCol.GetSize()-1);
			}
			else
			{
				nPageRowIndex = (pInfo->m_nCurPage-1)%(m_awPageFirstRow.GetSize()-1);
				nPageColIndex = (pInfo->m_nCurPage-1)/(m_awPageFirstRow.GetSize()-1);
			}

			// top left cell
			m_nPrintTopRow = m_awPageFirstRow[nPageRowIndex];
			m_nPrintLeftCol = m_awPageFirstCol[nPageColIndex];
		}
		*/

		// ... and bottom right cell
		if (nPageRowIndex+1 < m_awPageFirstRow.GetSize())
			bottomRow = GetClientRow(min(GetRowCount()+1, m_awPageFirstRow[nPageRowIndex+1]))-1;
		else
			bottomRow = GetClientRow(GetRowCount());

		if (nPageColIndex+1 < m_awPageFirstCol.GetSize())
			rightCol = GetClientCol(min(GetColCount()+1, m_awPageFirstCol[nPageColIndex+1]))-1;
		else
			rightCol = GetClientCol(GetColCount());

		// compute drawing rectangle
		int x = CalcSumOfClientColWidths(0, rightCol);
		int y = CalcSumOfClientRowHeights(0, bottomRow);

		// ... and center it
//		if (pProp->GetCenterHorizontal())
//			m_rectPrint.left += (m_rectPrint.Width()-x)/2;

//		if (pProp->GetCenterVertical())
//			m_rectPrint.top += (m_rectPrint.Height()-y)/2;

		m_rectPrint.right = m_rectPrint.left + x;
		m_rectPrint.bottom = m_rectPrint.top + y;

		if(!m_gridParent)
		{
			// print header and footer
			OnPrintHeaderAndFooter(pDC, pInfo);
		}

		// draw border around grid
		if (pProp->GetPrintFrame())
		{
			if (pParam->GetNewGridLineMode())
				x--, y--;

			DrawGridLine(pDC, m_rectPrint.left-1, m_rectPrint.top-1, x+3, 2, GX_HORZLINE, 0);
			DrawGridLine(pDC, m_rectPrint.left-1, m_rectPrint.top+y, x+3, 2, GX_HORZLINE, GetRow(bottomRow)+1);
			DrawGridLine(pDC, m_rectPrint.left-1, m_rectPrint.top-1, 2, y+3, GX_VERTLINE, 0);
			DrawGridLine(pDC, m_rectPrint.left+x, m_rectPrint.top-1, 2, y+3, GX_VERTLINE, GetCol(rightCol)+1);
		}

		// clipping
		nDC = pDC->SaveDC();
		pDC->IntersectClipRect(m_rectPrint);

		// draw page
		OnDrawTopLeftBottomRight(1, 1, bottomRow, rightCol, pDC);

		if (nDC)
			pDC->RestoreDC(nDC);
		nDC = 0;

		if(!m_gridParent)
		{
			// Adjust the page info... convert from 0 based to 1 based.
			int nOldPage = pInfo->m_nCurPage;
#ifdef _WIN64 //RW64
			pInfo->m_nCurPage = static_cast<UINT>(nPageColIndex+1);
#else
			pInfo->m_nCurPage = nPageColIndex+1;
#endif //_WIN64
			// Store the oldRect
			CRect oldRect = pInfo->m_rectDraw;

			// Get the top most logical row and the bottom most logical row with the child visible.
			ROWCOL nLogTopRow, nLogBottomRow, nDummyCol;
			GetLogCellFromAbsCell(GetTopRow(), 1, nLogTopRow, nDummyCol);
			GetLogCellFromAbsCell(GetRow(bottomRow), 1, nLogBottomRow, nDummyCol);
			// If the child is not visible in the logbottomrow decrement it
			ROWCOL nChildRow, nChildCol;
			GetAbsCellContainingChild(nLogBottomRow, nChildRow, nChildCol);
			if(GetRow(bottomRow) < nChildRow)
				nLogBottomRow--;

			// loop through all the children between topRow and bottomRow.
	//		if(nPageRowIndex == 0)	// Remove this.
	//		{
			// Parse through all the children and find the max page count.
			for(ROWCOL nRowParse = nLogTopRow; nRowParse <= nLogBottomRow; nRowParse++)
			{
				if(IsChildShown(nRowParse))
				{
					GetAbsCellContainingChild(nRowParse, nChildRow, nChildCol);
					pInfo->m_rectDraw = CalcRectFromRowColEx(nChildRow, nChildCol);
					pInfo->m_rectDraw.left = oldRect.left;
					pInfo->m_rectDraw.right = oldRect.right;
					CGXHierarchyGrid<T>* pChildGrid = dynamic_cast<CGXHierarchyGrid<T>*>(GetChildAt(nRowParse));
					ASSERT(pChildGrid != NULL);
					// Call the child's OnGridPrint
					pChildGrid->OnGridPrint(pDC, pInfo);
				}
			}

			pInfo->m_nCurPage = nOldPage;
		}

		// check if there are pages to go
		pInfo->m_bContinuePrinting =
			bottomRow != GetClientRow(GetRowCount()) ||
			rightCol != GetClientCol(GetColCount());

		// restore old font
		if (hOldFont)
			pDC->SelectObject(CFont::FromHandle(hOldFont));

		// Reset printing mode
		// Let only the top-level grid set the printing flag, it will recursiviely call the children.
		if(!m_gridParent)
			SetPrinting(FALSE);
	}
	CATCH_ALL(e)
	{
		if (nDC)
			pDC->RestoreDC(nDC);

		// restore old font
		if (hOldFont)
			pDC->SelectObject(CFont::FromHandle(hOldFont));

		// Reset printing mode
		// Let only the top-level grid set the printing flag, it will recursiviely call the children.
		if(!m_gridParent)
			SetPrinting(FALSE);

		THROW_LAST();
	}
	END_CATCH_ALL

	if (m_bPrintPaintMsg)
		Redraw(GX_UPDATENOW, FALSE);
}

template<class T>
ROWCOL CGXHierarchyGrid<T>::GetMaxChildPageSpanInCurrentRowRange(CDC* pDC, CPrintInfo* pInfo)
{
	// Parse through all the children within this page and find the max pages they span.
	CRect rectGrid;
	rectGrid = GetGridRect();
	ROWCOL nBottomRow = CalcClientRowFromPt(rectGrid.BottomRight());
	if(nBottomRow == GX_INVALID)
		nBottomRow = max(GetRowCount(), m_nPrintTopRow+1);
	else
	{
		nBottomRow--;
		nBottomRow = max(GetRow(nBottomRow), m_nPrintTopRow+1);
	}

	CRect oldRect = pInfo->m_rectDraw;
	ROWCOL nMaxChildPageCount=0;
		
	// Get the top most logical row and the bottom most logical row with the child visible.
	ROWCOL nLogTopRow, nLogBottomRow, nDummyCol;
	GetLogCellFromAbsCell(m_nPrintTopRow, 1, nLogTopRow, nDummyCol);
	GetLogCellFromAbsCell(nBottomRow, 1, nLogBottomRow, nDummyCol);
	// If the child is not visible in the logbottomrow decrement it?
	ROWCOL nChildRow, nChildCol;
	GetAbsCellContainingChild(nLogBottomRow, nChildRow, nChildCol);
	if(nBottomRow < nChildRow)
		nLogBottomRow--;

	// Parse through all the children and find the max page count.
	for(ROWCOL nRowParse = nLogTopRow; nRowParse <= nLogBottomRow; nRowParse++)
	{
		if(IsChildShown(nRowParse))
		{
			GetAbsCellContainingChild(nRowParse, nChildRow, nChildCol);
			pInfo->m_rectDraw = CalcRectFromRowColEx(nChildRow, nChildCol);
			pInfo->m_rectDraw.left = oldRect.left;
			pInfo->m_rectDraw.right = oldRect.right;
			CGXHierarchyGrid<T>* pChildGrid = dynamic_cast<CGXHierarchyGrid<T>*>(GetChildAt(nRowParse));
			ASSERT(pChildGrid != NULL);
			// Call the child's beginprinting.
			pChildGrid->OnGridBeginPrinting(pDC, pInfo);
			nMaxChildPageCount = max(nMaxChildPageCount, (ROWCOL)pChildGrid->m_awPageFirstCol.GetSize()-1);
		}
	}
	pInfo->m_rectDraw = oldRect;
	return nMaxChildPageCount;
}

// Use the parent's WYSYWIG mode and CGXPrintDC, if a child.
template<class T>
void CGXHierarchyGrid<T>::OnGridPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	if (pInfo)
	{
		// Adjust printer DC
		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(GXGetFontState()->m_nLogPixelsX, GXGetFontState()->m_nLogPixelsY);

		int nlogx = pDC->GetDeviceCaps(LOGPIXELSX);
		int nlogy = pDC->GetDeviceCaps(LOGPIXELSY);

		pDC->SetViewportExt(nlogx, nlogy);

		// Mapping: 72 pixels/unit (like MM_TEXT)
	}
	else if (GetParam()->IsDrawWYSIWYG() || m_gridParent && GetParentGrid() && GetParentGrid()->GetParam()->IsDrawWYSIWYG())
	{
		// make sure grid is drawn exactly the same
		// as it will be printed.

		CGXPrintDevice* pPD = GetParam()->GetPrintDevice();
		if(!pPD && m_gridParent)
			pPD = GetParentGrid()->GetParam()->GetPrintDevice();

		// GetPrintDC() will create printer device context
		// when it is called the first time. Further calls
		// will return the previously created device context.

		HDC hPrintDC = 0;
		if (pPD)
			hPrintDC = pPD->GetPrintDC();

		// Make sure, the same mapping mode is used
		if (hPrintDC != NULL)
		{
			pDC->SetAttribDC(hPrintDC);
			SIZE size;
			::SetMapMode(pDC->m_hAttribDC, MM_ANISOTROPIC);
			::SetWindowExtEx(pDC->m_hAttribDC, GXGetFontState()->m_nLogPixelsX, GXGetFontState()->m_nLogPixelsY, &size);
			int nlogx = ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSX);
			int nlogy = ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSY);

			::SetViewportExtEx(pDC->m_hAttribDC, nlogx, nlogy, &size);
		}
	}
	PrepareDCAttribs(pDC);
}

template<class T>
void CGXHierarchyGrid<T>::SetPrinting(BOOL b, BOOL bClientToRect /* = FALSE */)
{
	T::SetPrinting(b, bClientToRect);

	// Call SetPrinting on all the visible children as well.
	for(ROWCOL i=0; i<=GetLogRowCount(); i++)
	{
		if(IsChildShown(i))
		{
			CFriendlyGridTemplate<T>* pChildGrid = (CFriendlyGridTemplate<T>*)dynamic_cast<CGXGridCore*>(GetChildAt(i));
			ASSERT(pChildGrid);
			pChildGrid->SetPrinting(b, bClientToRect);
		}
	}
}

template<class T>
void CGXHierarchyGrid<T>::GetChildFontMetrics(CDC* pDC)
{
	// Set the font metrics for all the visible children as well.
	for(ROWCOL i=0; i<=GetLogRowCount(); i++)
	{
		if(IsChildShown(i))
		{
			CFriendlyGridTemplate<T>* pChildGrid = (CFriendlyGridTemplate<T>*)dynamic_cast<CGXGridCore*>(GetChildAt(i));
			if(pChildGrid)
				pChildGrid->GetFontMetrics(pDC, pChildGrid->m_dxPrintWidth, pChildGrid->m_dyPrintHeight);
		}
	}
}

#endif//_GXHGPRINT_H_
