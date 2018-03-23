///////////////////////////////////////////////////////////////////////////////
// DockHT.h
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
// Description:  Declaration of SECLNDockHitTester
//
// SECLNDockHitTester
// This helper class is used primarily for extended HitTest and other
// docking node utility logic.
// 

#ifndef __SEC_DOCK_HITTEST_H__
#define __SEC_DOCK_HITTEST_H__

// Header Includes
#include <math.h>
#include "NodeHT.h"
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

// Return codes for QueryDenyChildHitTesting
#define SEC_DOCKHT_PROCESS_CHILDREN		0x0000	// recurse into children looking for hit
#define SEC_DOCKHT_HIT_NONE				0x0001	// return no hit in this search
#define SEC_DOCKHT_HIT_THIS				0x0002	// return this node as a hit (ignore children)

/////////////////////////////////////////////////////////////////////////////
// ISECHookDockSourceHitTester, ISECHookDockTargetHitTester

// These interfaces provided as a mechanism to override
// the default hit-testing logic on a per-source or per-target basis.

class ISECHookDockSourceHitTester 
{
public:
	virtual DWORD DenyChildSourceHitTest(const CPoint& ptScreenTest,
										SECLayoutNode* pChildHit)=0;
};

class ISECHookDockTargetHitTester 
{
public:
	virtual DWORD DenyChildTargetHitTest(const CPoint& ptScreenTest,
										SECLayoutNode* pChildHit)=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDockHitTester

template <class IFACETEST>
class SECLNDockHitTester 
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	//@access Public Interface

	// Initialization/Destruction
	inline SECLNDockHitTester() { m_pIgnoreCntr=NULL; }
	virtual ~SECLNDockHitTester() {}

	// Attributes
	//	...Publicly accessible member variables...

	// Accessors
	//	...Get and Set functions...
	inline void SetIgnoreContainer(ISECLNContainer* pIgnoreCntr) { m_pIgnoreCntr=pIgnoreCntr; }
	inline ISECLNContainer* GetIgnoreContainer() { return m_pIgnoreCntr; }

	// Operations
	virtual IFACETEST* HitTestDockingIFace(SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest,
										BOOL bParentHitExclusiveFromChild=FALSE);
	virtual void HitTestDockingIFaceList(const SECLayoutNodePtrList& listRootNodes,
										SECLayoutNodePtrList& listHits,
										SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest,
										BOOL bParentHitExclusiveFromChild);									
	virtual IFACETEST* HitTestDockingIFace(SECLayoutNode* pRootNode,
										SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest,
										BOOL bParentHitExclusiveFromChild=FALSE);

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	virtual DWORD QueryDenyChildHitTesting(ISECLNContainer*,const CPoint&,SECLayoutNode*) 
								{ return SEC_DOCKHT_PROCESS_CHILDREN;}

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Functions
	virtual UINT HitTestRegRootNodes(SECLNDockingMgr* pDockMgr,
									const CPoint& ptScreenTest,
									SECLayoutNodePtrList& listHits);
	virtual BOOL HitTestRectSingleNode(SECLayoutNode* pNode,
									const CPoint& ptScreenTest,
									ISECLNContainer* pContainer);
	virtual void FilterNodeListThroughContainerZOrder(
									SECLNDockingMgr* pDockMgr,
									const CPoint& ptScreenTest,
									SECLayoutNodePtrList& listHits);
	virtual IFACETEST* HitTestNodeInterfaceOneTree(SECLayoutNode* pRoot,
									const CPoint& ptScreenTest,
									ISECLNContainer* pContainer,
									BOOL bParentHitExclusiveFromChild);
	virtual IFACETEST* HitTestNodeInterfaceOneTreeHelper(
									SECLayoutNode* pParent,
									const CPoint& ptScreenTest,
									ISECLNContainer* pContainer,
									BOOL bParentHitExclusiveFromChild);
	virtual SECLayoutNode* HitTestRectNodeChildren(
									SECLayoutNode* pParent,
									const CPoint& ptScreenTest,
									ISECLNContainer* pContainer);

	// Implementation Member Variables
	ISECLNContainer* m_pIgnoreCntr;

	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:

};

/////////////////////////////////////////////////////////////////////////////
// SECDockInitiatorHitTester

// Specialization of SECLNDockHitTester that queries for nodes that
// support the ISECDockInitiator interface.

class SECDockInitiatorHitTester : public SECLNDockHitTester<ISECDockInitiator> 
{

public:
	// Override the base methods to insure the child hit-test is exclusive
	// from that of the parent. I.e. if a point hits both in the parent and
	// the child, only the child can signal a hit, not the parent. This is
	// esp. useful for grippers, where you only want a hit if the mouse
	// is within the gripper, and not within the wrapped node. For dock
	// targets, though, we want to hit inside the child as well, thus
	// the use of the FALSE default parm above.
	TOOLKIT_API virtual ISECDockInitiator* HitTestDockingIFace(SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest,
										BOOL bParentHitExclusiveFromChild=FALSE);
	TOOLKIT_API virtual ISECDockInitiator* HitTestDockingIFace(SECLayoutNode* pRootNode,
										SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest,
										BOOL bParentHitExclusiveFromChild=FALSE);

protected:

	TOOLKIT_API virtual DWORD QueryDenyChildHitTesting(ISECLNContainer* pContainer,
										const CPoint& ptScreen,
										SECLayoutNode* pNode);
};

/////////////////////////////////////////////////////////////////////////////
// SECLNTargetDockHitTester

class SECLNTargetDockHitTester : public SECLNDockHitTester<ISECDockTarget> 
{
protected:
	TOOLKIT_API virtual DWORD QueryDenyChildHitTesting(ISECLNContainer* pContainer,
										const CPoint& ptScreen,
										SECLayoutNode* pNode);
};

/////////////////////////////////////////////////////////////////////////////
// SECLNOffNodeDockIFaceHitTest_T

// Specialization of SECLNOffNodeIFaceHitTest_T with docking specific dependencies.

template <class IFACETEST>
class SECLNOffNodeDockIFaceHitTest_T : public SECLNOffNodeIFaceHitTest_T<IFACETEST> 
{
public:
	virtual IFACETEST* GetOffDockNodeHit(SECLNDockingMgr* pDockMgr,
										const CPoint& ptScreenTest);
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


#endif //__SEC_DOCK_HITTEST_H__
