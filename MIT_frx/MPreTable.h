#pragma once

#include "MTable.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MPreTable : public MTable
		{
			DECLARE_DYNAMIC(MPreTable)

		public:
			MPreTable();
			virtual ~MPreTable();

			// TableDB
		public:
			virtual ITableDB* GetTableDB() const = 0;

		public:
			virtual void AfterExtraBottomCallback(BCGPGRID_DISPINFO* pdi) { AfterDataCallback(pdi); }

			// Event Handler		
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
		};
	}
}

#include "HeaderPost.h"
