///////////////////////////////////////////////////////////////////////////////
// SCutDlg.h
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
//  Author:			Jim Beveridge
//  Description:	Macro dialog - Definitions
//  Created:		Sun Jan 28 10:10:29 1996
//

#ifndef __SHORTCUTDLG_H__
#define __SHORTCUTDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32
#ifndef __SCUTCMDS_H__
#include "toolkit\SCutCmds.h"
#endif // __SCUTCMDS_H__

#ifndef __SCUTACCL_H__
#include "toolkit\SCutAccl.h"
#endif // __SCUTACCL_H__

//AAB #include "resource.h"

#include <StingrayExportDefs.h>

#ifdef _SECDLL
        #undef AFXAPP_DATA
        #define AFXAPP_DATA AFXAPI_DATA
        #undef AFX_DATA
        #define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

/////////////////////////////////////////////////////////////////////////////
// SECShortcutDlg dialog

/////////////////////////////
// AutoDuck tag block block for SECShortcutDlg 


// adinsert AutoDuck insertion point for SECShortcutDlg 
//@doc SECShortcutDlg 
//@class The SECShortcutDlg is a dialog class that provides a front end for entering application macros. It presents a standard
// dialog for accelerator key entry to the application.
//@comm See the SHORTCUT sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\SHORTCUT directory for a demonstration of this class.
//@BASE public|CDialog
//@xref<c SECShortcutTable> <c SECCommandList>
class SECShortcutDlg : public CDialog
{
// Construction
//@access Public Members
public:
	// standard constructor
	//@cmember
	/* The standard constructor creates an SECShortcutDlg instance.*/
	TOOLKIT_API SECShortcutDlg(SECCommandList& commandList, SECShortcutTable& shortcuts, CWnd* pParent = NULL);

	//@cmember
	/* The SECCommandList object associated with the shortcut dialog. Initiated in the constructor.*/
	SECCommandList&		m_Commands;
	//@cmember
	/* The SECShortcutTable object associated with the shortcut dialog. Initiated in the constructor.*/
	SECShortcutTable&	m_Shortcuts;

	BOOL				m_bDirty;

// Dialog Data
	//{{AFX_DATA(SECShortcutDlg)
	enum { IDD = IDD_SHORTCUT_KEYS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	TOOLKIT_API void UpdateKeys();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECShortcutDlg)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CListBox*		m_pctlNames;

		// Generated message map functions
	//{{AFX_MSG(SECShortcutDlg)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnSelchangeShortcutNameList();
	TOOLKIT_API afx_msg void OnShortcutRemove();
	TOOLKIT_API afx_msg void OnShortcutCreate();
	TOOLKIT_API afx_msg void OnShortcutReset();
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

#endif //WIN32

#endif // __SCUTDIALOG_H__

