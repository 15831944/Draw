///////////////////////////////////////////////////////////////////////////////
// DragDropDockFeat.h
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
// Description:  Declaration of SECDragDropDockingFeature 
//

#ifndef __SEC_DRAG_DROP_DOCKING_FEATURE_H__
#define __SEC_DRAG_DROP_DOCKING_FEATURE_H__

#ifdef WIN32

// Header Includes
#include "toolkit\DragDrop\DragBase.h"
#include "toolkit\Layout\Docking\DockIFace.h"
#include "toolkit\Layout\Docking\DockMgr.h"
#include "toolkit\Layout\Docking\DockInfo.h"
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
class SECLNDockingMgr;
class ISECDockInitiator;
class ISECDockableNode;
class ISECDockTarget;
class SECDockInProgressInfo;

/////////////////////////////////////////////////////////////////////////////
// SECDragDropDockingFeature

//
// ISECDragDropFeature
//		|
//		SECDragDropDockingFeature
//

//
// SECDragDropDockingFeature class
// This is an implementation of ISECDragDropFeature specific to
// OT Advanced docking windows, and to be plugged into any
// SECDragDropTaskBase derived object (via the "bridge" pattern).

//@doc SECDragDropDockingFeature 
//@class Internal Class. Refer only to the exported static functions below.
class SECDragDropDockingFeature : public ISECDragDropFeature
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECDragDropDockingFeature();
	TOOLKIT_API virtual ~SECDragDropDockingFeature();

	// Attributes
	//	...Publicly accessible member variables...

	// Accessors
	//	...Get and Set functions...

	// Set the docking manager associated with this feature. Use
	// the static members for the simplistic singleton model (common
	// case), or use the internal members if you want to use multiple
	// docking managers (less common).
	TOOLKIT_API static void SetDefDockingMgr(SECLNDockingMgr* pMgr);
	TOOLKIT_API static SECLNDockingMgr* GetDefDockingMgr();
	TOOLKIT_API void SetDockingMgr(SECLNDockingMgr* pMgr);
	TOOLKIT_API SECLNDockingMgr* GetDockingMgr();

	// Drag initiator - there can only be 1 active initiator
	// at any point in time (can only drag 1 root node at a time).
	TOOLKIT_API static ISECDockInitiator* m_pDockInitiator; // data member
	TOOLKIT_API static ISECDockInitiator* GetActiveDockInitiator();
	TOOLKIT_API static void SetActiveDockInitiator(ISECDockInitiator* pInitiator);

	// Realtime Drag Mode - allows "smooth" docking without prediction rects.

	//@cmember
	/* Enables realtime "Office-Style" docking support for the application. */
	TOOLKIT_API static void SetRealtimeDrag(BOOL bEnable);

	//@cmember
	/* Queries the current enablement of realtime "Office-Style" docking support. */
	TOOLKIT_API static BOOL GetRealtimeDrag();

	TOOLKIT_API static SECLayoutNode* GetOrigInitiator();

	// Operations

	// Overrides

	// Implementation of ISECDragDropFeature
	TOOLKIT_API virtual BOOL TestDragStartPoint(UINT nKeyFlags,const CPoint& ptScreenDragTest) ;
	TOOLKIT_API virtual BOOL InitiateDrag(UINT nKeyFlags,const CPoint& ptScreenDragStart);
	TOOLKIT_API virtual BOOL TrackDrag(UINT nKeyFlags,const CPoint& ptScreenMove);
	TOOLKIT_API virtual BOOL EndDrag(UINT nKeyFlags,const CPoint& ptScreenDragEnd,BOOL bDoDrop);
	TOOLKIT_API virtual BOOL DragDropToggleEvent(UINT nKeyFlags,const CPoint& ptScreenEvent);

	// Overridables
protected:
	TOOLKIT_API virtual BOOL OnInitiateDrag(UINT nKeyFlags,const CPoint& ptScreenDragStart,BOOL bTrueStartOfDrag);
	TOOLKIT_API virtual BOOL OnTrackDrag(UINT nKeyFlags,const CPoint& ptScreenMove,BOOL bTrueTrackDrag);
	TOOLKIT_API virtual BOOL OnEndDrag(UINT nKeyFlags,const CPoint& ptScreenDragEnd,BOOL bDoDrop,BOOL bTrueEndOfDrag);

protected:
	//
	// Implementation Member Variables
	//
	SECLNDockingMgr*		m_pDockingMgr;				// per-instance docking mgr
	TOOLKIT_API static SECLNDockingMgr* m_pDefDockingMgr;	// app-wide default docking mgr
	HDC						m_hScreenDC;
	SECLNMemMgr*			m_pTempDragMemMgr;
	ISECDockableNode*		m_pOldDockableNode;
	SECLayoutNode*			m_pParentBeforeDrag;
	SECDockInProgressInfo*	m_pDockingInfo;
	TOOLKIT_API static BOOL				m_bRealtimeDrag;
	BOOL					m_bTrackInProgress;
	TOOLKIT_API static SECLayoutNode*	m_pOrigInitiator;
	CPoint					m_ptScreenLastTrack;
	ISECDockInitiator*		m_pOldInitiator;

	// RealizeNode lockdown optimizations
	SECLayoutNode* m_pOldLockdownNode,*m_pOldLockdownRoot;
	ISECLNContainer* m_pOldLockdownCntr;
	CRect m_rectOldLockdownNode;

	//
	// Implementation Member Functions
	//
	TOOLKIT_API virtual HDC DoInitDC();
	TOOLKIT_API virtual void DoReleaseDC(HDC hDC);
	TOOLKIT_API virtual ISECDockInitiator* GetDockingInitiator(SECLNDockingMgr* pDockingMgr,
												const CPoint& ptScreenDragStart,
												BOOL bTrueStartOfDrag);
	TOOLKIT_API virtual BOOL DoDrop(const CPoint& ptScreenDrop,ISECDockableNode* pDockNode,
						ISECDockTarget* pTargetHit,SECLNDockingMgr* pDockingMgr);
	TOOLKIT_API virtual ISECDockTarget* GetTargetHit(const CPoint& ptScreenHit,
						SECLNDockingMgr* pMgr,
						ISECLNContainer* pDenyTargetCntr=NULL);
	TOOLKIT_API virtual BOOL OnAdjustHitTargetForKeys(const CPoint& ptScreenTest,
						UINT nKeyFlags,ISECDockTarget** pTargetHit);
	TOOLKIT_API virtual ISECDockableNode* QueryForDockableNode(const CPoint& ptHit,
						ISECDockTarget* pTarget,SECLNDockingMgr* pMgr);
	TOOLKIT_API virtual void SetLockdownMode(SECLayoutNode* pNode,BOOL bLockDown,
						SECLNDockingMgr* pMgr,BOOL bEndOfDrag=FALSE,
						BOOL bForceSet=FALSE);

#ifdef SECDOCK_EXTENDED_DIAGNOSTICS
public:
	// Internal diagnostic tools
	TOOLKIT_API void DumpDockTrackInfo(const CPoint& ptScreenMove,const CRect& rcScreenPredict,
									ISECDockTarget* pDockTargetForDrag);
#endif
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

#endif  //__SEC_DRAG_DROP_DOCKING_FEATURE_H__
