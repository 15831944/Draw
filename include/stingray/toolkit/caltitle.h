///////////////////////////////////////////////////////////////////////////////
// caltitle.h : header file for the SECCalendar's title panel class
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
//

#ifndef __SECCALTITLE_H__
#define __SECCALTITLE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECPANEL_H__
#include "toolkit\panel.h"
#endif //__SECPANL_H__

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//
#ifdef _SECDLL
	#undef AFXAPP_DATA
	//#define AFXAPP_DATA AFXAPI_DATA
	#define AFXAPP_DATA TOOLKIT_API
	#undef AFX_DATA
	//#define AFX_DATA    SEC_DATAEXT
	#define AFX_DATA TOOLKIT_API
#endif //_SECDLL


#define SEC_CALTITLE_SCHEMA 0x0100


class SECCalTitle : public SECPanel
{
	TOOLKIT_DECLARE_SERIAL( SECCalTitle ) 
// Construction
public:
	TOOLKIT_API SECCalTitle();
	TOOLKIT_API BOOL Create( CRect r,
		     CWnd *pParent,
		     DWORD dwStyle,
		     UINT nID,
		     BOOL bPressed, 
		     BOOL bHighlighted, 
		     long iDrawMode,
		     long iBehaviorMode,
		     UINT nBevelLines );
 
// Attributes
public:
	TOOLKIT_API virtual CRect SetContainerRect( CRect &rect );

// Operations
public:
#ifdef WIN32
	TOOLKIT_API virtual BOOL SetPage( const COleDateTime &date );
#else
	TOOLKIT_API virtual BOOL SetPage( const CTime        &date );
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECCalTitle)
	//}}AFX_VIRTUAL
	TOOLKIT_API virtual BOOL OnDraw( CDC *pDC );

// Implementation
public:
	TOOLKIT_API virtual ~SECCalTitle();
	TOOLKIT_API CSize RectSizeFromFont( CDC *pDC, SECCalendar* pWnd, LOGFONT *pLf = NULL );
	TOOLKIT_API LOGFONT FontSizeFromRect( CDC *pDC, 
							  LOGFONT *pLf = NULL,
							  CRect *pR = NULL );

protected:
	TOOLKIT_API void SizeButtons( void );
	TOOLKIT_API void OnNextYear();
	TOOLKIT_API void OnPrevYear();
	TOOLKIT_API void OnNextMonth();
	TOOLKIT_API void OnPrevMonth();

	SECCalendar*	m_pParent;
	CButton			m_btnPrevYear;
	CButton			m_btnPrevMonth;
	CButton			m_btnNextMonth;
	CButton			m_btnNextYear;
	BOOL			m_bYearButtons;
	BOOL			m_bMonthButtons;
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

#endif // __SECCALTITLE_H__
