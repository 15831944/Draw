///////////////////////////////////////////////////////////////////////////////
// tabctrl3.h
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
//  Author:       Dean Hallman
//  Description:  Declarations for SEC3DTab and SEC3DTabControl
//  Created:      July 20, 1996
//
//	Modified:	  Feb. 1997 (Kim Starks)
//	Description:  Added tab disable feature			
//	

#ifndef __TABCTRL3_H__
#define __TABCTRL3_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TABCTRLB_H__
#include "toolkit\tabctrlb.h"
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


// Array indexes for GDI objects
#define SEC3DTAB_INACTIVE	0
#define SEC3DTAB_ACTIVE		1

/////////////////////////////////////////////////////////////////////////////
// SEC3DTab

class SEC3DTab : public SECTab
{
    TOOLKIT_DECLARE_DYNAMIC(SEC3DTab);

public:
    TOOLKIT_API SEC3DTab();

// Attributes

public:
	CRect	m_rect;
	HICON	m_hIcon;
	BOOL	m_bEnabled;
	CString	m_csLong;	//Retrieves a copy of the tab label.
	BOOL	m_bToolTip;

// Implementation
protected:
    TOOLKIT_API virtual ~SEC3DTab();
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif
};


/////////////////////////////////////////////////////////////////////////////
// SEC3DTabControl window

/////////////////////////////
// AutoDuck tag block block for SEC3DTabControl 

//@doc SEC3DTabControl
//@mfunc BOOL  | SEC3DTabControl | SetFontActiveTab | Sets an active tab's current font to the specified font.  If bRedraw
// is TRUE, the tab will also be redrawn.
//
//The CFont object passed by pointer will be copied to duplicate storage, so 
// the caller need not hang onto the pointer.
//@parm CFont*  | pFont | Specifies the new font.
//@parm BOOL | bRedraw | If TRUE, redraw the SEC3DTabControl object.
//@xref<mf SEC3DTabControl::GetFontActiveTab>
//@xref<c SEC3DTabControl>

//@doc SEC3DTabControl
//@mfunc BOOL  | SEC3DTabControl | SetFontInactiveTab | Sets an inactive tab's current font to the specified font.  If 
// bRedraw is TRUE, the tab will also be redrawn.
//
//The CFont object passed by pointer will be copied to duplicate
// storage, so the caller need not hang onto the pointer.
//@parm CFont*  | pFont | Specifies the new font.
//@parm BOOL | bRedraw | If TRUE, redraw the SEC3DTabControl object.
//@xref<mf SEC3DTabControl::GetFontInactiveTab>
//@xref<c SEC3DTabControl>

//@doc SEC3DTabControl
//@mfunc CFont*  | SEC3DTabControl | GetFontActiveTab | Gets the current font of an active tab.  The CFont pointer passed 
// back is temporary and should not be stored for later use.
//@rdesc A pointer to a CFont that contains the current font.
//@xref<mf SEC3DTabControl::SetFontActiveTab>
//@xref<c SEC3DTabControl>

//@doc SEC3DTabControl
//@mfunc CFont*  | SEC3DTabControl | GetFontInactiveTab | Gets the current font of an inactive tab.  The CFont pointer 
// passed back is temporary and should not be stored for later use.
//@rdesc A pointer to a CFont that contains the current font.
//@xref<mf SEC3DTabControl::SetFontInactiveTab>
//@xref<c SEC3DTabControl>

// adinsert AutoDuck insertion point for SEC3DTabControl 
//@doc SEC3DTabControl 
//@class The SEC3DTabControl class implements a tab control with a three-dimensional look and feel (similar to Developer
// Studio’s Project Workspace window).  The 3-D tabs can be positioned on the top, bottom, left or right.  The SEC3DTabControl
// inherits its interface from SECTabControlBase and adds the implementation details that define its appearance.
//@comm
// The top, left and right tab position styles are supported only by the 3-D tabs and these do not apply to the 2-D tabs.
//
// Create an SEC3DTabControl in two steps. First, call the constructor SEC3DTabControl to construct the SEC3DTabControl
// object, then call the Create function (inherited from SECTabControlBase) to create the tab control’s window and attach
// it to the SEC3DTabControl object.
//
// If you create an SEC3DTabControl object within a dialog box (through a dialog
// resource), the SEC3DTabControl object is automatically destroyed when the user closes the dialog box.
//
// If you create an SEC3DTabControl object within a window, you may also need to destroy it.  An SEC3DTabControl object created 
// on the stack within a window is automatically destroyed.  If you create the SEC3DTabControl object on the heap by using
// the new function, you must call delete on the object to destroy it when the tab control window is destroyed.
//
// To handle tab control notification messages sent by an SEC3DTabControl object to its parent (usually a class derived from CWnd),
// add a message-map entry and message-handler member function to the parent class for each message.
//
// Each message-map entry takes the following form:
//
// 		ON_MESSAGE( <lt>tab control message id<gt>, memberFxn )
//
// where memberFxn is the name of the parent member function you have written to handle the notification and <lt>tab
// control message id<gt> is one of the following:
//
// 	Tab Control Message				Send To Parent When...<nl>
// 	TCM_TABSEL				A tab is selected.<nl>
// 	TCM_TABSELCLR				The tab selection is cleared.<nl>
// 	TCM_TABDBLCLK				Mouse double-clicked on a tab.
//
// The parent's function prototype is as follows:
//
// 		afx_msg LRESULT memberFxn(WPARAM wParam, LPARAM lParam);
//
// See the TABDEMO sample in the \SAMPLES\TOOLKIT\STANDARD\TABS\TABDEMO directory for a demonstration of SEC3DTabControl.
//@xref<c SECTabControlBase> <c SEC3DTabWnd>
//@BASE public | SECTabControlBase
class SEC3DTabControl : public SECTabControlBase
{
    TOOLKIT_DECLARE_DYNAMIC(SEC3DTabControl);

// Construction
public:
    
	//Access Public Members
	//@Access Constructors
	//@cmember
	/* Constructs an SEC3DTabControl object.*/
    TOOLKIT_API SEC3DTabControl();
    TOOLKIT_API virtual ~SEC3DTabControl();

// Overrides
	//@Access Overridables
	//@cmember
	/* Initializes the tab.*/
    TOOLKIT_API virtual void Initialize(DWORD dwStyle);

	//@cmember
	/* Creates a new tab.*/
	TOOLKIT_API virtual SECTab* CreateNewTab() const;

	//@cmember
	/* Recalculates the tab layout.*/
	TOOLKIT_API virtual void RecalcLayout();

	//@cmember
	/* Initializes the tab font.*/
	TOOLKIT_API virtual void InitializeFonts(DWORD dwStyle);

	//@cmember
	/* Call when the tab is being activated or deactivated.*/
	TOOLKIT_API virtual void OnActivateTab(int nTab);

	//@cmember
	/* Destroys all fonts, pens, and brushes used for tab control drawing.*/
	TOOLKIT_API virtual void DestroyGDIObjects();

	//Added to facilitate direct tab control creation
	TOOLKIT_API virtual SECTab* AddTab(LPCTSTR lpszLabel,
							  CObject* pClient,
							  HMENU hMenu,
							  void* pExtra);
	
	//Virtual overridden to allow tab resizing upon insertion of new tab
	TOOLKIT_API virtual SECTab* InsertTab(int nIndex,
								 LPCTSTR lpszLabel,
								 CObject* pClient,
								 HMENU hMenu,
								 void* pExtra);

	//override needed to update the m_csLong member of SEC3DTab
	TOOLKIT_API void RenameTab(int nIndex, LPCTSTR lpszLabel);
	
    //Overridden to prevent multiple invocation of OnToolHitTest.
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG * pMsg);

#if !defined(_WIN32_WCE_NO_TOOLTIPS)
    //@cmember
	/* Determines whether a point is in the bounding rectangle of the specified tool.  If the point is in the */
	// rectangle, it retrieves information about the tool.  Win32 only.
#ifdef _WIN64 //RW64
	TOOLKIT_API virtual LRESULT OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#endif //_WIN64
#endif

// Operations

	// Font support
	//@Access Operations
	//@cmember
	/* Sets an active tab's currrent font.*/
	inline BOOL SetFontActiveTab(CFont* pFont,BOOL bRedraw=TRUE) { return SetFontTab(pFont,SEC3DTAB_ACTIVE,bRedraw); }

	//@cmember
	/* Sets an inactive tab's current font.*/
	inline BOOL SetFontInactiveTab(CFont* pFont,BOOL bRedraw=TRUE) { return SetFontTab(pFont,SEC3DTAB_INACTIVE,bRedraw); }

	//@cmember
	/* Gets the current font of an active tab.*/
	inline CFont* GetFontActiveTab() { return &m_fonts[SEC3DTAB_ACTIVE]; }

	//@cmember
	/* Gets the current font of an inactive tab.*/
	inline CFont* GetFontInactiveTab() { return &m_fonts[SEC3DTAB_INACTIVE]; }

	//Called for dynamic sizing
	TOOLKIT_API void Rename3DTab(int nTab, LPCTSTR lpszLabel);

	// Set Tab Icon
	// Default size set to 16x16 to avoid downward scaling. If not found,
	// 32x32 alternative will be loaded, then scaled to fit 16x16.
	//@cmember
	/* Sets the tab icon.*/
	TOOLKIT_API virtual void SetTabIcon(int nIndex, HICON hIcon);

	//@cmember
	/* Sets the tab icon.*/
	TOOLKIT_API virtual void SetTabIcon(int nIndex, UINT nIDIcon,
							int cx=SEC_TAB_DEFICON_CX, int cy=SEC_TAB_DEFICON_CY);

	//@cmember
	/* Sets the tab icon.*/
	TOOLKIT_API virtual void SetTabIcon(int nIndex, LPCTSTR lpszResourceName,
							int cx=SEC_TAB_DEFICON_CX, int cy=SEC_TAB_DEFICON_CY);

	//@cmember
	/* Invalidates tab for repainting.*/
	TOOLKIT_API virtual void InvalidateTab(int nTab);

	//@cmember
	/* Enables or disables the tab.*/
	TOOLKIT_API virtual void EnableTab(int nIndex, BOOL bEnable=TRUE);

	//@cmember
	/* Specifies whether the tab is enabled or disabled.*/
	TOOLKIT_API virtual BOOL IsTabEnabled(int nIndex);

   //@cmember
   /* Enables/Disables the tab sizing feature.*/ 
	TOOLKIT_API void EnableTabSizing(BOOL bVal = TRUE);

#ifdef WIN32
	//@cmember
	/* Modifies the style. Win32 only*/
	TOOLKIT_API virtual BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
#endif

	inline int GetLeftOffset() { return m_nLeftOffset; }
	inline int GetTopOffset(){ return m_nTopOffset; }
	inline int GetDefTabHeight() { return m_nDefTabHeight; }
	inline int GetDefTabWidth() { return m_nDefTabWidth; }
	inline void SetDefTabHeight(int nHeight) { m_nDefTabHeight=nHeight; }
	inline void SetDefTabWidth(int nWidth) { m_nDefTabWidth=nWidth; }
	inline void SetLeftOffset(int nOffset) { m_nLeftOffset=nOffset; }
	inline void SetTopOffset(int nOffset) { m_nTopOffset=nOffset; }

//Protected Members used for dynamic resizing of tabs
protected:
	BOOL m_bSizing;
	int m_nDefTabHeight,m_nDefTabWidth,m_nLeftOffset,m_nTopOffset;
	HTHEME m_hTabTheme;

#ifndef UNDER_CE
#ifdef _AFXDLL
	BOOL m_bModuleDiff;
#endif //_AFXDLL
#endif //UNDER_CE

#ifndef UNDER_CE
	//Forwards mouse messages to CWnd::FilterToolTipMessage.
	TOOLKIT_API void RelayTabToolTipEvent(const MSG* pMsg);	
#endif //UNDER_CE (WindowsCE)

protected:
	//helper members for sizing
	TOOLKIT_API virtual void SizeTabs(int nTot, int nTIcon, int nDimParam);
	TOOLKIT_API void CalcLabelWidth(int& nTotBuff, int& nTotalIconBuff, BOOL bLong = FALSE);
	TOOLKIT_API int GetTabBig();

// Implementation
protected:
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	// GDI Objects
    CFont m_fonts[2];
    CPen m_pens[2];
    CPen m_penShadow;
    CPen m_penWhite;
//    CBrush m_brushes[2];
    COLORREF m_rgbText[2];
	int m_bShowTabLabels;	// show labels since tabs all tabs fit

	TOOLKIT_API virtual BOOL SetFontTab(CFont* pFont,int nTabType=SEC3DTAB_ACTIVE,BOOL bRedraw=TRUE);

public:
// Queries
	//@Access Queries
	//@cmember
	/* Indicates whether a given point is within the tab rectangle.*/
	TOOLKIT_API BOOL TabHit(int nTab, CPoint& point) const;

	//@cmember
	/* Returns a reference to the specified tab object.*/
    TOOLKIT_API SEC3DTab& GetTab(int nTab);

	//@cmember
	/* Returns a pointer to the specified tab object.*/
	TOOLKIT_API SEC3DTab* GetTabPtr(int nTab) const;

	//@cmember
	/* Retrieves the tab rectangle.*/
	TOOLKIT_API virtual void GetTabRect(int nTab, CRect &tabRect) const;

	//@cmember
	/* Retrieves the width of the tab label.*/
	TOOLKIT_API int GetLabelWidth(int nTab, BOOL bLong=FALSE);

protected:
// Layout
	TOOLKIT_API virtual void SetTabPos(int nTab, int x, int y, DWORD dwStyle);

// Drawing
	TOOLKIT_API virtual void DrawTab(CDC* pDC, int nTab);
    TOOLKIT_API virtual void rgbFill(CDC* pDC,int x,int y,int cx,int cy, COLORREF rgb);
	TOOLKIT_API virtual void DrawTabBottom(CDC* pDC, SEC3DTab* pTab, DWORD dwStyle);
	TOOLKIT_API virtual void DrawTabTop(CDC* pDC, SEC3DTab* pTab, DWORD dwStyle);
	TOOLKIT_API virtual void DrawTabLeft(CDC* pDC, SEC3DTab* pTab, DWORD dwStyle);
	TOOLKIT_API virtual void DrawTabRight(CDC* pDC, SEC3DTab* pTab, DWORD dwStyle);
	TOOLKIT_API virtual void DrawInterior(CDC* pDC, SEC3DTab* pTab, DWORD dwStyle);
	TOOLKIT_API virtual void DrawDisabled(CDC* pDC, int nWidth, int nHeight);

    // Generated message map functions
protected:
    //{{AFX_MSG(SEC3DTabControl)
    TOOLKIT_API afx_msg void OnDestroy();
    TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
    TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnKillFocus(CWnd* pNewWnd);
#ifndef UNDER_CE
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
#endif //UNDER_CE (WindowsCE)
	TOOLKIT_API afx_msg void OnSysColorChange();
	TOOLKIT_API afx_msg void OnCaptureChanged( CWnd* pWnd );
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API afx_msg LRESULT OnThemeChanged();
	#endif
    //}}AFX_MSG
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

#endif // __TABCTRL3_H__
/////////////////////////////////////////////////////////////////////////////

