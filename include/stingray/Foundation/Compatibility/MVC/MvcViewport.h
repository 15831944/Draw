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
//
// Author:       Dean Hallman
// Description:  Declaration of MvcViewport interface.
//

//@doc MvcViewport

#ifndef __COMPAT_MVCVIEWPORT_H__
#define __COMPAT_MVCVIEWPORT_H__

// Includes

#ifndef __COMPAT_MVCLOGICALPART_H__
#include "Foundation\Compatibility\MVC\MvcLogicalPart.h"
#endif

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _MVCDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    MVC_DATAEXT
#endif //_MVCDLL

#ifndef __COMPAT_MVCTEMPLATE_H__
#include "Foundation\Compatibility\MVC\MvcTemplate.h"
#endif

#ifndef __COMPAT_MVCMODEL_H__
#include "Foundation\Compatibility\MVC\MvcModel.h"
#endif

#ifndef __COMPAT_MVCCONTROLLER_H__
#include "Foundation\Compatibility\MVC\MvcController.h"
#endif

#ifndef __COMPAT_EVENTFACTORY_H__
#include "Foundation\Compatibility\Common\Events\EventFactory.h"
#endif

#include <StingrayExportDefs.h>


///////////////////////////////////////////////////////////////////////////
//
//  MvcViewport

//@doc MvcViewport
//@mfunc  void | MvcViewport | LineUp | Scroll one line up. Default implementation does nothing.
//@xref <c MvcViewport>

//@doc MvcViewport
//@mfunc  void | MvcViewport | LineDown | Scroll one line down. Default implementation does nothing.
//@xref <c MvcViewport>

//@doc MvcViewport
//@mfunc  void | MvcViewport | PageUp | Scroll one page up. Default implementation does nothing.
//@xref <c MvcViewport>

//@doc MvcViewport
//@mfunc  void | MvcViewport | PageDown | Scroll one page down. Default implementation does nothing.
//@xref <c MvcViewport>

//@doc MvcViewport
//@mdata MvcController* | MvcViewport | m_pCtlr  | A pointer to this viewport's controller
//@xref <c MvcViewport>

//@doc MvcViewport
//@mdata MvcModel* | MvcViewport | m_pModel | The model this visual part dependents upon
//@xref <c MvcViewport>


//
//@class
// A viewport is a logical part that depends upon a model and
// has a controller.  An MvcViewport is conceptually similar to MFC's
// CView class, but its most important difference is it isn't a
// window (or CWnd derivative).  In MFC, a CView uses inheritance
// to define the presentation logic to display a model.  MVC uses
// aggregation, thereby affording greater flexibility.  In effect,
// any CWnd-derived class can simply aggregate a viewport and
// delegate the rendering to it.
//
// MvcViewport can be mixed into any class.  So, if you want to define
// a CListCtrl viewport, you could multiply derive a class from
// CListCtrl and MvcViewport.  This would yield a list control that
// bridges into the MVC architecture nicely.
//
//@base public | MvcViewport_T
//@base public | MvcLogicalPart
//@base public | IMvcMsgHandler
//
class FOUNDATION_API MvcViewport : public MvcViewport_T<MvcLogicalPart,MvcModel,MvcController>, public IMvcMsgHandler
{
public:

	// DC
	// 
	//A visual part device context
	//
	class DC : public CDC
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
	MvcViewport(MvcVisualPart* pContainer = NULL);
	virtual ~MvcViewport();

	//@cmember
	/* Creates the viewport and optional controller*/
	virtual BOOL Create(CWnd* pWnd, MvcVisualPart* pContainer);

// Attributes
protected:

	CWnd* m_pWnd;

// Operations
public:

	virtual CWnd* GetWnd() const;

	virtual BOOL ContainsDP(const CPoint& pt);

	// Control Delegation

	//@cmember
	/* A windows message is being delegated to this component for handling*/
	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//@cmember
	/* The command message is being delegated to this component for handling*/
	BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Subject / Observer Members

	//@cmember
	/* The function reacts to notifications of change on the subject it is observing*/
	virtual void OnUpdate(IMvcSubject* pSubject, IMvcMessage* pMsg);

	// Invalidation Members

	//@cmember
	/* Invalidate the specified rectangle within this visual part*/
	virtual void InvalidateRect(const CRect& rcLog, BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

	//@cmember
	/* Returns the current invalid region as a rectangle.*/
	inline virtual BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);

	//@cmember
	/* Convert logical units to device units*/
	virtual void LPtoDP( LPPOINT lpPoints, int nCount = 1 ) const;
	virtual void LPtoDP( LPRECT lpRect ) const;
	virtual void LPtoDP( LPSIZE lpSize ) const;

	//@cmember
	/* Convert device units to logical units*/
	virtual void DPtoLP( LPPOINT lpPoints, int nCount = 1 ) const;
	virtual void DPtoLP( LPRECT lpRect ) const;
	virtual void DPtoLP( LPSIZE lpSize ) const;

	//@cmember
	/* Renders the component to a device context*/
	virtual void Draw(CDC* pDC);

	//@cmember
	/* Erases the viewport contents. */
	virtual void Erase(CDC* pDC);

	////////////// Logical Size Accessors //////////////

	//@cmember
	/* Returns the width and height of the component in logical units*/
	virtual CSize GetLogSize() const;

	//@cmember
	/* Returns a pointer to the event factory for this viewport. */
	virtual EventFactory* GetEventFactory();

// Implementation
protected:

	virtual BOOL OnCreate();
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

///////////////////////////////////////////////////////////////////////////


//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // __COMPAT_MVCVIEWPORT_H__

