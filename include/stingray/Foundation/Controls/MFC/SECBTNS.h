///////////////////////////////////////////////////////////////////////////////
// SECBTNS.h : Declaration of the SECOwnerDrawButton, SECWellButton,
//             SECBitmapButton and SECMenuButton custom controls.
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
//		Author:		Don			04/02/96
//


#ifndef __SFL_SECBTNS_H__
#define __SFL_SECBTNS_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

class SECPopupColorWell;

// Use the following flags when initializing a SECOwnerDrawButton object.
const int SEC_BTN_DEFAULT_ONFOCUS       = 0x0001;	// Will become the default button whenever it has the focus.

/////////////////////////////////////////////////////////////////////////////
// SECOwnerDrawButton

/////////////////////////////
// AutoDuck tag block block for SECOwnerDrawButton 

//@doc SECOwnerDrawButton
//@mdata int | SECOwnerDrawButton | m_iFlags | Flags defining behavior of the button.
//@doc SECOwnerDrawButton
//@mfunc virtual void | SECOwnerDrawButton | DrawSpecific | Draws the button.
//@parm CDC* | pDC |  Points to the device context.
//@parm  LPDRAWITEMSTRUCT | lpDS | The DRAWITEMSTRUCT passed with the 
// WM_DRAWITEM message.
//@parm  CRect& | rect | The bounding rectangle for the button face.
//@xref <c SECOwnerDrawButton> <mf SECOwnerDrawButton::DrawButton>

//@doc SECOwnerDrawButton
//@mfunc virtual void  | SECOwnerDrawButton | OnBnClicked | This method is meant
// to be overridden.
//@comm The current implementation is to do nothing when the button
// is clicked.

//@doc SECOwnerDrawButton
//@mdata BOOL  | SECOwnerDrawButton | m_bWin4 | TRUE if windows version 4.

// adinsert AutoDuck insertion point for SECOwnerDrawButton 
//@doc SECOwnerDrawButton 
//@class The SECOwnerDrawButton class is an abstract base class.  
// SECOwnerDrawButton provides the basic functionality required for 
// implementing an owner draw push button.  You can create your own owner 
// draw button objects simply by deriving a class from SECOwnerDrawButton 
// and overriding the pure virtual functions DrawFocus and DrawSpecific.
//
// When the user clicks the button, the control's OnBnClicked method is 
// called (as well as the standard BN_CLICKED notification that is sent to 
// its parent).
//
// See the COLOR sample in the \OT\SAMPLES\STANDARD\CONTROLS\COLRWELL 
// directory for a demonstration of this class.
//
//@ex You can attach classes derived from SECOwnerDrawButton to existing push 
// buttons with |
// 
// m_OwnerDrawButton.AttachButton(IDC_BUTTON1, this);
//
//@ex You can dynamically create an SECOwnerDrawButton button control with |
//
// m_OwnerDrawButton.Create(NULL, WS_VISIBLE | WS_TABSTOP 
//                          | WS_CHILD, rect, this, IDC_BUTTON1);
//
//@base public | CButton
class SECOwnerDrawButton : public CButton
{
	FOUNDATION_DECLARE_DYNAMIC(SECOwnerDrawButton);

	//@access Creation/Initialization

public:
	//@cmember
	/* Creates a SECOwnerDrawButton object.*/
	FOUNDATION_API SECOwnerDrawButton();

	//@cmember
	/* Attaches to an existing button control.*/
	FOUNDATION_API virtual BOOL AttachButton(int nCtlID, CWnd* pParentWnd, int iFlags=0);

	//@cmember
	/* Dynamically creates an SECOwnerDrawButton button control.*/
	FOUNDATION_API virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, int nID, int iFlags=0);

	// cmember Destructor.
	FOUNDATION_API virtual ~SECOwnerDrawButton();

	//@access Overridable
protected:
	// 
	//@cmember
	/* Called when button is clicked*/
	inline virtual void OnBnClicked() {}

#ifdef WIN32
	//@cmember
	/* Called when a BM_SETSTYLE message is sent ( Win32 Only).*/
	FOUNDATION_API virtual LRESULT OnSetStyle( WPARAM wParam, LPARAM lParam );
#endif

	// cmember Override to control the particular types of input to process.
	FOUNDATION_API afx_msg UINT OnGetDlgCode();

	// cmember Called when a change is made in the system color setting. 
	FOUNDATION_API afx_msg void OnSysColorChange();

	// cmember Called when the user releases a key.
	FOUNDATION_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	// cmember Called when the user double clicks the left mouse button.
	FOUNDATION_API afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );

	// cmember Called when the user releases the left mouse button.
	FOUNDATION_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	// cmember Called when the user moves the mouse over the button.
	FOUNDATION_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	// cmember Called when button is losing focus
	FOUNDATION_API afx_msg void OnKillFocus( CWnd* pWnd );

	// cmember Called when button is geting focus
	FOUNDATION_API afx_msg void OnSetFocus( CWnd* pWnd );

	// Implementation
public:
#ifdef _DEBUG
	 FOUNDATION_API virtual void Dump(CDumpContext& dc) const;
	 FOUNDATION_API virtual void AssertValid() const;
#endif

	inline virtual void SetCoolLook(BOOL bLook = TRUE) { m_bCoolLook = bLook; }
	inline virtual BOOL GetCoolLook() { return m_bCoolLook; }


protected:
	// Drawing functions.
	//@cmember
	/* Draws the button by calling <mf SECOwnerDrawButton::DrawButton>*/
	FOUNDATION_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);

	//@cmember
	/* Called before drawing the button.*/
	FOUNDATION_API virtual void PreDrawButton(CDC* pScreenDC, CDC* pMemDC);

	//@cmember
	/* Draws the button.*/
	FOUNDATION_API virtual CRect DrawButton(CDC* pDC, LPDRAWITEMSTRUCT lpDS );

	//@cmember
	/* Called after drawing the button.*/
	FOUNDATION_API virtual void PostDrawButton(CDC* pScreenDC, CDC* pMemDC);

	//@cmember
	/* Draws the button in a disabled state.*/
	FOUNDATION_API virtual void DrawDisabled(CDC* pDC, int nWidth, int nHeight);

	//@cmember
	/* Draws the focus rectangle.*/
	FOUNDATION_API virtual void DrawFocus(CDC* pDC, LPDRAWITEMSTRUCT lpDS);

	//@cmember
	/* Draws the focus rectangle.*/
	virtual void DrawFocus(CDC* pDC, CRect& rect) = 0;

	//@cmember
	/* Draws the button face.*/
	virtual void DrawSpecific(CDC* pDC, LPDRAWITEMSTRUCT lpDS, CRect& rect) = 0;

protected:

	// @access Protected data members

	//@cmember
	/* TRUE if windows version 4.*/
	BOOL m_bWin4;
	//@cmember
	/* TRUE if CoolLook is enabled.*/
	BOOL m_bCoolLook;

	//@cmember
	/* Contains return from DM_GETDEFID message after setfocus */
	DWORD m_dwPrevDefId;

	//@cmember
	/* Contains old button style */
	DWORD m_dwPrevStyle;

	// Implementation - message map and entries
	//DECLARE_MESSAGE_MAP()
	FOUNDATION_DECLARE_MESSAGE_MAP()

public:

	//@cmember
	/* Flags defining behavior of the button.*/
	int		m_iFlags;
	BOOL	m_bIsHot;

};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// SECWellButton window

/////////////////////////////
// AutoDuck tag block block for SECWellButton 


//@doc SECWellButton
//@mdata SECPopupColorWell*  | SECWellButton | m_pPopup | The popup color well.
//@xref <c SECWellButton> <mf SECWellButton::SetPopup> <mf SECWellButton::GetPopup>

//@doc SECWellButton
//@mdata CPalette  | SECWellButton | m_palette | Palette used for holding current color.
//@xref <c SECWellButton>
//@xref <mf SECWellButton::SetPaletteRealization> <mf SECWellButton::GetPaletteRealization>

//@doc SECWellButton
//@mdata CPalette*  | SECWellButton | m_pOldPal | Pallete used during drawing.
//@xref <c SECWellButton> <mf SECWellButton::SetPaletteRealization>
// <mf SECWellButton::GetPaletteRealization>

//@doc SECWellButton
//@mdata CPalette*  | SECWellButton | m_pMemOldPal | Pallete used during drawing.
//@xref <c SECWellButton> <mf SECWellButton::SetPaletteRealization>
// <mf SECWellButton::GetPaletteRealization>

//@doc SECWellButton
//@mdata BOOL  | SECWellButton | m_bRealizePalette | TRUE if object should 
// realize our palette before drawing
//@xref <c SECWellButton> <mf SECWellButton::SetPaletteRealization>
// <mf SECWellButton::GetPaletteRealization>

//@doc SECWellButton
//@mdata BOOL  | SECWellButton | m_bHasOther | TRUE if popup has other button.
//@xref <c SECWellButton> <mf SECWellButton::SetOtherButton>
// <mf SECWellButton::GetOtherButton>

//@doc SECWellButton
//@mdata DWORD  | SECWellButton | m_dwColorDialogFlags | Flags for customizing the CColorDialog displayed in response to clicking the Other button 
//@xref <c SECWellButton> <mf SECWellButton::SetColorDialogFlags> <mf SECWellButton::GetColorDialogFlags>

//@doc SECWellButton
//@mdata COLORREF*  | SECWellButton | m_pCustomColors | Pointer to an array of 16 colors for the custom color boxes in CColorDialog
//@xref <c SECWellButton>

// adinsert AutoDuck insertion point for SECWellButton 
//@doc SECWellButton 
//@class The SECWellButton class implements a button which can be used 
// for selecting colors.  The face of the button displays the color currently 
// selected.  When the user clicks the SECWellButton, a popup color palette is 
// displayed (SECPopupColorWell), which can be used to select the required 
// color.
//
//@comm You can specify whether the <c SECPopupColorWell> allows selection of colors 
// other than the 20 system colors with the SetOtherButton function.  This 
// will cause the SECPopupColorWell to display a button labeled 'Other', which 
// when clicked will cause a common color selection dialog to be displayed.
//
// You can specify whether you want the SECWellButton to support palettes with 
// the SetPaletteRealization function.  This will cause any colors selected to 
// be placed into a palette and the palette realized before drawing.
//
// The SECWellButton will send a CWN_COLOR_CHANGE message to its parent 
// when the selected color is changed.
//
// the <f DDX_Color> function can be used for data exchange in dialogs.
//
// See the COLOR sample in the \\OT\\SAMPLES\\STANDARD\\CONTROLS\\COLRWELL 
// directory for a demonstration of this class.
//
//@ex You can attach SECWellButton objects to existing push buttons with |
// 
// m_wellButton.AttachButton(IDC_BUTTON1, this);
//
//@ex You can dynamically create an SECWellButton button control with |
//
// m_wellButton.Create(NULL, WS_VISIBLE|WS_TABSTOP|
//                     WS_CHILD, rect, this, IDC_BUTTON1);
//
//@base public | SECOwnerDrawButton

class SECWellButton : public SECOwnerDrawButton
{
	FOUNDATION_DECLARE_DYNAMIC(SECWellButton);

	//@access Creation/Initialization
public:
	
	//@cmember
	/* Creates a SECWellButton object.*/
	FOUNDATION_API SECWellButton();

	//@access Attributes
public:

	//@cmember
	/* Set the currently selected color.*/
	FOUNDATION_API void SetColor(COLORREF cl);

	//@cmember
	/* Get the currently selected color.*/
	FOUNDATION_API COLORREF GetColor() const;

	//@cmember
	/* Set whether the popup has an other button or not.*/
	FOUNDATION_API void SetOtherButton( BOOL bOther );

	//@cmember
	/* Returns whether the popup has an other button or not.*/
	FOUNDATION_API BOOL GetOtherButton() const;

	//@cmember
	/* Set the current palette realizaion mode.*/
	FOUNDATION_API void SetPaletteRealization(BOOL bRealizePalette);

	//@cmember
	/* Get the current realization mode.*/
	FOUNDATION_API BOOL GetPaletteRealization() const;

	//@cmember
	/* Sets the flags for customizing the CColorDialog that is display in response to a click on the Other button. Default = CC_RGBINIT\|CC_FULLOPEN. */
	FOUNDATION_API virtual void SetColorDialogFlags(DWORD v);

	//@cmember
	/* Returns the flags for the color common dialog. Default = CC_RGBINIT\|CC_FULLOPEN. */
	FOUNDATION_API virtual DWORD GetColorDialogFlags() const;

	//@cmember
	/* Sets the array of 16 colors for the custom color boxes in CColorDialog */
	FOUNDATION_API virtual void SetCustomColors(COLORREF* pColors);
	
	//@cmember
	/* Retrieves the array of 16 colors for the custom color boxes in CColorDialog. Default=NULL */
	FOUNDATION_API COLORREF* GetCustomColors() const;

	//@cmember
	/* Sets the Popup to something other than the default.*/
	FOUNDATION_API void SetPopup(SECPopupColorWell* pPopup);

	//@cmember
	/* Returns a pointer to the current Popup.*/
	FOUNDATION_API SECPopupColorWell* GetPopup();

	//@access Overridable
protected:

	//@cmember
	/* Creates and initialises the palette.*/
	FOUNDATION_API virtual void CreatePalette();

	//@cmember
	/* Creates the popup color well.*/
	FOUNDATION_API virtual void CreatePopup();

	//@cmember
	/* Called when button is clicked (to create the popup).*/
	FOUNDATION_API virtual void OnBnClicked();
	
	//@cmember 
	/* Called when a color has been selected.*/
	FOUNDATION_API afx_msg LRESULT OnColorChange(WPARAM wParam, LPARAM lParam);
	
	//@cmember 
	/* Called when the "Other" button has been clicked.*/
	FOUNDATION_API afx_msg LRESULT OnCustomColor(WPARAM wParam, LPARAM lParam);

	//@cmember
	/* Called prior to drawing the button.*/
	FOUNDATION_API virtual void PreDrawButton(CDC* pScreenDC, CDC* pMemDC);

	//@cmember
	/* Called after drawing the button.*/
	FOUNDATION_API virtual void PostDrawButton(CDC* pScreenDC, CDC* pMemDC);

	//@cmember
	/* Draws the focus rectangle.*/
	FOUNDATION_API virtual void DrawFocus(CDC* pDC, CRect& rect);

	//@cmember
	/* Draws the button face.*/
	FOUNDATION_API virtual void DrawSpecific(CDC* pDC, LPDRAWITEMSTRUCT lpDS, CRect& rect);

	// Implementation

public:
	FOUNDATION_API virtual ~SECWellButton();

#ifdef _DEBUG
	 FOUNDATION_API virtual void Dump(CDumpContext& dc) const;
	 FOUNDATION_API virtual void AssertValid() const;
#endif

	//@access Protected data members

protected:

	//@cmember
	/* The popup color well.*/
	SECPopupColorWell* m_pPopup;
	
	//@cmember
	/* Palette used for holding current color.*/
	CPalette m_palette;
	
	//@cmember
	/* Pallete used during drawing.*/
	CPalette* m_pOldPal;
	
	//@cmember
	/* Pallete used during drawing.*/
	CPalette* m_pMemOldPal;
	
	//@cmember
	/* TRUE if object should realize our palette before drawing.*/
	BOOL m_bRealizePalette;
	
	//@cmember
	/* TRUE if popup has other button.*/
	BOOL m_bHasOther;

	//@cmember
	/* Flags for customizing the CColorDialog displayed in response to clicking the Other button */
	DWORD m_dwColorDialogFlags;

	//@cmember
	/* Pointer to an array of 16 colors for the custom color boxes in CColorDialog */
	COLORREF* m_pCustomColors;

	// Implementation - message map and entries
	//DECLARE_MESSAGE_MAP()
	FOUNDATION_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// DDX functions for use with the SECWellButton
 FOUNDATION_API void DDX_Color(CDataExchange* pDX, SECWellButton& cButton, COLORREF& color);

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// SECBitmapButton window

/////////////////////////////
// AutoDuck tag block block for SECBitmapButton 

//@doc SECBitmapButton
//@mdata LPCTSTR  | SECBitmapButton | m_lpszBmpName | Resource name for bitmap.
//@xref <c SECBitmapButton> <mf SECBitmapButton::AttachButton> <mf SECBitmapButton::Create>

//@doc SECBitmapButton
//@mdata CBitmap  | SECBitmapButton | m_bmp | The bitmap for the button.
//@xref <c SECBitmapButton> <mf SECBitmapButton::AttachButton> <mf SECBitmapButton::Create>

//@doc SECBitmapButton
//@mdata CSize  | SECBitmapButton | m_indents | Indentations of bitmap from edge of button face.
//@xref <c SECBitmapButton> <mf SECBitmapButton::SetIndents> <mf SECBitmapButton::GetIndents>


//@doc SECBitmapButton
//@mdata CRect  | SECBitmapButton | m_bmpRect | Window rectangle for the bitmap.
//@comm This rect is aligned with (0,0).
//@xref <c SECBitmapButton> 

//@doc SECBitmapButton
//@mdata CRect  | SECBitmapButton | m_textRect | Window rectangle for the text.	
//@comm This rect is aligned with (0,0).
//@xref <c SECBitmapButton> 

//@doc SECBitmapButton
//@mdata Alignment  | SECBitmapButton | m_alignment | The alignment mode.
//@xref <c SECBitmapButton> <md SECBitmapButton::Alignment>

// adinsert AutoDuck insertion point for SECBitmapButton 
//@doc SECBitmapButton 
//@class The SECBitmapButton class implements a button which displays a 
// bitmap and an optional caption on the button face.
//@comm The alignment modes are specified in <md SECBitmapButton::Alignment>.
// The alignment of the bitmap in all modes except SECBitmapButton::Al_Center 
// is always offset from the horizontal and vertical margins.  This offset 
// can be set with the SetIndents function.  The caption will always be clipped 
// so that it does not overwrite the bitmap.
//
// See the COLOR sample in the \\OT\\SAMPLES\\STANDARD\\CONTROLSCOLRWELL 
// directory for a demonstration of this class.
//
//@ex You can attach SECBitmapButton objects to existing push buttons with |
//
// m_bmpButton.AttachButton(IDC_BUTTON1,
// 		SECBitmapButton::Al_Left, 
// 		IDB_BMP, this);
//
//@ex You can dynamically create an SECBitmapButton button control with |
//
// m_bmpButton.Create("Help",
// 		WS_VISIBLE|WS_TABSTOP|WS_CHILD, SECBitmapButton::Al_Left, IDB_HELP,
// 		rect, this, IDC_BUTTON1);
//
//@base public | SECOwnerDrawButton

class SECBitmapButton : public SECOwnerDrawButton
{
	FOUNDATION_DECLARE_DYNAMIC(SECBitmapButton);
	
	//@cmember,menum
	/* The alignment modes.*/
	enum Alignment
	{
		Al_Left,		//@@emem Bitmap on left, text on right
		Al_Right,		//@@emem Bitmap on right, text on left
		Al_Top,			//@@emem Bitmap on top, text on bottom
		Al_Bottom,		//@@emem Bitmap on bottom, text on top
		Al_Center		//@@emem Bitmap centered in button. No caption.
	};

	//@access Creation/Initialization
public:

	//@cmember
	/* Creates a bitmap button object.*/
	FOUNDATION_API SECBitmapButton();

	
	//@cmember
	/* Attaches the bitmap button object to an existing button.*/
	FOUNDATION_API virtual BOOL AttachButton(int nCtlID, Alignment alignment, int nIDBmp, CWnd* pParentWnd, int iFlags=0);

	//@cmember
	/* Attaches the bitmap button object to an existing button.*/
	FOUNDATION_API virtual BOOL AttachButton(int nCtlID, Alignment alignment, LPCTSTR lpszBmpName, CWnd* pParentWnd, int iFlags=0);

	//@cmember
	/* Dynamically creates a bitmap button control.*/
	FOUNDATION_API virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, Alignment alignment, 
									   LPCTSTR lpszBmpName, const CRect& rect, CWnd* pParentWnd, 
									   int nID, int iFlags=0);

	//@cmember
	/* Dynamically creates a bitmap button control.*/
	FOUNDATION_API virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, Alignment alignment, 
								  	   int nIDBmp,	const CRect& rect, CWnd* pParentWnd, int nID,
									   int iFlags=0);

	//@access Attributes

public:

	//@cmember
	/* Sets the bitmap margin offsets.*/
	FOUNDATION_API void SetIndents(CSize sz);
	
	//@cmember
	/* Returns the bitmap margin offsets.*/
	FOUNDATION_API CSize GetIndents() const;

	//@access Operations
public:
	
	//@cmember
	/* Size the button to fit it's contents.*/
	FOUNDATION_API void SizeToContent();

	//@cmember
	/* Change the current bitmap*/
	FOUNDATION_API BOOL SetBitmap(LPCTSTR lpszBmp);
	
	//@cmember
	/* Change the current bitmap*/
	FOUNDATION_API BOOL SetBitmap(int nIDBmp);

	//@access Overridable

protected:

	//@cmember
	/* Calculates the position of the bitmap and text.*/
	FOUNDATION_API virtual void CalcLayout();

	//@cmember
	/* Draws the face of the button.*/
	FOUNDATION_API virtual void DrawSpecific(CDC* pDC, LPDRAWITEMSTRUCT lpDS, CRect& rect);
	
	//@cmember
	/* Draws the focus rectangle.*/
	FOUNDATION_API virtual void DrawFocus(CDC* pDC, CRect& rect);

	// cmember Called when a change is made in the system color setting. 
	FOUNDATION_API afx_msg void OnSysColorChange();

	// cmember Called after the window's size has changed. 
	FOUNDATION_API afx_msg void OnSize(UINT nType, int cx, int cy);

	// cmember Called when the window is destroyed.
	FOUNDATION_API afx_msg void OnDestroy();

// Implementation
public:
	FOUNDATION_API virtual ~SECBitmapButton();

#ifdef _DEBUG
	 FOUNDATION_API virtual void Dump(CDumpContext& dc) const;
	 FOUNDATION_API virtual void AssertValid() const;
#endif

protected:
	
	//@access Protected data members

	//@cmember
	/* Resource name for bitmap.*/
	LPCTSTR m_lpszBmpName;

	//@cmember
	/* The bitmap for the button.*/
	CBitmap m_bmp;

	//@cmember
	/* Indentations of bitmap from edge of button face.*/
	CSize m_indents;

	//@cmember
	/* Window rectangle for the bitmap*/
	CRect m_bmpRect;
	
	//@cmember
	/* Window rectangle for the text*/
	CRect m_textRect;
	
	//@cmember
	/* The alignment mode.*/
	Alignment m_alignment;

	// Implementation - message map and entries
	//DECLARE_MESSAGE_MAP()
	FOUNDATION_DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// SECMenuButton window

/////////////////////////////
// AutoDuck tag block block for SECMenuButton 

//@doc SECMenuButton
//@mdata CMenu    | SECMenuButton | m_menu | The popup menu.
//@xref <c SECMenuButton> <mf SECMenuButton::SetMenu>

//@doc SECMenuButton
//@mdata Direction  | SECMenuButton | m_direction | Direction of arrow (down or right).
//@xref <c SECMenuButton> <mf SECMenuButton::SetDirection> <mf SECMenuButton::GetDirection> 

//@doc SECMenuButton
//@mdata BOOL    | SECMenuButton | m_bAllowDraw | When FALSE, the button is not drawn.
//@xref <c SECMenuButton>

// adinsert AutoDuck insertion point for SECMenuButton 
//@doc SECMenuButton 
//@class The SECMenuButton class provides a simple button which when clicked 
// displays a popup menu.  This popup menu can be displayed either to the 
// right or below the button (See <md SECMenuButton::Direction>).  SECMenuButton 
// attaches to existing CButton controls and will pop up a given menu whenever 
// the button is clicked.
//
//@comm To use SECMenuButton, follow this procedure:
//
//1.  Attach SECMenuButton to an existing CButton using the AttachButton 
// member function.<nl>
//2. Specify the handle of the popup menu.<nl>
//3. Specify where to place the popup menu (below or to the right of the button).<nl>
//
// You can dynamically create an SECMenuButton using the Create function.  
// Note that the menu handle must exist for the life of the SECMenuButton 
// object.
//
// See the COLOR sample in the \\OT\\SAMPLES\\STANDARD\\CONTROLS\\COLRWELL 
// directory for a demonstration of this class.
//@base public | SECBitmapButon

class SECMenuButton : public SECBitmapButton
{
	FOUNDATION_DECLARE_DYNAMIC(SECMenuButton);

	//@cmember,menum
	/* Direction constants*/
	enum Direction
	{
		DT_Down,	//@@emem Menu drops down.
		DT_Right	//@@emem Menu appears to the right.
	};

	//@access Creation/Initialization

public:

	//@cmember
	/* Creates a menu button object.*/
	FOUNDATION_API SECMenuButton();

	//@cmember
	/* Attaches the menu button object to an existing button.*/
	FOUNDATION_API virtual BOOL AttachButton(int nCtlID, CWnd* pParentWnd, HMENU hMenu,
						  				     Direction direction=DT_Down, int iFlags=0);

	//@cmember
	/* Dynamically creates a menu button control.*/
	FOUNDATION_API virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CRect& rect, 
									   CWnd* pParentWnd, int nID, HMENU hMenu, 
									   Direction direction=DT_Down, int iFlags=0);

	//@access Attributes

public:
	
	//@cmember
	/* Sets the direction of the arrow on the button.*/
	FOUNDATION_API void SetDirection(Direction direction);

	//@cmember
	/* Gets the direction of the arrow on the button.*/
	FOUNDATION_API Direction GetDirection() const;
	
	//@access Operations

public:

	//@cmember
	/* Sets the popup menu.*/
	FOUNDATION_API void SetMenu(HMENU hMenu);

	//@access Overridable

protected:

	//@cmember
	/* Called when the button is clicked (to create popup menu) */
	FOUNDATION_API virtual void OnBnClicked();

	//@cmember
	/* Performs object initialisation.*/
	FOUNDATION_API virtual SECBitmapButton::Alignment Initialise(LPCTSTR lpszCaption, HMENU hMenu, 
  										  						 Direction direction, UINT& nIDBmp);

	//@cmember
	/* Draws the button.*/
	FOUNDATION_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDS);

	// cmember Called when the user releases the left mouse button.
	FOUNDATION_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	FOUNDATION_API virtual void PostNcDestroy( );

	// Implementation
public:
	FOUNDATION_API virtual ~SECMenuButton();

#ifdef _DEBUG
	FOUNDATION_API virtual void Dump(CDumpContext& dc) const;
	FOUNDATION_API virtual void AssertValid() const;
#endif


protected:

	//@access Protected data members

	FOUNDATION_API virtual BOOL PreTranslateMessage(MSG* pMsg);

	// cmember Called when the user releases a key.
	FOUNDATION_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	//@cmember
	/* The popup menu.*/
	CMenu	  m_menu;
	
	//@cmember
	/* Direction of arrow (down or right).*/
	Direction m_direction;

	//@cmember
	/* 	When FALSE, the button is not drawn.*/
	BOOL	  m_bAllowDraw;

	BOOL	  m_bMenuPresent;
	BOOL      m_bAllowKeyProcessing;

	// Implementation - message map and entries
	//DECLARE_MESSAGE_MAP()
	FOUNDATION_DECLARE_MESSAGE_MAP()
};

};  // namespace stingray::foundation
};  // namespace stingray

/////////////////////////////////////////////////////////////////////////////

//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif //__SFL_SECBTNS_H__

