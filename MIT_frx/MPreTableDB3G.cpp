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
	// 항상 FilledRowAll 임
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
		// Delete 되면 어차피 Cache 날려야함. Cache 만들 필요없다.
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

	// GetRow() 랑 굉장히 중복인데...

	// Modify 되면 어차피 Cache 날려야함. Cache 만들 필요없다.
	POSITION pos = m_index.RowToPosition(nRow, FALSE);
	ASSERT(pos);

	MIterator iter = m_rows.GetAt(pos);
	LPVOID pModifiedData = pSchema->GetCopyData((LPCVOID)iter);
	column.SetItem(pModifiedData, item);

	// ModifyData() 호출되면 DB Notify 에서 item 값을 실제 DB 에 들어간 값으로 바꿔준다.
	// (드물지만 DB 에 넣을때 넘겨준 값을 가공해서 바꾸는 경우 있음)		
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

	// ModifyData() 호출되면 DB Notify 에서 item 값을 실제 DB 에 들어간 값으로 바꿔준다.
	// (드물지만 DB 에 넣을때 넘겨준 값을 가공해서 바꾸는 경우 있음)		
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
//	// Data 하나 수정은 어차피 겁나 빠르기 때문에 
//	// 조금 더 빨리 수행하는 것이 의미없다.
//	// 따로 처리해서 쪼잔한 성능 향상을 하기 보다는 코드를 깔끔하게 유지하는 걸로...
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
//		// Realtime Sort (처리 후 정렬되어 있어야 함)
//		// 미구현
//		ASSERT(0);		
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (현재 순서를 유지해야함)
//		// 무조건 제일 밑에 추가하면 된다
//
//		for (std::vector<MKey>::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
//		{
//			ASSERT(!m_map.Lookup(*iter));
//			m_map.SetAt(*iter, m_rows.AddTail(new ITEM(*iter)));
//		}
//
//		// TODO: 추가된 키들이 다 크고 Sorting 된 상태라면??
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
//		ASSERT(!pRow); // 위에서 처음 추가했으므로 NULL.
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
//	// Data 하나 수정은 어차피 겁나 빠르기 때문에 
//	// 조금 더 빨리 수행하는 것이 의미없다.
//	// 따로 처리해서 쪼잔한 성능 향상을 하기 보다는 코드를 깔끔하게 유지하는 걸로...
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
//		// Realtime Sort (처리 후 정렬되어 있어야 함)
//		// 미구현
//		ASSERT(0);		
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (현재 순서를 유지해야함)	
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
//	// Data 하나 수정은 어차피 겁나 빠르기 때문에 
//	// 조금 더 빨리 수행하는 것이 의미없다.
//	// 따로 처리해서 쪼잔한 성능 향상을 하기 보다는 코드를 깔끔하게 유지하는 걸로...
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
//		// Realtime Sort (Sorting 상태를 유지해야함)
//		// 미구현
//		ASSERT(0);
//		m_isSorted = TRUE;
//	}
//	else
//	{
//		// Non Realtime Sort (현재 순서를 유지해야함)		
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
//		// TODO: 키 변경은 없다면? 있어도 순서가 안 바뀐다면?
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
//		ASSERT(!pRow); // 위에서 NULL 로 만들었음.
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
//		// Table에서 Modify 시 Update 할 것 없음
//	}
//	else
//	{
//		// Modifty는 개수 안 바뀌므로
//		// RebuildIndex();
//		GetTable()->UpdateData();
//	}
//}
