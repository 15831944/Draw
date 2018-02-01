#include "stdafx.h"
#include "MLayeredSliderCtrl.h"
#include "MVisualManager.h"
#include "MLayeredWindow.h"

using namespace mit;
using namespace mit::frx;

static const int cxSliderWidth = 18;
static const int cySliderHeight = 18;

static const int cxThumbWidth = 10; 
static const int cyThumbHeight = 10; 

static const int nThumbIndex = 0;
static const int nSliderIndex = 1;
static const int nZoomInIndex = 2;
static const int nZoomOutIndex = 3;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//*****************************************************************************************************
IMPLEMENT_DYNCREATE(MLayeredSliderCtrl, CBCGPCaptionButton)

MLayeredSliderCtrl::MLayeredSliderCtrl( int	nWidth, DWORD dwStyle)
{
	CommonInit ();

	m_nWidth = nWidth;
	m_dwStyle = dwStyle;
}
//*****************************************************************************************************
MLayeredSliderCtrl::~MLayeredSliderCtrl()
{
}
//*****************************************************************************************************
void MLayeredSliderCtrl::CommonInit ()
{
	m_nMin = 0;
	m_nMax = 100;
	m_nPos = 0;
	m_nPageSize = 10;
	m_bZoomButtons = FALSE;
	m_nWidth = 100;
	m_dwStyle = 0;

	m_rectZoomOut.SetRectEmpty ();
	m_rectZoomIn.SetRectEmpty ();
	m_rectSlider.SetRectEmpty ();
	m_rectThumb.SetRectEmpty ();
	m_rectLabel.SetRectEmpty ();

	m_bIsHighlighted = FALSE;
	m_bIsFocused = FALSE;
	m_bIsPressed = FALSE;
	m_bIsDisabled = FALSE;

	m_nHighlighted = -1;
	m_nPressed = -1;
	m_ptCapture.SetPoint(0, 0);

	m_strText.Empty();
	m_pParentMiniFrame = NULL;
}
//********************************************************************************
void MLayeredSliderCtrl::OnDraw (CDC* pDC, BOOL bActive, BOOL bHorz, BOOL bMaximized, BOOL bDisabled)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	// 차후 사용할 일이 생기면... 지금은 그릴 필요가 없는 부분이다.
	if( FALSE )
	{
		// Draw border + fill content:
		CBCGPCaptionButton::OnDraw (pDC, bActive, bHorz, bMaximized, bDisabled);
	}

	if (m_rect.IsRectEmpty ())
	{
		return;
	}

	MVisualManager* pVisualManager = NULL;
	if( CBCGPVisualManager::GetInstance ()->IsKindOf(RUNTIME_CLASS(MVisualManager)) )
	{
		pVisualManager = (MVisualManager*)CBCGPVisualManager::GetInstance();
	}

	if( !pVisualManager ) return;

	if (m_bZoomButtons)
	{
		// Draw zoom buttons:
		pVisualManager->OnDrawRibbonSliderZoomButton (
			pDC, m_rectZoomOut, TRUE, 
			m_bIsHighlighted && m_nHighlighted == nZoomOutIndex,
			m_bIsPressed && m_nPressed == nZoomOutIndex, IsDisabled ());

		pVisualManager->OnDrawRibbonSliderZoomButton (
			pDC, m_rectZoomIn, FALSE, 
			m_bIsHighlighted && m_nHighlighted == nZoomInIndex,
			m_bIsPressed && m_nPressed == nZoomInIndex, IsDisabled ());
	}

	// Draw channel:
	CRect rectChannel = m_rectSlider;

	if (IsVert ())
	{
		rectChannel.left = rectChannel.CenterPoint ().x - 1;
		rectChannel.right = rectChannel.left + 2;
	}
	else
	{
		rectChannel.top = rectChannel.CenterPoint ().y - 1;
		rectChannel.bottom = rectChannel.top + 2;
	}

	pVisualManager->OnDrawRibbonSliderChannel (
		pDC, this, rectChannel);

	// Draw thumb:
	pVisualManager->OnDrawRibbonSliderThumb (
		pDC, this, m_rectThumb,
		(m_bIsHighlighted && (m_nHighlighted == nThumbIndex || m_nHighlighted == nSliderIndex)) || IsFocused (),
		m_bIsPressed && m_nPressed == nThumbIndex, IsDisabled ());

	if (!m_rectLabel.IsRectEmpty () && !m_strText.IsEmpty ())
	{
		DoDrawText (pDC, m_strText, m_rectLabel, DT_CENTER | DT_SINGLELINE);
	}
}

int MLayeredSliderCtrl::DoDrawText (CDC* pDC, const CString& strText, CRect rectText, UINT uiDTFlags,
										COLORREF clrText)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	COLORREF clrTextOld = (COLORREF)-1;
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	int nRes = pDC->DrawText (strText, rectText, uiDTFlags);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	return nRes;
}

void MLayeredSliderCtrl::Redraw ()
{
	ASSERT_VALID (this);

	if( !m_pParentMiniFrame ) return;

	if (m_pParentMiniFrame->GetSafeHwnd () != NULL)
	{
		m_pParentMiniFrame->RedrawWindow (m_rect);
	}
}

//*****************************************************************************
CSize MLayeredSliderCtrl::GetRegularSize (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	const BOOL bIsVert = IsVert ();

	CSize size (bIsVert ? max (m_nWidth, cxSliderWidth) : m_nWidth, 
				bIsVert ? m_nWidth : cySliderHeight);

	if (m_dwStyle & TBS_VERT)
	{
		size.cx = 50;
	}

	double dblScale = globalData.GetRibbonImageScale ();

	if (bIsVert)
	{
		if (!m_strText.IsEmpty ())
		{
			int nTextWidth = pDC->GetTextExtent (m_strText).cx;
			size.cx = max (size.cx, nTextWidth);
		}

		int nZoomButtonSize = cxSliderWidth;

		if (dblScale > 1.)
		{
			dblScale = 1. + (dblScale - 1.) / 2;
			size.cx = (int)(.5 + dblScale * size.cx);
			nZoomButtonSize = (int)(.5 + dblScale * nZoomButtonSize);
		}

		if (m_bZoomButtons)
		{
			size.cy += 2 * nZoomButtonSize;
		}
	}
	else
	{
		if (dblScale > 1.)
		{
			dblScale = 1. + (dblScale - 1.) / 2;
			size.cy = (int)(.5 + dblScale * size.cy);
		}

		if (m_bZoomButtons)
		{
			size.cx += 2 * size.cy;
		}
	}

	return size;
}
//*****************************************************************************
void MLayeredSliderCtrl::SetRange (int nMin, int nMax)
{
	ASSERT_VALID (this);

	m_nMin = nMin;
	m_nMax = nMax;
}

//*****************************************************************************
void MLayeredSliderCtrl::MakeTransParent(BYTE factor)
{
	if( m_pParentMiniFrame && m_pParentMiniFrame->GetSafeHwnd() )
	{
		if (!MLayeredWindow::MakeWindowTransparent(m_pParentMiniFrame, factor) )
		{
			TRACE(_T("Transparency is not supported on this platform"));
		}
	}
}

//*****************************************************************************
void MLayeredSliderCtrl::SetPos (int nPos, BOOL bRedraw)
{
	ASSERT_VALID (this);

	m_nPos = min (max (m_nMin, nPos), m_nMax);
	SetThumbRect ();

	MakeTransParent((BYTE)m_nPos);

	if (bRedraw)
	{
		Redraw ();
	}
}
//*****************************************************************************
void MLayeredSliderCtrl::SetPageSize (int nPageSize)
{
	ASSERT_VALID (this);
	m_nPageSize = nPageSize;
}
//*****************************************************************************
void MLayeredSliderCtrl::SetZoomButtons (BOOL bSet)
{
	ASSERT_VALID (this);
	m_bZoomButtons = bSet;
}

//*****************************************************************************
void MLayeredSliderCtrl::SetThumbRect ()
{
	ASSERT_VALID (this);

	if (m_nMax <= m_nMin || m_rect.IsRectEmpty ())
	{
		m_rectThumb.SetRectEmpty ();
		return;
	}

	m_rectThumb = m_rectSlider;

	double dblScale = globalData.GetRibbonImageScale ();

	if (IsVert ())
	{
		double dy = ((double) m_rectSlider.Height ()) / (m_nMax - m_nMin);
		int yOffset = (int) (.5 + dy * (m_nPos - m_nMin));

		int nThumbHeight = cyThumbHeight;

		if (m_rectThumb.Width () > cxSliderWidth)
		{
			m_rectThumb.left = m_rectThumb.CenterPoint ().x - cxSliderWidth / 2;
			m_rectThumb.right = m_rectThumb.left + cxSliderWidth;
		}
		
		if (dblScale > 1.)
		{
			dblScale = 1. + (dblScale - 1.) / 2;

			nThumbHeight = (int)(.5 + dblScale * nThumbHeight) + 1;
			m_rectThumb.DeflateRect (2, 0);
		}

		m_rectThumb.bottom -= yOffset - nThumbHeight / 2;
		m_rectThumb.top = m_rectThumb.bottom - nThumbHeight;
	}
	else
	{
		double dx = ((double) m_rectSlider.Width ()) / (m_nMax - m_nMin);
		int xOffset = (int) (.5 + dx * (m_nPos - m_nMin));

		int nThumbWidth = cxThumbWidth;
		
		if (dblScale > 1.)
		{
			dblScale = 1. + (dblScale - 1.) / 2;

			nThumbWidth = (int)(.5 + dblScale * nThumbWidth) + 1;
			m_rectThumb.DeflateRect (0, 2);
		}

		m_rectThumb.left += xOffset - nThumbWidth / 2;
		m_rectThumb.right = m_rectThumb.left + nThumbWidth;
	}
}
//*****************************************************************************
void MLayeredSliderCtrl::OnLButtonDown (CPoint point)
{
	ASSERT_VALID (this);

	if (!IsDisabled ())
	{
		m_nPressed = GetHitTest (point);
		if (m_nPressed == nThumbIndex)
		{
			if (m_pParentMiniFrame && m_pParentMiniFrame->GetSafeHwnd())
			{
				MakeTransParent((BYTE)m_nPos);
				::SetCapture(m_pParentMiniFrame->GetSafeHwnd());
				m_ptCapture = m_rectThumb.CenterPoint() - point;
			}
		}
		else if (m_nPressed == nSliderIndex)
		{
			SetPos (GetPosFromPoint (point));
		}
		Redraw ();
	}
}
//*****************************************************************************
void MLayeredSliderCtrl::OnLButtonUp (CPoint point)
{
	ASSERT_VALID (this);

	if (m_pParentMiniFrame && m_pParentMiniFrame->GetSafeHwnd())
	{
		if (::GetCapture() == m_pParentMiniFrame->GetSafeHwnd())
		{
			::ReleaseCapture();
			point += m_ptCapture;
		}
	}

	if (m_nPressed == m_nHighlighted && !IsDisabled ())
	{
		switch (m_nPressed)
		{
		case nZoomInIndex:
			SetPos (m_nPos + m_nPageSize);
			break;
		case nZoomOutIndex:
			SetPos (m_nPos - m_nPageSize);
			break;
		case nThumbIndex:
			SetPos (GetPosFromPoint (point));
			break;
		default:
			break;
		}
	}
}
//*****************************************************************************
void MLayeredSliderCtrl::OnMouseMove (CPoint point)
{
	ASSERT_VALID (this);

	if (IsDisabled ())
	{
		return;
	}

	int nHighlightedOld = m_nHighlighted;

	m_nHighlighted = GetHitTest (point);

	if (nHighlightedOld != m_nHighlighted)
	{
		Redraw ();
	}

	if (m_bIsPressed)
	{
		if (m_nPressed == nThumbIndex)
		{			
			if (m_pParentMiniFrame && m_pParentMiniFrame->GetSafeHwnd())
			{
				ASSERT(::GetCapture() == m_pParentMiniFrame->GetSafeHwnd());
				point += m_ptCapture;
			}
			int nPos = GetPosFromPoint (point);
			if (nPos != m_nPos)
			{
				SetPos (nPos);				
			}
		}
	}
}
//*****************************************************************************
int MLayeredSliderCtrl::GetHitTest (CPoint point) const
{
	ASSERT_VALID (this);

	if (m_rectThumb.PtInRect (point))
	{
		return nThumbIndex;
	}

	if (m_rectSlider.PtInRect (point))
	{
		return nSliderIndex;
	}

	if (m_rectZoomOut.PtInRect (point))
	{
		return nZoomOutIndex;
	}

	if (m_rectZoomIn.PtInRect (point))
	{
		return nZoomInIndex;
	}

	return -1;
}
//*****************************************************************************
int MLayeredSliderCtrl::GetPosFromPoint (CPoint pt)
{
	ASSERT_VALID (this);

	if (m_nMax <= m_nMin || m_rect.IsRectEmpty ())
	{
		return m_nMin;
	}

	if (IsVert ())
	{
		const double dy = ((double) m_rectSlider.Height ()) / (m_nMax - m_nMin);
		const int yOffset = m_rectSlider.bottom - pt.y;

		return m_nMin + (int) ((double) yOffset / dy);
	}
	else
	{
		const double dx = ((double) m_rectSlider.Width ()) / (m_nMax - m_nMin);
		const int xOffset = pt.x - m_rectSlider.left;

		return m_nMin + (int) ((double) xOffset / dx);
	}
}
//***************************************************************************
BOOL MLayeredSliderCtrl::IsAutoRepeatMode (int& /*nDelay*/) const
{
	ASSERT_VALID (this);
	return m_nPressed == nZoomInIndex || m_nPressed == nZoomOutIndex;
}
//***************************************************************************
BOOL MLayeredSliderCtrl::OnAutoRepeat ()
{
	ASSERT_VALID (this);

	if (m_bIsDisabled)
	{
		return FALSE;
	}

	if (m_nPressed == nZoomInIndex)
	{
		SetPos (m_nPos + m_nPageSize);
	}
	else if (m_nPressed == nZoomOutIndex)
	{
		SetPos (m_nPos - m_nPageSize);		
	}

	return TRUE;
}

//********************************************************************************
BOOL MLayeredSliderCtrl::OnProcessKey (UINT nChar)
{
	ASSERT_VALID (this);

	const int nPrevPos = m_nPos;
	int nPos = m_nPos;

	switch (nChar)
	{
	case VK_LEFT:
		if (!IsVert ())
		{
			nPos--;
		}
		else
		{
			return FALSE;
		}
		break;

	case VK_UP:
		if (IsVert ())
		{
			nPos++;
		}
		else
		{
			return FALSE;
		}
		break;

	case VK_SUBTRACT:
		if (!m_bZoomButtons)
		{
			return FALSE;
		}

	case VK_PRIOR:
		if (IsVert ())
		{
			nPos += m_nPageSize;
		}
		else
		{
			nPos -= m_nPageSize;
		}
		break;

	case VK_ADD:
		if (!m_bZoomButtons)
		{
			return FALSE;
		}

	case VK_NEXT:
		if (IsVert ())
		{
			nPos -= m_nPageSize;
		}
		else
		{
			nPos += m_nPageSize;
		}
		break;

	case VK_RIGHT:
		if (!IsVert ())
		{
			nPos++;
		}
		else
		{
			return FALSE;
		}
		break;

	case VK_DOWN:
		if (IsVert ())
		{
			nPos--;
		}
		else
		{
			return FALSE;
		}
		break;

	case VK_HOME:
		nPos = IsVert () ? m_nMax : m_nMin;
		break;

	case VK_END:
		nPos = IsVert () ? m_nMin : m_nMax;
		break;

	default:
		return FALSE;
	}

	nPos = min (max (m_nMin, nPos), m_nMax);

	if (nPrevPos != nPos)
	{
		SetPos (nPos);		
	}

	return TRUE;
}