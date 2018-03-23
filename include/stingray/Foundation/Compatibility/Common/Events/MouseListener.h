///////////////////////////////////////////////////////////////////////////////
// MouseListener.h : Declares mouse listener interface and adapter class.
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

#ifndef __COMPAT_MOUSELISTENER_H__
#define __COMPAT_MOUSELISTENER_H__

#include "Foundation\Compatibility\Common\CmnGuids.h"

#ifndef __COMPAT_EVENTLISTENER_H__
#include "Foundation\Compatibility\Common\Events\EventListener.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
//@doc IMouseListener
//
//@class IMouseListener | Interface to handling mouse events. Mouse event
// listeners map various mouse events onto the virtual member functions for
// handling.
//
//@mfunc BOOL | IMouseListener | OnLButtonDown | Handle left mouse button down events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnLButtonUp | Handle left mouse button up events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnLButtonDblClk | Handle left mouse button double click events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnRButtonDown | Handle right mouse button down events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnRButtonUp | Handle right mouse button up events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnRButtonDblClk | Handle right mouse button double click events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc BOOL | IMouseListener | OnMouseMove | Handle mouse move events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@base public | IEventListener
//
class /*FOUNDATION_API*/ __declspec(uuid("47E1CE39-D500-11d2-8CAB-0010A4F36466"))
				IMouseListener : public IEventListener
{
public:
	//@cmember
	/* Handle left mouse button down events. */
	virtual BOOL OnLButtonDown(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle left mouse button up events. */
	virtual BOOL OnLButtonUp(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle left mouse button double click events. */
	virtual BOOL OnLButtonDblClk(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button down events. */
	virtual BOOL OnRButtonDown(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button up events. */
	virtual BOOL OnRButtonUp(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button double click events. */
	virtual BOOL OnRButtonDblClk(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle mouse move events. */
	virtual BOOL OnMouseMove(UINT nFlags, POINT pt) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc MouseAdapter
//
//@class MouseAdapter | The mouse adapter class supplies a default
// implementation of the <c IMouseListener> interface. The
// <mf MouseAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the IMouseListener interface
// that always return FALSE. Mouse listeners can be derived from this class
// that override and implement only the handlers they are interested in.
//
//@base public | EventListener_T
//
class FOUNDATION_API MouseAdapter : public EventListener_T<IMouseListener, &IID_IMouseListener>
{
// Operations
public:

	//@cmember
	/* Handle left mouse button down events. */
	virtual BOOL OnLButtonDown(UINT nFlags, POINT pt);

	//@cmember
	/* Handle left mouse button up events. */
	virtual BOOL OnLButtonUp(UINT nFlags, POINT pt);

	//@cmember
	/* Handle left mouse button double click events. */
	virtual BOOL OnLButtonDblClk(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button down events. */
	virtual BOOL OnRButtonDown(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button up events. */
	virtual BOOL OnRButtonUp(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button double click events. */
	virtual BOOL OnRButtonDblClk(UINT nFlags, POINT pt);

	//@cmember
	/* Handle mouse move events. */
	virtual BOOL OnMouseMove(UINT nFlags, POINT pt);
};

};  // end namespace rw

#endif // __COMPAT_MOUSELISTENER_H__
