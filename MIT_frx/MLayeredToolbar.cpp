#include "StdAfx.h"
#include "MLayeredToolbar.h"
#include "MLayeredDockingControlBar.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_SERIAL(MLayeredToolbar, CBCGPToolBar, VERSIONABLE_SCHEMA | 1)
MLayeredToolbar::MLayeredToolbar(void)
{
	m_bTrack = FALSE;
}

MLayeredToolbar::~MLayeredToolbar(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredToolbar, CBCGPToolBar)
	//{{AFX_MSG_MAP(MLayeredToolbar)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL MLayeredToolbar::LoadState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	return CBCGPToolBar::LoadState (lpszProfileName, nIndex, uiID);
}

BOOL MLayeredToolbar::SaveState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	return CBCGPToolBar::SaveState(lpszProfileName, nIndex, uiID);
}

void MLayeredToolbar::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bTrack == FALSE )
	{
		TRACKMOUSEEVENT MouseEvent;

		::ZeroMemory( &MouseEvent, sizeof( MouseEvent ) );

		// 최초 변수 생성 후 ZeroMemory를 사용해 초기화
		// cbSize에 sizeof를 사용해 크기 저장
		MouseEvent.cbSize       = sizeof( MouseEvent );

		// dwFlag는 TME_LEAVE, WM_MOUSELEAVE 메시지를 수신,
		MouseEvent.dwFlags      = TME_LEAVE;

		// CWnd의 핸들 m_hWnd를 넣어 준다.
		MouseEvent.hwndTrack    = m_hWnd;

		// 마우스 커서가 현재 윈도우에 존재하면 TRUE
		m_bTrack = ::_TrackMouseEvent( &MouseEvent );
	}

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
		{
			MLayeredDockingControlBar* pOutputWnd = (MLayeredDockingControlBar*)pParent;

			pOutputWnd->UpdateFrame(TRUE);
		}
	}

	CBCGPToolBar::OnMouseMove(nFlags, point);
}

LRESULT MLayeredToolbar::OnMouseLeave(WPARAM wp,LPARAM lp)
{
	m_bTrack = FALSE;

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
		{
			MLayeredDockingControlBar* pOutputWnd = (MLayeredDockingControlBar*)pParent;

			pOutputWnd->UpdateFrame(FALSE);
		}
	}

	return CBCGPToolBar::OnMouseLeave(wp, lp);
}