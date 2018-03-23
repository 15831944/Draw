///////////////////////////////////////////////////////////////////////////////
// gxdbteng.h
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
// Author: Praveen Ramesh
//

#ifndef _GXDBTENG
#define _GXDBTENG

#ifndef _GXDBENGINE
#include "grid\dbe\gxdbengine.h"
#endif

#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

#ifndef __RWTPSLIST_H__
#include <rw/tpslist.h>
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//
#if defined (_GXDLL) && !defined (_GXNOEXTSTATE)
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////
// CGXDBToolsEngine
//
// Exported through base class. 
class CGXDBToolsEngine : public CGXDBEngine
{
public:
	// Data structre that stores the fetched result set
	class GRID_API CGXMemTable : public RWTPtrSlist<RWDBRow>
	{
	public:
		CGXMemTable::~CGXMemTable();
		void populate(RWDBReader rd, int nUpto, BOOL& bEOF);
		void fillUpto(unsigned int nCount, BOOL& bEOF);
		size_t numberOfColumns();
		const RWDBSchema& schema();
		RWDBSchema sch;
		RWDBReader rd;
	}
	m_memTable;
	
private: 
	GRID_API void InitMembers();

public:
	// Default constructor. Use Init to initialize the engine.
	inline CGXDBToolsEngine(){};
	// To create an engine bound to a table (with no selection criteria)
	GRID_API CGXDBToolsEngine(RWDBTable table, RWDBSchema updateCols, RWDBConnection conn);
	// To create an engine bound to a table with selection criteria
	GRID_API CGXDBToolsEngine(RWDBSelector selector, RWDBConnection conn);
	// To create an engine bound to a join
	GRID_API CGXDBToolsEngine(RWDBTable table, RWDBSelector selector, RWDBSchema visibleCols, RWDBSchema updateCols,  RWDBConnection conn);

	GRID_API virtual ~CGXDBToolsEngine();

	// Connection on which to perform transactions
	RWDBConnection m_conn;

// Data members...
protected:
	short m_nResultType;
	RWDBTable m_table;
	RWDBSelector m_selector;
	// When binding the engine to a table with selection criteria, the grid needs to know
	// the columns whose data is to be exposed and
	RWDBSchema m_visibleCols;
	// the mandatory key columns based on which inserts and updates can be done
	// Knowing the key columns makes updating a more efficient operation.
	RWDBSchema m_updateCols;

	long m_nCols;		// No. of columns in the result set
	RWDBRow m_editRow;	// Edit buffer that stores the change in the current edited record

// Operations...
	// Compose a RWDBValue to be stored in the data source from a CString 
	GRID_API virtual RWDBValue ComposeValue(RWDBValue::ValueType type, CString* strValue);
	GRID_API virtual BOOL GetOrigFieldValue(long nRecord, long nField, CString& strValue);	

private:
	// returns the index of the column in the schema
	GRID_API int ColumnInSchema(RWDBColumn col, RWDBSchema schema);

public:
	// Is the engine initialzed
	GRID_API virtual BOOL IsInit();
	
// Virtual Operations...
public:
	// Convert the RWDBValue as a CString
	GRID_API BOOL GetDBTValueAsString(CString& strValue, RWDBValue value, RWDBValue::ValueType type);
	// Append schema to m_updateCols member except the Blob type columns.
	GRID_API void InitUpdateCols(RWDBSchema schema);
	GRID_API virtual void FetchRecords(long nRecords);	// Enables incremental fetching
	GRID_API virtual void CleanUp();	// Called by the destructor...
	GRID_API virtual BOOL GetValue(long nRecord, long nField, CString& strValue);	// nRecord and nField are 1 based...
	GRID_API virtual BOOL SetValue(long nRecord, long nField, CString* strValue);
	GRID_API virtual long GetRecordCount();	// 1 based...
	GRID_API virtual long GetFieldCount();	// 1 based...
	GRID_API virtual BOOL Edit(long nRecord);	// Call Edit before editing a record via SetValue...
	GRID_API virtual BOOL Update(CString* strError = NULL); // Complete the editing on a record by calling Update...
	GRID_API virtual long AddRow();	// The returned value is the new record no. that should be used in SetValue...
	GRID_API virtual BOOL DeleteRows(long nFrom, long nTo);	//	virtual BOOL CanUpdate();	
	GRID_API virtual BOOL CanAppend();
	GRID_API virtual BOOL CanUpdate();
	GRID_API virtual void CancelRecord();
	// Reinitialze the engine (schema remains same)
	GRID_API virtual void Requery();
	// Helper for corresponding constructors...
	// Use these directly when you want to reinitiaze the engine (including the schema)
	GRID_API void Init(RWDBTable table, RWDBSchema updateCols, RWDBConnection conn);
	GRID_API void Init(RWDBSelector selector, RWDBConnection conn);
	GRID_API void Init(RWDBTable table, RWDBSelector selector, RWDBSchema visibleCols, RWDBSchema updateCols,  RWDBConnection conn);
	// Helper for Requery
	GRID_API void ReInit();
	GRID_API RWDBSelector& GetSelector();
};

////////////////////////////////////////////////////////////////////////////

template <class T>
void GXInitColInfo(	CGXDBEGrid<T>* pGrid, RWDBColumn& col ,	CString& ,
	long& ,
	WORD& );

// Get the display size based on the column type
long GXGetDisplaySize(RWDBColumn column);


// Initialization function that initializes pGrid with pEngine.
// It sets the col count on the grid (based on the entries in pEngine),
// Sets the col width, column base styles based on the pEngine parameters.

// Take a look at CGXBrowserLayoutManager::GXInitDBEGridFromEngine in class refernece
// for more info on this function.

template <class T>
void GXInitDBToolsGridFromDBToolsEngine(CGXDBEGrid<T>* pGrid, CGXDBEngine* pEngine)
{
//  Assert runtime type info	for the pEngine formal param...
	CGXDBToolsEngine* pDBToolsEngine = (CGXDBToolsEngine*)pEngine;

	// Delete contents of CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(0);
	pGrid->GetParam()->GetData()->StoreColCount(0);

	ROWCOL nFieldCount = pDBToolsEngine ? pDBToolsEngine->GetFieldCount() : (short)0;
	// Reserve space in CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(1);
	pGrid->GetParam()->GetData()->StoreColCount( nFieldCount + pGrid->GetHeaderCols());

	RWDBSchema schema;
	if(pDBToolsEngine && pDBToolsEngine->IsInit())
		schema = pDBToolsEngine->m_memTable.schema();

	CGXStyle* pStyle = pGrid->CreateStyle();

	for (ROWCOL nField = 0; nField < nFieldCount; nField++)
	{
		ROWCOL nCol = (ROWCOL) nField + 1 + pGrid->GetHeaderCols();

		CString strName;
		long cbLength;
		WORD wBaseStyle;

		GXInitColInfo(pGrid, schema[nField], strName, cbLength, wBaseStyle);
		// b) store field name in cell (0, nCol)
		pGrid->SetValueRange(CGXRange(0, nCol), strName);

		cbLength = cbLength > strName.GetLength() ? cbLength : strName.GetLength();
		cbLength = pGrid->GetMaxColWidth() < cbLength ? pGrid->GetMaxColWidth() : cbLength;
		// c) store column width
		pGrid->SetColWidth(nCol, nCol, pGrid->Width_LPtoDP(cbLength * GX_NXAVGWIDTH));
			// ( GX_NXAVGWIDTH is the average width of a character in pixels ).

		// d) store the info in the column style.

		// This makes moving columns easy, because when the user
		// drags columns the grid will do all the necessary steps.
		// The base style and maximum length of the input text is also
		// stored in the column style. All cells in the column will
		// inherit their style attributes from the column style.

		pGrid->SetStyleRange(CGXRange().SetCols(nCol),
				(*pStyle)
					.SetMaxLength((WORD) cbLength)
					.SetBaseStyle(wBaseStyle)
			);

	}

	// clean up
	delete pStyle;
}


// Initializes the base styles for the columns based on the value types.
template <class T>
void GXInitColInfo(
	CGXDBEGrid<T>* pGrid,
	RWDBColumn& column,
	CString& strName,
	long& cbLength,
	WORD& wBaseStyle)
{
	CGXDBEParam* pDBEParam = pGrid->GetDBEParam();
	switch(column.type())
	{
	case RWDBValue::String:
	case RWDBValue::UnsignedChar:
	case RWDBValue::WString:
	case RWDBValue::MBString:
	case RWDBValue::Char:        wBaseStyle = pDBEParam->m_bsText;       break;
	case RWDBValue::Tiny:
	case RWDBValue::UnsignedTiny:
	case RWDBValue::Short:
	case RWDBValue::UnsignedShort:
	case RWDBValue::Int:
	case RWDBValue::UnsignedInt:
	case RWDBValue::Long:
	case RWDBValue::UnsignedLong:
	case RWDBValue::Float:
	case RWDBValue::Decimal:
	case RWDBValue::Double:
        wBaseStyle = pDBEParam->m_bsNumeric;    break;
	case RWDBValue::Date:
	case RWDBValue::DateTime:
    case RWDBValue::Duration:    
		wBaseStyle = pDBEParam->m_bsDate;       break;
	case RWDBValue::Blob:  wBaseStyle = pDBEParam->m_bsBinary;     break;

	case RWDBValue::NoType:
	default:
		TRACE0("Unknown Datatype\n");
		ASSERT(FALSE);
		AfxThrowNotSupportedException();
	}

	strName = column.name();
	cbLength = GXGetDisplaySize(column);

	if (strName.GetLength() > cbLength)
		cbLength = strName.GetLength();

}

// Initialization function that initializes pGrid with pEngine.
// It sets the col count on the grid (based on the entries in pEngine),
// Sets the col width, column base styles based on the pEngine parameters.

template <class T>
void GXInitHierGridFromDBToolsEngine(CGXDBEGrid <T>* pGrid, CGXDBEngine* pEngine)
{
//  Assert runtime type info	for the pEngine formal param...
	CGXDBToolsEngine* pDBToolsEngine = (CGXDBToolsEngine*)pEngine;

	// Delete contents of CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(0);
	pGrid->GetParam()->GetData()->StoreColCount(0);

	ROWCOL nFieldCount = pDBToolsEngine ? pDBToolsEngine->GetFieldCount() : (short)0;
	// Reserve space in CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(2);
	pGrid->GetParam()->GetData()->StoreColCount( nFieldCount + pGrid->GetFirstCol());	// Including a col for the expander column and a dummy col. to the right most.

	RWDBSchema schema;
	if(pDBToolsEngine && pDBToolsEngine->IsInit())
		schema = pDBToolsEngine->m_memTable.schema();

	CGXStyle* pStyle = pGrid->CreateStyle();

	for (ROWCOL nField = 0; nField < nFieldCount; nField++)
	{
		ROWCOL nCol = (ROWCOL) nField + pGrid->GetFirstCol();

		CString strName;
		long cbLength;
		WORD wBaseStyle;

		GXInitColInfo(pGrid, schema[nField], strName, cbLength, wBaseStyle);
		// b) store field name in cell (1, nCol)
		pGrid->SetValueRange(CGXRange(1, nCol), strName);

		cbLength = cbLength > strName.GetLength() ? cbLength : strName.GetLength();
		cbLength = pGrid->GetMaxColWidth() < cbLength ? pGrid->GetMaxColWidth() : cbLength;
		// c) store column width
		pGrid->SetColWidth(nCol, nCol, pGrid->Width_LPtoDP(cbLength * GX_NXAVGWIDTH));
			// ( GX_NXAVGWIDTH is the average width of a character in pixels ).

		// d) store the info in the column style.

		// This makes moving columns easy, because when the user
		// drags columns the grid will do all the necessary steps.
		// The base style and maximum length of the input text is also
		// stored in the column style. All cells in the column will
		// inherit their style attributes from the column style.

		pGrid->SetStyleRange(CGXRange().SetCols(nCol),
				(*pStyle)
					.SetMaxLength((WORD) cbLength)
					.SetBaseStyle(wBaseStyle)
			);

	}

	// clean up
	delete pStyle;
}

//////////////////////////////////////////////////////////////////////////

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
#endif //_GXDBTENG
