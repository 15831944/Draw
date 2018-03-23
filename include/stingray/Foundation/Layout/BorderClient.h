///////////////////////////////////////////////////////////////////////////////
// BorderClient.h : SFL Layout Manager
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
// Author:       Gilberto Araya
// Description:  SFL Layout Manager Border Client algorithm: generic frame layout
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#pragma warning (push)
#pragma warning (disable: 4996)

#include <foundation\Layout\LayoutNode.h>
#include <foundation\Util\TransRect.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc

//////////////////////////////////////////////////////////////////////////////
// IBorderClientLayout interface


//@interface IBorderClientLayout |
// Support for the special layout arrangement often encountered in frame windows,
// where there are four special areas attached to the borders of the window called the
// borders, and a space between them called the client area.<nl>
// IBorderClient interface provides the necessary additional functionality to implement
// such arrangement.
//@base public | ILayoutNode
interface __declspec(uuid("C86E1620-5EDD-11d3-9D9A-00C04F91E286")) IBorderClientLayout:
	public ILayoutNode
{
public:

	//@cmember,menum | BorderPosition | |
	// Identify the specific areas designated in the 
	// Border-Client arrangement.
	FOUNDATION_API enum BorderPosition 
	{ 
		Top = 0x01,		//@@emem Top border
		Bottom = 0x02,	//@@emem Bottom border
		Left = 0x04,	//@@emem Left border
		Right = 0x08,	//@@emem Right border
		Client = 0x10	//@@emem Client area
	};

	//@cmember,menum | BorderAlgorithm | |
	// Defines whether the horizontal borders take precedence
	// over the vertical ones or vice-versa.
	FOUNDATION_API enum BorderAlgorithm 
	{
		TopBottomLeftRight,		//@@emem Horizontal borders get priority, then vertical
		LeftRightTopBottom		//@@emem Vertical borders get priority, then horizontal
	};

public:

	//@meth,method int | AddLayoutNode | 
	// Adds a child layout node to this node's children list.
	//@@rdesc Returns the new number of child nodes in this node's children list.
	//@@parm ILayoutNode* | pNode | Node being added.
	//@@parm BorderPosition | position | Area of the Border-Client arrangement the new node will be responsible for.
	//  Must be a member of the BorderPosition enumerated type.
	//@@comm This is a variation of the <mf ILayoutNode::AddLayoutNode> method, that takes a second
	// parameter specifying the area the node being aggregated will occupy. The
	// <mf ILayoutNode::AddLayoutNode> version should not be used with BorderClient nodes,
	// as it does not allow specifying this important piece of information.
	 virtual int AddLayoutNode(ILayoutNode* pNode, BorderPosition position) = 0;

	//@prop,property BorderAlgorithm | Get/SetBorderAlgorithm | 
	//  Defines whether the horizontal borders take precedence
	//  over the vertical ones or vice-versa.
	 virtual void SetBorderAlgorithm(BorderAlgorithm alg) = 0;
	 virtual BorderAlgorithm GetBorderAlgorithm() const = 0;

	//@meth,method bool | LocatePositionFromNode |
	//  Given a layout node, returns the position that node is currently occupying
	//  within the Border-Client designated areas.
	//@@rdesc true if pNode was occupying one of the five designated areas within the Border-Client
	// arrangement. false if the node was not found.
	//@@parm ILayoutNode* | pNode | Node to locate position of.
	//@@parm BorderPosition& | position | Output parameter, which upon return contains the position
	// pNode is located at. Valid only if the return value is true.
	 inline virtual bool LocatePositionFromNode(ILayoutNode* pNode, BorderPosition& position) const = 0;

	//@meth,method ILayoutNode* | LocateNodeFromPosition |
	//  Returns the layout node located at the position indicated.
	//@@rdesc Pointer to the node located at the area indicated by the position parameter. NULL if there
	// is no node assigned to that area.
	//@@parm BorderPosition | position | Area being queried.
	 inline virtual ILayoutNode* LocateNodeFromPosition(BorderPosition position) const = 0;
};



//////////////////////////////////////////////////////////////////////////////
// CBorderClientLayout class


//@class CBorderClientLayout |
/* 
   Implementation of the Border-Client layout arrangement.<nl>
   The Border-Client Layout implements the typical arrangement found in frame windows,
   where there are four designated areas attached to each border of the window, where items 
   like toolbars and status bars are usually placed; and a rectangular space between these 
   "borders" generally called the "client" area.
*/
//@base public | CLayoutNode<lt>IBorderClientLayout <gt>
//@supint ILayoutNode | Basic layout node interface.
//@supint IBorderClientLayout | Specialized functionality for management of the Border-Client arrangement.
class __declspec(uuid("C86E1621-5EDD-11d3-9D9A-00C04F91E286")) CBorderClientLayout:
	public CLayoutNode<CBorderClientLayout, IBorderClientLayout>
{
public:
	* CBorderClientLayout(): 	m_pNodeTop(NULL), m_pNodeBottom(NULL), 
											m_pNodeLeft(NULL), m_pNodeRight(NULL), 
											m_pNodeClient(NULL), m_BorderAlg(TopBottomLeftRight) {}


public:
	
	// IBorderClientLayout interface

	inline virtual int AddLayoutNode(ILayoutNode* pNode, BorderPosition position);

	inline void SetBorderAlgorithm(BorderAlgorithm alg) { m_BorderAlg = alg; }
	inline BorderAlgorithm GetBorderAlgorithm() const { return m_BorderAlg; }

	inline virtual bool LocatePositionFromNode(ILayoutNode* pNode, BorderPosition& position) const;
	inline virtual ILayoutNode* LocateNodeFromPosition(BorderPosition position) const;


	// ILayoutNode interface
	inline virtual int AddLayoutNode (ILayoutNode* pNode);
	inline virtual int RemoveLayoutNode(ILayoutNode* pNode);
	inline virtual CRect OnRecalcLayout(const CRect& rcDesired, bool bChildNegotiate, bool bStrictRecalc);


protected:
	ILayoutNode* m_pNodeTop;
	ILayoutNode* m_pNodeBottom;
	ILayoutNode* m_pNodeLeft;
	ILayoutNode* m_pNodeRight;
	ILayoutNode* m_pNodeClient;

	BorderAlgorithm m_BorderAlg;

protected:

	// Implementation helpers
	 inline BorderPosition GetAutoInsertPosition() const;

	// Layout Calculation Logic
	 inline virtual void ApplyChildNodeRects(const CRect& rcClient, const CRect& rcTop, const CRect& rcBottom, const CRect& rcLeft, const CRect& rcRight);
	 inline virtual CRect RecalcBorderRects(const CRect& rcParent, CRect& rcTop, CRect& rcBottom, CRect& rcLeft, CRect& rcRight);
	 inline virtual CRect CalcClientRect(CRect rcTop, CRect rcBottom, CRect rcLeft, CRect rcRight) const;
	 inline virtual void GetBorderRects(CRect& rcTop, CRect& rcBottom, CRect& rcLeft, CRect& rcRight) const;
	 inline virtual void GetAdjustedBorderRect(ILayoutNode* pNode, CRect& rcNode) const;
	 inline virtual bool SetClientRectWithinMinMax(const CRect& rcParent, CRect& rcClient, CRect& rcTop, CRect& rcBottom, CRect& rcLeft, CRect& rcRight);
	 inline virtual void AdjustClientRectOneDimension(ILayoutNode* pBorderBefore, ILayoutNode* pBorderAfter, const CRect& rcParent, CRect& rcClient, int nDelta, bool bHorzAdjust);
	 inline virtual void ResetNodeRectsAroundClient(const CRect& rcClient, CRect& rcTop, CRect& rcBottom, CRect& rcLeft, CRect& rcRight);
	 inline virtual bool NegotiatePreferredChildNodeRects(const CRect& rcParent, CRect& rcTop, CRect& rcBottom, CRect& rcLeft, CRect& rcRight);

};

// Normalize the size to fit, if too large
inline
float NormalizeBorderSizeIfTooLarge (
									 int nFitSize,
									 int nSize1,
									 int nSize2
									 )
{
	if (nFitSize < 0) {
		return 0.0f;
	}

	int nSum = nSize1 + nSize2;
	float fScaleFactor = 1.0f;
	if (nSum > 0 && nSum > nFitSize) {
		fScaleFactor = (static_cast<float>(nFitSize)) / (static_cast<float>(nSum));
	}

	return fScaleFactor;
}

inline
void BoundClientInsideParent (
							  CRect& rcClient,
							  const CRect& rcParent
							  ) 
{
	rcClient.left	= _SFLMAX(rcClient.left, rcParent.left);
	rcClient.right	= _SFLMIN(rcClient.right, rcParent.right);
	rcClient.top	= _SFLMAX(rcClient.top, rcParent.top);
	rcClient.bottom = _SFLMIN(rcClient.bottom, rcParent.bottom);
}

inline
int CBorderClientLayout::AddLayoutNode (
										ILayoutNode* pNode
										)
{
	return AddLayoutNode(pNode, GetAutoInsertPosition());
}

inline
int CBorderClientLayout::AddLayoutNode (ILayoutNode* pNode, BorderPosition position)
{
	if (!pNode) {
		return -1;
	}

	// Insertion validation checks
	{
		// Node should not already exist as a child!
		BorderPosition pos;
		if (LocatePositionFromNode(pNode, pos)) {
			throw std::runtime_error("");
		}
		// And the insertion position should not already be configured (remove first!)
		if (LocateNodeFromPosition(position)) {
			throw std::runtime_error(_T("Position occupied"));
		}
	}

	// Add to the base class first
	int rc = _LayoutBase::AddLayoutNode(pNode);
	if (rc == -1) {
		return -1;
	}

	// Add border node
	if (position == Top) {
		_ASSERTE(!m_pNodeTop);
		m_pNodeTop = pNode;
	}
	else if (position == Bottom) {
		_ASSERTE(!m_pNodeBottom);
		m_pNodeBottom = pNode;
	}		
	else if (position == Left) {
		_ASSERTE(!m_pNodeLeft);
		m_pNodeLeft = pNode;
	}
	else if (position == Right) {
		_ASSERTE(!m_pNodeRight);
		m_pNodeRight = pNode;
	}
	else if (position == Client) {
		_ASSERTE(!m_pNodeClient);
		m_pNodeClient = pNode;
	}
	else {
		// This code should be unreachable!
		_ASSERTE(false);
	}

	return rc;
}

inline
int CBorderClientLayout::RemoveLayoutNode(ILayoutNode* pNode)
{
	int rc = _LayoutBase::RemoveLayoutNode(pNode);
	if (rc == -1) {
		return rc;
	}

	if (pNode == m_pNodeTop) {
		m_pNodeTop = NULL;
	}
	else if (pNode == m_pNodeBottom) {
		m_pNodeBottom = NULL;
	}
	else if (pNode == m_pNodeLeft) {
		m_pNodeLeft = NULL;
	}
	else if (pNode == m_pNodeRight) {
		m_pNodeRight = NULL;
	}
	else if (pNode == m_pNodeClient) {
		m_pNodeClient = NULL;
	}
	else {
		_ASSERTE(false);
	}

	return rc;
}

inline
bool CBorderClientLayout::LocatePositionFromNode(ILayoutNode* pNode, BorderPosition& position) const
{
	if (!pNode) {
		return false;
	}

	if (pNode == m_pNodeTop) {
		position = Top;
	}
	else if (pNode == m_pNodeBottom) {
		position = Bottom;
	}
	else if (pNode == m_pNodeLeft) {
		position = Left;
	}
	else if (pNode == m_pNodeRight) {
		position = Right;
	}
	else if (pNode == m_pNodeClient) {
		position = Client;
	}
	else {
		return false;
	}

	return true;
}

inline
ILayoutNode* CBorderClientLayout::LocateNodeFromPosition(BorderPosition position) const
{
	ILayoutNode* pNode = NULL;

	if (position == Top) {
		pNode = m_pNodeTop;
	}
	else if (position == Bottom) {
		pNode = m_pNodeBottom;
	}
	else if (position == Left) {
		pNode = m_pNodeLeft;
	}
	else if (position == Right) {
		pNode = m_pNodeRight;
	}
	else if (position == Client) {
		pNode = m_pNodeClient;
	}

	return pNode;
}

inline
CRect CBorderClientLayout::OnRecalcLayout(const CRect& rcDesired, bool bChildNegotiate, bool /*bStrictRecalc*/)
{

	// Cache the starting client rect
	CRect rcClientBeforeRecalc(0,0,0,0);
	if (m_pNodeClient) {
		rcClientBeforeRecalc = m_pNodeClient->GetCurrentRect();
	}
	// Properly resolve the node rect within a positive rectangle.
	CRect rcParent = rcDesired;
	if (rcParent.right < rcParent.left) {
		rcParent.right = rcParent.left;
	}
	if (rcParent.bottom < rcParent.top) {
		rcParent.bottom = rcParent.top;
	}

	// Calculate the optimal position of the L,T,R,B border nodes.
	CRect rcTop(0, 0, 0, 0), rcBottom(0, 0, 0, 0), rcLeft(0, 0, 0, 0), rcRight(0, 0, 0, 0);
	CRect rcClient = RecalcBorderRects(rcParent, rcTop, rcBottom, rcLeft, rcRight);

	// Set the client rect within it's min/max constraints, 
	// adjusting the border rects as appropiate to compensate.
	SetClientRectWithinMinMax(rcParent, rcClient, rcTop, rcBottom, rcLeft, rcRight);

	// If child negotiation enabled, negotiate with children their preferred node rects.
	if (bChildNegotiate) {
		if (NegotiatePreferredChildNodeRects(rcParent, rcTop, rcBottom, rcLeft, rcRight)) {
			// Recalc the child rect
			rcClient = CalcClientRect(rcTop, rcBottom, rcLeft, rcRight);
			SetClientRectWithinMinMax(rcParent, rcClient, rcTop, rcBottom, rcLeft, rcRight);
		}
	}

	// And finally, apply these calculated settings to all the child nodes.
	ApplyChildNodeRects(rcClient, rcTop, rcBottom, rcLeft, rcRight);

	// If client rect changed, notify the event receiver
	//
	//if (m_pNodeClient && m_pEventRcvr && rcClientBeforeRecalc!=rcClient)
	//	m_pEventRcvr->OnClientRectChanged(rcClient);

	return rcParent;
}

// Apply new child rects.
inline
void CBorderClientLayout::ApplyChildNodeRects (
	const CRect& rcClient,
	const CRect& rcTop,
	const CRect& rcBottom,
	const CRect& rcLeft,
	const CRect& rcRight
	)
{
	if (m_pNodeClient) {
		m_pNodeClient->RecalcLayout(rcClient, false, true);
	}
	if (m_pNodeTop) {
		m_pNodeTop->RecalcLayout(rcTop, false, true);
	}
	if (m_pNodeBottom) {
		m_pNodeBottom->RecalcLayout(rcBottom, false, true);
	}
	if (m_pNodeLeft) {
		m_pNodeLeft->RecalcLayout(rcLeft, false, true);
	}
	if (m_pNodeRight) {
		m_pNodeRight->RecalcLayout(rcRight, false, true);
	}
}


// Recalcs the positions of the top, bottom, left, right border nodes,
// and returns the resultant client rect.
inline
CRect CBorderClientLayout::RecalcBorderRects (
	const CRect& rcParent,
	CRect& rcTop,
	CRect& rcBottom,
	CRect& rcLeft,
	CRect& rcRight
	)
{	
	GetBorderRects(rcTop, rcBottom, rcLeft, rcRight);

	// Set top/bottom nodes. If cumulative height is too large, normalize.
	float fNormalizeFactorHeight = NormalizeBorderSizeIfTooLarge(rcParent.Height(), rcTop.Height(), rcBottom.Height());
	float fNormalizeFactorWidth = NormalizeBorderSizeIfTooLarge(rcParent.Width(), rcLeft.Width(), rcRight.Width());

	CSize szTopLeft(static_cast<int>(rcLeft.Width()*fNormalizeFactorWidth), static_cast<int>(rcTop.Height()*fNormalizeFactorHeight));
	CSize szBottomRight(static_cast<int>(rcRight.Width()*fNormalizeFactorWidth), static_cast<int>(rcBottom.Height()*fNormalizeFactorHeight));

	// Adjust size of rectangles
	rcTop = rcParent;
	rcTop.bottom = rcTop.top + szTopLeft.cy;
	rcBottom = rcParent;
	rcBottom.top = rcBottom.bottom - szBottomRight.cy;
	rcLeft = rcParent;
	rcLeft.right = rcLeft.left + szTopLeft.cx;
	rcRight = rcParent;
	rcRight.left = rcRight.right - szBottomRight.cx;

	// Bound the less priority dimension to the other one, according to the algorithm
	if (m_BorderAlg == TopBottomLeftRight) {
		rcRight.top = rcLeft.top = rcTop.bottom;
		rcRight.bottom = rcLeft.bottom = rcBottom.top;
	}
	else if (m_BorderAlg == LeftRightTopBottom) {
		rcBottom.left = rcTop.left = rcLeft.right;
		rcBottom.right = rcTop.right = rcRight.left;
	}

	CRect rcClient = CalcClientRect(rcTop, rcBottom, rcLeft, rcRight);
	return rcClient;
}

inline
void CBorderClientLayout::GetBorderRects (
	CRect& rcTop,
	CRect& rcBottom,
	CRect& rcLeft,
	CRect& rcRight
	) const
{
	// Get the desired border rects
	rcTop = rcBottom = rcLeft = rcRight = CRect(0,0,0,0);
	GetAdjustedBorderRect(m_pNodeTop, rcTop);
	GetAdjustedBorderRect(m_pNodeBottom, rcBottom);
	GetAdjustedBorderRect(m_pNodeLeft, rcLeft);
	GetAdjustedBorderRect(m_pNodeRight, rcRight);
}

inline
void CBorderClientLayout::GetAdjustedBorderRect (
	ILayoutNode* pNode,
	CRect& rcNode
	) const
{
	if(!pNode) {
		return;
	}

	if (pNode->IsVisible()) {
		// Load preferred rect for best fit. This will allow border nodes to
		// "bounce back" to preferred rect sizes as parent is sized very small,
		// then restored back (provided the node has set its preferred rect properly)
		pNode->GetPreferredRect(rcNode);

		// But make sure preferred rect is within min/max range.
		pNode->FitRectWithinNodeMinMax(rcNode);
	}
	else {
		rcNode.SetRectEmpty();
	}
}


// Based on the 4 node rects passed in, derive the resultant
// client rect that would be located within these nodes.
inline
CRect CBorderClientLayout::CalcClientRect (
	CRect rcTop,
	CRect rcBottom,
	CRect rcLeft,
	CRect rcRight
	) const
{
	// Derive the resultant client rect.
	CRect rcClient;
	rcClient.top = rcTop.bottom;
	rcClient.bottom = rcBottom.top;
	rcClient.left = rcLeft.right;
	rcClient.right = rcRight.left;

	// Data validation
	_ASSERTE(rcClient.left >= 0);
	_ASSERTE(rcClient.top >= 0);
	_ASSERTE(rcClient.right >= rcClient.left);
	_ASSERTE(rcClient.bottom >= rcClient.top);

	return rcClient;
}


// Set the client rect within the node's preset min/max settings,
// compensating by adjusting the surrounding border node rects.
inline
bool CBorderClientLayout::SetClientRectWithinMinMax (
	const CRect& rcParent,
	CRect& rcClient,
	CRect& rcTop,
	CRect& rcBottom,
	CRect& rcLeft,
	CRect& rcRight
	)
{
	if(!m_pNodeClient) {
		return false;
	}

	DWORD dwFlags;
	CSize szMin(0, 0), szMax(0, 0);
	CSize szDelta(0, 0);

	// Query the current min/max settings
	m_pNodeClient->GetMinMaxSize(szMin, szMax, dwFlags); 

	// Fit client within max size first
	if (!(dwFlags & NoMaxSize)) {
		if (rcClient.Width() > szMax.cx) {
			// Client too wide. Shorten, and adjust left/right
			szDelta.cx += (szMax.cx - rcClient.Width());
		}
		if(rcClient.Height() > szMax.cy) {
			// Client too tall. Shorten, and adjust top/bottom
			szDelta.cy += (szMax.cy - rcClient.Height());
		}
	}

	// Fit within min size second
	if (!(dwFlags & NoMinSize)) {
		if (rcClient.Width() < szMin.cx) {
			// Client not wide enough. Lengthen, and adjust left/right
			szDelta.cx += (szMin.cx - rcClient.Width());
		}
		if (rcClient.Height() < szMin.cy) {
			// Client not tall enough. Lengthen, and adjust top/bottom
			szDelta.cy += (szMin.cy - rcClient.Height());
		}
	}

	// Apply this delta to the client rect, while truncating within parent.
	AdjustClientRectOneDimension(m_pNodeLeft, m_pNodeRight, rcParent, rcClient, szDelta.cx, true);
	AdjustClientRectOneDimension(m_pNodeTop, m_pNodeBottom, rcParent, rcClient, szDelta.cy, false);

	// Insure the client is always properly bounded within the parent rect.
	BoundClientInsideParent(rcClient, rcParent);

	// And finally adjust the border rects around the new client.
	ResetNodeRectsAroundClient(rcClient, rcTop, rcBottom, rcLeft, rcRight);

	return TRUE;
}


// Adjust the client rect, based on the delta passed in, in 1 dimension
// (horz or vert). This function will not adjust the surrounding border rects.
inline
void CBorderClientLayout::AdjustClientRectOneDimension (
	ILayoutNode* pBorderBefore,
	ILayoutNode* pBorderAfter,
	const CRect& rcParent,
	CRect& rcClient,
	int nDelta,
	bool bHorzAdjust
	)
{
	if (nDelta == 0) {
		return;
	}
	// Use Transposable Rect for orientation-generic logic.
	CTransposableRect rcSParent(rcParent, bHorzAdjust);
	CTransposableRect rcSClient(rcClient, bHorzAdjust);

	// Give half to the left border, if present.
	if (pBorderBefore) {
		// Reset prev client border
		int nOriginalBorder = rcSClient.GetLT();
		rcSClient.LT(rcSClient.GetLT() - nDelta/2);
		rcSClient.LT(_SFLMAX(rcSClient.GetLT(), rcSParent.GetLT()));
		nDelta -= (nOriginalBorder - rcSClient.GetLT());
	}
	else {
		// already flush with parent
		_ASSERTE(rcSClient.GetLT() == rcSParent.GetLT()); 
	} 

	// Give the rest to right border, if present.
	if (pBorderAfter) {
		// Reset following client border
		int nOriginalBorder = rcSClient.GetRB();
		rcSClient.RB(rcSClient.GetRB() + nDelta);
		rcSClient.RB(_SFLMIN(rcSClient.GetRB(), rcSParent.GetRB()));
		nDelta -= (rcSClient.GetRB() - nOriginalBorder);
	}
	else {
		// already flush with parent
		_ASSERTE(rcSClient.GetRB() == rcSParent.GetRB()); 
	}

	// If still have pixels to allocate, try again on left side.
	if (nDelta!=0) {
		rcSClient.LT(rcSClient.GetLT() - nDelta);
	}

	// Apply the results back to the client reference to return.
	rcClient = rcSClient;
}


// Reset the border node rects to be properly contained by the new client.
inline
void CBorderClientLayout::ResetNodeRectsAroundClient (
	const CRect& rcClient,
	CRect& rcTop,
	CRect& rcBottom,
	CRect& rcLeft,
	CRect& rcRight
	)
{
	// Algorithm generic settings
	rcLeft.right = rcClient.left;
	rcRight.left = rcClient.right;
	rcTop.bottom = rcClient.top;
	rcBottom.top = rcClient.bottom;

	// Algorithm specific settings
	if (m_BorderAlg==TopBottomLeftRight) {
		rcLeft.top = rcTop.bottom;
		rcLeft.bottom = rcBottom.top;
		rcRight.top = rcTop.bottom;
		rcRight.bottom = rcBottom.top;
	}
	else {
		rcTop.left = rcLeft.right;
		rcTop.right = rcRight.left;
		rcBottom.left = rcLeft.right;
		rcBottom.right = rcRight.left;
	}
}


// Negotiate with the child nodes for preferred layout positioning
// (implementation of the child negotiation RecalcLayout parm)
// Returns true if a change to 1 or more children occurred, otherwise false for no change.
inline
bool CBorderClientLayout::NegotiatePreferredChildNodeRects (
	const CRect& rcParent,
	CRect& rcTop,
	CRect& rcBottom,
	CRect& rcLeft,
	CRect& rcRight
	)
{
	// Only consider size changes suggested by children. Do not
	// reposition origin of child nodes.
	bool bChange = false;
	CRect rcChild(0, 0, 0, 0);

	if (m_pNodeTop) {
		rcChild = m_pNodeTop->RecalcLayout(rcTop, true, true);
		if (rcChild.Height() != rcTop.Height()) {
			bChange = true;
			rcTop.bottom = rcTop.top + rcChild.Height();
		}
		rcTop.bottom = _SFLMIN(rcTop.bottom, rcParent.bottom);	// don't size below parent bottom
	}
	if (m_pNodeBottom) {
		rcChild = m_pNodeBottom->RecalcLayout(rcBottom, true, true);
		if (rcChild.Height() != rcBottom.Height()) {
			bChange = true;
			rcBottom.top = rcBottom.bottom - rcChild.Height();
		}
		rcBottom.top = _SFLMAX(rcBottom.top, rcParent.top);	// don't size above parent top
		rcBottom.top = _SFLMAX(rcBottom.top, rcTop.bottom);	// don't size above top border
	}
	if (m_pNodeLeft) {
		rcChild = m_pNodeLeft->RecalcLayout(rcLeft, true, true);
		if (rcChild.Width() != rcLeft.Width()) {
			bChange = true;
			rcLeft.right = rcLeft.left + rcChild.Width();
		}
		rcLeft.right = _SFLMIN(rcLeft.right, rcParent.right);	// don't size beyond parent right		
	}
	if (m_pNodeRight) {
		rcChild = m_pNodeRight->RecalcLayout(rcRight, true, true);
		if (rcChild.Width() != rcRight.Width()) {
			bChange = true;
			rcRight.left = rcRight.right - rcChild.Width();
		}
		rcRight.left = _SFLMAX(rcRight.left, rcParent.left);	// don't size beyond parent left
		rcRight.left = _SFLMAX(rcRight.left, rcLeft.right);	// don't size beyond left border		
	}


	if (bChange) {

		if (m_BorderAlg == TopBottomLeftRight) {
			rcRight.top = rcLeft.top = rcTop.bottom;
			rcRight.bottom = rcLeft.bottom = rcBottom.top;
		}
		else { 
			rcBottom.left = rcTop.left = rcLeft.right;
			rcBottom.right =rcTop.right = rcRight.left;
		}

		// If all was done properly, border nodes should fall within the acceptable ranges asserted below.
		_ASSERTE(rcParent.top <= rcTop.top);
		_ASSERTE(rcTop.top <= rcTop.bottom);
		_ASSERTE(rcTop.bottom <= rcBottom.top);
		_ASSERTE(rcBottom.top <= rcBottom.bottom);
		_ASSERTE(rcBottom.bottom <= rcParent.bottom);

		_ASSERTE(rcParent.left <= rcLeft.left);
		_ASSERTE(rcLeft.left <= rcLeft.right);
		_ASSERTE(rcLeft.right <= rcRight.left);
		_ASSERTE(rcRight.left <= rcRight.right);
		_ASSERTE(rcRight.right <= rcParent.right);
	}

	return bChange;
}

inline
IBorderClientLayout::BorderPosition CBorderClientLayout::GetAutoInsertPosition (
	) const
{
	BorderPosition autoPos;

	if (m_BorderAlg == TopBottomLeftRight) 
	{
		if (!m_pNodeTop) {
			autoPos = Top;
		}
		else if (!m_pNodeBottom) {
			autoPos = Bottom;
		}
		else if (!m_pNodeLeft) {
			autoPos = Left;
		}
		else if (!m_pNodeRight) {
			autoPos = Right;
		}
		else if (!m_pNodeClient) {
			autoPos = Client;
		}
		else {
			throw std::runtime_error(_T("No other position available"));
		}
	}
	else {	
		// LeftRightTopBottom
		if (!m_pNodeLeft) {
			autoPos = Left;
		}
		else if (!m_pNodeRight)	{
			autoPos = Right;
		}
		else if (!m_pNodeTop) {
			autoPos = Top;
		}
		else if (!m_pNodeBottom) {
			autoPos = Bottom;
		}
		else if (!m_pNodeClient) {
			autoPos = Client;
		}
		else {
			throw std::runtime_error(_T("No other position available"));
		}
	}

	return autoPos;
}


};	// namespace stingray::foundation
};	// namespace stingray

#pragma warning (pop)
