#include "stdafx.h"
#include "MTBMessageCtrl.h"
#include "MMemDC.h"

#include "MTable.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBMessageCtrl, CBCGPWnd)

BEGIN_MESSAGE_MAP(MTBMessageCtrl, CBCGPWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
END_MESSAGE_MAP()

MTBMessageCtrl::MTBMessageCtrl() :
	m_bDrawOnPaint(FALSE), // TRUE 는 구현 안했음
	m_rect(),
	m_bShow(FALSE),
	m_nHeight(0),
	m_nHorizontalPadding(0),
	m_nVerticalPadding(0),
	m_strMessage(_T("")),
	m_nMsgType(MT_COUNT),
	m_bMultiLine(FALSE),
	m_nHideElapse(3500),
	m_nShowFadeStep(4),
	m_nHideFadeStep(30),
	m_nFastHideFadeStep(5),
	m_hFont(NULL)
{
	for (int i = 0; i < MT_COUNT; i++) m_aIsMessageOn[i] = TRUE;
	m_aForeColor[MT_MESSAGE] = RGB(255, 255, 255);
	m_aBackColor[MT_MESSAGE] = RGB(0, 122, 204);
	m_aForeColor[MT_VALIDATE] = RGB(255, 255, 255);
	m_aBackColor[MT_VALIDATE] = RGB(202, 176, 0);
	m_aForeColor[MT_ERROR] = RGB(255, 255, 255);
	m_aBackColor[MT_ERROR] = RGB(202, 81, 0);
	m_aForeColor[MT_COMMIT] = RGB(255, 255, 255);
	m_aBackColor[MT_COMMIT] = RGB(97, 154, 21);
	m_aForeColor[MT_HELP] = RGB(255, 255, 255);
	m_aBackColor[MT_HELP] = RGB(104, 33, 122);

	WNDCLASS    wndcls;
	HINSTANCE   hInst = AfxGetInstanceHandle();
	 
	if ( !(::GetClassInfo(hInst, _T("TBMessageCtrl"), &wndcls)) )
	{
		wndcls.style            = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = _T("TBMessageCtrl");

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
		}
	}
}

MTBMessageCtrl::~MTBMessageCtrl()
{
}

void MTBMessageCtrl::MessageOnAll()
{
	for (int i = 0; i < MT_COUNT; i++) m_aIsMessageOn[i] = TRUE;
}

void MTBMessageCtrl::MessageOffAll()
{
	for (int i = 0; i < MT_COUNT; i++) m_aIsMessageOn[i] = FALSE;
}

void MTBMessageCtrl::MessageOn(MSG_TYPE nMsgType)
{
	m_aIsMessageOn[nMsgType] = TRUE;
}

void MTBMessageCtrl::MessageOff(MSG_TYPE nMsgType)
{
	m_aIsMessageOn[nMsgType] = FALSE;
}

void MTBMessageCtrl::Show(MSG_TYPE nMsgType, int nElapse, const CString& strMessage, va_list args)
{
	if (!m_aIsMessageOn[nMsgType]) return;
	m_bShow = TRUE;
	m_fade.SetFadeStep(m_nShowFadeStep);
	m_fade.StartFade(0, MFadeEffect::FADE_MAX);
	m_strMessage.FormatV(strMessage, args);
	m_nMsgType = nMsgType;
	if (nElapse > 0)
	{
		SetTimer(ID_TIMER_HIDE, nElapse, NULL);
	}
	GetTable()->AdjustLayout();
}

void MTBMessageCtrl::Hide(int nStep)
{
	if (!m_bShow) return;
	m_bShow = FALSE;
	m_fade.SetFadeStep(nStep);
	m_fade.StartFade(0);
}

void MTBMessageCtrl::Show(MSG_TYPE nMsgType, const CString& strMessage, ...)
{
	va_list ap;
	va_start(ap, strMessage);
	Show(nMsgType, m_nHideElapse, strMessage, ap);
	va_end(ap);
}

void MTBMessageCtrl::ShowConstant(MSG_TYPE nMsgType, const CString& strMessage, ...)
{
	va_list ap;
	va_start(ap, strMessage);
	Show(nMsgType, 0, strMessage, ap);
	va_end(ap);
}

void MTBMessageCtrl::Hide()
{
	Hide(m_nHideFadeStep);
}

BOOL MTBMessageCtrl::Create(DWORD dwStyle, const RECT& rect, MTable* pTable, UINT nID)
{
	m_pTable = pTable;	
	ASSERT(m_pTable);
	if (!CBCGPWnd::Create(_T("TBMessageCtrl"), _T(""), dwStyle, rect, pTable, nID)) return FALSE;	
	return TRUE;
}

UINT MTBMessageCtrl::GetDrawTextFormat()
{
	return m_bMultiLine ? DT_WORDBREAK : DT_SINGLELINE | DT_WORD_ELLIPSIS;
}

void MTBMessageCtrl::CalcHeight(int nWidth)
{
	CClientDC dc(GetTable());
	CRect rectMessage(0, 0, nWidth, 0);
	CFont* pOldFont = nullptr;
	if (GetFont()) pOldFont = dc.SelectObject(GetFont());
	dc.DrawText(m_strMessage, &rectMessage, DT_CALCRECT | GetDrawTextFormat());
	if (pOldFont) dc.SelectObject(pOldFont);
	m_nHeight = rectMessage.Height() + m_nVerticalPadding * 2;
}

void MTBMessageCtrl::CalcPadding()
{
	CClientDC dc(GetTable());
	CFont* pFont = (GetFont() ? GetFont() : dc.GetCurrentFont());
	ASSERT(pFont);
	TEXTMETRIC tm;
	ZeroMemory(&tm, sizeof(TEXTMETRIC));
	dc.GetTextMetrics(&tm);
	m_nHorizontalPadding = (int)(tm.tmAveCharWidth * 0.5);
	m_nVerticalPadding = (int)(tm.tmHeight * 0.1);
	if (m_nHorizontalPadding == 0) m_nHorizontalPadding = 1;
	if (m_nVerticalPadding == 0) m_nVerticalPadding = 1;
}

void MTBMessageCtrl::AdjustLayout(const CRect& rect)
{
	if (!GetSafeHwnd()) return;
		
	CPoint ptThis(0, 0);
	CSize szThis(0, 0);

	if (IsShowing())
	{
		CalcPadding();
		CalcHeight(rect.Width());

		ptThis.SetPoint(rect.left, rect.bottom - m_nHeight);
		szThis.SetSize(rect.Width(), m_nHeight);
	}
	m_rect.SetRect(ptThis, ptThis + szThis);
	
	SetWindowPos(NULL, ptThis.x, ptThis.y,
		szThis.cx, szThis.cy, SWP_NOZORDER | SWP_NOACTIVATE);
}

void MTBMessageCtrl::OnDraw(CDC* pDC, const CRect& rect)
{
	if (rect.IsRectEmpty()) return;
	if (m_fade.IsFading() && m_fade.GetFade() == 0) return;
	
	MMemDC memDC(*pDC, m_rect, m_fade.IsFading() ? (BYTE)m_fade.GetFade() : 0);
	memDC.GetDC().SelectObject(GetFont() ? GetFont() : pDC->GetCurrentFont());
	pDC = &memDC.GetDC();

	CRect rectBack(rect);
	pDC->FillSolidRect(&rectBack, m_aBackColor[m_nMsgType]);
	CRect rectMessage(rectBack);
	rectMessage.DeflateRect(m_nHorizontalPadding, m_nVerticalPadding);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_aForeColor[m_nMsgType]);
	pDC->DrawText(m_strMessage, rectMessage, GetDrawTextFormat());
}

void MTBMessageCtrl::OnDraw(CDC* pDC)
{
	OnDraw(pDC, m_rect);
}

void MTBMessageCtrl::OnFade(MFadeEffect* pFade)
{
	pFade->OnFade();
	if (pFade->IsFadeEnded()) GetTable()->AdjustLayout();
	else GetTable()->InvalidateRect(m_rect, FALSE);
}

int MTBMessageCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPWnd::OnCreate(lpCreateStruct) == -1) return -1;
	m_fade.Create(this);
	return 0;
}

void MTBMessageCtrl::OnDestroy()
{
	m_fade.Destroy();
}

BOOL MTBMessageCtrl::OnEraseBkgnd(CDC* pDC)
{
	if (!m_bDrawOnPaint) return FALSE;
	return CBCGPWnd::OnEraseBkgnd(pDC);
}

void MTBMessageCtrl::OnPaint()
{
	CPaintDC dc(this);
	if (m_bDrawOnPaint)
	{
		CRect rectClient;
		GetClientRect(&rectClient);

		CMemDC memDC(dc, this);
		CDC* pDC = &memDC.GetDC();
		OnDraw(pDC, rectClient);
	}
}

void MTBMessageCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	Hide(m_nFastHideFadeStep);
}

void MTBMessageCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == ID_TIMER_HIDE)
	{
		KillTimer(ID_TIMER_HIDE);
		Hide();
	}
}

LRESULT MTBMessageCtrl::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	m_hFont = (HFONT)wParam;
	return 0;
}

LRESULT MTBMessageCtrl::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return (LRESULT)m_hFont;
}