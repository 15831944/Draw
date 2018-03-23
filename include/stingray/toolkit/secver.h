// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Toolkit
// secver.h
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
//  Author:		Scot Wingo
//  Description:	Version information for SEC
//  Created:		Tue Aug 29 14:55:33 1995
// 

#ifndef __SECVER_H__
#define __SECVER_H__


#define _SEC     1      // SEC classes


/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _SECNOAUTOLIB when compiling OT so that it does not try and link to itself.
// Proverbial chicken and egg problem.
//
#ifndef _SECNOAUTOLIB
#if _MFC_VER >= 0x0421

	// If a custom autolink was used, do not bother with the defaults
	#ifndef SEC_CUSTOM_AUTOLINK

		// Ok, no custom autolink was used, 
		// use the default (i.e. if you only included "secall.h").
		// The default is the configuration last set by the build wizard

#if _MSC_VER >= 1700 // vc++ 11.0
		#ifndef _UNICODE
			#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101d.lib"
			#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101ad.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101a.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asd.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101as.lib"
			#elif defined(_SECDLL) && !defined(_AFXDLL)
				#error _SECDLL is defined but _AFXDLL is not. You must defined both.
			#endif
		#else
			#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101ud.lib"
			#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101u.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101aud.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101au.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asud.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asu.lib"
			#elif defined(_SECDLL) && !defined(_AFXDLL)
				#error _SECDLL is defined but _AFXDLL is not. You must defined both.
			#endif
		#endif
#else
	#ifndef _UNICODE
			#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101d.lib"
			#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101ad.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101a.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asd.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101as.lib"
			#elif defined(_SECDLL) && !defined(_AFXDLL)
				#error _SECDLL is defined but _AFXDLL is not. You must defined both.
			#endif
		#else
			#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101ud.lib"
			#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101u.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101aud.lib"
			#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101au.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asud.lib"
			#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SECAUTOLIBNAME "ot1101asu.lib"
			#elif defined(_SECDLL) && !defined(_AFXDLL)
				#error _SECDLL is defined but _AFXDLL is not. You must defined both.
			#endif
		#endif
#endif

	#endif	// SEC_CUSTOM_AUTOLINK
		
	#pragma comment(lib, _SECAUTOLIBNAME)
		
	// You may turn off this SEC specific compilation message by adding _SECNOMSG to your C/C++ preprocessor settings.
	#ifndef _SECNOMSG
	#pragma message( "Automatically linking with " _SECAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _SECNOAUTOLIB

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined

#if !defined(_WIN32)
#include "toolkit\gxtchar.h"

// provide types and macros that 32-bit wtypes.h usually provides
#define TEXT    _T
#define LPCTSTR LPCSTR
#define LPTSTR  LPSTR

#endif

#define SEC_DATA

#include <ManifestDefs.h>

#endif // __SECVER_H__
