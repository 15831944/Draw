///////////////////////////////////////////////////////////////////////////////
// Otlappbar.h
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

#ifndef __OTLAPPBAR_H__
#define __OTLAPPBAR_H__

#ifndef __OTLBASE_H__
	#error otlappbar.h requires otlbase.h to be included first
#endif

#include <shellapi.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{

// Forward declaration
class COtlAppBarImpl;

#define CHAIN_OTL_APPBAR() CHAIN_MSG_MAP(COtlAppBarImpl)

static const UINT wmOTLAppBarCallback = RegisterWindowMessage(_T("OtlAppBarCallback"));

#define OtlAbs(n) ((n < 0) ? -n : n)
#define OTLAPPBAR_TIMER_ID 1

#define GATE_OTL_PLUGIN(bGate) \
	if(bGate == 0) \
	{ \
		bHandled = FALSE; \
		return FALSE; \
	}

/////////////////////////////////////////////////////////////////////////////
// COtlAppBarImpl - Application Bar shell extension

class COtlAppBarImpl : public CMessageMap  
{
public:

// construction
	COtlAppBarImpl()
	{
		m_fRegistered = FALSE;
		m_fCurrentEdge = m_fNewEdge = ABE_TOP;		// default to top
		m_sizeDocked.cx = m_sizeDocked.cy = 0;
		m_sizeInc.cx = m_sizeInc.cy = 0;
		m_uTimer = 0;
		m_fAutoHide = FALSE;
		m_fAlwaysOnTop = FALSE;
		m_fFullScreenApp = FALSE;
		m_fdwTaskBarState = 0;
		m_fMirrorTaskBar = FALSE;
		m_fAutoHideVisible = FALSE;
//		m_AutoHideInterval = 300;  //  This causes no tooltips in other applications.
		m_AutoHideInterval = 600;
		m_pWnd = NULL;
		m_bMoving = FALSE;
	}

	inline int GetCurrentEdge(){ return m_fCurrentEdge; }
	inline BOOL IsAutoHide(){ return m_fAutoHide; }
	inline BOOL IsVertical() { return m_fCurrentEdge == ABE_LEFT || m_fCurrentEdge == ABE_RIGHT; }
	inline BOOL IsHorizontal() { return m_fCurrentEdge == ABE_BOTTOM || m_fCurrentEdge == ABE_TOP; }
	inline BOOL IsAlwaysOnTop(){ return m_fAlwaysOnTop; }
	inline BOOL IsMirroring() { return m_fMirrorTaskBar; }

	inline void SetAutoHide(BOOL bAutoHide)
	{
		m_fAutoHide = bAutoHide;
		Dock( m_fCurrentEdge );
	}

	inline void SetAutoHideInterval(UINT uInterval) 
	{	
		m_AutoHideInterval = uInterval;
		if(m_pWnd)
		{
			m_pWnd->KillTimer(OTLAPPBAR_TIMER_ID);
			m_uTimer = m_pWnd->SetTimer(OTLAPPBAR_TIMER_ID, m_AutoHideInterval);
		}
	}
	inline void SetHorzHeight(UINT uHorzHeight){ m_sizeDocked.cy = uHorzHeight; }
	inline void SetVertWidth(UINT uVertWidth){ m_sizeDocked.cx = uVertWidth; }
	inline void SetSizeIncrements(UINT cx, UINT cy) { m_sizeInc.cx = cx; m_sizeInc.cy = cy; }

	inline void MirrorTaskBar(BOOL bMirror)
	{
		m_fMirrorTaskBar = bMirror;
		if(bMirror)
			CopyTaskBarState(ABS_ALWAYSONTOP | ABS_AUTOHIDE, m_fdwTaskBarState);
	}

	inline void SetAlwaysOnTop(BOOL bOnTop)
	{
		if(bOnTop != m_fAlwaysOnTop)
		{
			m_fAlwaysOnTop = bOnTop;
			SetBarZOrder();
		}
	}

	virtual void RecalcLayout()
	{
		Dock(m_fCurrentEdge);
		OnLayoutBar(m_fCurrentEdge);
	}

	virtual void OnAutoHideFail(){m_fAutoHide = FALSE;}
	virtual void OnLayoutBar(int nEdge){ nEdge;}


BEGIN_MSG_MAP(COtlAppBarImpl)
	GATE_OTL_PLUGIN(m_fRegistered)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
	MESSAGE_HANDLER(WM_MOVING, OnMoving)
	MESSAGE_HANDLER(WM_SIZING, OnSizing)
	MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
	MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
	MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnWindowPosChanging)
	MESSAGE_HANDLER(WM_EXITSIZEMOVE, OnExitSizeMove)
	MESSAGE_HANDLER(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	MESSAGE_HANDLER(WM_TIMER, OnHideTimer)
	MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
	MESSAGE_HANDLER(wmOTLAppBarCallback, OnAppBarCallback)
END_MSG_MAP()

// message handlers
	inline LRESULT OnNcMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		ShowAutoHide(TRUE);
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		m_fNewEdge = m_fCurrentEdge;
		m_bMoving = TRUE;
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		wParam;
		ATLTRACE("Appbar:OnWindowPosChanging Edge: %d\n", m_fNewEdge);

		if( m_bMoving && !IsFullDragOn())
		{
			RECT r;
			GetDockingRect(m_fCurrentEdge, &r);
			LPWINDOWPOS lpwp = (LPWINDOWPOS) lParam;
			lpwp->x = r.left;
			lpwp->y = r.top;
			lpwp->cx = OtlRectWidth(r);
			lpwp->cy = OtlRectHeight(r);
			bHandled = TRUE;
			return 0;
		}
		bHandled = FALSE;
		return 1;
	}

	
	inline LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		ATLTRACE("Appbar:OnWindowPosChanged Edge: %d\n", m_fNewEdge);

		if(m_bMoving)
			OnLayoutBar(m_fNewEdge);

		OtlAppBarMessage(ABM_WINDOWPOSCHANGED);
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		wParam;
		RECT* prc = (RECT*) lParam;
		DWORD dwPos = ::GetMessagePos();
		POINT pt;
		pt.x = (short)LOWORD(dwPos);
		pt.y = (short)HIWORD(dwPos);
		m_fNewEdge = FindNearestEdge(pt);
		ATLTRACE("Appbar:OnMoving Edge: %d\n", m_fNewEdge);
		GetDockingRect(m_fNewEdge, prc);
			
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE("Appbar:Sizing\n");
		m_bMoving = FALSE;
		uMsg;
		RECT* prc = (RECT*)lParam;
		int iWidth = prc->right - prc->left;
		int iHeight = prc->bottom - prc->top;
		RECT rcBorder;
		::SetRectEmpty(&rcBorder);
		OTLASSERT(m_pWnd);
		::AdjustWindowRectEx(&rcBorder, m_pWnd->GetStyle(), FALSE, m_pWnd->GetExStyle());
		int iBWidth = rcBorder.right - rcBorder.left;
		int iBHeight = rcBorder.bottom - rcBorder.top;

		int nWidthNew  = ((iWidth  - iBWidth)  + m_sizeInc.cx / 2) / 
		  m_sizeInc.cx * m_sizeInc.cx + iBWidth;
		int nHeightNew = ((iHeight - iBHeight) + m_sizeInc.cy / 2) / 
		  m_sizeInc.cy * m_sizeInc.cy + iBHeight;

		switch (wParam) {
		  case WMSZ_LEFT:    
			 prc->left = prc->right  - nWidthNew;  
			 break;
		  case WMSZ_TOP:     
			 prc->top = prc->bottom - nHeightNew; 
			 break;
		  case WMSZ_RIGHT:   
			 prc->right  = prc->left + nWidthNew;  
			 break;
		  case WMSZ_BOTTOM:  
			 prc->bottom = prc->top + nHeightNew; 
			 break;
		  case WMSZ_BOTTOMLEFT:
			 prc->bottom = prc->top + nHeightNew; 
			 prc->left   = prc->right - nWidthNew;  
			 break;
		  case WMSZ_BOTTOMRIGHT:
			 prc->bottom = prc->top + nHeightNew; 
			 prc->right  = prc->left + nWidthNew;  
			 break;
		  case WMSZ_TOPLEFT:
			 prc->left   = prc->right - nWidthNew;
			 prc->top    = prc->bottom - nHeightNew;
			 break;
		  case WMSZ_TOPRIGHT:
			 prc->top    = prc->bottom - nHeightNew;
			 prc->right  = prc->left + nWidthNew;  
			 break;
		}

		OnLayoutBar(m_fCurrentEdge);
		bHandled = FALSE;
		return 0;
	}

	inline LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		OtlAppBarMessage(ABM_ACTIVATE);
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		m_pWnd->KillTimer(OTLAPPBAR_TIMER_ID);
		RegisterAppBar(FALSE);
		UnRegAutoHide();
		bHandled = FALSE;
		return 0;
	}

	inline LRESULT OnAppBarCallback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		bHandled;
		ATLTRACE( "OnAppBarCallback : " );
		switch (wParam)
		{
			case ABN_STATECHANGE:  
			{
				ATLTRACE( "ABN_STATECHANGE\n" );
				DWORD fdwTaskBarState = (DWORD)OtlAppBarMessage(ABM_GETSTATE);
				DWORD fdwStateChangedMask = 0;
				if ((fdwTaskBarState & ABS_ALWAYSONTOP) != (m_fdwTaskBarState & ABS_ALWAYSONTOP))
					fdwStateChangedMask |= ABS_ALWAYSONTOP;
				if ((fdwTaskBarState & ABS_AUTOHIDE) != (m_fdwTaskBarState & ABS_AUTOHIDE))
					fdwStateChangedMask |= ABS_AUTOHIDE;
				CopyTaskBarState(fdwStateChangedMask, fdwTaskBarState);
				m_fdwTaskBarState = fdwTaskBarState;
				break;
			}
			case ABN_FULLSCREENAPP:  
			{
				ATLTRACE( "ABN_FULLSCREENAPP, %d\n", lParam );
				if( m_fFullScreenApp != (BOOL)lParam )
				{
					m_fFullScreenApp = (BOOL)lParam;
					SetBarZOrder();
				}
				break;
			}
			case ABN_POSCHANGED:  
			{
				// The taskbar or another appbar has changed its size or position
				ATLTRACE( "ABN_POSCHANGED\n" );
				if(!IsAutoHide())
					Dock(m_fCurrentEdge);
				break;
			}
		}
		return 0;
	}

	virtual BOOL PrepareToDock(int uEdge)
	{
		uEdge;
		return TRUE;
	}

	inline void InitAppBar(CWindow* pWnd, int cyHorz=-1, int cxVert=-1, int dx=-1, int dy=-1)
	{
		// call this once from your OnCreate or OnInitDialog
		if(m_fRegistered)
			return;

		ResetSystemKnowledge();
		OTLASSERT(pWnd);
		OTLASSERT(::IsWindow(pWnd->m_hWnd));
		m_pWnd = pWnd;
		m_fdwTaskBarState = (DWORD)OtlAppBarMessage(ABM_GETSTATE);
		// register with the shell
		RegisterAppBar(TRUE);
		// modify style to remove caption and sys menu
		pWnd->ModifyStyle(WS_CAPTION | WS_SYSMENU, 0);
		pWnd->ModifyStyleEx(0, WS_EX_TOOLWINDOW);
		// set default height and width when docked
		if(cxVert == -1)
			cxVert = 200;
		SetVertWidth(cxVert);
		
		if(cyHorz == -1)
		{
			RECT rc;
			pWnd->GetWindowRect(&rc);
			cyHorz = rc.bottom - rc.top;
		}
		SetHorzHeight(cyHorz);
		// dy: height sizing increment, note dx defaults to 1
		if(dy == -1)
		{
			RECT rc;
			pWnd->GetClientRect(&rc);
			dy = rc.bottom - rc.top;
		}
		SetSizeIncrements(dx, dy);

		m_uTimer = m_pWnd->SetTimer(OTLAPPBAR_TIMER_ID, m_AutoHideInterval);
	}


	inline BOOL RegisterAppBar(BOOL fRegister)
	{ 
		if (fRegister && !m_fRegistered) 
		{
			if (!OtlAppBarMessage(ABM_NEW))
				return FALSE;
			m_fRegistered = TRUE;
		} 
		else if(m_fRegistered) 
		{   // Unregister the appbar
			OtlAppBarMessage(ABM_REMOVE); 
			m_fRegistered = FALSE;
		}
		return TRUE;
	}


	inline void GetDockingRect(int uEdge, LPRECT pRect)
	{
		OTLASSERT(pRect);
		SetRect(pRect, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		// query for a rectangle
		if(!IsAutoHide())
			OtlAppBarMessage(ABM_QUERYPOS, uEdge, 0, pRect);

		switch(uEdge)
		{
			case ABE_LEFT:
				pRect->right = pRect->left + m_sizeDocked.cx; 
				break;
			case ABE_RIGHT: 
				pRect->left = pRect->right - m_sizeDocked.cx;
				break;  
			case ABE_TOP:
				pRect->bottom = pRect->top + m_sizeDocked.cy; 
				break;
			case ABE_BOTTOM: 
				pRect->top = pRect->bottom - m_sizeDocked.cy;             
				break;
		}  
	}


	inline BOOL Dock(int uEdge)
	{ 
		ATLTRACE("Appbar:Dock Edge: %d\n", uEdge);

		// call Initialize first
		OTLASSERT(m_pWnd);

		if(!PrepareToDock(uEdge))
			return FALSE;

		UnRegAutoHide();

		RECT rc;
		if(IsAutoHide() && !OtlAppBarMessage(ABM_SETAUTOHIDEBAR, uEdge, TRUE))
			OnAutoHideFail();

		GetDockingRect(uEdge, &rc);
		// Pass the final bounding rectangle to the system. 
		if (IsAutoHide()) 
		{
			RECT rcTemp;
			::SetRectEmpty(&rcTemp);
			OtlAppBarMessage(ABM_SETPOS, ABE_LEFT, 0, &rcTemp);
		}
		else
			OtlAppBarMessage(ABM_SETPOS, uEdge, 0, &rc);  

		m_fCurrentEdge = uEdge;
		CalcAutoHideRect(m_fAutoHideVisible, &rc);
		SlideWindow(rc);
		SetBarZOrder();
		OtlAppBarMessage(ABM_ACTIVATE);
		return TRUE;
	}


protected:
	inline void UnRegAutoHide()
	{
	   for (int uEdge = ABE_LEFT; uEdge <= ABE_BOTTOM; uEdge++) 
	   {
		  if (m_pWnd->m_hWnd == (HWND)OtlAppBarMessage(ABM_GETAUTOHIDEBAR, uEdge))
		  {
			OtlAppBarMessage(ABM_SETAUTOHIDEBAR, uEdge, FALSE);
			break;
		  }
	   }
	}

	// helper for calling SHAppBarMessage
	inline SEC_UINT OtlAppBarMessage(DWORD dwMessage, int uEdge=ABE_TOP, LPARAM lParam=0, LPRECT pRect=NULL)
	{
		OTLASSERT(m_pWnd);
		APPBARDATA abd;
		abd.cbSize           = sizeof(abd);
		abd.hWnd             = m_pWnd->m_hWnd;
		abd.uCallbackMessage = wmOTLAppBarCallback;
		abd.uEdge            = (UINT)uEdge;

		if(pRect)
			CopyRect(&abd.rc, pRect);
		else
			SetRectEmpty(&abd.rc);

		abd.lParam           = lParam;
		SEC_UINT uRetVal         = ::SHAppBarMessage(dwMessage, &abd);

		// If the caller passed a rectangle, return the updated rectangle.
		if (pRect != NULL) ::CopyRect(pRect, &abd.rc);
		return(uRetVal);
	}

	inline void CopyTaskBarState (DWORD fdwStateChangedMask, DWORD fdwState) 
	{
		if(!m_fMirrorTaskBar)
			return;

		BOOL fAnyChange = FALSE;   // Assume that nothing changes
		if((fdwStateChangedMask & ABS_AUTOHIDE) != 0) 
		{
			BOOL fIsAutoHide = (ABS_AUTOHIDE & fdwState) != 0;
			if (IsAutoHide() != fIsAutoHide) 
			{
				m_fAutoHide = fIsAutoHide;
				fAnyChange = TRUE;
			}
		}
		if ((fdwStateChangedMask & ABS_ALWAYSONTOP) != 0)
		{
			m_fAlwaysOnTop = (ABS_ALWAYSONTOP & fdwState) != 0;
			fAnyChange = TRUE;
		}
		if (fAnyChange) 
		{
			Dock(m_fCurrentEdge);
			ShowAutoHide(FALSE);
		}
	}

	inline int FindNearestEdge(POINT& pt)
	{
		int cxScreen = GetSystemMetrics(SM_CXSCREEN);
		int cyScreen = GetSystemMetrics(SM_CYSCREEN);

		POINT ptCenter;
		ptCenter.x = cxScreen / 2;
		ptCenter.y = cyScreen / 2;

		POINT ptOffset;
		ptOffset.x = pt.x - ptCenter.x;
		ptOffset.y = pt.y - ptCenter.y;

		BOOL fIsLeftOrRight = (OtlAbs(ptOffset.y) * cxScreen) <= (OtlAbs(ptOffset.x) * cyScreen);

		int uEdge;
		if (fIsLeftOrRight)
		  uEdge = (0 <= ptOffset.x) ? ABE_RIGHT : ABE_LEFT;
		else
		  uEdge = (0 <= ptOffset.y) ? ABE_BOTTOM : ABE_TOP;
		
		return uEdge;
	}

	inline void ResetSystemKnowledge ()
	{
		// thanks to Jeffrey Richter(MSJ 1996) for this trick to reset the appbars after a debug stop
		#ifdef _DEBUG
		   // Only do this for debug builds.
		   APPBARDATA abd;
		   abd.cbSize = sizeof(abd);
		   abd.hWnd = NULL;
		   ::SHAppBarMessage(ABM_REMOVE, &abd);
		#endif
	}

	inline BOOL IsFullDragOn()
	{
		BOOL fFullDragOn;
		::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &fFullDragOn, 0);
		return fFullDragOn;
	}

	virtual void SlideWindow(RECT& rcEnd)
	{
		OTLASSERT(m_pWnd);
		RECT rcStart;
		m_pWnd->GetWindowRect(&rcStart);   
		int iStartWidth = rcStart.right - rcStart.left;
		int iStartHeight = rcStart.bottom - rcStart.top;
		int iEndWidth = rcEnd.right - rcEnd.left;
		int iEndHeight = rcEnd.bottom - rcEnd.top;

		// important: must use a signed value for interval, since
		// x and y can be negative
		int interval = m_AutoHideInterval;

		if (IsFullDragOn() && !::EqualRect(&rcStart, &rcEnd))
		{
			DWORD dwTimeStart = ::GetTickCount();
			DWORD dwTimeEnd = dwTimeStart + interval;
			DWORD dwTime;
			while ((dwTime = ::GetTickCount()) < dwTimeEnd)
			{
				int x = rcStart.left - (rcStart.left - rcEnd.left) 
				* (int) (dwTime - dwTimeStart) / interval;

				int y = rcStart.top  - (rcStart.top  - rcEnd.top)  
				* (int) (dwTime - dwTimeStart) / interval;

				int nWidth  = iStartWidth - (iStartWidth - iEndWidth)  
				* (int) (dwTime - dwTimeStart) / interval;

				int nHeight = iStartHeight - (iStartHeight - iEndHeight) 
				* (int) (dwTime - dwTimeStart) / interval;

				m_pWnd->SetWindowPos(NULL, x, y, nWidth, nHeight, 
						SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);
				m_pWnd->UpdateWindow();
			}
		}

		m_pWnd->SetWindowPos(NULL, rcEnd.left, rcEnd.top, 
							rcEnd.right - rcEnd.left,
							rcEnd.bottom - rcEnd.top,
							SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);

		m_pWnd->UpdateWindow();
	}

	inline void ShowAutoHide(BOOL bShow)
	{
		OTLASSERT(m_pWnd);
		RECT rc;
		m_pWnd->GetWindowRect(&rc);
		m_fAutoHideVisible = TRUE;
		if (CalcAutoHideRect(bShow, &rc)) 
		{
			m_fAutoHideVisible = bShow;
			SlideWindow(rc);
		}
	}

	inline BOOL CalcAutoHideRect(BOOL bShow, RECT* prc)
	{
		OTLASSERT(prc);
		if(!m_fAutoHide)
			return FALSE;
		int x = 0, y = 0;    // Assume a position of (0, 0)
		int iWidth = prc->right - prc->left;
		int iHeight = prc->bottom - prc->top;
		if (bShow)
		{
			switch (m_fCurrentEdge) 
			{
			case ABE_RIGHT:
				x = ::GetSystemMetrics(SM_CXSCREEN) - iWidth;
				break;
			case ABE_BOTTOM:
				y = ::GetSystemMetrics(SM_CYSCREEN) - iHeight;
				break;
			}
		} 
		else 
		{
			int cxVisibleBorder = 2 * GetSystemMetrics(SM_CXBORDER);
			int cyVisibleBorder = 2 * GetSystemMetrics(SM_CYBORDER);
			switch (m_fCurrentEdge) 
			{
			 case ABE_LEFT:   
				x = -(iWidth - cxVisibleBorder); 
				break;
			 case ABE_RIGHT:  
				 x = ::GetSystemMetrics(SM_CXSCREEN) - cxVisibleBorder; 
				break;
			 case ABE_TOP:
				y = -(iHeight - cyVisibleBorder); 
				break;
			 case ABE_BOTTOM:
				 y = ::GetSystemMetrics(SM_CYSCREEN) - cyVisibleBorder; 
				break;
			}
		}
		::SetRect(prc, x, y, x + iWidth, y + iHeight);
		return TRUE;
	}


	inline void SetBarZOrder()
	{
		OTLASSERT(m_pWnd);
		HWND hwndAfter = HWND_NOTOPMOST;
		if (m_fAlwaysOnTop)
			hwndAfter = m_fFullScreenApp ? HWND_BOTTOM : HWND_TOPMOST;
		m_pWnd->SetWindowPos(hwndAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	inline LRESULT OnHideTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled;
		uMsg;
		lParam;
		if(m_uTimer == wParam && (m_pWnd->m_hWnd != ::GetActiveWindow()) )
		{
			DWORD dwPos = ::GetMessagePos();
			POINT pt;
			pt.x = (short)LOWORD(dwPos);
			pt.y = (short)HIWORD(dwPos);
			RECT rc;
			m_pWnd->GetWindowRect(&rc);

			// Add a little margin around the AppBar
			::InflateRect(&rc,	2 * GetSystemMetrics(SM_CXDOUBLECLK), 
								2 * GetSystemMetrics(SM_CYDOUBLECLK));

			if (!::PtInRect(&rc, pt)) 
				ShowAutoHide(FALSE);
		}
		return 0;
	}


	inline LRESULT OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		uMsg;
		lParam;
		wParam;
		RECT rc;
		m_bMoving = FALSE;

		ATLTRACE("Appbar:OnExitSizeMove Edge: %d\n", m_fNewEdge);

		m_pWnd->GetWindowRect(&rc);
		// adjust the default height or width
		if(m_fCurrentEdge == m_fNewEdge)
		{
			switch (m_fCurrentEdge)
			{
			case ABE_LEFT: 
			case ABE_RIGHT:
				m_sizeDocked.cx = rc.right - rc.left;
				break;
			case ABE_TOP: 
			case ABE_BOTTOM:
				m_sizeDocked.cy = rc.bottom - rc.top;
				break;
			}
		}
		Dock(m_fNewEdge);

		if(!IsFullDragOn() )
			OnLayoutBar(m_fCurrentEdge);

		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled;
		POINT ptHit;
		ptHit.x = LOWORD(lParam);
		ptHit.y = HIWORD(lParam);
		LRESULT lHit = ::DefWindowProc(m_pWnd->m_hWnd, uMsg, wParam, lParam);
		BOOL fPrimaryMouseBtnDown = (::GetAsyncKeyState(::GetSystemMetrics(SM_SWAPBUTTON) 
			 ? VK_RBUTTON : VK_LBUTTON) & 0x8000) != 0;

		if ((lHit == HTCLIENT) && fPrimaryMouseBtnDown) 
		lHit = HTCAPTION;
		
		// restrict sizing to the one inside edge
		if ((HTSIZEFIRST <= lHit) && (lHit <= HTSIZELAST))
		{
			if (0 == (IsVertical() ? m_sizeInc.cx : m_sizeInc.cy)) 
				lHit = HTBORDER;
			else
			{
				RECT rcClient;
				m_pWnd->GetClientRect(&rcClient);
				m_pWnd->ClientToScreen((LPPOINT)&rcClient);
				m_pWnd->ClientToScreen(((LPPOINT)&rcClient)+1);
				lHit = HTBORDER;  // Assume that we can't resize
				switch (m_fCurrentEdge)
				{
				case ABE_LEFT:
				   if (ptHit.x > rcClient.right) lHit = HTRIGHT;
				   break;

				case ABE_TOP:
				   if (ptHit.y > rcClient.bottom) lHit = HTBOTTOM;
				   break;

				case ABE_RIGHT:
				   if (ptHit.x < rcClient.left) lHit = HTLEFT;
				   break;

				case ABE_BOTTOM:
				   if (ptHit.y < rcClient.top) lHit = HTTOP;
				   break;
				}
			}
		}
		return lHit;
	}


protected:
	int m_fCurrentEdge;
	int m_fNewEdge;
	BOOL m_fRegistered;
	BOOL m_fAutoHide;
	BOOL m_fAlwaysOnTop;
	BOOL m_fFullScreenApp;
	DWORD m_fdwTaskBarState;
	BOOL m_fMirrorTaskBar;
	SEC_UINT m_uTimer;
	BOOL m_fAutoHideVisible;
	BOOL m_bMoving;
	UINT m_AutoHideInterval;

public:
	CWindow* m_pWnd;
	SIZE m_sizeDocked;
	SIZE m_sizeInc;
};

}; // namespace StingrayOTL 

#endif // __OTLAPPBAR_H__
