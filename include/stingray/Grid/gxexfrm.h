///////////////////////////////////////////////////////////////////////////////
// GXExFrm.h : Interface of the CGXExcelChildFrame class
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
// gxexfrm.h : interface of the CGXExcelChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _GX_EX_FRM_H__
#define _GX_EX_FRM_H__

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


#include "gxchfrm.h"

class CGXExcelChildFrame : public CGXWChildFrame
{
	GRID_DECLARE_DYNCREATE(CGXExcelChildFrame)
public:
	GRID_API CGXExcelChildFrame();

// Operations
public:

// Overrides
	GRID_API virtual LRESULT InitNewHandler(WPARAM ui = 0, LPARAM l = 0);
	GRID_API virtual LRESULT InitFromFileHandler(WPARAM wParam, LPARAM lParam);
	GRID_API virtual void OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pInfo);

	GRID_API virtual void InsertWorkSheetHandler();
	GRID_API virtual void DeleteWorkSheetHandler();

	GRID_API virtual void HandleOnNewWindow();

	GRID_API virtual void HandleDestroy();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXExcelChildFrame)
public:
	GRID_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXExcelChildFrame();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXExcelChildFrame)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

	int m_nPrimary;
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

#endif //_GX_EX_FRM_H__

/////////////////////////////////////////////////////////////////////////////
