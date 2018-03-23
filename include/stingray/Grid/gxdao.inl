///////////////////////////////////////////////////////////////////////////////
// gxdao.inl
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

// gxdao.inl: Inlines for gxdao.h
/////////////////////////////////////////////////////////////////////////////

#ifdef GX_INLINE

GX_INLINE void CGXDaoParam::SetIgnoreBinary(BOOL b)
{
	m_bIgnoreBinaryData = b;
}

GX_INLINE BOOL CGXDaoParam::GetIgnoreBinary() const
{
	return m_bIgnoreBinaryData;
}

GX_INLINE CGXDaoParam* CGXDaoGrid::GetDaoParam()
	{ return (CGXDaoParam*) GetParam(); }

GX_INLINE void CGXDaoGrid::SetRecordset(CDaoRecordset* pSet)
	{ m_pRecordset = pSet; }

GX_INLINE void CGXDaoGrid::DeleteRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, nFromRow);
	awRowEnd.SetAtGrow(0, nToRow);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXDaoGrid::DeleteRows(const CGXRange& range)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, range.top);
	awRowEnd.SetAtGrow(0, range.bottom);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXDaoRecordView::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CGXView::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXDaoRecordView::Invalidate(BOOL bErase)
	{ CGXView::Invalidate(bErase); }

GX_INLINE void CGXDaoRecordView::UpdateWindow()
	{ CGXView::UpdateWindow(); }

GX_INLINE int CGXDaoRecordView::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CGXView::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXDaoRecordView::GetDC()
	{ return CGXView::GetDC(); }

GX_INLINE int CGXDaoRecordView::ReleaseDC(CDC* pDC)
	{ return CGXView::ReleaseDC(pDC); }

GX_INLINE void CGXDaoRecordView::GetClientRect(LPRECT lpRect)
	{ CGXView::GetClientRect(lpRect); }

GX_INLINE void CGXDaoRecordView::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CGXView::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXDaoRecordView::SetCapture()
	{ return CGXView::SetCapture(); }

GX_INLINE CWnd* CGXDaoRecordView::GetCapture()
	{ return CGXView::GetCapture(); }

GX_INLINE void CGXDaoRecordView::ScreenToClient(LPPOINT lpPoint)
	{ CGXView::ScreenToClient(lpPoint); }

GX_INLINE void CGXDaoRecordView::ScreenToClient(LPRECT lpRect)
	{ CGXView::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXDaoRecordView::OpenClipboard()
	{ return CGXView::OpenClipboard(); }

GX_INLINE CString CGXDaoRecordView::GetTabName()
	{ return CGXDaoGrid::GetTabName(); }

GX_INLINE void CGXDaoRecordView::SetTabName(CString s)
	{ CGXDaoGrid::SetTabName(s); }

GX_INLINE void CGXDaoRecordWnd::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CWnd::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXDaoRecordWnd::Invalidate(BOOL bErase)
	{ CWnd::Invalidate(bErase); }

GX_INLINE void CGXDaoRecordWnd::UpdateWindow()
	{ CWnd::UpdateWindow(); }

GX_INLINE int CGXDaoRecordWnd::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CWnd::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXDaoRecordWnd::GetDC()
	{ return CWnd::GetDC(); }

GX_INLINE int CGXDaoRecordWnd::ReleaseDC(CDC* pDC)
	{ return CWnd::ReleaseDC(pDC); }

GX_INLINE void CGXDaoRecordWnd::GetClientRect(LPRECT lpRect)
	{ CWnd::GetClientRect(lpRect); }

GX_INLINE void CGXDaoRecordWnd::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CWnd::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXDaoRecordWnd::SetCapture()
	{ return CWnd::SetCapture(); }

GX_INLINE CWnd* CGXDaoRecordWnd::GetCapture()
	{ return CWnd::GetCapture(); }

GX_INLINE void CGXDaoRecordWnd::ScreenToClient(LPPOINT lpPoint)
	{ CWnd::ScreenToClient(lpPoint); }

GX_INLINE void CGXDaoRecordWnd::ScreenToClient(LPRECT lpRect)
	{ CWnd::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXDaoRecordWnd::OpenClipboard()
	{ return CWnd::OpenClipboard(); }

GX_INLINE CGXDaoBlob::CGXDaoBlob():m_pOleVariant(NULL)
	{
	}
GX_INLINE CGXDaoBlob::~CGXDaoBlob()
	{
		ASSERT(m_pOleVariant == NULL); // should have been freed in Cleanup
	}
GX_INLINE void CGXDaoBlob::Cleanup(BOOL bDestruct)
	{
		if(m_pOleVariant != NULL)
			delete m_pOleVariant;
		m_pOleVariant = NULL;
		if(bDestruct)
			delete this;
	}
GX_INLINE const COleVariant* CGXDaoBlob::GetOleVariant()
	{
		return m_pOleVariant;
	}
GX_INLINE void CGXDaoBlob::SetOleVariant(const COleVariant* pVariant)
	{
		Cleanup();
		m_pOleVariant = new COleVariant(pVariant);
	}

GX_INLINE CGXOleViewer::CGXOleViewer()
{
	m_pControl = NULL;
}

GX_INLINE CGXOleViewer::~CGXOleViewer()
{
}

GX_INLINE CGXControl* CGXOleViewer::GetActiveControl()
{
	return m_pControl;
}

GX_INLINE void CGXOleViewer::SetActiveControl(CGXControl* pControl)
{
	m_pControl = pControl;
}

GX_INLINE void CGXOleViewer::Close()
{
	// once the viewer is closed, the active control becomes void
	SetActiveControl(NULL);
}

GX_INLINE void CGXOleViewer::OnModify()
{
	if (GetActiveControl() == NULL)
		return;
	GetActiveControl()->OnModifyCell();
	GetActiveControl()->SetModify(TRUE);
}
#endif // GX_INLINE
