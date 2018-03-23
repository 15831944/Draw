///////////////////////////////////////////////////////////////////////////////
// EventRouterMap.h
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
// Authors:      
// Description:  Framework independent event model.
//

#pragma once

#ifndef __EVENTROUTERMAP_H__
#define __EVENTROUTERMAP_H__

#if !defined(_SFL)
#define _SFL
#endif

#if defined(_SFL_ATL_SUPPORT)

#include <foundation\Events\Event.h>
#include <foundation\Events\EventRouter.h>
#include <foundation\Events\EventFactory.h>

namespace stingray {
namespace foundation {

////////////////////////////////////////////////////////////////////////////////
// CEventRouterMapWrapperBase - Derives from the event router template parameter
// and mixes in a CMessageMap. Messages passed to the message map are forwarded
// to the RouteEvent() method.

template <typename routerbase_t>
class CEventRouterMapWrapper : public routerbase_t, public CMessageMap
{
public:
	// BOOL Required due to override
	virtual BOOL ProcessWindowMessage( HWND, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT&, DWORD dwMsgMapID = 0 )
	{
		dwMsgMapID = 0;
		bool bHandled = false;

		IEvent* pIEvent = GetEventFactory()->CreateWindowsEvent(uMsg, wParam, lParam);
		if (pIEvent != NULL)
		{
			bHandled = RouteEvent(pIEvent);
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

////////////////////////////////////////////////////////////////////////////////
// CEventRouterMap - Used to mixin a CMessageMap into a class that
// supports the IEventRouter interface.  Template parameter is the derived
// class type.  This class downcasts to the derived class type in order to
// call the RouteEvent() method.

template <typename T>
class CEventRouterMap : public CMessageMap
{
public:
	virtual BOOL ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0 )
	{
		// To get rid of the warning... 
		hWnd;
		dwMsgMapID;
		lResult;

		bool bHandled = FALSE;
		T* pT = static_cast<T*>(this);

		IEvent* pIEvent = GetEventFactory()->CreateWindowsEvent(uMsg, wParam, lParam);
		if (pIEvent != NULL)
		{
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

#endif  // #if defined(_SFL_ATL_SUPPORT)

#endif  // #ifndef __EVENTROUTERMAP_H__
