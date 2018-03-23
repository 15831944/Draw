///////////////////////////////////////////////////////////////////////////////
// SREGraphView.h
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
// @doc SREGraphView
// @module SREGraphView.h | SREGraphView header file<nl>
//Written by Bob Powell and Chuanzhong Zhu (www.roguewave.com)
/////////////////////////////////////////////////////////////

//$head View classes
//$level 1
#if !defined(_GRAPHVIEW_H_INCLUDED_)
#define _GRAPHVIEW_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////
//
// SREGraphView.h : header file
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////
// AutoDuck tag block for SREGraphView 
//@doc SREGraphView

//@mdata BOOL  | SREGraphView | m_bAutoDelete | Semaphore indicating whether this object should delete itself
// when its window is destroyed. By default, m_bAutoDelete is set to FALSE, meaning that its parent
// will free the memory used by this object.  This is the case when the parent is a CDialog and CFormView or
// their derivatives. If an SREGraphView is allocated on the heap and used as a more typical view, such as a splitter window; SetAutoDelete(TRUE) should be called.

//@mdata SRGraphComponent*  | SREGraphView | m_DragingComponent | Holds the dragging component when in tracking mode -- available for derived classes

//@mfunc void  | SREGraphView | SetAutoDelete | Sets or resets the auto-delete semaphore
//@parm BOOL  | v | TRUE if this object will not be deleted by its parent
//@see <md SREGraphView::m_bAutoDelete>

//@mfunc BOOL  | SREGraphView | GetAutoDelete | Returns the value of the auto-delete semaphore 
//@see <md SREGraphView::m_bAutoDelete>

//@mdata SRGraph* | SREGraphView | m_pGraph | Pointer to an existing SRGraph-derived object -- must be set before the view is drawn
	
// adinsert AutoDuck insertion point for SREGraphView 

//@topic SREGraphView Class Overview |
//SREGraphView is a small extension of the SRGraphView class which can be 
//put into dialog boxes and similar windows.  It does not depend on a document class. 
//On the other hand, it still behaves like a SRGraphView class, reacting to mouse events, etc.<nl> 
//The m_pGraph member variable must be set to point to an existing SRGraph object.<nl> 
//SetAutoDelete(TRUE) should be called if this view object is not in a dialog or form view, so that it will delete itself.

//@doc SREGraphView 
//@class SREGraphView is a small extension of the SRGraphView class which can be 
//put into dialog boxes and similar windows.  It does not depend on a document class. 
//On the other hand, it still behaves like a SRGraphView class, reacting to mouse events, etc.<nl> 
//The m_pGraph member variable must be set to point to an existing SRGraph object.<nl> 
//SetAutoDelete(TRUE) should be called if this view object is not in a dialog or form view, so that it will delete itself.
//@base public | SRGraphView
class SREGraphView : public SRGraphView
{
	CHART_DECLARE_DYNCREATE(SREGraphView)
// Construction
public:
	//@cmember
	/* Constructor*/
	CHART_API SREGraphView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SREGraphView)
protected:
	//@cmember
	/* Deletes the this pointer when its window is destroyed, if m_bAutoDelete is TRUE*/
	CHART_API virtual void PostNcDestroy();

	//@cmember
	/* Checks the validity of m_pGraph and draws the chart that it points to*/
	CHART_API virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SREGraphView();

	//@cmember
	/* Sets or resets the auto-delete semaphore*/
	inline void SetAutoDelete(BOOL v){m_bAutoDelete=v;}
	//@cmember
	/* Returns the value of the auto-delete semaphore*/
	inline BOOL GetAutoDelete(){return m_bAutoDelete;}

	// Generated message map functions
protected:
#ifndef _OCCE_
	CHART_API virtual void PrintContent();
#endif //_OCCE_
	//@cmember
	/* Pointer to the dragging component when tracking (not used internally)*/
	SRGraphComponent* m_DragingComponent;

	//@cmember
	/* Semaphore indicating whether this object should delete itself when its window is destroyed*/
	BOOL m_bAutoDelete;

	//{{AFX_MSG(SREGraphView)
#ifndef _OCCE_
	//@cmember
	/* Performs zoom out and calls the base class function*/
	CHART_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//@cmember
	/* Special handling to support use as a child with no frame window -- always returns MA_ACTIVATE*/
	CHART_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
#endif //_OCCE_
	//@cmember
	/* Calls CWnd::OnCreate directly*/
	CHART_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	//@cmember
	/* Overridden to return the internal pointer m_pGraph instead of accessing a document*/
	CHART_API virtual SRGraph* GetGraph();

	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()

public:
	CHART_API virtual void UpdateGraphZoomout(CCmdUI* pCmdUI);
	CHART_API virtual void GraphZoomout(BOOL bAllTheWay);
#ifndef _OCCE_
	CHART_API virtual void Printing();
#endif //_OCCE_

	//@cmember
	/* Finds the top-most component under the mouse position*/
	CHART_API virtual SRGraphComponent* GetTrackingComponent(CPoint point);

	//@cmember
	/* Pointer to an existing SRGraph-derived object -- must be set before the view is drawn*/
	SRGraph* m_pGraph;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_GRAPHVIEW_H_INCLUDED_)
