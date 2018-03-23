///////////////////////////////////////////////////////////////////////////////
// usrtdlg.h
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
// 
//  Author:			John Williston
//  Description:	Declaration for SECUserToolsDlg
//  Created:		August 1996
//

#ifndef __USRTLDLG_H__
#define __USRTLDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

// Forward declarations
class SECBrowseFileEdit;
class SECBrowseDirEdit;
class SECUserTool;

/////////////////////////////////////////////////////////////////////////////
// SECUserToolsDlg dialog

/////////////////////////////
// AutoDuck tag block block for SECUserToolsDlg 

//@doc SECUserToolsDlg
//@mfunc void  | SECUserToolsDlg | SetToolsArrayPtr | To allow the user to edit a list of user-tools, the user-tools dialog
// must have an array of user-tools to operate on.  Since the lifetime of this array is typically greater than that of the
// user-tools dialog, the user-tools dialog cannot own the array.  The class which constructs the dialog must own the
// user-tools array and pass a pointer to it, using this method, just after constructing the dialog.  
//@parm CObArray*  | p | Pointer to the user tools array.
//@xref<mf SECUserToolsDlg::SECUserToolsDlg>
//@xref<c SECUserToolsDlg>


// adinsert AutoDuck insertion point for SECUserToolsDlg 
//@doc SECUserToolsDlg 
//@class The SECUserToolsDlg class implements a user-tools dialog.  A user-tools dialog allows a user to edit a list of 
// user-tools, where each user-tool is represented by one SECUserTool object. Through this dialog, the user can create 
// new user-tools, edit and delete existing user-tools and reorder the list of user-tools. Refer to the documentation for
// SECUserTool for a complete explanation of a user-tool.
//@comm See the USERTOOL sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\USERTOOL directory for a demonstration of this class.
//@xref<c SECUserTool>
//@BASE public|CDialog
class SECUserToolsDlg : public CDialog
{
// Construction
public:
	// standard constructor
	//@Access Public Members
	//@cmember
	/* Constructs an SECUserToolsDlg object.*/
	TOOLKIT_API SECUserToolsDlg(CWnd* pParent = NULL); 
	
	//@cmember
	/* Sets the array of user-tools the dialog is to edit.*/
	inline void SetToolsArrayPtr(CObArray* p) { m_pTools = p; }

// Dialog Data
	//{{AFX_DATA(SECUserToolsDlg)
	enum { IDD = IDD_UTM_USER_TOOLS };
	CListBox	m_lbTools;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECUserToolsDlg)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SECUserToolsDlg)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnAdd();
	TOOLKIT_API afx_msg void OnSelchangeList();
	TOOLKIT_API afx_msg void OnMoveDown();
	TOOLKIT_API afx_msg void OnMoveUp();
	TOOLKIT_API afx_msg void OnRemove();
	TOOLKIT_API afx_msg void OnChangeMenuText();
	TOOLKIT_API afx_msg void OnKillfocusMenuText();
	TOOLKIT_API virtual void OnCancel();
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
//
// customizations
//
////////////////////////////////////////////////////////////////////////////////

protected:
	CObArray* m_pTools;

	TOOLKIT_API afx_msg void OnUpdateAdd(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateRemove(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateMoveUp(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateMoveDown(CCmdUI* pCmdUI);
	TOOLKIT_API afx_msg void OnUpdateFields(CCmdUI* pCmdUI);

	SECBrowseFileEdit* m_peditCmd;
	SECBrowseDirEdit* m_peditDir;
	SECUserTool* m_pLastTool;

	TOOLKIT_API void UpdateLastTool( SECUserTool* pNewTool );

public:
	TOOLKIT_API virtual ~SECUserToolsDlg();
	
	inline SECBrowseFileEdit* GetBrowseFileEdit() {return m_peditCmd;}

	inline SECBrowseDirEdit* GetBrowseDirEdit() {return m_peditDir;}	
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// __USRTLDLG_H__

