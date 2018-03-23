///////////////////////////////////////////////////////////////////////////////
// SRREScrollView.h
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
// @doc SREScrollView
// @module SREScrollView.h | SREScrollView header file<nl>
//Written by Bob Powell and Chuanzhong Zhu (www.roguewave.com)
/////////////////////////////////////////////////////////////
#ifndef __SREScrollView_H__
#define __SREScrollView_H__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////
//
// SREScrollView.h : header file
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////
// AutoDuck tag block for SREScrollView 
//@doc SREScrollView

//$head View classes
//$level 1

//@mdata BOOL  | SREScrollView | m_bAutoDelete | Semaphore indicating whether this object should delete itself
// when its window is destroyed. By default, m_bAutoDelete is set to FALSE, meaning that its parent
// will free the memory used by this object.  This is the case when the parent is a CDialog and CFormView or
// their derivatives. If an SREScrollView is allocated on the heap and used as a more typical view, such as a splitter window; SetAutoDelete(TRUE) should be called.

//@mdata SRGraphComponent*  | SREScrollView | m_DragingComponent | Holds the dragging component when in tracking mode -- available for derived classes

//@mfunc void  | SREScrollView | SetAutoDelete | Sets or resets the auto-delete semaphore
//@parm BOOL  | v | TRUE if this object will not be deleted by its parent
//@see <md SREScrollView::m_bAutoDelete>

//@mfunc BOOL  | SREScrollView | GetAutoDelete | Returns the value of the auto-delete semaphore 
//@see <md SREScrollView::m_bAutoDelete>

//@doc SREScrollView
//@mdata SRGraph*  | SREScrollView | m_pGraph | Pointer to an existing SRGraph-derived object -- must be set before the view is drawn


// adinsert AutoDuck insertion point for SREScrollView 

//@topic SREScrollView Class Overview |
//This class, derived from SRGScrollView, provides an extended view class which has the ability to exist without a document. Consequently, this class may be used to provide 
// all the functionality of a CScrollView class and the data dragging capabilities and chart interaction of the SRGraphView class on dialogs and in non document - view aplications.


//@doc SREScrollView 
//@class SREScrollView is a small extension of the SRGScrollView class which can be 
//put into dialog boxes and similar windows.  It does not depend on a document class. 
//On the other hand, it still behaves like a SRGScrollView class, reacting to mouse events, etc.<nl> 
//The m_pGraph member variable must be set to point to an existing SRGraph object.<nl> 
//SetAutoDelete(TRUE) should be called if this view object is not in a dialog or form view, so that it will delete itself.
//@base public | SRGScrollView
class SREScrollView : public SRGScrollView
{
protected:
	CHART_DECLARE_DYNCREATE(SREScrollView)

// Attributes
public:
	//@cmember
	/* Sets or resets the auto-delete semaphore*/
	inline void SetAutoDelete(BOOL v){m_bAutoDelete=v;}
	//@cmember
	/* Returns the value of the auto-delete semaphore*/
	inline BOOL GetAutoDelete(){return m_bAutoDelete;}

// Operations
public:
	//@cmember
	/* Constructor*/
	CHART_API SREScrollView();           // protected constructor used by dynamic creation
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SREScrollView();

	//@cmember
	/* Overridden to return the internal pointer m_pGraph instead of accessing a document*/
	CHART_API virtual SRGraph* GetGraph();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SREScrollView)
protected:
	//@cmember
	/* Checks the validity of m_pGraph and draws the chart that it points to*/
	CHART_API virtual void OnDraw(CDC* pDC);

	//@cmember
	/* Deletes the this pointer when its window is destroyed, if m_bAutoDelete is TRUE*/
	CHART_API virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifndef _OCCE_
	CHART_API virtual void PrintContent();
#endif //_OCCE_

	//@cmember
	/* Pointer to the dragging component when tracking (not used internally)*/
	SRGraphComponent* m_DragingComponent;

	//@cmember
	/* Semaphore indicating whether this object should delete itself when its window is destroyed*/
	BOOL              m_bAutoDelete;


#ifdef _DEBUG
	//@cmember,mfunc
	/* Standard debug code */
	CHART_API virtual void AssertValid() const;
	//@cmember,mfunc
	/* Standard debug code */
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

#ifndef _OCCE_
	//@cmember
	/* Special handling to support use as a child for no frame window -- always returns MA_ACTIVATE*/
	CHART_API afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
#endif //_OCCE_
	// Generated message map functions
	//{{AFX_MSG(SREScrollView)
	//@cmember
	/* Calls CWnd::OnCreate directly*/
	CHART_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
public:
	CHART_API virtual void UpdateGraphZoomout(CCmdUI* pCmdUI);
	CHART_API virtual void GraphZoomout(BOOL bAllTheWay);
#ifndef _OCCE_
	//@cmember,mfunc
	/* Enables printing from non doc - view - frame architectures. */
	CHART_API virtual void Printing();
#endif //_OCCE_

	//@cmember
	/* Finds the top-most component under the mouse position*/
	CHART_API virtual SRGraphComponent* GetTrackingComponent(CPoint point);

	//@cmember
	/* Pointer to an existing SRGraph-derived object -- must be set before the view is drawn*/
	SRGraph* m_pGraph;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // __SREScrollView_H__
