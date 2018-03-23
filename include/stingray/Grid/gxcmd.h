///////////////////////////////////////////////////////////////////////////////
// gxcmd.h : Interface of the undo command classes
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

#ifndef _GXCMD_H_
#define _GXCMD_H_

#ifndef _GXCORE_H_
#include "gxcore.h"
#endif

#ifndef _GXABSTR_H_
#include "gxabstr.h"	// Abstract base classes
#endif

// // #include <StingrayExportDefs.h>

// constants

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



class CGXCommandFactory: public CGXAbstractCommandFactory
{
public:
	GRID_API CGXCommandFactory();

	GRID_API virtual CGXCommand* CreateBlockCmd(LPCTSTR s = NULL);
	GRID_API virtual CGXCommand* CreateSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray);
	GRID_API virtual CGXCommand* CreateHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide);
	GRID_API virtual CGXCommand* CreateSetDefaultRowHeightCmd(int nHeight);
	GRID_API virtual CGXCommand* CreateSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray);
	GRID_API virtual CGXCommand* CreateHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide);
	GRID_API virtual CGXCommand* CreateSetDefaultColWidthCmd(int nWidth);
	GRID_API virtual CGXCommand* CreateMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	GRID_API virtual CGXCommand* CreateMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
	GRID_API virtual CGXCommand* CreateRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow);
	GRID_API virtual CGXCommand* CreateRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol);
	GRID_API virtual CGXCommand* CreateInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount);
	GRID_API virtual CGXCommand* CreateInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount);
	GRID_API virtual CGXCommand* CreateSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol);
	GRID_API virtual CGXCommand* CreateSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray);
	GRID_API virtual CGXCommand* CreateSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows);
	GRID_API virtual CGXCommand* CreateSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols);
	GRID_API virtual CGXCommand* CreateMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex);
	GRID_API virtual CGXCommand* CreateMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex);
	GRID_API virtual CGXCommand* CreateChangeStylesMapCmd(const CGXStylesMap& stylesMap);
	GRID_API virtual CGXCommand* CreateChangePropertiesCmd(const CGXProperties& Properties);
	GRID_API virtual CGXCommand* CreateChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName);
	GRID_API virtual CGXCommand* CreateMoveCellsCmd(const CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo);
	GRID_API virtual CGXCommand* CreateSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange);
	GRID_API virtual CGXCommand* CreateDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo);

	GRID_API virtual BOOL SetAdvancedUndo(CGXGridCore* pGrid, BOOL bAdvUndo);
	GRID_API virtual CObject* GetAdvancedUndoInfo(CGXGridCore* pGrid);
	GRID_API virtual BOOL UndoAdvanced(CGXGridCore* pGrid, CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	GRID_API virtual void CleanAdvancedUndo(CGXGridCore* pGrid);
	GRID_API virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType);
	GRID_API virtual void AddCommand(CGXGridCore* pGrid, CGXCommand* pCmd, GXCmdType ctCmd);
	GRID_API virtual void RemoveCommand(CGXGridCore* pGrid, GXCmdType ctCmd);
	GRID_API virtual BOOL Undo(CGXGridCore* pGrid);
	GRID_API virtual BOOL Redo(CGXGridCore* pGrid);
	GRID_API virtual void BeginTrans(CGXGridCore* pGrid, LPCTSTR s);
	GRID_API virtual void CommitTrans(CGXGridCore* pGrid);
	GRID_API virtual void Rollback(CGXGridCore* pGrid);
	GRID_API virtual void OnCellUndone(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit);
	GRID_API virtual BOOL CanUndo(CGXGridCore* pGrid, CCmdUI* pCmdUI);
	GRID_API virtual BOOL CanRedo(CGXGridCore* pGrid, CCmdUI* pCmdUI);
	GRID_API virtual BOOL CreateRemoveRowsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nCount, ROWCOL& nColCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp);
	GRID_API virtual BOOL CreateRemoveColsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nCount, ROWCOL& nRowCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp);
};

// Command persistence

#define DECLARE_COMMAND(class_name) \
public: \
	static CString GXNEAR cmd##class_name; \
	virtual LPCTSTR GetDescription() const; \

#define IMPLEMENT_COMMAND(class_name, resource_id) \
	CString GXNEAR class_name::cmd##class_name; \
	LPCTSTR class_name::GetDescription() const \
		{ if (cmd##class_name.IsEmpty() && \
			!cmd##class_name.LoadString(resource_id)) \
				cmd##class_name = _T(' '); \
			return (LPCTSTR) cmd##class_name; } \

class CGXCommand: public CObject
{
	GRID_DECLARE_DYNAMIC(CGXCommand)
public:
	// Construction
	GRID_API CGXCommand();
	GRID_API virtual ~CGXCommand();

	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType) = 0;
			// TRUE, if succesfull
			// FALSE, if canceled

	ROWCOL  m_ncRow,        // current cell
			m_ncCol;
	BOOL    m_bCCell;
	CObject* m_pAdvUndo;

	// Data
	GRID_API virtual LPCTSTR GetDescription() const = 0;
};

class CGXBlockCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXBlockCmd)

public:
	// Construction
	GRID_API CGXBlockCmd(LPCTSTR s = NULL);
	GRID_API virtual ~CGXBlockCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);
	GRID_API virtual LPCTSTR GetDescription() const;

	// List of commands
	CObList m_CommandList;

protected:
	CString m_sDesc;
};

class CGXSetRowHeightCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetRowHeightCmd)
	DECLARE_COMMAND(CGXSetRowHeightCmd)

public:
	// Construction
	GRID_API CGXSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray);

	GRID_API virtual ~CGXSetRowHeightCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
	int*        m_anHeightArray;
};

class CGXHideRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXHideRowsCmd)
	DECLARE_COMMAND(CGXHideRowsCmd)

public:
	// Construction
	GRID_API CGXHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide);

	GRID_API virtual ~CGXHideRowsCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
	BOOL*       m_abHide;
};

class CGXSetDefaultRowHeightCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetDefaultRowHeightCmd)
	DECLARE_COMMAND(CGXSetDefaultRowHeightCmd)

public:
	// Construction
	GRID_API CGXSetDefaultRowHeightCmd(int nHeight);

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	int     m_nHeight;
};

class CGXSetColWidthCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetColWidthCmd)
	DECLARE_COMMAND(CGXSetColWidthCmd)

public:
	// Construction
	GRID_API CGXSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray);

	GRID_API virtual ~CGXSetColWidthCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
	int*        m_anWidthArray;
};

class CGXHideColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXHideColsCmd)
	DECLARE_COMMAND(CGXHideColsCmd)

public:
	// Construction
	GRID_API CGXHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide);

	GRID_API virtual ~CGXHideColsCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
	BOOL*       m_abHide;
};

class CGXSetDefaultColWidthCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetDefaultColWidthCmd)
	DECLARE_COMMAND(CGXSetDefaultColWidthCmd)

public:
	// Construction
	GRID_API CGXSetDefaultColWidthCmd(int nWidth);

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	int     m_nWidth;
};


class CGXMoveRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXMoveRowsCmd)
	DECLARE_COMMAND(CGXMoveRowsCmd)

public:
	// Construction
	GRID_API CGXMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow,
				m_nDestRow;
};

class CGXMoveColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXMoveColsCmd)
	DECLARE_COMMAND(CGXMoveColsCmd)

public:
	// Construction
	GRID_API CGXMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol,
				m_nDestCol;
};

class CGXRemoveRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXRemoveRowsCmd)
	DECLARE_COMMAND(CGXRemoveRowsCmd)

public:
	// Construction
	GRID_API CGXRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
};

class CGXRemoveColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXRemoveColsCmd)
	DECLARE_COMMAND(CGXRemoveColsCmd)

public:
	// Construction
	GRID_API CGXRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
};

class CGXInsertRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXInsertRowsCmd)
	DECLARE_COMMAND(CGXInsertRowsCmd)

public:
	// Construction
	GRID_API CGXInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount);
	GRID_API virtual ~CGXInsertRowsCmd();

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nRow,
				m_nCount;

	int*        m_anHeightArray;
	CObArray*   m_pCellsArray;
	CObArray*   m_pRowsArray;
	ROWCOL      m_nColCount;    // No. of Columns in m_pCellsArray
};

class CGXInsertColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXInsertColsCmd)
	DECLARE_COMMAND(CGXInsertColsCmd)

public:
	// Construction
	GRID_API CGXInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount);
	GRID_API virtual ~CGXInsertColsCmd();

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nCol,
				m_nCount;

	int*        m_anWidthArray;
	CObArray*   m_pCellsArray;
	CObArray*   m_pColsArray;
	ROWCOL      m_nRowCount;    // No. of Rows in m_pCellsArray
};

class CGXSetCoveredCellsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetCoveredCellsCmd)
	DECLARE_COMMAND(CGXSetCoveredCellsCmd)

public:
	// Construction
	GRID_API CGXSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nRow;
	ROWCOL      m_nCol;
	ROWCOL      m_nToRow;
	ROWCOL      m_nToCol;
};

class CGXSetStyleRangeCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetStyleRangeCmd)
	DECLARE_COMMAND(CGXSetStyleRangeCmd)

public:
	// Construction
	GRID_API CGXSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray);
	GRID_API virtual ~CGXSetStyleRangeCmd();

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXRange    m_range;
	int         m_nType;

	CObArray*   m_pCellsArray;
};

class CGXSetFrozenRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetFrozenRowsCmd)
	DECLARE_COMMAND(CGXSetFrozenRowsCmd)

public:
	// Construction
	GRID_API CGXSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFrozenRows;
	ROWCOL      m_nHeaderRows;
};

class CGXSetFrozenColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetFrozenColsCmd)
	DECLARE_COMMAND(CGXSetFrozenColsCmd)

public:
	// Construction
	GRID_API CGXSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols);

	// Operation
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFrozenCols;
	ROWCOL      m_nHeaderCols;
};

class CGXMoveDataRowsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXMoveDataRowsCmd)
	DECLARE_COMMAND(CGXMoveDataRowsCmd)

public:
	// Construction
	GRID_API CGXMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex);

	GRID_API virtual ~CGXMoveDataRowsCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CRowColArray*        m_pawRowIndex;
	CGXRange m_rangeSort;
};


class CGXMoveDataColsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXMoveDataColsCmd)
	DECLARE_COMMAND(CGXMoveDataColsCmd)

public:
	// Construction
	GRID_API CGXMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex);

	GRID_API virtual ~CGXMoveDataColsCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CRowColArray*        m_pawColIndex;
	CGXRange m_rangeSort;
};

class CGXChangeStylesMapCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXChangeStylesMapCmd)
	DECLARE_COMMAND(CGXChangeStylesMapCmd)

public:
	// Construction
	GRID_API CGXChangeStylesMapCmd(const CGXStylesMap& stylesMap);
	GRID_API virtual ~CGXChangeStylesMapCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXStylesMap* m_pStylesMap;
};

class CGXChangePropertiesCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXChangePropertiesCmd)
	DECLARE_COMMAND(CGXChangePropertiesCmd)

public:
	// Construction
	GRID_API CGXChangePropertiesCmd(const CGXProperties& Properties);
	GRID_API virtual ~CGXChangePropertiesCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXProperties* m_pProperties;
};

class CGXChangeBaseStyleCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXChangeBaseStyleCmd)

public:
	// Construction
	GRID_API CGXChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName);
	GRID_API virtual ~CGXChangeBaseStyleCmd();
	GRID_API virtual LPCTSTR GetDescription() const;

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXStyle* m_pBaseStyle;
	CString m_sName;
	WORD m_wStyleId;
};

class CGXMoveCellsCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXMoveCellsCmd)
	DECLARE_COMMAND(CGXMoveCellsCmd)

public:
	// Construction
	GRID_API CGXMoveCellsCmd(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo);
	GRID_API virtual ~CGXMoveCellsCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXRange m_rg;
	ROWCOL m_nRow, m_nCol;
	CObject* m_pUndoInfo;
};

class CGXSetRangeNameCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXSetRangeNameCmd)
	DECLARE_COMMAND(CGXSetRangeNameCmd)

public:
	// Construction
	GRID_API CGXSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange);
	GRID_API virtual ~CGXSetRangeNameCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CString m_strName;
	BOOL m_bOldRange;
	CGXRange m_oldRange;
};

class CGXDeleteRangeNameCmd: public CGXCommand
{
	GRID_DECLARE_DYNAMIC(CGXDeleteRangeNameCmd)
	DECLARE_COMMAND(CGXDeleteRangeNameCmd)

public:
	// Construction
	GRID_API CGXDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo);
	GRID_API virtual ~CGXDeleteRangeNameCmd();

	// Operations
	GRID_API virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CString m_strName;
	CGXRange m_oldRange;
	CObject* m_pUndoInfo;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

// inlines

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


#endif //_GXCMD_H_
