///////////////////////////////////////////////////////////////////////////////
// EventListener.h : Declares a template for Event Listeners
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

// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#ifndef __EVENTLISTENER_H__
#define __EVENTLISTENER_H__

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning(push,3)
	#endif
	#pragma warning(disable:4876)
	#pragma warning(disable:4284) // STL, not a UDT or reference to a UDT. Errors if infix notation used.
#endif

#include <foundation\stwarn.h>
#include <vector>
#include <list>
#include <foundation\stwarnp.h>
#include <foundation\CppIface.h>
#include <foundation\Events\Event.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IEventListener
//
//@class IEventListener | Interface for receiving and handling events. The
// HandleEvent method takes a pointer to an event and returns TRUE if the
// event is handled.
//
//@base public | IRefCount
//@base public | IQueryGuid
//
class __declspec(uuid("E23EB3AA-37AD-41f8-9BE4-594D72118510"))
				IEventListener : public IRefCount, public IQueryGuid
{
public:
	//@cmember
	/* Receive an event and attempt to handle it. */
	virtual bool HandleEvent(IEvent* pIEvent) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CEventListenerBase
//
//@class CEventListenerBase | This template class is provided as a convenient
// way to implement event listener interfaces in concrete classes. This
// template implements <mf CEventListenerBase::QueryInterface> and
// <mf CEventListenerBase::HandleEvent>. The event listener interface is one
// of the two template parameters, and is used as the base class in the
// template declaration. The interface passed in is assumed to be derived
// from <c IEventListener>. The other template parameter is a pointer to
// the interface ID for the event listener interface.
//
//@tcarg class | interfacebase_t | Event listener interface to implement.
//
//@mfunc HRESULT | CEventListenerBase | QueryInterface | Retrieve a pointer to
// an interface supported by this object.
//@rdesc S_OK if the interface is supported, E_NOINTERFACE if not.
//@parm REFIID | riid | Identifier of the interface being requested. 
//@parm void ** | ppvObj | Address of pointer variable that receives the
// interface pointer requested in riid.
//@comm Checks for the interface ID passed in the template parameter
// list. Also checks for IEventListener and IUnknown.
//
//@mfunc ULONG | CEventListenerBase | AddRef | Add a reference to this object.
//@rdesc New reference count value.
//@comm The CEventListenerBase template does not implement reference counting.
// This function does nothing and returns 0. Derived classes can implement
// reference counting by overriding AddRef and Release.
//
//@mfunc ULONG | CEventListenerBase | Release | Release a reference to this object.
//@rdesc New reference count value.
//@comm The CEventListenerBase template does not implement reference counting.
// This function does nothing and returns 0. Derived classes can implement
// reference counting by overriding AddRef and Release.
//
//@mfunc bool | CEventListenerBase | HandleEvent | Receive an event and attempt
// to handle it.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm IEvent* | pIEvent | Pointer to event object.
//@comm This function calls the function <mf IEvent::Dispatch> on
// the event passed in. The listener passes a pointer to itself to
// the event's dispatch message.
//
template<class interfacebase_t>
class CEventListenerBase : public interfacebase_t
{
public:

	//@cmember
	/* Retrieve a pointer to an interface supported by this object. */
	virtual bool QueryGuid(REFGUID guid, void **ppvObj)
	{
		*ppvObj = NULL;

		if (guid == __uuidof(interfacebase_t))
		{
			*ppvObj = static_cast<interfacebase_t*>(this);
		}
		else if (guid == __uuidof(IEventListener))
		{
			*ppvObj = static_cast<IEventListener*>(this);
		}

		if (*ppvObj != NULL)
		{
			return true;
		}

		return false;
	}

	//@cmember
	/* Add a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return 1;
	}

	//@cmember
	/* Release a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	//@cmember
	/* Receive an event and attempt to handle it. */
	virtual bool HandleEvent(IEvent* pIEvent)
	{
		bool bHandled = false;

		if (pIEvent != NULL)
		{
			bHandled = pIEvent->Dispatch(this);
		}

		return bHandled;
	}
};

///////////////////////////////////////////////////////////////////////////
//@type ListenerVector | STL vector of event listeners.
//
typedef std::vector<IEventListener*> ListenerVector;

///////////////////////////////////////////////////////////////////////////
//@type ListenerList | STL LIST of event listeners.
//
typedef std::list<IEventListener*> ListenerList;


};	// namespace stingray::foundation
};  // namespace stingray

#endif // #ifndef __EVENTLISTENER_H__


#ifndef _SFL_NO_PRAGMA_WARNINGS
	#if 1200 <= _MSC_VER
		#pragma warning (pop)
	#endif
#endif
