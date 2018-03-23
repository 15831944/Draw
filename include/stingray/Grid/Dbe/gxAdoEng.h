///////////////////////////////////////////////////////////////////////////////
// gxAdoEng.h
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

#pragma once

#ifndef _GXADOENG
#define _GXADOENG

#ifndef _GXDBENGINE
#include "grid\dbe\gxdbengine.h"
#endif

#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

#ifndef _GX_SCRCUR_ENG
#include "grid\dbe\gxScrCurEng.h"
#endif

// include decls for base class
#if _MSC_VER >= 1400
#include <adoguids.h>		// VC++ 8.0 ADO C++ header
#elif _MSC_VER == 1301 
#include <adoguids.h>	// VC++ 7.1 ADO C++ header // May need to change this
#else // _MSC_VER < 1301
#include <adoid.h>			// VC++ 6.0 ADO C++ header	 
#endif
#include <adoint.h>			// ADO C++ header

//
// GridMFC Extension DLL
// initialize declaration context
//
#if defined (_GXDLL)
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

//#ifndef _GXNOADOIDAUTOLIB
//#pragma comment(lib, "adoid.lib")
//#endif

// Replica of adoid.lib, but without the debug problem in adoid.lib...
// link to the correct version of adoid.lib

#ifdef _UNICODE
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidusd.lib")
			#pragma comment(lib, "gxadoidusd.lib")
		#else
			#pragma message("gxadoidud.lib")
			#pragma comment(lib, "gxadoidud.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoidus.lib")
			#pragma comment(lib, "gxadoidus.lib")
		#else
			#pragma message("gxadoidu.lib")
			#pragma comment(lib, "gxadoidu.lib")
		#endif //_AFXDLL
	#endif//_DEBUG
#else
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidsd.lib")
			#pragma comment(lib, "gxadoidsd.lib")
		#else
			#pragma message("gxadoidd.lib")
			#pragma comment(lib, "gxadoidd.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoids.lib")
			#pragma comment(lib, "gxadoids.lib")
		#else
			#pragma message("gxadoid.lib")
			#pragma comment(lib, "gxadoid.lib")
		#endif //_AFXDLL
	#endif //_DEBUG
#endif //_UNICODE


//statement is the statement to be executed
//recordset is a pointer to recordset to retrieve the errors if any occured
//succeded is the output param that would have true or false.
// QA 32218: Fixes crash and prevents memory leaks
#define GX_ADO_CHECK(exp, recordset, succeded)	\
	{							\
		HRESULT hr;					\
		succeded = TRUE;			\
		if(FAILED(hr = exp))		\
		{							\
			succeded = FALSE;				\
			CComPtr<ADOConnection> piConnection;	\
			CComVariant var;                       \
			recordset->get_ActiveConnection(&var);\
			piConnection = (ADOConnection *) V_DISPATCH(&var);\
			CComPtr<ADOErrors> piErrors;	\
			piConnection->get_Errors(&piErrors);	\
			long lCount;		\
			piErrors->get_Count(&lCount);	\
			CComPtr<ADOError> piError;				\
			for(int i=0; i<(int)lCount; i++)		\
			{										\
				CComVariant varIndex;				\
				varIndex.vt = VT_INT;				\
				varIndex.intVal = i;				\
				piErrors->get_Item(varIndex, &piError);	\
				CComBSTR error;							\
				piError->get_Description(&error);	\
				AfxMessageBox(CString(error));		\
			}										\
			piErrors->Clear();						\
		}							\
	}							\

/////////////////////////////////////////////////////////////////////////
// CGXADOEngine
//
// Exported through base class. 
class CGXADOEngine : public CGXScrollableCurEngine
{

public:
	// Default constructor. Use Init to initialize the engine.
	inline CGXADOEngine(){InitMembers();};

	// Use this constructor to pass the ADORecordset that the engine should bind to.
    // QA 32218: Fixes crash and prevents memory leaks
	GRID_API CGXADOEngine(CComPtr<ADORecordset> pSet, BOOL bIsOpen = TRUE);

	GRID_API virtual ~CGXADOEngine();

// Data members...
    // QA 32218: Fixes crash and prevents memory leaks
	CComPtr<ADORecordset> m_piRecordset;
	CComPtr<ADOFields> m_piFields;

protected:

	BOOL m_bIsInit;	// flag that indicates if the recordset is Open.

public:
	GRID_API void InitMembers();

	// Is the engine initialzed
	inline virtual BOOL IsInit(){ return m_bIsInit; };

	// QA 32218: Fixes crash and prevents memory leaks
	GRID_API static CComPtr<ADORecordset> CreateRecordset(CComBSTR bstrSource,CComBSTR bstrSQL);

// Virtual Operations...
public:
	// Convert the ADOField to a CString
    // QA 32218: Fixes crash and prevents memory leaks
	GRID_API BOOL GetADOValueAsString(CString& strValue, CComPtr<ADOField> pField);
	// Append schema to m_updateCols member except the Blob type columns.
	GRID_API virtual void FetchRecords(long nRecords);	// Enables incremental fetching
	GRID_API virtual void CleanUp();	// Called by the destructor...
	GRID_API virtual BOOL DeleteRows(long nFrom, long nTo);
	GRID_API virtual BOOL CanAppend();
	GRID_API virtual BOOL CanUpdate();
	// Reinitialze the engine (schema remains same)
	GRID_API virtual void Requery();
	
	// Helper for corresponding constructors...
	// Use these directly when you want to reinitiaze the engine (typically with a resultset with a new schema)
    // QA 32218: Fixes crash and prevents memory leaks
	GRID_API void Init(CComPtr<ADORecordset> pSet, BOOL bIsOpen = TRUE);
	GRID_API long SyncPosition();
	GRID_API virtual BOOL MoveToPosition(long nRecord, BOOL bSync = TRUE, BOOL bThrowExceptionOnError = FALSE);

	// Support for transactions.
	GRID_API virtual void BeginTrans(LPCTSTR pszDescription);
	GRID_API virtual void CommitTrans();
	GRID_API virtual void Rollback();

protected:
	GRID_API virtual BOOL OnFlushRecord(long nEditRecord, CString* ps);
	GRID_API virtual void OnFlushCellValue(long nEditRow, long nField, CString& strValue);
	GRID_API virtual BOOL GetOrigFieldValue(long nRecord, long nField, CString& strValue);
};

/////////////////////////////////////////////////////////////////////////
// CGXHierADOEngine
//
class CGXHierADOEngine : public CGXADOEngine
{
public:
	inline CGXHierADOEngine(){InitMembers();}
    // QA 32218: Fixes crash and prevents memory leaks
	GRID_API CGXHierADOEngine(CComPtr<ADORecordset> pSet, BOOL bIsOpen = TRUE);
	GRID_API virtual ~CGXHierADOEngine();

	GRID_API void InitMembers();
	GRID_API virtual void CleanUp();	// Called by the destructor...

	// Support for hierarchical resultsets
	GRID_API virtual CGXDBEngine* GetChildAt(long nRecord);
	GRID_API virtual BOOL AreChildrenAvailable();

	// Members for parent
	long m_lRecsetCursorMovedBy;	// If -1 then the latest Move on the cursor
									// was made by the parent itself; Otherwise the
									// value indicates the child that made the latest move.

	// Members for child
	long m_nChildId;	// If this is a child engine, refers to the associated record in the parent
	long m_nCanUpdate;	// -1 means don't know; 0/1 means FALSE/TRUE
	CGXHierADOEngine* m_pParentEngine;	// Reference to a parent if this is a child.

	GRID_API void SyncParentRecordset();

	GRID_API virtual void FetchRecords(long nRecords);
	GRID_API virtual BOOL GetOrigFieldValue(long nRecord, long nField, CString& strValue);
	GRID_API virtual BOOL MoveToPosition(long nRecord, BOOL bSync = TRUE, BOOL bThrowExceptionOnError = FALSE);
	GRID_API virtual BOOL Update(CString* strError = NULL); 
	GRID_API virtual BOOL DeleteRows(long nFrom, long nTo);	
	GRID_API virtual BOOL CanUpdate();
	GRID_API virtual void Requery();
    // QA 32218: Fixes crash and prevents memory leaks
	GRID_API virtual CComPtr<ADORecordset> GetChildRecordset();
protected:
	GRID_API virtual void OnFlushCellValue(long nEditRow, long nField, CString& strValue);

	// Array of pointers to Child Engines.
	CPtrArray m_apChildEngines;
};

////////////////////////////////////////////////////////////////////////////


// Get the display size based on the column type
// QA 32218: Fixes crash and prevents memory leaks
GRID_API long GXGetDisplaySize(CComPtr<ADOField> pField, CComPtr<ADORecordset> pRecordset);


// Initializes the base styles for the columns based on the value types.
template <class T>
void GXInitColInfo(
	CGXDBEGrid<T>* pGrid,
	CComPtr<ADOField> piField, // QA 32218: Fixes crash and prevents memory leaks
	CString& strName,
	long& cbLength,
	WORD& wBaseStyle)
{
	CGXDBEParam* pDBEParam = pGrid->GetDBEParam();
    // QA 32218: Fixes crash and prevents memory leaks
	CComPtr<ADORecordset> piRecordset = ((CGXADOEngine*)pGrid->GetEngine())->m_piRecordset;

	DataTypeEnum sFieldType;
	BOOL bSuccess;
	GX_ADO_CHECK(piField->get_Type(&sFieldType), piRecordset, bSuccess)

	switch(sFieldType)
	{
	case adWChar:
	case adVarWChar:
	case adLongVarWChar:
	case adChar:
	case adLongVarChar:
	case adVarChar:        wBaseStyle = pDBEParam->m_bsText;       break;
	case adNumeric:
	case adUnsignedTinyInt:
	case adUnsignedSmallInt:
	case adUnsignedInt:
	case adUnsignedBigInt:
	case adTinyInt:
	case adSmallInt:
	case adInteger: 
	case adBigInt:  
	case adSingle:  
	case adDouble:      wBaseStyle = pDBEParam->m_bsNumeric;    break;
	case adBoolean:     wBaseStyle = pDBEParam->m_bsBoolean;    break;
	case adCurrency:    wBaseStyle = pDBEParam->m_bsCurrency;   break;
	case adDBTimeStamp:
	case adDBTime:
	case adDBDate:
	case adDate:        wBaseStyle = pDBEParam->m_bsDate;       break;
	case adGUID:        wBaseStyle = pDBEParam->m_bsGUID;       break;
	case adChapter:     wBaseStyle = pDBEParam->m_bsChapter;       break;
	case adBinary:
	case adVarBinary:
	case adLongVarBinary: wBaseStyle = pDBEParam->m_bsBinary;	break;

	default:
		TRACE0("Unknown Datatype\n");
		ASSERT(FALSE);
		AfxThrowNotSupportedException();
	}

    // QA 32218: Fixes crash and prevents memory leaks
	CComBSTR bStrName;
	GX_ADO_CHECK(piField->get_Name(&bStrName), piRecordset, bSuccess)
	strName = CString(bStrName);
	cbLength = GXGetDisplaySize(piField, piRecordset);

	if (strName.GetLength() > cbLength)
		cbLength = strName.GetLength();

}


// Initialization function that initializes pGrid with pEngine.
// It sets the col count on the grid (based on the entries in pEngine),
// Sets the col width, column base styles based on the pEngine parameters.

// Take a look at CGXBrowserLayoutManager::GXInitDBEGridFromEngine in class refernece
// for more info on this function.

template <class T>
void GXInitDBEGridFromADOEngine(CGXDBEGrid<T>* pGrid, CGXDBEngine* pEngine)
{
//  Assert runtime type info	for the pEngine formal param...
	CGXADOEngine* pADOEngine = (CGXADOEngine*)pEngine;

	ASSERT(pADOEngine && pADOEngine->IsInit());

	BOOL bSuccess = FALSE;

	// Delete contents of CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(0);
	pGrid->GetParam()->GetData()->StoreColCount(0);

	ROWCOL nFieldCount = pADOEngine ? pADOEngine->GetFieldCount() : (short)0;
	// Reserve space in CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(1);
	pGrid->GetParam()->GetData()->StoreColCount( pGrid->GetFirstCol() + nFieldCount + - 1);

    // QA 32218: Fixes crash and prevents memory leaks
	CComPtr<ADORecordset> piRecordset = pADOEngine->m_piRecordset;
	CComPtr<ADOFields> piFields;
	GX_ADO_CHECK(piRecordset->get_Fields(&piFields), piRecordset, bSuccess)

	CGXStyle* pStyle = pGrid->CreateStyle();

	for (ROWCOL nField = 0; nField < nFieldCount; nField++)
	{
		ROWCOL nCol = (ROWCOL) nField +  pGrid->GetFirstCol();

		CString strName;
		long cbLength;
		WORD wBaseStyle;
        // QA 32218: Fixes crash and prevents memory leaks
		CComPtr<ADOField> pField;
		VARIANT varIndex;

		varIndex.vt = VT_I4;
		varIndex.lVal = (long)nField;
		GX_ADO_CHECK(piFields->get_Item(varIndex, &pField), piRecordset, bSuccess)

		GXInitColInfo(pGrid, pField, strName, cbLength, wBaseStyle);
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


// Initialization function that initializes pGrid with pEngine.
// It sets the col count on the grid (based on the entries in pEngine),
// Sets the col width, column base styles based on the pEngine parameters.

template <class T>
void GXInitHierGridFromADOEngine(CGXDBEGrid<T>* pGrid, CGXDBEngine* pEngine)
{
	if(!pEngine)
		return;
//  Assert runtime type info	for the pEngine formal param...
	CGXADOEngine* pADOEngine = (CGXADOEngine*)pEngine;

	ASSERT(pADOEngine && pADOEngine->IsInit());

	BOOL bSuccess = FALSE;

	// Delete contents of CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(0);
	pGrid->GetParam()->GetData()->StoreColCount(0);

	ROWCOL nFieldCount = pADOEngine ? pADOEngine->GetFieldCount() : (short)0;
	// Reserve space in CGXData
	pGrid->GetParam()->GetData()->StoreRowCount(2);
	pGrid->GetParam()->GetData()->StoreColCount( pGrid->GetFirstCol() + nFieldCount); // Including a col for the expander column and a dummy col. to the right most.

    // QA 32218: Fixes crash and prevents memory leaks
	CComPtr<ADORecordset> piRecordset = pADOEngine->m_piRecordset;
	CComPtr<ADOFields> piFields;
	GX_ADO_CHECK(piRecordset->get_Fields(&piFields), piRecordset, bSuccess)

	CGXStyle* pStyle = pGrid->CreateStyle();

	for (ROWCOL nField = 0; nField < nFieldCount; nField++)
	{
		ROWCOL nCol = (ROWCOL) nField +  pGrid->GetFirstCol();

		CString strName;
		long cbLength;
		WORD wBaseStyle;
        // QA 32218: Fixes crash and prevents memory leaks
		CComPtr<ADOField> pField;
		VARIANT varIndex;

		varIndex.vt = VT_I4;
		varIndex.lVal = (long)nField;
		GX_ADO_CHECK(piFields->get_Item(varIndex, &pField), piRecordset, bSuccess)

		GXInitColInfo(pGrid, pField, strName, cbLength, wBaseStyle);
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
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_GXADOENG
