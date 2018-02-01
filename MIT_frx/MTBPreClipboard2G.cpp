#include "stdafx.h"
#include "MTBPreClipboard2G.h"

#include "MTable.h"
#include "MPreTableDB2G.h"
#include "MTBProgressCtrlHelper.h"

#include <ppl.h>
#include <ppltasks.h>

using namespace mit::frx;
using namespace mit::lib;
using namespace std;
using namespace concurrency;

MTBPreClipboard2G::MTBPreClipboard2G(ITableDB* pTableDB) : 
	MTBClipboard(pTableDB)
{
}

MTBPreClipboard2G::~MTBPreClipboard2G()
{
}

int MTBPreClipboard2G::GetApproximateRowLength(const std::vector<MKey>& aKey, const std::vector<LPCVOID>& aRow)
{
	int nRowCount = GetRowCount();
	int nSampleRowCount = min(nRowCount, SAMPLE_ROW_COUNT);
	MSimpleProfiler sp(_T("GetApproximateRowLength(%d)"), nSampleRowCount); // 배보다 배꼽이 크면 안되겠지

	int nTotalSampleLength = 0;
	double dFactor = (double)nRowCount / (double)nSampleRowCount;
	for (int i = 0; i < nSampleRowCount; i++)
	{
		CString strSample;
		int nIndex = (int)(i * dFactor);
		ASSERT(nIndex >= 0 && nIndex < nRowCount);
		ExportRowToText(strSample, m_hasKeyColumn ? aKey[nIndex] : 0, aRow[nIndex], m_pGridRow);
		strSample.Append(m_strRowSeparator);
		nTotalSampleLength += strSample.GetLength();
	}
	return nTotalSampleLength / nSampleRowCount;
}

void MTBPreClipboard2G::Export(CString& strText)
{
	int nRowCount = GetRowCount();
	int nColCount = GetColCount();
	MSimpleProfiler sp(_T("Export(%d, %d)"), nRowCount, nColCount);

	std::vector<MKey> aKey;
	std::vector<LPCVOID> aRow;
	if (m_hasKeyColumn) GetPreTableDB2G()->GetKeyLange(aKey, m_range.m_nTop, m_range.m_nBottom);
	GetPreTableDB2G()->GetRowLange(aRow, m_range.m_nTop, m_range.m_nBottom);

	int nApproximateRowLength = GetApproximateRowLength(aKey, aRow);
	int nPreAllocateLength = GetPreAllocateLength(nApproximateRowLength);

	strText.Preallocate(nPreAllocateLength);
	for (int i = 0; i < nRowCount; i++)
	{
		ExportRowToText(strText, m_hasKeyColumn ? aKey[i] : 0, aRow[i], m_pGridRow);
		strText.Append(m_strRowSeparator);
	}

	// TODO: 적절한 배율로 조절
	// 버그는 아니고 String 재할당이 일어났다능...
	// 재할당 안일어나게 하려면 GetPreAllocateLength() 에서 배율을 좀 더 조절해보시라능...
	ASSERT(nPreAllocateLength >= strText.GetLength());
	CString strPreAlloc;
	strPreAlloc.Format(_T("PreAllocateLength: %d, StringLength: %d"), nPreAllocateLength, strText.GetLength());
	OutputDebugString(strPreAlloc);
}

void MTBPreClipboard2G::ParallelExport(int nTaskCount, CString* aText)
{
	int nRowCount = GetRowCount();
	int nColCount = GetColCount();
	MSimpleProfiler sp(_T("ParallelExport(%d, %d)"), nRowCount, nColCount);

	std::vector<MKey> aKey;
	std::vector<LPCVOID> aRow;
	if (m_hasKeyColumn) GetPreTableDB2G()->GetKeyLange(aKey, m_range.m_nTop, m_range.m_nBottom);
	GetPreTableDB2G()->GetRowLange(aRow, m_range.m_nTop, m_range.m_nBottom);

	int nApproximateRowLength = GetApproximateRowLength(aKey, aRow);
	int nPreAllocateLength = GetPreAllocateLength(nApproximateRowLength);
	int nPreTaskAllocateLength = (int)(nPreAllocateLength / (double)nTaskCount);

	for (int i = 0; i < nTaskCount; i++) aText[i].Preallocate(nPreTaskAllocateLength);

	int nRowCountPerTask = nRowCount / nTaskCount;
	int nStartIndex = 0;
	int nEndIndex = nRowCountPerTask;

	std::vector<task<void>> aTask;
	std::vector<MGridRow*> aGridRow;
	aTask.reserve(nTaskCount);
	aGridRow.reserve(nTaskCount);

	for (int i = 0; i < nTaskCount; i++) 
	{
		if (i == nTaskCount - 1) nEndIndex = nRowCount;
		MGridRow* pGridRow = GetTable()->CreateDummyRow(FALSE);
		aGridRow.push_back(pGridRow);
		CString* pstrText = aText + i;
		auto rfExport = [this, &aKey, &aRow, pstrText, pGridRow, nStartIndex, nEndIndex] ()
		{
			for (int nIndex = nStartIndex; nIndex < nEndIndex; nIndex++)
			{
				ExportRowToText(*pstrText, m_hasKeyColumn ? aKey[nIndex] : 0, aRow[nIndex], pGridRow);
				pstrText->Append(m_strRowSeparator);
			}
		};
		// TODO: Move 로 되겠지?? 확인
		aTask.push_back(create_task(rfExport));
		nStartIndex = nEndIndex;
		nEndIndex += nRowCountPerTask;
	}
	when_all(aTask.begin(), aTask.end()).wait();
	for (MGridRow* pRow : aGridRow) delete pRow;

	// TODO: 적절한 배율로 조절
	// 버그는 아니고 String 재할당이 일어났다능...
	// 재할당 안일어나게 하려면 GetPreAllocateLength() 에서 배율을 좀 더 조절해보시라능...
	int nStrLength = 0;
	for (int i = 0; i < nTaskCount; i++) nStrLength += aText[i].GetLength();
	ASSERT(nPreAllocateLength >= nStrLength);
	CString strPreAlloc;
	strPreAlloc.Format(_T("PreAllocateLength: %d, StringLength: %d"), nPreAllocateLength, nStrLength);
	OutputDebugString(strPreAlloc);
}

int MTBPreClipboard2G::ImportAppend(const CString& strText)
{
	int nTextLength = strText.GetLength();
	int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount(m_bVisibleColumnOnly);
	int nRowCount = GetTableDB()->GetRowCount();

	int nCurIndex = 0;
	std::vector<MKey> aKey;
	while (nCurIndex < nTextLength)
	{
		CString strRow;
		TokenizeText(strRow, nCurIndex, strText, m_strRowSeparator);
		int nRowLength = strRow.GetLength();

		LPVOID pRow = GetSchema()->CreateDefaultData();
		int nCurItemIndex = 0;
		for (int i = m_idPasteTo.m_nColumn; i < nColumnCount && nCurItemIndex < nRowLength; i++)
		{
			ASSERT(i < (int)m_aColumnOrder.size());
			int nCol = m_aColumnOrder[i];

			CString strItem;
			TokenizeText(strItem, nCurItemIndex, strRow, m_strColumnSeparator);

			CBCGPGridItem* pItem = m_pGridRow->GetItem(nCol);
			if (!pItem->IsEnabled() || !pItem->IsAllowEdit() || pItem->IsReadOnly()) continue;

			if (!pItem->TextToVar(strItem))
			{
				// TODO: 무시하기 옵션
				// TODO : Array 일 경우
				int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
				if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("데이터 타입이 맞지 않습니다. (%d 번째 문자 \"%s\")"), nErrorIndex + 1, strItem);
				GetSchema()->DeleteData(pRow);
				return 0;
			}

			const MTBColumn& column = GetSchema()->GetColumn(nCol);
			if (column.IsKeyType())
			{
				aKey.push_back(pItem->GetValue());
			}
			else
			{
				column.SetItem(pRow, pItem->GetValue());
			}
		}

		if (nCurIndex < nRowLength)
		{
			// TODO: 무시하기 옵션
			CString strItem;
			TokenizeText(strItem, nCurItemIndex, strRow, m_strColumnSeparator);
			int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
			if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
			GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("테이블을 벗어나는 열이 존재합니다. (%d 번째 문자 \"%s\")"), nErrorIndex + 1, strItem);
			GetSchema()->DeleteData(pRow);
			return 0;
		}

		m_lstPasteRow.AddTail(pRow);
		if (aKey.size() == 1)
		{
			MKey nKey = aKey[0];
			aKey[0] = GetPreTableDB2G()->GetNewKey();
			while (aKey.size() < m_lstPasteRow.GetCount()) aKey.push_back(aKey[aKey.size() - 1] + 1);
			aKey[aKey.size() - 1] = nKey;
		}
		else if (aKey.size() > 1)
		{
			if (aKey.size() < m_lstPasteRow.GetCount()) aKey.push_back(aKey[aKey.size() - 1] + 1);
		}
	}

	std::vector<LPCVOID> aPasteRows;
	CopyPasteRowToVector(aPasteRows);
	if (!( aKey.size() > 0 ? GetPreTableDB2G()->AddData(aKey, aPasteRows) : GetPreTableDB2G()->AddData(aPasteRows) )) return 0;
	return (int)aPasteRows.size();
}

int MTBPreClipboard2G::ImportModify(const CString& strText)
{
	int nTextLength = strText.GetLength();
	int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount(m_bVisibleColumnOnly);
	int nRowCount = GetTableDB()->GetRowCount();

	POSITION pos = GetPreTableDB2G()->m_index.RowToPosition(m_idPasteTo.m_nRow, FALSE);

	int nCurIndex = 0;
	std::vector<MKey> aKey;
	std::vector<MKey> aNewKey;
	for (int nRow = m_idPasteTo.m_nRow; nRow < nRowCount && nCurIndex < nTextLength; nRow++)
	{
		CString strRow;
		TokenizeText(strRow, nCurIndex, strText, m_strRowSeparator);
		int nRowLength = strRow.GetLength();

		MPreTableDB2G::ITEM* pItem = GetPreTableDB2G()->GetNextItem(pos);
		aKey.push_back(pItem->key);
		LPVOID pRow = GetSchema()->CreateCopyData(pItem->data);
		int nCurItemIndex = 0;
		for (int i = m_idPasteTo.m_nColumn; i < nColumnCount && nCurItemIndex < nRowLength; i++)
		{
			ASSERT(i < (int)m_aColumnOrder.size());
			int nCol = m_aColumnOrder[i];

			CString strItem;
			TokenizeText(strItem, nCurItemIndex, strRow, m_strColumnSeparator);

			CBCGPGridItem* pItem = m_pGridRow->GetItem(nCol);
			if (!pItem->TextToVar(strItem))
			{
				// TODO: 무시하기 옵션
				// TODO : Array 일 경우
				int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
				if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("데이터 타입이 맞지 않습니다. (%d 번째 문자 \"%s\")"), nErrorIndex + 1, strItem);
				GetSchema()->DeleteData(pRow);
				return 0;
			}

			const MTBColumn& column = GetSchema()->GetColumn(nCol);
			if (column.IsKeyType())
			{
				aNewKey.push_back(pItem->GetValue());
			}
			else
			{
				column.SetItem(pRow, pItem->GetValue());
			}
		}

		if (nCurItemIndex < nRowLength)
		{
			// TODO: 무시하기 옵션
			CString strItem;
			TokenizeText(strItem, nCurItemIndex, strRow, m_strColumnSeparator);
			int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
			if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
			GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("테이블을 벗어나는 열이 존재합니다. (%d 번째 문자 \"%s\")"), nErrorIndex + 1, strItem);
			GetSchema()->DeleteData(pRow);
			return 0;
		}

		if (aNewKey.size() < aKey.size()) aNewKey.push_back(aKey[aKey.size() - 1]);
		m_lstPasteRow.AddTail(pRow);
	}

	if (nCurIndex < nTextLength)
	{
		// TODO: 무시하기 옵션
		CString strItem;
		TokenizeText(strItem, nCurIndex, strText, m_strColumnSeparator);
		int nErrorIndex = nCurIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
		if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
		GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("테이블을 벗어나는 행이 존재합니다. (%d 번째 문자 \"%s\", 수정과 추가를 동시에 할 수 없습니다.)"), nErrorIndex + 1, strItem);
		return 0;
	}

	// DB Update 받을 것이므로 따로 Update 처리는 안한다.
	std::vector<LPCVOID> aPasteRows;
	CopyPasteRowToVector(aPasteRows);
	if (!GetPreTableDB2G()->ModifyData(aKey, aNewKey, aPasteRows)) return 0;
	ASSERT(aPasteRows.size() < INT_MAX);
	return (int)aPasteRows.size();
}