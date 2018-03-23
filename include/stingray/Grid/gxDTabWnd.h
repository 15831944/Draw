///////////////////////////////////////////////////////////////////////////////
// gxDTabWnd.h
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

#ifndef _GXDTABWND_H_
#define _GXDTABWND_H_

// #include <StingrayExportDefs.h>

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXDTabBeam window


class CGXDTabInfo: public CObject
{
public:
	int         nWidth;
	CString     sLabel;
	BOOL        bSel;
	CObject*    pExtra;
	BOOL        bDeleteExtra;
	HMENU       hMenu;
	BOOL        m_bHot;

	// Scrollbar Info
	SCROLLINFO  sbInfoVert,
				sbInfoHorz;

	// Color
	COLORREF rgbFaceNormal;
	COLORREF rgbFaceSel;
	CBrush   brFaceNormal;
	CBrush   brFaceSel;

	// bit-field flag to decide whether a tab should use its own color or
	// the default tab beam color.
	unsigned int flagUseOwnColorFaceNormal:1;  //1 bit flag
	unsigned int flagUseOwnColorFaceSel:1;

	GRID_API CGXDTabInfo();
	GRID_API virtual ~CGXDTabInfo();
};


/////////////////////////////
// AutoDuck tag block block for CGXDTabBeam 
// adinsert AutoDuck insertion point for CGXDTabBeam 
//@topic CGXDTabBeam  Class Overview |
//This class implements the tab-beam control used in the CGXDTabWnd. It provides a similar look
//and feel as that of workbooks of MS Excel 2000.

//@doc CGXDTabBeam 
//@class This class implements the tab-beam control used in the CGXDTabWnd. It provides a similar look
//and feel as that of workbooks of MS Excel 2000. It behaves the same as CGXTabBeam window. CGXDTabBeam is
//intended to be used with CGXDTabWnd. It haven't not tested extensively when used with other windows. So, it
//is recommended that you use CGXTabBeam instead in other situation such as in the dialog.
class CGXDTabBeam : public CWnd
{
	GRID_DECLARE_DYNCREATE(CGXDTabBeam)
	

// Construction, initialization
public:
	GRID_API CGXDTabBeam();
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	GRID_API void CreateBrushes();
	GRID_API void CreateFonts();
	GRID_API void UpdateColors();
	GRID_API void DestroyFonts();
	GRID_API void DisplayScrollBtns(BOOL bSet = TRUE, int nScrollBtns = 2);
	GRID_API void ScrollTabInView(int nTab);
	GRID_API void SetNotifyWnd(CWnd* pNotify);
	GRID_API void SetTabBkColor(int nTab, COLORREF cr);
	GRID_API void SetTabSelBkColor(int nTab, COLORREF cr);
	GRID_API virtual ~CGXDTabBeam();

// Attributes
public:
	CFont*      m_pFontCurrent;         // current tab font
	CFont*      m_pFontNormal;          // normal tab font

	COLORREF    m_rgbTextCurrent;       // current tab text color
	COLORREF    m_rgbTextNormal;        // normal tab text color
	COLORREF    m_rgbFaceNormal;        // normal tab back color
	COLORREF    m_rgbFaceSel;           // selected tab back color
	COLORREF    m_rgbBeam;              // beam color

	CBrush      m_brFaceNormal;
	CBrush      m_brFaceSel;
	CBrush      m_brBlack;

	CPen        m_penShadow;

	CObArray    m_TabInfo;              // Tab Infos

	int         m_nTabs;                // no of tabs
	int         m_nCurrent;             // current tab
	int         m_nFirstTab;            // First Visible Tab

	int         m_nWidthEx;             // Extra space at right and left side (triangles)
	int         m_nMargin;              // x coordinate of first tab
	int         m_nHeight;              // height of the beam
	int         m_nButtonWidth;         // width of scroll button (= scroll's thumb button)

	BOOL        m_bScrollBtns;          // Display ScrollButtons
	int         m_nScrollBtns;          // only arrows: 2; also most left and right: 4

	BOOL        m_bLastVisible;         // Is Last Button Visible

	HCURSOR     m_hcurArrow;

	// Mouse Actions
	int         m_nBtnDown;
	BOOL        m_bBtnDown;
	BOOL        m_bMouseCapture;

	int         m_nxTracking;           // If not -1, this marks the left
										// edge of the painting area
				// m_nxTracking will be set in
				// CGXDTabWnd while tracking the SplitterBar

	// Wnd to receive messages
	CWnd*       m_pNotifyWnd;


protected:
	// Hot Property For Buttons.	
	BOOL m_bBtnHot[4];

// Operations
public:
	GRID_API virtual void    DrawTab(CDC* pDC, int nTab, BOOL bMouseMove = FALSE);
	GRID_API virtual void    DrawButton(CDC* pDC, int i, BOOL bPressed);
	GRID_API virtual int     CalcTabOffset(int nTab);
	GRID_API virtual int     CalcTabFromOffset(int nOffset);
	GRID_API virtual int     CalcLastVisibleTab();

	GRID_API virtual void    AutoMove(UINT nRefMessage = WM_LBUTTONUP);
	GRID_API virtual void    SwitchToTab(CPoint point);
	GRID_API virtual int     ScrollBtnHit(CPoint point, int nButton = -1, BOOL bScroll = TRUE);
	GRID_API virtual void    Scroll(int nDirection);

	// TabInfo
	GRID_API CGXDTabInfo& GetTab(int nTab);
	GRID_API virtual void    InsertTab(BOOL bInsert, LPCTSTR szLabel, CObject* pExtra = NULL, BOOL bDelExtra = FALSE, int nWidth = -1, HMENU hMenu = 0);
	GRID_API virtual void    DeleteTab(int nTab);
	GRID_API virtual void    AdjustTabSize(int nTab);
	GRID_API virtual int     FindTab(const CObject *pExtra);

	// Current Selection, TabCount
	GRID_API int     GetCurSel();
	GRID_API int     GetCount();

protected:
	// To Handle Mouse leave
	GRID_API BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	GRID_API static void DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed);
	GRID_API static void PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXDTabBeam)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd window

// this class is based on the source code of the CSplitterWnd class

#define ID_GX_EDITWND       23001

class CGXDEditLabelPopup : public CEdit
{
	GRID_DECLARE_DYNAMIC(CGXDEditLabelPopup);

// Construction
public:
	GRID_API CGXDEditLabelPopup(CRect rect, CWnd* pParentWnd, UINT nID);

// Implementation
public:
	GRID_API virtual ~CGXDEditLabelPopup();

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXDEditLabelPopup)
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};


/////////////////////////////
// AutoDuck tag block block for CGXDTabWnd 
// adinsert AutoDuck insertion point for CGXDTabWnd 
//@topic CGXDTabWnd  Class Overview |
//This is a another tab window class that provides support dynamic splitter window. The tab window provide the 
//functionality to switch between several views in a frame window. If you want to support dynamic splitter
//window, you can use this tab window class, otherwise use the CGXTabWnd instead.


//@doc CGXDTabWnd 
//@class This is another tab window class that provides support to dynamic splitter window. If you are not going
//to support dynmaic splitter window, it is recommended to use the CGXTabWnd in the library. The CGXDTabWnd class
//displays a tab-beam control on the bottom-left side of the frame window. When it is used together with CDXSplitWnd,
//only one tab-beam control is drawn on the bottom-left side of the frame window even when user splitter the window
//by dragging the splitter box using mouse. This behavior is similar to that of workbooks in the MS Excel 2000. <nl>
//The GridDSplit sample in the sample folder demostrates the how CGXDTabWnd and CDXSplitWnd can be used together.
class CGXDTabWnd : public CWnd
{
	GRID_DECLARE_DYNCREATE(CGXDTabWnd)
	

// Construction
public:
	GRID_API CGXDTabWnd(CRuntimeClass *pBeamClass = RUNTIME_CLASS(CGXDTabBeam));

	// Create a single view type splitter with multiple splits
	GRID_API BOOL Create(CWnd* pParentWnd, LPCTSTR szFirstLabel,
				CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE |	WS_HSCROLL | WS_VSCROLL,
				DWORD dwExStyle = WS_EX_CLIENTEDGE,
				UINT nID = AFX_IDW_PANE_FIRST);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Attributes
public:
	CRuntimeClass*		m_pDynamicViewClass;
	BOOL				m_bHasHScroll, m_bHasVScroll;
	UINT				m_nFirstViewID;
	UINT				m_nLastViewID;
	CGXDTabBeam*		m_pBeam;
	CWnd*				m_pActivePane;
	int					m_cxBeam;           // size of the beam ( = x-position of the splitter)
	int					m_cxWnd;
	int					m_cxSplitter;
	int					m_cxVScroll, m_cyHScroll;
	int					m_nBarWidths;
	BOOL				m_bTracking;
	HCURSOR				m_hcurArrow;
	BOOL				m_bCtrlsCreated;
	CGXDEditLabelPopup*	m_pEditWnd;
	CBrush				m_brErase;
	CRuntimeClass*		m_pBeamClass;    // used for creating the beam
	BOOL				m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

protected:
	LONG m_lxBeam;          // temporary used for size of the beam

// Operations
public:
	GRID_API void PatB(CDC* pDC, int x, int y, int cx, int cy, COLORREF clr);

	GRID_API virtual CWnd* AttachWnd(CWnd* pWnd, LPCTSTR szLabel);
	GRID_API void SaveScrollbarState(CWnd* pSheetWnd);
	GRID_API void RestoreScrollbarState(CWnd* pSheetWnd);
	GRID_API BOOL CreateCommon(CWnd* pParentWnd, DWORD dwStyle, DWORD dwExStyle, UINT nID);
	GRID_API BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
	GRID_API void RecalcLayout(BOOL bTracking = FALSE);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow);
	GRID_API void GetInsideRect(CRect& rect) const;
	GRID_API CWnd* CreateView(CRuntimeClass* pViewClass, LPCTSTR szLabel, CCreateContext* pContext = NULL, UINT nID = 0);
	GRID_API void SwitchTab(CWnd* pWnd);
	GRID_API void SwitchTab(int nTab);
	GRID_API void RemoveTab(int nTabToDelete);
	GRID_API void RemoveTab(CWnd* pWnd);
	GRID_API void OnDrawSplitter(CDC* pDC, const CRect& rectArg);
	GRID_API UINT GetNextID();
	GRID_API CGXDTabBeam& GetBeam();
	GRID_API CWnd* GetActivePane();

	GRID_API LPCTSTR GetTabName(int nTab);
	GRID_API LPCTSTR GetTabName(const CWnd* pSheet);
	GRID_API void SetTabName(int nTab, LPCTSTR szName, BOOL bNotifySheet = TRUE);
	GRID_API void SetTabName(const CWnd* pSheet, LPCTSTR szName, BOOL bNotifySheet = TRUE);

// Implementation
public:
	GRID_API virtual ~CGXDTabWnd();

protected:
	GRID_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
	//{{AFX_MSG(CGXDTabWnd)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg LRESULT OnTabSwitch(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanTabSwitch(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnTabDblClk(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnEditCancel(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnEditEnd(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnNcPaint();
	GRID_API afx_msg void OnSysColorChange();
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif//_GXDTABWND_H_
