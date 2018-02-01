#include "stdafx.h"
#include "MTableDB.h"

using namespace mit;
using namespace mit::frx;

MTableDB::MTableDB(ITable* pTable, MTBSchemaBase* pSchema, ITBSort* pSort, ITBClipboard* pClipboard) :
	m_pDoc(nullptr),
	m_pTable(pTable),
	m_pSchema(pSchema),
	m_pSort(pSort),
	m_pClipboard(pClipboard)
{
}

MTableDB::~MTableDB()
{
}

BOOL MTableDB::GetItem(_variant_t& varValue, int nRow, int nCol) const
{	
	ASSERT(nRow >= 0 && nRow < GetRowCount());
	ASSERT(nCol >= 0 && nCol < m_pSchema->GetColumnCount());
	const MTBColumn& column = m_pSchema->GetColumn(nCol);

	switch (column.GetType())
	{
	case MTBColumn::TB_KEY: varValue = GetKey(nRow); break;
	case MTBColumn::TB_FOREIGN: return GetForeignItem(varValue, nRow, nCol);
	default: column.GetItem(varValue, GetRow(nRow)); break;
	}

	return TRUE;
}

BOOL MTableDB::GetRow(std::vector<_variant_t*>& aItems, int nRow) const
{
	ASSERT(nRow >= 0 && nRow < GetRowCount());
	ASSERT(m_pSchema->GetColumnCount() == (int)aItems.size());
	int nItemCount = (int)aItems.size();

	LPCVOID pRow = GetRow(nRow);
	for (int i = 0; i < nItemCount; i++)
	{
		const MTBColumn& column = m_pSchema->GetColumn(i);
		switch (column.GetType())
		{
		case MTBColumn::TB_KEY: *aItems[i] = GetKey(nRow); break;
		case MTBColumn::TB_FOREIGN: return GetForeignItem(*aItems[i], nRow, i);
		default: column.GetItem(*aItems[i], pRow); break;
		}
	}

	return TRUE;
}

const CDocument* MTableDB::GetUnitListenerDoc()
{
	return m_pDoc;
}

void MTableDB::OnUnitChanged()
{
	for (MTBColumn* pColumn : m_pSchema->GetColumns()) pColumn->UpdateUnitConvertCurrent();
	m_pTable->UpdateUnit();
}