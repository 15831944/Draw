/////////////////////////////////////////////////////////////////////////////
// slocale.h : Header file for localization.
//
///////////////////////////////////////////////////////////////////////////////
// slocale.h
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
//	Author:		Dean
//

#ifndef __SLOCALE_H__
#define __SLOCALE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	//#define AFXAPP_DATA TOOLKIT_API
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
	//#define AFX_DATA TOOLKIT_API
#endif //_SECDLL

#ifdef WIN32
#ifndef _WINNLS_
#include "winnls.h"
#endif	
#endif

#include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
// SECLocale 
//
//   This class aids in internationalization.
//


class SECLocale
{
// Construction
public:
	inline SECLocale(){}

// Attributes
public:

	TOOLKIT_API static const int DaysPerWeek;
	TOOLKIT_API static const int MonthsPerYear;

protected:

#ifdef WIN32
	TOOLKIT_API static LCID m_lcid;
	TOOLKIT_API static const LCTYPE DayNameIds[7][2];
	TOOLKIT_API static const LCTYPE MonthNameIds[12][2];
#else // WIN32
	TOOLKIT_API static TCHAR *dayAbbr[];
	TOOLKIT_API static TCHAR *dayFull[];
	TOOLKIT_API static TCHAR *monthAbbr[];
	TOOLKIT_API static TCHAR *monthFull[];
#endif

// Operations
public:

#ifdef WIN32
	TOOLKIT_API static void ResetLocaleID(LCID lcid);
	TOOLKIT_API static LCID GetLocaleID();
#endif

	TOOLKIT_API static BOOL GetDayName(CString& strDay, int nDay, BOOL bFullName = TRUE);
	TOOLKIT_API static BOOL GetMonthName(CString& strMonth, int nMonth, BOOL bFullName = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	inline virtual ~SECLocale(){}

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

#endif // __SLOCALE_H__
