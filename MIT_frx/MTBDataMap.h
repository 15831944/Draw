#pragma once

#include "ITBDataMap.h"
#include "MTBConvertor.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// ValueItem : 실제 Data
		// DisplayItem : Table 에 들어가는 Data (화면상에 보이는 Data, Copy/Paste 용 Data, Sorting 용 Data)
		template <typename VALUE_TYPE, typename DISPLAY_TYPE>
		class MTBDataMap : public ITBDataMap
		{			
			DECLARE_DYNCREATE(MTBDataMap)

		public:
			MTBDataMap() : m_useDefaultDisplay(FALSE), m_useDefaultValue(FALSE), m_bAllowDuplicate(TRUE) {}
			virtual ~MTBDataMap() {}

		private:
			static const int MAX_ITEM = 1024;
			CAtlList<DISPLAY_TYPE> m_order;
			CRBMap<VALUE_TYPE, POSITION> m_mapDisplay;
			CRBMap<DISPLAY_TYPE, VALUE_TYPE> m_mapValue;
			BOOL m_useDefaultDisplay;
			BOOL m_useDefaultValue;
			DISPLAY_TYPE m_defaultDisplay;
			VALUE_TYPE m_defaultValue;
			BOOL m_bAllowDuplicate;

		public:
			virtual void SetDefaultDisplay(_variant_t display) { m_useDefaultDisplay = TRUE; m_defaultDisplay = (DISPLAY_TYPE)display; }
			virtual void SetDefaultValue(_variant_t val) { m_useDefaultValue = TRUE; m_defaultValue = (VALUE_TYPE)val; }
			virtual void ClearDefaultDisplay() { m_useDefaultDisplay = FALSE; m_defaultDisplay = DISPLAY_TYPE(); }
			virtual void ClearDefaultValue() { m_useDefaultValue = FALSE; m_defaultValue = VALUE_TYPE(); }

		public:
			virtual BOOL AddItem(_variant_t val, _variant_t display) { return AddItem(val, display, TRUE); }
			BOOL AddItem(_variant_t val, _variant_t display, BOOL bDefaultValue);
			virtual BOOL RemoveItem(_variant_t val);

		public:
			virtual LPCVOID GetDisplayItem(LPCVOID pVal) const
			{
				const CRBMap<VALUE_TYPE, POSITION>::CPair* pPair = m_mapDisplay.Lookup(MTBConvertor<VALUE_TYPE>::Convert(pVal));
				return pPair ? &(m_order.GetAt(pPair->m_value)) : (m_useDefaultDisplay ? &m_defaultDisplay : nullptr);
			}

			virtual _variant_t GetValueItem(const _variant_t& varValue) const
			{
				const CRBMap<DISPLAY_TYPE, VALUE_TYPE>::CPair* pPair = m_mapValue.Lookup((DISPLAY_TYPE)varValue);
				return pPair ? _variant_t(pPair->m_value) : (m_useDefaultValue ? _variant_t(m_defaultValue) : _variant_t());		
			}

		public:
			virtual size_t GetCount() const { return m_order.GetCount(); }
			virtual POSITION GetHeadPosition() const { return m_order.GetHeadPosition(); }
			virtual POSITION Find(const _variant_t& item) const 
			{
				const CRBMap<DISPLAY_TYPE, VALUE_TYPE>::CPair* pPair = m_mapValue.Lookup((DISPLAY_TYPE)item);
				if (!pPair) return NULL;
				ASSERT(m_mapDisplay.Lookup(pPair->m_value));
				return m_mapDisplay.Lookup(pPair->m_value)->m_value;
			}
			virtual _variant_t GetNext(POSITION& pos) const 
			{
				return _variant_t(m_order.GetNext(pos)); 
			}
			virtual _variant_t GetAt(POSITION pos) const 
			{
				return _variant_t(m_order.GetAt(pos)); 
			}
		};

		IMPLEMENT_DYNCREATE_TEMPLATE_2(MTBDataMap, typename, typename, ITBDataMap)

		template <typename VALUE_TYPE, typename DISPLAY_TYPE>
		BOOL MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::AddItem(_variant_t val, _variant_t display, BOOL bDefaultValue)
		{
			if (m_mapDisplay.Lookup((VALUE_TYPE)val)) return FALSE;			
			CRBMap<DISPLAY_TYPE, VALUE_TYPE>::CPair* pPair = m_mapValue.Lookup((DISPLAY_TYPE)display);
			if (pPair)
			{
				if (!m_bAllowDuplicate) return FALSE;
				ASSERT(m_mapDisplay.Lookup(pPair->m_value));
				m_mapDisplay.SetAt((VALUE_TYPE)val, m_mapDisplay.Lookup(pPair->m_value)->m_value);
				if (bDefaultValue) m_mapValue.SetAt((DISPLAY_TYPE)display, (VALUE_TYPE)val);
			}
			else
			{
				m_mapDisplay.SetAt((VALUE_TYPE)val, m_order.AddTail((DISPLAY_TYPE)display));
				m_mapValue.SetAt((DISPLAY_TYPE)display, (VALUE_TYPE)val);
			}
			return TRUE;
		}

		template <typename VALUE_TYPE, typename DISPLAY_TYPE>
		BOOL MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::RemoveItem(_variant_t val)
		{
			CRBMap<VALUE_TYPE, POSITION>::CPair* pPairDisplay = m_mapDisplay.Lookup((VALUE_TYPE)val);
			if (!pPairDisplay) return FALSE;
			ASSERT(m_mapValue.Lookup(m_order.GetAt(pPairDisplay->m_value)));
			m_mapValue.RemoveKey(m_order.GetAt(pPairDisplay->m_value));
			m_order.RemoveAt(pPairDisplay->m_value);
			m_mapDisplay.RemoveAt(pPairDisplay);
			return TRUE;
		}
	}
}

#include "HeaderPost.h"