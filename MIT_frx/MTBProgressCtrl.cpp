#include "stdafx.h"
#include "MTBProgressCtrl.h"

#include "MTable.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBProgressCtrl, CBCGPWnd)

BEGIN_MESSAGE_MAP(MTBProgressCtrl, CBCGPWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

MTBProgressCtrl::MTBProgressCtrl() :
	m_align(ITBProgressCtrl::PCA_BOTTOM),
	m_bShow(FALSE),
	m_bShowCancelBtn(FALSE),
	m_nThickness(16),
	m_nCancelBtnLength(52)
{
	WNDCLASS    wndcls;
	HINSTANCE   hInst = AfxGetInstanceHandle();

	if ( !(::GetClassInfo(hInst, _T("TBProgressCtrl"), &wndcls)) )
	{
		wndcls.style            = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = _T("TBProgressCtrl");

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
		}
	}
}

MTBProgressCtrl::~MTBProgressCtrl()
{
}

BOOL MTBProgressCtrl::Create(DWORD dwStyle, const RECT& rect, MTable* pTable, UINT nID)
{
	m_pTable = pTable;	
	ASSERT(m_pTable);
	if (!CBCGPWnd::Create(_T("TBProgressCtrl"), _T(""), dwStyle, rect, pTable, nID)) return FALSE;	
	return TRUE;
}

void MTBProgressCtrl::Show(BOOL bShow, BOOL bShowCancelBtn)
{
	if (m_bShow == bShow) return;
	m_bShow = bShow;
	m_bShowCancelBtn = bShowCancelBtn;
	GetTable()->AdjustLayout();
}

void MTBProgressCtrl::SetAlign(Align align)
{
	if (m_align == align) return;
	m_align = align;
	GetTable()->AdjustLayout();
}

void MTBProgressCtrl::AdjustLayout(const CRect& rect, CRect& rectProgress)
{
	if (GetSafeHwnd()) return;
	if (!m_wndProgressBar.GetSafeHwnd()) return;
	if (!m_wndCancelBtn.GetSafeHwnd()) return;

	CPoint ptThis(rect.left, rect.top);
	CSize szThis(0, 0);
	CPoint ptProgressBar(0, 0);
	CSize szProgressBar(0, 0);
	CPoint ptProgressCancelBtn(0, 0);
	CSize szProgressCancelBtn(0, 0);

	if (m_bShow)
	{
		//// Grid Rect
		//const BOOL bCalcGridRect = FALSE;
		//if (bCalcGridRect)
		//{
		//	switch (m_align)
		//	{
		//	case PCA_LEFT: 
		//		m_rectHeader.left += m_nProgressBarThickness;
		//		m_rectRowHeader.left += m_nProgressBarThickness;
		//		break;
		//	case PCA_TOP: 
		//		m_rectRowHeader.top += m_nProgressBarThickness;
		//		m_rectHeader.top += m_nProgressBarThickness;
		//		break;
		//	case PCA_RIGHT: 
		//		m_rectList.right -= m_nProgressBarThickness;
		//		m_rectHeader.right -= m_nProgressBarThickness;
		//		if (GetColumnsInfo().IsAutoSize())
		//		{
		//			GetColumnsInfo().Resize(m_rectList.Width());
		//		}
		//		break;
		//	case PCA_BOTTOM:
		//		m_rectRowHeader.bottom -= m_nProgressBarThickness;
		//		m_rectList.bottom -= m_nProgressBarThickness;
		//		break;
		//	case PCA_CENTER: break; // 이건 불가능
		//	default: ASSERT(0); break;
		//	}
		//}

		// Point
		switch (m_align)
		{
		case PCA_LEFT: 
			ptProgressBar.SetPoint(rect.left, rect.top); 
			break;
		case PCA_TOP: 
			ptProgressBar.SetPoint(rect.left, rect.top); 
			break;
		case PCA_RIGHT:
			ptProgressBar.SetPoint(rect.right - m_nThickness, rect.top); 
			break;
		case PCA_BOTTOM:
			ptProgressBar.SetPoint(rect.left, rect.bottom - m_nThickness); 
			break;
		case PCA_CENTER:
			ptProgressBar.SetPoint(rect.left, rect.top + (int)(rect.Height() * 0.5) - (int)(m_nThickness * 0.5)); 
			break;
		default: ASSERT(0); break;
		}

		// Size
		switch (m_align)
		{
		case PCA_LEFT: case PCA_RIGHT:
			szProgressBar.SetSize(m_nThickness, rect.Height());
			break; 
		case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
			szProgressBar.SetSize(rect.Width(), m_nThickness);
			break;
		default: ASSERT(0); break;
		}		

		// TODO: 사이즈 키우면 딱 맞게 그려지긴 하는데 
		//       스크롤을 한 픽셀 먹어 버린다...ㅠㅜ
		//       BCG 에서 그릴때 한 픽셀 덜 그리는거 같다.
		//szProgressBar.cy++;
		//szProgressBar.cx++;
	}
	rectProgress.SetRect(ptProgressBar, ptProgressBar + szProgressBar);

	if (m_align)
	{
		// Progress Bar Size
		switch (m_align)
		{
		case PCA_LEFT: case PCA_RIGHT:
			szProgressBar.cy -= m_nCancelBtnLength;
			break; 
		case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
			szProgressBar.cx -= m_nCancelBtnLength;
			break;
		default: ASSERT(0); break;
		}		

		// Point
		switch (m_align)
		{
		case PCA_LEFT: case PCA_RIGHT:
			ptProgressCancelBtn.SetPoint(ptProgressBar.x, ptProgressBar.y + szProgressBar.cy); 
			break;
		case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
			ptProgressCancelBtn.SetPoint(ptProgressBar.x + szProgressBar.cx, ptProgressBar.y); 
			break;
		default: ASSERT(0); break;
		}

		// Size
		switch (m_align)
		{
		case PCA_LEFT: case PCA_RIGHT:
			szProgressCancelBtn.SetSize(szProgressBar.cx, m_nCancelBtnLength);
			break; 
		case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
			szProgressCancelBtn.SetSize(m_nCancelBtnLength, szProgressBar.cy);
			break;
		default: ASSERT(0); break;
		}	
	}

	// Vertical
	switch (m_align)
	{
	case PCA_LEFT: case PCA_RIGHT:
		m_wndProgressBar.ModifyStyle(0, PBS_VERTICAL);
		break;
	case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
		m_wndProgressBar.ModifyStyle(PBS_VERTICAL, 0);
		break;
	default: ASSERT(0); break;
	}

	// Point
	ptThis = ptProgressBar;
	// Size
	switch (m_align)
	{
	case PCA_LEFT: case PCA_RIGHT:
		szThis.SetSize(szProgressBar.cx, szProgressBar.cy + szProgressCancelBtn.cy);
		break;
	case PCA_TOP: case PCA_BOTTOM: case PCA_CENTER:
		szThis.SetSize(szProgressBar.cx + szProgressCancelBtn.cx, szProgressBar.cy);
		break;
	default: ASSERT(0); break;
	}

	ptProgressBar.Offset(-ptThis.x, -ptThis.y);
	ptProgressCancelBtn.Offset(-ptThis.x, -ptThis.y);
	
	SetWindowPos(NULL, ptThis.x, ptThis.y,
		szThis.cx, szThis.cy, SWP_NOZORDER | SWP_NOACTIVATE);
	m_wndProgressBar.SetWindowPos(NULL, ptProgressBar.x, ptProgressBar.y,
		szProgressBar.cx, szProgressBar.cy, SWP_NOZORDER | SWP_NOACTIVATE);
	m_wndCancelBtn.SetWindowPos(NULL, ptProgressCancelBtn.x, ptProgressCancelBtn.y,
		szProgressCancelBtn.cx, szProgressCancelBtn.cy, SWP_NOZORDER | SWP_NOACTIVATE);
}

int MTBProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPWnd::OnCreate(lpCreateStruct) == -1) return -1;
	m_wndProgressBar.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, CRect(), this, 1);
	m_wndCancelBtn.Create(_STR("Cancel"), WS_CHILD | WS_VISIBLE, CRect(), this, 2);
	return 0;
}