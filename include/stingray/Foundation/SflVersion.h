// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Stingray Foundation Library
// SflVersion.h
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
//@doc 
//@module SflVersion.h | Version information and automatic linking settings.
//
// Author:  GF
// <nl>Created: 1/00
// 


#ifndef __SFLVERSION_H__
#define __SFLVERSION_H__

#ifndef _SFL_MFC_SUPPORT
#ifdef _AFX
#define _SFL_MFC_SUPPORT
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _SFLNOAUTOLIB when compiling SFL so that it does not try and link to itself.
// Proverbial chicken and egg problem.
//
#ifndef _SFLNOAUTOLIB
#if _MFC_VER >= 0x0421

	
	// If a custom autolink was used, do not bother with the defaults
	#ifndef SFL_CUSTOM_AUTOLINK
	
		// Ok, no custom autolink was used, use the default
		// The default is the configuration last set by the build wizard

	// Auto link options for ATL compatible builds
#if _MSC_VER >= 1700  // VC++ 11.0
		#ifndef _SFL_MFC_SUPPORT
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && defined(_DEBUG) 
					#define _SFLAUTOLIBNAME "sfl501wd.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501w.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsd.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ws.lib"
				#endif
			#else
				#if !defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wud.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wu.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsud.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsu.lib"
				#endif
			#endif // _UNICODE without _SFL_MFC_SUPPORT
			
		// Auto link options for MFC compatible library builds
		#else // _SFL_MFC_SUPPORT defined
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501d.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ad.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501a.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asd.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501as.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#else
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ud.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501u.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501aud.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501au.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asud.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asu.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#endif //_UNICODE with _SFL_MFC_SUPPORT
		#endif // _SFL_MFC_SUPPORT
#else
		#ifndef _SFL_MFC_SUPPORT
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && defined(_DEBUG) 
					#define _SFLAUTOLIBNAME "sfl501wd.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501w.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsd.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ws.lib"
				#endif
			#else
				#if !defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wud.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wu.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsud.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501wsu.lib"
				#endif
			#endif // _UNICODE without _SFL_MFC_SUPPORT
			
		// Auto link options for MFC compatible library builds
		#else // _SFL_MFC_SUPPORT defined
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501d.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ad.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501a.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asd.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501as.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#else
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501ud.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501u.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501aud.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501au.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asud.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl501asu.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#endif //_UNICODE with _SFL_MFC_SUPPORT
		#endif // _SFL_MFC_SUPPORT
#endif
		
	#endif	// SFL_CUSTOM_AUTOLINK

	#pragma comment(lib, _SFLAUTOLIBNAME)
		
	// You may turn off this SFL specific compilation message by adding _SFLNOMSG to your C/C++ preprocessor settings.
	#ifndef _SFLNOMSG
	#pragma message( "Automatically linking with " _SFLAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _SFLNOAUTOLIB

#include <ManifestDefs.h>

#endif // __SFLVERSION_H__
