///////////////////////////////////////////////////////////////////////////////
// lstbxclr.h
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
//  Author:			John Williston
//  Description:	Declaration for SECColorsListBox
//  Created:		August 1996
//

#ifndef __LSTBXCLR_H__
#define __LSTBXCLR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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
// SECColorsListBox window

/////////////////////////////
// AutoDuck tag block block for SECColorsListBox 

// adinsert AutoDuck insertion point for SECColorsListBox 
//@doc SECColorsListBox 
//@class The SECColorsListBox class implements an owner-drawn list box that 
// displays a list of color names with the actual color beside each name.  
// Double-clicking on a color pops up a color edit box, displaying the color 
// and allowing the user to edit the color.  After the user is done, the 
// color is written back to the selected list box item.
//
//@comm See the TOOLMENU sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\TOOLMENU 
// directory for a  demonstration of this class.
//@base public | CListBox
class SECColorsListBox : public CListBox
{
public:

	//@access Creation/Initialization

	//@cmember
	/* Constructs an SECColorsListBox object. */
	TOOLKIT_API SECColorsListBox(BOOL bAllowDblClickEdit = TRUE);

	// Attributes
public:

	//@access Operations

	//@cmember
	/* The specified list box is converted to a color list box.*/
	TOOLKIT_API BOOL ReplaceListbox(CListBox* pWnd);

	//@cmember
	/* Adds a color to the list box.*/
	TOOLKIT_API int AddColor(const TCHAR* pcszName, COLORREF crColor);
	
	//@cmember
	/* Returns the text and color at the specified index*/
	TOOLKIT_API BOOL GetColor(int iIndex, CString& str, COLORREF& cr);
	
	//@cmember
	/* Sets the text and color at the specified index.*/
	TOOLKIT_API BOOL SetColor(int iIndex, const TCHAR* pcszName, COLORREF cr);
	
	//@cmember
	/* Pops up a color edit box to edit the selected color.*/
	TOOLKIT_API BOOL EditSelectedColor();

public:

	// access Overrides

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECColorsListBox)

	// Called when a list box with an owner-draw style is created. 
	TOOLKIT_API virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	// Called when a visual aspect of an owner-draw list view control changes. 
	TOOLKIT_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(SECColorsListBox)

	// Called when the user double-clicks the left mouse button. 
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	
	// Implementation
public:
	TOOLKIT_API virtual ~SECColorsListBox();

private:
	BOOL m_bAllowDblClickEdit;
	TOOLKIT_API void FastRect(CDC *pDC, CRect* pRect, COLORREF cr);

	// Generated message map functions
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

#endif	// __LSTBXCLR_H__

