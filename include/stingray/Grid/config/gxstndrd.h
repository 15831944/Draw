// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Grid
// gxstndrd.h : Generated Configuration Info for configuration "gxstndrd"
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
// 
//  Author:		Stefan Hoenig
//  Description:	Build Wizard configuration template
//  Created:		Jan 1998
//
//

// To automatically link your application with this configuration:
//
// Add 
// #include "config/gxstndrd.h" 
// before 
// #include "gxall.h" 
// in your application's stdafx.h file.

#ifndef _GXCONFIG_H_
#define _GXCONFIG_H_

#define _GXSTD		1	// This is an Objective Grid Standard Build

#ifdef _GXEXT
#undef _GXDLL
#define _GXDLL
#endif

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _GXNOAUTOLIB when compiling OG so that it does not try and link to itself. 
// Proverbial chicken and egg problem.
//
#ifndef _GXNOAUTOLIB
#if _MFC_VER >= 0x0421

#if _MSC_VER >= 1700  // VC++ 11.0
	#ifndef _UNICODE
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201d.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201ad.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201a.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asd.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201as.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#else
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201ud.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201u.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201aud.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201au.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asud.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asu.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#endif
#else
	#ifndef _UNICODE
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201d.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201ad.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201a.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asd.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201as.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#else
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201ud.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201u.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201aud.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201au.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asud.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og1201asu.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#endif
#endif
	

	#pragma comment(lib, _GXAUTOLIBNAME)

	// You may turn off this OG specific compilation message by adding _GXNOMSG to your C/C++ preprocessor settings.
	#ifndef _GXNOMSG
	#pragma message( "Automatically linking with " _GXAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _GXNOAUTOLIB

#include <ManifestDefs.h>

#endif // _GXCONFIG_H_
