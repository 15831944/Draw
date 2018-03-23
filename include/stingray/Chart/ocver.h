// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Chart
// ocver.h
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
//  Author:	  Steve Danielson
//                Chuanzhong Zhu: Modified for Objective Chart
//  Description:  Version information for Common libraries
//  Created:      06/24/98/

#ifndef __OCVER_H__
#define __OCVER_H__


// Changes have been made to serialization since version 0 (beta)
#define _OCHART_FILE_VERSION 1

/////////////////////////////////////////////
// Extension DLL link management

#ifdef _OBJCHART_DLL
	#ifdef _OCBUILDLIB
		#define OC_DATA _declspec(dllexport)
	#else
		#define OC_DATA _declspec(dllimport)
	#endif
#endif

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
	#pragma comment(lib, _OCAUTOLIBNAME)
			
	// You may turn off this OC specific compilation message by adding _OCNOMSG to your C/C++ preprocessor settings.
	#ifndef _OCNOMSG
	#pragma message( "Automatically linking with " _OCAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _OCNOAUTOLIB

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined
//
#ifdef _OBJCHART_DLL
	#ifndef _SFLDLL
		#define _SFLDLL
	#endif
#endif // _OBJCHART_DLL


#ifdef _USE_COMMON_

// version info
#include "Foundation\SflCommon.h"

#ifdef WIN32
#include "foundation\SflDef.h"
#endif

// resources
#include "Foundation\Sflres.h"


// All files are included here
// This file may be multiply included
// by other products that use SFL

//First Image
#include "Foundation\Image.h"

#endif//_USE_COMMON_

#include <ManifestDefs.h>

#endif // __OCVER_H__
