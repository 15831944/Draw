// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
///////////////////////////////////////////////////////////////////////////////
// GXVER.h
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

// gxver.h : Version Info for Objective Grid
//

#ifndef _GXVER_H_
#define _GXVER_H_

/////////////////////////////////////////////////////////////////////////////
// Master version numbers
/////////////////////////////////////////////////////////////////////////////
#define _GX 0

/*
#if (_MFC_VER > 0x0900)
// If you get this warning message, call Stingray for an update to
// Objective Grid that is compatible with this version of MFC.
#pragma message("Warning! This release of Objective Grid is not supported with versions")
#pragma message("         of MFC newer than 9.00. Contact Roguewave Software to obtain an update.")
#endif
*/

// The 7.1 release of MFC deprecates CDaoRecordSet
//#if (_MFC_VER == 0x0710 || _MFC_VER == 0x0800)
//	#if !defined _GXSAMPLE
//		#pragma warning(disable : 4995)
//		#pragma message("Warning! CDaoRecordSet deprecated as of MFC version 7.1 and higher.")
//		#pragma message("         CGXDaoGrid will not work properly on these compilers.")
//		#pragma message("         Do NOT unselect the DAO options in the Objective Grid build wizard.")
//		#pragma message("         Some functions are required by the Objective Grid Library.")
//	#endif
//#endif

/////////////////////////////////////////////////////////////////////////////
// Win16 libraries

#ifndef _GXNOAUTOLIB

#ifndef _GXCONFIG_H_
#include "config/gxstndrd.h"
#endif

#if !defined(_GXNOMSG) && _MFC_VER < 0x0300		// 16 bit
	#if !(defined(_GXDLL) || defined(_GXEXT))
		#ifndef _AFXDLL
			#ifdef _DEBUG
				#define _GXLIBNAME "gx16d.lib"
			#else
				#define _GXLIBNAME "gx16r.lib"
			#endif
		#else
			#ifdef _DEBUG
				#define _GXLIBNAME "gxa16d.lib"
			#else
				#define _GXLIBNAME "gxa16r.lib"
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#define _GXLIBNAME "gx6116d.lib"
		#else
			#define _GXLIBNAME "gx6116r.lib"
		#endif
	#endif

	#pragma message( "Objective Grid requires linking with " _GXLIBNAME  )
#endif

// 32-bit auto library linking is separate in config/name.h

#endif // _GXNOAUTOLIB

// #include <ManifestDefs.h>

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined

#if !defined(_WIN32)
#include "gxtchar.h"

// provide types and macros that 32-bit wtypes.h usually provides
#define TEXT    _T
#define LPCTSTR LPCSTR
#define LPTSTR  LPSTR

#endif

#ifndef _GX_DISABLE_INLINES  // Don't include inline files when .DEF file is created
#define _GX_ENABLE_INLINES
#define GX_INLINE inline
#endif

// GX_DATA used for NEAR data declarations with 16-Bit version
#define GX_DATA

typedef int             GINT;
typedef LONG            GBOOL;
typedef DWORD           ROWCOL;
typedef DWORD           GXCELL;

/////////////////////////////////////////////////////////////////////////////
// IA64 compatibility
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

/////////////////////////////////////////////////////////////////////////////

// Command type
enum GXCmdType
{
	gxDo = 0,
	gxRollback = 1,
	gxUndo = 2,
	gxRedo = 3
};

//#if _MFC_VER < 0x0300
//struct GXBYTE8
//{
//	double d;
//	BOOL operator==(const GXBYTE8& p) { return d == p.d; }
//	BOOL operator!=(const GXBYTE8& p) { return d != p.d; }
//};
//#else
typedef __int64			GXBYTE8;
//#endif

#define CRowColArray    CDWordArray
#define xWORD_MAX        USHRT_MAX

enum GXModifyType
{
	gxOverride,
	gxApplyNew,
	gxCopy,
	gxExclude,
	gxRemove
};


//#if _MFC_VER < 0x0300
//#define GX_GLOBALCLASS  0
//#else
#define GX_GLOBALCLASS  CS_GLOBALCLASS
//#endif

#define CGXPropertySheet CPropertySheet
#define CGXPropertyPage CPropertyPage

/////////////////////////////////////////////////////////////////////////////
// other helpers

// [VC7] Probably this function is not needed for MFC 7.0. Just played it safe.
#if _MFC_VER >= 0x0300 && _MFC_VER < 0x0700

	// Initialize locale settings (but not if we run under Win32s)
  #if defined(_AFXDLL)

#define GXSetLocaleAnd3dControl() \
	if (!GXGetAppData()->bWin31) \
		_tsetlocale(LC_ALL, _T("")); \
	Enable3dControls();
  #else

#define GXSetLocaleAnd3dControl() \
	if (!GXGetAppData()->bWin31) \
		_tsetlocale(LC_ALL, _T("")); \
	Enable3dControlsStatic();
  #endif

#elif (_MFC_VER >= 0x0700)
#define GXSetLocaleAnd3dControl() \
	if (!GXGetAppData()->bWin31) \
		_tsetlocale(LC_ALL, _T(""));
#else

#define GXSetLocaleAnd3dControl() \
	SetDialogBkColor(); \
	_tsetlocale(LC_ALL, _T(""));

#endif

// zero fill everything after the vtbl pointer
#define GX_ZERO_INIT_OBJECT(base_class) \
	memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));

#define GX_ZERO_INIT() \
	memset(this+1, 0, sizeof(*this));

/////////////////////////////////////////////////////////////////////////////
// Diagnostic support

/////////////////////////////////////////////////////////////////////////////
// Diagnostic support

#ifdef _DEBUG

void __cdecl GXTraceOnce(LPCTSTR lpszFormat, ...);
// Note: file names are still ANSI strings (filenames rarely need UNICODE)

#define GX_TRACEONCE             ::AfxTrace

#else   // _DEBUG

inline void __cdecl GXTraceOnce(LPCTSTR, ...) { }
#define GX_TRACEONCE              1 ? (void)0 : ::GXTraceOnce

#endif // !_DEBUG

#define GX_ASSERT_POINTER(p, type) \
	ASSERT(((p) != NULL) && AfxIsValidAddress((p), sizeof(type), FALSE))

#define GX_ASSERT_NULL_OR_POINTER(p, type) \
	ASSERT(((p) == NULL) || AfxIsValidAddress((p), sizeof(type), FALSE))

// Helper macros
#define GX_ASSERT_KINDOF(class_name, object) \
	ASSERT((object)->IsKindOf(RUNTIME_CLASS(class_name)))

#ifndef AFX_CDECL
#define AFX_CDECL __cdecl
#endif

// RTTI helper macros/functions

#if _MFC_VER < 0x0400

const CObject* AFX_CDECL GXDynamicDownCast(CRuntimeClass* pClass, const CObject* pObject);
CObject* AFX_CDECL GXDynamicDownCast(CRuntimeClass* pClass, CObject* pObject);

#define GX_DYNAMIC_DOWNCAST(class_name, object) \
	(class_name*)GXDynamicDownCast(RUNTIME_CLASS(class_name), object)

#ifdef _DEBUG
const CObject* AFX_CDECL GXStaticDownCast(CRuntimeClass* pClass, const CObject* pObject);
CObject* AFX_CDECL GXStaticDownCast(CRuntimeClass* pClass, CObject* pObject);
#define GX_STATIC_DOWNCAST(class_name, object) \
	((class_name*)GXStaticDownCast(RUNTIME_CLASS(class_name), object))
#else
#define GX_STATIC_DOWNCAST(class_name, object) ((class_name*)object)
#endif

#else // MFC 4.0

#define GX_DYNAMIC_DOWNCAST DYNAMIC_DOWNCAST
#define GX_STATIC_DOWNCAST STATIC_DOWNCAST

#endif

// Get rid of warning 4100 (unreferenced formal parameter)

#ifdef _DEBUG
#define GX_UNUSED(x)
#else
#define GX_UNUSED(x) x
#endif
#define GX_UNUSED_ALWAYS(x) x


/////////////////////////////////////////////////////////////////////////////
// UNIX: Wind/U compatibilty

#ifdef _UNIX_

  #define strnicmp          strncasecmp
  #define strcmp            strcasecmp

  // Wind/U complains if we do MoveWindow with no size
  // the following call also makes the window invisible
  // without invalidating the area
  #define MoveWindow0(b)    MoveWindow(-100, -100, 10, 10, b)

#else

  #define MoveWindow0(b)    MoveWindow(0,0,0,0,b)

#endif

/////////////////////////////////////////////////////////////////////////////
// Assertion helper

#ifdef _DEBUG
  #if _MFC_VER >= 0x300
	#define GX_ONASSERT(f, r) \
		do \
		{ \
			if (!(f)) { \
				if (AfxAssertFailedLine(THIS_FILE, __LINE__)) \
					AfxDebugBreak(); } \
		} while (0)
  #else
	#define GX_ONASSERT(f, r)        ((f) ? (void)0 : \
									::AfxAssertFailedLine(THIS_FILE, __LINE__))
  #endif  // _MFC_VER
#else
  #define GX_ONASSERT(f, r)  if (!(f)) r
#endif

#define ONASSERT GX_ONASSERT  // for backward compatibilty

#include <limits.h>

#ifndef GXNEAR
#define GXNEAR			near
#endif

#endif // _GXVER_H_

