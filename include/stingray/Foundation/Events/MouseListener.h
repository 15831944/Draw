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

// Author:       Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#pragma once

#ifndef __MOUSELISTENER_H__
#define __MOUSELISTENER_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\EventListener.h>
#include <foundation\Events\MouseListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IMouseListener
//
//@class IMouseListener | Interface to handling mouse events. Mouse event
// listeners map various mouse events onto the virtual member functions for
// handling.
//
//@mfunc bool | IMouseListener | OnLButtonDown | Handle left mouse button down events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnLButtonUp | Handle left mouse button up events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnLButtonDblClk | Handle left mouse button double click events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnRButtonDown | Handle right mouse button down events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnRButtonUp | Handle right mouse button up events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnRButtonDblClk | Handle right mouse button double click events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@mfunc bool | IMouseListener | OnMouseMove | Handle mouse move events.
//@rdesc TRUE if event is handled; otherwise FALSE.
//@parm UINT | nFlags | Flags indicating if certain virtual keys were pressed
// when the mouse event occurred.
//@parm POINT | pt | Point at which the mouse event occurred.
//
//@base public | IEventListener
//
class __declspec(uuid("F6D393EC-87E9-474e-AD7F-81802A500DE9"))
				IMouseListener : public IEventListener
{
public:
	//@cmember
	/* Handle left mouse button down events. */
	virtual bool OnLButtonDown(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle left mouse button up events. */
	virtual bool OnLButtonUp(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle left mouse button double click events. */
	virtual bool OnLButtonDblClk(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button down events. */
	virtual bool OnRButtonDown(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button up events. */
	virtual bool OnRButtonUp(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle right mouse button double click events. */
	virtual bool OnRButtonDblClk(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handle mouse move events. */
	virtual bool OnMouseMove(UINT nFlags, POINT pt) = 0;
	//@cmember
	/* Handles mouse set cursor events. */
	virtual bool OnSetCursor( HWND hWnd, UINT nHitTest, UINT message ) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CMouseAdapter
//
//@class CMouseAdapter | The mouse adapter class supplies a default
// implementation of the <c IMouseListener> interface. The
// <mf CMouseAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the IMouseListener interface
// that always return FALSE. Mouse listeners can be derived from this class
// that override and implement only the handlers they are interested in.
//
//@base public | CEventListenerBase
//
class CMouseAdapter : public CEventListenerBase<IMouseListener>
{
// Operations
public:

	//@cmember
	/* Handle left mouse button down events. */
	inline virtual bool OnLButtonDown(UINT nFlags, POINT pt);

	//@cmember
	/* Handle left mouse button up events. */
	inline virtual bool OnLButtonUp(UINT nFlags, POINT pt);

	//@cmember
	/* Handle left mouse button double click events. */
	inline virtual bool OnLButtonDblClk(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button down events. */
	inline virtual bool OnRButtonDown(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button up events. */
	inline virtual bool OnRButtonUp(UINT nFlags, POINT pt);

	//@cmember
	/* Handle right mouse button double click events. */
	inline virtual bool OnRButtonDblClk(UINT nFlags, POINT pt);

	//@cmember
	/* Handle mouse move events. */
	inline virtual bool OnMouseMove(UINT nFlags, POINT pt);

	//@cmember
	/* Handles mouse set cursor events. */
	inline virtual bool OnSetCursor( HWND hWnd, UINT nHitTest, UINT message );
};

///////////////////////////////////////////////////////////////////////////
//
// CMouseAdapter
//

//@mfunc Handle left mouse button down events.
bool CMouseAdapter::OnLButtonDown(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle left mouse button up events.
bool CMouseAdapter::OnLButtonUp(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle left mouse button double click events.
bool CMouseAdapter::OnLButtonDblClk(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle right mouse button down events.
bool CMouseAdapter::OnRButtonDown(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle right mouse button up events.
bool CMouseAdapter::OnRButtonUp(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle right mouse button double click events.
bool CMouseAdapter::OnRButtonDblClk(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle mouse move events.
bool CMouseAdapter::OnMouseMove(UINT nFlags, POINT pt)
{
	nFlags;
	pt;
	return false;
}

//@mfunc Handle mouse set cursor events.
bool CMouseAdapter::OnSetCursor( HWND hWnd, UINT nHitTest, UINT message )
{
	hWnd;
	nHitTest;
	message;
	return false;
}


};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MOUSELISTENER_H__
