#include "stdafx.h"
#include "MGridButtonItem.h"

using namespace mit;
using namespace mit::frx;

class CFriendButton : public CBCGPButton
{
	friend class MGridButtonItem;
};

IMPLEMENT_SERIAL(MGridButtonItem, MGridItem, VERSIONABLE_SCHEMA | 1)

MGridButtonItem* MGridButtonItem::s_pHighlightedItem = NULL;

MGridButtonItem::MGridButtonItem() :
	m_id(0)
{
}

MGridButtonItem::MGridButtonItem(UINT id) :
	m_id(id)
{
}

void MGridButtonItem::OnDrawValue(CDC* pDC, CRect rect)
{
	ASSERT_VALID(pDC);

	OnFillBackground(pDC, rect);

	rect.DeflateRect(1, 1);

	COLORREF clrText = globalData.clrBarText;

#ifndef _BCGSUITE_INC_
	CBCGPButton dummyBtn;
	((CFriendButton*)&dummyBtn)->m_bHighlighted = (s_pHighlightedItem == this);
	CBCGPVisualManager::GetInstance()->OnDrawPushButton(pDC, rect, &dummyBtn, clrText);
#else
	pDC->FillRect(rect, &globalData.brBarFace);

	pDC->Draw3dRect(rect, globalData.clrBarLight, globalData.clrBarDkShadow);
	rect.DeflateRect(1, 1);
	pDC->Draw3dRect(rect, globalData.clrBarHilite, globalData.clrBarShadow);
#endif

	COLORREF clrTextOld = pDC->SetTextColor(clrText);

	CString strText = GetLabel();
	pDC->DrawText(strText, rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

	pDC->SetTextColor(clrTextOld);
}

BOOL MGridButtonItem::OnClickValue(UINT uiMsg, CPoint point)
{
	if (uiMsg != WM_LBUTTONDOWN)
	{
		return MGridItem::OnClickValue(uiMsg, point);
	}

	CBCGPGridCtrl* pGridCtrl = GetOwnerList();
	ASSERT_VALID(pGridCtrl);

	pGridCtrl->SendMessage(WM_COMMAND, MAKEWPARAM(m_id, BN_CLICKED));

	return TRUE;
}