///////////////////////////////////////////////////////////////////////////////
// SECBoxEx.h
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
//		Author:		Brad		January 1999
//

#ifndef __SECCOMBOBOXEX_H__
#define __SECCOMBOBOXEX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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
// SECComboBoxEx window
//

const UINT SECCOMBOEX_NEWITEM = RegisterWindowMessage( _T("secComboExNewItem") );
const UINT SECCOMBOEX_APPLY   = RegisterWindowMessage( _T("secComboExApply") );

/////////////////////////////
// AutoDuck tag block block for SECComboBoxEx 

//@doc SECComboBoxEx
//@mdata UINT  | SECComboBoxEx | m_vkDelimiterKey | The delimiter key for the control.
//@xref <c SECComboBoxEx> <mf SECComboBoxEx::SetDelimiterKey>

//@doc SECComboBoxEx
//@mdata CString  | SECComboBoxEx | m_strDelimiter | The delimiter string for the control.
//@xref <c SECComboBoxEx> <mf SECComboBoxEx::SetDelimiterString>

//@doc SECComboBoxEx
//@mdata UINT  | SECComboBoxEx | m_nLastKey | The last key pressed in the control.
//@xref <c SECComboBoxEx>

//@doc SECComboBoxEx
//@mdata BOOL  | SECComboBoxEx | m_bCaseSensitive | Determines if control searches in 
// a case sensitive manner.
//@xref <c SECComboBoxEx> <mf SECComboBoxEx::SetCaseSensitive>

//@doc SECComboBoxEx
//@mfunc void  | SECComboBoxEx | SetCaseSensitive | Sets the case sensitivity of the control.
//@parm BOOL | bEnable | If TRUE, user entries must match case of combobox items in order for
// auto-complete to work.
//@xref <c SECComboBoxEx>

// adinsert AutoDuck insertion point for SECComboBoxEx 
//@doc SECComboBoxEx 
//@class SECComboBoxEx implements an enhanced CComboBoxEx, implementing
// auto-completion features. 
//@comm For the parent window to receive notification of the user pressing the Enter key, 
// the parent must handle the SECCOMBOEX_NEWITEM message.  The SECCOMBOEX_APPLY 
// message is sent after the SECCOMBOEX_NEWITEM message is handled successfully and 
// the new string has been added, or after an existing entry has been selected and the 
// Enter key pressed.
//@base public | CComboBoxEx
class SECComboBoxEx : public CComboBoxEx
{
	//@access Creation/Initialization

public:
	TOOLKIT_API SECComboBoxEx();

	//@access Attributes
public:

	//@cmember
	/* Sets the case sensitivity of the control for selecting items.*/
	inline void SetCaseSensitive(BOOL bEnable) { m_bCaseSensitive=bEnable; }
	
	//@cmember
	/* Sets the delimiter key for the control.*/
	TOOLKIT_API void SetDelimiterKey(UINT vkDelim);

	//@cmember
	/* Sets the delimiter string for the control.*/
	TOOLKIT_API void SetDelimiterString(LPCTSTR strDelim);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECComboBoxEx)
public:
	TOOLKIT_API virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:

	//@access Overridable

	//@cmember
	/* Called when the delimiter key is pressed.*/
	TOOLKIT_API virtual void OnDelimiterKey(UINT nKey);
	
	//@cmember
	/* Called when the enter key is pressed.*/
	TOOLKIT_API virtual void OnEnterKey();
	
	//@cmember
	/* Searches for a matching string and selects it into the edit control.*/
	TOOLKIT_API virtual BOOL SelectTheString(int nStartIndex, CString& strFind);
	
	//@cmember
	/* Override to add image, or to control insertion point in the list.*/
	TOOLKIT_API virtual BOOL OnInsertNewEntry(COMBOBOXEXITEM* pItem);

	//@cmember
	/* Override to provide any validation.*/
	TOOLKIT_API virtual BOOL PreProcessNewEntry(CString& strText);

	TOOLKIT_API virtual ~SECComboBoxEx();

	// Generated message map functions
protected:

	//@access Protected data members

	//@cmember
	/* The delimiter key for the control.*/
	UINT m_vkDelimiterKey;

	//@cmember
	/* The delimiter string for the control.*/
	CString m_strDelimiter;
	
	//@cmember
	/* the last key pressed in the control.*/
	UINT m_nLastKey;
	
	//@cmember
	/* Determines if control searches in a case sensitive manner.*/
	BOOL m_bCaseSensitive;

	//{{AFX_MSG(SECComboBoxEx)
	TOOLKIT_API afx_msg UINT OnGetDlgCode();
	TOOLKIT_API afx_msg BOOL OnEditchange();
	//}}AFX_MSG

	TOOLKIT_API void NotifyApply();

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

#endif // __SECCOMBOBOXEX_H__
