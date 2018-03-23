///////////////////////////////////////////////////////////////////////////////
// tabwnd.h
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
//  Author:			Dean Hallman
//  Description:	SECTabWnd declaration
//

#ifndef __TABWND_H__
#define __TABWND_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TABCTRL_H__
#include "toolkit\tabctrl.h"
#endif

#ifndef __TABWNDB_H__
#include "toolkit\tabwndb.h"
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

// Tab Window Styles
#define TWS_LEFTRIGHTSCROLL	0x0001
#define TWS_FULLSCROLL		0x0002

#define TWS_FLATSTYLE		0x0008

#define TWS_TABS_ON_BOTTOM	0x0010
#define TWS_TABS_ON_TOP		0x0020
#define TWS_TABS_ON_LEFT	0x0040
#define TWS_TABS_ON_RIGHT	0x0080

#define TWS_TAB_ORIENTATIONS 0x00f0

#define TWS_NOACTIVE_TAB_ENLARGED	0x0100
#define TWS_DRAW_STUDIO_LIKE		0x0200
#define TWS_DRAW_3D_NORMAL			0x0400
#define TWS_DYNAMIC_ARRANGE_TABS	0x0800
#define TWS_TAB_DRAW_STYLES			0x0f00

/////////////////////////////
// AutoDuck tag block block for SECTabWnd 

// adinsert AutoDuck insertion point for SECTabWnd 
//@doc SECTabWnd 
//@class The SECTabWnd class implements a tabbed window with a two-dimensional (Excel-like) look and feel.
//@comm
// SECTabWnd inherits its interface from <c SECTabWndBase> and adds the implementation details that 
// define its appearance.
//
// An SECTabWnd object can be embedded in any CWnd object.  To create an SECTabWnd object in a 
// CFrameWnd, use the following steps:
//
// 1.	Embed an SECTabWnd member variable in the parent frame.<nl>
// 2.	Override the parent frame’s OnCreateClient member function.<nl>
// 3.	From within the overridden OnCreateClient, call the Create member function of SECTabWnd.<nl>
// 4.	Call SECTabWnd::AddTab at any time during the life of the tabbed window to create a CWnd or CView child window in 
// the tabbed window.
//
// Note: <mf SECTabWnd::AddTab> method adds to a tab to the end of a series of tabs (i.e., appends a tab).  
// <mf SECTabWnd::InsertTab> inserts a tab to a specific location in a series of tabs.
//
// See the TABDEMO sample in the \SAMPLES\TOOLKIT\STANDARD\TABS\TABDEMO directory for a demonstration of the SECTabWnd class.
//@xref<c SECTabWndBase> <c SECTabControl> <c SECWorkbook>
//@BASE public | SECTabWndBase
class SECTabWnd : public SECTabWndBase
{
    TOOLKIT_DECLARE_DYNCREATE(SECTabWnd)
    
// Construction
public:
	//@Access Constructors
	//@cmember
	/* Constructs an SECTabWnd object.*/
    TOOLKIT_API SECTabWnd();
    TOOLKIT_API virtual ~SECTabWnd();

	//@Access Initializations
	//@cmember
	/* Creates the Windows window and attaches it to the SECTabWnd object.*/
    TOOLKIT_API BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE |
    		WS_HSCROLL | WS_VSCROLL | TWS_FULLSCROLL | TWS_TABS_ON_BOTTOM,
			UINT nID = AFX_IDW_PANE_FIRST);

protected: 
	//@cmember
	/* Creates a tab control in the style specified.*/
	TOOLKIT_API virtual BOOL CreateTabCtrl(DWORD dwStyle, UINT nID);

// Operations
public:
	//@Access Operations
	//@cmember
	/* Inserts a new tab into the tabbed window.*/
    TOOLKIT_API virtual SECTab* InsertTab(CWnd* pWnd, int nIndex, LPCTSTR lpszLabel);
	
	//@cmember
	/* Inserts a new tab into the tabbed window.*/
	inline virtual SECTab* InsertTab(CRuntimeClass* pViewClass, int nIndex,
		                             LPCTSTR lpszLabel, CCreateContext* pContext = NULL, UINT nID = -1)
	{
		return SECTabWndBase::InsertTab(pViewClass, nIndex, lpszLabel, pContext, nID);
	}

	//@cmember
	/* Removes a tab.*/
	TOOLKIT_API virtual void RemoveTab(int nIndex);

	//@cmember
	/* Sets the scrolling style for a tab.*/
	TOOLKIT_API virtual void SetScrollStyle(int nTab, DWORD dwStyle);

	//@cmember
	/* Activates a specific tab.*/
    TOOLKIT_API virtual BOOL ActivateTab(CWnd* pWnd, int nIndex);

	//@cmember
	/* Activates a specific tab.*/
    inline virtual BOOL ActivateTab(CWnd* pWnd) { return SECTabWndBase::ActivateTab(pWnd); };

	//@cmember
	/* Activates a specific tab.*/
    inline virtual BOOL ActivateTab(int nIndex) { return SECTabWndBase::ActivateTab(nIndex); };

	//@cmember
	/* Returns a pointer to the CScrollBar object used by a particular tab.*/
    TOOLKIT_API virtual CScrollBar* GetScrollBar(int nBar, const CWnd* const pWnd = NULL) const;

	// font support

	//@cmember
	/* Sets a selected tab’s current font.*/
	TOOLKIT_API BOOL SetFontSelectedTab(CFont* pFont,BOOL bRedraw=TRUE);

	//@cmember
	/* Sets an unselected tab’s current font.*/
	TOOLKIT_API BOOL SetFontUnselectedTab(CFont* pFont,BOOL bRedraw=TRUE); 
	
	//@cmember
	/* Sets an active tab’s currrent font.*/
	TOOLKIT_API BOOL SetFontActiveTab(CFont* pFont,BOOL bRedraw=TRUE);
	
	//@cmember
	/* Gets the current font of a selected tab.*/
	TOOLKIT_API CFont* GetFontSelectedTab(); 
	
	//@cmember
	/* Gets the current font of an unselected tab.*/
	TOOLKIT_API CFont* GetFontUnselectedTab(); 	
	
	//@cmember
	/* Gets the current font of an active tab.*/
	TOOLKIT_API CFont* GetFontActiveTab();

// Overrides5
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECTabWnd)
    //}}AFX_VIRTUAL
    
// Implementation
protected:
    int m_cxTabCtrl;
    int m_cyTabCtrl;
    int m_cxVScroll;
    int m_cyHScroll;
    int	m_cxSplitter;
    int m_nTrackOffset;
    BOOL m_bTracking;
    BOOL m_bSplitterHit;
    BOOL m_bFirstSize;
    HCURSOR m_hcurSplit;
    HCURSOR m_hcurArrow;
	DWORD m_dwTabCtrlStyle;
#ifdef WIN32
	CPtrArray m_arrHScrollInfo;
	CPtrArray m_arrVScrollInfo;
#endif
	CDWordArray m_arrScrollStyles;

    TOOLKIT_API void GetSplitterRect(CRect& rectSplit);
    TOOLKIT_API void OnDrawSplitter(CDC* pDC, const CRect& rect);
    TOOLKIT_API void rgbFill(CDC* pDC,int x,int y,int cx,int cy, COLORREF rgb);
    TOOLKIT_API void GetInsideRect(CRect& rect) const;
    TOOLKIT_API void RecalcLayout();

    // Generated message map functions
protected:
    //{{AFX_MSG(SECTabWnd)
    TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg LRESULT OnTabSelect(WPARAM wParam, LPARAM lParam);
    TOOLKIT_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    TOOLKIT_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
#ifndef UNDER_CE
	TOOLKIT_API afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpcs);
#endif //UNDER_CE (WindowsCE)
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

// For naming uniformity and backward compatibility,
// you can call it SECTabWnd or SEC2DTabWnd.
class SEC2DTabWnd : public SECTabWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SEC2DTabWnd)
    
// Construction
public:
    TOOLKIT_API SEC2DTabWnd();
    TOOLKIT_API virtual ~SEC2DTabWnd();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TABWND_H__

