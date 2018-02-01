#include "stdafx.h"
#include "MCustomproperties.h"
#include "MPropList.h"

#include "../MIT_lib/MUnitCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4800)
#define ADD_BUTTON  1
#define SLIDER      2

#define TEXT_MARGIN		4

using namespace mit;
using namespace mit::lib;
using namespace mit::frx;

class MFriendProp : public MStaticProp
{
	friend class MStaticProp;
	friend class MUnitProp;
};

class MFriendPropList : public CBCGPPropList
{
	friend class MStaticProp;
	friend class MUnitProp;
};

//////////////////////////////////////////////////////////////////////////
// class MPropEdit
//////////////////////////////////////////////////////////////////////////
MPropEdit::MPropEdit(MStaticProp* pParent)
{
	m_pParentProp = pParent;
}

BOOL MPropEdit::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
					  LPCTSTR lpszWindowName, DWORD dwStyle,
					  const RECT& rect,
					  CWnd* pParentWnd, UINT nID,
					  LPVOID lpParam)
{
	if( pParentWnd && pParentWnd->IsKindOf(RUNTIME_CLASS(MPropList)))
	{
		MPropList* pPropList = (MPropList*)pParentWnd;
		int nValueAlign = pPropList->GetValueAlign();
		if( nValueAlign == DT_RIGHT )
			dwExStyle |= WS_EX_RIGHT;
		else if ( nValueAlign == DT_LEFT )
			dwExStyle |= WS_EX_LEFT;
	}

	return CBCGPEdit::CreateEx( dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

BOOL MPropEdit::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
					  LPCTSTR lpszWindowName, DWORD dwStyle,
					  int x, int y, int nWidth, int nHeight,
					  HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam )
{
	if( hWndParent )
	{
		CWnd* pParentWnd = CWnd::FromHandle(hWndParent);
		if( pParentWnd && pParentWnd->IsKindOf(RUNTIME_CLASS(MPropList)))
		{
			MPropList* pPropList = (MPropList*)pParentWnd;
			int nValueAlign = pPropList->GetValueAlign();
			if( nValueAlign == DT_RIGHT )
				dwExStyle |= WS_EX_RIGHT;
			else if ( nValueAlign == DT_LEFT )
				dwExStyle |= WS_EX_LEFT;
		}
	}

	return CBCGPEdit::CreateEx( dwExStyle, lpszClassName, lpszWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, nIDorHMenu, lpParam);
}

//////////////////////////////////////////////////////////////////////////
// class MPropComboBox
//////////////////////////////////////////////////////////////////////////
MPropComboBox::MPropComboBox(MStaticProp* pParent)
{
	m_pParentProp = pParent;
}

BOOL MPropComboBox::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
						 LPCTSTR lpszWindowName, DWORD dwStyle,
						 const RECT& rect,
						 CWnd* pParentWnd, UINT nID,
						 LPVOID lpParam)
{
	if( pParentWnd && pParentWnd->IsKindOf(RUNTIME_CLASS(MPropList)))
	{
		MPropList* pPropList = (MPropList*)pParentWnd;
		int nValueAlign = pPropList->GetValueAlign();
		if( nValueAlign == DT_RIGHT )
			dwExStyle |= WS_EX_RIGHT;
		else if ( nValueAlign == DT_LEFT )
			dwExStyle |= WS_EX_LEFT;
	}

	return CBCGPComboBox::CreateEx( dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

BOOL MPropComboBox::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
						 LPCTSTR lpszWindowName, DWORD dwStyle,
						 int x, int y, int nWidth, int nHeight,
						 HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam )
{
	if( hWndParent )
	{
		CWnd* pParentWnd = CWnd::FromHandle(hWndParent);
		if( pParentWnd && pParentWnd->IsKindOf(RUNTIME_CLASS(MPropList)))
		{
			MPropList* pPropList = (MPropList*)pParentWnd;
			int nValueAlign = pPropList->GetValueAlign();
			if( nValueAlign == DT_RIGHT )
				dwExStyle |= WS_EX_RIGHT;
			else if ( nValueAlign == DT_LEFT )
				dwExStyle |= WS_EX_LEFT;
		}
	}

	return CBCGPComboBox::CreateEx( dwExStyle, lpszClassName, lpszWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, nIDorHMenu, lpParam);
}

//////////////////////////////////////////////////////////////////////
// MStaticProp
//////////////////////////////////////////////////////////////////////
MStaticProp::MStaticProp(const CString& strGroupName, DWORD_PTR dwData,
			BOOL bIsValueList)
			: CBCGPProp (strGroupName, dwData, bIsValueList)
{

}

MStaticProp::MStaticProp(const CString& strName, const _variant_t& varValue, 
						 LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask
						 , LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
						: CBCGPProp (strName, varValue, lpszDescr, dwData, lpszEditMask,
						lpszEditTemplate, lpszValidChars )
{
}

MStaticProp::MStaticProp(const CString& strName, UINT nID, const _variant_t& varValue, 
			LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask
			, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
			: CBCGPProp(strName, nID, varValue, lpszDescr, dwData, lpszEditMask,
			lpszEditTemplate, lpszValidChars )
{

}

MStaticProp::~MStaticProp()
{
}

void MStaticProp::OnDrawName (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return;

	COLORREF clrTextOld = (COLORREF)-1;

	if (IsSelected () && (!m_pWndList->IsVSDotNetLook() || !IsGroup () ||  m_bIsValueList))
	{
		CRect rectFill = rect;
		rectFill.top++;

		if (m_bDrawMenuButton)
		{
			rectFill.right += rectFill.Height();
		}

		if (m_bHasState)
		{
			rectFill.right += m_rectState.Width();
		}

		COLORREF clrText = CBCGPVisualManager::GetInstance()->OnFillPropertyListSelectedItem(pDC, this, m_pWndList, rectFill, pWndList->m_bFocused);
		clrTextOld = pDC->SetTextColor (clrText);
	}

	if (m_pWndList->IsVSDotNetLook() && IsGroup () && !m_bIsValueList)
	{
		if (pWndList->m_clrGroupText != (COLORREF)-1)
		{
			clrTextOld = pDC->SetTextColor (pWndList->m_clrGroupText);
		}
		else
		{
			clrTextOld = pDC->SetTextColor (CBCGPVisualManager::GetInstance()->GetPropListGroupTextColor (m_pWndList));
		}
	}

	if( m_pParent )
	{
		MFriendProp* pParentProp = reinterpret_cast<MFriendProp*>(m_pParent);
		if (pParentProp != NULL && pParentProp->m_bIsValueList)
		{
			rect.left += rect.Height ();
		}
	}

	rect.DeflateRect (TEXT_MARGIN, 0);

	int nNameAlign = IsGroup() ? DT_LEFT : pWndList->m_nNameAlign;

	int nTextHeight = pDC->DrawText (m_strName, rect, 
		nNameAlign | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	m_bNameIsTrancated = pDC->GetTextExtent (m_strName).cx > rect.Width ();

	if (IsSelected () && m_pWndList->IsVSDotNetLook() && IsGroup () && !m_bIsValueList)
	{
		CRect rectFocus = rect;
		rectFocus.top = rectFocus.CenterPoint ().y - nTextHeight / 2;
		rectFocus.bottom = rectFocus.top + nTextHeight;
		rectFocus.right = 
			min (rect.right, rectFocus.left + pDC->GetTextExtent (m_strName).cx);
		rectFocus.InflateRect (2, 0);

		COLORREF clrShadow = m_pWndList->DrawControlBarColors () ?
			globalData.clrBarShadow : globalData.clrBtnShadow;

		pDC->Draw3dRect (rectFocus, clrShadow, clrShadow);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}

void MStaticProp::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return;


	if ((IsGroup () && !m_bIsValueList) || !HasValueField ())
	{
		return;
	}

	CFont* pOldFont = NULL;
	if (IsModified () && pWndList->m_bMarkModifiedProperties)
	{
		pOldFont = pDC->SelectObject (&pWndList->m_fontBold);
	}

	CString strVal = FormatProperty ();

	rect.DeflateRect (TEXT_MARGIN, 0);

	if( m_pWndList->IsKindOf(RUNTIME_CLASS(MPropList)) )
	{
		MPropList* pPropList = (MPropList*)m_pWndList;
		pDC->DrawText (strVal, rect, 
		pPropList->GetValueAlign() | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
	}
	else
	{
		pDC->DrawText (strVal, rect, 
			m_pWndList->GetNameAlign() | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
	}

	m_bValueIsTrancated = pDC->GetTextExtent (strVal).cx > rect.Width ();

	if (pOldFont != NULL)
	{
		pDC->SelectObject (pOldFont);
	}
}

CWnd* MStaticProp::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	if (NoInplaceEdit())
	{
		return NULL;
	}

	switch (m_varValue.vt)
	{
	case VT_BSTR:
	case VT_R4:
	case VT_R8:
	case VT_UI1:
	case VT_I2:
	case VT_INT:
	case VT_UINT:
	case VT_I4:
	case VT_I8:
	case VT_UI8:
	case VT_UI2:
	case VT_UI4:
	case VT_BOOL:
		break;

	default:
		if (!m_bIsValueList)
		{
			return NULL;
		}
	}

	CEdit* pWndEdit = NULL;

	if (!m_strEditMask.IsEmpty () || !m_strEditTempl.IsEmpty () ||
		!m_strValidChars.IsEmpty ())
	{
		CBCGPMaskEdit* pWndEditMask = new CBCGPMaskEdit;
		pWndEditMask->EnableSetMaskedCharsOnly (FALSE);
		pWndEditMask->EnableGetMaskedCharsOnly (FALSE);

		if (!m_strEditMask.IsEmpty () && !m_strEditTempl.IsEmpty ())
		{
			pWndEditMask->EnableMask (m_strEditMask, m_strEditTempl, _T(' '));
		}

		if (!m_strValidChars.IsEmpty ())
		{
			pWndEditMask->SetValidChars (m_strValidChars);
		}

		pWndEdit = pWndEditMask;
	}
	else
	{
		pWndEdit = new MPropEdit(this);
	}

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL;

	if (!m_bEnabled || !m_bAllowEdit)
	{
		dwStyle |= ES_READONLY;
	}

	pWndEdit->Create (dwStyle, rectEdit, m_pWndList, BCGPROPLIST_ID_INPLACE);

	bDefaultFormat = TRUE;
	return pWndEdit;
}

//////////////////////////////////////////////////////////////////////
// MUnitProp
//////////////////////////////////////////////////////////////////////
mit::MList<MUnitProp*> MUnitProp::m_slTU;

MUnitProp::MUnitProp(const CString& strName, const _variant_t& varValue,
						 LPCTSTR lpszDescr, DWORD_PTR dwData)
						 : MStaticProp (strName, varValue, lpszDescr, dwData)
{
	m_pUnitCtrl = NULL;
	m_iUnitType = D_UNITSYS_BASE_LENGTH;
	m_slTU.AddTail( this );
	m_strUnit = _T("tonf/mm2");
	m_dUnitWitdhRadio = 0.3; // Unit 부분의 Width가 전체에서 차지하는 비율.
}

MUnitProp::~MUnitProp()
{
	POSITION pos, prevpos;
	pos = m_slTU.GetHeadPosition();
	MUnitProp* unit;
	while(pos)
	{
		prevpos = pos;
		unit = m_slTU.GetNext(pos);
		if(unit == this)
		{
			m_slTU.RemoveAt(prevpos);
			break;
		}
	}
}

void MUnitProp::SetStatic(MUnitCtrl* pUnitCtrl)
{
	POSITION pos = m_slTU.GetHeadPosition();
	MUnitProp* unit;
	while(pos)
	{
		unit = m_slTU.GetNext(pos);
		if(unit->GetUnitCtrl() == pUnitCtrl )
		{
			unit->SetStaticText();
			CWnd* pParent = unit->GetParentPropList();
			if(::IsWindow(pParent->GetSafeHwnd())) pParent->Invalidate();
		}
	}

}

void MUnitProp::SetStaticText()
{
	if( !m_pUnitCtrl ) { /*ASSERT(0);*/ return; }

	CString strUnit;
	if( !m_pUnitCtrl->GetUnitSystem(m_iUnitType, strUnit) ) strUnit = _T("");
	SetTextUnit( strUnit );
}

void MUnitProp::SetTextUnit(CString& strUnit)
{
	if(::IsWindow(m_pWndList->GetSafeHwnd())) m_strUnit = strUnit;
}

void MUnitProp::SetUnitType(MUnitCtrl* pUnitCtrl, int iUnitType)
{
	m_pUnitCtrl = pUnitCtrl;
	m_iUnitType = iUnitType;
	SetStaticText();

	if(::IsWindow(m_pWndList->GetSafeHwnd())) m_pWndList->Invalidate();
}

void MUnitProp::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return;


	if ((IsGroup () && !m_bIsValueList) || !HasValueField ())
	{
		return;
	}

	CFont* pOldFont = NULL;
	if (IsModified () && pWndList->m_bMarkModifiedProperties)
	{
		pOldFont = pDC->SelectObject (&pWndList->m_fontBold);
	}

	CString strVal = FormatProperty ();

	rect.DeflateRect (TEXT_MARGIN, 0);

	if( m_pWndList->IsKindOf(RUNTIME_CLASS(MPropList)) )
	{
		CRect rectValue = rect;
		CRect rectUnit  = rect;
		int nUnitWidth = (int)(((double)rect.Width()) * m_dUnitWitdhRadio);
		rectValue.right -= nUnitWidth;
		rectValue.right -= TEXT_MARGIN; // 마진

		if ( HasButton() )
			rectValue.right -= m_rectButton.Width();

		if (m_dwFlags & PROP_HAS_SPIN)
		{
			rectValue.right -= rectValue.Height ();
			OnDrawSpinButton(pDC);
		}

		// Value 를 그린다.
		MPropList* pPropList = (MPropList*)m_pWndList;
		pDC->DrawText (strVal, rectValue, 
			pPropList->GetValueAlign() | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

		rectUnit.left = rectUnit.right - nUnitWidth;

		// Unit 을 그린다.
		COLORREF clrShadow = m_pWndList->DrawControlBarColors () ?
			globalData.clrBarShadow : globalData.clrBtnShadow;

		CPen penLine (PS_SOLID, 1, pWndList->m_clrLine != (COLORREF)-1 ?
		pWndList->m_clrLine : ((pWndList->m_bVSDotNetLook && !globalData.IsHighContastMode()) ? pWndList->m_clrGray : clrShadow));
		CPen* pOldPen = pDC->SelectObject (&penLine);

		pDC->MoveTo (rectUnit.left, rectUnit.top - 1);
		pDC->LineTo (rectUnit.left, rectUnit.bottom);

		pDC->SelectObject (pOldPen);
		
		if( m_iUnitType == D_UNITSYS_NONE )
			m_strUnit = _T("");

		rectUnit.left++;
		rectUnit.OffsetRect(2, 0);

		pDC->DrawText (m_strUnit, rectUnit, 
			DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
	}
	else
	{
		pDC->DrawText (strVal, rect, 
			m_pWndList->GetNameAlign() | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
	}

	m_bValueIsTrancated = pDC->GetTextExtent (strVal).cx > rect.Width ();

	if (pOldFont != NULL)
	{
		pDC->SelectObject (pOldFont);
	}
}

void MUnitProp::AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectUnit)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return;

	rectEdit = m_Rect;
	rectEdit.DeflateRect (0, 2);

	int nMargin = pWndList->m_bMarkModifiedProperties && m_bIsModified ?
		pWndList->m_nBoldEditLeftMargin : pWndList->m_nEditLeftMargin;

	rectEdit.left = pWndList->m_rectList.left + pWndList->m_nLeftColumnWidth 
		+ TEXT_MARGIN - nMargin + 1;

	if (HasButton ())
	{
		AdjustButtonRect ();
		rectEdit.right = m_rectButton.left;
		rectEdit.right -= 2;
	}
	else
	{
		rectEdit.right -= 2;

		int nUnitWidth = (int)(((double)rectEdit.Width()) * m_dUnitWitdhRadio);
		rectEdit.right -= nUnitWidth;
		rectEdit.right -= TEXT_MARGIN;

		if (m_dwFlags & PROP_HAS_SPIN)
		{
			rectEdit.right -= m_Rect.Height();
		}

		rectUnit = m_Rect;
		rectUnit.left = rectUnit.right - nUnitWidth;
		rectUnit.top ++;
	}
}

void MUnitProp::AdjustButtonRect ()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return;

	CRect rectEdit = m_Rect;
	rectEdit.DeflateRect (0, 2);

	int nMargin = pWndList->m_bMarkModifiedProperties && m_bIsModified ?
		pWndList->m_nBoldEditLeftMargin : pWndList->m_nEditLeftMargin;

	rectEdit.left = pWndList->m_rectList.left + pWndList->m_nLeftColumnWidth 
		+ TEXT_MARGIN - nMargin + 1;

	m_rectButton = m_Rect;
	m_rectButton.right--;
	m_rectButton.left = m_rectButton.right - m_rectButton.Height();
	m_rectButton.top++;

	int nUnitWidth = (int)(((double)rectEdit.Width()) * m_dUnitWitdhRadio);
	m_rectButton.OffsetRect(-nUnitWidth, 0);
	m_rectButton.OffsetRect(-TEXT_MARGIN, 0);
	m_rectButton.OffsetRect(1, 0);
}

CComboBox* MUnitProp::CreateCombo (CWnd* pWndParent, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return NULL;

	CRect rectEdit = m_Rect;
	rectEdit.DeflateRect (0, 2);

	int nMargin = pWndList->m_bMarkModifiedProperties && m_bIsModified ?
		pWndList->m_nBoldEditLeftMargin : pWndList->m_nEditLeftMargin;

	rectEdit.left = pWndList->m_rectList.left + pWndList->m_nLeftColumnWidth 
		+ TEXT_MARGIN - nMargin + 1;

	int nUnitWidth = (int)(((double)rectEdit.Width()) * m_dUnitWitdhRadio);

	rect.right -= (nUnitWidth + TEXT_MARGIN);
	rect.bottom = rect.top + 400;

	CComboBox* pWndCombo = new MPropComboBox(this);
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL, 
		rect, pWndParent, BCGPROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}

	return pWndCombo;
}

CSpinButtonCtrl* MUnitProp::CreateSpinControl (CRect rectSpin)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	if (!m_bEnabled)
	{
		return NULL;
	}

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	if( !pWndList ) return NULL;

	CRect rectEdit = m_Rect;
	rectSpin = m_Rect;
	rectEdit.DeflateRect (0, 2);

	int nMargin = pWndList->m_bMarkModifiedProperties && m_bIsModified ?
		pWndList->m_nBoldEditLeftMargin : pWndList->m_nEditLeftMargin;

	rectEdit.left = pWndList->m_rectList.left + pWndList->m_nLeftColumnWidth 
		+ TEXT_MARGIN - nMargin + 1;

	int nUnitWidth = (int)(((double)rectEdit.Width()) * m_dUnitWitdhRadio);

	rectSpin.right -= (nUnitWidth + TEXT_MARGIN);
	rectSpin.left = rectSpin.right - rectSpin.Height ();
	rectSpin.top++;

	CSpinButtonCtrl* pWndSpin = new CBCGPSpinButtonCtrl;

	if (!pWndSpin->Create (
		WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_SETBUDDYINT | UDS_NOTHOUSANDS,
		rectSpin, m_pWndList, BCGPROPLIST_ID_INPLACE))
	{
		return NULL;
	}

	pWndSpin->SetBuddy (m_pWndInPlace);

	if (m_nMinValue != 0 || m_nMaxValue != 0)
	{
		pWndSpin->SetRange32 (m_nMinValue, m_nMaxValue);
	}

	return pWndSpin;
}

BOOL MUnitProp::OnEndEdit ()
{
	ASSERT_VALID (this);

	m_bInPlaceEdit = FALSE;
	m_bButtonIsFocused = FALSE;

	OnDestroyWindow ();

	return TRUE;
}

BOOL MUnitProp::IsButtonVisible() const
{
	ASSERT_VALID (this);

	if (!HasButton())
	{
		return FALSE;
	}

	if (m_pWndList == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (m_pWndList);

	// ComboBox는 항상 버튼이 나타나도록 한다.
	return HasButton();

	//return m_pWndList->GetCurSel() == this || (m_pWndList->IsContextMenuEnabled() && (m_dwFlags & PROP_HAS_LIST) == 0);
}

void MUnitProp::OnDrawSpinButton(CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	MFriendPropList* pWndList = reinterpret_cast<MFriendPropList*>(m_pWndList);
	ASSERT_VALID(pWndList);

	CRect rectEdit = m_Rect;
	CRect rectSpin = m_Rect;
	rectEdit.DeflateRect (0, 2);

	int nMargin = pWndList->m_bMarkModifiedProperties && m_bIsModified ?
		pWndList->m_nBoldEditLeftMargin : pWndList->m_nEditLeftMargin;

	rectEdit.left = pWndList->m_rectList.left + pWndList->m_nLeftColumnWidth 
		+ TEXT_MARGIN - nMargin + 1;

	int nUnitWidth = (int)(((double)rectEdit.Width()) * m_dUnitWitdhRadio);

	rectSpin.right -= (nUnitWidth + TEXT_MARGIN);
	rectSpin.left = rectSpin.right - rectSpin.Height ();
	rectSpin.top++;
	
	CRect rectBorder (0, 0, 0, 0);

	rectBorder = rectSpin;
	rectSpin.DeflateRect (1, 1);

	if (!rectBorder.IsRectEmpty ())
	{
		CBCGPVisualManager::GetInstance()->OnDrawControlBorder (
			pDC, rectBorder, NULL, CBCGPToolBarImages::m_bIsDrawOnGlass );
	}

	if (CBCGPToolBarImages::m_bIsDrawOnGlass )
	{
		CBCGPDrawManager dm (*pDC);
		dm.DrawRect (rectSpin, globalData.clrWindow, (COLORREF)-1);
	}
	else
	{
		pDC->FillRect (rectSpin, &globalData.brWindow);
	}

	int nState = 0;

	if( !m_bEnabled || !m_bAllowEdit )
		nState |= SPIN_DISABLED;

	CBCGPDrawOnGlass dog (CBCGPToolBarImages::m_bIsDrawOnGlass);

	CBCGPVisualManager::GetInstance()->OnDrawSpinButtons (
		pDC, rectSpin, nState, FALSE, NULL);
}

//////////////////////////////////////////////////////////////////////////
// MButtonProp
MButtonProp::MButtonProp(const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData)
: MStaticProp (strName, varValue, lpszDescr, dwData)
{

}

MButtonProp::~MButtonProp()
{

}

void MButtonProp::OnClickButton (CPoint point)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	if( m_pWndList->IsKindOf(RUNTIME_CLASS(MPropList)) )
	{
		MPropList* pPropList = (MPropList*)m_pWndList;

		if (m_pWndCombo != NULL && m_bEnabled)
		{
			m_bButtonIsDown = TRUE;
			m_bButtonIsHighlighted = FALSE;
			Redraw ();

			OnSetSelectedComboItem();

			m_pWndCombo->SetFocus ();
			m_pWndCombo->ShowDropDown ();
		}
		else
		{
			pPropList->OnPropertyClickButton(this, point);
		}
	}
	else
	{
		MStaticProp::OnClickButton( point );
	}
}
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPropSliderCtrl

MPropSliderCtrl::MPropSliderCtrl(MSliderProp* pProp)
{
	m_pProp = pProp;
}

MPropSliderCtrl::~MPropSliderCtrl()
{
}

BEGIN_MESSAGE_MAP(MPropSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CPropSliderCtrl)
	ON_WM_HSCROLL_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MPropSliderCtrl::HScroll (UINT nSBCode, UINT nPos)
{
	ASSERT_VALID (m_pProp);
	m_pProp->UpdatePropList();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MSliderProp::MSliderProp(const CString& strName, const _variant_t& varValue,
               LPCTSTR lpszDescr, DWORD_PTR dwData)
               :	MStaticProp (strName, varValue, lpszDescr, dwData)
{
	m_pSlider = NULL;
}

MSliderProp::~MSliderProp()
{
	if(m_pSlider) { delete m_pSlider;   m_pSlider = NULL; }
}

void MSliderProp::SetSlider(int nInit)
{
	if(m_pSlider == NULL)
	{
		CRect rectDummy;
		rectDummy.SetRectEmpty ();  

		m_pSlider = new MPropSliderCtrl(this);
		m_pSlider->Create(WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_NOTICKS, rectDummy, m_pWndList, SLIDER);
		m_pSlider->SetRange(0, 100);
		m_pSlider->SetPos(nInit);
	}
}

void  MSliderProp::UpdatePropList()
{
	m_pWndList->OnPropertyChanged (this);
}

void  MSliderProp::ShowControl(BOOL bShow)
{
	if(m_pSlider)
	{
		if(bShow)   m_pSlider->ShowWindow(SW_SHOW);
		else        m_pSlider->ShowWindow(SW_HIDE);
	}
}

void MSliderProp::OnDrawValue(CDC* pDC, CRect rect)
{
	if(m_pSlider)
	{
		m_pSlider->MoveWindow(rect);
		m_pSlider->Invalidate();
	}
}

int MSliderProp::GetSliderPos()
{
	if(m_pSlider)
	{
		return m_pSlider->GetPos();
	}
	return 0;
}

void MSliderProp::SetSliderPos(int nPos)
{
	if(m_pSlider)
		m_pSlider->SetPos(nPos);
}

////////////////////////////////////////////////////////////////////////////////
// CCheckBoxProp class

MCheckBoxProp::MCheckBoxProp(const CString& strName, BOOL bCheck, LPCTSTR lpszDescr, DWORD_PTR dwData)
: MStaticProp (strName, COleVariant ((short)(bCheck?VARIANT_TRUE:VARIANT_FALSE), VT_BOOL), lpszDescr, dwData)
{
	m_rectCheck.SetRectEmpty ();
}

void MCheckBoxProp::OnDrawName(CDC* pDC, CRect rect)
{
	m_rectCheck = rect;
	m_rectCheck.DeflateRect (1, 1);

	m_rectCheck.right = m_rectCheck.left + m_rectCheck.Height();

	rect.left = m_rectCheck.right + 1;

	MStaticProp::OnDrawName (pDC, rect);

	OnDrawCheckBox (pDC, m_rectCheck, m_varValue.boolVal);
}

void MCheckBoxProp::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	rect.DeflateRect (TEXT_MARGIN, 0);
	CString strValue;
	if(m_varValue.boolVal)
		strValue = _T("True");
	else
		strValue = _T("False");
	pDC->DrawText(strValue, rect,	DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	m_bValueIsTrancated = pDC->GetTextExtent (strValue).cx > rect.Width ();
}

void MCheckBoxProp::OnClickName(CPoint point)
{
	if (m_bEnabled && m_rectCheck.PtInRect (point)) 
	{
		m_varValue.boolVal = !m_varValue.boolVal;
		m_pWndList->InvalidateRect (m_rectCheck);
		m_pWndList->OnPropertyChanged (this);
		Redraw();
	}
}

BOOL MCheckBoxProp::OnDblClk (CPoint point)
{
	if (m_bEnabled && m_rectCheck.PtInRect (point)) 
	{
		return TRUE;
	}

	m_varValue.boolVal = !m_varValue.boolVal;
	m_pWndList->InvalidateRect (m_rectCheck);
	m_pWndList->OnPropertyChanged (this);
	Redraw();
	return TRUE;
}

void MCheckBoxProp::OnDrawCheckBox (CDC * pDC, CRect rect, BOOL bChecked)
{
	CBCGPVisualManager::GetInstance ()->OnDrawCheckBox (pDC, rect,
		FALSE, bChecked, m_bEnabled);
}

BOOL MCheckBoxProp::PushChar (UINT nChar)
{
	if (nChar == VK_SPACE)
	{
		OnDblClk (CPoint (-1, -1));
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// CCheckEditBoxProp class

MCheckEditBoxProp::MCheckEditBoxProp(const CString& strName, BOOL bCheck, _variant_t& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData)
: MStaticProp (strName, varValue, lpszDescr, dwData)
{
	m_rectCheck.SetRectEmpty ();
	m_bCheck = bCheck;
	m_bEnabled = bCheck;
	m_bAllowEdit = TRUE;
}

void MCheckEditBoxProp::OnDrawName(CDC* pDC, CRect rect)
{
	m_rectCheck = rect;
	m_rectCheck.DeflateRect (1, 1);

	m_rectCheck.right = m_rectCheck.left + m_rectCheck.Height();

	rect.left = m_rectCheck.right + 1;

	MStaticProp::OnDrawName (pDC, rect);

	OnDrawCheckBox (pDC, m_rectCheck, (VARIANT_BOOL)m_bCheck);
}

void MCheckEditBoxProp::OnClickName(CPoint point)
{
	if (m_rectCheck.PtInRect (point)) 
	{
		m_bCheck = !m_bCheck;
		m_bEnabled = m_bCheck;
		m_pWndList->InvalidateRect (m_rectCheck);
		m_pWndList->OnPropertyChanged (this);
		Redraw();
	}
}

void MCheckEditBoxProp::OnDrawCheckBox (CDC * pDC, CRect rect, BOOL bChecked)
{
	CBCGPVisualManager::GetInstance ()->OnDrawCheckBox (pDC, rect,
		FALSE, bChecked, m_bEnabled);
}

BOOL MCheckEditBoxProp::PushChar (UINT nChar)
{
	if (nChar == VK_SPACE)
	{
		OnDblClick (CPoint (-1, -1));
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// MCheckUnitProp class

MCheckUnitProp::MCheckUnitProp(const CString& strName, BOOL bCheck, _variant_t& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData)	
	: MUnitProp (strName, varValue, lpszDescr, dwData)
{
	m_rectCheck.SetRectEmpty ();
	m_bCheck = bCheck;
	m_bEnabled = bCheck;
	m_bAllowEdit = TRUE;
}

void MCheckUnitProp::OnDrawName(CDC* pDC, CRect rect)
{
	m_rectCheck = rect;
	m_rectCheck.DeflateRect (1, 1);

	m_rectCheck.right = m_rectCheck.left + m_rectCheck.Height();

	rect.left = m_rectCheck.right + 1;

	MUnitProp::OnDrawName (pDC, rect);

	OnDrawCheckBox (pDC, m_rectCheck, (VARIANT_BOOL)m_bCheck);
}

void MCheckUnitProp::OnClickName(CPoint point)
{
	if (m_rectCheck.PtInRect (point)) 
	{
		m_bCheck = !m_bCheck;
		m_bEnabled = m_bCheck;
		m_pWndList->InvalidateRect (m_rectCheck);
		m_pWndList->OnPropertyChanged (this);
		Redraw();
	}
}

void MCheckUnitProp::OnDrawCheckBox (CDC * pDC, CRect rect, BOOL bChecked)
{
	CBCGPVisualManager::GetInstance ()->OnDrawCheckBox (pDC, rect,
		FALSE, bChecked, m_bEnabled);
}

BOOL MCheckUnitProp::PushChar (UINT nChar)
{
	if (nChar == VK_SPACE)
	{
		OnDblClick (CPoint (-1, -1));
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// CComboBoxProp class

MComboBoxProp::MComboBoxProp(const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData)
	             : MStaticProp (strName, varValue, lpszDescr, dwData)
{
  m_nCurSel = 0;
}

void MComboBoxProp::OnSelectCombo()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndCombo);
	ASSERT_VALID (m_pWndInPlace);

	int iSelIndex = m_pWndCombo->GetCurSel ();
	if (iSelIndex >= 0)
	{
    m_nCurSel = iSelIndex;
		CString str;
		m_pWndCombo->GetLBText (iSelIndex, str);
		m_pWndInPlace->SetWindowText (str);
		OnUpdateValue ();
	}
}



BOOL MComboBoxProp::OnDblClk(CPoint point)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);
	ASSERT_VALID (m_pWndCombo);

	if (m_pWndInPlace == NULL)
	{
		return FALSE;
	}

	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));

	if (m_lstOptions.GetCount () > 1)
	{
		CString strText;
		m_pWndInPlace->GetWindowText (strText);

		POSITION pos = m_lstOptions.Find (strText);
		if (pos == NULL)
		{
			return FALSE;
		}

		m_lstOptions.GetNext (pos);
		if (pos == NULL)
		{
			pos = m_lstOptions.GetHeadPosition ();
		}

		ASSERT (pos != NULL);
		strText = m_lstOptions.GetAt (pos);

		m_pWndInPlace->SetWindowText (strText);

		int nSelIdx = m_pWndCombo->FindString( 0, strText ); 
		if(CB_ERR == nSelIdx )  return FALSE; 
		else                    m_nCurSel = nSelIdx;

		OnUpdateValue ();
		Redraw();

		return TRUE;
	}
	return FALSE; 
}

// CIconCombo
const int nIconMargin = 3;

MIconCombo::MIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames) :
	m_imageListIcons (imageListIcons),
	m_lstIconNames (lstIconNames)
{
}

MIconCombo::~MIconCombo()
{
}

BEGIN_MESSAGE_MAP(MIconCombo, CComboBox)
	//{{AFX_MSG_MAP(CIconCombo)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconCombo message handlers

void MIconCombo::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rect = lpDIS->rcItem;
	int nIcon = lpDIS->itemID;

	HBRUSH		brBackground;
	COLORREF	clText; 

	if (lpDIS->itemState & ODS_SELECTED)  
	{
		brBackground = GetSysColorBrush (COLOR_HIGHLIGHT); 
		clText = afxGlobalData.clrTextHilite; 
	} 
	else 
	{
		brBackground = GetSysColorBrush (COLOR_WINDOW); 
		clText = afxGlobalData.clrWindowText;
	} 

	if (lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		::FillRect (lpDIS->hDC, &rect, brBackground);
	}

	if (nIcon < 0)
	{
		return;
	}

	CBCGPDrawState ds;
	m_imageListIcons.PrepareDrawImage (ds);
	m_imageListIcons.Draw (pDC, rect.left + nIconMargin, rect.top + nIconMargin, nIcon);
	m_imageListIcons.EndDrawImage (ds);

	if (!m_lstIconNames.IsEmpty ())
	{
		CString str = m_lstIconNames.GetAt (m_lstIconNames.FindIndex (nIcon));
		CFont* pOldFont = pDC->SelectObject (&afxGlobalData.fontRegular);

		pDC->SetBkMode (TRANSPARENT);
		pDC->SetTextColor (clText);

		CRect rectText = rect;
		rectText.left += m_imageListIcons.GetImageSize ().cx + 2 * nIconMargin;

		pDC->DrawText (str, rectText, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}
}

void MIconCombo::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	int nTextWidth = 0;
	int nTextHeight = 0;

	if (!m_lstIconNames.IsEmpty ())
	{
		nTextHeight = afxGlobalData.GetTextHeight ();

		CClientDC dc (this);
		CFont* pOldFont = dc.SelectObject (&afxGlobalData.fontRegular);

		for (POSITION pos = m_lstIconNames.GetHeadPosition (); pos != NULL;)
		{
			CString str = m_lstIconNames.GetNext (pos);

			nTextWidth = max (nTextWidth, dc.GetTextExtent (str).cx + nIconMargin);
		}

		dc.SelectObject (pOldFont);
	}

	lpMeasureItemStruct->itemWidth = m_imageListIcons.GetImageSize ().cx + nTextWidth + 2 * nIconMargin;
	lpMeasureItemStruct->itemHeight = max (nTextHeight, m_imageListIcons.GetImageSize ().cy + 2 * nIconMargin);
}

////////////////////////////////////////////////////////////////////////////////
// CIconListProp class
MIconListProp::MIconListProp(const CString& strName, 
							const CImageList& imageListIcons,
							int nSelectedIcon,
							CStringList* plstIconNames,
							LPCTSTR lpszDescr, DWORD_PTR dwData)
	:	MStaticProp (strName, (long) nSelectedIcon, lpszDescr, dwData)
{
	m_imageListIcons.CreateFromImageList (imageListIcons);
	m_imageListIcons.SetTransparentColor (::GetSysColor (COLOR_3DFACE));

	if (plstIconNames != NULL)
	{
		m_lstIconNames.AddTail (plstIconNames);
		ASSERT (m_lstIconNames.GetCount () == m_imageListIcons.GetCount ());
	}

	for (int i = 0; i < m_imageListIcons.GetCount (); i++)
	{
		CString strItem;
		strItem.Format (_T("%d"), i);

		AddOption (strItem);
	}

	AllowEdit (FALSE);
}

CComboBox* MIconListProp::CreateCombo (CWnd* pWndParent, CRect rect)
{
	rect.bottom = rect.top + 400;

	MIconCombo* pWndCombo = new MIconCombo (m_imageListIcons, m_lstIconNames);
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS,
		rect, pWndParent, AFX_PROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}

	return pWndCombo;
}

void MIconListProp::OnDrawValue (CDC* pDC, CRect rect)
{
	CString strVal = (LPCTSTR)(_bstr_t) m_varValue;
	if (strVal.IsEmpty () || m_imageListIcons.GetCount () == 0)
	{
		return;
	}
	
	int nIndex = -1;
	_stscanf (strVal, _T("%d"), &nIndex);

	if (nIndex < 0)
	{
		return;
	}

	CRect rectImage = rect;
	rectImage.right = rectImage.left + rectImage.Height ();
	rectImage.DeflateRect (1, 1);

	CBCGPDrawState ds;
	m_imageListIcons.PrepareDrawImage (ds, rectImage.Size ());
	m_imageListIcons.Draw (pDC, rectImage.left, rectImage.top, nIndex);
	m_imageListIcons.EndDrawImage (ds);

	if (!m_lstIconNames.IsEmpty ())
	{
		CString str = m_lstIconNames.GetAt (m_lstIconNames.FindIndex (nIndex));

		rect.left = rectImage.right + 2 * nIconMargin;

		pDC->DrawText (str, rect, DT_SINGLELINE | DT_VCENTER);
	}

	m_bValueIsTrancated = FALSE;	
}

CWnd* MIconListProp::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	CWnd* pWnd = MStaticProp::CreateInPlaceEdit (rectEdit, bDefaultFormat);
	if (pWnd != NULL)
	{
		pWnd->ShowWindow (SW_HIDE);
	}

	return pWnd;
}


////////////////////////////////////////////////////////////////////////////////
// CBoundedNumberSubProp class

MSpinCtrlProp::MSpinCtrlProp(const CString& strName, const _variant_t& varValue, int nMinValue, int nMaxValue, LPCTSTR lpszDescr, DWORD_PTR dwData ) :
	MStaticProp(strName, varValue, lpszDescr, dwData)
{
	m_nMinValue = nMinValue;
	m_nMaxValue = nMaxValue;

	m_varValue.vt = VT_I4;
	m_varValue.intVal = varValue.intVal;
}

CSpinButtonCtrl* MSpinCtrlProp::CreateSpinControl(CRect rectSpin)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);

	CBCGPSpinButtonCtrl* pWndSpin = new CBCGPSpinButtonCtrl;

	if (!pWndSpin->Create(WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_SETBUDDYINT | UDS_NOTHOUSANDS, rectSpin, m_pWndList, AFX_PROPLIST_ID_INPLACE))
	{
		return NULL;
	}

	pWndSpin->SetBuddy(m_pWndInPlace);

	if (m_nMinValue != 0 || m_nMaxValue != 0)
	{
		pWndSpin->SetRange32(m_nMinValue, m_nMaxValue);
	}
	
	return pWndSpin;
}

BOOL MSpinCtrlProp::OnUpdateValue()
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT_VALID(m_pWndList);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	BOOL bRet = TRUE;
	CString strText;
	m_pWndInPlace->GetWindowText(strText);

	BOOL bIsChanged = FormatProperty() != strText;
	if (bIsChanged)
	{
		int nItem = _ttoi(strText);
		if ((nItem < m_nMinValue) || (nItem > m_nMaxValue))
		{
			static BOOL bRecursedHere = FALSE;
			if (bRecursedHere)
				return TRUE;
			bRecursedHere = TRUE;

			CString strMessage;
			strMessage.Format(_T("Value must be between %d and %d."), m_nMinValue, m_nMaxValue);
			AfxMessageBox(strMessage);

			bRecursedHere = FALSE;
			return FALSE;
		}

		bRet = MStaticProp::OnUpdateValue();

		if (m_pParent != NULL)
		{
			m_pWndList->OnPropertyChanged(m_pParent);
		}
	}

	return bRet;
}

void MSpinCtrlProp::OnClickName(CPoint point)
{

}

BOOL MSpinCtrlProp::OnClickValue(UINT uiMsg, CPoint point)
{
	BOOL bResult = MStaticProp::OnClickValue(uiMsg, point);

	return bResult;
}

// COptionPropertyGridColorProperty
IMPLEMENT_DYNAMIC(MOptionColorProp, CBCGPColorProp)

MOptionColorProp::MOptionColorProp(const CString& strName, const COLORREF& color, CPalette* pPalette, LPCTSTR lpszDescr, DWORD_PTR dwData)
:CBCGPColorProp(strName, color, pPalette, lpszDescr, dwData)
{
	m_bInitCtrl = FALSE;
}

MOptionColorProp::~MOptionColorProp()
{

}

void MOptionColorProp::OnClickName(CPoint point)
{

}

BOOL MOptionColorProp::OnClickValue(UINT uiMsg, CPoint point)
{
	BOOL bResult = FALSE;

	if( !m_bInitCtrl )
	{
		bResult = CBCGPProp::OnClickValue(uiMsg, point);
	}
	else
	{
		if (m_pWndInPlace == NULL)
		{
			return FALSE;
		}

		ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

		CString strText;
		m_pWndInPlace->GetWindowText(strText);

		point.x = m_Rect.left;

		bResult = TRUE;//CMFCPropertyGridProperty::OnClickValue(uiMsg, point);

		((CEdit*)m_pWndInPlace)->SetFocus();
		((CEdit*)m_pWndInPlace)->SetSel(0, -1);
	}

	return bResult;
}

void MOptionColorProp::OnDestroyWindow()
{
	if (m_pWndCombo != NULL)
	{
		m_pWndCombo->DestroyWindow();
		delete m_pWndCombo;
		m_pWndCombo = NULL;
	}

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->DestroyWindow();
		delete m_pWndInPlace;
		m_pWndInPlace = NULL;
	}

	if (m_pWndSpin != NULL)
	{
		m_pWndSpin->DestroyWindow();
		delete m_pWndSpin;
		m_pWndSpin = NULL;
	}

	if (m_varValue.vt == VT_BOOL)
	{
		m_lstOptions.RemoveAll();
	}

	m_bInitCtrl = FALSE;
}

BOOL MOptionColorProp::OnEdit(LPPOINT lptClick)
{
	CBCGPColorProp::OnEdit(lptClick);
	
	m_bInitCtrl = TRUE;
	return TRUE;
}

#undef ADD_BUTTON  
#undef SLIDER      

#undef TEXT_MARGIN
