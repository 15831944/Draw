///////////////////////////////////////////////////////////////////////////////
// cmnver.h
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
//  Author:	      Steve Danielson
//  Description:  Version information for Comon libraries
//  Created:      06/24/98/

#ifndef __CMNVER_H__
#define __CMNVER_H__

/////////////////////////////////////////////////////////////////////////////
// Master version numbers
/////////////////////////////////////////////////////////////////////////////

#define _CMN_VER 0x0FFF

#ifdef _CMNDLL
#ifndef _SFLDLL
#define _SFLDLL
#endif
#endif

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _CMNNOAUTOLIB when compiling CMN so that it does
// not try and link to itself.
//
#ifdef _CMNNOAUTOLIB
#ifndef _SFLNOAUTOLIB
#define _SFLNOAUTOLIB
#endif
#endif //_CMNNOAUTOLIB

#include <Foundation\SflVersion.h>

#endif // __CMNVER_H__
