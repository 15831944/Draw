///////////////////////////////////////////////////////////////////////////////
// ItemEdit.h
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
//@doc SRGraphItemEdit
//@module ItemEdit.h | SRGraphItemEdit header file<nl>
//Written by Bob Powell (www.roguewave.com)
/////////////////////////////////////////////////////////////

// using cmember tags only for this simple dialog class

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif
/////////////////////////////////////////////////////////////////////////////
// SRGraphItemEdit dialog
#ifndef __SRGRAPHITEMEDIT_H__
#define __SRGRAPHITEMEDIT_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGraphItemEdit 
//@doc SRGraphItemEdit

// adinsert AutoDuck insertion point for SRGraphItemEdit 

//$head The Chart explorer
//$level 1

//@doc SRGraphItemEdit 

//@topic SRGraphItemEdit Class Overview |
//This is a simple dialog to enable or disable background draw processing and feedback logging<nl>
//Part of Chart Explorer -- displayed when user double-clicks the root item in the tree diagram

//@class Dialog to enable or disable background draw processing and feedback logging<nl>
//Part of Chart Explorer -- displayed when user double-clicks the root item in the tree diagram
//@base public | CDialog
class SRGraphItemEdit : public CDialog
{
// Construction
public:
	CHART_API SRGraphItemEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SRGraphItemEdit)
	enum { IDD = SRG_IDD_GRAPHITEMEDIT };
	//@cmember
	/* Check box to enable background draw processing*/
	BOOL	m_bBackgroundDraw;
	//@cmember
	/* Check box to enable feedback logging*/
	BOOL	m_bFeedbackLogging;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGraphItemEdit)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SRGraphItemEdit)
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
#endif

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

