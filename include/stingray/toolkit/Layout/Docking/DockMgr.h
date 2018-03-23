///////////////////////////////////////////////////////////////////////////////
// DockMgr.h
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
// Description:  Declaration of SECLNDockingMgr class
// 

#ifndef __SECLAYOUT_DOCKING_MGR_H__
#define __SECLAYOUT_DOCKING_MGR_H__

// Header Includes
#include "toolkit\Layout\Container.h"
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

// Forward declarations
class ISECLNContainer;
class SECDockingNodeConstraints;

// Derived object manager class to search for SECLayoutNode objects
// across multiple child object managers.
class SECDockMgrMemMgr : public stingray::foundation::SECObjectMemoryManager_T<SECLNMemMgr> 
{
public:
	TOOLKIT_API virtual SECLNMemMgr* GetNodeMgr(SECLayoutNode* pNode);
	TOOLKIT_API virtual UINT GetNumZeroSizedMgrs();
};

/////////////////////////////////////////////////////////////////////////////
// SECLNDockingMgr

class SECLNDockingMgr 
{
public:
	TOOLKIT_API SECLNDockingMgr();
	TOOLKIT_API virtual ~SECLNDockingMgr();

	// Node-container registration. Note these functions will automatically manage
	// the memory of the container object passed in! Use care not to cache container
	// pointers, but rather to call the Get/Locate functions below as needed.
	TOOLKIT_API BOOL RegisterRootLayoutNode(SECLayoutNode* pRootNode,ISECLNContainer* pContainer);
	TOOLKIT_API BOOL RemoveRootRegisteredLayoutNode(SECLayoutNode* pNode);

	// Get a temporary pointer to the current container associated with a particular node.
	TOOLKIT_API ISECLNContainer* GetRegisteredNodeContainer(SECLayoutNode* pRegNode);
	TOOLKIT_API ISECLNContainer* LocateNodeOwnerContainer(SECLayoutNode* pChildNode);

	// Query if a particular container is currently managed by this mgr.
	inline BOOL IsContainerManaged(ISECLNContainer* pContainer) { return m_MemMgrCntrs.IsManaged(pContainer); }
	TOOLKIT_API BOOL IsRegisteredNode(SECLayoutNode* pNodeTest);

	// Get a list of all the root level nodes registered with this docking mgr.
	TOOLKIT_API void GetRegisteredRootNodeList(SECLayoutNodePtrList& listRootNodes);

	// Request a new memory manager object to be associated with a new root
	// level node. Unless otherwise specified, this object will go out of scope
	// when this docking mgr goes out of scope.
	TOOLKIT_API virtual SECLNMemMgr* CreateNewNodeMemMgr(SECLayoutNode* pRootNodeRequestingMgr);
	TOOLKIT_API virtual BOOL DeleteNodeMemMgr(SECLayoutNode* pRootNodeReqDelete,SECLNMemMgr* pLNMemMgr);
	inline BOOL IsMemMgrCreatedByDockMgr(SECLNMemMgr* pMgr) { return m_MemMgrOfNodeMemMgrs.IsManaged(pMgr); }

	// Send a docking event notification the relevant node tree branches.
	TOOLKIT_API virtual BOOL SendDockingEventNotification(SECLayoutNode* pNodeDocked,
							SECLayoutNode* pParentBeforeDock,
							SECLayoutNode* pTargetLN,
							SECLNMemMgr* pGarbageCollector);

	// Utility function to fetch the origin offset of the node passed in.
	TOOLKIT_API virtual BOOL GetNodeOriginOffset(const CPoint& ptScreen,SECLayoutNode* pNode,CSize& szOffset);

	// Docking Constraint Lookup
	TOOLKIT_API virtual BOOL SetDockingNodeConstraint(SECLayoutNode* pNode,SECDockingNodeConstraints* pConstraint);
	TOOLKIT_API virtual BOOL ClearDockingNodeConstraint(SECLayoutNode* pNode);
	TOOLKIT_API virtual SECDockingNodeConstraints* GetDockingNodeConstraint(SECLayoutNode* pNode,
											BOOL bCreateNew=FALSE);

	// Locate container at top of z-order
	TOOLKIT_API virtual ISECLNContainer* GetContainerTopZOrder(const CPoint& ptScreenTest);

	// Reset parent container link
	TOOLKIT_API virtual BOOL ResetDockedNodeParenting(SECLayoutNode* pNode);

protected:

	//
	// Member Functions
	//
	TOOLKIT_API virtual BOOL SECLNDockingMgr::SendDockingEventNotificationRecurse(
							SECLayoutNode* pRecurseNode,
							SECLayoutNode* pNodeDocked,
							SECLayoutNode* pParentBeforeDock,
							SECLayoutNode* pParentAfterDock,
							SECLayoutNode* pTargetLN,
							SECLNMemMgr* pGarbageCollector);

	TOOLKIT_API virtual void GetRegWndCntrs(CTypedPtrList<CPtrList,SECLNHwndContainer*>& listWndCntrs);
	TOOLKIT_API virtual SECLNHwndContainer* FindHwndInCntr(HWND hWndFind,
							const CTypedPtrList<CPtrList,SECLNHwndContainer*>& listWndCntrs);

	//
	// Member Variables
	//

	// Container Map
	CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,ISECLNContainer*> m_mapRegNodeToContainer;
	stingray::foundation::SECObjectMemoryManager_T<ISECLNContainer> m_MemMgrCntrs;

	// Node docking constraint map
	CTypedPtrMap<CMapPtrToPtr,SECLayoutNode*,SECDockingNodeConstraints*> m_mapNodeToDockConstraint;
	stingray::foundation::SECObjectMemoryManager_T<SECDockingNodeConstraints> m_MemMgrDockConstraints;

	// Roots can request the docking mgr for a new mem mgr. This object will
	// clean up the storage on deletion of the docking mgr.
	SECDockMgrMemMgr m_MemMgrOfNodeMemMgrs;

#ifdef SECDOCK_EXTENDED_DIAGNOSTICS
public:
	// Internal diagnostic tools
	TOOLKIT_API void DumpInfoAllAssocNodes();
	TOOLKIT_API void DumpNodeInfoChildren(SECLayoutNode* pParent,CString strPreface);
	TOOLKIT_API void DumpNodeInfo(SECLayoutNode* pNode);
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


#endif //__SECLAYOUT_DOCKING_MGR_H__
