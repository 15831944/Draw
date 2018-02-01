#include "stdafx.h"
#include "MGridCheckItem.h"

#include "MGridRow.h"
#include "MTable.h"
#include "MGridColumnsInfo.h"

using namespace mit;
using namespace mit::frx;

class MFriendGridCtrl : public CBCGPGridCtrl
{
	friend class MGridItem;
	friend class MGridCheckItem;
};

// InplaceWnd 가 다른 경로를 통해 생성/파괴 되는 것을 방지.
// 오로지 ToggleValue() 함수를 통해서만 생성/파괴한다.
class CToggleValue
{
	BOOL& m_bToggleValue;
public:
	CToggleValue(BOOL& bToggleValue) : m_bToggleValue(bToggleValue) { m_bToggleValue = TRUE; }
	~CToggleValue() { m_bToggleValue = FALSE; }
};

IMPLEMENT_SERIAL (MGridCheckItem, MGridItem, VERSIONABLE_SCHEMA | 1)

MGridCheckItem::MGridCheckItem () :
	MGridItem (_variant_t (false), 0),
	m_bToggleValue(FALSE)
{
}
//*****************************************************************************************
MGridCheckItem::~MGridCheckItem()
{
}

BOOL MGridCheckItem::ToggleValue()
{
	CToggleValue toggle(m_bToggleValue);

	static int i = 0; i++;
	CString str; str.Format(_T("ToggleValue(), %d\n"), i);
	OutputDebugString(str);

	MFriendGridCtrl* pWndList = (MFriendGridCtrl*)GetOwnerList ();
	ASSERT_VALID (pWndList);
	ASSERT(!GetInPlaceWnd());
	{
		MTBNoUpdateWindow noUpdate(pWndList->m_bNoUpdateWindow);
		pWndList->SetBeginEditReason(CBCGPGridCtrl::BeginEdit_MouseClick | CBCGPGridCtrl::BeginEdit_MouseDblClick);
		ASSERT_VALID(m_pGridRow);
		if (!pWndList->EditItem(m_pGridRow)) return FALSE;
	}
	bool bOldValue = (bool)GetValue ();
	GetInPlaceWnd()->m_varValue = !bOldValue;

	pWndList->SetEndEditReason(CBCGPGridCtrl::EndEdit_AutoApply);
	ASSERT_VALID(m_pGridRow);
	return pWndList->EndEditItem();
}

void MGridCheckItem::Init()
{
}

void MGridCheckItem::SetFlags()
{
	m_dwFlags = BCGP_GRID_ITEM_VCENTER;
}
//*****************************************************************************************
BOOL MGridCheckItem::OnEdit(LPPOINT lptClick)
{
	if (!m_bToggleValue) return FALSE;

	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);
	if (!m_bAllowEdit) return FALSE;

	CRect rectEdit;
	BOOL bDefaultFormat = FALSE;
	m_pWndInPlace = CreateInPlaceEdit (rectEdit, bDefaultFormat);
	m_bInPlaceEdit = TRUE;

	return TRUE;
}
//*****************************************************************************
BOOL MGridCheckItem::OnEndEdit ()
{
	if (!m_bToggleValue) return FALSE;

	ASSERT_VALID (this);

	m_bInPlaceEdit = FALSE;
	OnDestroyWindow ();

	OnEndInplaceEdit ();
	return TRUE;
}
//*****************************************************************************************
CWnd* MGridCheckItem::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pGridRow);

	CBCGPGridCtrl* pWndList = GetOwnerList();
	ASSERT_VALID(pWndList);

	MInplaceWnd* pWnd = new MInplaceWnd();
	pWnd->Create(WS_CHILD | WS_DISABLED, pWndList, 1); // #define	BCGPGRIDCTRL_ID_INPLACE	1

	return pWnd;
}
//*****************************************************************************************
void MGridCheckItem::AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectSpin)
{
	rectEdit.SetRectEmpty();
	rectSpin.SetRectEmpty();
}
//*****************************************************************************************
BOOL MGridCheckItem::OnUpdateValue ()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndInPlace);

	MInplaceWnd* pInplaceWnd = GetInPlaceWnd();
	BOOL bIsChanged = pInplaceWnd->m_varValue != m_varValue;
	BOOL bUpdateData = bIsChanged && CanUpdateData();

	if (bUpdateData)
	{
		ASSERT(pInplaceWnd->m_varValue.vt == VT_BOOL);
		m_varValue = pInplaceWnd->m_varValue;
		SetItemChanged ();
	}

	return TRUE;
}
//*****************************************************************************************
void MGridCheckItem::SetLabel(const CString& strLabel)
{
	m_strCheckLabel = strLabel;
}
//*****************************************************************************************
void MGridCheckItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	
	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);

	CRect rectCheck = rect;
	
	rectCheck.DeflateRect (0, 2);

	int nWidth = pWndList->GetButtonWidth ();

	if (m_strCheckLabel.IsEmpty())
	{
		rectCheck.left = rectCheck.CenterPoint ().x - nWidth / 2;
	}

	rectCheck.right = rectCheck.left + nWidth;

	CBCGPVisualManager::GetInstance()->OnDrawCheckBox (pDC, rectCheck, FALSE, (bool)m_varValue, m_bEnabled);

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	if (!m_strCheckLabel.IsEmpty())
	{
		CRect rectLabel = rect;
		rectLabel.left = rectCheck.right + 2;

		pWndList->DoDrawText (pDC, m_strCheckLabel, rectLabel, DT_NOPREFIX | DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}
//*****************************************************************************************
void MGridCheckItem::OnPrintValue (CDC* pDC, CRect rect)
{
	const bool bVal = (bool) m_varValue;
	if (!bVal)
	{
		return;
	}

	CBCGPGridCtrl* pWndList = GetOwnerList ();
	ASSERT_VALID (pWndList);

	const CRect& rectClip = pWndList->GetPrintParams().m_pageInfo.m_rectPageItems;
	const CSize& szOne = pWndList->GetPrintParams().m_pageInfo.m_szOne;

	CRect rectCheck = rect;

	rectCheck.right = rectCheck.left + pWndList->GetPrintParams().m_nButtonWidth;
	rectCheck.DeflateRect (szOne.cx, szOne.cy);
	rectCheck.top += szOne.cy;
	rectCheck.left += szOne.cx;

	rectCheck.NormalizeRect ();
	if (rectCheck.IntersectRect (&rectCheck, &rectClip))
	{
		CBCGPMenuImages::Draw (pDC, CBCGPMenuImages::IdCheck, rectCheck, CBCGPMenuImages::ImageBlack, rectCheck.Size());
	}
}
//*****************************************************************************************
BOOL MGridCheckItem::PushChar (UINT nChar)
{
	ASSERT_VALID (m_pGridRow);

	if (nChar == VK_SPACE && IsEnabled () && !IsReadOnly())
	{
		return ToggleValue();
	}
	
	return FALSE;
}
//*****************************************************************************************
BOOL MGridCheckItem::OnClickValue (UINT uiMsg, CPoint point)
{
	ASSERT_VALID (m_pGridRow);
	MFriendGridCtrl* pWndList = (MFriendGridCtrl*)GetOwnerList ();
	ASSERT_VALID (pWndList);

	if ((uiMsg == WM_LBUTTONDOWN || uiMsg == WM_RBUTTONDOWN) &&
		pWndList->AllowInPlaceEdit () && !IsReadOnly ())
	{
		if (!m_strCheckLabel.IsEmpty())
		{
			CRect rectCheck = m_Rect;
			rectCheck.right = rectCheck.left + pWndList->GetButtonWidth ();

			if (!rectCheck.PtInRect(point))
			{
				return MGridItem::OnClickValue (uiMsg, point);
			}
		}

		return ToggleValue();
	}

	return MGridItem::OnClickValue (uiMsg, point);
}
//*****************************************************************************************
BOOL MGridCheckItem::OnDblClick (CPoint point)
{
	return MGridItem::OnDblClick (point);
}
//*****************************************************************************************
BOOL MGridCheckItem::ReadFromArchive(CArchive& ar, BOOL bTestMode)
{
	BOOL bReadResult = MGridItem::ReadFromArchive(ar, bTestMode);

	CString strCheckLabel;
	ar >> strCheckLabel;

	if (!bTestMode)
	{
		m_strCheckLabel = strCheckLabel;
	}

	return bReadResult;
}
//*****************************************************************************************
void MGridCheckItem::WriteToArchive(CArchive& ar)
{
	MGridItem::WriteToArchive(ar);

	ar << m_strCheckLabel;
}
//*****************************************************************************************
BOOL MGridCheckItem::SetACCData (CWnd* pParent, CBCGPAccessibilityData& data)
{
	MGridItem::SetACCData (pParent, data);

	if (!GetLabel ().IsEmpty ())
	{
		data.m_strAccName = GetLabel ();
	}

	if ((bool)GetValue ())
	{
		data.m_bAccState |= STATE_SYSTEM_CHECKED;
	}

	return TRUE;
}