///////////////////////////////////////////////////////////////////////////////
// GXEXT.inl
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

// #include <StingrayExportDefs.h>

struct GRID_API CGXWaitCursor;
class GRID_API CGXLongOperation;

/////////////////////////////////////////////////////////////////////////////
// global methods

GX_INLINE void AFXAPI GXFormatString1(CString& rString, LPCTSTR lpszFormat, LPCTSTR lpsz1)
{
	AfxFormatStrings(rString, lpszFormat, &lpsz1, 1);
}

/////////////////////////////////////////////////////////////////////////////////
// CGXDrawingAndFormatting: wrapper methods to overridable methods in class

GX_INLINE const CBitmap* AFXAPI GXGetPatternBitmap(int n)
{
	return GXDaFTools()->GXGetPatternBitmap(n);
}

GX_INLINE int AFXAPI GXComputeLineBreaks(CDC* pDC, LPCTSTR sz, int nCount, LPRECT rc, UINT nFormat, int* LineBreaks, int* LineLengths, int nMaxBreaks)
{
	return GXDaFTools()->GXComputeLineBreaks(pDC, sz, nCount, rc, nFormat, LineBreaks, LineLengths,	nMaxBreaks);
}

GX_INLINE int AFXAPI GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LPRECT lpClipRect)
{
	return GXDaFTools()->GXDrawTextLikeMultiLineEdit(pDC, lpszString, nCount, rc, nFormat, lpClipRect);
}

GX_INLINE int AFXAPI GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LPRECT lpClipRect, gxEllipseType gxFormatEx)
{
	return GXDaFTools()->GXDrawTextLikeMultiLineEditEx(pDC, lpszString, nCount, rc, nFormat, lpClipRect, gxFormatEx);
}

GX_INLINE int AFXAPI GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt)
{
	return GXDaFTools()->GXGetMultiLineTextPosUnderPt(pDC, lpszString, nCount, rect, nFormat, pt);
}

GX_INLINE int AFXAPI GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat)
{
	return GXDaFTools()->GXGetMultiLineTextBreakCount(pDC, lpszString, nCount, rc, nFormat);
}

GX_INLINE CString AFXAPI GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl )
{
	return GXDaFTools()->GXFormatText(style, pszValue, nValueType, pGrid, pControl);
}

GX_INLINE BOOL AFXAPI GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces)
{
	return GXDaFTools()->GXDeval(s, d, pImportFormat, pImportPlaces);
}

GX_INLINE int AFXAPI GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect)
{
	return GXDaFTools()->GXDrawRotatedText(pDC, lpszString, nCount, rc, nFormat, lfOrientation, lpClipRect);
}

GX_INLINE void AFXAPI GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w,
			  COLORREF rgbTopLeft, COLORREF rgbBottomRight)
{
	GXDaFTools()->GXDraw3dFrame(pDC, x0, y0, x1, y1, w,
			  rgbTopLeft, rgbBottomRight);
}

GX_INLINE void AFXAPI _GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge)
{
	GXDaFTools()->_GXDrawSunkenBorders(pDC, rc, bBorder, bClientEdge);
}

GX_INLINE void AFXAPI GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat)
{
	GXDaFTools()->GXDrawFocusText(pDC, rect, bFocus, lpszString, nFormat);
}

/////////////////////////////////////////////////////////////////////////////////
// CGXDIB  : Device independant bitmaps

GX_INLINE BOOL CGXDIB::LoadDIB(UINT nIDResource)
{
	return LoadDIB(MAKEINTRESOURCE(nIDResource));
}

GX_INLINE HANDLE CGXDIB::GetSafeHandle() const
{
	return this ? m_hbm : NULL;
}

GX_INLINE DWORD CGXDIB::GetColorCount()
{
	return m_dwColors;
}

GX_INLINE CSize CGXDIB::GetSize()
{
	return CSize(m_nWidth, m_nHeight);
}

/////////////////////////////////////////////////////////////////////////////
// CGXWaitCursor: hourglass wrapper

GX_INLINE CGXWaitCursor::CGXWaitCursor()
	{ AfxGetApp()->BeginWaitCursor(); }

GX_INLINE CGXWaitCursor::~CGXWaitCursor()
	{ AfxGetApp()->EndWaitCursor(); }

GX_INLINE void CGXWaitCursor::Restore()
	{ AfxGetApp()->RestoreWaitCursor(); }


/////////////////////////////////////////////////////////////////////////////
// class GRID_API CGXLongOperation

GX_INLINE void AFXAPI CGXLongOperation::SetAbortString(LPCTSTR s)
	{ GXGetWaitState()->m_sAbortText = s; GXGetWaitState()->m_bAbortDialog = TRUE; }

GX_INLINE void AFXAPI CGXLongOperation::SetFrameWnd(CWnd* pWnd)
	{ GXGetWaitState()->m_hFrameWnd = pWnd->GetSafeHwnd(); }

GX_INLINE void AFXAPI CGXLongOperation::SetAbortString(UINT nID)
	{ GXGetWaitState()->m_sAbortText.LoadString(nID); GXGetWaitState()->m_bAbortDialog = TRUE; }

GX_INLINE void AFXAPI CGXLongOperation::SetDefaultCancelText(LPCTSTR s)
	{ GXGetWaitState()->m_sDefaultCancelText = s; }

GX_INLINE void AFXAPI CGXLongOperation::SetDefaulDoneText(LPCTSTR s)
	{ GXGetWaitState()->m_sDefaultDoneText = s; }

GX_INLINE void AFXAPI CGXLongOperation::SetDefaultStatusText(LPCTSTR s)
	{ GXGetWaitState()->m_sDefaultStatusText = s; }

GX_INLINE void AFXAPI CGXLongOperation::SetTicksFirstTime(DWORD dw)
	{ GXGetWaitState()->m_dwTicksFirstTime = dw; }

GX_INLINE void AFXAPI CGXLongOperation::SetTicksContinued(DWORD dw)
	{ GXGetWaitState()->m_dwTicksContinued = dw; }

GX_INLINE int AFXAPI CGXLongOperation::GetCurrentLevel()
	{ 
		//---------------------------------------------- 
		// QA: 32120 
		// Assert caused by global variables  
		// from multiple instances of Grid,  
		// statically linked in an OCX or DLL, 
		// within a multi-threaded environment. 
		// See GXSTATE.h for CThreadLocal<...> updates. 
		//---------------------------------------------- 
		ASSERT(GXGetWaitState()->m_nRefCount > 0);
		return GXGetWaitState()->m_nRefCount-1; 
	} 

GX_INLINE BOOL AFXAPI CGXLongOperation::GetWaitCursorState()
	{ return GXGetWaitState()->m_bWaitCursor; }

GX_INLINE BOOL AFXAPI CGXLongOperation::GetAbortConfirmedState()
	{ return GXGetWaitState()->m_bUserConfirmed; }

GX_INLINE BOOL AFXAPI CGXLongOperation::GetRollbackConfirmedState()
	{ return GXGetWaitState()->m_bRollbackConfirmed; }

GX_INLINE BOOL AFXAPI CGXLongOperation::GetAbortState()
	{ return GXGetWaitState()->m_bCanceled; }

GX_INLINE LPCTSTR CGXLongOperation::GetStatusText() const
	{ return m_pszStatusText; }

GX_INLINE void CGXLongOperation::SetStatusText(UINT nID)
	{ CString s; s.LoadString(nID); SetStatusText(s); }

GX_INLINE void CGXLongOperation::SetCanRollback(BOOL bCanRollback)
	{ GXGetWaitState()->m_bCanRollback = bCanRollback; }

GX_INLINE void CGXLongOperation::SetCanAbort(BOOL bCanAbort)
	{ GXGetWaitState()->m_bCanAbort = bCanAbort; }

GX_INLINE void CGXLongOperation::SetLockedState(BOOL bLocked /*= TRUE*/)
	{   if (!GetLockedState())  // Do I have the right to change the lock state?
			GXGetWaitState()->m_nLevelLocked = bLocked ? GetCurrentLevel() : -1; }

GX_INLINE BOOL CGXLongOperation::GetLockedState()
	{ return GXGetWaitState()->m_nLevelLocked != -1 && GetCurrentLevel() > GXGetWaitState()->m_nLevelLocked; }
		// if operation is locked, only lower levels than the current level are unlocked

GX_INLINE DWORD CGXLongOperation::GetTickCount() const
	{ return ::GetTickCount()-m_nTickStart; }

GX_INLINE void CGXLongOperation::SetPercentDone(int nPercent)
	{   if (!GetLockedState())
			GXGetWaitState()->m_nPercentDone = __min(nPercent, 100); }

GX_INLINE void CGXLongOperation::SetUpdateStatusBar(BOOL b)
	{ m_bUpdateStatusBar = b; }

GX_INLINE void CGXLongOperation::SetResetStatusBar(BOOL b)
	{ m_bResetStatusBar = b; }

GX_INLINE BOOL CGXLongOperation::NeedMessages()
{
	return ::GetTickCount() - m_nLastTick
		> (GXGetWaitState()->m_bWaitCursor ? GXGetWaitState()->m_dwTicksContinued : GXGetWaitState()->m_dwTicksFirstTime);
}

#endif // GX_INLINE
