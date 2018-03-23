///////////////////////////////////////////////////////////////////////////////
// GXCORE.inl
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

// #include <StingrayExportDefs.h>

// this file provides GX_INLINE  methods for following classes:

class CGXGridCore;
class CGXRange;
class CGXRangeList;
class CGXProperties;
class CGXGridParam;

/////////////////////////////////////////////////////////////////////////////
// Static members for Converting of Text-Alignment

GX_INLINE  UINT AFXAPI AlignTAToDT(UINT ntAlign)
	{ return (ntAlign == TA_RIGHT)?DT_RIGHT:(ntAlign == TA_CENTER)?DT_CENTER:DT_LEFT; }

GX_INLINE  UINT AFXAPI AlignDTToTA(UINT ntAlign)
	{ return (ntAlign&0x03)==DT_RIGHT?TA_RIGHT:(ntAlign&0x03)==DT_CENTER?TA_CENTER:TA_LEFT; }

GX_INLINE  UINT AFXAPI AlignESToTA(LONG ntAlign)
	{ return (ntAlign == ES_RIGHT)?TA_RIGHT:(ntAlign == ES_CENTER)?TA_CENTER:TA_LEFT; }

GX_INLINE  LONG AFXAPI AlignTAToES(UINT ntAlign)
	{ return (ntAlign == TA_RIGHT)?ES_RIGHT:(ntAlign == TA_CENTER)?ES_CENTER:ES_LEFT; }

// packing row and column in a DWORD

GX_INLINE DWORD AFXAPI GXRowColToDWord(ROWCOL nRow, ROWCOL nCol)
{
	ASSERT(nRow <= USHRT_MAX);
	ASSERT(nCol <= USHRT_MAX);
	return MAKELONG(nRow, nCol);
}

GX_INLINE WORD AFXAPI GXDWordToRow(DWORD dwValue)
{
	return LOWORD(dwValue);
}

GX_INLINE WORD AFXAPI GXDWordToCol(DWORD dwValue)
{
	return HIWORD(dwValue);
}

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXGridCore

// initialization and style

GX_INLINE  void CGXGridCore::SetGridWnd(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
	{ m_pGridWnd = pGridWnd; m_bIsViewContext = bIsViewContext; m_pGridDoc = pGridDoc; }

GX_INLINE CWnd* CGXGridCore::GridWnd()
	{ return m_pGridWnd; }

GX_INLINE  CDocument* CGXGridCore::GetGridDoc()
	{ return m_pGridDoc; }

GX_INLINE  void CGXGridCore::SetViewID(int nID)
	{ m_nViewID = nID; }

GX_INLINE  void CGXGridCore::SetIgnoreFocus(BOOL b)
	{ m_bIgnoreFocus = b; }

GX_INLINE  void CGXGridCore::SetDropDownCell(BOOL b)
	{ m_bDropDownCell = b; }

GX_INLINE  BOOL CGXGridCore::GetColStyle(ROWCOL nCol, CGXStyle& style, GXModifyType mt)
	{ return GetStyleRowCol(0, nCol, style, mt, -1); }

GX_INLINE  BOOL CGXGridCore::GetRowStyle(ROWCOL nRow, CGXStyle& style, GXModifyType mt)
	{ return GetStyleRowCol(nRow, 0, style, mt, -1); }

GX_INLINE  BOOL CGXGridCore::GetTableStyle(CGXStyle& style, GXModifyType mt)
	{ return GetStyleRowCol(0, 0, style, mt, -1); }

GX_INLINE  BOOL CGXGridCore::SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt, int nType, UINT flags)
	{ return SetStyleRange(range, &style, mt, nType, NULL, flags); }

GX_INLINE  BOOL CGXGridCore::SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, const CString& s, UINT flags)
	{ return SetValueRange(CGXRange(nRow, nCol), s, gxOverride, m_nExpressionValueType, flags);  }

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, LPCTSTR lpsz, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(lpsz), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, const CString& s, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(s), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

#ifdef _UNICODE
GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, const char* lpsz, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(lpsz), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END
#endif

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, DWORD dw, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(dw), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, WORD w, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(w), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, short s, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(s), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, LONG l, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(l), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, float f, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(f), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::SetValueRange(const CGXRange& range, double d, GXModifyType mt, int nType, UINT flags)
	{ ASSERT(m_bInitDone); m_pStyleValue->Free(); return SetStyleRange(range, &m_pStyleValue->SetValue(d), mt, nType, NULL, flags); }
	// ASSERTION-> Did you already call CGXGridCore::OnGridInitialUpdate
	// or CGXGridWnd::Initialize() ? ->END

GX_INLINE  BOOL CGXGridCore::LockUpdate(BOOL b)
	{ BOOL bOld = GetParam()->m_bUpdateLocked; GetParam()->m_bUpdateLocked = b; return bOld; }

GX_INLINE  BOOL CGXGridCore::IsLockUpdate()
	{ return GetParam()->m_bUpdateLocked; }

GX_INLINE  BOOL CGXGridCore::IsActiveFrame()
	{ return m_bActiveFrame; }

GX_INLINE  CGXGridParam* CGXGridCore::GetParam()
	{ return m_pParam; }

GX_INLINE  BOOL CGXGridCore::IsPrinting()
	{ return m_bPrintInProgress; }

GX_INLINE  void CGXGridCore::SetAutoScroll(BOOL bAutoScroll)
	{ m_bAutoScroll = bAutoScroll; }

GX_INLINE  void CGXGridCore::SetAccelArrowKey(BOOL bEnable)
	{ m_bAccelArrowKey = bEnable; }

GX_INLINE  void CGXGridCore::SetAccelScrollbars(BOOL bEnable)
	{ m_bAccelScrollbars = bEnable; }

GX_INLINE  BOOL CGXGridCore::GetCurrentCell(ROWCOL& nRow, ROWCOL& nCol, BOOL bIgnorePrint)
	{ return GetCurrentCell(&nRow, &nCol, bIgnorePrint); }

GX_INLINE  void CGXGridCore::RedrawRowCol(ROWCOL nRow, ROWCOL nCol, UINT flags, BOOL bCreateHint)
	{ RedrawRowCol(nRow, nCol, nRow, nCol, flags, bCreateHint); }

GX_INLINE  CRect CGXGridCore::CalcRectFromRowCol(ROWCOL nRow, ROWCOL nCol)
	{ return CalcRectFromRowCol(nRow, nCol, nRow, nCol); }

GX_INLINE  WORD CGXGridCore::GetHitState()
	{ return m_nHitState; }

GX_INLINE  BOOL CGXGridCore::EvalVisibleFloatMergeCells(
	const CGXRange& range,
	BOOL bUpdate, //= TRUE
	CGXRange* prgBoundary, // = NULL
	BOOL bLookupStyle) //
{
	return EvalVisibleFloatMergeCells(range,
				GetFrozenRows(), GetFrozenCols(),
				GetTopRow(), GetLeftCol(),
				GetLastVisibleRow(), GetLastVisibleCol(),
				bUpdate,
				prgBoundary,
				bLookupStyle);
}


/////////////////////////////////////////////////////////////////////////////
// TopLeft Cell

GX_INLINE ROWCOL CGXGridCore::GetTopRow()
	{ return m_bPrintInProgress ? m_nPrintTopRow : m_nTopRow; }

GX_INLINE ROWCOL CGXGridCore::GetLeftCol()
	{ return m_bPrintInProgress ? m_nPrintLeftCol: m_nLeftCol; }

GX_INLINE void CGXGridCore::GetTopLeftRowCol(ROWCOL *nRow, ROWCOL *nCol)
	{ *nRow = GetTopRow(); *nCol = GetLeftCol(); }

/////////////////////////////////////////////////////////////////////////////
// Width and Height of cells should be independent of font
// DP is depending on font (Device Points)
// LP is independent on font (Logical Point)

GX_INLINE  LONG CGXGridCore::Height_DPtoLP(int nHeight)
	{ return (LONG) nHeight * (GX_NXYFACTOR / GetFontHeight()); }

GX_INLINE  LONG CGXGridCore::Width_DPtoLP(int nWidth)
	{ return (LONG) nWidth * (GX_NXYFACTOR / GetFontWidth()); }

GX_INLINE  int CGXGridCore::Height_LPtoDP(LONG nHeight)
	{ return (int) (nHeight / (GX_NXYFACTOR / GetFontHeight())); }

GX_INLINE  int CGXGridCore::Width_LPtoDP(LONG nWidth)
	{ return (int) (nWidth / (GX_NXYFACTOR / GetFontWidth())); }

/////////////////////////////////////////////////////////////////////////////
// CWnd member methods used in CGXGridCore

GX_INLINE  void CGXGridCore::InvalidateRect(LPCRECT lpRect, BOOL bErase)
	{ m_pGridWnd->InvalidateRect(lpRect, bErase); }

GX_INLINE  void CGXGridCore::Invalidate(BOOL bErase)
	{ m_pGridWnd->Invalidate(bErase); }

GX_INLINE  void CGXGridCore::UpdateWindow()
	{ m_pGridWnd->UpdateWindow(); }

GX_INLINE  int CGXGridCore::ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
	{ return m_pGridWnd->ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip,
				prgnUpdate, lpRectUpdate, flags); }

GX_INLINE  CDC* CGXGridCore::GetDC()
	{ return m_pGridWnd->GetDC(); }

GX_INLINE  int CGXGridCore::ReleaseDC(CDC* pDC)
	{ return m_pGridWnd->ReleaseDC(pDC); }

GX_INLINE  void CGXGridCore::GetClientRect(LPRECT lpRect)
	{ m_pGridWnd->GetClientRect(lpRect); }

GX_INLINE  void CGXGridCore::ShowScrollBar(UINT nBar, BOOL bShow)
	{ m_pGridWnd->ShowScrollBar(nBar, bShow); }

GX_INLINE  CWnd* CGXGridCore::SetCapture()
	{ return m_pGridWnd->SetCapture(); }

GX_INLINE  CWnd* CGXGridCore::GetCapture()
	{ return m_pGridWnd->GetCapture(); }

GX_INLINE  void CGXGridCore::ScreenToClient(LPPOINT lpPoint)
	{ m_pGridWnd->ScreenToClient(lpPoint); }

GX_INLINE  void CGXGridCore::ScreenToClient(LPRECT lpRect)
	{ m_pGridWnd->ScreenToClient(lpRect); }

GX_INLINE  BOOL CGXGridCore::OpenClipboard()
	{ return m_pGridWnd->OpenClipboard(); }


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXRange

GX_INLINE  CGXRange::CGXRange(ROWCOL nRow, ROWCOL nCol)
	{ SetCells(nRow, nCol, nRow, nCol); }


GX_INLINE  CGXRange& CGXRange::SetCells(ROWCOL nRow, ROWCOL nCol)
	{ return SetCells(nRow, nCol, nRow, nCol); }

GX_INLINE  CGXRange& CGXRange::SetRows(ROWCOL nRow)
	{ return SetRows(nRow, nRow); }

GX_INLINE  CGXRange& CGXRange::SetCols(ROWCOL nCols)
	{ return SetCols(nCols, nCols); }

GX_INLINE  BOOL CGXRange::IsTable() const
	{ return rtType == rtTable; }

GX_INLINE  BOOL CGXRange::IsRows() const
	{ return rtType == rtRows; }

GX_INLINE  BOOL CGXRange::IsCols() const
	{ return rtType == rtCols; }

GX_INLINE  BOOL CGXRange::IsCells() const
	{ return rtType == rtCells; }

GX_INLINE  BOOL CGXRange::IsValid() const
	{ return m_bValid; }

GX_INLINE  ROWCOL CGXRange::GetWidth() const
	{ return right-left+1; }

GX_INLINE  ROWCOL CGXRange::GetHeight() const
	{ return bottom-top+1; }

GX_INLINE int CGXRange::operator==(const CGXRange &r) const
	{ return rtType == r.rtType && top == r.top && left == r.left && bottom == r.bottom && right == r.right && m_bValid == r.m_bValid; }

GX_INLINE int CGXRange::operator!=(const CGXRange &r) const
	{ return !(rtType == r.rtType && top == r.top && left == r.left && bottom == r.bottom && right == r.right && m_bValid == r.m_bValid); }

/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXRangeList

GX_INLINE  CGXRange*& CGXRangeList::GetHead()
	{ return (CGXRange*&) CPtrList::GetHead(); }
GX_INLINE  CGXRange* CGXRangeList::GetHead() const
	{ return (CGXRange*) CPtrList::GetHead(); }
GX_INLINE  CGXRange*& CGXRangeList::GetTail()
	{ return (CGXRange*&) CPtrList::GetTail(); }
GX_INLINE  CGXRange* CGXRangeList::GetTail() const
	{ return (CGXRange*) CPtrList::GetTail(); }

GX_INLINE  CGXRange* CGXRangeList::RemoveHead()
	{ return (CGXRange*) CPtrList::RemoveHead(); }
GX_INLINE  CGXRange* CGXRangeList::RemoveTail()
	{ return (CGXRange*) CPtrList::RemoveTail(); }

GX_INLINE  POSITION CGXRangeList::AddHead(CGXRange* newElement)
	{ return CPtrList::AddHead(newElement); }
GX_INLINE  POSITION CGXRangeList::AddTail(CGXRange* newElement)
	{ return CPtrList::AddTail(newElement); }

GX_INLINE  void CGXRangeList::AddHead(CGXRangeList* pNewList)
	{ CPtrList::AddHead(pNewList); }
GX_INLINE  void CGXRangeList::AddTail(CGXRangeList* pNewList)
	{ CPtrList::AddTail(pNewList); }

GX_INLINE  CGXRange*& CGXRangeList::GetNext(POSITION& rPosition)
	{ return (CGXRange*&) CPtrList::GetNext(rPosition); }
GX_INLINE  CGXRange* CGXRangeList::GetNext(POSITION& rPosition) const
	{ return (CGXRange*) CPtrList::GetNext(rPosition); }
GX_INLINE  CGXRange*& CGXRangeList::GetPrev(POSITION& rPosition)
	{ return (CGXRange*&) CPtrList::GetPrev(rPosition); }
GX_INLINE  CGXRange* CGXRangeList::GetPrev(POSITION& rPosition) const
	{ return (CGXRange*) CPtrList::GetPrev(rPosition); }

GX_INLINE  CGXRange*& CGXRangeList::GetAt(POSITION position)
	{ return (CGXRange*&) CPtrList::GetAt(position); }
GX_INLINE  CGXRange* CGXRangeList::GetAt(POSITION position) const
	{ return (CGXRange*) CPtrList::GetAt(position); }
GX_INLINE  void CGXRangeList::SetAt(POSITION pos, CGXRange* newElement)
	{ CPtrList::SetAt(pos, newElement); }

GX_INLINE  POSITION CGXRangeList::InsertBefore(POSITION position, CGXRange* newElement)
	{ return CPtrList::InsertBefore(position, newElement); }
GX_INLINE  POSITION CGXRangeList::InsertAfter(POSITION position, CGXRange* newElement)
	{ return CPtrList::InsertAfter(position, newElement); }

GX_INLINE  POSITION CGXRangeList::Find(CGXRange* searchValue, POSITION startAfter) const
	{ return CPtrList::Find(searchValue, startAfter); }


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXProperties

GX_INLINE  CGXProperties::UserPropertyInfo::UserPropertyInfo()
	{ }

GX_INLINE  CGXProperties::UserPropertyInfo::~UserPropertyInfo()
	{ delete pStyle; }

GX_INLINE  void CGXProperties::SetSection(LPCTSTR pszSection)
	{ m_sSection = pszSection; }

GX_INLINE  const CString& CGXProperties::GetSection() const
	{ return m_sSection; }

GX_INLINE  void CGXProperties::SetPrinting(BOOL b)
	{ m_bPrinting = b; }

GX_INLINE  BOOL CGXProperties::GetPrinting() const
	{ return m_bPrinting; }

GX_INLINE  void CGXProperties::SetDisplayHorzLines(BOOL b)
	{ m_bDisplayHorzLines = b; }

GX_INLINE  void CGXProperties::SetDisplayVertLines(BOOL b)
	{ m_bDisplayVertLines = b; }

GX_INLINE  void CGXProperties::SetDisplay3dButtons(BOOL b)
	{ m_b3dButtons = b; }

GX_INLINE  void CGXProperties::SetMarkRowHeader(BOOL b)
	{ m_bMarkRowHeader = b; }

GX_INLINE  void CGXProperties::SetMarkColHeader(BOOL b)
	{ m_bMarkColHeader = b; }

GX_INLINE  void CGXProperties::SetLastZoom(int nZoom)
	{ m_nZoom = nZoom; }

GX_INLINE BOOL CGXProperties::GetCenterHorizontal()
	{ return (BOOL) m_bCenterHorizontal; }

GX_INLINE BOOL CGXProperties::GetCenterVertical()
	{ return (BOOL) m_bCenterVertical; }

GX_INLINE BOOL CGXProperties::GetPrintRowHeaders()
	{ return (BOOL) m_bRowHeaders; }

GX_INLINE BOOL CGXProperties::GetPrintColHeaders()
	{ return (BOOL) m_bColHeaders; }

GX_INLINE BOOL CGXProperties::GetPrintFrame()
	{ return (BOOL) m_bPrintFrame; }

GX_INLINE BOOL CGXProperties::GetPrintHorzLines()
	{ return (BOOL) m_bPrintHorzLines; }

GX_INLINE BOOL CGXProperties::GetPrintVertLines()
	{ return (BOOL) m_bPrintVertLines; }

GX_INLINE int CGXProperties::GetPageOrder()
	{ return (int) m_nPageOrder; }

GX_INLINE BOOL CGXProperties::GetPrintBlackWhite()
	{ return (BOOL) m_bBlackWhite; }

GX_INLINE void CGXProperties::SetPrintHorzLines(BOOL b)
	{ m_bPrintHorzLines = b; }

GX_INLINE void CGXProperties::SetPrintVertLines(BOOL b)
	{ m_bPrintVertLines = b; }

GX_INLINE void CGXProperties::SetCenterHorizontal(BOOL b)
	{ m_bCenterHorizontal = b; }

GX_INLINE void CGXProperties::SetCenterVertical(BOOL b)
	{ m_bCenterVertical = b; }

GX_INLINE void CGXProperties::SetBlackWhite(BOOL b)
	{ m_bBlackWhite = b; }

GX_INLINE void CGXProperties::SetPrintRowHeaders(BOOL b)
	{ m_bRowHeaders = b; }

GX_INLINE void CGXProperties::SetPrintColHeaders(BOOL b)
	{ m_bColHeaders = b; }

GX_INLINE void CGXProperties::SetPageOrder(int n)
	{ m_nPageOrder = n; }

GX_INLINE void CGXProperties::SetPrintFrame(BOOL b)
	{ m_bPrintFrame = b; }

GX_INLINE CGXData& CGXProperties::GetDataHeader()
	{ return m_mapDataHeader; }

GX_INLINE CGXData& CGXProperties::GetDataFooter()
	{ return m_mapDataFooter; }

GX_INLINE CDWordArray& CGXProperties::GetColBreakArray()
{
	return m_awColBreaks;
}

GX_INLINE CDWordArray& CGXProperties::GetRowBreakArray()
{
	return m_awRowBreaks;
}


// Attributes

GX_INLINE BOOL CGXProperties::GetDisplayHorzLines() const
{
	return GetPrinting()
		? (BOOL) m_bPrintHorzLines
		: m_bDisplayHorzLines;
}

GX_INLINE BOOL CGXProperties::GetDisplayVertLines() const
{
	return GetPrinting()
		? (BOOL) m_bPrintVertLines
		: m_bDisplayVertLines;
}

GX_INLINE BOOL CGXProperties::GetDisplay3dButtons() const
{
	return m_b3dButtons;
}


GX_INLINE BOOL CGXProperties::GetDisplayRowHeaders() const
{
	return !GetPrinting() || m_bRowHeaders;
}

GX_INLINE BOOL CGXProperties::GetDisplayColHeaders() const
{
	return !GetPrinting() || m_bColHeaders;
}

GX_INLINE BOOL CGXProperties::GetBlackWhite() const
{
	return GetPrinting() && m_bBlackWhite;
}

GX_INLINE BOOL CGXProperties::GetMarkRowHeader() const
{
	return m_bMarkRowHeader;
}

GX_INLINE BOOL CGXProperties::GetMarkColHeader() const
{
	return m_bMarkColHeader;
}

GX_INLINE BOOL CGXProperties::GetLastZoom() const
{
	return m_nZoom;
}

// Margins

GX_INLINE void CGXProperties::GetMargins(int& top, int& left, int& bottom, int& right)
{
	top = (int) m_nTopMargin;
	left = (int) m_nLeftMargin;
	right = (int) m_nRightMargin;
	bottom = (int) m_nBottomMargin;
}

GX_INLINE void CGXProperties::SetMargins(int top, int left, int bottom, int right)
{
	m_nTopMargin = top;
	m_nLeftMargin = left;
	m_nRightMargin = right;
	m_nBottomMargin = bottom;
}

// Header&Footer

GX_INLINE void CGXProperties::GetDistances(int& top, int& bottom)
{
	top = (int) m_nDistTop;
	bottom = (int) m_nDistBottom;
}

GX_INLINE void CGXProperties::SetDistances(int top, int bottom)
{
	m_nDistTop = top;
	m_nDistBottom = bottom;
}

GX_INLINE void CGXProperties::SetFirstPage(int nStart)
{
	m_nFirstPage = nStart;
}

GX_INLINE int CGXProperties::GetFirstPage()
{
	return (int) m_nFirstPage;
}

/////////////////////////////////////////////////////////////////////////////
// class CGXGridParam

GX_INLINE  void CGXGridParam::SetSortColsOnDblClk(BOOL b)
	{ m_bSortColsOnDblClk = b; }

GX_INLINE  BOOL CGXGridParam::GetSortColsOnDblClk()
	{ return m_bSortColsOnDblClk; }

GX_INLINE  void CGXGridParam::SetSortRowsOnDblClk(BOOL b)
	{ m_bSortRowsOnDblClk = b; }

GX_INLINE  BOOL CGXGridParam::GetSortRowsOnDblClk()
	{ return m_bSortRowsOnDblClk; }

GX_INLINE  void CGXGridParam::SetExcelLikeCurrentCell(BOOL b)
	{ m_bExcelLikeCurrentCell = b; }

GX_INLINE  BOOL CGXGridParam::GetExcelLikeCurrentCell()
	{ return m_bExcelLikeCurrentCell; }

GX_INLINE  void CGXGridParam::SetExcelLikeSelectionFrame(BOOL b)
	{ m_bExcelLikeSelectionFrame = b; }

GX_INLINE  BOOL CGXGridParam::GetExcelLikeSelectionFrame()
	{ return m_bExcelLikeSelectionFrame; }

GX_INLINE  DWORD CGXGridParam::GetExcelLikeFillFlags() const
{	return m_nExcelLikeFillFlags; }

GX_INLINE  void CGXGridParam::SetExcelLikeHeaders(BOOL b)
	{ m_bExcelLikeHeaders = b; }

GX_INLINE  BOOL CGXGridParam::GetExcelLikeHeaders()
	{ return m_bExcelLikeHeaders; }

GX_INLINE  void CGXGridParam::SetNewGridLineMode(BOOL b)
	{ m_bNewGridLineMode = b; }

GX_INLINE  BOOL CGXGridParam::GetNewGridLineMode()
	{ return m_bNewGridLineMode; }

GX_INLINE  void CGXGridParam::SetGridLineStyle(UINT nStyle)
	{ m_nGridLineStyle = (WORD) nStyle; }

GX_INLINE  UINT CGXGridParam::GetGridLineStyle() const
	{ return m_nGridLineStyle; }

GX_INLINE void CGXGridParam::SetEnterKeyAction(WORD nAction) // 0 for simply storing current cells value
{
	m_nEnterKeyAction = nAction;
}

GX_INLINE WORD CGXGridParam::GetEnterKeyAction()
{
	return m_nEnterKeyAction;
}

GX_INLINE void CGXGridParam::SetUndoLimit(DWORD nMaxUndoOp)
{
	m_dwUndoLimit = nMaxUndoOp;
}

GX_INLINE DWORD CGXGridParam::GetUndoLimit()
{
	return m_dwUndoLimit;
}

GX_INLINE  void CGXGridParam::SetDrawWYSIWYG(BOOL b)
	{ m_bDrawWYSIWYG = b; }

GX_INLINE  BOOL CGXGridParam::IsDrawWYSIWYG()
	{ return m_bDrawWYSIWYG; }

GX_INLINE  void CGXGridParam::SetNumberedRowHeaders(BOOL b)
	{ m_bNumberedRowHeaders = b; }

GX_INLINE  void CGXGridParam::SetNumberedColHeaders(BOOL b)
	{ m_bNumberedColHeaders = b; }

GX_INLINE  BOOL CGXGridParam::IsNumberedRowHeaders()
	{ return m_bNumberedRowHeaders; }

GX_INLINE  BOOL CGXGridParam::IsNumberedColHeaders()
	{ return m_bNumberedColHeaders; }

GX_INLINE  void CGXGridParam::SetDefaultComboBoxHeight(int nHeight)
	{ m_nDefaultComboBoxHeight = nHeight; }

GX_INLINE  int CGXGridParam::GetDefaultComboBoxHeight()
	{ return m_nDefaultComboBoxHeight; }

GX_INLINE  void CGXGridParam::SetEatFirstMouseClick(BOOL b)
	{ m_bEatFirstMouseClick = b; }

GX_INLINE  BOOL CGXGridParam::IsEatFirstMouseClick()
	{ return m_bEatFirstMouseClick; }

GX_INLINE  void CGXGridParam::SetTransparentBackground(BOOL b)
	{ m_bTransparentBackground = b; }

GX_INLINE  BOOL CGXGridParam::IsTransparentBackground()
	{ return m_bTransparentBackground; }

GX_INLINE  void CGXGridParam::SetRemoveRowsFlags(WORD wFlags)
	{ m_nRemoveRowsFlags = wFlags; }

GX_INLINE  void CGXGridParam::SetRemoveColsFlags(WORD wFlags)
	{ m_nRemoveColsFlags = wFlags; }

GX_INLINE  WORD CGXGridParam::GetRemoveRowsFlags()
	{ return m_nRemoveRowsFlags; }

GX_INLINE  WORD CGXGridParam::GetRemoveColsFlags()
	{ return m_nRemoveColsFlags; }

GX_INLINE  void CGXGridParam::SetMinTrackRowHeight(int nHeight)
	{ m_nMinTrackRowHeight = nHeight; }

GX_INLINE  void CGXGridParam::SetMinTrackColWidth(int nWidth)
	{ m_nMinTrackColWidth = nWidth; }

GX_INLINE  int CGXGridParam::GetMinTrackRowHeight()
	{ return m_nMinTrackRowHeight; }

GX_INLINE  int CGXGridParam::GetMinTrackColWidth()
	{ return m_nMinTrackColWidth; }

GX_INLINE  void CGXGridParam::SetActivateCellFlags(WORD wFlags)
	{ m_wActivateCell = wFlags; }

GX_INLINE  WORD CGXGridParam::GetActivateCellFlags()
	{ return m_wActivateCell; }

GX_INLINE  void CGXGridParam::SetSmartResize(BOOL b)
	{ m_bSmartResize = b; }

GX_INLINE  BOOL CGXGridParam::IsSmartResize()
	{ return m_bSmartResize; }

GX_INLINE  void CGXGridParam::SetScrollLikeExcel(BOOL b)
	{ m_bScrollLikeExcel = b; }

GX_INLINE  BOOL CGXGridParam::IsScrollLikeExcel()
	{ return m_bScrollLikeExcel; }

GX_INLINE  void CGXGridParam::SetSyncCurrentCell(BOOL b)
	{ m_bSyncCurrentCell = b; }

GX_INLINE  BOOL CGXGridParam::IsSyncCurrentCell()
	{ return m_bSyncCurrentCell; }

GX_INLINE  void CGXGridParam::SetLockReadOnly(BOOL b)
	{ m_bLockReadOnly = b; }

GX_INLINE  BOOL CGXGridParam::IsLockReadOnly()
	{ return m_bLockReadOnly; }

GX_INLINE  void CGXGridParam::SetDrawOrder(WORD w)
	{ m_nDrawRowOrder = w; }

GX_INLINE  WORD CGXGridParam::GetDrawOrder()
	{ return m_nDrawRowOrder; }

GX_INLINE  void CGXGridParam::SetHideCurrentCell(WORD nSetting)
	{ m_nHideCurrentCell = nSetting; }

GX_INLINE  WORD CGXGridParam::GetHideCurrentCell()
	{ return m_nHideCurrentCell; }

GX_INLINE  CGXProperties* CGXGridParam::GetProperties()
	{ ASSERT(this); return m_pProperties; }

GX_INLINE  CGXData* CGXGridParam::GetData()
	{ ASSERT(this); return m_pData; }

GX_INLINE  CGXStylesMap* CGXGridParam::GetStylesMap()
	{ ASSERT(this); return m_pStylesMap; }

GX_INLINE  CGXRangeList* CGXGridParam::GetRangeList()
	{ ASSERT(this); return &m_SelRects; }

GX_INLINE  CGXRangeList* CGXGridParam::GetCoveredCellsList()
	{ ASSERT(this); return &m_CoveredCellsList; }

GX_INLINE  const CString& CGXGridParam::GetSheetName()
	{ ASSERT(this); return m_sSheetName; }

GX_INLINE  void CGXGridParam::SetSheetName(LPCTSTR szName)
	{ ASSERT(this); m_sSheetName = szName; }

GX_INLINE  BOOL CGXGridParam::IsInit() const
	{ ASSERT(this); return m_bIsInit; }

GX_INLINE  CGXPrintDevice* CGXGridParam::GetPrintDevice()
	{ return m_pPD; }


#endif // GX_INLINE
