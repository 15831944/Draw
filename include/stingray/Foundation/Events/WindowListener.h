///////////////////////////////////////////////////////////////////////////////
// WindowListener.h : Declares mouse listener interface and adapter class.
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

#pragma once

#ifndef __WINDOWLISTENER_H__
#define __WINDOWLISTENER_H__

#include <foundation\SflGuids.h>
#include <foundation\Events\EventListener.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc IWindowListener
//
//@class IWindowListener | Interface to handling mouse events. Window event
// listeners map various mouse events onto the virtual member functions for
// handling.
//
//
//@base public | IEventListener
//
class __declspec(uuid("A67C846D-0A0A-4b5e-8DC0-3DA18454F582"))
				IWindowListener : public IEventListener
{
public:
	//@cmember
	/* Handles window create events. */
	virtual bool OnCreate(LPCREATESTRUCT lpCreateStruct) = 0;
	//@cmember
	/* Handles window destroy events. */
	virtual bool OnDestroy() = 0;
	//@cmember
	/* Handles window move events. */
	virtual bool OnMove(int x, int y) = 0;
	//@cmember
	/* Handles window size events. */
	virtual bool OnSize(UINT nFlag, int cx, int cy) = 0;
	//@cmember
	/* Handles window erase background events. */
	virtual bool OnEraseBkgnd(HDC hDC) = 0;
	//@cmember
	/* Handles window paint events. */
	virtual bool OnPaint(HDC hDC) = 0;
	//@cmember
	/* Handles window position changing events. */
	virtual bool OnWindowPosChanging(LPWINDOWPOS lpWindowPos) = 0;
	//@cmember
	/* Handles window position changed events. */
	virtual bool OnWindowPosChanged(LPWINDOWPOS lpWindowPos) = 0;
	//@cmember
	/* Handles window timer events. */
	virtual bool OnTimer(SEC_UINT nIDTimer) = 0;
};

///////////////////////////////////////////////////////////////////////////
//@doc CWindowAdapter
//
//@class CWindowAdapter | The mouse adapter class supplies a default
// implementation of the <c IWindowListener> interface. The
// <mf CWindowAdapter::HandleEvent> function deciphers the event and maps
// it to a member function for handling. This class supplies a default
// implementation for all handler messages in the IWindowListener interface
// that always return FALSE. Window listeners can be derived from this class
// that override and implement only the handlers they are interested in.
//
//@base public | CEventListenerBase
//
class CWindowAdapter : public CEventListenerBase<IWindowListener>
{
// Operations
public:
	//@cmember
	/* Handles window create events. */
	inline virtual bool OnCreate(LPCREATESTRUCT lpCreateStruct);
	//@cmember
	/* Handles window destroy events. */
	inline virtual bool OnDestroy();
	//@cmember
	/* Handles window move events. */
	inline virtual bool OnMove(int x, int y);
	//@cmember
	/* Handles window size events. */
	inline virtual bool OnSize(UINT nFlag, int cx, int cy);
	//@cmember
	/* Handles window erase background events. */
	inline virtual bool OnEraseBkgnd(HDC hDC);
	//@cmember
	/* Handles window paint events. */
	inline virtual bool OnPaint(HDC hDC);
	//@cmember
	/* Handles window position changing events. */
	inline virtual bool OnWindowPosChanging(LPWINDOWPOS lpWindowPos);
	//@cmember
	/* Handles window position changed events. */
	inline virtual bool OnWindowPosChanged(LPWINDOWPOS lpWindowPos);
	//@cmember
	/* Handles window timer events. */
	inline virtual bool OnTimer(SEC_UINT nIDTimer);
};

///////////////////////////////////////////////////////////////////////////
//
// CWindowAdapter
//

//@mfunc Handles window create events.
bool CWindowAdapter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct;
	return false;
}

//@mfunc Handles window destroy events.
bool CWindowAdapter::OnDestroy()
{
	return false;
}

//@mfunc Handles window move events.
bool CWindowAdapter::OnMove(int x, int y)
{
	x; y;
	return false;
}

//@mfunc Handles window size events.
bool CWindowAdapter::OnSize(UINT nFlag, int cx, int cy)
{
	nFlag;
	cx; cy;
	return false;
}

//@mfunc Handles window erase background events.
bool CWindowAdapter::OnEraseBkgnd(HDC hDC)
{
	hDC;
	return false;
}

//@mfunc Handles window paint events.
bool CWindowAdapter::OnPaint(HDC hDC)
{
	hDC;
	return false;
}

//@mfunc Handles window position changing events.
bool CWindowAdapter::OnWindowPosChanging(LPWINDOWPOS lpWindowPos)
{
	lpWindowPos;
	return false;
}

//@mfunc Handles window position changed events.
bool CWindowAdapter::OnWindowPosChanged(LPWINDOWPOS lpWindowPos)
{
	lpWindowPos;
	return false;
}

//@mfunc Handles window timer events.
bool CWindowAdapter::OnTimer(SEC_UINT nIDTimer)
{
	nIDTimer;
	return false;
}

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __WINDOWLISTENER_H__
