///////////////////////////////////////////////////////////////////////////////
// msxmlimport.h : Common header for importing the MSXML typelibrary information
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

#pragma once

#ifndef __MSXMLIMPORT_H__
#define __MSXMLIMPORT_H__

#if !defined(_SFL)
#define _SFL
#endif

// Include this common header for importing the MSXML type information. This workaround is necessary
// as the IA64 compiler fails to ignore multiple #import directives causing errors. 

#ifdef NTDDI_VERSION
	//---------------------------------------------------------------
	// NOTE: msxml.h is no longer used on the Windows Vista platform. 
	// Use msxml6.h instead. 
	// 
	// To use MSXML6, make sure that NTDDI_VERSION is defined as 
	// NTDDI_VISTA on Windows Vista platforms and that the MSXML6 SDK 
	// is installed and pathed correctly. 
	//---------------------------------------------------------------
	#if NTDDI_VERSION >= NTDDI_VISTA
		
		#include <msxml6.h>
		#import "msxml6.dll" rename_namespace("xml")
	#else
		#include <msxml.h>
		#import "msxml.dll" rename_namespace("xml")
	#endif
#else
	#include <msxml.h>
	#import "msxml.dll" rename_namespace("xml")
#endif

#endif	//__MSXMLIMPORT_H__	
