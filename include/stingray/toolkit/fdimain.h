///////////////////////////////////////////////////////////////////////////////
// fdimain.h
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
//  Author:			Dean Hallman
//  Description:	Declarations for SECFDIFrameWnd
//

#ifndef __FDIMAIN_H__
#define __FDIMAIN_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SWINFRM_H__
#include "toolkit\swinfrm.h"
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

// adinsert AutoDuck insertion point for SECFDIFrameWnd 
//@doc SECFDIFrameWnd 
//@class SECFDIFrameWnd is derived from SECFrameWnd. The SECFDIFrameWnd class is the base class for the main frame of an 
// FDI-based application.  If you are converting an MDI application to FDI, change the base class of your main frame 
// from CMDIFrameWnd to SECFDIFrameWnd.  SECFDIFrameWnd adds support for a window recently used list on the "Window" menu
// as well as a "Windows..." dialog.  This class introduces no member functions or variables which are meant to be 
// called or overridden.
//@comm See the FDI sample in the \SAMPLES\TOOLKIT\STANDARD\MDI directory for a demonstration of this class.
//@xref<c SECFDIChildWnd>
//@BASE public|SECFrameWnd

class SECFDIFrameWnd : public SECFrameWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECFDIFrameWnd);

// Construction
public:

	CPtrList m_children;

protected:
	 
	CWnd* m_pActiveWnd;


public:
    TOOLKIT_API SECFDIFrameWnd();

	TOOLKIT_API void AddWindow(CWnd* pWnd);
	TOOLKIT_API void RemoveWindow(CWnd* pWnd);
	TOOLKIT_API void SetActiveWindow(CWnd* pWnd);
	TOOLKIT_API CWnd* GetActiveWindow() const;
	TOOLKIT_API virtual ~SECFDIFrameWnd();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECFDIFrameWnd)
public:
	TOOLKIT_API virtual CFrameWnd* GetActiveFrame();
	//}}AFX_VIRTUAL
    
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

	TOOLKIT_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		                              AFX_CMDHANDLERINFO* pHandlerInfo);

// Operations

// Generated message map functions
protected:
    //{{AFX_MSG(SECFDIFrameWnd)
	TOOLKIT_API afx_msg BOOL OnActivateWindow(UINT nID);
	TOOLKIT_API afx_msg void OnUpdateWindowMenu(CCmdUI* pCmdUI);
	//}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////
// SECWindowsDialog dialog

/////////////////////////////
// AutoDuck tag block block for SECWindowsDialog 
// adinsert AutoDuck insertion point for SECWindowsDialog 
//@doc SECWindowsDialog 
//@class SECWindowsDialog is a utility class that is used by SECFDIFrameWnd to display and maintain the windows' list.
//@xref<c SECFDIFrameWnd> 
//@BASE public|CDialog
class SECWindowsDialog : public CDialog
{
// Construction
public:
	TOOLKIT_API SECWindowsDialog(CWnd* pParent = NULL, CPtrList* pChildren = NULL);
	
// Attributes
public:
	CPtrList* m_pChildren;

// Dialog Data
	//{{AFX_DATA(SECWindowsDialog)
	enum { IDD = IDD_WINDOWS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECWindowsDialog)
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CObList* m_pWindowList;

	// Generated message map functions
	//{{AFX_MSG(SECWindowsDialog)
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnCloseWindow();
	TOOLKIT_API virtual void OnOK();
	TOOLKIT_API afx_msg void OnSave();
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

#endif // __FDIMAIN_H__
