///////////////////////////////////////////////////////////////////////////////
// ProVer.h
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


#ifndef __OTPRO_VERS_H
#define __OTPRO_VERS_H


#include <ProductVersions.h>

// If 16-bit, only OT standard 16-bit classes will be accessible
#ifndef WIN32
#pragma message("Warning! Objective Toolkit does not support 16-bit platforms. Using only applicable OT standard files.")
#else

#if (_MFC_VER < 0x0420)

#pragma message("Warning! Objective Toolkit is not supported for MFC version 4.1 or earlier.")
#pragma message("         Please contact Microsoft for upgrade information.")
#endif

#endif

#endif
