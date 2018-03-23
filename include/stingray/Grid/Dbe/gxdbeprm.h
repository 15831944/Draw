//////////////////////////////////////////////////////////////////////////////
// gxdbeprm.h
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


#ifndef _GXDBEPARAM
#define _GXDBEPARAM

//
// GridMFC Extension DLL
// initialize declaration context
//

#if defined( _GXDLL) && !defined _GXNOEXTSTATE
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#include  <StingrayExportDefs.h>

class CGXDBEParam: public CGXGridParam
{
	GRID_DECLARE_SERIAL(CGXDBEParam)
	
public:
	// Attributes - Base styles
	WORD
		m_bsBoolean,
		m_bsNumeric,
		m_bsCurrency,
		m_bsDate,
		m_bsText,
		m_bsBinary,
		m_bsMemo,
		m_bsGUID,
		m_bsChapter;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

	BOOL m_bAllowPasteMultiCells;
		// Set this TRUE if you want to allow the user to paste
		// multiple lines of text into the grid. 
		// If FALSE OG will only paste into the current cell (default)

	BOOL m_bCanStoreGridCellInCGXData;
		// TRUE if any cell data can be directly stored in CGXData
		// FALSE if only headers can stored in CGXData
		// CGXDaoGrid and CGXODBCGrid initialize m_bCanStoreGridCellInCGXData = FALSE
		// The default value is TRUE.

	int  m_nMaxColWidth;            // holds the maximum col width in characters

	BOOL m_bUpdateOnStore;          // TRUE when Update shall be called
	BOOL m_bDoReplaceAll;           // TRUE when OnReplaceAll is called

	BOOL m_bIsBrowseInit;           // TRUE when one-time initialization is done

	// moving columns / sorting rows
	CRowColArray
		m_awRowIndex,	// Index is the Row and the value is the Record
		m_awColIndex;	// Index is the Col and the value is the field

	ROWCOL m_nCurrentRow;	// Current row. 
		
	CGXStyle* m_pTmpStyle;          // temporary style object

// Caching, currently only CGXDaoGrid takes advantage of this
	long m_nCacheSize;      // specify -1 for no caching
	ROWCOL m_nRowCacheStart;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	long
		m_lMoveRecordWaitCursor;

// Implementation
public:
	GRID_API CGXDBEParam();
	GRID_API virtual ~CGXDBEParam();
	GRID_API virtual void Serialize(CArchive& ar);
};

//
// GridMFC extension DLL
// reset declaration context
//
#if !defined _GXNOEXTSTATE
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif
//


#endif
