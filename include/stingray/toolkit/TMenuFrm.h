///////////////////////////////////////////////////////////////////////////////
// TMenuFrm.h : Declaration of SECClass
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
// Author:       Don
// Description:  SECMenuBar frame window support
//

//@doc SECMenuBar
//@mfunc UINT  | SECMenuBar | GetCurMenuID | Returns the current menu ID

//adinsert

#ifndef __TMENUFRM_H__
#define __TMENUFRM_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

#ifdef WIN32

#ifndef __TBTNMENU_H__
#include "toolkit\tbtnmenu.h"
#endif

#ifndef __PLUGIN_H__
#include "Foundation\patterns\MFC\plugin.h"
#endif

#ifndef __TBMPMENU_H__
#include "toolkit\TBmpMenu.h"
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

/////////////////////////////////////////////////////////////////////////////
// g_IsXXXXStyleEnabled, RWIsXXXXStyleEnabled(), RWSetXXXXStyle() 
// have been moved to RWUXTheme.h
/////////////////////////////////////////////////////////////////////////////

struct SECMenuBarBtnInfo : public SECBtnInfo
{
	UINT       m_nPos;
	SECStdBtn* m_pBtn;		// Pointer to button
};

// Maps bit flags to menu resources. Used for identifying which buttons
// are associated with which views.
typedef CMap<UINT, UINT, DWORD, DWORD> SECMapMenuIDToBit;

//@doc SECMenuBar 
//@class SECMenuBar replaces your normal menu with a dockable bar that has the look and feel of the Visual Studio and Office 97 menus.  The menu bar buttons are represented by a simple button class that contains the HMENU to display when clicked.  SECMenuBar uses SECCustomToolBar as a base class.  So not only do you get the cool flat look, you also gain complete customization of the menu bar when used in conjuntion with SECToolBarManager.  To integrate this class into your own existing aplication that uses the SECToolBarManager takes as little as three lines of code.  See VIZ for an example of an application that was converted to use the new menu bar classes.  The button map that is used in customizable toolbars to denote combo boxes, two-part buttons, and custom buttons can also be utilized to dynamically swap menus based on the currently active view.
//@base public | SECCustomToolBar

// Exported through base class. 
class SECMenuBar : public SECCustomToolBar
{
	TOOLKIT_DECLARE_DYNAMIC(SECMenuBar)

public:
	//@cmember
	/* Constructor*/
	TOOLKIT_API SECMenuBar();
	
	//@cmember
	/* Destructor*/
	TOOLKIT_API virtual ~SECMenuBar();

	//@cmember
	/* Creates the SECMenuBar window*/
	TOOLKIT_API virtual BOOL CreateEx(DWORD dwExStyle, CWnd* pParentWnd, DWORD dwStyle = 
				WS_VISIBLE | WS_CHILD | CBRS_TOP, UINT nID = AFX_IDW_CONTROLBAR_LAST, 
				LPCTSTR lpszTitle = NULL);

	TOOLKIT_API virtual int  IsAccelerated(TCHAR c) const;

	TOOLKIT_API void InvokeSysMenu();

	TOOLKIT_API void DropDownMenuHeader();

	TOOLKIT_API void NextMenu(BOOL m_bRight);
	
	//@cmember
	/* Loads the menu specified*/
	TOOLKIT_API BOOL LoadMenu(UINT nIDResource);
	//@cmember
	/* Switches to the menu specified*/
	TOOLKIT_API BOOL SwitchMenu(UINT nIDResource);
	//@cmember
	/* Enables the bit flag*/
	TOOLKIT_API virtual void EnableBitFlag(DWORD dwBit, BOOL bUpdate = FALSE );
	//@cmember
	/* Notifies you when the style is changing*/
	TOOLKIT_API virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);
	TOOLKIT_API virtual DWORD RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout);

	//@cmember
	/* Returns font used for the menu*/
	TOOLKIT_API virtual HFONT GetMenuFont() const;
	//@cmember
	/* Resets the menu*/
	TOOLKIT_API virtual void ResetMenus(BOOL bNoUpdate = FALSE);

	//@cmember
	/* Defines the menu resources to use.*/
	TOOLKIT_API virtual BOOL SetMenuInfo(int nCount, UINT nIDMenu, ...);

	// Add a button to the menubar
	TOOLKIT_API virtual void AddButton(int nIndex, int nID, BOOL bSeparator = FALSE, BOOL bNoUpdate = FALSE);

	//@cmember
	/* Returns the current menu ID*/
	inline UINT GetCurMenuID() const { return m_nIDMenu; }
	
	// Prevent the menubar from ever being seen as a non-cool style. This function will 
	// be changed later when non-cool look functionality is defined for the menu bar.
	inline virtual BOOL CoolLookEnabled() const { return TRUE; }

	//Set Full Screen Display
	inline void SetMenuBarFSMode(BOOL bSet) { m_bFSView = bSet; };

	// override DelayShow required for Ole Containment to work properly (MDI case)
	TOOLKIT_API virtual void DelayShow(BOOL bShow);
	
	// for the DelayShow setting. Required for Ole Containment to work properly (MDI case)
	TOOLKIT_API void SetIgnoreDelayShow(BOOL b);
	TOOLKIT_API BOOL GetIgnoreDelayShow();

protected:
	//overrides necessary to accomodate menubar display during FullScreen Mode
	TOOLKIT_API virtual CSize CalcLayout(int nLength, DWORD dwMode);
	TOOLKIT_API virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);

// Implementation
public:
	SECMapMenuIDToBit m_mapMenuToBit;
	CStringArray      m_arrMenuTitles;

protected:
	BOOL              m_bRemoveSysMenu;
	HFONT             m_hMenuFont;
	DWORD			  m_dwBitFlag;			// Current menu bits;
	UINT              m_nIDMenu;			// Current menu ID
	BOOL			  m_bFSView;			// Flag to enable full screen display
	BOOL			  m_bIgnoreDelayShow;	// specifies whether DelayShow is to be ignored
											// This flag is checked only when bShow in DelayShow is FALSE

	// Loads the menu bar buttons from the given button map.
	TOOLKIT_API BOOL LoadBtnsFromBtnMap(const SECBtnMapEntry* pMap);

	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

class SECBtnCaption : public SECStdBtn
{
	// Dynamic button creation helpers defined in tbtnstd.h
	TOOLKIT_DECLARE_BUTTON(SECBtnCaption);

public:
	TOOLKIT_API SECBtnCaption();
	TOOLKIT_API virtual ~SECBtnCaption();


	TOOLKIT_API virtual BOOL BtnPressDown(CPoint point);
	TOOLKIT_API virtual void BtnPressMouseMove(CPoint point);
	TOOLKIT_API virtual void BtnPressCancel();
	TOOLKIT_API virtual UINT BtnPressUp(CPoint point);
	TOOLKIT_API virtual int  OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	inline virtual BOOL CanDrag() const { return FALSE; }

	TOOLKIT_API CMDIChildWnd* GetMDIChild() const;

// Implementation
public:
	DWORD m_dwMDIChildStyle;

protected:
	int   m_cxCapBtn;
	int   m_cyCapBtn;
	int   m_nTracking;
	HTHEME m_hWindowTheme;

	TOOLKIT_API int HitTest(CPoint pt) const;

	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	TOOLKIT_API virtual void AdjustSize();

	// Draw face of button
	TOOLKIT_API virtual void DrawFace(SECBtnDrawData& data, BOOL bForce, int& x, int& y, 
						              int& nWidth, int& nHeight, int nImgWidth, CDC& dc);
};

/////////////////////////////////////////////////////////////////////////////

class SECCapMenuBtn : public SECTBMenuBtn
{
	// Dynamic button creation helpers defined in tbtnstd.h
	TOOLKIT_DECLARE_BUTTON(SECCapMenuBtn);

public:
	TOOLKIT_API SECCapMenuBtn();
	TOOLKIT_API virtual ~SECCapMenuBtn();

	virtual BOOL CanDrag() const { return FALSE; }
	TOOLKIT_API virtual void ShowMenu();

	TOOLKIT_API CMDIChildWnd* GetMDIChild() const;

// Implementation
public:
	HICON m_hIcon;

protected:
	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	TOOLKIT_API virtual void AdjustSize();

	// Draw face of button
	TOOLKIT_API virtual void DrawFace(SECBtnDrawData& data, BOOL bForce, int& x, int& y, 
						              int& nWidth, int& nHeight, int nImgWidth, CDC& dc);
};

/////////////////////////////////////////////////////////////////////////////

//@doc SECMDIMenuBar 
//@class SECMDIMenuBar is a SECMenuBar derivative that handles the system menu and caption buttons when an MDI child window is maximized.  All other features are the same as the SECMenuBar class.  See the three MDI samples in the MenuBar project for demonstrations.
//@base public | SECMenuBar
class SECMDIMenuBar : public SECMenuBar
{
	TOOLKIT_DECLARE_DYNAMIC(SECMDIMenuBar);

public:
	TOOLKIT_API SECMDIMenuBar(); 
	TOOLKIT_API virtual ~SECMDIMenuBar();

	TOOLKIT_API virtual BOOL SetButtons(const UINT* lpIDArray, int nIDCount);
	TOOLKIT_API virtual BOOL OnZoomChange(BOOL bDisable = FALSE);
	TOOLKIT_API virtual void EnableBitFlag(DWORD dwBit);
	TOOLKIT_API virtual int GetStdBtnHeight() const;

	// Load/Save the toolbar configuration
	TOOLKIT_API virtual void GetBarInfoEx(SECControlBarInfo* pInfo);
	TOOLKIT_API virtual void SetBarInfoEx(SECControlBarInfo* pInfo, CFrameWnd* pFrameWnd);

	TOOLKIT_API virtual void ResetMenus(BOOL bNoUpdate = FALSE);
	TOOLKIT_API virtual BOOL MenuMouseEvent(MSG* pMsg);

protected:
	SECBtnCaption	m_capBtn;
	SECCapMenuBtn	m_sysBtn;
	UINT			m_nLBtnInit;

	TOOLKIT_API void AddCaptionBtns();
	TOOLKIT_API virtual void RemoveBtns();

	// Removes and re-adds the caption buttons
	TOOLKIT_API void RemoveCapBtns(BOOL& bRemoved1, BOOL& bRemoved2);
	TOOLKIT_API void ReAddCapBtns(BOOL bRemoved1, BOOL bRemoved2);

	// Handles a button drop
	TOOLKIT_API virtual BOOL DropButton(CRect& dropRect, SECStdBtn* pDragBtn, BOOL bAdd, 
							BOOL bNoUpdate = FALSE);

	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

class SECMenuBarMessages
{
public:
	TOOLKIT_API SECMenuBarMessages();
	TOOLKIT_API virtual ~SECMenuBarMessages();

	inline BOOL HasMenuBar() { return (m_pMenuBar != NULL) ? TRUE : FALSE; }
	inline SECMenuBar* GetMenuBar() { return m_pMenuBar; }
	
	TOOLKIT_API virtual void AwaitMenuSelect(BOOL bRight);
	TOOLKIT_API virtual void AbortMenu();
	TOOLKIT_API virtual void ActivateMenu(UINT nIDMenuInfo);
	TOOLKIT_API virtual void DropDownMenuHeader();
	TOOLKIT_API virtual void ProcessMenuHeaderMouseMove(CPoint& pt);
	TOOLKIT_API virtual void IgnoreNextKeyUp();
	TOOLKIT_API virtual BOOL ProcessSysMenuNcEvent(MSG* pMsg);

protected:
	SECMenuBar* m_pMenuBar;
	BOOL        m_bHiliteFirst;
	BOOL        m_bSeenSelect;
	BOOL        m_bRight;
	BOOL			m_bIgnoreNextKeyUp;

	virtual CWnd* GetWnd() = 0;
	TOOLKIT_API virtual void DisplayMenu(SECCustomToolBar* lpTB, HMENU hMenu, LPSECNMTOOLBAR lpnmTB);
	TOOLKIT_API virtual void DisplaySysMenu(SECCustomToolBar* lpTB, HMENU hMenu, LPSECNMTOOLBAR lpnmTB);
	TOOLKIT_API virtual void InstallHook(BOOL bInstall);
	TOOLKIT_API virtual void InstallHeaderHook(BOOL bInstall);
	TOOLKIT_API virtual BOOL MFPreTranslateMessage(MSG* pMsg);
	TOOLKIT_API virtual BOOL MFOnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	TOOLKIT_API virtual LRESULT MFOnMenuBarProd(WPARAM, LPARAM);
	TOOLKIT_API virtual BOOL MFOnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	TOOLKIT_API virtual BOOL MFOnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	TOOLKIT_API virtual BOOL MFOnSysCommand(UINT nID, LPARAM lParam);
	TOOLKIT_API virtual BOOL MFOnNcActivate(BOOL bActive);
};

/////////////////////////////////////////////////////////////////////////////

class SECMenuBarFeature : public SECBmpMenuPlugIn, public SECMenuBarMessages
{
	TOOLKIT_DECLARE_DYNAMIC( SECMenuBarFeature )
public:
	TOOLKIT_API SECMenuBarFeature();
	TOOLKIT_API virtual ~SECMenuBarFeature();

	TOOLKIT_API void AttachMenuBarTo( SECMenuBar* pMenuBar );

	TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );
	TOOLKIT_API virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	
	TOOLKIT_API BOOL IsSystemMenu();

protected:
	inline virtual CWnd* GetWnd(){ return this; }

	TOOLKIT_API afx_msg void OnMenuSelect( UINT nItemID, UINT nFlags, HMENU hSysMenu );
	TOOLKIT_API afx_msg LRESULT OnMenuBarProd( WPARAM, LPARAM );
	TOOLKIT_API afx_msg void OnInitMenuPopup( CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu );
	TOOLKIT_API afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	TOOLKIT_API afx_msg BOOL OnNcActivate(BOOL bActive);

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//Helper class for allowing access to SECMenuBarFeature's protected members
class SECFriendMenuBarFeature : public SECMenuBarFeature
{
	TOOLKIT_API friend LRESULT CALLBACK SECKeyboardHeaderHookProc(int nCode, WPARAM wParam, LPARAM lParam); 
};

// Theme style function definitions have been moved to RWUXTheme.

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////

#endif	// WIN32

#endif	// __TMENUFRM_H__

