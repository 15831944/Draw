#include "stdafx.h"
#include "MLayeredTabWnd.h"
#include "MLayeredDockingControlBar.h"
#include "MLayeredTabbedControlBar.h"
#include "MLayeredMiniFrameWnd.h"
#include "MLayeredMultiMiniFrameWnd.h"
#include "MVisualManager.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNCREATE(MLayeredTabWnd, CBCGPTabWnd)
MLayeredTabWnd::MLayeredTabWnd(void)
{
	m_bTrack = FALSE;
}

MLayeredTabWnd::~MLayeredTabWnd(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredTabWnd, CBCGPTabWnd)
	//{{AFX_MSG_MAP(MLayeredTabWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//***************************************************************************************
void MLayeredTabWnd::AdjustTabs()
{
	CBCGPTabWnd::AdjustTabs();
}

//*************************************************************************************
void MLayeredTabWnd::RecalcLayout()
{
	CBCGPTabWnd::RecalcLayout();
}

//***************************************************************************************
void MLayeredTabWnd::OnDraw(CDC* pDC)
{
	if ( !CBCGPVisualManager::GetInstance()->IsKindOf(RUNTIME_CLASS(MVisualManager)))
	{
		CBCGPTabWnd::OnDraw(pDC);
		return;
	}

	ASSERT_VALID(pDC);

	COLORREF	clrDark;
	COLORREF	clrBlack;
	COLORREF	clrHighlight;
	COLORREF	clrFace;
	COLORREF	clrDarkShadow;
	COLORREF	clrLight;
	CBrush*		pbrFace = NULL;
	CBrush*		pbrBlack = NULL;
				   
	CBCGPVisualManager::GetInstance ()->GetTabFrameColors (
		this, clrDark, clrBlack, clrHighlight, clrFace, clrDarkShadow, clrLight,
		pbrFace, pbrBlack);

	ASSERT_VALID (pbrFace);
	ASSERT_VALID (pbrBlack);

	CRect rectClient;
	GetClientRect (&rectClient);

	switch (m_ResizeMode)
	{
	case RESIZE_VERT:
		rectClient.right -= m_rectResize.Width ();
		break;

	case RESIZE_HORIZ:
		rectClient.bottom -= m_rectResize.Height ();
		break;
	}

	CBrush* pOldBrush = pDC->SelectObject (pbrFace);
	ASSERT (pOldBrush != NULL);

	CPen penDark (PS_SOLID, 1, clrDark);
	CPen penBlack (PS_SOLID, 1, clrBlack);
	CPen penHiLight (PS_SOLID, 1, clrHighlight);

	CPen* pOldPen = (CPen*) pDC->SelectObject (&penDark);
	ASSERT(pOldPen != NULL);

	const int nTabBorderSize = GetTabBorderSize ();

	CRect rectTabs = rectClient;

	if (m_location == LOCATION_BOTTOM)
	{
		rectTabs.top = m_rectTabsArea.top;
	}
	else
	{
		rectTabs.bottom = m_rectTabsArea.bottom;
	}
	
	pDC->ExcludeClipRect (m_rectWndArea);

	// jpahn : frame rect 미리 계산해서 EraseTabsFrame 에서 그린다.
	CRect rectFrame = rectClient;
	if (m_location == LOCATION_BOTTOM)
	{
		rectFrame.bottom = m_rectTabsArea.top + 1;
	}
	else
	{
		rectFrame.top = m_rectTabsArea.bottom - 1;
	}

	BOOL bBackgroundIsReady =
		CBCGPVisualManager::GetInstance ()->OnEraseTabsFrame (pDC, rectFrame, this);

	if (!m_bDrawFrame && !bBackgroundIsReady)
	{
		pDC->FillRect (rectClient, pbrFace);
	}

	CBCGPVisualManager::GetInstance ()->OnEraseTabsArea (pDC, rectTabs, this);

	// jpahn : 여기서 frame 따위 그리지 않는다.(OnEraseTabsFrame 에서 미리 그렸음)
	// 관련 코드 통째로 날림
	// Top Edge인가 뭐 그 딴거도 그리지 않는다.

	CFont* pOldFont = pDC->SelectObject (m_bFlat ?	&m_fntTabs : 
													&globalData.fontRegular);
	ASSERT(pOldFont != NULL);

	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (globalData.clrBtnText);

	if (m_rectTabsArea.Width () > 5 && m_rectTabsArea.Height () > 5)
	{
		//-----------
		// Draw tabs:
		//-----------
		CRect rectClip = m_rectTabsArea;
		rectClip.InflateRect (1, nTabBorderSize);

		CRgn rgn;
		rgn.CreateRectRgnIndirect (rectClip);

		for (int nIndex = m_iTabsNum - 1; nIndex >= 0; nIndex--)
		{
			int i = nIndex;

			if (m_arTabIndexs.GetSize() == m_iTabsNum)
			{
				i = m_arTabIndexs[nIndex];
			}

			CMITTabInfo* pTab = (CMITTabInfo*) m_arTabs [i];
			ASSERT_VALID (pTab);

			if (!pTab->m_bVisible)
				continue;

			m_iCurTab = i;

			if (i != m_iActiveTab)	// Draw active tab last
			{
				pDC->SelectClipRgn (&rgn);

				if (m_bFlat)
				{
					pDC->SelectObject (&penBlack);
					DrawFlatTab (pDC, pTab, FALSE);
				}
				else
				{
					Draw3DTab (pDC, pTab, FALSE);
				}
			}
		}

		if (m_iActiveTab >= 0)
		{
			//-----------------
			// Draw active tab:
			//-----------------
			pDC->SetTextColor (globalData.clrWindowText);

			CMITTabInfo* pTabActive = (CMITTabInfo*) m_arTabs [m_iActiveTab];
			ASSERT_VALID (pTabActive);

			m_iCurTab = m_iActiveTab;

			pDC->SelectClipRgn (&rgn);

			if (m_bFlat)
			{
				if (m_brActiveTab.GetSafeHandle() == NULL)
				{
					m_brActiveTab.CreateSolidBrush (GetActiveTabColor ());
				}

				pDC->SelectObject (&m_brActiveTab);
				pDC->SelectObject (&m_fntTabsBold);
				pDC->SetTextColor (GetActiveTabTextColor ());
				pDC->SelectObject (&penBlack);

				DrawFlatTab (pDC, pTabActive, TRUE);

				//---------------------------------
				// Draw line bellow the active tab:
				//---------------------------------
				const int xLeft = max (	m_rectTabsArea.left + 1,
										pTabActive->m_rect.left + 1);

				if (pTabActive->m_rect.right > m_rectTabsArea.left + 1)
				{
					CPen penLight (PS_SOLID, 1, GetActiveTabColor ());
					pDC->SelectObject (&penLight);

					if (m_location == LOCATION_BOTTOM)
					{
						pDC->MoveTo (xLeft, pTabActive->m_rect.top);
						pDC->LineTo (pTabActive->m_rect.right, pTabActive->m_rect.top);
					}
					else
					{
						pDC->MoveTo (xLeft, pTabActive->m_rect.bottom);
						pDC->LineTo (pTabActive->m_rect.right, pTabActive->m_rect.bottom);
					}

					pDC->SelectObject (pOldPen);
				}
			}
			else
			{
				if (m_bIsActiveTabBold)
				{
					if (!IsMDITabGroup () || m_bIsActiveInMDITabGroup)
					{
						pDC->SelectObject (&globalData.fontBold);
					}
				}

				Draw3DTab (pDC, pTabActive, TRUE);
			}
		}

		pDC->SelectClipRgn (NULL);
	}

	if (!m_rectTabSplitter.IsRectEmpty ())
	{
		pDC->FillRect (m_rectTabSplitter, pbrFace);

		CRect rectTabSplitter = m_rectTabSplitter;

		pDC->Draw3dRect (rectTabSplitter, clrDarkShadow, clrDark);
		rectTabSplitter.DeflateRect (1, 1);
		pDC->Draw3dRect (rectTabSplitter, clrHighlight, clrDark);
	}
	
	if (m_bFlat && m_nTabsHorzOffset > 0)
	{
		pDC->SelectObject (&penDark);

		const int xDivider = m_rectTabsArea.left - 1;

		if (m_location == LOCATION_BOTTOM)
		{
			pDC->MoveTo (xDivider, m_rectTabsArea.top + 1);
			pDC->LineTo (xDivider, m_rectTabsArea.bottom - 2);
		}
		else
		{
			pDC->MoveTo (xDivider, m_rectTabsArea.bottom);
			pDC->LineTo (xDivider, m_rectTabsArea.top + 2);
		}
	}

	if (!m_rectResize.IsRectEmpty ())
	{
		CBCGPVisualManager::GetInstance ()->OnDrawTabResizeBar (pDC, this, 
			m_ResizeMode == RESIZE_VERT, m_rectResize,
			pbrFace, &penDark);
	}

	pDC->SelectObject (pOldFont);
	pDC->SelectObject (pOldBrush);
	pDC->SelectObject (pOldPen);
}

void MLayeredTabWnd::OnMouseMove(UINT nFlags, CPoint point)
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
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredTabbedControlBar)) )
		{
			CWnd* pWnd = pParent->GetParent();

			if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
			{
				MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pWnd;

				pDockWnd->UpdateFrame(TRUE);
			}
			else if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredMiniFrameWnd)) )
			{
				MLayeredMiniFrameWnd* pDockWnd = (MLayeredMiniFrameWnd*)pWnd;	
				pDockWnd->UpdateTransParent(TRUE);
			}
			else if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredMultiMiniFrameWnd)) )
			{
				MLayeredMultiMiniFrameWnd* pDockWnd = (MLayeredMultiMiniFrameWnd*)pWnd;	
				pDockWnd->UpdateTransParent(TRUE);
			}
		}
	}

	CBCGPTabWnd::OnMouseMove(nFlags, point);
}

//***************************************************************************************
void MLayeredTabWnd::Draw3DTab(CDC* pDC, CBCGPTabInfo* pTab, BOOL bActive)
{
	ASSERT_VALID (pTab);
	ASSERT_VALID (pDC);

  CMITTabInfo* pMitTabInfo = (CMITTabInfo*)pTab;

	if ((m_bIsOneNoteStyle || m_bIsVS2005Style || m_bLeftRightRounded)
		&& pMitTabInfo->m_rect.left < m_rectTabsArea.left)
	{
		return;
	}

	if (pMitTabInfo->m_bVisible)
  {
    // jpahn : 겹치는 부분이 다시 그려지게 하기 위해 무조건 그림     
    CBCGPVisualManager::GetInstance ()->OnDrawTab(
      pDC, pMitTabInfo->m_rect, m_iCurTab, bActive, this);
	}
}

void MLayeredTabWnd::OnMouseLeave()
{
	m_bTrack = FALSE;

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredTabbedControlBar)) )
		{
			CWnd* pWnd = pParent->GetParent();

			if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
			{
				MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pWnd;

				pDockWnd->UpdateFrame(FALSE);
			}
			else if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredMiniFrameWnd)) )
			{
				MLayeredMiniFrameWnd* pDockWnd = (MLayeredMiniFrameWnd*)pWnd;	
				pDockWnd->UpdateTransParent(FALSE);
			}
			else if( pWnd->IsKindOf(RUNTIME_CLASS(MLayeredMultiMiniFrameWnd)) )
			{
				MLayeredMultiMiniFrameWnd* pDockWnd = (MLayeredMultiMiniFrameWnd*)pWnd;	
				pDockWnd->UpdateTransParent(FALSE);
			}
		}
	}

	CBCGPTabWnd::OnMouseLeave();
}