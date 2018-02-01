#pragma once

#include "MTable.h"
#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MPostTable : public mit::frx::MTable
		{
			DECLARE_DYNAMIC(MPostTable)
			
		public:
			MPostTable();
			virtual ~MPostTable();

			// TableDB
		public:
			virtual ITableDB* GetTableDB() const = 0;

		protected:
			virtual void MakeContextMenu(CMenu& menu);

			// Event Handler
		protected:
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"
