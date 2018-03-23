///////////////////////////////////////////////////////////////////////////////
// sbarcore.h
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
//  Description:	Declarations for SECControlBar
//  Created:		May 1996
//
//	Modified:	 	March 1997 (Mark Isham)
//	Description: 	Revamped gripper support
//	
//
//	Modified:	 	June 1998 (Brad King)
//	Description: 	SECReBar added for VC6.0

#ifdef WIN32

#ifndef __SBARCORE_H__
#define __SBARCORE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SDOCKCNT_H__
#include "toolkit\sdockcnt.h"
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
// SECControlBar

// Forward Declarations
class SECControlBarInfo;
class SECControlBarManager;

// Constants
#define CX_BORDER   1
#define CY_BORDER   1

// User-defined messages
#define WM_EXTENDCONTEXTMENU		0x38ff	// replaces	(WM_USER+800) to avoid
											// conflict with help subsystem messages.
// Extended Styles
#define CBRS_EX_STDCONTEXTMENU		0x0001L  // Standard context menu items
#define CBRS_EX_STRETCH_ON_SIZE		0x0002L  // Control bar is stretched on resize
#define CBRS_EX_UNIDIRECTIONAL		0x0004L  // Bar can be sized in one direction
                                             //    at a time (i.e. toolbar)
#define CBRS_EX_DRAWBORDERS			0x0008L  // Draw a border around the bar
#define CBRS_EX_BORDERSPACE			0x0010L  // Leave border space for ease of dragging
#define CBRS_EX_ALLOW_MDI_FLOAT		0x0020L  // Control bar can be re-parented
											 //    by an MDI Child window
#define CBRS_EX_SIZE_TO_FIT			0x0040L  // Size the (single) child to fit
#define CBRS_EX_FULL_ROW			0x0080L	 // control bar will always occupy entire row

// Not yet implemented
//#define CBRS_EX_DISALLOW_FLOAT		0x0100L  // Control bar can only be docked


// You probably just want to set the CBRS_EX_COOL style in your app,
// but you can also play around with these styles to customize
// Note: As of OT 5.0, gripper requires coolboders, and close reqs gripper.
#define CBRS_EX_COOLBORDERS			0x0100L  // floating buttons, no border
#define CBRS_EX_GRIPPER				0x0200L	 // draw dragging "gripper"
#define CBRS_EX_GRIPPER_CLOSE		0x0400L	 // draw close button on gripper
#define CBRS_EX_GRIPPER_EXPAND		0x0800L	 // draw expand/contract button
#define CBRS_EX_TRANSPARENT			0x1000L	 // toolbar buttons drawn transparently
#define CBRS_EX_DISALLOW_FLOAT		0x2000L	 // Control bar can only be docked // not implemented
#define CBRS_EX_MENU_STYLE			0X4000L  // Do not become large unless a large object
											 // is dropped on bar.
											 // Add another style to simulate the looks of Office toolbars.
#define CBRS_EX_SLIM				0x8000L  // Short toolbar and single line gripper.
#define CBRS_EX_COOL				CBRS_EX_COOLBORDERS | CBRS_EX_GRIPPER | \
									CBRS_EX_GRIPPER_CLOSE | CBRS_EX_GRIPPER_EXPAND

#define CBRS_EX_FLATSTYLE			0x10000L // Emulate close to vc7 look
#define CBRS_EX_TOOLBARGRIP			0x20000L // Affects toolbars and menus with gripper enabled
											 // When this flag is applied - VC7 style gripper will be not drawn

////////////////////////////////////////////////////////////////////////
// SECGripperInfo
//
class SECGripperInfo : public CObject 
{
public:
	TOOLKIT_API SECGripperInfo();
	TOOLKIT_API virtual ~SECGripperInfo();

	// override these for your own custom gripper
	TOOLKIT_API virtual int GetWidth();
	TOOLKIT_API virtual int GetHeight();

public:
	// horizontal spacing
	int m_cxPad1;
	int m_cxWidth1;
	int m_cxPad2;
	int m_cxWidth2;
	int m_cxPad3;

	// vertical spacing
	int m_cyPad1;
	int m_cyWidth1;
	int m_cyPad2;
	int m_cyWidth2;
	int m_cyPad3;

	// padding between border and client area for all non-gripper sides
	// when gripper style enabled
	int m_nGripperOffSidePadding;

	// Tooltip text 
	CString m_strCloseTipText;
	CString m_strExpandTipText;
	CString m_strContractTipText;
};


/////////////////////////////////////////////////////////////////////////
// SECControlBar
//

/////////////////////////////
// AutoDuck tag block block for SECControlBar 

//@doc SECControlBar
//@mdata static BOOL  | SECControlBar | m_bOptimizedRedrawEnabled | This member controls the
// delayed redraw methods used to control flicker on redraw. It is sometimes necessary to 
// turn off this functionality
//@xref <mf SECControlBar::SetOptimizedRedrawEnabled>
 
//@doc SECControlBar
//@mdata CSize  | SECControlBar | m_szDockHorz | The  size of the bar when docked horizontally.

//@doc SECControlBar
//@mdata CPoint  | SECControlBar | m_ptDockHorz | The upper left point of the bar when docked horizontally. 

//@doc SECControlBar
//@mdata CSize  | SECControlBar | m_szDockVert | The size of the bar when docked vertically.

//@doc SECControlBar
//@mdata CSize  | SECControlBar | m_szFloat | The size of the bar when floating.

//@doc SECControlBar
//@mdata DWORD  | SECControlBar | m_dwMRUDockingState | The most recent docking state of the bar.

//@doc SECControlBar
//@mdata float  | SECControlBar | m_fPctWidth | The percentage of the width (or height if docked vertically)
// that the bar wishes to occupy if the the bar is undocked. 

//@doc SECControlBar
//@mdata float  | SECControlBar | m_fDockedPctWidth | The percentage of the width (or height if docked vertically)
// that the bar wishes to occupy if the the bar is docked. This percentage may not be allowed
// if all of the docked bars request percentages adding up to more than one hundred percent. 

//@doc SECControlBar
//@mdata DWORD | SECControlBar | m_dwExStyle | Extended style bit flags
//
// CBRS_EX_STDCONTEXTMENU   Control bar is given the standard context menu (i.e., Allow docking, and Show/Hide control bar menu items).<nl>
// CBRS_EX_STRETCH_ON_SIZE   When the control bar is resized, all child windows are stretched and repositioned so as to preserve the proportions of the control bar.  If you require another form of resize handling, be sure to omit this extended style from the Create call and override SECControlBar::OnSize.<nl>
// CBRS_EX_DRAWBORDERS   Draw a border around the bar.<nl>
// CBRS_EX_BORDERSPACE   Leave border space for ease of dragging.<nl>
// CBRS_EX_ALLOW_MDI_FLOAT   Control bar can be re-parented by an MDI child window.<nl>
// CBRS_EX_SIZE_TO_FIT   Size the (single) child to fit.<nl>
// CBRS_EX_UNIDIRECTIONAL   The control bar can be sized in one dimension at a time (no diagonal sizing allowed).  In addition, a change in height dictates a new width and vice versa.  A toolbar is an example of a unidirectional control bar.<nl>
// CBRS_EX_COOLBORDERS   Floating buttons, no border.<nl>
// CBRS_EX_GRIPPER   Draw the dragging gripper.<nl>
// CBRS_EX_GRIPPER_CLOSE   Draw the close button on gripper.<nl>
// CBRS_EX_GRIPPER_EXPAND   Expand/contract control bar button.<nl>
// CBRS_EX_COOL = CBRS_EX_COOLBORDERS or CBRS_EX_GRIPPER or CBRS_EX_GRIPPER_CLOSE or CBRS_EX_GRIPPER_EXPAND   Control bar will have the “cool look??a flat, painted look similar to the control bars seen in Microsoft Developer Studio.  These extended style options allow you to customize the “cool look?for your application.  By default, customizable toolbars are CBRS_EX_COOLBORDERS or CBRS_EX_GRIPPER; all other control bars are CBRS_EX_COOL.  NOTE:  As of Objective Toolkit 5.0, gripper requires coolborders, and close requires gripper.  Also, the gripper drawing code has been virtualized, so you can easily plug in your own gripper (or modify the existing gripper) with just one or two overrides.<nl>

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarBeginDock | Virtual function that can be 
// overridden to handle special requirements before a bar is docked. The default 
// implementation just calls OnBarDock().

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarEndDock | Virtual function that can be 
// overridden to handle special requirements after a bar is docked. The default 
// implementation does nothing and returns.

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarBeginFloat | Virtual function that can be 
// overridden to handle special requirements before a bar is floated. The default 
// implementation just calls OnBarFloat().

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarEndFloat | Virtual function that can be 
// overridden to handle special requirements after a bar is floated. The default 
// implementation does nothing and returns.

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarBeginMDIFloat | Virtual function that can be 
// overridden to handle special requirements before a bar is floated in a MDI window. The default 
// implementation just calls OnBarMDIFloat().

//@doc SECControlBar
//@mfunc virtual void  | SECControlBar | OnBarEndMDIFloat | Virtual function that can be 
// overridden to handle special requirements before a bar is floated. The default 
// implementation does nothing and returns.

//@doc SECControlBar
//@mfunc virtual BOOL  | SECControlBar | OnGripperClose | Gripper button callback. 
// Return FALSE to abort closing.

//@doc SECControlBar
//@mfunc virtual BOOL  | SECControlBar | OnGripperExpand | Gripper button callback. 
// Return FALSE to abort expansion.

//@doc SECControlBar
//@mdata CRect  | SECControlBar | m_rcBorderSpace | The rect containing the bar border.

//@doc SECControlBar
//@mdata SECControlBarManager*  | SECControlBar | m_pManager | A pointer to the control bar
// manager object for this bar.

//@doc SECControlBar
//@mdata SECGripperInfo  | SECControlBar | m_GripperInfo | The class which manages the gripper.

//@doc SECControlBar
//@mdata CRect  | SECControlBar | m_rcGripperCloseButton | The rect for the gripper close
// button.

//@doc SECControlBar
//@mdata CRect  | SECControlBar | m_rcGripperExpandButton | The rect for the gripper expand
// button


// adinsert AutoDuck insertion point for SECControlBar 
//@doc SECControlBar 
//@class SECControlBar replaces CControlBar as the base class for all your control 
// bars.  
//@comm
// SECControlBar adds support for sizing while docked, automatic stretching 
// when resized and a default context menu with facilities for adding and removing 
// menu items. (NOTE: All control bars formally derived from CControlBar must be 
// rederived from SECControlBar.  No CControlBars are allowed when using Objective 
// Toolkit’s docking window enhancements, as they lack the member variables 
// required to perform the sizing calculations.)
//
// See the sample VIZ in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ directory for a demonstration of 
// this class.
//@base public | CControlBar
//@xref <c SECToolBar> <c SECCustomToolBar>
class SECControlBar : public CControlBar
{
	TOOLKIT_DECLARE_SERIAL(SECControlBar)

    enum eScrollDirection { eScrollOn, eScrollOff };
	//@access Construction

public:

	//@cmember
	/* Constructs an SECControlBar object.*/
    TOOLKIT_API SECControlBar();

	//@cmember
	/* Creates a control bar and attaches it to an SECControlBar object.*/
	TOOLKIT_API virtual BOOL Create(LPCTSTR lpszClassName, 
		                LPCTSTR lpszWindowName, 
						UINT nID,
						DWORD dwStyle, 
						DWORD dwExStyle, 
						const RECT& rect, 
						CWnd* pParentWnd = NULL,
						CCreateContext* pContext = NULL);
	
	//@cmember
	/* Creates a control bar and attaches it to an SECControlBar object.*/
	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, 
		                LPCTSTR lpszWindowName, 
						DWORD dwStyle,
						DWORD dwExStyle, 
						UINT nID, 
						CCreateContext* pContext = NULL);

	//@access Public data members
	
	//@cmember
	BOOL		m_bPreVisible;
	//@cmember
	/* TRUE if optimized redraw is in effect.*/
	TOOLKIT_API static BOOL m_bOptimizedRedrawEnabled; 
	//@cmember
	/* Dimensions when docked horizontally.*/
	CSize m_szDockHorz; 
	//@cmember
	/* Location when docked horizontally.*/
	CPoint m_ptDockHorz;
	//@cmember
	/* Dimensions when docked vertically.*/
	CSize m_szDockVert; 
	//@cmember
	/* Dimensions when floating.*/
	CSize m_szFloat;    
	//@cmember
	/* Remember docking state when “Allow Docking?unchecked.*/
	DWORD m_dwMRUDockingState; 
	//@cmember
	/* The percentage of the dock bar’s width this control bar occupies.*/
	float m_fPctWidth;
	//@cmember
	/* The percentage of the dock bar’s width this control bar occupies.*/
	float m_fDockedPctWidth;			
	//@cmember
	/* Extended style bits.*/
	DWORD m_dwExStyle; 
    //@cmember

protected:
	//@access Protected data members

	//@cmember
	/* White space around bar used for dragging.*/
	CRect m_rcBorderSpace; 			
	//@cmember
	/* Control bar manager.*/
	SECControlBarManager* m_pManager;	
	//@cmember
	/* Gripper information.*/
	SECGripperInfo m_GripperInfo;
	//@cmember
	/* Gripper close button.*/
	CRect m_rcGripperCloseButton;		
	// Left button is depressed on gripper close
	BOOL  m_bClickingGripperClose;
	//@cmember
	/* Expand button*/
	CRect m_rcGripperExpandButton;	
	//@cmember
	/* left button is depressed on gripper expand */
	BOOL  m_bClickingGripperExpand;	
	//@cmember
	/* Enable expansion button. */
	BOOL  m_bGripperExpandEnabled;
	//@cmember
	/* Is the gripper expanding? */
	BOOL  m_bGripperExpandExpanding;
	//@cmember
	/* Is the gripper horizontal? */
	BOOL  m_bGripperExpandHorz;
	//@cmember
	/* Is the gripper expanded? */
	BOOL m_bIsGripperExpanded;

	// The following structure and array are used for layout. They are not documented as there
	// may be changes in this structure. Use these with caution.
	struct LayoutInfo 
	{
		HWND m_hWnd;
		CRect m_rect;
	};

	CPtrArray* m_pArrLayoutInfo;

	HWND m_hWndChildRedraw;

	// Vista Support--------------------------------
	//@cmember
	/* Handle to rebar theme. */
	HTHEME m_hReBarTheme;
	//----------------------------------------------

	//@access Operations
public:
	//@cmember
	/* Retrieves attributes associated with control bar’s inside rectangle.*/
	TOOLKIT_API virtual void	GetInsideRect(CRect& rectInside) const;	
	//@cmember
	/* Determines whether control bar has been re-parented by an MDI child window.*/
	TOOLKIT_API BOOL			IsMDIChild() const;
	// Force redraw for a child window (required for ActiveX controls)
	inline void			SetForcedChildWndRedraw(HWND hWndChildRedraw) { m_hWndChildRedraw=hWndChildRedraw; }
	//@cmember
	/* Cross-dll accessor to get m_bOptimizedRedrawEnabled state.*/
	TOOLKIT_API static BOOL		GetOptimizeRedrawEnabled();					
	//@cmember
	/* Cross-dll accessor to set m_bOptimizedRedrawEnabled state.*/
	TOOLKIT_API static void		SetOptimizedRedrawEnabled(BOOL bOptimize);
	//@cmember
	/* Access function to get the position of a bar.*/
	TOOLKIT_API BOOL			GetBarSizePos(int& nRow,int& nCol);
	//@cmember
	/* Access function to get the position of a bar with the ID.*/
	TOOLKIT_API BOOL			GetBarSizePos(int& nRow,int& nCol,int& nDockbarID);
	//@cmember
	/* Access function to get the position of a bar with the ID, height, and percentage width.*/
	TOOLKIT_API BOOL			GetBarSizePos(int& nRow,int& nCol,int& nDockbarID,float& fPctWidth,int& nHeight);
	//@cmember
	/* Enables control bar docking.*/
    TOOLKIT_API virtual void    EnableDocking(DWORD dwDockStyle);
#ifndef UNDER_CE
	//@cmember
	/* This member is called by EnableDocking() to instantiate a derivative of SECDockContext*/
   TOOLKIT_API  virtual SECDockContext* NewDockContext(void);
#endif //UNDER_CE
	inline DWORD		GetExBarStyle() const { return m_dwExStyle; };
	//@cmember
	/* Set the extended bar style.*/
	TOOLKIT_API virtual void	SetExBarStyle(DWORD dwExStyle,BOOL bAutoUpdate=FALSE);
	//@cmember
	/* Called to give control bars derived from SECControlBar a chance to modify */
	// the default context menu.
	TOOLKIT_API virtual void	ModifyBarStyleEx(DWORD dwRemove,DWORD dwAdd,BOOL bAutoUpdate=FALSE);

	//@cmember
	/* Static utility function to derive a unique controlbar id*/
	TOOLKIT_API static UINT		GetUniqueBarID(CFrameWnd* pMainWnd,UINT nBaseID=0x100);

	//@cmember
	/* Static utility function to verify all existing controlbars have unique ids.*/
	TOOLKIT_API static BOOL		VerifyUniqueBarIds(CFrameWnd* pFrameWnd);

	//@cmember
	/* Static utility function to verify a specific controlbar id is unique*/
	TOOLKIT_API static BOOL		VerifyUniqueSpecificBarID(CFrameWnd* pFrameWnd,UINT nBarID);
	
	// access Overrides
#ifndef UNDER_CE
	// Determines whether a point is in the bounding rectangle of the specified tool.  If the point is in the rectangle, it retrieves information about the tool.
#ifdef _WIN64 //RW64
	TOOLKIT_API virtual LRESULT	OnToolHitTest(CPoint point,TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int		OnToolHitTest(CPoint point,TOOLINFO* pTI) const;
#endif //_WIN64
#endif //UNDER_CE

	// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECControlBar)
    //}}AFX_VIRTUAL

	//@access Overridable
public:
	//@cmember
	// SECControlBar Destructor
    TOOLKIT_API virtual ~SECControlBar();
	//@cmember
	// Return the size of the bar when it is not dockable
	TOOLKIT_API virtual CSize	CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	//@cmember
	/* Return the size of a dockable bar*/
	TOOLKIT_API virtual CSize	CalcDynamicLayout(int nLength, DWORD dwMode);
	// Drawing
	//@cmember
	// Virtual function that handles painting.
	TOOLKIT_API virtual void	DoPaint(CDC* pDC);
	//@cmember
	// Virtual function that handles drawing of borders.
	TOOLKIT_API virtual void	DrawBorders(CDC* pDC, CRect& rect);
	//@cmember
	// Virtual functionat that handles non client paints.
	TOOLKIT_API void			EraseNonClient();
	//@cmember
	// Get information about the bar.
	TOOLKIT_API virtual void	GetBarInfo(SECControlBarInfo* pInfo);
	//@cmember
	// Set information about the bar.
	TOOLKIT_API void			SetBarInfo(SECControlBarInfo* pInfo, CFrameWnd* pFrameWnd);
	//@cmember
	// UI Command Updates.
	TOOLKIT_API virtual void	OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//@cmember
	// Calculate the inside rects.
	TOOLKIT_API virtual void	CalcInsideRect(CRect& rect, BOOL bHorz, BOOL bVert = FALSE) const;
	//@cmember
	// Get SECControlBarManager.
	inline SECControlBarManager* GetManager() const;
	//@cmember
	// Set SECControlBarManager.
	inline void		SetManager(SECControlBarManager*);
	
	// Docking
	//@cmember
	/* Virtual function that can be overridden to handle special requirements before a bar is docked.*/
	inline virtual void	OnBarBeginDock(){ OnBarDock(); }
	// Virtual function that can be overridden to handle special requirements when a bar is docked.
	TOOLKIT_API virtual void	OnBarDock();
	//@cmember
	/* Virtual function that can be overridden to handle special requirements after a bar is docked.*/
	inline virtual void	OnBarEndDock(){ }
	//@cmember
	/* Virtual function that can be overridden to handle special requirements before a bar is floated.*/
	inline virtual void	OnBarBeginFloat(){ OnBarFloat(); }
	// Virtual function that can be overridden to handle special requirements when a bar is floated.
	TOOLKIT_API virtual void	OnBarFloat();
	//@cmember
	/* Virtual function that can be overridden to handle special requirements after a bar is floated.*/
	inline virtual void	OnBarEndFloat(){ }
	//@cmember
	/* Virtual function that can be overridden to handle special requirements before a bar is floated as a MDI child window.*/
	inline virtual void	OnBarBeginMDIFloat(){ OnBarMDIFloat(); }
	// Virtual function that can be overridden to handle special requirements when a bar is floated as a MDI child window.
	TOOLKIT_API virtual void	OnBarMDIFloat();
	//@cmember
	/* Virtual function that can be overridden to handle special requirements after a bar is floated as a MDI child window.*/
	inline virtual void	OnBarEndMDIFloat(){ }
	//@cmember
	// Virtual function that gets extended bar information.
	TOOLKIT_API virtual void	GetBarInfoEx(SECControlBarInfo* pInfo);
	//@cmember
	// Virtual function that sets extended bar information.
	TOOLKIT_API virtual void	SetBarInfoEx(SECControlBarInfo* pInfo, CFrameWnd* pFrameWnd);

    //-------------------------------------------//
    // Auto Hide Functions                       //
    //-------------------------------------------//
	//@cmember
    // Enable or Disable Auto Hiding
    inline  void SetAutoHide(BOOL _bAutoHide = TRUE) { m_bAutoHide = _bAutoHide; InitAutoHide(); }
	//@cmember
    // Are we Auto Hide?
    inline BOOL IsAutoHide() { return m_bAutoHide; }
	//@cmember
    // Are we Pinned? Only occurs for Auto Hide Windows
    inline BOOL IsPinned() { return m_bAutoHidePinned; }
	//@cmember
    // Are we aligned on the left dockbar?
    TOOLKIT_API BOOL IsLeftAligned();
	//@cmember
    // Are we aligned on the right dockbar?
    TOOLKIT_API BOOL IsRightAligned();
	//@cmember
    // Are we aligned on the top dockbar?
	//@cmember
    TOOLKIT_API BOOL IsTopAligned();
	//@cmember
    // Are we aligned on the bottom dockbar?
	//@cmember
    TOOLKIT_API BOOL IsBottomAligned();
	//@cmember
    // Are we vertically aligned?
    TOOLKIT_API BOOL IsVertAligned();
	//@cmember
    // Are we horizontally aligned?
    TOOLKIT_API BOOL IsHorzAligned();
	//@cmember
    // Are we hiding left?
    TOOLKIT_API BOOL IsHideLeft();
	//@cmember
    // Are we hiding right?
    TOOLKIT_API BOOL IsHideRight();
	//@cmember
    // Are we hiding Top?
    TOOLKIT_API BOOL IsHideTop();
	//@cmember
    // Are we hiding Bottom?
    TOOLKIT_API BOOL IsHideBottom();
	//@cmember
    // Active Window
    TOOLKIT_API void OnActiveWindow();
	//@cmember
    // Initialize Auto Hiding
    TOOLKIT_API BOOL InitAutoHide();
	//@cmember
    // Hide
    TOOLKIT_API void ScrollOff();
	//@cmember
    // Display
    TOOLKIT_API void ScrollOn();
	//@cmember
    // Display Actions
    TOOLKIT_API void ScrollEffect( eScrollDirection scrollDir );
	//@cmember
    // Timer
    TOOLKIT_API void OnTimer(UINT nIDEvent);
	//@cmember
	// Auto Hide Button
	TOOLKIT_API virtual void DrawGripperAutoHideButton(CDC* pDC, CRect& rect,BOOL bHorz);
	//@cmember
    // Set Sleep Value in milliseconds
    TOOLKIT_API void SetAutoHideDelay(DWORD _dwDelay);
	//@cmember
    // Set AutoHide scrolling time in milliseconds (0 for no scrolling)
    TOOLKIT_API void SetAutoHideTime( DWORD _dwTime )   { m_dwScrollTime = _dwTime; }
	//@cmember
    // Last Aligned Docking
    inline UINT GetLastAlignedDocking() { return m_nLastAlignedDocking; }
	//@cmember
	// Set Last Aligned Docking
    inline void SetLastAlignedDocking( UINT iAlignment )   { m_nLastAlignedDocking = iAlignment; }

	//@cmember
	// Toggle whether or not an AutoHide window is visible or not. Returns the visibility.
	// This behavior will mimic Visual Studio. Pinned windows will not lose their visibility.
	TOOLKIT_API virtual BOOL ToggleVisibility();

protected:
    //-------------------------------------------//
    // Auto Hide Data                            //
    //-------------------------------------------//
	//@cmember
	// Main Frame
    CWnd*   m_pMainFrm;
	//@cmember
    // State for allowing Auto Hide.
    BOOL m_bAutoHide;
	//@cmember
    // Have we called InitAutoHide?
    BOOL m_bAutoHideInitialized;
	//@cmember
    // State of Auto Hide
    BOOL m_bAutoHidePinned;
	//@cmember
    // Old Active Window
    BOOL m_bOldActive;
	//@cmember
    // Active
    BOOL m_bActive;
	//@cmember
    // Last aligned side.
    UINT m_nLastAlignedDocking;
	//@cmember
    // Auto Hide Button Rect
    CRect m_rcAutoHideButton;
	//@cmember
    // Scroll on/off time (in milliseconds) for Animated Windows
    DWORD m_dwScrollTime;


protected:

	//@access Implementation
	//@cmember
	TOOLKIT_API void InitLayoutInfo();
	//@cmember
	TOOLKIT_API void DeleteLayoutInfo();
	//@cmember
	// Called to give control bars derived from SECControlBar a chance to modify the default context menu.
	TOOLKIT_API virtual void OnExtendContextMenu(CMenu* pMenu);
	// Gripper button callbacks. Return FALSE to abort operation
	//@cmember
	/* Gripper button callback. Return FALSE to abort closing.*/
	inline virtual BOOL OnGripperClose()  { return TRUE; }
	//@cmember
	/* Gripper button callbacks. Return FALSE to abort expansion.*/
	inline virtual BOOL OnGripperExpand() { return TRUE; }

	//
	// gripper drawing functions
	//
	// override *both* of these if you want to draw your own custom gripper
	//@cmember
	TOOLKIT_API virtual void AdjustInsideRectForGripper(CRect& rect,BOOL bHorz);
	//@cmember
	TOOLKIT_API virtual void DrawGripper(CDC* pDC, CRect& rect);
	// utility functions to draw the gripper "close" button
	//@cmember
	TOOLKIT_API virtual void DrawGripperCloseButton(CDC* pDC, CRect& rect,BOOL bHorz);
	//@cmember
	TOOLKIT_API virtual void DrawGripperCloseButtonDepressed(CDC* pDC);
	//@cmember
	TOOLKIT_API virtual void DrawGripperCloseButtonRaised(CDC* pDC);
	//@cmember
	TOOLKIT_API virtual void DrawGripperCloseButtonNormal(CDC* pDC);

	// utility functions to draw the gripper "expand" button
	TOOLKIT_API virtual void DrawGripperExpandButton(CDC* pDC, CRect& rect,BOOL bHorz);
	//@cmember
	TOOLKIT_API virtual void DrawGripperExpandButtonDepressed(CDC* pDC);
	//@cmember
	TOOLKIT_API virtual void DrawGripperExpandButtonRaised(CDC* pDC);
	//@cmember
	TOOLKIT_API virtual void DrawGripperExpandButtonNormal(CDC* pDC);
	//@cmember
	TOOLKIT_API virtual void SetGripperExpandButtonState(BOOL bHorz);

// Command Handlers
protected:
	//@cmember
	// OnHide Message Handler.
	TOOLKIT_API afx_msg void OnHide();
	//@cmember
	// OnToggleAllowDocking Message Handler.
	TOOLKIT_API afx_msg void OnToggleAllowDocking();
	//@cmember
	// OnFloatAsMDIChild Message Handler.
	TOOLKIT_API afx_msg void OnFloatAsMDIChild();
	
// Generated message map functions
public: // public functions so other helper classes can call these handlers directly
    //{{AFX_MSG(SECControlBar)
	//@cmember
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	//@cmember
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint pt );
	//@cmember
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint pt );
	//@cmember
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
	//@cmember
	TOOLKIT_API afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//@cmember
	TOOLKIT_API afx_msg void OnDestroy();
	//@cmember
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//@cmember
    TOOLKIT_API afx_msg LRESULT OnPrintClient(WPARAM, LPARAM);
	//@cmember
	TOOLKIT_API afx_msg void OnNcPaint(); 
	//@cmember
	TOOLKIT_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
#if(_MFC_VER >= 0x0800)
	//@cmember
    TOOLKIT_API afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	//@cmember
    TOOLKIT_API afx_msg UINT OnNcHitTest(CPoint point);
#endif
	//@cmember
    TOOLKIT_API afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//@cmember
	TOOLKIT_API afx_msg void OnKillFocus(CWnd* pNewWnd);

	// Support-----------------------------------
	//@cmember
	// Theme Change Handler.
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API LRESULT OnThemeChanged();
	#endif
	//-------------------------------------------
	//}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// inline functions

inline SECControlBarManager* SECControlBar::GetManager() const
{
	return m_pManager;
}

inline void SECControlBar::SetManager(SECControlBarManager* pManager)
{
	m_pManager = pManager;
}

#if _MFC_VER >= 0x0600
/////////////////////////////////////////////////////////////////////////////
// SECReBar

//@doc SECReBar 
//@class this is a very thin class that enables SECControlBars to be contained in
// a Rebar common control
//@base public | CReBar
class SECReBar : public CReBar
{
	TOOLKIT_DECLARE_DYNAMIC(SECReBar)

// Construction
public:
	TOOLKIT_API SECReBar();
	TOOLKIT_API virtual ~SECReBar();
	//@cmember
	/* Calculates the layout of contained SECControlBars*/
	TOOLKIT_API virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	TOOLKIT_API afx_msg void OnNcPaint(); 

	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		LRESULT OnThemeChanged();
	#endif
	HTHEME m_hReBarTheme;
};
#endif	//_MFC_VER >= 0x0600

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SBARCORE_H__

#else // WIN32

#define SECControlBar CControlBar

#endif // WIN32

