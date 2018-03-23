///////////////////////////////////////////////////////////////////////////////
// tbarpage.h
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
//  Description:	Declarations for SECToolBarSheet/Page
//  Created:		May 1996
//

#ifdef WIN32

#ifndef __TBARPAGE_H__
#define __TBARPAGE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECRES_H__
#include "toolkit\secres.h"
#endif

#ifndef __TBARCUST_H__
#include "toolkit\tbarcust.h"
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
class SECCustomizeToolBar;
class SECCustomToolBar;


/////////////////////////////////////////////////////////////////////////////
// SECToolBarSheet
//
/////////////////////////////
//@doc SECCustomToolBar
//@mfunc   | SECToolBarSheet | SECToolBarSheet | The number of buttons currently on the toolbar.
//@syntax SECToolBarSheet(UINT nIDCaption = IDS_TOOLBAR_CUSTOMIZE, Cwnd* pParentWnd = NULL, UINT iSelectPage = 0 : CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {}
//@syntax SECToolBarSheet(LPCTSTR nIDCaption, Cwnd* pParentWnd = NULL, UINT iSelectPage = 0 : CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {}
//@parm UINT | nIDCaption | Caption ID for toolbar property sheet.
//@parm LPCTSTR | nIDCaption | Resource name of caption for toolbar property sheet.
//@parm Cwnd* | pParentWnd | The parent window.
//@parm UINT | iSelectPage | Index of selected property sheet page.


// AutoDuck tag block block for SECToolBarSheet 
// adinsert AutoDuck insertion point for SECToolBarSheet 
//@doc SECToolBarSheet 
//@class The SECToolBarSheet class constructs a property sheet used in conjunction 
// with toolbar button templates created by the classes SECToolBarCmdPage and 
// SECToolBarsPage.  
//@comm
// SECToolBarSheet supports a Customize dialog that lets the user 
// create a custom toolbar with a set of buttons in a style geared toward a particular 
// task.  This dialog displays a list of toolbars to the user, and allows the user to 
// manipulate these toolbars.  Through the toolbar dialog, the user can choose between 
// large or small buttons, tooltips enabled or disabled, and conventional appearance 
// or the new cool look.
//
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration of 
// this class.
//@xref <c SECCustomToolBar> <c SECToolBarCmdPage>
//@base public | CPropertySheet
class SECToolBarSheet : public CPropertySheet
{
// Construction
public:

	// If an ASSERT fires inside constructor, it is possible youd
	// did not include the Objective Toolkit resources. Please consult
	// the OT user's guide for the proper method of inclusion.
	//@cmember
	/* todo Add a description*/
	TOOLKIT_API SECToolBarSheet(UINT nIDCaption = IDS_TOOLBAR_CUSTOMIZE, CWnd* pParentWnd = NULL, UINT iSelectPage = 0) :
				CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {m_psh.dwFlags |= PSH_NOAPPLYNOW;}

	TOOLKIT_API SECToolBarSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0) :
				CPropertySheet(pszCaption, pParentWnd, iSelectPage) {m_psh.dwFlags |= PSH_NOAPPLYNOW;}

protected:
	// Implementation, data members.

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg LRESULT OnFloatStatus(WPARAM, LPARAM);
	TOOLKIT_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};


/////////////////////////////////////////////////////////////////////////////
// SECBtnGroup - Describes and manages the UI for a group of buttons
//
class SECBtnGroup : public CObject
{
public:
	TOOLKIT_API SECBtnGroup(const CString& strTitle, UINT nBtnCount, UINT* lpBtnIDs);
	TOOLKIT_API virtual ~SECBtnGroup();

	// Creates the user interface.
	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, SECToolBarManager* pManager, UINT nID) = 0;

	// Called to layout the user interface.
	inline virtual void DoSize(CRect& /* rect */) {}

	// Called to switch the user interface into config mode.
	inline virtual void EnableConfigMode(BOOL /* bEnable */) {}

	// Returns the window associated with the user interface
	TOOLKIT_API CWnd*   GetWnd() const;

	// Returns the title of this group
	TOOLKIT_API LPCTSTR GetTitle() const;

protected:
	CWnd*	m_pWnd;						// Pointer to groups window
	CString m_lpszTitle;				// Btn group title
	UINT    m_nBtnCount;				// No. of btns in group
	UINT*   m_lpBtnIDs;					// List of btn IDs.

private:
	TOOLKIT_API SECBtnGroup();
};

inline CWnd* SECBtnGroup::GetWnd() const { return m_pWnd; }
inline LPCTSTR SECBtnGroup::GetTitle() const { return m_lpszTitle; }


/////////////////////////////////////////////////////////////////////////////
// SECTBtnGroup - Describes and manages the UI for a group of toolbar
//                buttons
//
class SECTBBtnGroup : public SECBtnGroup
{
public:
	TOOLKIT_API SECTBBtnGroup(LPCTSTR lpszTitle, UINT nBtnCount, UINT* lpBtnIDs);

	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, SECToolBarManager* pManager, UINT nID);
	TOOLKIT_API virtual void DoSize(CRect& rect);
	TOOLKIT_API virtual void EnableConfigMode(BOOL bEnable);
};


/////////////////////////////////////////////////////////////////////////////
// SECMenuBtnGroup - Describes and manages the UI for a group of menu
//                   buttons
//
class SECMenuBtnGroup : public SECBtnGroup
{
public:
	TOOLKIT_API SECMenuBtnGroup(LPCTSTR lpszTitle, UINT nBtnCount, UINT* lpBtnIDs);

	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, SECToolBarManager* pManager, UINT nID);
};


/////////////////////////////////////////////////////////////////////////////
// SECMenuListBox - implements a listbox of menus (which can be tracked
//                  to a toolbar.
//
class SECMenuListBox : public CListBox
{
	TOOLKIT_DECLARE_DYNAMIC(SECMenuListBox)

public:
	TOOLKIT_API SECMenuListBox();
	inline virtual ~SECMenuListBox() {}

	TOOLKIT_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	TOOLKIT_API void SetManager(SECToolBarManager* pManager);

protected:
	SECToolBarManager* m_pManager;			// Pointer to toolbar manager

	BOOL m_bWinVerLessThan4;
	TOOLKIT_API UINT MenuItemFromPoint(CPoint pt, BOOL& bOutside) const;

	TOOLKIT_DECLARE_MESSAGE_MAP()
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

inline void SECMenuListBox::SetManager(SECToolBarManager* pManager)
{
	m_pManager = pManager;
}


/////////////////////////////////////////////////////////////////////////////
// SECToolBarCmdPage
//
/////////////////////////////
// AutoDuck tag block block for SECToolBarCmdPage 

// adinsert AutoDuck insertion point for SECToolBarCmdPage 
//@doc SECToolBarCmdPage 
//@class The <c SECToolBarCmdPage> class presents all the available toolbar buttons to 
// the user.  These buttons can be dragged onto an existing toolbar or used to 
// create a new toolbar.  SECToolBarCmdPage should only be used in an SECToolBarSheet 
// (cannot be used directly in a CPropertySheet).
// The developer should use the DefineBtnGroup function to define at least one button 
// group.  Also, SECToolBarCmdPage needs to be used in conjunction with a toolbar 
// manager.  
// @ex The following example might make this clearer: |
//  SECToolBarSheet sheet;
//  SECToolBarCmdPage page;
//	static UINT BASED_CODE fileButtons[4] =
//	{
//		ID_FILE_NEW,
//		ID_FILE_OPEN,
//		ID_FILE_SAVE,
//		ID_FILE_SAVE_ALL
//	};
//	static UINT BASED_CODE editButtons[3] =
//	{
//		ID_EDIT_COPY,
//		ID_EDIT_CUT,
//		ID_EDIT_PASTE
//	};
//	page.SetManager(m_pManager);
//	page.DefineBtnGroup(_T("File"), 4, &fileButtons);
//	page.DefineBtnGroup(_T("Edit"), 3, &editButtons);
//	sheet.AddPage(&page);
//
//sheet.DoModal();
//
//See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration of this class.
//@xref <c SECToolBarSheet> <c SECToolBarManager> <c SECCustomToolbar> <c SECToolBarsDlg>
//@base public | CPropertyPage
class SECToolBarCmdPage : public CPropertyPage
{
	TOOLKIT_DECLARE_DYNCREATE(SECToolBarCmdPage)

// Construction
public:
	//@cmember
	/* Constructs an SECToolBarCmdPage object.*/
	TOOLKIT_API SECToolBarCmdPage();
	//@cmember
	/* Constructs an SECToolBarCmdPage object.*/
	TOOLKIT_API SECToolBarCmdPage(UINT nIDTemplate, UINT nIDCaption = 0);
	//@cmember
	/* Constructs an SECToolBarCmdPage object.*/
	TOOLKIT_API SECToolBarCmdPage(LPCTSTR lpszTemplate, UINT nIDCaption = 0);

protected:
	TOOLKIT_API void Initialize();

// Attributes
public:
	enum { IDD = IDD_TOOLBAR_CUSTOMIZE };

// Operations
public:
	//@cmember
	/* Defines the toolbar manager.*/
	TOOLKIT_API void SetManager(SECToolBarManager* pManager);
	//@cmember
	/* Defines a button group, consisting of a title and an array of button IDs*/
	TOOLKIT_API void DefineBtnGroup(LPCTSTR lpszTitle, int nBtnCount, UINT* lpBtnIDs);
	TOOLKIT_API void DefineMenuGroup(LPCTSTR lpszTitle, int nBtnCount, UINT* lpBtnIDs);

	// Adds a menu item group (containing all menu items in the button map)
	TOOLKIT_API void DefineMenuGroup(LPCTSTR lpszTitle);

	// Sets the button description based on id passed in
	TOOLKIT_API virtual void SetDescription(int nID);

// Overrideables
protected:
	TOOLKIT_API virtual BOOL OnSetActive();
	TOOLKIT_API virtual BOOL OnKillActive();
	TOOLKIT_API virtual void OnReset();

// Implementation
public:
	TOOLKIT_API virtual ~SECToolBarCmdPage();

protected:
	TOOLKIT_API SECCustomToolBar* GetControlBar(UINT nID);

	TOOLKIT_API const SECBtnMapEntry* GetMapEntryFromID(UINT nID,const SECBtnMapEntry* pRoot);

	// Nested class implementation, data members.
	class CGroupArray : public CObArray
	{
	public:
		// Accessing elements
		inline SECBtnGroup* GetAt(int nIndex) const { return (SECBtnGroup*)CObArray::GetAt(nIndex); }
		inline SECBtnGroup*& ElementAt(int nIndex) { return (SECBtnGroup*&)CObArray::ElementAt(nIndex); }
		inline void SetAt(int nIndex, SECBtnGroup* ptr) { CObArray::SetAt(nIndex, ptr); }

		// Potentially growing the array
		inline void SetAtGrow(int nIndex, SECBtnGroup* newElement) { CObArray::SetAtGrow(nIndex, newElement); }
		inline SEC_INT Add(SECBtnGroup* newElement) { return CObArray::Add(newElement); }
		inline SEC_INT Append(const CGroupArray& src) { return CObArray::Append(src); }
		inline void Copy(const CGroupArray& src) { CObArray::Copy(src); }

		// Operations that move elements around
		inline void InsertAt(int nIndex, SECBtnGroup* newElement, int nCount = 1)
			{ CObArray::InsertAt(nIndex, newElement, nCount); }
		inline void InsertAt(int nStartIndex, CGroupArray* pNewArray)
		   { CObArray::InsertAt(nStartIndex, pNewArray); }

		// overloaded operator helpers
		inline SECBtnGroup* operator[](int nIndex) const
			{ return (SECBtnGroup*)CObArray::operator[](nIndex); }
		inline SECBtnGroup*& operator[](int nIndex)
			{ return (SECBtnGroup*&)CObArray::operator[](nIndex); }
	} m_btnGroups;							// Array of btn groups

	SECToolBarManager* m_pManager;			// My toolbar manager
	int                m_nCurSel;			// The currently selected btn group
	UINT*              m_lpMenuIDs;			// Used to hold dynamic list of menu IDs

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API virtual BOOL OnInitDialog();
	TOOLKIT_API afx_msg void OnSelChange();
	TOOLKIT_API afx_msg LRESULT OnBarNotify(WPARAM nID, LPARAM lParam);
	TOOLKIT_API afx_msg LRESULT OnToolBarStyleChanging(WPARAM nEvent, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
// SECCustomizeToolBar
//
/////////////////////////////
// AutoDuck tag block block for SECCustomizeToolBar 

// adinsert AutoDuck insertion point for SECCustomizeToolBar 
//@doc SECCustomizeToolBar 
//@class The SECCustomizeToolBar class manages the sizing of a user-defined, custom 
// toolbar having buttons geared toward a particular task.
//@comm
// See the sample TOOLBAR in the \SAMPLES\TOOLKIT\STANDARD\DOCKING\TOOLBAR directory for a demonstration 
// of this class.
//@xref <c SECCustomToolBar> <c SECToolBarSheet> <c SECToolBarCmdPage>
//@base public | SECCustomToolBar
class SECCustomizeToolBar : public SECCustomToolBar
{
// Construction
public:
	//@cmember
	/* Constructs an <c SECCustomizeToolBar> object.*/
	TOOLKIT_API SECCustomizeToolBar();

	TOOLKIT_DECLARE_DYNAMIC(SECCustomizeToolBar);

// Operations
public:
	//@cmember
	/* Dynamically sizes the toolbar rectangle.*/
	TOOLKIT_API virtual void DoSize(CRect& rect);

// Overrideables
protected:
	//@cmember
	/* Balances the wrapping of the toolbar.*/
	TOOLKIT_API virtual void BalanceWrap(int nRow, Wrapped* pWrap);
	//@cmember
	/* Returns TRUE if the default drag mode is to add.*/
	TOOLKIT_API virtual BOOL GetDragMode() const;
	//@cmember
	/* Returns TRUE if the toolbar accepts dropped buttons.*/
	TOOLKIT_API virtual BOOL AcceptDrop() const;
};

// Function to convert Dialog Base Units into pixels.
extern TOOLKIT_API void SECConvertDialogUnitsToPixels(HFONT hFont, int& cx, int& cy);

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBARPAGE_H__

#endif // WIN32

