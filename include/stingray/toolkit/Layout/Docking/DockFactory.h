///////////////////////////////////////////////////////////////////////////////
// DockFactory.h
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
// Description:  Declaration of SECLayoutDockFactory
//
// SECLayoutDockFactory
// This helper class is used primarility to automate many of the common
// tasks involved in allocating and configuring docking layout managers. It is also
// very useful for encapsulating all memory management required
// for the numerous dynamic node attachments for complex docking 
// layout configurations.
// 

#ifndef __SECLAYOUT_DOCK_FACTORY_H__
#define __SECLAYOUT_DOCK_FACTORY_H__

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

// Types

// Forward Declarations

/////////////////////////////////////////////////////////////////////////////
// Factory Creation Objects

// These templatized classes are provided as an alternate to the CObject 
// IMPLEMENT_DYNCREATE mechanism for creating runtime objects based on 
// class name information (necessary since SECLayoutNode is provided as 
// a true mixin base class, and is thus not CObject derived).
// Note that we are providing multiple derived classes here to insure
// the proper type safety of the CreateObject return value.

typedef stingray::foundation::SECClassFactory<SECLayoutNodeDCBase> SECLayoutNodeBaseDCClassFactory;

/////////////////////////////////////////////////////////////////////////////
// Macros

// Convenience macros for layout runtime class passing (note the use
// of templates to break the CObect dependency)

#define NODEDC_CLASS(cls)	stingray::foundation::SECClassFactory_T<cls,SECLayoutNodeDCBase>()
#define NODEBP(pNode) 		(SECLayoutNode**)(&pNode)		// Node "Back Pointer" macro
		
/////////////////////////////////////////////////////////////////////////////
// SECLayoutDockFactory

//@doc SECLayoutDockFactory 
//@class Docking Layout Node object creation factory
//@comm This extension of SECLayoutFactory is provided to support
// creation and initialization of dockable layout node objects.
//@BASE public | SECLayoutFactory
//@xref <c SECLayoutFactory>
class TOOLKIT_API SECLayoutDockFactory : public SECLayoutFactory
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	//@access Public Interface

	// Initialization/Destruction
	SECLayoutDockFactory();
	virtual ~SECLayoutDockFactory();

	// Class-Factory functions:
	// These members allocate, create, and attach specific layout mgr
	// objects for easy use	by the calling class. Note: the pointer returned
	// should *NOT* be deallocated by the caller. This class will handle all
	// necessary memory management.

	//@access Dockable Gripper Wrapper Creation

	//@cmember 
	/* Create a dockable gripper wrapper object */
	virtual SECLayoutNode* CreateDockingWrapper(CWnd* pParentWnd,
									                            SECLayoutNode* pNodeToWrap,
									                            LPCTSTR lpszTitle=NULL,
									                            DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable gripper wrapper object */
	virtual SECLayoutNode* CreateDockingWrapper(CWnd* pParentWnd,
									                            const SECLayoutNodeBaseDCClassFactory& classWrapper, 	
									                            SECLayoutNode* pNodeToWrap,
									                            LPCTSTR lpszTitle=NULL,
									                            DWORD dwGripperStyle=0);								

	//@access Dockable Node Creation

	//@cmember 
	/* Create a dockable layout node */
	virtual SECLayoutNode* CreateDockableNode(CWnd* pParentWnd,
									                          const SECLayoutNodeClassFactory& classNode, 
									                          LPCTSTR lpszTitle=NULL,
									                          SECLayoutNode** ppNode=NULL,
									                          DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable layout node */
	virtual SECLayoutNode* CreateDockableNode(SECLayoutNode* pParentNode,
									                          CWnd* pParentWnd,
									                          const SECLayoutNodeClassFactory& classNode, 
									                          LPCTSTR lpszTitle=NULL,
									                          SECLayoutNode** ppNode=NULL,
									                          DWORD dwGripperStyle=0);

	//@access Dockable DC based Node Creation

	//@cmember 
	/* Create a dockable device context based layout node */
	virtual SECLayoutNode* CreateDockableNodeDC(CWnd* pParentWnd,
									                            LPCTSTR lpszTitle=NULL,
									                            SECLayoutNode** ppNodeDC=NULL,
									                            DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable device context based layout node */
	virtual SECLayoutNode* CreateDockableNodeDC(CWnd* pParentWnd,
									                            const SECLayoutNodeDCClassFactory& classNodeDC, 
									                            LPCTSTR lpszTitle=NULL,
									                            SECLayoutNode** ppNodeDC=NULL,
									                            DWORD dwGripperStyle=0); 

	//@access Dockable HWND based Node Creation

	//@cmember 
	/* Create a dockable HWND based layout node. */
	virtual SECLayoutNode* CreateDockableNodeWnd(UINT nIDAttachWnd,CWnd* pParentWnd,
									                             LPCTSTR lpszTitle=NULL,
									                             BOOL bAutoScale=FALSE,
									                             SECLayoutNode** ppNodeWnd=NULL,
									                             DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable HWND based layout node. */
	virtual SECLayoutNode* CreateDockableNodeWnd(UINT nIDAttachWnd,CWnd* pParentWnd,
									                             const SECLayoutNodeWndClassFactory& classNodeWnd, 
									                             LPCTSTR lpszTitle=NULL,
									                             BOOL bAutoScale=FALSE,
									                             SECLayoutNode** ppNodeWnd=NULL,
									                             DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable HWND based layout node. */
	virtual SECLayoutNode* CreateDockableNodeWnd(CWnd* pAttachWnd,CWnd* pParentWnd,
									                             LPCTSTR lpszTitle=NULL,
									                             BOOL bAutoScale=FALSE,
									                             SECLayoutNode** ppNodeWnd=NULL,
									                             DWORD dwGripperStyle=0);

	//@cmember 
	/* Create a dockable HWND based layout node. */
	virtual SECLayoutNode* CreateDockableNodeWnd(CWnd* pAttachWnd,CWnd* pParentWnd,
									                             const SECLayoutNodeWndClassFactory& classNodeWnd, 
									                             LPCTSTR lpszTitle=NULL,
									                             BOOL bAutoScale=FALSE,
									                             SECLayoutNode** ppNodeWnd=NULL,
									                             DWORD dwGripperStyle=0);

	// Utility functions:
protected:
	// Implementation Member Functions
	virtual BOOL ApplyScaleToChildren(CWnd* pParentWnd);
	
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


#endif //__SECLAYOUT_DOCK_FACTORY_H__
