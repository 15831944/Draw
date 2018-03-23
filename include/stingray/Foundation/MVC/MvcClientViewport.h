///////////////////////////////////////////////////////////////////////////////
// MvcClientViewport.h : SFL Model-View-Controller architecture 
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
// Author:       Jeff Boenig
// Description:  SFL MVC: Client window viewport
//

#pragma once

#ifndef __MVCCLIENTVIEWPORT_H__
#define __MVCCLIENTVIEWPORT_H__

#if defined(_SFL_ATL_SUPPORT)

#include <foundation\Events\EventRouterMap.h>
#include <Foundation\Apps\ClientWnd.h>
#include <foundation\StructuredGraphics\VisualWindow.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////
// CMvcClientViewport - Mixes a CClientWindowImpl with an MVC
// viewport and handles WM_SIZE messages by setting the viewport
// size.

template <typename T, typename _Viewport>
class CMvcClientViewport : public CClientWindowImpl<T>,
                           public _Viewport,
                           public CEventRouterMap<T>,
                           public IVisualWindow
{
// Embedded types
public:
	typedef CMvcClientViewport<T, _Viewport> _thisClass;
	typedef CClientWindowImpl<T> _windowBase;

// Constructors/destructor
public:
	CMvcClientViewport() :
		m_bInitDone(false)
	{
	}

// Attributes
protected:
	bool m_bInitDone;

// Operations
public:
	virtual BOOL Create(HWND hWndParent, LPRECT rc)
	{
		BOOL bSuccess = FALSE;

		if (CClientWindowImpl<T>::Create(hWndParent, *rc) != NULL)
		{
			bSuccess = _Viewport::Create(hWndParent, rc);
		}

		return bSuccess;
	}

	virtual HWND GetWindowHandle()
	{
		return m_hWnd;
	}

	virtual void Draw(CDC* pDC)
	{
		if (pDC != NULL)
		{
			_Viewport::Draw(pDC);
		}
		else
		{
			CClientGraphicsContext dc(*this);
			_Viewport::Draw(&dc);
			dc.Delete();
		}
	}

// Message handlers
public:
	BEGIN_MSG_MAP(_thisClass)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(_windowBase)
		CHAIN_MSG_MAP(CEventRouterMap<T>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// To get rid of the warnings...
		uMsg;
		wParam;
		lParam;
		bHandled;

		m_bInitDone = false;
		CreateController();
		return 0;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// To get rid of the warnings...
		bHandled;
		wParam;
		uMsg;

		int nWidth = LOWORD(lParam);
		int nHeight = HIWORD(lParam);
		_Viewport::SetSize(nWidth, nHeight);
		return 0;
	}

	LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL&)
    {
		if (!m_bInitDone)
		{
			OnInitialUpdate();
			m_bInitDone = true;
		}

        // Paint the window
		CPaintGraphicsContext dcPaint(*this);
		OnPrepareDC(&dcPaint);
		Draw(&dcPaint);
		OnCleanupDC(&dcPaint);

        return 0;
    }


	// GUID map implements the QueryGuid() function
	BEGIN_GUID_MAP(_thisClass)
		GUID_CHAIN_ENTRY(_Viewport)
		GUID_ENTRY(IVisualWindow)
	END_GUID_MAP
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #if defined(_SFL_ATL_SUPPORT)

#endif  // #ifndef __MVCCLIENTVIEWPORT_H__
