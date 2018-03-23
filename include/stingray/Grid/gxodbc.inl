///////////////////////////////////////////////////////////////////////////////
// gxodbc.inl
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

#if _MFC_VER >= 0x0300 
GX_INLINE void GXInitODBC(UINT uiMfcVersion)
	{ uiMfcVersion; }
#endif

GX_INLINE CGXDbParam* CGXODBCGrid::GetDbParam()
	{ return (CGXDbParam*) GetParam(); }

GX_INLINE void CGXODBCGrid::SetRecordset(CRecordset* pSet)
	{ m_pRecordset = pSet; }

// provided for compatibility with 1.0
GX_INLINE UINT CGXODBCGrid::GetFieldCol(ROWCOL nCol)
	{ return (UINT) GetFieldFromCol(nCol); }

GX_INLINE void CGXODBCGrid::DeleteRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, nFromRow);
	awRowEnd.SetAtGrow(0, nToRow);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXODBCGrid::DeleteRows(const CGXRange& range)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, range.top);
	awRowEnd.SetAtGrow(0, range.bottom);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXRecordView::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CGXView::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXRecordView::Invalidate(BOOL bErase)
	{ CGXView::Invalidate(bErase); }

GX_INLINE void CGXRecordView::UpdateWindow()
	{ CGXView::UpdateWindow(); }

GX_INLINE int CGXRecordView::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CGXView::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXRecordView::GetDC()
	{ return CGXView::GetDC(); }

GX_INLINE int CGXRecordView::ReleaseDC(CDC* pDC)
	{ return CGXView::ReleaseDC(pDC); }

GX_INLINE void CGXRecordView::GetClientRect(LPRECT lpRect)
	{ CGXView::GetClientRect(lpRect); }

GX_INLINE void CGXRecordView::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CGXView::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXRecordView::SetCapture()
	{ return CGXView::SetCapture(); }

GX_INLINE CWnd* CGXRecordView::GetCapture()
	{ return CGXView::GetCapture(); }

GX_INLINE void CGXRecordView::ScreenToClient(LPPOINT lpPoint)
	{ CGXView::ScreenToClient(lpPoint); }

GX_INLINE void CGXRecordView::ScreenToClient(LPRECT lpRect)
	{ CGXView::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXRecordView::OpenClipboard()
	{ return CGXView::OpenClipboard(); }

GX_INLINE CString CGXRecordView::GetTabName()
	{ return CGXODBCGrid::GetTabName(); }

GX_INLINE void CGXRecordView::SetTabName(CString s)
	{ CGXODBCGrid::SetTabName(s); }

GX_INLINE void CGXRecordWnd::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CWnd::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXRecordWnd::Invalidate(BOOL bErase)
	{ CWnd::Invalidate(bErase); }

GX_INLINE void CGXRecordWnd::UpdateWindow()
	{ CWnd::UpdateWindow(); }

GX_INLINE int CGXRecordWnd::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CWnd::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXRecordWnd::GetDC()
	{ return CWnd::GetDC(); }

GX_INLINE int CGXRecordWnd::ReleaseDC(CDC* pDC)
	{ return CWnd::ReleaseDC(pDC); }

GX_INLINE void CGXRecordWnd::GetClientRect(LPRECT lpRect)
	{ CWnd::GetClientRect(lpRect); }

GX_INLINE void CGXRecordWnd::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CWnd::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXRecordWnd::SetCapture()
	{ return CWnd::SetCapture(); }

GX_INLINE CWnd* CGXRecordWnd::GetCapture()
	{ return CWnd::GetCapture(); }

GX_INLINE void CGXRecordWnd::ScreenToClient(LPPOINT lpPoint)
	{ CWnd::ScreenToClient(lpPoint); }

GX_INLINE void CGXRecordWnd::ScreenToClient(LPRECT lpRect)
	{ CWnd::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXRecordWnd::OpenClipboard()
	{ return CWnd::OpenClipboard(); }

#endif // GX_INLINE
