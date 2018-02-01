#include "StdAfx.h"
#include "MLayeredEdit.h"
#include "MLayeredPropList.h"
#include "MLayeredDockingControlBar.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredEdit, CEdit)
MLayeredEdit::MLayeredEdit(void)
{
	m_bTrack = FALSE;
}

MLayeredEdit::~MLayeredEdit(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredEdit, CEdit)
	//{{AFX_MSG_MAP(MLayeredButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MLayeredEdit::OnMouseMove(UINT nFlags, CPoint point)
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
			MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pParent;

			pDockWnd->UpdateFrame(TRUE);
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			MLayeredPropList* pPropList = (MLayeredPropList*)pParent;
			pPropList->MakeTransparent(TRUE);
		}
	}

	CEdit::OnMouseMove(nFlags, point);
}

void MLayeredEdit::OnMouseLeave()
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
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			//MLayeredPropList* pPropList = (MLayeredPropList*)pParent; // cppcheck - ���ȵ�
			//pPropList->MakeTransparent(FALSE);
		}
	}

	CEdit::OnMouseLeave();
}