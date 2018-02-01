#include "StdAfx.h"
#include "MLayeredHeaderCtrl.h"
#include "MLayeredDockingControlBar.h"
#include "MBaseDockWnd.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredHeaderCtrl, CBCGPHeaderCtrl)
MLayeredHeaderCtrl::MLayeredHeaderCtrl(void)
{
	m_bTrack = FALSE;
}

MLayeredHeaderCtrl::~MLayeredHeaderCtrl(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredHeaderCtrl, CBCGPHeaderCtrl)
	//{{AFX_MSG_MAP(MLayeredHeaderCtrl)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MLayeredHeaderCtrl::OnMouseMove(UINT nFlags, CPoint point)
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
		else if( pParent->IsKindOf(RUNTIME_CLASS(MBaseDockWnd)) )
		{
			CWnd* pWnd = pParent->GetParent();
			if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
			{
				MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pWnd;

				pDockWnd->UpdateFrame(TRUE);
			}
		}
	}

	CBCGPHeaderCtrl::OnMouseMove(nFlags, point);
}

LRESULT MLayeredHeaderCtrl::OnMouseLeave(WPARAM wp, LPARAM lp)
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
		else if( pParent->IsKindOf(RUNTIME_CLASS(MBaseDockWnd)) )
		{
			CWnd* pWnd = pParent->GetParent();
			if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
			{
				MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pWnd;

				pDockWnd->UpdateFrame(FALSE);
			}
		}
	}

	return CBCGPHeaderCtrl::OnMouseLeave(wp, lp);
}