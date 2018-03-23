///////////////////////////////////////////////////////////////////////////////
// tbtncmbo.h
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
//  Description:	Declarations for SECToolBar
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBTNCMBO_H__
#define __TBTNCMBO_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TBTNWND_H__
#include "toolkit\tbtnwnd.h"
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
class SECComboBtn;

///////////////////////////////////////////////////////////////////////////////
// SECComboBtnEdit class
//
class SECComboBtnEdit : public CEdit
{
// Construction
public:
	TOOLKIT_API SECComboBtnEdit();

// Implementation
public:
	inline virtual ~SECComboBtnEdit() {}

public:
	// Implementation, data members.
	SECWndBtn* m_pCombo;				// Parent combobox

protected:
	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

///////////////////////////////////////////////////////////////////////////////
// SECComboBtn class
//
class SECComboBtn : public CComboBox, public SECWndBtn
{
	TOOLKIT_DECLARE_BUTTON(SECComboBtn);

// Construction
public:
	inline SECComboBtn() {	m_nType=BtnCombo; }

	// Attributes
public:
	enum NotifyCodes		// Notification codes sent with
	{						// wmSECToolBarWndNotify
		NBase   = 0x0200,
		Entered = NBase + 1	// The user hit return
	};

	// Operations
public:
	// SetMode informs the button when the button either enters/leaves a
	// vertically docked state
	TOOLKIT_API virtual void SetMode(BOOL bVertical);

// Overrideables
protected:
	TOOLKIT_API virtual CWnd* GetWnd();
	TOOLKIT_API virtual BOOL CreateWnd(CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID);

	TOOLKIT_API  BOOL PreTranslateMessage(MSG* pMsg);
	TOOLKIT_API virtual void OnFontCreateAndSet();

// Implementation
public:
	inline virtual ~SECComboBtn() {}

	// Called when toolbar bitmap has changed ... buttons should 
	// now adjust their size.
	TOOLKIT_API virtual void AdjustSize();

protected:
	// Implementation, data members.
	SECComboBtnEdit m_edit;				// Our subclassed child edit control
	CFont m_font;

	// Implementation - message map and entries
	TOOLKIT_DECLARE_MESSAGE_MAP()

	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

// Define a combo button
#define COMBO_BUTTON(id, comboId, style, comboStyle, comboDefWidth, \
					 comboMinWidth, comboHeight) \
	WND_BUTTON(BUTTON_CLASS(SECComboBtn), id, comboId, style, comboStyle, \
		       comboDefWidth, comboMinWidth, comboHeight)

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBTNCMBO_H__

#endif // WIN32
