///////////////////////////////////////////////////////////////////////////////
// gxautscr.h
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

#ifndef _GXAUTSCR_H_
#define _GXAUTSCR_H_

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

// #include <StingrayExportDefs.h>

/////////////////////////////////////////////////////////////////////////////
// CGXAutoScrollPlugin window

class CGXAutoScrollPlugin : public CGXPluginComponent
{
// Construction
public:
	GRID_API CGXAutoScrollPlugin(CGXGridCore* pGrid);

// Attributes
public:
	CGXGridCore*	m_pGrid;
	BOOL			m_bScrollVert;
	BOOL			m_bScrollHorz; 
	SEC_UINT		m_nTimer;
	CRect			m_rectScroll;
	DWORD			m_dwCurrentTick;
	DWORD			m_dwLastTick;
	int				m_nNextScrollTicks;
	int				m_nNextMouseMoveTicks;
	CPoint			m_ptOrgPos;
	int				m_nScrollBy;
	int				m_nLastDistance;
	int				m_nScrollDirection;
	UINT			m_nSpeedKeyChar;
	UINT			m_nSpeedKeyFlags;


// Operations
public:
	GRID_API void KillAutoScroll();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXAutoScrollPlugin)
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXAutoScrollPlugin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXAutoScrollPlugin)
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnCancelMode();
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
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

#endif //_GXAUTSCR_H_
