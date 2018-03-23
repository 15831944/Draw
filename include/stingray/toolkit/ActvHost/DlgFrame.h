///////////////////////////////////////////////////////////////////////////////
// DlgFrame.h
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

#ifndef __SECDLGFRAME_H_
#define __SECDLGFRAME_H_

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
// SECADlgFrame frame

// SEC_SDIFRAMEWND maps to SECFrameWnd of _SEC_DOCKWINDOWS is defined (as set by
// the build wizard if docking windows support was checked off), or CFrameWnd
// if it is not defined.

//@doc SECAFloatDocTemplate 
//@class Frame window for use by SECAFloatDocTemplate to allow scriptable frame creation.
//@BASE public | SEC_SDIFRAMEWND
//@comm
// This frame implements a simple SDI top level frame to be utilized by ActiveScript
// scripts during dynamic form creation. SEC_SDIFRAMEWND is a macro that expands
// to SECFrameWnd if Stingray docking windows have been installed (selected via the
// BuildWizard) or CFrameWnd if not.
//@xref <c SECAFloatDocTemplate> <c SECAFormObj>
class SECADlgFrame : public SEC_SDIFRAMEWND
{
	TOOLKIT_DECLARE_DYNCREATE(SECADlgFrame)

protected:
	TOOLKIT_API SECADlgFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECADlgFrame)
protected:
	TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	TOOLKIT_API virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	TOOLKIT_API virtual ~SECADlgFrame();

	// Generated message map functions
	//{{AFX_MSG(SECADlgFrame)
	TOOLKIT_API afx_msg void OnAppExit();
	TOOLKIT_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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

#endif		// __SECDLGFRAME_H_

/////////////////////////////////////////////////////////////////////////////
