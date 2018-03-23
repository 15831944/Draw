///////////////////////////////////////////////////////////////////////////////
// olbar.h : Declaration of SECShortcutBar
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
// Author:       Justin Rudd
// Description:  Declaration of SECShortcutBar
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifdef WIN32

#ifndef __SECOUTLOOKBAR_H__
#define __SECOUTLOOKBAR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifndef __SECITER_H__
#include "toolkit\seciter.h"
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

// Constants
#define SEC_DEFAULT_ID					(0xffffffff)
#define SEC_IDW_BARCLIENT_FIRST			(0xEB00)
#define SEC_IDW_BARCLIENT_LAST			(0xEBFF)
#define SEC_WS_DEFAULT_BARCLIENT		(WS_CHILD|WS_VISIBLE)
#define SEC_DEFAULT_ANIMATION_SPEED		(7)
#define SEC_DEFAULT_ANIMATION_STEP 		(8)

//SECShortcutBar Styles
#define SEC_OBS_VERT					(0x0001)
#define SEC_OBS_HORZ					(0x0002)
#define SEC_OBS_BUTTONFEEDBACK			(0x0004)
#define SEC_OBS_CONTEXTMENU				(0x0008)
#define SEC_OBS_ANIMATESCROLL			(0x0010)
#define SEC_OBS_BUTTONFOCUS				(0x0020)

//composite alignment mask
#define SEC_OBS_ALIGN					(SEC_OBS_VERT				|\
										 SEC_OBS_HORZ)
//composite styles mask
#define SEC_OBS_STYLES					(SEC_OBS_ALIGN				|\
										 SEC_OBS_BUTTONFEEDBACK		|\
                                         SEC_OBS_CONTEXTMENU		|\
										 SEC_OBS_ANIMATESCROLL		|\
										 SEC_OBS_BUTTONFOCUS)


#define SEC_DEFAULT_OUTLOOKBAR			(WS_VISIBLE|WS_CHILD|SEC_OBS_VERT)

#ifdef _DEBUG

	#define ASSERT_BarExists(index) \
		if( BarExists(index) == FALSE ) \
		{\
			TRACE(_T("ERROR - Trying to access bar( %d ) which does not exist\n"),index); \
			ASSERT(FALSE); \
		}

#else

	#define ASSERT_BarExists(index)

#endif

// Forward Declarations
class SECBar;
class SECListBar;

// Types
typedef CArray<SECBar*,SECBar*> SECBarArray;

/////////////////////////////////////////////////////////////////////////////
// SECShortcutBar window

//@doc SECShortcutBar 
//@class SECShortcutBar offers the look and feel of the Microsoft Outlook Bar. 
//@comm 
// The shortcut bar acts as a container class and can hold any embedded CWnd-derived objects. 
// It can also be embedded anywhere.
//
// When the shortcut bar is usedas an Outlook Bar type interface it maintains a list of bars. 
// Each bar is the button that can be seen. 
//
// See the DEMO sample in the \SAMPLES\TOOLKIT\STANDARD\TABS\LISTBAR directory for a demonstration 
// of the SECShortcutBar class.
//@xref<c SECBar> <c SECListBar>
//@BASE public | CWnd
class SECShortcutBar : public CWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECShortcutBar)

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	//Construction/Destruction
	//@Access Public Members
	//@Access Constructors/Destructors
	//@cmember
	/* Constructs the SECShortcutBar object*/
	TOOLKIT_API SECShortcutBar();
	//@cmember
	/* Destructs the SECShortcutBar object*/
	TOOLKIT_API virtual ~SECShortcutBar();

	//@Access Initializations
	//@cmember
	/* Creates the SECShortcutBar window*/
	TOOLKIT_API virtual BOOL Create( CWnd* pParentWnd, DWORD dwStyle = SEC_DEFAULT_OUTLOOKBAR, UINT nID = AFX_IDW_PANE_FIRST );

	// Accessor functions...Get/Set
	//@Access Accessor Fuctions
	//@cmember
	/* Set the CRuntimeClass used for SECBar's*/
	TOOLKIT_API void SetBarClass( CRuntimeClass* const pBarClass );
	//@cmember
	/* Get the CRuntimeClass used for SECBar's*/
	TOOLKIT_API CRuntimeClass* GetBarClass() const;

	//@cmember
	/* Set the CRuntimeClass used for SECListBar's*/
	TOOLKIT_API void SetListBarClass( CRuntimeClass* const pBarClass );
	//@cmember
	/* Get the CRuntimeClass used for SECBar's*/
	TOOLKIT_API CRuntimeClass* GetListBarClass() const;

	//@cmember
	/* Set the CRuntimeClass used for SECShortcutListCtrl's*/
	TOOLKIT_API void SetListCtrlClass( CRuntimeClass* const pBarClass );
	//@cmember
	/* Get the CRuntimeClass used for SECShortcutListCtrl's*/
	TOOLKIT_API CRuntimeClass* GetListCtrlClass() const;

	TOOLKIT_API void SetMinPaneSize( const int& minSize );
	TOOLKIT_API int GetMinPaneSize() const;

	//@cmember
	/* Set the font point size to use for SECBar*/
	TOOLKIT_API void SetFontPointSize( const int& iFontPointSize );
	//@cmember
	/* Get the font point size to use for SECBar*/
	TOOLKIT_API int GetFontPointSize() const;

	//@cmember
	/* Set the font name to use for SECBar*/
	TOOLKIT_API void SetFontName( const CString& sFontName );
	//@cmember
	/* Get the font name to use for SECBar*/
	TOOLKIT_API const CString& GetFontName() const;

	//@cmember
	/* Set the Animation speed to use (in ms)*/
	TOOLKIT_API void SetAnimationSpeed( const int& iAnimationSpeed );
	//@cmember
	/* Get the Animation speed to use (in ms)*/
	TOOLKIT_API int GetAnimationSpeed() const;

	//@cmember
	/* Set the Animation Step (# of frames in animation)*/
	TOOLKIT_API void SetAnimationStep( const int& iAnimationStep );
	//@cmember
	/* Get the Animation Step (# of frames in animation)*/
	TOOLKIT_API int GetAnimationStep() const;

	//@cmember
	/* Set menu for SECBar to use*/
	TOOLKIT_API void SetBarMenu( HMENU hMenu, int iIndex = -1 );
	//@cmember
	/* Set menu for SECBar to use*/
	TOOLKIT_API void SetBarMenu( CMenu* pSubMenu, int iIndex = -1, int iLevel = -1 );

	//@cmember
	/* Set font for SECBar to use*/
	TOOLKIT_API void SetBarFont( CFont* pFont, int iIndex = -1 );
	//@cmember
	/* Set font for SECBar to use*/
	TOOLKIT_API void SetBarFont( HFONT hFont, int iIndex = -1 );

	//@cmember
	/* Set color to use as filler in animated scrolls*/
	TOOLKIT_API void SetBackFillColor( COLORREF color );
	//@cmember
	/* Set brush to use as filler in animated scrolls*/
	TOOLKIT_API void SetBackFillColor( CBrush* pBackFillBrush );

	//@cmember
	/* Set color of the focus rect for SECBar's*/
	TOOLKIT_API void SetFocusRectColor( COLORREF color, int iIndex = -1 );
	//@cmember
	/* Get color of the focus rect for SECBar's*/
	TOOLKIT_API COLORREF GetFocusRectColor( int iIndex = -1 ) const;

	//@cmember
	/* Set color of the bar text for SECBar's*/
	TOOLKIT_API void SetTextColor( COLORREF color, int iIndex = -1 );
	//@cmember
	/* Get color of the bar text for SECBar's*/
	TOOLKIT_API COLORREF GetTextColor(int iIndex = -1) const;

	//@cmember
	/* Set background color of the bar*/
	TOOLKIT_API void SetBkColor( COLORREF color, int iIndex = -1 );
	//@cmember
	/* Get background color of the bar*/
	TOOLKIT_API COLORREF GetBkColor(int iIndex = -1) const;

	//@cmember
	/* Set background color of the bar*/
	TOOLKIT_API void SetPaneBkColor( COLORREF color, int iIndex = -1 );
	//@cmember
	/* Get background color of the bar*/
	TOOLKIT_API COLORREF GetPaneBkColor(int iIndex = -1) const;

	//Operations...
	//@Access Queries
	//@cmember
	/* Queries the number of bars in SECShortcutBar*/
    TOOLKIT_API int GetBarCount() const;

	//@cmember
	/* Returns the CWnd associated with the Bar*/
	TOOLKIT_API CWnd* GetBarWnd( int iIndex ) const;

	//@cmember
	/* Sets the alignment style*/
	TOOLKIT_API void SetAlignStyle( DWORD dwAlign );
	//@cmember
	/* Gets the alignment style*/
	TOOLKIT_API DWORD GetAlignStyle() const;

	//@cmember
	/* Modifies the bar style*/
	TOOLKIT_API void ModifyBarStyle( DWORD dwRemove, DWORD dwAdd, BOOL bRecalcRedraw = TRUE );
	//@cmember
	/* Queries the bar style*/
	TOOLKIT_API DWORD GetBarStyle() const;

	//@cmember
	/* Get SECBar associated with active bar*/
	TOOLKIT_API SECBar& GetActiveBar() const;
	//@cmember
	/* Queries wether or not we have an active bar*/
	TOOLKIT_API BOOL HasActiveBar() const;
	//@cmember
	/* Returns the index of the active bar*/
	TOOLKIT_API int GetActiveIndex() const;

	//@cmember
	/* Queries for the style SEC_OBS_VERT*/
	TOOLKIT_API BOOL IsVertAlign() const;
	//@cmember
	/* Queries for the style SEC_OBS_HORZ*/
	TOOLKIT_API BOOL IsHorzAlign() const;
	//@cmember
	/* Queries for a particular style*/
	TOOLKIT_API BOOL IsStyleSet( DWORD dwStyle ) const;

	//@cmember
	/* Creates an iterator to use for traversal*/
	TOOLKIT_API SECIterator<SECBar*>* CreateBarIterator() const;

	//@cmember
	/* Returns a SECBar at specified index*/
	TOOLKIT_API SECBar&	GetBar( int iIndex ) const;
	//@cmember
	/* Returns a SECBar* at specified index*/
	TOOLKIT_API SECBar* GetBarPtr( int iIndex ) const;
	//@cmember
	/* Returns index of the bar at specified point.*/
	TOOLKIT_API int HitBar( const CPoint& pt );

	//@cmember
	/* Specifies whether to use flat style or not.*/
	TOOLKIT_API void SetFlatStyleMode( BOOL bEnabled = TRUE );

	//---------------------------------------------------------------------//
	// 						   Public Overrideables						   //
	//---------------------------------------------------------------------//
public:
	//@Access Public Overrideables
	//@cmember
	/* Adds a new bar at the end*/
    TOOLKIT_API virtual SECBar* AddBar(CWnd* pWnd,LPCTSTR lpszLabel,BOOL bRecalc=FALSE);
	//@cmember
	/* Adds a new bar at the end*/
	TOOLKIT_API virtual SECBar* AddBar(CRuntimeClass* pViewClass,LPCTSTR lpszLabel,
						               CCreateContext* pContext = NULL,BOOL bRecalc = FALSE, 
						               UINT nID = SEC_DEFAULT_ID);
	//@cmember
	/* Adds a new SECListBar at the end*/
	TOOLKIT_API virtual SECListBar* AddBar( LPCTSTR lpszLabel, BOOL bRecalc=FALSE);

	//@cmember
	/* Inserts a new bar*/
	TOOLKIT_API virtual SECBar* InsertBar( int iIndex, CWnd* pWnd, LPCTSTR lpszLabel, BOOL bRecalc=FALSE);
	//@cmember
	/* Inserts a new bar*/
	TOOLKIT_API virtual SECBar* InsertBar( int iIndex, CRuntimeClass* pViewClass, LPCTSTR lpszLabel, 
		                       CCreateContext* pContext = NULL, BOOL bRecalc = FALSE, UINT uID = SEC_DEFAULT_ID );
	//@cmember
	/* Inserts a new SECListBar*/
	TOOLKIT_API virtual SECListBar* InsertBar( int iIndex, LPCTSTR lpszLabel, BOOL bRecalc=FALSE);

	//@cmember
	/* Removes a bar at specified index*/
	TOOLKIT_API virtual void RemoveBar( int iIndex );

	//@cmember
	/* Renames a bar at specified index*/
	TOOLKIT_API virtual void RenameBar( int iIndex, LPCTSTR lpszLabel );

	//@cmember
	/* Activates bar at specified index*/
    TOOLKIT_API virtual void ActivateBar(int nIndex);
	
	//legacy API.  Will be removed at the end of the beta cycle
	inline void SelectPane( int i ){ ActivateBar(i); }

	TOOLKIT_API virtual BOOL RecalcLayout();

	//@cmember
	/* Disables bar at specified index*/
	TOOLKIT_API virtual void DisableBar( int iIndex );
	//@cmember
	/* Enables bar at specified index*/
	TOOLKIT_API virtual void EnableBar( int iIndex );

	//---------------------------------------------------------------------//
	// 						   Protected Overrideables					   //
	//---------------------------------------------------------------------//
protected:
	//@Access Protected Overrideables
	//@cmember
	/* Called when styles changing*/
	TOOLKIT_API virtual void OnStyleChange( DWORD dwRemovedStyles, DWORD dwAddedStyles );
	//@cmember
	/* Called when trying to change bar*/
	TOOLKIT_API virtual BOOL OnChangeBar( int iIndex );
	//@cmember
	/* Called when trying to remove a bar*/
	TOOLKIT_API virtual BOOL OnRemoveBar( int iIndex );
	//@cmember
	/* Called when trying to disable a bar*/
	TOOLKIT_API virtual BOOL OnDisableBar( int iIndex );
	//@cmember
	/* Called when trying to enable a bar*/
	TOOLKIT_API virtual BOOL OnEnableBar( int iIndex );
	//@cmember
	/* Called after creating CWnd for bar object*/
	TOOLKIT_API virtual BOOL OnCreatePaneWnd( CWnd* pwnd );
	//@cmember
	/* Called after creating SECBar object*/
	TOOLKIT_API virtual BOOL OnCreateBar( SECBar* pbar );
		
	//@cmember
	/* Called to create GDI Objects*/
	TOOLKIT_API virtual void ConstructGDIObjects();
	//@cmember
	/* Called to destroy GDI Objects*/
	TOOLKIT_API virtual void DestructGDIObjects();

	TOOLKIT_API virtual void CalcFixedLayout( int iNewSize, int iLastSize );

	TOOLKIT_API virtual void SetupRects( BOOL bVert, CRect& rc );
	TOOLKIT_API virtual void SetPanePositions();

	TOOLKIT_API virtual void InvalidateBar( int iBar );
	TOOLKIT_API virtual void InvalidateBar( SECBar& bar );
	TOOLKIT_API virtual void InvalidateBar( SECBar* pBar );

	//@cmember
	/* Called to create SECBar object*/
	TOOLKIT_API virtual SECBar* CreateNewBar() const;
	//@cmember
	/* Called to create SECListBar objects*/
	TOOLKIT_API virtual SECListBar* CreateNewListBar() const;

	TOOLKIT_API virtual SECBar* DoAddBar( CWnd* pWnd, LPCTSTR lpszLabel, BOOL bRecalc );
	TOOLKIT_API virtual SECBar* DoInsertBar( int iIndex, CWnd* pWnd, LPCTSTR lpszLabel, BOOL bRecalc );
	TOOLKIT_API virtual void DoPaint( CDC& dc );
	
	TOOLKIT_API virtual void NoAnimateScroll( int iIndex );
	TOOLKIT_API virtual void AnimateScroll( int iOldIndex, int iNewIndex );

	TOOLKIT_API virtual void FindPrevActiveBar( int& riIndex );
	TOOLKIT_API virtual void FindNextActiveBar( int& riIndex );

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:
	// Implementation Member Variables
	int				m_iHitIndex;
	int				m_iActiveIndex;
	int				m_iMinPaneSize;
	int				m_iLastTotalBtnSize;
	int				m_iLastTotalPaneSize;
	int				m_iFontPointSize;
	int				m_iAnimationSpeed;
	int				m_iAnimationStep;
	BOOL			m_bActiveIndex;
	BOOL			m_bBtnDown;
	DWORD			m_dwAlign;
	DWORD			m_dwStyle;
	CRuntimeClass*	m_pBarClass;
	CRuntimeClass*  m_pListBarClass;
	CRuntimeClass*  m_pListCtrlClass;
	CSize			m_lastWndSize;
	CString			m_sFontName;
	CBrush*			m_pbrBackBrush;
	SECBarArray		m_bars;
	CFont			m_defaultVertFont;
	CFont			m_defaultHorzFont;
	COLORREF    m_clrDefaultText;
	COLORREF    m_clrDefaultBk;
	COLORREF	m_clrDefaultPaneBk;

	BOOL		m_bFlatStyleMode;
	
	// Implementation Member Functions
	TOOLKIT_API CWnd* CreateWnd( CRuntimeClass* pWndClass, CCreateContext* pContext = NULL, UINT nID = SEC_DEFAULT_ID );
    TOOLKIT_API BOOL BarExists(int nBar) const;
	TOOLKIT_API void CleanUpBackFillBrush();

	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//

public:
	TOOLKIT_API virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);


	//---------------------------------------------------------------------//
	// 						Message Map Declarations					   //
	//---------------------------------------------------------------------//
protected:
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	TOOLKIT_DECLARE_MESSAGE_MAP()

		
	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:
	static CString s_strClassName;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECOUTLOOKBAR_H__

#endif // WIN32

