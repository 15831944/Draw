///////////////////////////////////////////////////////////////////////////////
// GXSCRLTP.h : header file for the CGXScrollTip class
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

/////////////////////////////////////////////////////////////////////////////
// CGXScrollTip window

#ifndef _GXSCRLTP_H_
#define _GXSCRLTP_H_

#if _MFC_VER >= 0x0400

// // #include <StingrayExportDefs.h>

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

class CGXScrollTip : public CWnd
{
// Construction
public:
	GRID_API CGXScrollTip();

// Attributes
public:
	HFONT           m_hFont;        // font to use for text

// Operations
public:
	GRID_API BOOL HandleThumbTrackMessage(CWnd * pParent, int nBar, LPCTSTR pszText, CScrollBar * pBar);
	GRID_API BOOL HandleScrollMessage(CWnd * pParent,
							UINT nSBCode,
							int nBar,           // SB_VERT or SB_HORZ
							LPCTSTR pszText,
							CScrollBar * pBar);  // pointer to the scrollbar

	GRID_API BOOL Create(CWnd * pParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXScrollTip)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXScrollTip();
	GRID_API static CPoint AFXAPI GetSliderPositionHelper(CWnd * pParent, int nBar, CScrollBar * pBar, CSize sizeText = CSize(0,0));
	GRID_API void SaveBackground(CWnd* pWnd, const CRect& rect);
	GRID_API void RestoreBackground(CWnd* pWnd);

// Double buffering
	CBitmap m_bmBackground;
	HBITMAP m_hbmBackgroundOld;
	CDC		m_dcBackground;
	CRect	m_rcBackground;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXScrollTip)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXScrollTipPlugin window

class CGXScrollTipPlugin : public CGXPluginComponent
{
// Construction
public:
	GRID_API CGXScrollTipPlugin(CGXGridCore* pGrid = NULL);

// Attributes
public:
	CGXScrollTip*   m_pScrollTip;
	CGXGridCore*	m_pGrid;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXScrollTipPlugin)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXScrollTipPlugin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXScrollTipPlugin)
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
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

#endif
/////////////////////////////////////////////////////////////////////////////
