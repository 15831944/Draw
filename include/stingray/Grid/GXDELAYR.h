///////////////////////////////////////////////////////////////////////////////
// GXDELAYR.h
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

#ifndef _GXDELAYR_H_
#define _GXDELAYR_H_

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

// // #include <StingrayExportDefs.h>

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

/////////////////////////////////////////////////////////////////////
// class GRID_API CGXDelayedRange

class CGXDelayedRange: public CObject
{
	GRID_DECLARE_SERIAL(CGXDelayedRange);

public:
	GRID_API CGXDelayedRange();

	// Range to be checked
	CGXRange m_range;

	// Done row intervals
	CDWordArray m_awLastRow;
	CDWordArray m_awFirstRow;

	BOOL m_bResolved;

	GRID_API BOOL ResolveRange(CGXRange& rg);
	GRID_API void SetEmpty();
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual void operator=(const CGXDelayedRange& other);
};

/////////////////////////////////////////////////////////////////////
// class GRID_API CGXDelayedRangePool

class CGXDelayedRangePool: public CObject
{
	GRID_DECLARE_SERIAL(CGXDelayedRangePool);

public:
	GRID_API CGXDelayedRangePool();

	GRID_API static void AFXAPI ImplementDelayedRangePool();
	CObArray m_argDelayed;  // array of CGXDelayedRange objects

	// Grid Operations
	GRID_API BOOL EvalRows(const CGXRange& range, CDWordArray &dwColStart, CDWordArray &dwColEnd);
	GRID_API void DelayRange(const CGXRange& range);
	GRID_API void CleanUp();
	GRID_API void MakeEmpty();
	GRID_API void SetRowCount(ROWCOL nMaxRow);
	GRID_API void SetColCount(ROWCOL nMaxCol);

	// Implementation (EvalRows helper)
	GRID_API void SplitDelayedRange(const CGXRange& range);

	// Serialization
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXDelayedRangePool& operator=(const CGXDelayedRangePool& pool);

	// Destructor
	GRID_API virtual ~CGXDelayedRangePool();
};

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXDWordArrayPtrArray

// type-safe CPtrArray for array with CDWordArray objects

class CGXDWordArrayPtrArray: public CPtrArray
{
	GRID_DECLARE_DYNAMIC(CGXDWordArrayPtrArray)

public:
	// Construcion/Destruction
	GRID_API CGXDWordArrayPtrArray();
	GRID_API virtual ~CGXDWordArrayPtrArray();
		// destructor automatically deletes all referenced objects

	GRID_API void DeleteAll();   // delete all referenced objects
	GRID_API void DeleteAt(int nIndex, int nCount = 1);
	GRID_API void Move(int nIndex, int nCount, int nDest);

	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXDWordArrayPtrArray& operator=(const CGXDWordArrayPtrArray& ar);

public:
	// Accessing elements
	GRID_API CDWordArray* GetAt(int nIndex) const;
	GRID_API void SetAt(int nIndex, CDWordArray* newElement);

	// Potentially growing the array
	GRID_API void SetAtGrow(int nIndex, CDWordArray* newElement);
	GRID_API int Add(CDWordArray* newElement);

	// overloaded operator helpers
	GRID_API CDWordArray* operator[](int nIndex) const;
	GRID_API CDWordArray*& operator[](int nIndex);

	// Operations that move elements around
	GRID_API void InsertAt(int nIndex, CDWordArray* newElement, int nCount = 1);
	GRID_API void InsertAt(int nStartIndex, CGXDWordArrayPtrArray* pNewArray);

	GRID_API BOOL InsertRows(ROWCOL nRow, ROWCOL nCount);
	GRID_API BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API BOOL MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API BOOL InsertCols(ROWCOL nCol, ROWCOL nCount);
	GRID_API BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol);
	GRID_API BOOL MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
};

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXSpanCellPool

class CGXSpanCellPool: public CObject
{
	GRID_DECLARE_SERIAL(CGXSpanCellPool);

public:
	GRID_API CGXSpanCellPool();

	GRID_API static void AFXAPI ImplementSpanCellPool();


	// Range to be checked
	CGXDWordArrayPtrArray   m_SpanRows;
	CGXDWordArrayPtrArray   m_SpanCols;

	GRID_API virtual BOOL GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& rg);
	GRID_API virtual BOOL StoreSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);

	GRID_API void InitFromRangeList(const CGXRangeList* pRangeList);

	GRID_API virtual void InsertRows(ROWCOL nRow, ROWCOL nCount);
	GRID_API virtual void RemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API virtual void MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API virtual void InsertCols(ROWCOL nCol, ROWCOL nCount);
	GRID_API virtual void RemoveCols(ROWCOL nFromCol, ROWCOL nToCol);
	GRID_API virtual void MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	GRID_API void MakeEmpty();

	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual CGXSpanCellPool& operator=(const CGXSpanCellPool& pool);
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxdelayr.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXDELAYR_H_
