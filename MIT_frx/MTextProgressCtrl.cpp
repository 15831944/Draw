#include "stdafx.h"
#include "MTextProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit;
using namespace mit::frx;

MTextProgressCtrl::MTextProgressCtrl()
: CBCGPRibbonProgressBar( NULL, 90, 22 )
{
	m_iStepSize		= 1;
	m_bShowText		= TRUE;
	m_clrFore		= ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrBk			= ::GetSysColor(COLOR_WINDOW);
	m_clrTextFore	= ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrTextBk		= ::GetSysColor(COLOR_WINDOW);

	m_iBarWidth = -1;

	m_strFaceName = _T("Tahoma");
	m_iWeight = FW_BOLD;
	m_bItalic = FALSE;
	m_bUnderline = FALSE;
}

MTextProgressCtrl::MTextProgressCtrl(UINT nID, int nWidth, int nHeight)
: CBCGPRibbonProgressBar( nID, nWidth, nHeight )
{
	m_iStepSize		= 1;
	m_bShowText		= TRUE;	
	m_clrFore		= ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrBk			= ::GetSysColor(COLOR_WINDOW);
	m_clrTextFore	= ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrTextBk		= ::GetSysColor(COLOR_WINDOW);

	m_iBarWidth = -1;	
	m_strFaceName = _T("Tahoma");
	m_iWeight = FW_BOLD;
	m_bItalic = FALSE;
	m_bUnderline = FALSE;
}

MTextProgressCtrl::~MTextProgressCtrl()
{
}

void MTextProgressCtrl::SetForeColour(COLORREF col)
{
	m_clrFore = col;
}

void MTextProgressCtrl::SetBkColour(COLORREF col)
{
	m_clrBk = col;
}

void MTextProgressCtrl::SetTextForeColour(COLORREF col)
{
	m_clrTextFore = col;
}

void MTextProgressCtrl::SetTextBkColour(COLORREF col)
{
	m_clrTextBk = col;
}

COLORREF MTextProgressCtrl::GetForeColour()
{
	return m_clrFore;
}

COLORREF MTextProgressCtrl::GetBkColour()
{
	return m_clrBk;
}

COLORREF MTextProgressCtrl::GetTextForeColour()
{
	return m_clrTextFore;
}

COLORREF MTextProgressCtrl::GetTextBkColour()
{
	return m_clrTextBk;
}

void MTextProgressCtrl::SetFontData(CString strFaceName, int nWeight, BOOL bItalic, BOOL bUnderline)
{
	m_strFaceName = strFaceName;
	m_iWeight     = nWeight;
	m_bItalic     = bItalic;
	m_bUnderline  = bUnderline;
}
/////////////////////////////////////////////////////////////////////////////
// MTextProgressCtrl message handlers

void MTextProgressCtrl::SetShowText(BOOL bShow)
{ 
	m_bShowText = bShow;
	Redraw();
}

int MTextProgressCtrl::StepIt() 
{
	int iPos = GetPos();
	if(m_bInfiniteMode && iPos > GetRangeMax() ) SetPos(0);

	SetPos(iPos + m_iStepSize);

	return GetPos();
}

int MTextProgressCtrl::OffsetPos(int iOffset)
{
	int iPos = GetPos();
	SetPos(iPos + iOffset);
	return GetPos();
}

int MTextProgressCtrl::SetStep(int nStep)
{
	int nOldStep = m_iStepSize;
	m_iStepSize = nStep;
	return nOldStep;
}

void MTextProgressCtrl::SetWidth(int iWidth)
{
	m_nWidth = iWidth;
	Redraw();
}

int MTextProgressCtrl::GetWidth()
{
	return m_nWidth;
}

void MTextProgressCtrl::SetHeight(int iHeight)
{
	m_nHeight = iHeight;
	Redraw();
}

int MTextProgressCtrl::GetHeight()
{
	return m_nHeight;
}

void MTextProgressCtrl::OnDraw(CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	if (m_rect.IsRectEmpty () || m_nMax - m_nMin <= 0)
	{
		return;
	}

	CRect rectProgress = m_rect;
	rectProgress.DeflateRect (5, 1);

	CRect rectChunk = rectProgress;
	rectChunk.right = rectChunk.left + 
		(m_nPos - m_nMin) * rectChunk.Width () / (m_nMax - m_nMin);
	rectChunk.DeflateRect (1, 1);

	CBCGPVisualManager::GetInstance ()->OnDrawRibbonProgressBar (
		pDC, this, rectProgress, rectChunk, m_bInfiniteMode);

	int iPos = GetPos();
	int iMax = GetRangeMax();
	int iMin = GetRangeMin();
	double Fraction = (double)(iPos - iMin) / ((double)(iMax - iMin));

	CRect LeftRect, RightRect, ClientRect;

	LeftRect = RightRect = ClientRect = m_rect;

	if (m_bShowText)
	{
		CString str;
		if (m_strText.GetLength())
			str = m_strText;
		else
			str.Format(_T("%d%%"), (int)(Fraction*100.0));

		pDC->SetBkMode(TRANSPARENT);

		CRgn rgn;
		rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
		pDC->SelectClipRgn(&rgn);
		pDC->SetTextColor(m_clrTextBk);

		CFont font;
		font.CreateFont(13, 0, 0, 0, m_iWeight, m_bItalic, m_bUnderline, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, m_strFaceName);
		CFont* pFont = pDC->SelectObject(&font);

		pDC->DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rgn.DeleteObject();
		rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
		pDC->SelectClipRgn(&rgn);
		pDC->SetTextColor(m_clrTextFore);

		pDC->DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		pDC->SelectObject(pFont);
	}
}