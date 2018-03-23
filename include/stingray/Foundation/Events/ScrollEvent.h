///////////////////////////////////////////////////////////////////////////////
// ScrollEvent.h : Interface for mouse events.
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

#pragma once

#ifndef __SCROLLEVENT_H__
#define __SCROLLEVENT_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\WinEvent.h>
#include <foundation\Events\ScrollEvent.h>
#include <foundation\Events\ScrollListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IScrollEvent | Interface for mouse events.
//
//@class IScrollEvent | Interface to scroll events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("930EAE9B-9FBB-4610-9C1D-1DD2C6A532CD"))
					IScrollEvent : public IWinEvent
{
public:
	//@cmember
	/* The scroll code identifies the type of scrolling (line, page, etc.). */
	virtual int GetScrollCode() = 0;

	//@cmember
	/* Return the scroll position. */
	virtual short GetScrollPosition() = 0;

	//@cmember
	/* Return the scroll bar window handle. */
	virtual HWND GetScrollBarHandle() = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CScrollEvent
//
//@class CScrollEvent |
//
//@base public | CWinEventBase
//
class CScrollEvent : public CWinEventBase<IScrollEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a scroll event from a message ID, WPARAM, and LPARAM. */
	inline CScrollEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* The scroll code identifies the type of scrolling (line, page, etc.). */
	inline virtual int GetScrollCode();

	//@cmember
	/* Return the scroll position. */
	inline virtual short GetScrollPosition();

	//@cmember
	/* Return the scroll bar window handle. */
	inline virtual HWND GetScrollBarHandle();
};

//@mfunc | CScrollEvent | CScrollEvent | Construct a scroll event from a message ID,
// WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CScrollEvent::CScrollEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IScrollEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CScrollEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IScrollListener* pIScrollListener = guid_cast<IScrollListener*>(pIListener);

	if (pIScrollListener != NULL)
	{
		switch (GetMessageID())
		{
		case WM_HSCROLL:
			bHandled = pIScrollListener->OnHScroll(GetScrollCode(), GetScrollPosition(), GetScrollBarHandle());
			break;

		case WM_VSCROLL:
			bHandled = pIScrollListener->OnVScroll(GetScrollCode(), GetScrollPosition(), GetScrollBarHandle());
			break;
		}
	}

	return bHandled;
}

//@mfunc int | CScrollEvent | GetScrollCode | The scroll code identifies the type of scrolling (line, page, etc.).
//@rdesc int
int CScrollEvent::GetScrollCode()
{
	return LOWORD(GetWParam());
}

//@mfunc short | CScrollEvent | GetScrollPosition | Return the scroll position.
//@rdesc short
short CScrollEvent::GetScrollPosition()
{
	return HIWORD(GetWParam());
}

//@mfunc short | CScrollEvent | GetScrollWindow | Return the scroll bar window handle.
//@rdesc HWND
HWND CScrollEvent::GetScrollBarHandle()
{
	return (HWND) GetLParam();
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __SCROLLEVENT_H__
