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

// Authors:      Jeff Boenig and Bob Powell
// Description:  Framework independent event model.
//

#pragma once

#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\WinEvent.h>
#include <foundation\Events\MouseEvent.h>
#include <foundation\Events\MouseListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IMouseEvent | Interface for mouse events.
//
//@class IMouseEvent | Interface to mouse events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("0F5F5DE3-B582-4539-9145-E749250F2FDA"))
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
	virtual bool TestFlags(const UINT nMask) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CMouseEvent
//
//@class CMouseEvent | This class encapsulates a Windows mouse event. The
// LONG parameter of the Windows message contains the point at which the
// mouse event occurred. The function <mf CMouseEvent::GetPoint> decodes
// the LONG parameter and returns it as a POINT. The WORD parameter
// contains flags indicating if certain virtual keys are down. The
// <mf CMouseEvent::TestFlags> method can be used to test the flags with
// the following masks -
//
//     MK_CONTROL   Set if the CTRL key is down.
//     MK_LBUTTON   Set if the left mouse button is down.
//     MK_MBUTTON   Set if the middle mouse button is down.
//     MK_RBUTTON   Set if the right mouse button is down.
//     MK_SHIFT     Set if the SHIFT key is down. 
//
//
//@base public | CWinEventBase
//
class CMouseEvent : public CWinEventBase<IMouseEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a mouse event from a message ID, WPARAM, and LPARAM. */
	inline CMouseEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the point at which the mouse event occurred. */
	inline virtual void GetPoint(POINT& pt);

	//@cmember
	/* Set the point at which the mouse event occurred. */
	inline virtual void SetPoint(const POINT& pt);

	//@cmember
	/* Test to see if certain virtual keys were pressed during the mouse event. */
	inline virtual bool TestFlags(const UINT nMask);
};


//@mfunc | CMouseEvent | CMouseEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CMouseEvent::CMouseEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IMouseEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CMouseEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IMouseListener* pIMouseListener = guid_cast<IMouseListener*>(pIListener);

	if (pIMouseListener != NULL)
	{
		POINT pt;
		GetPoint(pt);

		switch (GetMessageID())
		{
		case WM_LBUTTONDOWN:
			bHandled = pIMouseListener->OnLButtonDown((int)GetWParam(), pt);
			break;

		case WM_LBUTTONUP:
			bHandled = pIMouseListener->OnLButtonUp((int)GetWParam(), pt);
			break;

		case WM_LBUTTONDBLCLK:
			bHandled = pIMouseListener->OnLButtonDblClk((int)GetWParam(), pt);
			break;

		case WM_RBUTTONDOWN:
			bHandled = pIMouseListener->OnRButtonDown((int)GetWParam(), pt);
			break;

		case WM_RBUTTONUP:
			bHandled = pIMouseListener->OnRButtonUp((int)GetWParam(), pt);
			break;

		case WM_RBUTTONDBLCLK:
			bHandled = pIMouseListener->OnRButtonDblClk((int)GetWParam(), pt);
			break;

		case WM_MOUSEMOVE:
			bHandled = pIMouseListener->OnMouseMove((int)GetWParam(), pt);
			break;
		}
	}

	return bHandled;
}

//@mfunc void | CMouseEvent | GetPoint | Return the point at which the mouse event occurred.
//@rdesc void
//@parm POINT& | pt | Reference to POINT structure in which to assign return value.
void CMouseEvent::GetPoint(POINT& pt)
{
	WORD xPos = LOWORD(GetLParam());  // horizontal position of cursor 
	WORD yPos = HIWORD(GetLParam());  // vertical position of cursor 
	pt.x = xPos;
	pt.y = yPos;
}

//@mfunc void | CMouseEvent | SetPoint | Set the point at which the mouse event occurred.
//@rdesc void
//@parm const POINT& | pt | Point to assign to mouse event.
void CMouseEvent::SetPoint(const POINT& pt)
{
	SetLParam(MAKELONG(pt.x, pt.y));
}

//@mfunc void | CMouseEvent | TestFlags | Test to see if certain virtual keys were pressed during the mouse event.
//@rdesc bool
//@parm const UINT | nMask | Mask to test flags against.
//@comm The mask can be a combination of the following flags -
//     MK_CONTROL   Set if the CTRL key is down.
//     MK_LBUTTON   Set if the left mouse button is down.
//     MK_MBUTTON   Set if the middle mouse button is down.
//     MK_RBUTTON   Set if the right mouse button is down.
//     MK_SHIFT     Set if the SHIFT key is down. 
// This function returns TRUE if all flags in the mask are set.
bool CMouseEvent::TestFlags(const UINT nMask)
{
	return (GetWParam() & nMask) != 0;
}



///////////////////////////////////////////////////////////////////////////
//@doc IMouseSetCursorEvent | Interface for mouse set cursor events.
//
//@class IMouseSetCursorEvent | Interface for mouse set cursor events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("4C53E132-7D9F-4ce6-AB04-0A79A741F1E1"))
					IMouseSetCursorEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the window that contains the cursor. */
	virtual HWND GetCursorWindow() const = 0;

	//@cmember
	/* Return the hit-test area code. */
	virtual UINT GetHitTestCode() const = 0;

	//@cmember
	/* Return the mouse message number. */
	virtual UINT GetMouseMessage() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CMouseSetCursorEvent
//
//@class CMouseSetCursorEvent | This class encapsulates a set cursor message.
//
//@base public | CWinEventBase
//
class CMouseSetCursorEvent : public CWinEventBase<IMouseSetCursorEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a set cursor event from a message ID, WPARAM, and LPARAM. */
	inline CMouseSetCursorEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:
	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the window that contains the cursor. */
	inline virtual HWND GetCursorWindow() const;

	//@cmember
	/* Return the hit-test area code. */
	inline virtual UINT GetHitTestCode() const;

	//@cmember
	/* Return the mouse message number. */
	inline virtual UINT GetMouseMessage() const;
};


///////////////////////////////////////////////////////////////////////////
// CMouseSetCursorEvent

//@mfunc | CMouseSetCursorEvent | CMouseSetCursorEvent | Construct a set cursor event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for window handle.
//@parmopt LPARAM | lParam | 0 | Long parameter for hit-test code and mouse message.
CMouseSetCursorEvent::CMouseSetCursorEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IMouseSetCursorEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CMouseSetCursorEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IMouseListener* pIMouseListener = guid_cast<IMouseListener*>(pIListener);

	if (pIMouseListener != NULL)
	{
		bHandled = pIMouseListener->OnSetCursor(GetCursorWindow(), GetHitTestCode(), GetMouseMessage());
	}

	return bHandled;
}

HWND CMouseSetCursorEvent::GetCursorWindow() const
{
	return (HWND)GetWParam();
}

UINT CMouseSetCursorEvent::GetHitTestCode() const
{
	return (UINT)LOWORD(GetLParam());
}

UINT CMouseSetCursorEvent::GetMouseMessage() const
{
	return (UINT)HIWORD(GetLParam());
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MOUSEEVENT_H__
