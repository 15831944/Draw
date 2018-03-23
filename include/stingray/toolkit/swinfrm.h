///////////////////////////////////////////////////////////////////////////////
// swinfrm.h
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
//  Description:	Declarations for SECFrameWnd
//  Created:		May 1996
//
//	Modified:		Feb 1997 (Kenn Scribner)
//	Description:	Added italicized text to inactive windows
//					Fixed MDI-derived class behavior (parent
//					and children window captions are activated/
//					de-activated properly)
//
//

#ifdef WIN32

#ifndef __SWINFRM_H__
#define __SWINFRM_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SBARDOCK_H__
#include "toolkit\sbardock.h"
#endif

#ifndef __SECWSMGREX_H__
#include "toolkit\swsmgrex.h"
#endif

#ifndef __SECAUTOHIDEBAR__H__
#include "toolkit\sbarautohide.h"
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

/////////////////////////////////////////////////////////////////////////////
// SECFrameWnd frame

// Forward Declarations
class CDockBar;
class SECDockState;
class SECControlBar;
class SECControlBarManager;
class stingray::foundation::SECWndPlugIn;
class SECBmpMenuPlugIn;
class SECMenuBar;

/////////////////////////////
// AutoDuck tag block block for SECFrameWnd 

//@doc SECFrameWnd
//@mfunc BOOL  | SECFrameWnd | GetActiveState | GetActiveState returns true if this is the 
// active window.
//@xref<c SECFrameWnd>

//@doc SECFrameWnd
//@mdata SECControlBarManager*  | SECFrameWnd | m_pControlBarManager | A control bar manager 
// should be created in the constructor if use of a control bar manager class is desired. This
// should be created on the heap, and must be destroyed in the destructor for the frame.

//@doc SECFrameWnd
//@mdata UINT  | SECFrameWnd | m_uiTextAlign | DrawText alignment flags for caption

//@doc SECFrameWnd
//@mdata BOOL  | SECFrameWnd | m_bHandleCaption | If custom caption drawing is enabled, this will be the caption handle. 

//@doc SECFrameWnd
//@mdata BOOL  | SECFrameWnd | m_bActive | Activation status (WM_ACTIVATE status)

//@doc SECFrameWnd
//@mfunc void  | SECFrameWnd | SetMenuBar | Sets the menubar for the frame.
//@parm SECMenuBar*  | pMenuBar | A pointer to a SECMenuBar Object.

// adinsert AutoDuck insertion point for SECFrameWnd 
//@doc SECFrameWnd 
//@class The SECFrameWnd class is a replacement for MFC’s CFrameWnd class.  
//@comm
// The creation of a 
// CFrameWnd replacement is necessary to support the extended control bar architecture and 
// the gradient caption feature.  Building on  this architecture, your application can create 
// docking windows with capabilities comparable to those seen in the Microsoft Developer 
// Studio.  You can also give your applications the gradient caption similar to the Microsoft 
// Word title bar.  Control bars can be resized while docked, diagonally resized while 
// floating and more. The SECFrameWnd class derives from CFrameWnd and adds the 
// implementation details and public operations required to support these enhancements.
//
// Since SECFrameWnd inherits the CFrameWnd interface, all occurrences of CFrameWnd in 
// your application code can simply be replaced with SECFrameWnd.  For detailed 
// instructions on adding enhanced docking window support to your application, 
// refer to The Extended Control Bar Architecture section of the Objective Toolkit 
// User’s Guide.
//
// The SECFrameWnd and <c SECMDIFrameWnd> classes serve similar purposes  they add enhanced 
// docking window support to your application.  If your application is SDI-based, you’ll 
// need to change the base class of your application’s main frame window from CFrameWnd 
// to SECFrameWnd.  On the other hand, if your application is MDI-based, you’ll need to 
// change the base class of your application’s main frame window from CMDIFrameWnd to 
// <c SECMDIFrameWnd>.
//@base public | CFrameWnd
//@xref <c SECMDIFrameWnd>
class SECFrameWnd : public CFrameWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECFrameWnd)

protected:
	//@access Construction
	//@cmember
	/* Constructor for the SECFrameWnd class.*/
    TOOLKIT_API SECFrameWnd();

// Attributes
public:
	//@access Attributes
	//@cmember
	/* Returns the activation state for the window.*/
	inline BOOL GetActiveState() { return m_bActive; }

	//@access Operations
public:
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	//@cmember
	/* Enables docking for the frame. */
    TOOLKIT_API void EnableDocking(DWORD dwDockStyle, DWORD dwDockStyleEx = 0);
	//@cmember
	/* Create a new dockbar*/
	TOOLKIT_API virtual CDockBar* CreateNewDockBar();

	//@cmember
	/* Enables or disables the control bar context list mode.*/
	TOOLKIT_API void EnableContextListMode(BOOL bEnable = TRUE);

	//@cmember
	/* Remove a control bar from it's dockbar and float it, or move a floating bar to*/
	// another location.
	TOOLKIT_API virtual void FloatControlBar(CControlBar* pBar, CPoint point, 
		                                     DWORD dwStyle = CBRS_ALIGN_TOP);
	//@cmember
	/* Dock a control bar with extended information. */
	TOOLKIT_API virtual void DockControlBarEx(CControlBar* pBar, 
		                                      UINT nDockBarID = 0,int nCol = 0, int nRow = 0, 
		                                      float fPctWidth = (float)1.0, int nHeight = 150);
	TOOLKIT_API void DockControlBar(CControlBar* pBar, UINT nDockBarID = 0,LPCRECT lpRect = NULL);
	TOOLKIT_API void DockControlBar(CControlBar* pBar, CDockBar* pDockBar, LPCRECT lpRect = NULL);
	TOOLKIT_API void ReDockControlBar(CControlBar* pBar, CDockBar* pDockBar, LPCRECT lpRect = NULL);
	TOOLKIT_API void ShowControlBar(CControlBar* pBar, BOOL bShow, BOOL bDelay);
	TOOLKIT_API SECControlBar* CtrlBarFromID(const UINT nID);

	//@cmember
	// Saving and loading control bar state
	TOOLKIT_API virtual void LoadBarState(LPCTSTR lpszProfileName);
	TOOLKIT_API virtual void SaveBarState(LPCTSTR lpszProfileName) const;
	TOOLKIT_API virtual void SetDockState(SECDockState& state);
	TOOLKIT_API virtual void GetDockState(SECDockState& state) const;

	// Control Bar Manager
	//@cmember
	// Get controlbar manager.
	TOOLKIT_API virtual SECControlBarManager* GetControlBarManager() const;
	//@cmember
	// Set controlbar manager.
	TOOLKIT_API virtual void SetControlBarManager(SECControlBarManager*);

	// General custom caption members
	//@cmember
	// Is the custom caption enabled?
	inline BOOL IsCustomCaptionEnabled() const { return m_bHandleCaption; }
	//@cmember
	// Enable custom caption.
	TOOLKIT_API BOOL EnableCustomCaption(BOOL bEnable, BOOL bRedraw = TRUE);
	//@cmember
	// Force caption redraw.
	TOOLKIT_API void ForceCaptionRedraw(BOOL bImmediate);
	//@cmember
	// Force caption redraw.
	TOOLKIT_API void ForceCaptionRedraw();
	//@cmember
	/* Creates the caption text font for the application name */
	TOOLKIT_API virtual void CreateCaptionAppFont(CFont& font);
	//@cmember
	/* Creates the caption text font for the document name */
	TOOLKIT_API virtual void CreateCaptionDocFont(CFont& font);
	//@cmember
	/* Draws the text on the caption bar */
	TOOLKIT_API virtual void DrawCaptionText();

	// Caption text control members

	enum AlignCaption { acLeft, acCenter, acRight };
	//@cmember
	// Get caption text alignment.
	inline AlignCaption GetCaptionTextAlign() const { return (AlignCaption)m_uiTextAlign; }
	//@cmember
	// Set caption text alignment.
	TOOLKIT_API void SetCaptionTextAlign(AlignCaption ac, BOOL bRedraw = TRUE);
	//@cmember
	// Enables support for bitmap menus
	TOOLKIT_API void EnableBmpMenus(BOOL bEnable = TRUE, BOOL bManaged = TRUE);
	//@cmember
	// Adds bitmaps for the bitmap menu support
	TOOLKIT_API BOOL AddBmpMenuToolBarResource(LPCTSTR lpszStdBmpName);
	TOOLKIT_API BOOL AddBmpMenuToolBarResource(UINT nIDStdBmp);
	TOOLKIT_API BOOL AddBmpMenuBitmapResource(LPCTSTR lpszStdBmpName,
								  const UINT* lpIDArray, UINT nIDCount);
	TOOLKIT_API BOOL AddBmpMenuBitmapResource(UINT nIDstdBmpName,
								  const UINT* lpIDArray, UINT nIDCount);
	TOOLKIT_API BOOL AddBmpMenuBitmap(HBITMAP hBmpSmall, const UINT* lpIDArray, UINT nIDCount);
	//@cmember
	// Returns the SECBmpMenuPlugIn object
	TOOLKIT_API SECBmpMenuPlugIn* GetBmpMenuPlugIn() const;
	//@cmember
	/* Switches the menu on the menubar when running with a cool look menubar.*/
	TOOLKIT_API void SwapMenu(UINT nID);
	//@cmember
	// Set menu bitmap transparency color.
	inline virtual void SetMenuBmpTransparencyColor(COLORREF clrBmpTransparent, BOOL bUseCustomBmpTransparentColor = TRUE)
	{ 
		m_clrBmpTransparency = clrBmpTransparent; 
		m_bUseBmpTransparency = bUseCustomBmpTransparentColor;
	}
	//@cmember
	// Get menu bitmap transparency color.
	inline virtual COLORREF GetMenuBmpTransparentColor() 
	{
		return m_bUseBmpTransparency;
	}

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECFrameWnd)
	//@cmember
	// OnSetPreviewMode handler.
 	TOOLKIT_API virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
   //}}AFX_VIRTUAL

// Implementation
protected:
	//@cmember
	// Destructor for the SECFrameWnd
    TOOLKIT_API virtual ~SECFrameWnd();
	TOOLKIT_API static const DWORD dwSECDockBarMap[4][2];
	//@cmember
	// Get Windows version.
	TOOLKIT_API void GetWindowsVersion();
	BOOL m_bIsWin95orAbove;
	BOOL m_bDidClose;
	//@cmember
	// Returns the HMENU for the given id.
	TOOLKIT_API virtual HMENU MenuFromResource(UINT nID);

public:
	//@cmember
	// Recalculate layout.
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify = TRUE);
	//@cmember
	// OnUpdateFrameMenu handler.
	TOOLKIT_API virtual void OnUpdateFrameMenu(BOOL bActive, CWnd* pActivateWnd, HMENU hMenuAlt);
	//@cmember
	// OnCmdMsg handler.
	TOOLKIT_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//@cmember
	// OnEnterIdle handler.
	TOOLKIT_API virtual void OnEnterIdle(UINT nWhy, CWnd* pWho);

    // Generated message map functions
    //{{AFX_MSG(SECFrameWnd)
	//@cmember
	// OnNcPaint handler.
	TOOLKIT_API afx_msg void	OnNcPaint();
	//@cmember
	// OnActivate handler.
	TOOLKIT_API afx_msg void	OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//@cmember
	// OnNcActivate handler.
	TOOLKIT_API afx_msg BOOL	OnNcActivate(BOOL bActive);
	//@cmember
	// OnEraseBkgnd handler.
	TOOLKIT_API afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	//@cmember
	// OnSetText handler.
	TOOLKIT_API afx_msg LRESULT	OnSetText(WPARAM wParam, LPARAM lParam);
#if (_MFC_VER >= 0x0800)
	//@cmember
	// OnNcHitTest handler.
	TOOLKIT_API afx_msg LRESULT	OnNcHitTest(CPoint point);
#else
	//@cmember
	// OnNcHitTest handler.
	TOOLKIT_API afx_msg UINT	OnNcHitTest(CPoint point);
#endif
	//@cmember
	// OnEnable handler.
	TOOLKIT_API afx_msg void	OnEnable(BOOL bEnable);
	//@cmember
	// OnContextHelp handler.
	TOOLKIT_API afx_msg void	OnContextHelp();
	//}}AFX_MSG
	
#if(_MFC_VER >= 0x0700)
	//@cmember
	// DestroyDockBars handler.
	TOOLKIT_API void DestroyDockBars();
#endif

	// Default handlers for the workspace functions to assure the menu
	// items are properly enabled (plugin will not enable menus, but
	// will accept commands)
	DECLARE_WSMGREX_DEFAULT_HANDLERS()

    TOOLKIT_DECLARE_MESSAGE_MAP()

	///////////////////////////////////////////////////////////////////////
	//                     Menu Bar Information							 //
	///////////////////////////////////////////////////////////////////////
public:
	//@cmember
	/* Returns TRUE if a menubar is present, FALSE if CMenu.*/
	TOOLKIT_API BOOL HasMenuBar();
	//@cmember
	/* Gets a pointer to the menu bar.*/
	TOOLKIT_API SECMenuBar* GetMenuBar();
	//@cmember
	/* Set the MenuBar for this frame.*/
	inline void SetMenuBar(SECMenuBar* pMenuBar) { m_pMenuBar=pMenuBar; }
	//@cmember
	/* Returns a pointer to the currently active menu.*/
	TOOLKIT_API CMenu* GetMenu() const;

	// returns approp. default HMENU, accounting for menubar state
	TOOLKIT_API virtual HMENU GetDefaultMenu();

	///////////////////////////////////////////////////////////////////////
	// AUTO HIDE FEATURES
	///////////////////////////////////////////////////////////////////////
	//@cmember
	// Enable autohide.
	TOOLKIT_API void EnableAutoHide(DWORD dwAlign);
	//@cmember
	// Insert item.
	TOOLKIT_API BOOL InsertItem();
	//@cmember
	// Remove item.
	TOOLKIT_API BOOL RemoveItem();
	//@cmember
	// Show tab.
	TOOLKIT_API BOOL ShowTab();

    // Our Auto Hide Bars
    SECAutoHideBar m_dockHideLeft;
    SECAutoHideBar m_dockHideTop;
    SECAutoHideBar m_dockHideBottom;
    SECAutoHideBar m_dockHideRight;

	//@cmember
	// WindowProc handler.
	TOOLKIT_API virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	//@cmember
	// PreTranslateMessage handler.
	TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );
	//@cmember
	// Load frame.
	TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, 
						   DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
						   CWnd* pParentWnd = NULL,
						   CCreateContext* pContext = NULL);

	// Integration of the extended workspace manager
public:
	
	//@cmember
	/* Initialize the extended workspace manager. */
	TOOLKIT_API virtual SECWorkspaceManagerEx* InitWorkspaceMgrEx(const CString& strAppKey,
										BOOL bRegistryMode=FALSE,	
										CRuntimeClass* pWSClass=
										RUNTIME_CLASS(SECWorkspaceManagerEx),
                                        BOOL bSectionKey=FALSE);

	//@cmember
	// Get a pointer to the frame's workspace mgr.
	inline SECWorkspaceManagerEx* GetWorkspaceMgrEx() { return m_pWorkspaceManagerEx; }
	//@cmember
	// Accessor the dynamic controlbar allocation list
	inline CPtrList* GetListAllocControlBars() { return &m_listAllocControlBars; }

private:
	// Cache the return value of InitWorkspaceMgrEx to use in a derived class.
	SECWorkspaceManagerEx* m_pWorkspaceManagerEx;

protected:
	//@access Protected data members
	CRect m_prevLayout;

	// Gradient Caption Attributes
	//@cmember
	/* DrawText alignment flags for caption*/
	UINT m_uiTextAlign;	
	//@cmember
	/* If custom caption drawing is enabled, this will be the caption handle. */
	BOOL m_bHandleCaption;	
	//@cmember
	/* Activation status (WM_ACTIVATE status)*/
	BOOL m_bActive;	

	//@cmember
	/* Pointer to the ControlBarManager*/
	SECControlBarManager* m_pControlBarManager;
	// Pointer to the Menu Bar Plugin. 
	stingray::foundation::SECWndPlugIn * m_pMenuBarFeature;
	// Do we have a bitmap menu?
	BOOL        m_bBmpMenu;
	// Is the bitmap menu managed?
	BOOL           m_bBmpMenuManaged;
	// Pointer to our Menu Bar
	SECMenuBar*	m_pMenuBar;
	// Handle to the menu frame
	HMENU		m_hMenuFrame;
	// ID of Menu Resource
	UINT		m_nIDMenuResource;
	// List of control bar pointers
	CPtrList	m_listAllocControlBars;

	COLORREF	m_clrBmpTransparency;
	BOOL		m_bUseBmpTransparency;

	// Generated message map functions
	//{{AFX_MSG(SECFrameWnd)
	//@cmember
	// OnCreate handler.
	TOOLKIT_API afx_msg int OnCreate( LPCREATESTRUCT lpcs );
	//@cmember
	// OnClose handler.
	TOOLKIT_API afx_msg void OnClose();
	//@cmember
	// OnSysColorChange handler.
	TOOLKIT_API afx_msg void OnSysColorChange();
	//@cmember
	// OnSecGetMenu handler.
	TOOLKIT_API afx_msg LRESULT OnSecGetMenu(WPARAM wParam, LPARAM lParam);
#if(_MFC_VER >= 0x0700)
	//@cmember
	// OnDestroy handler.
	TOOLKIT_API afx_msg void OnDestroy();
#endif
	//}}AFX_MSG
	//@cmember
	// ProcessHelpMsg handler.
	TOOLKIT_API BOOL ProcessHelpMsg(MSG& msg, DWORD* pContext);
};

//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SWINFRM_H__

#else // WIN32                       

#define SECFrameWnd CFrameWnd

#endif // WIN32

