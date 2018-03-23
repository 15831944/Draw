///////////////////////////////////////////////////////////////////////////////
// tbtnstd.h
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
//  Description:	Declarations for SECToolBar
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBTNSTD_H__
#define __TBTNSTD_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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
class SECCustomToolBar;
struct SECButtonClass;

// Define the height and width of an individual item in the toolbar bitmap
#define SEC_TOOLBAR_IMAGE_WIDTH		16
#define SEC_TOOLBAR_IMAGE_HEIGHT	15

///////////////////////////////////////////////////////////////////////////////
// SECBtnDrawData struct - contains cached info for drawing toolbars
//
struct SECBtnDrawData
{
	CDC m_monoDC;					// mono DC used during drawing
	CDC m_bmpDC;					// DC holding the toolbar bmp
	CDC m_drawDC;					// mem. DC we use to draw to
	CBrush m_ditherBrush;			// Dither brush used for drawing
									// checked/indeterminate buttons

	TOOLKIT_API SECBtnDrawData();

	// Called when system color scheme changes.
	TOOLKIT_API void SysColorChange();

	// Pre/Post drawing initialization
	TOOLKIT_API void SetBitmap(HBITMAP hBmp);
	TOOLKIT_API BOOL PreDrawButton(CDC& dc, int nMaxBtnWidth, int nMaxBtnHeight, SECCustomToolBar* pToolBar);
	TOOLKIT_API void PostDrawButton();

	TOOLKIT_API static HBRUSH CreateDitherBrush();

	// QA: 31881
	// Set Button's transparency color. 
	inline virtual void SetTransparentColor(COLORREF clrTransparent, BOOL bUseCustomTransparentColor = TRUE) 
	{ 
		m_clrTransparency = clrTransparent; 
		m_bUseCustomTransparentColor = bUseCustomTransparentColor;
	}
	// QA: 31881
	// Get Buttonm's transparency color.
	inline virtual COLORREF GetTransparentColor() 
	{
		if(m_bUseCustomTransparentColor)
		{
			return m_clrTransparency; 
		}else
		{
			if(m_bmpDC.m_hDC)
			{
				BITMAP bm;
				CBitmap* pBmp = m_bmpDC.GetCurrentBitmap();
				pBmp->GetBitmap(&bm);
				ASSERT(pBmp);

				return (bm.bmBitsPixel < 16 ) ? RGB(192, 192, 192) : m_bmpDC.GetPixel(0, 0);
			}else
			{
				return RGB(192, 192, 192);
			}
		}
	}

protected:
	// Members used by pre/post drawing functions
	CBitmap  m_bmpDraw;
	CBitmap* m_pOldBmpDraw;
	CBitmap  m_bmpMono;
	CBitmap* m_pOldBmpMono;
	HGDIOBJ  m_hOldBmp;
	HBITMAP  m_hCurBmp;
	COLORREF m_clrTransparency;
	BOOL     m_bUseCustomTransparentColor;
};

///////////////////////////////////////////////////////////////////////////////
// SECStdBtn class

/////////////////////////////
// AutoDuck tag block block for SECStdBtn

// adinsert AutoDuck insertion point for SECStdBtn
//@doc SECStdBtn
//@class The SECStdBtn class includes various operations for drawing buttons on a 
// toolbar. Its member functions are normally called from the Customize dialog 
// (see class SECToolBarsDlg).  
//@comm 
// An end user can use this dialog to create a toolbar 
// with buttons in a style geared toward a particular task.  If the default styles 
// offered in the Customize dialog do not match the user’s requirements, the New 
// Toolbar dialog, reached from within the Customize dialog, allows the user to 
// create a new toolbar from scratch, with a set of buttons in a unique style.
//
// SECStdBtn encapsulates a single toolbar button.  It is used by the 
// SECCustomToolBar class.
//
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration 
// of this class.
//@xref <c SECToolBarsDlg> <c SECToolBarsPage> <c SECCustomToolBar> <c SECToolBarManager>
class SECStdBtn
{
// Construction
public:
	TOOLKIT_API SECStdBtn();

// Attributes
public:
	enum InformCode			// Codes informing us to take some kind of action
	{
		IBase   = 0x0000,
		Styles  = IBase + 1	// Add/Remove button styles.
	};

	enum BtnType			// List the various button types.
	{
		BtnStandard,		// SECStdBtn
		BtnTwoPart,			// SECTwoPartBtn
		BtnWnd,				// SECWndBtn
		BtnMenu,			// SECTBMenuBtn
		BtnMenuCap,			// SECCapMenuBtn
		BtnCaption,			// SECBtnCaption
		BtnCombo,			// SECComboBtn
		BtnText 			// SECTBTextButton
	};

	struct StyleChange		// Used by InformCode::Styles
	{
		DWORD dwAdd;		// Style bits to add
		DWORD dwRemove;		// Style bits to remove
	};

	UINT m_nID;				// Button ID
	UINT m_nImage;			// Index of image in toolbar bitmap
	UINT m_nStyle;			// Button styles

	int  m_x;				// x position in parent toolbars client rect
	int  m_y;				// y position in parent toolbars client rect
	int  m_cx;				// Width of button
	int  m_cy;				// Height of button
	int  m_nType;			// See BtnType enum

// Operations
public:
	// Sets the parent toolbar
	//@cmember
	/* tSets the parent toolbar.*/
	TOOLKIT_API void SetToolBar(SECCustomToolBar* pToolBar);

	// Returns the window rect. for this button (relative to parent's client)
	//@cmember
	/* Returns the window rect. for this button (relative to parent’s client).*/
	TOOLKIT_API void GetBtnRect(CRect& rect) const;

	// Returns TRUE if this button is hidden
	TOOLKIT_API BOOL IsHidden() const;

	// Returns TRUE if this is a menu button
	TOOLKIT_API BOOL IsMenuButton() const;
	TOOLKIT_API BOOL IsStandardMenuButton() const;

	// SetMode informs the button when the button either enters/leaves a
	// vertically docked state
	//@cmember
	/* Informs the button when the button either enters or leaves a vertically docked state.*/
	TOOLKIT_API virtual void SetMode(BOOL bVertical);

	// SetStyle sets the button style for this button object.
	//@cmember
	/* Sets the button style for this button object.*/
   TOOLKIT_API virtual void SetStyle(UINT nStyle);

	// GetStyle gets the button style for this button object.
	//@cmember
	/* Gets the button style for this button object.*/
   TOOLKIT_API virtual UINT GetStyle() const;

	// TestStyle tests if a specifc style is set for this button object
	//@cmember
	/* Tests if a specifc style is set for this button object*/
   TOOLKIT_API virtual BOOL TestStyle(UINT nStyle) const;

	// Modifies our window position
	//@cmember
	/* Modifies the window position relative to the parent’s client area.*/
	TOOLKIT_API virtual void SetPos(int x, int y);

	// Invalidates the button
	//@cmember
	/* Invalidates the button.*/
	TOOLKIT_API virtual void Invalidate(BOOL bErase = FALSE) const;

// Overrideables
public:
	// Initialises button after creation.
	//@cmember
	/* Called after construction to allow the button to initialize.*/
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);

	// Return FALSE if the button cannot be dragged

	inline virtual BOOL CanDrag() const { return TRUE; }

	// Draw the button on the given DC.
	//@cmember
	/* Draws the button on the given DC.*/
	TOOLKIT_API virtual void DrawButton(CDC& dc, SECBtnDrawData& data);

	// Handle mouse events in the button's window rect.
	//@cmember
	/* Handles a mouse button press in the toolbar button’s window rect.*/
	TOOLKIT_API virtual BOOL BtnPressDown(CPoint point);
	//@cmember
	/* Handles dragging the mouse while a mouse button is pressed.*/
	TOOLKIT_API virtual void BtnPressMouseMove(CPoint point);
	//@cmember
	/* Handles the WM_CANCELMODE message while tracking a WM_LBUTTONDOWN message.*/
	TOOLKIT_API virtual void BtnPressCancel();
	//@cmember
	/* Handles release of a mouse button press.*/
	TOOLKIT_API virtual UINT BtnPressUp(CPoint point);

	// Called when the button is hidden or unhidden.
	inline virtual void OnHide() {}

	// Our parent toolbars style has been modified.
	//@cmember
	/* Notifies that parent toolbar’s style has been modified.*/
	TOOLKIT_API virtual void BarStyleChanged(DWORD dwStyle);

	// Tool-tip/flyby help hit-testing
	//@cmember
	/* Tests tooltip/flyby help.*/
	TOOLKIT_API virtual int  OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	// Informs button of some event
	//@cmember
	/* Informs button of some event.  Normally used to reflect a change of */
	// state in all buttons of the same ID.
	TOOLKIT_API virtual void InformBtn(UINT nCode, void* pData);

	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	//@cmember
	/* Called when toolbar bitmap has changed; button should now adjust their size.*/
	TOOLKIT_API virtual void AdjustSize();

	// Functions called when saving/loading a toolbar state, allowing the
	// button to save state info.
	//@cmember
	/* Called when loading a toolbar state, allowing a toolbar button to save state info.*/
	TOOLKIT_API virtual void GetBtnInfo(BYTE* nSize, LPBYTE* ppInfo) const;
	//@cmember
	/* Called when saving a toolbar state, allowing a  toolbar button to save state information.*/
	TOOLKIT_API virtual void SetBtnInfo(BYTE nSize, const LPBYTE pInfo);

	// Function that sends a WM_NOTIFY for this button.
	TOOLKIT_API virtual LRESULT SendWmNotify(UINT code, SEC_DWORD dwMisc1 = 0, SEC_DWORD dwMisc2 = 0);

protected:
	// Drawing functions ...
	TOOLKIT_API virtual void DrawFace(SECBtnDrawData& data, BOOL bForce, int& x, int& y, 
						  int& nWidth, int& nHeight, int nImgWidth, CDC& dc);
	TOOLKIT_API virtual void DrawDisabled(SECBtnDrawData& data, int x, int y, int nWidth, 
							  int nHeight, CDC& dc);
	TOOLKIT_API virtual void DrawChecked(SECBtnDrawData& data, int x, int y, int nWidth, 
							 int nHeight, CDC& dc);
	TOOLKIT_API virtual void DrawIndeterminate(SECBtnDrawData& data, int x, int y, 
								               int nWidth, int nHeight, CDC& dc);
	TOOLKIT_API virtual void DrawConfigFocus(SECBtnDrawData& data);
	TOOLKIT_API virtual void LoadItemBitmap(SECBtnDrawData& data);

	// DrawButton hooks
	TOOLKIT_API virtual BOOL OnDrawButtonAsSeparator(CDC& dc);
	TOOLKIT_API virtual void OnDrawButtonFace(SECBtnDrawData& data, CDC& dc);
	TOOLKIT_API virtual void OnDrawFaceBlt(int xImg,int yImg,int nImgWidth,int nImgHeight, SECBtnDrawData& data,int xDest,int yDest, CDC& dc);
	TOOLKIT_API virtual void OnDrawButtonBkgnd(CDC& dc, SECBtnDrawData& data);
	TOOLKIT_API virtual void OnDrawButtonFocus(SECBtnDrawData& data);
	TOOLKIT_API virtual void OnDrawButtonFinalBlt(CDC& dc, SECBtnDrawData& data);

// Implementation
public:
	TOOLKIT_API virtual ~SECStdBtn();

protected:	
	// Drawing helper functions
	TOOLKIT_API void CreateMask(SECBtnDrawData& data, int x, int y, int nWidth, int nHeight);

protected:
	// Implementation, data members.
	SECCustomToolBar* m_pToolBar;			// Our parent toolbar
	HTHEME m_hToolbarTheme;

public:
	// Dynamic creation helpers
	TOOLKIT_API virtual SECButtonClass* GetButtonClass() const;
	TOOLKIT_API static SECStdBtn* PASCAL CreateButton();

	TOOLKIT_API static const /*AFX_DATA*/ SECButtonClass classSECStdBtn; // QA: 31952
	BOOL m_bVertical;
};

///////////////////////////////////////////////////////////////////////////////

inline BOOL SECStdBtn::IsHidden() const
{
	return (BOOL) (m_nStyle & TBBS_HIDDEN);
}

inline BOOL SECStdBtn::IsMenuButton() const
{
	return (BOOL) (m_nType == BtnMenu || m_nType == BtnMenuCap);
}

inline BOOL SECStdBtn::IsStandardMenuButton() const
{
	return (BOOL) (m_nType == BtnMenu);
}

///////////////////////////////////////////////////////////////////////////////
// Dynamic button creation helpers
//
#define BUTTON_CLASS(class_name) ((SECButtonClass*)(&class_name::class##class_name))

//---------------------------------------------------------------------------//
// The definition of DECLARE_BUTTON has been moved to StingrayExportDefs.h   //
// Refer to TOOLKIT_DECLARE_BUTTON.                                          //
//---------------------------------------------------------------------------//

struct SECButtonClass 
{
// Attributes
	SECStdBtn* (PASCAL* m_pfnCreateButton)(); // Treat as function template; do not export

// Operations
	TOOLKIT_API SECStdBtn* CreateButton();
};

///////////////////////////////////////////////////////////////////////////////
// Button map definitions and helper macros	 **** DEAN - Should this be moved?
//
#define BTNMAP_DATA_ELEMENTS	5
struct TOOLKIT_API SECBtnMapEntry
{
	SECButtonClass* m_pBtnClass;					// Class for this button
	UINT            m_nID;							// ID for this button
	UINT	 	    m_nStyle;						// Style for this button
	SEC_UINT        m_nData[BTNMAP_DATA_ELEMENTS];	// Button specific info.
};

// Define the beginning of a toolbar map.
#define BEGIN_BUTTON_MAP(name) \
	static const SECBtnMapEntry name[] = {

// Define a standard toolbar button
#define STD_BUTTON(id, style) \
	{BUTTON_CLASS(SECStdBtn), id, style|TBBS_BUTTON, 0, 0, 0, 0, 0},

// Define the end of the toolbar map
#define END_BUTTON_MAP() \
	{NULL, 0, 0, 0, 0, 0, 0, 0} \
	};
//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBTNSTD_H__

#endif // WIN32

