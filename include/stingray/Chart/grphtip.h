///////////////////////////////////////////////////////////////////////////////
// grphtip.h
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
// @doc SRGraphTip
// @module GrphTip.h | SRGraphTip header file<nl>
//Written by Bob Powell (www.roguewave.com)
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// SRGraphTip window

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __GRAPH_TIP__
#define __GRAPH_TIP__

#include <StingrayExportDefs.h>

//@doc SRGraphTip

//@mfunc virtual BOOL  | SRGraphTip | IsShowing | Returns TRUE if the Graph Tip is currently visible

// using cmember tags only for simple data items

//@doc SRGraphTip
//@mdata HBRUSH  | SRGraphTip | m_hBkBrush | This handle stores the brush used to paint the background of chart tips. It is created 
//when ShowTip is called and recycled automatically when the SRGraphTip object is deleted.

//@mdata CString  | SRGraphTip | m_ClassName | Afx generated class name

//@mdata CString  | SRGraphTip | m_TextString | Text string to display in the Graph Tip

//@mdata CPoint  | SRGraphTip | m_Point | Point at which the graph tip is drawn

//@mdata BOOL  | SRGraphTip | m_bShowing | TRUE when the Graph Tip is visible

//@doc SRGraphTip
//@mdata int  | SRGraphTip | m_nTipTime | The time (in milliseconds) that the tip is to be shown

//@doc SRGraphTip
//@mdata COLORREF | SRGraphTip | m_TextColor | The tooltip foreground color
	
//adinsert
//$head Utility classes
//$level 1
//@class A simple tooltip-style window designed to show data for the SRGraphFeedback system
//@rem This simple window draws a ToolTip-like box with text on the main window. It is not 
//clipped by its parent and remains in place for 5 seconds unless it is turned off or 
//the mouse cursor passes over it.
class SRGraphTip : public CWnd
{
// Construction
public:
	//@cmember,mfunc
	/* Initializes the tip timer*/
	CHART_API virtual void SetTipTime(int v);

	//@cmember,mfunc
	/* retrieves the tip timer value */
	CHART_API virtual int GetTipTime();
	//@cmember
	/* Returns TRUE if the Graph Tip is currently visible*/
	CHART_API virtual BOOL IsShowing();

	//@cmember
	/* One-step initialization of the Graph Tip*/
	CHART_API virtual void ShowTip(LPCTSTR strText,CPoint point,CWnd *pParentWnd);

	//@cmember
	/* Variable argument version of ShowTip*/
	CHART_API virtual void ShowTip(CPoint point, CWnd* pParentWnd, LPCTSTR lpszFormat, ...);

	//@cmember
	/* Variable argument version of ShowTip */
	CHART_API virtual void ShowTip(CPoint point, HWND hParentWnd, LPCTSTR lpszFormat, ...);
	//@cmember
	/* Show tooltips */
	CHART_API virtual void ShowTip(LPCTSTR strText, CPoint point, HWND hParentWnd);

	//@cmember
	/* Constructor*/
	CHART_API SRGraphTip();

	//@cmember
	/* Removes the Graph Tip and destroys the window*/
	CHART_API virtual void EraseTip();

// Implementation
public:
	//@cmember
	/* Set the text color for the tooltip */
	CHART_API void SetTextColor(COLORREF color);
	//@cmember
	/* Set the background color for the tooltip */
	CHART_API void SetBkColor(COLORREF color);

	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGraphTip();

	// Generated message map functions
protected:
	//@cmember
	/* The tooltip foreground color */
	COLORREF m_TextColor;

	//@cmember
	/* The time (in milliseconds) that the tip is to be shown */
	int m_nTipTime;

	//@cmember
	/* Handle to the background brush*/
	HBRUSH m_hBkBrush;

	//@cmember
	/* The Afx generated class name*/
	CString m_ClassName;

	//@cmember
	/* The text to display in the Graph Tip*/
	CString m_TextString;

	//@cmember
	/* The point at which the graph tip is drawn*/
	CPoint m_Point;

	//@cmember
	/* TRUE when the Graph Tip is visible*/
	BOOL m_bShowing;

	//{{AFX_MSG(SRGraphTip)
	//@cmember
	/* Draws the tip text in the window*/
	CHART_API afx_msg void OnPaint();
	//@cmember
	/* Destroys the tip window when mouse cursor passes over it*/
	CHART_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	/* Destroys the tip window when time limit (5 seconds) expires*/
	CHART_API afx_msg void OnTimer(SEC_UINT nIDEvent);
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

