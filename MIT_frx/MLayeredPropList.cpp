#include "StdAfx.h"
#include "MLayeredPropList.h"
#include "MLayeredDockingControlBar.h"
#include "MBaseDockWnd.h"
#include "MLayeredProp.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredPropList, CBCGPPropList)
MLayeredPropList::MLayeredPropList(void)
{
	m_bTrack = FALSE;
}

MLayeredPropList::~MLayeredPropList(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredPropList, CBCGPPropList)
	//{{AFX_MSG_MAP(MLayeredPropList)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MLayeredPropList::OnMouseMove(UINT nFlags, CPoint point)
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
	}

	CBCGPPropList::OnMouseMove(nFlags, point);
}

LRESULT MLayeredPropList::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTrack = FALSE;

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
		{
			MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pParent;

			pDockWnd->UpdateFrame(FALSE);
		}
	}

	return CBCGPPropList::OnMouseLeave(wParam, lParam);
}

void MLayeredPropList::MakeTransparent(BOOL bActive)
{
	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)))
		{
			MLayeredDockingControlBar* pWnd = ((MLayeredDockingControlBar*)pParent);
			pWnd->UpdateFrame(bActive);
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MBaseDockWnd)) )
		{
			MBaseDockWnd* pWnd = ((MBaseDockWnd*)pParent);

			CWnd* pParentPane = pWnd->GetParent();

			if( pParentPane->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
			{
				MLayeredDockingControlBar* pPane = (MLayeredDockingControlBar*)pParentPane;
				pPane->UpdateFrame(bActive);
			}
		}
	}
}

MLayeredProp* MLayeredPropList::GetProperty (int nIndex) const
{
	ASSERT_VALID (this);

	if (nIndex < 0 || nIndex >= m_lstProps.GetCount ())
	{
		ASSERT (FALSE);
		return NULL;
	}

	CBCGPProp* pBCGPProp =  m_lstProps.GetAt (m_lstProps.FindIndex (nIndex));
	MLayeredProp* pLayeredProp = NULL;
	if (pBCGPProp && pBCGPProp->IsKindOf(RUNTIME_CLASS(MLayeredProp)))
	{
		pLayeredProp = (MLayeredProp*)pBCGPProp;
	}
	else
	{
		// ���� ������ ���� MLayeredProp ��ӹ޵��� �����ؾ���
		ASSERT(0);
	}

	return pLayeredProp;
}