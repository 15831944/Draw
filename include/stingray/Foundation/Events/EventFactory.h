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

// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#pragma once

#ifndef __EVENTFACTORY_H__
#define __EVENTFACTORY_H__

#include <foundation\Events\Event.h>
#include <Foundation\Events\MouseEvent.h>
#include <Foundation\Events\CommandEvent.h>
#include <Foundation\Events\WindowEvents.h>
#include <Foundation\Events\KeyboardEvent.h>
#include <Foundation\Events\UIUpdateEvent.h>
#include <Foundation\Events\ScrollEvent.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc CEventFactory
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
class CEventFactory
{
// Operations
public:
	//@cmember
	/* Filter out unwanted Windows messages. */
	inline virtual bool FilterWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam);
	//@cmember
	/* Create a Windows event. */
	inline virtual IEvent* CreateWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam);

	//@cmember
	/* Filter out unwanted Windows command messages. */
	inline virtual bool FilterCommandEvent(UINT nID, int nCode);
	//@cmember
	/* Create a Windows command event. */
	inline virtual IEvent* CreateCommandEvent(UINT nID, int nCode);

	//@cmember
	/* Create a command query event. */
	inline virtual IEvent* CreateCommandQueryEvent(UINT nID);
};

///////////////////////////////////////////////////////////////////////////
//
// CEventFactory
//

//@doc CEventFactory
//@mfunc bool | CEventFactory | FilterWindowsEvent | Filter out unwanted Windows messages.
//@rdesc TRUE if the message is supported by the factory; otherwise FALSE.
//@parm UINT | message | Windows message ID (WM_*).
//@parm WPARAM | wParam | Word parameter for windows message.
//@parm LPARAM | lParam | Long parameter for windows message.
//@comm The base class implementation always returns TRUE. Override this
// method to filter out unwanted windows messages.
bool CEventFactory::FilterWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	message;
	wParam;
	lParam;
	return true;
}

//@doc CEventFactory
//@mfunc IEvent* | CEventFactory | CreateWindowsEvent | Create a Windows event.
//@rdesc Pointer to generated event object or NULL if message is filtered out.
//@parm UINT | message | Windows message ID (WM_*).
//@parm WPARAM | wParam | Word parameter for windows message.
//@parm LPARAM | lParam | Long parameter for windows message.
//@comm This function calls <mf CEventFactory::FilterWindowsEvent> to determine
// if the event should be created or not. If the message is not filtered out,
// then the message ID is used to determine what type of event object to
// create. The event object is AddRef'd and then returned to the caller.
IEvent* CEventFactory::CreateWindowsEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	IEvent* pIEvent = NULL;

	if (FilterWindowsEvent(message, wParam, lParam))
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MOUSEMOVE:
			pIEvent = new CMouseEvent(message, wParam, lParam);
			break;

		case WM_SETCURSOR:
			pIEvent = new CMouseSetCursorEvent(message, wParam, lParam);
			break;

		case WM_CREATE:
			pIEvent = new CWindowCreateEvent(message, wParam, lParam);
			break;

		case WM_DESTROY:
			pIEvent = new CWindowDestroyEvent();
			break;

		case WM_SIZE:
			pIEvent = new CWindowSizeEvent(message, wParam, lParam);
			break;

		case WM_PAINT:
			pIEvent = new CWindowPaintEvent(message, wParam, lParam);
			break;

		case WM_ERASEBKGND:
			pIEvent = new CWindowEraseBkgndEvent(message, wParam, lParam);
			break;

		case WM_TIMER:
			pIEvent = new CWindowTimerEvent(message, wParam, lParam);
			break;

		case WM_COMMAND:
			pIEvent = new CCommandEvent(LOWORD(wParam), HIWORD(wParam));
			break;

		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_DEADCHAR:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
		case WM_SYSDEADCHAR:
			pIEvent = new CKeyboardEvent(message, wParam, lParam);
			break;

		case WM_HSCROLL:
		case WM_VSCROLL:
			pIEvent = new CScrollEvent(message, wParam, lParam);
			break;
		}
	}

	return pIEvent;
}

//@doc CEventFactory
//@mfunc bool | CEventFactory | FilterCommandEvent | Filter out unwanted Windows command messages.
//@rdesc TRUE if the message is supported by the factory; otherwise FALSE.
//@parm UINT | nID | Command ID.
//@parm int | nCode | Notification code.
//@comm The base class implementation always returns TRUE. Override this
// method to filter out unwanted command messages.
bool CEventFactory::FilterCommandEvent(UINT nID, int nCode)
{
	nID;
	nCode;
	return true;
}

//@doc CEventFactory
//@mfunc IEvent* | CEventFactory | CreateCommandEvent | Create a Windows command event.
//@rdesc Pointer to generated event object or NULL if message is filtered out.
//@parm UINT | nID | Command ID.
//@parm int | nCode | Notification code.
//@comm This function calls <mf CEventFactory::FilterCommandEvent> to determine
// if the event should be created or not. If the command is not filtered out,
// then a <c CCommandEvent> object is created. The command event object is
// AddRef'd and then returned to the caller.
IEvent* CEventFactory::CreateCommandEvent(UINT nID, int nCode)
{
	IEvent* pIEvent = NULL;

	if (FilterCommandEvent(nID, nCode))
	{
		pIEvent = new CCommandEvent(nID, nCode);
	}

	return pIEvent;
}

//@doc CEventFactory
//@mfunc IEvent* | CEventFactory | CreateCommandQueryEvent | Create a command query event.
//@rdesc Pointer to generated event object or NULL if message is filtered out.
//@parm UINT | nID | Command ID.
//@comm This function creates a <c CCommandQueryEvent> object, AddRefs it, and
// returns it to the caller.
IEvent* CEventFactory::CreateCommandQueryEvent(UINT nID)
{
	return new CCommandQueryEvent(nID);
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __EVENTFACTORY_H__
