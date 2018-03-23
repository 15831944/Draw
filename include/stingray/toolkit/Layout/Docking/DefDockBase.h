///////////////////////////////////////////////////////////////////////////////
// DefDockSrc.h
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
// Description:  Declaration of default dock node base classes
//

#ifndef __SECDEF_DOCKNODE_BASE__H__
#define __SECDEF_DOCKNODE_BASE__H__

#include "toolkit\Layout\BorderGraphic.h"
#include "toolkit\Layout\UndoNode.h"
#include "toolkit\Layout\Docking\DockIFace.h"
#include "toolkit\Layout\Docking\DockHT.h"
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

// Types

// Forward Declarations
class SECDynGridLineTarget;

/////////////////////////////////////////////////////////////////////////////
// SECDefDockNodeInitiatorBase

//
// ISECDockInitiator
//		|
//		SECDefDockNodeInitiatorBase
//

// Mixin base class the provides a node with a default 
// docking initiator implementation.

class SECDefDockNodeInitiatorBase : public ISECDockInitiator 
{
public:
	TOOLKIT_API SECDefDockNodeInitiatorBase();
	TOOLKIT_API virtual ~SECDefDockNodeInitiatorBase();

	// Get/Set the "this" pointer to the layout node associated
	// with this object in a derived class.
	inline void SetThisNode(SECLayoutNode* pThisNode) { m_pThisNode=pThisNode; }
	inline SECLayoutNode* GetThisNode() { return m_pThisNode; }

	// Implementation of ISECDockInitiator. 
	// See ISECDockableNode prototype for a description of these methods.
	TOOLKIT_API virtual SECLayoutNode* InitForDrag(SECLNDockingMgr* pDockMgr,BOOL bTrueDragStart,
							SECDockInProgressInfo& DockingInfo);	
	TOOLKIT_API virtual ISECDockableNode* GetDockableNode(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr);
	TOOLKIT_API virtual void PostDockProcessing(ISECDockTarget* pHitTarget,
							const CPoint& ptScreen,SECLNDockingMgr* pDockMgr,
							SECLNMemMgr* pDragMemMgr);
	TOOLKIT_API virtual void RefreshDrawingPostDock(ISECDockableNode* pNodeDocked,
							SECLNDockingMgr* pDockMgr);
	TOOLKIT_API virtual void RestoreStateAbortedDrag();
	TOOLKIT_API virtual void CleanupStateAfterDrag();
	virtual BOOL DenyContainerAsTarget() { return FALSE; }
	virtual BOOL FloatNode(SECLNDockingMgr* /* pDockMgr */,
							LPCRECT lpRectScreen=NULL) { lpRectScreen; return FALSE; } // default no floatable
	TOOLKIT_API virtual BOOL DockNode(SECLNDockingMgr* pDockMgr,SECDockInsertionConstraints* pCnstr=NULL);
	virtual BOOL ToggleFloat(SECLNDockingMgr* /* pDockMgr */) { return FALSE; }	// ditto

protected:
	// Implementation Member Funcsions
	TOOLKIT_API virtual ISECDockTarget* LocateBorderTarget(SECLNDockingMgr* pDockMgr,
							SECDockingNodeConstraints* pDockCnstr,
							const SECDockInsertionConstraints& InsertConstraints);
	TOOLKIT_API virtual ISECDockInitiator* LocateFloatInitiator();

	// Implementation Member Variables
	SECLayoutNode*		m_pThisNode,*m_pRootBeforeDrag;
	POSITION			m_posOrigInsertAfter;
	ISECLNContainer*	m_pCntrBeforeDrag;
	SECLNMemMgr*		m_pDragGarbageCollector;
	ISECDragEventGarbageCollector* m_pDragCollectorNode;
	ISECUndoableNode*	m_pUndoableParentNode;
};

/////////////////////////////////////////////////////////////////////////////
// SECDefDockNodeBase

//
// ISECDockableNode		ISECHideableNode
//		|				|
//		|			SECDefHideableNode
//		|			|
//		SECDefDockNodeBase
//

// Mixin base class the provides a node with a default 
// docking node implementation.

//@doc SECDefDockNodeBase 
//@class Internal Class. Refer only to the exported static functions below.
class SECDefDockNodeBase : public ISECDockableNode,
						   public SECDefHideableNode
{
public:
	TOOLKIT_API SECDefDockNodeBase();
	TOOLKIT_API virtual ~SECDefDockNodeBase();

	// Get/Set the "this" pointer to the layout node associated
	// with this object in a derived class.
	inline void SetThisNode(SECLayoutNode* pThisNode) { m_pThisNode=pThisNode; }
	inline SECLayoutNode* GetThisNode() { return m_pThisNode; }

	//@cmember
	/* Enable the "thin border" drag prediction, similar to the VC++ IDE behavior */
	TOOLKIT_API static void EnableThinDragBorder(BOOL bEnable=TRUE);

	//@cmember
	/* Get the current "thin border" drag prediction setting */
	TOOLKIT_API static BOOL GetThinDragBorderMode();

	// Implementation of ISECDockableNode. 
	// See ISECDockableNode prototype for a description of these methods.
	TOOLKIT_API virtual BOOL PredictInsertRectSecondary(const CPoint& ptScreenTest,
						CRect& rectScreenInsert,
						SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual void DrawInsertPrediction(HDC hScreenDC,const CRect& rectScreenInsert,
								ISECDockTarget* pHitTarget);
	TOOLKIT_API virtual void ClearInsertPrediction(HDC hScreenDC);
	TOOLKIT_API virtual BOOL DockNodeSecondary(const CPoint& ptScreenDock,
						SECLNDockingMgr* pDockMgr,
						const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual void RegisterAndResetMemMgr(SECLNDockingMgr* pDockMgr,
								const SECLNMemMgr* pOldMemMgrDuringDrag);									
	TOOLKIT_API virtual ISECDockInitiator* LocateDockInitiatorParent();

protected:	
	// SECDefHideableNode override
	TOOLKIT_API virtual BOOL OnShowNode(BOOL bShow);	

protected:

	// Implementation Member Functions
	TOOLKIT_API virtual CBrush* CalcDrawDragRectParms(BOOL bFloating,CSize& szTracker,
								CRect& rcScreenTracker,CBrush** ppBrushLast);
	TOOLKIT_API virtual CBrush* GetTrackerBrush(BOOL bThinBrush);

	CRect				m_rcLastTracker;
	CSize				m_szLastTracker;
	BOOL				m_bLastTrackThinBrush;
	SECLayoutNode*		m_pThisNode;
	ISECUndoableNode*	m_pUndoableParentNode;	
	TOOLKIT_API static CSize		m_szTrackerOverTarget;
	TOOLKIT_API static CSize		m_szTrackerFloating;
	TOOLKIT_API static BOOL			m_bThinDragBorder;
};

/////////////////////////////////////////////////////////////////////////////
// SECDefDockTargetBase

// Common default implementation of some core dock-target functionality.
// This class can not be instantiated directly, but rather serves
// as a base class for concrete implementations.

class SECDefDockTargetBase : public ISECDockTarget,
							 public ISECHookDockTargetHitTester 
{
public:							 
	// Implementation of ISECDockTarget
	TOOLKIT_API virtual BOOL PredictInsertRectPrimary(const CPoint& ptScreenTest,
									CRect& rectScreenInsert,
									SECLNDockingMgr* pDockMgr,
									const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual BOOL DockNode(ISECDockableNode* pNodeToDock,
									const CPoint& ptScreenDock,
									SECLNDockingMgr* pDockMgr,
									const SECDockInProgressInfo& DockingInfo);		

	// Implementation of ISECHookDockTargetHitTester
	TOOLKIT_API virtual DWORD DenyChildTargetHitTest(const CPoint& ptScreenTest,
									SECLayoutNode* pChildHit);							 

protected:
	virtual SECLayoutNode* CreateDummyPredictInsertRectNode() { return new SECLayoutNode; }
	TOOLKIT_API virtual BOOL InsertDockingNode(SECLayoutNode* pNodeInsert,
									const CPoint& ptNodeInsert,
									const CPoint& ptScreenInsert,
									BOOL bTrueDock,
									SECLNDockingMgr* pDockMgr,
									const SECDockInProgressInfo& DockingInfo);
	TOOLKIT_API virtual BOOL RestoreStateFromBeforePrediction(SECLayoutNode* pNode);
};							 

/////////////////////////////////////////////////////////////////////////////
// SECReparentableLayoutNodeDC_T

template <class NodeDCBase>
class SECReparentableLayoutNodeDC_T : public NodeDCBase,
									  public SECDefReparentableNode {
public:
	// Override of SECDefReparentableNode
	virtual void SetNewNodeOwnerHWND(HWND hWndNew)	{ SetNodeOwnerHWND(hWndNew); }
};

//@doc SECReparentableNodeDC
//@type SECReparentableNodeDC | Class type that supports dockable DC based layout nodes
//@xref <c SECLayoutNodeDCBase>
typedef SECReparentableLayoutNodeDC_T<SECLayoutNodeDC> SECReparentableNodeDC;

/////////////////////////////////////////////////////////////////////////////
// SECReparentableGripperEx

class SECReparentableGripperEx : public SECReparentableLayoutNodeDC_T<SECLayoutNodeGripperEx>,
								 public ISECDockEventReceiver
{
public:
	// Implementation of ISECDockEventReceiver
	TOOLKIT_API virtual BOOL OnNotifyDockingEventComplete(SECLayoutNode* pNodeDocked,
							SECLayoutNode* pParentBeforeDock,
							SECLayoutNode* pParentAfterDock,
							SECLayoutNode* pTargetLN,
							SECLNMemMgr* pGarbageCollector);
};

/////////////////////////////////////////////////////////////////////////////
// SECDefDragEventGarbageCollector

// Utility garbage collector used during the drag/drop operation.

class SECDefDragEventGarbageCollector : public ISECDragEventGarbageCollector 
{
public:
	inline SECDefDragEventGarbageCollector() { m_pGarbageCollector=NULL; }
	virtual ~SECDefDragEventGarbageCollector() {}
	
	virtual void SetDragGarbageCollector(SECLNMemMgr* pGarbageCollector) 
						{ m_pGarbageCollector=pGarbageCollector; }
	virtual SECLNMemMgr* GetDragGarbageCollector() { return m_pGarbageCollector; }
protected:
	SECLNMemMgr* m_pGarbageCollector;
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


#endif //__SECDEF_DOCKNODE_BASE__H__
