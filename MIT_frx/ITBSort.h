#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		struct __MY_EXT_CLASS__ TBSortColumn
		{
			int nColumn;
			BOOL bAscending;
			TBSortColumn() : nColumn(0), bAscending(TRUE) {}
			TBSortColumn(int nCol, BOOL bAsc) : nColumn(nCol), bAscending(bAsc) {}
			TBSortColumn(const TBSortColumn& src) : nColumn(src.nColumn), bAscending(src.bAscending) {}
			void operator=(const TBSortColumn& src) { nColumn = src.nColumn; bAscending = src.bAscending; }
		};

		class __MY_EXT_CLASS__ ITBSort
		{
		public:
			// Sort Column
			virtual void SetSortColumns(const CAtlList<TBSortColumn>& lstSortcol) = 0;
			virtual void AddSortColumn(const TBSortColumn& sortcol) = 0;
			virtual BOOL RemoveSortColumn(int nColumn) = 0;
			virtual void RemoveAllSortColumns() = 0;
			virtual int GetSortColumns(CAtlList<TBSortColumn>& lstSortcol) const = 0;
			virtual BOOL GetSortColumn(int nColumn, TBSortColumn& sortcol) const = 0;

			// Sort
			virtual BOOL Sort() = 0;
		};
	}
}

#include "HeaderPost.h"