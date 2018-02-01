#include "stdafx.h"
#include "MPreTBSort3G.h"

#include "MPreTableDB3G.h"
#include "MTBProgressCtrlHelper.h"

using namespace mit::frx;

MPreTBSort3G::MPreTBSort3G(MPreTableDB3G* pTableDB) :
	MTBSort(pTableDB)
{
}

MPreTBSort3G::~MPreTBSort3G()
{
}

BOOL MPreTBSort3G::PrivateSort()
{
	CAtlMap<MIterator, POSITION>& map = GetPreTableDB3G()->m_map;
	CAtlList<MIterator>& data = GetPreTableDB3G()->m_rows;
	size_t nDataCount = data.GetCount();
	
	std::vector<LPCVOID> sorted_data;
	{
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
		for (std::vector<LPCVOID>::const_iterator iter = sorted_data.cbegin(); iter != sorted_data.cend(); iter++)
		{
			map.SetAt((MIterator)*iter, data.AddTail((MIterator)*iter));
			progressBar.SetPos(++i);
		}

		GetPreTableDB3G()->m_index.Rebuild();
	}

	return TRUE;
}