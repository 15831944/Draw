///////////////////////////////////////////////////////////////////////////////
// GXVIEW.h
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
// Author: Stefan Hoenig
//

#ifndef _GXVIEW_H_
#define _GXVIEW_H_

// // #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file

class CGXTabWnd;
class CGXPrintDevice;

/////////////////////////////////////////////////////////////////////////////
// CGXView view

class CGXView : public CView
{
	GRID_DECLARE_DYNAMIC(CGXView)

// Constructors
protected:
	GRID_API CGXView();         // protected constructor used by dynamic creation

// Attributes
public:
	BOOL			m_bOwnPD;
	CGXPrintDevice*	m_pPD;

	// Printer Settings
public:
	GRID_API CGXPrintDevice* GetPrintDevice();
	GRID_API void    SetPrintDevice(CGXPrintDevice* pPD, BOOL bMustDelete = TRUE);

	// Printing support
public:
	GRID_API virtual void    OnModifiedPrintDevice();
	GRID_API int             DoPrintDialog(CPrintDialog* pPD);
	GRID_API BOOL            DoPreparePrinting(CPrintInfo* pInfo);

protected:
	GRID_API virtual BOOL    OnPreparePrinting(CPrintInfo* pInfo);
	GRID_API void            UpdatePrinterDevice(CGXPrintDevice* pd);

	// Support for tabwnds
public:
	GRID_API static CSplitterWnd* AFXAPI GetParentSplitter(const CWnd* pWnd, BOOL bAnyState);
	GRID_API static CSplitterWnd* AFXAPI GetParentDynamicSplitter(const CWnd* pWnd, BOOL bAnyState);
	GRID_API static UINT     AFXAPI GetParentTabViewID(const CWnd* pWnd);
	
	GRID_API CScrollBar*     GetScrollBarCtrl(int nBar) const;
	GRID_API CString         GetTabName();
	GRID_API void            SetTabName(CString s);

// Implementation
// CView overridable member functions
protected:
	GRID_API virtual ~CGXView();

	GRID_API virtual void OnInitialUpdate();

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXView)
	GRID_API afx_msg void OnFilePrintSetup();
	GRID_API afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	GRID_API afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

public:
	friend class CGXPageBreakPlugin; 
};

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXVIEW_H_
