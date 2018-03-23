///////////////////////////////////////////////////////////////////////////////
// MFCMI.h : MFC Multiple Inheritance convenience macros
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
// Author:       Mark Isham
// Description:  MFC Multiple Inheritance convenience macros
//
// $Header: $
// $NoKeywords: $

#ifndef SECMI_MACROS_H
#define SECMI_MACROS_H

//
// When using multiple inheritence (MI) with MFC, ambiguous CObject parent
// methods must be resolved. Using MI with 2 or more CWnd derived 
// objects is not recommended!
// (Please refer to MSDN technote TN016 for more information).
// 


// The macro SEC_MFC_MI is used below to cleanly resolve the 
// obvious CObject collisions that result from MI. If further exploitation
// of CObject is performed, you may also need to resolve other 
// CObject collisions (Serialize, Dump, etc.) in a similar fashion. Also, 
// the runtime CObject type checking, such as ASSERT_KINDOF, will only work 
// for the 1 base class fed to the SEC_IMPLEMENT_DYNCREATE (or IMPLEMENT_DYNAMIC) 
// macro (despite the fact that in a true OO sense, the object has an 
// "IsKindOf" relationship to all these base classes).

//
// Use this macro inside the "public" section of your class header:
//
#if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)					
#define SEC_MFC_MI(base) \
	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine) \
		{ return base::operator new(nSize,lpszFileName,nLine); } \
    void* operator new(size_t nSize)					\
        { return base::operator new(nSize); }			\
    void operator delete(void* p)						\
        { base::operator delete(p); }					\
	BOOL IsKindOf(const CRuntimeClass* pClass) const 	\
		{ return base::IsKindOf(pClass); }

#else
#define SEC_MFC_MI(base) 								\
    void* operator new(size_t nSize)					\
        { return base::operator new(nSize); }			\
    void operator delete(void* p)						\
        { base::operator delete(p); }					\
	BOOL IsKindOf(const CRuntimeClass* pClass) const 	\
		{ return base::IsKindOf(pClass); }
#endif

//
// Use this macro in place of IMPLEMENT_DYNCREATE in your
// implementation file.
//
#if _MFC_VER > 0x0410
#define SEC_IMPLEMENT_RUNTIMECLASS IMPLEMENT_RUNTIMECLASS
#else
#define SEC_IMPLEMENT_RUNTIMECLASS _IMPLEMENT_RUNTIMECLASS
#endif

#define SEC_IMPLEMENT_DYNCREATE(class_name, base_class_name) 	\
	CObject* PASCAL class_name::CreateObject() 					\
		{ return (base_class_name *)new class_name; } 			\
	SEC_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)



#endif		// SECMI_MACROS_H

