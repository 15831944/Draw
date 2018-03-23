///////////////////////////////////////////////////////////////////////////////
// SwtchBtn.h
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

/////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc SRSwatchButton
//@module SwtchBtn.h | SRSwatchButton header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// SwtchBtn.h: interface of the SRSwatchButton class
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGSWATCHBUTTON_H__
#define __SRGSWATCHBUTTON_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRSwatchButton 

//@doc SRSwatchButton

//@mdata COLORREF  | SRSwatchButton | m_RGBSwatchColor | RGB color of the button -- must be set directly

// adinsert AutoDuck insertion point for SRSwatchButton 
//$head Utility classes
//$level 1

//@topic SRSwatchButton Class Overview |
//This class is an extension of the simple buton class which is used to display a "swatch" of color on a dialog. 
//The button has a variable which may be set to an RGB color combination. This then indicates a chosen color value.

//@doc SRSwatchButton 
//@class Simple button control that paints itself the solid color specified in the 
//m_RGBSwatchColor member variable<nl>
//SRSwatchButton is used in dialogs to display a current color selection.<nl>
//Typically, the developer will provide a handler for this control's "been clicked" message 
//which invokes the standard color selection dialog.
//@base public | CButton
class SRSwatchButton : public CButton
{
// Construction
public:
		//@cmember
		/* Color of the button -- must be set directly*/
	COLORREF m_RGBSwatchColor;
		//@cmember
		/* Default constructor*/
	CHART_API SRSwatchButton();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRSwatchButton)
	public:
		//@cmember
		/* Standard function called to draw the item onto the dialog or parent window.*/
		CHART_API virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
		//@cmember
		/* Destructor*/
	CHART_API virtual ~SRSwatchButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(SRSwatchButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


