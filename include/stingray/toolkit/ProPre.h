///////////////////////////////////////////////////////////////////////////////
// ProPre.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Author:			Mark Isham
//  Description:	ProPre.h - Objective Toolkit Pro prefix Mega-Header
//  Created:		August 1997
//
//
//	This file is included via "Secall.h", do not include directly.
//

// OT pro resources that must be included prior to OT standard edition.
// In general, you will want to link OT pro includes in "proall.h", 
// after the standard toolkit includes. This file is provided as a
// placeholder for the few OT pro includes that must be invoked
// before the standard edition includes.

#ifndef __PROPRE_H_
#define __PROPRE_H_

#ifdef WIN32

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#endif

#endif	// __PROPRE_H_
