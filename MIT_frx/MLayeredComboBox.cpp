#include "StdAfx.h"
#include "MLayeredComboBox.h"
#include "MLayeredDockingControlBar.h"
#include "MLayeredPropList.h"
#include "MVisualManager.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredComboBoxButton, CBCGPToolbarComboBoxButton)

IMPLEMENT_DYNAMIC(MLayeredComboBox, CBCGPComboBox)
MLayeredComboBox::MLayeredComboBox(void)
{
	m_bTrack = FALSE;
	m_nHeight = 0;
}

MLayeredComboBox::~MLayeredComboBox(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredComboBox, CBCGPComboBox)
	//{{AFX_MSG_MAP(MLayeredComboBox)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL MLayeredComboBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{ 
	if (message == WM_DRAWITEM)
	{
		// 아무리 Background 칠해놔도 여기 오기전에 어디선가
		// 흰색 테두리를 그려버림. 지운다!!
		LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT)lParam;

		CRect rect(lpDrawItemStruct->rcItem);
		rect.InflateRect(1, 1);

		CRgn rgn;
		rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);

		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		pDC->SelectClipRgn(&rgn);

		COLORREF clrBack = pDC->GetBkColor();

		pDC->FillSolidRect(rect, clrBack);
	}
	return CBCGPComboBox::OnChildNotify(message, wParam, lParam, pResult);
}

HBRUSH MLayeredComboBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{ 
	COLORREF clrBack = RGB(0,0,0);

	if (pDC)
	{
		pDC->SetBkColor(clrBack);
	}

	if (m_brush.GetSafeHandle()) 
	{
		LOGBRUSH log;
		ZeroMemory(&log, sizeof(LOGBRUSH));
		m_brush.GetLogBrush(&log);
		if (log.lbColor != clrBack)
		{
			m_brush.DeleteObject();
			m_brush.CreateSolidBrush(clrBack);
		}
	}
	else
	{
		m_brush.CreateSolidBrush(clrBack);
	}

	return (HBRUSH)m_brush;
} 

void MLayeredComboBox::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CBCGPComboBox::OnWindowPosChanging(lpwndpos);
	if (m_nHeight > 0)
	{
		lpwndpos->cy = m_nHeight;
	}
}

//**************************************************************************
void MLayeredComboBox::OnPaint() 
{
#ifndef _BCGSUITE_
	if (globalData.bIsWindows9x)
	{
		Default();
		return;
	}
#endif

	if ((GetStyle () & 0x0003L) == CBS_SIMPLE)
	{
		Default ();
		return;
	}

	if (!m_bVisualManagerStyle && !m_bOnGlass)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting

	BYTE alpha = 0;
	if (m_bOnGlass)
	{
		alpha = 255;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPMemDC memDC (dc, this, alpha);
	CDC* pDC = &memDC.GetDC ();

	BOOL bDefaultDraw = TRUE;

#ifndef _BCGSUITE_
	if ((GetStyle() & CBS_OWNERDRAWFIXED) == 0 && (GetStyle() & CBS_OWNERDRAWVARIABLE) == 0)
	{
		bDefaultDraw = !CBCGPVisualManager::GetInstance ()->OnDrawComboBoxText(pDC, this);
	}

#endif

	if (bDefaultDraw)
	{
		SendMessage (WM_PRINTCLIENT, (WPARAM) pDC->GetSafeHdc (), (LPARAM) PRF_CLIENT);
	}

	if ((GetStyle() & CBS_OWNERDRAWFIXED) != 0 || (GetStyle() & CBS_OWNERDRAWVARIABLE) != 0)
	{
		pDC->SelectClipRgn (NULL);
	}

	const int cxDropDown = ::GetSystemMetrics (SM_CXVSCROLL) + 4;

	m_rectBtn = rectClient;
	m_rectBtn.left = m_rectBtn.right - cxDropDown;

	m_rectBtn.DeflateRect (2, 2);

	CBCGPDrawOnGlass dog (m_bOnGlass);

	MLayeredComboBoxButton buttonDummy;
#ifndef _BCGSUITE_
	buttonDummy.m_bIsCtrl = TRUE;

	CBCGPVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);

	// 무조건 OnDrawControlBorder 로 넘김
	//if (bDefaultDraw)
	//{
	//	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrBarShadow);
	//}
	//else
	//{
	CBCGPVisualManager::GetInstance ()->OnDrawControlBorder (pDC, rectClient, this, m_bOnGlass);
	//}

#else
	CMFCVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);

	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrBarShadow);

#endif

}

void MLayeredComboBox::OnMouseMove(UINT nFlags, CPoint point)
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
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			MLayeredPropList* pPropList = (MLayeredPropList*)pParent;

			pPropList->MakeTransparent(TRUE);
		}
	}

	CBCGPComboBox::OnMouseMove(nFlags, point);
}

void MLayeredComboBox::OnMouseLeave()
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
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			//MLayeredPropList* pPropList = (MLayeredPropList*)pParent; // cppcheck - 사용안됨

			//pPropList->MakeTransparent(FALSE);
		}
	}

	CBCGPComboBox::OnMouseLeave();
}

void MLayeredComboBox::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPComboBox::OnSetFocus(pOldWnd);

	if( pOldWnd && pOldWnd->GetSafeHwnd() )
	{
		if( pOldWnd->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			MLayeredPropList* pPropList = (MLayeredPropList*)pOldWnd;
			pPropList->MakeTransparent(TRUE);
		}
	}
}
