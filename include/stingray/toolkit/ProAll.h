///////////////////////////////////////////////////////////////////////////////
// ProAll.h
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
//  Author:			Mark Isham
//  Description:	ProAll.h - Objective Toolkit Pro Mega-Header
//  Created:		August 1997
//
//
//	This file is included via "Secall.h", do not include directly.
//

#ifndef __PROALL_H_
#define __PROALL_H_


/////////////////////////////////////////////////////////////////////////////
// Docking Views
//

#ifdef OT_BLD_DOCKVIEWS

	// Message filters
	#ifndef __SMSGFILT_H
	#include "toolkit\smsgfilt.h"
	#endif

	// WM_SYSCOMMANDEX
	#ifndef __SYSCMDEX_H
	#include "toolkit\syscmdex.h"
	#endif

	// Frame Bar
	#ifndef __SBARFRM_H__
	#include /* */ "toolkit\sbarfrm.h"
	#endif

	// Dockable frame
	#ifndef __SDOCKFRM_H__
	#include /* */ "toolkit\sdockfrm.h"
	#endif

	// Doc templates
	#ifndef __SDOCMULT_H__
	#include /* */ "toolkit\sdocmult.h"
	#endif

	// Not used any more, SECSingleDocTemplate is completely removed
//	#ifndef __SDOCSNGL_H__
//	#include /* */ "sdocsngl.h"
//	#endif

#endif // OT_BLD_DOCKVIEWS

/////////////////////////////////////////////////////////////////////////////
// Layout Manager
//

// Conditionally include Layout Mgr headers based on Build Wizard input
#ifdef OT_BLD_LAYOUTMGR

#ifndef __LAYOUT_MGR_HEADERS_
#include "toolkit\Layout\LyoutAll.h"
#endif	// __LAYOUT_MGR_HEADERS_

#endif	// OT_BLD_LAYOUTMGR

/////////////////////////////////////////////////////////////////////////////
// Advanced Docking Windows
//

#ifdef OT_BLD_ADVDOCKWIN
#include "toolkit\Layout\Docking\DockAll.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ActiveScript
//

// Conditionally include ActiveScript headers based on Build Wizard input
#ifdef OT_BLD_ACTIVESCRIPT

#ifndef __ACTIVEHOST_H
#include "toolkit\ActvHost\ActvHost.h"
#endif

#endif	// OT_BLD_ACTIVESCRIPT 

/////////////////////////////////////////////////////////////////////////////
// Model View Controller
//

// Conditionally include MVC headers based on Build Wizard input
#ifdef OT_BLD_MVC

#ifndef __MODEL_VIEW_CONTROLLER_HEADERS_
#include "Foundation\Mvc.h"	// now comes from the SFL library 1/20/2000
#endif

#endif	// OT_BLD_MVC

#endif __PROALL_H_

