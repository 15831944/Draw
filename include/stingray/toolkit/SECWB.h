///////////////////////////////////////////////////////////////////////////////
// SECWB.h
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
//  Description:	Declarations for Worksheet, Workbook, and WorkbookClient
//

#ifndef __SECWB_H__
#define __SECWB_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SWINMDI_H__
#include "toolkit\swinmdi.h"
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

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

// User-defined message sent to the SECWorkbookWnd class
#define SECWB_WM_ACTIVATIONCHANGED  (WM_USER + 1101)

// User-defined message sent to the SECWorkbookClientWnd class
#define SECWB_WM_USINGMENUBARS		(WM_USER + 1102)

class SECWorkbookWnd;

/////////////////////////////
// AutoDuck tag block block for SECWorksheetWnd 
// adinsert AutoDuck insertion point for SECWorksheetWnd 
//@doc SECWorksheetWnd 
//@class The SECWorksheetWnd class is an MDI child window that can viewed as an individual worksheet in an SECWorkbookWnd when
// in workbook mode.  To use SECWorksheetWnd, derive your MDI child window classes from SECWorksheetWnd rather than 
// SECMDIChildWnd.  There are no public operations or member variables defined by SECWorksheetWnd.
//@comm See the WORKBPAD sample in the \SAMPLES\TOOLKIT\STANDARD\MDI\WORKBPAD directory for a demonstration of this class.
//@xref<c SECWorkbookWnd>
//@BASE public|SECMDIChildWnd
class SECWorksheetWnd : public SECMDIChildWnd
{
    friend class SECWorkbookWnd;
    TOOLKIT_DECLARE_DYNCREATE(SECWorksheetWnd);
    
// Construction
public:
    TOOLKIT_API SECWorksheetWnd();

// Implementation
protected:
    HICON	m_hIcon;	// Icon for this window
    int		m_nPosition;	// Position of tab within array
    BOOL	m_bSelected;    // True if the tab is selected but
				//   the frame isn't yet active

    TOOLKIT_API SECWorkbookWnd* GetWorkbook();
    TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext = NULL);
	TOOLKIT_API virtual void OnUpdateFrameMenu( BOOL bActive, CWnd* pActiveWnd, HMENU hMenuAlt );
	TOOLKIT_API virtual void OnUpdateFrameTitle( BOOL bAddToTitle );
    
public:
    TOOLKIT_API virtual ~SECWorksheetWnd();
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    //{{AFX_MSG(SECWorksheetWnd)
    TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	TOOLKIT_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnParentNotify( UINT message, LPARAM lParam );
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

#ifndef _DEBUG  // debug version in secwb.cpp
inline SECWorkbookWnd* SECWorksheetWnd::GetWorkbook(){ return (SECWorkbookWnd*)GetMDIFrame(); };
#endif

/////////////////////////////
// AutoDuck tag block block for SECWorkbookClientWnd 
// adinsert AutoDuck insertion point for SECWorkbookClientWnd 
//@doc SECWorkbookClientWnd 
//@class Utility class used in the implementation of SECWorkbookWnd. This class is derived from CWnd.
//@xref<c SECWorkbookWnd>
//@BASE public|CWnd
class SECWorkbookClientWnd : public CWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECWorkbookClientWnd);
	
// Construction
public:
    TOOLKIT_API SECWorkbookClientWnd();
    
// Operations
public:
    TOOLKIT_API void SetMargins(int left, int right, int top, int bottom);
    TOOLKIT_API void GetMargins(int& left, int& right, int& top, int& bottom);
    
// Implementation
protected:
    CRect m_margins;	// Space between frame border and MDI Client
    TOOLKIT_API virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType);
    TOOLKIT_API SECWorkbookWnd* GetWorkbook();

public:
    TOOLKIT_API virtual ~SECWorkbookClientWnd();
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif
    
// Generated message map functions
protected:
    //{{AFX_MSG(SECWorkbookClientWnd)
	TOOLKIT_API afx_msg LRESULT OnMDISetMenu(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

#ifndef _DEBUG  // debug version in secwb.cpp
inline SECWorkbookWnd* SECWorkbookClientWnd::GetWorkbook() { return (SECWorkbookWnd*)GetParent(); };
#endif

/////////////////////////////
// AutoDuck tag block block for SECWorkbookWnd 


// adinsert AutoDuck insertion point for SECWorkbookWnd 
//@doc SECWorkbookWnd 
//@class The SECWorkbookWnd is a Windows multiple document interface (MDI) frame window that adds the 
// capability to view the MDI child windows as worksheets in a workbook.  
//@comm
// Tool tips are now present for workbook tab text that is partially or fully obscured.  This is 
// new with release 5.0 of Objective Toolkit.
//
// SECWorkbookWnd inherits most of its functionality from SECMDIFrameWnd with the workbook viewing 
// mode being an extension. This workbook view capability provides an alternative, tab-based user 
// interface for managing multiple documents.  An SECWorkbookWnd-based application can operate in either 
// normal or workbook mode, and the user can switch between these modes at runtime.  In normal mode, 
// the application appears and functions exactly like an MDI application.  In workbook mode, the MDI 
// child windows are presented as a collection of worksheets with cascaded tabs for navigation (i.e., 
// selecting a tab activates the associated MDI child window).
//
// When the workbook mode is switched on, the MDICLIENT window is resized to provide room for tabs 
// to be drawn.  One tab is drawn for each MDI child window.  In the description of the class’s 
// operations given below, it is important to note that a worksheet and an MDI child window are one 
// and the same, since <c SECWorksheetWnd> is derived from <c SECMDIChildWnd>.
//
// NOTE: Workbook mode can be in effect without maximizing the MDI child windows.
//
// To create a workbook-based application, derive the CMainFrame class (or your equivalent class) 
// from SECWorkbookWnd instead of CMDIFrameWnd.  In addition, add a "Workbook" item on the "View" menu, 
// and map its command and update handlers to <mf SECWorkbookWnd::OnViewWorkbook> and 
// <mf SECWorkbookWnd::OnUpdateViewWorkbook>, respectively.
//
// For example, your CMainFrame class message map would have the following entries:
//
//	BEGIN_MESSAGE_MAP(CMainFrame, SECWorkbookWnd)<nl>
//		//{{AFX_MSG_MAP(CMainFrame)<nl>
//			ON_WM_CREATE()<nl>
//			ON_COMMAND(ID_VIEW_WORKBOOK, OnViewWorkbook)<nl>
//		//}}AFX_MSG_MAP<nl>
//	END_MESSAGE_MAP()
//
// Adding "workbook" handlers to your pulldown menus is optional.  The user can just hardcode the 
// workbook to be always on.
// 
// See the WORKBPAD sample in the \SAMPLES\TOOLKIT\STANDARD\MDI\WORKBPAD directory for a demonstration of 
// this class.
//@xref<c SECWorksheetWnd>
//@BASE public|SECMDIFrameWnd
class SECWorkbookWnd : public SECMDIFrameWnd
{
    friend class SECWorksheetWnd;
    TOOLKIT_DECLARE_DYNCREATE(SECWorkbookWnd);

// Construction
public:
	
    TOOLKIT_API SECWorkbookWnd();

// Attributes
public:
	TOOLKIT_API virtual void GetFullWorkbookRect(CRect& rectFullWorkbook);

    CObArray m_worksheets;		// List of worksheets
    BOOL	m_bWorkbookMode;	// Are we in workbook mode?
    BOOL	m_bShowIcons;		// Show document icons on the tabs?
    CFont	m_fontTab;		// The font to use for tab labels
    int		m_nScrollOffset;	// Amount to displace tab offset by
    SECWorkbookClientWnd* m_pWBClient;	// The MDI client
    CPen	m_penWhite, m_penBlack, m_penShadow, m_penFace;
    int		m_cxTab;		// Width of tab 
    int		m_cyTab;		// Height of tab
    int		m_cxFold;		// Width of fold in the tab
	int		m_cxActive;		// Extra tab width when active
	int		m_cyActive;		// Extra tab height when active
	int		m_nMaxTabWidth;
    CRect	m_rectClientLast;	// Redraw hint   

	BOOL	m_bFlatStyleMode; //

	// Set to TRUE for the workbook to paint properly as an OLE
	// container. If not using OLE containment, it is recommended
	// you not reset to maintain less flicker.
	BOOL	m_bSupportOleContainer;

protected:

	int m_nActiveWorksheet;
	HTHEME m_hTabTheme;

// Overridables
protected:
	TOOLKIT_API virtual BOOL OnNewWorksheetSelected(SECWorksheetWnd* pSheet);
	TOOLKIT_API virtual CMDIChildWnd* CreateFloatingMDIChild(DWORD dwStyle, CControlBar* pBar = NULL);

// Implementation
protected:

    TOOLKIT_API void GetTabRgn(SECWorksheetWnd* pSheet, CRgn& rgn);
    TOOLKIT_API void InvalidateTab(SECWorksheetWnd* pSheet, BOOL bInvalidAfter = FALSE);
    TOOLKIT_API void InvalidateAllTabs();
    TOOLKIT_API int recalcTabWidth();
	inline int GetIconWidth() { return m_cyTab-8; }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECWorkbookWnd)
public:
    TOOLKIT_API virtual BOOL CreateClient(LPCREATESTRUCT lpCreateStruct, CMenu* pWindowMenu);
    TOOLKIT_API virtual void RecalcLayout(BOOL bNotify = TRUE);
    //}}AFX_VIRTUAL

#ifdef WIN32
	// tooltip support
protected:
	CToolTipCtrl* m_pToolTips;
public:
#ifdef _WIN64 //RW64
	TOOLKIT_API virtual LRESULT OnToolHitTest(CPoint point,TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int OnToolHitTest(CPoint point,TOOLINFO* pTI) const;
#endif //_WIN64
#endif 

public:
    TOOLKIT_API ~SECWorkbookWnd();
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

// Overridables

protected:

	//@Access Protected Members
	//@Access Overrideables
	//@cmember
	/* Adds a new worksheet to the workbook*/
    TOOLKIT_API virtual void AddSheet(SECWorksheetWnd* pSheet);
	//@cmember
	/* Removes the specified worksheet from the workbook*/
    TOOLKIT_API virtual void RemoveSheet(SECWorksheetWnd* pSheet);
	TOOLKIT_API virtual BOOL IsFullTabTextVisible(SECWorksheetWnd* pSheet);
    TOOLKIT_API virtual void GetTabPts(SECWorksheetWnd* pSheet, CPoint*& pts, int& count);
	//@cmember
	/* Gets the label associated with the tab*/
    TOOLKIT_API virtual const TCHAR* GetTabLabel(SECWorksheetWnd* pSheet) const;
	//Gets the bounding rectangle of the tab's text
	TOOLKIT_API virtual BOOL GetTextRect(CPoint* pts,int ciIconWidth,CRect& rectText);
	//@cmember
	/* Draws a blank tab at the position specified*/
    TOOLKIT_API virtual void OnDrawTab(CDC* pDC, SECWorksheetWnd* pSheet);
	//Draws a border around the tab
	TOOLKIT_API virtual void OnDrawBorder(CDC* pDC);
	//@cmember
	/* Renders the icon and tab label on top of the blank tab drawn by OnDrawTab()*/
    TOOLKIT_API virtual void OnDrawTabIconAndLabel(CDC* pDC, SECWorksheetWnd* pSheet, UINT nDrawTextFlags=DT_SINGLELINE|DT_CENTER|DT_VCENTER);

// Operations

public:

    //@Access Public Members
	//@Access Operations
	//@cmember
	/* Toggles between Workbook and Normal modes*/
    TOOLKIT_API void SetWorkbookMode(BOOL bEnabled = TRUE);
	//@cmember
	/* Sets display of icons*/
    TOOLKIT_API void SetShowIcons(BOOL bShowIcons = TRUE);
	//@cmember
	/* Returns the icon to be drawn on the tab*/
    TOOLKIT_API virtual HICON GetTabIcon(SECWorksheetWnd* pSheet) const;
	//@cmember
	/* Sets an icon to be drawn on the tab*/
	TOOLKIT_API virtual BOOL SetTabIcon(SECWorksheetWnd* pSheet,HICON hIcon,BOOL bRedraw=TRUE);
	//@cmember
	/* Sets display of icons*/
    TOOLKIT_API void SetFlatStyleMode(BOOL bFlatStyle = TRUE);

// Queries

    //@Access Queries
	//@cmember
	/* Looks up the specified worksheet in the workbook*/
    TOOLKIT_API BOOL LookupSheet(SECWorksheetWnd* pSheet, int& nIndex);
	//@cmember
	/* Returns a pointer to the worksheet specified in the index */
    TOOLKIT_API SECWorksheetWnd* GetWorksheet(int nSheet) const;
	//@cmember
	/* Returns a count of the total number of worksheets*/
    TOOLKIT_API int GetSheetCount() const;

// Generated message map functions
protected:
    //{{AFX_MSG(SECWorkbookWnd)
    TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnViewWorkbook();
    TOOLKIT_API afx_msg void OnUpdateViewWorkbook(CCmdUI* pCmdUI);
    TOOLKIT_API afx_msg void OnOptionsToggleIcons();
    TOOLKIT_API afx_msg void OnUpdateOptionsToggleIcons(CCmdUI* pCmdUI);
    TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg LRESULT OnActivationChanged(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////
// SECControlBarWorksheet

class SECControlBarWorksheet : public SECWorksheetWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECControlBarWorksheet)

// Constructors
protected:
	TOOLKIT_API SECControlBarWorksheet();           // protected constructor used by dynamic creation

public:
#ifdef WIN32
	SECDockBar	m_wndDockBar;		
#endif

// Attributes
public:
	
// Overrides
	TOOLKIT_API void RecalcLayout(BOOL bNotify = TRUE);

// Implementation
protected:
	TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext = NULL);
	TOOLKIT_API virtual ~SECControlBarWorksheet();

	TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	TOOLKIT_API virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	TOOLKIT_API virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

	// Generated message map functions
	//{{AFX_MSG(SECControlBarWorksheet)
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnClose();
	TOOLKIT_API afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	TOOLKIT_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

// For backward compatibility...
#define SECDDIWorksheet SECWorksheetWnd
#define SECDDIWorkbookClient SECWorkbookClientWnd
#define SECDDIWorkbook SECWorkbookWnd

// For backward compatibility... New affix 'Wnd' allows the classwizard to display virtual functions.
#define SECWorksheet SECWorksheetWnd
#define SECWorkbookClient SECWorkbookClientWnd
#define SECWorkbook SECWorkbookWnd

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECWB_H__

