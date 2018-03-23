///////////////////////////////////////////////////////////////////////////////
// TBtnMenu.h
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
//  Description:	Declarations for SECTBMenuBtn
//  Created:		May 1997
//

#ifdef WIN32

#ifndef __TBTNMENU_H__
#define __TBTNMENU_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#if !defined(__TBARCUST_H__)
#include "toolkit\tbarcust.h"
#endif

#if !defined(__TBTNSTD_H__)
#include "toolkit\tbtnstd.h"
#endif

#include <StingrayExportDefs.h>

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
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


class SECTBMenuBtn : public SECStdBtn
{
	TOOLKIT_DECLARE_BUTTON(SECTBMenuBtn);

public:
	TOOLKIT_API SECTBMenuBtn();
	TOOLKIT_API virtual ~SECTBMenuBtn();

	TOOLKIT_API virtual BOOL BtnPressDown(CPoint point);

	TOOLKIT_API virtual void ShowMenu();
	TOOLKIT_API virtual void CalcAccel();

	// Initialises button after creation.
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);

	CString m_strTitle;					// Title of menu button
	UINT    m_nIDMenu;					// ID of menu resource
	int     m_nIndexMenu;				// Index within menu resource
	TCHAR   m_cAccel;					// Character to accelerate this menu item
	DWORD   m_dwMenuBitFlag;			// Bit flag for menu resource

protected:
	HTHEME m_hToolbarTheme;
	HTHEME m_hTaskBandTheme;


	// Drawing functions ...
	TOOLKIT_API virtual void DrawFace(SECBtnDrawData& data, BOOL bForce, int& x, int& y, 
						  int& nWidth, int& nHeight, int nImgWidth, CDC& dc);
	// No bitmap, so override to load nothing.
	inline virtual void LoadItemBitmap(SECBtnDrawData& /* data */) {}

	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	TOOLKIT_API virtual void AdjustSize();
};

extern TOOLKIT_API HMENU   SecPopupMenuFromMenuTemplate(PMENUITEMTEMPLATE& pItem);
extern TOOLKIT_API BOOL    SecFindItemInMenuTemplate(PMENUITEMTEMPLATE& pItem, UINT nIndex);
extern TOOLKIT_API void    SecAdvanceItemInMenuTemplate(PMENUITEMTEMPLATE& pItem);
extern TOOLKIT_API LPCWSTR SecNameFromMenuTemplate(PMENUITEMTEMPLATE pItem);

#define MENU_BUTTON(id, style, lpszResource, nIndex, lpszTitle) \
	{BUTTON_CLASS(SECTBMenuBtn), id, style|TBBS_BUTTON, (SEC_UINT)lpszResource, nIndex, (SEC_UINT)lpszTitle, 0, 0},

#define MENU_BUTTON_EX(id, style, lpszResource, nIndex, lpszTitle, dwBitFlag) \
	{BUTTON_CLASS(SECTBMenuBtn), id, style|TBBS_BUTTON, (SEC_UINT)lpszResource, nIndex, (SEC_UINT) lpszTitle, dwBitFlag, 0},

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// __TBTNMENU_H__

#endif	// WIN32
