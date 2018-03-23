///////////////////////////////////////////////////////////////////////////////
// gxfltcel.h : Floating cells implementation class declaration.
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
// Author: Stefan Hoenig
//

#ifndef _GX_FLTCEL_H__
#define _GX_FLTCEL_H__

// #include <StingrayExportDefs.h>

class CGXAbstractGridFloatCellsImp;

class CGXGridFloatCellsImp: public CGXAbstractGridFloatCellsImp
{
public:
	GRID_API virtual void SetFloatCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw = TRUE);

	GRID_API virtual void DelayFloatCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxCols);
	GRID_API virtual BOOL EvalFloatCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle);

	GRID_API virtual CGXRange* GetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	GRID_API virtual BOOL CanFloatCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
	GRID_API virtual BOOL CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

protected:
	// Implementation - EvalFloatCells implementation
	GRID_API virtual BOOL EvalAllFloatCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle);
	GRID_API virtual BOOL EvalDelayedFloatCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle);
	GRID_API virtual BOOL FloatCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary, BOOL bLookupStyle);
	GRID_API virtual BOOL FCellImpl(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary, BOOL bLookupStyle);

	// Implementation - Float Cell Ranges
	GRID_API virtual BOOL SetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags);
	GRID_API virtual BOOL StoreFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);
	GRID_API virtual void UpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint);
	GRID_API virtual void MergeFloatedCells(CGXGridCore* pGrid, CGXRange& range);
};

#endif