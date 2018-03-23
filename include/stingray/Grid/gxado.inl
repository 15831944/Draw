///////////////////////////////////////////////////////////////////////////////
// gxado.inl
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
// Authors: Praveen Ramesh, Stefan Hoenig
//

#pragma once

#ifdef GX_INLINE

//@doc
//@mfunc
//@rdesc A pointer to a <c CGXAdoParam> object.
//@rem
//Returns a pointer to the associated <c CGXAdoParam> object.
//@xref <c CGXAdoParam> <c CGXAdoGrid>
GX_INLINE CGXAdoParam* CGXAdoGrid::GetAdoParam()
	{ return (CGXAdoParam*) GetParam(); }

//@doc
//@mfunc
//@parm  ADORecordset* | pSet |
//@rem
//Lets you attach the ADORecordset object to be displayed in the grid.<nl>
//See the attached example.
//@ex
/* This sample code shows a typical <mf OnInitialUpdate> method where an 
<c ADORecordset> is instantiated and attached to the grid.|
void CAdpbrowsView::OnInitialUpdate() 

{

CAdobrowsDoc* pDoc = GetDocument();

if (pDoc->m_pParam == NULL)

{

  // construct parameter object

pDoc->m_pParam = new CGXAdoParam;

}

  // else

  // No data need to be initialized. They are already available in the document.

  // pass the pointer to the grid view

SetParam(pDoc->m_pParam, FALSE);

                              // ^-- indicates that document is responsible 

  // for deleting the object.

  // Attach the recordset object

if (pDoc->m_pStudentSet == NULL)

pDoc->m_pStudentSet = CreateRecordset();//Create the ADORecordset and return it

m_pSet = pDoc->m_pStudentSet;

SetRecordset(m_pSet);

  // standard initialization, will create other objects 

  // such as column names, widths, base styles, ...

CGXAdoRecordView::OnInitialUpdate();

  // Enable Objective Grid internal update-hint mechanism

EnableHints();

  // Note: You can use the Window|New command to open a new
  // view on the same cursor.

}
*/
//@xref <c CGXAdoGrid> <mf CGXAdoGrid::OnGetRecordset> 
// QA 32218: Fixes crash and prevents memory leaks
GX_INLINE void CGXAdoGrid::SetRecordset(CComPtr<ADORecordset> pSet, BOOL bOpen)
	{if(!pSet)return; m_piRecordset = pSet; m_bIsOpen = bOpen; }

GX_INLINE void CGXAdoGrid::DeleteRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, nFromRow);
	awRowEnd.SetAtGrow(0, nToRow);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXAdoGrid::DeleteRows(const CGXRange& range)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, range.top);
	awRowEnd.SetAtGrow(0, range.bottom);

	DeleteRows(awRowStart, awRowEnd);
}

GX_INLINE void CGXAdoRecordView::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CGXView::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXAdoRecordView::Invalidate(BOOL bErase)
	{ CGXView::Invalidate(bErase); }

GX_INLINE void CGXAdoRecordView::UpdateWindow()
	{ CGXView::UpdateWindow(); }

GX_INLINE int CGXAdoRecordView::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CGXView::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXAdoRecordView::GetDC()
	{ return CGXView::GetDC(); }

GX_INLINE int CGXAdoRecordView::ReleaseDC(CDC* pDC)
	{ return CGXView::ReleaseDC(pDC); }

GX_INLINE void CGXAdoRecordView::GetClientRect(LPRECT lpRect)
	{ CGXView::GetClientRect(lpRect); }

GX_INLINE void CGXAdoRecordView::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CGXView::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXAdoRecordView::SetCapture()
	{ return CGXView::SetCapture(); }

GX_INLINE CWnd* CGXAdoRecordView::GetCapture()
	{ return CGXView::GetCapture(); }

GX_INLINE void CGXAdoRecordView::ScreenToClient(LPPOINT lpPoint)
	{ CGXView::ScreenToClient(lpPoint); }

GX_INLINE void CGXAdoRecordView::ScreenToClient(LPRECT lpRect)
	{ CGXView::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXAdoRecordView::OpenClipboard()
	{ return CGXView::OpenClipboard(); }

GX_INLINE CString CGXAdoRecordView::GetTabName()
	{ return CGXAdoGrid::GetTabName(); }

GX_INLINE void CGXAdoRecordView::SetTabName(CString s)
	{ CGXAdoGrid::SetTabName(s); }

GX_INLINE void CGXAdoRecordWnd::InvalidateRect(LPCRECT lpRect, BOOL bErase)
		{ CWnd::InvalidateRect(lpRect, bErase); }

GX_INLINE void CGXAdoRecordWnd::Invalidate(BOOL bErase)
	{ CWnd::Invalidate(bErase); }

GX_INLINE void CGXAdoRecordWnd::UpdateWindow()
	{ CWnd::UpdateWindow(); }

GX_INLINE int CGXAdoRecordWnd::ScrollWindowEx(int dx, int dy,
		LPCRECT lpRectScroll, LPCRECT lpRectClip,
		CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return CWnd::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
			prgnUpdate, lpRectUpdate, flags); }

GX_INLINE CDC* CGXAdoRecordWnd::GetDC()
	{ return CWnd::GetDC(); }

GX_INLINE int CGXAdoRecordWnd::ReleaseDC(CDC* pDC)
	{ return CWnd::ReleaseDC(pDC); }

GX_INLINE void CGXAdoRecordWnd::GetClientRect(LPRECT lpRect)
	{ CWnd::GetClientRect(lpRect); }

GX_INLINE void CGXAdoRecordWnd::ShowScrollBar(UINT nBar, BOOL bShow)
	{ CWnd::ShowScrollBar(nBar, bShow); }

GX_INLINE CWnd* CGXAdoRecordWnd::SetCapture()
	{ return CWnd::SetCapture(); }

GX_INLINE CWnd* CGXAdoRecordWnd::GetCapture()
	{ return CWnd::GetCapture(); }

GX_INLINE void CGXAdoRecordWnd::ScreenToClient(LPPOINT lpPoint)
	{ CWnd::ScreenToClient(lpPoint); }

GX_INLINE void CGXAdoRecordWnd::ScreenToClient(LPRECT lpRect)
	{ CWnd::ScreenToClient(lpRect); }

GX_INLINE BOOL CGXAdoRecordWnd::OpenClipboard()
	{ return CWnd::OpenClipboard(); }

#endif // GX_INLINE


