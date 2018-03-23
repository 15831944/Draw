///////////////////////////////////////////////////////////////////////////////
// CMNALL.h
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
//  Author:			Steve Danielson
//  Description:	cmnall.h - header file for common stingray library
//  Created:		06/24/98
//
//

#ifndef __CMNALL_H__
#define __CMNALL_H__

// version info
#include /* */ "Foundation\Compatibility\Common\cmnver.h"

// Preliminary defines - as set by build wizard
#ifdef WIN32
#include "foundation\SflDef.h"
#endif

#define _SFL_MFC_SUPPORT

// RTTI check
// _CPPRTTI is supplied by the compiler if /GR was used on the command line.
// COMPILER_OPTION_RTTI is a Stingray defined pre-processor
#if !defined(_CPPRTTI) && defined(COMPILER_OPTION_RTTI)
#pragma message( "-------------------------------------------------------------------------------------" )
#pragma message( "One or more Stingray components you have enabled require RTTI (Run-Time Type Information)." )
#pragma message( "You can enable this for your project in Visual Studio." )
#pragma message( "From the Project->Settings dialog, on the C++ tab. Choose the C++ Language" )
#pragma message( "item in the combo box. Check the RTTI Checkbox and re-build your project." )
#pragma message( "This adds the /GR compiler option." )
#pragma message( "-------------------------------------------------------------------------------------" )
#error RTTI required
#endif



// OT needs 8 byte packing for structures
#if _MFC_VER >= 0x0300
// pshpack8.h saves the current #pragma pack value
#include /* */ "pshpack8.h"
#else
#pragma pack(8)
#endif

// resources
#include /* */ "osc_cmnres.h"


// dll support
//#ifndef __CMNDLL_H__
//#include /* */ "cmndll.h"
//#endif //_CMNDLL_H_

// All files are included here
// This file may be multiply included
// by other products that use CMN
#include "cmn_cnt.h"

#if _MFC_VER >= 0x0300
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif



#endif //__CMNALL_H__
