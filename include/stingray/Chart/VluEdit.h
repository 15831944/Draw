///////////////////////////////////////////////////////////////////////////////
// VluEdit.h
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
//@doc SRGraphValueEdit
//@module VluEdit.h | SRGraphValueEdit header file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// VluEdit.cpp: interface of the SRGraphValueEdit class
//
/////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif
/////////////////////////////////////////////////////////////////////////////
// SRGraphValueEdit dialog
#ifndef __SRGRAPHVALUEEDIT_H__
#define __SRGRAPHVALUEEDIT_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGraphValueEdit 
// adinsert AutoDuck insertion point for SRGraphValueEdit 
// cmember tags only for this simple dialog class

//$head The Chart explorer
//$level 1

//@doc SRGraphValueEdit 
//@topic SRGraphValueEdit Class Overview |
//This is a part of Chart Explorer, this dialog is invoked when the user double-clicks a 
//data item's value on the tree control.  It allows the user to modify the value assigned to the data item.

//@class Part of Chart Explorer, this simple dialog is invoked when the user double-clicks a 
//data item's value on the tree control.  It allows the user to modify the value assigned to the data item.
//@base public | CDialog
class SRGraphValueEdit : public CDialog
{
// Construction
public:
		//@cmember
		/* Standard constructor*/
	CHART_API SRGraphValueEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SRGraphValueEdit)
	enum { IDD = SRG_IDD_VALUEEDIT };
		//@cmember
		/* Value displayed in the edit control -- may be modified by the user*/
	double	m_dValue;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGraphValueEdit)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SRGraphValueEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};
#endif

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


