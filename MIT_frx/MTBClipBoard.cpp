#include "stdafx.h"
#include "MTBClipBoard.h"

#include "MTable.h"
#include "MTBProgressCtrlHelper.h"

#include <ppl.h>
#include <ppltasks.h>

using namespace mit::frx;
using namespace mit::lib;
using namespace std;
using namespace concurrency;

#ifdef _UNICODE
#define _TCF_TEXT	CF_UNICODETEXT
#else
#define _TCF_TEXT	CF_TEXT
#endif

class MFriendGridRow : public MGridRow
{
	friend class MTBClipBoard;
};

class MFriendGridItem : public CBCGPGridItem
{
	friend class MTBClipBoard;
};

CString MTBClipboard::s_strTabSVColumnSeparator(_T("\t"));
CString MTBClipboard::s_strTabSVRowSeparator(_T("\r\n"));
CString MTBClipboard::s_strCSVColumnSeparator(_T(","));
CString MTBClipboard::s_strCSVRowSeparator(_T("\r\n"));

MTBClipboard::MTBClipboard(ITableDB* pTableDB) :
	m_pTableDB(pTableDB),
	m_pSchema(pTableDB->GetSchema()),
	m_pGridRow(nullptr)
{	
	m_pTable = dynamic_cast<MTable*>(pTableDB->GetTable());
	ASSERT(m_pTable);
	CWnd* pWndTable = dynamic_cast<CWnd*>(m_pTable);
	ASSERT_VALID(pWndTable); // ITable 은 윈도우여야 한다.

	InitTempVariable();
}

MTBClipboard::~MTBClipboard()
{
}

void MTBClipboard::InitTempVariable()
{
	m_bVisibleColumnOnly = FALSE;
	m_hasKeyColumn = FALSE;
	if (m_pGridRow) delete m_pGridRow;
	m_pGridRow = nullptr;
	m_aColumnOrder.clear();
	m_dwFlags = 0;
	m_range.Set(-1, -1, -1, -1);
	m_idPasteTo.SetNull();
	m_bPasteAppendRow = FALSE;
	ClearPasteRow();
}

int MTBClipboard::CopyPasteRowToVector(std::vector<LPCVOID>& aPasteRow)
{
	aPasteRow.reserve(m_lstPasteRow.GetCount());
	POSITION pos = m_lstPasteRow.GetHeadPosition();
	while (pos)
	{
		LPCVOID pRow = m_lstPasteRow.GetNext(pos);
		ASSERT(pRow);
		aPasteRow.push_back(pRow);
	}
	return (int)aPasteRow.size();
}

void MTBClipboard::ClearPasteRow()
{
	POSITION pos = m_lstPasteRow.GetHeadPosition();
	while (pos)
	{
		LPCVOID pRow = m_lstPasteRow.GetNext(pos);
		m_pSchema->DeleteData(pRow);
	}
	m_lstPasteRow.RemoveAll();
}

int MTBClipboard::GetPreAllocateLength(int nApproximateRowLength)
{
	int nRowCount = GetRowCount();
	int nPreAllocateLength = nApproximateRowLength * nRowCount;
	if (nRowCount < 10) nPreAllocateLength = (int)(nPreAllocateLength * 1.5);
	else if (nRowCount < 100) nPreAllocateLength = (int)(nPreAllocateLength * 1.4);
	else if (nRowCount < 1000) nPreAllocateLength = (int)(nPreAllocateLength * 1.3);
	else if (nRowCount < 10000) nPreAllocateLength = (int)(nPreAllocateLength * 1.2);
	else if (nRowCount < 100000) nPreAllocateLength = (int)(nPreAllocateLength * 1.1);
	else nPreAllocateLength = (int)(nPreAllocateLength * 1.05);
	return nPreAllocateLength;
}

BOOL MTBClipboard::Copy(DWORD dwFlags)
{
	if (GetTable()->GetCurSelItemID().IsNull()) 
	{
		GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("복사할 Cell 을 선택해야 합니다."));
		return FALSE;
	}
	if (!GetTable()->IsCopyEnabled()) { ASSERT(0); return FALSE; }

	// Range
	CBCGPGridRange& rangeData = m_range;
	CBCGPGridRange rangeTop;
	CBCGPGridRange rangeBottom;
	int nRowCount = GetCopyRange(rangeData, rangeTop, rangeBottom);
	if (nRowCount <= 0) { ASSERT(0); return FALSE; }
	BOOL bExportData = rangeData.m_nTop <= rangeData.m_nBottom;
	BOOL bExportExtraTop = rangeTop.m_nTop <= rangeTop.m_nBottom;
	BOOL bExportExtraBottom = rangeBottom.m_nTop <= rangeBottom.m_nBottom;
	if ( !(bExportData || bExportExtraTop || bExportExtraBottom) ) { ASSERT(0); return FALSE; }
	rangeData.m_nBottom = GetTable()->GetDBRowIndex(rangeData.m_nBottom);
	rangeData.m_nTop = GetTable()->GetDBRowIndex(rangeData.m_nTop);
	ASSERT(bExportData ? m_range.m_nTop <= m_range.m_nBottom : TRUE);
	ASSERT(bExportData ? m_range.m_nLeft <= m_range.m_nRight : TRUE);

	// ColumnOrder
	if (m_bVisibleColumnOnly)
	{
		int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount(TRUE);
		m_aColumnOrder.resize(nColumnCount);
		VERIFY(GetTable()->GetColumnsInfo().GetColumnOrderArray(m_aColumnOrder.data()) == nColumnCount);
	}
	else
	{
		int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount();
		m_aColumnOrder.resize(nColumnCount);
		for (int i = 0; i < nColumnCount; i++) m_aColumnOrder[i] = i;
	}
	
	// Default Format
	if (dwFlags == (DWORD)-1) dwFlags = CBCGPGridCtrl::Format_TabSV;
	// TabSV, CSV 둘 다 지정시, 둘 중 하나만 Export
	if (dwFlags & CBCGPGridCtrl::Format_TabSV && dwFlags & CBCGPGridCtrl::Format_CSV) dwFlags = CBCGPGridCtrl::Format_TabSV;
	// HTML 지원 안해
	if (dwFlags & CBCGPGridCtrl::Format_Html) { ASSERT(0); return FALSE; }	
	ASSERT(dwFlags & (CBCGPGridCtrl::Format_CSV | CBCGPGridCtrl::Format_TabSV));
	ASSERT(!(dwFlags & CBCGPGridCtrl::Format_Html));
	m_dwFlags = dwFlags;

	// Separator
	if (IsFormatCSV())
	{
		m_strColumnSeparator = s_strCSVColumnSeparator;
		m_strRowSeparator = s_strCSVRowSeparator;
	}
	else if (IsFormatTabSV())
	{
		m_strColumnSeparator = s_strTabSVColumnSeparator;
		m_strRowSeparator = s_strTabSVRowSeparator;
	}
	else ASSERT(0);

	// HasKeyColumn
	m_hasKeyColumn = FALSE;
	for (int i = m_range.m_nLeft; i <= m_range.m_nRight; i++)
	{
		int nCol = m_aColumnOrder[i];
		const MTBColumn& column = GetSchema()->GetColumn(nCol);
		if (column.GetType() == MTBColumn::TB_KEY) 
		{
			m_hasKeyColumn = TRUE;
			break;
		}
	}

	// TaskCount
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int nTaskCount = sysInfo.dwNumberOfProcessors == 1 ? 1 : sysInfo.dwNumberOfProcessors + 1; 

	// Text
	CStringArray aText;
	aText.SetSize(nTaskCount + 2);
	CString& strExtraTop = aText[0];
	CString& strExtraBottom = aText[nTaskCount + 1];

	// Export
	if (bExportExtraTop) 
	{
		// ExportRangeToText 원래는 대체 함수를 직접 짜야 하는데...
		// 시간관계상... ExtraTop, Bottom 이 너무 커서 Cache 가 넘치면 안됨
		for (int nRow = rangeTop.m_nTop; nRow <= rangeTop.m_nBottom; nRow++) GetTable()->GetRow(nRow);
		GetTable()->ExportRangeToText(strExtraTop, rangeTop, m_dwFlags);
		//if (strExtraTop.IsEmpty()) { ASSERT(0); return FALSE; } -> empty 인 Cell 하나 선택해서 복사하면 발생함.
		strExtraTop.Append(m_strRowSeparator);
	}
	if (bExportExtraBottom) 
	{
		// ExportRangeToText 원래는 대체 함수를 직접 짜야 하는데...
		// 시간관계상... ExtraTop, Bottom 이 너무 커서 Cache 가 넘치면 안됨
		for (int nRow = rangeBottom.m_nTop; nRow <= rangeBottom.m_nBottom; nRow++) GetTable()->GetRow(nRow);
		GetTable()->ExportRangeToText(strExtraBottom, rangeBottom, m_dwFlags);
		//if (strExtraBottom.IsEmpty()) { ASSERT(0); return FALSE; } -> empty 인 Cell 하나 선택해서 복사하면 발생함.
		strExtraBottom.Append(m_strRowSeparator);
	}
	if (bExportData)
	{
		m_pGridRow = GetTable()->CreateDummyRow(FALSE);
		ASSERT_VALID(m_pGridRow);
		if (nTaskCount == 1)
			Export(aText[1]);
		else
			ParallelExport(nTaskCount, aText.GetData() + 1);

		int i = 0;
		for (;i < nTaskCount; i++) { if (!aText[i+1].IsEmpty()) break; }
		ASSERT(i < nTaskCount);
	}

	// CopyTextToClipboard
	CInitTempVariable initTempVariable(this);
	if (!CopyTextToClipboard(aText)) return FALSE;

	GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("%d 개의 행이 복사되었습니다."), nRowCount);
	return TRUE;
}

int MTBClipboard::GetCopyRange(CBCGPGridRange& rangeData, CBCGPGridRange& rangeTop, CBCGPGridRange& rangeBottom)
{
	// GetRange
	if (GetTable()->m_lstSel.IsEmpty()) { ASSERT(0); return 0; }
	if (GetTable()->m_lstSel.GetCount() > 1)
	{
		GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_HELP, _STR("여러 범위를 선택했을 경우 마지막에 선택한 범위만 복사됩니다."));
	}
	CBCGPGridRange* pRange = GetTable()->m_lstSel.GetTail();
	ASSERT(pRange);

	// 엑셀 데이터 갯수 제한
	//  "Excel에서는 1,048,576개의 행과 16,384개의 열 제한을 초과할 수 없습니다."
	// 라고 한다. ( 2^20 개의 행, 2^14 개의 열 )	
	// 엑셀이 지원하는 만큼만 지원한다.
	// 천만개도 가능은 한데 필요가 있을지...
	int nRowCount = pRange->m_nBottom - pRange->m_nTop + 1;
	ASSERT(nRowCount > 0);
	if (nRowCount > (0x01 << 20))
	{
		GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("1,048,576 개의 행까지만 복사가 가능합니다."));
		return 0;
	}

	// GetRange
	rangeData.Set(*pRange);
	if (m_bVisibleColumnOnly)
	{
		rangeData.m_nLeft = GetTable()->GetColumnsInfo().IndexToOrder(rangeData.m_nLeft);
		rangeData.m_nRight = GetTable()->GetColumnsInfo().IndexToOrder(rangeData.m_nRight);		
	}
	rangeData.Normalize();
	rangeTop.Set(rangeData);
	rangeBottom.Set(rangeData);
	if (rangeData.m_nTop < GetTable()->GetExtraTopRowCount()) rangeData.m_nTop = GetTable()->GetExtraTopRowCount();
	if (rangeData.m_nBottom >= GetTable()->GetDataRowEndIndex()) rangeData.m_nBottom = GetTable()->GetDataRowEndIndex() - 1;
	if (rangeTop.m_nBottom > GetTable()->GetExtraTopRowCount() - 1) rangeTop.m_nBottom = GetTable()->GetExtraTopRowCount() - 1;
	if (rangeBottom.m_nTop < GetTable()->GetDataRowEndIndex()) rangeBottom.m_nTop = GetTable()->GetDataRowEndIndex();

	return nRowCount;
}

BOOL MTBClipboard::CopyTextToClipboard(const CStringArray& aText) const
{
	HWND hTable = GetTable()->GetSafeHwnd();

	// Clipboard
	try
	{
		if (!::OpenClipboard(hTable))
		{
			TRACE0("Can't open clipboard\n");
			return FALSE;
		}

		if (!::EmptyClipboard())
		{
			TRACE0("Can't empty clipboard\n");
			::CloseClipboard();
			return FALSE;
		}

		// Copy CF_TEXT to clipboard:
		//if (dwFlags & (CBCGPGridCtrl::Format_TabSV | CBCGPGridCtrl::Format_CSV))
		//{
		if (!CopyTextToClipboardInternal(aText)) 
		{
			::CloseClipboard(); 
			return FALSE; 
		}
		//}

		// Serialize Copy 지원안함

		::CloseClipboard();
	}
	catch (...)
	{
		TRACE0("Copy: out of memory\n");
	}

	return TRUE;
}

HGLOBAL MTBClipboard::CopyTextToClipboardInternal(const CStringArray& aText) const
{
	HGLOBAL hClipbuffer = NULL;

	ASSERT(aText.GetCount() <= INT_MAX);
	int nStringCount = (int)aText.GetCount();
	int nTotalLen = 0;
	for (int i = 0; i < nStringCount; i++)
		nTotalLen += aText[i].GetLength();

	try
	{
		SIZE_T cbFinalSize = (nTotalLen + 1) * sizeof(TCHAR);

		hClipbuffer = ::GlobalAlloc (GMEM_DDESHARE, cbFinalSize);

		if (hClipbuffer == NULL)
		{
			TRACE0("CopyTextToClipboardInternal: out of memory\n");
			return NULL;
		}

		LPTSTR lpBuffer = (LPTSTR) ::GlobalLock (hClipbuffer);
		if (lpBuffer == NULL)
		{
			TRACE0("CopyTextToClipboardInternal: out of memory\n");
			::GlobalFree (hClipbuffer);
			return NULL;
		}

		for (int i = 0; i < nStringCount; i++)
		{
			memcpy (lpBuffer, (LPCTSTR)aText[i], aText[i].GetLength() * sizeof(TCHAR)); 
			lpBuffer += aText[i].GetLength();
		}
		*lpBuffer = _T ('\0');

		::GlobalUnlock (hClipbuffer);
		::SetClipboardData (_TCF_TEXT, hClipbuffer);
	}
	catch (CMemoryException*)
	{
		TRACE0("CopyTextToClipboardInternal: out of memory\n");
	}
	catch (...)
	{
	}

	return hClipbuffer;
}

BOOL MTBClipboard::Import(const CString& strText)
{
	// TODO: Text 쪼개서 병렬처리
	// TODO: 꼬리 떼기
	// TODO: Display Mapping 실패시 처리 ( GridItem 의 varValue 가 EMPTY 일때 TextToVar() 실패 )
	CInitTempVariable initTempVariable(this);
	int nPastedRow = (m_bPasteAppendRow ? ImportAppend(strText) : ImportModify(strText));
	if (nPastedRow <= 0) return FALSE;
	GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_COMMIT, 
		(m_bPasteAppendRow ? _STR("%d 개의 데이터가 추가되었습니다.") : _STR("%d 개의 데이터가 수정되었습니다.")), nPastedRow);
	return TRUE;
}

BOOL MTBClipboard::Paste()
{
	if (GetTable()->IsReadOnly()) return FALSE;
	if (GetTable()->IsEditingRow()) return FALSE;

	CBCGPGridRow* pSel = GetTable()->GetCurSel();
	if (pSel && pSel->IsInPlaceEditing()) return FALSE;
	
	// id
	CBCGPGridItemID& idPasteTo = m_idPasteTo;
	idPasteTo = GetTable()->GetCurSelItemID();
	if (idPasteTo.m_nRow == -1) idPasteTo.m_nRow = 0;
	if (idPasteTo.m_nColumn == -1 || GetTable()->IsWholeRowSel()) idPasteTo.m_nColumn = 0;
	if (idPasteTo.m_nRow < GetTable()->GetExtraTopRowCount()) return FALSE;
	if (m_bVisibleColumnOnly) idPasteTo.m_nColumn = GetTable()->GetColumnsInfo().IndexToOrder(idPasteTo.m_nColumn);

	// AppendRow
	if (idPasteTo.m_nRow == GetTable()->GetDataRowEndIndex()) m_bPasteAppendRow = TRUE;
	else m_bPasteAppendRow = FALSE; 
	idPasteTo.m_nRow = GetTable()->GetDBRowIndex(idPasteTo.m_nRow);

	// ColumnOrder
	int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount(m_bVisibleColumnOnly);
	if (m_bVisibleColumnOnly)
	{
		m_aColumnOrder.resize(nColumnCount);
		VERIFY(GetTable()->GetColumnsInfo().GetColumnOrderArray(m_aColumnOrder.data()) == nColumnCount);
	}
	else
	{
		m_aColumnOrder.resize(nColumnCount);
		for (int i = 0; i < nColumnCount; i++) m_aColumnOrder[i] = i;
	}

	// HasKeyColumn
	m_hasKeyColumn = FALSE;
	for (int i = idPasteTo.m_nColumn; i < nColumnCount; i++)
	{
		int nCol = m_aColumnOrder[i];
		const MTBColumn& column = GetSchema()->GetColumn(nCol);
		if (column.GetType() == MTBColumn::TB_KEY) 
		{
			m_hasKeyColumn = TRUE;
			break;
		}
	}

	return PasteTextFromClipboard();
}

BOOL MTBClipboard::CheckTextFormat(const CString& strText)
{
	CString strTemp = strText.Left(MAX_ITEM_STRING_LENGTH);

	int nColumnSeparator = strTemp.Find(s_strTabSVColumnSeparator);
	if (nColumnSeparator > 0) 
	{
		m_strColumnSeparator = s_strTabSVColumnSeparator;
		m_strRowSeparator = s_strTabSVRowSeparator;
		return TRUE;
	}

	nColumnSeparator = strTemp.Find(s_strCSVColumnSeparator);
	if (nColumnSeparator > 0) 
	{
		m_strColumnSeparator = s_strCSVColumnSeparator;
		m_strRowSeparator = s_strCSVRowSeparator;
		return TRUE;
	}

	if (strText.GetLength() < MAX_ITEM_STRING_LENGTH)
	{
		// 한 Item 혹은 한 Column 으로 취급
		ASSERT(s_strTabSVRowSeparator == s_strCSVRowSeparator);
		m_strColumnSeparator = s_strTabSVColumnSeparator;
		m_strRowSeparator = s_strTabSVRowSeparator;
		return TRUE;
	}

	GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("TSV 혹은 CSV 형식의 텍스트만 붙여넣기가 가능합니다."));
	return FALSE;
}

BOOL MTBClipboard::PasteTextFromClipboard()
{
	HWND hTable = GetTable()->GetSafeHwnd();

	try
	{
		if (!::IsClipboardFormatAvailable(_TCF_TEXT)) return FALSE;

		if (!::OpenClipboard(hTable))
		{
			TRACE0("Can't open clipboard\n");
			return FALSE;
		}

		HGLOBAL hClipbuffer = ::GetClipboardData(_TCF_TEXT);
		if (hClipbuffer == NULL)
		{
			TRACE0("PasteTextFromClipboard: out of memory\n");
			return NULL;
		}

		LPTSTR lpBuffer = (LPTSTR)::GlobalLock(hClipbuffer);
		if (lpBuffer == NULL)
		{
			TRACE0("PasteTextFromClipboard: \n");
			::GlobalUnlock(hClipbuffer);
			::CloseClipboard();		
			return NULL;
		}

		CString strText(lpBuffer);
		if (!CheckTextFormat(strText))
		{
			TRACE0("PasteTextFromClipboard: \n");
			::GlobalUnlock(hClipbuffer);
			::CloseClipboard();		
			return FALSE;
		}

		m_pGridRow = GetTable()->CreateDummyRow(TRUE);
		ASSERT_VALID(m_pGridRow);
		if (!Import(strText))
		{
			TRACE0("PasteTextFromClipboard: \n");
			::GlobalUnlock(hClipbuffer);
			::CloseClipboard();		
			ClearPasteRow();
			return FALSE;
		}	
		ClearPasteRow();

		::GlobalUnlock(hClipbuffer);
		::CloseClipboard();		
	}
	catch (CMemoryException*)
	{
		TRACE0("PasteTextFromClipboard: out of memory\n");
	}
	catch (...)
	{

	}

	return TRUE;
}

BOOL MTBClipboard::GetNextRowText(const CString& strText, CString& strRow, int& nCurIndex)
{
	int nRowEndIndex;
	while (TRUE) 
	{
		nRowEndIndex = strText.Find(m_strRowSeparator, nCurIndex);
		if (nRowEndIndex == nCurIndex)
		{
			nCurIndex = nRowEndIndex + m_strRowSeparator.GetLength();
			continue;
		}
		if (nRowEndIndex < 0)
		{
			strRow = strText.Mid(nCurIndex, strText.GetLength() - nCurIndex);
			return TRUE;
		}
		if (nRowEndIndex > nCurIndex)
		{
			nCurIndex = nRowEndIndex + m_strRowSeparator.GetLength();
			strRow = strText.Mid(nCurIndex, nRowEndIndex - nCurIndex);
			return TRUE;
		}
	}	
}