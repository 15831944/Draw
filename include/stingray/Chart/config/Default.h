// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Chart
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
// #include "chart/config/Default.h" 
// before 
// #include "chart\ochart.h" 
// in your application's stdafx.h file.

#ifndef _OCBWCONFIG_H_
#define _OCBWCONFIG_H_

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _OCNOAUTOLIB when compiling OC so that it does not try and link to itself.
// Proverbial chicken and egg problem.
//
#ifndef _OCNOAUTOLIB
#if _MFC_VER >= 0x0421

	// If a custom autolink was used, do not bother with the defaults
	// This file is used to autolink a custom build configuration. 
	// NOTE: Do not include more than 1 custom autolink.
	#ifdef OC_CUSTOM_AUTOLINK
		#pragma message("Error! More than one autolink header is not allowed.")
	#endif

	// Define this preprocessor such that ocver.h knows not to use the default autolink information
	#define OC_CUSTOM_AUTOLINK

#if _MSC_VER >= 1700  // VC++ 11.0
	#ifndef _UNICODE
		#if !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001d.lib"
		#elif !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001ad.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001a.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asd.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001as.lib"
		#elif defined(_OBJCHART_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#else
		#if !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001ud.lib"
		#elif !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001u.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001aud.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001au.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asud.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asu.lib"
		#elif defined(_OBJCHART_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#endif
#else
	#ifndef _UNICODE
		#if !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001d.lib"
		#elif !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001ad.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001a.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asd.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001as.lib"
		#elif defined(_OBJCHART_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#else
		#if !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001ud.lib"
		#elif !defined(_OBJCHART_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001u.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001aud.lib"
		#elif !defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001au.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asud.lib"
		#elif defined(_OBJCHART_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCAUTOLIBNAME "oc1001asu.lib"
		#elif defined(_OBJCHART_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#endif
#endif

#endif // _MFC_VER >= 0x0421
#endif // _OCNOAUTOLIB

// If using the autolink, 
// also add any preprocessor defines that are unique to this configuration
#ifdef OC_CUSTOM_AUTOLINK

#ifndef SEC_NO_TMPL_EXPLICIT_INST
#define SEC_NO_TMPL_EXPLICIT_INST
#endif

#ifndef _OCNOAUTOLIB
#define _OCNOAUTOLIB
#endif

#ifndef _OC_XMLSERIALIZE_
#define _OC_XMLSERIALIZE_
#endif



#pragma message("Objective Chart autolink configuration: Default")

#endif

#endif // _OCBWCONFIG_H_
