///////////////////////////////////////////////////////////////////////////////
// Layoutnd.h : Declaration of SECLayoutNode
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
// Description:  Declaration of SECLayoutNode abstract base class.
//
// SECLayoutNode abstract base class
// SECLayoutNode is the base type for the layout manager framework.
// All layout algorithms and primitive types (CWnds, etc) are derived from
// this class.

#ifndef __SECLAYOUTNODE_H__
#define __SECLAYOUTNODE_H__

#include "Foundation\Patterns\MFC\Composite.h"
#include "Foundation\Patterns\MFC\FactoryP.h"

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

// For Get/SetMinMaxSize
#define SEC_LNODE_NO_MINSIZE	0x0001		// Minsize value not to be used
#define SEC_LNODE_NO_MAXSIZE	0x0002		// Maxsize value not to be used

// Generic node extended styles

// Node size/movement restrictions
#define SEC_LNODE_EX_NOSIZE_HORZ	0x0001	// fixed width
#define SEC_LNODE_EX_NOSIZE_VERT	0x0002	// fixed height
#define SEC_LNODE_EX_NOMOVE_HORZ	0x0004	// fixed horizontal position
#define SEC_LNODE_EX_NOMOVE_VERT	0x0008	// fixed vertical position

// Optimized redraw:
#define SEC_LNODE_EX_OPTIMIZE_REDRAW	0x0010	

// Default extended styles:
#define SEC_LNODE_EX_DEFAULTS		0			// no optimizations by default

// Macros

// Types

// Forward Declarations
class SECLayoutNode;
typedef stingray::foundation::SECObjectMemoryManager_T<SECLayoutNode> SECLNMemMgr;

//@doc SECLayoutNode
//@mfunc void  | SECLayoutNode | ClearInvalidateDirty | Clears the current invalidate dirty bit.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void  | SECLayoutNode | ClearRecalcDirty | Clears the current recalc layout dirty bit.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc CRect  | SECLayoutNode | GetCurrentRect | Gets the current layout node rectangle.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void  | SECLayoutNode | SetCurrentRect | Sets the current layout node rectangle.
//@parm const CRect& | rectCurrent | New rectangle.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc CRect  | SECLayoutNode | GetOldRect | Gets the previous node rectangle before the last RecalcLayout.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void  | SECLayoutNode | SetOldRect | Resets the previous node rectangle setting.
//@parm const CRect& | rectOld | Old rectangle value.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc CRect  | SECLayoutNode | GetInvalidateRect | Gets the current invalidation rectangle.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void  | SECLayoutNode | SetInvalidateRect | Sets the node invalidation rectangle.
//@parm const CRect& | rectInv | Invalidation rectangle.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | ResetInitialRect | Resets the initial rectangle setting.
//@parm const CRect& | rectInitial | Initial rectangle.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | GetPreferredRect| Gets the preferred rectangle setting.
//@parm CRect& | rectPreferred | Preferred rect.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetPreferredRect | Sets the preferred rectangle setting.
//@parm CRect& | rectPreferred | Preferred rect.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetParentNode | Sets the parent of this layout node.
//@parm SECLayoutNode* | pNode | New parent node.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc SECLayoutNode* | SECLayoutNode | GetParentNode | Gets the parent of this layout node.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetInvalidateDirty | Sets the invalidation dirty bit.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc BOOL | SECLayoutNode | IsInvalidateDirty | Queries the invalidation dirty bit.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc BOOL | SECLayoutNode | IsNodeAttached | Queries if this node is attached to an HWND or other external object.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc DWORD | SECLayoutNode | GetNodeExStyle | Queries the node extended styles.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | GetInitialRect | Queries the node initial rect
//@parm CRect& | rectInitial | Initial node rect.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetInitialRect | Sets the node initial rect
//@parm CRect& | rectInitial | Initial node rect.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc int | SECLayoutNode | GetDeferWindowCount | Returns the total number of children items to be drawn 
// by a DeferWindowPos call in RealizeNode
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetNodeHorizontal | Sets the base node orientation.
//@parmopt BOOL | bHorz | TRUE | If TRUE, sets to horizontal orientation.
//@parmopt BOOL | bRecurse | FALSE | If TRUE, recurses all child nodes.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc BOOL | SECLayoutNode | GetNodeHorizontal | Gets base node orientation setting.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc void | SECLayoutNode | SetNodeTitle | Sets the associated node title string.
//@parm LPCTSTR | lpszTitle | The title string.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc LPCTSTR | SECLayoutNode | GetNodeTitle | Gets the associated node title string.
//@xref <c SECLayoutNode>

//@doc SECLayoutNode
//@mfunc BOOL | SECLayoutNode | UpdateFrameTitle | Updates the node title in a manner appropriate to the derived class.
//@xref <c SECLayoutNode>


/////////////////////////////////////////////////////////////////////////////
// SECLayoutNode

//@doc SECLayoutNode 
//@class Common base class to all layout nodes

class SECLayoutNode : public stingray::foundation::SECComposite_T<SECLayoutNode*>
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Initialization/Destruction
	TOOLKIT_API SECLayoutNode();
	TOOLKIT_API virtual ~SECLayoutNode();

	// Attributes

	//@access Attributes

	//@cmember
	/* Queries the number of child items to be drawn by a DeferWindowPos call in RealizeNode.*/
	inline virtual int GetDeferWindowCount() { return 0; }
	
	//@cmember
	/* Gets current node attachment state.*/
	inline virtual BOOL IsNodeAttached() { return TRUE; }

	//	...Publicly accessible member variables...

	// Accessors
	//	...Get and Set functions...

	//@cmember
	/* Sets the minimum/maximum node size information.*/
	TOOLKIT_API virtual void SetMinMaxSize(const CSize& sizeMin,const CSize& sizeMax,DWORD dwFlags=0);

	//@cmember
	/* Gets the minimum/maximum node size information.*/
	TOOLKIT_API virtual void GetMinMaxSize(CSize& sizeMin,CSize& sizeMax,DWORD& dwFlags); 

	//@cmember
	/* Sets the node parent.*/
	inline virtual void SetParentNode(SECLayoutNode* pNode) 			{ SetParent(pNode); }

	//@cmember
	/* Gets the node parent.*/
	inline virtual SECLayoutNode* GetParentNode()			 			{ return (SECLayoutNode*)GetParent(); }

	//@cmember
	/* Gets the root node parent.*/
	TOOLKIT_API virtual SECLayoutNode* GetRootParentNode();

	//@cmember
	/* Marks as dirty for needed position recalculation.*/
	TOOLKIT_API virtual void SetRecalcDirty(BOOL bSetAncestorsDirty=FALSE);

	//@cmember
	/* Marks as clean for needed position recalculation.*/
	inline virtual void ClearRecalcDirty()								{ m_bRecalcDirty=FALSE; }

	//@cmember
	/* Marks as dirty for needed invalidation.*/
	inline virtual void SetInvalidateDirty() 							{ m_bInvalidateDirty=TRUE; }

	//@cmember
	/* Gets the invalidation dirty flag.*/
	inline virtual BOOL IsInvalidateDirty()  							{ return m_bInvalidateDirty; }

	//@cmember
	/* Sets the node extended style information.*/
	TOOLKIT_API virtual void SetNodeExStyle(DWORD dwExStyle=0,BOOL bRecurseChildren=FALSE);

	//@cmember
	/* Modifies the node extended style information.*/
	TOOLKIT_API virtual void ModifyNodeStyleEx(DWORD dwRemove=0,DWORD dwAdd=0,BOOL bRecurseChildren=FALSE);

	//@cmember
	/* Gets the node extended style information*/
	inline virtual DWORD GetNodeExStyle() 								{ return m_dwExStyle; }

	// Gets/Sets the realize node lockdown mode (prevents RealizeNode from being processed)
	TOOLKIT_API virtual void SetLockRealizeNode(BOOL bLock=TRUE,BOOL bRecurse=TRUE);
	inline BOOL GetLockRealizeNode() { return m_bLockRealizeNode; }

	// rectangle manipulation/queries

	//@cmember
	/* Gets initial rectangle setting.*/
	virtual void GetInitialRect(CRect& rectInitial) { rectInitial=m_rectInitial; }

	//@cmember
	/* Sets the initial rectangle setting.*/
	TOOLKIT_API virtual void SetInitialRect(const CRect& rectInitial);

	//@cmember
	/* Sets the initial rectangle setting.*/
	TOOLKIT_API virtual void SetInitialRect();		

	//@cmember
	/* Resets the initial rectangle setting.*/
	virtual inline void ResetInitialRect(const CRect& rectInitial)		{ m_rectInitial=rectInitial; }

	//@cmember
	/* Gets the preferred rectangle setting.*/
	virtual inline void GetPreferredRect(CRect& rectPreferred)	  		{ rectPreferred=m_rectPreferred; }

	//@cmember
	/* Sets the preferred rectangle setting.*/
	virtual inline void SetPreferredRect(const CRect& rectPreferred) 	{ m_rectPreferred=rectPreferred; }

	//@cmember
	/* Gets current rectangle setting.*/
	virtual inline CRect GetCurrentRect()			 					{ return m_rectCurrent;}
	TOOLKIT_API virtual CRect GetCurrentRectWithinMinMax();
	TOOLKIT_API void FitRectWithinNodeMinMax(CRect& rect);

	//@cmember
	/* Sets current rectangle setting.*/
	virtual inline void SetCurrentRect(const CRect& rectCurrent)		{ m_rectCurrent=rectCurrent; }

	//@cmember
	/* Gets the rectangle setting previous to the last recalculation.*/
	virtual inline CRect GetOldRect()									{ return m_rectOld; }

	//@cmember
	/* Resets the rectangle setting previous to the last recalculation.*/
	virtual inline void SetOldRect(const CRect& rectOld)				{ m_rectOld=rectOld; }

	//@cmember
	/* Gets the invalidation rectangle setting.*/
	virtual inline CRect GetInvalidateRect()							{ return m_rectInvalidate; }

	//@cmember
	/* Sets the invalidation rectangle setting.*/
	virtual inline void SetInvalidateRect(const CRect& rectInv)			{ m_rectInvalidate=rectInv; }

	// Operations
	//@access Operations
	//@cmember
	/* Adds a layout node as a child.*/
	TOOLKIT_API virtual int AddLayoutNode(SECLayoutNode* pNode);
	
	//@cmember
	/* Changes the position of one child node relative to another.*/
	TOOLKIT_API virtual BOOL ChangeChildNodePosition(SECLayoutNode* pNodeToChange,
									SECLayoutNode* pNodeTarget,BOOL bAfter=TRUE);

	//@cmember
	/* Removes a layout node as a child.*/
	TOOLKIT_API virtual int RemoveLayoutNode(SECLayoutNode* pNode);

	//@cmember
	/* Recalculates the position of this and all child nodes.*/
	TOOLKIT_API virtual CRect RecalcLayout(const CRect& rectDesired,
							   BOOL bChildNegotiate=TRUE,
							   BOOL bStrictRecalc=FALSE);
	inline CRect RecalcLayout() { return RecalcLayout(GetCurrentRect(),FALSE,TRUE); }							   

	// "Realize" the node on the screen.
	// This member recursively kicks off RealizeNodeHelper, in general
	// users should override RealizeNodeHelper, not RealizeNode.
	//@cmember
	/* Applies the latest recalculation to actual screen display.*/
	TOOLKIT_API virtual BOOL RealizeNode(HDC hDC=NULL);
	inline virtual BOOL RealizeNodeHelper(HDWP*,HDC) { return TRUE; }	// NoOp for base class

	// If applicable, erase/paint the node as needed (optimization above RealizeNode)
	TOOLKIT_API virtual void EraseNodeBkgnd(BOOL bRecurse=TRUE,HDC hDC=NULL);
	TOOLKIT_API virtual void PaintNode(BOOL bRecurse=TRUE,HDC hDC=NULL);

	// "Smart" invalidation used by RealizeNode, invalidate minimum change!
	// In general, you will not want to override any of these members, but
	// rather override OnInvalidateRect with specific invalidation code.
	TOOLKIT_API void OptimizedRedrawHelper(BOOL bRecurseChildren=TRUE);

	//@cmember
	/* Kicks off the node painting invalidation.*/
	TOOLKIT_API virtual BOOL PerformInvalidation(BOOL bDoErase,BOOL bRecurseChildren=TRUE);

	//@cmember
	/* Clears the "dirty" flag for optimized invalidation.*/
	inline void ClearInvalidateDirty()			{ m_bInvalidateDirty=FALSE; }

	//@cmember
	/* Calculates the minimum bounding rect based on the current rect of this and all children nodes.*/
	TOOLKIT_API virtual void CalcMinBoundingRect(CRect& rectBounding);

	//@cmember
	/* Recalculates the Z-Order for this node as appropriate.*/
	TOOLKIT_API virtual void RecalcZOrder(BOOL bRecurseChildren=TRUE);
	
	// Sets the back-link to the object memory manager tracking this node (if any)
	inline virtual SECLNMemMgr* GetLNMemMgr()				{ return m_pLNMemMgr; }
	TOOLKIT_API virtual void SetLNMemMgr(SECLNMemMgr* pMemMgr,BOOL bRecurse=FALSE);

	// Sets the offset value for positioning nodes relative to a nonclient area
	inline virtual void SetNonClientOffset(int nLeft,int nTop) { m_nNCOffsetLeft=nLeft; m_nNCOffsetTop=nTop; }
	void GetNonClientOffset(int& nLeft,int& nTop) { nLeft=m_nNCOffsetLeft; nTop=m_nNCOffsetTop; }

	//@cmember
	/* Sets the base node orientation setting. */
	TOOLKIT_API virtual void SetNodeHorizontal(BOOL bHorz=TRUE,BOOL bRecurse=FALSE);

	//@cmember
	/* Gets the base node orientation setting. */
	inline BOOL GetNodeHorizontal()	{ return m_bHorizontalNode; }

	//@cmember
	/* Sets the node title string. */
	inline void SetNodeTitle(LPCTSTR lpszTitle) { m_strTitle=lpszTitle; UpdateFrameTitle();}

	//@cmember
	/* Gets the node title string. */
	inline LPCTSTR GetNodeTitle()				 { return m_strTitle; }

	//@cmember
	/* Updates the node title in a manner appropriate to the derived class. */
	inline virtual void UpdateFrameTitle(){};


	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//
protected:

	//@access Overridables

	//@cmember
	/* Callback on RecalcLayout. Override this for custom layout.*/
	TOOLKIT_API virtual CRect OnRecalcLayout(const CRect& rectDesired,BOOL bChildNegotiate,
								 BOOL bStrictRecalc);

	//@cmember
	/* Node painting invalidation is occurring. Override for custom redraw optimizations.*/
	TOOLKIT_API virtual void OnInvalidateRect(const CRect& rectInvalid,BOOL bDoErase);

	//@cmember
	/* Override to selectively allow or reject recalculation attempts.*/
	TOOLKIT_API virtual BOOL DoProcessRecalcLayout(BOOL bStrict,const CRect& rectDesired);

	//@cmember
	/* Override to hook into parent-child layout negotiation*/
	TOOLKIT_API virtual void OnNegotiateNodeRect(CRect& rectNode);

	// last chance to override node rectangle after RecalcLayout, 
	// but before RealizeNode
	//@cmember
	/* Override to hook into node "manual overrides"*/
	TOOLKIT_API virtual void OnApplyOverrides(const CRect& rectOld,CRect& rectNew);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	CSize	m_sizeMin,m_sizeMax;
	DWORD	m_dwMinMaxFlags;
	BOOL	m_bRecalcDirty;
	BOOL	m_bInvalidateDirty;
	DWORD	m_dwExStyle;
	int		m_nNCOffsetLeft,m_nNCOffsetTop;
	BOOL	m_bLockRealizeNode;
	BOOL	m_bHorizontalNode;
	CString	m_strTitle;

	// Implementation Member Functions
	TOOLKIT_API virtual void EraseInvalidRects();

	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECLayoutNode)
	//}}AFX_VIRTUAL

	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:

	// Derived classes must always get/set these through the accessors!
	CRect m_rectInitial,m_rectCurrent;
	CRect m_rectPreferred,m_rectOld,m_rectInvalidate;
	SECLNMemMgr* m_pLNMemMgr;	
};


// Useful collection type
typedef CTypedPtrList<CPtrList,SECLayoutNode*> SECLayoutNodePtrList;
typedef CTypedPtrArray<CPtrArray,SECLayoutNode*> SECLayoutNodePtrArray;

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SECLAYOUTNODE_H__

