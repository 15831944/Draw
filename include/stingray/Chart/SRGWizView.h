///////////////////////////////////////////////////////////////////////////////
// SRGWizView.h
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
// SRGWizView.h: interface for the SRGWizView class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGWizView_H__
#define __SRGWizView_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
// SRGWizView view

//$head View classes
//$level 1

//@doc SRGWizView
//@mdata BOOL  | SRGWizView | m_bIsTracking | Flag for tracking.

//@mdata CRectTracker  | SRGWizView | m_Tracker | Tracking rectangle used for component dragging

//@mdata CRect         | SRGWizView | m_rectTracker | Helper rectangle for tracking

//@mdata BOOL  | SRGWizView | m_bShowGrid | Semaphore indicating if user want to
// draw alignment grid

//$head The Chart Wizard
//level 1

// adinsert AutoDuck insertion point for SRGWizView 

//@doc SRGWizView 
//@class Special view class for internal use by the Wizard
class SRGWizView : public SREScrollView
{
protected:
	CHART_DECLARE_DYNCREATE(SRGWizView)

// Operations
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGWizView();           // protected constructor used by dynamic creation
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGWizView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGWizView)
protected:
	//@cmember
	/* Draws the chart, tracking component, and placement grid*/
		CHART_API virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//@cmember
	/* Flag if it is in the tracking mode*/
	BOOL m_bIsTracking;
	//@cmember
	/* Tracking rectangle for component dragging*/
	SRGRectTracker m_Tracker;

	//@cmember
	/* Semaphore indicating if user want to draw an alignment grid*/
	BOOL m_bShowGrid;

#ifdef _DEBUG
	//@cmember,mfunc
	/* Debug code */
	CHART_API virtual void AssertValid() const;
	//@cmember,mfunc
	/* Debug code */
	CHART_API virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(SRGWizView)
	//@cmember
	/* Left button down + shift key initiates tracking */
	CHART_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//@cmember
	/* Terminates tracking*/
	CHART_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//@cmember
	/* Changes cursor while tracking*/
	CHART_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//@cmember
	/* Command handler to stop tracking when in Tracking mode*/
	CHART_API afx_msg void OnStopTracking();
	//@cmember
	/* Copies the graph to the clipboard as a bitmap*/
	CHART_API afx_msg void OnWizardCopy();
	//@cmember
	/* Command handler to save the layout for future use*/
	CHART_API afx_msg void OnSaveLayout();
	//@cmember
	/* Command handler to print the graph from the wizard*/
	CHART_API afx_msg void OnWizardPrint();
	//@cmember
	/* Bring up the context menu in the view area when user right click mouse*/
	CHART_API afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//@cmember,mfunc
	/* Handler for the "Save as DIB" menu */
	CHART_API afx_msg void OnSaveAsDib();
	//@cmember,mfunc
	/* Handler for the "Save as JPEG" menu */
	CHART_API afx_msg void OnSaveAsJpeg();
	//}}AFX_MSG
	//@cmember
	/* Message handler called when tracking rect changed size*/
	CHART_API afx_msg LRESULT OnTrackingRectChanged(WPARAM wParam, LPARAM lParam);
	//@cmember
	/* Message handler called when tracking rect adjust size*/
	CHART_API afx_msg LRESULT OnAdjustTrackingRect(WPARAM wParam, LPARAM lParam);
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
public:
	CHART_API virtual void StopTracking();
	//@cmember
	/* Finding the top most component under the mouse.*/
	CHART_API virtual SRGraphComponent* GetTrackingComponent(CPoint point);
	//@cmember
	/* Addjust the rectangle to align with the alignment grid*/
	CHART_API virtual void SnapToGrid(CRect* pRect);
	//@cmember
	/* Draw or erase the alignment grid*/
	CHART_API virtual void DrawGrid(BOOL bShow = TRUE);
};

#endif // __SRGWizView_H__

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


