///////////////////////////////////////////////////////////////////////////////
// nodewnd.h : Declaration of SECLayoutNodeWnd
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
// Author:       Mark Isham
// Description:  Declaration of SECLayoutNodeWnd
//
// SECLayoutNodeWnd class (see also SECLayoutNode base class)
// This derivation of SECLayoutNode provides the implementation
// for CWnd types in the layout node tree.
//

#ifndef __SECLAYOUTNODEWND_H__
#define __SECLAYOUTNODEWND_H__

// Header Includes
#include <StingrayExportDefs.h>

#ifndef __SECLAYOUTNOD_H__
#include "toolkit\layout\layoutnd.h"
#endif

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

//@doc SECLayoutNodeWnd
//@mfunc HWND  | SECLayoutNodeWnd | GetAttachedHwnd | Get the HWND of the window attached to this node.
//@xref <c SECLayoutNodeWnd>

/////////////////////////////////////////////////////////////////////////////
// SECLayoutNodeWnd

//@doc SECLayoutNodeWnd 
//@class Layout node designed to bridge the gap to the WIN32 windows world.
//@BASE public | SECLayoutNode
//@comm Objects of this class are used to attach to existing windows and plug them into the layout framework.
class SECLayoutNodeWnd : public SECLayoutNode, public SECDefReparentableNode,
						 public SECDefHideableNode
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLayoutNodeWnd();
	TOOLKIT_API virtual ~SECLayoutNodeWnd();

	//@access Operations
	
	//@cmember
	/* Attach to a window from a CWnd*/
	TOOLKIT_API BOOL AttachWnd(CWnd* pWnd,CWnd* pParent);

	//@cmember
	/* Attach to a window from a handle*/
	TOOLKIT_API BOOL AttachWnd(HWND hWnd,CWnd* pParent);

	//@cmember
	/* Attach to a window from a control id*/
	TOOLKIT_API BOOL AttachWnd(UINT nID,CWnd* pParent);

	//@cmember
	/* Get the attached hWnd*/
	virtual HWND GetAttachedHwnd() { return m_hNodeWnd; }

	// Attributes

	TOOLKIT_API virtual BOOL IsNodeAttached();

	// Returns the DeferWindowCount for this and all child nodes.
	virtual int GetDeferWindowCount()		{ return 1; }
	virtual int GetDeferWindowCount(BOOL)	{ return GetDeferWindowCount(); }

	// Operations
	TOOLKIT_API virtual BOOL RealizeNodeHelper(HDWP* phDWP,HDC hDC);	

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	//@access Overridables

	//@cmember
	/* Window invalidation is about to occur*/
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rectInvalid,BOOL bDoErase);
	
	// SECDefReparentableNode overrides
	TOOLKIT_API virtual void SetNewNodeOwnerHWND(HWND hWndNew);
	
	// SECDefHideableNode overrides
	TOOLKIT_API virtual BOOL OnShowNode(BOOL bShow);	

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	HWND m_hNodeWnd,m_hParentWnd;
	BOOL m_bIsActiveX;
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SECLAYOUTNODEWND_H__

