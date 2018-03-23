///////////////////////////////////////////////////////////////////////////////
// WindowNode.h : SFL Layout Manager
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
// Description:  SFL Layout Manager: Window layout node
//

#pragma once

#if !defined(_SFL)
#define _SFL
#endif

#include <foundation\Layout\LayoutNode.h>
#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc


//@class CWindowLayoutNode |
// Implements a reactive node associated with a child window. 
// Layout operations are translated to Windows API calls to move or resize the
// associated window.
//@base public | CLayoutNode<ILayoutNode>
//@supint ILayoutNode | Basic layout node interface.
class __declspec(uuid("8B1647C2-45E5-11d3-9D92-00C04F91E286")) CWindowLayoutNode : 
	public CLayoutNode<CWindowLayoutNode, ILayoutNode> 
{
public:
	// Initialization/Destruction
	CWindowLayoutNode()
		: m_hNodeWnd(NULL),	m_hParentWnd(NULL), m_bIsActiveX(false) {}
	virtual ~CWindowLayoutNode() {}

	// ILayoutNode interface

	virtual bool IsNodeAttached() const
	{return (m_hNodeWnd != 0);}

	virtual long GetNodeId() const
	{
		return ::GetWindowLong(m_hNodeWnd, GWL_ID);
	}

	inline virtual int GetDeferWindowCount() const;

	inline virtual void Init(HWND hwndParent, HWND hwndChild = 0);
	inline virtual void Show(bool bShow = true);

protected:
	// Overridables	
	// Window invalidation is about to occur
	inline virtual void OnInvalidateRect(const CRect& rectInvalid, bool bDoErase);
	// Operations
	inline virtual bool OnRealizeNode(CLayoutTransaction& aTransaction);

protected:

	// Implementation Member Variables
	HWND m_hNodeWnd, m_hParentWnd;
	bool m_bIsActiveX;

};

////////////////////////////////////////////////

// Bridges a WIN32 window into the layout framework, via the inherited ILayoutNode interface.
void 
CWindowLayoutNode::Init (
						 HWND hwndParent, 
						 HWND hwndChild
						 )
{
	if (!hwndParent || !hwndChild) {
		return;
	}
	// If this ASSERT fires, you are attempting to attach
	// a window more than once. The window can be attached
	// either through this member, or the constructor.
	// ASSERT(!IsNodeAttached());

	// test for ActiveX control
	/* MFCism
	m_bIsActiveX = (CWnd::FromHandle(hWnd)->GetControlUnknown() != NULL);
	*/

	if (::IsWindow(hwndParent)) {
		m_hParentWnd = hwndParent;
	}

	if (::IsWindow(hwndChild)) {
		m_hNodeWnd = hwndChild;
		CRect rectInitial(0, 0, 0, 0);
		if (!::GetWindowRect(m_hNodeWnd, &rectInitial)) {
			return;
		}
		::ScreenToClient(m_hParentWnd, &rectInitial.TopLeft());
		::ScreenToClient(m_hParentWnd, &rectInitial.BottomRight());
		SetInitialRect(rectInitial);
	}
}

void CWindowLayoutNode::Show (
							  bool bShow
							  )
{

	_ASSERTE(m_hNodeWnd);
	::ShowWindow(m_hNodeWnd, bShow? SW_SHOWNORMAL : SW_HIDE);
	_LayoutBase::Show(bShow);
}

int 
CWindowLayoutNode::GetDeferWindowCount (
										) const
{  
	int nNumWindows = 1;	// self
	Children::const_iterator i;
	for (i = m_Children.begin(); i != m_Children.end(); ++i) {
		nNumWindows += (*i)->GetDeferWindowCount();
	}
	return nNumWindows;
}

// Apply the latest rectangle setting to the screen
// Note: the phDWP double ptr is a link to the
// DeferWindowPos pointer that must be propagated
bool 
CWindowLayoutNode::OnRealizeNode ( CLayoutTransaction& aTransaction )
{
	// Node must be attached!
	_ASSERTE(IsNodeAttached());

	// If userdata ptr defined, we can exploit DeferWindowPos
	// for clean, flicker-free screen updating
	CRect rcCurrent = GetCurrentRect();

	if (!m_bIsActiveX) {
		// Each subclass of CLayoutNode can handle optimization in its
		// own way (or ignore it altogether). 
		// For windows, it is best to not redraw the window on position change, 
		// then invalidate the minimum changed area to prevent flicker 
		// (performed in OnInvalidateRect below)
		DWORD dwSWPFlags = SWP_NOZORDER;	// maintain existing tab order
		if (m_dwExStyle & OptimizeRedraw) {
			dwSWPFlags |= SWP_NOREDRAW;
		}

		if (aTransaction.IsValid() /*false*/) {
			aTransaction.DeferWindowPos(m_hNodeWnd, NULL, rcCurrent, dwSWPFlags);
		}

		// Otherwise, ol flicker-face for you...
		else {
			if (!SetWindowPos(m_hNodeWnd, NULL, rcCurrent.left, rcCurrent.top,
				rcCurrent.Width(), rcCurrent.Height(), dwSWPFlags)) {
					return false;
			}
		}	
	}

	// Use base class to realize children
	return _LayoutBase::OnRealizeNode(aTransaction);
}


// Custom invalidation optimizations
void 
CWindowLayoutNode::OnInvalidateRect (
									 const CRect& rectInvalid,
									 bool bDoErase
									 )
{
	if ((!m_hParentWnd) || (!IsNodeAttached())) {
		return;
	}
	if (bDoErase) {
		::InvalidateRect(m_hParentWnd, rectInvalid, true);
	}
	else {
		RedrawWindow(m_hNodeWnd, NULL, NULL, RDW_INVALIDATE);
	}
}

};	// namespace stingray::foundation
};	// namespace stingray

