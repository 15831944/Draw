///////////////////////////////////////////////////////////////////////////////
// gxrddoc.h
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
// "gxrddoc.h" : interface of the CGXExcelReadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _GX_RD_DC_H__
#define _GX_RD_DC_H__

#ifndef _GX_DCADPT_H__
#include "gxdcadpt.h"
#endif //_GX_DCADPT_H__

#include "gxextb.h"
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

#ifndef _UNICODE

class CGXExcelReadDoc : public CGXDocument, public CGXExcelDocAdapter
{
protected: // create from serialization only
	GRID_API CGXExcelReadDoc();
	GRID_DECLARE_SERIAL(CGXExcelReadDoc)
// Attributes
public:

// Operations
public:
	GRID_API BOOL OnOpenDocument(LPCTSTR pszPathName);
	GRID_API BOOL OnSaveDocument(LPCTSTR pszPathName);
	GRID_API BOOL CanCloseFrame(CFrameWnd* pFrame);

	GRID_API virtual BOOL BaseOnOpenDocument(LPCTSTR lpszPathName);
	GRID_API virtual BOOL SaveModified();

// access
	GRID_API CGXExTabWndMgr* GetExTabManager();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXExcelReadDoc)
public:
	GRID_API virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL
	
	GRID_API virtual void Serialize(CArchive& ar);
	GRID_API virtual void WorkBookSerialize(CArchive& ar);
		
// Implementation
public:
	GRID_API virtual ~CGXExcelReadDoc();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_strFilePath;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGXExcelReadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

#endif

/////////////////////////////////////////////////////////////////////////////

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

#endif //_GX_RD_DC_H__
