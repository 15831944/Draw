///////////////////////////////////////////////////////////////////////////////
// KeyboardEvent.h : Interface for keyboard events.
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
// Authors:      Steve Danielson
// Description:  Framework independent event model.
//

#pragma once

#ifndef __KEYBOARDEVENT_H__
#define __KEYBOARDEVENT_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\WinEvent.h>
#include <foundation\Events\KeyboardEvent.h>
#include <foundation\Events\KeyboardListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

class __declspec(uuid("3C741331-9C59-4966-B509-B4A0A2FD2250"))
					IKeyboardEvent : public IWinEvent
{
public:
	// Basic keyboard params
	virtual UINT GetChar() const = 0;
	virtual UINT GetRepCount() const = 0;
	virtual UINT GetFlags() const = 0;

	// Extra flags (HIWORD of lParam)
	virtual UINT GetScanCode() const = 0;
	virtual bool GetExtendedKey() const = 0;
	virtual bool GetContextCode() const = 0;
	virtual bool GetPrevKeyState() const = 0;
	virtual bool GetTransitionState() const = 0;
};

class CKeyboardEvent : public CWinEventBase<IKeyboardEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a keyboard event from a message ID, WPARAM, and LPARAM. */
	inline CKeyboardEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	// Basic keyboard params
	inline virtual UINT GetChar() const;
	inline virtual UINT GetRepCount() const;
	inline virtual UINT GetFlags() const;

	// Extra flags (HIWORD of lParam)
	inline virtual UINT GetScanCode() const;
	inline virtual bool GetExtendedKey() const;
	inline virtual bool GetContextCode() const;
	inline virtual bool GetPrevKeyState() const;
	inline virtual bool GetTransitionState() const;
};


CKeyboardEvent::CKeyboardEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IKeyboardEvent>(nMessageID, wParam, lParam)
{
}

bool CKeyboardEvent::Dispatch(IQueryGuid* pIListener)
{
	// We want to handle these messages:
	/*
	#define WM_KEYFIRST                     0x0100
	#define WM_KEYDOWN                      0x0100
	#define WM_KEYUP                        0x0101
	#define WM_CHAR                         0x0102
	#define WM_DEADCHAR                     0x0103
	#define WM_SYSKEYDOWN                   0x0104
	#define WM_SYSKEYUP                     0x0105
	#define WM_SYSCHAR                      0x0106
	#define WM_SYSDEADCHAR                  0x0107
	#define WM_KEYLAST                      0x0108
	*/

	bool bHandled = false;
	IKeyboardListener* pIKeyboardListener = guid_cast<IKeyboardListener*>(pIListener);

	if (pIKeyboardListener != NULL)
	{
		switch (GetMessageID())
		{
		case WM_KEYDOWN:
			bHandled = pIKeyboardListener->OnKeyDown(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_KEYUP:
			bHandled = pIKeyboardListener->OnKeyUp(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_CHAR:
			bHandled = pIKeyboardListener->OnChar(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_DEADCHAR:
			bHandled = pIKeyboardListener->OnDeadChar(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_SYSKEYDOWN:
			bHandled = pIKeyboardListener->OnSysKeyDown(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_SYSKEYUP:
			bHandled = pIKeyboardListener->OnSysKeyUp(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_SYSCHAR:
			bHandled = pIKeyboardListener->OnSysChar(GetChar(), GetRepCount(), GetFlags());
			break;

		case WM_SYSDEADCHAR:
			bHandled = pIKeyboardListener->OnSysDeadChar(GetChar(), GetRepCount(), GetFlags());
			break;
		}
	}

	return bHandled;
}

// Basic keyboard params
UINT CKeyboardEvent::GetChar() const
{
	return static_cast<UINT>(GetWParam());
}

UINT CKeyboardEvent::GetRepCount() const
{
	return static_cast<UINT>(LOWORD(GetLParam()));
}

UINT CKeyboardEvent::GetFlags() const
{
	return static_cast<UINT>(HIWORD(GetLParam()));
}

// Extra flags (HIWORD of lParam)
UINT CKeyboardEvent::GetScanCode() const
{
	// TODO test this to see if it is correct
	return static_cast<UINT>(GetFlags() & 0x00FF);
}

bool CKeyboardEvent::GetExtendedKey() const
{
	// TODO test this to see if it is correct
	return ((GetFlags() & 0x0100) != 0);
}

bool CKeyboardEvent::GetContextCode() const
{
	// TODO test this to see if it is correct
	return ((GetFlags() & 0x2000) != 0);
}

bool CKeyboardEvent::GetPrevKeyState() const
{
	// TODO test this to see if it is correct
	return ((GetFlags() & 0x4000) != 0);
}

bool CKeyboardEvent::GetTransitionState() const
{
	// TODO test this to see if it is correct
	return ((GetFlags() & 0x8000) != 0);
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __KEYBOARDEVENT_H__
