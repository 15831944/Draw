///////////////////////////////////////////////////////////////////////////////
// OtlLayoutNode.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __OTLLAYOUTNODE_H__
#define __OTLLAYOUTNODE_H__

#ifndef __OTLBASE_H__
	#error otllayoutnode.h requires otlbase.h to be included first
#endif

#include <foundation\stwarn.h>
#include <list>
#include <algorithm>
#include <foundation\stwarnp.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

// For Get/SetMinMaxSize
#define OTL_LNODE_NO_MINSIZE	0x0001		// Minsize value not to be used
#define OTL_LNODE_NO_MAXSIZE	0x0002		// Maxsize value not to be used

// Generic node extended styles

// Node size/movement restrictions
#define OTL_LNODE_EX_NOSIZE_HORZ	0x0001	// fixed width
#define OTL_LNODE_EX_NOSIZE_VERT	0x0002	// fixed height
#define OTL_LNODE_EX_NOMOVE_HORZ	0x0004	// fixed horizontal position
#define OTL_LNODE_EX_NOMOVE_VERT	0x0008	// fixed vertical position

// Optimized redraw:
#define OTL_LNODE_EX_OPTIMIZE_REDRAW	0x0010	

// Default extended styles:
#define OTL_LNODE_EX_DEFAULTS		0			// no optimizations by default


/////////////////////////////////////////////////////////////////////////////
// COtlLayoutNode

class TOOLKIT_API COtlLayoutNode
{
public:
	typedef std::list< COtlLayoutNode* > OTLNODELIST;
	OTLNODELIST m_children;
	COtlLayoutNode* m_pParent;
public:
	COtlLayoutNode();
	~COtlLayoutNode();

public:
	inline DWORD GetNodeExStyle() { return m_dwExStyle; }
	BOOL AddChild(COtlLayoutNode* pNode);
	BOOL RemoveChild(COtlLayoutNode* pNode);
	void SetParent(COtlLayoutNode* parent,BOOL bRemoveFromOldParent=TRUE);
	void ModifyNodeStyleEx(DWORD dwRemove=0,DWORD dwAdd=0,BOOL bRecurseChildren=FALSE);
	void ClearInvalidateDirty() {m_bInvalidateDirty=FALSE;}
	void GetOldRect(LPRECT lpRect);
	void SetOldRect(const RECT& rectOld) {::CopyRect(&m_rectOld, &rectOld);	}
	void SetInvalidateDirty() {	m_bInvalidateDirty=TRUE;}
	void OptimizedRedrawHelper(BOOL bRecurseChildren=TRUE);
	void SetInitialRect(const RECT& rectInitial);
	void SetCurrentRect(const RECT& rectCurrent);
	void SetPreferredRect(const RECT& rectPreferred);
	void GetCurrentRect(LPRECT lpRect);
	void GetInitialRect(LPRECT lpRect);
	void SetInitialRect();
	void CalcMinBoundingRect(LPRECT prectBounding);

// overrideables
	virtual void RecalcZOrder(BOOL bRecurseChildren=TRUE);
	virtual BOOL DoProcessRecalcLayout(BOOL bStrict,const RECT& rectDesired);
	virtual void RecalcLayout(	LPRECT lpRect, const RECT& rectDesired, BOOL bChildNegotiate=TRUE, BOOL bStrictRecalc=FALSE);
	virtual void RecalcLayout(LPRECT lpRect=NULL);
	virtual void ClearRecalcDirty() {m_bRecalcDirty=FALSE;}
	virtual void OnRecalcLayout( LPRECT lpRect, const RECT& rectDesired, BOOL bChildNegotiate, BOOL bStrictRecalc); 
	virtual void OnNegotiateNodeRect(RECT& rectNode);
	virtual int GetChildCount(BOOL bRecursive=FALSE);
	virtual int GetDeferWindowCount();
	virtual BOOL RealizeNode(HDC hDC=NULL);
	virtual BOOL RealizeNodeHelper(HDWP* phDWP,HDC hDC);
	virtual void SetInvalidateRect(const RECT& rectInv) {::CopyRect(&m_rectInvalidate, &rectInv);}
	virtual BOOL IsInvalidateDirty() {return m_bInvalidateDirty;}
	virtual BOOL PerformInvalidation(BOOL bDoErase,BOOL bRecurseChildren=TRUE);
	virtual void GetInvalidateRect(LPRECT lpRect);
	virtual void EraseInvalidRects();
	virtual void OnInvalidateRect(const RECT& rectInvalid,BOOL bDoErase);
	virtual void OnApplyOverrides(const RECT& rectOld, RECT& rectNew);
	virtual void SetMinMaxSize(int cxMin, int cyMin, int cxMax=0, int cyMax=0, DWORD dwFlags=0);
	virtual void SetMinMaxSize(const SIZE& sizeMin,const SIZE& sizeMax,DWORD dwFlags=0);
	virtual void GetMinMaxSize(SIZE& sizeMin, SIZE& sizeMax, DWORD& dwFlags);
	virtual BOOL IsNodeAttached() { return TRUE; }
	virtual COtlLayoutNode* GetParentNode() { return m_pParent; }
	virtual void SetNodeExStyle(DWORD dwExStyle=0,BOOL bRecurseChildren=FALSE);
	virtual void Show( BOOL bShow ) {}
	virtual COtlLayoutNode* FindChild( int nCtrlID );
	virtual int GetCtrlID() { return 0; }
	virtual BOOL WithinSizeLimits(DWORD dwDrawAspect, SIZEL *psizel);

protected:
	SIZE m_sizeMin,m_sizeMax;
	DWORD m_dwMinMaxFlags;
	BOOL  m_bRecalcDirty;
	BOOL  m_bInvalidateDirty;
	DWORD m_dwExStyle;
	BOOL m_bHorizontalNode;
	
private:
	RECT m_rectInitial,m_rectCurrent;
	RECT m_rectPreferred,m_rectOld,m_rectInvalidate;
};

	inline COtlLayoutNode::COtlLayoutNode() 
	{
		::SetRectEmpty(&m_rectOld);
		::SetRectEmpty(&m_rectCurrent);
		::SetRectEmpty(&m_rectInitial);
		::SetRectEmpty(&m_rectPreferred);
		::SetRectEmpty(&m_rectInvalidate);
		m_sizeMin.cx=m_sizeMin.cy=0;
		m_sizeMax.cx=m_sizeMax.cy=0;
		m_dwMinMaxFlags=OTL_LNODE_NO_MAXSIZE;
		m_bRecalcDirty=TRUE;
		m_bInvalidateDirty=FALSE;
		m_dwExStyle=OTL_LNODE_EX_DEFAULTS;
		m_bHorizontalNode=TRUE;
		m_pParent = NULL;
	}

	inline COtlLayoutNode::~COtlLayoutNode() 
	{
		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			if(*ppNode)
				delete *ppNode;
		}
		m_children.clear();
	}


	inline BOOL COtlLayoutNode::AddChild(COtlLayoutNode* pNode) 
	{
		if(!pNode) return FALSE;

		// Make sure the node has been properly created and initialized
		// before adding to parent!
		OTLASSERT(pNode->IsNodeAttached());
		if(!pNode->IsNodeAttached()) return FALSE;

		COtlLayoutNode* pParent=pNode->GetParentNode();
		if(pParent) 
		{
			if(pParent==this)
				return TRUE;	// already a child!
			else pParent->RemoveChild(pNode);
		}

		OTLNODELIST::iterator ppNode = std::find(m_children.begin(), m_children.end(), pNode);
		if(ppNode == m_children.end() )
		{
			// Add the new child
			m_children.push_back(pNode);
			pNode->m_pParent = this;	// calling SetParent would loop infinitely
		}

		return TRUE;
	}

	inline BOOL COtlLayoutNode::RemoveChild(COtlLayoutNode* pNode) 
	{
		// removes child from the list. does not delete the child
		if(!pNode) return FALSE;

		// Remove the child
		OTLNODELIST::iterator ppNode = std::find(m_children.begin(), m_children.end(), pNode);
		if(ppNode == m_children.end() )
			return FALSE;
		
		m_children.erase(ppNode);
		pNode->SetParent(NULL,FALSE);
		return TRUE;
	}

	inline void COtlLayoutNode::SetParent(COtlLayoutNode* parent,BOOL bRemoveFromOldParent) 
	{
		// If remove from old parent flag set, also perform a removal on
		// top of the parent link reset.
		if(bRemoveFromOldParent) 
		{
			// Remove from old parent
			if(m_pParent)
				m_pParent->RemoveChild(this);

			// Add to new parent
			if(parent)
				parent->AddChild(this);
		}

		// And set the internal link
		m_pParent=parent;
	}

	inline void COtlLayoutNode::ModifyNodeStyleEx(DWORD dwRemove,DWORD dwAdd,BOOL bRecurseChildren)
	{
		// modify style for this node
		DWORD dwStyle=GetNodeExStyle();
		dwStyle&=(~(dwRemove));
		dwStyle|=dwAdd;
		SetNodeExStyle(dwStyle,FALSE);

		// and optionally recursively modify style of all children
		if(bRecurseChildren) 
		{
			OTLNODELIST::iterator ppChild;
			for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
			{
				OTLASSERT(*ppChild);
				(*ppChild)->ModifyNodeStyleEx(dwRemove,dwAdd,FALSE);
			}
		}
	}

	inline void COtlLayoutNode::GetOldRect(LPRECT lpRect) 
	{
		OTLASSERT(lpRect);
		::CopyRect(lpRect, &m_rectOld); 
	}


	inline void COtlLayoutNode::OptimizedRedrawHelper(BOOL bRecurseChildren) 
	{
		// Determine optimization state for this node
		BOOL bOptimized=FALSE;
		if(m_dwExStyle & OTL_LNODE_EX_OPTIMIZE_REDRAW)
		   bOptimized=TRUE;
		if((!bOptimized)||(!IsInvalidateDirty())) 
		{
			// Either this node is clean, or optimization has been set for ignore.
			// In either case, we now want to continue searching the children
			// for a pending optimized invalidation.
			ClearInvalidateDirty();				// clear in case not optimized set

			// Recurse children
			if(bRecurseChildren) 
			{
				COtlLayoutNode* pNode = 0;
				OTLNODELIST::iterator ppChild;
				for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
				{
					OTLASSERT(*ppChild);
					pNode = *ppChild;
					pNode->OptimizedRedrawHelper(FALSE);
				}
			}
		}
		else 
		{
			// Perform invalidation in 2 passes: first make all needed erasures,
			// then all needed repaints (this insures a clean repaint).
			PerformInvalidation(TRUE);		// erase all old children rects
			PerformInvalidation(FALSE);		// repaint all new children rects

			// PerformInvalidation has traversed the remainder of this branch,
			// return now and recursively examine other branches.
		}		
	}

	inline void COtlLayoutNode::SetInitialRect(const RECT& rectInitial) 
	{
		::CopyRect(&m_rectInitial, &rectInitial);
		SetCurrentRect(rectInitial);
		SetPreferredRect(rectInitial);

		// Make sure min/max size is not outside of initial rect
		if(m_sizeMin.cx > OtlRectWidth(rectInitial))
		   m_sizeMin.cx=OtlRectWidth(rectInitial);
		if(m_sizeMin.cy>OtlRectHeight(rectInitial))
		   m_sizeMin.cy=OtlRectHeight(rectInitial);
		if(m_sizeMax.cx<OtlRectWidth(rectInitial))
		   m_sizeMax.cx=OtlRectWidth(rectInitial);
		if(m_sizeMax.cy<OtlRectHeight(rectInitial))
		   m_sizeMax.cy=OtlRectHeight(rectInitial);
		
	}

	inline void COtlLayoutNode::SetCurrentRect(const RECT& rectCurrent) 
	{
		::CopyRect(&m_rectCurrent, &rectCurrent); 
	}

	inline void COtlLayoutNode::SetPreferredRect(const RECT& rectPreferred) 
	{ 
		::CopyRect(&m_rectPreferred, &rectPreferred);
	}

	inline void COtlLayoutNode::GetCurrentRect(LPRECT lpRect) 
	{
		OTLASSERT(lpRect);
		::CopyRect(lpRect, &m_rectCurrent);
	}

	inline void COtlLayoutNode::GetInitialRect(LPRECT lpRect) 
	{ 
		OTLASSERT(lpRect);
		::CopyRect(lpRect, &m_rectInitial);
	}

	inline void COtlLayoutNode::SetInitialRect() 
	{
		RECT rectBounding;
		CalcMinBoundingRect(&rectBounding);
		SetInitialRect(rectBounding);
	}

	inline void COtlLayoutNode::CalcMinBoundingRect(LPRECT prectBounding) 
	{
		OTLASSERT(prectBounding);
		RECT rectNodeCurrent;
		::SetRectEmpty(prectBounding);

		// Iterate through top level nodes, calculating
		// the bounding rect for all. Since child nodes completely
		// contain grandchildren, 1 level will be deep enough.
		COtlLayoutNode* pNode;
		BOOL bInitialPass=TRUE;

		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			pNode = *ppNode;
			pNode->GetCurrentRect(&rectNodeCurrent);

			// initialize with first rect
			if(bInitialPass) 
			{ 
				::CopyRect(prectBounding, &rectNodeCurrent);
				bInitialPass=FALSE;
			}
			else 
			{
				// size with additional nodes
				prectBounding->left=min(prectBounding->left,rectNodeCurrent.left);
				prectBounding->right=max(prectBounding->right,rectNodeCurrent.right);
				prectBounding->top=min(prectBounding->top,rectNodeCurrent.top);
				prectBounding->bottom=max(prectBounding->bottom,rectNodeCurrent.bottom);
			}
		}
	}

	inline void COtlLayoutNode::RecalcZOrder(BOOL bRecurseChildren) 
	{
		// Base class does nothing but delegate to children
		if(bRecurseChildren) 
		{
			OTLNODELIST::iterator ppNode;
			for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
			{
				OTLASSERT(*ppNode);
				(*ppNode)->RecalcZOrder(FALSE);
			}
		}
	}

	inline BOOL COtlLayoutNode::DoProcessRecalcLayout(BOOL bStrict,const RECT& rectDesired) 
	{
		BOOL bDirty=m_bRecalcDirty;
		m_bRecalcDirty=FALSE;
		RECT rectCurrent;
		GetCurrentRect(&rectCurrent);
		
		if((bStrict)||(bDirty)||(!::EqualRect(&rectCurrent, &rectDesired)))
			 return TRUE;
		else return FALSE;
	}


	inline void COtlLayoutNode::RecalcLayout(	LPRECT lpRect, 
												const RECT& rectDesired, 
												BOOL bChildNegotiate, 
												BOOL bStrictRecalc) 
	{
		// Recalcs can be expensive - only do this when required!
		if(!DoProcessRecalcLayout(bStrictRecalc,rectDesired)) 	
		{
			if(lpRect)
				GetCurrentRect(lpRect);
			return;
		}

		// Fire off to the virtual callback
		RECT rectOld;
		GetCurrentRect(&rectOld);
		RECT rectNew;
		OnRecalcLayout(&rectNew, rectDesired,bChildNegotiate,bStrictRecalc);

		// Style overrides receive precedence over all other considerations!
		OnApplyOverrides(rectOld,rectNew);
		SetCurrentRect(rectNew);

		// If there was any change, flag for "smart invalidation" at the Realize stage
		if(!::EqualRect(&rectNew, &rectOld))
			SetInvalidateDirty();

		// Done with recalc, clear dirty bit to avoid unnecessary non-strict recalcs.
		ClearRecalcDirty();

		if(lpRect)
			::CopyRect(lpRect, &rectNew);
	}

	inline void COtlLayoutNode::RecalcLayout(LPRECT lpRect) 
	{
		RECT rect;
		GetCurrentRect(&rect);
		RECT rectRet;
		RecalcLayout(&rectRet, rect, FALSE, TRUE); 
		if(lpRect)
			::CopyRect(lpRect, &rectRet);
	}							   

	inline void COtlLayoutNode::OnRecalcLayout(	LPRECT lpRect,
											const RECT& rectDesired,
											BOOL bChildNegotiate,
											BOOL bStrictRecalc) 
	{
		OTLASSERT(lpRect);
		// Base class implements the default layout algorithm: 
		// Child nodes maintain same position.

		// Set this node's rect, offering up to negotiation if non-strict
		RECT rectDesired2;
		::CopyRect(&rectDesired2, &rectDesired);
		if(bChildNegotiate) 
			OnNegotiateNodeRect(rectDesired2);
		SetCurrentRect(rectDesired2);

		int nChildNodes = GetChildCount();
		if(nChildNodes<1) 
		{
			::CopyRect(lpRect, &rectDesired2);
			return;
		}

		// Get initial rect info. This can be used to maintain constant positioning
		// of child windows.
		RECT rectInitial;
		GetInitialRect(&rectInitial);
		int nOffsetX=rectDesired2.left-rectInitial.left;
		int nOffsetY=rectDesired2.top-rectInitial.top;

		// recursively calculate all children nodes as well
		RECT rectNodeInitial;
		RECT rectNodeDesired;

		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			OTLASSERT(*ppNode);

			// Calc rectDesired to maintain constant positioning
			(*ppNode)->GetInitialRect(&rectNodeInitial);
			rectNodeDesired.left=rectNodeInitial.left+nOffsetX;
			rectNodeDesired.right=rectNodeDesired.left+ OtlRectWidth(rectNodeInitial);
			rectNodeDesired.top=rectNodeInitial.top+nOffsetY;
			rectNodeDesired.bottom=rectNodeDesired.top+OtlRectHeight(rectNodeInitial);

			// Now hand off the recal to child...
			RECT r;
			(*ppNode)->RecalcLayout(&r, rectNodeDesired,bChildNegotiate,bStrictRecalc);
		}

		::CopyRect(lpRect, &rectDesired2);

	}

	inline void COtlLayoutNode::OnNegotiateNodeRect(RECT& rectNode) 
	{

		// Do we have a maximum size? If so, accomodate as needed.
		if(!(m_dwMinMaxFlags & OTL_LNODE_NO_MAXSIZE)) 
		{
			if(OtlRectWidth(rectNode)>m_sizeMax.cx)
			   rectNode.right=rectNode.left+m_sizeMax.cx;
			if(OtlRectHeight(rectNode)>m_sizeMax.cy)
			   rectNode.bottom=rectNode.top+m_sizeMax.cy;
		}

		// Do we have a minimum size? If so, accomodate as needed.
		if(!(m_dwMinMaxFlags & OTL_LNODE_NO_MINSIZE)) 
		{
			if(OtlRectWidth(rectNode)<m_sizeMin.cx)
			   rectNode.right=rectNode.left+m_sizeMin.cx;
			if(OtlRectHeight(rectNode)<m_sizeMin.cy)
			   rectNode.bottom=rectNode.top+m_sizeMin.cy;
		}
	}

	inline int COtlLayoutNode::GetChildCount(BOOL bRecursive) 
	{
		// get count of immediate children
		int nChildCount=m_children.size();

		if(bRecursive) 
		{
			// and recurse if specified
			OTLNODELIST::iterator ppNode;
			for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
			{
				OTLASSERT(*ppNode);
				nChildCount += (*ppNode)->GetChildCount(bRecursive);
			}
		}
		return nChildCount;
	}

	inline int COtlLayoutNode::GetDeferWindowCount()
	{ 
		// recurse all children
		int nNodesToUpdate = 0;
		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			OTLASSERT(*ppNode);
			nNodesToUpdate += (*ppNode)->GetDeferWindowCount();
		}
		return nNodesToUpdate;
	}

	inline BOOL COtlLayoutNode::RealizeNode(HDC hDC) 
	{
		// Need initial node count for BeginDeferWindowPos. Traverse all children and sum up.
		int nNodesToUpdate=0;

		OTLNODELIST::iterator ppNode;
		for(ppNode = m_children.begin(); ppNode != m_children.end(); ppNode++) 
		{
			OTLASSERT(*ppNode);
			nNodesToUpdate+= (*ppNode)->GetDeferWindowCount();
		}

		if(nNodesToUpdate<0) return FALSE;

		if(nNodesToUpdate>0) 
		{
			HDWP hDWP=::BeginDeferWindowPos(nNodesToUpdate);
			if(!hDWP) return FALSE;
			HDWP* phDWP=&hDWP;	// need double ptr, as handle may change...

			// recursively realize all children
			OTLNODELIST::iterator ppChild;
			for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
			{
				OTLASSERT(*ppChild);
				COtlLayoutNode* pNode = *ppChild;
				pNode->RealizeNodeHelper(phDWP,hDC);

				// Save the old rectangle to calculate minimum flicker invalidation
				RECT r;
				pNode->GetOldRect(&r);
				pNode->SetInvalidateRect(r);
				pNode->GetCurrentRect(&r);
				pNode->SetOldRect(r);
			}

			// End the update (pointer may have changed inside RealizeNodeHelper)
			hDWP=*phDWP;
			::EndDeferWindowPos(hDWP);


		}

		// If optimized redraw is set, we must manually iterate through all nodes,
		// erasing and redrawing only mimimal necessary changes. Much smoother, but
		// also more CPU intensive (and may not work properly for misbehaving nodes).
		// Invalidate only those branches which are colored "dirty"

		// Scan this and all child nodes for optimized redraw invalidations
		// (optimized redraw can be set on a per-node basis)
		OptimizedRedrawHelper();
		return TRUE;

	}

	inline BOOL COtlLayoutNode::RealizeNodeHelper(HDWP* phDWP,HDC hDC) 
	{ 
		// recurse all children
		OTLNODELIST::iterator ppChild;
		for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
		{
			OTLASSERT(*ppChild);
			(*ppChild)->RealizeNodeHelper(phDWP, hDC);
		}
		return TRUE;
	}

	inline BOOL COtlLayoutNode::PerformInvalidation(BOOL bDoErase,BOOL bRecurseChildren) 
	{
		// Mark our visitation
		ClearInvalidateDirty();

		// Calculate optimized invalidation rects for this node (this code works well
		// in the generic sense since only dealing with abstract rectangles) and feed
		// to overrideable OnInvalidateRect for subclass specific invalidation.
		if(bDoErase) 
		{
			// We are erasing this pass. Calculate minimum eraseable invalidation 
			// rects to minimize flicker.
			if(m_dwExStyle & OTL_LNODE_EX_OPTIMIZE_REDRAW)
				 EraseInvalidRects();
			else 
			{ 
				RECT r;
				GetCurrentRect(&r);
				OnInvalidateRect(r, TRUE);
			}
		}
		else 
		{
			// If not erasing, we are drawing. Use current rect to redraw node.
			RECT r;
			GetCurrentRect(&r);
			OnInvalidateRect(r, FALSE);
		}

		if(bRecurseChildren) 
		{
			OTLNODELIST::iterator ppChild;
			for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
			{
				OTLASSERT(*ppChild);
				(*ppChild)->PerformInvalidation(bDoErase,FALSE);
			}
		}
		return TRUE;
	}

	inline void COtlLayoutNode::GetInvalidateRect(LPRECT lpRect)
	{
		OTLASSERT(lpRect);
		::CopyRect(lpRect, &m_rectInvalidate);
	}

	inline void COtlLayoutNode::EraseInvalidRects() 
	{
		OTLASSERT(m_dwExStyle & OTL_LNODE_EX_OPTIMIZE_REDRAW);

		RECT rectInvalidate;
		GetInvalidateRect(&rectInvalidate);
		RECT rectCurrent;
		GetCurrentRect(&rectCurrent);

		RECT rect;
		if(rectInvalidate.top<rectCurrent.top) 
		{
			::CopyRect(&rect, &rectInvalidate);
			rect.bottom=rectCurrent.top;
			OnInvalidateRect(rect,TRUE);
		}
		if(rectInvalidate.left<rectCurrent.left) 
		{
			::CopyRect(&rect, &rectInvalidate);
			rect.right=rectCurrent.left;
			OnInvalidateRect(rect,TRUE);
		}
		if(rectInvalidate.right>rectCurrent.right) 
		{
			::CopyRect(&rect, &rectInvalidate);
			rect.left=rectCurrent.right;
			OnInvalidateRect(rect,TRUE);
		}
		if(rectInvalidate.bottom>rectCurrent.bottom) 
		{
			::CopyRect(&rect, &rectInvalidate);
			rect.top=rectCurrent.bottom;
			OnInvalidateRect(rect,TRUE);
		}
	}

	inline void COtlLayoutNode::OnInvalidateRect(const RECT& rectInvalid,BOOL bDoErase) 
	{
		rectInvalid;		// unreferenced
		bDoErase;			// unreferenced
	}


	inline void COtlLayoutNode::OnApplyOverrides(const RECT& rectOld, RECT& rectNew)
	{
		if(m_dwExStyle & OTL_LNODE_EX_NOSIZE_HORZ)
			rectNew.right=rectNew.left+ OtlRectWidth(rectOld);
		if(m_dwExStyle & OTL_LNODE_EX_NOSIZE_VERT) 
			rectNew.bottom=rectNew.top+OtlRectHeight(rectOld);
		if(m_dwExStyle & OTL_LNODE_EX_NOMOVE_HORZ) 
			rectNew.left=rectOld.left;
		if(m_dwExStyle & OTL_LNODE_EX_NOMOVE_VERT) 
			rectNew.top=rectOld.top;
	}


	inline void COtlLayoutNode::SetMinMaxSize(int cxMin, int cyMin, int cxMax, int cyMax, DWORD dwFlags)
	{
		SIZE sizeMin;
		sizeMin.cx = cxMin;
		sizeMin.cy = cyMin;
		SIZE sizeMax;
		sizeMax.cx = cxMax;
		sizeMax.cy = cyMax;
		SetMinMaxSize(sizeMin, sizeMax, dwFlags);
	}

	inline void COtlLayoutNode::SetMinMaxSize(const SIZE& sizeMin,const SIZE& sizeMax,DWORD dwFlags)
	{
		m_sizeMin=sizeMin;
		m_sizeMax=sizeMax;
		m_dwMinMaxFlags=dwFlags;

		// Minimum must not be larger than maximum!
	#ifdef _DEBUG
		if((!(dwFlags & OTL_LNODE_NO_MINSIZE))&&
		   (!(dwFlags & OTL_LNODE_NO_MAXSIZE))) {
			OTLASSERT(m_sizeMin.cx<=m_sizeMax.cx);
			OTLASSERT(m_sizeMin.cy<=m_sizeMax.cy);
			}
	#endif

	}

	inline void COtlLayoutNode::GetMinMaxSize(SIZE& sizeMin, SIZE& sizeMax, DWORD& dwFlags)
	{
		sizeMin=m_sizeMin;
		sizeMax=m_sizeMax;
		dwFlags=m_dwMinMaxFlags;	
	}

	inline void COtlLayoutNode::SetNodeExStyle(DWORD dwExStyle,BOOL bRecurseChildren)
	{
		m_dwExStyle=dwExStyle;
		if(bRecurseChildren)
		{
			OTLNODELIST::iterator ppChild;
			for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
			{
				OTLASSERT(*ppChild);
				(*ppChild)->SetNodeExStyle(dwExStyle,FALSE);
			}
		}
		
	}
	
	// find a child with the given window control id
	inline COtlLayoutNode* COtlLayoutNode::FindChild( int nCtrlID )
	{ 
		OTLNODELIST::iterator ppChild;
		COtlLayoutNode* pNode = 0;
		for(ppChild = m_children.begin(); ppChild != m_children.end(); ppChild++) 
		{
			OTLASSERT(*ppChild);
			pNode = *ppChild;
			if(nCtrlID == pNode->GetCtrlID())
				return pNode;
		}

		return NULL;
	}

	inline BOOL COtlLayoutNode::WithinSizeLimits(DWORD dwDrawAspect, SIZEL *psizel)
	{
		if(dwDrawAspect == DVASPECT_CONTENT )
		{
			SIZE sizeMin;
			SIZE sizeMax;
			DWORD dwFlags;
			GetMinMaxSize(sizeMin, sizeMax, dwFlags);
			AtlPixelToHiMetric(&sizeMin, &sizeMin);
			AtlPixelToHiMetric(&sizeMax, &sizeMax);
			if(!(dwFlags & OTL_LNODE_NO_MINSIZE))	// check minimum
			{
				if( psizel->cx < sizeMin.cx)
					return FALSE;
				if( psizel->cy < sizeMin.cy)
					return FALSE;

			}
			if(!(dwFlags & OTL_LNODE_NO_MAXSIZE))	// check maximum
			{
				if( psizel->cx > sizeMax.cx)
					return FALSE;
				if( psizel->cy > sizeMax.cy)
					return FALSE;
			}

		}
		return TRUE;
	}

};	// namespace StingrayOTL

#endif // __OTLLAYOUTNODE_H__
