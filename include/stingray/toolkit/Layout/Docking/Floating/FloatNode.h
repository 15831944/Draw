///////////////////////////////////////////////////////////////////////////////
// FloatNode.h
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
// Description:  Declaration of SECDockFloatingNode
//


#ifndef __SECDOCK_FLOATING_NODE_H__
#define __SECDOCK_FLOATING_NODE_H__

// Header Includes
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

// Macros

#if ( _MFC_VER < 0x0421 )
// disable warning 4097 for VC4.x:
// SECLNBorder intentially used as a synonym of SECLNBorder_T<SECLayoutNode>
// SECFloatableGripperNode used as a synonym for SECFloatableDockingNode_T<class SECReparentableGripperEx>
#pragma warning(disable:4097)
#endif 

// Types

// Forward Declarations

// Core query logic used as a mixin
class SECQueryChildTargetInfo 
{
protected:
	TOOLKIT_API virtual SECLayoutNode* GetChildTargetHeadNode(SECLayoutNode* pChildTarget);
	TOOLKIT_API virtual int GetChildTargetChildCount(SECLayoutNode* pChildTarget);
	TOOLKIT_API virtual void GetGrandChildrenList(SECLayoutNode* pChildTarget,
								SECLayoutNodePtrList& listGrandChildren);
};

/////////////////////////////////////////////////////////////////////////////
// SECDockFloatingNode

//
// ISECDockInitiator			SECLayoutNode		ISECDockableNode
//	|								|				|
//	SECDefDockNodeInitiatorBase	 SECLNBorder SECDefDockNodeBase
//						  |			|		 |       ISECHookDockSourceHitTester
//SECQueryChildTargetInfo |         |     ----        |
//						| |         |     ||-----------
//						 SECDockFloatingNode			
//

//
// Floating dockable window
//

class ISECFloatingNode 
{
public:
	virtual ~ISECFloatingNode() {}
	TOOLKIT_API virtual BOOL IsFloatingNode()=0;
	TOOLKIT_API virtual BOOL ShowFloatingNode(BOOL bShow)=0;
};

// Used as an initiator (docking a pre-existing floating window)
// or as a dockable node (floating an existing docked window).

class SECDockFloatingNode :	public SECDefDockNodeInitiatorBase,
							public SECDefDockNodeBase,
							public SECLNBorder,
							public SECQueryChildTargetInfo,
							public ISECFloatingNode,
							public ISECHookDockSourceHitTester
{
public:
	TOOLKIT_API SECDockFloatingNode();
	TOOLKIT_API virtual ~SECDockFloatingNode();	

	TOOLKIT_API virtual BOOL CreateFloatingNode(SECLayoutNode* pNodeChildToFloat,
							 SECLNDockingMgr* pDockMgr,
							 ISECLNContainer* pCntrChildToFloat,
							 LPCTSTR lpszTitle);

	// ISECDockInitiator Overrides
	TOOLKIT_API virtual SECLayoutNode* InitForDrag(SECLNDockingMgr* pDockMgr,BOOL bTrueDragStart,
							SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual ISECDockableNode* GetDockableNode(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr);
	TOOLKIT_API virtual void PostDockProcessing(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr);
	TOOLKIT_API virtual BOOL DenyContainerAsTarget() { return TRUE; }
	TOOLKIT_API virtual BOOL DockNode(SECLNDockingMgr* pDockMgr,SECDockInsertionConstraints* pCnstr=NULL);
	TOOLKIT_API virtual BOOL ToggleFloat(SECLNDockingMgr* pDockMgr);

	// ISECDockableNode Overrides
	TOOLKIT_API virtual BOOL PredictInsertRectSecondary(const CPoint& ptScreenTest,
							CRect& rectScreenInsert,
							SECLNDockingMgr* pDockMgr,
							const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual BOOL DockNodeSecondary(const CPoint& ptScreenDock,
							SECLNDockingMgr* pDockMgr,
							const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual void RegisterAndResetMemMgr(SECLNDockingMgr* pDockMgr,
							const SECLNMemMgr* pOldMemMgrDuringDrag);		

	// Implementation of ISECFloatingNode
	TOOLKIT_API virtual BOOL IsFloatingNode() { return TRUE; }
	TOOLKIT_API virtual BOOL ShowFloatingNode(BOOL bShow);	

	// ISECHookDockSourceHitTester implementation
	TOOLKIT_API virtual DWORD DenyChildSourceHitTest(const CPoint& ptScreenTest,
							SECLayoutNode* pChildHit);

protected:
	// Overridables
	TOOLKIT_API virtual SECLayoutNode* CreateChildTarget(ISECLNContainer* pContainerThis);
	
protected:
	TOOLKIT_API virtual ISECDockableNode* GetChildNodeForDocking();
	TOOLKIT_API virtual ISECLNContainer* LocateContainer(SECLNDockingMgr* pDockMgr);
	TOOLKIT_API virtual BOOL LoadBorderMargins(UINT& nLeft,UINT& nTop,
							UINT& nRight,UINT& nBottom,
							SECLNDockingMgr* pDockMgr);
	TOOLKIT_API virtual BOOL RefreshMRUFloatSize(SECLNDockingMgr* pDockMgr);

	ISECLNContainer* m_pCntrNotYetReg;	
	BOOL m_bMarginsCached,m_bSuccessfullyFloated,m_bDidCreate;
	SECLayoutNode* m_pChildTarget;	
	SECLayoutNode* m_pNodeChildTryingToFloat;
	SECLNDockingMgr* m_pDockMgrRegistered;
	SECLayoutDockFactory m_LDockFactory;
};			

// Simple extension of SECDynGridLineTarget with additional logic
// to deny child target hit-testing, if specified.

//@doc SECFloatDynGridLineTarget 
//@class Internal Class. Refer only to the exported static functions below.
class SECFloatDynGridLineTarget : public SECDynGridLineTarget 
{
public:
	//@cmember
	/* Enables floating "MultiDock" support. */
	TOOLKIT_API static void EnableMultiDock(BOOL bEnable=TRUE);

	//@cmember
	/* Queries the current "MultiDock" enablement state */
	TOOLKIT_API static BOOL GetMultiDockEnabled();

	// override of base ISECHookDockTargetHitTester implementation
	TOOLKIT_API virtual DWORD DenyChildTargetHitTest(const CPoint& ptScreenTest,
										SECLayoutNode* pChildHit);

protected:
	TOOLKIT_API static BOOL m_bMultiDockMode;
};

/////////////////////////////////////////////////////////////////////////////
// SECFloatableDockingNode_T

//
// ISECDockInitiator		     ISECDockableNode	    SECLayoutNode
//	|								|					|
//	SECDefDockNodeInitiatorBase	 SECDefDockNodeBase	 <BaseNode>
//						|			|	             |
//			         SECFloatableDockingNode_T<BaseNode>

//
// A node of this type can initiate a drag, be docked to a target,
// and will create a floating parent initiator on docking over
// a NULL target.

template <class BaseNode>
class SECFloatableDockingNode_T :  public SECDefDockNodeInitiatorBase,
								   public SECDefDockNodeBase,
								   public BaseNode
{
public:
	inline SECFloatableDockingNode_T() { m_pCachedFloatNode=NULL; }
	virtual ~SECFloatableDockingNode_T() 
	{
		// Do not delete m_pCachedFloatNode! This memory will be deallocated elsewhere.
		m_pCachedFloatNode=NULL;
	}

	// Overrides to create a floating dockable node (if applicable)
	TOOLKIT_API virtual SECLayoutNode* InitForDrag(SECLNDockingMgr* pDockMgr,BOOL bTrueDragStart,
							SECDockInProgressInfo& DockingInfo);		
	TOOLKIT_API virtual ISECDockableNode* GetDockableNode(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr);
	TOOLKIT_API virtual void CleanupStateAfterDrag();
	TOOLKIT_API virtual BOOL FloatNode(SECLNDockingMgr* pDockMgr,LPCRECT lpRectScreen=NULL);
	TOOLKIT_API virtual BOOL ToggleFloat(SECLNDockingMgr* pDockMgr) { return FloatNode(pDockMgr); }	// docked to floating
	
	// SECDefHideableNode override	
	TOOLKIT_API virtual BOOL ShowNode(BOOL bShow,BOOL bResetRefCount=FALSE,BOOL bRecurse=TRUE);	

	virtual void UpdateFrameTitle(){UpdateFrameTitle( (SECLNDockingMgr*)NULL);};
	TOOLKIT_API virtual void UpdateFrameTitle(SECLNDockingMgr* pD);

protected:
	// Overridables
	virtual SECDockFloatingNode* CreateFloatingDockableNode() { return new SECDockFloatingNode; }
	
protected:
	// Implementation
	SECDockFloatingNode* m_pCachedFloatNode;
};


/////////////////////////////////////////////////////////////////////////////
// SECFloatableGripperNode

// A gripper node that can be floated as a floating docknode.

typedef SECFloatableDockingNode_T<SECReparentableGripperEx> SECFloatableGripperNode;

/////////////////////////////////////////////////////////////////////////////
// SECFloatingTargetGripper

// Gripper logic specific to the embedded child dock-target in an
// existing floated docknode.

class SECFloatingTargetGripper : public SECFloatableGripperNode,
								 public SECQueryChildTargetInfo
{
public:
	// Overrides of ISECDockEventReceiver
	TOOLKIT_API virtual BOOL OnNotifyDockingEventComplete(SECLayoutNode* pNodeDocked,
							SECLayoutNode* pParentBeforeDock,
							SECLayoutNode* pParentAfterDock,
							SECLayoutNode* pTargetLN,
							SECLNMemMgr* pGarbageCollector);				
};

/////////////////////////////////////////////////////////////////////////////

#if ( _MFC_VER < 0x0421 )
// reenable warning 4097 for VC4.x:
#pragma warning(default:4097)
#endif 

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SECDOCK_FLOATING_NODE_H__
