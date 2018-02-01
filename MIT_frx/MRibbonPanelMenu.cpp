#include "StdAfx.h"
#include "MRibbonPanelMenu.h"

#include "MVisualManager.h"

using namespace mit;
using namespace mit::frx;

class MRibbonPanel : public CBCGPRibbonPanel
{
	friend class MRibbonPanelMenu;
};

class MBaseRibbonElement : public CBCGPBaseRibbonElement
{
	friend class MRibbonPanelMenu;
};

class MToolbarMenuButton : public CBCGPToolbarMenuButton
{
	friend class MRibbonPanelMenu;
};

namespace mit
{
	namespace frx
	{
		class MRibbonPanelMenuBar : public CBCGPRibbonPanelMenuBar
		{
			friend class MRibbonPanelMenu;
		};
	}
}

IMPLEMENT_DYNCREATE(MRibbonPanelMenu, CBCGPRibbonPanelMenu);

static const int iFadeStep = 10;
static const int iAnimTimerId = 1;
static const int iScrollTimerId = 2;
static const int iScrollTimerDuration = 80;
static const int iMenuBarId = 1;
static const int iTearOffBarHeight = 10;
static const int iResizeBarBarHeightRight = 12;
static const int iResizeBarBarHeight = 9;
static const int nScrollBarID = 1;

//****************************************************************************************
void MRibbonPanelMenu::RecalcLayout (BOOL bNotify) 
{
	if (!CBCGPVisualManager::GetInstance()->IsKindOf(RUNTIME_CLASS(MVisualManager)))
	{
		CBCGPRibbonPanelMenu::RecalcLayout(bNotify);
		return;
	}

	//MVisualManager* pVM = (MVisualManager*)CBCGPVisualManager::GetInstance();

	MBaseRibbonElement* pParentRibbonElement = (MBaseRibbonElement*)m_pParentRibbonElement; // cppcheck - 사용안됨
	MToolbarMenuButton* pParentBtn = (MToolbarMenuButton*)m_pParentBtn;
#ifdef _DEBUG
	if (pParentBtn != NULL)
	{
		ASSERT_VALID (pParentBtn);
		ASSERT (pParentBtn->m_pPopupMenu == this);
	}

#ifndef BCGP_EXCLUDE_RIBBON
	if (pParentRibbonElement != NULL)
	{
		ASSERT_VALID (pParentRibbonElement);
		ASSERT (pParentRibbonElement->m_pPopupMenu == this);
	}
#endif
#endif // _DEBUG

	// jpahn: 타입검사
	CBCGPPopupMenuBar* pBCGMenuBar = GetMenuBar ();
	ASSERT(pBCGMenuBar->IsKindOf(RUNTIME_CLASS(CBCGPRibbonPanelMenuBar)));
	MRibbonPanelMenuBar* pMenuBar = (MRibbonPanelMenuBar*)pBCGMenuBar;
	
	ASSERT_VALID (pMenuBar);

	if (!::IsWindow (m_hWnd) ||
		pMenuBar == NULL ||
		!::IsWindow (pMenuBar->m_hWnd))
	{
		return;
	}

	if (pMenuBar->m_bInUpdateShadow)
	{
		return;
	}

	//-------------------------
	// Set tear-off attributes:
	//-------------------------
	BOOL bIsTearOff = (pParentBtn != NULL && pParentBtn->IsTearOffMenu () &&
		!CBCGPToolBar::IsCustomizeMode ());

	CRect rectScreen;

	MONITORINFO mi;
	mi.cbSize = sizeof (MONITORINFO);
	if (GetMonitorInfo (MonitorFromPoint (m_ptLocation, MONITOR_DEFAULTTONEAREST),
		&mi))
	{
		rectScreen = mi.rcWork;
	}
	else
	{
		::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);
	}

	// jpahn: Border 는 0. 이딴거 계산 안해
	const int nBorderSize = 0; //GetBorderSize ();
	const BOOL bRTL = GetExStyle() & WS_EX_LAYOUTRTL;

	if (m_bResizeTracking)
	{
		if (bRTL)
		{
			m_sizeCurrent.cx = min (
				m_sizeCurrent.cx, 
				m_ptLocation.x - rectScreen.left - 2 * nBorderSize);
		}
		else
		{
			m_sizeCurrent.cx = min (
				m_sizeCurrent.cx, 
				rectScreen.right - m_ptLocation.x - 2 * nBorderSize);
		}

		m_sizeCurrent.cy = min (
			m_sizeCurrent.cy, 
			rectScreen.bottom - m_ptLocation.y - 2 * nBorderSize - m_rectResize.Height ());
	}

	//---------------------------------------
	// Normalize location in the screen area:
	//---------------------------------------
	m_ptLocation.x = max (rectScreen.left, min (m_ptLocation.x, rectScreen.right));

	if (pParentBtn == NULL)
	{
		m_ptLocation.y = max (rectScreen.top, min (m_ptLocation.y, rectScreen.bottom));
	}

	CSize size = m_sizeCurrent;

	if (!m_bResizeTracking && !m_bWasResized)
	{
		// jpahn: m_wndRibbonBar 를 멤버로 가지고 있어서
		// CBCGPRibbonPanelMenuBar 서브 클래싱이 힘들다
		// friend class 지정해서 함수에서 대신 처리
		size = CalcSize(pMenuBar, TRUE);
	}

	BOOL bScrollSizeAdded = FALSE;
	if (!m_bResizeTracking && !m_bWasResized)
	{
		size.cx += nBorderSize * 2;
		size.cy += nBorderSize * 2;

		if (m_bScrollable && m_bShowScrollBar)
		{
			size.cx += ::GetSystemMetrics (SM_CXVSCROLL);

			if (!m_rectResize.IsRectEmpty ())
			{
				m_rectResize.right += ::GetSystemMetrics (SM_CXVSCROLL);
			}

			bScrollSizeAdded = TRUE;
		}

		switch (m_nLogoLocation)
		{
		case MENU_LOGO_LEFT:
		case MENU_LOGO_RIGHT:
			size.cx += m_iLogoWidth;
			break;

		case MENU_LOGO_TOP:
		case MENU_LOGO_BOTTOM:
			size.cy += m_iLogoWidth;
			break;
		}
	}

	if (m_pMenuCustomizationPage != NULL)
	{
		size.cy += ::GetSystemMetrics (SM_CYSMCAPTION);
		size.cy += 2 * ::GetSystemMetrics (SM_CYBORDER) + 5;
	}
	else if (bIsTearOff)
	{
		m_rectTearOffCaption = CRect (CPoint (nBorderSize, nBorderSize), 
			CSize (size.cx - 2 * nBorderSize, iTearOffBarHeight));
		size.cy += iTearOffBarHeight;

		if (!CBCGPToolBar::IsCustomizeMode () && m_wndToolTip.GetSafeHwnd () == NULL)
		{
			ASSERT(0);
			//CBCGPLocalResource locaRes;

			m_wndToolTip.Create (this);
			m_wndToolTip.Activate (TRUE);
			if (globalData.m_nMaxToolTipWidth != -1)
			{
				m_wndToolTip.SetMaxTipWidth(globalData.m_nMaxToolTipWidth);
			}

			m_wndToolTip.AddTool (this, IDS_TEAR_OFF, m_rectTearOffCaption, 1);
		}
	}

	if (m_nMaxHeight != -1 && size.cy > m_nMaxHeight)
	{
		if (!m_bResizeTracking && !m_bWasResized)
		{
			int nMaxHeight = m_nMaxHeight - nBorderSize * 2;

			size.cy = nMaxHeight - (nMaxHeight % pMenuBar->GetRowHeight ()) + nBorderSize * 2 + 2;
			m_bHasBeenResized = TRUE;
		}

		m_bScrollable = TRUE;
	}

	if (m_bIsResizable)
	{
		const int nResizeBarHeight = 
			m_sizeMinResize.cx > 0 ? iResizeBarBarHeightRight : iResizeBarBarHeight;

		if (m_bIsResizeBarOnTop)
		{
			m_rectResize = CRect (CPoint (nBorderSize, nBorderSize),
				CSize (size.cx - 2 * nBorderSize, nResizeBarHeight));
		}
		else
		{
			m_rectResize = CRect (CPoint (nBorderSize, size.cy - nBorderSize),
				CSize (size.cx - 2 * nBorderSize, nResizeBarHeight));
		}

		size.cy += nResizeBarHeight;
	}

	BOOL bIsRightAlign = bRTL || m_bRightAlign;

	CBCGPMenuBar* pParentMenuBar = pParentBtn == NULL ? NULL :
		DYNAMIC_DOWNCAST (CBCGPMenuBar, pParentBtn->m_pWndParent);

	if (pParentMenuBar != NULL && pParentMenuBar->IsFloating ())
	{
		// When the popup menu is dropped-down from the floating menu bar,
		// it should not cover other menu bar items. Ask parent menu bar about
		// right popup menu location:
		DROP_DIRECTION direction = (DROP_DIRECTION) 
			pParentMenuBar->GetFloatPopupDirection (pParentBtn);

		switch (direction)
		{
		case DROP_DIRECTION_TOP:
			m_ptLocation.y = m_ptLocationInitial.y - size.cy - pParentBtn->Rect ().Height () + 1;
			m_DropDirection = direction;
			break;

		case DROP_DIRECTION_LEFT:
			m_ptLocation.y = m_ptLocationInitial.y - pParentBtn->Rect ().Height () + 1;
			m_DropDirection = direction;

			if (bRTL)
			{
				m_ptLocation.x = m_ptLocationInitial.x + size.cx;

				if (m_ptLocation.x > rectScreen.right)
				{
					m_ptLocation.x = rectScreen.right;
					m_DropDirection = DROP_DIRECTION_NONE;
				}
			}
			else
			{
				m_ptLocation.x = m_ptLocationInitial.x - size.cx;

				if (m_ptLocation.x < rectScreen.left)
				{
					m_ptLocation.x = rectScreen.left;
					m_DropDirection = DROP_DIRECTION_NONE;
				}
			}
			break;

		case DROP_DIRECTION_RIGHT:
			if (bRTL)
			{
				m_ptLocation.x = m_ptLocationInitial.x - pParentBtn->Rect ().Width ();
			}
			else
			{
				m_ptLocation.x = m_ptLocationInitial.x + pParentBtn->Rect ().Width ();
			}

			m_ptLocation.y = m_ptLocationInitial.y - pParentBtn->Rect ().Height () + 1;
			m_DropDirection = direction;
			break;
		}
	}

	//---------------------------------
	// Prepare Quick Customize Drawing 
	//----------------------------------
	CRect rectQCParent;
	rectQCParent.SetRectEmpty ();

	BOOL bConnectQCToParent = FALSE;

	if (CBCGPVisualManager::GetInstance ()->IsOfficeXPStyleMenus ())
	{
		CBCGPPopupMenu* pParentPopup = GetParentPopupMenu();

		if (pParentPopup != NULL)
		{
			CBCGPToolbarMenuButton* pParentBtn = GetParentButton ();
			if ((pParentBtn != NULL) && (pParentBtn->IsQuickMode()))
			{
				if (!bRTL)
				{
					pParentPopup->RedrawWindow();
				}

				if (pParentPopup->IsQuickCustomize ())
				{
					if (!m_bQuickCusomize)
					{
						rectQCParent = pParentBtn->Rect ();
						CWnd* pParentWnd = pParentBtn->GetParentWnd ();

						if (pParentWnd->GetSafeHwnd () != NULL)
						{
							pParentWnd->ClientToScreen (&rectQCParent);

							m_ptLocation.y = rectQCParent.top;
							bConnectQCToParent = TRUE;

							if (m_DropDirection == DROP_DIRECTION_LEFT)
							{
								m_ptLocation.x = 
									bRTL ?
									rectQCParent.left :
								rectQCParent.left - size.cx;
							}
							else
							{
								m_ptLocation.x = 
									bRTL ?
									rectQCParent.right + size.cx :
								rectQCParent.right;
							}
						}
					}
				}
			}
		}
	}

	//---------------------------------------------
	// Adjust the menu position by the screen size:
	//---------------------------------------------
	if ((bRTL && (m_ptLocation.x - size.cx < rectScreen.left)) || 
		(!bIsRightAlign && (m_ptLocation.x + size.cx > rectScreen.right)))
	{
		//-----------------------------------------------------
		// Menu can't be overlapped with the parent popup menu!
		//-----------------------------------------------------
		CBCGPPopupMenu* pParentMenu = GetParentPopupMenu ();

		if (pParentMenu != NULL)
		{
			CRect rectParent;
			pParentMenu->GetWindowRect (rectParent);

			m_ptLocation.x = bRTL ? rectParent.right + size.cx : rectParent.left - size.cx;

#ifndef BCGP_EXCLUDE_RIBBON
			if (pParentRibbonElement != NULL)
			{
				ASSERT_VALID (pParentRibbonElement);

				if (!pParentRibbonElement->IsMenuMode ())
				{
					rectParent = pParentRibbonElement->GetRect ();
					pParentMenu->ClientToScreen (&rectParent);

					m_ptLocation.x = bRTL ? rectParent.left + size.cx : rectParent.right - size.cx;
				}
			}

#endif // BCGP_EXCLUDE_RIBBON

			m_DropDirection = bRTL ? DROP_DIRECTION_RIGHT : DROP_DIRECTION_LEFT;
		}
		else if (pParentMenuBar != NULL && 
			(pParentMenuBar->IsHorizontal ()) == 0)
		{
			//------------------------------------------------
			// Parent menu bar is docked vertical, place menu 
			// in the left or right side of the parent frame:
			//------------------------------------------------
			CRect rectParentBtn = pParentBtn->Rect();
			pParentMenuBar->ClientToScreen(&rectParentBtn);

			m_ptLocation.x = bRTL ? rectParentBtn.right + size.cx : rectParentBtn.left - size.cx;

			if (m_ptLocation.x + size.cx >= rectScreen.right)
			{
				m_ptLocation.x = rectScreen.right - size.cx - 1;
			}

			m_DropDirection = DROP_DIRECTION_LEFT;
		}
		else
		{
			m_ptLocation.x = bRTL ? rectScreen.left + size.cx + 1 : m_bRightAlign ? rectScreen.left + 1 : rectScreen.right - size.cx - 1;
			m_DropDirection = DROP_DIRECTION_NONE;
		}

		if (!bRTL && (m_ptLocation.x < rectScreen.left))
		{
			m_ptLocation.x = rectScreen.left;
			m_DropDirection = DROP_DIRECTION_NONE;
		}

		if (bRTL && (m_ptLocation.x > rectScreen.right))
		{
			m_ptLocation.x = rectScreen.right;
			m_DropDirection = DROP_DIRECTION_NONE;
		}

		if (!m_bDisableAnimation)
		{
			if (GetAnimationType () == UNFOLD)
			{
				m_bIsAnimRight = FALSE;
			}
			else if (GetAnimationType () == FADE)
			{
				m_bIsAnimRight = FALSE;
				m_bIsAnimDown = FALSE;
			}
		}
	}

	if (m_ptLocation.y + size.cy > rectScreen.bottom)
	{
		const int nResizeBarHeight = m_rectResize.Height ();

		if (m_bIsResizable)
		{
			m_rectResize = CRect (CPoint (nBorderSize, nBorderSize),
				CSize (size.cx - 2 * nBorderSize, nResizeBarHeight));

			m_bIsResizeBarOnTop = TRUE;
		}

		m_bIsAnimDown = FALSE;

		CRect rectParentBtn;
		CWnd* pWndParent = GetParentArea (rectParentBtn);

		if (pWndParent != NULL && 
			m_DropDirection != DROP_DIRECTION_LEFT && m_DropDirection != DROP_DIRECTION_RIGHT)
		{
			CPoint ptRight (rectParentBtn.right, 0);
			pWndParent->ClientToScreen (&ptRight);

			CPoint ptTop (0, rectParentBtn.top - size.cy);
			pWndParent->ClientToScreen (&ptTop);

			if (ptTop.y < 0)
			{
				int yParentButtonTop = ptTop.y + size.cy;

				//-----------------------------------------------------
				// Where more space: on top or on bottom of the button?
				//-----------------------------------------------------
				if (rectScreen.bottom - yParentButtonTop < 
					yParentButtonTop - rectScreen.top)
				{
					m_ptLocation.y = rectScreen.top;
					m_DropDirection = DROP_DIRECTION_NONE;
					size.cy += ptTop.y;
				}
				else
				{
					size.cy = rectScreen.bottom - m_ptLocation.y;
					m_bIsAnimDown = TRUE;

					if (m_bIsResizable)
					{
						//-----------------------------------
						// Restore resize box back to bottom:
						//-----------------------------------
						m_bIsResizeBarOnTop = FALSE;
						m_rectResize = CRect (CPoint (nBorderSize, size.cy - nBorderSize - nResizeBarHeight),
							CSize (size.cx - 2 * nBorderSize, nResizeBarHeight));
					}
				}

				m_bHasBeenResized = TRUE;
				m_bScrollable = TRUE;
			}
			else
			{
				m_ptLocation.y = ptTop.y;

				m_DropDirection = 
					(pParentMenuBar != NULL && pParentMenuBar->IsHorizontal ()) ?
DROP_DIRECTION_TOP : DROP_DIRECTION_NONE;
			}
		}
		else
		{
			if (bConnectQCToParent)
			{
				m_ptLocation.y = rectQCParent.bottom - size.cy - 1;
			}
			else
			{
				m_ptLocation.y -= size.cy;

				if (GetParentPopupMenu () != NULL)
				{
					m_ptLocation.y += pMenuBar->GetRowHeight () + nBorderSize * 2;
				}
			}
		}

		if (m_ptLocation.y < rectScreen.top)
		{
			m_ptLocation.y = rectScreen.top;
			m_DropDirection = DROP_DIRECTION_NONE;
		}

		if (m_ptLocation.y + size.cy > rectScreen.bottom)
		{
			size.cy = rectScreen.bottom - m_ptLocation.y;
			m_bHasBeenResized = TRUE;
			m_bScrollable = TRUE;
		}
	}

	if (m_ptLocation.y < rectScreen.top)
	{
		if (pParentBtn != NULL && pParentBtn->GetParentWnd () != NULL &&
			GetParentPopupMenu () == NULL)
		{
			CPoint ptRight (pParentBtn->Rect ().right, 0);
			pParentBtn->GetParentWnd ()->ClientToScreen (&ptRight);

			CPoint ptBottom (0, pParentBtn->Rect ().bottom);
			pParentBtn->GetParentWnd ()->ClientToScreen (&ptBottom);

			m_ptLocation.y = ptBottom.y;

			m_DropDirection = 
				(pParentMenuBar != NULL && pParentMenuBar->IsHorizontal ()) ?
DROP_DIRECTION_BOTTOM : DROP_DIRECTION_NONE;
		}
		else
		{
			m_ptLocation.y = rectScreen.top;
		}

		if (m_ptLocation.y + size.cy > rectScreen.bottom)
		{
			m_ptLocation.y = rectScreen.top;

			if (size.cy > rectScreen.Height ())
			{
				size.cy = rectScreen.Height ();
				m_bHasBeenResized = TRUE;
				m_bScrollable = TRUE;
			}

			m_DropDirection = DROP_DIRECTION_NONE;
		}
	}

	if (!bScrollSizeAdded && m_bScrollable && m_bShowScrollBar && !m_bResizeTracking && !m_bWasResized)
	{
		size.cx += ::GetSystemMetrics (SM_CXVSCROLL);

		if (!m_rectResize.IsRectEmpty ())
		{
			m_rectResize.right += ::GetSystemMetrics (SM_CXVSCROLL);
		}
	}

	m_FinalSize = size;

	if (GetAnimationType () != NO_ANIMATION || m_bAnimationIsDone || 
		CBCGPToolBar::IsCustomizeMode ())
	{
		if (!CBCGPToolBar::IsCustomizeMode ())
		{
			size.cx += m_iShadowSize;
			size.cy += m_iShadowSize;
		}

		if (m_pMenuCustomizationPage != NULL)
		{
			SetWindowPos (NULL, -1, -1, size.cx, size.cy,
				SWP_NOMOVE | SWP_NOZORDER |
				SWP_NOACTIVATE);
		}
		else
		{
			SetWindowPos (NULL, m_ptLocation.x - (bRTL ? size.cx : 0), m_ptLocation.y, size.cx, size.cy,
				SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}

	if (CBCGPToolBar::IsCustomizeMode ())
	{
		pMenuBar->AdjustLocations ();
	}

	//---------------------------------------------------
	// Parent button maybe covered by shadow, repaint it:
	//---------------------------------------------------
	if (m_iShadowSize != 0 &&
		!CBCGPToolBar::IsCustomizeMode () &&
		pParentBtn != NULL &&
		pParentBtn->GetParentWnd () != NULL)
	{
		BOOL bOldShown = m_bShown;
		m_bShown = TRUE;

		CWnd* pWndParent = pParentBtn->GetParentWnd ();

		CRect rectInter;

		CRect rectMenu;
		GetWindowRect (rectMenu);

		CRect rectShadowRight (CPoint (bRTL ? rectMenu.left - 1 - m_iShadowSize : rectMenu.right + 1, rectMenu.top), 
			CSize (m_iShadowSize, rectMenu.Height () + m_iShadowSize));
		pWndParent->ScreenToClient (&rectShadowRight);

		if (rectInter.IntersectRect (rectShadowRight, pParentBtn->m_rect))
		{
			pWndParent->InvalidateRect (pParentBtn->m_rect);
			pWndParent->UpdateWindow ();
		}

		CRect rectShadowBottom (CPoint (rectMenu.left, rectMenu.bottom + 1),
			CSize (rectMenu.Width () + m_iShadowSize, m_iShadowSize));
		pWndParent->ScreenToClient (&rectShadowBottom);

		if (rectInter.IntersectRect (rectShadowBottom, pParentBtn->m_rect))
		{
			pWndParent->InvalidateRect (pParentBtn->m_rect);
			pWndParent->UpdateWindow ();
		}

		m_bShown = bOldShown;
	}

	if (m_bScrollable && m_bShowScrollBar && !m_bResizeTracking && !m_bWasResized)
	{
		RedrawWindow ();
	}
}

CSize MRibbonPanelMenu::CalcSize(MRibbonPanelMenuBar* pMenuBar, BOOL bVertDock)
{
	ASSERT_VALID (pMenuBar);

	MRibbonPanel* pPanel = (MRibbonPanel*)pMenuBar->m_pPanel;
	CBCGPRibbonCategory* pCategory = pMenuBar->m_pCategory;
	CBCGPRibbonBar* pRibbonBar = pMenuBar->m_pRibbonBar;

	const BOOL& bSimpleMode = pMenuBar->m_bSimpleMode;
	const BOOL& bIsMenuMode = pMenuBar->m_bIsMenuMode;
	const BOOL& bIsDefaultMenuLook = pMenuBar->m_bIsDefaultMenuLook;
	const CSize& sizePrefered = pMenuBar->m_sizePrefered;
	const CSize& sizeCategory = pMenuBar->m_sizeCategory;
	const BOOL& bIsQATPopup = pMenuBar->m_bIsQATPopup;
	const BOOL& bIsOneRowFloaty = pMenuBar->m_bIsOneRowFloaty;

	if (pCategory != NULL)
	{
		ASSERT_VALID (pCategory);
		ASSERT (sizeCategory != CSize (0, 0));

		return sizeCategory;
	}

	ASSERT_VALID (pRibbonBar);
	ASSERT_VALID (pPanel);

	pPanel->m_bIsQATPopup = bIsQATPopup;

	CClientDC dc (pRibbonBar);

	CFont* pOldFont = dc.SelectObject (pRibbonBar->GetFont ());
	ASSERT (pOldFont != NULL);

	if (bIsMenuMode)
	{
		pPanel->m_bMenuMode = TRUE;
		pPanel->m_bIsDefaultMenuLook = bIsDefaultMenuLook;

		pPanel->Repos (&dc, CRect (0, 0, sizePrefered.cx, sizePrefered.cy));

		dc.SelectObject (pOldFont);

		CSize size = pPanel->m_rect.Size ();

		if (sizePrefered != CSize (0, 0))
		{
			size.cx = max (sizePrefered.cx, size.cx);

			if (sizePrefered.cy <= 0)
			{
				size.cy = pPanel->m_rect.Size ().cy;
			}
			else
			{
				if (pPanel->m_pPaletteButton != NULL)
				{
					size.cy = max (size.cy, sizePrefered.cy);
				}
				else
				{
					if (size.cy > sizePrefered.cy)
					{
						CBCGPPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPPopupMenu, pMenuBar->GetParent ());
						if (pParentMenu != NULL)
						{
							ASSERT(pParentMenu->IsKindOf(RUNTIME_CLASS(MRibbonPanelMenu)));
							((MRibbonPanelMenu*)pParentMenu)->m_bScrollable = TRUE;
						}
					}

					size.cy = sizePrefered.cy;
				}
			}
		}

		return size;
	}

	if (bSimpleMode && pPanel->m_arWidths.GetSize () == 0)
	{
		CWaitCursor wait;
		pPanel->RecalcWidths (&dc, 32767);
	}

	const int nWidthSize = (int) pPanel->m_arWidths.GetSize ();
	if (nWidthSize == 0)
	{
		dc.SelectObject (pOldFont);
		return CSize (10, 10);
	}

	if (pPanel->m_bAlignByColumn && !pPanel->m_bFloatyMode && !pPanel->IsFixedSize ())
	{
		int nCategoryHeight = pRibbonBar->GetCategoryHeight ();
		if (nCategoryHeight <= 0)
		{
			nCategoryHeight = pPanel->GetHeight (&dc) + pPanel->GetCaptionSize (&dc).cy;
		}

		const int nHeight = nCategoryHeight - 2 * pPanel->m_nYMargin;
		pPanel->Repos (&dc, CRect (0, 0, 32767, nHeight));
	}
	else if (bIsQATPopup)
	{
		int nWidth = pPanel->m_arWidths [0] + 2 * pPanel->m_nXMargin;
		pPanel->Repos (&dc, CRect (0, 0, nWidth, 32767));
	}
	else
	{
		int nWidth = 0;
		int nHeight = 0;

		if (!pPanel->m_bFloatyMode)
		{
			nWidth = pPanel->m_arWidths [0] + 4 * pPanel->m_nXMargin;

			int nCategoryHeight = pRibbonBar->GetCategoryHeight ();
			if (nCategoryHeight <= 0)
			{
				nCategoryHeight = pPanel->GetHeight (&dc) + pPanel->GetCaptionSize (&dc).cy;
			}

			nHeight = nCategoryHeight - 2 * pPanel->m_nYMargin;
		}
		else
		{
			nWidth = pPanel->m_arWidths [nWidthSize > 2 && !bIsOneRowFloaty ? 1 : 0] + 4 * pPanel->m_nXMargin;
			nHeight = 32767;
		}

		pPanel->Repos (&dc, CRect (0, 0, nWidth, nHeight));
	}

	CSize size = pPanel->m_rect.Size ();
	dc.SelectObject (pOldFont);

	if (bSimpleMode && pPanel->GetCount () > 0 && !bIsQATPopup)
	{
		int xMin = 32767;
		int xMax = 0;

		int yMin = 32767;
		int yMax = 0;

		for (int i = 0; i < pPanel->GetCount (); i++)
		{
			CBCGPBaseRibbonElement* pButton = pPanel->GetElement (i);
			ASSERT_VALID (pButton);

			CRect rectButton = pButton->GetRect ();

			xMin = min (xMin, rectButton.left);
			yMin = min (yMin, rectButton.top);

			xMax = max (xMax, rectButton.right);
			yMax = max (yMax, rectButton.bottom);
		}

		return CSize (
			xMax - xMin + 2 * pPanel->m_nXMargin, 
			yMax - yMin + 2 * pPanel->m_nYMargin);
	}

	return size;
}
