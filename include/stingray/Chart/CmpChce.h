///////////////////////////////////////////////////////////////////////////////
// CmpChce.h
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

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

/////////////////////////////////////////////////////////////////////////////
// SRGComponentChoice dialog

#ifndef __SRGRAPHCOMPONENTCHOICE_H__
#define __SRGRAPHCOMPONENTCHOICE_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGComponentChoice 
//@doc SRGComponentChoice
//@mdata CComboBox  | SRGComponentChoice | m_ComponentType | Combo box to hold component names

// adinsert AutoDuck insertion point for SRGComponentChoice 
// cmember tags only used for this dialog class

//$head The Chart Explorer
//$level 1

//@topic SRGComponentChoice Class Overview |
//This dialog is displayed when the user right-clicks the Components item 
//in the tree diagram and then selects the Add Component command from the popup menu. 
//The user can choose the type of component to be added from a combo box.

//@doc SRGComponentChoice 
//@class Part of Chart Explorer<nl>
//This dialog is displayed when the user right-clicks the Components item 
//in the tree diagram and then selects the Add Component command from the popup menu. 
//The user can choose the type of component to be added from a combo box.
//@base public | CDialog
class SRGComponentChoice : public CDialog
{
// Construction
public:
	//@cmember
	/* Standard constructor*/
	CHART_API SRGComponentChoice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SRGComponentChoice)
	enum { IDD = SRG_IDD_CHOOSECOMP };
	//@cmember
	/* List of components that can be added*/
	CComboBox	m_ComponentType;
	//}}AFX_DATA

	//@cmember
	/* Index of the selected component*/
	int m_nSelection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGComponentChoice)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	//@cmember
	/* Initializes the dialog -- sets initial selection in the combo box*/
	CHART_API virtual BOOL OnInitDialog();

protected:

	// Generated message map functions
	//{{AFX_MSG(SRGComponentChoice)
	//@cmember
	/* Retrieves user selection*/
	CHART_API virtual void OnOK();
	//}}AFX_MSG
	CHART_DECLARE_MESSAGE_MAP()
	//DECLARE_MESSAGE_MAP()
};

#endif
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

