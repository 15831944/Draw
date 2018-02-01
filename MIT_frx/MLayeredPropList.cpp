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
		// 여기 들어오는 놈은 MLayeredProp 상속받도록 변경해야함
		ASSERT(0);
	}

	return pLayeredProp;
}