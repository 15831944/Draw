///////////////////////////////////////////////////////////////////////////////
// gxCvrdPattn.h
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

#ifndef _GX_COVERED_PATTERN
#define _GX_COVERED_PATTERN

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

class CGXCoveredCellPatternMap
{
public:
	GRID_API int GetColCount() const;
	GRID_API virtual int GetRowHeaderWidth() const;
	GRID_API void SetRowHeaderWidth(int nHdrWidth);
	GRID_API int GetColWidth(int nPatternCol);
	GRID_API void CalcColCount();
	GRID_API void SetColWidth(int nPatternCol, int nColWidth);
	GRID_API BOOL GetAbsRangeFromPatternCell(ROWCOL nLogRow, ROWCOL nLogCol, ROWCOL& nAbsTopRow, ROWCOL& nAbsLeftCol, CGXRange* range = NULL);
	GRID_API CGXRange* GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range, ROWCOL* nPatternCol);
	GRID_API ROWCOL GetRowSpan();
	GRID_API CGXCoveredCellPatternMap();
	GRID_API void SetColCount(ROWCOL nCols);
	GRID_API void InsertCols(ROWCOL nCol, ROWCOL nCount);
	GRID_API void RemoveCols(ROWCOL nCol, ROWCOL nCount);
	GRID_API void SetColWidths(CDWordArray* pArrayWidths);	// The width should be specified in Colwidth units where each unit is 5 pixels...
	GRID_API void MoveColWidth(int nFromCol, int nToCol, int nDestCol);
	GRID_API void SetRowBreaks(CDWordArray* pArrayBreaks, CWordArray* panIndentWidths = NULL);
	GRID_API const CDWordArray* GetRowBreaks() const;
	GRID_API ROWCOL GetEffectiveColCount() const;
	GRID_API BOOL PurgeEmptyRows();
	GRID_API BOOL GetRowOfCol(int nCol, int& nRow);

	GRID_API virtual CGXCoveredCellPatternMap& operator=(const CGXCoveredCellPatternMap& map);

	CDWordArray m_colWidths;	// The width of each column...
	CWordArray	m_indentWidths;	// The width of each indent in each row.
	WORD		m_wChildIndentWidth;// Indent width for each child.
	BOOL		m_bIsHeaders;			// Turn on/off headers.
	ROWCOL		m_nDefaultCellWidth;	// In multiples of core grid cells.
	UINT		m_nCellWidthPrecision;			// Default Width of each core grid cell, in logical points
	unsigned short m_nPMButtonCellWidth;	// Plus Minus Button Cell Width. In multiples of cell-width precision.

protected:

	ROWCOL		m_nCols;				// The no. of columns...
	CDWordArray m_rowBreaks;			// Breaks as to where the row wraps...
	ROWCOL		m_nBreaks;				// This is equal to no. of rows a record spans as it wraps...
	ROWCOL		m_nEffectiveColCount;
	DWORD		m_nRowHeaderWidth;		// Row header width in multiples of cell-width precision.
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//
#endif //_GX_COVERED_PATTERN
