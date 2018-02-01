#include "stdafx.h"
#include "MMemDC.h"

using namespace mit::frx;

struct FRIENDGLOBAL_DATA : public BCGPGLOBAL_DATA
{
	friend class MMemDC;
};

BOOL MMemDC::m_bUseMemoryDC = TRUE;

MMemDC::MMemDC(CDC& dc, CWnd* pWnd, BYTE alpha, double dblScale) :
	m_dc			(dc),
	m_bMemDC		(FALSE),
	m_hBufferedPaint(NULL),
	m_pOldBmp		(NULL),
	m_alpha			(alpha),
	m_dblScale		(dblScale)
{
	ASSERT_VALID(pWnd);

	FRIENDGLOBAL_DATA* pGlobalData = (FRIENDGLOBAL_DATA*)&globalData;

	if (m_dblScale <= 0)
	{
		m_dblScale = 1.0;
	}

	pWnd->GetClientRect (m_rect);

	m_rect.right += pWnd->GetScrollPos (SB_HORZ);
	m_rect.bottom += pWnd->GetScrollPos (SB_VERT);

	if (m_alpha == 0 && m_dblScale == 1.0 && pGlobalData->m_pfBeginBufferedPaint != NULL && pGlobalData->m_pfEndBufferedPaint != NULL)
	{
		HDC hdcPaint = NULL;

		m_hBufferedPaint = (*pGlobalData->m_pfBeginBufferedPaint) 
			(dc.GetSafeHdc (), m_rect, BCGP_BPBF_TOPDOWNDIB, NULL, &hdcPaint);

		if (m_hBufferedPaint != NULL && hdcPaint != NULL)
		{
			m_bMemDC = TRUE;
			m_dcMem.Attach (hdcPaint);
		}
	}
	else
	{
		if (m_bUseMemoryDC &&
			m_dcMem.CreateCompatibleDC (&m_dc) &&
			m_bmp.CreateCompatibleBitmap (&m_dc, m_rect.Width (), m_rect.Height ()))
		{
			//-------------------------------------------------------------
			// Off-screen DC successfully created. Better paint to it then!
			//-------------------------------------------------------------
			m_bMemDC = TRUE;
			m_pOldBmp = m_dcMem.SelectObject (&m_bmp);
		}
	}
}

MMemDC::MMemDC(CDC& dc, const CRect& rect, BYTE alpha, double dblScale) :
	m_dc			(dc),
	m_bMemDC		(FALSE),
	m_hBufferedPaint(NULL),
	m_pOldBmp		(NULL),
	m_rect			(rect),
	m_alpha			(alpha),
	m_dblScale		(dblScale)
{
	ASSERT(!m_rect.IsRectEmpty());

	FRIENDGLOBAL_DATA* pGlobalData = (FRIENDGLOBAL_DATA*)&globalData;

	if (m_dblScale <= 0)
	{
		m_dblScale = 1.0;
	}

	if (m_alpha == 0 && m_dblScale == 1.0 && pGlobalData->m_pfBeginBufferedPaint != NULL && pGlobalData->m_pfEndBufferedPaint != NULL)
	{
		HDC hdcPaint = NULL;

		m_hBufferedPaint = (*pGlobalData->m_pfBeginBufferedPaint) 
			(dc.GetSafeHdc (), m_rect, BCGP_BPBF_TOPDOWNDIB, NULL, &hdcPaint);

		if (m_hBufferedPaint != NULL && hdcPaint != NULL)
		{
			m_bMemDC = TRUE;
			m_dcMem.Attach (hdcPaint);
		}
	}
	else
	{
		if (m_bUseMemoryDC &&
			m_dcMem.CreateCompatibleDC (&m_dc) &&
			m_bmp.CreateCompatibleBitmap (&m_dc, m_rect.Width (), m_rect.Height ()))
		{
			//-------------------------------------------------------------
			// Off-screen DC successfully created. Better paint to it then!
			//-------------------------------------------------------------
			m_bMemDC = TRUE;
			m_pOldBmp = m_dcMem.SelectObject (&m_bmp);
			m_dcMem.SetViewportOrg(-m_rect.TopLeft());
		}
	}
}

MMemDC::~MMemDC()
{
	if (m_hBufferedPaint != NULL)
	{
		FRIENDGLOBAL_DATA* pGlobalData = (FRIENDGLOBAL_DATA*)&globalData;

		m_dcMem.Detach ();

		if (m_alpha != 0 && pGlobalData->m_pfBufferedPaintSetAlpha != NULL)
		{
			(*pGlobalData->m_pfBufferedPaintSetAlpha) (m_hBufferedPaint, NULL, m_alpha);
		}

		(*pGlobalData->m_pfEndBufferedPaint) (m_hBufferedPaint, TRUE);
	}
	else if (m_bMemDC)
	{
		//--------------------------------------
		// Copy the results to the on-screen DC:
		//-------------------------------------- 
		CRect rectClip;
		int nClipType = m_dc.GetClipBox (rectClip);

		if (nClipType != NULLREGION)
		{
			if (nClipType != SIMPLEREGION)
			{
				rectClip = m_rect;
			}

			if (m_dblScale != 1.0)
			{
				CRect rectDst = m_rect;
				rectDst.right = rectDst.left + (int)(0.5 + m_dblScale * m_rect.Width());
				rectDst.bottom = rectDst.top + (int)(0.5 + m_dblScale * m_rect.Height());

				m_dc.SetStretchBltMode(HALFTONE);

				if (m_dblScale < 1.0)
				{
					CRect rectRight = m_rect;
					rectRight.left = rectDst.right;

					m_dc.FillRect(rectRight, &globalData.brWindow);

					CRect rectBottom = m_rect;
					rectBottom.top = rectDst.bottom;

					m_dc.FillRect(rectBottom, &globalData.brWindow);
				}

				m_dc.StretchBlt(rectDst.left, rectDst.top,
					rectDst.Width(), rectDst.Height(), 
					&m_dcMem, m_rect.left, m_rect.top,
					m_rect.Width(), m_rect.Height(), SRCCOPY);
			}
			else
			{
				if (m_alpha > 0)
				{
					BLENDFUNCTION bf;
					bf.BlendOp = AC_SRC_OVER;
					bf.BlendFlags = 0;
					bf.SourceConstantAlpha = m_alpha;
					bf.AlphaFormat = 0;
					m_dc.AlphaBlend(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
						&m_dcMem, m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), bf);
				}
				else
				{
					m_dc.BitBlt (rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(),
						&m_dcMem, rectClip.left, rectClip.top, SRCCOPY);
				}
			}
		}

		m_dcMem.SelectObject (m_pOldBmp);
	}
}