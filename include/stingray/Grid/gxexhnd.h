////////////////////////////////////////////////////////////////////////////////
// gxexhnd.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_EXHND_H__
#define _GX_EXHND_H__

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _UNICODE

#ifndef _GX_EXMAN_H__
#include "gxexman.h"
#endif

#ifndef _GX_EX_LOG_H__
#include "gxexlog.h"
#endif //!_GX_EX_LOG_H__

#ifndef _GX_EX_TBL_RECSIZE_H__
#include "gxexdef.h"
#endif //_GX_EX_TBL_RECSIZE_H__

#pragma warning(disable: 4245 4706)

// helper data structures
enum gxreadseekOp
{
	gxread,
	gxseek,
};

enum gxreadseekDataType
{
	gx_Word,
	gx_Long,
	gx_Bool,
	gx_Dword,
	gx_Short,
	gx_Int,
	gx_Tchar,
	gx_Byte,
	gx_Double,
};

// Seek data will be used by ReadSeekHelper to determine whether the operation is a read or a 
// seek and also to determine the offset as well as the actual data buffer. This will be filled 
// in from the CGXExcelHandler derivative that is making tbis call
struct GXREADSEEKDATA
{
	GRID_API GXREADSEEKDATA();

	// overloaded constructors
	GRID_API GXREADSEEKDATA(WORD* pwData, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(long* plData, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(DWORD* pdwData, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(short* psiData, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(int* piData, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(BYTE* piByte, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(TCHAR* pszData, DWORD dwSize = 255, gxreadseekOp op = gxread);
	
	GRID_API GXREADSEEKDATA(double* pD, gxreadseekOp op = gxread);
	
	// initialization
	GRID_API void Init(WORD* pwData, gxreadseekOp op = gxread);
	GRID_API void Init(long* plData, gxreadseekOp op = gxread);
	GRID_API void Init(DWORD* pdwData, gxreadseekOp op = gxread);
	GRID_API void Init(short* psiData, gxreadseekOp op = gxread);
	GRID_API void Init(int* piData, gxreadseekOp op = gxread);
	GRID_API void Init(BYTE* piByte, DWORD dwSize = 1, gxreadseekOp op = gxread);
	GRID_API void Init(TCHAR* pszData, DWORD dwSize = 255, gxreadseekOp op = gxread);
	GRID_API void Init(double* pD, gxreadseekOp o = gxread);
	
	// union of types
	union 
	{
		WORD* pwData; //WORD
		long* plData; //long
		BOOL* pbData; //BOOL
		DWORD* pdwData; //DWORD
		short* psiData; //SHORT
		int* piData; //int
		TCHAR* pszData; //TCHAR
		BYTE* pbyData;//BYTE
		DOUBLE* pDData; //double
	};

	// the size of data
	// will be used for the actual read or seek operation
	DWORD dwSize;
	
	// the type of data held
	gxreadseekDataType type;

	// the type of operation to be performed
	gxreadseekOp op;
};

// Exception description structure
struct READSEEKEXCEP
{
	// construction
	READSEEKEXCEP(HRESULT h, DWORD dwindex);
	~READSEEKEXCEP();

	// operations
	void TraceError();
	void ReportError();
	
	void Destroy();

	//data
	HRESULT hrLast;
	DWORD dwerrorIndex;
};

// These functions perform the low level Read/Seek operation based on 
// parameters passed in.
GRID_API void* ResolveReadSeekData(GXREADSEEKDATA* pReadSeekData);
GRID_API BOOL ReadSeekHelper(IStream* pStream, GXREADSEEKDATA* pReadSeekData, DWORD cNum);

GRID_API UINT GXExGetReadSeekOffset();
GRID_API UINT& GXExGetReadSeekOffsetRef();

#define __T_CON__

template<class T>

BOOL ReadSeekHelperEx(IStream* pStream, GXREADSEEKDATA* pReadSeekData, DWORD cNum, T* pHandler)
{
	ASSERT(pReadSeekData != NULL); //---->Invalid data sent

	HRESULT hr = S_OK;
	ULONG ulRead(0);
	void* pVoid = NULL;

	DWORD dwOffsetLeft(0);

	for (DWORD dw = 0; dw < cNum ; dw++)
	{
		ASSERT(pReadSeekData->op == gxread || pReadSeekData->op == gxseek);

		dwOffsetLeft =  pHandler->GetRecordLength() - pHandler->GetRecordOffset();

		TRACE1("ReadSeekHelperEx: Offset left: %x\n", dwOffsetLeft);

		if(pReadSeekData->op == gxread)
		{
			pVoid = ResolveReadSeekData(pReadSeekData); 
		
			if(pReadSeekData->dwSize < dwOffsetLeft)
			{
				hr = pStream->Read(pVoid, pReadSeekData->dwSize, &ulRead);
				pHandler->SetRecordOffset(ulRead);
			}
			else if(pReadSeekData->dwSize == dwOffsetLeft)
			{
				// 2 part read
				hr = pStream->Read(pVoid, dwOffsetLeft, &ulRead);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LARGE_INTEGER lit;
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				if(wType != 0x003C)
				{
					LARGE_INTEGER lit;
					LISet32(lit, -2);
			
					hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
					
					GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;

					return TRUE;
				}
				
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
				
				pHandler->SetRecordLength(wLength);
#endif
			}
			else
			{
				// 2 part read
				hr = pStream->Read(pVoid, dwOffsetLeft, &ulRead);
				
				pHandler->ResetRecordOffset();

				pVoid = ((BYTE*)pVoid) + ulRead;

#ifndef __T_CON__
				// do a seek on the continue record
				LARGE_INTEGER lit;
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				
				ASSERT(wType = 0x3c);
				
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
				
				pHandler->SetRecordLength(wLength);

				LARGE_INTEGER lit;
				LISet32(lit, 1);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);

				pHandler->SetRecordOffset(1);
#endif
	
				hr = pStream->Read(pVoid, pReadSeekData->dwSize - dwOffsetLeft, &ulRead);
				
				pHandler->SetRecordOffset(ulRead);

			}

			GXExGetReadSeekOffsetRef() += ulRead;
			
		}
		else
		{
			LARGE_INTEGER lit;
			
			
			if(pReadSeekData->dwSize < dwOffsetLeft)
			{

				LISet32(lit, pReadSeekData->dwSize);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->SetRecordOffset(pReadSeekData->dwSize);
			}
			else if(pReadSeekData->dwSize == dwOffsetLeft)
			{
				// 2 part seek
				LISet32(lit, dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				if(wType != 0x003C)
				{
					LARGE_INTEGER lit;
					LISet32(lit, -2);
			
					GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;
					
					hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
					
					return TRUE;
				}
						
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
					
				pHandler->SetRecordLength(wLength);

#endif
			}
			else
			{
					// 2 part seek
				LISet32(lit, dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				ASSERT(wType == 0x3C);
						
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
					
				pHandler->SetRecordLength(wLength);

				LARGE_INTEGER lit;
				LISet32(lit, 1);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);

				pHandler->SetRecordOffset(1);
#endif


				LISet32(lit, pReadSeekData->dwSize - dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
	
				pHandler->SetRecordOffset(pReadSeekData->dwSize - dwOffsetLeft);
			}


			GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;
		}
			
			
		
		
		if(FAILED(hr))
		{
			TRACE0("Warning: Unable to read from stream!");
			throw new READSEEKEXCEP(hr, dw);
		}
		
		pReadSeekData ++;

	}

	return TRUE;
}


GRID_API UINT GXExGetReadSeekOffset();
GRID_API void GXExSetReadSeekOffset(UINT nOffset);


// This is the base class for all record specific handlers. This class lays out the interaction interface 
// for each label type (between the Excel data and that of a Objective Grid Data Structure)
class CGXExcelHandler : public CObject
{
	GRID_DECLARE_DYNAMIC(CGXExcelHandler)
public:
	// construction
	GRID_API CGXExcelHandler();
	GRID_API virtual ~CGXExcelHandler();

	// data declarations
	enum gxexType
	{
		nullPtr,
		corePtr,
		stylePtr,
		paramPtr,
		dataPtr
	};
	
	// nested classes
	struct GRID_API gxexpointer
	{
		// default is core pointer
		gxexpointer(void* pv);

		gxexpointer();

		gxexpointer(CGXGridCore* p);

		virtual ~gxexpointer();
		
		// data
		gxexType vt;

		union
		{
			CGXGridCore* pCore;
			CGXGridParam* pParam;
			CGXStyle* pStyle;
			CGXData* pData;
		};
	};

	// operations
	
	// Read/Write from/to stream
	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);
		
	// logging support
	GRID_API virtual void LogText(const TCHAR* pszText);
	GRID_API virtual void LogNumber(int nNum, BOOL bTerminate = FALSE);
	GRID_API virtual void LogXNumber(int nNum, BOOL bTerminate = FALSE);
	
	// public for the base class
	virtual void ResetInternalState() = 0;

	// static functions
	GRID_API static CGXExcelLogger* GetLogger();
	GRID_API static void SetCanLog(BOOL bCanLog);
	GRID_API static BOOL GetClipMode();
	GRID_API static void SetClipMode(BOOL b);
	
	GRID_API static CGXExcelLogger* s_pLogger;

	GRID_API static BOOL GetOptimizedMode();
	GRID_API static void SetOptimizedMode(BOOL b);

	// this is used for dealing with continue records
	GRID_API DWORD GetRecordOffset() const;
	GRID_API void SetRecordOffset(DWORD dw, BOOL bInc = TRUE );
	GRID_API void ResetRecordOffset();
	
	GRID_API DWORD GetRecordLength() const;
	GRID_API void SetRecordLength(DWORD dw);

protected:
	GRID_API virtual BOOL DelegateHelper(gxexpointer p, BOOL bStore = FALSE);
	
	// actual init functions
	GRID_API virtual BOOL InitializeStyle(CGXStyle* pStyle, BOOL bStore = FALSE);
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);
	GRID_API virtual BOOL InitializeParam(CGXGridParam* pParam, BOOL bStore = FALSE);
	GRID_API virtual BOOL InitializeData(CGXData* pData, BOOL bStore = FALSE);

	// data
	GRID_API static BOOL m_bCanLog;
	GRID_API static BOOL m_bClipMode;
	GRID_API static BOOL m_bOptimized;

	DWORD m_dwRecordOffset;
	DWORD m_dwRecordLength;
};


// Concrete implementation for the LABEL record
class CGXExcelLabelHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelLabelHandler)

public:
	GRID_API CGXExcelLabelHandler();
	GRID_API virtual ~CGXExcelLabelHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct labelStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		WORD wLength;
		WCHAR* buffer;
		BYTE grbit;
	} m_lStruct;

};

// CGXExcelRkHandler
class CGXExcelRkHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelRkHandler)

public:
	// construction
	GRID_API CGXExcelRkHandler();
	GRID_API virtual ~CGXExcelRkHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct rkStruct
	{
		WORD row;
		WORD col;
		short ixfe;
		double dblVal;
	} m_rkStruct;
};

// CGXExcelMulRkHandler
class CGXExcelMulRkHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelMulRkHandler)

public:
	GRID_API CGXExcelMulRkHandler();
	GRID_API virtual ~CGXExcelMulRkHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct mulrkStruct
	{
		WORD row;
		WORD colStart;
		WORD colEnd;
		BYTE* pMulRkData;
	} m_mulrkStruct;
};


// CGXExcelColInfoHandler
class CGXExcelColInfoHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelColInfoHandler)

public:
	// construction
	GRID_API CGXExcelColInfoHandler();
	GRID_API virtual ~CGXExcelColInfoHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct GRID_API ColInfoStruct
	{
		WORD colFirst;
		WORD colLast;
		WORD coldx;
		short ixfe;
		WORD grbit;
	} m_colInfoStruct;
};

//CGXExcelRowHandler
class CGXExcelRowHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelRowHandler)

public:
	// construction
	GRID_API CGXExcelRowHandler();
	GRID_API virtual ~CGXExcelRowHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct rowInfoStruct
	{
		WORD rw;
		WORD colMic;
		WORD colMac;
		WORD miyRw;
		WORD grbit;
		short ixfe;
	} m_rowInfoStruct;
};


//CGXExcelFormulaHandler
class CGXExcelFormulaHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelFormulaHandler)
	
public:
	// construction
	GRID_API CGXExcelFormulaHandler();
	GRID_API virtual ~CGXExcelFormulaHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	formulaStruct m_formulaStruct;

	friend void gx_xls_do_formula(CGXExcelFormulaHandler::formulaStruct* pFormulaStruct, int row, int col, int ixfe, int flags,
					int len, WORD *data, WORD *val);
};


// BOF handler
class CGXExcelBOFHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelBOFHandler)

public:
	GRID_API CGXExcelBOFHandler();
	GRID_API virtual ~CGXExcelBOFHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	
	// implementation
	struct BOFStruct
	{
		WORD vers;
		WORD dt;
	} m_bofStruct;
};


//CGXExcelBlankHandler
class CGXExcelBlankHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelBlankHandler)

public:
	// construction
	GRID_API CGXExcelBlankHandler();
	GRID_API virtual ~CGXExcelBlankHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct blankStruct
	{
		WORD rw;
		WORD col;
		short ixfe;
	} m_blankStruct;
};


//CGXExcelMulBlankHandler
class CGXExcelMulBlankHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelMulBlankHandler)

public:
	GRID_API CGXExcelMulBlankHandler();
	GRID_API virtual ~CGXExcelMulBlankHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct mblankStruct
	{
		WORD rw;
		WORD colFirst;
		short* pixfe;
		WORD colLast;
	} m_mblankStruct;
};

//CGXExcelLabelSSTHandler
class CGXExcelLabelSSTHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelLabelSSTHandler)

public:
	GRID_API CGXExcelLabelSSTHandler();
	GRID_API virtual ~CGXExcelLabelSSTHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct labelSSTStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		WORD ixsst;
	} m_sslStruct;
};


//
// CGXExcelDimensionHandler
class CGXExcelDimensionHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelDimensionHandler)
	
	friend class CGXExcelClipHandler;

public:
	GRID_API CGXExcelDimensionHandler();
	GRID_API virtual ~CGXExcelDimensionHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct dimStruct
	{
		DWORD rwMic;
		DWORD rwMac;
		WORD colMic;
		WORD colMac;
		WORD wRes;
	} m_dimStruct;
};


//
// CGXExcelWindow2Handler
class CGXExcelWindow2Handler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelWindow2Handler)

public:
	GRID_API CGXExcelWindow2Handler();
	GRID_API virtual ~CGXExcelWindow2Handler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

// implementation
	struct window2Struct
	{
		WORD grbit;
		WORD rwTop;
		WORD colLeft;
		DWORD icvHdr;
		WORD wScaleSLV;
		WORD wScaleNormal;
		DWORD wRes;
	} m_Window2Struct;
};

// Merged cells handler
// This does not seem to be documented anywhere.
// CGXExcelMergedCellsHandler
class CGXExcelMergedCellsHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelMergedCellsHandler)

public:
	GRID_API CGXExcelMergedCellsHandler();
	GRID_API virtual ~CGXExcelMergedCellsHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	WORD m_nCount;
	struct mergedStruct
	{
		WORD nStartRow;
		WORD nEndRow;
		WORD nStartCol;
		WORD nEndCol;
	};
		
	mergedStruct* m_pMergedStruct;
};


// CGXNumberHandler

class CGXExcelNumberHandler : public CGXExcelHandler
{
	GRID_DECLARE_DYNCREATE(CGXExcelNumberHandler)

public:
	GRID_API CGXExcelNumberHandler();
	GRID_API virtual ~CGXExcelNumberHandler();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	GRID_API void ResetInternalState();
	
	// handlers
	GRID_API virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct numberStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		double value;
	};
	
	numberStruct m_numberStruct;
};

#endif 

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif //_GX_EXHND_H__
