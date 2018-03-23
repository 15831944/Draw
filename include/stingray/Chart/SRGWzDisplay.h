///////////////////////////////////////////////////////////////////////////////
// SRGWzDisplay.h
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
///////////////////////////////////////////////////////////////
#if !defined(_OCEWIZPAGE1_H_INCLUDED_)
#define _OCEWIZPAGE1_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CMainPage.h : header file
//

#include <afxcmn.h>
#include "swtchbtn.h"
#include "wizres.h"
#include <StingrayExportDefs.h>

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#define WM_CHANGECOMPONENTTYPE					(WM_USER + 7)
#define WM_NEED_REDRAW							(WM_USER + 8)
#define WM_APPLY_NOW							(WM_USER + 9)
#define WM_ADD_REMOVE_COMPONENT					(WM_USER + 10)
#define WM_CHANGEGRAPHTYPE						(WM_USER + 11)
#define WM_CHANGEAXISTYPE                       (WM_USER + 12)
#define WM_CHANGECOMPONENTNAME                  (WM_USER + 13)
#define WM_REARRANGECOMPONENT                   (WM_USER + 14)
#define WM_TRACKINGRECTCHANGED                  (WM_USER + 15)
#define WM_ADJUSTTRACKINGRECT                   (WM_USER + 16)
//$head The Chart wizard
//$level 1

// Rename VC++ DLGTEMPLATEEX and DLGITEMTEMPLATEEX
typedef struct {  
    WORD   dlgVer;
    WORD   signature; 
    DWORD  helpID; 
    DWORD  exStyle; 
	DWORD  style; 
     WORD   cDlgItems; 
	 short  x; //     
	 short  y; //     
	 short  cx; 
     short  cy; 
} SRG_DLGTEMPLATEEX; 

typedef struct { //     
	DWORD  helpID; //     
	DWORD  exStyle; 
    DWORD  style; //     
	short  x; //     
	short  y; //     
	short  cx; 
    short  cy; //     
	WORD   id;   // 
} SRG_DLGITEMTEMPLATEEX; 


struct CHART_API SRGLayoutInfo
{
	CString m_strName;
	int     m_nMeasure;
	int     m_nBorderStyle;
	int     m_nShadowStyle;
	int     m_nFillStyle;
	CRect   m_rect;
	SRGLayoutInfo(LPCTSTR lpszName, int measure, int borderStyle, int shadowStyle,
		int fillStyle, const CRect& rect)
	{
		m_strName = lpszName;
		m_nMeasure = measure;
		m_nBorderStyle = borderStyle;
		m_nShadowStyle = shadowStyle;
		m_nFillStyle = fillStyle;
		m_rect = rect;
	}
};

class CGenDialog : public CObject  
{
	CHART_DECLARE_DYNCREATE(CGenDialog)

public:
	CHART_API void SetParent(CWnd* pParent);
	CHART_API virtual BOOL DecodeResource();
	CHART_API virtual BOOL CreateGenDialog();
	CHART_API void GetFont(int& nPointSize, CString& strFaceName);
	
	CHART_API void MapDialogRectEx(RECT& rc);
	
	CHART_API BOOL ShowDialog(BOOL bShow = TRUE);
	
	CHART_API CGenDialog(UINT nTemplateID, UINT nPlaceID, CWnd* pParentWnd = NULL);
	
	CHART_API CGenDialog(LPCTSTR lpszTepmlateName, UINT nPlaceID, CWnd* pParentWnd = NULL);
	
	CHART_API CGenDialog(UINT nTemplateID, CSize offSet, CWnd* pParentWnd = NULL);
	
	CHART_API CGenDialog(LPCTSTR lpszTepmlateName, CSize offSet, CWnd* pParentWnd = NULL);
	
	CHART_API CGenDialog();
	
	CHART_API virtual ~CGenDialog();

	struct CHART_API CCtrlInfo
	{
		HWND m_hWnd;
		CString m_strClassName;
		CString m_strCaption;
		DWORD m_nHelpID;
		DWORD  m_dwStyle;
		DWORD m_dwExtendedStyle;
		CRect     m_Rect;
		UINT     m_nCtrlID;
		CCtrlInfo(DWORD dwExtStyle, CString strClassName, CString strCaption,
			DWORD dwStyle, const RECT& rc, UINT nCtrlID, DWORD helpID)
		{
			m_hWnd = NULL;
			m_dwExtendedStyle = dwExtStyle;
			m_strClassName = strClassName;
			m_strCaption = strCaption;
			m_dwStyle = dwStyle;
			m_Rect = rc;
			m_nCtrlID = nCtrlID;
			m_nHelpID = helpID;
		}
	};

protected:
	
	BOOL	m_bItalic;
	short	m_sFontWeight;
	int		m_nCtrl;
	
	CHART_API void Init(LPCTSTR lpszTemplateName, UINT nPlaceID, CSize Offset, CWnd* pParent);
	
	BOOL	m_bIsDialogEx;
	CSize	m_Offset;
	CString m_strFontFaceName;
	int		m_nFontSize;
	BOOL	m_bHasFont;
	WORD*	GotoFirstCtrlItem(const DLGTEMPLATE* pTemplate);
	LPCTSTR m_lpszTemplateName;
	UINT	m_nPlaceID;
	CWnd*	m_pParent;
	BOOL	m_bCreated;
	BOOL	m_bShown;

	CPtrList m_CtrlInfoPtrList;
};

/////////////////////////////
// AutoDuck tag block block for SRGDragListBox 
//@doc SRGStatic
//@mdata CPtrArray*   | SRGStatic | m_pLayout | Pointer to the layout information used to construct the components
// for the graph.

//@doc SRGStatic
//@mdata COLORREF  | SRGStatic | m_Colors[4] | The filling color for the 4 differnt kind of component.
// 

//@doc SRGStatic
//@mdata BOOL      | SRGStatic | m_bHasFocusRect | Semaphore indicating whether to draw a focus rectangle
// on top of the control

//@doc SRGStatic
//@mdata SRGraph*  | SRGStatic | m_pGraph | Pointer to the graph that will be drawn in this window area

// adinsert AutoDuck insertion point for SRGDragListBox 
//@doc SRGDragListBox 
//@class This is a extension class of CDragListBox class. It add some functions to make it
// easier to work with the item data. This class always add an dummy item at the end of the
// draglist to overcome the fault that CDragListBox does not allow you to drag an item to 
// the end of the list. It also added the keyboard support to move an item up and down.
class SRGDragListBox : public CDragListBox
{
// Construction
public:
	CHART_API SRGDragListBox();
// Operations
public:
	//@cmember
	/* Move item along with its data from one place to the other.*/
	CHART_API virtual void RePositionItemAndData(int nSrcIndex, int nDestIndex);
	//@cmember
	/* Replaces the data dwOld with the data dwNew. Every item */
	//with data dwOld will have its data be replaced.
	CHART_API virtual void ReplaceItemData(SEC_DWORD dwOld, SEC_DWORD dwNew);
	//@cmember
	/* Deletes the item from the DragListBox that has the specified resource ID */
	//in its associated SRGraphItemData object
	CHART_API virtual void DeleteItemByData(SEC_DWORD dwItemData);
	//@cmember
	/* Adds a string to the DragListBox and sets the 32/64-bit value associated with the item to the specified value*/
	CHART_API int AddStringData(LPCTSTR lpszString, SEC_DWORD dwItemData);
	//@cmember
	/* Searches the items in the DragListBox for one that has the specified value */
	//in its associated 32/64-bit data -- if such an item is found, it becomes the current selection
	CHART_API int SetCurSelByData(SEC_DWORD dwValue);
	//@cmember
	/* Returns the 32/64-bit value associated the currently selected item or CB_ERR*/
	CHART_API virtual		SEC_DWORD GetCurItemData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGDragListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Replace the string of an item with a new one and return TRUE if successful.*/
	CHART_API virtual BOOL ReplaceItemString(int index, LPCTSTR lpszNew);
	//@cmember
	/* Overrider of CDragListBox to handle redraw the list after dropped.*/
	CHART_API virtual void Dropped(int nSrcIndex, CPoint pt);
	CHART_API virtual ~SRGDragListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(SRGDragListBox)
	//@cmember
	/* Keyboard support of moving item in the list*/
	CHART_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// SRGStatic window
/////////////////////////////
// AutoDuck tag block block for SRGStatic 

//@doc SRGStatic
//@mdata CPtrArray*   | SRGStatic | m_pLayout | A pointer to an SRGLayoutInfo structure.

// adinsert AutoDuck insertion point for SRGStatic 
//@doc SRGStatic 
//@class This static control draws a layout chart in its window area. The m_pLayout
// veriable points to an array of a SRGLayoutInfo struct that stores what kind of 
// component to drawn, the component measurement, border style, shadow style, fill
// style(only CX_NO_FILL, CX_SOLID_FILL all other style will fall to CX_SOLID_FILL),
// and the component rectangle. It only handle 4 kind of components, i.e. SRGraphDisplay,
// SRGraphTitle, SRGraphBackground, SRGraphLegend. They are filled with the 4 different
// key color. There can be more than component of the same kind.
class SRGStatic : public CStatic
{
// Construction
public:
	CHART_API SRGStatic();

// Attributes
public:

// Operations
public:
	//@cmember
	/* Pointer to the graph that will be drawn in this window area.*/
	SRGraph* m_pGraph;
	//@cmember
	/* Pointer to the layout information used to construct the components*/
	// for the graph.
	CPtrArray*  m_pLayout;
	//@cmember
	/* The filling color for the 4 differnt kind of component.*/
	COLORREF m_Colors[4];
	//@cmember
	/* Flag that tells if a focus rectangle has been drawn on this control.*/
	BOOL     m_bHasFocusRect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Draw or erase the focus rectangle */
	CHART_API virtual void DrawFocusRect(BOOL bDraw);
	CHART_API virtual ~SRGStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(SRGStatic)
	CHART_API afx_msg void OnPaint();
	//}}AFX_MSG

	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFontStyle dialog

/////////////////////////////
// AutoDuck tag block for CFontStyle 
//@doc CFontStyle
//@mdata BOOL     | CFontStyle | m_bForPanelTitle | Flag that tells if the setting of this page
// is for the text panel body or for the text panel title

//@topic CFontStyle Class Overview |
//This dialog is a part of the chart wizard.

// adinsert AutoDuck insertion point for CFontStyle 
//@doc CFontStyle 
//@class Property page for selecting Font information to apply to currently selected component
class CFontStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CFontStyle)

// Construction
public:
	CHART_API virtual void EnableControls(BOOL bEnable);
	//@cmember
	/* Constructor*/
	CHART_API CFontStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~CFontStyle();

// Dialog Data
	//{{AFX_DATA(CFontStyle)
	enum { IDD = IDD_SRG_FONT_STYLE };
	//@cmember
	/* Store the component Type information*/
	SRGComboBox	m_Component;
	//@cmember
	/* Button which runs the color selection dialog*/
	SRSwatchButton	m_FontColor;
	//@cmember
	/* Index of selected Alignment radio button -- Left, Right, Center*/
	int		m_Alignment;
	//@cmember
	/* Face name for desired font*/
	CString	m_FontName;
	//@cmember
	/* Font size in points*/
	int		m_FontSize;
	//@cmember
	/* Flag attached to the Bold checkbox*/
	BOOL	m_bBold;
	//@cmember
	/* Flag attached to the Italic checkbox*/
	BOOL	m_bItalic;
	//@cmember
	/* Flag attached to the Strikeout checkbox*/
	BOOL	m_bStrikeout;
	//@cmember
	/* Flag attached to the Underline checkbox*/
	BOOL	m_bUnderline;
	//@cmember
	/* Flag attached to the Auto Size checkbox*/
	BOOL	m_bAutoSize;
	//@cmember
	/* Flag if the setting is for title or body text of SRGTextPanel component*/
	int    m_ForPanelTitle;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFontStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CHART_API virtual BOOL OnSetActive();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFontStyle)
	//@cmember
	/* Handles Choose Font button, runs Font Selection dialog*/
	CHART_API afx_msg void OnFontselect();
	//@cmember
	/* Handles changes to font name or size*/
	CHART_API afx_msg void OnChange();
	//@cmember
	/* Handles changes to font color*/
	CHART_API afx_msg void OnFontcolor();
	//@cmember
	/* Handles changes to other font properties*/
	CHART_API afx_msg void OnFontPropChange();
	//@cmember
	/* Handles changes to selected component*/
	CHART_API afx_msg void OnSelchangeComponent();
	CHART_API afx_msg void OnPanelPartChange();
	CHART_API afx_msg void OnChangeComponentName();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFillStyle dialog

/////////////////////////////
// AutoDuck tag block for CFillStyle 
//@doc CAdvancedPage
//@mdata SRGComboBox  | CAdvancedPage | m_ObjectList | Store all the components that
// the user can add to their graph from inside the chart wizard

//@doc CAdvancedPage
//@mdata SRGDragListBox  | CAdvancedPage | m_Component | This is a drag list box that list
// all the component inside the graph in the same order as they are in the graph component 
// list. User can reorder the component by drag and drop.

//@doc CAdvancedPage
//@mdata BOOL  | CAdvancedPage | m_bUseScroll | Flag that tells if the view area use the
// size the user passed to the wizard or the the size of actual client area

//@doc CAdvancedPage
//@mdata BOOL     | CAdvancedPage | m_bShowDragingContent | It flags if the user want 
// to display the whole content of the component or just the highlight rectangle while
// the user drag the component.

//@doc CAdvancedPage
//@mdata BOOL     | CAdvancedPage | m_bShowGrid | Flag that tells if we need to draw
// the grid dot in the view area to help user align the component.

//@doc CAdvancedPage
//@mdata BOOL     | CAdvancedPage | m_bSnapToGrid | Flag that tells if the user want to 
// align the component to grid or not while draging component

//@doc CAdvancedPage
//@mdata int      | CAdvancedPage | m_nGridWidth | The grid width in pixel in the view area

//@doc CFillStyle
//@mdata int  | CFillStyle | m_ForPanelTitle | Flag that tells if the setting of this page is 
// for the text panel body or text panel title.

// adinsert AutoDuck insertion point for CFillStyle 
//@doc CFillStyle 
//@class Property page for selecting Fill information to apply to the currently selected component
class CFillStyle : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CFillStyle)

// Construction
public:
	CHART_API virtual void EnableControls(BOOL bEnable);
	//@cmember
	/* Flag that tells if the setting of this page is for the text panel body*/
	// or for the text panel title.
	int m_ForPanelTitle;
	//@cmember
	/* Constructor*/
	CHART_API CFillStyle();
	//@cmember
	/* Destructor*/
	CHART_API ~CFillStyle();

// Dialog Data
	//{{AFX_DATA(CFillStyle)
	enum { IDD = IDD_SRG_FILL_STYLE };
	//@cmember
	/* Index of the selected item in the Component combobox*/
	SRGComboBox	m_Component;
	//@cmember
	/* Button for selecting a final color for vignetting (Horizontal, Vertical, or Angle fill styles)*/
	SRSwatchButton	m_EndColor;
	//@cmember
	/* Button for selecting a color for the current object or the initial color for vignetting*/
	SRSwatchButton	m_StartColor;
	//@cmember
	/* Index of the selected Fill Style radio button*/
	int		m_FillStyle;
	//@cmember
	/* Text string containing the name of a resource file for the image to use for fill*/
	CString	m_strResFileName;
	//@cmember
	/* Index of the selected fill mode (stretch or tile) for image fills*/
	int		m_FillMode;
	//@cmember
	/* Angle in degrees for vignetting -- used if Angle fill style is chosen*/
	int		m_nAngle;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFillStyle)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CHART_API virtual BOOL OnSetActive();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFillStyle)
	//@cmember
	/* Handles changes to fill style or image fill mode*/
	CHART_API afx_msg void OnFillChange();
	//@cmember
	/* Handles changes to final vignett color selection*/
	CHART_API afx_msg void OnEndcolor();
	//@cmember
	/* Handles changes to initial or solid color selection*/
	CHART_API  void OnStartcolor();
	//@cmember
	/* Standard property page initialization*/
	//@cmember
	/* Handles Filename button -- permits browsing for desired resource file*/
	CHART_API afx_msg void OnFilenameselect();
	//@cmember
	/* Handles changes to resource File Name or Angle edit boxes*/
	CHART_API  void OnChange();
	//@cmember
	/* Handles changes to selected component*/
	CHART_API afx_msg void OnSelchangeComponent();
	CHART_API afx_msg void OnPanelPartChange();
	CHART_API afx_msg void OnChangeComponentName();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdvancedPage dialog

/////////////////////////////
// AutoDuck tag block block for CAdvancedPage 
// adinsert AutoDuck insertion point for CAdvancedPage 
//@doc CAdvancedPage 
//@class Part of the Class wiazard dialog and property page system
class CAdvancedPage : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CAdvancedPage)

// Construction
public:
	CHART_API CAdvancedPage();
	CHART_API ~CAdvancedPage();

// Dialog Data
	//{{AFX_DATA(CAdvancedPage)
	enum { IDD = IDD_SRG_ADVANCED };
	//@cmember
	/* Place to store all the available components that the user can */
	// add to their graph from inside the chart wizard
	SRGComboBox	m_ObjectList;
	//@cmember
	/* List all the components in the graph component list.*/
	SRGDragListBox	m_Component;
	//@cmember
	/* Do we need to use the size user passed into the wizard or the size */
	// of the actual client rectangle area?
	BOOL	m_bUseScroll;
	//@cmember
	/* Flag to tell if user want to draw the content of the component or */
	// just the highlight rectange while dragging component
	BOOL    m_bShowDragingContent;
	//@cmember
	/* Flag to tell if user want to draw the alignment grid in the view area*/
	// or not
	BOOL    m_bShowGrid;
	//@cmember
	/* When user dragging component, this flag tells if the user want to */
	// align the component to grid or not
	BOOL    m_bSnapToGrid;
	//@cmember
	/* This varibale stores the alignment grid width.*/
	int     m_nGridWidth;  // In pixel
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedPage)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAdvancedPage)
	CHART_API afx_msg void OnUsescroll();
	CHART_API afx_msg void OnShowDragingContent();
	CHART_API afx_msg void OnShowGrid();
	CHART_API  void OnSnapToGrid();
	CHART_API afx_msg void OnGridWidthChange();
	CHART_API  void OnUp();
	CHART_API afx_msg void OnDown();
	CHART_API afx_msg void OnHead();
	CHART_API afx_msg void OnEnd();
	CHART_API afx_msg void OnAddcomponent();
	CHART_API afx_msg void OnDeleteComponent();
	//}}AFX_MSG
	CHART_API afx_msg LRESULT OnReArrangeComponent(WPARAM wParam, LPARAM lParam);
	
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CMainPage dialog

/////////////////////////////
// AutoDuck tag block block for CMainPage 
//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_LegendStyle | A combo box to store the avaliable legend style

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_KeyStyle | A combo box to store the available legend key style

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_AxisType | A combo box to store the available axis style for the chosen graph

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_GraphType | A combo box object to store the available graph type

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_Measurement | A combo box object to store the available measurement

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_ShadowStyle | Combo box to store the available shadow style

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_Component | Combo box that will store all the component inside the graph

//@doc CMainPage
//@mdata SRGComboBox  | CMainPage | m_BorderStyle | Combo box that stores the available border style

//@doc CMainPage
//@mdata int   | CMainPage | m_nBottom | Bottom value of component rect

//@doc CMainPage
//@mdata int   | CMainPage | m_nLeft | Left value of the component rect

//@doc CMainPage
//@mdata int   | CMainPage | m_nRight | Right value of the component rect

//@doc CMainPage
//@mdata int   | CMainPage | m_nTop | Top value of the component rect

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bShowZero | Semaphore indicating whether always show zero or not on the displaly

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bShowXGrid | Semaphore indicating if user wants to show X grid

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bShowYGrid | Semaphore indicating if user wants to show Y grid 

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bRelIndex | Semaphore indicating if user wants to use the relative index. By using
// relative index, the display can make use of the annotation of every data item

//@doc CMainPage
//@mdata int   | CMainPage | m_nMinI | Value of the minimum index of the scope

//@doc CMainPage
//@mdata int   | CMainPage | m_nMinG | Value of the minimum group of the scope

//@doc CMainPage
//@mdata int   | CMainPage | m_nMaxI | Value of the maximum index of the scope

//@doc CMainPage
//@mdata int   | CMainPage | m_nMaxG | Value of the maximum group of the scope

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bKeyFirst | If TRUE, the legend will draw the key in front of the legend label text

//@doc CMainPage
//@mdata int   | CMainPage | m_nKeySize | Value for the legend key size

//@doc CMainPage
//@mdata int   | CMainPage | m_nColumns | Number of maximu columns the legend will arrange the legend key

//@doc CMainPage
//@mdata int   | CMainPage | m_nRows | Number of maximum rows the legend will arrange the legend keys

//@doc CMainPage
//@mdata CString  | CMainPage | m_strPanelTitle | Text string for the text panel title
//@doc CMainPage
//@mdata CString  | CMainPage | m_strPanelBody | Text string for the text panel body 

//@doc CMainPage
//@mdata CString  | CMainPage | m_strTitle | Text string for the SRGraphTitle component

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bShowXTick | Semaphore indicating if user want to show X ticks

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bShowYTick | Semaphore indicating if user want to show Y ticks 

//@doc CMainPage
//@mdata BOOL  | CMainPage | m_bPanelUseTitle | Semaphore indicating if user want the text panel component to have title

//@doc CMainPage
//@mdata int   | CMainPage | m_nPanelTextOrientation | Value for the text panel orientation, there are four 
// choices: top, bottom, left and right

//@doc CMainPage
//@mdata BOOL     | CMainPage | m_bPanelBodyResize | Semaphore indicating if user want the body rectangle 
// of the text panel to be automatically resize

//@doc CMainPage
//@mdata CGenDialog  | CMainPage | m_ExtraD | A set of controls for display component

//@doc CMainPage
//@mdata CGenDialog  | CMainPage | m_ExtraL | A set of controls for Legend component

//@doc CMainPage
//@mdata CGenDialog  | CMainPage | m_ExtraT | A set of controls for title component

//@doc CMainPage
//@mdata CGenDialog  | CMainPage | m_ExtraTP | A set of controls for text panel component

// adinsert AutoDuck insertion point for CMainPage 
//@doc CMainPage 
//@class This page store all the basic configuration information for a given component.
// the user can change the component measurement, border style, shadow style, component 
// rectangle size, the data range a given component is interested in, the graph style, 
// axis style, legend style, legend key style and so on.
class CMainPage : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CMainPage)

// Construction
public:
	CHART_API virtual void EnableControls(BOOL bEnable);
	CHART_API CMainPage();
	CHART_API ~CMainPage();

// Dialog Data
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_SRG_MAIN };
	//@cmember
	/* Store the available legend style*/
	SRGComboBox	m_LegendStyle;
	//@cmember
	/* Store the available legend key style*/
	SRGComboBox	m_KeyStyle;
	//@cmember
	/* Store the available axis style for the chosen graph type*/
	SRGComboBox	m_AxisType;
	//@cmember
	/* Store the supported graph type*/
	SRGComboBox	m_GraphType;
	//@cmember
	/* Store the available measurement.*/
	SRGComboBox	m_Measurement;
	//@cmember
	/* Store the available shadow style for the component*/
	SRGComboBox	m_ShadowStyle;
	//@cmember
	/* Store the component currently inside the graph*/
	SRGComboBox	m_Component;
	//@cmember
	/* Store the available border style*/
	SRGComboBox	m_BorderStyle;
	//@cmember
	/* Component rect bottom value*/
	int		m_nBottom;
	//@cmember
	/* Component rect left value*/
	int		m_nLeft;
	//@cmember
	/* Component rect right value*/
	int		m_nRight;
	//@cmember
	/* Component rect top value*/
	int		m_nTop;
	//@cmember
	/* This semaphore indicate if user want the display to always show zero*/
	BOOL	m_bShowZero;
	//@cmember
	/* Semaphore indicating if user want to draw X grid line*/
	BOOL	m_bShowXGrid;
	//@cmember
	/* Semaphore indicating if user want to draw Y grid line*/
	BOOL	m_bShowYGrid;
	//@cmember
	/* Semaphore indicating if user want the display to use the relative index.*/
	BOOL	m_bRelIndex;
	//@cmember
	/* Value of the minimum index scope*/
	int		m_nMinI;
	//@cmember
	/* Value of the minimum group scope*/
	int		m_nMinG;
	//@cmember
	/* Value of the maximum index scope*/
	int		m_nMaxI;
	//@cmember
	/* Value of the maximum group scope*/
	int		m_nMaxG;
	//@cmember
	/* Semaphore indication if user want to draw the legend key in front of the text*/
	BOOL	m_bKeyFirst;
	//@cmember
	/* Value of the legend key size*/
	int		m_nKeySize;
	//@cmember
	/* Number of columns the legend want to use*/
	int		m_nColumns;
	//@cmember
	/* Number of rows the legend want to use*/
	int		m_nRows;
	//@cmember
	/* Store the text for the text panel title*/
	CString	m_strPanelTitle;
	//@cmember
	/* Store the text for the text panel body*/
	CString	m_strPanelBody;
	//@cmember
	/* Store the title text for the SRGraphTitle component*/
	CString	m_strTitle;
	//@cmember
	/* Semaphore indicating if user want to show X ticks*/
	BOOL	m_bShowXTick;
	//@cmember
	/* Semaphore indicating if user want to show Y ticks*/
	BOOL	m_bShowYTick;
	//@cmember
	/* Semaphore indicating if user want the text panel component use title or not*/
	BOOL	m_bPanelUseTitle;
	//@cmember
	/* Value indicating the text panel orientation*/
	int		m_nPanelTextOrientation;
	//@cmember
	/* Semaphore indicating if user want the text panel body to be resizable*/
	BOOL    m_bPanelBodyResize;
	BOOL    m_bUseMaxSize;
	int     m_nMaxObjectSize;
	BOOL    m_bObjectInsideView;
	BOOL    m_bLegendRectLock;

	//}}AFX_DATA
	//@cmember
	/* Section of controls that are specific to display component setup*/
	CGenDialog m_ExtraD;
	//@cmember
	/* Section of controls that are specific to legend component setup*/
	CGenDialog m_ExtraL;
	//@cmember
	/* Section of controls that are specific to Title component setup*/
	CGenDialog m_ExtraT;
	//@cmember
	/* Section of controls that are specific to the text panel component setup*/
	CGenDialog m_ExtraTP;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMainPage)

protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CHART_API virtual BOOL OnSetActive();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainPage)
	CHART_API virtual BOOL OnInitDialog();
	CHART_API afx_msg void OnChange();
	CHART_API afx_msg void OnSelchange();
	CHART_API afx_msg void OnSelchangeComponent();
	CHART_API afx_msg void OnSelchangeAxistype();
	CHART_API afx_msg void OnSelchangeGraphtype();
	CHART_API afx_msg void OnDestroy();
	CHART_API afx_msg void OnUsetitle();
	CHART_API afx_msg void OnChangeComponentName();
	CHART_API afx_msg void OnLegendRectLock();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////
// AutoDuck tag block block for CStandardChartPage 
//@doc CStandardChartPage
//@mdata CListBox  | CStandardChartPage | m_ChartType | Store all the standard chart type,
// the graph will automatically choose a suitable axis style

// adinsert AutoDuck insertion point for CStandardChartPage 
//@doc CStandardChartPage 
//@class This page allow user to select standard chart type from a list box.
class CStandardChartPage : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CStandardChartPage)

// Construction
public:
	CHART_API CStandardChartPage();
	CHART_API ~CStandardChartPage();

// Dialog Data
	//{{AFX_DATA(CStandardChartPage)
	enum { IDD = IDD_SRG_STANDARDCHART };
	//@cmember
	/* Stores all the standard chart type, the graph will automatically choose */
	// a suitable axis style
	CListBox	m_ChartType;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStandardChartPage)
	
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStandardChartPage)
	CHART_API afx_msg void OnSelStandardcharts();
	CHART_API afx_msg void OnPaint();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CLayoutPage dialog

/////////////////////////////
// AutoDuck tag block block for CLayoutPage 
//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image5 | The sixth layout image of one page

//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image4 | The fifth layout image of one page

//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image3 | The forth layout image of one page

//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image2 | The third layout image of one page

//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image1 | The second layout image of one page

//@doc CLayoutPage
//@mdata SRGStatic  | CLayoutPage | m_Image0 | The first layout image of one page

//@doc CLayoutPage
//@mdata SRGraph  | CLayoutPage | m_Graph | The graph used to draw layout on all the layout images

// adinsert AutoDuck insertion point for CLayoutPage 
//@doc CLayoutPage 
//@class This page display a set of preconstructed layout for the user to choose
// from. The use can view 6 layout at a time.
class CLayoutPage : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CLayoutPage)

// Construction
public:
	//@cmember
	/* This function actually draw the images on each of the six*/
	// layout image control and also update the view area by using the 
	// current selected layout.
	CHART_API virtual void DrawStatics();
	CHART_API CLayoutPage();
	CHART_API ~CLayoutPage();

// Dialog Data
	//{{AFX_DATA(CLayoutPage)
	enum { IDD = IDD_SRG_LAYOUTPAGE };
	//@cmember
	/* The sixth layout image of one page*/
	SRGStatic	m_Image5;
	//@cmember
	/* The fifth layout image of one page*/
	SRGStatic	m_Image4;
	//@cmember
	/* The fourth layout image of one page*/
	SRGStatic	m_Image3;
	//@cmember
	/* The third layout image of one page*/
	SRGStatic	m_Image2;
	//@cmember
	/* The second layout image of one page*/
	SRGStatic	m_Image1;
	//@cmember
	/* The second layout image of one page*/
	SRGStatic	m_Image0;
	//}}AFX_DATA
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLayoutPage)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLayoutPage)
	CHART_API virtual BOOL OnInitDialog();
	CHART_API afx_msg void OnLayoutprevious();
	CHART_API afx_msg void OnLayoutnext();
	CHART_API afx_msg void OnPaint();
	//}}AFX_MSG
	CHART_API afx_msg void OnLayoutClicked(UINT nID);
	CHART_API afx_msg void OnLayoutKeyClicked(UINT nID);
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
	
	//@cmember
	/* The graph used to draw layout on all the layout images*/
	SRGraph m_Graph;

	enum {m_nImageCount = 6};
};


/////////////////////////////////////////////////////////////////////////////
// CFinishPage dialog

class CFinishPage : public CPropertyPage
{
	CHART_DECLARE_DYNCREATE(CFinishPage)

// Construction
public:
	CHART_API CFinishPage();
	CHART_API ~CFinishPage();

// Dialog Data
	//{{AFX_DATA(CFinishPage)
	enum { IDD = IDD_SRG_FINISHPAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFinishPage)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFinishPage)
	CHART_API afx_msg void OnPaint();
	CHART_API afx_msg void OnAdvancedButton();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};


/////////////////////////////
// AutoDuck tag block block for SRGToolTipCtrl 

//@doc SRGToolTipCtrl
//@mdata CString  | SRGToolTipCtrl | m_strName | The name shown 

//@doc SRGToolTipCtrl
//@mdata int      | SRGToolTipCtrl | m_nMeasure | The measurement to be used

//@doc SRGToolTipCtrl
//@mdata int      | SRGToolTipCtrl | m_nBorderStyle | The border style setting.

// adinsert AutoDuck insertion point for SRGToolTipCtrl 
//@doc SRGToolTipCtrl 
//@class This class is a simple derived class of MFC CToolTipCtrl class. It overcomes the
// drawback of CToolTipCtrl class so that it works with child control inside a dialog box
// without overlay event. It adds in the automatic subclassing capability of the ToolTip 
// common control into the this class.
class SRGToolTipCtrl : public CToolTipCtrl  
{
public:
	//@cmember
	/* Used the same way as AddTool of CToolTipCtl class*/
	CHART_API virtual BOOL AddRectTool(CWnd* pWnd, LPCTSTR lpszTool, LPCRECT lpRect, SEC_UINT nIDTool);
	//@cmember
	/* Used the same way as AddTool of CToolTipCtl class*/
	CHART_API virtual BOOL AddWndTool(CWnd* pWnd, LPCTSTR lpszTool);
	//@cmember
	/* Constutor */
	CHART_API SRGToolTipCtrl();
	//@cmember
	/* Destructor */
	CHART_API virtual ~SRGToolTipCtrl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // !defined(_OCEWIZPAGE1_H_INCLUDED_)

