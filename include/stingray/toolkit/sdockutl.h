///////////////////////////////////////////////////////////////////////////////
// sdockutl.h
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
// Author:       
// Description:  SECDockViewsUtils functions
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __SDOCKUTL_H__
#define __SDOCKUTL_H__

#ifndef __SDOCKFRM_H__
#include "toolkit\sdockfrm.h"
#endif

#include <StingrayExportDefs.h>

namespace SECDockViewsUtil {

	//@func Activate any visible docking frame
	TOOLKIT_API BOOL OnActivateDockable ( SECDockableFrame* pwndExclude = NULL );

	//@func Determine if there is an MDI child that can be activated.
	TOOLKIT_API BOOL CanActivateMDIChild ( CWnd* pwndExclude = NULL );

	//@func Given a dockable frame, determine if it and its parents are visible
	TOOLKIT_API BOOL IsDockableFrameVisible ( SECDockableFrame* pwndTest );
}

#endif // __SDOCKUTL_H__
