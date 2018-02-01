#include "stdafx.h"
#include "MProgressCtrl.h"

#include "MVisualManager.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MProgressCtrl, CBCGPProgressCtrl)

BEGIN_MESSAGE_MAP(MProgressCtrl, CBCGPProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	if (!CBCGPVisualManager::GetInstance ()->OnFillParentBarBackground (this, pDC))
	{
		globalData.DrawParentBackground (this, pDC);
	}

	CRect rect;
	GetClientRect (rect);

	CRect rectProgress = rect;
	rectProgress.DeflateRect (1, 1);

	BOOL bInfiniteMode = (GetStyle() & PBS_MARQUEE) != 0;

	int nMin = 0;
	int nMax = 100;
	int nPos = m_nMarqueeStep;

	if (!bInfiniteMode)
	{
		GetRange (nMin, nMax);
		nPos = GetPos();
	}

	CRect rectChunk (0, 0, 0, 0);

	const int nMarginHorz = 1;
	const int nMarginVert = 1;

	if (nMax > nMin && rectProgress.Width () > (nMarginHorz * 2) &&
		rectProgress.Height () > (nMarginVert * 2))
	{
		rectChunk = rectProgress;
		rectChunk.DeflateRect (nMarginHorz, nMarginVert);

		int ptPos = nPos * rectChunk.Width () / (nMax - nMin);

		if (bInfiniteMode)
		{
			const int nChunkWidth = min(rectProgress.Height() * 3, rectProgress.Width() / 6);

			rectChunk.InflateRect (nChunkWidth, 0);
			ptPos = nPos * rectChunk.Width () / (nMax - nMin);

			rectChunk.left += ptPos;
			ptPos = nChunkWidth;
		}

		rectChunk.right = min (rectChunk.left + ptPos, rectProgress.right - nMarginHorz);
		rectChunk.left = max (rectChunk.left, rectProgress.left + nMarginHorz);
	}

	CBCGPDrawOnGlass dog (m_bOnGlass);

#ifndef BCGP_EXCLUDE_RIBBON

	CBCGPRibbonProgressBar dummy;
	dummy.SetRange(nMin, nMax);
	dummy.SetPos(nPos, FALSE);

	MVisualManager::GetInstance()->OnDrawRibbonProgressBar (
		pDC, &dummy, rectProgress, rectChunk, bInfiniteMode);
#else
	MVisualManager::GetInstance()->OnDrawStatusBarProgress (pDC, NULL,
		rectProgress, nMax - nMin, 
		GetPos (),
		globalData.clrHilite, 
		(COLORREF)-1, 
		(COLORREF)-1,
		FALSE);
#endif

	{
		CRect rect;
		GetClientRect(&rect);

		CString strText;
		GetWindowText(strText);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(96, 96, 96));
		pDC->DrawText(strText, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
}