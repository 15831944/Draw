///////////////////////////////////////////////////////////////////////////////
// gxctwnd.h
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
/////////////////////////////////////////////////////////////////////////////////
// Author: Ricky Pearson
//
// gxctwnd.h : header file for the CGXCellTipWnd class
//

//RWP02a (entire file)

#ifndef _GXCTWND_H_
#define _GXCTWND_H_

#if _MFC_VER >= 0x0400

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif


/////////////////////////////////////////////////////////////////////////////
// _gxCellTipWndHelper

class _gxCellTipWndHelper
{
public:
	GRID_API static CString GetText(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static CSize GetTextSize(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static CPoint GetTextTopLeft(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static CPoint GetBitmapTopLeft(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static CRect GetAdjustedCellRect(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static CRect GetVisibleTextRect(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static UINT GetBitmapClipping(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static UINT GetTextClipping(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	GRID_API static UINT GetClippingOutsideCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CRect* rcData);
};


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWnd

class CGXCellTipWnd : public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXCellTipWnd)

// Construction
public:
	inline CGXCellTipWnd(){ASSERT(0);};
	GRID_API CGXCellTipWnd(CGXGridCore* pGrid);

// Attributes
public:
	CGXGridCore*	m_pGrid;	// "Parent" grid

protected:
	DWORD			m_dwID;		// Cell tip ID for this class

	// Double buffering for background saves
	CBitmap			m_bmBackground;
	HBITMAP			m_hbmBackgroundOld;
	CDC				m_dcBackground;
	CRect			m_rcBackground;

// Operations
public:
	GRID_API virtual BOOL CreateTipWnd();

// Implementation
public:
	GRID_API virtual ~CGXCellTipWnd();
	GRID_API virtual BOOL Show();
	GRID_API virtual BOOL Hide();

	inline DWORD GetID()	{ return m_dwID; }

protected:
	GRID_API void SaveBackground(CWnd* pWnd, const CRect& rect);
	GRID_API void RestoreBackground(CWnd* pWnd);
	GRID_API virtual void ForwardMouseMessage(UINT nFlags, CPoint point);
	GRID_API virtual void ForwardMessage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCellTipWnd)
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGXTextCellTipWnd

class CGXTextCellTipWnd : public CGXCellTipWnd
{
	GRID_DECLARE_DYNAMIC(CGXTextCellTipWnd)

// Construction
public:
	GRID_API CGXTextCellTipWnd(CGXGridCore* pGrid);

// Attributes
public:

protected:
	CGXFont	m_font;				// Font for cell tip text
	CBrush	m_brBackground;		// Brush for cell tip background
	CRect	m_rcText;			// Rect for cell text

// Operations
public:
	GRID_API virtual BOOL CreateTipWnd();
	GRID_API void SetFont(CGXFont& font);
	GRID_API void SetText(CString& strText);
	GRID_API void SetTipRect(CRect& rcTip);
	GRID_API void SetTextRect(CRect& rcText);

	GRID_API CRect GetTextRect();

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCellTipWnd)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGXStaticBitmapCellTipWnd

class CGXStaticBitmapCellTipWnd : public CGXCellTipWnd
{
	GRID_DECLARE_DYNAMIC(CGXStaticBitmapCellTipWnd)

// Construction
public:
	GRID_API CGXStaticBitmapCellTipWnd(CGXGridCore* pGrid);

// Attributes
public:

protected:
	CBrush	m_brBackground;	// Brush for cell tip background
	HANDLE  m_hBitmap;		// Handle to cell's bitmap
	CRect	m_rcBitmap;		// Rect to draw bitmap in

// Operations
public:
	GRID_API virtual BOOL CreateTipWnd();
	GRID_API void SetBitmapHandle(HANDLE hBitmap);
	GRID_API void SetTipRect(CRect rcTip);
	GRID_API void SetBitmapRect(CRect& rcBitmap);

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXStaticBitmapCellTipWnd)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _MFC_VER

#endif //_GXCTWND_H_
