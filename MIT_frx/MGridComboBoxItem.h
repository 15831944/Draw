#pragma once

#include "MGridItem.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MGridComboBoxItem : public MGridItem
		{
			DECLARE_SERIAL(MGridComboBoxItem)

			friend class MTable;
			friend class MGridRow;
		public:
			MGridComboBoxItem(void);
			virtual ~MGridComboBoxItem(void);

		protected:
			BOOL m_bDropList;		// TODO: ¹Ì±¸Çö	

		public:
			void SetCurItem(int idx);

		};
	}
}

#include "HeaderPost.h"