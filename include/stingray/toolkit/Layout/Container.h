///////////////////////////////////////////////////////////////////////////////
// Container.h : Declaration of ISECLNContainer and derived classes
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
// Description:  Declaration of ISECLNContainer and derived classes
//

#ifndef __SECLAYOUT_DOCKING_CONTAINER_H__
#define __SECLAYOUT_DOCKING_CONTAINER_H__

// Header Includes
#include "toolkit\Layout\LayoutNd.h"
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
class SECLNFloatingHwndContainer;
class SECLayoutMiniFloatWnd;

/////////////////////////////////////////////////////////////////////////////
// ISECLNContainer

// Abstraction of physical coordinate mapping performed via the owner
// windows of root level layout nodes. This abstraction allows the same
// logic to be used with containers other than HWND's.
// For use by SECLNDockingMgr

class ISECLNContainer 
{
public:
	virtual ~ISECLNContainer() {}

	// Coordinate mapping within the context of this container
	TOOLKIT_API virtual BOOL ClientToScreen(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL ClientToScreen(LPRECT lpRect)=0;

	TOOLKIT_API virtual BOOL ScreenToClient(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL ScreenToClient(LPRECT lpRect)=0;

	TOOLKIT_API virtual BOOL NodeToClient(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL NodeToClient(LPRECT lpRect)=0;

	TOOLKIT_API virtual BOOL ClientToNode(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL ClientToNode(LPRECT lpRect)=0;

	TOOLKIT_API virtual BOOL NodeToScreen(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL NodeToScreen(LPRECT lpRect)=0;

	TOOLKIT_API virtual BOOL ScreenToNode(LPPOINT lpPoint)=0;
	TOOLKIT_API virtual BOOL ScreenToNode(LPRECT lpRect)=0;

	TOOLKIT_API virtual CPoint GetNonClientOffset()=0;

	// Painting
	TOOLKIT_API virtual void Invalidate(BOOL bErase)=0;
	TOOLKIT_API virtual BOOL LockDesktopWindowUpdate(BOOL bLock=TRUE)=0;
	
	// Visibility
	TOOLKIT_API virtual BOOL ShowWindow(BOOL bShow)=0;
	
	// Container positional negotiation, movement
	TOOLKIT_API virtual BOOL GetClientRect(LPRECT lpRect)=0;
	TOOLKIT_API virtual BOOL GetWindowRect(LPRECT lpRect)=0;
	TOOLKIT_API virtual BOOL QueryNonClientMargins(UINT& nLeft,UINT& nTop,
									UINT& nRight,UINT& nBottom)=0;
	TOOLKIT_API virtual BOOL DisplayContainer(const CRect& rcScreenDisplay)=0;
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify=TRUE)=0;

	// Factory creational methods for context cloning.
	TOOLKIT_API virtual ISECLNContainer* CreateCompatibleCntr()=0;
	TOOLKIT_API virtual ISECLNContainer* CreateCompatibleFloatingCntr(
										SECLayoutNode* pRootNode,
										LPCTSTR lpszTitle,
										BOOL bHideOnClose=TRUE,
										BOOL bCloseEnabled=TRUE)=0;
	// container visibility
	virtual BOOL IsContainerVisible() { return TRUE; }
};

/////////////////////////////////////////////////////////////////////////////
// SECLNHwndContainer

// Implementation of ISECLNContainer specific for HWND's

class SECLNHwndContainer : public ISECLNContainer 
{
public:
	// Construction/Destruction
	TOOLKIT_API SECLNHwndContainer(CWnd* pContainerWnd);
	TOOLKIT_API SECLNHwndContainer(HWND hContainerWnd);

	// Implementation of ISECLNContainer
	TOOLKIT_API virtual BOOL ClientToScreen(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL ClientToScreen(LPRECT lpRect);
	TOOLKIT_API virtual BOOL ScreenToClient(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL ScreenToClient(LPRECT lpRect);

	// Node-Client conversions. Only applicable for containers with nonclient areas.
	virtual BOOL NodeToClient(LPPOINT)  { return TRUE; }
	virtual BOOL NodeToClient(LPRECT)	{ return TRUE; }
	virtual BOOL ClientToNode(LPPOINT)	{ return TRUE; }
	virtual BOOL ClientToNode(LPRECT)	{ return TRUE; }
	TOOLKIT_API virtual BOOL NodeToScreen(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL NodeToScreen(LPRECT lpRect);
	TOOLKIT_API virtual BOOL ScreenToNode(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL ScreenToNode(LPRECT lpRect);
	TOOLKIT_API virtual CPoint GetNonClientOffset();

	// Painting
	TOOLKIT_API virtual void Invalidate(BOOL bErase);
	TOOLKIT_API virtual BOOL LockDesktopWindowUpdate(BOOL bLock=TRUE);

	// Visibility	
	TOOLKIT_API virtual BOOL ShowWindow(BOOL bShow);	

	TOOLKIT_API virtual BOOL GetClientRect(LPRECT lpRect);
	TOOLKIT_API virtual BOOL GetWindowRect(LPRECT lpRect);
	TOOLKIT_API virtual BOOL QueryNonClientMargins(UINT& nLeft,UINT& nTop,
									UINT& nRight,UINT& nBottom);
	TOOLKIT_API virtual BOOL DisplayContainer(const CRect&) { return FALSE; } // N/A
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify=TRUE);

	virtual ISECLNContainer* CreateCompatibleCntr() 
						{ return new SECLNHwndContainer(m_hWndContainer); }
	TOOLKIT_API virtual ISECLNContainer* CreateCompatibleFloatingCntr(
										SECLayoutNode* pRootNode,
										LPCTSTR lpszTitle,
										BOOL bHideOnClose=TRUE,
										BOOL bCloseEnabled=TRUE);
						
	// Derived Public interface	
	TOOLKIT_API virtual BOOL ReparentHwnd(HWND hWndChild);
	inline HWND GetContainerHWND() 			{ return m_hWndContainer; }
	inline void SetContainerHWND(HWND hWnd) 	{ m_hWndContainer=hWnd; }
	
	TOOLKIT_API static void LockRecalcUpdate(BOOL bLock);
	TOOLKIT_API static void RecalcLayoutAllFrames(BOOL bNotify=TRUE);
	TOOLKIT_API static BOOL LockHWNDDesktopUpdate(BOOL bLock=TRUE);
	
#ifdef OT_BLD_ADVDOCKWIN
	// Override to instantiate derived type
	TOOLKIT_API virtual SECLNFloatingHwndContainer* CreateLNFloatingHWNDContainer(HWND hWndContainer);
#endif

protected:
	// Implementation
	HWND m_hWndContainer;
	
	TOOLKIT_API static BOOL m_bLockRecalcUpdate;
};

/////////////////////////////////////////////////////////////////////////////
// ISECReparentableLayoutNode

// Mixin interface for layout node's that can support a reparenting action.

class ISECReparentableNode 
{
public:
	virtual ~ISECReparentableNode() {}

	// Reassign window ownership based on the context passed in via
	// the opaque ISECLNContainer pointer.
	TOOLKIT_API virtual BOOL ReparentNode(ISECLNContainer* pNewOwner)=0;
	TOOLKIT_API virtual ISECLNContainer* GetContainer()=0;
};

/////////////////////////////////////////////////////////////////////////////
// SECDefReparentableNode

// Default implementation of the ISECReparentableNode interface.

class SECDefReparentableNode : public ISECReparentableNode 
{
public:
	inline SECDefReparentableNode() { m_pCurrentContainer=NULL; }
	
	// Implementation of ISECReparentableNode
	TOOLKIT_API virtual BOOL ReparentNode(ISECLNContainer* pNewOwner);
	virtual ISECLNContainer* GetContainer() { return m_pCurrentContainer; }	
	
	// New Operations
	TOOLKIT_API static void ClearReparentLink(SECLayoutNode* pRoot,ISECLNContainer* pCntr);

protected:
	// New Overridables
	virtual void SetNewNodeOwnerHWND(HWND) {}
	
protected:
	// Implementation
	TOOLKIT_API virtual void ResetMemoryManagement();
	TOOLKIT_API virtual BOOL ResetWindowLink(ISECLNContainer* pNewOwner);

	ISECLNContainer* m_pCurrentContainer;
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

#endif //__SECLAYOUT_DOCKING_CONTAINER_H__
