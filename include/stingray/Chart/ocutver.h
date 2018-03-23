// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Chart Utility Toolkit
// ocutver.h
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

#ifndef __OCUTVER_H__
#define __OCUTVER_H__


// Changes have been made to serialization since version 0 (beta)
#define _OCUTCHART_FILE_VERSION 1

/////////////////////////////////////////////
// Extension DLL link management

#ifdef _OBJCHART_UT_DLL
	#ifdef _OCUTBUILDLIB
		#define OCUT_DATA _declspec(dllexport)
	#else
		#define OCUT_DATA _declspec(dllimport)
	#endif
#endif

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
	
	#pragma comment(lib, _OCUTAUTOLIBNAME)
		
	// You may turn off this OCUT specific compilation message by adding _OCUTNOMSG to your C/C++ preprocessor settings.
	#ifndef _OCUTNOMSG
	#pragma message( "Automatically linking with " _OCUTAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _OCUTNOAUTOLIB

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined
//
#ifdef _OBJCHART_UT_DLL
	#ifndef _OBJCHART_DLL
		#define _OBJCHART_DLL
	#endif
#endif // _OBJCHART_UT_DLL

#include <ManifestDefs.h>

#endif // __OCUTVER_H__
