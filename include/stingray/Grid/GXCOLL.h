///////////////////////////////////////////////////////////////////////////////
// GXCOLL.h
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

#ifndef _GXCOLL_H_
#define _GXCOLL_H_

#ifndef __AFX_H__
#include <afx.h>
#endif

#include "StingrayExportDefs.h"
 
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

// classes declared in this header file:

class CGXNDX;
class CGXCollMapDWordToString;	// CGXStylesMap: m_ControlMap, AppendOG5Map
class CGXCollMapDWordToLong;	// 
class CGXCollMapDWordToPtr;		// User property info map: m_UserPropertyInfoMap
class CMapNdxToOb;		
class CGXCollMapStringToWord;   // base styles: m_mswNameId
class CGXMapDWordToLong;		// row heights: m_RowHeights
class CGXMapCellToOb;

class GXNDX
{
public:
	// construction
	GRID_API GXNDX();
	GRID_API GXNDX(const GXNDX& r);
	GRID_API GXNDX(ROWCOL r, ROWCOL c);

	GRID_API operator DWORD();

	// assignment
	GRID_API const GXNDX& operator=(const GXNDX& r);

	// data
	ROWCOL  nRow;
	ROWCOL  nCol;
};

// Row, Col (ROWCOL) to GXNDX Index
GRID_API GXNDX     AFXAPI RowColToNdx(ROWCOL nRow, ROWCOL nCol);
GRID_API ROWCOL    AFXAPI NdxToRow(GXNDX Ndx);
GRID_API ROWCOL    AFXAPI NdxToCol(GXNDX Ndx);
GRID_API BOOL AFXAPI operator==(const GXNDX& rc1, const GXNDX& rc2);
GRID_API BOOL AFXAPI operator!=(const GXNDX& rc1, const GXNDX& rc2);
GRID_API CArchive& AFXAPI operator <<(CArchive& ar, const GXNDX& ndx);
GRID_API CArchive& AFXAPI operator >>(CArchive& ar, GXNDX& ndx);


#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif

struct CGXPlex    // warning variable length structure
{
	CGXPlex* pNext;
	UINT nMax;
	UINT nCur;
	/* BYTE data[maxNum*elementSize]; */

	inline void* data() { return this+1; }

	GRID_API static CGXPlex* PASCAL Create(CGXPlex*& head, UINT nMax, UINT cbElement);
			// like 'calloc' but no zero fill
			// may throw memory exceptions

	GRID_API void FreeDataChain();       // free this one and links
};

#ifdef AFX_COLL_SEG
#pragma code_seg()
#endif

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToString : public CObject
{

	GRID_DECLARE_SERIAL(CGXCollMapDWordToString)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		CString value;
	};
public:

// Construction
	GRID_API CGXCollMapDWordToString(int nBlockSize=10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(DWORD key, CString& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API CString& operator[](DWORD key);

	// add a new (key, value) pair
	GRID_API void SetAt(DWORD key, LPCTSTR newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(DWORD key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, CString& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	GRID_API virtual ~CGXCollMapDWordToString();

	GRID_API void Serialize(CArchive&);
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToLong : public CObject
{

	GRID_DECLARE_SERIAL(CGXCollMapDWordToLong)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		LONG value;
	};
public:

// Construction
	GRID_API CGXCollMapDWordToLong(int nBlockSize=10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(DWORD key, LONG& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API LONG& operator[](DWORD key);

	// add a new (key, value) pair
	GRID_API void SetAt(DWORD key, LONG newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(DWORD key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, LONG& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	GRID_API virtual ~CGXCollMapDWordToLong();

	GRID_API void Serialize(CArchive&);
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif
	friend class CGXCollMapDWordToLongFTR;
};


/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToPtr : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXCollMapDWordToPtr)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		void* value;
	};

public:

// Construction
	GRID_API CGXCollMapDWordToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(DWORD key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API void*& operator[](DWORD key);

	// add a new (key, value) pair
	GRID_API void SetAt(DWORD key, void* newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(DWORD key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, void*& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc**	m_pHashTable;
	UINT		m_nHashTableSize;
	int			m_nCount;
	CAssoc*		m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int			m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	GRID_API virtual ~CGXCollMapDWordToPtr();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef DWORD BASE_KEY;
	typedef DWORD BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CMapNdxToOb : public CObject
{

	GRID_DECLARE_SERIAL(CMapNdxToOb)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXNDX key;
		CObject* value;
	};

public:

// Construction
	GRID_API CMapNdxToOb(int nBlockSize = 10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(GXNDX key, CObject*& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API CObject*& operator[](GXNDX key);

	// add a new (key, value) pair
	GRID_API void SetAt(GXNDX key, CObject* newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(GXNDX key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, GXNDX& rKey, CObject*& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(GXNDX key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(GXNDX, UINT&) const;

public:
	GRID_API virtual ~CMapNdxToOb();

	GRID_API void Serialize(CArchive&);
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXNDX BASE_KEY;
	typedef GXNDX BASE_ARG_KEY;
	typedef CObject* BASE_VALUE;
	typedef CObject* BASE_ARG_VALUE;
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapStringToWord : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXCollMapStringToWord)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		CString key;
		WORD value;
	};
public:

// Construction
	GRID_API CGXCollMapStringToWord(int nBlockSize=10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(LPCTSTR key, WORD& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API WORD& operator[](LPCTSTR key);

	// add a new (key, value) pair
	GRID_API void SetAt(LPCTSTR key, WORD newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(LPCTSTR key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, CString& rKey, WORD& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(LPCTSTR key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(LPCTSTR, UINT&) const;

public:
	GRID_API virtual ~CGXCollMapStringToWord();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapStringToHandle : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXCollMapStringToHandle)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		CString key;
		HANDLE value;
	};
public:

// Construction
	GRID_API CGXCollMapStringToHandle(int nBlockSize=10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(LPCTSTR key, HANDLE& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API HANDLE& operator[](LPCTSTR key);

	// add a new (key, value) pair
	GRID_API void SetAt(LPCTSTR key, HANDLE newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(LPCTSTR key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, CString& rKey, HANDLE& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(LPCTSTR key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(LPCTSTR, UINT&) const;

public:
	GRID_API virtual ~CGXCollMapStringToHandle();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif
};

// header file

class CGXMapDWordToLong : public CGXCollMapDWordToLong	// Row Heights
{
	GRID_DECLARE_SERIAL(CGXMapDWordToLong)

public:
	// Inserting Colums or Rows
	GRID_API void   Insert(DWORD nId, DWORD nCount);

	// Removing Colums or Rows
	GRID_API void   Remove(DWORD nFrom, DWORD nTo);

	// Moving Colums or Rows
	GRID_API void   Move(DWORD nFrom, DWORD nTo, DWORD nDest);

	GRID_API virtual CGXMapDWordToLong& operator=(const CGXMapDWordToLong& map);
};


class CGXMapCellToOb : public CMapNdxToOb
{
	GRID_DECLARE_SERIAL(CGXMapCellToOb)

public:
	// Inserting Colums or Rows
	GRID_API void   InsertRows(DWORD nRow, DWORD nCount);
	GRID_API void   InsertCols(DWORD nCol, DWORD nCount);

	// Removing Colums or Rows
	GRID_API void   RemoveRows(DWORD nFromRow, DWORD nToRow);
	GRID_API void   RemoveCols(DWORD nFromCol, DWORD nToCol);

	// Moving Colums or Rows
	GRID_API void   MoveRows(DWORD nFromRow, DWORD nToRow, DWORD nDestRow);
	GRID_API void   MoveCols(DWORD nFromCol, DWORD nToCol, DWORD nDestCol);
};

// CGXBitArray allows you to insert, move and remove specific
// bits in an array of bytes. The class lets you directly store
// and retrieve bits. The bits can be serialized just like a
// normal CByteArray.

class CGXBitArray : public CByteArray
{
public:
	GRID_API BOOL SetBitAt(DWORD dwIndex, BOOL bValue);
	GRID_API BOOL GetBitAt(DWORD dwIndex);
	GRID_API void RemoveBits(DWORD dwFrom, DWORD dwTo);
	GRID_API void MoveBits(DWORD nFrom, DWORD nTo, DWORD nDest);
	GRID_API void InsertBits(DWORD nFrom, DWORD nCount);
};

/////////////////////////////////////////////////////////////////////////////

class CGXMapByte8ToPtr : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXMapByte8ToPtr)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXBYTE8 key;
		void* value;
	};

public:

// Construction
	GRID_API CGXMapByte8ToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(GXBYTE8 key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API void*& operator[](GXBYTE8 key);

	// add a new (key, value) pair
	GRID_API void SetAt(GXBYTE8 key, void* newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(GXBYTE8 key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, GXBYTE8& rKey, void*& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(GXBYTE8 key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(GXBYTE8, UINT&) const;

public:
	GRID_API virtual ~CGXMapByte8ToPtr();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXBYTE8 BASE_KEY;
	typedef GXBYTE8 BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};

// create LOGFONT structure on demand and use reference count
struct GRID_API CGXFontData
{
	long nRefs;     // reference count
	LOGFONT lf;
	unsigned bInit            : 1;  // TRUE when LOGFONT is initialized
};


/////////////////////////////////////////////////////////////////////////////

class CGXMapFontData : public CObject
{

	GRID_DECLARE_DYNAMIC(CGXMapFontData)
protected:
	// Association
	struct GRID_API CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXBYTE8 key;
		CGXFontData value;
	};

public:

// Construction
	GRID_API CGXMapFontData(int nBlockSize = 10);

// Attributes
	// number of elements
	GRID_API int GetCount() const;
	GRID_API BOOL IsEmpty() const;

	// Lookup
	GRID_API BOOL Lookup(GXBYTE8 key, CGXFontData& rValue) const;

// Operations
	// Lookup and add if not there
	GRID_API CGXFontData& operator[](GXBYTE8 key);

	// add a new (key, value) pair
	GRID_API void SetAt(GXBYTE8 key, CGXFontData& newValue);

	// removing existing (key, ?) pair
	GRID_API BOOL RemoveKey(GXBYTE8 key);
	GRID_API void RemoveAll();

	// iterating all (key, value) pairs
	GRID_API POSITION GetStartPosition() const;
	GRID_API void GetNextAssoc(POSITION& rNextPosition, GXBYTE8& rKey, CGXFontData& rValue) const;

	// advanced features for derived classes
	GRID_API UINT GetHashTableSize() const;
	GRID_API void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	GRID_API UINT HashKey(GXBYTE8 key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct GRID_API CGXPlex* m_pBlocks;
	int m_nBlockSize;

	GRID_API CAssoc* NewAssoc();
	GRID_API void FreeAssoc(CAssoc*);
	GRID_API CAssoc* GetAssocAt(GXBYTE8, UINT&) const;

public:
	GRID_API virtual ~CGXMapFontData();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXBYTE8 BASE_KEY;
	typedef GXBYTE8 BASE_ARG_KEY;
	typedef CGXFontData BASE_VALUE;
	typedef CGXFontData& BASE_ARG_VALUE;
};
               
struct CGXSortInfo
{
	ROWCOL nRC;

	enum SortType
	{
		numeric,
		alphanumeric,
		date,
		absolute, // Added per Caterpillar Enhancement
		autodetect
	} sortType;

	enum SortOrder
	{
		ascending,
		descending
	} sortOrder;

	BOOL bCase;		// TRUE==case sensitive, FALSE==not
	DWORD dwCookie; // 32-Bit value you can use to pass a cookie to your own sorting routins

	// Reserved:
	BOOL bOnlyNum;
	BOOL bOnlyDate;

	GRID_API CGXSortInfo();
};

class CGXSortInfoArray : public CObject
{
	GRID_DECLARE_DYNAMIC(CGXSortInfoArray)
public:

// Construction
	GRID_API CGXSortInfoArray();

// Attributes
	GRID_API int GetSize() const;
	GRID_API int GetUpperBound() const;
	GRID_API void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	GRID_API void FreeExtra();
	GRID_API void RemoveAll();

	// Accessing elements
	GRID_API CGXSortInfo GetAt(int nIndex) const;
	GRID_API void SetAt(int nIndex, CGXSortInfo newElement);
	GRID_API CGXSortInfo& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	GRID_API const CGXSortInfo* GetData() const;
	GRID_API CGXSortInfo* GetData();

	// Potentially growing the array
	GRID_API void SetAtGrow(int nIndex, CGXSortInfo newElement);
	GRID_API int Add(CGXSortInfo newElement);
	GRID_API int Append(const CGXSortInfoArray& src);
	GRID_API void Copy(const CGXSortInfoArray& src);

	// overloaded operator helpers
	GRID_API CGXSortInfo operator[](int nIndex) const;
	GRID_API CGXSortInfo& operator[](int nIndex);

	// Operations that move elements around
	GRID_API void InsertAt(int nIndex, CGXSortInfo newElement, int nCount = 1);
	GRID_API void RemoveAt(int nIndex, int nCount = 1);
	GRID_API void InsertAt(int nStartIndex, CGXSortInfoArray* pNewArray);

// Implementation
protected:
	CGXSortInfo* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	GRID_API virtual ~CGXSortInfoArray();
#ifdef _DEBUG
	GRID_API void Dump(CDumpContext&) const;
	GRID_API void AssertValid() const;
#endif

protected:
	// local typedefs for class templates
	typedef CGXSortInfo BASE_TYPE;
	typedef CGXSortInfo BASE_ARG_TYPE;
};

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXPtrArrayPtrArray

// type-safe CPtrArray for array with CPtrArray objects

class CGXPtrArrayPtrArray: public CPtrArray
{
	GRID_DECLARE_DYNAMIC(CGXPtrArrayPtrArray)

public:
	// Construcion/Destruction
	GRID_API CGXPtrArrayPtrArray();
	GRID_API virtual ~CGXPtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	GRID_API void DeleteAll();   // delete all referenced objects
	GRID_API void DeleteAt(int nIndex, int nCount = 1);
	GRID_API void Move(int nIndex, int nCount, int nDest);

public:
	// Accessing elements
	GRID_API CPtrArray* GetAt(int nIndex) const;
	GRID_API void SetAt(int nIndex, CPtrArray* newElement);

	// Potentially growing the array
	GRID_API void SetAtGrow(int nIndex, CPtrArray* newElement);
	GRID_API int Add(CPtrArray* newElement);

	// overloaded operator helpers
	GRID_API CPtrArray* operator[](int nIndex) const;
	GRID_API CPtrArray*& operator[](int nIndex);

	// Operations that move elements around
	GRID_API void InsertAt(int nIndex, CPtrArray* newElement, int nCount = 1);
	GRID_API void InsertAt(int nStartIndex, CGXPtrArrayPtrArray* pNewArray);
};

/////////////////////////////////////////////////////////////////////////////
// Some helper classes

GRID_API void AFXAPI GXDeleteAllObjects(CMapPtrToPtr& ptmap);
GRID_API void AFXAPI GXDeleteAllObjects(CObList& oblist);
GRID_API void AFXAPI GXDeleteAllObjects(CObArray& obarray);

class CGXAutoDeleteObList: public CObList
{
	GRID_API virtual ~CGXAutoDeleteObList();
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "gxcoll.inl"
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

#endif // _GXCOLL_H_
