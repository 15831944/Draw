// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Stingray Foundation Library
// Default.h : Generated Configuration Info for configuration "Default"
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
//  Author:		Mark Isham
//  Description:	Build Wizard configuration template
//  Created:		Jan 1998
//
//

// To automatically link your application with this configuration:
//
// Add 
// #include "config/Default.h" 
// before any other SFL include
// in your application's stdafx.h file.

#ifndef _SFLBWCONFIG_H_
#define _SFLBWCONFIG_H_

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
	// This file is used to autolink a custom build configuration. 
	// NOTE: Do not include more than 1 custom autolink.
	#ifdef SFL_CUSTOM_AUTOLINK
		#pragma message("Error! More than one autolink header is not allowed.")
	#endif

	// Define this preprocessor such that sflver.h knows not to use the default autolink information
	#define SFL_CUSTOM_AUTOLINK
	
	// Auto link options for ATL compatible builds

#if _MSC_VER >= 1700  // VC++ 11.0
	#ifndef _SFL_MFC_SUPPORT
		#ifndef _UNICODE
			#if !defined(_SFLDLL) && defined(_DEBUG) 
				#define _SFLAUTOLIBNAME "sfl601wd.lib"
			#elif !defined(_SFLDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601w.lib"
			#elif defined(_SFLDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601wsd.lib"
			#elif defined(_SFLDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601ws.lib"
			#endif
		#else
			#if !defined(_SFLDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601wud.lib"
			#elif !defined(_SFLDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601wu.lib"
			#elif defined(_SFLDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601wsud.lib"
			#elif defined(_SFLDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601wsu.lib"
			#endif
		#endif // _UNICODE without _SFL_MFC_SUPPORT	
	
	// Auto link options for MFC compatible library builds			
	#else 
		#ifndef _UNICODE
			#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601d.lib"
			#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601.lib"
			#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601ad.lib"
			#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601a.lib"
			#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601asd.lib"
			#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601as.lib"
			#elif defined(_SFLDLL) && !defined(_AFXDLL)
				#error _SFLDLL is defined but _AFXDLL is not. You must define both.
			#endif
		#else
			#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601ud.lib"
			#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601u.lib"
			#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601aud.lib"
			#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601au.lib"
			#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601asud.lib"
			#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
				#define _SFLAUTOLIBNAME "sfl601asu.lib"
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
	#else 
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

	
#endif //  _MFC_VER >= 0x0421
#endif // _SFLNOAUTOLIB

// If using the autolink, 
// also add any preprocessor defines that are unique to this configuration
#ifdef SFL_CUSTOM_AUTOLINK

#ifndef SEC_NO_TMPL_EXPLICIT_INST
#define SEC_NO_TMPL_EXPLICIT_INST
#endif

#ifndef SFL_BLD_GRAPHICS
#define SFL_BLD_GRAPHICS
#endif

#ifndef SFL_BLD_LAYOUTMGR
#define SFL_BLD_LAYOUTMGR
#endif

#ifndef SFL_BLD_EVENTS
#define SFL_BLD_EVENTS
#endif

#ifndef SFL_BLD_PRINTPREVIEW
#define SFL_BLD_PRINTPREVIEW
#endif

#ifndef SFL_BLD_IMAGE
#define SFL_BLD_IMAGE
#endif

#ifndef SFL_BLD_XMLSERCORE
#define SFL_BLD_XMLSERCORE
#endif

#ifndef SFL_BLD_COMPATIBILITY
#define SFL_BLD_COMPATIBILITY
#endif



#pragma message("SFL autolink configuration: Default")

#endif

#endif // _SFLBWCONFIG_H_
