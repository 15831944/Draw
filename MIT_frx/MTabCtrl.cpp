#include "stdafx.h"
#include "MTabCtrl.h"

using namespace mit::frx;

enum { PADDING = 3, EDGE = 20};

IMPLEMENT_DYNCREATE(MTabCtrl, CTabCtrl)
MTabCtrl::MTabCtrl(void)
{	
	m_clrBackground = /*globalData.clrBarLight*/::GetSysColor(COLOR_3DFACE);
}


MTabCtrl::~MTabCtrl(void)
{
}

BEGIN_MESSAGE_MAP(MTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()

int MTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Owner Draw วัดู.
	ModifyStyle(0, TCS_OWNERDRAWFIXED);

	return 0;
}

void MTabCtrl::PreSubclassWindow() 
{
	CTabCtrl::PreSubclassWindow();

	ModifyStyle(0, TCS_OWNERDRAWFIXED);
}

void MTabCtrl::OnPaint() 
{
	CPaintDC dc(this); 

	dc.SelectObject(GetFont());

	DRAWITEMSTRUCT dis;
	dis.CtlType = ODT_TAB;
	dis.CtlID = GetDlgCtrlID();
	dis.hwndItem = GetSafeHwnd();
	dis.hDC = dc.GetSafeHdc();
	dis.itemAction = ODA_DRAWENTIRE;

	CRect rClient, rPage;
	GetClientRect(&dis.rcItem);
	rPage = dis.rcItem;
	AdjustRect(FALSE, rPage);
	dis.rcItem.top = rPage.top - 2;

	DrawMainBorder(&dis);

	// paint the tabs first and then the borders
	int nTab = GetItemCount();
	int nSel = GetCurSel();

	if (!nTab) // no pages added
		return;

	while (nTab--)
	{
		if (nTab != nSel)
		{
			dis.itemID = nTab;
			dis.itemState = 0;

			VERIFY(GetItemRect(nTab, &dis.rcItem));

			dis.rcItem.bottom -= 2;
			DrawItem(&dis);
			DrawItemBorder(&dis);
		}
	}

	// now selected tab
	dis.itemID = nSel;
	dis.itemState = ODS_SELECTED;

	VERIFY(GetItemRect(nSel, &dis.rcItem));

	dis.rcItem.bottom += 2;
	dis.rcItem.top -= 2;
	DrawItem(&dis);
	DrawItemBorder(&dis);
}


BOOL MTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rClient, rTab, rTotalTab, rBkgnd, rEdge;
	COLORREF crBack;
	int nTab, nTabHeight = 0;

	CTabCtrl::OnEraseBkgnd(pDC);

	GetClientRect(rClient);
	nTab = GetItemCount();
	rTotalTab.SetRectEmpty();

	while (nTab--)
	{
		GetItemRect(nTab, rTab);
		rTotalTab.UnionRect(rTab, rTotalTab);
	}

	nTabHeight = rTotalTab.Height();

	rTotalTab.InflateRect(2, 3);
	rEdge = rTotalTab;

	crBack = (m_clrBackground == -1) ? ::GetSysColor(COLOR_3DFACE) : m_clrBackground;

	rBkgnd = rClient;
	rBkgnd.bottom = rTotalTab.top + 3;
	pDC->SetBkColor(crBack);
	pDC->ExtTextOut(rBkgnd.left, rBkgnd.top, ETO_CLIPPED | ETO_OPAQUE, rBkgnd, "", NULL);

	rBkgnd = rClient;
	rBkgnd.right = 2;
	rBkgnd.bottom = rBkgnd.top + (nTabHeight + 2);
	pDC->ExtTextOut(rBkgnd.left, rBkgnd.top, ETO_CLIPPED | ETO_OPAQUE, rBkgnd, "", NULL);

	// to right of tabs
	rBkgnd = rClient;
	rBkgnd.left += rTotalTab.Width() - 2;
	rBkgnd.bottom = rBkgnd.top + (nTabHeight + 2);
	pDC->ExtTextOut(rBkgnd.left, rBkgnd.top, ETO_CLIPPED | ETO_OPAQUE, rBkgnd, "", NULL);

	return TRUE;
}

void MTabCtrl::SetBkgndColor(COLORREF color)
{	
	m_clrBackground = color;

	// redraw
	if (GetSafeHwnd())
		Invalidate();
}

COLORREF MTabCtrl::GetTabColor(BOOL /*bSelected*/)
{
	return ::GetSysColor(COLOR_3DFACE);
}

COLORREF MTabCtrl::GetTabTextColor(BOOL /*bSelected*/)
{
	return ::GetSysColor(COLOR_WINDOWTEXT);
}

CSize MTabCtrl::FormatText(CString& sText, CDC* pDC, int nWidth)
{
	CRect rect(0, 0, nWidth, 20);
	UINT uFlags = DT_CALCRECT | DT_SINGLELINE | DT_MODIFYSTRING | DT_END_ELLIPSIS;

	::DrawText(pDC->GetSafeHdc(), sText.GetBuffer(sText.GetLength() + 4), -1, rect, uFlags);
	sText.ReleaseBuffer();

	return pDC->GetTextExtent(sText);
}

void MTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	TC_ITEM     tci;
	CDC* pDC = CDC::FromHandle(lpdis->hDC);
	HIMAGELIST hilTabs = (HIMAGELIST)TabCtrl_GetImageList(GetSafeHwnd());

	BOOL bSelected = (lpdis->itemID == (UINT)GetCurSel());

	CRect rItem(lpdis->rcItem);

	if (bSelected)
		rItem.bottom -= 1;
	else
		rItem.bottom += 2;

	// tab
	COLORREF crFrom = GetTabColor(bSelected);

	pDC->FillSolidRect(rItem, crFrom);

	// text & icon
	rItem.left += PADDING;
	rItem.top += PADDING + (bSelected ? 1 : 0);

	pDC->SetBkMode(TRANSPARENT);

	CString sTemp;
	tci.mask        = TCIF_TEXT | TCIF_IMAGE;
	tci.pszText     = sTemp.GetBuffer(100);
	tci.cchTextMax  = 99;
	GetItem(lpdis->itemID, &tci);
	sTemp.ReleaseBuffer();

	// icon
	if (hilTabs)
	{
		ImageList_Draw(hilTabs, tci.iImage, *pDC, rItem.left, rItem.top, ILD_TRANSPARENT);
		rItem.left += 16 + PADDING;
	}

	// text
	rItem.right -= PADDING;
	FormatText(sTemp, pDC, rItem.Width());

	pDC->SetTextColor(GetTabTextColor(bSelected));
	pDC->DrawText(sTemp, rItem, DT_NOPREFIX | DT_CENTER);
}

void MTabCtrl::DrawItemBorder(LPDRAWITEMSTRUCT lpdis)
{
	BOOL bSelected = (lpdis->itemID == (UINT)GetCurSel());

	CRect rItem(lpdis->rcItem);
	CDC* pDC = CDC::FromHandle(lpdis->hDC); 

	COLORREF crTab = GetTabColor(bSelected);
	COLORREF crHighlight = globalData.clrBarHilite;
	COLORREF crShadow = globalData.clrBarShadow;

	if ( bSelected )
	{
		rItem.bottom += bSelected ? -1 : 1;

		// edges
		pDC->FillSolidRect(CRect(rItem.left, rItem.top, rItem.left + 1, rItem.bottom), crHighlight);
		pDC->FillSolidRect(CRect(rItem.left, rItem.top, rItem.right, rItem.top + 1), crHighlight);
		pDC->FillSolidRect(CRect(rItem.right - 1, rItem.top, rItem.right, rItem.bottom), crShadow);
	}
	else // draw simple dividers
	{
		pDC->FillSolidRect(CRect(rItem.left - 1, rItem.top, rItem.left, rItem.bottom), crShadow);
		pDC->FillSolidRect(CRect(rItem.right - 1, rItem.top, rItem.right, rItem.bottom), crShadow);
	}
}

void MTabCtrl::DrawMainBorder(LPDRAWITEMSTRUCT lpdis)
{
	CRect rBorder(lpdis->rcItem);
	CDC* pDC = CDC::FromHandle(lpdis->hDC); 

	COLORREF crTab = GetTabColor();
	COLORREF crHighlight = globalData.clrBarLight;
	COLORREF crShadow = globalData.clrBarShadow;

	CRect temp(rBorder);
	temp.InflateRect(1, 1);

	pDC->FillSolidRect(temp, crHighlight);
	pDC->Draw3dRect(rBorder, crHighlight, crShadow);
}
