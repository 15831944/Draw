///////////////////////////////////////////////////////////////////////////////
// OtlWindowNode.h
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

#ifndef __OTLWINDOWNODE_H__
#define __OTLWINDOWNODE_H__

#ifndef __OTLBASE_H__
	#error otlwindownode.h requires otlbase.h to be included first
#endif

#include <Toolkit\atl\otllayoutNode.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

/////////////////////////////////////////////////////////////////////////////
// COtlWindowNode
// a layout manager node that is a window

class COtlWindowNode : public COtlLayoutNode
{
public:
	COtlWindowNode();
	~COtlWindowNode();
public:
	BOOL AttachWnd(HWND hWnd,HWND hwndParent);
	void ReparentNodeHWND(HWND hWndparent);

// COtlLayoutNode overrides

	virtual int GetDeferWindowCount();
	virtual BOOL IsNodeAttached() {return m_hNodeWnd ? TRUE : FALSE;}
	virtual BOOL RealizeNodeHelper(HDWP* phDWP,HDC hDC);
	virtual void OnInvalidateRect(const RECT& rectInvalid,BOOL bDoErase);
	virtual void Show(BOOL bShow);
	virtual void SetNodeExStyle(DWORD dwExStyle=0,BOOL bRecurseChildren=FALSE);
	virtual int GetCtrlID();

public:
	HWND m_hNodeWnd;
	HWND m_hParentWnd;
};

inline COtlWindowNode::COtlWindowNode() 
{
	m_hNodeWnd=(HWND)NULL;
	m_hParentWnd=(HWND)NULL;
}

inline COtlWindowNode::~COtlWindowNode()
{
}

inline BOOL COtlWindowNode::AttachWnd(HWND hWnd,HWND hwndParent) 
{

	// If this ASSERT fires, you are attempting to attach
	// a window more than once.
	OTLASSERT(!IsNodeAttached());
	if((!hWnd)||(!hwndParent)) return FALSE;
	m_hNodeWnd=hWnd;
	m_hParentWnd=hwndParent;
	RECT rectInitial;
	if(!::GetWindowRect(m_hNodeWnd,&rectInitial)) return FALSE;
	CWindow wnd(m_hParentWnd);
	wnd.ScreenToClient(&rectInitial);
	SetInitialRect(rectInitial);

	return TRUE;
}

inline void COtlWindowNode::ReparentNodeHWND(HWND hWndParent) 
{
	OTLASSERT(m_hNodeWnd);
	m_hParentWnd=hWndParent;
	
	// Reset the child's parent link
	::SetParent(m_hNodeWnd,m_hParentWnd);
}

inline int COtlWindowNode::GetDeferWindowCount() 
{ 
	// ourselves and any children
	return 1 + COtlLayoutNode::GetDeferWindowCount();
}

// Apply the latest rectangle setting to the screen
// Note: the phDWP double ptr is a link to the
// DeferWindowPos pointer that must be propagated
inline BOOL COtlWindowNode::RealizeNodeHelper(HDWP* phDWP,HDC hDC) 
{
	// Node must be attached!
	OTLASSERT(IsNodeAttached());

	RECT rectCurrent;
	GetCurrentRect(&rectCurrent);


	DWORD dwSWPFlags=SWP_NOZORDER | SWP_NOACTIVATE;

	if(m_dwExStyle & OTL_LNODE_EX_OPTIMIZE_REDRAW)
		dwSWPFlags|=SWP_NOREDRAW;


	if((phDWP)&&(*phDWP)) 
	{
		*phDWP=DeferWindowPos(	*phDWP,
								m_hNodeWnd,
								NULL,
								rectCurrent.left,
								rectCurrent.top,
								OtlRectWidth(rectCurrent),
								OtlRectHeight(rectCurrent),
								dwSWPFlags);

		if(!(*phDWP)) return FALSE;
	}
	else	// we got a NULL HDWP, fall back on SetWindowPos
	{
		if(!SetWindowPos(	m_hNodeWnd,
							NULL,
							rectCurrent.left,
							rectCurrent.top,
							OtlRectWidth(rectCurrent),
							OtlRectHeight(rectCurrent),
							dwSWPFlags))
			return FALSE;


	}	

	// Use base class to realize children
	return COtlLayoutNode::RealizeNodeHelper(phDWP,hDC);
}

inline void COtlWindowNode::OnInvalidateRect(const RECT& rectInvalid,BOOL bDoErase) 
{
	if((!m_hParentWnd)||(!IsNodeAttached())) return;

	if(bDoErase)
		 ::InvalidateRect(m_hParentWnd, &rectInvalid,TRUE);
	else ::RedrawWindow(m_hNodeWnd,NULL,NULL,RDW_INVALIDATE | RDW_FRAME | RDW_ERASE);
}


inline void COtlWindowNode::Show(BOOL bShow)
{
	::ShowWindow(m_hNodeWnd, bShow ? SW_SHOW : SW_HIDE);
}

inline void COtlWindowNode::SetNodeExStyle(DWORD dwExStyle,BOOL bRecurseChildren)
{
	COtlLayoutNode::SetNodeExStyle(dwExStyle,bRecurseChildren);

	// is optimized redraw being set?
	if(m_dwExStyle & OTL_LNODE_EX_OPTIMIZE_REDRAW)
	{
		// if we are a group box, then don't allow optimization
		if(::IsWindow(m_hNodeWnd))
		{
			DWORD dwStyle = (DWORD)::GetWindowLong(m_hNodeWnd, GWL_STYLE);
			if((dwStyle & 0x0F) == BS_GROUPBOX)
				m_dwExStyle &= ~OTL_LNODE_EX_OPTIMIZE_REDRAW;
		}
	}

}


inline int COtlWindowNode::GetCtrlID() 
{ 
	if(!m_hNodeWnd)
		return 0;
	OTLASSERT(::IsWindow(m_hNodeWnd));
	return ::GetDlgCtrlID(m_hNodeWnd);
}


};	// namespace StingrayOTL

#endif // __OTLWINDOWNODE_H__
