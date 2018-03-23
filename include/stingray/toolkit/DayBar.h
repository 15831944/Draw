///////////////////////////////////////////////////////////////////////////////
// DayBar.h : header file for the SECCalendar's Day Bar class.
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
//    CSD   06.19.06    exported classes with TOOLKIT_API macro

#ifndef __DAYBAR_H__
#define __DAYBAR_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SEC_PANEL_H__
#include "toolkit\Panel.h"
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
// SECDayBar window

class SECDayBar : public SECPanel
{
// Construction
public:
	TOOLKIT_API SECDayBar();

// Attributes
public:

// Operations
public:
	TOOLKIT_API CSize RectSizeFromFont( CDC *pDC, SECCalendar* pWnd, LOGFONT *pLf = NULL );
	TOOLKIT_API LOGFONT	FontSizeFromRect( CDC *pDC, LOGFONT *pLf = NULL, CRect *pR = NULL );
	TOOLKIT_API virtual BOOL OnDrawLabel( CDC *pDC );
	TOOLKIT_API void SetFirstDayOfWeek(int nFirstDay);
	TOOLKIT_API int GetFirstDayOfWeek() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	TOOLKIT_API virtual ~SECDayBar();

	int m_nFirstDayOfWeek;
};


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


/////////////////////////////////////////////////////////////////////////////
#endif // __DAYBAR_H__
