///////////////////////////////////////////////////////////////////////////////
// gxcvrcel.h : Covered Cells
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

#ifndef _GXCVRCEL_H_
#define _GXCVRCEL_H_

#ifndef _GXABSTR_H_
#include "gxabstr.h"
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

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXCoverCellPool

class CGXCoveredCellPool: public CObject
{
	GRID_DECLARE_DYNCREATE(CGXCoveredCellPool)

public:
	GRID_API CGXCoveredCellPool();

	GRID_API static void AFXAPI ImplementCoveredCellPool();

	// Range to be checked
	CGXPtrArrayPtrArray   m_SpanPool;

	GRID_API virtual POSITION GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL StoreSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, POSITION pos);

	GRID_API void InitFromRangeList(const CGXRangeList* pRangeList);

	GRID_API void MakeEmpty();
};


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

#endif //_GXCVRCEL_H_
