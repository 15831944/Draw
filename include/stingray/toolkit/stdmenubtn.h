///////////////////////////////////////////////////////////////////////////////
// stdmenubtn.h
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
//  Authors:		Matthew
//  Description:	Declarations for SECStdMenuBtn
//  Created:		January 1999
//

#ifdef WIN32

#ifndef __STDMENUBTN_H__
#define __STDMENUBTN_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TBTNSTD_H__
#include "toolkit\tbtnstd.h"
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// SECStdMenuBtn class
//
/////////////////////////////
// AutoDuck tag block block for SECStdMenuBtn

// adinsert AutoDuck insertion point for SECStdMenuBtn
//@doc SECStdMenuBtn
//@class The SECStdMenuBtn class is derived from SECStdBtn.
// It provides a method to have a toolbar button display a popup
// menu instead of executing one command. 
//@comm 
// 
// A SECStdMenuBtn is instantiated by implementing the STD_MENU_BUTTON
// macro in BUTTON_MAP macro used by the custom toobar framework.
//
//@xref <c SECStdBtn> <c SECCustomToolBar> <c SECToolBarManager>
class SECStdMenuBtn : public SECStdBtn  
{
public:
//Contruction
	TOOLKIT_API SECStdMenuBtn();
	TOOLKIT_API virtual ~SECStdMenuBtn();
//Public methods
	//@access Operations

	//@cmember
	/* Returns a CMenu pointer to the button submenu.*/
	TOOLKIT_API CMenu* GetMenu();

	//@cmember
	/* Sets the popup menu for the button.*/
	TOOLKIT_API void SetNewMenu(UINT nNewResID, UINT nSubmenu = 0, UINT nTrackStyle = TPM_LEFTALIGN);
//Overrides
	TOOLKIT_API virtual UINT BtnPressUp(CPoint point);
	TOOLKIT_API virtual BOOL BtnPressDown(CPoint point);
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);
//Declaratives
//Dynamic button creation helpers defined in tbtnstd.h
	TOOLKIT_DECLARE_BUTTON(SECStdMenuBtn)
//Internals
private:
	CMenu m_Menu;
	UINT m_nSubMenuIdx;
	UINT m_TrackStyle;
	TOOLKIT_API void DoMenuPopup();
};

//Button macro definition
#define STD_MENU_BUTTON(id, style, menuID, submenuindex, alignstyle) \
	{BUTTON_CLASS(SECStdMenuBtn), id, style|TBBS_BUTTON, menuID, submenuindex, alignstyle, 0, 0},

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __STDMENUBTN_H__

#endif // WIN32
