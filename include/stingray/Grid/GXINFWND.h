///////////////////////////////////////////////////////////////////////////////
// GXINFWND.h
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

#ifndef _GXINFWND_H_
#define _GXINFWND_H_

#ifndef _GXEXT_H_
#include "gxext.h"  // for use as custom control
#endif

#ifndef _GXSPLIT_H_
#include "gxsplit.h"
#endif

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

class CGXRecordInfoBeam;
class CGXRecordInfoWnd;
class CGXRecordInfoEdit;

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoBeam window

class CGXRecordInfoBeam : public CWnd
{
	GRID_DECLARE_DYNCREATE(CGXRecordInfoBeam)
	GRID_DECLARE_REGISTER()

// Construction, initialization
public:
	GRID_API CGXRecordInfoBeam();
	GRID_API BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Attributes
public:
	GRID_API void    SetCurrentRecord(long nRecord);
	GRID_API void    SetRecordCount(long nCount);
	GRID_API long    GetCurrentRecord();
	GRID_API long    GetRecordCount();
	GRID_API void    UpdateColors();
	GRID_API virtual int     GetWidth();

// Operations
public:

// Implementation
public:
	GRID_API virtual ~CGXRecordInfoBeam();

	GRID_API virtual BOOL    IsOnFirstRecord();
	GRID_API virtual BOOL    IsOnLastRecord();
	GRID_API virtual CString GetCurrentRecordText();

	GRID_API virtual void    DrawButton(CDC* pDC, int i, BOOL bPressed);

	GRID_API void    AutoMove(UINT nRefMessage = WM_LBUTTONUP);

	GRID_API int     ScrollBtnHit(CPoint point, int nButton = -1);
	GRID_API virtual void    Scroll(int nDirection);

	GRID_API void CreateEditWnd(const RECT& rect);
	GRID_API void CreateFonts();
	GRID_API void DestroyFonts();
	GRID_API void SetNotifyWnd(CWnd* pNotify);
	GRID_API static void AFXAPI DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed);
	GRID_API static void AFXAPI PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);

// Implementation - Attributes
	CFont*      m_pFont;                // font
	COLORREF    m_rgbText;              // text color
	COLORREF    m_rgbBack;              // back color
	COLORREF    m_rgbFace;              // button color
	COLORREF    m_rgbBeam;              // beam color

	long        m_nRecordCount;         // no. of records
	long        m_nCurrentRecord;       // current record

	CString     m_strRecord;            // "Record?

	int         m_nHeight;              // height of the beam
	int         m_nButtonWidth;         // width of scroll button (= scroll's thumb button)
	CRect       m_rectInterior;         // interior rect (  Record: xxxx )
	CRect       m_rectEdit;             // edit window
	int         m_nInteriorWidth;       // how big to make the text area in button units.

	// Mouse Actions
	int         m_nBtnDown;
	BOOL        m_bBtnDown;
	BOOL        m_bMouseCapture;

	// Wnd to receive messages
	CWnd*       m_pNotifyWnd;
	CEdit*      m_pWndEdit;

	HCURSOR     m_hcurArrow;

protected:
	// Btn Hot indicators.	
	int m_bBtnHot[4];	

public:
	GRID_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXRecordInfoBeam)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	GRID_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnSysColorChange();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoWnd window

// this class is based on the source code of the CSplitterWnd class

class CGXRecordInfoWnd: public CWnd
{
	GRID_DECLARE_DYNCREATE(CGXRecordInfoWnd)
	GRID_DECLARE_REGISTER()

// Construction
public:
	GRID_API CGXRecordInfoWnd(CRuntimeClass *pBeamClass = RUNTIME_CLASS(CGXRecordInfoBeam));

	// Create the window with a single view
	GRID_API BOOL Create(CWnd* pParentWnd,
				CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE |
					WS_HSCROLL,
				UINT nID = AFX_IDW_PANE_FIRST);

// Overridables and other helpers (for implementation of derived classes)
protected:
//#if _MFC_VER < 0x0300
//	// for deriving from a standard control
//	virtual WNDPROC* GetSuperWndProcAddr();
//#endif

// Attributes
public:
	GRID_API CGXRecordInfoBeam* GetBeam();
	GRID_API CWnd* GetPane();

	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

// Operations
public:
	GRID_API void GetInsideRect(CRect& rect) const;
	GRID_API CWnd* AttachWnd(CWnd* pWnd);
	GRID_API virtual void RecalcLayout();

// Implementation
public:
	GRID_API virtual ~CGXRecordInfoWnd();

	GRID_API BOOL CreateCommon(CWnd* pParentWnd, DWORD dwStyle, UINT nID);
	GRID_API BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
	GRID_API void ShowScrollBar(UINT nBar, BOOL bShow);
	GRID_API CWnd* CreateView(CRuntimeClass* pViewClass, CCreateContext* pContext = NULL, UINT nID = 0);
	GRID_API void OnDrawSplitter(CDC* pDC, const CRect& rectArg);

// Implementation - Attributes
	CRuntimeClass*		m_pBeamClass;    // used for creating the beam
	CGXRecordInfoBeam*	m_pBeam;

	CRuntimeClass*		m_pViewClass;
	CWnd*				m_pPane;

	BOOL				m_bHasHScroll, m_bHasVScroll;
	int					m_cxVScroll, m_cyHScroll;

	int					m_cxBeam;           // size of the beam ( = x-position of the splitter)
	int					m_cxWnd;
	int					m_cxSplitter;
	int					m_nBarWidths;
	BOOL				m_bCtrlsCreated;

	HCURSOR				m_hcurArrow;
	CBrush				m_brErase;
	BOOL				m_bForceRecalcLayout;

	UINT				m_nFirstViewID;
	UINT				m_nLastViewID;

protected:
	GRID_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
	//{{AFX_MSG(CGXRecordInfoWnd)
	GRID_API afx_msg void OnPaint();
	GRID_API afx_msg void OnSize(UINT nType, int cx, int cy);
	GRID_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	GRID_API afx_msg void OnNcPaint();	
	GRID_API afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	GRID_API afx_msg void OnSysColorChange();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoEdit window

class CGXRecordInfoEdit : public CEdit
{
// Construction
public:
	GRID_API CGXRecordInfoEdit();

// Implementation
public:
	GRID_API virtual ~CGXRecordInfoEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXRecordInfoEdit)
	GRID_API afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRID_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRID_API afx_msg UINT OnGetDlgCode();	
	//}}AFX_MSG

	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#if _MFC_VER >= 0x0400

// This class is only supported under MFC 4.x or higher

class CGXRecordInfoSplitterWnd : public CGXSplitterWnd  
{
	GRID_DECLARE_DYNAMIC(CGXRecordInfoSplitterWnd)
public:
	GRID_API CGXRecordInfoSplitterWnd(CRuntimeClass* pBeamClass = RUNTIME_CLASS(CGXRecordInfoBeam));
	GRID_API virtual ~CGXRecordInfoSplitterWnd();

	GRID_API CGXRecordInfoBeam* GetBeam();
	GRID_API virtual void RecalcLayout();    // call after changing sizes

	CRuntimeClass* m_pBeamClass;
	CGXRecordInfoBeam* m_pBeam;

// Overrides
	GRID_API virtual void SetActivePane(int row, int col, CWnd* pWnd = NULL);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRecordInfoSplitterWnd)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXRecordInfoSplitterWnd)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif // _GXINFWND_H_
