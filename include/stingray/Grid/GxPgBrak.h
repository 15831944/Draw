///////////////////////////////////////////////////////////////////////////////
// GxPgBrak.h
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

#ifndef _GXPGBRAK_H_
#define _GXPGBRAK_H_

// #include <StingrayExportDefs.h>

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _GXVW_H_
#include "gxvw.h"
#endif//_GXVW_H_

/////////////////////////////////////////////////////////////////////////////
// CGXPageBreakPlugin window
const int NONEEDGE = 0;
const int HORZEDGE = 1;
const int VERTEDGE = 2;

#include <vector>
#include <algorithm>

struct CGXPageLabelInfo
{
	CRect rc;
	CString strText;
	inline CGXPageLabelInfo(const CRect& rect, CString s)
		: rc(rect), strText(s)
	{
	}
	inline CGXPageLabelInfo()
		: rc(0, 0, 0, 0), strText(_T(""))
	{
	}
};

struct CGXBreakLineInfo
{
	CRect rc;
	BOOL bCustom;
	inline CGXBreakLineInfo(const CRect& rect, BOOL b = FALSE)
		: rc(rect), bCustom(b)
	{}
	inline CGXBreakLineInfo()
		: rc(0, 0, 0, 0), bCustom(FALSE)
	{}
};

/////////////////////////////
// AutoDuck tag block block for CGXPageBreakPlugin 

//@doc CGXPageBreakPlugin
//@mdata static HCURSOR  | CGXPageBreakPlugin | m_hV2Arrow | Mouse cursor when mouse on vertical page break lines

//@doc CGXPageBreakPlugin
//@mdata static HCURSOR  | CGXPageBreakPlugin | m_hH2Arrow | Mouse cursor when mouse on horizontal page break lines

//@doc CGXPageBreakPlugin
//@mdata BOOL   | CGXPageBreakPlugin | m_bDrawPageBreak | Flag if the view is in page break mode

//@doc CGXPageBreakPlugin
//@mdata int    | CGXPageBreakPlugin | m_nPageBreakLineWidth | Page break line width

//@doc CGXPageBreakPlugin
//@mdata COLORREF  | CGXPageBreakPlugin | m_clrCustomBreakLine | Color of custom page break lines

//@doc CGXPageBreakPlugin
//@mdata COLORREF  | CGXPageBreakPlugin | m_clrDefaultBreakLine | Color of internal page break lines

//@doc CGXPageBreakPlugin
//@mdata COLORREF  | CGXPageBreakPlugin | m_clrLabel | Color of the page label text when in page break mode

//@doc CGXPageBreakPlugin
//@mdata vector<CGXBreakLineInfo>   | CGXPageBreakPlugin | m_vecPageRow | A vector of horizontal break line info

//@doc CGXPageBreakPlugin
//@mdata vector<CGXBreakLineInfo>   | CGXPageBreakPlugin | m_vecPageCol | A vector of vertical break line info

//@doc CGXPageBreakPlugin
//@mdata vector<CGXPageLabelInfo>  | CGXPageBreakPlugin | m_vecPageLabels | A vector of the page label info

//@doc CGXPageBreakPlugin
//@mdata CGXGridViewFriendship  | CGXPageBreakPlugin | *m_pView | The view this plugin plugs into

// adinsert AutoDuck insertion point for CGXPageBreakPlugin 
//@topic CGXPageBreakPlugin  Class Overview |
//This plugin add page break UI support for Objective Grid. 
//To use the plugin, you need to put an instance of this class in your CGXGridView derivative
//class, then typically, in your OnInitialUpdate function of your view class, call the
//Plugin function of this class with your view class as the single argument. You can 
//change the page break line color and page label text color. There are two types of break lines.
//One is the customer set break line, the other is the line created by the Grid system.
//They are drawn using two different color. When you drag a break line created by the Grid
//system, this line will become a customer break line. Currently, Grid doesn't do scaling. So 
//when user resize the page and the page is too big for Grid system to draw it on one page, 
//the grid system will automatic add some page break lines for you.
//

//@doc CGXPageBreakPlugin 
//@class Objective Grid page break UI plugin
class CGXPageBreakPlugin : public CWnd
{
// Construction
public:
	GRID_API CGXPageBreakPlugin();

	//@cmember
	/* Mouse cursor when mouse is on the vertical break lines */
	GRID_API static HCURSOR	m_hV2Arrow;
	//@cmember
	/* Mouse cursor when mouse is on the horizontal break lines */
	GRID_API static HCURSOR	m_hH2Arrow;

// Attributes
public:
	
	BOOL	m_bSkipOtherPlugins;
	BOOL	m_bExitMessage;

	//@cmember
	/* Flag if the view is in the page break mode or not */
	BOOL		m_bDrawPageBreak;
	//@cmember
	/* Width of the page break lines */
	int			m_nPageBreakLineWidth;
	//@cmember
	/* Color of custom break lines */
	COLORREF	m_clrCustomBreakLine;
	//@cmember
	/* Color of internal break lines */
	COLORREF	m_clrDefaultBreakLine;
	//@cmember
	/* Color of the page label text */
	COLORREF	m_clrLabel;

	//@cmember
	/* A vector of the horizontal break line info */
	std::vector<CGXBreakLineInfo>		m_vecPageRow;
	//@cmember
	/* A vector of the vertical break line info */
	std::vector<CGXBreakLineInfo>		m_vecPageCol;

	//@cmember
	/* A vector of the page label info */
	std::vector<CGXPageLabelInfo>	m_vecPageLabels;

	//@cmember
	/* The view this plugin plugs into */
	//CGXGridView				*m_pView;
	CGXGridCore*		    m_pGrid;  
	CGXView*				m_pView;
 
	BOOL					m_bFitToPages;
	int						m_nColPages;
	int						m_nRowPages;

	CSize					m_pageSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXPageBreakPlugin)
protected:
	GRID_API virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual BOOL DoBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	GRID_API virtual void DoPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	GRID_API void SetPageGrid(int nRowCount, int nColCount, BOOL bFitTo = TRUE);
	GRID_API virtual void CalcPageSize(CDC* pDC);
	//@cmember
	/* switch the page break mode */
	GRID_API virtual void SetPageBreakMode(BOOL bPageBreakMode);
	//@cmember
	/* This plugin's drawing control point */
	GRID_API virtual void DoDraw(CDC* pDC);
	//@cmember
	/* Draw the page break lines and page labels */
	GRID_API virtual void DrawPageBreak(CDC* pDC);
	//@cmember
	/* Test if a value is in the array */
	GRID_API BOOL IsValueInArray(const CDWordArray& aw, int value);
	//@cmember
	/* Calculate the page break line position and page labels */
	GRID_API virtual void CalcFinalPosition();
	//@cmember
	/* Create the page break lines position in term of row-col index */
	GRID_API virtual void CreatePageBreak();
	//@cmember
	/* Update the page break lines position in term of row-col index */
	GRID_API virtual void UpdatePageBreak(LPRECT pRect, int nHitTest, LPRECT pInitRect);
	//@cmember
	/* Adjust the dragging break line position */
	GRID_API virtual void AdjustRect(LPRECT pRect, int nHitTest);
	//@cmember
	/* Hit test for page break line dragging */
	GRID_API virtual int HitTestPageBreak(CPoint pt, LPRECT pRect);
	//@cmember
	/* Plug this plugin into the income view class */
	GRID_API virtual void Plugin(CGXGridCore* pView);
	//@cmember
	/* Central message handle function called by the view this plugin plugged into */
	GRID_API virtual BOOL HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	GRID_API virtual ~CGXPageBreakPlugin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXPageBreakPlugin)
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _GXPGBRAK_H_
