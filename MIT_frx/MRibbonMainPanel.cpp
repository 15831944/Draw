#include "StdAfx.h"
#include "MRibbonMainPanel.h"

#include "MVisualManager.h"

using namespace mit;
using namespace mit::frx;

#define LABEL_MARGIN_X				8
#define LABEL_MARGIN_Y				4
#define BACKSTAGE_BUTTON_MARGIN_X	6

class MBaseRibbonElement: public CBCGPBaseRibbonElement
{
	friend class MRibbonMainPanel;
};

IMPLEMENT_DYNCREATE(MRibbonRecentFilesList, CBCGPRibbonRecentFilesList);

void MRibbonRecentFilesList::OnAfterChangeRect (CDC* pDC)
{
	if ( !CBCGPVisualManager::GetInstance()->IsKindOf(RUNTIME_CLASS(MVisualManager)) )
	{
		return MRibbonRecentFilesList::OnAfterChangeRect(pDC);
	};

	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	if (GetCount () == 0)
	{
		FillList ();
	}

	int y = m_rect.top + 2;

	for (int i = 0; i < m_arButtons.GetSize (); i++)
	{
		CBCGPBaseRibbonElement* pButton = m_arButtons [i];
		ASSERT_VALID (pButton);

		pButton->SetParentMenu (m_pParentMenu);

		pButton->OnCalcTextSize (pDC);
		CSize sizeButton = pButton->GetSize (pDC);

		CRect rectButton = m_rect;

		// jpahn : Deflate´Â ¾ÈÇÑ´Ù. ´ë½Å ¿ÞÂÊ Separator ¸¸Å« 1ÇÈ¼¿¸¸ ¶ç¿î´Ù.
		//rectButton.DeflateRect (1, 0);
		rectButton.left++;

		rectButton.top = y;
		rectButton.bottom = y + sizeButton.cy;

		pButton->SetRect (rectButton);
		pButton->OnAfterChangeRect (pDC);

		y = rectButton.bottom;
	}
}

//**********************************************************************************
CSize MRibbonRecentFilesList::GetRegularSize (CDC* pDC)
{
	return CBCGPRibbonRecentFilesList::GetRegularSize(pDC);
}

//********************************************************************************
void MRibbonRecentFilesList::OnDraw (CDC* pDC)
{
	CBCGPRibbonRecentFilesList::OnDraw(pDC);
}

IMPLEMENT_DYNCREATE(MRibbonMainPanel, CBCGPRibbonMainPanel);

//**************************************************************************************
void MRibbonMainPanel::AddMRecentFilesList (LPCTSTR lpszLabel, int nWidth, BOOL bShowPins)
{
	ASSERT_VALID (this);
	ASSERT (lpszLabel != NULL);

	if (IsBackstageView())
	{
		ASSERT(FALSE);
		return;
	}

	AddToRight (new MRibbonRecentFilesList (lpszLabel, bShowPins), nWidth);
}

//********************************************************************************
void MRibbonMainPanel::Repos (CDC* pDC, const CRect& rect)
{
	CBCGPRibbonMainPanel::Repos(pDC, rect);
}