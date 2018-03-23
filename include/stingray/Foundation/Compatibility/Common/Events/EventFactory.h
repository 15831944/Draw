///////////////////////////////////////////////////////////////////////////////
// EventFactory.h : Interface to event factory class.
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
// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#ifndef __COMPAT_EVENTFACTORY_H__
#define __COMPAT_EVENTFACTORY_H__

#ifndef __COMPAT_EVENT_H__
#include "Foundation\Compatibility\Common\Events\Event.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
//@doc EventFactory
//
//@class An event factory creates events based on various types of
// input parameters and filter criterion. It consists of filter
// methods and create methods for different categories of events.
// It translates Windows messages into event objects that can be
// passed to event routers and event listeners. It can also be used
// to generate custom events. This class serves as a base class for
// derived event factories, which can provide their own custom
// filtering and creation methods.
//
class FOUNDATION_API EventFactory
{
// Operations
public:
	//@cmember
	/* Filter out unwanted Windows messages. */
	virtual BOOL FilterWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam);
	//@cmember
	/* Create a Windows event. */
	virtual IEvent* CreateWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam);

	//@cmember
	/* Filter out unwanted Windows command messages. */
	virtual BOOL FilterCommandEvent(UINT nID, int nCode);
	//@cmember
	/* Create a Windows command event. */
	virtual IEvent* CreateCommandEvent(UINT nID, int nCode);

	//@cmember
	/* Create a command query event. */
	virtual IEvent* CreateCommandQueryEvent(UINT nID);
};

};  // end namespace rw

#endif // __COMPAT_EVENTFACTORY_H__
