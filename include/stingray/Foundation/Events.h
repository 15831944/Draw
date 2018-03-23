///////////////////////////////////////////////////////////////////////////////
// Events.h : SFL Event Handling package
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

#include <Foundation\Events\Event.h>
#include <Foundation\Events\EventFactory.h>
#include <Foundation\Events\EventListener.h>
#include <Foundation\Events\EventRouter.h>
#include <Foundation\Events\EventQueue.h>
#include <Foundation\Events\CommandEvent.h>
#include <Foundation\Events\CommandListener.h>
#include <Foundation\Events\KeyboardEvent.h>
#include <Foundation\Events\KeyboardListener.h>
#include <Foundation\Events\MouseEvent.h>
#include <Foundation\Events\MouseListener.h>
#include <Foundation\Events\ScrollEvent.h>
#include <Foundation\Events\ScrollListener.h>
#include <Foundation\Events\UIUpdateEvent.h>
#include <Foundation\Events\UIUpdateElement.h>
#include <Foundation\Events\UIUpdateListener.h>
#include <Foundation\Events\WindowEvents.h>
#include <Foundation\Events\WindowListener.h>
#include <Foundation\Events\WinEvent.h>

#if defined(_SFL_ATL_SUPPORT)
#include <Foundation\Events\EventRouterMap.h>
#endif
