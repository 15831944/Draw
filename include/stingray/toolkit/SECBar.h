///////////////////////////////////////////////////////////////////////////////
// SECBar.h : Declaration of SECBar
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
// Description:  Declaration of SECBar
//

//@doc SECBar
//@mdata BOOL | SECBar | m_bAutoDelete | Set to TRUE if you want the bar to delete itself

//adinsert

#ifdef WIN32

#ifndef __SECBAR_H__
#define __SECBAR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECICON_H__
#include "toolkit\secicon.h"
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

// Constants

// Macros

// Types

// Forward Declarations
class SECShortcutBar;
/////////////////////////////////////////////////////////////////////////////
// SECBar

//@doc SECBar 
//@class A SECBar object represents a single "bar" window that a user can select. 
// It is displayed inside the SECShortcutBar window. Every time a bar that is to 
// contain an embedded CWnd object is added to the shortcut bar, a SECBar is created.
// SECBar maintains its own size and the size of its associated CWnd.  SECBar is also 
// smart enough to know how big it needs to be based on the font it is supposed to use.
//@BASE public | CObject
class SECBar : public CObject
{
	friend class SECShortcutBar;

	TOOLKIT_DECLARE_DYNCREATE(SECBar)
	
	//---------------------------------------------------------------------//
	// 						   Public Enumerations						   //
	//---------------------------------------------------------------------//
public:	
	//@access Public Enumerations
	//@cmember,menum
	/* Button Style and States*/
	enum ButtonStyleAndState
	{
		LMouseBtnDown		= 0x01,	//@@emem State: Left Mouse Button Down
		RMouseBtnDown		= 0x02,	//@@emem State: Right Mouse Button Down
		Focus				= 0x04,	//@@emem State: Button has Focus
		NoSetFocusOnChild	= 0x08	//@@emem Style: If set using SetStyle the child control will never get keyboard focus.
	};

	//@cmember,menum
	/* Label Alignment*/
	enum LabelAlignment
	{
		laLeft,					//@@emem Align Text Left
		laCenter,				//@@emem Align Text Center
		laRight					//@@emem Align Text Right
	};

	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Initialization/Destruction
	
	//@access Construction/Destruction
	//@cmember
	/* constructs the SECBar object*/
	TOOLKIT_API SECBar();
	//@cmember
	/* constructs the SECBar object from another SECBar object*/
	TOOLKIT_API SECBar( const SECBar& rBar );
	//@cmember
	/* destructs an SECBar object*/
	TOOLKIT_API virtual ~SECBar();

	//@access Operators
	//@cmember
	/* Assignment Operator for SECBar objects*/
	TOOLKIT_API const SECBar& operator=( const SECBar& rBar );

	//@access Attributes
	//@cmember
	/* returns the rect of the button.*/
	TOOLKIT_API CRect GetBtnRect() const;
	//@cmember
	/* returns the rect of the pane*/
	TOOLKIT_API CRect GetPaneRect() const;
	TOOLKIT_API int GetPrefSize() const;

	//@cmember
	/* returns the associated CWnd pointer*/
	TOOLKIT_API CWnd* GetWnd() const;
	//@cmember
	/* sets the associated HWND from the CWnd pointer*/
	TOOLKIT_API virtual void SetWnd( const CWnd* const pWnd );
	//@cmember
	/* caches the CWnd pointer*/
	TOOLKIT_API virtual void SetWndPermanent( CWnd* pWnd );

	//@cmember
	/* returns the current SECBar label*/
	TOOLKIT_API CString GetLabel() const;
	//@cmember
	/* sets the bar label*/
	TOOLKIT_API void SetLabel( const CString& sLabel );

	//@cmember
	/* returns the bar alignment style for the text*/
	TOOLKIT_API LabelAlignment GetLabelAlignment() const;
	//@cmember
	/* Sets the bar alignment style for the text*/
	TOOLKIT_API void SetLabelAlignment( LabelAlignment la );

	//@cmember
	/* returns the CFont object being used by the bar*/
	TOOLKIT_API CFont* GetFont() const;
	//@cmember
	/* sets the CFont object being used by the bar*/
	TOOLKIT_API void SetFont( const CFont* const pFont );

	//@cmember
	/* returns the color the bar is using to show focus*/
	TOOLKIT_API COLORREF GetFocusColor() const;
	//@cmember
	/* sets the color the bar is using to show focus*/
	TOOLKIT_API void SetFocusColor( COLORREF color );

	//@cmember
	/* returns the color the bar is using for text*/
	TOOLKIT_API COLORREF GetTextColor() const;
	//@cmember
	/* sets the color the bar is using for text*/
	TOOLKIT_API void SetTextColor( COLORREF color );

	//@cmember
	/* returns the background color for the bar*/
	TOOLKIT_API COLORREF GetBkColor() const;
	//@cmember
	/* sets the background color for the bar*/
	TOOLKIT_API void SetBkColor( COLORREF color );

	//@cmember
	/* returns the icon associated with the bar*/
	TOOLKIT_API HICON GetIcon() const;
	//@cmember
	/* sets the icon associated with the bar*/
	TOOLKIT_API void SetIcon( HICON hIcon );
	//@cmember
	/* sets the icon associated with the bar*/
	TOOLKIT_API void SetIcon( LPCTSTR lpszIconRes, int iHeight = 16, int iWidth = 16 );
	//@cmember
	/* sets the icon associated with the bar*/
	TOOLKIT_API void SetIcon( UINT nIconRes, int iHeight = 16, int iWidth = 16 );

	//@cmember
	/* returns the HMENU associated with the bar*/
	TOOLKIT_API HMENU GetMenu() const;
	//@cmember
	/* sets the menu associated with the bar*/
	TOOLKIT_API void SetMenu( HMENU hMenu );
	//@cmember
	/* sets the menu associated with the bar*/
	TOOLKIT_API void SetMenu( CMenu* pMenu, int iSubMenu = -1 );

	//@cmember
	/* returns the opaque pointer associated with the bar*/
	TOOLKIT_API void* GetExtraData() const;
	//@cmember
	/* sets the opaque pointer associated with the bar*/
	TOOLKIT_API void SetExtraData( const void* const pData );

	//@cmember
	/* Query whether the bar is enabled*/
	TOOLKIT_API BOOL IsEnabled() const;
	//@cmember
	/* Set the bar's enabled/disabled state*/
	TOOLKIT_API void SetEnabled( BOOL bSel = TRUE );

	//@cmember
	/* Query the bar's style*/
	TOOLKIT_API long GetStyle() const;
	//@cmember
	/* Set the bar's style*/
	TOOLKIT_API void SetStyle( long lStyle );

	//@cmember
	/* Query the auto delete flag*/
	TOOLKIT_API BOOL WillAutoDelete() const;
	//@cmember
	/* Set the auto delete flag*/
	TOOLKIT_API void SetAutoDelete( BOOL bAuto = TRUE );
	//@cmember
	/* The auto delete flag*/
	BOOL m_bAutoDelete;		

	//@access Public Operations
	//@cmember
	/* Query if the mouse hit the bar*/
	TOOLKIT_API BOOL MouseHit( const CPoint& ptMouseDown ) const;
	//@cmember
	/* Delete the SECBar object if able to */
	TOOLKIT_API void Delete();

	//---------------------------------------------------------------------//
	// 							 Public Overridables					   //
	//---------------------------------------------------------------------//
public:
	//@access Public Overridable
	//@cmember
	/* Draws the SECBar object*/
	TOOLKIT_API virtual void Draw( CDC& dc, BOOL bVert );
	//@cmember
	/* Initializes the GDI Resources used by the bar*/
	TOOLKIT_API virtual void InitializeGDIResources();
	//@cmember
	/* Uninitializes the GDI Resources used by the bar*/
	TOOLKIT_API virtual void UninitializeGDIResources();
	//@cmember
	/* Computes button rect*/
	TOOLKIT_API virtual void ComputeRect( CDC& dc, BOOL bVert );

	TOOLKIT_API virtual void DestroyWindow();
	TOOLKIT_API virtual void DeleteWindow();
	//---------------------------------------------------------------------//
	// 							 Protected Overridables					   //
	//---------------------------------------------------------------------//
protected:
	//@access Protected Overridable
	//@cmember
	/* Draws the button part of the bar*/
	TOOLKIT_API virtual void DrawButton( CDC& dc, BOOL bPressed );
	//@cmember
	/* Draws the icon part of the bar*/
	TOOLKIT_API virtual void DrawIcon(   CDC& dc, BOOL bPressed, BOOL bVert );
	//@cmember
	/* Draws the text part of the bar*/
	TOOLKIT_API virtual void DrawText(   CDC& dc, BOOL bPressed, BOOL bVert );

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	// Drawing member variables...
	CRect    m_rcBtn;			//Button Rectangle
	CRect    m_rcWnd;			//Client Area of associated CWnd
	int      BarSize;
	int		 PaneSize;
	int	     m_prefSize;
	CFont*   m_pFont;			//font of the bar
	CString  m_sLabel;			//text for the bar
	void*    m_pExtra;			//extra data for the bar
	HWND     m_hWnd;			//window associated with bar
	HMENU	 m_hMenu;			//used for context-menu
	COLORREF m_clrText;			//text color of the bar
	COLORREF m_clrDisabledText;
	COLORREF m_clrFocus;
	COLORREF m_clrBk;          // Background color for the bar
	CBrush   m_brBk;           // Brush for background color
	CBrush   m_brFocusBrush;
	SECIcon	 m_icon;			//Icon associated with the bar
	long     m_lStyle;			//the button style
	BOOL	 m_bSelected;
	LabelAlignment m_alignment;	//the text alignment of the label
	CWnd*	 m_pWndPermanent;	// permanent CWnd, created internally by the control
	HTHEME   m_hButtonTheme;
	
	// Implementation Member Functions

protected:
	TOOLKIT_API void InitBar();
	TOOLKIT_API void SetBtnRect( const CRect& rect );
	TOOLKIT_API void SetPaneRect( const CRect& rect );


	//---------------------------------------------------------------------//
	// 						  Base Class Overrides						   //
	//---------------------------------------------------------------------//
public:
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump( CDumpContext& dc ) const;
#endif

	//---------------------------------------------------------------------//
	// 						Private Implementation						   //
	//---------------------------------------------------------------------//
private:
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

#endif // __SECBAR_H__
#endif // WIN32

