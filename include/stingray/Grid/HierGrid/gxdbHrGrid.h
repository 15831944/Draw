///////////////////////////////////////////////////////////////////////////////
// gxdbHrGrid.h : Hierarchical Regular Grid bound to DB Engine.
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

#ifndef _GX_DBEHIER_GRID
#define _GX_DBEHIER_GRID

#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

#ifndef _GX_REGULAR_GRID
#include "grid\HierGrid\gxreggrid.h"
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

// forward declaration
template <class GRID>
class CGXHierGridLayoutManager;

/////////////////////////////////////////////////
// CGXDBEHierGrid
//
// GRID Should be a subclass of CGXGridCore

template <class GRID>
class CGXDBEHierGrid : public CGXDBEGrid < CGXRegularGrid <GRID> >
{
public:
//	CGXDBEHierGrid();
//	virtual ~CGXDBEHierGrid();
	virtual void CreateLayoutManager(CGXDBEngine* pEngine);
	virtual void OnChildGridInitializing(IGXHierarchyGrid* pChildGrid);
	virtual void OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol);
	virtual void Requery();
	friend class CGXHierGridLayoutManager< GRID >;
};

// CGXHierGridLayoutManager

// Implements the logic for the layout of the Hierarchical grid
// and the update logic...

template <class GRID>
class CGXHierGridLayoutManager : public CGXBrowserLayoutManager< CGXRegularGrid <GRID> >
{
public:
	// Create with a grid and engine
	CGXHierGridLayoutManager(CGXDBEHierGrid<GRID>* pDBEGrid, CGXDBEngine* pEngine);

public:

	// Overriden virtuals from CGXBrowserLayoutManager
	virtual ROWCOL GetFirstCol();
	virtual ROWCOL GetFirstRow();
	virtual long GetRecordFromRow(ROWCOL nRow);
	virtual void InitBrowserSettings();
	virtual BOOL IsOnLastRecord();
	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);
	virtual long OnGetRecordCount();
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL IsDBValueCell(ROWCOL nRow, ROWCOL nCol);
	virtual ROWCOL AddNew();
	virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd);
	// End of Overriden virtuals from CGXBrowserLayoutManager

	CGXDBEHierGrid<GRID>* Grid();
};

typedef CGXDBEHierGrid <CGXGridWnd>* LPDBEHIER_CHILD;

template<class GRID>
void CGXDBEHierGrid<GRID>::CreateLayoutManager(CGXDBEngine* pEngine)
{
	if(m_pLayoutManager)
		delete m_pLayoutManager;
	// Create the default LayoutManager
	m_pLayoutManager =	new CGXHierGridLayoutManager<GRID>( this, pEngine);
}

// Initialize the child with it's own CGXDBEngine.
template<class GRID>
void CGXDBEHierGrid<GRID>::OnChildGridInitializing(IGXHierarchyGrid* pChildGrid)
{
	LPDBEHIER_CHILD pDBEHierChild = dynamic_cast<LPDBEHIER_CHILD>(pChildGrid);
	// The incoming m_nChildId is the logical row where the child is hosted (1 based)
	// Get the original row from the log. row.
	ROWCOL nOrigChildRow, nDummyCol;
	GetAbsCellFromLogCell(pDBEHierChild->m_nChildId, 1, nOrigChildRow, nDummyCol);
	// and adjust for moved rows.
	pDBEHierChild->m_nChildId = GetRecordFromRow(nOrigChildRow)+1;
	CGXDBEngine* pChildEngine = GetEngine()->GetChildAt(pDBEHierChild->m_nChildId - 1);

	if(pChildEngine)
	{
		CGXHierGridLayoutManager<CGXGridWnd>* pLayoutManager =
			new CGXHierGridLayoutManager<CGXGridWnd>( pDBEHierChild, pChildEngine);

		pDBEHierChild->SetEngine(pChildEngine, pLayoutManager, FALSE);
	}
}

/* [VC7] Earlier version was accepting usage of "T" instead of "GRID"
but VC7 gives an error*/
template<class GRID>
void CGXDBEHierGrid<GRID>::OnClickedPMCell(ROWCOL nAbsRow, ROWCOL nAbsCol)
{
	if(nAbsRow == GetAppendRow())
		return;	// Do nothing while clicking on the Append row.
	CGXDBEGrid < CGXRegularGrid <GRID> >::OnClickedPMCell(nAbsRow, nAbsCol);
}

// Requery
//
template<class GRID>
void CGXDBEHierGrid<GRID>::Requery()
{
	// Reset current cell's data
	TransferCurrentCell(FALSE);
	GetEngine()->Requery();

	// If child grid, Redraw the parent grid.
	if(m_gridParent)
	{
		CGXGridCore* pGridParent = dynamic_cast<CGXGridCore*>(m_gridParent);
		pGridParent->Redraw();
	}
	else
	// else just redraw yourself.
		Redraw();
}

// Accessor functions
template<class GRID>
CGXDBEHierGrid<GRID>* CGXHierGridLayoutManager<GRID>::Grid()
{
	ASSERT(m_pDBEGrid != NULL);
	return (CGXDBEHierGrid<GRID>*)m_pDBEGrid;
}

// Create with grid and engine
template<class GRID>
CGXHierGridLayoutManager<GRID>::CGXHierGridLayoutManager(CGXDBEHierGrid<GRID>* pDBEGrid, CGXDBEngine* pEngine)
:CGXBrowserLayoutManager< CGXRegularGrid <GRID> >(pDBEGrid, pEngine)
{
	m_nRecordSpan = 2;
}

// GetFirstCol
//
// Returns the col number for the first DB Value holding col.
template<class GRID>
ROWCOL CGXHierGridLayoutManager<GRID>::GetFirstCol()
{
	return Grid()->GetHeaderCols()+2;
}

template<class GRID>
ROWCOL CGXHierGridLayoutManager<GRID>::GetFirstRow()
{
	// The first 2 rows are always the header-row and child-header-row.
	return 3;
}

template<class GRID>
long CGXHierGridLayoutManager<GRID>::GetRecordFromRow(ROWCOL nRow)
{
	return ((long) Grid()->GetRowIndex(nRow) - (long) Grid()->GetFirstRow() + 1)/2;
}

template<class GRID>
void CGXHierGridLayoutManager<GRID>::InitBrowserSettings()
{
	// Initialize pointer to some objects
	CGXGridParam* pParam = Grid()->GetParam();
	ASSERT_VALID(pParam);

	CGXBrowserLayoutManager< CGXRegularGrid <GRID> >::InitBrowserSettings();

	BOOL bUndo = pParam->IsEnableUndo();
	pParam->EnableUndo(FALSE);

	pParam->EnableTrackRowHeight();     // Track RowHeights with default flags.

	pParam->EnableUndo(bUndo);
}

template<class GRID>
BOOL CGXHierGridLayoutManager<GRID>::IsOnLastRecord()
{
	ROWCOL nRow, nCol;
	if (!Grid()->GetCurrentCell(nRow, nCol))
		return FALSE;

	// Never TRUE as long as we have not seen the last record

	return nRow == Grid()->GetLastRow() || nRow == (Grid()->GetLastRow() - 1);
}

template<class GRID>
long CGXHierGridLayoutManager<GRID>::OnGetRecordCount()
{
	CGXDBEngine* pEngine = GetEngine();

	if (pEngine == NULL || !pEngine->IsInit())
		return 0;

	return GetEngine()->GetRecordCount();
}

template<class GRID>
BOOL CGXHierGridLayoutManager<GRID>::IsDBValueCell(ROWCOL nRow, ROWCOL nCol)
{
	if(nRow < Grid()->GetFirstRow() || nCol < Grid()->GetFirstCol()
		|| (nRow % 2) == 0 || nCol == Grid()->GetColCount())
		return FALSE;
	else
		return TRUE;
}

template<class GRID>
void CGXHierGridLayoutManager<GRID>::OnReplaceAll(LPCTSTR /*lpszFind*/, LPCTSTR /*lpszReplace*/,
		BOOL /*bCase*/)
{
}

template<class GRID>
void CGXHierGridLayoutManager<GRID>::OnTestGridDimension(ROWCOL nLastRow, ROWCOL /*nLastCol*/)
{
	if(!GetEngine() || !GetEngine()->IsInit())
		return;
	if(!GetEngine()->IsEOFSeen())
		GetEngine()->FetchRecords(nLastRow/2);
}

template<class GRID>
BOOL CGXHierGridLayoutManager<GRID>::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	CGXDBEParam* pDBEParam = Grid()->GetDBEParam();

	ASSERT(nRow + Grid()->GetHeaderRows() <= LONG_MAX);

	BOOL bSuccess = Grid()->CGXRegularGrid <GRID>::GetStyleRowCol(nRow, nCol, style, mt, nType);

	// no further processing for the following conditions

	if (mt == gxRemove
		|| nType == -1)
		return bSuccess;

	// give the programmer the chance to load value from data source
	// or apply additional formattings at runtime

	bSuccess |= ((CGXDBEHierGrid<GRID>*)Grid())->OnLoadCellStyle(nRow, nCol, style, NULL);

	return bSuccess;
}

template<class GRID>
ROWCOL CGXHierGridLayoutManager<GRID>::AddNew()
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

	// Do not Scroll if a child grid
	if (!Grid()->m_gridParent && bScroll)
		Grid()->OnScrollBecauseOfEdit(GX_DOWN, 1);

	// reenable scrollbars and update them
	Grid()->LockScrollbars(FALSE);
	return lAppendRow;
}

template<class GRID>
void CGXHierGridLayoutManager<GRID>::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd)
{
	CGXBrowserLayoutManager< CGXRegularGrid <GRID> >::DeleteRows(awRowStart, awRowEnd);
	// Indicate the parent to redraw.
	if( Grid()->m_gridParent != NULL )
		Grid()->m_gridParent->OnChangedChildRowHeight(Grid()->m_nChildId);
}

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif _GX_DBEHIER_GRID
