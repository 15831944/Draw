#include "stdafx.h"
#include "MTBPostClipboard.h"

#include "MTable.h"
#include "MPostTableDB.h"
#include "MTBProgressCtrlHelper.h"

#include <ppl.h>
#include <ppltasks.h>

using namespace mit::frx;
using namespace mit::lib;
using namespace std;
using namespace concurrency;

MTBPostClipboard::MTBPostClipboard(ITableDB* pTableDB) : 
	MTBClipboard(pTableDB)
{
}

MTBPostClipboard::~MTBPostClipboard()
{
}

int MTBPostClipboard::GetApproximateRowLength(const std::vector<MKey>&, const std::vector<LPCVOID>&)
{
	int nRowCount = GetRowCount();
	int nSampleRowCount = min(nRowCount, SAMPLE_ROW_COUNT);
	MSimpleProfiler sp(_T("GetApproximateRowLength(%d)"), nSampleRowCount); // �躸�� ����� ũ�� �ȵǰ���
	
	int nTotalSampleLength = 0;
	double dFactor = (double)nRowCount / (double)nSampleRowCount;
	for (int i = 0; i < nSampleRowCount; i++)
	{
		CString strSample;
		int nRow = (int)(i * dFactor) + m_range.m_nTop;
		ASSERT(nRow >= m_range.m_nTop && nRow <= m_range.m_nBottom);
		ExportRowToText(strSample, 0, GetPostTableDB()->GetRow(nRow), m_pGridRow);
		strSample.Append(m_strRowSeparator);
		nTotalSampleLength += strSample.GetLength();
	}
	return nTotalSampleLength / nSampleRowCount;
}

void MTBPostClipboard::Export(CString& strText)
{
	ASSERT(!m_hasKeyColumn);
	int nRowCount = GetRowCount();
	int nColCount = GetColCount();
	MSimpleProfiler sp(_T("Export(%d, %d)"), nRowCount, nColCount);

	int nApproximateRowLength = GetApproximateRowLength(std::vector<MKey>(), std::vector<LPCVOID>());
	int nPreAllocateLength = GetPreAllocateLength(nApproximateRowLength);

	strText.Preallocate(nPreAllocateLength);
	for (int nRow = m_range.m_nTop; nRow <= m_range.m_nBottom; nRow++)
	{
		ExportRowToText(strText, 0, GetPostTableDB()->GetRow(nRow), m_pGridRow);
		strText.Append(m_strRowSeparator);
	}

	// TODO: ������ ������ ����
	// ���״� �ƴϰ� String ���Ҵ��� �Ͼ�ٴ�...
	// ���Ҵ� ���Ͼ�� �Ϸ��� GetPreAllocateLength() ���� ������ �� �� �����غ��ö��...
	ASSERT(nPreAllocateLength >= strText.GetLength());
	CString strPreAlloc;
	strPreAlloc.Format(_T("PreAllocateLength: %d, StringLength: %d"), nPreAllocateLength, strText.GetLength());
	OutputDebugString(strPreAlloc);
}

void MTBPostClipboard::ParallelExport(int nTaskCount, CString* aText)
{
	ASSERT(!m_hasKeyColumn);
	int nRowCount = GetRowCount();
	int nColCount = GetColCount();
	MSimpleProfiler sp(_T("ParallelExport(%d, %d)"), nRowCount, nColCount);
	
	int nApproximateRowLength = GetApproximateRowLength(std::vector<MKey>(), std::vector<LPCVOID>());
	int nPreAllocateLength = GetPreAllocateLength(nApproximateRowLength);
	int nPreTaskAllocateLength = (int)(nPreAllocateLength / (double)nTaskCount);

	for (int i = 0; i < nTaskCount; i++) aText[i].Preallocate(nPreTaskAllocateLength);

	int nRowCountPerTask = nRowCount / nTaskCount;
	int nStartRow = m_range.m_nTop;
	int nEndRow = nStartRow + nRowCountPerTask;

	std::vector<task<void>> aTask;
	std::vector<MGridRow*> aGridRow;
	aTask.reserve(nTaskCount);
	aGridRow.reserve(nTaskCount);

	MKey key = 0;
	MPostTableDB* pTableDB = GetPostTableDB();
	for (int i = 0; i < nTaskCount; i++) 
	{
		if (i == nTaskCount - 1) nEndRow = m_range.m_nBottom + 1;
		MGridRow* pGridRow = GetTable()->CreateDummyRow(FALSE);
		aGridRow.push_back(pGridRow);
		CString* pstrText = aText + i;
		auto rfExport = [this, pTableDB, pstrText, pGridRow, nStartRow, nEndRow] ()
		{
			for (int nRow = nStartRow; nRow < nEndRow; nRow++)
			{
				ExportRowToText(*pstrText, 0, pTableDB->GetRow(nRow), pGridRow);
				pstrText->Append(m_strRowSeparator);
			}
		};
		// TODO: Move �� �ǰ���?? Ȯ��
		aTask.push_back(create_task(rfExport));
		nStartRow = nEndRow;
		nEndRow += nRowCountPerTask;
	}
	when_all(aTask.begin(), aTask.end()).wait();
	for (MGridRow* pRow : aGridRow) delete pRow;

	// TODO: ������ ������ ����
	// ���״� �ƴϰ� String ���Ҵ��� �Ͼ�ٴ�...
	// ���Ҵ� ���Ͼ�� �Ϸ��� GetPreAllocateLength() ���� ������ �� �� �����غ��ö��...
	int nStrLength = 0;
	for (int i = 0; i < nTaskCount; i++) nStrLength += aText[i].GetLength();
	ASSERT(nPreAllocateLength >= nStrLength);
	CString strPreAlloc;
	strPreAlloc.Format(_T("PreAllocateLength: %d, StringLength: %d"), nPreAllocateLength, nStrLength);
	OutputDebugString(strPreAlloc);
}

int MTBPostClipboard::ImportModify(const CString& strText)
{
	int nTextLength = strText.GetLength();
	int nColumnCount = GetTable()->GetColumnsInfo().GetColumnCount(m_bVisibleColumnOnly);
	int nRowCount = GetTableDB()->GetRowCount();
	
	int nCurIndex = 0;
	std::vector<int> aRow;
	for (int nRow = m_idPasteTo.m_nRow; nRow < nRowCount && nCurIndex < nTextLength; nRow++)
	{
		CString strRow;
		TokenizeText(strRow, nCurIndex, strText, m_strRowSeparator);
		int nRowLength = strRow.GetLength();

		LPVOID pRow = GetSchema()->CreateCopyData(GetPostTableDB()->GetRow(nRow));
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
				// TODO: �����ϱ� �ɼ�
				// TODO : Array �� ���
				int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
				if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("������ Ÿ���� ���� �ʽ��ϴ�. (%d ��° ���� \"%s\")"), nErrorIndex + 1, strItem);
				GetSchema()->DeleteData(pRow);
				return 0;
			}

			const MTBColumn& column = GetSchema()->GetColumn(nCol);
			ASSERT (!column.IsKeyType());
			column.SetItem(pRow, pItem->GetValue());
		}

		if (nCurItemIndex < nRowLength)
		{
			// TODO: �����ϱ� �ɼ�
			CString strItem;
			TokenizeText(strItem, nCurItemIndex, strRow, m_strColumnSeparator);
			int nErrorIndex = nCurIndex - nRowLength - m_strRowSeparator.GetLength() + nCurItemIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
			if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
			GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("���̺��� ����� ���� �����մϴ�. (%d ��° ���� \"%s\")"), nErrorIndex + 1, strItem);
			GetSchema()->DeleteData(pRow);
			return 0;
		}

		aRow.push_back(nRow);
		m_lstPasteRow.AddTail(pRow);
	}

	if (nCurIndex < nTextLength)
	{
		// TODO: �����ϱ� �ɼ�
		CString strItem;
		TokenizeText(strItem, nCurIndex, strText, m_strColumnSeparator);
		int nErrorIndex = nCurIndex - strItem.GetLength() - m_strColumnSeparator.GetLength();
		if (strItem.GetLength() > 16) strItem = strItem.Left(16) + _LSX(...);
		GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_ERROR, _STR("���̺��� ����� ���� �����մϴ�. (%d ��° ���� \"%s\", ������ �߰��� ���ÿ� �� �� �����ϴ�.)"), nErrorIndex + 1, strItem);
		return 0;
	}

	// DB Update �����Ƿ� ���� Update
	std::vector<LPCVOID> aPasteRows;
	CopyPasteRowToVector(aPasteRows);
	if (!GetPostTableDB()->ModifyData(aRow, aPasteRows)) return 0;
	GetTable()->UpdateData();
	return (int)aPasteRows.size();
}