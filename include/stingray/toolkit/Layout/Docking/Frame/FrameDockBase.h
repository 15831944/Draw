///////////////////////////////////////////////////////////////////////////////
// FrameDockBase.h
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
// Description:  Declaration of SECFrameDockingFeatureBase 
//

#ifndef __SEC_FRAME_DOCKING_FEATURE_BASE_H__
#define __SEC_FRAME_DOCKING_FEATURE_BASE_H__

#ifdef WIN32

// Header Includes
#include "toolkit\layout\BorderClient.h"
#include "toolkit\layout\docking\DockIFace.h"
#include "toolkit\layout\docking\DragDrop\DockListn.h"
#include <StingrayExportDefs.h>

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

// Constants

// Dock Site constants for EnableDocking.
// (Not coincedently, these match the CBRS_ALIGN_* values)
#define SEC_DOCK_LEFT  			0x1000L
#define SEC_DOCK_TOP 			0x2000L
#define SEC_DOCK_RIGHT 			0x4000L
#define SEC_DOCK_BOTTOM			0x8000L
#define SEC_DOCK_HORZ			(SEC_DOCK_TOP|SEC_DOCK_BOTTOM)
#define SEC_DOCK_VERT			(SEC_DOCK_LEFT|SEC_DOCK_RIGHT)
#define SEC_DOCK_ANY			(SEC_DOCK_HORZ|SEC_DOCK_VERT)

// Border Client layout constants for SetBorderLayout
#define SEC_DOCKBORDERS_TBLR	SECLNBorderClient::TopBottomLeftRight
#define SEC_DOCKBORDERS_LRTB	SECLNBorderClient::LeftRightTopBottom

// Macros

// Types

// Forward Declarations
class SECVirtualDockbar;
class SECLNSizableDockBorder;
class SECLNDockBorderClientEdge;

/////////////////////////////////////////////////////////////////////////////
// SECClientWndNode

// Client window node supports the default implementation of ISECUndoableNode
class SECClientWndNode : public SECLayoutNode, public SECDefUndoableNode {};

/////////////////////////////////////////////////////////////////////////////
// SECFrameDockingFeatureBase

//@doc SECFrameDockingFeatureBase 
//@class Advanced docking frame window feature base class
//@comm Provides base advanced docking functionality that is not tied directly
// to a particular docking target type. The frame docking feature is the primary
// interface utilized to merge advanced docking window support with a particular
// frame window. SECFrameDockingFeatureBase is not intended to be instantiated
// directly, but rather serve as a base class for a concrete implementation.
//@xref <c SECFrameDockingFeature>
class SECFrameDockingFeatureBase : public ISECLNBorderClientEventRcvr
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Initialization/Destruction
	TOOLKIT_API SECFrameDockingFeatureBase();
	TOOLKIT_API virtual ~SECFrameDockingFeatureBase();

	enum DockSite { top, bottom, left, right };

	//@access Operations

	//@cmember
	/* Enable docking to the specified borders */
	TOOLKIT_API virtual BOOL EnableDocking(CWnd* pParent,DWORD dwDockStyle=SEC_DOCK_ANY,
							BOOL bCreateNewLocalDockMgr=FALSE,
							SECLNDockingMgr* pMgr=NULL);

	//@cmember
	/* Dock a dockable layout node to the associated frame window */
	virtual BOOL DockNode(SECLayoutNode* pNode) { return DockNode(pNode,top); }

	//@cmember
	/* Dock a dockable layout node to the associated frame window */
	TOOLKIT_API virtual BOOL DockNode(SECLayoutNode* pNode,DockSite site);

	//@cmember
	/* Float a dockable layout node to the specified screen rectangle */
	TOOLKIT_API virtual BOOL FloatNode(SECLayoutNode* pNode,LPCRECT lpRectScreen=NULL);	

	//@cmember
	/* Show/Hide an associated dockable layout node */
	TOOLKIT_API virtual BOOL ShowNode(SECLayoutNode* pNode,BOOL bShowNode=TRUE);

	//@cmember
	/* Toggle the current visibility state of an associated dockable node */
	TOOLKIT_API virtual BOOL ToggleNodeVisible(SECLayoutNode* pNode);	

	//@cmember
	/* Query the current visibility state of an associated dockable node */
	TOOLKIT_API virtual BOOL GetNodeVisible(SECLayoutNode* pNode, BOOL bCheckContainer = TRUE); // Fix# 104

	//@access Configuration

	//@cmember
	/* Set the current border layout algorithm used for positioning the associated dockable nodes */
	TOOLKIT_API virtual void SetBorderLayout(SECLNBorderClient::BorderAlgorithm BorderAlg,BOOL bRecalc=TRUE);

	//@cmember
	/* Set floating window parameters associated with a specific dockable node */
	TOOLKIT_API virtual BOOL SetFloatConfig(SECLayoutNode* pNode,BOOL bHideOnClose,BOOL bCloseEnabled=TRUE,
								CRect* pMRUFloatRect=NULL);

	// Utility Functions
	TOOLKIT_API static SECFrameDockingFeatureBase::DockSite DWordToDocksite(DWORD dwSite);
	TOOLKIT_API static DWORD DocksiteToDWord(SECFrameDockingFeatureBase::DockSite site);
	TOOLKIT_API static SECLNBorderClient::BorderPosition DocksiteToBorderPos(SECFrameDockingFeatureBase::DockSite site);
	inline SECLNDockingMgr* GetActiveDockMgr() { return m_pActiveDockMgr; }

protected:
	// Implementation of ISECLNBorderClientEventRcvr
	TOOLKIT_API virtual void OnClientRectChanged(const CRect&);

	// Overridables

	// Notification the OnSizeParent event has occurred
	TOOLKIT_API virtual LRESULT OnNotifyOnSizeParent(AFX_SIZEPARENTPARAMS* lpLayout);
	virtual LRESULT OnNotifyPostOnSizeParent() { return 1; }

	// Initialization of the docking border nodes.
	TOOLKIT_API virtual BOOL InitializeDockingBorders(CWnd* pParent,DWORD dwDockStyle);

	// Initialization of the docking window listener
	TOOLKIT_API virtual BOOL InitializeDockingWindowListner(CWnd* pParent,SECLayoutNode* pRootNode,
											SECLNDockingMgr* pMgr);

	// Must override this function to create the proper target type!											
	virtual SECLayoutNode* CreateDockingTarget(SECLayoutNode* pParent,
							DockSite site,CWnd* pParentWnd)=0;	// must override!											

	// Object Creation Overridables
	TOOLKIT_API virtual SECVirtualDockbar* 		CreateVirtualDockbar();
	virtual SECLNBorderClientEdge* 	CreateBorderClientEdge()	{ return new SECLNBorderClientEdge; }
	TOOLKIT_API virtual SECLNSizableDockBorder* 	CreateSizableDockBorder();
	virtual SECLNBorderClient* 		CreateBorderClientNode()	{ return new SECLNBorderClient; }
	virtual SECLayoutNode* 			CreateClientNode() 			{ return new SECClientWndNode; }
	virtual SECDockingListener* 		CreateDockingListener() 	{ return new SECDockingListener; }
	virtual SECLNDockingMgr* 		CreateDockingMgr(BOOL /* bDefMgr */) { return new SECLNDockingMgr; }

protected:
	// Implementation Member Functions
	TOOLKIT_API virtual BOOL CreateClientWnd(CWnd* pParentWnd);
	TOOLKIT_API virtual BOOL CreateClientEdges(CWnd* pParentWnd,DWORD dwDockStyle);
	TOOLKIT_API virtual BOOL CreateSizableBorders(CWnd* pParentWnd);
	TOOLKIT_API virtual void CreateDockingTargetBorders(CWnd* pParentWnd);
	TOOLKIT_API virtual SECLNSizableDockBorder* GetBorderSizingNode(DockSite site);
	TOOLKIT_API virtual SECLayoutNode* GetBorderTarget(DockSite site);
	TOOLKIT_API virtual SECLNDockingMgr* GetAppropDockingMgr(BOOL bCreateNewLocalDockMgr,
								SECLNDockingMgr* pMgr);
	TOOLKIT_API virtual DWORD ConvertDockSiteToBorderStyle(DockSite site,BOOL& bHorz);
	TOOLKIT_API virtual BOOL ResetSizableBorderVirtualRects();
	TOOLKIT_API virtual SECDockingNodeConstraints* CreateDockNodeCnstrIfNeeded(
								SECLayoutNode* pNode,SECLNDockingMgr* pMgr);

	// Implementation Member Variables
	
	// Implementation for hooking into the attached window
	SECVirtualDockbar* m_pVirtualDockBar;
	SECDockingListener* m_pDockingListener;
	
	// Docking mgr hooks
	SECLNDockingMgr* m_pLocalAllocDockMgr;
	SECLNDockingMgr* m_pActiveDockMgr;

	// Default docking mgr allocation ref-counting.
	TOOLKIT_API static SECLNDockingMgr* m_pDefDockingMgr;
	TOOLKIT_API static void RefCountDefDockMgrAlloc(BOOL bIncrease);
	TOOLKIT_API static int m_nDefDockMgrRefCount;

	// Members of the border layout
	SECLNMemMgr m_NodeMemMgr;	// for simplified memory management	
	SECLNBorderClient* m_pBorderClientParent;	
	SECLNBorderClientEdge* m_pBorderTop,*m_pBorderBottom,*m_pBorderLeft,*m_pBorderRight;
	SECLNSizableDockBorder* m_pBorderTopSize,*m_pBorderBottomSize,*m_pBorderLeftSize,*m_pBorderRightSize;
	SECLayoutNode* m_pBorderTargetTop,*m_pBorderTargetBottom,*m_pBorderTargetLeft,*m_pBorderTargetRight;
	SECLayoutNode* m_pClientWndNode;
	
	// Floating ptr pointing to the attached root layout node. 
	// Most likely m_pBorderClientParent
	SECLayoutNode* m_pRootNode;
	
	friend class SECVirtualDockbar;
};

/////////////////////////////////////////////////////////////////////////////
// SECVirtualDockbar

// Since our layout logic is nicely encapsulated outside a traditional
// CDockBar, we do not need a heavyweight window to administrate our
// advanced docking windows. Instead, the frame docking feature
// will create 1 "virtual dockbar" window that in turn will propagate
// WM_SIZE_PARENT events to the docking feature, thus providing us
// a hook to customize the size of the client area.

#define WM_POST_SIZEPARENT	WM_USER + 0x11df

class SECVirtualDockbar : public CWnd
{
// Construction
public:
	TOOLKIT_API SECVirtualDockbar();
	TOOLKIT_API virtual ~SECVirtualDockbar();

	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd,SECFrameDockingFeatureBase* pDockingFeature,UINT nID=0);

	// Invoke to reset the default window id. Note that the default id will
	// be incremented after each successful invocation to Create flagged
	// for a default id, thus creating unique windows.
	TOOLKIT_API static void SetDefaultWindowID(UINT nID);
	TOOLKIT_API static UINT GetDefaultWindowID();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECVirtualDockbar)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyWnd)
	TOOLKIT_API afx_msg LRESULT OnSizeParent(WPARAM wParam,LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnPostSizeParent(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
	// Implementation
	SECFrameDockingFeatureBase* m_pDockingFeature;

	TOOLKIT_API static UINT m_nDefaultID;
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

#endif	// WIN32

#endif  //__SEC_FRAME_DOCKING_FEATURE_H__
