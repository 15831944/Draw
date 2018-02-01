#include "stdafx.h"
#include "MPostTableDB.h"

using namespace mit;
using namespace mit::frx;

MPostTableDB::MPostTableDB(ITable* pTable, MTBSchemaBase* pSchema) :
	MTableDB(pTable, pSchema, &m_sort, &m_clipboard),
	m_sort(this), m_clipboard(this)
{	
}

MPostTableDB::~MPostTableDB()
{
}

LPCVOID MPostTableDB::GetRow(int nRow) const
{
	ASSERT(m_records.size() <= INT_MAX);
	ASSERT(nRow >= 0 && nRow < (int)m_records.size());
	LPCVOID& pRow = m_records.at(nRow);
	if (!pRow)
	{
		if (!GetData(nRow, pRow)) { ASSERT(0); return NULL; }
		ASSERT(pRow);
	}
	return pRow;
}

void MPostTableDB::InitRows()
{
	m_records.clear();
	size_t size = GetDataCount();
	m_records.resize(size);
	ZeroMemory(m_records.data(), sizeof(LPCVOID) * size);
}

void MPostTableDB::DestroyRows()
{
	m_records.clear();
}

void MPostTableDB::FillRowAll()
{
	int nCount = GetRowCount();
	for (int i = 0; i < nCount; i++)
	{
		LPCVOID& pRow = m_records.at(i);
		if (!pRow)
		{
			if (!GetData(i, pRow)) { ASSERT(0); return; }
			ASSERT(pRow);
		}
	}
}

int MPostTableDB::GetRowCount() const
{
	ASSERT(m_records.size() <= INT_MAX);
	return (int)m_records.size();
}

BOOL MPostTableDB::ModifyItem(int nRow, int nCol, _variant_t& item)
{
	MTBChangedFromTable<TModifiedItem> cft(m_modifiedItem, TModifiedItem(nRow, nCol, &item));

	const MTBColumn& column = m_pSchema->GetColumn(nCol);
	LPVOID pModifiedData = m_pSchema->GetCopyData(m_records[nRow]);
	column.SetItem(pModifiedData, item);

	return ModifyData(nRow, nCol, pModifiedData);
}

BOOL MPostTableDB::ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems)
{
	MTBChangedFromTable<TModifiedRow> cft(m_modifiedRow, TModifiedRow(nRow, aModifiedRowItems));

	ASSERT(m_pSchema->GetColumnCount() == (int)aModifiedRowItems.size());
	int nItemCount = (int)aModifiedRowItems.size();

	LPVOID pModifiedData = m_pSchema->GetCopyData(m_records[nRow]);
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = m_pSchema->GetColumn(i);
		column.SetItem(pModifiedData, *aModifiedRowItems[i]);
	}
	
	return ModifyData(std::vector<int>(1, nRow), std::vector<LPCVOID>(1, pModifiedData));
}