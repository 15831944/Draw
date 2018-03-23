///////////////////////////////////////////////////////////////////////////////
// gxextbl.h
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

#ifndef _GX_EXTBL_H__
#define _GX_EXTBL_H__

#ifndef _GX_EX_HLP_H__
#include "gxexhlp.h"
#endif //_GX_EX_HLP_H__

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

#ifndef _GX_EX_TBL_RECSIZE_H__
#include "gxexdef.h"
#endif //_GX_EX_TBL_RECSIZE_H__


#ifndef _UNICODE

// declaration for all classes managing tables in the Excel file

// This is the base class for reading and holding table structures
class CGXExcelTable : public CObject
{
	GRID_DECLARE_DYNAMIC(CGXExcelTable)
public:
	GRID_API CGXExcelTable();
	GRID_API virtual ~CGXExcelTable();

	// operations
	// Read/Write from/to stream
	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength) = 0;
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1) = 0;
	
	virtual DWORD GetTableSize() = 0;
	
	virtual void ResetInternalState() = 0;

	// logging support
	GRID_API virtual void LogText(const TCHAR* pszText);
	GRID_API virtual void LogNumber(int nNum, BOOL bTerminate = FALSE);
	GRID_API virtual void LogXNumber(int nNum, BOOL bTerminate = FALSE);
	
	// continue record support
	// this is used for dealing with continue records
	GRID_API DWORD GetRecordOffset() const;
	GRID_API void SetRecordOffset(DWORD dw, BOOL bInc = TRUE );
	GRID_API void ResetRecordOffset();

	GRID_API DWORD GetRecordLength() const;
	GRID_API void SetRecordLength(DWORD dw);

	// statics
	GRID_API static CGXExcelLogger* GetLogger();
	GRID_API static void SetCanLog(BOOL bCanLog);
	
	GRID_API static BOOL GetOptimizedMode();
	GRID_API static void SetOptimizedMode(BOOL b);

	GRID_API static CGXExcelLogger* s_pLogger;

protected:
	// data
	GRID_API static BOOL m_bCanLog;
	GRID_API static BOOL m_bOptimized;
	// for continue record support
	DWORD m_dwRecordOffset;
	DWORD m_dwRecordLength;
};


// CGXExcelFontTable
struct fontStruct
{
	// construction
	GRID_API fontStruct();
	GRID_API ~fontStruct();

	WORD dyHeight;//2
	WORD grbit;//2
	WORD icv;//2
	WORD bls;//2
	WORD sss;//2
	BYTE uls;//1
	BYTE bFamily;//1
	BYTE bCharSet;//1
	BYTE bReserved;//1
	BYTE cch;//1
	BYTE grbit1;
	WCHAR* pszFontName;//var
	
	GRID_API void Cleanup();
};

// This class should never be constructed and is only used as 
// a default template argument
class _cgxNullClass
{
public:
	GRID_API _cgxNullClass();
	GRID_API ~_cgxNullClass();
};

template<class T, class T1 = _cgxNullClass>
class GRID_API CGXExcelBaseTable : public CGXExcelTable
{
	DECLARE_DYNAMIC(CGXExcelBaseTable)

public:
	typedef CGXExcelBaseTable _base;

	CGXExcelBaseTable()
	{
		ResetInternalState();
	};
	
	virtual ~CGXExcelBaseTable()
	{
		ResetInternalState();
	};

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength) = 0;
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs) = 0;
	virtual DWORD GetTableSize();
	
	virtual BOOL ApplyToObject(DWORD index, T1*& p);

	T1* CreateTableObject()
	{return (T1*)gs_TableObjectManager.CreateObject();};
	
	void RecycleObject(T1* pObject)
	{gs_TableObjectManager.RecycleObject(pObject);};

	BOOL IsIndexValid(DWORD index)
	{return index <= m_dwIndex;};

	virtual void ResetInternalState();

protected:
	virtual BOOL LookupValue(DWORD index, T*& pT);

// implementation
	CMap<DWORD, DWORD&, T*, T*&> m_mapStruct;
	DWORD m_dwIndex;

	CGXCaptiveManager<T1> gs_TableObjectManager;
};


struct CGXExcelFontIndex
{
	GXBYTE8 byte8;
	COLORREF colorIndex;
	UINT nTabIndex;

	inline CGXExcelFontIndex(){
		this->byte8 = 0;
		this->colorIndex = 0;
		this->nTabIndex = 0xFFFF;
	}

	inline CGXExcelFontIndex(const CGXExcelFontIndex& fontIndex){
		this->byte8 = fontIndex.byte8;
		this->colorIndex = fontIndex.colorIndex;
		this->nTabIndex = fontIndex.nTabIndex;
	}

	
	inline CGXExcelFontIndex(GXBYTE8 _byte8, COLORREF _colorIndex, UINT _nTabIndex = 0xFFFF){
		this->byte8 = _byte8;
		this->colorIndex = _colorIndex;
		this->nTabIndex = _nTabIndex;
	}

	inline CGXExcelFontIndex& operator = (const CGXExcelFontIndex& fontIndex){
		this->byte8 = fontIndex.byte8;
		this->colorIndex = fontIndex.colorIndex;
		this->nTabIndex = fontIndex.nTabIndex;
	
		return *this;
	}
	
	inline bool operator == (const CGXExcelFontIndex& fontIndex) const{
		return (this->byte8 == fontIndex.byte8 
			&& this->colorIndex == fontIndex.colorIndex
			&& this->nTabIndex == fontIndex.nTabIndex);
	}

	inline bool operator != (const CGXExcelFontIndex& fontIndex) const{
		return !(*this == fontIndex);
	}
};

template<>
UINT AFXAPI HashKey(const CGXExcelFontIndex& key);

class CGXExcelFontTable : public CGXExcelBaseTable<fontStruct, CGXStyle>
{
	GRID_DECLARE_DYNCREATE(CGXExcelFontTable)

public:
	GRID_API CGXExcelFontTable();
	GRID_API virtual ~CGXExcelFontTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	GRID_API virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyleFont);

	// does a lookup and returns the index of the font in the font table
	GRID_API UINT GetFontIndex(const CGXExcelFontIndex& b) const;
	GRID_API void SetFontIndex(const CGXExcelFontIndex&  b, UINT index);
	GRID_API BOOL IsInitFontIndex(const CGXExcelFontIndex&  b);

	GRID_API virtual WORD TranslateFontToFontEntry(CGXFont& font, BYTE* pszBuffer, const CGXStyle* pStyle);

	
	GRID_API virtual BOOL WriteFontPtrArray( CGXStylePtrArray* pStylePtrArray,
									IStream* pStream, 
									DWORD& dwLength, 
									UINT& nFontIndex,
									const CGXStylesMap* pStylesMap,
									const CGXStyle* pStyleStandard, UINT nTabIndex = 0);

	GRID_API virtual BOOL WriteFormulaFont(int nR, int nCol, IStream* pStream, const CGXStyle*  pStandard,
									const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nFontIndex);

protected:
	GRID_API virtual void ResetInternalState();
	
	//data
	CMap<CGXExcelFontIndex, const CGXExcelFontIndex&, UINT, UINT&> m_mpHashToIndex;
};


// CGXExcelColorTable

struct colorStruct
{
	// construction
	GRID_API colorStruct();
	GRID_API ~colorStruct();
	
	// data
	WORD	num; // size 2: number of entries
	COLORREF* dwValues;

	GRID_API void Cleanup();
};


class CGXExcelColorTable : public CGXExcelBaseTable<colorStruct, CGXStyle>
{
	GRID_DECLARE_DYNCREATE(CGXExcelColorTable)

	enum gxWriteMode
	{	
		gxRead = 0x1,
		gxWrite = 0x2,
	};

public:
	GRID_API CGXExcelColorTable();
	GRID_API virtual ~CGXExcelColorTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	GRID_API virtual COLORREF GetColorAtPalIndex(DWORD index, COLORREF defColor = GX_INVALID);

	// write support
	GRID_API virtual BOOL WriteColorTablePtrArray(CGXStylePtrArray* pStylePtrArray, UINT& nColorIndex);
	GRID_API virtual void WriteStyleColorInfo(const CGXStyle* pStyle, UINT& nColorIndex);
	
	//access
	GRID_API void SetColorWriteIndex(COLORREF ref, UINT& index);
	GRID_API UINT GetColorWriteIndex(COLORREF ref) const;

	GRID_API void SetWriteMode(short b);
	GRID_API short GetWriteMode();

	// This is a special case does not support apply to object mainly because
	// the color can be used in a wide variety of contexts. It is upto the calling
	// object to consider the correct context and apply the color
	// UserGetColorAtPalIndex for this purpose
	GRID_API virtual BOOL ApplyToObject(DWORD index, CGXStyle*& p);

protected:
	// writing support
	CMap<COLORREF, COLORREF&, UINT, UINT&> m_mpColorToIndex;
	short m_gxWriteMode;
};


// CGXExcelStyleTable

struct styleStruct
{
	GRID_API styleStruct();
	GRID_API ~styleStruct();
	
	// data
	WORD	ixfe; //2
	BYTE 	istyBuiltIn; //1
	BYTE	iLevel; //1
	
	WORD	cch; //2
	TCHAR* pVarChar;
	
	WORD wID;

	GRID_API void Cleanup();
};

class CGXExcelStyleTable : public CGXExcelBaseTable<styleStruct, CGXStyle>
{
	GRID_DECLARE_DYNCREATE(CGXExcelStyleTable)

public:
	GRID_API CGXExcelStyleTable();
	GRID_API virtual ~CGXExcelStyleTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	GRID_API virtual BOOL CheckIfUserDefined(const CWordArray& arr, WORD index);
	GRID_API virtual WORD GetBaseStyleID(DWORD index);
};


//CGXExcelXFTable
struct XFStruct
{
	WORD	ifnt;
	WORD	ifmt;	
	WORD	fLocked;	
	WORD	alc;
	WORD	cIndent;
	WORD	dgLeft;
	WORD	icvLeft;
	DWORD	icvTop;
	WORD	icvFore;
	
	GRID_API void Cleanup();
};

class CGXXFArray : public CGXExStyleMap
{
public:
	GRID_API CGXXFArray();
	GRID_API virtual ~CGXXFArray();
	GRID_API virtual void Destroy();
};

struct CGXXFArrayCreator :public CGXCreator<CGXXFArray>
{
	GRID_API virtual CGXXFArray* CreateObject();
};

typedef CGXNodeManagerNor<CGXXFArray> CGXXFArrayManager;

class CGXExcelXFTable : public CGXExcelBaseTable<XFStruct, CGXStyle>
{
	enum gxRowColType
	{
		gxRowColRow,
		gxRowColCol,
		gxRowCol,
	};

	GRID_DECLARE_DYNCREATE(CGXExcelXFTable)

	typedef  CGXExcelBaseTable<XFStruct> _baseClass;

public:
	GRID_API CGXExcelXFTable();
	GRID_API virtual ~CGXExcelXFTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	GRID_API virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);
	
	GRID_API BOOL StyleHelper(XFStruct* pXFStruct, CGXStyle* pStyle);
	GRID_API BOOL CellHelper(XFStruct* pXFStruct, CGXStyle* pStyle);

	//access
	GRID_API CGXExStyleMap& GetExcelStyleMap(UINT index);
	GRID_API CGXExStyleIDMap& GetExcelBStyleMap();
	
	// these functions are to be used only when reading/writing sheet data
	// never for global data
	GRID_API ROWCOL GetCurrentReadCol();
	GRID_API ROWCOL GetCurrentReadRow();
	GRID_API UINT GetCurrentReadIndex();
	
	GRID_API void SetCurrentReadCol(ROWCOL nCol);
	GRID_API void SetCurrentReadRow(ROWCOL nRow);
	GRID_API void SetCurrentReadIndex(UINT nIndex);


protected:
	GRID_API virtual void ResetInternalState();

	GRID_API virtual int TranslatePattern(int index, BOOL bToGrid = TRUE);
	
	GRID_API virtual void TranslateStyleToXF(const CGXStyle* pStyle, BYTE* pszBuffer, BOOL bStyle = TRUE, const CGXStylesMap* pStylesMap = NULL, BOOL bStandardStyle = FALSE, UINT nTab = 0xffff);
	GRID_API virtual void TranslateStyleToStyleXF(const CGXStyle* pStyle, BYTE* pszBuffer, const CGXStylesMap* pStylesMap);
	GRID_API virtual void TranslateStyleToCellXF(const CGXStyle* pStyle, BYTE* pszBuffer, const CGXStylesMap* pStylesMap = NULL, BOOL bStandard = FALSE, UINT nTab = 0xffff);

	GRID_API virtual BOOL WriteStylePtrArray(     CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* pStandardStyle,
										 UINT nC,
										 const CGXStylesMap* pStylesMap = NULL,
										 BOOL bStyle = TRUE
								   );

	GRID_API virtual BOOL WriteComposedStylePtrArray(CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* pStandardStyle,
										 UINT nC,
										 const CGXStylesMap* pStylesMap = NULL,
										 BOOL bStyle = TRUE,
										 CGXStylePtrArray* pColStylePtrArray = NULL,
										 CGXStylePtrArray* pRowStylePtrArray = NULL						
								   );


	GRID_API virtual BOOL WriteFormulaStyle(int nR, int nCol, IStream* pStream, const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nStyleIndex, UINT nC);

	GRID_API virtual BOOL SetPenStyle(WORD wStyle, CGXPen& pen);
	GRID_API WORD GetPenStyle(CGXPen& pen);
	
	GRID_API virtual WORD GetDefaultExcelBorder();
	GRID_API virtual WORD GetDefaultExcelBorderColor();

	// data
	//CGXExStyleMap m_mpStyleMap;
	CGXExStyleIDMap m_mpStyleIDMap;
	CArray<int, int> m_ArrPattern;
	CGXXFArrayManager* m_pArManager;
	
	ROWCOL m_iCurRow;
	ROWCOL m_iCurCol;
	UINT m_uinTab;
};


struct formatStruct
{
	WORD	ifmt;
	BYTE	cch;	
	TCHAR*	pVarFormat;

	GRID_API void Cleanup();
};

// class GRID_API CGXExcelFormatTable
class CGXExcelFormatTable : public CGXExcelBaseTable<formatStruct, CGXStyle>
{
	GRID_DECLARE_DYNCREATE(CGXExcelFormatTable)

	typedef  CGXExcelBaseTable<formatStruct> _baseClass;

public:
	GRID_API CGXExcelFormatTable();
	GRID_API virtual ~CGXExcelFormatTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	GRID_API virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);

	GRID_API virtual COLORREF GetDefaultNegativeStateColor();
	GRID_API virtual WORD GetExcelIndexForWrite(const CGXStyle* pStyle);
};


struct _sst
{
	// construction
	GRID_API _sst();
	GRID_API ~_sst();

	// data
	WORD cch;
	BYTE grbit;
	WCHAR* pszValue;
	
	WORD wRuns;

	GRID_API void Cleanup();
};

// sstStruct
struct sstStruct
{
	GRID_API sstStruct();
	GRID_API ~sstStruct();
	
	DWORD	cstTotal;
	DWORD	cstUnique;	
	_sst*	pStrings;

	GRID_API void Cleanup();
};

class CGXExcelSSTTable : public CGXExcelBaseTable<sstStruct, CGXStyle>
{
	GRID_DECLARE_DYNCREATE(CGXExcelSSTTable)

public:
	GRID_API CGXExcelSSTTable();
	GRID_API virtual ~CGXExcelSSTTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	GRID_API virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);
};


// CGXExcelBoundSheetTable

struct BoundSheetStruct
{
	GRID_API BoundSheetStruct();
		
	DWORD dwOffsetPos;
	WORD grbit;
	WORD cch;
	TCHAR* pszName;
		
	GRID_API void Cleanup();
} ;

class CGXExcelBoundSheetTable : public CGXExcelBaseTable<BoundSheetStruct, CString>
{
	GRID_DECLARE_DYNCREATE(CGXExcelBoundSheetTable)

	typedef CArray<DWORD, DWORD&> CGXExOffsetArray;

public:
	// construction
	GRID_API CGXExcelBoundSheetTable();
	GRID_API virtual ~CGXExcelBoundSheetTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream,DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	GRID_API virtual BOOL ApplyToObject(DWORD index, CString*& pStrName);
	GRID_API virtual void ResetInternalState();

	// access
	GRID_API CGXExOffsetArray* GetBOFOffsetArray();
	GRID_API DWORD GetOffsetPos() const;
	GRID_API void  SetOffsetPos(DWORD dw);

	GRID_API BOOL GetSeekMode() const;
	GRID_API void  SetSeekMode(BOOL b);

	GRID_API BoundSheetStruct* LookupOffsetStruct(DWORD index);
protected:
	CArray<DWORD, DWORD&>	m_ArOffsetPos;
	DWORD					m_dwOffsetPos;
	BOOL					m_bSeekMode;
};


struct sfStruct
{
	GRID_API sfStruct();

	WORD rwFirst;
	WORD rwLast;
	BYTE colFirst;
	BYTE colLast;
	WORD cce;
	BYTE* pVar;

	static DWORD GetFixedSize()
	{
		return (3*sizeof(WORD) + 2*sizeof(BYTE));
	}
	
	GRID_API void Cleanup();
};



class CGXExcelSharedFormulaTable : public CGXExcelBaseTable<sfStruct, formulaStruct>
{
	GRID_DECLARE_DYNCREATE(CGXExcelSharedFormulaTable)

public:
	// construction
	GRID_API CGXExcelSharedFormulaTable();
	GRID_API virtual ~CGXExcelSharedFormulaTable();

	GRID_API virtual BOOL ReadFromStream(IStream* pStream,DWORD dwLength);
	GRID_API virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	GRID_API virtual BOOL ApplyToObject(DWORD index, formulaStruct*& pFS);
	GRID_API virtual void ResetInternalState();

	GRID_API DWORD GetCompositeIndex(WORD nRow, WORD nCol);

	// interface
	GRID_API virtual BOOL LookupSharedFormula(WORD nRow, WORD nCol);
	GRID_API BOOL ApplyToObject(WORD nRow, WORD nCol, formulaStruct*& pFS);
};


//
// GridMFC extension DLL
// reset declaration context
//

#endif

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif //_GX_EXTBL_H__
