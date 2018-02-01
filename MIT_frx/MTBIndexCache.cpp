#include "stdafx.h"
#include "MTBIndexCache.h"

using namespace mit;
using namespace mit::frx;

void MTBIndex::Rebuild()
{
	MSimpleProfiler sp(_T("RebuildIndex(%d)"), (int)m_pRows->GetCount());
	// 이 함수 존나 빨라야 함.
	// TODO: 성능 개선 가능성
	// 1. Head 부터 인덱싱하지 않고 수정된 부분만 갱신하도록 할수도 있을듯...
	//    쉽진 않을듯...
	// 2. 현재 화면에 보여야할 row 까지만 앞에서든 뒤에서든 가까운쪽에서 인덱싱해두고
	//    나중에 필요해질때 마다 Indexing
	//    스크롤이 중간에 있을때 가장 느리겠지.
	//    스크롤이 처음에 있는 상태로 갱신된 뒤에 마지막으로 한 번에 옮기면 딜레이가 생기겠지.
	// 3. TableDB 클래스에서만 노는 Indexing Thread 하나 돌리기
	//    클래스를 Thread Safe 하게 작성. (클래스 밖으로 안나가니까 관리하기 쉬울듯...)
	//    Index 필요할때 Thread가 아직 Indexing 안해놨으면 방법2 처럼 직접 Indexing
	// 3 은 좀 오바고 현실적으로 2 로 성능개선 하는게 좋을듯...

	m_cachedIndex.RemoveAll();
	size_t size = m_divider.Divide((int)m_pRows->GetCount()) + 1;
	m_index.SetCount(size);

	//register int i = 0;
	//register int j = 0;
	//POSITION pos = m_pRows->GetHeadPosition();
	//while (pos)
	//{
	//	for (i = 0; i < m_divider.DEVIDE_BY; i++) m_pRows->GetNext(pos);
	//	m_index[j++] = pos;
	//}

	register int i = 0;
	register int j = -1;
	POSITION pos = m_pRows->GetHeadPosition();
	while (pos)
	{
		if (m_divider.IsDivisible(i) ) m_index[++j] = pos;
		m_pRows->GetNext(pos);
		i++;
	}
}

POSITION MTBIndex::RowToPosition(int nRow, BOOL bMakeCacheIndex)
{
	ASSERT(m_pRows->GetCount() <= INT_MAX);
	if (nRow >= (int)m_pRows->GetCount()) return NULL;

	// before index (Data가 Index 뒤)
	// after index (Data가 Index 앞)
	// * 주의 : pos_a, pos_b 가 m_cachedIndex 걸로 쓰였다가
	//          m_data 걸로 바뀐다. 성능 중요 함수라 변수 덜 쓰고 싶음.
	//          알아서 최적화 되려나??
	POSITION pos_a = m_cachedIndex.FindFirstKeyAfter(nRow);
	POSITION pos_b = pos_a;
	if (!pos_b) pos_b = m_cachedIndex.GetTailPosition();
	else m_cachedIndex.GetPrev(pos_b);

	int distance_b = INT_MAX;
	if (pos_b)
	{
		distance_b = nRow - m_cachedIndex.GetAt(pos_b)->m_key;
		pos_b = m_cachedIndex.GetAt(pos_b)->m_value;
	}
	// 일치할 때 before == 0
	ASSERT(distance_b >= 0);

	int distance_a = -INT_MAX;
	if (pos_a)
	{
		distance_a = nRow - m_cachedIndex.GetAt(pos_a)->m_key;
		pos_a = m_cachedIndex.GetAt(pos_a)->m_value;
	}
	// after 는 0 안 나올수 없음
	ASSERT(distance_a < 0);

	if (m_divider.Remainder(nRow) < distance_b)
	{
		int i = m_divider.Divide(nRow);
		ASSERT(i < (int)m_index.GetCount());
		pos_b = m_index[i];
		distance_b = m_divider.Remainder(nRow);
	}

	if (m_divider.Remainder(nRow) - m_divider.DEVIDE_BY > distance_a)
	{
		int i = m_divider.Divide(nRow) + 1;
		ASSERT(i <= (int)m_index.GetCount());
		if (i < (int)m_index.GetCount()) 
		{
			pos_a = m_index[i];
			distance_a = m_divider.Remainder(nRow) - m_divider.DEVIDE_BY;
		}
		else
		{
			pos_a = NULL;
			distance_a = nRow - (int)m_pRows->GetCount();
		}
	}
	ASSERT(distance_b >= 0 && distance_b < m_divider.DEVIDE_BY);
	ASSERT(distance_a < 0 && distance_b >= -m_divider.DEVIDE_BY);

	// before, after 중 가까운거 찾기
	POSITION pos = NULL;
	int distance = 0;
	if (distance_b <= abs(distance_a)) 
	{
		pos = pos_b;
		distance = distance_b;
	}
	else
	{
		pos = pos_a;
		distance = distance_a;
	}

	// 찾은 Index 와 Data 의 거리가 
	// CACHED_INDEX_UNIT 보다 크거나 같을 경우에만 CacheIndex 생성
	bMakeCacheIndex &= abs(distance) >= m_cacheDivider.DEVIDE_BY;

	// POSITION 구하기
	if (distance < 0)
	{
		if (!pos)
		{
			pos = m_pRows->GetTailPosition();
			distance++;
		}
		while (distance < 0)
		{
			m_pRows->GetPrev(pos);
			distance++;
		}
	}
	else
	{
		while (distance > 0)
		{
			m_pRows->GetNext(pos);
			distance--;
		}
	}

	if (bMakeCacheIndex)
	{
		m_cachedIndex.SetAt(nRow, pos);
	}

	ASSERT(pos);
	return pos;
}

POSITION MTBIndex::RowToPositionNoCache(int nRow)
{
	ASSERT(m_pRows->GetCount() <= INT_MAX);
	if (nRow >= (int)m_pRows->GetCount()) return NULL;

	// before index (Data가 Index 뒤)
	int i = m_divider.Divide(nRow);
	ASSERT(i < (int)m_index.GetCount());
	POSITION pos_b = m_index[i];
	int distance_b = m_divider.Remainder(nRow);

	// after index (Data가 Index 앞)
	POSITION pos_a = NULL;
	int distance_a = 0;
	i++;
	ASSERT(i <= (int)m_index.GetCount());
	if (i < (int)m_index.GetCount()) 
	{
		pos_a = m_index[i];
		distance_a = m_divider.Remainder(nRow) - m_divider.DEVIDE_BY;
	}
	else
	{
		pos_a = NULL;
		distance_a = nRow - (int)m_pRows->GetCount();
	}

	// before, after 중 가까운거 찾기
	POSITION pos = NULL;
	int distance = 0;
	if (distance_b <= abs(distance_a)) 
	{
		pos = pos_b;
		distance = distance_b;
	}
	else
	{
		pos = pos_a;
		distance = distance_a;
	}

	// POSITION 구하기
	if (distance < 0)
	{
		if (!pos)
		{
			pos = m_pRows->GetTailPosition();
			distance++;
		}
		while (distance < 0)
		{
			m_pRows->GetPrev(pos);
			distance++;
		}
	}
	else
	{
		while (distance > 0)
		{
			m_pRows->GetNext(pos);
			distance--;
		}
	}

	return pos;
}

void MTBIndex::RemoveAll()
{
	m_index.RemoveAll();
	m_cachedIndex.RemoveAll();
}