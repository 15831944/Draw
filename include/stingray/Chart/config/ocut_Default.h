// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
// 
// Objective Chart Utility Toolkit
// ocut_Default.h : Generated Configuration Info for configuration "ocut_Default"
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
/////////////////////////////////////////////////////////////////////////////
// 
//  Author:		Mark Isham
//  Description:	Build Wizard configuration template
//  Created:		Jan 1998
//
//

// To automatically link your application with this configuration:
//
// Add 
// #include "chart\config/ocut_Default.h" 
// before 
// #include "chart\ochart.h" 
// in your application's stdafx.h file.

#ifndef _OCUTBWCONFIG_H_
#define _OCUTBWCONFIG_H_

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _OCUTNOAUTOLIB when compiling OCUT so that it does not try and link to itself.
// Proverbial chicken and egg problem.
//
#ifndef _OCUTNOAUTOLIB
#if _MFC_VER >= 0x0421

	// If a custom autolink was used, do not bother with the defaults
	// This file is used to autolink a custom build configuration. 
	// NOTE: Do not include more than 1 custom autolink.
	#ifdef OCUT_CUSTOM_AUTOLINK
		#pragma message("Error! More than one autolink header is not allowed.")
	#endif

	// Define this preprocessor such that ocutver.h knows not to use the default autolink information
	#define OCUT_CUSTOM_AUTOLINK

	#ifndef _UNICODE
		#if !defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001d.lib"
		#elif !defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001.lib"
		#elif !defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001ad.lib"
		#elif !defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001a.lib"
		#elif defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001asd.lib"
		#elif defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001as.lib"
		#elif defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_UT_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#else
		#if !defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001ud.lib"
		#elif !defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001u.lib"
		#elif !defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001aud.lib"
		#elif !defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001au.lib"
		#elif defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001asud.lib"
		#elif defined(_OBJCHART_UT_DLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _OCUTAUTOLIBNAME "ocut1001asu.lib"
		#elif defined(_OBJCHART_UT_DLL) && !defined(_AFXDLL)
			#error _OBJCHART_UT_DLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#endif
#endif // _MFC_VER >= 0x0421
#endif // _OCUTNOAUTOLIB

// If using the autolink, 
// also add any preprocessor defines that are unique to this configuration
#ifdef OCUT_CUSTOM_AUTOLINK

#ifndef SEC_NO_TMPL_EXPLICIT_INST
#define SEC_NO_TMPL_EXPLICIT_INST
#endif

#ifndef _OCUTNOAUTOLIB
#define _OCUTNOAUTOLIB
#endif



#pragma message("Objective Chart Utility Toolkit autolink configuration: Default")

#endif

#endif // _OCUTBWCONFIG_H_
