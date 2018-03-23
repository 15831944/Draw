///////////////////////////////////////////////////////////////////////////////
// tbtntxt.h
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
// Description:  Declaration of SECTBTextButton
//
// Use this subclass of SECStdBtn to utilize large
// buttons with rendered text. (no text rendered for small icons)


#ifndef __SECTEXTWBDBUTTON_H__
#define __SECTEXTWBDBUTTON_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32

// Header Includes
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

/////////////////////////////////////////////////////////////////////////////
// SECTBTextButton

class SECTBTextButton : public SECStdBtn
{
	//---------------------------------------------------------------------//
	// 						   Public Interface							   //
	//---------------------------------------------------------------------//
public:
	// Dynamic button creation helpers defined in tbtnstd.h
	// establish toolbar button interface
	TOOLKIT_DECLARE_BUTTON(SECTBTextButton)

	// Initialization/Destruction
	TOOLKIT_API SECTBTextButton();
	TOOLKIT_API virtual ~SECTBTextButton();

	// Attributes
	// ...Publicly accessible member variables...

	// Use a static font to allow easy reset without mucking
	// with button macros.
	TOOLKIT_API static void SetTextFont(CFont* pFont);
	TOOLKIT_API static CFont* GetTextFont();

	// Accessors
	// ...Get and Set functions...
	inline void GetButtonText(CString& strText)		  { strText=m_strDrawText; }
	inline void SetButtonText(const CString& strText) { m_strDrawText=strText; }

	// Operations

	//---------------------------------------------------------------------//
	// 							 Overridables							   //
	//---------------------------------------------------------------------//

	// Initializes button after creation.
	TOOLKIT_API virtual void Init(SECCustomToolBar* pToolBar, const SEC_UINT* pData);

protected:

	// Hook into the button drawing
	TOOLKIT_API virtual void OnDrawFaceBlt(int xImg,int yImg,int nImgWidth,int nImgHeight, SECBtnDrawData& data,int xDest,int yDest, CDC& dc);
	TOOLKIT_API virtual void OnDrawFaceText(SECBtnDrawData& data);

	//---------------------------------------------------------------------//
	// 						Protected Implementation					   //
	//---------------------------------------------------------------------//
protected:

	// Implementation Member Variables
	CString m_strDrawText;
	TOOLKIT_API static CFont* m_pTextFont;
	TOOLKIT_API static int m_nFontRefCount;
};

// SECTBTextButton helper macro	- BUTTON_CLASS expansion requires use
// of both DECLARE_BUTTON and IMPLEMENT_BUTTON macros in class definition.
#define TEXT_BUTTON(ButtonID, textResourceID) \
	{BUTTON_CLASS(SECTBTextButton), ButtonID, TBBS_BUTTON, textResourceID, 0, 0, \
	 0, 0},
// sam as above, witht he addition of a style
#define TEXT_BUTTON_EX(ButtonID, textResourceID, style) \
	{BUTTON_CLASS(SECTBTextButton), ButtonID, TBBS_BUTTON|style, textResourceID, 0, 0, \
	 0, 0},

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// WIN32

#endif //__SECTEXTWBDBUTTON_H__
