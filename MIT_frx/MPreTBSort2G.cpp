#include "stdafx.h"
#include "MPreTBSort2G.h"

#include "MPreTableDB2G.h"
#include "MTBProgressCtrlHelper.h"

using namespace mit::frx;
using namespace mit::lib;

MPreTBSort2G::MPreTBSort2G(MPreTableDB2G* pTableDB) :
	MTBSort(pTableDB)
{
}

MPreTBSort2G::~MPreTBSort2G()
{
}

BOOL MPreTBSort2G::PrivateSort()
{
	CAtlMap<MKey, POSITION>& map = GetPreTableDB2G()->m_map;
	CAtlList<MPreTableDB2G::ITEM*>& data = GetPreTableDB2G()->m_rows;
	size_t nDataCount = data.GetCount();

	std::vector<LPCVOID> sorted_data;
	{
		MSimpleProfiler sp(_T("Sort-CopyList(%d)"), nDataCount);
		sorted_data.reserve(nDataCount);
		POSITION pos = data.GetHeadPosition();
		while (pos) sorted_data.push_back((LPCVOID)data.GetNext(pos));
	}

	if (!MTBSort::Sort(sorted_data, FALSE)) return FALSE;

	{
		MSimpleProfiler sp(_T("Sort-Remapping(%d)"), nDataCount);
		MTBProgressCtrlHelper progressBar(GetTableDB()->GetTable(), 0, (int)nDataCount, FALSE, _STR("Remapping..."));
		int i = 0;

		data.RemoveAll();	
		map.RemoveAll();
		for (LPCVOID pRow : sorted_data)
		{
			map.SetAt(((MPreTableDB2G::ITEM*)pRow)->key, data.AddTail((MPreTableDB2G::ITEM*)pRow));
			progressBar.SetPos(++i);
		}

		GetPreTableDB2G()->m_index.Rebuild();
	}

	return TRUE;
}

int MPreTBSort2G::CompareItem(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol)
{
	if (GetSchema()->GetColumn(sortcol.nColumn).IsKeyType())
	{
		return (sortcol.bAscending) ?
			((MPreTableDB2G::ITEM*)pRow1)->key - ((MPreTableDB2G::ITEM*)pRow2)->key :
			((MPreTableDB2G::ITEM*)pRow2)->key - ((MPreTableDB2G::ITEM*)pRow1)->key;
	}
	return MTBSort::CompareItem(((MPreTableDB2G::ITEM*)pRow1)->data, ((MPreTableDB2G::ITEM*)pRow2)->data, sortcol);
}