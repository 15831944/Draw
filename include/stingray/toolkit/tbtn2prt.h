///////////////////////////////////////////////////////////////////////////////
// tbtn2prt.h
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
//  Description:	Declarations for SECTwoPartBtn
//  Created:		August 1996
//

#ifdef WIN32

#ifndef __TBTN2PRT_H__
#define __TBTN2PRT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __TBTNSTD_H__
#include "toolkit\tbtnstd.h"
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

#include <StingrayExportDefs.h>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// SECTwoPartBtn class
//

// Define the width of the SECTwoPartBtn when in two part mode.
#define SEC_TOOLBAR_TWOPART_WIDTH	37
#define SEC_TOOLBAR_TWOPART_DWIDTH	14

// Define a two-part toolbar button
#define TWOPART_BUTTON(id, id2, style, dispatchID) \
	{BUTTON_CLASS(SECTwoPartBtn), id, style|TBBS_BUTTON, id2, dispatchID, 0, \
	 0, 0},

class SECTwoPartBtn : public SECStdBtn
{
// Construction
public:
	TOOLKIT_API SECTwoPartBtn();

// Attributes
public:
	BOOL m_bTwoPartMode;	// Button is horz. aligned - so in two part mode
	UINT m_nID2;			// ID of second part
	UINT m_nDispatchID2;	// Command ID dispatched for second part.
	UINT m_nImage2;			// Bitmap index of second part.

// Operations
public:
	// SetMode informs the button when the button either enters/leaves a
	// vertically docked state
	TOOLKIT_API virtual void SetMode(BOOL bVertical);

// Overrideables
public:
	// Called when toolbar bitmap has changed ... buttons should now adjust
	// their size.
	TOOLKIT_API virtual void AdjustSize();

protected:
	// Initialises button after creation.
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);

	// Draw the button
	TOOLKIT_API virtual void DrawButton(CDC& dc, SECBtnDrawData& data);
	
	// Handle mouse events in the button's window rect.
	TOOLKIT_API virtual BOOL BtnPressDown(CPoint point);
	TOOLKIT_API virtual void BtnPressMouseMove(CPoint point);
	TOOLKIT_API virtual void BtnPressCancel();
	TOOLKIT_API virtual UINT BtnPressUp(CPoint point);

// Implementation
// Dynamic button creation helpers defined in tbtnstd.h
	TOOLKIT_DECLARE_BUTTON(SECTwoPartBtn)
};

// Define a two-part toolbar button
#define TWOPART_BUTTON(id, id2, style, dispatchID) \
	{BUTTON_CLASS(SECTwoPartBtn), id, style|TBBS_BUTTON, id2, dispatchID, 0, \
	 0, 0},

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TBTN2PRT_H__

#endif // WIN32
