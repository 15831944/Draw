///////////////////////////////////////////////////////////////////////////////
// CustToolBoxDlg.h
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

#ifndef __SECCUSTOMIZETOOLBOXDLG_H_
#define __SECCUSTOMIZETOOLBOXDLG_H_

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

/////////////////////////////////////////////////////////////////////////////
// SECACustTBDlg dialog

class SECACustTBDlg : public CDialog
{
// Construction
public:
	TOOLKIT_API SECACustTBDlg(CArray < CString, CString& > & , CWnd* pParent = NULL);   // standard constructor

	inline CArray < CString, CString& > &GetUserPickedItems() { return m_UserPickedClassIDs; }

// Dialog Data
	//{{AFX_DATA(SECACustTBDlg)
	enum { IDD = SECAH_IDD_CustomizeToolbox };
	CCheckListBox m_controls;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECACustTBDlg)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CArray < CString, CString& > &m_initialllySelected;
	CArray < CString, CString& >  m_ClassIDs;
	CArray < CString, CString& >  m_UserPickedClassIDs;

	// Generated message map functions
	//{{AFX_MSG(SECACustTBDlg)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API virtual void OnOK();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// __SECCUSTOMIZETOOLBOXDLG_H_
