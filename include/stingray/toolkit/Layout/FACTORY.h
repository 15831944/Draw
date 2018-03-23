///////////////////////////////////////////////////////////////////////////////
// Factory.h : Declaration of SECLayoutFactory
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
// Description:  Declaration of SECLayoutFactory
//
// SECLayoutFactory
// This helper class is used primarility to automate many of the common
// tasks involved in allocating and configuring layout managers. It is also
// very useful for encapsulating all memory management required
// for the numerous dynamic node attachments for complex layout configurations.
// 

#ifndef __SECLAYOUT_FACTORY_H__
#define __SECLAYOUT_FACTORY_H__

// Header Includes

#ifndef __SECLAYOUTNODEWND_H__
#include "toolkit\layout\nodewnd.h"
#endif

#include "toolkit\layout\LayListn.h"
#include "toolkit\layout\NodeDC.h"
#include "toolkit\layout\Docking\DefDockBase.h"
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
typedef CTypedPtrList<CPtrList,CWnd *> CWndPtrList;

// Forward Declarations

/////////////////////////////////////////////////////////////////////////////
// Factory Creation Objects

// These templatized classes are provided as an alternate to the CObject 
// IMPLEMENT_DYNCREATE mechanism for creating runtime objects based on 
// class name information (necessary since SECLayoutNode is provided as 
// a true mixin base class, and is thus not CObject derived).
// Note that we are providing multiple derived classes here to insure
// the proper type safety of the CreateObject return value.

typedef stingray::foundation::SECClassFactory<SECLayoutNode>		SECLayoutNodeClassFactory;
typedef stingray::foundation::SECClassFactory<SECLayoutNodeWnd>		SECLayoutNodeWndClassFactory;
typedef stingray::foundation::SECClassFactory<SECLayoutWndListener>	SECLayoutWndListenerClassFactory;
typedef stingray::foundation::SECClassFactory<SECLayoutNodeDCBase>	SECLayoutNodeDCClassFactory;

/////////////////////////////////////////////////////////////////////////////
// Macros

// Convenience macros for layout runtime class passing 
// (recall the use of templates to break the CObect dependency)
#define NODE_CLASS(cls)			stingray::foundation::SECClassFactory_T<cls,SECLayoutNode>()
#define NODEWND_CLASS(cls)		stingray::foundation::SECClassFactory_T<cls,SECLayoutNodeWnd>()
#define NODELISTEN_CLASS(cls)	stingray::foundation::SECClassFactory_T<cls,SECLayoutWndListener>()
#define NODEDC_CLASS(cls)		stingray::foundation::SECClassFactory_T<cls,SECLayoutNodeDCBase>()

/////////////////////////////////////////////////////////////////////////////
// SECLayoutFactory

//@doc SECLayoutFactory 
//@class Layout node production factory class
class SECLayoutFactory 
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	//@access Public Interface

	// Initialization/Destruction
	TOOLKIT_API SECLayoutFactory();
	TOOLKIT_API virtual ~SECLayoutFactory();

	// Attributes
	//	...Publicly accessible member variables...

	//@cmember
	/* Automatically sets the min/max size information for all subsequently produced nodes*/
	TOOLKIT_API void AutoSetMinMaxSize(CSize sizeMin, CSize sizeMax, DWORD dwFlags=0, BOOL bEnable=TRUE);

	//@cmember
	/* Automatically sets the preferred rectangle for all subsequently produced nodes*/
	TOOLKIT_API void AutoSetPreferredRect(const CRect& rectPreferred, BOOL bEnable=TRUE);
	
	//@cmember
	/* Automatically sets the initial rectangle for all subsequently produced nodes*/
	TOOLKIT_API void AutoSetInitialRect(const CRect& rectInitial,BOOL bEnable=TRUE);

	// Class-Factory functions:
	// These members allocate, create, and attach specific layout mgr
	// objects for easy use	by the calling class. Note: the pointer returned
	// should *NOT* be deallocated by the caller. This class will handle all
	// necessary memory management.

	//@cmember
	/* Creates a layout node object with the specified runtime class*/
	TOOLKIT_API SECLayoutNode* CreateNode(LPCTSTR lpszTitle=NULL);
	//@cmember
	/* Creates a layout node object with the specified runtime class*/
	TOOLKIT_API SECLayoutNode* CreateNode(const SECLayoutNodeClassFactory& classNode,LPCTSTR lpszTitle=NULL);
	//@cmember
	/* Creates a layout node object with the specified runtime class*/
	TOOLKIT_API SECLayoutNode* CreateNode(SECLayoutNode* pParentNode,LPCTSTR lpszTitle=NULL);
	//@cmember
	/* Creates a layout node object with the specified runtime class as a child of pParentNode*/
	TOOLKIT_API SECLayoutNode* CreateNode(SECLayoutNode* pParentNode,const SECLayoutNodeClassFactory& classNode,
							LPCTSTR lpszTitle=NULL);

	//@cmember
	/* Create a window node and auto-attach to CWnd*/
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(CWnd* pAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode,
							const SECLayoutNodeWndClassFactory& classNodeWnd,
							LPCTSTR lpszTitle=NULL);
							
	//@cmember
	/* Create a window node and auto-attach to CWnd*/
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(CWnd* pAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode=NULL,
							LPCTSTR lpszTitle=NULL);						

	//@cmember
	/* Create a window node and auto-attach to HWND*/
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(HWND hAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode,
							const SECLayoutNodeWndClassFactory& classNodeWnd,
							LPCTSTR lpszTitle=NULL);
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(HWND hAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode=NULL,
							LPCTSTR lpszTitle=NULL);

	//@cmember
	/* Create a window node and auto-attach to a control id*/
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(UINT nIDAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode,
							const SECLayoutNodeWndClassFactory& classNodeWnd,
							LPCTSTR lpszTitle=NULL);
	//@cmember
	/* Create a window node and auto-attach to a control id*/
	TOOLKIT_API SECLayoutNodeWnd* CreateNodeWnd(UINT nIDAttachWnd,CWnd* pParent,
							SECLayoutNode* pParentNode=NULL,
							LPCTSTR lpszTitle=NULL);

	//@cmember
	/* Create a group of window nodes from a range of control ids*/
	TOOLKIT_API int CreateNodeWndRange(UINT nIDStart,UINT nIDEnd,
							CWnd* pParent,SECLayoutNode* pParentNode,
							CPtrArray* pArrNodes,
							const SECLayoutNodeWndClassFactory& classNodeWnd);
	//@cmember
	/* Create a group of window nodes from a range of control ids*/
	TOOLKIT_API int CreateNodeWndRange(UINT nIDStart,UINT nIDEnd,
							CWnd* pParent,SECLayoutNode* pParentNode=NULL,
							CPtrArray* pArrNodes=NULL);

	//@cmember
	/* Create a group of window nodes from an array of control ids*/
	TOOLKIT_API int CreateNodeWndArray(const UINT* lpuIDs,int nIDCount,
							CWnd* pParent,SECLayoutNode* pParentNode,
							CPtrArray* pArrNodes,
							const SECLayoutNodeWndClassFactory& classNodeWnd);
	//@cmember
	/* Create a group of window nodes from an array of control ids*/
	TOOLKIT_API int CreateNodeWndArray(const UINT* lpuIDs,int nIDCount,
							CWnd* pParent,SECLayoutNode* pParentNode=NULL,
							CPtrArray* pArrNodes=NULL);

	//@cmember
	/* Create a Device Context associated layout node */
	TOOLKIT_API SECLayoutNodeDCBase* CreateNodeDC(CWnd* pWndParent,SECLayoutNode* pParentNode,
							const SECLayoutNodeDCClassFactory& classNodeDC,
							LPCTSTR lpszTitle=NULL);

	//@cmember
	/* Create a node window listener object*/
	TOOLKIT_API SECLayoutWndListener* CreateLayoutWndListener(const SECLayoutWndListenerClassFactory& 
							classLayoutWndListener);
	//@cmember
	/* Create a node window listener object*/
	TOOLKIT_API SECLayoutWndListener* CreateLayoutWndListener();

	// Utility functions:

	//@cmember
	/* Get a list of all child windows of a particular parent*/
	TOOLKIT_API virtual BOOL GetChildWindowList(CWndPtrList& listWnds,CWnd* pParent,
							CRuntimeClass* pClassMask=(CRuntimeClass *)NULL);
	//@cmember
	/* Automatically allocate, link, and add all children windows as children nodes*/
	TOOLKIT_API virtual BOOL AutoPopulateNodeWnd(SECLayoutNode* pParentNode,CWnd* pParentWnd,
							CRuntimeClass* pClassMask=(CRuntimeClass *)NULL);

	//@cmember
	/* Deallocate a layout node object*/
	TOOLKIT_API virtual void DeallocNode(SECLayoutNode* pNode);

	//@cmember 
	/* Deallocate all layout node objects */
	TOOLKIT_API virtual void DeallocAllNodes();

	//@cmember 
	/* Deallocate a window listener object */
	TOOLKIT_API virtual void DeallocWndListener(SECLayoutWndListener* pListener);

	//@cmember 
	/* Deallocate all window listener objects */
	TOOLKIT_API virtual void DeallocAllWndListeners();

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:
	//@access Overridables

	//@cmember
	/* Override to reject automatic property setting on a newly allocated node.*/
	TOOLKIT_API virtual BOOL OnAutoSetNode(SECLayoutNode* pNode);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Default state cached factory creation objects 
	stingray::foundation::SECClassFactory_T<SECLayoutNode,SECLayoutNode> m_classLayoutNode;
	stingray::foundation::SECClassFactory_T<SECLayoutNodeWnd,SECLayoutNodeWnd> m_classLayoutNodeWnd;
	stingray::foundation::SECClassFactory_T<SECLayoutWndListener,SECLayoutWndListener> m_classLayoutWndListener;

	// Factory memory management tracking (type safe)
	SECLNMemMgr m_mgrLayoutNode;	// can use for SECLayoutNodeWnd too, since destruct virtual
	stingray::foundation::SECObjectMemoryManager_T<SECLayoutWndListener> m_mgrLayoutWndListener;

	// Min/Max node size
	BOOL m_bAutoSetMinMaxSize,m_bAutoSetPreferredRect,m_bAutoSetInitialRect;
	CSize m_sizeMin,m_sizeMax;
	CRect m_rectPreferred,m_rectInitial;
	DWORD m_dwMinMaxFlags;
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


#endif //__SECLAYOUT_FACTORY_H__

