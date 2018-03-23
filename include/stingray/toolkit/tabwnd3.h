///////////////////////////////////////////////////////////////////////////////
// tabwnd3.h
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
//  Author:      Dean Hallman
//  Description: SEC3DTabWnd declaration
//  Created:     July 20, 1996
//
//	Modified:	  Feb. 1997 (Kim Starks)
//	Description:  Added tab disable feature			
//	

#ifndef __TABWND3_H__
#define __TABWND3_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TABCTRL3_H__
#include "toolkit\tabctrl3.h"
#endif

#ifndef __TABWNDB_H__
#include "toolkit\tabwndb.h"
#endif

#ifndef __TABWND_H__
#include "toolkit\tabwnd.h"
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

/////////////////////////////
// AutoDuck tag block block for SEC3DTabWnd 

//@doc SEC3DTabWnd
//@mfunc DWORD  | SEC3DTabWnd | GetTabStyle | Call this function to get the styles for the tab.
//@rdesc Tab Styles. 
//@xref <c SEC3DTabWnd> <mf SEC3DTabWnd::SetTabStyle> 

// adinsert AutoDuck insertion point for SEC3DTabWnd 
//@doc SEC3DTabWnd 
//@class The SEC3DTabWnd class implements a tab control with a three-dimensional look and feel 
// (similar to Developer Studio’s Project Workspace window).  
//@comm
// The 3-D tabs can be positioned on the top, bottom, left or right.  The SEC3DTabWnd 
// inherits its interface from <c SECTabWndBase> and adds the implementation details that define its 
// appearance.
//
// Note: The top, left and right tab position styles are supported only by the 3-D tabs and these 
// do not apply to the 2-D tabs.
//
// A SEC3DTabWnd object can be embedded in any CWnd object. To create an SEC3DTabWnd object in a CFrameWnd, use the 
// following steps:
//
// 1.	Embed an SEC3DTabWnd member variable in the parent frame.<nl>
// 2.	Override the parent frame's OnCreateClient member function.<nl>
// 3.	From within the overridden OnCreateClient, call the Create member function of SEC3DTabWnd.<nl>
// 4.	Call SEC3DTabWnd::AddTab at any time during the life of the tabbed window to create a CWnd or CView child window
// in the tabbed window.
//
// See the TABDEMO sample in the \SAMPLES\TOOLKIT\STANDARD\TABS\TABDEMO directory for a 
// demonstration of the SEC3DTabWnd class.
//@xref <c SECTabWndBase> <c SEC3DTabControl> <c SECWorkbook>
//@BASE public | SECTabWndBase
class SEC3DTabWnd : public SECTabWndBase
{
    TOOLKIT_DECLARE_DYNCREATE(SEC3DTabWnd)
    
// Construction
public:
	//@Access Constructors
	//@cmember
	/* todo Add a description*/
    TOOLKIT_API SEC3DTabWnd();

    TOOLKIT_API virtual ~SEC3DTabWnd();

	//@Access Initialization
	//@cmember
	/* todo Add a description*/
    TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | TWS_TABS_ON_BOTTOM,
		                            UINT nID = AFX_IDW_PANE_FIRST);

protected:    
	TOOLKIT_API virtual BOOL CreateTabCtrl(DWORD dwStyle, UINT nID);


public:

	//@Access Operations
	//@cmember
	/* Gets tab style.*/
	DWORD GetTabStyle() const { return m_dwTabCtrlStyle; }

	//@cmember
	/* Sets the tab style.*/
	TOOLKIT_API DWORD SetTabStyle(DWORD dwTabStyle);

	//@cmember
	/* Enables/disables tab.*/
    TOOLKIT_API void EnableTab(CWnd* pWnd, BOOL bEnable = TRUE);

	//@cmember
	/* Enables/disables tab.*/
    TOOLKIT_API void EnableTab(int nIndex, BOOL bEnable = TRUE);

	//@cmember
	/* Sets an active tab's currrent font.*/
	TOOLKIT_API BOOL SetFontActiveTab(CFont* pFont,BOOL bRedraw=TRUE);

	//@cmember
	/* Sets an inactive tab's currrent font.*/
	TOOLKIT_API BOOL SetFontInactiveTab(CFont* pFont,BOOL bRedraw=TRUE);

	//@cmember
	/* Gets the current font of an active tab.*/
	TOOLKIT_API CFont* GetFontActiveTab();


	//@cmember
	/* Gets the current font of an inactive tab.*/
	TOOLKIT_API CFont* GetFontInactiveTab(); 			

// Attributes
	//@Access Attributes
	//@cmember
	/* Determines if tab is enabled or disabled.*/
	TOOLKIT_API BOOL IsTabEnabled(CWnd* pWnd);

	//@cmember
	/* Determines if tab is enabled or disabled.*/
	TOOLKIT_API BOOL IsTabEnabled(int nIndex);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SEC3DTabWnd)
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL
    
// Implementation
private:
	TOOLKIT_API void VLine3D(CDC* pDC, int x, int y, int nHeight, BOOL bLeft = FALSE);
	TOOLKIT_API void HLine3D(CDC* pDC, int x, int y, int nWidth, BOOL bFlip = FALSE);

protected:
    int m_cyTabCtrl;
	int m_cxTabCtrl;
	DWORD m_dwTabCtrlStyle;

    TOOLKIT_API void rgbFill(CDC* pDC,int x,int y,int cx,int cy, COLORREF rgb);
    TOOLKIT_API virtual void GetInsideRect(CRect& rect) const;
    TOOLKIT_API virtual void RecalcLayout();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(SEC3DTabWnd)
    TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    TOOLKIT_API afx_msg LRESULT OnTabSelect(WPARAM wParam, LPARAM lParam);
#ifndef UNDER_CE
	TOOLKIT_API afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpcs);
#endif //UNDER_CE (WindowsCE)
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnChildActivate();
	//}}AFX_MSG
	TOOLKIT_API afx_msg void OnSysColorChange();

    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TABWND3_H__

