#pragma once

#include "MFastDivider.h"

#include "atlcoll.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTBIndex
		{
		public:
			MTBIndex(CAtlList<LPCVOID>* pRows) : m_pRows(pRows) { ASSERT(m_pRows); }

		protected:
			const CAtlList<LPCVOID>* m_pRows;
				
		protected:
			MFastDivider<int, 16> m_divider;
			MFastDivider<int, 10> m_cacheDivider;
			CAtlArray<POSITION> m_index;
			CRBMap<int, POSITION> m_cachedIndex; // Index ���̿� �߰��Ǵ� CachedIndex

		public:
			void Rebuild();
			POSITION RowToPosition(int nRow, BOOL bMakeCacheIndex = TRUE);						
			POSITION RowToPositionNoCache(int nRow); // Cache �Ⱦ��� ����. �ϴ� ���ֺ�. �ʿ������??
			void RemoveAll();
		};
	}
}

#include "HeaderPost.h"
