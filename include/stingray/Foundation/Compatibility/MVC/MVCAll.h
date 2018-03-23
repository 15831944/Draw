///////////////////////////////////////////////////////////////////////////////
// MVCAll.h
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
//  Description:	MVCAll.h - MVC composite header
//  Created:		October 1997
//
//
//	This file is included via "ProAll.h"
//

#ifndef __MODEL_VIEW_CONTROLLER_HEADERS_
#define __MODEL_VIEW_CONTROLLER_HEADERS_

// Common Libraries
// If MVC is being linked as a dll, then we must specify
// to link the common library as a dll
#ifdef _MVCDLL
	#ifndef _CMNDLL
		#define _CMNDLL
	#endif
#endif

#define _SFL_MFC_SUPPORT

#include "Foundation\Compatibility\MVC\mvcver.h"

// Objective Studio Common Library header
// Set up  the components in CMN that MVC depends upon
#ifndef CMN_BLD_PATTERNS
	#define CMN_BLD_PATTERNS
#endif

#ifndef _DECORATE_VISUAL_H_NAMES
#define _DECORATE_VISUAL_H_NAMES
#endif

#include <Foundation\Compatibility\Common\cmnall.h>
#include <Foundation\Compatibility\Common\cmn_cnt.h>

// MVC Libraries
#include "Foundation\Compatibility\Common\IRefCount.h"
#include "Foundation\Compatibility\MVC\MvcIfcs.h"
#include "Foundation\Compatibility\MVC\SmartPtr.h"
#include "Foundation\Compatibility\MVC\MvcMsgHandler.h"
#include "Foundation\Compatibility\MVC\MvcBorderWrapper.h"
#include "Foundation\Compatibility\MVC\MvcBufferedWrapper.h"
#include "Foundation\Compatibility\MVC\MvcCommand.h"
#include "Foundation\Compatibility\MVC\MvcModel.h"
#include "Foundation\Compatibility\MVC\MvcTransactionModel.h"
#include "Foundation\Compatibility\MVC\MvcViewport.h"
#include "Foundation\Compatibility\MVC\MvcVisualComponent.h"
#include "Foundation\Compatibility\MVC\MvcVisualPart.h"
#include "Foundation\Compatibility\MVC\MvcPresentationModel.h"
#include "Foundation\Compatibility\MVC\MvcLogicalPart.h"
#include "Foundation\Compatibility\MVC\MvcWrapper.h"
#include "Foundation\Compatibility\MVC\MvcController.h"
#include "Foundation\Compatibility\MVC\MvcScrollWrapper.h"
#include "Foundation\Compatibility\MVC\MvcScrollView.h"
#include "Foundation\Compatibility\MVC\MvcCompositeViewport.h"
#include "Foundation\Compatibility\MVC\MvcDefSbjObs.h"

#endif 		// __MODEL_VIEW_CONTROLLER_HEADERS_
