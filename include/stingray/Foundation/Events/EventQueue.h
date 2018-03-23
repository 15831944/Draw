///////////////////////////////////////////////////////////////////////////////
// EventQueue.h
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

// Author:       Jeff Boenig
// Description:  Framework independent event model.
//

#pragma once

#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__

#include <unknwn.h>
#include <foundation\Events\Event.h>
#include <Foundation\Events\EventRouter.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc IEventQueue
//
//@class IEventQueue | Interface to an event queue. Events are placed in
// the queue using the <mf IEventQueue::QueueEvent> method. Each event is
// assigned a priority so that the event queue can dispatch events according
// to their priority. Events are dispatched to event routers using
// the <mf IEventQueue::DispatchEvent> method.
//
//@mfunc bool | IEventQueue | QueueEvent | Place an event in the queue and
// assign it a priority.
//@rdesc TRUE if the event is successfully added to the queue; otherwise FALSE.
//@parm IEvent* | pIEvent | Pointer to event object.
//@parm UINT | nPriority | Priority that the queue should assign to the event.
//
//@mfunc bool | IEventQueue | DispatchEvent | Remove next event from the queue
// and send it to an event router
//@rdesc TRUE if an event was dispatched; otherwise FALSE.
//@parm IEventRouter* | pIEventRouter | Pointer to event router to receive
// event.
//@comm The queue determines the next event to be dispatched and pulls it
// from the queue. It then sends it to the event router using the
// <mf IEventRouter::RouteEvent> method. The next event in the queue
// is usually determined by a combination of chronological order and
// priority. This function removes the event from the queue.
//
//@mfunc void | IEventQueue | ClearAllEvents | Remove all events from the
// queue without dispatching them
//@rdesc void
//@comm This function clears out the queue without dispatching any of
// the events.
//
//@base public | IUnknown
//
class __declspec(uuid("D89E6C95-069E-4312-9933-60259A571F41"))
				IEventQueue : public IUnknown
{
public:
	//@cmember
	/* Place an event in the queue and assign it a priority. */
	virtual bool QueueEvent(IEvent* pIEvent, const UINT nPriority) = 0;
	//@cmember
	/* Remove next event from the queue and send it to an event router. */
	virtual bool DispatchEvent(IEventRouter* pIEventRouter) = 0;
	//@cmember
	/* Remove all events from the queue without dispatching them. */
	virtual void ClearAllEvents() = 0;
};

/////////////////////////////////////////////////////////////////////////////
//@doc CEventQueueEntry
//
//@class CEventQueueEntry | Encapsulates an event entry in an event queue. It
// wraps a pointer to <c IEvent> and takes care of reference counting. In
// addition, it stores a priority value for the event queue entry. Comparison
// operators are overloaded and implemented by comparing the priority value.
// This allows event queue entries to be used with standard collection
// classes and easily sorted.
//
class CEventQueueEntry
{
public:

	//@cmember
	/* Construct an event queue entry from an event pointer and priority. */
	CEventQueueEntry(IEvent* pIEvent = NULL, const UINT nPriority = 0)
	{
		m_pIEvent = pIEvent;
		if (m_pIEvent != NULL)
		{
			m_pIEvent->AddRef();
		}
		m_nPriority = nPriority;
	}

	//@cmember
	/* Release the event pointer. */
	virtual ~CEventQueueEntry()
	{
		if (m_pIEvent != NULL)
		{
			m_pIEvent->Release();
		}
	}

	//@cmember
	/* Copy constructor. */
	CEventQueueEntry(const CEventQueueEntry& src)
	{
		*this = src;
	}

	//@cmember
	/* Assign an event queue entry to this object. */
	CEventQueueEntry& operator=(const CEventQueueEntry& src)
	{
		m_pIEvent = src.m_pIEvent;
		if (m_pIEvent != NULL)
		{
			m_pIEvent->AddRef();
		}
		m_nPriority = src.m_nPriority;
		return *this;
	}

	//@cmember
	/* Cast the event queue entry to an IEvent pointer. */
	operator IEvent*() const
	{
		return m_pIEvent;
	}

	//@cmember
	/* Greater than operator. */
	bool operator>(const CEventQueueEntry& entry) const
	{
		return (m_nPriority > entry.m_nPriority);
	}

	//@cmember
	/* Less than operator. */
	bool operator<(const CEventQueueEntry& entry) const
	{
		return (m_nPriority < entry.m_nPriority);
	}

	//@cmember
	/* Compare for equivalence. */
	bool operator==(const CEventQueueEntry& entry) const
	{
		return (m_nPriority == entry.m_nPriority);
	}

	//@cmember
	/* Greater than or equal operator. */
	bool operator>=(const CEventQueueEntry& entry) const
	{
		return (m_nPriority >= entry.m_nPriority);
	}

	//@cmember
	/* Less than or equal operator. */
	bool operator<=(const CEventQueueEntry& entry) const
	{
		return (m_nPriority <= entry.m_nPriority);
	}

protected:
	//@cmember
	/* Pointer to event that this entry contains. */
	IEvent* m_pIEvent;
	//@cmember
	/* Priority for this event queue entry. */
	UINT m_nPriority;
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __EVENTQUEUE_H__
