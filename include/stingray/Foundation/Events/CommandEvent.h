///////////////////////////////////////////////////////////////////////////////
// CommandEvent.h : : Interface for command events.
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

#ifndef __COMMANDEVENT_H__
#define __COMMANDEVENT_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\WinEvent.h>
#include <foundation\Events\CommandEvent.h>
#include <foundation\Events\CommandListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc ICommandEvent
//
//@class ICommandEvent | Interface to a Windows command event. A command
// event contains a command identifier, a notification code, and possibly
// a handle to the control the generated the event.
//
//@base public | IWinEvent
//
class __declspec(uuid("30A118DD-AC83-49d4-A5B3-1E3FA3649A9B"))
				ICommandEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the command ID. */
	virtual UINT GetCommandID() const = 0;

	//@cmember
	/* Return the notify code. */
	virtual int GetNotifyCode() const = 0;

	//@cmember
	/* Return the control handle. */
	virtual HWND GetControlHandle() const = 0;

	//@cmember
	/* Set the command ID. */
	virtual void SetCommandID(const UINT nCommandID) = 0;

	//@cmember
	/* Set the notify code. */
	virtual void SetNotifyCode(const int nNotifyCode) = 0;

	//@cmember
	/* Set the control handle. */
	virtual void SetControlHandle(HWND hCtl) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CCommandEvent
//
//@class CCommandEvent | This class encapsulates a Windows command event. A
// command event contains a command identifier, a notification code, and
// possibly a handle to the control the generated the event. The WORD
// parameter contains the command ID and notification code. The control
// handle is stored in the LONG parameter.
//
//@base public | CWinEventBase
//
class CCommandEvent : public CWinEventBase<ICommandEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a command event from a command ID, notify code, and control handle. */
	inline CCommandEvent(UINT nCommandID, int nNotifyCode, HWND hCtl = 0);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the command ID. */
	inline virtual UINT GetCommandID() const;

	//@cmember
	/* Return the notify code. */
	inline virtual int GetNotifyCode() const;

	//@cmember
	/* Return the control handle. */
	inline virtual HWND GetControlHandle() const;

	//@cmember
	/* Set the command ID. */
	inline virtual void SetCommandID(const UINT nCommandID);

	//@cmember
	/* Set the notify code. */
	inline virtual void SetNotifyCode(const int nNotifyCode);

	//@cmember
	/* Set the control handle. */
	inline virtual void SetControlHandle(HWND hCtl);
};

///////////////////////////////////////////////////////////////////////////
//@doc ICommandQueryEvent
//
//@class ICommandQueryEvent | A command query event is sent to command
// listeners to find out if a given command is handled. A command query
// event contains a command ID that indicates the command that is being
// queried.
//
//@base public | IEvent
//
class __declspec(uuid("E11D5180-57DD-4b33-BC29-D2719700B999"))
				ICommandQueryEvent : public IEvent
{
	//@cmember
	/* Return the command ID. */
	virtual UINT GetCommandID() const = 0;

	//@cmember
	/* Set the command ID. */
	virtual void SetCommandID(const UINT nCommandID) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CCommandQueryEvent
//
//@class CCommandQueryEvent | A command query event is sent to command
// listeners to find out if a given command is handled. The command query
// only contains the command ID for a given command.
//
//@base public | ICommandQueryEvent
//
class CCommandQueryEvent : public ICommandQueryEvent
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a command query event from a command ID. */
	inline CCommandQueryEvent(UINT nCommandID);

// Attributes
protected:
	//@cmember
	/* Reference count. */
	unsigned long m_ulRefCount;
	//@cmember
	/* Command ID to query. */
	UINT m_nCommandID;

// Operations
public:

	//@cmember
	/* Retrieve a pointer to an interface supported by this object. */
	inline virtual bool QueryGuid(REFGUID guid, void **ppvObj);
	//@cmember
	/* Add a reference to this object. */
	inline virtual ULONG STDMETHODCALLTYPE AddRef();
	//@cmember
	/* Release a reference to this object. */
	inline virtual ULONG STDMETHODCALLTYPE Release();

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the command ID. */
	inline virtual UINT GetCommandID() const;
	//@cmember
	/* Set the command ID. */
	inline virtual void SetCommandID(const UINT nCommandID);
};


///////////////////////////////////////////////////////////////////////////
// CCommandEvent

//@mfunc Construct a command event from a command ID, notify code, and control handle.
//@parm UINT | nCommandID | Command ID to associate with this command event.
//@parm int | nNotifyCode | Notification code to associate with this command event.
//@parmopt HWND | hCtl | 0 | Handle of control that generated the command event.
CCommandEvent::CCommandEvent(UINT nCommandID, int nNotifyCode, HWND hCtl) :
CWinEventBase<ICommandEvent>(WM_COMMAND, MAKELONG(nCommandID, nNotifyCode), (LPARAM) hCtl)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if event dispatched; otherwise FALSE.
//@parm Pointer to listener to dispatch event to.
bool CCommandEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = FALSE;

	ICommandListener* pICommandListener = guid_cast<ICommandListener*>(pIListener);

	if (pICommandListener != NULL)
	{
		pICommandListener->AddRef();
		bHandled = pICommandListener->OnCommand(GetCommandID(), GetNotifyCode());
		pICommandListener->Release();
	}

	return bHandled;
}

//@mfunc Return the command ID.
//@rdesc Command ID associated with this command event.
UINT CCommandEvent::GetCommandID() const
{
	return (UINT) (LOWORD(m_wParam));
}

//@mfunc Return the notify code.
//@rdesc Notification code associated with this command event.
int CCommandEvent::GetNotifyCode() const
{
	return (int) ((short) HIWORD(m_wParam));
}

//@mfunc Return the control handle.
//@rdesc Control handle associated with this command event.
HWND CCommandEvent::GetControlHandle() const
{
	return (HWND) m_lParam;
}

//@mfunc Set the command ID.
//@rdesc void
//@parm Command ID to associate with this event.
void CCommandEvent::SetCommandID(const UINT nCommandID)
{
	m_wParam = MAKELONG((WORD) nCommandID, (WORD) GetNotifyCode());
}

//@mfunc Set the notify code.
//@rdesc void
//@parm Notification code.
void CCommandEvent::SetNotifyCode(const int nNotifyCode)
{
	m_wParam = MAKELONG((WORD) GetCommandID(), (WORD) nNotifyCode);
}

//@mfunc Set the control handle.
//@rdesc void
//@parm Control handle to associate with this event.
void CCommandEvent::SetControlHandle(HWND hCtl)
{
	m_lParam = (LPARAM) hCtl;
}

///////////////////////////////////////////////////////////////////////////
// CCommandQueryEvent

//@mfunc Construct a command query event from a command ID.
//@parm Command ID to query.
CCommandQueryEvent::CCommandQueryEvent(UINT nCommandID) :
m_ulRefCount(1),
m_nCommandID(nCommandID)
{
}

//@mfunc Retrieve a pointer to an interface supported by this object.
//@parm Identifier of the interface being requested. 
//@parm Address of pointer variable that receives the interface pointer
// requested in riid.
//@rdesc S_OK if the interface is supported, E_NOINTERFACE if not.
bool CCommandQueryEvent::QueryGuid(REFGUID guid, void **ppvObj)
{
	if (guid == __uuidof(ICommandQueryEvent))
	{
		*ppvObj = static_cast<ICommandQueryEvent*>(this);
		return true;
	}

	if (guid == __uuidof(IEvent))
	{
		*ppvObj = static_cast<IEvent*>(this);
		return true;
	}

	return false;
}

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
ULONG CCommandQueryEvent::AddRef()
{
	return ++m_ulRefCount;
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
ULONG CCommandQueryEvent::Release()
{
	ULONG ulRefCount = --m_ulRefCount;
	if (m_ulRefCount == 0)
	{
		delete this;
	}
	return ulRefCount;
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if event dispatched; otherwise FALSE.
//@parm Pointer to listener to dispatch event to.
bool CCommandQueryEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;

	ICommandListener* pICommandListener = guid_cast<ICommandListener*>(pIListener);

	if (pICommandListener != NULL)
	{
		pICommandListener->AddRef();
		bHandled = pICommandListener->OnCommandQuery(GetCommandID());
		pICommandListener->Release();
	}

	return bHandled;
}

//@mfunc Return the command ID.
//@rdesc Command ID associated with this event.
UINT CCommandQueryEvent::GetCommandID() const
{
	return m_nCommandID;
}

//@mfunc Set the command ID.
//@rdesc void
//@parm Command ID to assign to event.
void CCommandQueryEvent::SetCommandID(const UINT nCommandID)
{
	m_nCommandID = nCommandID;
}


};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __COMMANDEVENT_H__
