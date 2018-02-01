#pragma once

#include "MTBSort.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MPreTableDB2G;
		class __MY_EXT_CLASS__ MPreTBSort2G : public MTBSort
		{
		public:
			MPreTBSort2G(MPreTableDB2G* pTableDB);
			virtual ~MPreTBSort2G();

			// TableDB
		private:
			MPreTableDB2G* GetPreTableDB2G() { return reinterpret_cast<MPreTableDB2G*>(GetTableDB()); }

			// ITBSort Impl - Sort
		public:
			virtual BOOL PrivateSort();

			// Compare
		private:
			virtual int CompareItem(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol);
		};
	}
}

#include "HeaderPost.h"