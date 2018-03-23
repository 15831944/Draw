///////////////////////////////////////////////////////////////////////////////
// gxexhlp.h
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
#ifndef _GX_EX_HLP_H__
#define _GX_EX_HLP_H__

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

struct GXEXWRITEDATA
{
	enum gxEnumWrite
	{
		gxexEnd,
		gxexDword,
		gxexWord,
		gxexpByte,
		gxexByte,
		gxexDouble,
	} vt;
	
	UINT nLength;
	union
	{
		DWORD dw;
		WORD w;
		const BYTE* pby;
		BYTE by;
		double db;
	};

// constructors
	GRID_API GXEXWRITEDATA();
	GRID_API GXEXWRITEDATA(DWORD dw);
	GRID_API GXEXWRITEDATA(WORD w);
	GRID_API GXEXWRITEDATA(BYTE b);
	GRID_API GXEXWRITEDATA(const BYTE* pb, UINT length);
	GRID_API GXEXWRITEDATA(double db);
};

struct __gxexmpSt
{
	UINT uival;
	BYTE* by;
	GRID_API void Cleanup();
};

// class to store index of stored style in the XF table
class CGXExStyleMap : public CMap<DWORD, DWORD&, __gxexmpSt*, __gxexmpSt*&>
{
public:
	GRID_API CGXExStyleMap();
	GRID_API ~CGXExStyleMap();

// operations
	GRID_API DWORD IsXFPresent(const BYTE* by);

// access
	GRID_API UINT GetIndexRowCol(ROWCOL nRow, ROWCOL nCol);
	GRID_API void SetIndexRowCol(ROWCOL nRow, ROWCOL nCol, UINT nIndex, const BYTE* pb = NULL);

	
// implementation
protected:
	GRID_API DWORD GetDWordFromRowCol(ROWCOL nRow, ROWCOL nCol) const;
};

// class to store index of stored style in the XF table
class CGXExStyleIDMap : public CMap<DWORD, DWORD&, UINT, UINT&>
{
public:
	GRID_API CGXExStyleIDMap();
	GRID_API ~CGXExStyleIDMap();

// access
	GRID_API UINT GetIndexID(DWORD nID);
	GRID_API void SetIndexID(DWORD nID, UINT nIndex);
};


// helper class to gain access to CGXData protected data
class _accData : public CGXData
{
	friend class CGXExcelXFTable;
	friend class CGXExcelRkHandler;
	friend class CGXExcelFontTable;
	friend class CGXExcelColorTable;
};

// Excel read code error flags
enum egxExcelRWFlags
{
	egxSuccess,
	egxGenericFailure,
	egxUserAbort, // the user aborted the operation
	egxFileExistButIsInvalid, // the specified file is a valid compound 
							  // but is not accessible
	egxFileExistButIsNotExcelFile, // This is a valid compound file that
							  // was opened. But there is no workbook
							  // stream. Maybe this is an eariler version?

	egxFailDocCreate, // failed to create document file
	egxStreamFailCreate, // compound file was created but unable to create stream
	egxWriteHandlerNotFound, // attempt to write failed as there was 
							// no handler for a required field
	
	egxWriteNoData, // There does not appear to be any data to write out
					 // atleast for one tab (usually the first one)
	
	egxWriteStream, // Writing to the Ole Stream failed
	egxInvalidGrid, // Invalid CGXGridCore object was 
					// passed in
	
	egxInvalidParam, // Invalid parameter object was 
					 // passed in
	
	egxInvalidProp, // Invalid properties object was
					// passed in
	
	egxInvalidStylesMap, // Invalid StyleMap was passed in
	
	egxReadStream, // Read operation on the stream failed
	
	egxWriteInvalidData, // data of an invalid type was passed to a write operation
	
	egxFileReadError, // generic file create/handling error
	egxFileWriteError, // generic file create/handling error
	
	egxInvalidData, // Data that was used internally is corrupt
					// or incorrect

	egxCodeError, // an internal error caused by incorrect program
	egxEndPoint,
	egxProbableVersionError, // this is most likely a version error
};

struct CEGXTable
{
	egxExcelRWFlags errFlag;
	egxExcelRWFlags userFlag;
	UINT nIDDevMessage;
	UINT nIDUserMessage;
};

struct CGXExRWErrorHandler
{
	GRID_API static BOOL bDisplay;
	GRID_API static  const CEGXTable f_table[];
	GRID_API static void HandleError(egxExcelRWFlags flags);
	GRID_API static const CEGXTable* LocateEntry(egxExcelRWFlags flags);
};

template<class T>
struct GRID_API CGXExDeleteHlp
{
	inline CGXExDeleteHlp()
	{
		p = NULL;
		bArr = FALSE;
	};
	inline ~CGXExDeleteHlp()
	{
		Cleanup();
	}
	inline void SetPtr(T* ptr, BOOL bCleanExisiting = FALSE, BOOL bA = FALSE)
	{
		if(bCleanExisiting)
			Cleanup();
		p = ptr;
		bArr = bA;
	};
	
	inline void Cleanup()
	{	
		if(p == NULL)
			return;
		if(bArr)
			delete [] p;
		else
			delete p;
		
		p = NULL;
	}

	T* p;
	BOOL bArr;
};

// Helper macros
#define GX_EX_TRY(expr)\
	hr = expr;\
	if(FAILED(hr))\
		{\
		GX_EX_FMT_TRACE("OG Pro: An error occured when reading from doc file.")\
			throw egxFileReadError;\
			return;\
		}

#define GX_EX_FMT_MSG()\
LPVOID lpMsgBuf;\
FormatMessage(\
FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,\
NULL,\
GetLastError(),\
MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),\
(LPTSTR) &lpMsgBuf,\
0,\
NULL );\
::MessageBox( NULL, (LPTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );\
LocalFree( lpMsgBuf );


#define GX_EX_FMT_TRACE(context)\
LPVOID lpMsgBuf;\
FormatMessage(\
FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,\
NULL,\
GetLastError(),\
MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),\
(LPTSTR) &lpMsgBuf,\
0,\
NULL );\
TRACE1("%s: ", context);\
TRACE1("%s\n", (LPTSTR)lpMsgBuf);\
LocalFree( lpMsgBuf );


#ifdef _DEBUG
#define GXEXDUMP(pszBuffer, nLength)\
afxDump.HexDump( ".", (BYTE*) pszBuffer, nLength, nLength );
#else
#define GXEXDUMP(pszBuffer, nLength)\
// Dump
#endif //_DEBUG


#define _gxdata(wr) \
GXEXWRITEDATA wr##[] = { 

#define _gxend \
 GXEXWRITEDATA()};

#define _gxw(w)\
	(WORD)(w),

#define _gxdw(dw)\
	(DWORD)dw,

#define _gxdo(db)\
	(double)db,


#define _gxb(b)\
	(BYTE)b,

#define _gxby(b, n)\
	GXEXWRITEDATA((const BYTE*)b, n),

#define _gxstr(str, n)\
	GXEXWRITEDATA((const BYTE*)(LPCTSTR)str, n),

// map macros
#define BEGIN_GX_EXCEL_MAP(cl)\
GXEXCELMAPCREATOR<cl> CGXExcelMapImpl<cl>::_handlerMapEntries[] = \
{

#define END_GX_EXCEL_MAP()\
};

#define GX_EXCEL_MAP_ENTRY(type, cl, size)\
	{type, RUNTIME_CLASS(cl), NULL, size},

#define GX_EXCEL_MAP_ENTRY1(type, cl, handler, size)\
	{type, RUNTIME_CLASS(cl), handler, size},


#define BYTE_CHECK(bY, wType)\
bY = wType;\
bY = (bY << 8);\
bY = (bY & 0xFF00);\
bY = (bY >> 8);

#define _gxadjustPalette(index)\
	if(index > 0x08)\
			index -= 0x08;


#define GX_EX_WRITE(expr)\
hr = expr;\
if(FAILED(hr))\
	throw egxWriteStream;

#define GX_EX_WRITEEX(expr)\
hr = expr;\
if(FAILED(hr))\
	throw egxWriteStream;


#define GX_EXCEL_WRITEMAP_ENTRY(type, handlerType)\
CGXWriteEntry(type, handlerType),

#define GX_EXCEL_WRITEMAP_ENTRY1(type, handlerType, pass)\
CGXWriteEntry(type, handlerType, pass),

#define GX_EX_WTMB(pszW, psz, CP, nIndex, context)\
char* psz = NULL;\
int nRetval = ::WideCharToMultiByte(\
								CP,\
								0,\
								pszW,\
								nIndex,\
								NULL,\
								0,\
								NULL,\
								NULL);\
if(nRetval)\
{\
	psz = new char[nRetval + 1];\
	nRetval  = ::WideCharToMultiByte(\
								CP,\
								0,\
								pszW,\
								nIndex,\
								psz,\
								nRetval,\
								NULL,\
								NULL);\
}\
if(nRetval == 0)\
{\
	GX_EX_FMT_TRACE(context)\
}\
if(psz != NULL)\
{\
	psz[nIndex] = '\0';\
}

// for logging support
#ifdef _GX_EX_LOG_SUPPORT

	#ifndef _UNICODE

	#define _gxlog(text)\
		LogText(text);
	#else
	#define _gxlog(text)\
		LogText(L ## text);

	#endif //!_UNICODE

	#define _gxlnum(val)\
		LogNumber(val);

	#define _gxlxnum(val)\
		LogXNumber(val);

	#define _gxlnumt(val)\
		LogNumber(val, TRUE);

	#define _gxlxnumt(val)\
		LogXNumber(val, TRUE);

	#define _GXEXLogText(text)\
		if(CGXExcelHandler::GetLogger() != NULL)\
		{\
		CGXExcelHandler::GetLogger()->LogText(text);\
		CGXExcelTable::GetLogger()->LogText(text);\
		}

	#define _GXEXLogNumber(number, b)\
		if(CGXExcelHandler::GetLogger() != NULL)\
		{\
		CGXExcelHandler::GetLogger()->LogNumber(number, b);\
		CGXExcelTable::GetLogger()->LogNumber(number, b);\
		}

	#define _GXEXLogXNumber(number, b)\
		if(CGXExcelHandler::GetLogger() != NULL)\
		{\
		CGXExcelHandler::GetLogger()->LogXNumber(number, b);\
		CGXExcelTable::GetLogger()->LogXNumber(number, b);\
		}
#else
	
	#define _gxlog(text)
	
	#define _gxlnum(val)
		
	#define _gxlxnum(val)
		
	#define _gxlnumt(val)
	
	#define _gxlxnumt(val)
		
	#define _GXEXLogText(text)
	
	#define _GXEXLogNumber(number, b)
	
	#define _GXEXLogXNumber(number, b)

#endif //_GX_EX_LOG_SUPPORT

// Objective Grid Excel Write code
// helper function declarations
GRID_API void _gxExWriteWord(BYTE* buffer, WORD w);
GRID_API void _gxExWriteDWord(BYTE* buffer, DWORD dw);
GRID_API void _gxExWriteByte(BYTE* buffer, BYTE w);
GRID_API void _gxExWriteBuffer(BYTE* buffer, const BYTE* bufferData, ULONG nLength);

// Sets or clears the zero based nth bit
GRID_API void _gxExSetBit(WORD& w, UINT nBitPos, BOOL nBitval);
GRID_API WORD _gxExCalcMask(WORD wBitval, UINT nBitStartPos);
GRID_API void _gxExSetBitEx(WORD& w, UINT nBitStartPos,WORD wBitval);
GRID_API void _gxExSetDWBitEx(DWORD& dw, UINT nBitStartPos,DWORD dwBitval);


GRID_API BOOL _gxExWrite(GXEXWRITEDATA* wr, BYTE* pszBuffer);

// string conversion helper
GRID_API WCHAR* _gxexExpandToUnicode(BYTE* pByte, UINT nCount);

class _core:public CGXGridCore
{
	friend class CGXExcelFormulaHandler;
	friend class CGXExcelGrid;
};


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

#endif
