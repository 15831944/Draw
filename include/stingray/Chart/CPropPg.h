///////////////////////////////////////////////////////////////////////////////
// CPropPg.h
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
//@doc
//@module CPropPg.h | definitions for Chart Explorer property page classes
//Written by Bob Powell ( www.roguewave.com )
//
// using cmember tags only for these dialog classes
/////////////////////////////////////////////////////////////
//
// CPropPg.h : header file
//
//////////////////////////////////////////////////////////////

//$head The chart explorer
//$level 1
//adinsert

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGCOMPONENTPROPERTYPAGES_H__
#define __SRGCOMPONENTPROPERTYPAGES_H__

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
// SRGCTypeAndPos dialog
//
/////////////////////////////
// AutoDuck tag block for SRGCTypeAndPos 


//@doc SRGCBorderStyle
//@mdata int   | SRGCBorderStyle | m_nBorderStyle | The border style

// adinsert AutoDuck insertion point for SRGCTypeAndPos 

//@topic SRGCTypeAndPos Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCTypeAndPos 
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to specify the position, measurement mode, and view angles 
//for the selected component
//@base public | CPropertyPage
class SRGCTypeAndPos : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCTypeAndPos)

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCTypeAndPos();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCTypeAndPos();

// Dialog Data
	//{{AFX_DATA(SRGCTypeAndPos)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE1 };
	//@cmember
	/* Position of left edge of component rectangle*/
	double	m_dLeft;
	//@cmember
	/* Position of top edge of component rectangle*/
	double	m_dTop;
	//@cmember
	/* Position of right edge of component rectangle*/
	double	m_dRight;
	//@cmember
	/* Position of bottom edge of component rectangle*/
	double	m_dBottom;
	//@cmember
	/* Measurement mode or units for position parameters*/
	int		m_nMeasurement;
	//@cmember
	/* Text naming the type of the selected component*/
	CString	m_strType;
	//@cmember
	/* Z viewing angle*/
	double	m_dZAngle;
	//@cmember
	/* X viewing angle*/
	double	m_dXAngle;
	//@cmember
	/* Y viewing angle*/
	double	m_dYAngle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCTypeAndPos)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCTypeAndPos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCFillStyle dialog

//@topic SRGCFillStyle Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCFillStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to specify how the background of the selected component is filled
//@base public | CPropertyPage
class SRGCFillStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCFillStyle)

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCFillStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCFillStyle();

// Dialog Data
	//{{AFX_DATA(SRGCFillStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE2 };
	//@cmember
	/* Displays and selects final color for shade (vignette)*/
	SRSwatchButton	m_SwatchB;
	//@cmember
	/* Displays and selects solid color or initial color for shade (vignette)*/
	SRSwatchButton	m_SwatchA;
	//@cmember
	/* Index of radio button for selected type of fill*/
	int		m_nFillStyle;
	//@cmember
	/* Angle for Angled shade*/
	double	m_dAngle;
	//@cmember
	/* Name of resource file for resource image fill*/
	CString	m_strResourceName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCFillStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CHART_API virtual BOOL OnInitDialog();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCFillStyle)
	CHART_API afx_msg void OnButton1();
	CHART_API afx_msg void OnButton2();
	CHART_API afx_msg void OnButton3();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCBorderStyle dialog

//@topic SRGCBorderStyle Class Overview |
//This class is a simple property page that is used in the chart explorer.

//@doc SRGCBorderStyle
//@mdata int   | SRGCBorderStyle | m_nBorderStyle | Holds the radio button data.

//@doc SRGCBorderStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to choose a border style for the selected component
//@base public | CPropertyPage
class SRGCBorderStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCBorderStyle)

// Construction
public:
	//@cmember,mfunc
	/* Constructor*/
	CHART_API SRGCBorderStyle();
	//@cmember,mfunc
	/* Destructor*/
	CHART_API ~SRGCBorderStyle();

// Dialog Data
	//{{AFX_DATA(SRGCBorderStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE3 };
	//@cmember
	/* Index of radio button for selected style*/
	int		m_nBorderStyle;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCBorderStyle)
protected:

	//@cmember,mfunc
	/* Standard dialog box data exchange */
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCBorderStyle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCShadowStyle dialog

//@topic SRGCShadowStyle Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCShadowStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to choose a shadow style for the selected component
//@base public | CPropertyPage
class SRGCShadowStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCShadowStyle)

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCShadowStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCShadowStyle();

// Dialog Data
	//{{AFX_DATA(SRGCShadowStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE4 };
	//@cmember
	/* Index of radio button for selected style*/
	int		m_nShadowStyle;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCShadowStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCShadowStyle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCFontStyle dialog

//@topic SRGCFontStyle Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCFontStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to choose a font style for the selected component
//@base public | CPropertyPage
class SRGCFontStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCFontStyle)

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCFontStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCFontStyle();

// Dialog Data
	//{{AFX_DATA(SRGCFontStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE5 };
	//@cmember
	/* Displays and selects a color for the font*/
	SRSwatchButton	m_FontSwatch;
	//@cmember
	/* Face name for the font*/
	CString	m_strTypeFaceName;
	//@cmember
	/* Units for font size*/
	int		m_nPointsOrPixels;
	//@cmember
	/* Font size*/
	int		m_nPointSize;
	//@cmember
	/* Bold check box*/
	BOOL	m_bBoldFont;
	//@cmember
	/* Italic check box*/
	BOOL	m_bItalicFont;
	//@cmember
	/* Autosize check box*/
	BOOL	m_bAutosizeFont;
	//@cmember
	/* Underline check box*/
	BOOL	m_bUnderlineFont;
	//@cmember
	/* Strikeout check box*/
	BOOL	m_bStrikeoutFont;
	//@cmember
	/* Index of radio button for selected justification (Left, Right, or Centered)*/
	int		m_nJustification;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCFontStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCFontStyle)
	CHART_API afx_msg void OnButton2();
	CHART_API afx_msg void OnButton3();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCDisplayStyle dialog

//@topic SRGCDisplayStyle Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCDisplayStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to change to appearance of the graph in the display component
//@base public | CPropertyPage
class SRGCDisplayStyle : public CPropertyPage
{
	 CHART_DECLARE_DYNCREATE(SRGCDisplayStyle)

	//$NoJumps

// public data
public:
	//@cmember
	/* Current graph type*/
	DWORD m_dwGraphType;
	//@cmember
	/* Current axis type*/
	DWORD m_dwAxisType;
	//@cmember
	/* Current label type*/
	DWORD m_dwLabelType;

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCDisplayStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCDisplayStyle();

	// Dialog Data
	//{{AFX_DATA(SRGCDisplayStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE6 };
	//@cmember
	/* List of available axis types*/
	CComboBox	m_AxisType;
	//@cmember
	/* List of available label types*/
	CComboBox	m_LabelType;
	//@cmember
	/* List of available graph types*/
	CComboBox	m_GraphType;
	//@cmember
	/* First group in scope*/
	int		m_nFirstGroup;
	//@cmember
	/* Last group in scope*/
	int		m_nLastGroup;
	//@cmember
	/* First index in scope*/
	int		m_nFirstIndex;
	//@cmember
	/* Last index in scope*/
	int		m_nLastIndex;
	//@cmember
	/* Log scale check box*/
	BOOL	m_bLogScale;
	//@cmember
	/* Always show zero check box*/
	BOOL	m_bAlwaysShowZero;
	//@cmember
	/* Show X labels check box*/
	BOOL	m_bShowXL;
	//@cmember
	/* Show Y labels check box*/
	BOOL	m_bShowYL;
	//@cmember
	/* Show Z labels check box*/
	BOOL	m_bShowZL;
	//@cmember
	/* Show X grid lines check box*/
	BOOL	m_bShowXG;
	//@cmember
	/* Show Y grid lines check box*/
	BOOL	m_bShowYG;
	//@cmember
	/* Show Z grid lines check box*/
	BOOL	m_bShowZG;
	//@cmember
	/* Show tick marks check box*/
	BOOL	m_bShowTicks;
	//@cmember
	/* Show grid on top check box*/
	BOOL	m_bGridOrder;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCDisplayStyle)
public:
	//@cmember
	/* When leaving page, set current type DWORDS from combo box selections*/
	CHART_API virtual BOOL OnKillActive();
	//@cmember
	/* When entering page, set combo box selections from current type DWORDS*/
	CHART_API virtual BOOL OnSetActive();
	
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCDisplayStyle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCLegendEdit dialog

//@topic SRGCLegendEdit Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCLegendEdit
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to change the appearance of the legend component
//@base public | CPropertyPage
class SRGCLegendEdit : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCLegendEdit)

// Construction
public:
	//@cmember
	/* Current key type*/
	DWORD m_dwKeyStyle;
	//@cmember
	/* Current legend type*/
	DWORD m_dwLegendStyle;

	//@cmember
	/* Constructor*/
	CHART_API SRGCLegendEdit();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCLegendEdit();

// Dialog Data
	//{{AFX_DATA(SRGCLegendEdit)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE7 };
	//@cmember
	/* List of available key types*/
	CComboBox	m_KeyCombo;
	//@cmember
	/* List of available legend types*/
	CComboBox	m_LegendCombo;
	//@cmember
	/* First group in scope*/
	int		m_nFirstGroup;
	//@cmember
	/* Last group in scope*/
	int		m_nLastGroup;
	//@cmember
	/* First index in scope*/
	int		m_nFirstIndex;
	//@cmember
	/* Last index in scope*/
	int		m_nLastIndex;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCLegendEdit)
public:
	//@cmember
	/* When leaving page, set current type DWORDS from combo box selections*/
	CHART_API virtual BOOL OnKillActive();
	//@cmember
	/* When entering page, set combo box selections from current type DWORDS*/
	CHART_API virtual BOOL OnSetActive();
	
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCLegendEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGCLabelStyle dialog

//@topic SRGCLabelStyle Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGCLabelStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to change the appearance of the label component
//@base public | CPropertyPage
class SRGCLabelStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGCLabelStyle)

// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGCLabelStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGCLabelStyle();

// Dialog Data
	//{{AFX_DATA(SRGCLabelStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE8 };
	//@cmember
	/* Orientation angle*/
	double	m_dOrientation;
	//@cmember
	/* X coordinate of screen position*/
	double	m_dXPos;
	//@cmember
	/* Y coordinate of screen position*/
	double	m_dYPos;
	//@cmember
	/* Index of radio button for selected alignment and rotation location*/
	int		m_nLocationPoint;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGCLabelStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGCLabelStyle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// SRGObjStyle dialog

//@topic SRGObjStyle Class Overview |
//This class is a simple property page used in the chart explorer.


//@doc SRGCLabelStyle
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to change the appearance of the data objects in the graph
//@base public | CPropertyPage
class SRGObjStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGObjStyle)

// Construction
public:
	//@cmember
	/* TRUE if the user selected a data list from the tree, FALSE if data item was selected*/
	BOOL m_bIsList;
	//@cmember
	/* Current frame style*/
	int m_nFrameStyle;
	//@cmember
	/* Current object style*/
	int m_nObjectStyle;

	//@cmember
	/* Constructor*/
	CHART_API SRGObjStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGObjStyle();

// Dialog Data
	//{{AFX_DATA(SRGObjStyle)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE10 };
	//@cmember
	/* List of available frame styles*/
	CComboBox	m_FrameStyle;
	//@cmember
	/* List of available object styles*/
	CComboBox	m_ObjectStyle;
	//@cmember
	/* Displays and selects color for the frame*/
	SRSwatchButton	m_FrameColor;
	//@cmember
	/* Pen width used to draw the frame*/
	int		m_nFrameWidth;
	//@cmember
	/* Check to have setting apply to all data objects in the list (group)*/
	BOOL	m_bApplyToList;
	//@cmember
	/* Check to enable maximum size parameters*/
	BOOL	m_bUseMaxSize;
	//@cmember
	/* Maximum width for object*/
	double	m_dMaxWidth;
	//@cmember
	/* Maximum height for object*/
	double	m_dMaxHeight;
	//@cmember
	/* Maximum depth for object*/
	double	m_dMaxDepth;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGObjStyle)
public:
	//@cmember
	/* When leaving page, set current types from combo box selections*/
	CHART_API virtual BOOL OnKillActive();
	//@cmember
	/* When entering page, set combo box selections from current types*/
	CHART_API virtual BOOL OnSetActive();
	
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGObjStyle)
	//@cmember
	/* Handles color swatch button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton1();
	//@cmember
	/* Handles Choose Color button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton2();
	//@cmember
	/* Handles change in Use Max Dimensions check box*/
	CHART_API afx_msg void OnIdcCheck2();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// SRGInteriorEdit dialog

//@topic SRGInteriorEdit Class Overview |
//This class is a simple property page used in the chart explorer.

//@doc SRGInteriorEdit
//@class One of the property pages of Chart Explorer's editing dialog<nl>
//Allows the user to change the interior appearance of the data objects in the graph
//@base public | CPropertyPage
class SRGInteriorEdit : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(SRGInteriorEdit)

// Construction
public:
	//@cmember
	/* Current interior style*/
	int m_nInteriorStyle;
	//@cmember
	/* Constructor*/
	CHART_API SRGInteriorEdit();
	//@cmember
	/* Destructor*/
	CHART_API ~SRGInteriorEdit();

// Dialog Data
	//{{AFX_DATA(SRGInteriorEdit)
	enum { IDD = SRG_IDD_COMPONENT_PROPPAGE11 };
	//@cmember
	/* List of available interior styles*/
	CComboBox	m_InteriorStyle;
	//@cmember
	/* Displays and selects the final color for shades (vignettes)*/
	SRSwatchButton	m_ColorB;
	//@cmember
	/* Displays and selects a solid color or the initial color for shades*/
	SRSwatchButton	m_ColorA;
	//@cmember
	/* Rotation angle for angled shades*/
	double	m_dAngle;
	//@cmember
	/* Resource file name or resource image fills*/
	CString	m_strResourceName;
	//@cmember
	/* Object name*/
	CString	m_strObjectName;
	//@cmember
	/* Check to stretch an resource image to fill the area, clear to tile*/
	BOOL	m_bStretch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SRGInteriorEdit)
public:
	//@cmember
	/* When leaving page, set current style from combo box selection*/
	CHART_API virtual BOOL OnKillActive();
	//@cmember
	/* When entering page, set combo box selection from current style*/
	CHART_API virtual BOOL OnSetActive();
	
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SRGInteriorEdit)
	//@cmember
	/* Handles Choose Color 1 button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton3();
	//@cmember
	/* Handles Choose Color 2 button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton4();
	//@cmember
	/* Handles Color 1 swatch button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton1();
	//@cmember
	/* Handles Color 2 swatch button click -- displays color selection dialog*/
	CHART_API afx_msg void OnIdcButton2();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
#endif // __SRGCOMPONENTPROPERTYPAGES_H__

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

