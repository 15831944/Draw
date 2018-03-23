///////////////////////////////////////////////////////////////////////////////
// DayBox.h : header file for the SECDayBox component of the SECCalendar 
//            custom control.
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
// CHANGELOG:
//
//    PCB	01/19/96	Started
//

#ifndef __SEC_DAYBOX_H__
#define __SEC_DAYBOX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SEC_PANEL_H__
#include "toolkit\Panel.h"
#endif

#ifndef __AFXDISP_H__
#include "afxdisp.h"
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


#define SEC_DAY_SCHEMA					0x0100

// Forward Declarations
class SECCalendar;


/////////////////////////////////////////////////////////////////////////////
// SECDayBox:
// See SECDayBox.cpp for the implementation of this class
//

class SECDayBox	: public SECPanel
{
	TOOLKIT_DECLARE_SERIAL( SECDayBox ) 
// Construction
public:
	TOOLKIT_API SECDayBox( );
	TOOLKIT_API BOOL Create( CRect rect,
				 SECCalendar *pParent,
				 UINT nID,
 				 DWORD dwStyle = WS_CHILD|WS_VISIBLE,
				 BOOL bSelected = FALSE,
				 BOOL bHighlighted = FALSE,
				 long iDrawMode = SECPDM_DEFAULT_DIALOG_DRAW,
				 long iBehaviorMode = SECPBM_DEFAULT_DIALOG_BEHAVIOR,
				 UINT nBevelLines = SECP_DEFAULTBEVELLINES );
		
// Attributes
public:
	TOOLKIT_API void SetValid(BOOL bValid = TRUE);
	TOOLKIT_API BOOL IsValid();

#ifdef WIN32
	TOOLKIT_API COleDateTime SetDate( COleDateTime newDate);
	TOOLKIT_API const COleDateTime &GetDate( void );
#else
	TOOLKIT_API CTime SetDate( CTime newDate);
	TOOLKIT_API const CTime &GetDate( void );
#endif
	
	TOOLKIT_API BOOL SetPrePostState( BOOL bToWhat );
	TOOLKIT_API BOOL GetPrePostState( void );

// Operations
public:

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECDayBox)
	//}}AFX_VIRTUAL
 	TOOLKIT_API virtual BOOL OnDrawLabel( CDC *pDC  );

// Implementation
public:
	TOOLKIT_API virtual ~SECDayBox( );
	TOOLKIT_API CSize GetBorderSize();
	TOOLKIT_API CSize RectSizeFromFont( CDC *pDC, SECCalendar* pWnd, LOGFONT *pLf = NULL );
	TOOLKIT_API LOGFONT	FontSizeFromRect( CDC *pDC, 
							 LOGFONT *pLf = NULL, 
							 CRect *pR = NULL );
	TOOLKIT_API void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API void OnLButtonDblClk(UINT nFlags, CPoint point);


protected:
	UINT m_ordinal;
#ifdef WIN32
	COleDateTime m_today;
#else
	CTime        m_today;
#endif
	BOOL m_bPrePost;
	BOOL m_bDateInitted;
//	BW: Provide an invalid type.
	BOOL m_bValid;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SEC_DAYBOX_H__

