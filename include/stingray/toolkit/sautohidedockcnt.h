///////////////////////////////////////////////////////////////////////////////
// sautohidedockcnt.h
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
//  Description:	Declarations for SECAutoHideBarDockContext
//  Created:		Sept 2005
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SECAUTOHIDEDOCKCONTEXT_H__
#define __SECAUTOHIDEDOCKCONTEXT_H__

//#ifndef __SDOCKCNT_H__
#include "toolkit\sdockcnt.h"
//#endif

#include <StingrayExportDefs.h>


class SECAutoHideBarDockContext : public SECDockContext
{
public:
	//@cmember
     TOOLKIT_API SECAutoHideBarDockContext(CControlBar* pBar);
	 //@cmember
     inline virtual ~SECAutoHideBarDockContext(){}

	 //@cmember
     // Override this to prevent sizing
     TOOLKIT_API virtual void StartDrag(CPoint pt);
};

#endif // __SECAUTOHIDEDOCKCONTEXT_H__