///////////////////////////////////////////////////////////////////////////////
// WkSExDlg.h
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
//  Author:			Mark Isham
//  Description:	

#ifndef __WKSEXDLG_H__
#define __WKSEXDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

#ifndef __LSTBXEDT_H__
#include "toolkit\lstbxedt.h"
#endif

#include <StingrayExportDefs.h>

class SECToolBarManager;

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

class SECWsMgrDialogEx;

/////////////////////////////////////////////////////////////////////////////
// SECWSLBEditorEx

class TOOLKIT_API SECWSLBEditorEx : public SECListBoxEditor
{
public:
	SECWSLBEditorEx(CStringList& listOrigWorkspaces,
					CStringList& listNewWorkspaces,	
					CStringList& listDeletedWorkspaces,
					SECWsMgrDialogEx* pParent);
					
protected:
	// virtual overrides
	virtual void OnEditingJustStarted();
	virtual void OnEditingStopped();
	virtual void OnItemRenamed(int nIndexRenamed,CString strOldName,CString NewName);
	virtual void OnItemAdded(int nIndexNewItem,CString strTextInserted);
	virtual void OnItemMoved(int nOldIndex,int nNewIndex,CString strTextMoved,BOOL WasDragged);
	virtual BOOL OnItemDelete(int nIndexToBeDeleted,CString strTextDeleted);
	
	// implementation
	BOOL ReplaceListBoxItem(CListBox* pLB,int iIndex,CString strNewText);
	BOOL MoveStrings(int nOldIndex,int nNewIndex,CStringList& strList);
	
	CStringList& m_listOrigWorkspaces;			// list with original workspace names
	CStringList& m_listNewWorkspaces;			// list with latest workspaces names
	CStringList& m_listDeletedWorkspaces;		// list of all removed workspaces	
	SECWsMgrDialogEx* m_pParent;	
};


/////////////////////////////////////////////////////////////////////////////
// SECWorkspaceManagerDialog

class SECWsMgrDialogEx : public CDialog
{
// Construction
public:
	TOOLKIT_API SECWsMgrDialogEx(CStringList& listOrigWorkspaces,
					 CStringList& listNewWorkspaces,		
					 CStringList& listDeletedWorkspaces,
					 CString& strActionWorkspace,
					 BOOL bAllowOpen,BOOL bAllowSave,
					 CWnd* pParent = NULL);

	TOOLKIT_API virtual ~SECWsMgrDialogEx();
	
	TOOLKIT_API void SetOpenSaveButtons(BOOL bEnableOpen,BOOL bEnableSave);

// Dialog Data
	//{{AFX_DATA(SECWsMgrDialogEx)
	enum { IDD = IDD_OPEN_WORKSPACE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{Afx_VIRTUAL(SECWsMgrDialogEx)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	SECWSLBEditorEx* m_pLBEditor;
	CStringList& m_listOrigWorkspaces;
	CString& m_strActionWorkspace;				// name of workspace receiving the action
	BOOL m_bNT351;
	BOOL m_bAllowOpen,m_bAllowSave;

	// Generated message map functions
	//{{AFX_MSG(SECWsMgrDialogEx)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnApplyWorkspace();
	TOOLKIT_API afx_msg void OnDone();
	TOOLKIT_API afx_msg void OnPaint();
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

#endif // WIN32

#endif // __WKSEXDLG_H__
