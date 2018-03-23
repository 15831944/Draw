///////////////////////////////////////////////////////////////////////////////
// gximouse.h : Interface of the CGXIntelliMousePlugin class
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

#ifndef _GXIMOUSE_H_
#define _GXIMOUSE_H_

#ifndef _GXPLUGIN_H_
#include "gxplugin.h"
#endif

#if defined(_GX)

#include "gxproc.h"

#endif

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

#ifndef WM_GX_IMOUSE_GETZOOM
#define WM_GX_IMOUSE_GETZOOM			(WM_USER+991)
#define WM_GX_IMOUSE_SETZOOM			(WM_USER+992)
#endif

struct GX_INTELLI_STATE: public CGXNoTrackObject
{
	int nLockMouseTicks;
	int nScrollSpeed;
	int nScrollAccel;
	int nScrollByPix;

	HCURSOR m_hcurLast;
	HCURSOR m_hcurDestroy;
	UINT m_idcPrimaryLast;
	BOOL m_bNotFound;

	GRID_API GX_INTELLI_STATE();
};                               


// GX_EXTERN_PROCESS_LOCAL(GX_INTELLI_STATE, _gxIntelliState)

#if _MFC_VER >= 0x0421
extern "C" GRID_API UINT AFXAPI GXGetMouseScrollLines(BOOL bForceFresh = FALSE);
#endif

class CGXMouseWheelOriginWnd: public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXMouseWheelOriginWnd)
public:
	GRID_API CGXMouseWheelOriginWnd();
	GRID_API BOOL CreateWnd(CWnd* pParent, const CRect& rect, UINT nID);

// Operations
public:
	GRID_API static void AFXAPI DrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
		int yStart, COLORREF cTransparentColor);

// Attributes
public:
	CBitmap m_bmOrigin;
	CSize m_size;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXMouseWheelOriginWnd)
	GRID_API afx_msg void OnPaint();
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

class CGXMouseWheelPlugin: public CGXPlugInComponent
{
	GRID_DECLARE_DYNAMIC(CGXMouseWheelPlugin)
public: 
	GRID_API CGXMouseWheelPlugin();

// Attributes
public:

// Operations
public:

// Overrides
	GRID_API virtual int OnIMouseGetZoom();
	GRID_API virtual void OnIMouseSetZoom(int nZoom);
	GRID_API virtual void OnIMouseVScroll(UINT nSBCode, UINT nScroll);
	GRID_API virtual void OnIMouseHScroll(UINT nSBCode, UINT nScroll);

// Implementation
public:
	GRID_API virtual ~CGXMouseWheelPlugin();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGXMouseWheelPlugin)
	//}}AFX_MSG
	GRID_API afx_msg LRESULT OnSettingChange(WPARAM, LPARAM);
#if _MFC_VER >= 0x0421
	GRID_API afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif
	GRID_DECLARE_MESSAGE_MAP()
};

class CGXIntelliMousePlugin: public CGXMouseWheelPlugin
{
	GRID_DECLARE_DYNAMIC(CGXIntelliMousePlugin)
public: 
	GRID_API CGXIntelliMousePlugin();

// Attributes
public:
	BOOL		m_bMouseWheelDrag;
	DWORD		m_dwMouseWheelTick;
	DWORD		m_dwMouseWheelLastTick;
	int			m_nMouseWheelNextTicks;
	int			m_nMouseWheelLastDirection;
	SEC_UINT	m_nMouseWheelTimer;
	CPoint		m_ptMouseWheelOrg;
	BOOL		m_bMouseWheelCanVertScroll;
	BOOL		m_bMouseWheelCanHorzScroll;
	CGXMouseWheelOriginWnd* m_pWndOrigin;
	UINT		m_idcCursor; 

// Double buffering
	GRID_API void SaveBackground(const CRect& rect);
	GRID_API void RestoreBackground();
	GRID_API void HideOriginWnd();
	GRID_API void ShowOriginWnd();
	
	CBitmap m_bmBackground;
	HBITMAP m_hbmBackgroundOld;
	CDC		m_dcBackground;
	CRect	m_rcBackground;

// Operations
public:
	GRID_API void KillMouseWheel(CPoint point);
	GRID_API void SetImouseCursor(UINT idcCursor);
	GRID_API BOOL ShowImouseCursor(UINT idcPrimary);

// Implementation
public:
	GRID_API virtual ~CGXIntelliMousePlugin();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGXIntelliMousePlugin)
	GRID_API afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	GRID_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	GRID_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	GRID_API afx_msg void OnCancelMode();
	//}}AFX_MSG
	GRID_API afx_msg LRESULT OnSettingChange(WPARAM, LPARAM);
#if _MFC_VER >= 0x0421
	GRID_API afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif
	GRID_DECLARE_MESSAGE_MAP()
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GXIMOUSE_H_

