///////////////////////////////////////////////////////////////////////////////
// fdichild.h
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
//  Description:	Declarations for SECFDIChildWnd
//
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __FDICHILD_H__
#define __FDICHILD_H__

#include <StingrayExportDefs.h>

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

/////////////////////////////
// AutoDuck tag block block for SECFDIChildWnd 


// adinsert AutoDuck insertion point for SECFDIChildWnd 
//@doc SECFDIChildWnd 
//@class Class SECFDIChildWnd derives from SECFrameWnd and provides the implementation for the FDI child window. The 
// SECFDIChildWnd class is the base class for all FDI child windows.  If you are converting an MDI application to FDI,
// rederive your MDI child windows from SECFDIChildWnd.  
//@comm See the FDI sample in the \SAMPLES\TOOLKIT\STANDARD\MDI directory for a demonstration of this class.
//@xref<c SECFDIFrameWnd>
//@BASE public|SECFrameWnd

// Exported through base class. 
class SECFDIChildWnd : public SECFrameWnd
{
    TOOLKIT_DECLARE_DYNCREATE(SECFDIChildWnd);


protected:
	TOOLKIT_API static int s_xInit;
	TOOLKIT_API static int s_yInit;
	HMENU m_hMenu;
	
// Construction

public:
	//@Access Constructors/Destructors
	//@cmember
	/* Class constructor*/
    TOOLKIT_API SECFDIChildWnd();

    TOOLKIT_API virtual ~SECFDIChildWnd();
    
	//@Access Initializations
	//@cmember
	/* Creates the Windows frame window object. */
	TOOLKIT_API BOOL Create(LPCTSTR lpszClassName,
				            LPCTSTR lpszWindowName,
							DWORD dwStyle = WS_OVERLAPPEDWINDOW,
							const RECT& rect = rectDefault,
							CWnd* pParentWnd = NULL,        // != NULL for popups
							LPCTSTR lpszMenuName = NULL,
							DWORD dwExStyle = 0,
							CCreateContext* pContext = NULL);
			
// Attributes

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(SECFDIChildWnd)
	public:
    //@Access Overrideables
	//@cmember
	/* Loads the Windows object along with the resources and associates it with the SECFDIChildWnd object*/
		TOOLKIT_API virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//@cmember
	/* Sets the calling window as the active window and brings it to the top of the Z-order*/
		TOOLKIT_API virtual void ActivateFrame(int nCmdShow = -1);
		TOOLKIT_API virtual BOOL DestroyWindow();
	protected:
	//@cmember
	/* Override to specify initial size of the window*/
		TOOLKIT_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    //{{AFX_MSG(SECFDIChildWnd)
    TOOLKIT_API afx_msg void OnWindowNew();
	TOOLKIT_API afx_msg void OnClose();
	TOOLKIT_API afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	TOOLKIT_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	TOOLKIT_API afx_msg BOOL OnNcActivate(BOOL bActive);
	//}}AFX_MSG
    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __FDICHILD_H__

