///////////////////////////////////////////////////////////////////////////////
// gxbrowse.inl
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

#ifdef GX_INLINE

GX_INLINE CGXRecSetInfo* CGXBrowseParam::GetRecSetInfo()
	{ return (CGXRecSetInfo*) m_pRecSetInfo; };

GX_INLINE CGXBrowseDirtyFieldStruct::CGXBrowseDirtyFieldStruct()
	: bDirty(FALSE), pAttribute(NULL)
{
}

GX_INLINE CGXBrowseDirtyFieldStruct::~CGXBrowseDirtyFieldStruct()
{
	if(pAttribute != NULL)
		pAttribute->Cleanup(TRUE); // delete the object
}
//@doc
//@mfunc
//@syntax CGXBrowseParam* GetBrowseParam();
//@rdesc
//A pointer to the <c CGXBrowseParam> object. <bold>NULL<ebold> if there 
//is no parameter-object attached
//@rem
//Returns a pointer to the associated <c CGXBrowseParam> object.
//@xref <c CGXBrowseParam> <c CGXBrowserGrid>
GX_INLINE CGXBrowseParam* CGXBrowserGrid::GetBrowseParam()
	{ return (CGXBrowseParam*) GetParam(); }

//@doc
//@mfunc
//@syntax int GetMaxColWidth();
//@rdesc
//An integer specifying the column width.
//@rem
//Returns the maximum number of characters for text fields to be displayed in the cells.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::SetMaxColWidth> 
GX_INLINE int CGXBrowserGrid::GetMaxColWidth()
	{ return GetBrowseParam()->m_nMaxColWidth; }

GX_INLINE void CGXBrowserGrid::SetCanAppend(BOOL b)
	{ GetBrowseParam()->m_bCanAppend = b; }

GX_INLINE BOOL CGXBrowserGrid::SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt, int nType, UINT flags)
	{ return SetStyleRange(range, &style, mt, nType, NULL, flags); }

GX_INLINE void CGXBrowserView::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CGXView::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXBrowserView::Invalidate(BOOL bErase)
	{ CGXView::Invalidate(bErase); }

GX_INLINE void CGXBrowserView::UpdateWindow()
	{ CGXView::UpdateWindow(); }

GX_INLINE int CGXBrowserView::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CGXView::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXBrowserView::GetDC()
	{ return CGXView::GetDC(); }

GX_INLINE int CGXBrowserView::ReleaseDC(CDC* pDC)
	{ return CGXView::ReleaseDC(pDC); }

GX_INLINE void CGXBrowserView::GetClientRect(LPRECT lpRect)
	{ CGXView::GetClientRect(lpRect); }

GX_INLINE void CGXBrowserView::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CGXView::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXBrowserView::SetCapture()
	{ return CGXView::SetCapture(); }

GX_INLINE CWnd* CGXBrowserView::GetCapture()
	{ return CGXView::GetCapture(); }

GX_INLINE void CGXBrowserView::ScreenToClient(LPPOINT lpPoint)
	{ CGXView::ScreenToClient(lpPoint); }

GX_INLINE void CGXBrowserView::ScreenToClient(LPRECT lpRect)
	{ CGXView::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXBrowserView::OpenClipboard()
	{ return CGXView::OpenClipboard(); }

GX_INLINE CString CGXBrowserView::GetTabName()
	{ return CGXBrowserGrid::GetTabName(); }

GX_INLINE void CGXBrowserView::SetTabName(CString s)
	{ CGXBrowserGrid::SetTabName(s); }

GX_INLINE void CGXBrowserWnd::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CWnd::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXBrowserWnd::Invalidate(BOOL bErase)
	{ CWnd::Invalidate(bErase); }

GX_INLINE void CGXBrowserWnd::UpdateWindow()
	{ CWnd::UpdateWindow(); }

GX_INLINE int CGXBrowserWnd::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CWnd::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXBrowserWnd::GetDC()
	{ return CWnd::GetDC(); }

GX_INLINE int CGXBrowserWnd::ReleaseDC(CDC* pDC)
	{ return CWnd::ReleaseDC(pDC); }

GX_INLINE void CGXBrowserWnd::GetClientRect(LPRECT lpRect)
	{ CWnd::GetClientRect(lpRect); }

GX_INLINE void CGXBrowserWnd::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CWnd::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXBrowserWnd::SetCapture()
	{ return CWnd::SetCapture(); }

GX_INLINE CWnd* CGXBrowserWnd::GetCapture()
	{ return CWnd::GetCapture(); }

GX_INLINE void CGXBrowserWnd::ScreenToClient(LPPOINT lpPoint)
	{ CWnd::ScreenToClient(lpPoint); }

GX_INLINE void CGXBrowserWnd::ScreenToClient(LPRECT lpRect)
	{ CWnd::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXBrowserWnd::OpenClipboard()
	{ return CWnd::OpenClipboard(); }

// CGXAbstractBlob
GX_INLINE CGXAbstractBlob::CGXAbstractBlob()
{
}

GX_INLINE CGXAbstractBlob::~CGXAbstractBlob()
{
}

#endif // GX_INLINE
