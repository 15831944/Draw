#include "stdafx.h"
#include "GroupList.h"

#include "MVisualManager.h"

#include "ColorLib.h"

using namespace mit::frx;

IMPLEMENT_DYNCREATE(CGroupList, CWnd)

BEGIN_MESSAGE_MAP(CGroupList, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

CGroupList::CGroupList()
: m_bMouseOver(FALSE),
m_ptMouse(0,0),
m_bMouseDrag(FALSE),
m_ptScrollBarMouseDragStart(0,0),
m_ptScrollMouseDragStart(0,0),
m_bLButtonClick(FALSE),
m_bNeedHitTest(FALSE),
m_pImageList(NULL),
m_posActiveGroup(NULL),
m_nItemHeight(20),
m_nItemCount(12),
m_bFitItemCount(TRUE),
m_clrBorder(RGB(32,32,32)),
m_clrListBack(RGB(119,119,119)),
m_clrListSelectBorder(RGB(40,60,102)),
m_clrListSelectBack1(RGB(165,193,232)),
m_clrListSelectBack2(RGB(124,143,172)),
m_clrListText(RGB(255,255,255)),
m_clrScrollBarBack(RGB(110,110,110)),
m_clrScrollBar(RGB(187,187,187)),
m_clrScrollBarOver(RGB(255,255,255)),
m_nScrollWidth(16),
m_nScrollBarWidth(6),
m_clrGroupBack(RGB(81,81,81)),
m_clrGroupText(RGB(255,255,255)),
m_nGroupDeactiveAlpha(169),
m_nExtendBtnWidth(6),
m_nExtendBtnThick(2),
m_hFont(NULL),
m_bSuspendUpdate(FALSE),
m_nHeightBeforeUpdate(0)
{
	WNDCLASS    wndcls;
	HINSTANCE   hInst = AfxGetInstanceHandle();

	if ( !(::GetClassInfo(hInst, _T("GroupList"), &wndcls)) )
	{
		wndcls.style            = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = _T("GroupList");

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
		}
	}

	ZeroMemory(&m_trackMouse, sizeof(m_trackMouse));
}

CGroupList::~CGroupList()
{

}

BOOL CGroupList::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CWnd::Create(_T("GroupList"), _T(""), dwStyle, rect, pParentWnd, nID, pContext);
}

POSITION CGroupList::AddGroup(const CString& strName)
{
	POSITION pos = m_listGroup.AddTail(new TGroupListGroup(strName));
	if (IsNoActiveGroup()) SetActiveGroup(pos);
	AdjustSize();
	return pos;
}

void CGroupList::RemoveGroup(POSITION pos)
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(pos);
	if (!pGroup) return;
	delete pGroup;
	m_listGroup.RemoveAt(pos);
	if (pos == m_posActiveGroup)
	{
		if (m_listGroup.IsEmpty())
		{
			SetActiveGroup(NULL);
		}
		else
		{
			SetActiveGroup(m_listGroup.GetHeadPosition());			
		}
	}
	AdjustSize();
}

void CGroupList::RemoveGroupAll()
{
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		TGroupListGroup* pGroup = m_listGroup.GetNext(pos);
		delete pGroup;
	}
	m_listGroup.RemoveAll();
	m_posActiveGroup = NULL;
	AdjustSize();
	Invalidate(FALSE);
}

void CGroupList::SetActiveGroup(POSITION pos)
{
	if (m_posActiveGroup == pos) return;
	ASSERT(pos == NULL || m_listGroup.GetAt(pos));

	//BOOL bAdjustSize = FALSE; // cppcheck - 사용안됨
	int nOldHeight = 0;
	if (m_bFitItemCount) nOldHeight = GetHeight();

	m_posActiveGroup = pos;

	if (m_bFitItemCount) 
	{
		if (nOldHeight != GetHeight()) AdjustSize();
	}
	Invalidate(FALSE);
}

CString CGroupList::GetActiveGroupName() const
{
	if (!m_posActiveGroup) return _T("");
	return m_listGroup.GetAt(m_posActiveGroup)->strName;
}

BOOL CGroupList::SetActiveGroupName(const CString& strName)
{
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		if (m_listGroup.GetAt(pos)->strName == strName)
		{
			SetActiveGroup(pos);
			return TRUE;
		}
		m_listGroup.GetNext(pos);
	}
	return FALSE;
}

void CGroupList::AddItem(POSITION pos, const CString& strItemName, int idx)
{
	m_listGroup.GetAt(pos)->AddItem(idx, strItemName);
}

void CGroupList::RemoveItemAll(POSITION pos)
{
	m_listGroup.GetAt(pos)->RemoveItemAll();
}

BOOL CGroupList::IsEmpty() const
{
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		if (m_listGroup.GetNext(pos)->items.GetSize() > 0) return FALSE;
	}
	return TRUE;
}

void CGroupList::BeginUpdate()
{
	m_bSuspendUpdate = TRUE;
	m_nHeightBeforeUpdate = GetHeight();
}

void CGroupList::EndUpdate()
{
	m_bSuspendUpdate = FALSE;
	if (GetHeight() != m_nHeightBeforeUpdate) AdjustSize();
	m_nHeightBeforeUpdate = 0;
	// jpahn: 마우스가 움직여야 HitTest 하도록 한다.
	//   마우스가 특정 좌표에 있었는데 그 좌표까지 List가 확장될 경우 
	//   (Update 후 Control 이 마우스 좌표를 포함하게 될 경우)
	//   좌표상의 아이템이 바로 선택되어 버림.
	//   키보드 위주로 작업할 경우 불편할 수 있음.
	//HitTest();
	Invalidate(FALSE);
}

void CGroupList::AdjustSize()
{
	if (!GetSafeHwnd()) return;
	if (m_bSuspendUpdate) return;
	CRect rect;
	GetWindowRect(rect);
	int h = GetHeight();
	SetWindowPos(NULL, 0, 0, rect.Width(), h, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
}

void CGroupList::SetItemCount(int nItemCount)
{
	if (m_nItemCount == nItemCount) return;
	ASSERT(nItemCount >= 0);
	m_nItemCount = nItemCount;
	AdjustSize();
}

int CGroupList::GetCalcItemCount() const 
{
	if (m_bFitItemCount)
	{
		if (!m_posActiveGroup) return 0;
		int nItemCount = (int)m_listGroup.GetAt(m_posActiveGroup)->items.GetSize() + GetGroupCount() - 1;		
		return min(nItemCount, m_nItemCount);
	}
	else
	{
		return m_nItemCount;
	}
}

int CGroupList::GetListGroupRect(POSITION posGroup, CRect& rectGroup) const
{ 
	BOOL bFind = FALSE;
	int y = 0;
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		if (pos == posGroup)
		{
			bFind = TRUE;
			break;
		}

		if (pos == m_posActiveGroup) y += GetListHeight();
		else y += m_nItemHeight;
		y++;
		m_listGroup.GetNext(pos);
	}
	ASSERT(bFind);
	return GetListGroupRect(posGroup, y, rectGroup);
}

int CGroupList::GetListGroupRect(POSITION posGroup, int y, CRect& rectGroup) const
{
	CRect rectClient;
	GetClientRect(rectClient);

	rectGroup.left = rectClient.left;
	rectGroup.top = rectClient.top + y;
	rectGroup.right = rectClient.right;
	if (posGroup == m_posActiveGroup) rectGroup.bottom = rectGroup.top + GetListHeight();
	else rectGroup.bottom = rectGroup.top + m_nItemHeight;
	return rectGroup.bottom + 1; // +1 은 border 
}

void CGroupList::GetGroupRect(const CRect& rectGroup, CRect& rectExecute, CRect& rectExtend) const
{
	rectExecute.SetRect(rectGroup.left, rectGroup.top, rectGroup.right - rectGroup.Height(), rectGroup.bottom);
	rectExtend.SetRect(rectExecute.right, rectGroup.top, rectGroup.right, rectGroup.bottom);
}

void CGroupList::GetListRect(const CRect& rectGroup, CRect& rectItems, CRect& rectScroll) const
{
	if (HasScroll(m_posActiveGroup)) 
	{
		rectItems.SetRect(rectGroup.left, rectGroup.top, rectGroup.right - m_nScrollWidth, rectGroup.bottom);
		rectScroll.SetRect(rectItems.right, rectGroup.top, rectGroup.right, rectGroup.bottom);
	}
	else
	{
		rectItems.SetRect(rectGroup.left, rectGroup.top, rectGroup.right, rectGroup.bottom);
		rectScroll.SetRect(0,0,0,0);
	}
}

void CGroupList::GetListItemRect(int idx, const CRect& rectItems, CRect& rectItem) const
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);	
	int top = rectItems.top + ((idx - pGroup->nScroll) * m_nItemHeight);
	rectItem.SetRect(rectItems.left, top, rectItems.right, top + m_nItemHeight);
}

void CGroupList::GetListScrollRect(const CRect& rectScroll, CRect& rectScrollBar, BOOL bDraw) const
{
	// bDraw = TRUE  : 그려야할 ScrollBar의 Rect를 구함
	// bDraw = FALSE : 논리적인 ScrollBar의 Rect. (충돌검사 및 Scroll 계산용)
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);

	int w = rectScroll.Width();
	int h = rectScroll.Height();
	int nListItemCount = GetListItemCount();

	double dHeightRate = (double)nListItemCount / (double)pGroup->items.GetSize();
	int barrh = (int)(dHeightRate * h);
	if (barrh < (int)(1.5 * w)) barrh = (int)(1.5 * w);
	if (barrh >= h) barrh = (w < h) ? w : (int)(h * 0.5);

	double dLocationRate = (double)pGroup->nScroll / (double)(pGroup->items.GetSize() - nListItemCount);
	int nRange = h - barrh;

	int barl = rectScroll.left;
	int bart = rectScroll.top + (int)(dLocationRate * nRange);
	int barw = w;
	int barh = barrh;

	rectScrollBar.SetRect(barl, bart, barl + barw, bart + barh);

	if (bDraw)
	{
		if (m_bMouseDrag)
		{
			CPoint ptScroll(m_ptMouse.x - rectScroll.left, m_ptMouse.y - rectScroll.top);
			double dScrollRate = GetScrollRate(h, barh, ptScroll);
			rectScrollBar.top = rectScroll.top + (int)(dScrollRate * nRange);
			rectScrollBar.bottom = rectScrollBar.top + barh;
		}

		int s = (w - m_nScrollBarWidth) / 2;
		rectScrollBar.top += s;
		rectScrollBar.left += s;
		rectScrollBar.right -= s;
		rectScrollBar.bottom -= s;
	}
}

BOOL CGroupList::HasScroll(POSITION pos) const
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(pos);
	return (pGroup->items.GetSize() > GetListItemCount());
}

void CGroupList::HitInfoChanged()
{
	m_bLButtonClick = FALSE;
	Invalidate(FALSE);
}

void CGroupList::HitTest()
{
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	m_ptMouse = pt;
	HitTest(pt);
}

void CGroupList::HitTest(const CPoint& pt)
{
	THitTestInfo info;
	HitTest(pt, info);

	switch (info.type)
	{
	case HIT_ITEM:
		{
			ASSERT(info.pos == m_posActiveGroup);
			TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
			if (m_hitInfo.type == info.type && m_hitInfo.pos == info.pos && m_hitInfo.idx == info.idx && pGroup->nSelectedItem == info.idx) return;
			m_hitInfo = info;
			pGroup->nSelectedItem = info.idx;
			HitInfoChanged();
		}
		break;
	default:
		if (m_hitInfo.type == info.type && m_hitInfo.pos == info.pos) return;
		m_hitInfo = info;
		HitInfoChanged();
		break;
	}
}

void CGroupList::HitTest(const CPoint& pt, THitTestInfo& info)
{
	info.type = HIT_NONE;

	CRect rectGroup;
	POSITION pos = FindGroup(pt, rectGroup);
	if (!pos) return;
	info.pos = pos;

	if (pos != m_posActiveGroup)
	{
		CRect rectExecute;
		CRect rectExtend;
		GetGroupRect(rectGroup, rectExecute, rectExtend);
		if (rectExecute.PtInRect(pt))
		{
			info.type = HIT_GROUP_EXECUTE;
			info.rect = rectExecute;
		}
		else if (rectExtend.PtInRect(pt))
		{
			info.type = HIT_GROUP_EXTEND;
			info.rect = rectExtend;
		}
		else ASSERT(0);
	}
	else
	{
		CRect rectItems;
		CRect rectScroll;
		GetListRect(rectGroup, rectItems, rectScroll);
		if (rectItems.PtInRect(pt))
		{
			int idx = GetListItemIndex(rectItems, CPoint(pt.x - rectItems.left, pt.y - rectItems.top));
			if (idx >= 0) 
			{
				GetListItemRect(idx, rectItems, info.rect);
				info.type = HIT_ITEM;
				info.idx = idx;
			}
			else
			{
				info.type = HIT_ITEM_EMPTY;
				info.rect = rectItems;
			}
		}
		else if (rectScroll.PtInRect(pt))
		{
			CRect rectScrollBar;
			GetListScrollRect(rectScroll, rectScrollBar, FALSE);
			if (pt.y < rectScrollBar.top) 
			{
				info.type = HIT_SCROLL_PGUP;
				info.rect = rectScroll;
			}
			else if (pt.y > rectScrollBar.bottom) 
			{
				info.type = HIT_SCROLL_PGDN;
				info.rect = rectScroll;
			}
			else
			{
				info.type = HIT_SCROLL_BAR;
				info.rect = rectScrollBar;
			}
		}
		else ASSERT(0);
	}
}

POSITION CGroupList::FindGroup(const CPoint& pt, CRect& rectGroup) const
{
	CRect rect;
	GetClientRect(rect);
	if (pt.x < rect.left || pt.x > rect.right) return NULL;

	int y = 0;
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		y = GetListGroupRect(pos, y, rectGroup);
		if (rectGroup.PtInRect(pt)) return pos;
		if (pt.y == y) return NULL;
		m_listGroup.GetNext(pos);    
	}

	return NULL;
}

int CGroupList::GetListItemIndex(const CRect& rectItems, const CPoint& ptItems) const
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
	if (pGroup->nScroll < 0) return -1;

	int idx = ptItems.y / m_nItemHeight + pGroup->nScroll;
	if (idx < 0) return -1;
	if (idx >= pGroup->items.GetSize()) return -1;

	return idx;
}

void CGroupList::ScrollDrag(const CPoint& pt)
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
	CRect rectGroup;
	GetListGroupRect(m_posActiveGroup, rectGroup);
	CRect rectItems;
	CRect rectScroll;
	GetListRect(rectGroup, rectItems, rectScroll);
	CRect rectScrollBar;
	GetListScrollRect(rectScroll, rectScrollBar, FALSE);  
	CPoint ptScroll(pt.x - rectScroll.left, pt.y - rectScroll.top);

	double dRate = GetScrollRate(rectScroll.Height(), rectScrollBar.Height(), ptScroll);
	int nListItemCount = GetListItemCount();
	int nScrollRange = (int)pGroup->items.GetSize() - nListItemCount;
	if (nScrollRange < 0) nScrollRange = 0;
	pGroup->nScroll = (int)(nScrollRange * dRate);

	int nSelectedItemMax = pGroup->nScroll + nListItemCount - 1;
	if (pGroup->nSelectedItem < pGroup->nScroll) pGroup->nSelectedItem = pGroup->nScroll;
	if (pGroup->nSelectedItem > nSelectedItemMax) pGroup->nSelectedItem = nSelectedItemMax;

	InvalidateRect(rectGroup);
}

void CGroupList::Scroll(int scroll)
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);

	int nListItemCount = GetListItemCount();
	int nScrollRange = (int)pGroup->items.GetSize() - nListItemCount;
	if (nScrollRange < 0) nScrollRange = 0;

	pGroup->nScroll += scroll;
	if (pGroup->nScroll < 0) pGroup->nScroll = 0;
	if (pGroup->nScroll > nScrollRange) pGroup->nScroll = nScrollRange;

	int nSelectedItemMax = pGroup->nScroll + nListItemCount - 1;
	if (pGroup->nSelectedItem < pGroup->nScroll) pGroup->nSelectedItem = pGroup->nScroll;
	if (pGroup->nSelectedItem > nSelectedItemMax) pGroup->nSelectedItem = nSelectedItemMax;

	CRect rectGroup;
	GetListGroupRect(m_posActiveGroup, rectGroup);
	InvalidateRect(rectGroup);
}

double CGroupList::GetScrollRate(int rectScrollHeight, int rectScrollBarHeight, const CPoint& ptScroll) const
{
	int y_scroll = ptScroll.y;
	if (abs(m_ptScrollMouseDragStart.x - ptScroll.x) > 150) y_scroll = m_ptScrollMouseDragStart.y;
	int nRange = rectScrollHeight - rectScrollBarHeight;
	ASSERT(nRange > 0);
	int nPos = y_scroll - m_ptScrollBarMouseDragStart.y;
	double dRate = (double)nPos / (double)nRange;
	if (dRate < 0.0) dRate = 0.0;
	if (dRate > 1.0) dRate = 1.0;
	return dRate;
}

int CGroupList::GetSelectedItem() const
{
	if (!m_posActiveGroup) return -1;
	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
	return pGroup->nSelectedItem;
}

BOOL CGroupList::SetSelectItem(int idx, BOOL bRelativeIdx, BOOL bScroll)
{
	if (!m_posActiveGroup) return FALSE;

	TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);

	int nSelectedItem;
	if (bRelativeIdx) nSelectedItem = pGroup->nSelectedItem + idx;
	else nSelectedItem = idx;

	if (nSelectedItem < 0) nSelectedItem = 0;
	if (nSelectedItem >= (int)pGroup->items.GetSize()) nSelectedItem = (int)pGroup->items.GetSize() - 1;
	if (nSelectedItem == pGroup->nSelectedItem) return FALSE;
	pGroup->nSelectedItem = nSelectedItem;

	if (bScroll)
	{
		int nListItemCount = GetListItemCount();
		if (nSelectedItem < pGroup->nScroll) pGroup->nScroll = nSelectedItem;
		if (nSelectedItem >= pGroup->nScroll + nListItemCount) pGroup->nScroll = nSelectedItem - nListItemCount + 1;
	}

	CRect rectGroup;
	GetListGroupRect(m_posActiveGroup, rectGroup);
	InvalidateRect(rectGroup);

	return TRUE;
}

void CGroupList::ActiveNextGroup()
{
	if (!m_posActiveGroup) return;
	POSITION posNextGroup = m_posActiveGroup;
	m_listGroup.GetNext(posNextGroup);
	if (!posNextGroup) posNextGroup = m_listGroup.GetHeadPosition();
	SetActiveGroup(posNextGroup);
}

int CGroupList::DrawList(CDC* pDC, POSITION pos, int y)
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(pos);

	CRect rect;
	y = GetListGroupRect(pos, y, rect);
	pDC->FillSolidRect(rect, m_clrListBack);

	if (pGroup->nScroll >= 0)
	{
		CRect rectItems;
		CRect rectScroll;
		GetListRect(rect, rectItems, rectScroll);
		DrawListItems(pDC, pGroup, rectItems);
		if (rectScroll.Width() > 0) DrawListScroll(pDC, pGroup, rectScroll);
	}

	return y;
}

void CGroupList::DrawListItems(CDC* pDC, TGroupListGroup* pGroup, const CRect& rect)
{
	int nDrawItemCount = GetListItemCount();
	CRect rectItem;
	BOOL bSelected;
	int idx = pGroup->nScroll;
	for (int i = 0; i < nDrawItemCount; i++)
	{
		if (idx == pGroup->items.GetSize()) break;
		bSelected = (idx == pGroup->nSelectedItem);
		GetListItemRect(idx, rect, rectItem);
		DrawListItem(pDC, &pGroup->items[idx], bSelected, rectItem);
		idx++;
	}
}

void CGroupList::DrawListItem(CDC* pDC, TGroupListItem* pItem, BOOL bSelected, const CRect& rect)
{
	if (bSelected)
	{
		CPen pen(PS_SOLID, 1, m_clrListSelectBorder);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(rect);
		pDC->SelectObject(pOldPen);
		DrawGradient(pDC, CRect(rect.left+1, rect.top+1, rect.right-1, rect.bottom-1), m_clrListSelectBack1, m_clrListSelectBack2);
	}

	DrawImage(pDC, pItem->idx, CRect(rect.left, rect.top, rect.left + rect.Height(), rect.bottom));

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_clrListText);
	pDC->DrawText(pItem->strName, CRect(rect.left + rect.Height(), rect.top, rect.right, rect.bottom), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CGroupList::DrawListScroll(CDC* pDC, TGroupListGroup* pGroup, const CRect& rect)
{
	pDC->FillSolidRect(rect, m_clrScrollBarBack);  

	CRect rectScrollBar;
	GetListScrollRect(rect, rectScrollBar, TRUE);
	int round = (m_nScrollBarWidth / 2) + 1;
	CPoint ptRound(round, round);

	CBrush brush;
	brush.CreateSolidBrush(m_hitInfo.type == HIT_SCROLL_BAR ? m_clrScrollBarOver : m_clrScrollBar);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->RoundRect(rectScrollBar, ptRound);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

int CGroupList::DrawGroup(CDC* pDC, POSITION pos, int y)
{
	TGroupListGroup* pGroup = m_listGroup.GetAt(pos);
	TGroupListItem* pItem = NULL;
	if (pGroup->nSelectedItem >= 0) pItem = &pGroup->items[pGroup->nSelectedItem];

	CRect rect;
	y = GetListGroupRect(pos, y, rect);
	pDC->FillSolidRect(rect, m_clrGroupBack);

	CRect rectExecute;
	CRect rectExtend;
	GetGroupRect(rect, rectExecute, rectExtend);
	BOOL bExecuteOver = (m_hitInfo.type == HIT_GROUP_EXECUTE && m_hitInfo.pos == pos);
	BOOL bExetendOver = (m_hitInfo.type == HIT_GROUP_EXTEND && m_hitInfo.pos == pos);
	DrawGroupExecute(pDC, pItem, bExecuteOver, rectExecute);
	DrawGroupExtendBtn(pDC, bExetendOver, rectExtend);

	return y;
}

void CGroupList::DrawGroupExecute(CDC* pDC, TGroupListItem* pItem, BOOL bMouseOver, const CRect& rect)
{
	if (!pItem) return;

	int w = rect.Width();
	int h = rect.Height();
	COLORREF clrShadow = CColorLib::MultipleColor(m_clrGroupBack, 0.75);

	CDC dc;
	VERIFY(dc.CreateCompatibleDC(pDC));
	CBitmap bmp;
	VERIFY(bmp.CreateCompatibleBitmap(pDC, w, h));
	CBitmap* pOldBmp = dc.SelectObject(&bmp);
	CFont* pOldFont = dc.SelectObject(GetFont());

	dc.FillSolidRect(0, 0, w, h, m_clrGroupBack);
	DrawImage(&dc, pItem->idx, CRect(0, 0, h, h));
	DrawGroupText(&dc, pItem->strName, CRect(h, 0, w, h), m_clrGroupText, clrShadow);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (bMouseOver ? 255 : m_nGroupDeactiveAlpha);
	bf.AlphaFormat = 0;
	VERIFY(pDC->AlphaBlend(rect.left, rect.top, w, h, &dc, 0, 0, w, h, bf));

	dc.SelectObject(pOldBmp);
	dc.SelectObject(pOldFont);
}

void CGroupList::DrawGroupText(CDC* pDC, const CString& str, const CRect& rect, COLORREF cf, COLORREF cb)
{
	pDC->SetBkMode(TRANSPARENT);

	CRect rectText(rect);
	rectText.left += 1;
	rectText.top += 2;
	pDC->SetTextColor(cb);
	pDC->DrawText(str, rectText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	rectText.left -= 1;
	rectText.top -= 2;
	pDC->SetTextColor(cf);
	pDC->DrawText(str, rectText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CGroupList::DrawGroupExtendBtn(CDC* pDC, BOOL bMouseOver, const CRect& rect)
{
	int w = rect.Width();
	int h = rect.Height();
	COLORREF clrShadow = CColorLib::MultipleColor(m_clrGroupBack, 0.75);

	CDC dc;
	VERIFY(dc.CreateCompatibleDC(pDC));
	CBitmap bmp;
	VERIFY(bmp.CreateCompatibleBitmap(pDC, w, h));
	CBitmap* pOldBmp = dc.SelectObject(&bmp);

	dc.FillSolidRect(0, 0, w, h, m_clrGroupBack);
	DrawGroupExtendBtn(&dc, CRect(0, 0, w, h), m_clrGroupText, clrShadow);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (bMouseOver ? 255 : m_nGroupDeactiveAlpha);
	bf.AlphaFormat = 0;
	VERIFY(pDC->AlphaBlend(rect.left, rect.top, w, h, &dc, 0, 0, w, h, bf));
	dc.SelectObject(pOldBmp);
}

void CGroupList::DrawGroupExtendBtn(CDC* pDC, const CRect& rect, COLORREF cf, COLORREF cb)
{
	int h = rect.Height();
	int s = (h - m_nExtendBtnWidth) / 2;

	CPoint pt;
	pt.x  = rect.right - s - m_nExtendBtnWidth + 1;
	pt.y = s + 1;
	DrawGroupExtendSymbol(pDC, pt, cb);

	pt.x -= 1;
	pt.y -= 1;
	DrawGroupExtendSymbol(pDC, pt, cf);
}

void CGroupList::DrawGroupExtendSymbol(CDC* pDC, const CPoint& pt, COLORREF c)
{
	int s = (m_nExtendBtnWidth / 2) - (m_nExtendBtnThick / 2);
	pDC->FillSolidRect(pt.x, pt.y + s, m_nExtendBtnWidth, m_nExtendBtnThick, c);
	pDC->FillSolidRect(pt.x + s, pt.y, m_nExtendBtnThick, m_nExtendBtnWidth, c);
}

void CGroupList::DrawImage(CDC* pDC, int idx, const CRect& rect)
{
	if (!m_pImageList) return;
	if (idx < 0) return;

	IMAGEINFO info;
	ZeroMemory(&info, sizeof(info));
	if (!m_pImageList->GetImageInfo(idx, &info)) return;
	int w = info.rcImage.right - info.rcImage.left;
	int h = info.rcImage.bottom - info.rcImage.top;

	CPoint pt;
	pt.x = rect.left + (int)( (rect.Width() - w) * 0.5 );
	pt.y = rect.top + (int)( (rect.Height() - h) * 0.5 );

	m_pImageList->Draw(pDC, idx, pt, ILD_NORMAL);
}

void CGroupList::DrawGradient(CDC* pDC, const CRect& rect, COLORREF c1, COLORREF c2)
{
	TRIVERTEX vert[2];
	GRADIENT_RECT grect;

	vert[0].x      = rect.left;
	vert[0].y      = rect.top;

	vert[0].Red    = (COLOR16)((GetRValue(c1) / 255.0) * 65535);
	vert[0].Green  = (COLOR16)((GetGValue(c1) / 255.0) * 65535);
	vert[0].Blue   = (COLOR16)((GetBValue(c1) / 255.0) * 65535);
	vert[0].Alpha  = 0x0000;

	vert[1].x      = rect.right;
	vert[1].y      = rect.bottom;

	vert[1].Red    = (COLOR16)((GetRValue(c2) / 255.0) * 65535);
	vert[1].Green  = (COLOR16)((GetGValue(c2) / 255.0) * 65535);
	vert[1].Blue   = (COLOR16)((GetBValue(c2) / 255.0) * 65535);
	vert[1].Alpha  = 0x0000;

	grect.UpperLeft  = 0;
	grect.LowerRight = 1;

	GradientFill(pDC->m_hDC, vert, 2, &grect, 1, GRADIENT_FILL_RECT_V);
}

void CGroupList::SendNotifyMsgSizeChanged(int cx, int cy)
{
	CWnd* parent = GetParent();
	if (!parent) return;

	NMHDR_GL_SIZE_CHANGED nmhdr;
	nmhdr.hwndFrom = GetSafeHwnd();
	nmhdr.idFrom = GetDlgCtrlID();
	nmhdr.code = NM_GL_SIZE_CHANGED;
	nmhdr.cx = cx;
	nmhdr.cy = cy;
	parent->SendNotifyMessage(WM_NOTIFY, nmhdr.idFrom, (LPARAM)(&nmhdr));
}

void CGroupList::SendNotifyMsgItem(int code, POSITION pos)
{
	CWnd* parent = GetParent();
	if (!parent) return;

	if (!pos) return;
	TGroupListGroup* pGroup = m_listGroup.GetAt(pos);
	if (pGroup->nSelectedItem == -1) return;
	CString strItem = GetExecuteName(pGroup->items[pGroup->nSelectedItem].strName);

	NMHDR_GL_EXECUTE nmhdr;
	nmhdr.hwndFrom = GetSafeHwnd();
	nmhdr.idFrom = GetDlgCtrlID();
	nmhdr.code = code;
	nmhdr.strItem = strItem;
	parent->SendNotifyMessage(WM_NOTIFY, nmhdr.idFrom, (LPARAM)(&nmhdr));
}

BOOL CGroupList::HandleMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_DOWN:
			if (SetSelectItem(1, TRUE)) m_bNeedHitTest = TRUE;
			return TRUE;
		case VK_UP:
			if (SetSelectItem(-1, TRUE)) m_bNeedHitTest = TRUE;
			return TRUE;
		case VK_PRIOR:
			if (m_posActiveGroup) 
			{
				TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
				if (pGroup->nSelectedItem == pGroup->nScroll) 
				{
					if (SetSelectItem(-GetListItemCount(), TRUE)) m_bNeedHitTest = TRUE;
				}
				else 
				{
					if (SetSelectItem(pGroup->nScroll, FALSE)) m_bNeedHitTest = TRUE;
				}
			}
			return TRUE;
		case VK_NEXT:
			if (m_posActiveGroup) 
			{
				TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
				int nScrollBottom = pGroup->nScroll + GetListItemCount() - 1;
				if (pGroup->nSelectedItem == nScrollBottom) 
				{
					if (SetSelectItem(GetListItemCount(), TRUE)) m_bNeedHitTest = TRUE;
				}
				else 
				{
					if (SetSelectItem(nScrollBottom, FALSE)) m_bNeedHitTest = TRUE;
				}
			}
			return TRUE;
		case VK_HOME:
			if (SetSelectItem(0, FALSE)) m_bNeedHitTest = TRUE;
			return TRUE;
		case VK_END:
			if (m_posActiveGroup) 
			{
				TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup);
				if (SetSelectItem((int)pGroup->items.GetSize() - 1, FALSE)) m_bNeedHitTest = TRUE;
			}
			return TRUE;
		case VK_TAB:
			ActiveNextGroup();
			HitTest();
			return TRUE;
		case VK_RETURN:
		case VK_SPACE:
			SendNotifyMsgItem(NM_GL_EXECUTE, m_posActiveGroup);
			return TRUE;
		case VK_F1:
			SendNotifyMsgItem(NM_GL_HELP, m_posActiveGroup);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGroupList::PreTranslateMessage(MSG* pMsg)
{
	if (HandleMessage(pMsg)) return TRUE;
	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGroupList::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SETFONT)
	{
		m_hFont = (HFONT)wParam;
	}
	else if  (message == WM_GETFONT)
	{
		return (LRESULT)m_hFont;
	}

	return CWnd::WindowProc(message, wParam, lParam);
}

int CGroupList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

// 	if ( CBCGPVisualManager::GetInstance()->IsKindOf(RUNTIME_CLASS(MVisualManager)) )
// 	{
// 		((MVisualManager*)CBCGPVisualManager::GetInstance())->InitGroupListVisual(this);
// 	}

	m_trackMouse.cbSize = sizeof(m_trackMouse);
	m_trackMouse.dwFlags = TME_LEAVE;
	m_trackMouse.dwHoverTime = HOVER_DEFAULT;
	m_trackMouse.hwndTrack = GetSafeHwnd();

	return 0;
}

void CGroupList::OnDestroy()
{
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		TGroupListGroup* pGroup = m_listGroup.GetNext(pos);
		delete pGroup;
	}
	m_listGroup.RemoveAll();
	CWnd::OnDestroy();
}

void CGroupList::OnSize(UINT nType, int cx, int cy)
{
	//int height = GetHeight();
	//if (cy != height) 
	//{
	//	AdjustSize();
	//	return;
	//}
	SendNotifyMsgSizeChanged(cx, cy);

	CWnd::OnSize(nType, cx, cy);
}

void CGroupList::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CGroupList::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CRect rect;
	rect.left = lpwndpos->x;
	rect.top = lpwndpos->y;
	rect.right = lpwndpos->x + lpwndpos->cx;
	rect.bottom = lpwndpos->y + GetHeight();
	AdjustWindowRect(rect, GetStyle(), FALSE);
	lpwndpos->cy = rect.Height();
	CWnd::OnWindowPosChanging(lpwndpos);
}

BOOL CGroupList::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CGroupList::OnPaint()
{
	CPaintDC dc(this);

	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();
	
	CFont* pOldFont = pDC->SelectObject(GetFont());

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, m_clrBorder);

	if (IsEmpty())
	{
		pDC->FillSolidRect(rect, m_clrListBack);
		return;
	}

	int y = 0;
	POSITION pos = m_listGroup.GetHeadPosition();
	while (pos)
	{
		if (pos == m_posActiveGroup) y = DrawList(pDC, pos, y);
		else y = DrawGroup(pDC, pos, y);
		m_listGroup.GetNext(pos);
	}

	pDC->SelectObject(pOldFont);
}

void CGroupList::OnNcPaint()
{
	CWindowDC wndDC(this);
	CDC* pDC = &wndDC;

	CRect rt;
	GetWindowRect(&rt);
	rt.NormalizeRect();
	rt.OffsetRect(-rt.left, -rt.top);

	COLORREF clrBorder = RGB(32,32,32);
	pDC->FillSolidRect(rt.left, rt.top, rt.Width(), 1, clrBorder);
	pDC->FillSolidRect(rt.left, rt.bottom - 1, rt.Width(), 1, clrBorder);
	pDC->FillSolidRect(rt.left, rt.top, 1, rt.Height(), clrBorder);
	pDC->FillSolidRect(rt.right - 1, rt.top, 1, rt.Height(), clrBorder);
}

void CGroupList::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_ptMouse == point) 
	{
		CWnd::OnMouseMove(nFlags, point); 
		return; 
	}
	m_ptMouse = point;

	if (!m_bMouseOver)
	{
		::_TrackMouseEvent(&m_trackMouse);
		m_bMouseOver = TRUE;
		Invalidate(FALSE);
	}

	if (m_bMouseDrag)
	{
		ScrollDrag(point);
	}
	else
	{
		HitTest(point);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CGroupList::OnMouseLeave()
{
	m_bMouseOver = FALSE;
	Invalidate(FALSE);

	HitTest();

	CWnd::OnMouseLeave();
}

void CGroupList::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	CWnd::OnLButtonDown(nFlags, point);

	if (m_bNeedHitTest)
	{
		m_bNeedHitTest = FALSE;
		HitTest(point);
	}

	m_bLButtonClick = TRUE;
	if (m_hitInfo.type == HIT_SCROLL_BAR) 
	{
		SetCapture();

		m_bMouseDrag = TRUE;
		//TGroupListGroup* pGroup = m_listGroup.GetAt(m_posActiveGroup); // cppcheck - 사용안됨
		CRect rectGroup;
		GetListGroupRect(m_posActiveGroup, rectGroup);
		CRect rectItems;
		CRect rectScroll;
		GetListRect(rectGroup, rectItems, rectScroll);
		CRect rectScrollBar;
		GetListScrollRect(rectScroll, rectScrollBar, FALSE);   
		m_ptScrollMouseDragStart.x = point.x - rectScroll.left;
		m_ptScrollMouseDragStart.y = point.y - rectScroll.top;   
		m_ptScrollBarMouseDragStart.x = point.x - rectScrollBar.left;
		m_ptScrollBarMouseDragStart.y = point.y - rectScrollBar.top; 
	}
	else if (m_hitInfo.type == HIT_SCROLL_PGUP) 
	{
		Scroll(-GetListItemCount());
		HitTest(point);
	}
	else if (m_hitInfo.type == HIT_SCROLL_PGDN) 
	{
		Scroll(GetListItemCount());
		HitTest(point);
	}
}

void CGroupList::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);

	if (m_bMouseDrag)
	{
		m_bMouseDrag = FALSE;
		m_ptScrollMouseDragStart.x = 0;
		m_ptScrollMouseDragStart.y = 0;
		m_ptScrollBarMouseDragStart.x = 0;
		m_ptScrollBarMouseDragStart.y = 0;
		ReleaseCapture();
	}

	if (m_bLButtonClick)
	{
		switch (m_hitInfo.type)
		{
		case HIT_NONE: break;
		case HIT_ITEM_EMPTY: break;
		case HIT_ITEM:
			SendNotifyMsgItem(NM_GL_EXECUTE, m_posActiveGroup);
			break;
		case HIT_SCROLL_BAR:
			HitTest(point);
			Invalidate(FALSE);
			break;
		case HIT_SCROLL_PGUP:
		case HIT_SCROLL_PGDN:
			// MouseDown 에서 처리
			break;
		case HIT_GROUP_EXECUTE:
			SendNotifyMsgItem(NM_GL_EXECUTE, m_hitInfo.pos);
			break;
		case HIT_GROUP_EXTEND:
			SetActiveGroup(m_hitInfo.pos);
			HitTest(point);
			Invalidate(FALSE);
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
}

BOOL CGroupList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CPoint ptClient(pt);
	ScreenToClient(&ptClient);

	if (m_bNeedHitTest)
	{
		m_bNeedHitTest = FALSE;
		HitTest(ptClient);
	}

	if (m_hitInfo.type == HIT_ITEM || m_hitInfo.type == HIT_ITEM_EMPTY || 
		m_hitInfo.type == HIT_SCROLL_BAR || m_hitInfo.type == HIT_SCROLL_PGUP || m_hitInfo.type == HIT_SCROLL_PGDN)
	{
		int idx = -3 * (zDelta / WHEEL_DELTA);
		Scroll(idx);
		HitTest(ptClient);
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CGroupList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGroupList::OnTimer(UINT_PTR nIDEvent)
{
	CWnd::OnTimer(nIDEvent);
}

void CGroupList::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
}