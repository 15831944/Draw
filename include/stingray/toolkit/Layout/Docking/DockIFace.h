///////////////////////////////////////////////////////////////////////////////
// DockIFace.h
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
// Authors:      Mark Isham
// Description:  Declaration of SEC Advanced Docking Interfaces
//

#ifndef __SEC_ADV_DOCKING_IFACES_H__
#define __SEC_ADV_DOCKING_IFACES_H__

#ifdef WIN32

// Header Includes
#include "DockMgr.h"
#include "DockInfo.h"
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

// Forward Declarations
class ISECDockTarget;
class ISECDockableNode;

/////////////////////////////////////////////////////////////////////////////
// ISECDockInitiator

// Mixin to a SECLayoutNode derived class. A layout node that supports 
// ISECDockInitiator is a node that can initiate a drag drop operation
// on a mouse click.

class ISECDockInitiator 
{
public:
	virtual ~ISECDockInitiator() {}

	// Called before a drag operation is about to occur. Perform any
	// preliminary init. Returns the parent of this initiator to be cached.
	// The true drag start parm is used to signal the first drag initiation,
	// as opposed to subsequental initialization (in a realtime drag operation).
	virtual SECLayoutNode* InitForDrag(SECLNDockingMgr* pDockMgr,BOOL bTrueDragStart,
							SECDockInProgressInfo& DockingInfo)=0;

	// Return the dockable node associated with this docking initiator.
	// The dockable node may be this node, or a child of this node.
	virtual ISECDockableNode* GetDockableNode(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr)=0;

	// Perform any post-docking processing here
	virtual void PostDockProcessing(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr)=0;

	// This is the hook to refresh the painting of the old and new windows
	// that participated in a drag/drop operation.
	virtual void RefreshDrawingPostDock(ISECDockableNode* pNodeDocked,
							SECLNDockingMgr* pDockMgr)=0;

	// The docking operation was aborted. Restore the state of this
	// initiator as set before InitForDraw was called.
	virtual void RestoreStateAbortedDrag()=0;

	// This function is always called after the completion of a drag 
	// operation (if dock succeeded or not).
	virtual void CleanupStateAfterDrag()=0;

	// Hook for a dock initiator to forbid docking to a target
	// defined within the same container as the initiator.
	virtual BOOL DenyContainerAsTarget()=0;

	// Locate the floating intiator parent, if found.
	virtual ISECDockInitiator* LocateFloatInitiator()=0;

	// Float this initiator to the specified screen coordinates. Use MRU if NULL.
	virtual BOOL FloatNode(SECLNDockingMgr* pDockMgr,LPCRECT lpRectScreen=NULL)=0;

	// Dock this initiator given the specified constraints. Use MRU if NULL.
	virtual BOOL DockNode(SECLNDockingMgr* pDockMgr,SECDockInsertionConstraints* pCnstr=NULL)=0;

	// Toggle the current float state on/off. 
	virtual BOOL ToggleFloat(SECLNDockingMgr* pDockMgr)=0;
};

/////////////////////////////////////////////////////////////////////////////
// ISECDockableNode

// Mixin to a SECLayoutNode derived class. A layout node that supports 
// ISECDockableNode is a node that can actually be docked to a docking
// target. 
//
// This is an important distinction from ISECDockInitiator. A docking
// initiator can start a drag, but can not be docked. A dockable node
// can not initiate a drag, but can be docked. A node that supports
// both interfaces can initiate and be docked. This distinction
// allows separation of special node types, like floating nodes,
// who can start the drag, but actually reparent a child node
// upon successful dock.

class ISECDockableNode 
{
public:
	virtual ~ISECDockableNode() {}

	// Predict the insertion rect that would occur if a docking source
	// was dropped at the point passed in. This function is called only
	// if there is now dock target, or dock target failed prediction.
	virtual BOOL PredictInsertRectSecondary(const CPoint& ptScreenTest,
						CRect& rectScreenInsert,
						SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo)=0;

	// Draw a graphic representing the predicted insertion position
	// of this docking source upon the docking target passed in.
	virtual void DrawInsertPrediction(HDC hScreenDC,const CRect& rectScreenInsert,
						ISECDockTarget* pHitTarget)=0;

	// No more insertion prediction tracking. Clean up any afterimages.
	virtual void ClearInsertPrediction(HDC hScreenDC)=0;

	// Secondary docking operation, called only if the dock target failed to dock.
	// The rect of the docking should be exactly the same as that returned by
	// PredictInsertRectSecondary.
	virtual BOOL DockNodeSecondary(const CPoint& ptScreenDock,
						SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo)=0;

	// Register with the docking mgr and reset the mem mgr link.
	virtual void RegisterAndResetMemMgr(SECLNDockingMgr* pDockMgr,
										const SECLNMemMgr* pOldMemMgrDuringDrag)=0;	

	// This or a parent node must be the docking initiator corresponding to
	// this dockable node. Call this function to locate the initiator.
	virtual ISECDockInitiator* LocateDockInitiatorParent()=0;
};


/////////////////////////////////////////////////////////////////////////////
// ISECDockTarget

// Mixin interface for docking target nodes 
// Docking target nodes are nodes that can allow a drop operation in
// a docking drag/drop event.

class ISECDockTarget 
{
public:
	virtual ~ISECDockTarget() {}
	
	// Predict the insertion rect that would occur if a docking source
	// was dropped on this target at the point passed in. If no docking
	// can occur, return FALSE.
	// Note: coordinates are in screen coordinates!
	virtual BOOL PredictInsertRectPrimary(const CPoint& ptScreenTest,
						CRect& rectScreenInsert,SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo)=0;

	// Dock the docking node at the specified point. Note that the final
	// docked rect should match that returned by PredictInsertRect exactly).
	// Return FALSE to deny docking.
	virtual BOOL DockNode(ISECDockableNode* pNodeToDock,const CPoint& ptScreenDock,
						SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo)=0;
};

/////////////////////////////////////////////////////////////////////////////
// ISECDockEventReceiver

// Mixin interface for a node who wishes to react to docking-mgr wide
// events.

class ISECDockEventReceiver 
{
public:
	virtual ~ISECDockEventReceiver() {}

	// This event is fired when a docking operation has just
	// completed. This notification is sent to all nodes (that
	// support ISECDockEventReceiver) in the layout tree from 
	// which the dock event initiated, and to the tree in which 
	// the dock event terminated. If a particular node
	// wishes to deny this message to its children, it can return
	// FALSE. Otherwise return TRUE to continue processing to the
	// children.
	virtual BOOL OnNotifyDockingEventComplete(SECLayoutNode* pNodeDocked,
							SECLayoutNode* pParentBeforeDock,
							SECLayoutNode* pParentAfterDock,
							SECLayoutNode* pTargetLN,
							SECLNMemMgr* pGarbageCollector)=0;
};

/////////////////////////////////////////////////////////////////////////////
// ISECDragEventGarbageCollector

// Utility garbage collector used during the drag/drop operation.

class ISECDragEventGarbageCollector 
{
public:
	virtual ~ISECDragEventGarbageCollector() {}
	virtual void SetDragGarbageCollector(SECLNMemMgr* pGarbageCollector)=0;
	virtual SECLNMemMgr* GetDragGarbageCollector()=0;	
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

#endif	//__SEC_ADV_DOCKING_IFACES_H__
