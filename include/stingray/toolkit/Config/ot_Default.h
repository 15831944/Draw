// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Toolkit
// ot_Default.h : Generated Configuration Info for configuration "ot_Default"
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
// #include "toolkit/config/ot_Default.h" 
// before 
// #include "toolkit\secall.h" 
// in your application's stdafx.h file.

#ifndef _SECBWCONFIG_H_
#define _SECBWCONFIG_H_

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
	// This file is used to autolink a custom build configuration. 
	// NOTE: Do not include more than 1 custom autolink.
	#ifdef SEC_CUSTOM_AUTOLINK
		#pragma message("Error! More than one autolink header is not allowed.")
	#endif

	// Define this preprocessor such that otver.h knows not to use the default autolink information
	#define SEC_CUSTOM_AUTOLINK
	
#if _MSC_VER >= 1700 // vc++ 11.0
	#ifndef _UNICODE
		#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201d.lib"
		#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201.lib"
		#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201ad.lib"
		#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201a.lib"
		#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201asd.lib"
		#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201as.lib"
		#elif defined(_SECDLL) && !defined(_AFXDLL)
			#error _SECDLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#else
		#if !defined(_SECDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201ud.lib"
		#elif !defined(_SECDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201u.lib"
		#elif !defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201aud.lib"
		#elif !defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201au.lib"
		#elif defined(_SECDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201asud.lib"
		#elif defined(_SECDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _SECAUTOLIBNAME "ot1201asu.lib"
		#elif defined(_SECDLL) && !defined(_AFXDLL)
			#error _SECDLL is defined but _AFXDLL is not. You must defined both.
		#endif
	#endif // _UNICODE
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
	#endif // _UNICODE
#endif
	
#endif // _SECNOAUTOLIB
#endif // _MFC_VER >= 0x0421

// If using the autolink, 
// also add any preprocessor defines that are unique to this configuration
#ifdef SEC_CUSTOM_AUTOLINK

#ifndef OT_BLD_BROWEDIT
#define OT_BLD_BROWEDIT
#endif

#ifndef SEC_NO_TMPL_EXPLICIT_INST
#define SEC_NO_TMPL_EXPLICIT_INST
#endif

#ifndef OT_BLD_COMMON
#define OT_BLD_COMMON
#endif

#ifndef OT_BLD_FILESYS
#define OT_BLD_FILESYS
#endif

#ifndef CMN_BLD_BUTTON_CTRL
#define CMN_BLD_BUTTON_CTRL
#endif

#ifndef CMN_BLD_COLORWELL
#define CMN_BLD_COLORWELL
#endif

#ifndef OT_BLD_CALCEDIT
#define OT_BLD_CALCEDIT
#endif

#ifndef OT_BLD_CALENDAR
#define OT_BLD_CALENDAR
#endif

#ifndef OT_BLD_CLRLSTBOX
#define OT_BLD_CLRLSTBOX
#endif

#ifndef OT_BLD_CURREDIT
#define OT_BLD_CURREDIT
#endif

#ifndef OT_BLD_DROPEDIT
#define OT_BLD_DROPEDIT
#endif

#ifndef OT_BLD_DATETIME
#define OT_BLD_DATETIME
#endif

#ifndef OT_BLD_LBEDIT
#define OT_BLD_LBEDIT
#endif

#ifndef OT_BLD_COMBOBOXEX
#define OT_BLD_COMBOBOXEX
#endif

#ifndef OT_BLD_PROGRESS
#define OT_BLD_PROGRESS
#endif

#ifndef OT_BLD_MASKEDIT
#define OT_BLD_MASKEDIT
#endif

#ifndef OT_BLD_MARQUEE
#define OT_BLD_MARQUEE
#endif

#ifndef CMN_BLD_SECDIB
#define CMN_BLD_SECDIB
#endif

#ifndef OT_BLD_SECGIF
#define OT_BLD_SECGIF
#endif

#ifndef CMN_BLD_SECJPEG
#define CMN_BLD_SECJPEG
#endif

#ifndef OT_BLD_SECPCX
#define OT_BLD_SECPCX
#endif

#ifndef OT_BLD_SECTARGA
#define OT_BLD_SECTARGA
#endif

#ifndef OT_BLD_SECTIFF
#define OT_BLD_SECTIFF
#endif

#ifndef OT_BLD_MTI
#define OT_BLD_MTI
#endif

#ifndef OT_BLD_GRADIENT
#define OT_BLD_GRADIENT
#endif

#ifndef OT_BLD_DOCKWIN
#define OT_BLD_DOCKWIN
#endif

#ifndef OT_BLD_WDI
#define OT_BLD_WDI
#endif

#ifndef OT_BLD_CUSTTBAR
#define OT_BLD_CUSTTBAR
#endif

#ifndef OT_BLD_WSMGR
#define OT_BLD_WSMGR
#endif

#ifndef OT_BLD_FDI
#define OT_BLD_FDI
#endif

#ifndef OT_BLD_REGISTRY
#define OT_BLD_REGISTRY
#endif

#ifndef OT_BLD_TABCTRL
#define OT_BLD_TABCTRL
#endif

#ifndef OT_BLD_SCUTBAR
#define OT_BLD_SCUTBAR
#endif

#ifndef OT_BLD_BMPDLG
#define OT_BLD_BMPDLG
#endif

#ifndef OT_BLD_STATUS
#define OT_BLD_STATUS
#endif

#ifndef OT_BLD_FULLSCREENVIEW
#define OT_BLD_FULLSCREENVIEW
#endif

#ifndef COMPILER_OPTION_RTTI
#define COMPILER_OPTION_RTTI
#endif

#ifndef CMN_BLD_PATTERNS
#define CMN_BLD_PATTERNS
#endif

#ifndef OT_BLD_KBSCUT
#define OT_BLD_KBSCUT
#endif

#ifndef OT_BLD_TOD
#define OT_BLD_TOD
#endif

#ifndef OT_BLD_TOOLSMENU
#define OT_BLD_TOOLSMENU
#endif

#ifndef OT_BLD_THUMBNAIL
#define OT_BLD_THUMBNAIL
#endif

#ifndef OT_BLD_SPLASH
#define OT_BLD_SPLASH
#endif

#ifndef OT_BLD_TRAYICON
#define OT_BLD_TRAYICON
#endif

#ifndef OT_BLD_ENCRYPT
#define OT_BLD_ENCRYPT
#endif

#ifndef OT_BLD_COMPRESSFILE
#define OT_BLD_COMPRESSFILE
#endif

#ifndef OT_ZLIB095
#define OT_ZLIB095
#endif

#ifndef OT_BLD_RANDOM
#define OT_BLD_RANDOM
#endif

#ifndef OT_BLD_FORMULA
#define OT_BLD_FORMULA
#endif

#ifndef OT_BLD_TREECTRL
#define OT_BLD_TREECTRL
#endif

#ifndef OT_BLD_PANZOOM
#define OT_BLD_PANZOOM
#endif

#ifndef OT_BLD_MVC
#define OT_BLD_MVC
#endif

#ifndef OTPRO
#define OTPRO
#endif

#ifndef OT_BLD_ADVDOCKWIN
#define OT_BLD_ADVDOCKWIN
#endif

#ifndef OT_BLD_LAYOUTMGR
#define OT_BLD_LAYOUTMGR
#endif

#ifndef OT_BLD_DOCKVIEWS
#define OT_BLD_DOCKVIEWS
#endif



#pragma message("Objective Toolkit autolink configuration: Default")

#endif

#endif // _SECBWCONFIG_H_
