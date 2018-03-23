///////////////////////////////////////////////////////////////////////////////
// swinmdi.h
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
//  Description:	Declarations for SECMDIFrameWnd	/ SECMDIChildWnd / SECControlBarMDIChildWnd
//  Created:		May 1996
//
#ifdef WIN32

#ifndef __SWINMDI_H__
#define __SWINMDI_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif

#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
#endif

#ifndef __SBARDOCK_H__
#include "toolkit\sbardock.h"
#endif

#ifndef __SMSGFILT_H__
#include "toolkit\smsgfilt.h"
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // #ifndef __AFXTEMPL_H__

#ifndef __SECWSMGREX_H__
#include "toolkit\swsmgrex.h"
#endif

#ifndef __SECAUTOHIDEBAR__H__
#include "toolkit\sbarautohide.h"
#endif

#include <StingrayExportDefs.h>

#pragma warning(disable: 4311)

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

// Forward Declarations
class SECControlBarMDIChildWnd;
class SECControlBarInfo;
class SECControlBarManager;
class SECControlBar;
class SECMenuBar;
class stingray::foundation::SECWndPlugIn;
class SECBmpMenuPlugIn;
class SECAutoHideBar;

/////////////////////////////////////////////////////////////////////////////
// SECMDIFrameWnd

/////////////////////////////
// AutoDuck tag block block for SECMDIFrameWnd 

//@doc SECMDIFrameWnd
//@mfunc void | SECMDIFrameWnd | EnableOleContainmentMode | Sets CBRS_HIDE_INPLACE for all control bars. Call when used with Ole Containers.
//@xref <c SECMDIFrameWnd>

// adinsert AutoDuck insertion point for SECMDIFrameWnd 
//@doc SECMDIFrameWnd 
//@class The SECMDIFrameWnd class is an interface equivalent for CMDIFrameWnd that adds support for 
// a variety of new features.  SECMDIFrameWnd supports enhanced docking window capabilities and a gradient 
// caption (similar to the Microsoft Word caption).  Future releases will add more features to this 
// class.
//@comm
// The enhanced docking window capabilities enable control bars to be resized while docked, 
// converted to MDI child windows, diagonally resized while floating and more.  These enhancments 
// give your application docking window capabilities comparable to those seen in the Microsoft 
// Developer Studio. The SECMDIFrameWnd class derives from CMDIFrameWnd and adds the implementation 
// details and public operations required to support the above mentioned enhancements to MDI.  
// Since SECMDIFrameWnd inherits the CMDIFrameWnd interface, all occurrences of CMDIFrameWnd in 
// your application code can simply be replaced with SECMDIFrameWnd.  Refer to the Objective 
// Toolkit User’s Guide for more information about using the enhanced docking window and gradient 
// caption features.
// 
// To create a useful SECMDIFrameWnd frame window for your application, derive a class (typically, 
// your CMainFrame class) from SECMDIFrameWnd.  Add member variables to the derived class to store 
// data specific to your application.  Implement message-handler member functions and a message map 
// in the derived class to specify what happens when messages are directed to the window.  Note, 
// if you are converting an existing MDI application to Objective Toolkit’s SECMDIFrameWnd, 
// simply change the base class of your main frame (i.e., CMainFrame), from CMDIFrameWnd to 
// SECMDIFrameWnd.
// 
// You can construct an SECMDIFrameWnd by calling the Create or LoadFrame member function of 
// CFrameWnd.
// 
// Before you call Create or LoadFrame, you must construct the frame window object on the heap 
// using the C++ new operator. Before calling Create you can also register a window class with 
// the AfxRegisterWndClass global function to set the icon and class styles for the frame.
//
// Use the Create member function to pass the frame’s creation parameters as immediate arguments.
// 
// LoadFrame requires fewer arguments than Create, and instead retrieves most of its default values 
// from resources, including the frame’s caption, icon, accelerator table, and menu.  To be 
// accessed by LoadFrame, all these resources must have the same resource ID (for example, 
// IDR_MAINFRAME).
// 
// Though SECMDIFrameWnd is derived from CMDIFrameWnd, a frame window class derived from 
// SECMDIFrameWnd need not be declared with DECLARE_DYNCREATE.
//
// The SECMDIFrameWnd class inherits much of its default implementation from CMDIFrameWnd.  
// For a detailed list of these features, refer to the CMDIFrameWnd class description. 
// The SECMDIFrameWnd class has the following additional features:
//
// ?When docked inside an SECMDIFrameWnd window, a control bar can be resized via splitter bars positioned 
// along the control bar’s edge.<nl>
// ?A control bar can be converted to an MDI child window and floated inside the MDI client area.<nl>
// ?The context menu associated with any control bar can be edited by the SECMDIFrameWnd object prior to 
// the menu’s display.
//
// Do not use the C++ delete operator to destroy a frame window. Use CWnd::DestroyWindow instead.  
// The CFrameWnd implementation of PostNcDestroy will delete the C++ object when the window is 
// destroyed. When the user closes the frame window, the default OnClose handler will call 
// DestroyWindow.
// 
// For more information on SECMDIFrameWnd, see The Extended Control Bar Architecture section of 
// the Objective Toolkit User’s Guide.
//
// See the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ and \SAMPLES\TOOLKIT\STANDARD\UIEXT\GRADFRM samples, which demonstrate the capabilities of this class.
//@base public | CMDIFrameWnd
class SECMDIFrameWnd : public CMDIFrameWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECMDIFrameWnd)

protected:
    TOOLKIT_API SECMDIFrameWnd(); 

// Attributes
protected:
	CRect					m_prevLayout;
	CRuntimeClass*			m_pDockBarClass;
	CRuntimeClass*			m_pFloatingMDIChildClass;
	TOOLKIT_API static const DWORD dwSECDockBarMap[4][2];
	CPoint					m_ptDefaultMDIPos;
	SECFrameWnd*			m_pActiveDockableFrame;
	SECControlBarManager*	m_pControlBarManager;
	BOOL					m_bLockNotifyActiveView;	// prevents NotifyActiveView() recursion loop

	// Gradient Caption Attributes
	UINT m_uiTextAlign;		// DrawText alignment flags for caption
	BOOL m_bActive;			// Track Activation State
	BOOL m_bHandleCaption;	// is custom caption drawing enabled?

// Operations
public:
#ifdef _DEBUG
	//@cmember
	// Assert valid.
    TOOLKIT_API virtual void AssertValid() const;
	//@cmember
	// Dump context.
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif
	//@cmember
	// Enable docking.
    TOOLKIT_API void EnableDocking(DWORD dwDockStyle, DWORD dwDockStyleEx = 0);
	//@cmember
	// Create new dockbar.
	TOOLKIT_API virtual CDockBar* CreateNewDockBar();

	//@cmember
	/* Enables or disables the control bar context list mode.*/
	TOOLKIT_API void EnableContextListMode(BOOL bEnable = TRUE);

	//@cmember
	/* Similar to DockControlBar but gives greater control over how and where the control bar will */
	// dock. 
	TOOLKIT_API virtual void DockControlBarEx(CControlBar* pBar, UINT nDockBarID = 0,int nCol = 0, int nRow = 0, float fPctWidth = (float)1.0, int nHeight = 150);
    TOOLKIT_API virtual void DockControlBarEx(CControlBar* pBar, const SECDockPos & rDockPos, UINT nDockBarID = 0,const SECDockSize & rDockSize = SECDockSize());
	TOOLKIT_API virtual void FloatControlBar(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
	TOOLKIT_API void DockControlBar(CControlBar* pBar, UINT nDockBarID = 0, LPCRECT lpRect = NULL);
	
	//@cmember
	/* Converts the control bar back to a normal docking or floating control bar.*/
	TOOLKIT_API void ReDockControlBar(CControlBar* pBar, CDockBar* pDockBar, LPCRECT lpRect = NULL);
	TOOLKIT_API void ShowControlBar(CControlBar* pBar, BOOL bShow, BOOL bDelay);
	
	//@cmember
	/* Converts the control bar to an MDI child window. */
	TOOLKIT_API virtual void FloatControlBarInMDIChild(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
	TOOLKIT_API void ReFloatControlBar(CControlBar* pBar, CPoint point, DWORD dwStyle = CBRS_ALIGN_TOP);
	TOOLKIT_API virtual CMDIChildWnd* CreateFloatingMDIChild(DWORD dwStyle, CControlBar* pBar = NULL);

	//@cmember
	// Activate and Deactivate the dociable grame.
	TOOLKIT_API virtual void ActivateDockableFrame(SECFrameWnd* pFrameWnd, BOOL bForce = FALSE);
    TOOLKIT_API virtual void DeactivateDockableFrame(BOOL bAutoActivateSibling = TRUE);
	TOOLKIT_API virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

	//@cmember
	// Active frame (for frames within frames -- MDI)
	TOOLKIT_API virtual CFrameWnd* GetActiveFrame();

	//@cmember
	// saving and loading control bar state
	TOOLKIT_API virtual void LoadBarState(LPCTSTR lpszProfileName);
	TOOLKIT_API virtual void SaveBarState(LPCTSTR lpszProfileName) const;
	TOOLKIT_API virtual void SetDockState(SECDockState& state);
	TOOLKIT_API virtual void GetDockState(SECDockState& state) const;

	//@cmember
	// Control Bar Manager
	TOOLKIT_API virtual SECControlBarManager* GetControlBarManager() const;
	TOOLKIT_API virtual void SetControlBarManager(SECControlBarManager*);
	TOOLKIT_API SECControlBar* CtrlBarFromID(const UINT nID);

	// General custom caption members

	//@cmember
	// Returns true if the gradient caption rendering is enabled or false if not.
	inline BOOL IsCustomCaptionEnabled() const { return m_bHandleCaption; }

	//@cmember
	/* Enables or disables gradient caption rendering.*/
	TOOLKIT_API BOOL EnableCustomCaption(BOOL bEnable, BOOL bRedraw = TRUE);

	//@cmember
	/* Forces a redraw of the caption bar.*/
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
	// Returns the alignment of the caption text relative to the caption bar.
	inline AlignCaption GetCaptionTextAlign() const { return (AlignCaption)m_uiTextAlign; }
	
	//@cmember
	/* Modifies the alignment of the caption text relative to the caption bar.*/
	TOOLKIT_API void SetCaptionTextAlign(AlignCaption ac, BOOL bRedraw = TRUE);
	//@cmember
	// Enables support for bitmap menus
	TOOLKIT_API void EnableBmpMenus(BOOL bEnable = TRUE, BOOL bManaged = TRUE);
	//@cmember
	// Adds bitmaps for the bitmap menu support
	TOOLKIT_API BOOL AddBmpMenuToolBarResource(LPCTSTR lpszStdBmpName);
	TOOLKIT_API BOOL AddBmpMenuToolBarResource(UINT nIDStdBmp);
	TOOLKIT_API BOOL AddBmpMenuBitmapResource(LPCTSTR lpszStdBmpName, const UINT* lpIDArray, UINT nIDCount);
	TOOLKIT_API BOOL AddBmpMenuBitmapResource(UINT nIDstdBmpName, const UINT* lpIDArray, UINT nIDCount);
	TOOLKIT_API BOOL AddBmpMenuBitmap(HBITMAP hBmpSmall, const UINT* lpIDArray, UINT nIDCount);

	// Returns the SECBmpMenuPlugIn object
	TOOLKIT_API SECBmpMenuPlugIn* GetBmpMenuPlugIn() const;

	//@cmember
	/* Switches the menu on the menubar when running with a cool look menubar.*/
	TOOLKIT_API void SwapMenu(UINT nID);

	//@cmember
	/* Loads additional menus that are not created by the document templates.*/
	TOOLKIT_API BOOL LoadAdditionalMenus(UINT nCount, UINT nIDMenu, ...);


	//@cmember
	/* Sets CBRS_HIDE_INPLACE for all control bars. Call when used with Ole Containers.*/
	TOOLKIT_API void EnableOleContainmentMode();

// operation:  enabling handler for WM_SYSCOMMANDEX
//   WM_SYSCOMMANDEX is an OTPRO extension to WM_SYSCOMMAND that allows the
//   frame type to change dynamically (mdi child, docking, floating).  An extra
//   caption button is used to automatically generate WM_SYSCOMMANDEX messages
//   for the user.  Turn on WM_SYSCOMMANDEX handling with flag SCXOPT_ENABLED.
//   Turn off the caption button with SCXOPT_ENABLED|SCXOPT_NO_CAPTION_BUTTON.  
//   Similarly, use the flag SCXOPT_NO_HANDLE_RDBLCLK to disable right double
//   click firing of WM_SYSCOMMANDEX.
//   All flags are ignored unless SCXOPT_ENABLED is used.
//   The SCXOPT_ constants are from the namespace ns_SysCommandEx.
public:
	//@cmember
	// Enable extended system commands. 
     TOOLKIT_API virtual void EnableSysCommandEx(DWORD dwScxFlags);

// advanced properties:  message handling filter
//   m_pMsgFilter               -- a generic container that can have multiple sub-filters added.
//   m_pScxMsgFilterDescriptors -- table of descriptors for the msg filters needed for the WM_SYSCOMMANDEX handler
//                                 See implementation of EnableSysCommandEx() for example usage.
public:
     SECMsgFilter * m_pMsgFilter;
     SECMsgFilter::DescriptorTable m_pScxMsgFilterDescriptors;

     // Auto Hide Members
     SECAutoHideBar m_dockHideLeft;
     SECAutoHideBar m_dockHideTop;
     SECAutoHideBar m_dockHideBottom;
     SECAutoHideBar m_dockHideRight;

private:
	SECMsgFilter::Descriptor* m_pMaxMDIDockingButtonDescriptor;
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECMDIFrameWnd)
	//@cmember
	// OnSetPreviewMode handler.
	TOOLKIT_API virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
    //}}AFX_VIRTUAL
	//@cmember
    // overridden to provide default handling for WM_SYSCOMMANDEX
    TOOLKIT_API virtual LRESULT DefWindowProc(UINT uiMsg, WPARAM wParam, LPARAM lParam); 

// Message handler member functions
protected:
	//@cmember
	// OnSysColorChange handler.
	TOOLKIT_API afx_msg void OnSysColorChange();
	//@cmember
	/* Traps WM_EXTENDCONTEXTMENU message sent by the SECControlBar class after it creates a context menu.  Trap this message if you wish to customize the default context menu.*/
    TOOLKIT_API afx_msg LRESULT OnExtendContextMenu(WPARAM wParam, LPARAM lParam);

	//////////////////////////////////////////////////////////////////
	//					Menu Bar Enhancments						//
	//////////////////////////////////////////////////////////////////
public:
	//@cmember
	// Do we have a menu bar?
	TOOLKIT_API BOOL HasMenuBar();
	//@cmember
	// Get menubar.
	TOOLKIT_API SECMenuBar* GetMenuBar();
	//@cmember
	// Set menubar.
	inline void SetMenuBar(SECMenuBar* pMenuBar) { m_pMenuBar=pMenuBar; }
	//@cmember
	// Get menu.
	TOOLKIT_API CMenu* GetMenu() const;
	//@cmember
	// Returns appropriate default HMENU, accounting for menubar state
	TOOLKIT_API virtual HMENU GetDefaultMenu();
	//@cmember
	//Special Message Handler...
	TOOLKIT_API afx_msg int OnCreate( LPCREATESTRUCT lpcs );
	TOOLKIT_API afx_msg void OnClose();
#if(_MFC_VER >= 0x0700)
	TOOLKIT_API afx_msg void OnDestroy();
#endif

	//Special Virtuals
	//@cmember
	// Activate menu.
	TOOLKIT_API virtual void ActivateMenu(UINT nIDMenuInfo);
	//@cmember
	// Load frame.
	TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
						               CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//@cmember
	// OnCreateClient handler.
	TOOLKIT_API virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//@cmember
	// Called when the zoom state of a window changes
	TOOLKIT_API virtual void OnMDIZoomChange();
	//@cmember
	// Updates the window menu
	TOOLKIT_API virtual void UpdateWindowMenu();
	//@cmember
	// Needed PlugIn Overrides
	TOOLKIT_API virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	TOOLKIT_API virtual BOOL    PreTranslateMessage( MSG* pMsg );
	//@cmember
	// Accessor the dynamic controlbar allocation list
	inline CPtrList* GetListAllocControlBars() { return &m_listAllocControlBars; }
	//@cmember
	// Ole container support with menu bars
	TOOLKIT_API virtual BOOL NegotiateBorderSpace(UINT nBorderCmd, LPRECT lpRectBorder);

	// Implementation public variable.
	BOOL m_bDoingMDIFloat;
	//@cmember
	// OnContextHelp handler.
	TOOLKIT_API afx_msg void OnContextHelp();
	//@cmember
	// Set the menu's bitmap transparency color.
	inline virtual void SetMenuBmpTransparencyColor(COLORREF clrBmpTransparent, BOOL bUseCustomBmpTransparentColor = TRUE)
	{ 
		m_clrBmpTransparency = clrBmpTransparent; 
		m_bUseBmpTransparency = bUseCustomBmpTransparentColor;
	}
	//@cmember
	// Get the menu's bitmap transparency color.
	inline virtual COLORREF GetMenuBmpTransparentColor() 
	{
		return m_bUseBmpTransparency;
	}

protected:
	SECMenuBar * m_pMenuBar;
	stingray::foundation::SECWndPlugIn * m_pMenuBarFeature;
	BOOL           m_bBmpMenu;
	BOOL           m_bBmpMenuManaged;
	HMENU m_hMenuFrame;
	CMap<UINT, UINT, HMENU, HMENU> m_mapExtraMenus;	// Additional menu handles
	UINT m_nIDCurMenuRsrc;							// ID of current frame window menu resource
	UINT m_nIDMenuResource;
	CPtrList m_listAllocControlBars;

	COLORREF	m_clrBmpTransparency;
	BOOL		m_bUseBmpTransparency;

	// suppress frame menu updates if using a menubar
	inline virtual BOOL SuppressUpdateMenuForMenubar() { return (BOOL)(SEC_INT)m_pMenuBar; }

	TOOLKIT_API BOOL ProcessHelpMsg(MSG& msg, DWORD* pContext);

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
private:
	// Cache the return value of InitWorkspaceMgrEx to use in a derived class.
	SECWorkspaceManagerEx* m_pWorkspaceManagerEx;

// Implementation
protected:
	//@cmember
	// Get the Windows version.
	TOOLKIT_API void GetWindowsVersion();
	BOOL m_bIsWin95orAbove;
	//@cmember
	// Virtual destructor.
    TOOLKIT_API virtual ~SECMDIFrameWnd();
	//@cmember
	// Get the embedded frame.
    TOOLKIT_API virtual SECFrameWnd * GetEmbeddedFrame ( CControlBar * pwndBar );
	//@cmember
	// Reset the style for embedded frame floating.
    TOOLKIT_API virtual void ResetStyleForEmbeddedFrameFloat ( SECFrameWnd * pwndEmbeddedFrame, BOOL bToFloating );
	//@cmember
	// Adjust the floating embedded frame size.
    TOOLKIT_API virtual void AdjustFloatingEmbeddedFrameSize ( SECFrameWnd * pwndEmbeddedFrame );
	//@cmember
	// Notify active view.
    TOOLKIT_API virtual void NotifyActiveView (UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//@cmember
	// Returns the HMENU for the given id.
	TOOLKIT_API virtual HMENU MenuFromResource(UINT nID);
	//@cmember
	// Class local NotifyActiveView function
    class TOOLKIT_API CViewWithSECMDIFrameFriendship : public CView { friend class SECMDIFrameWnd; }; 

public:
	//@cmember
	// Dock controlbar.
	TOOLKIT_API void DockControlBar(CControlBar* pBar, CDockBar* pDockBar, LPCRECT lpRect = NULL);
	//@cmember
	// Recalculate layout.
	TOOLKIT_API virtual void RecalcLayout(BOOL bNotify = TRUE);
	//@cmember
	// OnCmdMsg handler.
	TOOLKIT_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//@cmember
	// OnUpdateFrameMenu handler.
	TOOLKIT_API virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
	//@cmember
	// OnSetDefaultDockPosAndSize handler.
    TOOLKIT_API virtual void OnSetDefaultDockPosAndSize(UINT & rnDockBarID, SECDockPos & rPos, SECDockSize & rSize);
    
    CArray<UINT,UINT> m_nDockCycle;
    int m_iDockCyclePos;

#if(_MFC_VER >= 0x0700)
	//@cmember
	// Cleanup dockbars.
	TOOLKIT_API void DestroyDockBars();
#endif

protected:
	//@cmember
	// OnCommand handler.
	TOOLKIT_API virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnEnterIdle handler.
	TOOLKIT_API virtual void OnEnterIdle(UINT nWhy, CWnd* pWho);

	// Generated message map functions
    //{{AFX_MSG(SECMDIFrameWnd)
	//@cmember
	// OnNcActivate handler.
	TOOLKIT_API afx_msg BOOL OnNcActivate(BOOL bActive);
	//@cmember
	// OnNcPaint handler.
	TOOLKIT_API afx_msg void OnNcPaint();
#if ( _MFC_VER < 0x0700 )
	//@cmember
	// OnActivateApp handler.
	TOOLKIT_API afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
#else
	//@cmember
	// OnActivateApp handler.
	TOOLKIT_API afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
#endif
	//@cmember
	// OnActivate handler.
    TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	//@cmember
	// OnSetText handler.
	TOOLKIT_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnCommandHelp handler.
	TOOLKIT_API afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnSecGetMenu handler.
	TOOLKIT_API afx_msg LRESULT OnSecGetMenu(WPARAM wParam, LPARAM lParam);
#if (_MFC_VER >= 0x0800)  // Visual Studio 2005 (as of CTP August 2005)
	//@cmember
	// OnNcHitTest handler.
	TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	//@cmember
	// OnNcHitTest handler.
	TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
	//@cmember
	// OnEnable handler.
	TOOLKIT_API afx_msg void OnEnable(BOOL bEnable);

	// Default handlers for the workspace functions to assure the menu
	// items are properly enabled (plugin will not enable menus, but
	// will accept commands)
	DECLARE_WSMGREX_DEFAULT_HANDLERS()
	//@cmember
	// OnNcLButtonDown handler.
    TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//@cmember
	// OnNcRButtonDown handler.
    TOOLKIT_API afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	//@cmember
	// OnLButtonUp handler.
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//@cmember
	// OnMouseMove handler.
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	// OnNcRButtonDblClk handler.
 	TOOLKIT_API afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	//@cmember
	// OnEraseBkgnd handler.
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SECMDIChildWnd

/////////////////////////////
// AutoDuck tag block block for SECMDIChildWnd 
// adinsert AutoDuck insertion point for SECMDIChildWnd 
//@doc SECMDIChildWnd 
//@class The SECMDIChildWnd class derives from CMDIChildWnd and adds the implementation details 
// required to support the enhanced docking window capabilities.  
//@comm
// To make use of this class, just re-derive your CMDIChildWnd-based class from SECMDIChildWnd 
// instead.  This class adds no new members to those inherited from CMDIChildWnd.
//
// See the SCRIBBLE sample in the \SAMPLES\TOOLKIT\STANDARD\MDI\MT_SCRIB directory for a 
// demonstration of this class.
//@xref <c SECMDIFrameWnd> <c SECWorksheet>
//@base public | CMDIChildWnd
class SECMDIChildWnd : public CMDIChildWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECMDIChildWnd)

protected:
	//@cmember
	// SECMDIChildWnd Constructor.
    TOOLKIT_API SECMDIChildWnd(); 

	//////////////////////////////////////////////////////////////////
	//					Menu Bar Enhancments						//
	//////////////////////////////////////////////////////////////////
public:
	//@cmember
	// Load frame from resource.
	TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle,CWnd* pParentWnd, CCreateContext* pContext);
	//@cmember
	// Refresh frame menu.
	TOOLKIT_API virtual void RefreshFrameMenu(CWnd* pActiveWnd);		// smart refresh of current frame window menu
	//@cmember
	// Get menu resource id.
	inline UINT GetMenuRsrc() { return m_nIDMenuRsrc; }

	//@cmember
	/* Switches the menu on the menubar when running with a cool look menubar.*/
	TOOLKIT_API void SwapMenu(UINT nID);

	class TOOLKIT_API CViewWithSECMDIChildFriendship : public CView { friend class SECMDIChildWnd; }; 

protected:
	UINT m_nIDMenuRsrc;
	BOOL m_bUsingMenuBars;
	HMENU m_hUpdateFrameMenu;
	//@cmember
	// Determine which menu to use from template.
	TOOLKIT_API void DetermineMenuToUse( CMultiDocTemplate* pTemplate );
	//@cmember
	// OnUpdateFrameMenu handler.
	TOOLKIT_API virtual void OnUpdateFrameMenu(BOOL bActive, CWnd* pActivateWnd, HMENU hMenuAlt);
	//@cmember
	// OnSize handler.
	TOOLKIT_API afx_msg void OnSize( UINT nType, int cx, int cy );
	//@cmember
	// OnMDIActivate handler.
	TOOLKIT_API afx_msg void OnMDIActivate( BOOL bActive, CWnd* pActivateWnd, CWnd* pDeactivateWnd );

// Operations
public:
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECMDIChildWnd)
    //}}AFX_VIRTUAL
	//@cmember
     // Overridden to provide default handling for WM_SYSCOMMANDEX
     TOOLKIT_API virtual LRESULT DefWindowProc(UINT uiMsg, WPARAM wParam, LPARAM lParam); 

// Implementation
protected:
	//@cmember
	// SECMDIChildWnd destructor.
    TOOLKIT_API virtual ~SECMDIChildWnd();

// operation:  enabling handler for WM_SYSCOMMANDEX
//   WM_SYSCOMMANDEX is an OTPRO extension to WM_SYSCOMMAND that allows the
//   frame type to change dynamically (mdi child, docking, floating).  An extra
//   caption button is used to automatically generate WM_SYSCOMMANDEX messages
//   for the user.  Turn on WM_SYSCOMMANDEX handling with flag SCXOPT_ENABLED.
//   Turn off the caption button with SCXOPT_ENABLED|SCXOPT_NO_CAPTION_BUTTON.  
//   Similarly, use the flag SCXOPT_NO_HANDLE_RDBLCLK to disable right double
//   click firing of WM_SYSCOMMANDEX.
//   All flags are ignored unless SCXOPT_ENABLED is used.
//   The SCXOPT_ constants are from the namespace ns_SysCommandEx.
public:
	//@cmember
	// Enable WM_SYSCOMMANDEX handling.
     TOOLKIT_API virtual void EnableSysCommandEx(DWORD dwScxFlags);

// 11/05/03
#if(_MFC_VER >= 0x0700)
	 //@cmember
	 // Cleanup dockbars.
	TOOLKIT_API void DestroyDockBars();
#endif
// advanced properties:  message handling filter
//   m_pMsgFilter               -- a generic container that can have multiple sub-filters added.
//   m_pScxMsgFilterDescriptors -- table of descriptors for the msg filters needed for the WM_SYSCOMMANDEX handler
//                                 See implementation of EnableSysCommandEx() for example usage.
public:
     SECMsgFilter * m_pMsgFilter;
     SECMsgFilter::DescriptorTable m_pScxMsgFilterDescriptors;

	// Generated message map functions
    //{{AFX_MSG(SECMDIChildWnd)
	//@cmember
	// OnMouseActivate handler.
	TOOLKIT_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//@cmember
	// OnChildActivate handler.
	TOOLKIT_API afx_msg void OnChildActivate();
	//@cmember
	// OnNcActivate handler.
	TOOLKIT_API afx_msg BOOL OnNcActivate(BOOL bActive);
	//@cmember
	// OnParentNotify handler.
    TOOLKIT_API afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//@cmember
	// OnNcPaint handler.
	TOOLKIT_API afx_msg void OnNcPaint();
	//@cmember
	// OnNcLButtonDown handler.
    TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//@cmember
	// OnNcRButtonDown handler.
    TOOLKIT_API afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	//@cmember
	// OnSetText handler.
    TOOLKIT_API afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//@cmember
	// OnLButtonUp handler.
    TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//@cmember
	// OnMouseMove handler.
    TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	// OnNcRButtonDblClk handler.
 	TOOLKIT_API afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	//@cmember
	// OnSetCursor handler.
	TOOLKIT_API afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	//@cmember
	// OnNcRButtonUp handler.
	TOOLKIT_API afx_msg void OnNcRButtonUp(UINT nFlags, CPoint point);
	//@cmember
	// OnDestroy handler.
	TOOLKIT_API afx_msg void OnDestroy( );
	//}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SECControlBarMDIChildWnd

class SECControlBarMDIChildWnd : public SECMDIChildWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECControlBarMDIChildWnd)

// Constructors
protected:
	//@cmember
	// SECControlBarMDIChildWnd constructor.
	TOOLKIT_API SECControlBarMDIChildWnd();           // protected constructor used by dynamic creation

public:
	SECDockBar	m_wndDockBar;		

// Overrides
	//@cmember
	// Recalculate layout.
	TOOLKIT_API void RecalcLayout(BOOL bNotify = TRUE);

// Implementation
protected:
	//@cmember
	// SECControlBarMDIChildWnd destructor.
	TOOLKIT_API virtual ~SECControlBarMDIChildWnd();
	//@cmember
	// PreCreateWindow handler.
	TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//@cmember
	// OnCreateClient handler.
	TOOLKIT_API virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//@cmember
	// OnUpdateFrameTitle handler.
	TOOLKIT_API virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

	// Generated message map functions
	//{{AFX_MSG(SECControlBarMDIChildWnd)
	//@cmember
	// OnSize handler.
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	//@cmember
	// OnClose handler.
	TOOLKIT_API afx_msg void OnClose();
	//@cmember
	// OnWindowPosChanged handler.
	TOOLKIT_API afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//@cmember
	// OnShowWindow handler.
	TOOLKIT_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SWINMDI_H__

#else // WIN32                       

#define SECMDIFrameWnd CMDIFrameWnd
#define SECMDIChildWnd CMDIChildWnd

#endif // WIN32

