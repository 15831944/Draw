///////////////////////////////////////////////////////////////////////////////
// tbarcust.h
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
//  Description:	Declarations for SECCustomToolBar
//  Created:		August 1996
//
//	Modified:		March 1997 (Mark Isham)
//	Description:	Numerous "cool look" enhancements
//	

#ifdef WIN32

#ifndef __TBARCUST_H__
#define __TBARCUST_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
#endif

#ifndef __TBMPMGR_H__
#include "toolkit\TBmpMgr.h"
#endif

#ifndef __SDOCKSTA_H__
#include "toolkit\sdocksta.h"
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

// Forward declarations
struct SECBtnMapEntry;
class  SECToolBarManager;
class  SECStdBtn;
class  SECTBMenuBtn;
struct SECBtnDrawData;

// Define the height and width of a standard toolbar button
#define SEC_TOOLBAR_BTN_WIDTH       23
#define SEC_TOOLBAR_BTN_HEIGHT      22

// Height of a separator between two toolbar rows.
#define SEPARATOR_HEIGHT  ((m_nSepWidth*2)/3)

// Additional buttons styles
#define SEC_TBBS_FOCUS     (MAKELONG(0, 0x0100))	// Btn has customize focus
#define SEC_TBBS_RAISED    (MAKELONG(0, 0x0200))	// Btn is raised
#define SEC_TBBS_NODISABLE (MAKELONG(0, 0x1000))	// Btn not disabled if no
													// command handler
#define SEC_TBBS_VCENTER   (MAKELONG(0, 0x2000))	// Btn is centered vert.
													// in row

// Styles for SECTwoPartBtn		
#define SEC_TBBS_PRESSED2  (MAKELONG(0, 0x0400))	// 2nd part is pressed
#define SEC_TBBS_TRACKING2 (MAKELONG(0, 0x0800))	// We're tracking 2nd part

#define SEC_TBBS_DROPDOWN  (MAKELONG(0x0008, 0))	// Btn is dropdown same as
													// TBSTYLE_DROPDOWN

// ID of first user defined toolbar. IDs between AFX_IDW_TOOLBAR and
// SEC_IDW_FIRST_USER_TOOLBAR are received for default/system toolbars
#define SEC_IDW_FIRST_USER_TOOLBAR		(AFX_IDW_TOOLBAR + 0x20)
#define SEC_IDW_MENUBAR					(AFX_IDW_TOOLBAR + 0xff)

// Helper macro - used for calculating no. of elements in an array.
#define NUMELEMENTS(array) (sizeof(array)/sizeof(array[0]))

// Define the custom toolbar type ID
// This value can be written to the registry (via SaveBarState)
// and a later retore (via LoadBarState) can use this value to
// determine which control bar type to reinstantiate.
#define CBT_SECCUSTOMTOOLBAR	14946  // Control Bar Type ID
#define CBT_SECCUSTOMMENUBAR	14947  // Menu Bar Type ID

// Toolbar specific extended styles
#define SEC_CTB_EX_INTERNAL_CUSTOMIZE				0x0001

///////////////////////////////////////////////////////////////////////////////
// SECCustomToolBar
//
/////////////////////////////
// AutoDuck tag block block for SECCustomToolBar 

//@doc SECCustomToolBar
//@mfunc inline int  | SECCustomToolBar | GetBtnCount | The number of buttons currently on the toolbar.

//@doc SECCustomToolBar
//@mfunc inline BOOL  | SECCustomToolBar | InConfigMode | TRUE if the toolbar is in customize mode.

//@doc SECCustomToolBar
//@mfunc inline BOOL  | SECCustomToolBar | InAltDragMode | TRUE when performing a drag of the button with the ALT key down (while not in customize mode).

// adinsert AutoDuck insertion point for SECCustomToolBar 
//@doc SECCustomToolBar 
//@class Use SECCustomToolBar to create customizable toolbars from scratch to enhance your application.  
//@comm
// Each toolbar can be assigned a set of buttons in a style geared toward a particular task.  For example, one set 
// of buttons could be for common File operations; another set might represent a user-defined task.  From 
// Customize dialogs, the user can add or delete buttons and set their style from default or custom categories.  
// Through the toolbar dialog, the user can choose between large or small buttons, tooltips enabled or disabled, 
// and conventional appearance or the new cool look. Once the button has been selected, it can be dragged to 
// any toolbar.  It is also possible to drag and drop buttons between toolbars.
//
// Although SECCustomToolBar can be used as a replacement for CToolBar, it works best when used in conjunction 
// with SECToolBarManager.
//
// To correctly use customizable toolbars, the base class of the frame window in which the toolbars are created 
// must be derived from SECFrameWnd or an SECFrameWnd derivative.
//
// While dragging a toolbar, the Ctrl key can be pressed to prevent docking.  Thus, the toolbar can float anywhere 
// on the desktop; however, if docked, it acquires a gripper that makes it easy to move.  The visibility of a 
// toolbar can be toggled on and off to indicate active or inactive states.
//
// Because this class inherits from SECControlBar, it includes support for sizing while docked, automatic 
// stretching when resized, and a default context menu with facilities for adding and removing menu items.
//
// (NOTE:  No CControlBars are allowed when using Objective Toolkit’s docking window enhancements, as they lack 
// the member variables required to perform the sizing calculations.)
//
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration of this class.
//@xref <c SECControlBar> <c SECToolBarManager> <c SECToolBarSheet> <c SECToolBarCmdPage>
//@xref <c SECToolBarsDlg> <c SECDialogBar> <c SECToolBarsPage> <c SECToolBar> <c SECStdBtn>
//@base public | SECControlBar
class SECCustomToolBar : public SECControlBar
{
// Construction
public:
	
	TOOLKIT_API SECCustomToolBar();
	
	//@cmember
	/* Creates the child window for the customizable toolbar and attaches it to an SECCustomToolBar object.*/
	TOOLKIT_API virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, UINT nID,
		                DWORD dwStyle, DWORD dwExStyle, const RECT& rect, 
						CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, 
		                            DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBRS_TOP, 
									UINT nID = AFX_IDW_TOOLBAR, LPCTSTR lpszTitle = NULL);

	//@cmember
	/* Creates a customizable toolbar with extended style attributes.*/
	TOOLKIT_API virtual BOOL CreateEx(DWORD dwExStyle, CWnd* pParentWnd, DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBRS_TOP, UINT nID = AFX_IDW_TOOLBAR, LPCTSTR lpszTitle = NULL);

	TOOLKIT_DECLARE_DYNCREATE(SECCustomToolBar)

// Attributes
public:
	enum BarNotifyCode				// ToolBar Notification codes
	{
		BarShow,					// The toolbar is being shown
		BarHide,					// The toolbar is being hidden
		BarCreate,					// The toolbar has been created
		BarDelete,					// The toolbar is being deleted
		BarDesChange				// The config focus button has changed
	};

	// Structure used during wrapping. Details each wrap position
	struct Wrapped
	{
		int  m_nAfter;				// The index that we wrap after
		BOOL m_bAtSep;				// TRUE if we are wrapping on a separator
		int  m_nSize;				// Horizontal size of this row
		int  m_nRowHeight;			// Vertical size of this row
	};

	TOOLKIT_API virtual void GetInsideRect(CRect& rectInside) const;

// Operations
public:
	// Load/Save the toolbar configuration
	// Loads the toolbar configuration.
	TOOLKIT_API virtual void GetBarInfoEx(SECControlBarInfo* pInfo);
	//@cmember
	/* Saves the toolbar configuration*/
	TOOLKIT_API virtual void SetBarInfoEx(SECControlBarInfo* pInfo, CFrameWnd* pFrameWnd);

	// Set/Get the style of a button
	//@cmember
	/* Sets the style of a button.*/
	TOOLKIT_API void SetButtonStyle(int nIndex, UINT nStyle);
	//@cmember
	/* Gets the style of a button.*/
	TOOLKIT_API UINT GetButtonStyle(int nIndex) const;

	// Hides/Shows the given button
	TOOLKIT_API void HideButton(int nIndex, BOOL bHide);

	// Remove/Add a button from/to the toolbar
	//@cmember
	/* Removes a button from the toolbar*/
	TOOLKIT_API virtual BOOL RemoveButton(int nIndex, BOOL bNoUpdate = FALSE);
	//@cmember
	/* Adds a button to the toolbar.*/
	TOOLKIT_API virtual void AddButton(int nIndex, int nID, BOOL bSeparator = FALSE,BOOL bNoUpdate = FALSE);
	// Appends the given buttons to the toolbar
	TOOLKIT_API BOOL AddButtons(UINT nNumButtons, LPTBBUTTON lpButtons);

	// Returns the no. of buttons on the toolbar
	//@cmember
	/* Returns number of buttons on toolbar.*/
	inline int GetBtnCount() const { return (int)m_btns.GetSize(); }

	// Returns the SECStdBtn object at the given index (NULL if error)
	// Returns the SECStdBtn object at the given index (NULL if error)
	TOOLKIT_API SECStdBtn* GetBtnObject(int nIndex) const;

	// Returns TRUE if this toolbar is in customize mode.
	//@cmember
	/* Returns TRUE if toolbar is in customize mode.*/
	inline BOOL InConfigMode() const { return m_bConfig; }

	// Returns TRUE when we are performing a drag with ALT key down (note that
	// we are not in customize mode).
	//@cmember
	/* Returns TRUE when dragging with ALT key down (when not in customize mode).*/
	inline BOOL InAltDragMode() const { return m_bAltDrag; }

	// Converts the command ID to a button index.
	//@cmember
	/* Returns the command ID for a given button index.*/
	TOOLKIT_API int CommandToIndex(UINT nID) const;

	// Returns the button index of the given button.
	// Returns the button index of the given button.
	TOOLKIT_API int BtnToIndex(SECStdBtn* pBtn) const;

	// Returns the command ID for the given button index.
	//@cmember
	/* Returns the command ID for a given button index.*/
	TOOLKIT_API UINT GetItemID(int nIndex) const;

	// Returns the index of the currently active button
	//@cmember
	/* Returns the index of the currently active button.*/
	TOOLKIT_API int GetCurBtn() const;

	// Converts a command ID to an index in the button bitmap.
	// Note that from 5.2 onwards, the prototype of this function
	// has changed to provide the bitmap handle as well. This is to
	// facilitate the support of multiple bitmaps.
	//@cmember
	/* Converts a command ID to an index in the bitmap button.*/
	TOOLKIT_API virtual int IDToBmpIndex(UINT nID, HBITMAP* lphBmp);

	// Loads the toolbar bitmap resource
	//@cmember
	/* Loads a toolbar bitmap resource.*/
	TOOLKIT_API BOOL LoadToolBar(LPCTSTR lpszResourceName);
	TOOLKIT_API BOOL LoadToolBar(UINT nIDResource);
	//@cmember
	/* tLoads a toolbar bitmap resource.*/
	TOOLKIT_API BOOL LoadBitmap(UINT nIDResource, const UINT* lpIDArray, int nIDCount);
	TOOLKIT_API BOOL LoadBitmap(LPCTSTR lpszResourceName, const UINT* lpIDArray,int nIDCount);
	// Note that from VC++ 5.2 forward, the prototype of this function has changed.
	// Sets the toolbar’s bitmap information.
	TOOLKIT_API virtual void SetToolBarInfo(int nImgWidth, int nImgHeight);

	// Sets the buttons on the current toolbar
	//@cmember
	/* Sets the buttons on the current toolbar.*/
	TOOLKIT_API virtual BOOL SetButtons(const UINT* lpIDArray, int nIDCount);

	// Returns the rect. of the given button index.
	//@cmember
	/* Returns the rect of the given button index.*/
	TOOLKIT_API void GetItemRect(int nIndex, LPRECT lpRect) const;

	// Passes notification through to all buttons of nID
	//@cmember
	/* Passes notification through to all buttons of nID.*/
	TOOLKIT_API void InformBtns(UINT nID, UINT nCode, void* pData, BOOL bPass = FALSE);

	// Set/Get the current button map.
	TOOLKIT_API void SetButtonMap(const SECBtnMapEntry* pMap);
	TOOLKIT_API const SECBtnMapEntry* GetButtonMap() const;

	// Synchronize latest undockable toolbar info
	TOOLKIT_API virtual void SizeUndockableTB();

	inline SECBmpMgr* GetBmpMgr() const { return m_pBmpMgr; }
	TOOLKIT_API void SetBmpMgr(SECBmpMgr* pBmpMgr);

// Overrideables
public:
	TOOLKIT_API virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	TOOLKIT_API virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
	TOOLKIT_API virtual void  OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	TOOLKIT_API virtual void  OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);
#ifdef _WIN64 //RW64
	TOOLKIT_API virtual LRESULT OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int   OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#endif //_WIN64

	// Shows the menu associated with the given SECMenuBtn
	TOOLKIT_API virtual void  ShowMenu(SECTBMenuBtn* pBtn, SEC_DWORD nIDMenu, int nIndexMenu);

	// Forces the menu button at the given index to display it's menu.
	TOOLKIT_API virtual void  InvokeMenu(int nIndex);

	// Menu header management
	TOOLKIT_API virtual void  InvokeMenuHeader(CPoint& pt);
	TOOLKIT_API virtual void  InvokeMenuHeader(int nIndex);
	TOOLKIT_API virtual void  CloseMenuHeader();
	TOOLKIT_API virtual BOOL IsMenuHeaderInvoked();

	// Returns the first or last menu item on the toolbar
	TOOLKIT_API virtual int  FindFirstMenu() const;
	TOOLKIT_API virtual int  FindLastMenu() const;

	// Returns the first non-system menu item on the toolbar
	TOOLKIT_API virtual int FindFirstStandardMenu() const;

	// Returns the next menu item left or right of the current position.
	TOOLKIT_API virtual int  FindNextMenu(BOOL bRight) const;

	// Functions returning the font to be used for drawing standard and menu buttons
	TOOLKIT_API virtual HFONT GetBtnFont() const;
	TOOLKIT_API virtual HFONT GetMenuFont() const;

protected:
	TOOLKIT_API virtual void  DoPaint(CDC* pDC);
	TOOLKIT_API virtual void  DelayShow(BOOL bShow);

	// Balance the wrapping of the toolbar.
	//@cmember
	/* Balances the wrapping of the toolbar.*/
	TOOLKIT_API virtual void  BalanceWrap(int nRow, Wrapped* pWrap);

	// Returns TRUE if the default drag mode is add.
	//@cmember
	/* Returns TRUE if the default drag mode is add.*/
	TOOLKIT_API virtual BOOL  GetDragMode() const;

	// Returns TRUE if this toolbar accepts dropped buttons.
	//@cmember
	/* Returns TRUE if the toolbar accepts dropped buttons.*/
	TOOLKIT_API virtual BOOL  AcceptDrop() const;

	// override	for custom sizing of toolbar
	TOOLKIT_API virtual void  AdjustInsideRectForGripper(CRect& rect,BOOL bHorz);

// Implementation
public:
	TOOLKIT_API virtual ~SECCustomToolBar();

	// override of SECControlBar::DrawBorders
	TOOLKIT_API virtual void DrawBorders(CDC* pDC, CRect& rect);

	// Removes and destroys all buttons
	TOOLKIT_API virtual void RemoveBtns();

	// Puts the toolbar into config mode
	TOOLKIT_API void EnableConfigMode(BOOL bEnable);

	// Returns TRUE if "Cool" look is enabled.
	inline virtual BOOL CoolLookEnabled() const { return (m_dwExStyle & CBRS_EX_COOLBORDERS) ? TRUE : FALSE; }

	// Returns TRUE if buttons are to be drawn transparently
	TOOLKIT_API BOOL IsTransparent() const;

	// Functions returning button dimensions
	inline virtual int GetImgWidth() const { return m_pBmpMgr->GetImgWidth(); }
	inline virtual int GetImgHeight() const { return m_pBmpMgr->GetImgHeight(); }
	inline virtual int GetStdBtnWidth() const { return (GetImgWidth() + 7); }
	inline virtual int GetStdBtnHeight() const { return (GetImgHeight() + 7); }
	inline virtual int GetSepWidth() const { return ((GetImgWidth() + 8) / 3); }
	inline virtual int GetSepHeight() const { return (GetImgHeight() + 7); }

	// Modifies m_bLocked
	TOOLKIT_API void LockToolBar(BOOL bLock);

	// Returns TRUE when toolbar is vertically docked.
	inline BOOL IsVerticallyDocked() const { return m_bVertical; }

	// Returns the cached drawing data
	TOOLKIT_API SECBtnDrawData& GetDrawData();

	// Function to provide "Cool" style button with raised look
	TOOLKIT_API void RaiseButton(BOOL bUpdate = TRUE);

	TOOLKIT_API virtual BOOL MenuMouseEvent(MSG* pMsg);
	TOOLKIT_API virtual void MenuComplete();

	inline void SetCTBExStyle(DWORD dwExStyle) { m_dwCTBExStyle=dwExStyle; }
	inline DWORD GetCTBExStyle() { return m_dwCTBExStyle; }

	// Performs a drag of a toolbar button
	TOOLKIT_API static BOOL DragButton(SECToolBarManager* pMgr, SECStdBtn* pBtn, int nIndex, 
						   CPoint point, SECCustomToolBar* pBar, CWnd* pDragWnd, 
						   BOOL bAdd);

protected:
#if _MFC_VER >= 0x0600
	// adjusts the rebar band to the calculated size of the toolbar
	TOOLKIT_API virtual void FitBandToSize(SECReBar* pReBar, CSize& barSize);
#endif

	// Returns TRUE if the given row can be wrapped to reduce toolbar width.
	TOOLKIT_API BOOL CanWrapRow(int nRowToWrap, int nMaxSize, int nRows, Wrapped* pWrap);

	// Perform a wrap of the toolbar to the specified horz. size.
	TOOLKIT_API virtual int PerformWrap(int nLength, Wrapped* pWrap);

	// Calculates the size of the current wrap.
	TOOLKIT_API CSize CalcSize(int nRows, Wrapped* pWrap);

	// Wraps a toolbar to the given horz/vert constraint
	TOOLKIT_API virtual CSize SizeToolBar(int nLength, BOOL bVert);

	// Vertically center a row of buttons
	TOOLKIT_API void VCenterBtns(int nStart, int nEnd, int nRowHeight);

	// Re-calcs the layout of the toolbar.
	TOOLKIT_API virtual CSize CalcLayout(int nLength, DWORD dwMode);

	// Passes a notification onto the manager.
	TOOLKIT_API void NotifyManager(BarNotifyCode nCode);

	// Invalidates the specified button
	TOOLKIT_API virtual void InvalidateButton(int nIndex);

	// Returns the index of the button under the specified point
	TOOLKIT_API virtual int ItemFromPoint(CPoint point, CRect& rect) const;

	// Executes the command handler for the specified button index
	TOOLKIT_API virtual void UpdateButton(int nIndex);

	// Sets the mode of the toolbar (TRUE=vert. docked)
	TOOLKIT_API void SetMode(BOOL bVertDock);

	// Sets the config focus to the specified button
	TOOLKIT_API void SetConfigFocus(int nBtn, BOOL bRedraw = FALSE);
	TOOLKIT_API void SetConfigFocus(SECStdBtn* pBtn, BOOL bRedraw = FALSE);

	// Removes the config focus from the specified button
	TOOLKIT_API void RemoveConfigFocus(BOOL bRedraw = FALSE);

	// Starts a drag of the specified button
	TOOLKIT_API virtual BOOL DragButton(int nIndex, CPoint point);

	// Handles a button drop
	TOOLKIT_API virtual BOOL DropButton(CRect& dropRect, SECStdBtn* pDragBtn, BOOL bAdd,BOOL bNoUpdate = FALSE); 

	// Finds the row over which the button has been dropped
	TOOLKIT_API void FindRow(CRect& clientRect, CRect& dropRect, int& nRowStart, 
				 int& nRowEnd);

	// Returns reference to pointer to toolbar with current cofnig focus
	TOOLKIT_API SECCustomToolBar* GetConfigFocus() const;
	TOOLKIT_API void SetConfigFocus(SECCustomToolBar* pFocus);

	// Creates a new toolbar
	TOOLKIT_API static void NewToolBar(CPoint pt, const SECStdBtn& btn, SECToolBarManager* pMgr,
						   BOOL bAltDrag);

	// Handles the case of a slight drag of the button (dropped over sep.
	// next to button).
	TOOLKIT_API BOOL SmallDrag(CRect& dropRect, int nRowStart, int nRowEnd, BOOL bAdd, BOOL bNoUpdate = FALSE);

	// Creates a new button
	TOOLKIT_API virtual SECStdBtn* CreateButton(UINT nID, SECCustomToolBar* pToolBar = NULL);

	// Creates a new separator
	TOOLKIT_API virtual SECStdBtn* CreateSeparator(SECCustomToolBar* pToolBar = NULL);

	// Returns the toolbar under the specified point
	TOOLKIT_API static SECCustomToolBar* ToolBarFromPoint(int x, int y);

	public:
	inline virtual void SetBtnTransparentColor(COLORREF clrBtnTransparent, BOOL bUseCustomBtnTransparentColor = TRUE) 
	{ 
		m_clrBtnTransprancy = clrBtnTransparent; 
		m_bUseBtnTransparancy = bUseCustomBtnTransparentColor;
	}
	inline virtual COLORREF GetBtnTransparentColor() 
	{
		return m_bUseBtnTransparancy;
	}
protected:
	// Implementation, data members.
	SECBmpMgr*                   m_pBmpMgr;			// Manages our bitmaps
	int							 m_nSepWidth;		// Width of separator
	int							 m_nDown;			// Button pressed/config
	int							 m_nRaised;			// Index of raised button
													// "Cool" look only.
	int							 m_nMenuBtn;		// Current menu button
	BOOL						 m_bConfig;			// TRUE if in customize mode
	static BOOL					 m_bAltDrag;		// TRUE if we are performing
													// a drag with Alt key down
	SECBtnDrawData*				 m_pDrawData;		// Cached info for drawing
													// btns.
	BOOL						 m_bVertical;		// TRUE if vert. docked
	BOOL 						 m_bFloatSizeUnknown;
	BOOL						 m_bHorzDockSizeUnknown;
	BOOL						 m_bVertDockSizeUnknown;
	CSize						 m_szTbarDockHorz;	// custom toolbar copy of m_szDockHorz
	CSize						 m_szTbarDockVert;	// custom toolbar copy of m_szDockVert
	CSize						 m_szTbarFloat;		// custom toolbar copy of m_szFloat
	DWORD						 m_dwCTBExStyle;	// custom toolbar specific extended styles
	HFONT						 m_hFont;			// Font used for drawing buttons
	TOOLKIT_API static BOOL		 m_bLocked;			// TRUE while dispatching WM_COMMAND
	const SECBtnMapEntry*		 m_pBtnMap;			// Maps ID's to button types.
	SECBtnMapEntry*				 m_pAuxBtnMap;		// Additional button map.

	BOOL						 m_bMenuHeaderInvoked;	// TRUE when a menu header is being tracked

	BOOL						 m_bIsMenuBar; //TRUE when is used as menubar
	HTHEME						 m_hRebarTheme;
	HTHEME						 m_hMenuTheme;
	COLORREF					 m_clrBtnTransprancy;
	BOOL						 m_bUseBtnTransparancy;

public:
	int                          m_nMaxBtnWidth;	// Max. width of button
	int							 m_nMaxBtnHeight;	// Max. height of button
	// Array of all my buttons
	//
	// Note that this nested class would normally be declared using the template 
	// CTypedPtrArray, but some Unix compilers don't support templates.
	//
	class SECBtnArray : public CPtrArray
	{
	public:
		// Accessing elements
		inline SECStdBtn* GetAt(int nIndex) const { return (SECStdBtn*)CPtrArray::GetAt(nIndex); }
		inline SECStdBtn*& ElementAt(int nIndex) { return (SECStdBtn*&)CPtrArray::ElementAt(nIndex); }
		inline void SetAt(int nIndex, SECStdBtn* ptr) { CPtrArray::SetAt(nIndex, ptr); }

		// Potentially growing the array
		inline void SetAtGrow(int nIndex, SECStdBtn* newElement) { CPtrArray::SetAtGrow(nIndex, newElement); }
		inline SEC_INT Add(SECStdBtn* newElement) { return CPtrArray::Add(newElement); }
		inline SEC_INT Append(const SECBtnArray& src) { return CPtrArray::Append(src); }
		inline void Copy(const SECBtnArray& src) { CPtrArray::Copy(src); }

		// Operations that move elements around
		inline void InsertAt(int nIndex, SECStdBtn* newElement, int nCount = 1) { CPtrArray::InsertAt(nIndex, newElement, nCount); }
		inline void InsertAt(int nStartIndex, SECBtnArray* pNewArray) { CPtrArray::InsertAt(nStartIndex, pNewArray); }

		// overloaded operator helpers
		inline SECStdBtn* operator[](int nIndex) const { return (SECStdBtn*)CPtrArray::operator[](nIndex); }
		inline SECStdBtn*& operator[](int nIndex) { return (SECStdBtn*&)CPtrArray::operator[](nIndex); }
	};

	SECBtnArray	m_btns;							// Array of button objects

protected:

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
	TOOLKIT_API afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	TOOLKIT_API afx_msg void OnSysColorChange();
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnCancelMode();
	TOOLKIT_API afx_msg int  OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg LRESULT OnNoDelayHide(WPARAM nID, LPARAM lParam);
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	TOOLKIT_API afx_msg LRESULT OnSizeParent(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnAddButtons(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnDeleteButton(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg void OnNcPaint();
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};

/////////////////////////////////////////////////////////////////////////////
// SECCustomToolBarInfoEx

struct SECBtnInfo			
{
	UINT  m_nID;			// ID of button
	BYTE  m_nSizeExtraInfo;	// Size of additional data
	BYTE* m_pExtraInfo;		// Ptr to additional data

	inline SECBtnInfo() : m_nSizeExtraInfo(0), m_pExtraInfo(NULL) {}
	TOOLKIT_API virtual ~SECBtnInfo();
};


class SECBtnInfoArray : public CPtrArray
{
public:
	inline ~SECBtnInfoArray() { RemoveAll(); }

	// Accessing elements
	inline SECBtnInfo* GetAt(int nIndex) const { return (SECBtnInfo*)CPtrArray::GetAt(nIndex); }
	inline SECBtnInfo*& ElementAt(int nIndex) { return (SECBtnInfo*&)CPtrArray::ElementAt(nIndex); }
	inline void SetAt(int nIndex, SECBtnInfo* ptr) { CPtrArray::SetAt(nIndex, ptr); }

	// Potentially growing the array
	inline void SetAtGrow(int nIndex, SECBtnInfo* newElement) { CPtrArray::SetAtGrow(nIndex, newElement); }
	inline SEC_INT Add(SECBtnInfo* newElement) { return CPtrArray::Add(newElement); }
	inline SEC_INT Append(const SECBtnInfoArray& src) { return CPtrArray::Append(src); }
	inline void Copy(const SECBtnInfoArray& src) { CPtrArray::Copy(src); }

	// Operations that move elements around
	inline void InsertAt(int nIndex, SECBtnInfo* newElement, int nCount = 1) { CPtrArray::InsertAt(nIndex, newElement, nCount); }
	inline void InsertAt(int nStartIndex, SECBtnInfoArray* pNewArray) { CPtrArray::InsertAt(nStartIndex, pNewArray); }
	inline void RemoveAll() { for(int i=0; i<GetSize(); i++) delete GetAt(i); CPtrArray::RemoveAll(); }

	// overloaded operator helpers
	inline SECBtnInfo* operator[](int nIndex) const { return (SECBtnInfo*)CPtrArray::operator[](nIndex); }
	inline SECBtnInfo*& operator[](int nIndex) { return (SECBtnInfo*&)CPtrArray::operator[](nIndex); }
};


class SECCustomToolBarInfoEx : public SECControlBarInfoEx
{
	TOOLKIT_DECLARE_DYNCREATE(SECCustomToolBarInfoEx)

// Constructors
public:
	TOOLKIT_API SECCustomToolBarInfoEx();

// Attributes
public:

	CString m_strBarName;		// Title of toolbar

	// Array of button information
	SECBtnInfoArray m_btnInfo;

// Operations
public:
	TOOLKIT_API virtual void Serialize(CArchive& ar, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(LPCTSTR lpszSection, SECDockState* pDockState);
	TOOLKIT_API virtual BOOL LoadState(SECPersistentTreeNode* pBarNode);
	TOOLKIT_API virtual BOOL SaveState(LPCTSTR lpszSection);
	TOOLKIT_API virtual BOOL SaveState(SECPTNFactory& nodeFactory,SECPersistentTreeNode* pBarNode);

// Implementation
public:
	TOOLKIT_API virtual ~SECCustomToolBarInfoEx();

	TOOLKIT_API void MakeBtnInfoFromBinary(const BYTE* pData, UINT nSize, SECBtnInfoArray& info);
	TOOLKIT_API BOOL MakeBinaryBtnInfo(BYTE*& pData, UINT& nSize, const SECBtnInfoArray& info);
};


/////////////////////////////////////////////////////////////////////////////
//  Definition of structure passed with WM_NOTIFY for SECCustomToolBar
//
typedef struct tagSECNMTOOLBARA {
	NMHDR		 hdr;
	int			 iItem;
	TBBUTTON	 tbButton;
	int			 cchText;
	LPSTR		 pszText;
	int			 iIndex;			// Index of button on toolbar
	SEC_DWORD    dwMisc1;			// Miscellaneous fields (depends on code)
	SEC_DWORD    dwMisc2;
	BOOL		 bFlag;
} SECNMTOOLBARA, FAR* LPSECNMTOOLBARA;


typedef struct tagSECNMTOOLBARW
{
	NMHDR		 hdr;
	int			 iItem;
	TBBUTTON	 tbButton;
	int			 cchText;
	LPWSTR		 pszText;
	int			 iIndex;			// Index of button on toolbar
	SEC_DWORD    dwMisc1;			// Miscellaneous fields (depends on code)
	SEC_DWORD    dwMisc2;
	BOOL		 bFlag;
} SECNMTOOLBARW, FAR* LPSECNMTOOLBARW;

#ifdef UNICODE
#define SECNMTOOLBAR               SECNMTOOLBARW
#define LPSECNMTOOLBAR             LPSECNMTOOLBARW
#else
#define SECNMTOOLBAR               SECNMTOOLBARA
#define LPSECNMTOOLBAR             LPSECNMTOOLBARA
#endif

/////////////////////////////////////////////////////////////////////////////
// Notification codes
//

// Range of SECCustomToolBar notifications
#define SEC_TBN_FIRST		(0U-2120U)
#define SEC_TBN_LAST		(0u-2140U)

// If TBN_DROPDOWN (standard notification as of commctrl 4.70) not defined
// then define it now.
#ifndef TBN_DROPDOWN
#define TBN_DROPDOWN		(TBN_FIRST - 10)
#endif

#define SEC_TBN_SHOWMENU	(SEC_TBN_FIRST - 0)		// Show the given menu
#define SEC_TBN_CANCELMENU	(SEC_TBN_FIRST - 1)		// Cancel the current menu
#define SEC_TBN_ACTIVATEMENUHEADER	(SEC_TBN_FIRST - 2)		// Menu header has been activated
#define SEC_TBN_CLOSEMENUHEADER	   (SEC_TBN_FIRST - 3)		// Menu header has been closed

/////////////////////////////////////////////////////////////////////////////
// inline functions

#ifndef __TBARMGR_H__
#include "toolkit\tbarmgr.h"
#endif

inline SECCustomToolBar* SECCustomToolBar::GetConfigFocus() const
{
	if(m_pManager) {
		ASSERT_KINDOF(SECToolBarManager, m_pManager);
		return ((SECToolBarManager*)m_pManager)->GetConfigFocus();
	}

	return NULL;
}

inline void SECCustomToolBar::SetConfigFocus(SECCustomToolBar* pFocus)
{
	if(m_pManager) {
		ASSERT_KINDOF(SECToolBarManager, m_pManager);
		((SECToolBarManager*)m_pManager)->SetConfigFocus(pFocus);
	}
}

inline BOOL SECCustomToolBar::IsTransparent() const
{
	return (BOOL) ((m_dwExStyle & CBRS_EX_COOLBORDERS) &&
				   (m_dwExStyle & CBRS_EX_TRANSPARENT));
}


// Loads a toolbar resource into the given bitmap and variables
TOOLKIT_API BOOL SECLoadToolBarResource(LPCTSTR lpszResourceName, CBitmap& bmp, 
							UINT*& pBmpItems, UINT& nBmpItems,
							int& nImgWidth, int& nImgHeight,
							UINT* pBtnCount = NULL, 
							UINT** ppBtnArray = NULL);


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBARCUST_H__

#endif // WIN32

