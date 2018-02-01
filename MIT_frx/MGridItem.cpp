#include "stdafx.h"
#include "MGridItem.h"
#include "MGridRow.h"
#include "MTable.h"
#include "MGridColumnsInfo.h"
//#include "strtk.hpp"

#define TEXT_MARGIN		3
#define TEXT_VMARGIN	2

using namespace mit;
using namespace mit::frx;

class MFriendGridCtrl : public CBCGPGridCtrl
{
	friend class MGridItem;
};

IMPLEMENT_DYNAMIC(MInplaceWnd, CWnd)
MInplaceWnd::MInplaceWnd()
{
	WNDCLASS    wndcls;
	HINSTANCE   hInst = AfxGetInstanceHandle();
	if ( !(::GetClassInfo(hInst, _T("InplaceWnd"), &wndcls)) )
	{
		wndcls.style            = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = _T("InplaceWnd");

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
		}
	}
}

BOOL MInplaceWnd::Create(DWORD dwStyle, CWnd* pParent, UINT nID)
{
	return CWnd::Create(_T("InplaceWnd"), _T(""), dwStyle, CRect(), pParent, nID);
}

IMPLEMENT_SERIAL(MGridItem, CBCGPGridItem, VERSIONABLE_SCHEMA | 1)
MGridItem::MGridItem(void) :
	m_bShowValue(TRUE),
	m_bBold(FALSE),
	m_bItalic(FALSE),
	m_bUnderline(FALSE),
	m_bStrikeOut(FALSE)
{
}

MGridItem::MGridItem(const _variant_t& varValue, DWORD_PTR dwData, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars) :
	CBCGPGridItem(varValue, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars),
	m_bShowValue(TRUE),
	m_bBold(FALSE),
	m_bItalic(FALSE),
	m_bUnderline(FALSE),
	m_bStrikeOut(FALSE)
{
}

MGridItem::~MGridItem(void)
{
	// GridItem이 소멸했는데 테이블의 MergedItem에 데이터가 남아있어서 버그가 발생.
	// 그래서 이렇게 처리함. BCG 자체 버그인 것으로 보임.
	MTable* pGrid = (MTable*)GetOwnerList();
	if( pGrid )
	{
		POSITION pos = pGrid->m_lstMergedItemsToRedraw.Find(this);
		if( pos )
			pGrid->m_lstMergedItemsToRedraw.RemoveAt(pos);
	}
}

void MGridItem::ShowValue(BOOL bShow)
{
	if (m_bShowValue == bShow) return;
	m_bShowValue = bShow;
	m_bIsChanged = TRUE;
}

CString MGridItem::FloatFormatItem(const _variant_t& var)
{
	CBCGPGridCtrl* pWndList = m_pGridRow->GetOwnerList();
	ASSERT_VALID (pWndList);

	ASSERT( pWndList->IsKindOf(RUNTIME_CLASS(MTable)) );
	MTable* pTable = (MTable*)pWndList;
	ASSERT_VALID (pTable);

	CString strVal;
	MFormatInfo info;
	if ( pTable->GetColumnFormat(GetColumnId(), info) && !info.GetFormat().IsEmpty())
	{
		switch (var.vt)
		{
		case VT_R4:
			strVal.Format (info.GetFormat(), (float) var);
			break;
		case VT_R8:
			strVal.Format (info.GetFormat(), (double) var);
			break;
		}
	}
	else
	{
		switch (var.vt)
		{
		case VT_R4:
			strVal.Format (CBCGPGridRow::m_strFormatFloat, (float) var);
			break;
		case VT_R8:
			strVal.Format (CBCGPGridRow::m_strFormatDouble, (double) var);
			break;
		}
	}

	return strVal;
}

void MGridItem::AppendFloatFormat(CString& strText, const _variant_t& var)
{
	CBCGPGridCtrl* pWndList = m_pGridRow->GetOwnerList();
	ASSERT (pWndList);

	ASSERT( pWndList->IsKindOf(RUNTIME_CLASS(MTable)) );
	MTable* pTable = (MTable*)pWndList;
	ASSERT (pTable);

	MFormatInfo info;
	if ( pTable->GetColumnFormat(GetColumnId(), info) && !info.GetFormat().IsEmpty())
	{
		switch (var.vt)
		{
		case VT_R4:
			strText.AppendFormat (info.GetFormat(), (float) var);
			break;
		case VT_R8:
			strText.AppendFormat (info.GetFormat(), (double) var);
			break;
		}
	}
	else
	{
		switch (var.vt)
		{
		case VT_R4:
			strText.AppendFormat (CBCGPGridRow::m_strFormatFloat, (float) var);
			break;
		case VT_R8:
			strText.AppendFormat (CBCGPGridRow::m_strFormatDouble, (double) var);
			break;
		}
	}
}

CString MGridItem::FormatItem()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	if (!m_bShowValue) return _T("");

	CBCGPGridCtrl* pWndList = GetOwnerList();
	ASSERT_VALID (pWndList);

	MFriendGridCtrl* pGridCtrl = reinterpret_cast<MFriendGridCtrl*>(pWndList);
	ASSERT_VALID (pGridCtrl);

	// If merged, refer to main item
	CBCGPGridItem* pMergedItem = GetMergedMainItem ();
	const _variant_t& var = (pMergedItem != NULL) ? pMergedItem->GetValue () : m_varValue;

	CString strVal;

	switch (var.vt)
	{
	case VT_BSTR:
		strVal = (LPCTSTR)(_bstr_t)var;
		break;

	case VT_DECIMAL:
		{
			DECIMAL num = (DECIMAL) var;
			globalUtils.StringFromDecimal (strVal, num);
		}
		break;

	case VT_CY:
		{
			CY cy = (CY) var;
			globalUtils.StringFromCy (strVal, cy);
		}
		break;

	case VT_I2:
		strVal.Format (CBCGPGridRow::m_strFormatShort, (short) var);
		break;

	case VT_I4:
	case VT_INT:
		strVal.Format (CBCGPGridRow::m_strFormatLong, (long) var);
		break;

	case VT_UI1:
		strVal.Format (CBCGPGridRow::m_strFormatUShort, (BYTE) var);
		break;

	case VT_UI2:
		strVal.Format (CBCGPGridRow::m_strFormatUShort, var.uiVal);
		break;

	case VT_UINT:
	case VT_UI4:
		strVal.Format (CBCGPGridRow::m_strFormatULong, var.ulVal);
		break;

	case VT_R4:
		strVal = FloatFormatItem(var);
		break;

	case VT_R8:
		strVal = FloatFormatItem(var);
		break;

	case VT_BOOL:
		{
			bool bVal = (bool) var;
			strVal = bVal ? pGridCtrl->m_strTrue : pGridCtrl->m_strFalse;
		}
		break;

	case VT_DATE:
		{
			COleDateTime date = (DATE) var;
			strVal = date.Format ();
		}
		break;

	default:
		break;
	}

	return strVal;
}

void MGridItem::AppendFormatItem(CString& strText)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	CBCGPGridCtrl* pWndList = m_pGridRow->GetOwnerList();
	ASSERT (pWndList);

	MFriendGridCtrl* pGridCtrl = reinterpret_cast<MFriendGridCtrl*>(pWndList);
	ASSERT (pGridCtrl);

	// If merged, refer to main item
	CBCGPGridItem* pMergedItem = GetMergedMainItem();
	const _variant_t& var = (pMergedItem != NULL) ? pMergedItem->GetValue() : m_varValue;
	
	switch (var.vt)
	{
	case VT_BSTR:
		strText.Append((LPCTSTR)(_bstr_t)var);
		break;
	case VT_DECIMAL:
		{
			CString strVal;
			DECIMAL num = (DECIMAL)var;
			globalUtils.StringFromDecimal(strVal, num);
			strText.Append(strVal);
		}
		break;
	case VT_CY:
		{
			CString strVal;
			CY cy = (CY) var;
			globalUtils.StringFromCy (strVal, cy);
			strText.Append(strVal);
		}
		break;
	case VT_I2:
		strText.AppendFormat(CBCGPGridRow::m_strFormatShort, (short)var);
		break;
	case VT_I4:
	case VT_INT:
		//strText.Append(strtk::type_to_string<long>((long)var).c_str());
		strText.AppendFormat(CBCGPGridRow::m_strFormatLong, (long)var);
		break;
	case VT_UI1:
		strText.AppendFormat(CBCGPGridRow::m_strFormatUShort, (BYTE)var);
		break;
	case VT_UI2:
		strText.AppendFormat(CBCGPGridRow::m_strFormatUShort, var.uiVal);
		break;
	case VT_UINT:
	case VT_UI4:
		strText.AppendFormat(CBCGPGridRow::m_strFormatULong, var.uiVal);
		break;
	case VT_R4:
	case VT_R8:
		AppendFloatFormat(strText, var);
		break;
	case VT_BOOL:
		strText.Append((bool)var ? pGridCtrl->m_strTrue : pGridCtrl->m_strFalse);
		break;
	case VT_DATE:
		{
			COleDateTime date = (DATE) var;
			strText.Append(date.Format());
		}
		break;

	default:
		break;
	}
}

void MGridItem::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	CBCGPGridCtrl* pGridCtrl = m_pGridRow->GetOwnerList();
	ASSERT_VALID(pGridCtrl);

	COLORREF clrTextOld = (COLORREF)-1;
	COLORREF clrText = OnFillBackground (pDC, rect);
	
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	CFont  BoldFont;
	LOGFONT logfont;
	CFont* pFont = pDC->GetCurrentFont();
	CFont* pOldFont = NULL;
	if( pFont )
	{
		pFont->GetLogFont( &logfont );
		if( m_bBold		)  logfont.lfWeight = FW_BOLD;
		if( m_bItalic	)  logfont.lfItalic = TRUE;
		if( m_bUnderline ) logfont.lfUnderline = TRUE;
		if( m_bStrikeOut ) logfont.lfStrikeOut = TRUE;
		BoldFont.CreateFontIndirect( &logfont );

		if( m_bBold || m_bItalic || m_bUnderline || m_bStrikeOut )
		{
			pOldFont = pDC->SelectObject( &BoldFont );
		}
	}

	//-----------
	// Draw icon:
	//-----------
	OnDrawIcon (pDC, rect);

	// -----------
	// Draw value:
	// -----------
	rect.DeflateRect (TEXT_MARGIN, TEXT_VMARGIN);

	// If merged, refer to main item
	CBCGPGridItem* pMergedItem = GetMergedMainItem ();
	const CString& strText = (pMergedItem != NULL) ? pMergedItem->GetLabel () : GetLabel ();
	const DWORD dwFlags = (pMergedItem != NULL) ? pMergedItem->GetFlags () : GetFlags ();
	int nTextAlign = (pMergedItem != NULL) ? pMergedItem->GetAlign () : GetAlign ();

	UINT uiTextFlags = DT_NOPREFIX | DT_END_ELLIPSIS;

	// Merge 정보가 있으면 무조건 가운데 정렬하게함
	if ( pMergedItem || (nTextAlign & HDF_CENTER) )
	{
		uiTextFlags |= DT_CENTER;
	}
	else if (nTextAlign & HDF_RIGHT)
	{
		uiTextFlags |= DT_RIGHT;
	}
	else // nTextAlign & HDF_LEFT
	{
		uiTextFlags |= DT_LEFT;
	}

	if (dwFlags & BCGP_GRID_ITEM_VTOP)
	{
		uiTextFlags |= DT_TOP;
	}
	else if (dwFlags & BCGP_GRID_ITEM_VBOTTOM)
	{
		uiTextFlags |= DT_BOTTOM;
	}
	else // dwFlags & BCGP_GRID_ITEM_VCENTER
	{
		uiTextFlags |= DT_VCENTER;
	}

	if (!(dwFlags & BCGP_GRID_ITEM_MULTILINE))
	{
		uiTextFlags |= DT_SINGLELINE;
	}
	else
	{
		if (dwFlags & BCGP_GRID_ITEM_WORDWRAP)
		{
			uiTextFlags |= DT_WORDBREAK;
		}
	}

	m_bValueIsTrancated = pGridCtrl->DoDrawText (pDC, strText, rect, uiTextFlags);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	if( pOldFont )
		pDC->SelectObject(pOldFont);
}

COLORREF MGridItem::OnFillBackground (CDC* pDC, CRect rect)
{
	MTable* pWndList = (MTable*)m_pGridRow->GetOwnerList();
	ASSERT_VALID (pWndList);

	if( !m_pGridRow->IsKindOf(RUNTIME_CLASS(MGridRow)) ) 
	{
		ASSERT(0);
		return m_clrText != (COLORREF)-1 ? m_clrText : pWndList->m_ColorData.m_clrText;
	}

	MGridRow* pGridRow = (MGridRow*)m_pGridRow;

	COLORREF clrText = m_clrText != (COLORREF)-1 ? m_clrText : pWndList->m_ColorData.m_clrText;

	CBCGPGridItem* pCurSelItem = pWndList->GetCurSelItem ();

	BOOL bActiveItem =	pCurSelItem == this && 
		pWndList->AllowInPlaceEdit ();

	if (GetMergedCells () != NULL && pCurSelItem != NULL)
	{
		if (pCurSelItem->GetMergedCells () == GetMergedCells () &&
			pWndList->AllowInPlaceEdit ())
		{
			bActiveItem = TRUE;
		}
	}

	BOOL bNoHighlightActiveItem = !pWndList->IsHighlightActiveItem ();// || 
	//pWndList->IsSelectionBorderEnabled (); // BUG
	BOOL bSelectionBorderActiveItem = pWndList->IsSelectionBorderForActiveItem () && 
		!pWndList->IsSelectionBorderEnabled ();

	CRect rectFill = rect;
	rectFill.top++;

	BOOL bSelected = 
		(pWndList->m_bSingleSel && pWndList->m_bWholeRowSel) ?
		m_pGridRow->IsSelected () :
		IsSelected ();

	if (bSelected && 
		pGridRow->HasValueField () && 
		!(bActiveItem && bNoHighlightActiveItem || m_bInPlaceEdit))
	{
		if (pWndList->m_bFocused && pWndList->IsWholeRowSel ())
		{
			rectFill.right++;
		}

		if (!IsEnabled() || !IsAllowEdit())
		{
			CBrush br(RGB(210, 210, 210));
			pDC->FillRect (rectFill, &br);
			return ::GetSysColor (COLOR_GRAYTEXT);
		}
		clrText = pWndList->OnFillSelItem (pDC, rectFill, this);
	}
	else if (bActiveItem && bNoHighlightActiveItem)
	{
		if (!m_rectButton.IsRectEmpty ())
		{
			rectFill.right = m_rectButton.left;
		}

		if (bSelectionBorderActiveItem || pWndList->IsSelectionBorderEnabled () &&
			(pWndList->m_lstSel.GetCount () > 1 || pWndList->IsGrouping ()))
		{
			pDC->FillRect (rectFill, &globalData.brBlack);

			rectFill.DeflateRect (1, 1);
		}

		if (!IsEnabled() || !IsAllowEdit())
		{
			CBrush br(RGB(210, 210, 210));
			pDC->FillRect (rectFill, &br);
			return ::GetSysColor (COLOR_GRAYTEXT);
		}

		if (pWndList->m_brBackground.GetSafeHandle () != NULL)
		{
			pDC->FillRect (rectFill, &pWndList->m_brBackground);
		}
		else
		{
			COLORREF clr = CBCGPVisualManager::GetInstance()->OnFillGridItem (
				pWndList, pDC, rectFill, bSelected, bActiveItem, FALSE);
			if (clrText == (COLORREF)-1)
			{
				clrText = clr;
			}
		}
	}
	else 
	{
		CBCGPGridItemID id = pWndList->GetGridItemID (this);
		BOOL bCustomColors = FALSE;
		
		// Item has own color - first priority
		if (m_clrBackground != (COLORREF)-1)
		{
			CBrush br (m_clrBackground);
			pDC->FillRect (rectFill, &br);
			bCustomColors = TRUE;
		}

		// Use m_ColorData to get colors
		else if (!id.IsNull ())
		{
			if (pWndList->OnAlternateColor (id))
			{
				bCustomColors = pWndList->m_ColorData.m_EvenColors.Draw (pDC, rectFill);
				if (m_clrText == (COLORREF)-1 &&
					pWndList->m_ColorData.m_EvenColors.m_clrText != (COLORREF)-1)
				{
					clrText = pWndList->m_ColorData.m_EvenColors.m_clrText;
				}
			}
			else
			{
				bCustomColors = pWndList->m_ColorData.m_OddColors.Draw (pDC, rectFill);
				if (m_clrText == (COLORREF)-1 &&
					pWndList->m_ColorData.m_OddColors.m_clrText != (COLORREF)-1)
				{
					clrText = pWndList->m_ColorData.m_OddColors.m_clrText;
				}
			}
		}

		if (!bCustomColors)
		{
			if (!IsEnabled() || !IsAllowEdit())
			{
				CBrush br(RGB(210, 210, 210));
				pDC->FillRect (rectFill, &br);
				return ::GetSysColor (COLOR_GRAYTEXT);
			}
			
			// If the column of this item is sorted
			BOOL bSortedColumn = (pWndList->m_bMarkSortedColumn &&
				!id.IsNull () &&
				(pWndList->GetColumnsInfo ().GetColumnState (id.m_nColumn) != 0));

			COLORREF clr = CBCGPVisualManager::GetInstance()->OnFillGridItem (
					pWndList, pDC, rectFill, bSelected, bActiveItem && bNoHighlightActiveItem, bSortedColumn);

			if (clrText == (COLORREF)-1)
			{
				clrText = clr;
			}
		}
	}

	//if (IsReadOnly()) return ::GetSysColor (COLOR_GRAYTEXT);
	return clrText;
}

BOOL MGridItem::OnUpdateValue()
{
	// Item 편집이 끝났을때 ValidateItemData() 후 들어옴
	// 여기서 return FALSE 하면 편집 완료가 취소됨. ValidateItemData() 실패와 동일함.
	// 단 ValidateItemData() 에서는 Value 가 원래 값 그대로이기 때문에 String 을 가지고 Check 해야해서 불편함
	// 그래서 여기에 Validation Check 포인트(ValidateItemDataAfterUpdateValue())를 하나 더 둔다. 

	ASSERT_VALID (m_pGridRow->GetOwnerList());
	ASSERT( m_pGridRow->GetOwnerList()->IsKindOf(RUNTIME_CLASS(MTable)) );
	MTable* pTable = (MTable*)m_pGridRow->GetOwnerList();

	// 원래값 저장해두기
	_variant_t oldValue = m_varValue;

	// UpdateValue 
	if (!CBCGPGridItem::OnUpdateValue()) return FALSE;
	// 이 뒤로 return FALSE 하려면 ModifiedFlag 지워줘야 함.

	// Validation Check
	ASSERT(m_pGridRow->IsKindOf(RUNTIME_CLASS(MGridRow)));
	BOOL bResult = pTable->ValidateItem((MGridRow*)m_pGridRow);
	// 필요할 경우 수정된 것 DB 에 반영. 
	if (bResult) bResult = pTable->OnUpdateValue(this);

	if (!bResult)
	{
		// Validation Check 나 Modify 실패시 원래 값 복원
		m_varValue = oldValue;
		SetModifiedFlag();
		GetLabel(); // 중간에 Redraw 되면 m_strLabel 이 바뀌기 때문에 호출
		return FALSE;
	}

	return TRUE;
}

CWnd* MGridItem::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	CWnd* pWndEdit = CBCGPGridItem::CreateInPlaceEdit(rectEdit, bDefaultFormat);
	if (m_varValue.vt == VT_R4)
	{
		MFormatInfo info;
		if ( ((MTable*)GetOwnerList())->GetColumnFormat(GetColumnId(), info) )
		{
			CString str;
			str.Format(_T("%.*g"), DBL_DIG + 1, (float)m_varValue);
			pWndEdit->SetWindowText(str);
			bDefaultFormat = FALSE;
		}
	}
	else if (m_varValue.vt == VT_R8)
	{
		MFormatInfo info;
		if ( ((MTable*)GetOwnerList())->GetColumnFormat(GetColumnId(), info) )
		{
			CString str;
			str.Format(_T("%.*g"), DBL_DIG + 1, (double)m_varValue);
			pWndEdit->SetWindowText(str);
			bDefaultFormat = FALSE;
		}
	}
	return pWndEdit;
}

HBRUSH MGridItem::OnCtlColor(CDC* pDC, UINT nCtlColor)
{
	return CBCGPGridItem::OnCtlColor(pDC, nCtlColor);
}