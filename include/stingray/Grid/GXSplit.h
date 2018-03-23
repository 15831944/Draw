///////////////////////////////////////////////////////////////////////////////
// GXSplit.h
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

// gxsplit.h : interface for CGXSplitterWnd class
//

#ifndef _GXSPLIT_H_
#define _GXSPLIT_H_

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

#define GX_IDW_INSIDE_FIRST           0x8A00  // first inside window

enum GXSplitterBoxPos
{
	gxLeft = 0,
	gxTop = 1,
	gxRight = 2,
	gxBottom = 3
};

struct CGXInsideWndState
{
	GRID_API CGXInsideWndState();
	GRID_API ~CGXInsideWndState();

	CWnd*	pWnd;
	int     nAlign;
	CSize	size;
	CSize	sizeMin;
	CSize	sizeBox;
	BOOL	bResizable;
	long	lRelSize;
	int     ndx;

	// will be assigned in RecalcLayout
	CRect	rectWnd;
	CRect	rectBox;
	CSize	sizeMax;
};

/////////////////////////////////////////////////////////////////////////////
// CGXSplitterWnd window

class CGXSplitterWnd : public CSplitterWnd
{
	GRID_DECLARE_DYNAMIC(CGXSplitterWnd);
// Construction
public:
	GRID_API CGXSplitterWnd();

// Attributes
public:
	int m_nvSplitterBoxPos,		// position of splitboxes 
		m_nhSplitterBoxPos;

	BOOL m_bTrackBox;

	CGXInsideWndState*	m_apInsideWndState[4];

// Operations
public:
	GRID_API virtual void RecalcLayout();    // call after changing sizes

	// starting and stopping tracking
	GRID_API virtual void StartTracking(int ht);
	GRID_API virtual void StopTracking(BOOL bAccept);
	GRID_API void GetHitRect(int ht, CRect& rect);
	GRID_API int HitTest(CPoint pt) const;

	GRID_API CRect GetSplitterBoxRect(int ht) const; //%%
	GRID_API virtual void OnDrawInsideSplitter(CDC* pDC, GXSplitterBoxPos nType, CGXInsideWndState* pState);
	GRID_API void SetSplitCursor(int ht);

#if _MFC_VER < 0x0400
	// determining active pane from focus or active view in frame
	GRID_API virtual CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	GRID_API virtual void SetActivePane(int row, int col, CWnd* pWnd = NULL);
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXSplitterWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXSplitterWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXSplitterWnd)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
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

//

#endif //_GXSPLIT_H_
