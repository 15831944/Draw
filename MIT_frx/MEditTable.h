#pragma once

#include "MTable.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MEditTable : public MTable
		{
			DECLARE_DYNAMIC(MEditTable)

		public:
			MEditTable();
			virtual ~MEditTable();

			// TableDB
		public:
			virtual ITableDB* GetTableDB() const = 0;

			// Event Handler		
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
		};
	}
}

#include "HeaderPost.h"
