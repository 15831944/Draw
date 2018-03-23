///////////////////////////////////////////////////////////////////////////////
// gxexlog.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_EX_LOG_H__
#define _GX_EX_LOG_H__

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _GX_EX_HLP_H__
#include "gxexhlp.h"
#endif //_GX_EX_HLP_H__

///////////////////////////////////////////
// CGXExcelLogger /////////////////////////
// Logging support for Excel Read/Write ///

class CGXExcelLogger
{
public:
	// construction
	GRID_API CGXExcelLogger();
	
	GRID_API CGXExcelLogger(const TCHAR* pszFileName);

	GRID_API virtual ~CGXExcelLogger();

	// operations
	GRID_API void InitLogFile(const TCHAR* pszFileName);
	GRID_API void CloseLogFile();
	
	// log text
	GRID_API void LogText(const TCHAR* pszText);
	GRID_API void LogNumber(int nNum, BOOL bNewLine = FALSE);
	GRID_API void LogXNumber(int nNum, BOOL bNewLine = FALSE);

	// access
	GRID_API void SetNoLogging(BOOL b);
	GRID_API BOOL GetNoLogging() const;

protected:
	// data
	CStdioFile fileLog;
	BOOL m_bIsLogFileOpen;
	BOOL m_bNoLogging;
};

typedef CGXCaptiveManagerNoRef<CGXExcelLogger> CGXLoggerManager;

struct CGXExcelLoggerFactory
{
	static CGXExcelLogger* CreateInstance()
	{
		CGXExcelLogger* pLogger = s_loggerMan.CreateObject();
		return pLogger;
	};

	static CGXLoggerManager* GetLoggerManager()
	{return &s_loggerMan;};

	GRID_API static CGXLoggerManager s_loggerMan;
};

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif


#endif //_GX_EX_LOG_H__
