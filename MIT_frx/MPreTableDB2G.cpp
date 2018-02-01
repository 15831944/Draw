#include "stdafx.h"
#include "MPreTableDB2G.h"

using namespace mit;
using namespace mit::frx;

MPreTableDB2G::MPreTableDB2G(ITable* pTable, MTBSchemaBase* pSchema) :
	MTableDB(pTable, pSchema, &m_sort, &m_clipboard),
	m_sort(this),
	m_clipboard(this),
	m_index((CAtlList<LPCVOID>*)&m_rows)
{	
}

MPreTableDB2G::~MPreTableDB2G()
{
}

BOOL MPreTableDB2G::GetForeignItem(_variant_t& varValue, int nRow, int nCol) const
{
	return GetForeignData(varValue, GetItem(nRow)->key, nCol);
}

MKey MPreTableDB2G::GetKey(int nRow) const
{
	return GetItem(nRow)->key;
}

LPCVOID MPreTableDB2G::GetRow(int nRow) const
{
	return GetItem(nRow)->data;
}

int MPreTableDB2G::GetKeyLange(std::vector<MKey>& aKeys, int nStartRow, int nEndRow) const
{
	ASSERT(m_rows.GetCount() <= INT_MAX);
	ASSERT(nStartRow >= 0 && nStartRow < (int)m_rows.GetCount());
	ASSERT(nEndRow >= 0 && nEndRow < (int)m_rows.GetCount());

	aKeys.clear();
	int nRowCount = nEndRow - nStartRow + 1;
	if (nRowCount < 0) return 0;
	aKeys.reserve(nRowCount);

	POSITION pos = m_index.RowToPosition(nStartRow);
	ASSERT(pos);

	for (int i = 0; i < nRowCount; i++)
	{
		ITEM* pItem = m_rows.GetNext(pos);
		aKeys.push_back(pItem->key);
	}

	return nRowCount;
}

int MPreTableDB2G::GetRowLange(std::vector<LPCVOID>& aRows, int nStartRow, int nEndRow) const
{
	ASSERT(m_rows.GetCount() <= INT_MAX);
	ASSERT(nStartRow >= 0 && nStartRow < (int)m_rows.GetCount());
	ASSERT(nEndRow >= 0 && nEndRow < (int)m_rows.GetCount());

	aRows.clear();
	int nRowCount = nEndRow - nStartRow + 1;
	if (nRowCount < 0) return 0;
	aRows.reserve(nRowCount);

	POSITION pos = m_index.RowToPosition(nStartRow);
	ASSERT(pos);

	for (int i = 0; i < nRowCount; i++)
	{
		ITEM* pItem = m_rows.GetNext(pos);
		LPCVOID& pRow = pItem->data;
		if (!pRow)
		{
			if (!GetData(pItem->key, pRow)) { ASSERT(0); return NULL; }
			ASSERT(pRow);
		}
		aRows.push_back(pRow);
	}

	return nRowCount;
}

void MPreTableDB2G::InitRows()
{
	m_rows.RemoveAll();
	m_map.RemoveAll();

	std::vector<MKey> keys;
	size_t size = GetKeyList(keys, GetKeySortOption());
	ASSERT(size <= INT_MAX);

	for (size_t i = 0; i < size; i++)
	{
		m_map.SetAt(keys[i], m_rows.AddTail(new ITEM(keys[i])));
	}

	m_index.Rebuild();
}

void MPreTableDB2G::DestroyRows()
{
	POSITION pos = m_rows.GetHeadPosition();
	while (pos)
	{
		delete m_rows.GetNext(pos);
	}
	m_rows.RemoveAll();
	m_map.RemoveAll();
	m_index.RemoveAll();
}

void MPreTableDB2G::FillRowAll()
{
	// TODO: Data �� ä�������� Ȯ�� �ϴ� Flag �α�
	POSITION pos = m_rows.GetHeadPosition();
	while (pos) 
	{
		GetNextItem(pos);
	}
}

int MPreTableDB2G::GetRowCount() const
{
	ASSERT(m_rows.GetCount() <= INT_MAX);
	return (int)m_rows.GetCount();
}

BOOL MPreTableDB2G::DeleteRows(const std::vector<std::pair<int, int>>& aRowRanges)
{	
	ASSERT(m_rows.GetCount() <= INT_MAX);

	int nTotalCount = 0;
	for (const std::pair<int, int>& rowRange : aRowRanges)
	{
		ASSERT(rowRange.first <= rowRange.second);
		ASSERT(rowRange.first >= 0 && rowRange.first < (int)m_rows.GetCount());
		ASSERT(rowRange.second >= 0 && rowRange.second < (int)m_rows.GetCount());
		nTotalCount += rowRange.second - rowRange.first + 1;
	}

	std::vector<MKey> keys;
	keys.reserve(nTotalCount);

	for (const std::pair<int, int>& rowRange : aRowRanges)
	{
		// Delete �Ǹ� ������ Cache ��������. Cache ���� �ʿ����.
		POSITION pos = m_index.RowToPosition(rowRange.first, FALSE);		
		int nCount = rowRange.second - rowRange.first + 1;
		for (int i = 0; i < nCount; i++)
		{
			ASSERT(pos);
			keys.push_back(m_rows.GetNext(pos)->key);
		}
	}
	ASSERT(keys.size() == nTotalCount);

	return DeleteData(keys);
}

BOOL MPreTableDB2G::ModifyItem(int nRow, int nCol, _variant_t& item)
{
	MTBChangedFromTable<TModifiedItem> cft(m_modifiedItem, TModifiedItem(nRow, nCol, &item));

	const MTBColumn& column = m_pSchema->GetColumn(nCol);

	// Modify �Ǹ� ������ Cache ��������. Cache ���� �ʿ����.
	ITEM* pItem = GetItem(nRow, FALSE);
	MKey newkey = pItem->key;
	LPVOID pModifiedData = m_pSchema->GetCopyData(pItem->data);

	if (column.IsKeyType())
	{
		newkey = item;
	}
	else
	{
		column.SetItem(pModifiedData, item);
	}
	
	// ModifyData() ȣ��Ǹ� DB Notify ���� item ���� ���� DB �� �� ������ �ٲ��ش�.
	// (�幰���� DB �� ������ �Ѱ��� ���� �����ؼ� �ٲٴ� ��� ����)	
	return ModifyData(std::vector<MKey>(1, pItem->key), std::vector<MKey>(1, newkey), std::vector<LPCVOID>(1, pModifiedData));
}

BOOL MPreTableDB2G::ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems)
{
	MTBChangedFromTable<TModifiedRow> cft(m_modifiedRow, TModifiedRow(nRow, aModifiedRowItems));

	ASSERT(m_pSchema->GetColumnCount() == (int)aModifiedRowItems.size());
	int nItemCount = (int)aModifiedRowItems.size();

	// Modify �Ǹ� ������ Cache ��������. Cache ���� �ʿ����.
	ITEM* pItem = GetItem(nRow, FALSE);
	MKey newkey = pItem->key;
	LPVOID pModifiedData = m_pSchema->GetDefaultData();

	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = m_pSchema->GetColumn(i);
		if (column.IsKeyType())
		{
			newkey = *aModifiedRowItems[i];
		}
		else
		{
			column.SetItem(pModifiedData, *aModifiedRowItems[i]);
		}
	}

	// ModifyData() ȣ��Ǹ� DB Notify ���� item ���� ���� DB �� �� ������ �ٲ��ش�.
	// (�幰���� DB �� ������ �Ѱ��� ���� �����ؼ� �ٲٴ� ��� ����)		
	return ModifyData(std::vector<MKey>(1, pItem->key), std::vector<MKey>(1, newkey), std::vector<LPCVOID>(1, pModifiedData));
}

BOOL MPreTableDB2G::GetNewRowItems(std::vector<_variant_t*>& aNewRowItems)
{
	ASSERT(m_pSchema->GetColumnCount() == (int)aNewRowItems.size());
	int nItemCount = (int)aNewRowItems.size();

	LPCVOID pDefaultData = m_pSchema->GetDefaultData();
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = m_pSchema->GetColumn(i);
		switch (column.GetType())
		{
		case MTBColumn::TB_KEY: *aNewRowItems[i] = GetNewKey(); break;
		case MTBColumn::TB_FOREIGN: ASSERT(0); return GetForeignData(*aNewRowItems[i], GetRowCount(), i);
		default: column.GetItem(*aNewRowItems[i], pDefaultData); break;
		}
	}

	return TRUE;
}

BOOL MPreTableDB2G::AppendRow(std::vector<_variant_t*>& aNewRowItems)
{
	MTBChangedFromTable<TAppendedRow> cft(m_appendedRow, TAppendedRow(aNewRowItems));

	ASSERT(m_pSchema->GetColumnCount() == (int)aNewRowItems.size());
	int nItemCount = (int)aNewRowItems.size();

	MKey key = 0;
	LPVOID pNewData = m_pSchema->GetDefaultData();
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = m_pSchema->GetColumn(i);
		if (column.IsKeyType())
		{
			key = *aNewRowItems[i];
		}
		else
		{
			column.SetItem(pNewData, *aNewRowItems[i]);
		}
	}
	
	return (key > 0) ?
		AddData(std::vector<MKey>(1, key), std::vector<LPCVOID>(1, pNewData)) : 
		AddData(std::vector<LPCVOID>(1, pNewData));
}

void MPreTableDB2G::OnAddedFromDB(const std::vector<MKey>& keys)
{
	CWaitCursor wait;

	if (keys.empty()) return;

	if (IsRealtimeSortFromDB())
	{
		// Realtime Sort (ó�� �� ���ĵǾ� �־�� ��)
		// �̱���
		ASSERT(0);		
		m_isSorted = TRUE;
	}
	else
	{
		// ���� ������ ���� (������ �������� �߰��ϸ� �ȴ�.)
		for (MKey key : keys)
		{
			ASSERT(!m_map.Lookup(key));
			m_map.SetAt(key, m_rows.AddTail(new ITEM(key)));
		}

		// TODO: �߰��� Ű���� �� ũ�� Sorting �� ���¶��??
		m_isSorted = FALSE;
	}

	if (IsAppendedFromTable())
	{
		// ���� DB �� Commit �� ���� Table �� �ݿ�
		ASSERT(keys.size() == 1);
		CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(keys[0]);
		ASSERT(pair);
		ASSERT(!m_rows.GetAt(pair->m_value)->data); // ������ ó�� �߰������Ƿ� NULL.
		ITEM* pItem = GetAtItem(pair->m_value);

		ASSERT(m_appendedRow.aItems.size() <= INT_MAX && m_pSchema->GetColumnCount() == m_appendedRow.aItems.size());
		int nItemCount = (int)m_appendedRow.aItems.size();
		for (int i = 0; i < nItemCount; i++)
		{
			const MTBColumn& column = m_pSchema->GetColumn(i);
			switch (column.GetType())
			{
			case MTBColumn::TB_KEY: *m_appendedRow.aItems[i] = pItem->key; break;
			case MTBColumn::TB_FOREIGN: VERIFY(GetForeignData(*m_appendedRow.aItems[i], pItem->key, i)); break;
			default: column.GetItem(*m_appendedRow.aItems[i], pItem->data); break;
			}
		}	
		m_index.Rebuild();
	}
	else
	{
		m_index.Rebuild();
		GetTable()->UpdateAppendRow();
	}
}

void MPreTableDB2G::OnDeletedFromDB(const std::vector<MKey>& keys)
{
	CWaitCursor wait;

	if (keys.empty()) return;
	if (m_rows.IsEmpty()) return; 

	if (IsRealtimeSortFromDB())
	{
		// Realtime Sort (ó�� �� ���ĵǾ� �־�� ��)
		// �̱���
		ASSERT(0);		
		m_isSorted = TRUE;
	}
	else
	{
		// ���� ������ ����
		for (MKey key : keys)
		{
			CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(key);
			if (!pair) continue;
			delete m_rows.GetAt(pair->m_value);
			m_rows.RemoveAt(pair->m_value);
			m_map.RemoveAtPos(pair);
		}
	}		

	m_index.Rebuild();
	GetTable()->UpdateRowCount();
}

void MPreTableDB2G::OnModifiedFromDB(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys)
{
	CWaitCursor wait;

	ASSERT(keys.size() == newkeys.size());
	if (keys.empty()) return;
	if (m_rows.IsEmpty()) return; 

	if (IsRealtimeSortFromDB())
	{
		// Realtime Sort (Sorting ���¸� �����ؾ���)
		// �̱���
		ASSERT(0);
		m_isSorted = TRUE;
	}
	else
	{
		// ���� ������ ����
		ASSERT(keys.size() <= INT_MAX);
		int size = (int)keys.size();
		for (int i = 0; i < size; i++)
		{
			CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(keys[i]);
			if (!pair) continue;
			ITEM* pItem = m_rows.GetAt(pair->m_value);
			if (keys[i] != newkeys[i])
			{
				ASSERT(!m_map.Lookup(newkeys[i]));
				m_map.SetAt(newkeys[i], pair->m_value);
				m_map.RemoveAtPos(pair);
				pItem->key = newkeys[i];
			}
			pItem->data = NULL;
		}

		// TODO: Ű ������ ���ٸ�? �־ ������ �� �ٲ�ٸ�?
		m_isSorted = FALSE;
	}

	if (IsModifiedFromTable())
	{
		// ���� DB �� Commit �� ���� Table �� �ݿ�
		ASSERT(newkeys.size() == 1);
		CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(newkeys[0]);
		ASSERT(pair);
		ASSERT(!m_rows.GetAt(pair->m_value)->data); // ������ NULL �� �������.
		ITEM* pItem = GetAtItem(pair->m_value);

		if (m_modifiedItem.HasModifiedItem())
		{
			// Item ���� ����
			const MTBColumn& column = m_pSchema->GetColumn(m_modifiedItem.nCol);
			switch (column.GetType())
			{
			case MTBColumn::TB_KEY: *m_modifiedItem.pItem = pItem->key; break;
			case MTBColumn::TB_FOREIGN: VERIFY(GetForeignData(*m_modifiedItem.pItem, pItem->key, m_modifiedItem.nCol)); break;
			default: column.GetItem(*m_modifiedItem.pItem, pItem->data); break;
			}
		}
		else if (m_modifiedRow.HasModifiedRow())
		{
			// Row ���� ����
			ASSERT(m_modifiedRow.aItems.size() <= INT_MAX && m_pSchema->GetColumnCount() == m_modifiedRow.aItems.size());
			int nItemCount = (int)m_modifiedRow.aItems.size();
			for (int i = 0; i < nItemCount; i++)
			{
				const MTBColumn& column = m_pSchema->GetColumn(i);
				switch (column.GetType())
				{
				case MTBColumn::TB_KEY: *m_modifiedRow.aItems[i] = pItem->key; break;
				case MTBColumn::TB_FOREIGN: VERIFY(GetForeignData(*m_modifiedRow.aItems[i], pItem->key, i)); break;
				default: column.GetItem(*m_modifiedRow.aItems[i], pItem->data);	break;
				}
			}	
		}
		else 
		{
			ASSERT(0);
		}
		// RebuildIndex();
	}
	else
	{
		// Modifty�� ���� �� �ٲ�Ƿ�
		// RebuildIndex();
		GetTable()->UpdateData();
	}
}

MPreTableDB2G::SORT_OPTION MPreTableDB2G::GetKeySortOption() const
{
	CAtlList<TBSortColumn> lstSortCol;
	int nSortColCount = GetSort()->GetSortColumns(lstSortCol);
	if (nSortColCount != 1) return NOT_SORT;
	int nSortColumn = lstSortCol.GetHead().nColumn;
	ASSERT(nSortColumn >= 0 && nSortColumn < m_pSchema->GetColumnCount());
	const MTBColumn& column = m_pSchema->GetColumn(nSortColumn);
	if (!column.IsKeyType()) return NOT_SORT;
	return lstSortCol.GetHead().bAscending ? SORT_ASCENDING : SORT_DESCENDING;
}

size_t MPreTableDB2G::GetKeyList(std::vector<MKey>& keys, SORT_OPTION so) const
{
	BOOL bSorted = FALSE;
	size_t size = GetKeyList(keys, so, bSorted);
	if (so == NOT_SORT || bSorted) return size;	
	if (so == SORT_ASCENDING) std::sort(keys.begin(), keys.end());
	else std::sort(keys.rbegin(), keys.rend());
	return size;
}
