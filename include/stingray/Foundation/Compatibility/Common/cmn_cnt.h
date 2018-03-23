///////////////////////////////////////////////////////////////////////////////
// cmn_cnt.h
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
//
// All classes included by CMN are in this file
// and this file may be multiply included

#pragma once

//  *************** Image Classes ******************

// ***********************************************************
// *
// *  SECDib
// *
// ***********************************************************

#ifdef CMN_BLD_SECDIB
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  CMN_BLD_SECDIB" )
	#endif
	// SECImage - ABC for all images
	#ifndef __SECIMAGE_H__
	#include /* */ "secimage.h"
	#endif //__SECIMAGE_H__

	// SECDib
	#ifndef __SECDIB_H__
	#include /* */ "secdib.h"
	#endif //_SECDIB_H__
#endif	// CMN_BLD_SECDIB

// ***********************************************************
// *
// *  SECJPeg
// *
// ***********************************************************

#ifdef CMN_BLD_SECJPEG
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  CMN_BLD_SECJPEG" )
	#endif
	// SECJpeg
	#ifndef __SECJPEG_H__
	#include "secjpeg.h"
	#endif // __SECJPEG_H_
#endif	// CMN_BLD_SECJPEG

// ***********************************************************
// *
// *  SECMemDC
// *
// ***********************************************************

#ifndef _SECDC_H_
#include /* */ "secdc.h"
using stingray::foundation::SECMemDC;
#endif

// ***********************************************************
// *
// *  SEC CRect Extension 
// *
// ***********************************************************

#ifndef __SEC_RECT_H__
#include /* */ "secrect.h"
#endif

// ***********************************************************
// *
// *  Bitmap loading
// *
// ***********************************************************

#ifndef __SLOADBMP_H__
#include "sloadbmp.h"
#endif // __SLOADBMP_H__

// ***********************************************************
// *
// *  Color Well
// *
// ***********************************************************

#ifdef CMN_BLD_COLORWELL
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  CMN_BLD_COLORWELL" )
	#endif
	// SECColorWell
	#ifndef __SECWELL_H__
	#include /* */ "secwell.h"
	#endif // __SECWELL_H__
#endif

// ***********************************************************
// *
// *  Button Classes
// *
// ***********************************************************

#ifdef CMN_BLD_BUTTON_CTRL
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  CMN_BLD_BUTTON_CTRL" )
	#endif

	// SECBtns
	#ifndef __SECBTNS_H__
	#include /* */ "secbtns.h"
	#endif // __SECBTNS_H__
#endif	// CMN_BLD_BUTTON_CTRL

// ***********************************************************
// *
// *  Design Patterns
// *
// ***********************************************************

#if defined(WIN32) && defined(CMN_BLD_PATTERNS)
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  CMN_BLD_PATTERNS" )
	#endif
	#ifndef __SEC_PATTERNS_H
	#include /* */ "patterns\patterns.h"
	#endif
#endif // CMN_BLD_PATTERNS

// ***********************************************************
// *
// *  Template Utility Macros
// *
// ***********************************************************

#if defined(WIN32) && defined(_SECMESMACROS_H)
	#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
		#pragma message ( __TIME__ ":  _SECMESMACROS_H" )
	#endif
	#ifndef _SECMESMACROS_H
	#include /* */ "SECMesMac.h"
	#endif
#endif // _SECMESMACROS_H


