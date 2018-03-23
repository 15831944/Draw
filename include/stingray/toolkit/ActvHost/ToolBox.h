///////////////////////////////////////////////////////////////////////////////
// ToolBox.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef __TOOLBOX_H_
#define __TOOLBOX_H_

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

struct SEC_ToolEntry
{
	// QA: 32238
	TOOLKIT_API SEC_ToolEntry & operator= (const SEC_ToolEntry &src);
	CLSID		ClassID;
	CString		strPath;
	WORD		wToolID;
	CString		strInitialObjName;
};

#define SEC_ToolArray CArray < SEC_ToolEntry, SEC_ToolEntry& >

class SECAToolBox : public SEC_TOOLBAR
{
public:
	TOOLKIT_API SECAToolBox();
	TOOLKIT_API virtual BOOL Create(CWnd* pParentWnd, UINT nID = 0, DWORD dwDockStyle = 0);

	TOOLKIT_API virtual void RemoveAllTools();
	TOOLKIT_API virtual void AddTool( SEC_ToolEntry &tool );
	TOOLKIT_API virtual BOOL AddTool( const CString &strToolClassID );
	TOOLKIT_API virtual BOOL CommitChanges();

	TOOLKIT_API virtual BOOL SaveTools( const CString &strFile );
	TOOLKIT_API virtual BOOL LoadTools( const CString &strFile );

	TOOLKIT_API virtual REFCLSID ClassIDfromCommandID   ( UINT nCmdID );
	TOOLKIT_API virtual CString	 ObjectNameFromCommandID( UINT nCmdID );

	TOOLKIT_API virtual void SetColumns(UINT nColumns);
	inline virtual UINT GetColumns() { return m_nColumns; };

#ifdef _WIN64
	TOOLKIT_API virtual LRESULT OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#else
	TOOLKIT_API virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
#endif // _WIN64

public:
	TOOLKIT_API virtual ~SECAToolBox();
#ifdef _DEBUG
	TOOLKIT_API virtual void AssertValid() const;
	TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT	  	  m_nColumns;
	CBitmap		 *m_pBitmap;
	SEC_ToolArray m_Tools;
protected:
	//{{AFX_MSG(CPaletteBar)
	TOOLKIT_API afx_msg void OnPaletteChange();
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRefresh();
	TOOLKIT_API afx_msg void OnCustomize();
	//}}AFX_MSG
	TOOLKIT_API virtual void AddBitmap( int nToolIndex, CDC *pDest, HBITMAP hBitmap, HPALETTE  hPal );
	TOOLKIT_DECLARE_MESSAGE_MAP()
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

#endif	// __TOOLBOX_H_
