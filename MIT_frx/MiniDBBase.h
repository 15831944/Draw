////////////////////////////////////////////////////////////////////////
// 전처리 테이블 구현용 미니DB
// Key 기반의 2세대 DB 와 
// Iterator 개념이 추가된 3세대 DB 의 특징을 다 담는다

#pragma once

#include "../MIT_lib/MTypeDef.h"

#include <vector>
#include "atlcoll.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class CMiniDBBase
		{	
		public:
			struct ITEM
			{
				MKey key;
				LPVOID pData;

				ITEM(MKey k, LPVOID d) : key(k), pData(d) { }
				~ITEM() { }
			};
			
		public:
			static CAtlList<ITEM*> templist; // GetNext, GetPrev 용
			static MKey GetKey(MIterator iter) 
			{
				ASSERT(iter);
				return templist.GetAt((POSITION)iter)->key;
			}
			static LPCVOID GetData(MIterator iter)
			{
				ASSERT(iter);
				return templist.GetAt((POSITION)iter)->pData;
			}
			static void GetNext(MIterator& iter)
			{
				ASSERT(iter);
				templist.GetNext((POSITION&)iter);
			}
			static void GetPrev(MIterator& iter)
			{
				ASSERT(iter);
				templist.GetPrev((POSITION&)iter);
			}
		};
	}
}

#include "HeaderPost.h"
