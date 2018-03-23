///////////////////////////////////////////////////////////////////////////////
// MvcController.h : Declaration of MvcController
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

// Author:       Dean Hallman
// Description:  Declaration of MvcController class.
//

//@doc MvcController

#pragma once

#ifndef __MFC_MVCCONTROLLER_H__
#define __MFC_MVCCONTROLLER_H__

// Includes

#include <Foundation\MVC\MvcController.h>
#include <Foundation\MVC\MFC\MvcModel.h>
#include <Foundation\Patterns\MFC\plugin.h>
#include <Foundation\MVC\MFC\MvcMsgHandler.h>
#include <Foundation\MVC\MFC\MvcVisualComponent.h>
#include <StingrayExportDefs.h>

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//
// MvcController
//
//@doc MvcController
//@mdata CWnd* | MvcController | m_pWnd | Pointer to the window that this controller is plugged into
//@xref <c MvcController>

//@doc MvcController
//@mdata MvcModel* | MvcController | m_pModel | Pointer to the model that this controller acts upon
//@xref <c MvcController>

//@doc MvcController
//@mdata MvcVisualComponent* | MvcController | m_pVp | Pointer to the component that this controller acts upon
//@xref <c MvcController>

//@doc MvcController
//@mdata static MvcController* | MvcController | m_psActiveCtlr | The single active controller.  Only one controller can be active at a time.
//@xref <c MvcController>


//
//@class
// The controller interprets mouse and keyboard input, updating
// the information in the model as needed to reflect that input.  The
// changes in the model are then displayed in the viewport.
//
// A controller is a message handler that can plug into a window and
// listen to the events it receives.  In response to those events,
// such as a mouse down or keypress, the controller calls the
// appropriate functions in the model and or viewport it controls.
//
//@base public | SECWndPlugIn
//@base public | IMvcMsgHandler
//
class MvcController : public SECWndPlugIn, public CMvcController<MvcModel,MvcVisualComponent>
{
// Constructor/Destructor
public:
	//@cmember SAD!
	/* Retrieve a pointer to an interface supported by this object. */
	/*
	virtual bool QueryGuid(REFGUID guid, void **ppvObj)
	{
		*ppvObj = NULL;

		if (guid == IID_IEventRouter)
			*ppvObj = static_cast<IEventRouter *>(this);

		return (*ppvObj != NULL);
	}*/

	 FOUNDATION_API MvcController();
	 FOUNDATION_API virtual ~MvcController();

	//@cmember
	/* Create the controller on the specified visual component*/
	 FOUNDATION_API virtual BOOL Create(CWnd* pWnd, MvcVisualComponent* pComp);

	//@cmember
	/* Plugs the controller into the specified window and visual component*/
	 FOUNDATION_API virtual BOOL PlugInTo(CWnd* pWnd, MvcVisualComponent* pVp);

// Attributes
protected:

	//@cmember
	/* Pointer to the window that this controller is plugged into*/
	CWnd* m_pWnd;

	// Static Attributes

	//@cmember
	/* The single active controller.  Only one controller can be active at a time.*/
	static MvcController* m_psActiveCtlr;

// Operations
public:

	//@cmember
	/* Get a pointer to the window that this controller is plugged into*/
	inline CWnd* GetWnd() const;

	//@cmember
	/* Retrieve the visual part the agent acts upon*/
	inline MvcVisualComponent* GetComponent() const;

	//@cmember
	/* Retrieve the visual part the agent acts upon*/
	FOUNDATION_API virtual void SetComponent(MvcVisualComponent* pVp);

	// IMvcMsgHandler interface

	//@cmember
	/* A windows message is being delegated to this component for handling*/
	FOUNDATION_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//@cmember
	/* The command message is being delegated to this component for handling*/
	FOUNDATION_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	//@cmember
	/* Retrieve the single active controller in the system*/
	FOUNDATION_API static MvcController* GetActiveController();

	//@cmember
	/* Set the active controller throughout the system*/
	FOUNDATION_API static void SetActiveController(MvcController* pWndCtlr);
};

///////////////////////////////////////////////////////////////////////////

// @mfunc Get a pointer to the window that this controller is plugged into
// @rdesc Pointer to a window
inline CWnd* MvcController::GetWnd() const
{
	return m_pWnd;
}

//@mfunc Returns the visual part this controller is acting upon
//@rdesc A pointer to the visual part the controller is acting upon
inline MvcVisualComponent* MvcController::GetComponent() const
{
	return GetViewport();
}

////////////////////////////////////////////////////////////////////////////
// MvcMsgDecoder
//
// @doc MvcMsgDecoder
// @class A set of static routines for decoding and manipulating Windows
// messages. The struct is used only as a way to give the functions a
// namespace and to allow inlining.

class MvcMsgDecoder
{
public:
	// @cmember
	/* Determine if message ID is a key message*/
	static BOOL IsKeyMessage(UINT m);
	// @cmember
	/* Determine if message ID is a mouse message*/
	static BOOL IsMouseMessage(UINT m);
	// @cmember
	/* If message is a mouse message, then extract the device point*/
	static BOOL DecodeMouseMessage(UINT m, WPARAM, LPARAM lParam, CPoint& pt);
};

/////////////////////////////////////////////////////////////////////////////
// MvcMsgDecoder inline methods

// @mfunc Determine if message ID is a key message
// @rdesc TRUE if message ID is a key message, FALSE if it is not
// @parm UINT | m | Message ID
inline BOOL MvcMsgDecoder::IsKeyMessage(UINT m)
{
	return (m == WM_CHAR || m == WM_KEYUP || m == WM_KEYDOWN);
}

// @mfunc Determine if message ID is a mouse message
// @rdesc TRUE if message ID is a mouse message, FALSE if it is not
// @parm UINT | m | Message ID
inline BOOL MvcMsgDecoder::IsMouseMessage(UINT m)
{
	return (
		m == WM_LBUTTONDBLCLK || m == WM_LBUTTONDOWN || m == WM_LBUTTONUP ||
		m == WM_MBUTTONDBLCLK || m == WM_MBUTTONDOWN || m == WM_MBUTTONUP ||
		m == WM_RBUTTONDBLCLK || m == WM_RBUTTONDOWN || m == WM_RBUTTONUP ||
		m == WM_MOUSEMOVE 
#if _MFC_VER > 0x0420
		|| m == WM_MOUSEWHEEL
#endif
		);
}

// @mfunc If message is a mouse message, then extract the device point
// @rdesc TRUE if message ID is a mouse message, FALSE if it is not
// @parm UINT | m | Message ID
// @parm Message WORD parameter (unused)
// @parm Message LONG parameter (contains point information)
// @parm CPoint& | pt | Output parameter
inline BOOL MvcMsgDecoder::DecodeMouseMessage(UINT m, WPARAM, LPARAM lParam, CPoint& pt)
{
	if (IsMouseMessage(m))
	{
		WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
		WORD yPos = HIWORD(lParam);  // vertical position of cursor 
		pt.x = xPos;
		pt.y = yPos;
		return TRUE;
	}
	return FALSE;
}

};  // namespace stingray::foundation
};  // namespace stingray

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // #ifndef __MFC_MVCCONTROLLER_H__
