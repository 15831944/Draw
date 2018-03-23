///////////////////////////////////////////////////////////////////////////////
// FSView.h
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
//  Author:			Prakash Surendra
//  Description:	Declaration of SECFullScreenView
//

#ifndef __SECFULLSCREEN_H__
#define __SECFULLSCREEN_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif // __AFXPRIV_H__

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // __AFXTEMPL_H__

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

// Private messages, Constants & Macros

/////////////////////////////////////////////////////////////////////////////
#define SEC_IDR_FSVIEWER		0xE123
#define SEC_ID_FSTOOLBAR		0xE124

#define SEC_FSHIDEMENU			(WM_USER+0x0301)
#define FSM_SETMODE				(WM_USER+0x0302)

//Timer for keeping track of OT Menu bars
#define TIMER_MENUUPDATE		0xE001

//FS styles
#define SEC_FS_DEFAULT			0				//Use default toolbar icon and no menus
#define SEC_FS_DROPDOWNMENU		0x0001			//Enable drop-down menu display
#define SEC_FS_TEXTTOOLBAR		0x0002			//Use text-only tool bar
#define SEC_FS_TASKBARHIDE		0x0004			//Forcibly hide the Windows task bar
#define SEC_FS_NOCUSTTOOLBAR	0x0008			//Default to SECToolBar

//Default Toolbar Styles
#if _MFC_VER >= 0x0600
#define FS_DEFAULT_TBARSTYLES	CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER|CBRS_BORDER_3D|CBRS_SIZE_DYNAMIC
#else
#define FS_DEFAULT_TBARSTYLES	CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC
#endif

//callback for setting the FS toolbar styles
typedef void (CALLBACK *PFNFSSETSTYLES)(UINT& dwStyle, UINT& dwExStyle);

//Helper macro for determining the mainframe type
#define SEC_FS_SECFRAME(pFrmWnd) ( pFrmWnd->IsKindOf(RUNTIME_CLASS(SECFrameWnd)) || pFrmWnd->IsKindOf(RUNTIME_CLASS(SECMDIFrameWnd)) )

//Helper structure used for setting the FullScreen control bars
typedef struct tagSECFSBarState
{
	CControlBar* pCtrlBar;
	BOOL bFSModeOnly;
} SECFSBarState;
/////////////////////////////////////////////////////////////////////////////

// Forward declarations
class SECFSMainFrmListener;

/////////////////////////////////////////////////////////////////////////////
// SECFSMDIClientListener 
class SECFSMDIClientListener : public stingray::foundation::SECWndListener
{
//Nested Child frame listener
public:
	class SECFSChildFrmListener : public stingray::foundation::SECWndListener
	{
	friend class SECFSMDIClientListener;
	// Construction
	public:
		TOOLKIT_API SECFSChildFrmListener();
		TOOLKIT_API virtual ~SECFSChildFrmListener();

	protected:
		SECFSMainFrmListener* m_pMainFrmLstnr;

		inline void SetMainFrmRef(SECFSMainFrmListener* pMainFrmLstnr) { m_pMainFrmLstnr = pMainFrmLstnr; };
		//{{AFX_MSG(SECFSChildFrmListener)
		TOOLKIT_API afx_msg LRESULT OnWMGetMinMaxInfo(WPARAM wPar, LPARAM lPar);
		TOOLKIT_API afx_msg LRESULT OnWMSysCommand(WPARAM wPar, LPARAM lPar);
		TOOLKIT_API afx_msg LRESULT OnWMSize(WPARAM wPar, LPARAM lPar);
		//}}AFX_MSG
		TOOLKIT_DECLARE_MESSAGE_MAP()
	};


// SECFSMDIClientListener Construction
public:
	TOOLKIT_API SECFSMDIClientListener();
	TOOLKIT_API virtual ~SECFSMDIClientListener();

//Operations
	TOOLKIT_API virtual BOOL PlugInTo( CWnd* pWnd, SECFSMainFrmListener* pMainFrmLstnr);
	TOOLKIT_API virtual void UnPlug();

protected:
	SECFSChildFrmListener m_wndMDIChildLstnr;
	SECFSMainFrmListener* m_pMainFrmLstnr;

protected:
	TOOLKIT_API virtual BOOL IsWindowProc(HWND hWndListen);

	//{{AFX_MSG(SECFSMDIClientListener)
	TOOLKIT_API afx_msg LRESULT OnMDISetMenu(WPARAM wPar, LPARAM lPar);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// SECFSMainFrmListener 
class SECFSMainFrmListener : public stingray::foundation::SECWndListener
{
friend class SECFullScreenView;
friend class SECFSMDIClientListener;
friend class SECFSMDIClientListener::SECFSChildFrmListener;
// Construction
public:
	TOOLKIT_API SECFSMainFrmListener();
	TOOLKIT_API virtual ~SECFSMainFrmListener();

protected:
	SECFullScreenView* m_pFSViewer;
	BOOL m_bMenuing;
	BOOL m_bMenuFlag;
	BOOL m_bMenuBar;
	HWND m_hWndActiveChild;
	BOOL m_bSDI;
	BOOL m_bAllowClientMsg;

	HMENU m_hMenuCached;

	TOOLKIT_API void DisableFrameRecalcLayout(BOOL bVal);

	TOOLKIT_API virtual BOOL PlugInTo( CWnd* pWnd, SECFullScreenView* pViewer);	

	inline void SetActiveChild(HWND hWndChild)
	{
		ASSERT(::IsWindow(hWndChild));
		m_hWndActiveChild = hWndChild;		
	};

	TOOLKIT_API void HideMenuDisp();
	TOOLKIT_API BOOL RestoreMaxMenuState(CFrameWnd* pFrmWnd);
	inline void SetMenuNULL()	{ m_hMenuCached = NULL; };

	//{{AFX_MSG(SECFSMainFrmListener)
	TOOLKIT_API afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	TOOLKIT_API afx_msg void OnNcMouseMove( UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnToggleFullScreen();
	TOOLKIT_API afx_msg LRESULT OnExitMenuLoop(WPARAM wPar, LPARAM lPar);
#ifdef _WIN64 //RW64
	TOOLKIT_API afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
#else
	TOOLKIT_API afx_msg void OnSysCommand( UINT nID, LONG lParam );
#endif //_WIN64
	TOOLKIT_API afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	TOOLKIT_API afx_msg LRESULT OnFSHideMenu(WPARAM wPar, LPARAM lPar);
	TOOLKIT_API afx_msg void OnTimer( SEC_UINT nIDEvent );
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// SECFSToolBar 
template<class TBarBase>
class SECFSToolBar : public TBarBase
{
//Construction/Destruction
public:
	inline SECFSToolBar() {};
	inline virtual ~SECFSToolBar()	{};	

// Overrides
	inline virtual void OnUpdateCmdUI( CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/ )
	{
		CFrameWnd* pParent = (CFrameWnd*)GetOwner();
		TBarBase::OnUpdateCmdUI(pParent, FALSE);
	}; 
};
/////////////////////////////////////////////////////////////////////////////


// SECFullScreenView declaration

/////////////////////////////
// AutoDuck tag block block for SECFullScreenView 


//@doc SECFullScreenView
//@mfunc BOOL  | SECFullScreenView | GetFSMode | Returns TRUE if the Full Screen mode is currently set. Else FALSE.
//@xref<mf SECFullScreenView::SetFSMode>
//@xref<c SECFullScreenView>

//@doc SECFullScreenView
//@mfunc void  | SECFullScreenView | SetFSStyle | Sets the Full Screen View styles.
//@parm DWORD | dwStyle | Full Screen View styles.
//@xref<mf SECFullScreenView::GetFSStyle>
//@xref<c SECFullScreenView>

//@doc SECFullScreenView
//@mfunc DWORD  | SECFullScreenView | GetFSStyle | Returns the current Full Screen View styles.
//@xref<mf SECFullScreenView::SetFSStyle>
//@xref<c SECFullScreenView>


// adinsert AutoDuck insertion point for SECFullScreenView 
//@doc SECFullScreenView
//@class The SECFullScreenView class is a plug-in type component that can be added to existing MDI/SDI based application and provides
// a 'full screen view' of your client window that extends across the entire desktop. When the full screen mode is set, SECFullScreenView 
// provides a dockable toolbar that can be used to revert to the normal viewing mode. The \<ESCAPE\> keyboard accelerator can also be used
// to exit the full screen mode. Similar to Microsoft Word, the class also provide a drop-down menu when the cursor is hovered over the 
// top portion of the window in the full screen mode.
//@comm
// SECFullScreenView supports the following styles:
//
// SEC_FS_TEXTTOOLBAR - The full screen toolbar is a text-only toolbar. 
//
// SEC_FS_DROPDOWNMENU - Displays main window menu in the full screen mode.
//
// SEC_FS_TASKBARHIDE - Forcibly hides the Windows task bar when full screen mode is triggered. 
//
// SEC_FS_NOCUSTTOOLBAR - Setting this style creates the toolbar as type SECToolBar. Default is SECCustomToolBar.
//
// See the SCREENVIEW sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\SCREENVIEW directory for a demonstration of SECFullScreenView.

// Note: SECFullScreenView requires C++ RTTI to be enabled for your project. From within the VC++ IDE, you can select this option
// through the C/C++ tab in the 'Project - Settings' dialog.

//@BASE public | CWnd
class SECFullScreenView : public CWnd
{
public:

	TOOLKIT_API SECFullScreenView();
	TOOLKIT_API virtual ~SECFullScreenView();

// Attributes
protected:
	CControlBar* m_pWndFSTBar;

protected:
	BOOL m_bFSMode;
	DWORD m_dwFSStyle;

	CRect m_rcMainWnd;

	UINT m_nFSTBarResID;
	CBitmap* m_pBitmap;
	CString m_strTBarText;
	//Toolbar setstyles callback
	PFNFSSETSTYLES m_lpfnSetStyles;

	HACCEL m_hMainFrmAccel;
	HACCEL m_hFSAccelTemp;

	//FS controlbar state
	CMap<CControlBar*, CControlBar*, BOOL, BOOL> m_mapBarToState;
	CMap<CControlBar*, CControlBar*, BOOL, BOOL> m_mapBarHidden;

	SECFSMDIClientListener m_PaneLstnr;
	SECFSMainFrmListener m_MainFrmLstnr;

	SECDockState* m_pDockStateMenuBar;

// Operations
public:
	//@Access Public Members
	//@cmember
	/* Invokes the Full Screen mode.*/
	TOOLKIT_API BOOL SetFSMode(DWORD dwStyle=SEC_FS_DEFAULT);

	//@cmember
	/* Invokes the Full Screen mode with a text toolbar.*/
	TOOLKIT_API BOOL SetFSMode(DWORD dwStyle, LPCTSTR lpszTBTxt); 

	//@cmember
	/* Invokes the Full Screen mode with the specified toolbar bitmap.*/
	TOOLKIT_API BOOL SetFSMode(DWORD dwStyle, UINT nResBitmapID);

	//@cmember
	/* Exits the Full Screen mode.*/
	TOOLKIT_API void CloseFSMode();

	//@cmember
	/* Returns TRUE if full screen mode is set.*/
	inline BOOL GetFSMode() { return m_bFSMode;};

	//@cmember
	/*Call this member to set control bars that have to be displayed in the full screen mode.*/
	TOOLKIT_API BOOL SetBarStateArray(SECFSBarState* pBarArray, int nCount);

	//@cmember
	/*Specifies a callback function for changing the default toolbar styles*/
	TOOLKIT_API void SetFSToolBarStylesCB(PFNFSSETSTYLES lpfnSetStyles);

	//@cmember
	/*Returns the current full screen styles.*/
	inline DWORD GetFSStyle() { return m_dwFSStyle; };

	//@cmember
	/*Sets the full screen view styles.*/
	inline void SetFSStyle(DWORD dwStyle) { m_dwFSStyle = dwStyle; };

protected:
	TOOLKIT_API void SetTaskBarState(BOOL bVal);
	TOOLKIT_API void SetControlBarListState(BOOL bVal);
	TOOLKIT_API void ResetMainWndState();

	TOOLKIT_API void SetAccelTable();
	TOOLKIT_API void RestoreAccelTable();

	TOOLKIT_API void GetMenuBarState(CFrameWnd* pFrameWnd);
	TOOLKIT_API void SetMenuBarState(CFrameWnd* pFrameWnd);

	TOOLKIT_API BOOL TextToBmp(CBitmap* pBmp, CDC* pDC);

	//Function template used for CToolBar/SECToolBar instantiation
	template<class TBarType> TOOLKIT_API BOOL SetFSStdToolBar(TBarType* pToolBar, CFrameWnd* pMainFrmWnd, UINT* pArr, CSize szBmp);

//Overrides	
	TOOLKIT_API virtual int SetFSToolBar(CFrameWnd* pMainFrmWnd);
	TOOLKIT_API virtual void CloseDefFSToolBar();

	//@Access Overridables
	//@cmember
	/*Override for displaying any custom windows in the full screen mode.*/
	TOOLKIT_API virtual void PreFullScreenMode();

	//@cmember
	/*Override for removing custom windows that are local to the full screen mode.*/
	TOOLKIT_API virtual void PostFullScreenMode();

	// Generated message map functions
protected:
	//{{AFX_MSG(SECFullScreenView)
	TOOLKIT_API afx_msg BOOL OnTTNNeedText(UINT id, NMHDR * pTTTStruct, LRESULT * pResult );
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
//

#endif //__SECFULLSCREEN_H__

