///////////////////////////////////////////////////////////////////////////////
// EventRouter.h : Interface to event routers.
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
// Authors:      Jeff Boenig
// Description:  Framework independent event model.
//

#ifndef __COMPAT_EVENTROUTER_H__
#define __COMPAT_EVENTROUTER_H__

#include "Foundation\Compatibility\Common\CppIface.h"

#ifndef __COMPAT_EVENT_H__
#include "Foundation\Compatibility\Common\Events\Event.h"
#endif

#ifndef __COMPAT_EVENTLISTENER_H__
#include "Foundation\Compatibility\Common\Events\EventListener.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
// IEventRouter

//@doc IEventRouter
//@mfunc BOOL | IEventRouter | RouteEvent | Routes event objects to event listeners.
//@rdesc TRUE if at least one listener handled the event.
//@parm IEvent* | pIEvent | Pointer to event object.

//@doc IEventRouter
//@mfunc BOOL | IEventRouter | AddListener | Add an event listener to the router.
//@rdesc TRUE if successful, otherwise FALSE.
//@parm IEventListener* | pIListener | Pointer to event listener to add.

//@doc IEventRouter
//@mfunc BOOL | IEventRouter | RemoveListener | Remove an event listener from the router.
//@rdesc TRUE if successful, otherwise FALSE.
//@parm IEventListener* | pIListener | Pointer to event listener to remove.

//@class IEventRouter | Interface for routing events to event listeners.
// The RouteEvent method takes a pointer to an event and returns TRUE if
// the event was handled by one or more listeners or FALSE if the event
// was not handled.

//@base public | IUnknown

class __declspec(uuid("47E1CE36-D500-11d2-8CAB-0010A4F36466"))
				IEventRouter : public IUnknown
{
public:
	//@cmember
	/* Routes event objects to event listeners. */
	virtual BOOL RouteEvent(IEvent* pIEvent) const = 0;
	//@cmember
	/* Add an event listener to the router. */
	virtual BOOL AddListener(IEventListener* pIListener) = 0;
	//@cmember
	/* Remove an event listener from the router. */
	virtual BOOL RemoveListener(IEventListener* pIListener) = 0;
};

};  // end namespace rw

#endif // __COMPAT_EVENTROUTER_H__
