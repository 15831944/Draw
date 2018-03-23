///////////////////////////////////////////////////////////////////////////////
// WindowEvents.h  Interface for mouse events.
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

#ifndef __WINDOWEVENTS_H__
#define __WINDOWEVENTS_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\WinEvent.h>
#include <foundation\Events\WindowEvents.h>
#include <foundation\Events\WindowListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IWindowCreateEvent | Interface for mouse events.
//
//@class IWindowCreateEvent | Interface to mouse events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("1ED09371-40A9-11d3-AF0D-006008AFE059"))
					IWindowCreateEvent : public IWinEvent
{
public:
	//@cmember
	/* Return pointer to CREATESTRUCT structure. */
	virtual LPCREATESTRUCT GetCreateStruct() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowCreateEvent
//
//@class CWindowCreateEvent | This class encapsulates a Windows size event. The
// LONG parameter of the Windows message contains the width and height
// specified by the size event.
//
//@base public | CWinEventBase
//

class CWindowCreateEvent : public CWinEventBase<IWindowCreateEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a size event from a message ID, WPARAM, and LPARAM. */
	inline CWindowCreateEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return pointer to CREATESTRUCT structure. */
	inline virtual LPCREATESTRUCT GetCreateStruct() const;
};

///////////////////////////////////////////////////////////////////////////
// CWindowCreateEvent

//@mfunc | CWindowCreateEvent | CWindowCreateEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CWindowCreateEvent::CWindowCreateEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IWindowCreateEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowCreateEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		pIWindowListener->AddRef();
		bHandled = pIWindowListener->OnCreate(GetCreateStruct());
		pIWindowListener->Release();
	}

	return bHandled;
}

//@mfunc Return pointer to CREATESTRUCT structure.
LPCREATESTRUCT CWindowCreateEvent::GetCreateStruct() const
{
	return (LPCREATESTRUCT) GetLParam();
}


///////////////////////////////////////////////////////////////////////////
//@doc CWindowDestroyEvent
//
//@class CWindowDestroyEvent | This class encapsulates a Windows size event. The
// LONG parameter of the Windows message contains the width and height
// specified by the size event.
//
//@base public | CWinEventBase
//
 
class CWindowDestroyEvent : public IWinEvent
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a size event from a message ID, WPARAM, and LPARAM. */
	inline CWindowDestroyEvent(const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Attributes
protected:
	//@cmember
	/* Reference count. */
	ULONG m_ulRefCount;

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
	/* Return the message ID. */
	inline virtual UINT GetMessageID() const;

	//@cmember
	/* Return the WORD parameter. */
	inline virtual WPARAM GetWParam() const;

	//@cmember
	/* Set the WORD parameter. */
	inline virtual void SetWParam(const WPARAM wParam);

	//@cmember
	/* Return the LONG parameter. */
	inline virtual LPARAM GetLParam() const;

	//@cmember
	/* Set the LONG parameter. */
	inline virtual void SetLParam(const LPARAM lParam);

	//@cmember
	/* Return the message result. */
	inline virtual LRESULT GetLResult() const;

	//@cmember
	/* Set the message result. */
	inline virtual void SetLResult(const LRESULT lResult);

};


///////////////////////////////////////////////////////////////////////////
// CWindowDestroyEvent

//@mfunc | CWindowDestroyEvent | CWindowDestroyEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CWindowDestroyEvent::CWindowDestroyEvent(const WPARAM wParam, const LPARAM lParam)
{
	wParam;
	lParam;
	m_ulRefCount = 1;
}

//@mfunc Retrieve a pointer to an interface supported by this object.
bool CWindowDestroyEvent::QueryGuid(REFGUID guid, void **ppvObj)
{
	*ppvObj = NULL;

	if (guid == __uuidof(IEvent))
	{
		*ppvObj = static_cast<IEvent*>(this);
	}
	else if (guid == __uuidof(IWinEvent))
	{
		*ppvObj = static_cast<IWinEvent*>(this);
	}

	return (*ppvObj != NULL);
}

//@mfunc Add a reference to this object.
ULONG CWindowDestroyEvent::AddRef()
{
	return ++m_ulRefCount;
}

//@mfunc Release a reference to this object.
ULONG CWindowDestroyEvent::Release()
{
	ULONG ulRefCount = --m_ulRefCount;
	if (m_ulRefCount == 0)
	{
		delete this;
	}
	return ulRefCount;
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowDestroyEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		pIWindowListener->AddRef();
		bHandled = pIWindowListener->OnDestroy();
		pIWindowListener->Release();
	}

	return bHandled;
}

//@mfunc Return the message ID.
UINT CWindowDestroyEvent::GetMessageID() const
{
	return WM_DESTROY;
}

//@mfunc Return the WORD parameter.
WPARAM CWindowDestroyEvent::GetWParam() const
{
	return 0;
}

//@mfunc Set the WORD parameter.
void CWindowDestroyEvent::SetWParam(const WPARAM wParam)
{
	wParam;
}

//@mfunc Return the LONG parameter.
LPARAM CWindowDestroyEvent::GetLParam() const
{
	return 0;
}

//@mfunc Set the LONG parameter.
void CWindowDestroyEvent::SetLParam(const LPARAM lParam)
{
	lParam;
}

//@mfunc Return the message result.
LRESULT CWindowDestroyEvent::GetLResult() const
{
	return 0;
}

//@mfunc Set the message result.
void CWindowDestroyEvent::SetLResult(const LRESULT lResult)
{
	lResult;
}



///////////////////////////////////////////////////////////////////////////
//@doc IWindowSizeEvent | Interface for mouse events.
//
//@class IWindowSizeEvent | Interface to mouse events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("DB2FC42C-FE00-47a3-80DF-22DFD4FE5E54"))
					IWindowSizeEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the resizing flag. */
	virtual UINT GetFlag() const = 0;

	//@cmember
	/* Return the width specified by the size message. */
	virtual long GetWidth() const = 0;

	//@cmember
	/* Return the width specified by the size message. */
	virtual long GetHeight() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowSizeEvent
//
//@class CWindowSizeEvent | This class encapsulates a Windows size event. The
// LONG parameter of the Windows message contains the width and height
// specified by the size event.
//
//@base public | CWinEventBase
//
class CWindowSizeEvent : public CWinEventBase<IWindowSizeEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a size event from a message ID, WPARAM, and LPARAM. */
	inline CWindowSizeEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the resizing flag. */
	inline virtual UINT GetFlag() const;

	//@cmember
	/* Return the width specified by the size message. */
	inline virtual long GetWidth() const;

	//@cmember
	/* Return the width specified by the size message. */
	inline virtual long GetHeight() const;
};


///////////////////////////////////////////////////////////////////////////
// CWindowSizeEvent

//@mfunc | CWindowSizeEvent | CWindowSizeEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CWindowSizeEvent::CWindowSizeEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IWindowSizeEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowSizeEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		pIWindowListener->AddRef();
		bHandled = pIWindowListener->OnSize(GetFlag(), GetWidth(), GetHeight());
		pIWindowListener->Release();
	}

	return bHandled;
}

//@mfunc UINT | CWindowSizeEvent | GetFlag | Return the resizing flag.
//@rdesc UINT
UINT CWindowSizeEvent::GetFlag() const
{
	return (UINT)GetWParam();
}

//@mfunc long | CWindowSizeEvent | GetWidth | Return the width specified by the size message.
long CWindowSizeEvent::GetWidth() const
{
	return LOWORD(GetLParam());
}

//@mfunc long | CWindowSizeEvent | GetWidth | Return the width specified by the size message.
long CWindowSizeEvent::GetHeight() const
{
	return HIWORD(GetLParam());
}


///////////////////////////////////////////////////////////////////////////
//@doc IWindowPaintEvent | Interface for mouse events.
//
//@class IWindowPaintEvent | Interface to mouse events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("10C387AD-7462-46a5-9A59-17EAADE1CE15"))
					IWindowPaintEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the device context. */
	virtual HDC GetDC() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowPaintEvent
//
//@class CWindowPaintEvent | This class encapsulates a Windows paint event.
//
//@base public | CWinEventBase
//
class CWindowPaintEvent : public CWinEventBase<IWindowPaintEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a size event from a message ID, WPARAM, and LPARAM. */
	inline CWindowPaintEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the device context. */
	inline virtual HDC GetDC() const;
};


///////////////////////////////////////////////////////////////////////////
// CWindowPaintEvent

//@mfunc | CWindowPaintEvent | CWindowPaintEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CWindowPaintEvent::CWindowPaintEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IWindowPaintEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowPaintEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		bHandled = pIWindowListener->OnPaint(GetDC());
		pIWindowListener->Release();
	}

	return bHandled;
}

HDC CWindowPaintEvent::GetDC() const
{
	return (HDC) GetWParam();
}


///////////////////////////////////////////////////////////////////////////
//@doc IWindowEraseBkgndEvent | Interface for erase background events.
//
//@class IWindowEraseBkgndEvent | Interface to erase background events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("512FEF03-0739-4cd1-A468-41E0C67F2A33"))
					IWindowEraseBkgndEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the device context. */
	virtual HDC GetDC() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowEraseBkgndEvent
//
//@class CWindowEraseBkgndEvent | This class encapsulates a Windows erase background message.
//
//@base public | CWinEventBase
//
class CWindowEraseBkgndEvent : public CWinEventBase<IWindowEraseBkgndEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct an erase background event from a message ID, WPARAM, and LPARAM. */
	inline CWindowEraseBkgndEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the device context. */
	inline virtual HDC GetDC() const;
};


///////////////////////////////////////////////////////////////////////////
// CWindowEraseBkgndEvent

//@mfunc | CWindowEraseBkgndEvent | CWindowEraseBkgndEvent | Construct a mouse event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for windows message.
//@parmopt LPARAM | lParam | 0 | Long parameter for windows message.
CWindowEraseBkgndEvent::CWindowEraseBkgndEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IWindowEraseBkgndEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowEraseBkgndEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		bHandled = pIWindowListener->OnEraseBkgnd(GetDC());
		pIWindowListener->Release();
	}

	return bHandled;
}

HDC CWindowEraseBkgndEvent::GetDC() const
{
	return (HDC) GetWParam();
}

///////////////////////////////////////////////////////////////////////////
//@doc IWindowTimerEvent | Interface for timer events.
//
//@class IWindowTimerEvent | Interface for timer events. This interface derives
// from IWinEvent.
//
//@base public | IWinEvent
//
class __declspec(uuid("3CB65660-6096-11d3-8459-006008BFFE10"))
					IWindowTimerEvent : public IWinEvent
{
public:
	//@cmember
	/* Return the identifier of the timer. */
	virtual SEC_UINT GetTimerID() const = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowTimerEvent
//
//@class CWindowTimerEvent | This class encapsulates a Windows timer message.
//
//@base public | CWinEventBase
//
class CWindowTimerEvent : public CWinEventBase<IWindowTimerEvent>
{
// Constructor/destructor
public:

	//@cmember
	/* Construct a timer event from a message ID, WPARAM, and LPARAM. */
	inline CWindowTimerEvent(const UINT nMessageID, const WPARAM wParam = 0, const LPARAM lParam = 0L);

// Operations
public:

	//@cmember
	/* Dispatches the event to the given event listener. */
	inline virtual bool Dispatch(IQueryGuid* pIListener);

	//@cmember
	/* Return the identifier of the timer. */
	inline virtual SEC_UINT GetTimerID() const;
};

///////////////////////////////////////////////////////////////////////////
// CWindowTimerEvent

//@mfunc | CWindowTimerEvent | CWindowTimerEvent | Construct a timer event from a message ID, WPARAM, and LPARAM.
//@parm const UINT | nMessageID | Windows message ID (WM_*).
//@parmopt WPARAM | wParam | 0 | Word parameter for timer identifer.
//@parmopt LPARAM | lParam | 0 | Long parameter for timer callback.
CWindowTimerEvent::CWindowTimerEvent(const UINT nMessageID, const WPARAM wParam, const LPARAM lParam) :
CWinEventBase<IWindowTimerEvent>(nMessageID, wParam, lParam)
{
}

//@mfunc Dispatches the event to the given event listener.
//@rdesc TRUE if listener handles event; otherwise FALSE.
//@parm Pointer to listener to handle event.
bool CWindowTimerEvent::Dispatch(IQueryGuid* pIListener)
{
	bool bHandled = false;
	IWindowListener* pIWindowListener = guid_cast<IWindowListener*>(pIListener);

	if (pIWindowListener != NULL)
	{
		bHandled = pIWindowListener->OnTimer(GetTimerID());
		pIWindowListener->Release();
	}

	return bHandled;
}

SEC_UINT CWindowTimerEvent::GetTimerID() const
{
	return (SEC_UINT)GetWParam();
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __WINDOWEVENTS_H__
