///////////////////////////////////////////////////////////////////////////////
// GraphVw.h
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
// @doc SRGraphView
// @module GraphVw.h | SRGraphView header file<nl>
// Also includes CSelectQuery and PageSetup and PageSetup2<nl>
//Written by Bob Powell (www.roguewave.com)
/////////////////////////////////////////////////////////////
//

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __GRAPHVW_H__
#define __GRAPHVW_H__

#include <StingrayExportDefs.h>

// GraphVw.h : interface of the SRGraphView class
//

/////////////////////////////////////////////////////////////////////////////
// PageSetup dialog

//@doc PageSetup

//$head Dialogs used by the view classes
//$level 1

// using cmember tags only for typical dialog functions

//@mdata BOOL | PageSetup | m_bUseMaxArea | Set TRUE if the page should be limited in size during printing
//@rem The PageSetup dialog allows standard sizes of display or a selection of paper sizes to be chosen and a 
//simple alignment to be specified.

//@mdata int | PageSetup | m_nValign | Vertical alignment code for print pagination
//@rem May be... Align to top of page, center, or bottom of page, or none

//@mdata int | PageSetup | m_nHalign | Horizontal alignment code for print pagination
//@rem May be... Align to left, middle, or right of page, or none

//@mdata CComboBox  | PageSetup | m_Size | Combo box for page size selection

//@mdata int | PageSetup | m_nPageSizeCode | Selected page size from combo box
//@rem The following standard page sizes are available:<nl><nl>
// 320 X 240<nl>
// 640 X 480<nl>
// 800 X 600<nl>
//1024 X 768<nl>
//A5<nl>
//A4<nl>

//adinsert

//@topic PageSetup Class Overview |
//This dialog class allows print pagination for charts. This class could be modified to provide other paper sizes.

//@class PageSetup - Dialog for setting options for placing graph on printed page
//@base public | CDialog
class PageSetup : public CDialog
{
// Construction
public:
	//@cmember
	/* Standard constructor*/
	CHART_API PageSetup(CWnd* pParent = NULL);   // standard constructor

	//@cmember
	/* Selected page size code from combo box*/
	int m_nPageSizeCode;

// Dialog Data
	//{{AFX_DATA(PageSetup)
	enum { IDD = IDD_GVW_PAGESETUP };
	//@cmember
	/* Combo box for page size selection*/
	CComboBox	m_Size;
	//@cmember
	/* Set TRUE if the page should be limited in size during printing*/
	BOOL	m_bUseMaxArea;
	//@cmember
	/* Vertical alignment code for print pagination*/
	int		m_nValign;
	//@cmember
	/* Horizontal alignment code for print pagination*/
	int		m_nHalign;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageSetup)
protected:
	//@cmember
	/* Standard dialog data excange */
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageSetup)
	//@cmember
	/* Initializes controls, calls <mf PageSetup::OnGvwCheck1>*/
	CHART_API virtual BOOL OnInitDialog();
	//@cmember
	/* Retrieves user selections from controls and closes the dialog*/
	CHART_API virtual void OnOK();
	//@cmember
	/* Enables or disables alignment radio buttons according to state of Use Max Size check box*/
	CHART_API afx_msg void OnGvwCheck1();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// PageSetup2 dialog

//@doc PageSetup2

//$head Dialogs used by the view classes
//$level 1

// using cmember tags only for typical dialog functions

//@mdata int | PageSetup2 | m_nValign | Vertical alignment code for print pagination
//@rem May be... Align to top of page, center, bottom of page or Custom Margin= using a user specified margin

//@mdata int | PageSetup2 | m_nHalign | Horizontal alignment code for print pagination
//@rem May be... Align to left, middle, right of page or Custom Margin = using a user specified margin

//@mdata int | PageSetup2 | m_nSizeChoice | Selected chart sizing option
// Full Page<nl> 
// Full Width/Half Height<nl> 
// Half Width/Full Height<nl> 
// Custom -- using user specified dimensions in m_dXSize and m_dYSize

//@mdata double | PageSetup2 | m_dXOffset | Horizontal position of the top-left corner of the chart relative to the printed page for the Custom margin option

//@mdata double | PageSetup2 | m_dXOffsetInUnit | Dialog variable associated with the displayed Custom horizontal position edit box -- internal use only

//@mdata double | PageSetup2 | m_dXSize | Horizontal size of the printed chart in inches for the Custom Size option

//@mdata double	| PageSetup2 | m_dXSizeInUnit | Dialog variable associated with the displayed horizontal size edit box -- internal use only

//@mdata double | PageSetup2 | m_dYOffset | Vertical position of the top-left corner of the chart relative to the printed page for the Custom margin option

//@mdata double	| PageSetup2 | m_dYOffsetInUnit | Dialog variable associated with the displayed Custom vertical position edit box -- internal use only

//@mdata double | PageSetup2 | m_dYSize | Vertical size of the printed chart in inches for the Custom Size option

//@mdata double	| PageSetup2 | m_dYSizeInUnit | Dialog variable associated with the displayed vertical size edit box -- internal use only

//@mdata int | PageSetup2 | m_nUnitChoice | Dialog variable associated with the Units (inches or centimeters) radio buttons

//adinsert

//@topic PageSetup2 Class Overview |
//This dialog class allows print pagination for charts. 
//PageSetup2 is a new alternative to PageSetup.
//It offers more flexibility by allowing the end-user to specify the size of the chart as well as
//Its position/alignment on the printed page.
//This class could be modified to provide other paper sizes.

//@class PageSetup2 - Dialog for setting options for placing the graph on printed page
//@base public | CDialog
class PageSetup2 : public CDialog
{
// Construction
public:
	//@cmember
	/* Standard constructor*/
	CHART_API PageSetup2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageSetup2)
	enum { IDD = IDD_GVW_PAGESETUP2 };
	//@cmember
	/* Dialog variable associated with the Units (inches or centimeters) radio buttons*/
	int		m_nUnitChoice;
	//@cmember
	/* Dialog variable associated with the Vertical alignment (Top, Center, Bottom, Custom Margin) radio buttons*/
	int		m_nValign;
	//@cmember
	/* Dialog variable associated with the Horizontal alignment (Left, Middle, Right, Custom Margin) radio buttons*/
	int		m_nHalign;
	//@cmember
	/* Dialog variable associated with the displayed Custom horizontal position edit box -- internal use only*/
	double	m_dXOffsetInUnit;
	//@cmember
	/* Dialog variable associated with the displayed Custom vertical position edit box -- internal use only*/
	double	m_dYOffsetInUnit;
	//@cmember
	/* Dialog variable associated with the displayed horizontal size edit box -- internal use only*/
	double	m_dXSizeInUnit;
	//@cmember
	/* Dialog variable associated with the displayed vertical size edit box -- internal use only*/
	double	m_dYSizeInUnit;
	//@cmember
	/* Dialog variable associated with the Size options or radio buttons*/
	int		m_nSizeChoice;
	//}}AFX_DATA

	//@cmember
	/* Horizontal position of the top-left corner of the chart relative to the printed page for the Custom margin option*/
	double m_dXOffset;
	//@cmember
	/* Vertical position of the top-left corner of the chart relative to the printed page for the Custom margin option*/
	double m_dYOffset;
	//@cmember
	/* Horizontal size of the printed chart in inches for the Custom Size option*/
	double m_dXSize;
	//@cmember
	/* Vertical size of the printed chart in inches for the Custom Size option*/
	double m_dYSize;
	int m_nUnit;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageSetup2)
protected:
	//@cmember
	/* Standard dialog data excange */
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageSetup2)
	//@cmember
	/* Handles click on the Centimeters radio button*/
	CHART_API afx_msg void OnGvwCm();
	//@cmember
	/* Handles click on the Inches radio button*/
	CHART_API afx_msg void OnGvwInches();
	//@cmember
	/* Handles click on the Size selecting radio buttons except Custom Size*/
	CHART_API afx_msg void OnGvwSizeStandard();
	//@cmember
	/* Handles click on the Custom Size radio button*/
	CHART_API afx_msg void OnGvwSizeCustom();
	//@cmember
	/* Handles click on the Top, Center, and Bottom Vertical Position radio buttons*/
	CHART_API afx_msg void OnGvwYStandard();
	//@cmember
	/* Handles click on the Custom Vertical Margin radio button*/
	CHART_API afx_msg void OnGvwYCustom();
	//@cmember
	/* Handles click on the Left, Middle, and Right Horizontal Position radio buttons*/
	CHART_API afx_msg void OnGvwXStandard();
	//@cmember
	/* Handles click on the Custom Horizontal Margin radio button*/
	CHART_API afx_msg void OnGvwXCustom();
	//@cmember
	/* Initializes the dialog, converting units and disabling edit boxes as appropriate*/
	CHART_API virtual BOOL OnInitDialog();
	//@cmember
	/* Retrieves data from the dialog converting units if necessary*/
	CHART_API virtual void OnOK();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSelectQuery dialog

//@doc CSelectQuery 

// using cmember tags only for this simple dialog class

//@doc CSelectQuery
//@mdata int   | CSelectQuery | m_Selection | Holds the radiobutton results

//@mdata void | CSelectQuery | CSelectQuery | Constructor.

//@doc CSelectQuery
//@mfunc virtual void  | CSelectQuery | DoDataExchange | Standard dialog data exchange. 

//adinsert

//$head Miscellaneous dialog classes
//$level 1

//@doc CSelectQuery 
//@class CSelectQuery - dialog displayed when user selects data items including both groups and indices 
//@base public | CDialog
class CSelectQuery: public CDialog
{
// Construction
public:
	//@cmember
	/* Standard constructor*/
	CHART_API CSelectQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectQuery)
	enum { IDD = IDD_GVW_SELECTQUERY1 };
	//@cmember
	/* Radio button index specifying type of data items desired*/
	int		m_Selection;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectQuery)
protected:
	//@cmember
	/* Standard dialog data exchange */
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectQuery)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

#define MOUSE_TIMER_EVENT 3860

//$head View classes
//$level 1

/////////////////////////////////////////////
//@doc SRGraphView

// data members

//@mdata BOOL | SRGraphView | m_bUseMaxArea | TRUE if the page should be limited in size during printing
//@rem The PageSetup or PageSetup2 dialog allows standard sizes of display or a selection of paper sizes to be chosen and a 
//simple alignment to be specified.

//@mdata int | SRGraphView | m_nValign | Vertical alignment code for print pagination
//@rem Align to top of page(0), center(1), or bottom(2) of page, or none
//@devnote The PageSetup2 dialog offers a Custom option (3) with a margin specified by m_dYOffset

//@mdata int | SRGraphView | m_nHalign | Horizontal alignment code for print pagination
//@rem Align to left(0), middle(1), or right(2) of page, or none
//@devnote The PageSetup2 dialog offers a Custom option (3) with a margin specified by m_dXOffset

//@mdata int | SRGraphView | m_nPageSizeCode | Selected page size from the PageSetup or PageSetup2 dialog
//The PageSetup dialog offers the following option:<nl>
// 0		320x240 pixels<nl>
// 1		640x480 pixels<nl>
// 2		800x600 pixels<nl>
// 3		1024x768 pixels<nl>
// 4		A4 Portrait <nl>
// 5		A4 Landscape <nl>
// 6		A5 Portrait<nl>
// 7		A5 Landscape<nl>
// 8		Letter Portrait<nl> 
// 9		Letter Landscape<nl> 
//<nl> 
//The PageSetup2 dialog offers more flexible options:<nl> 
//10		Full Page<nl> 
//11		Half Height/Full Width<nl> 
//12		Full Width/Half Height<nl> 
//13		Custom -- with user specified horizontal and vertical dimension -- m_dXSize and m_dYSize

//@mdata int | SRGraphView | m_nPrintUnit | Unit for displaying dimensions in PageSetup2 dialog: 0-cm, 1-inch.
//@mdata double | SRGraphView | m_dXOffset | Horizontal margin for printing set by PageSetup2 dialog
//@mdata double | SRGraphView | m_dYOffset | Vertical margin for printing set by PageSetup2 dialog
//@mdata double | SRGraphView | m_dXSize | Horizontal size of printed chart set by PageSetup2 dialog
//@mdata double | SRGraphView | m_dYSize | Vertical size of printed chart set by PageSetup2 dialog

//@mdata CRect  | SRGraphView | m_OldAreaRect | Area of the chart before pagination

//@mdata BOOL  | SRGraphView | m_bPreserveArea | When TRUE the old chart area should be restored after print preview or printing is done

//@mdata DWORD  | SRGraphView | m_dwOldAlignment | Retains the old alignment codes during printing

//@mdata SEC_UINT | SRGraphView | m_TimerIdent | Mouse timer identifier

//@mdata SRGraphTip | SRGraphView | m_GraphTip | The single graph tip object

//@mdata int | SRGraphView | m_nUnzoomMinIndex | The graph's original minimum index (used for unzooming data)

//@mdata int | SRGraphView | m_nUnzoomMaxIndex |  The graph's original maximum index (used for unzooming data)

//@mdata int | SRGraphView | m_nUnzoomMinGroup | The graph's original minimum group (used for unzooming data)

//@mdata int | SRGraphView | m_nUnzoomMaxGroup | The graph's original maximum group (used for unzooming data)

//@mdata SRGraphComponent * | SRGraphView | m_pZoomedDisplay |	Pointer to the display which has been zoomed (used to restore the original state)

//@mdata BOOL | SRGraphView | m_bZoomed | TRUE if the graph has been zoomed (used to activate the unzoom menu command via the command update interface)

//@mdata BOOL | SRGraphView | m_bShowingTip | TRUE if a graph tip is currently on display -- a call for a new tip will recycle the old one

//@mdata CPoint | SRGraphView | m_SelectionPointA | First point in a selection area

//@mdata CPoint | SRGraphView | m_SelectionPointB | Last point in a selection area

//@mdata BOOL | SRGraphView | m_bSelecting | TRUE if the graph is in selection box mode

//@mdata BOOL | SRGraphView | m_bInFeedback | TRUE if the mouse point was clicked inside a feedback area (data dragging will commence)

//@mdata int | SRGraphView | m_nDragIndex | Index of the data item being dragged

//@mdata int | SRGraphView | m_nDragGroup | Group of the data item being dragged

//@mdata BOOL | SRGraphView | m_bDragging | TRUE if dragging is in progress

//@mdata CPoint | SRGraphView | m_MousePoint | Stored mouse position (used to ascertain if the mouse has remained still for the requisite 1.5 seconds)

//@mdata BOOL | SRGraphView | m_bMouseTimerIsRunning | TRUE if the mouse is considered to be "still" and the timeout is waiting to fire

//@mdata BOOL  | SRGraphView | m_bZoomable | Flag to enable or disable the zooming process -- TRUE to enable chart zooming

//@mdata BOOL  | SRGraphView | m_bDragable | Flag which specifies whether data may be dragged

//@mdata BOOL  | SRGraphView | m_bHasDocument | Flag to signify whether this view has a document

//@mdata CObStack  | SRGraphView | m_ZoomStack | First-in last-out stack for storing and recovering zoomed states

//@mdata CPalette  | SRGraphView | m_Palette | Color palette to use in drawing the graph

//@mdata SRGDisplayBase* | SRGraphView | m_pDragDisplay | Pointer to the store the graph component.

// inline functions

//@mfunc void  | SRGraphView | SetDragable | Sets the m_Draggable flag which allows data to be dragged
//@parm BOOL  | v | TRUE to allow dragging, FALSE to disable dragging

//@mfunc BOOL  | SRGraphView | GetDragable | Returns the m_Draggable flag -- TRUE if data may be dragged

//@mfunc void  | SRGraphView | SetZoomable | Call to set or reset the m_bZoomable flag -- TRUE if zooming is allowed 
//@parm BOOL  | v | TRUE to enable zooming, FALSE to disable

//@mfunc BOOL  | SRGraphView | GetZoomable | Returns the zoomable flag -- TRUE if the chart may be zoomed

//@mfunc void  | SRGraphView | SetHasDocument | Sets m_bHasDocument flag to indicate that this view has a document 
//@parm BOOL  | v | TRUE if view has a document, FALSE if it does not 

//@mfunc BOOL  | SRGraphView | GetHasDocument | Returns the m_bHasDocument flag -- TRUE if this view has a document 


//@doc SRGraphView
//@mdata BOOL  | SRGraphView | m_bDragTips | This will be set to TRUE if drag tips are enabled. Drag tips are numerical chart tips that change as data is dragged on the display.

//@doc SRGraphView
//@mfunc virtual void  | SRGraphView | SetDragTips | Sets the semaphore that enables or disables drag tips.
//@parm BOOL  | v | TRUE to enable FALSE to disable


//@doc SRGraphView
//@mfunc virtual BOOL  | SRGraphView | GetDragTips | Returns TRUE if drag tips are enabled, FALSE if disabled.

//@doc SRGraphView
//@mfunc virtual void | SRGraphView | AssertValid | Standard debug code

//@doc SRGraphView
//@mfunc virtual void | SRGraphView | Dump | Standard debug code
//@parm CDumpContext& | dc | The dump device context

//@doc SRGraphView
//@mfunc CGraphDoc * | SRGraphView | GetDocument | Returns the document for this view

//@doc SRGraphView
//@mfunc virtual void | SRGraphView | OnPrepareDC | Sets window to viewport mapping
//@parm CDC * |  pDC | The pointer to the device context
//@parm CPrintInfo * | pInfo | The pointer to the print information (default set to NULL)

//@doc SRGraphView
//@mfunc void | SRGraphView | SetUseMaxArea | Enables or disables the use of the maximum size rectangle
//@parm BOOL | b | "true" to enable the use of the maximum size of the rectangle, "false" to disable the use of the maximum rectangle

//@doc SRGraphView
//@mdata int | SRGraphView | m_nPageCountX | Number of pages required to print chart in horizontal direction - internal

//@doc SRGraphView
//@mdata int | SRGraphView | m_nPageCountY | Number of pages required to print chart in vertical direction - internal

//adinsert

//@doc SRGraphView
//@class Specialized view class for the display and management of SRGraph objects<nl>
//This CView-based class simply adds graph feedback, data dragging, and data zooming 
//to your graph and chart applications.
//@base public | CView
//@devnote The classes for PageSetup, PageSetup2, and CSelectQuery are also in the files of this class.
class SRGraphView : public CView
{
protected:
	//@cmember
	/* Set TRUE if the page should be limited in size during printing*/
	BOOL m_bUseMaxArea;
	//@cmember
	/* Vertical alignment code for print pagination*/
	int m_nValign;
	//@cmember
	/* Horizontal alignment code for print pagination*/
	int m_nHalign;
	//@cmember
	/* Code for selected page sizes*/
	int m_nPageSizeCode;
	
	//@cmember
	/* Unit for dimensions in PageSetup2 dialog: 0-cm, 1-inch*/
	int m_nPrintUnit;
	//@cmember
	/* Horizontal margin for printing*/
	double m_dXOffset;
	//@cmember
	/* Vertical margin for printing*/
	double m_dYOffset;
	//@cmember
	/* Horizontal chart size for printing*/
	double m_dXSize;
	//@cmember
	/* Vertical chart size for printing*/
	double m_dYSize;
	//@cmember
	/* Number of pages required to print chart in horizontal direction - internal*/
	int m_nPageCountX;
	//@cmember
	/* Number of pages required to print chart in vertical direction - internal*/
	int m_nPageCountY;

	//@cmember
	/* Mouse timer identifier*/
	SEC_UINT m_TimerIdent;
	//@cmember
	/* The single graph tip object*/
 	SRGraphTip m_GraphTip;
	//@cmember
	/* Original minimum index (used for unzooming data)*/
	int m_nUnzoomMinIndex;
	//@cmember
	/* Original maximum index (used for unzooming data)*/
	int m_nUnzoomMaxIndex;
	//@cmember
	/* Original minimum group (used for unzooming data)*/
	int m_nUnzoomMinGroup;
	//@cmember
	/* Original maximum group (used for unzooming data)*/
	int m_nUnzoomMaxGroup;
	//@cmember
	/* Pointer to the display which has been zoomed (used in restoration of the original state)*/
	SRGraphComponent * m_pZoomedDisplay;
	//@cmember
	/* TRUE if the graph has been zoomed (used to activate the unzoom menu command via the command update interface)*/
	BOOL m_bZoomed;
	//@cmember
	/* TRUE if a graph tip is currently on display*/
	BOOL m_bShowingTip;
	//@cmember
	/* First point in a selection area*/
	CPoint m_SelectionPointA;
	//@cmember
	/* Last point in a selection area*/
	CPoint m_SelectionPointB;
	//@cmember
	/* TRUE if the graph is in selection box mode*/
	BOOL m_bSelecting;
	//@cmember
	/* TRUE if the mouse point was clicked inside a feedback area (data dragging will commence)*/
	BOOL m_bInFeedback;
	//@cmember
	/* Index of the data item being dragged*/
	int m_nDragIndex;
	//@cmember
	/* Group of the data item being dragged*/
	int m_nDragGroup;
	//@cmember
	/* TRUE if dragging is in progress*/
	BOOL m_bDragging;
	//@cmember
	/* Stored mouse position (used to ascertain if the mouse has rested still for the requisite 1.5 seconds)*/
	CPoint m_MousePoint;
	//@cmember
	/* TRUE if the mouse is considered to be "still" and the timeout is waiting to fire*/
	BOOL m_bMouseTimerIsRunning;
	//@cmember
	/* Flag to define the charts ability to be zoomed -- TRUE enables zooming*/
	BOOL m_bZoomable;
	//@cmember
	/* Flag which specifies whether data may be dragged*/
	BOOL m_bDragable;
	//@cmember
	/* Flag to signify whether this view has a document*/
	BOOL m_bHasDocument;
public:

	//@cmember
	/* Pointer to store the graph component */
	SRGDisplayBase * m_pDragDisplay;

public:

	//@cmember
	/* Constructor*/
	CHART_API SRGraphView(); // moved to the public section as an experiment...

	CHART_DECLARE_DYNCREATE(SRGraphView)

// Attributes
public:
	//@cmember
	/* Set or resets the m_bDragTips flag*/
	CHART_API virtual void SetDragTips(BOOL v);
	//@cmember
	/* Return the m_bDragTips flag*/
	CHART_API virtual BOOL GetDragTips();
	//@cmember
	/* Sets or resets the m_bDragable flag*/
	CHART_API virtual void SetDragable(BOOL v);
	//@cmember
	/* Returns the m_bDragable flag*/
	CHART_API virtual BOOL GetDragable();
	//@cmember
	/* Sets or resets the flag signifying whether this chart is able to zoom*/
	CHART_API virtual void SetZoomable(BOOL v);
	//@cmember
	/* Returns the zoom enable flag*/
	CHART_API virtual BOOL GetZoomable();
	//@cmember
	/* Draws a selecting box*/
	CHART_API virtual void DrawSelection(CPoint point);
	//@cmember
	/* Override this function to draw your own selection styles*/
	CHART_API virtual void DrawCustomSelection(CPoint point);
	//@cmember
	/* Handles data dragging and selection box display*/
	CHART_API virtual void MouseDrag(int nFlags,CPoint point);
	//@cmember
	/* Returns the document for this view*/
	CHART_API CGraphDoc* GetDocument();
	//@cmember
	/* Sets or resets the m_bHasDocument flag*/
	CHART_API virtual void SetHasDocument(BOOL v);
	//@cmember
	/* Returns the m_bHasDocument flag*/
	CHART_API virtual BOOL GetHasDocument();
	//@cmember
	/* Enables or disables the use of the maximum size rectangle*/
	inline void SetUseMaxArea(BOOL b){m_bUseMaxArea=b;}

public:
	//@cmember
	/* Draws the graph*/
	CHART_API virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//@cmember
	/* Sets window to viewport mapping*/
	CHART_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	
protected:
	
#ifndef _OCCE_
	//@cmember
	/* Prepares the print job*/
	CHART_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//@cmember
	/* Performs print pagination and outputs the graph to the printer*/
	CHART_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	/* Completes printing and terminates print mode*/
	CHART_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
#endif //_OCCE_
	
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Render the chart into the passed bitmap*/
	CHART_API virtual void DrawToBitmap(CDC* pDC, CBitmap& bmp);
	//@cmember
	/*  Returns a SRGraphPosition object in response to a mouse event -- override */
	CHART_API virtual SRGraphPosition * GetPosition(SRGraph *pGraph,CPoint point);
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphView();
#ifdef _DEBUG
	//@cmember
	/* Standard debug code */
	CHART_API virtual void AssertValid() const;
	//@cmember
	/* Standard debug code */
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//@cmember
	/* Returns a pointer to the graph object which this view displays and interfaces to*/
	CHART_API virtual SRGraph * GetGraph();
	//@cmember
	/* Displays a feedback chart tip -- override*/
	CHART_API virtual void ShowFeedback(SRGraphFeedback *pFeedback);
	//@cmember
	/* Saves current view as a DIB file. */
	CHART_API virtual void SaveToFileAsDib(LPCTSTR lpszFileName);
	//@cmember
	/* Saves the current view's image as a JPEG */
	CHART_API virtual void SaveToFileAsJpeg(LPCTSTR lpszFileName);
	//@cmember
	/* Helper function that implements the ZoomOut and ZoomOutAll features */
	CHART_API virtual void GraphZoomout(BOOL bAlltheWay);

protected:
	//@cmember
	/* Semaphore for the draging tips*/
	BOOL m_bDragTips;
	//@cmember
	/* First-in last-out stack of zoomed states*/
	CObStack m_ZoomStack;

#ifndef _OCCE_
	//@cmember
	/* Color palette*/
	CPalette m_Palette;
#endif //_OCCE_
	
	//@cmember
	/* Retains the old alignment codes during printing*/
	DWORD m_dwOldAlignment;
	//@cmember
	/* Retains the old alignment rectangle during printing*/
	CRect m_OldAreaRect;
	//@cmember
	/* Set TRUE if the area should be restored after printing*/
	BOOL m_bPreserveArea;


// Generated message map functions
	//{{AFX_MSG(SRGraphView)
	//@cmember
	/* Does nothing*/
	CHART_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//@cmember
	/* Handles mouse movement and chart tip triggering*/
	CHART_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	/* Handles mouse button press*/
	CHART_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//@cmember
	/* Handles mouse button release*/
	CHART_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//@cmember
	/* Checks to see if a chart tip is needed*/
	CHART_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//@cmember
	/* Copies the image to the clipboard*/
	CHART_API afx_msg void OnEditCopy();
	//@cmember
	/* Returns zoomed graph to previous size*/
	CHART_API afx_msg void OnGraphZoomout();
	//@cmember
	/* Activates or deactivates the zoom out button and menu items*/
	CHART_API afx_msg void OnUpdateGraphZoomout(CCmdUI* pCmdUI);
	//@cmember
	/* Returns zoomed graph to normal, unzoomed state*/
	CHART_API afx_msg void OnGraphZoomoutAll();
	//@cmember
	/* Activates or deactivates the Zoom Out All button and menu items*/
	CHART_API afx_msg void OnUpdateGraphZoomoutAll(CCmdUI* pCmdUI);
#ifndef _OCCE_
	//@cmember
	/* Runs a simple pagination dialog*/
	CHART_API afx_msg void OnGraphPagesetup();
	/* Runs a different pagination dialog*/
	CHART_API afx_msg void OnGraphPagesetup2();
#endif //_OCCE_
	//@cmember
	/* Edits a graph using the Graph Explorer*/
	CHART_API afx_msg void OnGraphEdit();
	//@cmember
	/* Message handler for the Save As DIB menu item */
	CHART_API afx_msg void OnSaveAsDib();
	//@cmember
	/* Message handler for the Save As JPEG menu item */
	CHART_API afx_msg void OnSaveAsJpeg();
	//@cmember
	/* Invokes the chart wizard */
	CHART_API afx_msg void OnGraphWizard();
	//@cmember
	/* Creation initialization*/
	CHART_API afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//@cmember
	/* Palette management*/
	CHART_API afx_msg BOOL OnQueryNewPalette();
	//@cmember
	/* Palette management */
	CHART_API afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in GraphView.cpp
inline CGraphDoc* SRGraphView::GetDocument()
   { return (CGraphDoc*)m_pDocument; }
#endif

#endif // __GRAPHVW_H__

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

/////////////////////////////////////////////////////////////////////////////

