///////////////////////////////////////////////////////////////////////////////
// tbarsdlg.h
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
//  Authors:		Don
//  Description:	Declarations for SECToolBarsDlg/SECNewToolBar
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBARSDLG_H__
#define __TBARSDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECRES_H__
#include "toolkit\secres.h"
#endif

#ifndef __TBARMGR_H__
#include "toolkit\tbarmgr.h"
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
class SECToolBarManager;


///////////////////////////////////////////////////////////////////////////////
// SECToolBarsBase 
//
// Implements common functionality for SECToolBarsDlg and SECToolBarsPage.
//
class SECToolBarsBase
{
// Construction
protected:
	// Hide constructor, so that class cannot be instantiated directly
	TOOLKIT_API SECToolBarsBase();

// Attributes
public:
	BOOL m_bToolTips;						// TRUE if tooltips enabled
	BOOL m_bCoolLook;						// TRUE if cool look enabled
	BOOL m_bLargeButtons;					// TRUE if large buttons enabled

	// Backup values to restore upon "cancel"
	BOOL m_bOrigToolTips;					
	BOOL m_bOrigCoolLook;					
	BOOL m_bOrigLargeButtons;				

// Operations
public:
	TOOLKIT_API void SetManager(SECToolBarManager* pManager);

// Implementation
	TOOLKIT_API virtual ~SECToolBarsBase();

protected:
	inline CFrameWnd* GetFrameWnd() const { return m_pManager->GetFrameWnd(); }
	TOOLKIT_API BOOL GetCurBar(CControlBar*& pBar, int* nID = NULL);
	TOOLKIT_API int  FindIndex(UINT nID);
	TOOLKIT_API void SetWnd(CWnd* pWnd);
	TOOLKIT_API void InitDialog();
	TOOLKIT_API void FillToolBarList();
	TOOLKIT_API void SaveState();
	TOOLKIT_API void RestoreState();

	// Implementation, data members.
protected:
	SECToolBarManager* m_pManager;			// Pointer to the toolbar manager
	CCheckListBox	   m_toolbarList;		// Subclassed listbox showing list
											// of all toolbars
	CWnd*			   m_pWnd;				// Pointer to dialog window object

	// Implementation - message map entries
	TOOLKIT_API void OnSelChange();
	TOOLKIT_API void OnNameKillFocus();
	TOOLKIT_API BOOL OnNewToolbar();
	TOOLKIT_API void OnResetBtn();
	TOOLKIT_API void OnChkChange();
	TOOLKIT_API void OnToolTips();
	TOOLKIT_API void OnCoolLook();
	TOOLKIT_API void OnLargeButtons();
	TOOLKIT_API LRESULT OnBarNotify(WPARAM nID, LPARAM lParam);
};


/////////////////////////////////////////////////////////////////////////////
// SECToolBarsDlg
//
/////////////////////////////
// AutoDuck tag block block for SECToolBarsDlg 
// adinsert AutoDuck insertion point for SECToolBarsDlg 
//@doc SECToolBarsDlg 
//@class SECToolBarsDlg implements the Customize dialog, which an end user can use 
// to create a customized toolbar with buttons geared toward a particular task.  
//@comm 
// This dialog displays a list of toolbars to the user, and allows the user to manipulate these 
// toolbars.  Through the toolbar dialog, the user can choose between large or small buttons, 
// tooltips enabled or disabled, and conventional appearance or the new cool look. This 
// dialog can be invoked through the SECToolBarManager::ExecViewToolBarsDlg() method.  
// Note that if this function returns IDC_TOOLBAR_CUSTOMIZE, then the customize dialog 
// should be displayed.
//
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration of 
// this class.
//@xref <c SECToolBarsPage>  <c SECCustomToolBar>  <c SECToolBarManager>

	//@cmember
	/* Constructs an SECToolBarsDlg dialog object and associates it with a parent window.*/
class SECToolBarsDlg : public CDialog, public SECToolBarsBase
{
// Construction
public:
	/////////////////////////////
	TOOLKIT_API SECToolBarsDlg(CWnd* pParent);

// Attributes
public:
	enum { IDD = IDD_TOOLBARS };	

// Overrideables
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);

protected:
	TOOLKIT_API void Terminate(int nResult);

	// Implementation, data members.

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	TOOLKIT_API afx_msg void OnChkChange();
	TOOLKIT_API afx_msg void OnSelChange();
	TOOLKIT_API afx_msg void OnNameKillFocus();
	TOOLKIT_API afx_msg LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnBarNotify(WPARAM nID, LPARAM lParam);
	TOOLKIT_API virtual void OnOK();
	TOOLKIT_API virtual void OnCancel();
	TOOLKIT_API afx_msg void OnResetBtn();
	TOOLKIT_API afx_msg void OnNewToolbar();
	TOOLKIT_API afx_msg void OnCustomise();
	TOOLKIT_API afx_msg void OnToolTips();
	TOOLKIT_API afx_msg void OnCoolLook();
	TOOLKIT_API afx_msg void OnLargeButtons();
};


/////////////////////////////////////////////////////////////////////////////
// SECToolBarsPage property page
//
/////////////////////////////
// AutoDuck tag block block for SECToolBarsPage 

// adinsert AutoDuck insertion point for SECToolBarsPage 
//@doc SECToolBarsPage 
//@class SECToolBarsPage constructs a toolbar property page for the Customize dialog, 
// which can be used to create a toolbar with buttons geared toward a particular task.
//@comm
// Through the toolbar dialog, the user can choose between large or small buttons, 
// tooltips enabled or disabled, and conventional appearance or the new cool look.
//
// The SECToolBarsPage property page should only be embedded in an SECToolBarSheet 
// (not a CPropertySheet).
//
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration 
// of this class.
//@xref <c SECToolBarsBase>
//@base public | CPropertyPage
//@base public | SECToolBarsBase
class SECToolBarsPage : public CPropertyPage, public SECToolBarsBase
{
// Construction
public:
	//@cmember
	/* Constructs a SECToolBarsPage.*/
	TOOLKIT_API SECToolBarsPage();
	TOOLKIT_API SECToolBarsPage(UINT nIDTemplate, UINT nIDCaption = 0);
	TOOLKIT_API SECToolBarsPage(LPCTSTR lpszTemplate, UINT nIDCaption = 0);

// Attributes
public:
	enum { IDD = IDD_TOOLBARS_PAGE };

// Overrideables
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);
	TOOLKIT_API virtual BOOL OnSetActive();
	TOOLKIT_API virtual BOOL OnKillActive();
	TOOLKIT_API virtual void OnReset();
	TOOLKIT_API virtual void OnCancel();
	TOOLKIT_API virtual void OnOK();

// Implementation
public:
	TOOLKIT_API virtual ~SECToolBarsPage();

protected:
	// Notifies sibling pages of a change in toolbar style.
	TOOLKIT_API void OnStyleChanging(UINT nEvent);

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnSelChange();
	TOOLKIT_API afx_msg void OnNameKillFocus();
	TOOLKIT_API afx_msg void OnNewToolbar();
	TOOLKIT_API afx_msg void OnResetBtn();
	TOOLKIT_API afx_msg void OnChkChange();
	TOOLKIT_API afx_msg void OnToolTips();
	TOOLKIT_API afx_msg void OnCoolLook();
	TOOLKIT_API afx_msg void OnLargeButtons();
	TOOLKIT_API afx_msg LRESULT OnBarNotify(WPARAM nID, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
// SECNewToolBar dialog
//
class SECNewToolBar : public CDialog
{
// Construction
public:
	TOOLKIT_API SECNewToolBar(CWnd* pParent = NULL);

// Attributes
public:
	enum { IDD = IDD_TOOLBAR_NEW };
	CString	m_strToolBarName;				// Name of new toolbar

// Overrideables
protected:
	TOOLKIT_API virtual void DoDataExchange(CDataExchange* pDX);

protected:

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()
	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnChangeName();
};

// Registered message used by SECToolBarsPage to notify sibling pages when 
// a toolbar style is changing
extern TOOLKIT_API const int wmSECToolBarStyleChanging;

// wParam for wmSECToolBarStyleChanging.
#define TBSC_LARGEBTNS		0x0001			// Changing to large buttons
#define TBSC_COOLLOOK		0x0002			// Changing to cool look

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBARSDLG_H__

#endif // WIN32

