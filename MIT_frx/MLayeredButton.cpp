#include "StdAfx.h"
#include "MLayeredButton.h"
#include "MLayeredDockingControlBar.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredButton, CBCGPButton)
MLayeredButton::MLayeredButton(void)
{
	m_bTrack = FALSE;
}

MLayeredButton::~MLayeredButton(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredButton, CBCGPButton)
	//{{AFX_MSG_MAP(MLayeredButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MLayeredButton::OnMouseMove(UINT nFlags, CPoint point)
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

	CBCGPButton::OnMouseMove(nFlags, point);
}

void MLayeredButton::OnMouseLeave()
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

	CBCGPButton::OnMouseLeave();
}