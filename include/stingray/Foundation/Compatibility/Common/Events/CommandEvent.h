///////////////////////////////////////////////////////////////////////////////
// CommandEvent.h : Interface for command events.
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

#ifndef __COMPAT_COMMANDEVENT_H__
#define __COMPAT_COMMANDEVENT_H__

#include "Foundation\Compatibility\Common\CmnGuids.h"
#include "Foundation\Compatibility\Common\Events\WinEvent.h"
#include <StingrayExportDefs.h>

namespace rw
{

///////////////////////////////////////////////////////////////////////////
//@doc ICommandEvent
//
//@class ICommandEvent | Interface to a Windows command event. A command
// event contains a command identifier, a notification code, and possibly
// a handle to the control the generated the event.
//
//@base public | IWinEvent
//
class /*FOUNDATION_API*/ __declspec(uuid("47E1CE34-D500-11d2-8CAB-0010A4F36466"))
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
//@doc CommandEvent
//
//@class CommandEvent | This class encapsulates a Windows command event. A
// command event contains a command identifier, a notification code, and
// possibly a handle to the control the generated the event. The WORD
// parameter contains the command ID and notification code. The control
// handle is stored in the LONG parameter.
//
//@base public | WinEvent_T
//
class FOUNDATION_API CommandEvent : public WinEvent_T<ICommandEvent, &IID_ICommandEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a command event from a command ID, notify code, and control handle. */
	CommandEvent(UINT nCommandID, int nNotifyCode, HWND hCtl = 0);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	virtual BOOL Dispatch(IUnknown* pIListener);

	//@cmember
	/* Return the command ID. */
	virtual UINT GetCommandID() const;

	//@cmember
	/* Return the notify code. */
	virtual int GetNotifyCode() const;

	//@cmember
	/* Return the control handle. */
	virtual HWND GetControlHandle() const;

	//@cmember
	/* Set the command ID. */
	virtual void SetCommandID(const UINT nCommandID);

	//@cmember
	/* Set the notify code. */
	virtual void SetNotifyCode(const int nNotifyCode);

	//@cmember
	/* Set the control handle. */
	virtual void SetControlHandle(HWND hCtl);
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
class /*FOUNDATION_API*/ __declspec(uuid("47E1CE35-D500-11d2-8CAB-0010A4F36466"))
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
//@doc CommandQueryEvent
//
//@class CommandQueryEvent | A command query event is sent to command
// listeners to find out if a given command is handled. The command query
// only contains the command ID for a given command.
//
//@base public | ICommandQueryEvent
//
class FOUNDATION_API CommandQueryEvent : public ICommandQueryEvent
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a command query event from a command ID. */
	CommandQueryEvent(UINT nCommandID);

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
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
	//@cmember
	/* Add a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE AddRef();
	//@cmember
	/* Release a reference to this object. */
	virtual ULONG STDMETHODCALLTYPE Release();

	//@cmember
	/* Dispatches the event to the given event listener. */
	virtual BOOL Dispatch(IUnknown* pIListener);

	//@cmember
	/* Return the command ID. */
	virtual UINT GetCommandID() const;
	//@cmember
	/* Set the command ID. */
	virtual void SetCommandID(const UINT nCommandID);
};

};  // end namespace rw

#endif  // __COMPAT_COMMANDEVENT_H__
