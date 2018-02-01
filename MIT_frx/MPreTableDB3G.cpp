#include "stdafx.h"
#include "MPreTableDB3G.h"

using namespace mit;
using namespace mit::frx;

MPreTableDB3G::MPreTableDB3G(ITable* pTable, MTBSchemaBase* pSchema) :
	MTableDB(pTable, pSchema, &m_sort, &m_clipboard),
	m_sort(this),
	m_clipboard(this),
	m_index((CAtlList<LPCVOID>*)&m_rows)
{	
}

MPreTableDB3G::~MPreTableDB3G()
{
}

void MPreTableDB3G::InitRows()
{
	m_rows.RemoveAll();
	m_map.RemoveAll();

	std::vector<MIterator> iters;
	size_t size = GetIteratorList(iters);
	ASSERT(size <= INT_MAX);

	for (size_t i = 0; i < size; i++)
	{
		m_map.SetAt(iters[i], m_rows.AddTail(iters[i]));
	}

	m_index.Rebuild();
}

void MPreTableDB3G::FillRowAll()
{
	// �׻� FilledRowAll ��
}

void MPreTableDB3G::DestroyRows()
{
	m_rows.RemoveAll();
	m_map.RemoveAll();
	m_index.RemoveAll();
}

int MPreTableDB3G::GetRowCount() const
{
	ASSERT(m_rows.GetCount() <= INT_MAX);
	return (int)m_rows.GetCount();
}

LPCVOID MPreTableDB3G::GetRow(int nRow) const
{
	ASSERT(m_rows.GetCount() <= INT_MAX);
	ASSERT(nRow >= 0 && nRow < (int)m_rows.GetCount());

	POSITION pos = ((MPreTableDB3G*)this)->m_index.RowToPosition(nRow);
	ASSERT(pos);

	return (LPCVOID)m_rows.GetAt(pos);
}

BOOL MPreTableDB3G::DeleteRows(const std::vector<std::pair<int, int>>& aRowRanges)
{	
	ASSERT(m_rows.GetCount() <= INT_MAX);

	int nTotalCount = 0;
	for (std::vector<std::pair<int, int>>::const_iterator iter = aRowRanges.cbegin(); iter != aRowRanges.cend(); iter++)
	{
		ASSERT(iter->first <= iter->second);
		ASSERT(iter->first >= 0 && iter->first < (int)m_rows.GetCount());
		ASSERT(iter->second >= 0 && iter->second < (int)m_rows.GetCount());
		nTotalCount += iter->second - iter->first + 1;
	}

	std::vector<MIterator> iters;
	iters.reserve(nTotalCount);

	POSITION pos = NULL;
	int nCount = 0;
	for (std::vector<std::pair<int, int>>::const_iterator iter = aRowRanges.cbegin(); iter != aRowRanges.cend(); iter++)
	{
		ASSERT(iter->first <= iter->second);
		ASSERT(iter->first >= 0 && iter->first < (int)m_rows.GetCount());
		ASSERT(iter->second >= 0 && iter->second < (int)m_rows.GetCount());
		// Delete �Ǹ� ������ Cache ��������. Cache ���� �ʿ����.
		pos = m_index.RowToPosition(iter->first, FALSE);	

		nCount = iter->second - iter->first + 1;
		for (int i = 0; i < nCount; i++)
		{
			ASSERT(pos);
			iters.push_back(m_rows.GetNext(pos));
		}
	}
	ASSERT(iters.size() == nTotalCount);

	return DeleteData(iters);
}

BOOL MPreTableDB3G::ModifyItem(int nRow, int nCol, _variant_t& item)
{
	MTBChangedFromTable<TModifiedItem> cft(m_modifiedItem, TModifiedItem(nRow, nCol, &item));

	MTBSchemaBase* pSchema = GetSchema();
	const MTBColumn& column = pSchema->GetColumn(nCol);

	// GetRow() �� ������ �ߺ��ε�...

	// Modify �Ǹ� ������ Cache ��������. Cache ���� �ʿ����.
	POSITION pos = m_index.RowToPosition(nRow, FALSE);
	ASSERT(pos);

	MIterator iter = m_rows.GetAt(pos);
	LPVOID pModifiedData = pSchema->GetCopyData((LPCVOID)iter);
	column.SetItem(pModifiedData, item);

	// ModifyData() ȣ��Ǹ� DB Notify ���� item ���� ���� DB �� �� ������ �ٲ��ش�.
	// (�幰���� DB �� ������ �Ѱ��� ���� �����ؼ� �ٲٴ� ��� ����)		
	return ModifyData(iter, (MIterator)pModifiedData);
}

BOOL MPreTableDB3G::ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems)
{
	MTBChangedFromTable<TModifiedRow> cft(m_modifiedRow, TModifiedRow(nRow, aModifiedRowItems));

	MTBSchemaBase* pSchema = GetSchema();
	ASSERT(pSchema->GetColumnCount() == (int)aModifiedRowItems.size());
	int nItemCount = (int)aModifiedRowItems.size();

	POSITION pos = m_index.RowToPosition(nRow, FALSE);
	ASSERT(pos);

	MIterator iter = m_rows.GetAt(pos);
	MKey newkey = 0;

	LPVOID pModifiedData = pSchema->GetDefaultData();
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		column.SetItem(pModifiedData, *aModifiedRowItems[i]);
	}

	// ModifyData() ȣ��Ǹ� DB Notify ���� item ���� ���� DB �� �� ������ �ٲ��ش�.
	// (�幰���� DB �� ������ �Ѱ��� ���� �����ؼ� �ٲٴ� ��� ����)		
	return ModifyData(iter, (MIterator)pModifiedData);
}

BOOL MPreTableDB3G::GetNewRowItems(std::vector<_variant_t*>& aNewRowItems)
{
	MTBSchemaBase* pSchema = GetSchema();
	ASSERT(pSchema->GetColumnCount() == (int)aNewRowItems.size());
	int nItemCount = (int)aNewRowItems.size();

	LPCVOID pDefaultData = pSchema->GetDefaultData();
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		column.GetItem(*aNewRowItems[i], pDefaultData);
	}

	return TRUE;
}

BOOL MPreTableDB3G::AppendRow(std::vector<_variant_t*>& aNewRowItems)
{
	MTBChangedFromTable<TAppendedRow> cft(m_appendedRow, TAppendedRow(aNewRowItems));

	MTBSchemaBase* pSchema = GetSchema();
	ASSERT(pSchema->GetColumnCount() == (int)aNewRowItems.size());
	int nItemCount = (int)aNewRowItems.size();

	LPVOID pNewData = pSchema->GetDefaultData();
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		column.SetItem(pNewData, *aNewRowItems[i]);
	}

	return AddData((MIterator)pNewData);
}

//void MPreTableDB3G::OnAddedFromDB(MKey key)
//{
//	// Data �ϳ� ������ ������ �̳� ������ ������ 
//	// ���� �� ���� �����ϴ� ���� �ǹ̾���.
//	// ���� ó���ؼ� ������ ���� ����� �ϱ� ���ٴ� �ڵ带 ����ϰ� �����ϴ� �ɷ�...
//	std::vector<MKey> keys;
//	keys.resize(1);
//	keys[0] = key;
//	OnAddedFromDB(keys);
//}

//void MPreTableDB2G::OnAddedFromDB(const std::vector<MKey>& keys)
//{
//	CWaitCursor wait;
//
//	if (keys.empty()) return;
//
//	if (IsRealtimeSortFromDB())
//	{
//		// Realtime Sort (ó�� �� ���ĵǾ� �־�� ��)
//		// �̱���
//		ASSERT(0);		
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (���� ������ �����ؾ���)
//		// ������ ���� �ؿ� �߰��ϸ� �ȴ�
//
//		for (std::vector<MKey>::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
//		{
//			ASSERT(!m_map.Lookup(*iter));
//			m_map.SetAt(*iter, m_rows.AddTail(new ITEM(*iter)));
//		}
//
//		// TODO: �߰��� Ű���� �� ũ�� Sorting �� ���¶��??
//		m_isSorted = FALSE;
//	}
//
//	if (IsAppendedFromTable())
//	{
//		ASSERT(keys.size() == 1);
//		CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(keys[0]);
//		ASSERT(pair);
//		ITEM* pItem = m_rows.GetAt(pair->m_value);
//
//		LPCVOID& pRow = pItem->data;
//		ASSERT(!pRow); // ������ ó�� �߰������Ƿ� NULL.
//		if (!GetData(pItem->key, pRow)) { ASSERT(0); return; }
//		ASSERT(pRow);
//
//		MTBSchemaBase* pSchema = GetSchema();
//		ASSERT(m_appendedRow.aItems.size() <= INT_MAX && pSchema->GetColumnCount() == m_appendedRow.aItems.size());
//		int nItemCount = (int)m_appendedRow.aItems.size();
//		for (int i = 0; i < nItemCount; i++)
//		{
//			const MTBColumn& column = pSchema->GetColumn(i);
//			if (column.GetType() == MTBColumn::TB_KEY)
//			{
//				*m_appendedRow.aItems[i] = pItem->key;
//			}
//			else
//			{
//				column.GetItem(*m_appendedRow.aItems[i], pRow);	
//			}
//		}	
//		RebuildIndex();
//		GetTable()->UpdateAppendRowFromTable();
//	}
//	else
//	{
//		RebuildIndex();
//		GetTable()->UpdateAppendRow();
//	}
//}
//
//void MPreTableDB2G::OnDeletedFromDB(MKey key)
//{
//	// Data �ϳ� ������ ������ �̳� ������ ������ 
//	// ���� �� ���� �����ϴ� ���� �ǹ̾���.
//	// ���� ó���ؼ� ������ ���� ����� �ϱ� ���ٴ� �ڵ带 ����ϰ� �����ϴ� �ɷ�...
//	std::vector<MKey> keys;
//	keys.resize(1);
//	keys[0] = key;
//	OnDeletedFromDB(keys);
//}
//
//void MPreTableDB2G::OnDeletedFromDB(const std::vector<MKey>& keys)
//{
//	CWaitCursor wait;
//
//	if (keys.empty()) return;
//	if (m_rows.IsEmpty()) return; 
//
//	if (IsRealtimeSortFromDB())
//	{
//		// Realtime Sort (ó�� �� ���ĵǾ� �־�� ��)
//		// �̱���
//		ASSERT(0);		
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (���� ������ �����ؾ���)	
//
//		CAtlMap<MKey, POSITION>::CPair* pair;
//		for (std::vector<MKey>::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
//		{
//			pair = m_map.Lookup(*iter);
//			if (!pair) continue;
//			delete m_rows.GetAt(pair->m_value);
//			m_rows.RemoveAt(pair->m_value);
//			m_map.RemoveAtPos(pair);
//		}
//	}		
//
//	RebuildIndex();
//	GetTable()->UpdateRowCount();
//}
//
//void MPreTableDB2G::OnModifiedFromDB(MKey key, MKey newkey)
//{
//	// Data �ϳ� ������ ������ �̳� ������ ������ 
//	// ���� �� ���� �����ϴ� ���� �ǹ̾���.
//	// ���� ó���ؼ� ������ ���� ����� �ϱ� ���ٴ� �ڵ带 ����ϰ� �����ϴ� �ɷ�...
//	std::vector<MKey> keys;
//	keys.resize(1);
//	keys[0] = key;
//	std::vector<MKey> newkeys;
//	newkeys.resize(1);
//	newkeys[0] = newkey;
//	OnModifiedFromDB(keys, newkeys);
//}
//
//void MPreTableDB2G::OnModifiedFromDB(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys)
//{
//	CWaitCursor wait;
//
//	ASSERT(keys.size() == newkeys.size());
//	if (keys.empty()) return;
//	if (m_rows.IsEmpty()) return; 
//
//	if (IsRealtimeSortFromDB())
//	{
//		// Realtime Sort (Sorting ���¸� �����ؾ���)
//		// �̱���
//		ASSERT(0);
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (���� ������ �����ؾ���)		
//
//		CAtlMap<MKey, POSITION>::CPair* pair;
//		ASSERT(keys.size() <= INT_MAX);
//		int size = (int)keys.size();
//		for (int i = 0; i < size; i++)
//		{
//			pair = m_map.Lookup(keys[i]);
//			if (!pair) continue;
//			ITEM* pItem = m_rows.GetAt(pair->m_value);
//			if (keys[i] != newkeys[i])
//			{
//				if (m_map.Lookup(newkeys[i])) { ASSERT(0); continue; }
//				m_map.SetAt(newkeys[i], pair->m_value);
//				m_map.RemoveAtPos(pair);
//				pItem->key = newkeys[i];
//			}
//			pItem->data = NULL;
//		}
//
//		// TODO: Ű ������ ���ٸ�? �־ ������ �� �ٲ�ٸ�?
//		m_isSorted = FALSE;
//	}
//
//	if (IsModifiedFromTable())
//	{
//		MTBSchemaBase* pSchema = GetSchema();
//
//		ASSERT(newkeys.size() == 1);
//		CAtlMap<MKey, POSITION>::CPair* pair = m_map.Lookup(newkeys[0]);
//		ASSERT(pair);
//		ITEM* pItem = m_rows.GetAt(pair->m_value);
//
//		LPCVOID& pRow = pItem->data;
//		ASSERT(!pRow); // ������ NULL �� �������.
//		if (!GetData(pItem->key, pRow)) { ASSERT(0); return; }
//		ASSERT(pRow);
//
//		if (m_modifiedItem.HasModifiedItem())
//		{
//			const MTBColumn& column = pSchema->GetColumn(m_modifiedItem.nCol);
//			if (column.GetType() == MTBColumn::TB_KEY)
//			{
//				*m_modifiedItem.pItem = pItem->key;
//			}
//			else
//			{
//				column.GetItem(*m_modifiedItem.pItem, pRow);	
//			}	
//		}
//		else if (m_modifiedRow.HasModifiedRow())
//		{
//			ASSERT(m_modifiedRow.aItems.size() <= INT_MAX && pSchema->GetColumnCount() == m_modifiedRow.aItems.size());
//			int nItemCount = (int)m_modifiedRow.aItems.size();
//			for (int i = 0; i < nItemCount; i++)
//			{
//				const MTBColumn& column = pSchema->GetColumn(i);
//				if (column.GetType() == MTBColumn::TB_KEY)
//				{
//					*m_modifiedRow.aItems[i] = pItem->key;
//				}
//				else
//				{
//					column.GetItem(*m_modifiedRow.aItems[i], pRow);	
//				}
//			}	
//		}
//		else 
//		{
//			ASSERT(0);
//		}
//		// Table���� Modify �� Update �� �� ����
//	}
//	else
//	{
//		// Modifty�� ���� �� �ٲ�Ƿ�
//		// RebuildIndex();
//		GetTable()->UpdateData();
//	}
//}
