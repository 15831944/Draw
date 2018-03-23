///////////////////////////////////////////////////////////////////////////////
// MFCEventRouter.h
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

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\Events\Event.h>
#include <foundation\Events\EventRouter.h>
#include <foundation\Events\EventFactory.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

// IMsgHandler - Interface that is compatible with CWnd's message handling functions. IMsgHandler
// serves as a default base for CMFCEventRouter. 
class IMsgHandler
{
public:	
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) = 0;
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// CMFCEventRouter - Acts as a bridge between MFC's command/message handling mechanism and the 
// SFL event routing mechanism. Messages and commands are forwarded to the RouteEvent() method implemented
// by the router class.

template <typename router, typename MsgHandlerbase = IMsgHandler>
class CMFCEventRouter : public MsgHandlerbase
{
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{
		BOOL bHandled = FALSE;
		// Create the event and route it to event listeners.
		CEventFactory* pEventFactory = GetEventFactory();
		IEvent* pIEvent = NULL;

		if (pHandlerInfo != NULL)
		{
			// This message is a request for handler info.
			pIEvent = pEventFactory->CreateCommandQueryEvent(nID);
		}
		else if (nCode == CN_UPDATE_COMMAND_UI)
		{
			// Create a command update UI event.
			CCmdUI* pCmdUI = (CCmdUI*) pExtra;
			pCmdUI;
		}
		else
		{
			// Regular command event.
			pIEvent = pEventFactory->CreateCommandEvent(nID, nCode);
		}

		if (pIEvent != NULL)
		{
			// Route event to event listeners.
			router* pT = static_cast<router*>(this);
			bHandled = pT->RouteEvent(pIEvent);
			pIEvent->Release();
		}

		return bHandled;
	}

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		BOOL bHandled = FALSE;	
		// Create an event, using the event factory and route it to the event listeners.		
		IEvent* pIEvent = GetEventFactory()->CreateWindowsEvent(message, wParam, lParam);
		if (pIEvent != NULL)
		{
			router* pT = static_cast<router*>(this);
			bHandled = pT->RouteEvent(pIEvent);
			pIEvent->Release();
		}
		
		return bHandled;
	}	

	virtual CEventFactory* GetEventFactory()
	{
		static CEventFactory eventFactory;
		return &eventFactory;
	}
};


};	// namespace stingray::foundation
};  // namespace stingray
