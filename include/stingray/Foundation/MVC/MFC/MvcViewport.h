///////////////////////////////////////////////////////////////////////////////
// MvcViewport.h : Declaration of MvcViewport
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
// Description:  Declaration of MvcViewport interface.
//

//@doc MvcViewport

#pragma once

#ifndef __MFC_MVCVIEWPORT_H__
#define __MFC_MVCVIEWPORT_H__

// Includes
#include <Foundation\MVC\MFC\MvcIfcs.h>
#include <Foundation\MVC\MFC\MvcLogicalPart.h>

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

#include <Foundation\MVC\MFC\MvcModel.h>
#include <Foundation\MVC\MFC\MvcController.h>
#include <Foundation\Events\EventFactory.h>
#include <Foundation\Events\EventRouter.h>
#include <Foundation\MVC\MvcViewport.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

///////////////////////////////////////////////////////////////////////////
//@doc MvcViewport
//
//@class This class is derived from an instantiation of the <c CMvcViewport>
// template class. It implements an MFC-specific, windowless viewport and
// maintains a pointer to the CWnd it belongs to. It instantiates the
// CMvcViewport template using <t MvcLogicalPart>, <t MvcModel>, and
// <t MvcController> as the parameters. It implements the MFC message
// handling functions <mf MvcViewport::OnWndMsg> and <mf MvcViewport::OnCmdMsg>
// so that it can integrated with the MFC message map architecture.
//
//@base public | CMvcViewport
//

class MvcViewport : public CMvcViewport<MvcLogicalPart,MvcModel,MvcController>
{
public:

	// DC
	// 
	//A visual part device context
	//
	class FOUNDATION_API DC : public CDC
	{
	// Constructors
	public:
		// Constructor takes a visual part and auto-prepare parameter
		 DC(MvcViewport* pViewport, BOOL bAutoPrepare = TRUE);

		 virtual ~DC();

	// Attributes
	protected:
		HWND m_hWnd;
	};

// Constructor(s) & destructor
public:
	 FOUNDATION_API MvcViewport(MvcVisualPart* pContainer = NULL);
	 FOUNDATION_API virtual ~MvcViewport();

	//@cmember
	/* Creates the viewport and optional controller*/
	 FOUNDATION_API virtual BOOL Create(CWnd* pWnd, MvcVisualPart* pContainer);

// Attributes
protected:

	CWnd* m_pWnd;

// Operations
public:

	 FOUNDATION_API virtual CWnd* GetWnd() const;

	 FOUNDATION_API virtual BOOL ContainsDP(const CPoint& pt);

	// Control Delegation

	//@cmember
	/* A windows message is being delegated to this component for handling*/
	  FOUNDATION_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//@cmember
	/* The command message is being delegated to this component for handling*/
	  FOUNDATION_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Subject / Observer Members

	//@cmember
	/* The function reacts to notifications of change on the subject it is observing*/
	  FOUNDATION_API virtual void OnUpdate(IMvcSubject* pSubject, IMvcMessage* pMsg);

	// Invalidation Members

	//@cmember
	/* Invalidate the specified rectangle within this visual part*/
	  FOUNDATION_API virtual void InvalidateRect(const CRect& rcLog, BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

	//@cmember
	/* Returns the current invalid region as a rectangle.*/
	inline virtual BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);

	//@cmember
	/* Convert logical units to device units*/
	  FOUNDATION_API virtual void LPtoDP( LPPOINT lpPoints, int nCount = 1 ) const;
	  FOUNDATION_API virtual void LPtoDP( LPRECT lpRect ) const;
	  FOUNDATION_API virtual void LPtoDP( LPSIZE lpSize ) const;

	//@cmember
	/* Convert device units to logical units*/
	FOUNDATION_API virtual void DPtoLP( LPPOINT lpPoints, int nCount = 1 ) const;
	FOUNDATION_API virtual void DPtoLP( LPRECT lpRect ) const;
	FOUNDATION_API  virtual void DPtoLP( LPSIZE lpSize ) const;

	//@cmember
	/* Renders the component to a device context*/
	FOUNDATION_API virtual void Draw(CDC* pDC);

	//@cmember
	/* Erases the viewport contents. */
	FOUNDATION_API virtual void Erase(CDC* pDC);

	////////////// Logical Size Accessors //////////////

	//@cmember
	/* Returns the width and height of the component in logical units*/
	 FOUNDATION_API virtual CSize GetLogSize() const;

	//@cmember
	/* Returns a pointer to the event factory for this viewport. */
	 FOUNDATION_API virtual stingray::foundation::CEventFactory* GetEventFactory();

// Implementation
protected:

	 FOUNDATION_API virtual BOOL OnCreate();
};

////////////
//
// Inline functions
//

//@doc MvcViewport
//@mfunc Returns the current invalid region as a rectangle.
//@rdesc Specifies the status of the update region. The value is nonzero if the
// update region is not empty; otherwise 0.
//@parm LPRECT | lpRect | Points to a CRect object or RECT structure that is to
// receive the client coordinates of the update that encloses the update region.
//@parm BOOL | bErase | Specifies whether the background in the update region is
// to be erased.
inline BOOL MvcViewport::GetUpdateRect(LPRECT lpRect, BOOL bErase) { return GetWnd()->GetUpdateRect(lpRect, bErase); }

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

#endif // #ifndef __MFC_MVCVIEWPORT_H__
