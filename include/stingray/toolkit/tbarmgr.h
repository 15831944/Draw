///////////////////////////////////////////////////////////////////////////////
// tbarmgr.h
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
//  Authors:		Don
//  Description:	Declarations for SECToolBarManager
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBARMGR_H__
#define __TBARMGR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SBARMGR_H__
#include "toolkit\sbarmgr.h"
#endif

#ifndef __TBARCUST_H__
#include "toolkit\tbarcust.h"
#endif

#ifndef __TBTNSTD_H__
#include "toolkit\tbtnstd.h"
#endif

#ifndef __SDOCKSTA_H__
#include "toolkit\sdocksta.h"
#endif

#ifndef __TBMPMGR_H__
#include "toolkit\TBmpMgr.h"
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
// SECMenuMap - used in calls to SetMenuMap (maps menu resource ID to
//              bit flag)
//
struct SECMenuMap
{
	UINT  m_nID;				// Menu resource ID	
	DWORD m_dwBit;				// Bit setting
};

/////////////////////////////////////////////////////////////////////////////
// SECToolBarManager
//

// Registered messages forwarded by ToolBar manager
extern TOOLKIT_API const int wmSECNotifyMsg;			// ToolBar notification
extern TOOLKIT_API const int wmSECToolBarWndNotify;		// SECWndBtn derivative notification

//@doc SECToolBarManager 
//@class Implements the toolbar management to allow runtime customization of SECCustomToolBar/SECMenuBar objects.
//@BASE public | SECControlBarManager
//@xref <c SECControlBarManager> <c SECCustomToolBar> <c SECMenuBar>
class SECToolBarManager : public SECControlBarManager
{
	TOOLKIT_DECLARE_DYNAMIC(SECToolBarManager)

// Construction
public:
	
	//@access Construction/Initialization

	//@cmember
	/* Constructor*/
	TOOLKIT_API SECToolBarManager();

	//@cmember
	/* Constructor*/
	TOOLKIT_API SECToolBarManager(CFrameWnd* pFrameWnd,CFrameWnd* pOwnerFrame=NULL);

	//@access Operations
public:
	//@cmember
	/* Define a customizable toolbar default state.*/
	TOOLKIT_API void DefineDefaultToolBar(UINT nID, 
							  const CString& strTitle, 
							  UINT    nBtnCount, 
							  UINT*   lpBtnIDs,
							  DWORD   dwAlignment   = CBRS_ALIGN_ANY,
							  UINT    nDockBarID    = AFX_IDW_DOCKBAR_TOP,
							  UINT    nDockNextToID = NULL,
							  BOOL    bDocked       = TRUE,
							  BOOL    bVisible      = TRUE);

	//@cmember
	/* Define a customizable toolbar default state based on a toolbar resource.*/
	TOOLKIT_API void DefineDefaultToolBar(UINT nID, 
							  const CString& strTitle, 
							  UINT    nToolbarID,
							  UINT&	  nRetButtonCount,
							  UINT*&  pRetButtonArray,
							  DWORD   dwAlignment   = CBRS_ALIGN_ANY,
							  UINT    nDockBarID    = AFX_IDW_DOCKBAR_TOP,
							  UINT    nDockNextToID = NULL,
							  BOOL    bDocked       = TRUE,
							  BOOL    bVisible      = TRUE);

	// Defines the layout of the menu bar.
	TOOLKIT_API void LayoutMenuBar(UINT nBtnCount, UINT* lpBtnIDs);
	TOOLKIT_API void GetMenuBarLayout(UINT& nBtnCount, const UINT*& lpBtnIDs) const;

	// Iterates all menu resource ids used to preconfigure the menubar.
	TOOLKIT_API BOOL SetMenuInfo(int nCount, UINT nIDMenu, ...);

	// Returns TRUE if the mainframe is currently enabled. FALSE if we are
	// in customize-mode and we are pretending that it is disabled.
	TOOLKIT_API BOOL IsMainFrameEnabled();

	// Put's all toolbars in/out of customize mode.
	TOOLKIT_API void EnableConfigMode(BOOL bEnable=TRUE);
	TOOLKIT_API BOOL InConfigMode() const;

	// @cmember
	/* Returns TRUE (with the btn rect. in question) if we are currently processing a button command.*/
	TOOLKIT_API BOOL IsToolBarCommand(CRect& rect) const;

	//@cmember
	/* Returns the toolbar under the given window rect.*/
	TOOLKIT_API virtual SECCustomToolBar* ToolBarUnderRect(const CRect& rect) const;

	//@cmember
	/* Returns the toolbar pointer for a given default toolbar ID. */
	TOOLKIT_API virtual SECCustomToolBar* ToolBarFromID(const UINT nToolBarID) const;

	// Returns the buttons for a given default toolbar ID.
	TOOLKIT_API BOOL GetDefaultBtns(UINT nID, int& nCount, UINT*& lpBtnIDs);

	//@cmember
	/* Creates a new 'user' toolbar*/
	TOOLKIT_API SECCustomToolBar* CreateUserToolBar(LPCTSTR lpszTitle = NULL);

	//@cmember
	/* Loads the toolbar resource (to be shared by all toolbars)*/
	TOOLKIT_API BOOL LoadToolBarResource(LPCTSTR lpszStdBmpName, LPCTSTR lpszLargeBmpName = NULL);

	//@cmember
	/* Loads the toolbar resource (to be shared by all toolbars)*/
	TOOLKIT_API BOOL LoadToolBarResource(UINT nIDStdBmp, UINT nIDLargeBmp = 0);
	
	// Alternative's to LoadToolBarResource ... used for defining several
	// toolbar resources, then a singe call to LoadToolBarResource() to load
	// them.

	//@cmember
	/* Loads the toolbar resource (to be shared by all toolbars)*/
	TOOLKIT_API BOOL LoadToolBarResource();

	//@cmember
	/* Appends a toolbar resource to the current LoadToolBarResource image*/
	TOOLKIT_API BOOL AddToolBarResource(LPCTSTR lpszStdBmpName, LPCTSTR lpszLargeBmpName = NULL);

	//@cmember
	/* Appends a toolbar resource to the current LoadToolBarResource image*/
	TOOLKIT_API BOOL AddToolBarResource(UINT nIDStdBmp, UINT nIDLargeBmp = 0);

	//@cmember
	/* Append a new bitmap resource for use with the available custom toolbar buttons*/
	TOOLKIT_API BOOL AddBitmapResource(LPCTSTR lpszStdBmpName, LPCTSTR lpszLargeBmpName,
						   const UINT* lpIDArray, UINT nIDCount);

	//@cmember
	/* Append a new bitmap resource for use with the available custom toolbar buttons*/
	TOOLKIT_API BOOL AddBitmapResource(UINT nIDstdBmpName, UINT nIDLargeBmpName,
						   const UINT* lpIDArray, UINT nIDCount);

	//@cmember
	/* Append a new bitmap for use with the available custom toolbar buttons*/
	TOOLKIT_API BOOL AddBitmap(HBITMAP hBmpSmall, HBITMAP hBmpLarge,
				   const UINT* lpIDArray, UINT nIDCount);

	// Returns the toolbar managers, bitmap manager object.
	inline SECBmpMgr* GetBmpMgr() const { return m_pBmpMgr; }

	// Returns the rectangle within which toolbar buttons cannot be dropped
	TOOLKIT_API void GetNoDropRect(CRect& rect) const;

	//@cmember
	/* Runs the view toolbars dialog.*/
	TOOLKIT_API int ExecViewToolBarsDlg();

	//@cmember
	/* Passes notification through to all buttons of nID*/
	TOOLKIT_API void InformBtns(UINT nID, UINT nCode, void* pData);

	// Functions for enabling/disabling tooltips and flyby help
	//@access State Configuration

	//@cmember
	/* Enable tooltips for all custom toolbars*/
	TOOLKIT_API void EnableToolTips(BOOL bEnable=TRUE);

	//@cmember
	/* Enable flyby help for all custom toolbars*/
	TOOLKIT_API void EnableFlyBy(BOOL bEnable=TRUE);

	//@cmember
	/* Return current tooltip state*/
	TOOLKIT_API BOOL ToolTipsEnabled() const;

	//@cmember
	/* Return current flyby help state*/
	TOOLKIT_API BOOL FlyByEnabled() const;

	//@cmember
	/* Enable large button mode*/
	TOOLKIT_API void EnableLargeBtns(BOOL bEnable=TRUE);

	//@cmember
	/* Return current large button mode status*/
	TOOLKIT_API BOOL LargeBtnsEnabled() const;

	//@cmember
	/* Enable "cool look" mode*/
	TOOLKIT_API void EnableCoolLook(BOOL bEnable=TRUE,DWORD dwExCoolLookStyles=CBRS_EX_COOLBORDERS|CBRS_EX_GRIPPER);

	//@cmember
	/* Return current "cool look" mode*/
	TOOLKIT_API BOOL CoolLookEnabled() const;

	// Function to initialise info in toolbar.
	TOOLKIT_API void SetToolBarInfo(SECCustomToolBar* pToolBar);

	// Initializes the menu map information across all menubars
	TOOLKIT_API void SetMenuMap(const SECMenuMap* pMap, int nCount);

	//@cmember
	/* Intialize the toolbar button map information across all toolbars*/
	TOOLKIT_API void SetButtonMap(const SECBtnMapEntry* pMap);

	//@cmember
	/* Get the button map information*/
	TOOLKIT_API const SECBtnMapEntry* GetButtonMap() const;

	// Return the aux button map.
	TOOLKIT_API const SECBtnMapEntry* GetAuxButtonMap() const;

	// Save/Restore manager state (i.e. tooltips, cool look etc.)
	TOOLKIT_API virtual void LoadState(LPCTSTR lpszProfileName);
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pBarNode);	
	TOOLKIT_API virtual void SaveState(LPCTSTR lpszProfileName) const;
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory,
						   SECPersistentTreeNode* pParent);		

	// This is called by LoadState to establish default toolbar
	// layout when no configured workspace was loaded. If you
	// are not using a workspace manager, call this directly
	// to establish a default toolbar layout.

	//@cmember
	/* Load a default toolbar configuration state.*/
	TOOLKIT_API virtual void SetDefaultDockState();

	// Support for dynamic control bar save/restore. Use when
	// a variable number of control bars of a particular type
	// must be saved and restored.  (i.e. User-defined toolbars)
	TOOLKIT_API virtual DWORD GetBarTypeID(CControlBar* pBar) const;
	TOOLKIT_API virtual SECControlBarInfoEx* CreateControlBarInfoEx(SECControlBarInfo*) const;
	TOOLKIT_API virtual CControlBar* DynCreateControlBar(SECControlBarInfo* pBarInfo);

// Implementation
public:
	TOOLKIT_API virtual ~SECToolBarManager();

	// Nested class used to hold info. about the current commands
	class SECCurrentCommand
	{
	public:
		inline SECCurrentCommand() : m_nRef(1), m_bIn(FALSE) {}

		// This object is reference counted ...
		TOOLKIT_API LONG AddRef();
		TOOLKIT_API LONG Release();

		// Functions to set/get the command state
		TOOLKIT_API void SetCommand(BOOL bIn, const CRect& rect);
		TOOLKIT_API BOOL InCommand(CRect& rect) const;

	protected:
		TOOLKIT_API virtual ~SECCurrentCommand();

		LONG  m_nRef;		// My reference count
		CRect m_rect;		// Rectangle of button executing current command
		BOOL  m_bIn;		// TRUE if a button is current executing a command
	};

	// Enable/Disable the main frame while a customize dialog is up (disabling
	// all child windows of the mainframe).
	TOOLKIT_API void EnableMainFrame();
	TOOLKIT_API void DisableMainFrame();

	// Function returns the object that stores the current command state. Note
	// that the object is reference counted, so you must call Release when you
	// have finished with it.
	TOOLKIT_API SECCurrentCommand* GetCurCommandObject() const;

	// Function which receives notifications from toolbar.
	TOOLKIT_API void BarNotify(int nID, SECCustomToolBar::BarNotifyCode notify);

	// Function specifing which window should receive the toolbar notifications
	TOOLKIT_API void AddNotify(CWnd* pWnd);
	TOOLKIT_API void RemoveNotify(CWnd* pWnd);

	// Sets a window within which buttons cannot be dropped.
	TOOLKIT_API void SetNoDropWnd(CWnd* pWnd);

	// Returns the reference to pointer to toolbar with current config focus.
	inline SECCustomToolBar* GetConfigFocus() const { return m_pConfigFocus; }
	inline void SetConfigFocus(SECCustomToolBar* pFocus) { m_pConfigFocus = pFocus; }

	inline SECBtnDrawData& GetDrawData() { return m_drawData; }

	TOOLKIT_API void ChangeBarStyle(BOOL bAdd, DWORD dwStyle);
	TOOLKIT_API void ChangeExBarStyle(BOOL bAdd, DWORD dwExStyle);

	// Performs one-time initialisation
	TOOLKIT_API void Initialise();

protected:
	// Toggles bitmap between large and small
	TOOLKIT_API virtual BOOL ChangeBitmap();

	TOOLKIT_API virtual void ReparentToolBars();

	// Implementation, data members.
	struct SECDefaultToolBar			// Record for a default toolbar
	{
		UINT    nID;					// The toolbar ID
		CString lpszTitle;				// The toolbar title
		UINT    nBtnCount;				// No. of default buttons
		UINT*   lpBtnIDs;				// List of default buttons
		DWORD   dwAlignment;			// Default alignment mode 
		UINT    nDockBarID;				// Default bar to dock in
		UINT    nDockNextToID;			// Default bar to dock next to
		BOOL    bDocked;				// FALSE if bar is initialially float
		BOOL    bVisible;				// TRUE if bar is visible
	};

	// CArray specialization for IA64 compatible HWNDs 
	typedef CArray<SEC_DWORD, SEC_DWORD> SECDWordArray;
	SECDWordArray m_enabledList;		// List of windows which have been
										// disabled (EnableMainFrame)
	CPtrArray m_defaultBars;			// Array of default toolbars
	CPtrArray m_notifyWnds;				// Wnd's to pass toolbar notifications
	CWnd* m_pNoDropWnd;					// Wnd that won't accept dropped btns
	BOOL m_bMainFrameEnabled;			// TRUE if EnableMainFrame called
	BOOL m_bConfig;						// TRUE if in toolbar customize mode
	BOOL m_bToolTips;					// TRUE if tooltips enabled
	BOOL m_bFlyBy;						// TRUE if flyby help enabled
	BOOL m_bCoolLook;					// TRUE if "Cool" look enabled
	BOOL m_bLargeBmp;					// TRUE if using large bitmaps
	const SECBtnMapEntry* m_pBtnMap;	// Maps ID's to button types.
	SECBtnMapEntry* m_pAuxBtnMap;		// Aux version of button map.
	SECCustomToolBar* m_pConfigFocus;	// Toolbar with current config focus
	SECCurrentCommand* m_pCmd;			// Holds status about current command
	UINT* m_lpMenuBarBtnIDs;			// IDs for default menu bar layout
	UINT m_nMenuBarBtnCount;			// No. of btns in m_lpMenuBarBtnIDs
	SECBmpMgr* m_pBmpMgr;				// Manages all our bitmap resources
	SECBtnDrawData m_drawData;			// Shared drawing resources
	CFrameWnd* m_pOwnerFrame;			// Owner frame window, don't confuse with parent

public:
	CRuntimeClass* m_pToolBarClass;		// Used to create toolbars.
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBARMGR_H__

#endif // WIN32

