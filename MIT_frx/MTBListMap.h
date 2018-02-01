#pragma once

#include "atlcoll.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// 미구현
		// 순서가 있으면서 POSITION 으로 직접 접근가능하고
		// Insert
		template<typename KEY, typename DATA>
		class MTBListMap
		{
		public:
			MTBListMap();
			virtual ~MTBListMap();

		protected:
			CAtlList<DATA> m_datas;
			CAtlMap<KEY, POSITION> m_map;

		public:
			size_t GetCount() const
			{
				return m_datas.GetCount();
			}
			bool IsEmpty() const
			{
				return m_datas.IsEmpty();
			}
			POSITION GetHeadPosition() const
			{
				return m_rows.GetHeadPosition();
			}
			const DATA& GetNext(POSITION& pos) const
			{
				return m_rows.GetNext(pos);
			}
			DATA& GetNext(POSITION& pos)
			{
				return m_rows.GetNext(pos);
			}
			BOOL Remove(KEY key)
			{
				CAtlMap<KEY, POSITION>::CPair* pair = m_map.Lookup(key);
				if (!pair) return FALSE;
				m_rows.RemoveAt(pair->m_value);
				m_map.RemoveAtPos(pair);
				return TRUE;
			}
			void SetAtHead(KEY key, DATA data)
			{
				// 일부러 리턴 안함.
				// map 의 POSITION 은 노출 안하기 위해.
				// 근데 구현하다보면 노출해야 될지도 모름
				m_map.SetAt(key, m_datas.AddHead(data));
			}
			void SetAtTail(KEY key, DATA data)
			{
				m_map.SetAt(key, m_datas.AddTail(data));
			}
			void RemoveAll()
			{
				m_datas.RemoveAll();
				m_map.RemoveAll();
			}
		};
	}
}

#include "HeaderPost.h"