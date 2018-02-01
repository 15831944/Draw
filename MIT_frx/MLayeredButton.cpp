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

		// ���� ���� ���� �� ZeroMemory�� ����� �ʱ�ȭ
		// cbSize�� sizeof�� ����� ũ�� ����
		MouseEvent.cbSize       = sizeof( MouseEvent );

		// dwFlag�� TME_LEAVE, WM_MOUSELEAVE �޽����� ����,
		MouseEvent.dwFlags      = TME_LEAVE;

		// CWnd�� �ڵ� m_hWnd�� �־� �ش�.
		MouseEvent.hwndTrack    = m_hWnd;

		// ���콺 Ŀ���� ���� �����쿡 �����ϸ� TRUE
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