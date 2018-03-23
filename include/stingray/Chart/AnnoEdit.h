///////////////////////////////////////////////////////////////////////////////
// AnnoEdit.h
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
// SRGraphAnnotationEdit dialog

#ifndef __SRGRAPHANNOTATIONEDIT_H__
#define	__SRGRAPHANNOTATIONEDIT_H__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGraphAnnotationEdit 
// cmember tags only used for this dialog class
// adinsert AutoDuck insertion point for SRGraphAnnotationEdit 

//$head The Chart explorer
//$level 1

//@doc SRGraphAnnotationEdit
//@topic SRGraphAnnotationEdit Class Overview |
//This dialog is displayed when the user right-clicks a data item or data list. 
//It allows the user to enter annotation text and country code for the selected object.


//@doc SRGraphAnnotationEdit 
//@class Part of Chart Explorer<nl>
//This dialog is displayed when the user right-clicks a data item or data list. 
//It allows the user to enter annotation text and country code for the selected object.
//@base public | CDialog
class SRGraphAnnotationEdit : public CDialog
{
// Construction
public:
	CHART_API SRGraphAnnotationEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SRGraphAnnotationEdit)
	enum { IDD = SRG_IDD_ANNOTATIONEDIT };
	//@cmember
	/* Annotation text*/
	CString	m_Text;
	//@cmember
	/* Country code*/
	int		m_nCode;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SRGraphAnnotationEdit)
protected:
	CHART_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SRGraphAnnotationEdit)
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

