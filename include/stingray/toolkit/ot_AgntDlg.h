///////////////////////////////////////////////////////////////////////////////
// ot_AgntDlg.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author:       Praveen Ramesh
// Description:  Declaration SECAgentParseDlg
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef _SEC_AGENT_PARSEDLG
#define _SEC_AGENT_PARSEDLG

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

using namespace AgentServerObjects;
/////////////////////////////////////////////////////////////////////////////

//@doc SECAgentParseDlg 
//@class The SECAgentParseDlg allows the user to preview the installed agent characters
// and select one.
class SECAgentParseDlg : public CDialog
{
// Construction/Destruction
public:
	TOOLKIT_API SECAgentParseDlg(CWnd* pParent = NULL);	// standard constructor
	TOOLKIT_API virtual ~SECAgentParseDlg();

	// Initialization
	TOOLKIT_API virtual void DefaultInit();

	// 
	//@access Attributes
	//@cmember
	/* Get the chosen character. The returned string is empty if no characters are selected. */
	inline virtual CString GetSelectedChar(){return m_strCurChar;}

	// virtual overridables
	TOOLKIT_API virtual CStringList* GetAgentFilesInDir(const CString& strChar);
	TOOLKIT_API virtual void ShowNewChar(const CString& strNewChar);

	// Utility functions
	TOOLKIT_API CString GetFilePathFromCharName(CString& strChar);
	TOOLKIT_API CStringList* GetCharNamesFromFileNames(CStringList* pFileList);
	TOOLKIT_API void FillCharsCombo(CStringList* pFilesList);
	
	IAgentExPtr m_ptrAgent;
	CString m_strCurChar;
	long m_lCurCharID;
	CStringList* m_pFilesList;
	CToolTipCtrl m_wndToolTip;

// Dialog Data
	//{{AFX_DATA(SECAgentParseDlg)
	enum { IDD = IDD_AGENTPARSE_DIALOG };
	CButton	m_btnDir;
	CComboBox	m_agentList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECAgentParseDlg)
public:
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SECAgentParseDlg)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnSelchangeAgentList();
	TOOLKIT_API afx_msg void OnCharsdirBtn();
	TOOLKIT_API afx_msg void OnDefButton();
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


#endif 
