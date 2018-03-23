///////////////////////////////////////////////////////////////////////////////
// GXCOLL.inl
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

#pragma once

#ifdef GX_INLINE

GX_INLINE GXNDX::GXNDX()
	{ nRow = 0; nCol = 0; }

GX_INLINE GXNDX::GXNDX(const GXNDX& r)
	{ nRow = r.nRow; nCol = r.nCol; }

GX_INLINE GXNDX::GXNDX(ROWCOL r, ROWCOL c)
	{ nRow = r; nCol = c; }

GX_INLINE GXNDX::operator DWORD()
	{ return (DWORD) MAKELONG(nRow, nCol); }   // needed for CMapNdxTopOb

////////////////////////////////////////////////////////////////////////////

// assignment
GX_INLINE const GXNDX& GXNDX::operator=(const GXNDX& r)
	{ nRow = r.nRow; nCol = r.nCol; return (*this); }

GX_INLINE int CGXCollMapDWordToString::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXCollMapDWordToString::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXCollMapDWordToString::SetAt(DWORD key, LPCTSTR newValue)
	{ CString& value = (*this)[key]; value.Empty(); value = newValue; }
GX_INLINE POSITION CGXCollMapDWordToString::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXCollMapDWordToString::GetHashTableSize() const
	{ return m_nHashTableSize; }

// type conversions

GX_INLINE GXNDX AFXAPI RowColToNdx(ROWCOL nRow, ROWCOL nCol)
	{ GXNDX rcndx; rcndx.nRow = nRow; rcndx.nCol = nCol; return rcndx; }

GX_INLINE ROWCOL AFXAPI NdxToRow(GXNDX Ndx)
	{ return Ndx.nRow; }

GX_INLINE ROWCOL AFXAPI NdxToCol(GXNDX Ndx)
	{ return Ndx.nCol; }

GX_INLINE BOOL AFXAPI operator==(const GXNDX& rc1, const GXNDX& rc2)
	{ return rc1.nRow == rc2.nRow && rc1.nCol == rc2.nCol; }

GX_INLINE BOOL AFXAPI operator!=(const GXNDX& rc1, const GXNDX& rc2)
	{ return rc1.nRow != rc2.nRow || rc1.nCol != rc2.nCol; }

GX_INLINE CArchive& AFXAPI operator <<(CArchive& ar, const GXNDX& ndx)
	{ return ar << ndx.nRow << ndx.nCol; }

GX_INLINE CArchive& AFXAPI operator >>(CArchive& ar, GXNDX& ndx)
	{ return ar >> ndx.nRow >> ndx.nCol; }

////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXCollMapDWordToLong::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXCollMapDWordToLong::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXCollMapDWordToLong::SetAt(DWORD key, LONG newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXCollMapDWordToLong::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXCollMapDWordToLong::GetHashTableSize() const
	{ return m_nHashTableSize; }

////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXCollMapDWordToPtr::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXCollMapDWordToPtr::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXCollMapDWordToPtr::SetAt(DWORD key, void* newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXCollMapDWordToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXCollMapDWordToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }

////////////////////////////////////////////////////////////////////////////

GX_INLINE int CMapNdxToOb::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CMapNdxToOb::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CMapNdxToOb::SetAt(GXNDX key, CObject* newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CMapNdxToOb::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CMapNdxToOb::GetHashTableSize() const
	{ return m_nHashTableSize; }

////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXCollMapStringToWord::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXCollMapStringToWord::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXCollMapStringToWord::SetAt(LPCTSTR key, WORD newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXCollMapStringToWord::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXCollMapStringToWord::GetHashTableSize() const
	{ return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXCollMapStringToHandle::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXCollMapStringToHandle::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXCollMapStringToHandle::SetAt(LPCTSTR key, HANDLE newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXCollMapStringToHandle::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXCollMapStringToHandle::GetHashTableSize() const
	{ return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXMapByte8ToPtr::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXMapByte8ToPtr::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXMapByte8ToPtr::SetAt(GXBYTE8 key, void* newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXMapByte8ToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXMapByte8ToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }

////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXMapFontData::GetCount() const
	{ return m_nCount; }
GX_INLINE BOOL CGXMapFontData::IsEmpty() const
	{ return m_nCount == 0; }
GX_INLINE void CGXMapFontData::SetAt(GXBYTE8 key, CGXFontData& newValue)
	{ (*this)[key] = newValue; }
GX_INLINE POSITION CGXMapFontData::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
GX_INLINE UINT CGXMapFontData::GetHashTableSize() const
	{ return m_nHashTableSize; }
               
////////////////////////////////////////////////////////////////////////////

GX_INLINE int CGXSortInfoArray::GetSize() const
	{ return m_nSize; }
GX_INLINE int CGXSortInfoArray::GetUpperBound() const
	{ return m_nSize-1; }
GX_INLINE void CGXSortInfoArray::RemoveAll()
	{ SetSize(0); }
GX_INLINE CGXSortInfo CGXSortInfoArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
GX_INLINE void CGXSortInfoArray::SetAt(int nIndex, CGXSortInfo newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }
GX_INLINE CGXSortInfo& CGXSortInfoArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
GX_INLINE const CGXSortInfo* CGXSortInfoArray::GetData() const
	{ return (const CGXSortInfo*)m_pData; }
GX_INLINE CGXSortInfo* CGXSortInfoArray::GetData()
	{ return (CGXSortInfo*)m_pData; }
GX_INLINE int CGXSortInfoArray::Add(CGXSortInfo newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }
GX_INLINE CGXSortInfo CGXSortInfoArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
GX_INLINE CGXSortInfo& CGXSortInfoArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }

/////////////////////////////////////////////////////////////////////////////
// CGXPtrArrayPtrArray

GX_INLINE CGXPtrArrayPtrArray::CGXPtrArrayPtrArray()
	{ };

GX_INLINE CPtrArray* CGXPtrArrayPtrArray::GetAt(int nIndex) const
	{ return (CPtrArray*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXPtrArrayPtrArray::SetAt(int nIndex, CPtrArray* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXPtrArrayPtrArray::SetAtGrow(int nIndex, CPtrArray* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXPtrArrayPtrArray::Add(CPtrArray* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CPtrArray* CGXPtrArrayPtrArray::operator[](int nIndex) const
	{ return (CPtrArray*) CPtrArray::operator[](nIndex); }

GX_INLINE CPtrArray*& CGXPtrArrayPtrArray::operator[](int nIndex)
	{ return (CPtrArray*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXPtrArrayPtrArray::InsertAt(int nIndex, CPtrArray* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXPtrArrayPtrArray::InsertAt(int nStartIndex, CGXPtrArrayPtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////

#endif // GX_INLINE

