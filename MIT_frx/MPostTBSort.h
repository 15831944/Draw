#pragma once

#include "MTBSort.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MPostTableDB;
		class __MY_EXT_CLASS__ MPostTBSort : public MTBSort
		{
		public:
			MPostTBSort(MPostTableDB* pTableDB);
			virtual ~MPostTBSort();

			// TableDB
		private:
			MPostTableDB* GetPostTableDB() { return reinterpret_cast<MPostTableDB*>(GetTableDB()); }

			// ITBSort Impl - Sort
		public:
			virtual BOOL PrivateSort();
		};
	}
}

#include "HeaderPost.h"