#include "StdAfx.h"
#include "MRibbonTab.h"
#include "MRibbonCategory.h"

using namespace mit::frx;

static const int nPanelMarginTop = 3;

MRibbonTab::MRibbonTab()
:CBCGPRibbonTab()
{

}

void MRibbonTab::CopyFrom (const CBCGPBaseRibbonElement& src)
{
	CBCGPRibbonTab::CopyFrom (src);

	this->m_bIsFocused = src.IsFocused();
	this->m_bIsHighlighted = src.IsHighlighted();
	this->m_bIsPressed = src.IsPressed();
	this->m_bIsDisabled = src.IsDisabled();
	this->m_bIsChecked  = src.IsChecked();
	this->m_bIsDroppedDown = src.IsDroppedDown();
	this->m_rect = src.GetRect();
	this->m_pParent = src.GetParentCategory();
}

void MRibbonTab::OnDraw(CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pParent);
	ASSERT_VALID (m_pParent->GetParentRibbonBar ());

	if (m_rect.IsRectEmpty ())
	{
		return;
	}

	BOOL bIsActive = (m_pParent->IsActive () || GetDroppedDown () != NULL) && !m_pParent->GetParentRibbonBar ()->IsBackstageViewActive();

	COLORREF clrText = CBCGPVisualManager::GetInstance ()->OnDrawRibbonCategoryTab (
		pDC, this, bIsActive);

	MRibbonCategory* pParent = reinterpret_cast<MRibbonCategory*>(m_pParent);
	ASSERT(pParent);

	if (!pParent->m_strName.IsEmpty ())
	{
		m_nTextGlassGlowSize = 0;

		CRect rectTab = m_rect;
		CRect rectTabText = m_rect;

		pDC->DrawText (pParent->m_strName, rectTabText, 
			DT_CALCRECT | DT_SINGLELINE | DT_VCENTER);

		const int cxTabText = rectTabText.Width ();
		const int cxTabTextMargin = max (4, (rectTab.Width () - cxTabText) / 2);

		rectTab.DeflateRect (cxTabTextMargin, 0);
		rectTab.top += nPanelMarginTop;

// 		CFont* pOldFont = NULL;
// 		if( bIsActive )
// 		{
// 			pOldFont = pDC->SelectObject (&globalData.fontBold);
// 			ASSERT (pOldFont != NULL);
// 		}

		DoDrawText(pDC, pParent->m_strName, rectTab, DT_SINGLELINE | DT_VCENTER, clrText);

// 		if (pOldFont != NULL)
// 		{
// 			pDC->SelectObject (pOldFont);
// 		}
	}	
}