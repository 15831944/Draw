///////////////////////////////////////////////////////////////////////////////
// SRGScrollView.h
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
//@doc SRGScrollView
//@module SRGScrollView.h | SRGScrollView header file<nl>
//Written by Bob Powell (www.roguewave.com)

////////////////////////////////////////////////////////////////
//
// SRGScrollView.h : interface of the SRGScrollView class
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __GRAPHSCROLLVW_H__
#define __GRAPHSCROLLVW_H__

#include <StingrayExportDefs.h>

//$head View classes
//$level 1

/////////////////////////////////////////////////////////////////////////////
//@doc SRGScrollView 

//@mdata BOOL  | SRGScrollView | m_bDragable | Flag which specifies whether data may be dragged

//@mdata BOOL  | SRGScrollView | m_bZoomable | Flag to define the charts ability to be zoomed -- TRUE enables zooming

//@mdata SRGraphTip  | SRGScrollView | m_GraphTip | The chart tip object for this view

//@mdata BOOL  | SRGScrollView | m_bSelecting | TRUE when a selection is in progress

//@mdata BOOL  | SRGScrollView | m_bDragging | TRUE when chart data is being dragged

//@mdata BOOL  | SRGScrollView | m_bInFeedback | TRUE when the mouse point is in a feedback area

//@mdata BOOL  | SRGScrollView | m_bShowingTip | TRUE when a chart tip is displayed

//@mdata BOOL  | SRGScrollView | m_bZoomed | TRUE when the chart is zoomed

//@mdata SRGraphComponent*  | SRGScrollView | m_pZoomedDisplay | Pointer to the zoomed display

//@mdata SRGDisplayBase* | SRGScrollView | m_pDragDisplay | Pointer to the store the graph component.

//@mdata BOOL  | SRGScrollView | m_bMouseTimerIsRunning | TRUE when the mouse timer is running<nl>
//When the timer expires, a check is made to see if the mouse point is in a feedback area. 
//If it is, then a graph tip may be displayed.

//@mdata BOOL  | SRGScrollView | m_bUseMaxArea | TRUE when the area of the chart is set 
//at print time or during print preview
//@rem The PageSetup or PageSetup2 dialog allows standard sizes of display or a selection of paper sizes to be chosen and a 
//simple alignment to be specified.

//@mdata int  | SRGScrollView | m_nValign | Vertical alignment code for pagination
//@rem Align to top of page(0), center(1), or bottom(2) of page, or none
//@devnote The PageSetup2 dialog offers a Custom option (3) with a margin specified by m_dYOffset

//@mdata int  | SRGScrollView | m_nHalign | Horizontal alignment code for pagination
//@rem Align to left(0), middle(1), or right(2) of page, or none
//@devnote The PageSetup2 dialog offers a Custom option (3) with a margin specified by m_dXOffset

//@mdata int  | SRGScrollView | m_nPageSizeCode | Page size code used in print pagination<nl>
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

//@mdata int | SRGScrollView | m_nPrintUnit | Unit for displaying dimensions in PageSetup2 dialog: 0-cm, 1-inch.
//@mdata double | SRGScrollView | m_dXOffset | Horizontal margin for printing set by PageSetup2 dialog
//@mdata double | SRGScrollView | m_dYOffset | Vertical margin for printing set by PageSetup2 dialog
//@mdata double | SRGScrollView | m_dXSize | Horizontal size of printed chart set by PageSetup2 dialog
//@mdata double | SRGScrollView | m_dYSize | Vertical size of printed chart set by PageSetup2 dialog

//@mdata int  | SRGScrollView | m_nDragGroup | Group in which the dragged item is stored

//@mdata int  | SRGScrollView | m_nDragIndex | Index of the item being dragged

//@mdata int  | SRGScrollView | m_nUnzoomMinGroup | Minimum group of the un-zoomed display -- used to restore the unzoomed state

//@mdata int  | SRGScrollView | m_nUnzoomMaxGroup | Maximum group of the un-zoomed display -- used to restore the unzoomed state
//@mdata int  | SRGScrollView | m_nUnzoomMinIndex | Minimum index of the un-zoomed display -- used to restore the unzoomed state

//@mdata int  | SRGScrollView | m_nUnzoomMaxIndex | Maximum index of the un-zoomed display -- used to restore the unzoomed state

//@mdata CPoint  | SRGScrollView | m_SelectionPointA | First screen point used in defining the selection area

//@mdata CPoint  | SRGScrollView | m_SelectionPointB | Second screen point used in defining the selection area

//@mdata CPoint  | SRGScrollView | m_MousePoint | Current mouse point

//@mdata SEC_UINT  | SRGScrollView | m_TimerIdent | Identifier of the mouse feedback timer

//@mdata CRect  | SRGScrollView | m_OldAreaRect | Area of the chart before pagination

//@mdata BOOL  | SRGScrollView | m_bPreserveArea | When TRUE the old chart area should be restored after print preview or printing is done

//@mdata DWORD  | SRGScrollView | m_dwOldAlignment | Retains the old alignment codes during printing

//@mfunc virtual void  | SRGScrollView | SetDragable | Sets or resets the dragable flag
//@parm BOOL  | v | TRUE to enable data dragging

//@mfunc virtual BOOL  | SRGScrollView | GetDragable |  Returns the dragable flag 

//@mfunc virtual void  | SRGScrollView | SetZoomable | Sets the flag signifying whether this chart is able to zoom
//@parm BOOL  | v | TRUE to enable zooming 

//@mfunc virtual BOOL  | SRGScrollView | GetZoomable | Gets the zoom enable flag

//@mfunc void  | SRGScrollView | SetHasDocument | Sets m_bHasDocument flag to indicate that this view has a document 
//@parm BOOL  | v | TRUE if view has a document, FALSE if it does not 

//@mfunc BOOL  | SRGScrollView | GetHasDocument | Returns the m_bHasDocument flag -- TRUE if this view has a document 

//@mdata CPalette  | SRGScrollView | m_Palette | Our color palette

//@doc SRGScrollView
//@mdata BOOL  | SRGScrollView | m_bDragTips | TRUE if drag tips are enabled

//@doc SRGScrollView
//@mdata BOOL  | SRGScrollView | m_bHasDocument | TRUE if this view uses or needs a document


//@doc SRGScrollView
//@mdata CObStack  | SRGScrollView | m_ZoomStack | The FILO stack that contains the zoom levels

//@doc SRGScrollView
//@mfunc virtual SRGraph * | SRGScrollView | GetGraph | Returns a pointer to the graph object

//@doc SRGScrollView
//@mfunc virtual BOOL | SRGScrollView | GetDragTips | Returns the drag-tips flag. If this is TRUE then drag-tips are enabled. Otherwise FALSE.

//@doc SRGScrollView
//@mfunc afx_msg void | SRGScrollView | OnGraphWizard | Message handler for the Graph Wizard menu item

//@doc SRGScrollView
//@mfunc virtual void | SRGScrollView | OnPrepareDC | Sets window to viewport mapping
//@parm CDC * | pDC | Pointer to the device context
//@parm CPrintInfo * | pInfo | Pointer to the print information (default set to NULL)

//@doc SRGScrollView
//@mfunc afx_msg void | SRGScrollView | OnSaveAsDib | Message handler for the Save As DIB menu item

//@doc SRGScrollView
//@mfunc afx_msg void | SRGScrollView | OnSaveAsJpeg | Message handler for the Save As JPEG menu item

//@doc SRGScrollView
//@mfunc virtual void | SRGScrollView | SetDragTips | Turns drag-tips on (TRUE) or off (FALSE)
//@parm BOOL | v | "true" to turn drag-tips on, "false" to turn drag-tips off

//@doc SRGScrollView
//@mfunc void | SRGScrollView | SetUseMaxArea | Enables or disables the use of the maximum size rectangle
//@parm BOOL | b | "true" to enable maximum size of rectangle, "false" to disable maximum size of rectangle

//@doc SRGScrollView
//@mdata int | SRGScrollView | m_nPageCountY | Number of pages required to print chart in vertical direction - internal

//adinsert

//@topic SRGScrollView Class Overview |
//This class provides all the functionality of an SRGraphView and adds the scrolling capabilities of CScrollView too.


//@doc SRGScrollView 
//@class This class provides a CScrollView-based alternative to the <c SRGraphView> class.
//@base public | CScrollView
class SRGScrollView : public CScrollView
{
protected: // create from serialization only
	
	CHART_DECLARE_DYNCREATE(SRGScrollView)
	
	//@cmember
	/* Constructor*/
	CHART_API SRGScrollView();
	

	//@cmember
	/* Flag which specifies whether data may be dragged*/
	BOOL m_bDragable;
	//@cmember
	/* Called when items are being dragged*/
	CHART_API virtual void MouseDrag(int nFlags,CPoint point);
	//@cmember
	/* Draws the mouse selection rectangle*/
	CHART_API virtual void DrawSelection(CPoint point);
	//@cmember
	/* Helper function that implements the ZoomOut and ZoomOutAll features */
	CHART_API virtual void GraphZoomout(BOOL bAlltheWay);

// Attributes
public:
	/*inline*/ CGraphDoc* GetDocument();

public:
	//@cmember
	/* The draw function -- overridden to draw this view*/
	CHART_API virtual void OnDraw(CDC* pDC);  
	//@cmember
	/* Standard window pre-creation*/
	CHART_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected:
	//@cmember
	/* Standard CView overridable -- sets the chart scroll sizes*/
	CHART_API virtual void OnInitialUpdate();  // called first time after construct
	//@cmember
	/* Sets window to viewport mapping*/
	CHART_API virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

#ifndef _OCCE_
	//@cmember
	/* Standard CView overridable*/
	CHART_API virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//@cmember
	/* Standard CView overridable -- sets up print pagination*/
	CHART_API virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//@cmember
	/* Standard CView overridable*/
	CHART_API virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
#endif //_OCCE_
	//}}AFX_VIRTUAL

// Member variables
protected:
	//@cmember
	/* A FILO stack for the zoom levels */
	CObStack m_ZoomStack;
	//@cmember
	/* Flag to define the charts ability to be zoomed -- TRUE enables zooming*/
	BOOL m_bZoomable;
	//@cmember
	/* The one and only GraphTip window*/
	SRGraphTip m_GraphTip;
	//@cmember
	/* When TRUE the chart is being selected with a selecting rectangle or other shape*/
	BOOL m_bSelecting;
	//@cmember
	/* When TRUE chart data is being dragged*/
	BOOL m_bDragging;
	//@cmember
	/* When TRUE the mouse is in a feedback area*/
	BOOL m_bInFeedback;
	//@cmember
	/* When TRUE the chart tip is being displayed*/
	BOOL m_bShowingTip;
	//@cmember
	/* When TRUE the chart is zoomed in*/
	BOOL m_bZoomed;
	//@cmember
	/* Points to the display item currently being zoomed*/
	SRGraphComponent* m_pZoomedDisplay;
	//@cmember
	/* When TRUE the mouse timer is running<nl>*/
	//A timeout of this timer will trigger a feedback search and possibly initiate the display of a chart tip.
	BOOL m_bMouseTimerIsRunning;
	//@cmember
	/* When TRUE the max area of the chart is set explicitly during printing and print preview*/
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
	/* Number of pages required to print chart in horizontal direction - internal*/
	int m_nPageCountX;
	//@cmember
	/* Number of pages required to print chart in vertical direction - internal*/
	int m_nPageCountY;
	
	//@cmember
	/* Group in which the dragged item is stored*/
	int m_nDragGroup;
	//@cmember
	/* Index of the item being dragged*/
	int m_nDragIndex;
	//@cmember
	/* Record of the un-zoomed scope -- min group*/
	int m_nUnzoomMinGroup;
	//@cmember
	/* Record of the un-zoomed scope -- max group*/
	int m_nUnzoomMaxGroup;
	//@cmember
	/* Record of the un-zoomed scope -- min index*/
	int m_nUnzoomMinIndex;
	//@cmember
	/* Record of the un-zoomed scope -- max index*/
	int m_nUnzoomMaxIndex;
	//@cmember
	/* First selection point on screen -- used for drawing the selection area*/
	CPoint m_SelectionPointA;
	//@cmember
	/* Second selection point on screen -- used for drawing the selection area*/
	CPoint m_SelectionPointB;
	//@cmember
	/* Current mouse position*/
	CPoint m_MousePoint;
public:
	//@cmember
	/* Timer identifier*/
	SEC_UINT m_TimerIdent;
	//@cmember
	/* Pointer to store the graph component */
	SRGDisplayBase * m_pDragDisplay;


// Implementation
public:
	//@cmember
	/* Render the chart into the passed bitmap*/
	CHART_API virtual void DrawToBitmap(CDC* pDC, CBitmap& bmp);

	//@cmember
	/* Sets the semaphore that signfies that this view has a document (true) or does not (false) */
	CHART_API virtual void SetHasDocument(BOOL v);
	//@cmember
	/* Returns TRUE if this view has a document or FALSE if it does not */
	CHART_API virtual BOOL GetHasDocument();

	//@cmember
	/* Turns drag-tips on (TRUE) or off (FALSE) */
	CHART_API virtual void SetDragTips(BOOL v);
	//@cmember
	/* Returns the drag-tips flag. If this is TRUE then drag-tips are enabled. Otherwise FALSE. */
	CHART_API virtual BOOL GetDragTips();
	//@cmember
	/* Sets or resets the dragable flag*/
	CHART_API virtual void SetDragable(BOOL v);
	//@cmember
	/* Returns the dragable flag*/
	CHART_API virtual BOOL GetDragable();
	//@cmember
	/* Sets the flag signifying whether this chart is able to zoom*/
	CHART_API virtual void SetZoomable(BOOL v);
	//@cmember
	/* Gets the zoom enable flag*/
	CHART_API virtual BOOL GetZoomable();
	//@cmember
	/* Override to draw the custom selection shape for your own chart type*/
	CHART_API virtual void DrawCustomSelection(CPoint point);
	//@cmember
	/* Displays the feedback with a chart tip -- override to add your own text formatting*/
	CHART_API virtual void ShowFeedback(SRGraphFeedback *pFeedback);
	//@cmember
	/* Enables or disables the use of the maximum size rectangle*/
	inline void SetUseMaxArea(BOOL b){m_bUseMaxArea=b;}
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGScrollView();
#ifdef _DEBUG
	//@cmember
	/* Standard debug code */
	CHART_API virtual void AssertValid() const;
	//@cmember
	/* Standard debug code */
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//@cmember
	/* Semaphore to flag the existence of document class*/
	BOOL m_bHasDocument;

	//@cmember
	/* semaphore for the draging tips*/
	BOOL m_bDragTips;

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
	//@cmember
	/* Creates and returns an SRGraphPosition object filled with data about the chart item under the specified point*/
	CHART_API virtual SRGraphPosition * GetPosition(SRGraph *pGraph, CPoint point);
	//@cmember
	/* Returns a pointer to the graph object*/
	CHART_API virtual SRGraph* GetGraph();
	//{{AFX_MSG(SRGScrollView)
	//@cmember
	/* Overridden to do nothing*/
	CHART_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//@cmember
	/* Begins the selection or dragging process*/
	CHART_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//@cmember
	/* Ends the selection or dragging process*/
	CHART_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//@cmember
	/* Handles the selection or dragging of data items*/
	CHART_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	/* Handles the chart-tip timing and display*/
	CHART_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	//@cmember
	/* Copies the screen bitmap to the clipboard for pasting into another application*/
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
	/* Displays the print pagination setup dialog*/
	CHART_API afx_msg void OnGraphPagesetup();
	/* Runs a different pagination dialog*/
	CHART_API afx_msg void OnGraphPagesetup2();
#endif //_OCCE_
	//@cmember
	/* Handles the GraphEdit command*/
	CHART_API afx_msg void OnGraphEdit();
	//@cmember
	/* Creation initialization -- creates a color palette if required*/
	CHART_API afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//@cmember
	/* Palette management*/
	CHART_API afx_msg BOOL OnQueryNewPalette();
	//@cmember
	/* Palette management*/
	CHART_API afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//@cmember
	/* Message handler for the Graph Wizard menu item */
	CHART_API afx_msg void OnGraphWizard();
	//@cmember
	/* Message handler for the Save As DIB menu item */
	CHART_API afx_msg void OnSaveAsDib();
	//@cmember
	/* Message handler for the Save As JPEG menu item */
	CHART_API afx_msg void OnSaveAsJpeg();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};


// #ifndef _DEBUG  // debug version in SRGScrollView.cpp
// inline CGraphDoc* SRGScrollView::GetDocument()
//    { return (CGraphDoc*)m_pDocument; }
// #endif

//#ifndef _DEBUG  // debug version in SRGScrollView.cpp
inline CGraphDoc* SRGScrollView::GetDocument()
{ return (CGraphDoc*)m_pDocument; }
//#endif

/////////////////////////////////////////////////////////////////////////////
#endif // __GRAPHSCROLLVW_H__

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


