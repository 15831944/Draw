///////////////////////////////////////////////////////////////////////////////
// TBMPMENU.h
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
//  Description:	Declarations for SECBmpMenuPlugIn
//  Created:		Jan 1998
//

#ifdef WIN32

#ifndef __TBMPMENU_H__
#define __TBMPMENU_H__

#pragma warning(disable:4786)

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif


#ifndef __PLUGIN_H__
#include "Foundation\patterns\MFC\plugin.h"
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
//  SECBmpMenuItemInfo class
//
//  Holds information about a menu item that we will draw.
//
class SECBmpMenuItemInfo : public CObject
{
	TOOLKIT_DECLARE_DYNAMIC(SECBmpMenuItemInfo)

public:
	UINT    m_nID;						// The ID of the menu item
	CString m_strText;					// The text of the menu item
	TCHAR   m_cAccel;					// The accelerator character for the item
	BOOL	m_bDefault;					// The Default item flag for the item
};


/////////////////////////////////////////////////////////////////////////////
//  SECBmpMenuPlugIn class
//  
//  Implements bitmap menu support (plugging into the window that owns the
//  the menu).
// 
class SECBmpMenuPlugIn : public stingray::foundation::SECWndPlugIn
{
	TOOLKIT_DECLARE_DYNAMIC(SECBmpMenuPlugIn)

// Construction
public:
	// Note bFixCheckBmps will cause internal bitmaps to be used for check
	// marks. This gets around the problem with the standard check marks
	// being scaled to the current font (where as our bitmaps are fixed to
	// the size of the toolbar bitmap small image).
	TOOLKIT_API SECBmpMenuPlugIn(BOOL bFixCheckBmps = TRUE);

// Operations
public:
	// Adds a toolbar resource for providing bitmap images.
	TOOLKIT_API BOOL AddToolBarResource(LPCTSTR lpszStdBmpName);
	TOOLKIT_API BOOL AddToolBarResource(UINT nIDStdBmp);

	// Adds a bitmap resource for providing bitmap images.
	TOOLKIT_API BOOL AddBitmapResource(LPCTSTR lpszStdBmpName,
						               const UINT* lpIDArray, UINT nIDCount);
	TOOLKIT_API BOOL AddBitmapResource(UINT nIDstdBmpName, const UINT* lpIDArray, UINT nIDCount);

	// Defines a bitmap handle for providing bitmap images.
	TOOLKIT_API BOOL AddBitmap(HBITMAP hBmpSmall, const UINT* lpIDArray, UINT nIDCount);

	// Sets the bitmap manager to use (normally an internal version will be
	// used).
	TOOLKIT_API void SetBmpMgr(SECBmpMgr* pMgr);

	// Defines menu item IDs that are not to be drawn by this class.
	TOOLKIT_API void AddNoSubclass(UINT nID);

	inline virtual void SetBmpTransparentColor(COLORREF clrBmpTransparent, BOOL bUseCustomBmpTransparentColor = TRUE) 
	{
		m_clrBmpTransparency = clrBmpTransparent; 
		m_bUseBmpTransparency = bUseCustomBmpTransparentColor;
	}

	inline virtual COLORREF GetBmpTransparentColor()
	{
		return m_clrBmpTransparency;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECBmpMenuPlugIn)
	//}}AFX_VIRTUAL

// Implementation
public:
	TOOLKIT_API virtual ~SECBmpMenuPlugIn();

	// Performs garbage collection of various internal allocated structures.
	TOOLKIT_API virtual void GarbageCollect();

	// Entrypoint for frame window to hook WM_INITMENUPOPUP to
	TOOLKIT_API void InitMenuPopup(WPARAM wParam, LPARAM lParam);

protected:
	// SECBmpMenuInfo contains information relating to a specific menu handle,
	// and the items that we have made owner drawn.
	struct SECBmpMenuInfo
	{
		TOOLKIT_API ~SECBmpMenuInfo();

		// The handle of the menu.
		HMENU m_hMenu;

		// List of items that we have made owner drawn.
		CList<SECBmpMenuItemInfo*, SECBmpMenuItemInfo*> m_items;
	};

	// Map of menu handles to associated SECBmpMenuInfo structure.
	CMap<HMENU, HMENU, SECBmpMenuInfo*, SECBmpMenuInfo*> m_infos;

	// List of ID's that we are not to make owner drawn.
	CMap<UINT, UINT, UINT, UINT> m_noTouch;

	BOOL       m_bFixCheckBmps;			// TRUE if we are to use our own check mark bitmaps
	SECBmpMgr* m_pBmpMgr;				// Our Bitmap Manager
	CFont      m_fontMenu;				// The font used for drawing menu items
	CFont      m_fontDefaultMenu;		// The font used for drawing default menu items
	HBRUSH     m_hDitherBrush;			// Brush used for dithering background of checked items
	HTHEME     m_hMenuTheme;
	COLORREF   m_clrBmpTransparency;
	BOOL	   m_bUseBmpTransparency;

	// Function for Creating m_fontMenu.
	TOOLKIT_API virtual void  CreateMenuFont();
	TOOLKIT_API virtual void  CreateDefaultMenuFont();
	
	// Returns the font handle (m_fontMenu) used for drawing menu items.
	// See implementations below
	inline HFONT GetMenuFont();
	inline HFONT GetDefaultMenuFont();

	// Create a mono mask for the given bitmap
	TOOLKIT_API virtual BOOL CreateMask(CDC& dcSrc, CDC& monoDC, CBitmap& bmpMask, CBitmap*& pOldBmp, 
							            int cx, int cy, int xSrc);

	// Draws a checked bitmap (background if dithered).
	TOOLKIT_API virtual void DrawChecked(CDC& dcDest, int x, int y, int cx, int cy, CDC& dcSrc, int xSrc);

	// Draws a disabled bitmap
	TOOLKIT_API virtual void DrawDisabled(CDC& dcDest, int x, int y, int cx, int cy, CDC& dcSrc, int xSrc);

	// Method for drawing a bitmap button on a menu item
	TOOLKIT_API virtual void DrawButton(LPDRAWITEMSTRUCT lpDIS, CDC& dc, CRect& r, CBitmap* pBmp, 
							            int nBmpIndex, int nBmpWidth, int nBmpHeight);

	// Vista Support-----------------------------
	void DoDrawButton(CRect& r, CDC* pDC, LPDRAWITEMSTRUCT lpDIS, CBitmap* pBmp, UINT& nBmpIndex);
	//-------------------------------------------

	// Generated message map functions
protected:
	//{{AFX_MSG(SECBmpMenuPlugIn)
	TOOLKIT_API afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	TOOLKIT_API afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	TOOLKIT_API afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	TOOLKIT_API afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	TOOLKIT_API afx_msg void OnIdleUpdateCmdUI();
	TOOLKIT_API afx_msg void OnSysColorChange();
	TOOLKIT_API afx_msg void OnSettingChange();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

inline HFONT SECBmpMenuPlugIn::GetMenuFont()
{
	if(m_fontMenu.m_hObject == NULL)
		CreateMenuFont();

	return m_fontMenu;
}
inline HFONT SECBmpMenuPlugIn::GetDefaultMenuFont()
{
	if(m_fontDefaultMenu.m_hObject == NULL)
		CreateDefaultMenuFont();

	return m_fontDefaultMenu;
}

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
/////////////////////////////////////////////////////////////////////////////

#endif	// __TBMPMENU_H__
#endif	// WIN32
