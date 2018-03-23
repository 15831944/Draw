///////////////////////////////////////////////////////////////////////////////
// MouseEvent.h : Interface for mouse events.
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
// Authors:      Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#ifndef __COMPAT_MOUSEEVENT_H__
#define __COMPAT_MOUSEEVENT_H__

#include "Foundation\Compatibility\Common\CmnGuids.h"

#ifndef __COMPAT_WINEVENT_H__
#include "Foundation\Compatibility\Common\Events\WinEvent.h"
#endif

#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
//@doc IMouseEvent | Interface for mouse events.
//
//@class IMouseEvent | Interface to mouse events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class /*FOUNDATION_API*/ __declspec(uuid("47E1CE33-D500-11d2-8CAB-0010A4F36466"))
					IMouseEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the point at which the mouse event occurred. */
	virtual void GetPoint(POINT& pt) = 0;

	//@cmember
	/* Set the point at which the mouse event occurred. */
	virtual void SetPoint(const POINT& pt) = 0;

	//@cmember
	/* Test to see if certain virtual keys were pressed during the mouse event. */
	virtual BOOL TestFlags(const UINT nMask) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc MouseEvent
//
//@class MouseEvent | This class encapsulates a Windows mouse event. The
// LONG parameter of the Windows message contains the point at which the
// mouse event occurred. The function <mf MouseEvent::GetPoint> decodes
// the LONG parameter and returns it as a POINT. The WORD parameter
// contains flags indicating if certain virtual keys are down. The
// <mf MouseEvent::TestFlags> method can be used to test the flags with
// the following masks -
//
//     MK_CONTROL   Set if the CTRL key is down.
//     MK_LBUTTON   Set if the left mouse button is down.
//     MK_MBUTTON   Set if the middle mouse button is down.
//     MK_RBUTTON   Set if the right mouse button is down.
//     MK_SHIFT     Set if the SHIFT key is down. 
//
//
//@base public | WinEvent_T
//
class /*FOUNDATION_API*/ MouseEvent : public WinEvent_T<IMouseEvent, &IID_IMouseEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a mouse event from a message ID, WPARAM, and LPARAM. */
	MouseEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	virtual BOOL Dispatch(IUnknown* pIListener);

	//@cmember
	/* Return the point at which the mouse event occurred. */
	virtual void GetPoint(POINT& pt);

	//@cmember
	/* Set the point at which the mouse event occurred. */
	virtual void SetPoint(const POINT& pt);

	//@cmember
	/* Test to see if certain virtual keys were pressed during the mouse event. */
	virtual BOOL TestFlags(const UINT nMask);
};

};  // end namespace rw

#endif // __COMPAT_MOUSEEVENT_H__
