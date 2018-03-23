///////////////////////////////////////////////////////////////////////////////
// gxwv.inl
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
// Author: Stefan Hoenig
//

#pragma once

#ifdef GX_INLINE

GX_INLINE void CGXGridView::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CGXView::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXGridView::Invalidate(BOOL bErase)
	{ CGXView::Invalidate(bErase); }

GX_INLINE void CGXGridView::UpdateWindow()
	{ CGXView::UpdateWindow(); }

GX_INLINE int CGXGridView::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CGXView::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXGridView::GetDC()
	{ return CGXView::GetDC(); }

GX_INLINE int CGXGridView::ReleaseDC(CDC* pDC)
	{ return CGXView::ReleaseDC(pDC); }

GX_INLINE void CGXGridView::GetClientRect(LPRECT lpRect)
	{ CGXView::GetClientRect(lpRect); }

GX_INLINE void CGXGridView::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CGXView::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXGridView::SetCapture()
	{ return CGXView::SetCapture(); }

GX_INLINE CWnd* CGXGridView::GetCapture()
	{ return CGXView::GetCapture(); }

GX_INLINE void CGXGridView::ScreenToClient(LPPOINT lpPoint)
	{ CGXView::ScreenToClient(lpPoint); }

GX_INLINE void CGXGridView::ScreenToClient(LPRECT lpRect)
	{ CGXView::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXGridView::OpenClipboard()
	{ return CGXView::OpenClipboard(); }

GX_INLINE CString CGXGridView::GetTabName()
	{ return CGXGridCore::GetTabName(); }

GX_INLINE void CGXGridView::SetTabName(CString s)
	{ CGXGridCore::SetTabName(s); }

GX_INLINE CGXGridCore* CGXGridHandleView::GetGrid()
	{ return m_pGrid; }

#endif // GX_INLINE
