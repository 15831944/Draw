///////////////////////////////////////////////////////////////////////////////
// mvc.h : SFL Model View Controller package
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

#pragma once


#if !defined(_SFL)
#define _SFL
#endif

#include <Foundation\SflCommon.h>

#include <Foundation\MVC\MvcVisualComponent.h>
#include <Foundation\MVC\MvcVisualPart.h>
#include <Foundation\MVC\MvcLogicalPart.h>
#include <Foundation\MVC\MvcCommand.h>
#include <Foundation\MVC\MvcModel.h>
#include <Foundation\MVC\MvcController.h>
#include <Foundation\MVC\MvcViewport.h>
#include <Foundation\MVC\MvcComponent.h>
#include <Foundation\MVC\MvcBorderWrapper.h>
#include <Foundation\MVC\MvcPrintable.h>
#include <Foundation\MVC\MvcWrapper.h>
#include <Foundation\MVC\MvcZoomCommand.h>

#ifdef _SFL_MFC_SUPPORT
#include <Foundation\MVC\MFC\MvcMsgHandler.h>
#include <Foundation\MVC\MFC\MvcBufferedWrapper.h>
#include <Foundation\MVC\MFC\MvcCommand.h>
#include <Foundation\MVC\MFC\MvcCompositeViewport.h>
#include <Foundation\MVC\MFC\MvcController.h>
#include <Foundation\MVC\MFC\MvcDefSbjObs.h>
#include <Foundation\MVC\MFC\MvcIfcs.h>
#include <Foundation\MVC\MFC\MvcLogicalPart.h>
#include <Foundation\MVC\MFC\MvcModel.h>
#include <Foundation\MVC\MFC\MvcBufferedVp.h>
#include <Foundation\MVC\MFC\MvcPresentationModel.h>
#include <Foundation\MVC\MFC\MvcScrollView.h>
#include <Foundation\MVC\MFC\MvcScrollWrapper.h>
#include <Foundation\MVC\MFC\MvcTransactionModel.h>
#include <Foundation\MVC\MFC\MvcViewport.h>
#include <Foundation\MVC\MFC\MvcVisualComponent.h>
#include <Foundation\MVC\MFC\MvcVisualPart.h>
#endif

#ifdef _SFL_ATL_SUPPORT
#include <Foundation\MVC\MvcAtl.h>
#include <Foundation\MVC\MvcClientViewport.h>
#include <Foundation\MVC\MvcScrollWrapper.h>

#if defined(_WIN32_IE) && (_WIN32_IE >= 0x0500)
#include <Foundation\MVC\MvcPersist.h>
#endif

#endif
