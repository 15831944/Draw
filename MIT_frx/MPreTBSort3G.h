#pragma once

#include "MTBSort.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MPreTableDB3G;
		class __MY_EXT_CLASS__ MPreTBSort3G : public MTBSort
		{
		public:
			MPreTBSort3G(MPreTableDB3G* pTableDB);
			virtual ~MPreTBSort3G();

			// TableDB
		private:
			MPreTableDB3G* GetPreTableDB3G() { return reinterpret_cast<MPreTableDB3G*>(GetTableDB()); }

			// ITBSort Impl - Sort
		public:
			virtual BOOL PrivateSort();
		};
	}
}

#include "HeaderPost.h"