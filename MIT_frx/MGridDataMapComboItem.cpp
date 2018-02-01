#include "stdafx.h"
#include "MGridDataMapComboItem.h"

#include "MGridRow.h"
#include "MTable.h"
#include "MGridColumnsInfo.h"

using namespace mit;
using namespace mit::frx;

class CFriendTable : public MTable
{
	friend class MGridDataMapComboItem;
};

IMPLEMENT_SERIAL(MGridDataMapComboItem, MGridItem, VERSIONABLE_SCHEMA | 1)

MGridDataMapComboItem::MGridDataMapComboItem() :
	m_pDisplayMap(NULL),
	m_bDropList(FALSE)
{
	ASSERT(0);
	// DisplayMap 지정해서 생성
}

MGridDataMapComboItem::MGridDataMapComboItem(ITBDataMap* pDisplayMap) :
	m_pDisplayMap(pDisplayMap),
	m_bDropList(FALSE)
{
	ASSERT(m_pDisplayMap);
}

MGridDataMapComboItem::~MGridDataMapComboItem(void)
{

}

void MGridDataMapComboItem::Init()
{
	m_bReadOnly = TRUE;
}

void MGridDataMapComboItem::SetFlags()
{
	m_dwFlags |= BCGP_GRID_ITEM_HAS_LIST;
}

BOOL MGridDataMapComboItem::OnEdit(LPPOINT lptClick)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	if (!m_bAllowEdit)
	{
		return FALSE;
	}

	CFriendTable* pTable = (CFriendTable*)GetOwnerList();
	ASSERT_VALID (DYNAMIC_DOWNCAST(MTable, GetOwnerList()));

	if (m_bReadOnly && (pTable->m_dwBeginEditReason & CBCGPGridCtrl::BeginEdit_Char) != 0)
	{
		if ((m_dwFlags & BCGP_GRID_ITEM_HAS_LIST) == 0 && m_pDisplayMap->GetCount () == 0)
		{
			return FALSE;
		}
	}

	m_pWndInPlace = NULL;

	OnBeginInplaceEdit ();

	CRect rectEdit;
	CRect rectSpin;

	AdjustInPlaceEditRect (rectEdit, rectSpin);

	BOOL bDefaultFormat = FALSE;
	m_pWndInPlace = CreateInPlaceEdit (rectEdit, bDefaultFormat);

	pTable->OnAfterInplaceEditCreated (this, m_pWndInPlace);

	if (m_pWndInPlace != NULL)
	{
		if (bDefaultFormat)
		{
			m_pWndInPlace->SetWindowText (FormatItem ());
		}

		if (m_dwFlags & BCGP_GRID_ITEM_HAS_LIST)
		{
			CRect rectCombo = m_Rect;
			rectCombo.left = rectEdit.left - 4;

			m_pWndCombo = CreateCombo (pTable, rectCombo);
			ASSERT_VALID (m_pWndCombo);

			SetComboFont ();

			//-------------------------------------------------------------------
			// Synchronize bottom edge of the combobox with the item bottom edge:
			//-------------------------------------------------------------------
			m_pWndCombo->GetWindowRect (rectCombo);
			pTable->ScreenToClient (&rectCombo);

			int dy = rectCombo.Height () - m_Rect.Height ();

			m_pWndCombo->SetWindowPos (NULL, rectCombo.left,
				rectCombo.top - dy + 1, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

			MStoreGridItemValue storeValue(m_varValue);
			for (POSITION pos = m_pDisplayMap->GetHeadPosition (); pos != NULL;)
			{
				m_varValue = m_pDisplayMap->GetNext(pos);
				m_pWndCombo->AddString(FormatItem());
			}
		}

		if (m_dwFlags & BCGP_GRID_ITEM_HAS_SPIN)
		{
			m_pWndSpin = CreateSpinControl (rectSpin);
		}

		SetInPlaceEditFont ();
		m_pWndInPlace->SetFocus ();

		if (!m_bAllowEdit)
		{
			m_pWndInPlace->HideCaret ();
		}

		m_bInPlaceEdit = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL MGridDataMapComboItem::OnDblClick(CPoint point)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);

	if (m_pWndInPlace == NULL)
	{
		return FALSE;
	}

	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));

	if (m_pDisplayMap->GetCount () > 1)
	{
		CString strText;
		m_pWndInPlace->GetWindowText (strText);

		{
			MStoreGridItemValue storeValue(m_varValue);
			if (!TextToVar(strText)) return FALSE;

			POSITION pos = m_pDisplayMap->Find(m_varValue);
			if (pos == NULL)
			{
				return FALSE;
			}

			m_pDisplayMap->GetNext(pos);
			if (pos == NULL)
			{
				pos = m_pDisplayMap->GetHeadPosition();
			}

			ASSERT (pos != NULL);
			m_varValue = m_pDisplayMap->GetAt(pos);

			m_pWndInPlace->SetWindowText(FormatItem());
		}
		OnUpdateValue ();

		return TRUE;
	}

	if (m_dwFlags & BCGP_GRID_ITEM_HAS_LIST)
	{
		CWaitCursor wait;

		CString strPrevVal = GetLabel ();

		OnClickButton (CPoint (-1, -1));

		if (strPrevVal != FormatItem ())
		{
			SetItemChanged ();
		}

		return TRUE;
	}

	return FALSE;
}

BOOL MGridDataMapComboItem::PushChar(UINT nChar)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pGridRow);
	ASSERT (m_pGridRow->IsSelected ());//ASSERT (m_pWndList->m_pSel == this);
	ASSERT_VALID (m_pWndInPlace);

	CFriendTable* pTable = (CFriendTable*)GetOwnerList();
	ASSERT_VALID (DYNAMIC_DOWNCAST(MTable, GetOwnerList()));

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
	case VT_UI2:
	case VT_UI4:
		if (m_bEnabled && m_bAllowEdit && !m_bReadOnly)
		{
			if (nChar == VK_RETURN && 
				pTable != NULL && !pTable->m_bClearInplaceEditOnEnter)
			{
				pTable->DoInplaceEditSetSel (
					pTable->OnInplaceEditSetSel (this, CBCGPGridCtrl::BeginEdit_Return));
				return TRUE;
			}

			m_pWndInPlace->SetWindowText (_T(""));
			m_pWndInPlace->SendMessage (WM_CHAR, (WPARAM) nChar);
			return TRUE;
		}
	}

	if (!m_bAllowEdit || m_bReadOnly)
	{
		if (nChar == VK_SPACE)
		{
			OnDblClick (CPoint (-1, -1));
		}
		else if (m_lstOptions.GetCount () > 1)
		{
			CString strText;
			m_pWndInPlace->GetWindowText (strText);

			// 미구현
			ASSERT(0);

			POSITION pos = m_lstOptions.Find (strText);
			if (pos == NULL)
			{
				return FALSE;
			}

			POSITION posSave = pos;
			CString strChar;
			strChar += (TCHAR) nChar;
			strChar.MakeUpper ();

			m_lstOptions.GetNext (pos);

			while (pos != posSave)
			{
				if (pos == NULL)
				{
					pos = m_lstOptions.GetHeadPosition ();
				}

				if (pos == posSave)
				{
					break;
				}

				strText = m_lstOptions.GetAt (pos);

				CString strUpper = strText;
				strUpper.MakeUpper ();

				if (strUpper.Left (1) == strChar)
				{
					m_pWndInPlace->SetWindowText (strText);
					OnUpdateValue ();
					break;
				}

				m_lstOptions.GetNext (pos);
			}
		}
	}

	OnEndEdit ();
	
	if (::GetCapture () == pTable->GetSafeHwnd ())
	{
		ReleaseCapture ();
	}

	return FALSE;
}