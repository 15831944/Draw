///////////////////////////////////////////////////////////////////////////////
// LayListn.h : Declaration of SECLayoutWndListner
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
// Author:       Mark Isham
// Description:  Declaration of SECLayoutWndListener 
//
// SECLayoutWndListener base class
// A SECLayoutWndListener objects will listen for the appropriate window
// messages to automate the invocation of the proper layout recalcs.

#ifndef __SECLAYOUT_LISTENER_H__
#define __SECLAYOUT_LISTENER_H__

// Header Includes

#ifndef __SECLAYOUTNOD_H__
#include "toolkit\layout\layoutnd.h"
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

/////////////////////////////////////////////////////////////////////////////
// SECLayoutWndListener

//@doc SECLayoutWndListener 
//@class Layout window message listener class
//@BASE public | SECWndListener
class SECLayoutWndListener : public stingray::foundation::SECWndListener
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:

	// Initialization/Destruction
	TOOLKIT_API SECLayoutWndListener();
	TOOLKIT_API virtual ~SECLayoutWndListener();

	//@cmember
	/* Configure the layout node to receive listener notifications*/
	TOOLKIT_API virtual BOOL SetListenNode(SECLayoutNode* pLayoutNode);

	//@cmember
	/* Retrieve the layout node receiving listener notifications*/
	TOOLKIT_API virtual SECLayoutNode* GetListenNode();
	
	// Accessor to discontinue OnSize Recalc/Realize processing
	inline virtual void EnableOnSizeRecalcProcessing(BOOL bEnable=TRUE) { m_bOnSizeRecalc=bEnable; }
	inline BOOL GetOnSizeRecalcProcessingEnablement() { return m_bOnSizeRecalc; }

	// Operations
	//@cmember
	/* Initializes a listener bridge between a window and layout node*/
	TOOLKIT_API virtual BOOL AutoInit(SECLayoutNode* pRootNode,CWnd* pParent,BOOL bDialogProc=TRUE,BOOL bDoRecalc=TRUE,BOOL bInitUsingWindowRect=FALSE);

	//@cmember
	/* Initializes a listener bridge between a window and layout node*/
	TOOLKIT_API virtual BOOL AutoInit(SECLayoutNode* pRootNode,CWnd* pParent,const CRect& rectNodeInitial,BOOL bDialogProc=TRUE,BOOL bDoRecalc=TRUE);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECLayoutWndListener)
	//}}AFX_VIRTUAL

protected:

	// Implementation Member Variables
	SECLayoutNode* m_pLayoutNode;
	BOOL m_bUseWindowRect;
	BOOL m_bOnSizeRecalc;

	// Generated message map functions
protected:
	//{{AFX_MSG(SECLayoutWndListener)
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SECLAYOUT_LISTENER_H__

