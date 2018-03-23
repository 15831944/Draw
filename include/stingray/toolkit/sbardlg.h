///////////////////////////////////////////////////////////////////////////////
// sbardlg.h
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
//  Description:	Declarations for SECDialogBar
//  Created:		May 1996
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifdef WIN32

#ifndef __SBARDLG_H__
#define __SBARDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

// CDockBar is an private, undocumented MFC class that we subclass.
// Hence, the necessity to include afxpriv.h
#ifndef __AFXPRIV_H__
#include "afxpriv.h"
#endif

#ifndef __SBARCORE_H__
#include "toolkit\sbarcore.h"
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

//////////////////////////////////////////////////////////////////////
// SECCDialogBar

/////////////////////////////
// AutoDuck tag block block for SECDialogBar 


// adinsert AutoDuck insertion point for SECDialogBar 
//@doc SECDialogBar 
//@class SECDialogBar is an interface equivalent replacement for CDialogBar and serves as the 
// base class for all of your dialog bars.  
//@comm 
// SECDialogBar does nothing more than rederive from <c SECControlBar>, so that all member 
// variables and implementation details exist to facilitate sizing while docked, etc.  No member 
// variables or functions are introduced by this class.  (NOTE: All dialog bars formally derived 
// from CDialogBar must be  rederived from SECDialogBar.  No CDialogBars are allowed when using 
// Objective Toolkit’s docking window enhancements as they lack the member variables required to 
// perform the sizing calculations.)
//
// See the VIZ sample in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\VIZ directory for a demonstration of this class.
//@xref <c SECControlBar> <c SECToolbar>
//@base public | SECControlBar

// Exported through Base Class
class SECDialogBar : public SECControlBar
{
	TOOLKIT_DECLARE_SERIAL(SECDialogBar)

// Construction
public:
	//@cmember
	/* Constructs an SECDialogBar object.*/

	TOOLKIT_API SECDialogBar();


	/*BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, UINT nID,
		DWORD dwStyle, DWORD dwExStyle, const RECT& rect, CWnd* pParentWnd = NULL,
		CCreateContext* pContext = NULL);*/


	//@cmember
	/* Creates an instance of SECDialogBar. */
	inline BOOL Create(CWnd* pParentWnd, UINT nIDTemplate,UINT nStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,DWORD dwExStyle = CBRS_EX_STDCONTEXTMENU, UINT nID = 1)
		{ return Create(pParentWnd, MAKEINTRESOURCE(nIDTemplate), nStyle, dwExStyle, nID); };

	//@cmember
	/* Creates an instance of SECDialogBar.*/
	TOOLKIT_API BOOL Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName,UINT nStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,DWORD dwExStyle = CBRS_EX_STDCONTEXTMENU, UINT nID = 1);
	TOOLKIT_API virtual void GetBarInfo(SECControlBarInfo* pInfo);

// Implementation
public:
	TOOLKIT_API virtual ~SECDialogBar();
	TOOLKIT_API virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	CSize m_sizeDefault;

protected:
	int m_nResourceID;

#ifndef _AFX_NO_OCC_SUPPORT
	// data and functions necessary for OLE control containment
	_AFX_OCC_DIALOG_INFO* m_pOccDialogInfo;
	LPCTSTR m_lpszTemplateName;
	TOOLKIT_API virtual BOOL SetOccDialogInfo(_AFX_OCC_DIALOG_INFO* pOccDialogInfo);
	TOOLKIT_API afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
#endif

// Generated message map functions
public:
    //{{AFX_MSG(SECDialogBar)
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
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

#endif // __SBARDLG_H__

#endif // WIN32

