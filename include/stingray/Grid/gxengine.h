///////////////////////////////////////////////////////////////////////////////
// gxengine.h : Objective Grid interface to the formula engine
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

#ifndef _GXENGINE_H_
#define _GXENGINE_H_

#ifndef _GXCOLL_H_
#include "gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "gxstate.h"
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
	#define AFX_DATA	GX_DATAEXT
#endif

struct gxCell;
struct _gx_formula;
typedef struct _gx_formula gxFormula;

struct _gx_keyword;
typedef struct _gx_keyword gxKeyword;

class CGXUndoEngineCellsInfo;
class CGXFormula;
class CGXWorksheetFunctions;

class GX_ENGINE_STATE: public CObject
{
public:
// costruction/destruction
	GRID_API GX_ENGINE_STATE();
	GRID_API virtual ~GX_ENGINE_STATE();

	// Support for custom worksheet functions
	GRID_API void SetWorksheetFunctionClass(CGXWorksheetFunctions* pClassObject);
	GRID_API void SetDefaultWorksheetFunctions();

// Attributes
	int print_lotus;
	int print_lc;
	int print_at_sign;

	int expr_err_flag;
	int error_reason;
	int error_position;

	int xs_error_silence;
	int xs_error_status;
	int xs_error_code;
	int last_severity;
	int doing_insert_or_delete;

	TCHAR _gx_col_to_text_alpha[10];
	TCHAR _gx_rc_to_text_id[20];
	TCHAR _gx_range_to_text_buf[24];

	int iso_escape;

	CString text_buf;
	
	// sheet contexts
	CPtrArray m_apSheetContext;

	CGXWorksheetFunctions* m_pWorksheetFunctions;
};

GRID_API GX_ENGINE_STATE* GXGetEngineState();

GRID_API void GXEnableWorksheetFunctions();

class CGXFormulaSheet: public CGXData
{
	GRID_DECLARE_SERIAL(CGXFormulaSheet)

public:
// Constructor/Destructor
	GRID_API CGXFormulaSheet();
	GRID_API virtual ~CGXFormulaSheet();
	GRID_API void ResetSheet();
	GRID_API virtual void InitParam(CGXGridParam* pParam);

// Value Interface
	GRID_API virtual BOOL SetFormulaRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszFormula);
	GRID_API virtual BOOL SetTextRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszText);
	GRID_API virtual BOOL SetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double number);
	GRID_API virtual BOOL SetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned format, unsigned places);
	GRID_API virtual unsigned GetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned* pPlaces = NULL);

	GRID_API virtual BOOL SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszInput);
		// parse text, set formula/text/number, apply format (if date)

	GRID_API virtual int GetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double& number);
		// formula will be evaluated if needed
		// d will be 0 for text cells 
		// returns errcode (ok, error, constraint, cycle, N/A)

	GRID_API virtual int GetTextRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText);
		// formula will be evaluated if needed
		// numeric cells will be converted to string 
		// returns errcode (ok, error, constraint, cycle, N/A)

	GRID_API virtual int GetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText);
		// stores formula as string is sText if formula cell
		// otherwise cell value will be stored in sText
		// returns errcode (ok, error, constraint, cycle, N/A)

// Convert Row/Col Coordinates
	GRID_API static int __cdecl GetEngineRow(ROWCOL nRow);
	GRID_API static int __cdecl GetEngineCol(ROWCOL nCol);
	GRID_API static ROWCOL __cdecl GetGridRow(int nEngineRow);
	GRID_API static ROWCOL __cdecl GetGridCol(int nEngineCol);

// Common settings for Formula Engine:
	GRID_API void SetIterationLimit(int nLimit);	// 0 - no iteration
	GRID_API int GetIterationLimit() const;

	GRID_API void SetBlanksAreZeros(BOOL bToggle);
	GRID_API BOOL GetBlanksAreZeros() const;

	GRID_API void SetRecalcMode(int nMode);	// automatic/manual
	GRID_API int GetRecalcMode() const;

	GRID_API void SetRecalcMethod(int nMethod); // foreground / as needed
	GRID_API int GetRecalcMethod() const;

	GRID_API void SetConstraintCheck(BOOL bToggle);	
	GRID_API BOOL GetConstraintCheck() const;

// Base Styles
	GRID_API void RegisterBaseStyles(CGXStylesMap* pMap);

	// CGXStyle* colstyles, rowstyles, tablestyle will 
	// be inherited from CGXData

// overrides
	GRID_API virtual void DeleteContents();
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual const CGXData& operator=(const CGXData& p);

	// Inserting Colums or Rows
	GRID_API virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount);
	GRID_API virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount);

	// Removing Colums or Rows
	GRID_API virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol);

	// Moving Colums or Rows
	GRID_API virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// copy/move ranges in one step
	GRID_API virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd);

	// gxCell data
	GRID_API virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType = 0);
	GRID_API BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType = 0);
	GRID_API virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType = 0);

	// Sorting (rearraging) rows and columns
	GRID_API virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& anRowIndex);
	GRID_API virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& anColIndex);

	// Update
	GRID_API virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);  
	GRID_API virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);  
		// set update flag (TRUE if cell shall be updated next time CGXGridCore::RefreshView is called)
	GRID_API virtual void AddRecalcRange(const CGXRange& range);
	GRID_API virtual void Recalc(BOOL bForceRecalc = FALSE);
	GRID_API virtual void ResetError();
	GRID_API virtual BOOL GetError(CString& strError);

	// Range names
	GRID_API virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL);
	GRID_API virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	GRID_API virtual BOOL DeleteRangeName(LPCTSTR name, CObject*& pUndoInfo, BOOL bCreateUndoInfo);
	GRID_API BOOL GetRangeNameArray(CStringArray& strarray) const;
	GRID_API void SetRangeNameArray(CStringArray& namedRanges);

	// Text/Range conversion
	GRID_API static BOOL __cdecl TextToRange(LPCTSTR strRange, CGXRange& rg);
	GRID_API static LPCTSTR __cdecl RangeToText(const CGXRange& rg, LPTSTR buffer, int nSize, BOOL bForceRange = FALSE);

	// Manual evaluation of formulas
	GRID_API virtual BOOL EvaluateExpression(CString& sResult, LPCTSTR pszFormula);
	GRID_API virtual BOOL EvaluateExpression(CString& sResult, CGXFormula& fm);
	GRID_API virtual BOOL ParseExpression(LPCTSTR pszFormula, CGXFormula& fm);

// Implementation
public:
	GRID_API virtual int GetCellText(gxCell* cp, CString& sText);
	GRID_API virtual int GetExpression(gxCell* cp, CString& sText);

	GRID_API virtual CObject* GetAdvancedUndoInfo();
	GRID_API virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	GRID_API virtual BOOL SetAdvancedUndo(BOOL b);

	GRID_API void CheckAdvancedUndo(BOOL bClearDest, BOOL bToolCells);
	GRID_API BOOL SetPreserveCells(BOOL b);

// Attributes
public:
	WORD m_bsConstraint;	// Base Style id for constraint violation
	int m_nSheetContext;	// sheet index (see GX_ENGINE_STATE::m_apSheetContext)
protected:
	BOOL m_bAdvancedUndoInfo;
	CGXUndoEngineCellsInfo* m_pAdvUndoInfo;
};

class CGXFormula
{
public:
	GRID_API CGXFormula();
	GRID_API virtual ~CGXFormula();

	gxFormula* pfm;
};

class CGXWorksheetFunctions: public CObject
{										   
public:
	GRID_API CGXWorksheetFunctions();

	GRID_API virtual gxKeyword* LookupFunction(LPCTSTR text) = 0;
		// Override this methode in your derived class and 
		// return Lookup(text, fn_table, sizeof(fn_table)); 
		// (see CGXAllWorksheetFunctions::Lookup as an example)
	
	// Helper routine for lookup in a gived keyword table 
	GRID_API static gxKeyword* __cdecl Lookup(LPCTSTR text, gxKeyword* fn_table, int sizeofTable);

	// Helper routine for sorting the table
	GRID_API static void __cdecl SortTable(gxKeyword* fn_table, int sizeofTable);
};

class CGXDefaultWorksheetFunctions: public CGXWorksheetFunctions
{										   
public:
	// Constructor
	GRID_API CGXDefaultWorksheetFunctions();

	// Lookup
	GRID_API virtual gxKeyword* LookupFunction(LPCTSTR text);

	// Get table
	GRID_API static gxKeyword* Get_fn_table();

	// Attributes (keyword table table)
	GRID_API static gxKeyword fn_table[];
	GRID_API static int fn_table_size;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

GX_INLINE BOOL CGXFormulaSheet::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType)
{
	return StoreStyleRowCol(nRow, nCol, &style, mt, nType);
}

// #include "gxstyles.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif //_GXENGINE_H_
