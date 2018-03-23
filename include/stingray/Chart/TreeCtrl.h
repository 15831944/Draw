///////////////////////////////////////////////////////////////////////////////
// TreeCtrl.h
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
//@doc SRGTreeCtrl
//@module TreeCtrl.h | SRGTreeCtrl header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// TreeCtrl.cpp: interface of the SRGTreeCtrl class
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGRAPHEDITDIALOH_H__
#define __SRGRAPHEDITDIALOH_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGTreeCtrl 
// adinsert AutoDuck insertion point for SRGTreeCtrl 

// cmember tags only used for this simple control class

//$head The Chart explorer
//$level 1

//@doc SRGTreeCtrl 
//@topic SRGTreeCtrl Class Overview |
//This class is a simple extension of the standard CTreeCtrl class that 
//maintains the current mouse position and the last tree view item clicked.<nl>
//It is part of the chart explorer.

//@class SRGTreeCtrl is a simple extension of the standard CTreeCtrl class that 
//maintains the current mouse position and the last tree view item clicked
//@base public | CTreeCtrl
class SRGTreeCtrl : public CTreeCtrl
{
// Construction
public:
	//@cmember
	/* Current position of the mouse cursor in screen coordinates*/
	CPoint m_CurrentPoint;
	//@cmember
	/* Last tree view item clicked by the user or NULL*/
	HTREEITEM m_LastItemHit;
	//@cmember
	/* Constructor*/
	CHART_API SRGTreeCtrl();

// Implementation
public:
	//@cmember
	/* Destructor*/
	CHART_API virtual ~SRGTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(SRGTreeCtrl)
	//@cmember
	/* Overridden to store the mouse position*/
	CHART_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//@cmember
	/* Overridden to store the tree item clicked*/
	CHART_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//@cmember
	/* Overridden to store the tree item clicked*/
	CHART_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
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

