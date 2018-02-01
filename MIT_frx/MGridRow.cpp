#include "stdafx.h"
#include "MGridRow.h"

#include "MPreTable.h"

using namespace mit;
using namespace mit::frx;

class MFriendGridCtrl : public CBCGPGridCtrl
{
	friend class MGridRow;
};

IMPLEMENT_SERIAL(MGridRow, CBCGPGridRow, VERSIONABLE_SCHEMA | 1)
MGridRow::MGridRow (const CString& strGroupName, DWORD_PTR dwData, int nBlockSize) :
CBCGPGridRow( strGroupName, dwData, nBlockSize ),
m_pCachedRow(NULL)
{
	
}
//******************************************************************************************
MGridRow::MGridRow (int nColumnsNum, DWORD_PTR dwData, int nBlockSize) :
	CBCGPGridRow ( nColumnsNum, dwData, nBlockSize ),
	m_pCachedRow(NULL)
{
	
}

MGridRow::~MGridRow()
{
	ASSERT(m_nIdRow >= 0 && GetTable() ? GetTable()->GetEditingRow() != m_nIdRow : TRUE);
	
	int nSize = (int)m_arrRowItems.GetSize();
	for(int i=0;i<nSize; ++i)
	{
		_SAFE_DELETE(m_arrRowItems[i]);
	}

	m_arrRowItems.RemoveAll();
}

LPCVOID MGridRow::GetCachedRow() const
{
	MTable* pTable = GetTable();
	if (!m_pCachedRow) m_pCachedRow = pTable->GetTableDB()->GetRow(pTable->GetDBRowIndex(m_nIdRow));
	return m_pCachedRow;
}

LPCVOID MGridRow::GetDBData() const
{	
	MTable* pTable = GetTable();
	MTBSchemaBase* pSchema = pTable->GetSchema();

	if (m_nIdRow < pTable->GetExtraTopRowCount()) return NULL;
	if (m_nIdRow < pTable->GetDataRowEndIndex() && m_nIdRow != pTable->GetEditingRow()) return GetCachedRow();
	if (m_nIdRow != pTable->GetEditingRow()) return pSchema->GetDefaultData();
	ASSERT(m_nIdRow == pTable->GetEditingRow() && pTable->IsEditingRow());

	LPVOID pRow = pTable->IsAppendingRow() ? 
		pSchema->GetDefaultData() : 
		pSchema->GetCopyData(GetCachedRow());

	ASSERT(pSchema->GetColumnCount() == (int)m_arrRowItems.GetSize());
	int nItemCount = (int)m_arrRowItems.GetSize();

	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		if (column.IsKeyType()) continue;
		if (m_arrRowItems[i]->IsInPlaceEditing())
		{
			// TODO: 편집 중일때의 값 바로 파싱
		}
		column.SetItem(pRow, m_arrRowItems[i]->GetValue());
	}

	return pRow;
}

void MGridRow::OnDrawItems (CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	MFriendGridCtrl* pWndList = reinterpret_cast<MFriendGridCtrl*>(m_pWndList);
	ASSERT_VALID( pWndList );

	rect.NormalizeRect ();
	const int nFreezeOffset = pWndList->m_rectList.left + pWndList->GetColumnsInfo ().GetFreezeOffset ();

	for (int i = 0; i < m_arrRowItems.GetSize (); i++)
	{
		CBCGPGridItem* pItem = m_arrRowItems [i];
		ASSERT_VALID (pItem);

		CRect rectValue = pItem->GetRect ();
		if (!rectValue.IsRectEmpty ())
		{
			if (pItem->GetMergedCells () != NULL)
			{
				// Item is a part of merged item - Draw item later.
				pWndList->RedrawMergedItem (pItem);
				continue;
			}

			rectValue.NormalizeRect ();

			CRect rectClipItem = rectValue;

			// frozen columns:
			if (pWndList->GetColumnsInfo ().IsFreezeColumnsEnabled () &&
				!pWndList->GetColumnsInfo ().IsColumnFrozen (i))
			{
				// Do not allow unfrozen columns to draw inside the frozen area
				rectClipItem.left = max (nFreezeOffset, rectClipItem.left);
				if (rectClipItem.left >= rectClipItem.right)
				{
					continue;
				}
			}

			rectClipItem.IntersectRect (rectClipItem, rect);

			CRect rectBordersSize (0, 0, 0, 0);
			if (pWndList->m_bGridItemBorders)
			{
				pItem->OnGetBorders (rectBordersSize);
				rectClipItem.InflateRect (rectBordersSize);
			}

			pWndList->m_rgnClipItem.CreateRectRgnIndirect (&rectClipItem);
			pDC->SelectClipRgn (&pWndList->m_rgnClipItem);

			pItem->OnDrawValue (pDC, rectValue);

			if (pWndList->m_bGridItemBorders)
			{
				pItem->OnDrawBorders (pDC, rectValue);
			}

			if (!pItem->GetButtonRect().IsRectEmpty ())
			{
				pItem->OnDrawButton (pDC, pItem->GetButtonRect());
			}

			pDC->SelectClipRgn (&pWndList->m_rgnClipRow);
			pWndList->m_rgnClipItem.DeleteObject ();
		}
	}
}

void MGridRow::OnDrawEditingRowMarker(CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pWndList);
	MPreTable* pTable = DYNAMIC_DOWNCAST(MPreTable, m_pWndList);
	ASSERT(pTable);
	ASSERT (!IsGroup () || pTable->IsAppendRowMarkerOnRowHeader ());

	COLORREF clrText = pTable->m_ColorData.m_HeaderColors.m_clrText;
	COLORREF clrTextOld = (COLORREF)-1;
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	CRect rectLabel = rect;
	rectLabel.DeflateRect (TEXT_MARGIN, 0);

	UINT uiTextFlags = DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_CENTER;
	if (GetLinesNumber() == 1) uiTextFlags |= DT_VCENTER;
	else rectLabel.DeflateRect(0, 2); // TEXT_VMARGIN = 2

	pDC->DrawText (_T("*"), rectLabel, uiTextFlags);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}
}

void MGridRow::OnDrawAppendRowMarker(CDC* pDC, CRect rect)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (m_pWndList);
	MPreTable* pTable = DYNAMIC_DOWNCAST(MPreTable, m_pWndList);
	ASSERT(pTable);
	ASSERT (!IsGroup () || pTable->IsAppendRowMarkerOnRowHeader ());

	COLORREF clrText = pTable->m_ColorData.m_HeaderColors.m_clrText;
	COLORREF clrTextOld = (COLORREF)-1;
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	CRect rectLabel = rect;
	rectLabel.DeflateRect (TEXT_MARGIN, 0);

	UINT uiTextFlags = DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_CENTER;
	if (GetLinesNumber() == 1) uiTextFlags |= DT_VCENTER;
	else rectLabel.DeflateRect(0, 2); // TEXT_VMARGIN = 2

	pDC->DrawText (_T("+"), rectLabel, uiTextFlags);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	//	ASSERT_VALID (this);
	//	ASSERT_VALID (pDC);
	//	ASSERT_VALID (m_pWndList);
	//	MPreTable* pTable = DYNAMIC_DOWNCAST(MPreTable, m_pWndList);
	//	ASSERT(pTable);
	//	ASSERT (!IsGroup () || pTable->IsAppendRowMarkerOnRowHeader ());
	//
	//	if (pTable->m_bIsPrinting) return;
	//
	//	CPoint ptCenter = rect.CenterPoint ();
	//
	//	int nBoxSize = min (9, rect.Width ());
	//
	//	rect = CRect (ptCenter, CSize (1, 1));
	//	rect.InflateRect (nBoxSize / 2, nBoxSize / 2);
	//
	//#ifndef _BCGPGRID_STANDALONE
	//	COLORREF clr = globalData.clrWindow;
	//
	//	if (pTable->m_ColorData.m_LeftOffsetColors.m_clrBackground != (COLORREF)-1)
	//	{
	//		clr = pTable->m_ColorData.m_LeftOffsetColors.m_clrBackground;
	//	}
	//
	//	CBCGPMenuImages::DrawByColor(pDC, CBCGPMenuImages::IdMaximizeRibbon, rect.TopLeft (), clr);
	//#else
	//	visualManager->OnDrawRowMarker (pDC, rect);
	//#endif

}

BOOL MGridRow::OnEdit(LPPOINT lptClick)
{
	//if (!CBCGPGridRow::OnEdit(lptClick)) return FALSE;

	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);
	MTable* pTable = GetTable();
	if (!HasValueField () || !pTable->AllowInPlaceEdit ()) return FALSE;

	CBCGPGridItem* pItem = NULL;
	if (lptClick == NULL)
	{
		pItem = pTable->GetCurSelItem (this);
	}
	else
	{
		for (int i = 0; i < m_arrRowItems.GetSize (); i++)
		{
			CBCGPGridItem* pCurItem = m_arrRowItems [i];
			ASSERT_VALID (pCurItem);
			if (pCurItem->GetRect().PtInRect (*lptClick) && pCurItem->IsEnabled()) { pItem = pCurItem; break; }
		}
	}

	if (pItem == NULL) return FALSE;
	if (!pItem->IsAllowEdit ()) return FALSE;

	// 원래 pItem->OnEdit() 뒤에 호출했으나 Appending Row의 Default Value 를 채우기 위해 먼저 호출한다.
	if (!pTable->OnEdit(this)) return FALSE;

	m_bInPlaceEdit = pItem->OnEdit(lptClick);
	if (!m_bInPlaceEdit)
	{ 
		//VERIFY(pTable->OnCancelEditingRow(this));
		return FALSE; 
	}

	//// 편집 시작할때
	//// BCG 쪽에서 InPlaceEdit 을 생성하는 등의 작업을 함.
	//// 다른 문제로 return FALSE 해야 경우 생성되었던 것들 정리해준다.
	//if (!pTable->OnEdit(this))
	//{
	//	// 근데 딱히 들어오는 상황은 없을듯...
	//	pTable->EndEditItem(FALSE);
	//	return FALSE;
	//}

	return TRUE;
}

BOOL MGridRow::OnEndEdit()
{
	// Item 편집 끝날때
	ASSERT_VALID (m_pWndList);
	MTable* pTable = DYNAMIC_DOWNCAST(MTable, m_pWndList);
	ASSERT(pTable);

	if (!pTable->OnEndEdit(this)) return FALSE;

	// BCG 쪽에서 InPlaceEdit 을 날리는 등의 작업을 함.
	// 다른 문제로 return FALSE 해야 경우 InPlaceEdit 을 날리지 말아야 하므로
	// BCG 쪽 함수를 나중에 호출한다.
	return CBCGPGridRow::OnEndEdit();
}
