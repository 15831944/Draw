///////////////////////////////////////////////////////////////////////////////
// ot_secjpeg.h
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
//  Author:			Rob Oliver
//  Description:	ot_secjpeg.h - SECJpeg component header
//  Created:		Tue Aug 27 14:08:25 1998
//
//

#ifndef __OTM_SECJPEG_H__
#define __OTM_SECJPEG_H__

// ***********************************************************
// *
// *  OT needs 8 byte packing for structures
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// pshpack8.h saves the current #pragma pack value
#include "pshpack8.h"
#else
#pragma pack(8)
#endif

// ***********************************************************
// *
// *  OT optimized include file
// *
// ***********************************************************

#ifndef __SECOPT_H__
    #include "toolkit\secopt.h"
#endif

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
	#ifndef __SFL_SECJPEG_H__
	#include "Foundation\Image\MFC\secjpeg.h"
	#endif // __SFL_SECJPEG_H_

#else
	#pragma message("Warning:  JPEG image support was not included in the Stingray Foundation Library.")
	#pragma message("          Add this component to the library using the BuildWizard and rebuild the Stingray Foundation Library.")
#endif	// CMN_BLD_SECJPEG

// ***********************************************************
// *
// *  Restore default byte packing
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#ifndef SEC_NO_NAMESPACE_USING
	using namespace stingray::foundation;
#endif

#endif // __OTM_SECJPEG_H__
