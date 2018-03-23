///////////////////////////////////////////////////////////////////////////////
// gxctplug.h : CGXCellTipPlugin class
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
// Author: Ricky Pearson
//

//RWP02a (entire file)

#ifndef _GXCTPLUG_H_
#define _GXCTPLUG_H_

#if _MFC_VER >= 0x0400

// #include <StingrayExportDefs.h>

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

class CGXCellTipWndManager;
class CGXCellTipWndFactory;

/////////////////////////////////////////////////////////////////////////////
// CGXCellTipPlugin 

class CGXCellTipPlugin : public CGXPluginComponent
{
	GRID_DECLARE_DYNAMIC(CGXCellTipPlugin)

public:
	CGXGridCore*			m_pGrid;		// "Parent" grid

protected:
	// Members
	CGXCellTipWndManager*	m_pCellTipWndManager;
	DWORD					m_dwCurrentTipID;
	ROWCOL					m_nCurRow;
	ROWCOL					m_nCurCol;
	SEC_UINT				m_nCellTipTimer;
	BOOL					m_bShowHeaders;
	BOOL					m_bShowActive;
	BOOL					m_bShowActiveCell;
	UINT					m_nDelay;

public:
	// Construction
	GRID_API CGXCellTipPlugin(CGXGridCore* pGrid, CRuntimeClass* pFactory, 
					 BOOL bShowHeaders, BOOL bShowActive, UINT nDelay);

	// Destruction
	GRID_API virtual ~CGXCellTipPlugin();

protected:
	// Implementation
	GRID_API virtual BOOL NeedShowCellTip(CGXControl* pControl);
	GRID_API virtual DWORD GetCellTipID(CGXControl* pControl);
	GRID_API virtual void InitializeCellTip(CGXControl* pControl, CGXCellTipWnd* pCellTip);

	// Helper methods
	GRID_API virtual void ShowCellTip();
	GRID_API virtual void HideCellTip();
	GRID_API virtual void StartTimer();
	GRID_API virtual void StopTimer();
	GRID_API virtual BOOL IsGridInSpecialMode();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCellTipPlugin)
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndManager

class CGXCellTipWndManager : public CGXNodeManager<CGXCellTipWnd>
{
public:
	CGXGridCore*			m_pGrid;
	CGXCellTipWndFactory*	m_pFactory;

public:
	// Construction
	GRID_API CGXCellTipWndManager(CGXGridCore* pGrid, CRuntimeClass* pRuntimeClass);
	GRID_API virtual ~CGXCellTipWndManager();

	GRID_API virtual CGXCellTipWnd* CreateObject(SEC_DWORD dw);
};


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndFactory

class CGXCellTipWndFactory : public CObject
{
	GRID_DECLARE_DYNCREATE(CGXCellTipWndFactory)

public:
	CGXGridCore* m_pGrid;

	GRID_API CGXCellTipWndFactory() : CObject() { m_pGrid = NULL; }

	GRID_API virtual CGXCellTipWnd* CreateCellTipWnd(DWORD dwCellTipID);
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

#endif // _MFC_VER

#endif //_GXCTPLUG_H_
