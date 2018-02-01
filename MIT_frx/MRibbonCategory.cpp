#include "StdAfx.h"
#include "MRibbonCategory.h"
#include "MRibbonBar.h"
#include "MRibbonButton.h"

static const int nPanelMarginLeft = 2;
static const int nPanelMarginRight = 2;
static const int nPanelMarginTop = 3;
static const int nPanelMarginBottom = 4;

using namespace mit::frx;

MRibbonCategory::MRibbonCategory(void)
: CBCGPRibbonCategory()
{
}

MRibbonCategory::MRibbonCategory(MRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage, CSize sizeLargeImage)
: CBCGPRibbonCategory(pParentRibbonBar, lpszName, uiSmallImagesResID, uiLargeImagesResID, sizeSmallImage, sizeLargeImage)
{

}


MRibbonCategory::~MRibbonCategory(void)
{
}

MRibbonPanel* MRibbonCategory::AddPanel (LPCTSTR lpszPanelName, HICON hIcon, CRuntimeClass* pRTI, BOOL bAutoDestroyIcon, int nInsertAt)
{
	ASSERT_VALID (this);
	ASSERT (lpszPanelName != NULL);

	MRibbonPanel* pPanel = NULL;

	if (pRTI != NULL)
	{
		pPanel = DYNAMIC_DOWNCAST (MRibbonPanel, pRTI->CreateObject ());

		if (pPanel == NULL)
		{
			ASSERT (FALSE);
			return NULL;
		}

		pPanel->CommonInit (lpszPanelName, hIcon, bAutoDestroyIcon);
	}
	else
	{
		pPanel = new MRibbonPanel (lpszPanelName, hIcon, bAutoDestroyIcon);
	}

	AddPanelInternal(pPanel, nInsertAt);

	return pPanel;
}

void MRibbonCategory::RecalcLayout(CDC* pDC)
{
	if (m_rect.IsRectEmpty ())
	{
		return;
	}

	if (m_pParentMenuBar != NULL)
	{
		CleanUpSizes ();
	}

	RecalcPanelWidths (pDC);

	if (m_arPanels.GetSize () == 0)
	{
		return;
	}

	if (m_bOnDialogBar)
	{
		ReposPanelsVert (pDC);

		if (GetParentRibbonBar ()->GetSafeHwnd () != NULL)
		{
			GetParentRibbonBar ()->RedrawWindow (m_rect);
		}

		return;
	}

	int i = 0;
	BOOL bRedrawScroll = FALSE;

	MRibbonBar* pRibbonBar = reinterpret_cast<MRibbonBar*>(GetParentRibbonBar ());
	ASSERT(pRibbonBar);

	const DWORD dwRibbonHideFlags = pRibbonBar->m_dwHideFlags;
	const BOOL bHideAll = (dwRibbonHideFlags & BCGPRIBBONBAR_HIDE_ALL) ||
		(dwRibbonHideFlags & BCGPRIBBONBAR_HIDE_ELEMENTS);

	if (m_nMinWidth < 0)
	{
		m_nMinWidth = GetMinWidth (pDC);
	}

	if (bHideAll && m_pParentMenuBar == NULL)
	{
		for (i = 0; i < m_arPanels.GetSize (); i++)
		{
			MRibbonPanel* pPanel = reinterpret_cast<MRibbonPanel*>(m_arPanels [i]);
			ASSERT_VALID (pPanel);

			pPanel->Repos (pDC, CRect (0, 0, 0, 0));
			pPanel->OnShow (FALSE);
		}

		m_nLastCategoryWidth = -1;
		m_nMinWidth = -1;
	}
	else if (m_nLastCategoryWidth != m_rect.Width () || m_nLastCategoryOffsetY != m_rect.top)
	{
		m_nLastCategoryWidth = m_rect.Width ();
		m_nLastCategoryOffsetY = m_rect.top;

		CRect rectClient = m_rect;
		rectClient.DeflateRect (nPanelMarginLeft * 2, nPanelMarginTop, 
			nPanelMarginRight * 2, nPanelMarginBottom);

		ResetPanelsLayout ();

		if (rectClient.Width () <= m_nMinWidth)
		{
			//-------------------------
			// Just collapse all panes:
			//-------------------------
			for (i = 0; i < m_arPanels.GetSize (); i++)
			{
				MRibbonPanel* pPanel = reinterpret_cast<MRibbonPanel*>(m_arPanels [i]);
				ASSERT_VALID (pPanel);

				pPanel->m_bForceCollpapse = TRUE;
				pPanel->m_nCurrWidthIndex = (int) pPanel->m_arWidths.GetSize () - 1;
			}
		}
		else
		{
			BOOL bAutoResize = TRUE;

			if (m_arCollapseOrder.GetSize () > 0)
			{
				bAutoResize = FALSE;

				BOOL bOK = TRUE;

				for (int iNextPane = 0; iNextPane <= m_arCollapseOrder.GetSize (); iNextPane++)
				{
					bOK = SetPanelsLayout (rectClient.Width ());
					if (bOK || iNextPane == m_arCollapseOrder.GetSize ())
					{
						break;
					}

					//------------------------------------------------------------
					// Find next pane for collapsing - from the user-defined list:
					//------------------------------------------------------------
					int nPaneIndex = m_arCollapseOrder [iNextPane];
					if (nPaneIndex < 0 || nPaneIndex >= m_arPanels.GetSize ())
					{
						ASSERT (FALSE);
						bOK = FALSE;
						break;
					}

					MRibbonPanel* pPanel = reinterpret_cast<MRibbonPanel*>(m_arPanels [nPaneIndex]);
					ASSERT_VALID (pPanel);

					if (iNextPane < m_arCollapseOrder.GetSize () - 1 &&
						m_arCollapseOrder [iNextPane + 1] == -1)
					{
						pPanel->m_bForceCollpapse = TRUE;
						pPanel->m_nCurrWidthIndex = (int) pPanel->m_arWidths.GetSize () - 1;

						iNextPane++;
					}
					else
					{
						if (pPanel->m_nCurrWidthIndex < pPanel->m_arWidths.GetSize () - 1)
						{
							pPanel->m_nCurrWidthIndex++;
						}
					}
				}

				if (!bOK)
				{
					bAutoResize = TRUE;
					ResetPanelsLayout ();
				}
			}

			if (bAutoResize)
			{
				while (TRUE)
				{
					if (SetPanelsLayout (rectClient.Width ()))
					{
						break;
					}

					//----------------------------------------------
					// Find next pane for collapsing - next matched:
					//----------------------------------------------
					int nMaxWeightIndex = -1;
					int nMaxWeight = 1;

					for (i = 0; i < m_arPanels.GetSize (); i++)
					{
						MRibbonPanel* pPanel = reinterpret_cast<MRibbonPanel*>(m_arPanels [i]);
						ASSERT_VALID (pPanel);

						int nWeight = (int) pPanel->m_arWidths.GetSize () - pPanel->m_nCurrWidthIndex - 1;
						if (nWeight >= nMaxWeight)
						{
							nMaxWeightIndex = i;
							nMaxWeight = nWeight;
						}
					}

					if (nMaxWeightIndex < 0)
					{
						break;
					}

					MRibbonPanel* pPanel = reinterpret_cast<MRibbonPanel*>(m_arPanels [nMaxWeightIndex]);
					ASSERT_VALID (pPanel);

					pPanel->m_nCurrWidthIndex++;
				}
			}
		}

		ReposPanels (pDC);
		bRedrawScroll = TRUE;
	}

	UpdateScrollButtons ();

	if (bRedrawScroll && pRibbonBar->GetSafeHwnd () != NULL)
	{
		if (!m_ScrollLeft.GetRect ().IsRectEmpty () ||
			!m_ScrollRight.GetRect ().IsRectEmpty ())
		{
			pRibbonBar->RedrawWindow (m_rect);
		}
	}
}