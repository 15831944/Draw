///////////////////////////////////////////////////////////////////////////////
// UIUpdateEvent.h : Interface for UIUpdate events.
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
// Authors:      Jeff Boenig and George Shepherd
// Description:  Framework independent event model.
//

#pragma once

#ifndef __UIUPDATEEVENT_H__
#define __UIUPDATEEVENT_H__

#include <Foundation\SflGuids.h>
#include <Foundation\SflCommon.h>
#include <Foundation\Events\Event.h>
#include <Foundation\Events\UIUpdateElement.h>
#include <foundation\Events\UIUpdateEvent.h>
#include <foundation\Events\UIUpdateListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IUIUpdateEvent
//
//@class IUIUpdateEvent | Interface to a Windows UIUpdate event. A UIUpdate
// event contains a UIUpdate identifier, a notification code, and possibly
// a handle to the control the generated the event.
//
//@base public | IWinEvent
//
class __declspec(uuid("EB4A8E29-4C6A-4a81-87D5-1A8D74C39462"))
				IUIUpdateEvent : public IEvent
{
public:
	//@cmember
	/* Return the command ID. */
	virtual UINT GetCommandID() const = 0;

	//@cmember
	/* Return the update element. */
	virtual IUIUpdateElement* GetUpdateElement() const = 0;

	//@cmember
	/* Set the UIUpdate ID. */
	virtual void SetCommandID(const UINT nCommandID) = 0;

	//@cmember
	/* Set the update element. */
	virtual void SetUpdateElement(IUIUpdateElement* pIUpdateElement) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CUIUpdateEvent
//
//@class CUIUpdateEvent | This class encapsulates a Windows UIUpdate event. A
// UIUpdate event contains a UIUpdate identifier, a notification code, and
// possibly a handle to the control the generated the event. The WORD
// parameter contains the UIUpdate ID and notification code. The control
// handle is stored in the LONG parameter.
//
//@base public | CWinEventBase
//
 
class CUIUpdateEvent : public IUIUpdateEvent
{
// Constructor/destructor
public:
	//@cmember
	/* Construct a UIUpdate event from a command ID, notify code, and update element. */
	inline CUIUpdateEvent(UINT nCommandID, IUIUpdateElement* pIUpdateElement = 0);

// Attributes
protected:
	//@cmember
	/* Reference count. */
	unsigned long m_ulRefCount;
	//@cmember
	/* Command ID to query. */
	UINT m_nCommandID;
	//@cmember
	/* Pointer to the update element. */
	IUIUpdateElement* m_pIUpdateElement;

// Operations
public:
	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the command ID. */
	inline virtual UINT GetCommandID() const;

	//@cmember
	/* Return the update element. */
	inline virtual IUIUpdateElement* GetUpdateElement() const;

	//@cmember
	/* Set the UIUpdate ID. */
	inline virtual void SetCommandID(const UINT nCommandID);

	//@cmember
	/* Set the update element. */
	inline virtual void SetUpdateElement(IUIUpdateElement* pIUpdateElement);

	// The GUID map implements the QueryGuid function
	BEGIN_GUID_MAP(CUIUpdateEvent)
		GUID_ENTRY(IUIUpdateEvent)
		GUID_ENTRY(IEvent)
		GUID_ENTRY(IQueryGuid)
		GUID_ENTRY(IRefCount)
	END_GUID_MAP

	//@cmember
	/* Add a reference to this object. */
	inline virtual ULONG STDMETHODCALLTYPE AddRef();
	//@cmember
	/* Release a reference to this object. */
	inline virtual ULONG STDMETHODCALLTYPE Release();
};

///////////////////////////////////////////////////////////////////////////
// CUIUpdateEvent

//@mfunc Construct a UIUpdate event from a UIUpdate ID, notify code, and control handle.
//@parm UINT | nUIUpdateID | UIUpdate ID to associate with this UIUpdate event.
//@parm int | nNotifyCode | Notification code to associate with this UIUpdate event.
//@parmopt HWND | hCtl | 0 | Handle of control that generated the UIUpdate event.
CUIUpdateEvent::CUIUpdateEvent(UINT nCommandID, IUIUpdateElement* pIUpdateElement) :
m_pIUpdateElement(pIUpdateElement),
m_nCommandID(nCommandID),
m_ulRefCount(0L)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if event dispatched; otherwise FALSE.
//@parm Pointer to listener to dispatch event to.
bool CUIUpdateEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;

	IUIUpdateListener* pIUIUpdateListener = guid_cast<IUIUpdateListener*>(pIListener);

	if (pIUIUpdateListener != NULL)
	{
		pIUIUpdateListener->AddRef();
		bHandled = pIUIUpdateListener->OnUIUpdate(m_pIUpdateElement, m_nCommandID);
		pIUIUpdateListener->Release();
	}

	return bHandled;
}

//@mfunc Return the UIUpdate ID.
//@rdesc UIUpdate ID associated with this UIUpdate event.
UINT CUIUpdateEvent::GetCommandID() const
{
	return m_nCommandID;
}

//@mfunc Return the update element.
//@rdesc Control handle associated with this UIUpdate event.
IUIUpdateElement* CUIUpdateEvent::GetUpdateElement() const
{
	return m_pIUpdateElement;
}

//@mfunc Set the command ID.
//@rdesc void
//@parm Command ID to associate with this event.
void CUIUpdateEvent::SetCommandID(const UINT nCommandID)
{
	m_nCommandID = nCommandID;
}

//@mfunc Set the update element.
//@rdesc void
//@parm Update element to associate with this UI update event.
void CUIUpdateEvent::SetUpdateElement(IUIUpdateElement* pIUpdateElement)
{
	m_pIUpdateElement = pIUpdateElement;
}

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
ULONG CUIUpdateEvent::AddRef()
{
	return ++m_ulRefCount;
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
ULONG CUIUpdateEvent::Release()
{
	ULONG ulRefCount = --m_ulRefCount;
	if (m_ulRefCount == 0)
	{
		delete this;
	}
	return ulRefCount;
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __UIUPDATEEVENT_H__
