///////////////////////////////////////////////////////////////////////////////
// Otlbase.h
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

#ifndef __OTLBASE_H__
#define __OTLBASE_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _ATL_VER 
#if (_ATL_VER < 0x0300)		
#error The Objective Toolkit PRO ATL components require VC++ 6.0 and ATL version 3.0 or higher. Stopping compilation!
#endif	//_ATL_VER < 0x0300
#endif	//_ATL_VER

#ifndef _ATL_NO_DEBUG_CRT
	#include <crtdbg.h>
#endif


// OTL Version information

#if !defined(_OTL)
#define _OTL
#endif

#if !defined(OTL_VER)
#define OTL_VER 0x0200
#endif

#define OTL_VER_MAJOR	HIBYTE(OTL_VER)
#define OTL_VER_MINOR	LOBYTE(OTL_VER)

// Legacy
#define STINGRAY_OTLVER OTL_VER

/////////////////////////////////////////////////////////////////////////////
// Win64 compatibility
#ifndef SEC_IA64_TYPES
#define SEC_IA64_TYPES

#ifdef _WIN64

typedef INT_PTR SEC_INT, *SEC_PINT;
typedef UINT_PTR SEC_UINT, *SEC_PUINT;
typedef ULONG_PTR SEC_ULONG, *SEC_PULONG;
typedef LONG_PTR SEC_LONG, *SEC_PLONG;
typedef DWORD_PTR SEC_DWORD, *SEC_PDWORD;

#else	//WIN32

typedef int SEC_INT, *SEC_PINT;
typedef unsigned int SEC_UINT, *SEC_PUINT;
typedef unsigned long SEC_ULONG, *SEC_PULONG;
typedef long SEC_LONG, *SEC_PLONG;
typedef unsigned long SEC_DWORD, *SEC_PDWORD;

#endif	//_WIN64

#endif	//SEC_IA64_TYPES

#ifdef _WIN64
// STL causes numerous truncation warnings. Ignore these till an updated version of the SDK is available
#pragma warning(disable : 4018 4146 4244)
#endif	//_WIN64

/////////////////////////////////////////////////////////////////////////////

#ifndef OTLASSERT
#define OTLASSERT(expr) _ASSERTE(expr)
#endif

namespace StingrayOTL
{
	inline int OtlRectWidth(const RECT& rect) { return rect.right - rect.left; }
	inline int OtlRectHeight(const RECT& rect) { return rect.bottom - rect.top; }
	inline int OtlRectWidth(LPCRECT prect) 
	{ 
		OTLASSERT(prect);
		return prect->right - prect->left; 
	}
	inline int OtlRectHeight(LPCRECT prect) 
	{ 
		OTLASSERT(prect);
		return prect->bottom - prect->top; 
	}


};	// namespace StingrayOTL

using namespace StingrayOTL;

#endif // __OTLBASE_H__
