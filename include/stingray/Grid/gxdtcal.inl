///////////////////////////////////////////////////////////////////////////////
// gxdtcal.inl
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

#pragma once

#if _MFC_VER >= 0x0400 && defined(GX_INLINE)

GX_INLINE BOOL CGXBDateTimeCtrl::IsHourPM()
	{ return m_bHourPM; }

// Accessing elements
GX_INLINE CGXBDTGadget* CGXBDateTimeCtrl::CGXBDTGadgetArray::GetAt(int nIndex) const
	{ return (CGXBDTGadget*)CObArray::GetAt(nIndex); }

GX_INLINE CGXBDTGadget*& CGXBDateTimeCtrl::CGXBDTGadgetArray::ElementAt(int nIndex)
	{ return (CGXBDTGadget*&)CObArray::ElementAt(nIndex); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::SetAt(int nIndex, CGXBDTGadget* ptr)
	{ CObArray::SetAt(nIndex, ptr); }

// Potentially growing the array
GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::SetAtGrow(int nIndex, CGXBDTGadget* newElement)
   { CObArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXBDateTimeCtrl::CGXBDTGadgetArray::Add(CGXBDTGadget* newElement)
   { return (int)CObArray::Add(newElement); }

GX_INLINE int CGXBDateTimeCtrl::CGXBDTGadgetArray::Append(const CGXBDTGadgetArray& src)
   { return (int)CObArray::Append(src); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::Copy(const CGXBDTGadgetArray& src)
	{ CObArray::Copy(src); }

// Operations that move elements around
GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::InsertAt(int nIndex, CGXBDTGadget* newElement, int nCount)
	{ CObArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::InsertAt(int nStartIndex, CGXBDTGadgetArray* pNewArray)
   { CObArray::InsertAt(nStartIndex, pNewArray); }

// overloaded operator helpers
GX_INLINE CGXBDTGadget* CGXBDateTimeCtrl::CGXBDTGadgetArray::operator[](int nIndex) const
	{ return (CGXBDTGadget*)CObArray::operator[](nIndex); }

GX_INLINE CGXBDTGadget*& CGXBDateTimeCtrl::CGXBDTGadgetArray::operator[](int nIndex)
	{ return (CGXBDTGadget*&)CObArray::operator[](nIndex); }

#endif // GX_INLINE

