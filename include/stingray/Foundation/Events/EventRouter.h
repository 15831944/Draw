///////////////////////////////////////////////////////////////////////////////
// EventRouter.h
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

// Authors:      Jeff Boenig
// Description:  Framework independent event model.
//

#pragma once

#ifndef __EVENTROUTER_H__
#define __EVENTROUTER_H__

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\SflGuids.h>
#include <foundation\CppIface.h>
#include <foundation\Events\Event.h>
#include <foundation\Events\EventListener.h>
#include <StingrayExportDefs.h>

#pragma warning(disable: 4251)

namespace stingray {
namespace foundation {


///////////////////////////////////////////////////////////////////////////
// IEventRouter

//@doc IEventRouter
//@mfunc bool | IEventRouter | RouteEvent | Routes event objects to event listeners.
//@rdesc TRUE if at least one listener handled the event.
//@parm IEvent* | pIEvent | Pointer to event object.

//@doc IEventRouter
//@mfunc bool | IEventRouter | AddListener | Add an event listener to the router.
//@rdesc TRUE if successful, otherwise FALSE.
//@parm IEventListener* | pIListener | Pointer to event listener to add.

//@doc IEventRouter
//@mfunc bool | IEventRouter | RemoveListener | Remove an event listener from the router.
//@rdesc TRUE if successful, otherwise FALSE.
//@parm IEventListener* | pIListener | Pointer to event listener to remove.

//@class IEventRouter | Interface for routing events to event listeners.
// The RouteEvent method takes a pointer to an event and returns TRUE if
// the event was handled by one or more listeners or FALSE if the event
// was not handled.

//@base public | IRefCount
//@base public | IQueryGuid

class __declspec(uuid("0122C05E-122A-46a0-939C-E67047CF00CA"))
				IEventRouter : public IRefCount, public IQueryGuid
{
public:
	//@cmember
	/* Routes event objects to event listeners. */
	virtual bool RouteEvent(IEvent* pIEvent) = 0;
	//@cmember
	/* Add an event listener to the router. */
	virtual bool AddListener(IEventListener* pIListener) = 0;
	//@cmember
	/* Remove an event listener from the router. */
	virtual bool RemoveListener(IEventListener* pIListener) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc IEventRouterImpl
//
//@class IEventRouterImpl | Provides a default implementation of the
// <c IEventRouter> interface. This class maintains a list of event
// listeners and implements <mf IEventRouterImpl::RouteEvent> by iterating
// over the listeners and calling <mf IEventListener::HandleEvent>.
//
//@base public | IEventRouter

class IEventRouterImpl : public IEventRouter
{
// Constructors/destructor
public:
	virtual ~IEventRouterImpl()
	{
		while (m_listeners.size() > 0)
		{
			IEventListener* pIListener = m_listeners.back();
			pIListener->Release();
			m_listeners.pop_back();
		}
	}

// Attributes
protected:
	//@cmember
	/* Array of event listeners*/
	ListenerVector m_listeners;

// Operations
public:
	//@cmember,mfunc Cast object to a pointer type given a GUID.
	//@@rdesc true if object is successfully cast to the new data type, otherwise false.
	//@@parm REFGUID | guid | Input GUID that determines the data type to cast to.
	//@@parm void ** | ppvObj | Output parameter to receive the result of the cast.
	//@@end
	/* Cast object to a pointer type given a GUID*/
	virtual bool QueryGuid(REFGUID guid, void **ppvObj)
	{
		bool bResult = false;
		*ppvObj = NULL;

		if (guid == __uuidof(IEventRouter))
		{
			*ppvObj = static_cast<IEventRouter*>(this);
			bResult = true;
		}

		return bResult;
	}

	//@cmember,mfunc
	// Add a reference to this object.
	//@@rdesc New reference count value.
	//@@comm This is a no-op implementation. Derived classes must
	// override in order to provide reference counting.
	//@@end
	/* Add a reference to this object*/
	ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1;
	}

	//@cmember,mfunc
	// Release a reference to this object.
	//@@rdesc New reference count value.
	//@@comm This is a no-op implementation. Derived classes must
	// override in order to provide reference counting.
	//@@end
	/* Release a reference to this object*/
	ULONG STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	//@cmember,mfunc
	// Routes event objects to event listeners.
	//@@rdesc TRUE if at least one listener handled the event.
	//@@parm IEvent* | pIEvent | Pointer to event object.
	//@@end
	/* Routes event objects to event listeners*/
	virtual bool RouteEvent(IEvent* pIEvent)
	{
		int nHandledCount = 0;

		if (pIEvent != NULL)
		{
			ListenerVector::const_iterator itListener;

			//
			// Give each event listener a chance to handle the event.
			//
			for (itListener = m_listeners.begin(); itListener != m_listeners.end(); itListener++)
			{
				if ((*itListener)->HandleEvent(pIEvent))
				{
					nHandledCount++;
				}
			}
		}

		return (nHandledCount > 0);
	}

	//@cmember,mfunc
	// Add an event listener to the router.
	//@@rdesc TRUE if successful, otherwise FALSE.
	//@@parm IEventListener* | pIListener | Pointer to event listener to add.
	//@@end
	/* Add an event listener to the router*/
	virtual bool AddListener(IEventListener* pIListener)
	{
		if (pIListener != NULL)
		{
			pIListener->AddRef();
			m_listeners.push_back(pIListener);
			return true;
		}
		return false;
	}

	//@cmember,mfunc
	// Remove an event listener from the router.
	//@@rdesc TRUE if successful, otherwise FALSE.
	//@@parm IEventListener* | pIListener | Pointer to event listener to remove.
	//@@end
	/* Remove an event listener from the router*/
	virtual bool RemoveListener(IEventListener* pIListener)
	{
		ListenerVector::iterator itListener = m_listeners.begin();
		while (itListener != m_listeners.end())
		{
			if (pIListener == *itListener)
			{
				(*itListener)->Release();
				m_listeners.erase(itListener);
				return true;
			}
			else
			{
				itListener++;
			}
		}
		return false;
	}
};

///////////////////////////////////////////////////////////////////////////
//@doc CComboRouterListener
//
//@class CComboRouterListener | Implements HandleEvent method for a
// combined router and listener object.
//
//@tcarg class | base_t | Base class to override. Must be derived from both <c IEventListener>
// and <c IEventRouter>
//
//@base public | base_t

template <class base_t>
class CComboRouterListener : public base_t
{
public:
	//@cmember,mfunc
	// Receive an event and attempt to handle it.
	//@@rdesc TRUE if successful, otherwise FALSE.
	//@@parm IEvent* | pIEvent | Pointer to event to handle.
	//@@comm This function first attempts to dispatch the event onto
	// the base class, since it is an event listener. If the event
	// isn't handle, it then calls RouteEvent.
	//@@end
	/* Receive an event and attempt to handle it*/
	virtual bool HandleEvent(IEvent* pIEvent)
	{
		bool bHandled = false;

		if (pIEvent != NULL)
		{
			bHandled = pIEvent->Dispatch(guid_cast<IEventRouter*>(this));
		}

		if (!bHandled)
			bHandled = base_t::RouteEvent(pIEvent);

		return bHandled;
	}
};

///////////////////////////////////////////////////////////////////////////
//@doc CListeningRouter
//
//@class CListeningRouter | Mixes in IEventListener into an event router
// and implements HandleEvent method.
//
//@tcarg class | base_t | Base class to override. Must be derived from <c IEventRouter>
//
//@base public | base_t
//@base public | IEventListener

template <class base_t>
class CListeningRouter : public base_t, public IEventListener
{
public:
	//@cmember,mfunc
	// Receive an event and attempt to handle it.
	//@@rdesc TRUE if successful, otherwise FALSE.
	//@@parm IEvent* | pIEvent | Pointer to event to handle.
	//@@comm This function first attempts to dispatch the event onto
	// the base class, since it is an event listener. If the event
	// isn't handle, it then calls RouteEvent.
	//@@end
	/* Receive an event and attempt to handle it*/
	virtual bool HandleEvent(IEvent* pIEvent)
	{
		bool bHandled = false;

		if (pIEvent != NULL)
		{
			bHandled = pIEvent->Dispatch(guid_cast<IEventRouter*>(this));
		}

		if (!bHandled)
			bHandled = base_t::RouteEvent(pIEvent);

		return bHandled;
	}

	BEGIN_GUID_MAP(CListeningRouter<base_t>)
		GUID_ENTRY(IEventListener)
		GUID_CHAIN_ENTRY(base_t)
	END_GUID_MAP

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return base_t::AddRef();
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		return base_t::Release();
	}
};

};  // end namespace stingray::foundation
};	// end namespace stingray

#endif  // #ifndef __EVENTROUTER_H__
