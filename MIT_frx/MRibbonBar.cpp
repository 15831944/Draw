#include "StdAfx.h"
#include "MRibbonBar.h"

#include "MRibbonButton.h"
#include "MRibbonButtonsGroup.h"
#include "MRibbonCaptionButton.h"
#include "MRibbonContextCaption.h"
#include "MRibbonCategory.h"
#include "MRibbonTab.h"

#include "MVisualManager.h"

static const int xTabMargin = 14;
static const int yTabMargin = 5;

static const int xMargin = 2;
static const int yMargin = 2;

using namespace mit;
using namespace mit::lib;
using namespace mit::frx;

class MCastCategory : public CBCGPRibbonCategory
{
	friend class MRibbonBar;
	friend class MRibbonTab;
};

class MCastCaptionButton : public CBCGPRibbonCaptionButton
{
	friend class MRibbonBar;
	friend class MRibbonTab;
};

class MCastMainButton : public CBCGPRibbonMainButton
{
	friend class MRibbonBar;
	friend class MRibbonTab;
};

class MCastContextCaption : public CBCGPRibbonContextCaption
{
	friend class MRibbonBar;
	friend class MRibbonTab;
};

class MCastButtonsGroup : public CBCGPRibbonButtonsGroup
{
	friend class MRibbonBar;
	friend class MRibbonTab;
};



//////////////////////////////////////////////////////////////////////////
// class MRibbonBar
MRibbonBar::MRibbonBar()
{
	m_pTitleBarMenu = NULL;	
}

MRibbonBar::~MRibbonBar()
{
	m_pTitleBarMenu = NULL;	
}

BEGIN_MESSAGE_MAP(MRibbonBar, CBCGPRibbonBar)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MRibbonBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CBCGPRibbonBar::OnUpdateCmdUI( pTarget, bDisableIfNoHndler );

// 	if( m_pTitleBarMenu )
// 		m_pTitleBarMenu->OnUpdateCmdUI( &state, pTarget, bDisableIfNoHndler);
}

CBCGPBaseRibbonElement* MRibbonBar::HitTest(CPoint point, BOOL bCheckActiveCategory, BOOL bCheckPanelCaption)
{
	CBCGPBaseRibbonElement* pElem = CBCGPRibbonBar::HitTest( point, bCheckActiveCategory, bCheckPanelCaption );

	if( !pElem && m_pTitleBarMenu )
	{
		pElem = m_pTitleBarMenu->HitTest(point);
		if (pElem != NULL)
		{
			ASSERT_VALID(pElem);
			return pElem;
		}
	}

	return pElem;
}

// void MRibbonBar::RecalcLayout()
// {
// 	LockWindowUpdate();
// 
// 	CBCGPRibbonBar::RecalcLayout();
// 
// 	BOOL bFirst = FALSE;
// 	int nCategoryRectWidth=0;
// 	CRect rect, RibbonRect;
// 	rect.SetRectEmpty();
// 	RibbonRect.SetRectEmpty();
// 
// 	CClientDC dc(this);
// 	GetClientRect(RibbonRect);
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	int nTitlebarHeight = 0;
// 	const BOOL bHideAll = m_dwHideFlags & AFX_RIBBONBAR_HIDE_ALL;
// 
// 	if( m_pTitleBarMenu )
// 	{
// 		if (bHideAll)
// 		{
// 			m_pTitleBarMenu->m_rect.SetRectEmpty();
// 		}
// 		else
// 		{
// 			CSize sizeTitleMenu = m_pTitleBarMenu->GetRegularSize(&dc);
// 
// 			m_pTitleBarMenu->m_rect = m_rectCaptionText;
// 
// 			m_rectCaptionText.right -= ( sizeTitleMenu.cx + 10 );
// 
// 			const int yOffset = max(0, (m_rectCaptionText.Height() - sizeTitleMenu.cy) / 2);
// 
// 			m_pTitleBarMenu->m_rect.top += yOffset;
// 			m_pTitleBarMenu->m_rect.bottom = m_pTitleBarMenu->m_rect.top + sizeTitleMenu.cy;
// 
// 			m_pTitleBarMenu->m_rect.left  = m_rectCaptionText.right;
// 			m_pTitleBarMenu->m_rect.right = m_pTitleBarMenu->m_rect.left + sizeTitleMenu.cx;
// 
// 			m_pTitleBarMenu->OnAfterChangeRect(&dc);
// 		}
// 	}
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	int nTabCnt = m_TabElements.GetCount();
// 
// 	//Category를 계산후에 버튼을 옴기도록 한다.
// 	int nCategoryCnt = GetVisibleCategoryCount();
// 
// 	if(nCategoryCnt > 0)
// 	{
// 		for (int i = 0; i < m_arCategories.GetSize(); i++)
// 		{
// 			CBCGPRibbonCategory* pCategory = m_arCategories [i];
// 			ASSERT_VALID(pCategory);
// 
// 			if (pCategory->IsVisible())
// 			{
// 				rect = pCategory->GetTabRect();
// 				if(!bFirst) 
// 				{
// 					bFirst = TRUE;
// 					nCategoryRectWidth += rect.left;
// 				}
// 
// 				nCategoryRectWidth += rect.Width();
// 			}
// 		}
// 
// // 		nCategoryRectWidth += 40; //간격 설정
// // 
// // 		for(int i=0; i<nTabCnt; i++) 
// // 		{
// // 			CMFCRibbonBaseElement* pWnd = m_TabElements.GetButton(i);
// // 			if(pWnd->GetID() == SC_RESTORE	|| pWnd->GetID() == SC_MINIMIZE || 
// // 			   pWnd->GetID() == SC_MAXIMIZE || pWnd->GetID() == SC_CLOSE    
// // 			   )
// // 			   continue;
// // 
// // 			CMFCRibbonComboBox* pCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pWnd);
// // 			if(pCombo)
// // 			{
// // 				rect = pCombo->GetRect();
// // 				pCombo->SetRect(CRect(nCategoryRectWidth,rect.top,nCategoryRectWidth+rect.Width(),rect.bottom));
// // 				nCategoryRectWidth += rect.Width();
// // 			}
// // 			else
// // 			{
// // 				rect = pWnd->GetRect();
// // 				pWnd->SetRect(CRect(nCategoryRectWidth,rect.top,nCategoryRectWidth+rect.Width(),rect.bottom));
// // 				nCategoryRectWidth += rect.Width();
// // 			}
// // 
// // 			pWnd->OnAfterChangeRect(&dc);
// // 		}
// 
// 		InvalidateRect(RibbonRect);
// 	}
// 
// 	UnlockWindowUpdate();
// }

void MRibbonBar::RecalcLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rect;
	GetClientRect (rect);

	if (m_bDlgBarMode)
	{
		CClientDC dc (this);

		CFont* pOldFont = dc.SelectObject (GetFont ());
		ASSERT (pOldFont != NULL);

		if (m_pActiveCategory != NULL)
		{
			ASSERT_VALID (m_pActiveCategory);

			MCastCategory* pActiveCategory = reinterpret_cast<MCastCategory*>(m_pActiveCategory);
			ASSERT(pActiveCategory);

			pActiveCategory->m_rect = rect;
			pActiveCategory->RecalcLayout (&dc);
		}

		dc.SelectObject (pOldFont);
		return;
	}

	DeactivateKeyboardFocus ();

	m_bIsTransparentCaption = FALSE;

	if (m_pPrintPreviewCategory == NULL && m_bIsPrintPreview)
	{
		AddPrintPreviewCategory ();
		ASSERT_VALID (m_pPrintPreviewCategory);
	}

	m_nTabTrancateRatio = 0;

	CBCGPControlBar::RecalcLayout ();

	m_rectBackstageTopArea.SetRectEmpty();
	m_BackStageCloseBtn.SetRect(CRect(0, 0, 0, 0));

	const BOOL bHideAll = (m_dwHideFlags & BCGPRIBBONBAR_HIDE_ALL) || (m_bBackstageViewActive && CBCGPVisualManager::GetInstance()->IsRibbonBackstageHideTabs());
	int nCategoryHeight = (m_dwHideFlags & BCGPRIBBONBAR_HIDE_ELEMENTS) || (m_bAllTabsAreInvisible && !m_bIsPrintPreview && !m_bBackstageViewActive) ? 0 : m_nCategoryHeight;

	if (m_bBackstageViewActive)
	{
		nCategoryHeight = CBCGPVisualManager::GetInstance ()->GetRibbonBackstageTopLineHeight();
	}

	const int cyFrameBorder = GetFrameHeight();

	m_bTransparentTabs = CBCGPVisualManager::GetInstance()->DoesRibbonExtendCaptionToTabsArea() && !bHideAll &&
		(!GetParent ()->IsZoomed () || globalData.bIsWindows7);

	int i = 0;

	CClientDC dc (this);

	CFont* pOldFont = dc.SelectObject (GetFont ());
	ASSERT (pOldFont != NULL);

	CString strCaption;
	GetParent ()->GetWindowText (strCaption);

	const int nCaptionTextWidth = dc.GetTextExtent (strCaption).cx;

	for (i = 0; i < m_arContextCaptions.GetSize (); i++)
	{
		ASSERT_VALID (m_arContextCaptions [i]);
		m_arContextCaptions [i]->SetRect (CRect (0, 0, 0, 0));
	}

	//-----------------------------------
	// Repos caption and caption buttons:
	//-----------------------------------
	int xSysButtonsLeft = 0;
	m_rectSysButtons.SetRectEmpty ();

	if (!m_bReplaceFrameCaption)
	{
		m_rectCaption.SetRectEmpty ();
		m_rectCaptionText.SetRectEmpty ();

		for (i = 0; i < RIBBON_CAPTION_BUTTONS; i++)
		{
			m_CaptionButtons [i].SetRect (CRect (0, 0, 0, 0));
		}

		for (i = 0; i < m_arCaptionCustomButtons.GetSize(); i++)
		{
			ASSERT_VALID(m_arCaptionCustomButtons[i]);
			m_arCaptionCustomButtons[i]->SetRect(CRect (0, 0, 0, 0));
		}
	}
	else
	{
		m_rectCaption = rect;
		m_rectCaption.bottom = m_rectCaption.top + m_nCaptionHeight;

		int x = m_rectCaption.right;
		int nCaptionOffsetY = 0;

		if (CBCGPVisualManager::GetInstance()->IsDWMCaptionSupported ())
		{
			if (GetParent ()->IsZoomed ())
			{
				rect.top += cyFrameBorder / 2 + yMargin;
				m_rectCaption.OffsetRect (0, cyFrameBorder / 2 + yMargin);
			}

			//------------------
			// Hide our buttons:
			//------------------
			for (i = 0; i < RIBBON_CAPTION_BUTTONS; i++)
			{
				m_CaptionButtons [i].SetRect (CRect (0, 0, 0, 0));
			}

			//-------------------------
			// Get system buttons size:
			//-------------------------
			NONCLIENTMETRICS ncm;
			globalData.GetNonClientMetrics  (ncm);

			int nSysButtonsWidth = ncm.iCaptionWidth;

			if (GetParent ()->GetStyle () & WS_MINIMIZEBOX)
			{
				nSysButtonsWidth += ncm.iCaptionWidth;
			}

			if (GetParent ()->GetStyle () & WS_MAXIMIZEBOX)
			{
				nSysButtonsWidth += ncm.iCaptionWidth;
			}

			x -= nSysButtonsWidth;

			int yOffsetCaptionButton = 0;

			for (i = (int)m_arCaptionCustomButtons.GetSize() - 1; i >= 0 ; i--)
			{
				if (i == (int)m_arCaptionCustomButtons.GetSize() - 1)
				{
					x -= 10;	// Add some space between system and custom buttons
				}

				ASSERT_VALID(m_arCaptionCustomButtons[i]);
				m_arCaptionCustomButtons[i]->SetRect(CRect (0, 0, 0, 0));

				CRect rectCaptionButton (
					CPoint (x - ncm.iCaptionWidth, m_rectCaption.top + yOffsetCaptionButton),
					CSize(ncm.iCaptionWidth, ncm.iCaptionHeight - 1));

				m_arCaptionCustomButtons[i]->SetRect (rectCaptionButton);

				x -= ncm.iCaptionWidth;
			}

			m_rectSysButtons = m_rectCaption;
			m_rectSysButtons.left = x;
			xSysButtonsLeft = x;
		}
		else
		{
			NONCLIENTMETRICS ncm;
			globalData.GetNonClientMetrics  (ncm);

			int nSysBtnEdge = min(ncm.iCaptionHeight, m_rectCaption.Height () - yMargin);

			const CSize sizeCaptionButton (ncm.iCaptionWidth, nSysBtnEdge);
			const int yOffsetCaptionButton = max (0, 
				(m_rectCaption.Height () - sizeCaptionButton.cy) / 2);

			for (i = RIBBON_CAPTION_BUTTONS - 1; i >= 0; i--)
			{
				MCastCaptionButton* pCationBtn = reinterpret_cast<MCastCaptionButton*>(&(m_CaptionButtons [i]));
				ASSERT(pCationBtn);

				if (m_CaptionButtons [i].GetID () == SC_CLOSE)
				{
					pCationBtn->m_bIsDisabled = FALSE;

					CMenu* pSysMenu = GetParent ()->GetSystemMenu (FALSE);
					if (pSysMenu->GetSafeHmenu () != NULL)
					{
						MENUITEMINFO menuInfo;
						ZeroMemory(&menuInfo,sizeof(MENUITEMINFO));
						menuInfo.cbSize = sizeof(MENUITEMINFO);
						menuInfo.fMask = MIIM_STATE;

						if (!pSysMenu->GetMenuItemInfo (SC_CLOSE, &menuInfo) ||
							(menuInfo.fState & MFS_GRAYED) || 
							(menuInfo.fState & MFS_DISABLED))
						{
							pCationBtn->m_bIsDisabled = TRUE;
						}
					}
				}

				if ((m_CaptionButtons [i].GetID () == SC_RESTORE ||
					m_CaptionButtons [i].GetID () == SC_MAXIMIZE) &&
					(GetParent ()->GetStyle () & WS_MAXIMIZEBOX) == 0)
				{
					m_CaptionButtons [i].SetRect (CRect (0, 0, 0, 0));
					continue;
				}

				if (m_CaptionButtons [i].GetID () == SC_MINIMIZE &&
					(GetParent ()->GetStyle () & WS_MINIMIZEBOX) == 0)
				{
					m_CaptionButtons [i].SetRect (CRect (0, 0, 0, 0));
					continue;
				}

				CRect rectCaptionButton (
					CPoint (x - sizeCaptionButton.cx, m_rectCaption.top + yOffsetCaptionButton),
					sizeCaptionButton);

				m_CaptionButtons [i].SetRect (rectCaptionButton);

				x -= sizeCaptionButton.cx;

				if (m_CaptionButtons [i].GetID () == SC_RESTORE ||
					m_CaptionButtons [i].GetID () == SC_MAXIMIZE)
				{
					m_CaptionButtons [i].SetID (GetParent ()->IsZoomed () ? SC_RESTORE : SC_MAXIMIZE);
				}
			}

			for (i = (int)m_arCaptionCustomButtons.GetSize() - 1; i >= 0 ; i--)
			{
				ASSERT_VALID(m_arCaptionCustomButtons[i]);
				m_arCaptionCustomButtons[i]->SetRect(CRect (0, 0, 0, 0));

				CRect rectCaptionButton (
					CPoint (x - sizeCaptionButton.cx, m_rectCaption.top + yOffsetCaptionButton),
					sizeCaptionButton);

				m_arCaptionCustomButtons[i]->SetRect (rectCaptionButton);

				x -= sizeCaptionButton.cx;
			}
		}

		m_rectCaptionText = m_rectCaption;

		if (CBCGPVisualManager::GetInstance()->IsDWMCaptionSupported ())
		{
			m_rectCaptionText.top += GetFrameHeight() / 2;
		}

		m_rectCaptionText.right = x - xMargin;
		m_rectCaptionText.OffsetRect (0, nCaptionOffsetY);

		xSysButtonsLeft = m_rectCaptionText.right;
	}

	//-------------------
	// Repos main button:
	//-------------------
	CSize sizeMainButton = m_sizeMainButton;
	if (IsScenicLook ())
	{
		sizeMainButton.cx += 2 * yTabMargin;
	}

	double scale = globalData.GetRibbonImageScale ();
	if (scale > 1.)
	{
		sizeMainButton.cx = (int)(.5 + scale * sizeMainButton.cx);
		sizeMainButton.cy = (int)(.5 + scale * sizeMainButton.cy);
	}

	if (m_pMainButton != NULL)
	{
		ASSERT_VALID (m_pMainButton);

		MCastMainButton* pMainButton = reinterpret_cast<MCastMainButton*>(m_pMainButton);
		ASSERT_VALID (pMainButton);

		pMainButton->OnCalcTextSize(&dc);

		sizeMainButton.cx = max(sizeMainButton.cx, pMainButton->m_sizeTextRight.cx + 2 * xTabMargin);
		sizeMainButton.cy = max(sizeMainButton.cy, pMainButton->m_sizeTextRight.cy);

		if (bHideAll)
		{
			m_pMainButton->SetRect (CRect (0, 0, 0, 0));
		}
		else
		{
			if (!IsScenicLook ())
			{
				int yOffset = yMargin + m_sizePadding.cy;

				if (CBCGPVisualManager::GetInstance()->IsDWMCaptionSupported ())
				{
					yOffset += GetFrameHeight() / 2;
				}

				m_pMainButton->SetRect (CRect (
					CPoint (rect.left, rect.top + yOffset), sizeMainButton));

				m_rectCaptionText.left = m_pMainButton->GetRect ().right + xMargin;
			}
			else
			{
				CRect rectMainBtn = rect;
				sizeMainButton.cx += m_sizePadding.cx;

				rectMainBtn.top = m_rectCaption.IsRectEmpty () ? rect.top : m_rectCaption.bottom;
				rectMainBtn.bottom = rectMainBtn.top + m_nTabsHeight;
				rectMainBtn.right = rectMainBtn.left + sizeMainButton.cx;

				m_pMainButton->SetRect (rectMainBtn);

				if (IsQuickAccessToolbarOnTop ())
				{
					m_rectCaptionText.left = m_rectCaption.left + 
						::GetSystemMetrics (SM_CXSMICON) + 
						4 * xMargin + m_sizePadding.cx / 2;
				}
			}
		}
	}

	CRect rectCategory = rect;
	m_nBackstageViewTop = m_rectCaption.bottom;

	//----------------------------
	// Repos quick access toolbar:
	//----------------------------
	int nQAToolbarHeight = 0;

	MRibbonQuickAccessToolBar* pQAT = reinterpret_cast<MRibbonQuickAccessToolBar*>(&m_QAToolbar);
	ASSERT(pQAT);

	MCastButtonsGroup* pTabElements = reinterpret_cast<MCastButtonsGroup*>(&m_TabElements);
	ASSERT(pTabElements);

	if (bHideAll)
	{
		pQAT->m_rect.SetRectEmpty();
		pTabElements->m_rect.SetRectEmpty();
	}
	else
	{
		CSize sizeAQToolbar = pQAT->GetRegularSize (&dc);

		if (IsQuickAccessToolbarOnTop ())
		{
			pQAT->m_rect = m_rectCaptionText;

			const int yOffset = max (0, 
				(m_rectCaptionText.Height () - sizeAQToolbar.cy) / 2);

			pQAT->m_rect.top += yOffset;
			pQAT->m_rect.bottom = pQAT->m_rect.top + sizeAQToolbar.cy;

			if (CBCGPVisualManager::GetInstance()->IsDWMCaptionSupported ())
			{
				pQAT->m_rect.top += yMargin;
			}

			pQAT->m_rect.right = 
				min (pQAT->m_rect.left + sizeAQToolbar.cx, 
				m_rectCaptionText.right - 50);

			pQAT->OnAfterChangeRect (&dc);

			int nQAActualWidth = pQAT->GetActualWidth ();
			int nQARight = pQAT->m_rect.left + nQAActualWidth + xMargin;

			if (nQARight < pQAT->m_rect.right)
			{
				pQAT->m_rect.right = nQARight;
			}

			m_rectCaptionText.left = pQAT->m_rect.right;
			if (!IsScenicLook ())
			{
				m_rectCaptionText.left += CBCGPVisualManager::GetInstance ()->GetRibbonQATRightMargin ();
			}
			else
			{
				m_rectCaptionText.left += 3 * xMargin;
			}
		}
		else if (m_bBackstageViewActive)
		{
			pQAT->m_rect.SetRectEmpty();
		}
		else
		{
			pQAT->m_rect = rect;
			pQAT->m_rect.top = pQAT->m_rect.bottom - sizeAQToolbar.cy;
			nQAToolbarHeight = sizeAQToolbar.cy;

			rectCategory.bottom = pQAT->m_rect.top;
		}
	}

	CBCGPVisualManager* pVisualMgr = CBCGPVisualManager::GetInstance();
	if( pVisualMgr && pVisualMgr->IsKindOf(RUNTIME_CLASS(MVisualManager)) )
	{
		((MVisualManager*)pVisualMgr)->OnAfterQATChangeRect(pQAT);
	}

	pQAT->OnAfterChangeRect (&dc);

	if (!bHideAll)
	{
		const int yTabTop = m_rectCaption.IsRectEmpty () ? rect.top : m_rectCaption.bottom;
		const int yTabBottom = m_bAllTabsAreInvisible ? rect.bottom - nQAToolbarHeight : rect.bottom - nCategoryHeight - nQAToolbarHeight;

		m_nBackstageViewTop = yTabBottom + CBCGPVisualManager::GetInstance ()->GetRibbonBackstageTopLineHeight();

		//--------------------
		// Repos tab elements:
		//--------------------
		CSize sizeTabElemens = m_TabElements.GetCompactSize (&dc);

		const int yOffset = (m_bBackstageViewActive && m_bAllTabsAreInvisible) ? 0 : max (0, (yTabBottom - yTabTop - sizeTabElemens.cy) / 2);
		const int nTabElementsHeight = min (m_nTabsHeight, sizeTabElemens.cy);

		m_TabElements.SetRect( CRect (
			CPoint (rect.right - sizeTabElemens.cx, yTabTop + yOffset), 
			CSize (sizeTabElemens.cx, nTabElementsHeight)) );

		//------------
		// Repos tabs:
		//------------
		CArray<CBCGPRibbonCategory*,CBCGPRibbonCategory*> arCategoriesOrdered;

		if (m_bPrintPreviewMode)
		{
			arCategoriesOrdered.Append(m_arCategories);
		}
		else
		{
			m_CustomizationData.PrepareTabsArray(m_arCategories, arCategoriesOrdered);
		}

		const int nTabs = GetVisibleCategoryCount ();

		if (nTabs > 0)
		{
			const int nTabLeftOffset = sizeMainButton.cx + 1;
			const int cxTabsArea = rect.Width () - nTabLeftOffset - sizeTabElemens.cx - xMargin;
			const int nMaxTabWidth = cxTabsArea / nTabs;

			int x = rect.left + nTabLeftOffset;
			BOOL bIsFirstContextTab = TRUE;
			BOOL bCaptionOnRight = FALSE;

			m_Tabs.SetRect( CRect(x,  yTabTop, cxTabsArea, yTabBottom) );

			int cxTabs = 0;

			for (i = 0; i < arCategoriesOrdered.GetSize (); i++)
			{
				MCastCategory* pCategory = reinterpret_cast<MCastCategory*>(arCategoriesOrdered [i]);
				ASSERT_VALID (pCategory);

				if (pCategory->IsVisible () && !m_CustomizationData.IsTabHidden(pCategory))
				{
					CRect rectTabText (0, 0, nMaxTabWidth, m_nTabsHeight);

					dc.DrawText (pCategory->GetDisplayName(TRUE), rectTabText, DT_CALCRECT | DT_SINGLELINE | DT_VCENTER);

					int nTextWidth = rectTabText.Width ();
					int nCurrTabMargin = xTabMargin + nTextWidth / 40;

					pCategory->m_Tab.m_nFullWidth = nTextWidth + 2 * nCurrTabMargin + m_sizePadding.cx;

					const UINT uiContextID = pCategory->GetContextID ();

					if (uiContextID != 0 && m_bReplaceFrameCaption)
					{
						// If the current tab is last in current context, and there is no space
						// for category caption width, add extra space:
						BOOL bIsSingle = TRUE;

						for (int j = 0; j < arCategoriesOrdered.GetSize (); j++)
						{
							CBCGPRibbonCategory* pCategoryNext = arCategoriesOrdered [j];
							ASSERT_VALID (pCategoryNext);

							if (i != j && pCategoryNext->GetContextID () == uiContextID)
							{
								bIsSingle = FALSE;
								break;
							}
						}

						if (bIsSingle)
						{
							CBCGPRibbonContextCaption* pCaption = FindContextCaption (uiContextID);
							if (pCaption != NULL)
							{
								ASSERT_VALID (pCaption);

								const int nMinCaptionWidth = dc.GetTextExtent (pCaption->GetText ()).cx + 2 * xTabMargin;

								if (nMinCaptionWidth > pCategory->m_Tab.m_nFullWidth)
								{
									pCategory->m_Tab.m_nFullWidth = nMinCaptionWidth;
								}
							}
						}
					}


					cxTabs += pCategory->m_Tab.m_nFullWidth;
				}
				else
				{
					pCategory->m_Tab.m_nFullWidth = 0;
				}
			}

			BOOL bNoSpace = cxTabs > cxTabsArea;

			for (i = 0; i < arCategoriesOrdered.GetSize (); i++)
			{
				MCastCategory* pCategory = reinterpret_cast<MCastCategory*>(arCategoriesOrdered [i]);
				ASSERT_VALID (pCategory);

				if (!pCategory->IsVisible () || m_CustomizationData.IsTabHidden(pCategory))
				{
					pCategory->m_Tab.SetRect (CRect (0, 0, 0, 0));
					continue;
				}

				int nTabWidth = pCategory->m_Tab.m_nFullWidth;

				if (nTabWidth > nMaxTabWidth && bNoSpace)
				{
					pCategory->m_Tab.m_bIsTrancated = TRUE;

					if (nTabWidth > 0)
					{
						m_nTabTrancateRatio = max (m_nTabTrancateRatio,
							(int) (100 - 100. * nMaxTabWidth / nTabWidth));
					}

					nTabWidth = nMaxTabWidth;
				}
				else
				{
					pCategory->m_Tab.m_bIsTrancated = FALSE;
				}

				pCategory->m_Tab.SetRect ( 
					CRect (x, yTabTop, x + nTabWidth, yTabBottom));

				const UINT uiContextID = pCategory->GetContextID ();

				if (uiContextID != 0 && m_bReplaceFrameCaption)
				{
					MCastContextCaption* pCaption = reinterpret_cast<MCastContextCaption*>(FindContextCaption (uiContextID));
					if (pCaption != NULL)
					{
						ASSERT_VALID (pCaption);

						int nCaptionWidth = nTabWidth;

						CRect rectOld = pCaption->GetRect ();
						CRect rectCaption = m_rectCaption;

						rectCaption.left = rectOld.left == 0 ? x : rectOld.left;
						rectCaption.right = min (xSysButtonsLeft, x + nCaptionWidth);

						if (bIsFirstContextTab)
						{
							if (IsQuickAccessToolbarOnTop () &&
								rectCaption.left - xTabMargin < pQAT->m_rect.right)
							{
								pQAT->m_rect.right = rectCaption.left - xTabMargin;

								if (pQAT->m_rect.right <= pQAT->m_rect.left)
								{
									pQAT->m_rect.SetRectEmpty ();
								}

								pQAT->OnAfterChangeRect (&dc);

								m_rectCaptionText.left = rectCaption.right + xTabMargin;
								bCaptionOnRight = TRUE;
							}
							else
							{
								const int yCaptionRight = min (m_rectCaptionText.right, x);
								const int nCaptionWidthLeft = yCaptionRight - m_rectCaptionText.left;
								const int nCaptionWidthRight = m_rectCaption.right - rectCaption.right - xTabMargin;

								if (nCaptionTextWidth > nCaptionWidthLeft &&
									nCaptionWidthLeft < nCaptionWidthRight)
								{
									m_rectCaptionText.left = rectCaption.right + xTabMargin;
									bCaptionOnRight = TRUE;
								}
								else
								{
									m_rectCaptionText.right = yCaptionRight;
								}
							}

							bIsFirstContextTab = FALSE;
						}
						else if (bCaptionOnRight)
						{
							m_rectCaptionText.left = rectCaption.right + xTabMargin;
						}

						pCaption->SetRect (rectCaption);

						pCaption->m_nRightTabX = pCategory->m_Tab.m_bIsTrancated ? -1 : 
							pCategory->m_Tab.GetRect ().right;
					}
				}

				x += nTabWidth;
			}
		}

		rectCategory.top = yTabBottom;
	}
	else if (m_bBackstageViewActive && CBCGPVisualManager::GetInstance()->IsRibbonBackstageHideTabs())
	{
		const int yTabBottom = rect.bottom - nCategoryHeight - nQAToolbarHeight;

		m_nBackstageViewTop = yTabBottom + CBCGPVisualManager::GetInstance ()->GetRibbonBackstageTopLineHeight();

		CBCGPRibbonCategory* pCategory = GetBackstageCategory ();
		if (pCategory != NULL && pCategory->GetPanelCount () > 0)
		{
			CBCGPRibbonBackstageViewPanel* pPanel = DYNAMIC_DOWNCAST(CBCGPRibbonBackstageViewPanel, pCategory->GetPanel (0));
			if (pPanel != NULL)
			{
				int nCommandsWidth = pPanel->GetCommandsFrame().Width();

				m_rectBackstageTopArea = m_rectCaption;
				m_rectBackstageTopArea.right = m_rectBackstageTopArea.left + nCommandsWidth;
				m_rectBackstageTopArea.bottom += m_nTabsHeight + 2;

				CSize sizeImage = m_imageBackstageClose.GetImageSize();

				if (sizeImage.cy < m_rectBackstageTopArea.Height())
				{
					int nMargin = max(0, (m_rectBackstageTopArea.Height() - sizeImage.cy) / 2);

					CRect rectClose = m_rectBackstageTopArea;

					rectClose.left += 4 * nMargin;
					rectClose.right = rectClose.left + sizeImage.cx;
					rectClose.DeflateRect(0, nMargin);

					m_BackStageCloseBtn.SetRect(rectClose);
				}
			}
		}
	}

	pTabElements->OnAfterChangeRect (&dc);

	CRect rectCategoryRedraw = rectCategory;

	if (m_pActiveCategory != NULL)
	{
		ASSERT_VALID (m_pActiveCategory);

		MCastCategory* pActiveCategory = reinterpret_cast<MCastCategory*>(m_pActiveCategory);
		ASSERT(pActiveCategory);

		pActiveCategory->m_rect = bHideAll ? CRect (0, 0, 0, 0) : rectCategory;

		if (nCategoryHeight > 0 && !m_bBackstageViewActive)
		{
			int nLastPanelIndex = pActiveCategory->GetPanelCount () - 1;

			CRect rectLastPaneOld;
			rectLastPaneOld.SetRectEmpty ();

			if (nLastPanelIndex >= 0)
			{
				rectLastPaneOld = pActiveCategory->GetPanel (nLastPanelIndex)->GetRect ();
			}

			pActiveCategory->RecalcLayout (&dc);

			if (nLastPanelIndex >= 0 &&
				pActiveCategory->GetPanel (nLastPanelIndex)->GetRect () == rectLastPaneOld)
			{
				rectCategoryRedraw.left = rectLastPaneOld.right;
			}
		}
	}

	dc.SelectObject (pOldFont);

	if (globalData.DwmIsCompositionEnabled() && m_bReplaceFrameCaption && IsVisible())
	{
		BCGPMARGINS margins;
		margins.cxLeftWidth = 0;
		margins.cxRightWidth = 0;
		margins.cyBottomHeight = 0;
		margins.cyTopHeight = 0;

		if (CBCGPVisualManager::GetInstance()->IsDWMCaptionSupported ())
		{
			margins.cyTopHeight = m_rectCaption.bottom;

			GetParent ()->ModifyStyleEx (0, WS_EX_WINDOWEDGE);

			if (m_bTransparentTabs)
			{
				margins.cyTopHeight += m_nTabsHeight + 1;
			}

			if (globalData.DwmExtendFrameIntoClientArea (
				GetParent ()->GetSafeHwnd (), &margins))
			{
				m_bIsTransparentCaption = TRUE;
			}
			else
			{
				m_bTransparentTabs = FALSE;
			}
		}
		else
		{
			globalData.DwmExtendFrameIntoClientArea(GetParent ()->GetSafeHwnd (), &margins);
		}
	}

	if (m_bForceRedraw)
	{
		RedrawWindow ();
		m_bForceRedraw = FALSE;
	}
	else
	{
		InvalidateRect (m_rectCaption);

		CRect rectTabs = rect;
		rectTabs.top = m_rectCaption.IsRectEmpty () ? rect.top : m_rectCaption.bottom;
		rectTabs.bottom = rectTabs.top + m_nTabsHeight + 2 * yTabMargin;

		InvalidateRect (rectTabs);
		InvalidateRect (pQAT->m_rect);
		InvalidateRect (rectCategoryRedraw);

		UpdateWindow ();
	}

	CMenu* pSysMenu = GetParent ()->GetSystemMenu (FALSE);

	if (m_bReplaceFrameCaption &&
		pSysMenu->GetSafeHmenu () != NULL && 
		!m_bIsTransparentCaption)
	{
		for (i = 0; i < RIBBON_CAPTION_BUTTONS; i++)
		{
			CString strName;
			pSysMenu->GetMenuString (m_CaptionButtons [i].GetID (), strName, MF_BYCOMMAND);

			strName = strName.SpanExcluding (_T("\t"));
			strName.Remove (_T('&'));

			m_CaptionButtons [i].SetToolTipText (strName);
		}
	}

	UpdateToolTipsRect ();

	if (!IsSingleLevelAccessibilityMode())
	{
		m_Tabs.UpdateTabs (m_arCategories);
	}
}

MRibbonCategory* MRibbonBar::AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
											   CSize sizeSmallImage, CSize sizeLargeImage, int nInsertAt, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszName != NULL);

	MRibbonCategory* pCategory = NULL;

	if (pRTI != NULL)
	{
		pCategory = DYNAMIC_DOWNCAST(MRibbonCategory, pRTI->CreateObject());

		if (pCategory == NULL)
		{
			ASSERT(FALSE);
			return NULL;
		}

		pCategory->CommonInit(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}
	else
	{
		pCategory = new MRibbonCategory(this, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage);
	}

	if (nInsertAt < 0)
	{
		m_arCategories.Add(pCategory);
	}
	else
	{
		m_arCategories.InsertAt(nInsertAt, pCategory);
	}

	pCategory->m_nKey = m_nNextCategoryKey++;

	if (m_pActiveCategory == NULL)
	{
		m_pActiveCategory = pCategory;

		MRibbonCategory* pActiveCategory = reinterpret_cast<MRibbonCategory*>(m_pActiveCategory);
		pActiveCategory->m_bIsActive = TRUE;
	}

	m_bRecalcCategoryHeight = TRUE;
	m_bRecalcCategoryWidth = TRUE;

	return pCategory;
}

MRibbonCategory* MRibbonBar::AddContextCategory(LPCTSTR lpszName, LPCTSTR lpszContextName, UINT uiContextID, BCGPRibbonCategoryColor clrContext,
													  UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage, CSize sizeLargeImage, int nInsertAt, CRuntimeClass* pRTI)
{
	ASSERT_VALID(this);
	ENSURE(lpszContextName != NULL);
	ENSURE(uiContextID != 0);

	MRibbonCategory* pCategory = AddCategory(lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage, nInsertAt, pRTI);

	if (pCategory == NULL)
	{
		return NULL;
	}

	ASSERT_VALID(pCategory);

	pCategory->m_bIsVisible = FALSE;

	MRibbonContextCaption* pCaption = NULL;

	for (int i = 0; i < m_arContextCaptions.GetSize(); i++)
	{
		pCaption = reinterpret_cast<MRibbonContextCaption*>(m_arContextCaptions [i]);
		ASSERT_VALID(pCaption);

		if (pCaption->m_uiID == uiContextID)
		{
			pCaption->m_strText = lpszContextName;
			pCaption->m_Color = clrContext;
			break;
		}
	}

	if (pCaption == NULL)
	{
		pCaption = new MRibbonContextCaption(lpszContextName, uiContextID, clrContext);
		pCaption->m_pRibbonBar = this;

		m_arContextCaptions.Add(pCaption);
	}

	pCategory->SetTabColor(clrContext);
	pCategory->m_uiContextID = uiContextID;

	return pCategory;
}

MRibbonCategory* MRibbonBar::AddQATOnlyCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, CSize sizeSmallImage)
{
	ASSERT_VALID(this);

	MRibbonCategory* pCategory = AddCategory(lpszName, uiSmallImagesResID, 0, sizeSmallImage);

	if (pCategory == NULL)
	{
		return NULL;
	}

	ASSERT_VALID(pCategory);

	pCategory->m_bIsVisible = FALSE;

	return pCategory;
}

void MRibbonBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int i = 0;

	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rectClip;
	dc.GetClipBox (rectClip);

	CRgn rgnClip;

	if (!rectClip.IsRectEmpty ())
	{
		rgnClip.CreateRectRgnIndirect (rectClip);
		pDC->SelectClipRgn (&rgnClip);
	}

	pDC->SetBkMode (TRANSPARENT);

	CRect rectClient;
	GetClientRect (rectClient);

	OnFillBackground (pDC, rectClient);

	CFont* pOldFont = pDC->SelectObject (GetFont ());
	ASSERT (pOldFont != NULL);

	CRect rectTabs = rectClient;
	rectTabs.top = m_rectCaption.IsRectEmpty () ? rectClient.top : m_rectCaption.bottom;
	rectTabs.bottom = rectTabs.top + m_nTabsHeight;

	//------------------
	// Draw caption bar:
	//------------------
	if (!m_rectCaption.IsRectEmpty ())
	{
		if (m_bIsTransparentCaption)
		{
			CRect rectFill = m_rectCaption;

			if (m_bTransparentTabs)
			{
				rectFill.bottom += m_nTabsHeight + 1;
			}

			rectFill.top = 0;

			pDC->FillSolidRect (rectFill, RGB (0, 0, 0));

			CBCGPToolBarImages::m_bIsDrawOnGlass = TRUE;
		}

		CBCGPVisualManager::GetInstance ()->OnDrawRibbonCaption
			(pDC, this, m_rectCaption, m_rectCaptionText);

		CBCGPVisualManager::GetInstance ()->OnPreDrawRibbon (pDC, this, rectTabs);

		for (i = 0; i < RIBBON_CAPTION_BUTTONS; i++)
		{
			MRibbonCaptionButton* pCaptionButton = reinterpret_cast<MRibbonCaptionButton*>(&m_CaptionButtons[i]);
			ASSERT(pCaptionButton);

			if (!pCaptionButton->GetRect ().IsRectEmpty ())
			{
				pCaptionButton->OnDraw (pDC);
			}
		}

		for (i = 0; i < m_arContextCaptions.GetSize (); i++)
		{
			ASSERT_VALID (m_arContextCaptions [i]);

			MRibbonContextCaption* pContextCaption = reinterpret_cast<MRibbonContextCaption*>(m_arContextCaptions[i]);
			ASSERT(pContextCaption);

			pContextCaption->OnDraw (pDC);
		}

		CBCGPToolBarImages::m_bIsDrawOnGlass = FALSE;
	}

	if (m_bIsTransparentCaption && m_bQuickAccessToolbarOnTop)
	{
		CBCGPToolBarImages::m_bIsDrawOnGlass = TRUE;
	}

	//---------------------------
	// Draw quick access toolbar:
	//---------------------------
	COLORREF cltTextOld = (COLORREF)-1;
	COLORREF cltQATText = CBCGPVisualManager::GetInstance ()->GetRibbonQATTextColor ();

	if (cltQATText != (COLORREF)-1)
	{
		cltTextOld = pDC->SetTextColor (cltQATText);
	}

	MRibbonQuickAccessToolBar* pQAT = reinterpret_cast<MRibbonQuickAccessToolBar*>(&m_QAToolbar);
	ASSERT(pQAT);

	pQAT->OnDraw (pDC);

	if (cltTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (cltTextOld);
	}

	CBCGPToolBarImages::m_bIsDrawOnGlass = FALSE;

	//---------------------
	// Draw active category:
	//---------------------
	if (m_pActiveCategory != NULL && m_dwHideFlags == 0)
	{
		ASSERT_VALID (m_pActiveCategory);
		m_pActiveCategory->OnDraw (pDC);
	}

	//-----------
	// Draw tabs:
	//-----------
	if (AreTransparentTabs ())
	{
		CBCGPToolBarImages::m_bIsDrawOnGlass = TRUE;
	}

	COLORREF clrTextTabs = CBCGPVisualManager::GetInstance ()->OnDrawRibbonTabsFrame(pDC, this, rectTabs);

	for (i = 0; i < m_arCategories.GetSize (); i++)
	{
		CBCGPRibbonCategory* pCategory = m_arCategories [i];
		ASSERT_VALID (pCategory);

		MRibbonCategory* pMCategory = NULL;
		if( pCategory->IsKindOf(RUNTIME_CLASS(MRibbonCategory)))
		{
			pMCategory = reinterpret_cast<MRibbonCategory*>(m_arCategories [i]);
		}

		if (pCategory->IsVisible () && !m_CustomizationData.IsTabHidden(pCategory))
		{
			if( pMCategory ) 
			{
				MRibbonTab MTab;
				MTab.CopyFrom(pMCategory->m_Tab);
				MTab.OnDraw (pDC);
			}
			else
			{
				MCastCategory* pCastCategory = reinterpret_cast<MCastCategory*>(pCategory);
				ASSERT_VALID (pCastCategory);

				pCastCategory->m_Tab.OnDraw(pDC);
			}
		}
	}

	if (m_bBackstageViewActive && IsScenicLook())
	{
		CRect rectBackstageLine = rectTabs;
		rectBackstageLine.top = rectTabs.bottom;
		rectBackstageLine.bottom += CBCGPVisualManager::GetInstance ()->GetRibbonBackstageTopLineHeight();

		CBCGPVisualManager::GetInstance ()->OnDrawRibbonBackstageTopLine(pDC, rectBackstageLine);
	}

	//--------------------------------
	// Draw elements on right of tabs:
	//--------------------------------
	COLORREF clrTextOld = (COLORREF)-1;
	if (clrTextTabs != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrTextTabs);
	}

	MRibbonButtonsGroup* pTabElements = reinterpret_cast<MRibbonButtonsGroup*>(&m_TabElements);
	ASSERT(pTabElements);

	pTabElements->OnDraw (pDC);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	//------------------
	// Draw main button:
	//------------------
	if (m_pMainButton != NULL)
	{
		ASSERT_VALID (m_pMainButton);

		if (!m_pMainButton->GetRect ().IsRectEmpty ())
		{
			CBCGPVisualManager::GetInstance ()->OnDrawRibbonMainButton(pDC, m_pMainButton);

			if (m_bIsTransparentCaption)
			{
				CBCGPToolBarImages::m_bIsDrawOnGlass = TRUE;
			}

			m_pMainButton->OnDraw (pDC);
		}
	}

	CBCGPToolBarImages::m_bIsDrawOnGlass = FALSE;

	pDC->SelectObject (pOldFont);
	pDC->SelectClipRgn (NULL);
}

UINT MRibbonBar::GetMenuIDFromText(MRibbonBar* pRibbonBar, CString strCategory, CString strPanel, CString strElem1, CString strElem2, CString strElem3)
{
  MRibbonCategory* pCategory;
  MRibbonPanel*    pPanel;
  MRibbonButton    *pElem1, *pElem2, *pElem3;

  for(int i=0; i<pRibbonBar->m_arCategories.GetSize(); i++)
  {
    pCategory = (MRibbonCategory*)pRibbonBar->m_arCategories[i];
    if(strCategory.CompareNoCase(MakeFilteredText(pCategory->GetName()))!=0) continue;

    for(int j=0; j<pCategory->m_arPanels.GetSize(); j++)
    {
      pPanel = (MRibbonPanel*)pCategory->m_arPanels[j];
      if(strPanel.CompareNoCase(MakeFilteredText(pPanel->GetName()))!=0) continue;

      for(int k=0; k<pPanel->m_arElements.GetSize(); k++)
      {
        pElem1 = (MRibbonButton*)pPanel->m_arElements[k];
        if(strElem1.CompareNoCase(MakeFilteredText(pElem1->GetText()))==0)
        {
          if(strElem2.IsEmpty()) return pElem1->GetID();
          for(int m=0; m<pElem1->m_arSubItems.GetSize(); m++)
          {
            pElem2 = (MRibbonButton*)pElem1->m_arSubItems[m];
            if(strElem2.CompareNoCase(MakeFilteredText(pElem2->GetText()))==0)
            {
              if(strElem3.IsEmpty()) return pElem2->GetID();

              for(int n=0; n<pElem2->m_arSubItems.GetSize(); n++)
              {
                pElem3 = (MRibbonButton*)pElem2->m_arSubItems[n];
                if(strElem3.CompareNoCase(MakeFilteredText(pElem3->GetText()))==0)
                {
                  return pElem3->GetID();
                }
              }
            }
          }
        }
      }
    }

    // Civil을 위해 임시 처리(15.1.29)
    // Category->AddHidden()으로 추가된 경우 Panel이 아닌 Category에 정보가 들어있습니다.
    // Civil은 AddHidden()을 사용하고 있는데, 같은 이름의 메뉴가 중복되어 있는 경우 정확한 경로를 알지 못해 먼저 검색되는 메뉴가 실행되게 됩니다.
    // 이 문제를 해결하려면 MainFrm_Ribbon_civil.cpp에서 메뉴생성 시 AddSubItem()을 사용하도록 수정해야 합니다.

    // 특수처리...
#include "..\wg_main\wg_mainRes2.h"
//#include "..\wg_base\wg_base_MsgDll.h"
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)  ) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_WINDOW2       )))  return ID_VIEW_SELECT_WINDOW;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_IDENTITY      )))  return ID_VIEW_SELECT_IDENTITY;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_WINDOW2       )))  return ID_VIEW_SELECT_UNSELECT_WINDOW;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_POLYGON       )))  return ID_VIEW_SELECT_UNSELECT_POLYGON;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_INTERSECT_LINE)))  return ID_VIEW_SELECT_UNSELECT_INTERSECT;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_PLANE         )))  return ID_VIEW_SELECT_UNSELECT_PLANE ;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_VOLUME        )))  return ID_VIEW_SELECT_UNSELECT_VOLUME;
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_View)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Select)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Unselect)) && strElem2==MakeFilteredText(_LS(IDS_MAIN_RIBBON_VIEW_SELECT_ALL    )))  return ID_VIEW_SELECT_UNSELECTALL    ;
    //

    // node/element => elememt
    // delete
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Delete)))  return ID_STRUCT_ELEM_DELETE;
    // translate
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Translate)))  return ID_STRUCT_ELEM_TRANSLATE;
    //rotate
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Rotate)))  return ID_STRUCT_ELEM_ROTATE;
    // Mirror
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Mirror)))  return ID_STRUCT_ELEM_MIRROR;
    // Divide
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Divide)))  return ID_STRUCT_ELEM_DIVIDE;  
    // Merge
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Merge)))  return ID_STRUCT_ELEM_MERGE;
    // Renumbering
    if(strCategory==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Node_Element)) && strPanel==MakeFilteredText(_LS(IDS_MAIN_RIBBON_MENU_Elements)) && strElem1==MakeFilteredText(_T("Renumbering")))  return ID_STRUCT_ELEM_RENUMBER;


    for(int k=0; k<pCategory->m_arElements.GetSize(); k++)
    {
      pElem1 = (MRibbonButton*)pCategory->m_arElements[k];

      CString strElem = MakeFilteredText(pElem1->GetText());
      if(strElem1.CompareNoCase(strElem)==0 || strElem2.CompareNoCase(strElem)==0 || strElem3.CompareNoCase(strElem)==0)
      {
        return pElem1->GetID();
      }
    }
  }

  ASSERT(0);
  return 0;
}

// 앞뒤의 공백 제거, ... 기호 제거
CString MRibbonBar::MakeFilteredText(CString str)
{
  str.TrimLeft(); 
  str.TrimRight();
  str.Replace("...","");
  str.Replace("..","");

  return str;
}