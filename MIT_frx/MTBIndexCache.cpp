#include "stdafx.h"
#include "MTBIndexCache.h"

using namespace mit;
using namespace mit::frx;

void MTBIndex::Rebuild()
{
	MSimpleProfiler sp(_T("RebuildIndex(%d)"), (int)m_pRows->GetCount());
	// �� �Լ� ���� ����� ��.
	// TODO: ���� ���� ���ɼ�
	// 1. Head ���� �ε������� �ʰ� ������ �κи� �����ϵ��� �Ҽ��� ������...
	//    ���� ������...
	// 2. ���� ȭ�鿡 �������� row ������ �տ����� �ڿ����� ������ʿ��� �ε����صΰ�
	//    ���߿� �ʿ������� ���� Indexing
	//    ��ũ���� �߰��� ������ ���� ��������.
	//    ��ũ���� ó���� �ִ� ���·� ���ŵ� �ڿ� ���������� �� ���� �ű�� �����̰� �������.
	// 3. TableDB Ŭ���������� ��� Indexing Thread �ϳ� ������
	//    Ŭ������ Thread Safe �ϰ� �ۼ�. (Ŭ���� ������ �ȳ����ϱ� �����ϱ� �����...)
	//    Index �ʿ��Ҷ� Thread�� ���� Indexing ���س����� ���2 ó�� ���� Indexing
	// 3 �� �� ���ٰ� ���������� 2 �� ���ɰ��� �ϴ°� ������...

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

	// before index (Data�� Index ��)
	// after index (Data�� Index ��)
	// * ���� : pos_a, pos_b �� m_cachedIndex �ɷ� �����ٰ�
	//          m_data �ɷ� �ٲ��. ���� �߿� �Լ��� ���� �� ���� ����.
	//          �˾Ƽ� ����ȭ �Ƿ���??
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
	// ��ġ�� �� before == 0
	ASSERT(distance_b >= 0);

	int distance_a = -INT_MAX;
	if (pos_a)
	{
		distance_a = nRow - m_cachedIndex.GetAt(pos_a)->m_key;
		pos_a = m_cachedIndex.GetAt(pos_a)->m_value;
	}
	// after �� 0 �� ���ü� ����
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

	// before, after �� ������ ã��
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

	// ã�� Index �� Data �� �Ÿ��� 
	// CACHED_INDEX_UNIT ���� ũ�ų� ���� ��쿡�� CacheIndex ����
	bMakeCacheIndex &= abs(distance) >= m_cacheDivider.DEVIDE_BY;

	// POSITION ���ϱ�
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

	// before index (Data�� Index ��)
	int i = m_divider.Divide(nRow);
	ASSERT(i < (int)m_index.GetCount());
	POSITION pos_b = m_index[i];
	int distance_b = m_divider.Remainder(nRow);

	// after index (Data�� Index ��)
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

	// before, after �� ������ ã��
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

	// POSITION ���ϱ�
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