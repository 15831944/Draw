///////////////////////////////////////////////////////////////////////////////
// MiniFloatWnd.h
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
// Description:  Declaration of SECLayoutMiniFloatWnd base
//

#ifndef __SECLAYOUTMINIFLOATWND_H__
#define __SECLAYOUTMINIFLOATWND_H__

// Header Includes
#include "toolkit\layout\docking\DragDrop\DockListn.h"
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
// SECLayoutMiniFloatWnd

class SECLayoutMiniFloatWnd : public CMiniFrameWnd
{
	TOOLKIT_DECLARE_DYNCREATE(SECLayoutMiniFloatWnd)

public:
// Construction
	TOOLKIT_API SECLayoutMiniFloatWnd();
	TOOLKIT_API virtual ~SECLayoutMiniFloatWnd();

	TOOLKIT_API virtual BOOL Create(CWnd* pParent,SECLayoutNode* pRootNode,LPCTSTR lpszTitle,
									BOOL bHideOnClose,BOOL bCloseEnabled);
	TOOLKIT_API virtual BOOL DisplayAndAutoInit(const CRect& rcScreenDisplay,SECLNDockingMgr* pMgr=NULL);
	TOOLKIT_API virtual void ClearListener();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECLayoutMiniFloatWnd)
	public:
	//}}AFX_VIRTUAL

protected:
	virtual SECDockingListener* CreateDockingListener() { return new SECDockingListener; }

// Implementation
public:
	inline SECLayoutNode* GetFloatRootNode() { return m_pRootLayoutNode; }

	//{{AFX_MSG(CMiniFrameWnd)
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnClose();
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	TOOLKIT_DECLARE_MESSAGE_MAP()

protected:
	SECLayoutNode* m_pRootLayoutNode;
	SECDockingListener* m_pListener;
	BOOL m_bHideOnClose;
};

/////////////////////////////////////////////////////////////////////////////
// SECLNFloatingHwndContainer

// This derived container class is used to create and administrate
// a floating frame window used for dock floating operations.

class SECLNFloatingHwndContainer : public SECLNHwndContainer 
{
public:
	TOOLKIT_API SECLNFloatingHwndContainer(HWND hContainerWnd);	
	TOOLKIT_API virtual ~SECLNFloatingHwndContainer();	

	// Overrides
	TOOLKIT_API virtual BOOL NodeToClient(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL NodeToClient(LPRECT lpRect);
	TOOLKIT_API virtual BOOL ClientToNode(LPPOINT lpPoint);
	TOOLKIT_API virtual BOOL ClientToNode(LPRECT lpRect);
	
	TOOLKIT_API virtual BOOL QueryNonClientMargins(UINT& nLeft,UINT& nTop,
									UINT& nRight,UINT& nBottom);	
	TOOLKIT_API virtual BOOL DisplayContainer(const CRect& rcScreenDisplay);

	TOOLKIT_API virtual BOOL IsContainerVisible();

	// New methods
	inline void SetAutoInitDockMgr(SECLNDockingMgr* pMgr) { m_pAutoInitDockMgr=pMgr; }
	inline SECLNDockingMgr* GetAutoInitDockMgr() { return m_pAutoInitDockMgr; }
	TOOLKIT_API virtual BOOL CreateFloatingFrameWnd(SECLayoutNode* pRootNode,CWnd* pOwnerWnd,
										LPCTSTR lpszTitle=NULL,
										BOOL bHideOnClose=TRUE,
										BOOL bCloseEnabled=TRUE);

	inline SECLayoutMiniFloatWnd* GetFloatingFrame() { return m_pWndFloating; }

protected:
	// Overridables
	TOOLKIT_API virtual SECLayoutMiniFloatWnd* CreateMiniFloatWnd(); 

protected:
	// Implementation
	SECLayoutMiniFloatWnd* m_pWndFloating;
	UINT m_nNCMarginLeft,m_nNCMarginTop;
	SECLNDockingMgr* m_pAutoInitDockMgr;
	
	TOOLKIT_API static CTypedPtrList<CPtrList,SECLayoutMiniFloatWnd*> m_listOldMiniFloatWnds;
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


#endif //__SECLAYOUTMINIFLOATWND_H__
