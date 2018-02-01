#pragma once

#include "MGridItem.h"
#include "ITBDataMap.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// m_lstOption 대신 DataMap 을 사용함
		class __MY_EXT_CLASS__ MStoreGridItemValue
		{
		private:
			_variant_t& m_varValue;
			_variant_t m_varValueOrg;
		public:
			MStoreGridItemValue(_variant_t& varValue) : m_varValue(varValue), m_varValueOrg(varValue) {}
			~MStoreGridItemValue() { m_varValue = m_varValueOrg; }
		};

		class __MY_EXT_CLASS__ MGridDataMapComboItem : public MGridItem
		{
			DECLARE_SERIAL(MGridDataMapComboItem)

			friend class MTable;
			friend class MGridRow;
		public:
			MGridDataMapComboItem();
			MGridDataMapComboItem(ITBDataMap* pDisplayMap);
			virtual ~MGridDataMapComboItem();

		protected:
			ITBDataMap* m_pDisplayMap;
			BOOL m_bDropList;		// TODO: 미구현	

		protected:
			virtual void Init();
			virtual void SetFlags();
		public:
			virtual BOOL OnEdit(LPPOINT lptClick);
			virtual BOOL OnDblClick(CPoint point);
			virtual BOOL PushChar(UINT nChar);
		};
	}
}

#include "HeaderPost.h"