#include "stdafx.h"
#include "MTBSort.h"

#include "MTableDB.h"
#include "MTBProgressCtrlHelper.h"

#include <ppl.h>

using namespace mit::frx;
using namespace mit::lib;
using namespace concurrency;

MTBSort* MTBSort::s_sort = NULL;

MTBSort::MTBSort(ITableDB* pTableDB) :
	m_pTableDB(pTableDB),
	m_pSchema(pTableDB->GetSchema()),
	m_bCanCancel(TRUE),
	m_nGroupCount(0),
	m_nProgressPos(0),
	m_posProgressHelper(NULL),
	m_mainThreadID(0)
{
}

MTBSort::~MTBSort()
{
	ASSERT(!s_sort);
}

void MTBSort::SetSortColumns(const CAtlList<TBSortColumn>& lstSortCol)
{
	PrivateSetSortColumns(lstSortCol); 
	GetTableDB()->GetTable()->UpdateSortColumns();
}

void MTBSort::AddSortColumn(const TBSortColumn& sortcol) 
{ 
	PrivateAddSortColumn(sortcol);
	GetTableDB()->GetTable()->UpdateSortColumns();
}

BOOL MTBSort::RemoveSortColumn(int nColumn)
{
	if (!PrivateRemoveSortColumn(nColumn)) return FALSE;
	GetTableDB()->GetTable()->UpdateSortColumns();
	return TRUE;
}

void MTBSort::RemoveAllSortColumns()
{
	PrivateRemoveAllSortColumns();
	GetTableDB()->GetTable()->UpdateSortColumns();
}

void MTBSort::PrivateRemoveAllSortColumns()
{
	m_lstSortCol.RemoveAll();
}

int MTBSort::GetSortColumns(CAtlList<TBSortColumn>& lstSortCol) const
{
	return CopyList(lstSortCol, m_lstSortCol);
}

POSITION MTBSort::FindSortColumn(int nColumn) const
{
	POSITION pos = m_lstSortCol.GetHeadPosition();
	while (pos)
	{
		if (m_lstSortCol.GetAt(pos).nColumn == nColumn) return pos;
		m_lstSortCol.GetNext(pos);
	}
	return NULL;
}

void MTBSort::PrivateSetSortColumns(const CAtlList<TBSortColumn>& lstSortCol)
{
	CopyList(m_lstSortCol, lstSortCol);
}

void MTBSort::PrivateAddSortColumn(const TBSortColumn& sortcol)
{
	POSITION pos = FindSortColumn(sortcol.nColumn);
	if (pos) m_lstSortCol.SetAt(pos, sortcol);
	else m_lstSortCol.AddTail(sortcol);
}

BOOL MTBSort::PrivateRemoveSortColumn(int nColumn)
{
	POSITION pos = FindSortColumn(nColumn);
	if (!pos) return FALSE;
	m_lstSortCol.RemoveAt(pos);
	return TRUE;
}

BOOL MTBSort::GetSortColumn(int nColumn, TBSortColumn& sortcol) const
{
	POSITION pos = FindSortColumn(nColumn);
	if (!pos) return FALSE;
	sortcol = m_lstSortCol.GetAt(pos);
	return TRUE;
}

BOOL MTBSort::Sort()  
{
	GetTableDB()->FillRowAll();
	if (PrivateSort())
	{
		GetTableDB()->GetTable()->UpdateData();
		return TRUE;
	}
	return FALSE;
}

BOOL MTBSort::Sort(std::vector<LPCVOID>& data, BOOL bRestoreCancel)
{
	// 1000만개면 2억 4천만번 정도 Compare
	ASSERT(data.size() <= INT_MAX);
	int nDataCount = (int)data.size();
	int nUpper = MTBSort::GetApproximateCompareCount(nDataCount);
	MTBProgressCtrlHelper progressBar(GetTableDB()->GetTable(), 0, nUpper, m_bCanCancel, _STR("Sorting..."), FALSE, &m_posProgressHelper);
	m_nProgressPos = 0;

	// TODO: 정수형 단독 정렬일 경우 RadixSort

	// 1000만개 double 열 하나로 정렬시 
	// ParallelBufferedSort : 약 5.5sec, 정렬상태로 또 수행시 3.8sec
	// StlSort : 약 14sec, 정렬상태로 또 수행시 7sec
	// QSort : 약 12sec, 정렬상태로 또 수행시 6sec
	void (MTBSort::*pfSort)(std::vector<LPCVOID>&);
	pfSort = &MTBSort::ParallelBufferedSort;

	if (m_bCanCancel)
	{
		if (bRestoreCancel)
		{
			std::vector<LPCVOID> org(data);
			try
			{
				(this->*pfSort)(data);
			}
			catch (MTBProgressCancel&)
			{
				// 기다리다 취소했노...
				// 미안하다. 더 빠르게 만들어 보께...
				s_sort = NULL;
				m_mainThreadID = 0;
				std::copy(org.begin(), org.end(), data.begin());
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("정렬이 취소되었습니다."));
				return FALSE;
			}
		}
		else
		{
			try
			{
				(this->*pfSort)(data);
			}
			catch (MTBProgressCancel&)
			{
				s_sort = NULL;
				m_mainThreadID = 0;
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("정렬이 취소되었습니다."));
				return FALSE;
			}
		}
	}
	else
	{
		(this->*pfSort)(data);
	}
	
	return TRUE;
}

void MTBSort::StlSort(std::vector<LPCVOID>& data)
{
	MSimpleProfiler profile(_T("StlSort(%d)"), GetTableDB()->GetRowCount());

	s_sort = this;
	std::sort(data.begin(), data.end(), StlCompareStatic);
	s_sort = NULL;
}

void MTBSort::QSort(std::vector<LPCVOID>& data)
{
	MSimpleProfiler profile(_T("QSort(%d)"), GetTableDB()->GetRowCount());

	s_sort = this;
	qsort(data.data(), data.size(), sizeof(LPCVOID), QCompareStatic);
	s_sort = NULL;
}

void MTBSort::ParallelSort(std::vector<LPCVOID>& data)
{
	MSimpleProfiler profile(_T("ParallelSort(%d)"), GetTableDB()->GetRowCount());

	m_mainThreadID = ::GetCurrentThreadId();
	s_sort = this;
	parallel_sort(data.begin(), data.end(), ParallelCompareStatic);
	s_sort = NULL;
	m_mainThreadID = 0;
}

void MTBSort::ParallelBufferedSort(std::vector<LPCVOID>& data)
{
	MSimpleProfiler profile(_T("ParallelBufferedSort(%d)"), GetTableDB()->GetRowCount());

	m_mainThreadID = ::GetCurrentThreadId();
	s_sort = this;
	parallel_buffered_sort(data.begin(), data.end(), ParallelCompareStatic);
	s_sort = NULL;
	m_mainThreadID = 0;
}

bool MTBSort::StlCompareStatic(LPCVOID pRow1, LPCVOID pRow2)
{
	ASSERT(s_sort);
	// 결과는 less than (STL sort)
	return s_sort->Compare(pRow1, pRow2) < 0;
}

int MTBSort::QCompareStatic(LPCVOID pRow1, LPCVOID pRow2)
{
	ASSERT(s_sort);
	return s_sort->Compare(*((LPCVOID*)pRow1), *((LPCVOID*)pRow2));
}

bool MTBSort::ParallelCompareStatic(LPCVOID pRow1, LPCVOID pRow2)
{
	ASSERT(s_sort);
	// 결과는 less than (STL sort)
	return s_sort->ParallelCompare(pRow1, pRow2) < 0;
}

int MTBSort::Compare(LPCVOID pRow1, LPCVOID pRow2)
{
	MTBProgressCtrlHelper::GetInstance(m_posProgressHelper)->SetPos(++m_nProgressPos);
	
	static int nCompare;
	static POSITION pos;
	nCompare = 0;
	pos = m_lstSortCol.GetHeadPosition();
	while (pos)
	{
		// Group 기능 미구현
		//nCompare = (iLevel < m_nGroupCount) ? 
		//	CompareGroup(row1, row2, nCol) :
		//	CompareItem(row1, row2, nCol);
		nCompare = CompareItem(pRow1, pRow2, m_lstSortCol.GetNext(pos));
		if (nCompare != 0) return nCompare;
	}
	return 0;
}

int MTBSort::ParallelCompare(LPCVOID pRow1, LPCVOID pRow2)
{
	// m_nProgressPos 말고는 병렬처리에 있어 문제될 만한 부분 없음.
	// int, 포인터의 ++ 연산은 원자성 갖기 때문에 m_nProgressPos 도 괜찮음.
	if (GetCurrentThreadId() == m_mainThreadID)
	{
			MTBProgressCtrlHelper::GetInstance(m_posProgressHelper)->SetPos(++m_nProgressPos);
	}
	else ++m_nProgressPos;

	int nCompare = 0;
	POSITION pos = m_lstSortCol.GetHeadPosition();
	while (pos)
	{
		nCompare = CompareItem(pRow1, pRow2, m_lstSortCol.GetNext(pos));
		if (nCompare != 0) return nCompare;
	}
	return 0;
}

int MTBSort::CompareGroup(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol)
{
	// 성능상 구현상 빼둔다
	ASSERT(0);
	return 0;
}

int MTBSort::CompareItem(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol)
{	
	const MTBColumn& column = GetSchema()->GetColumn(sortcol.nColumn);
	// TODO: DisplayMap 있는 놈들 Radix 로 정렬
	//int nRes = sortcol.HasRadix() ?
	//	sortcol.GetRadix(column.GetDwordPtr(pRow1)) - sortcol.GetRadix(column.GetDwordPtr(pRow2)) :
	//	column.CompareItem(pRow1, pRow2);
	//if (column.IsIntegerType())
	int nRes = column.CompareItem(pRow1, pRow2);
	return (sortcol.bAscending) ? nRes : -nRes;
}

int MTBSort::CopyList(CAtlList<TBSortColumn>& dst, const CAtlList<TBSortColumn>& src)
{
	if (dst.IsEmpty() && src.IsEmpty()) return 0;
	MSimpleProfiler profile(_T("CopyList(%d)"), src.GetCount());

	dst.RemoveAll();
	POSITION pos = src.GetHeadPosition();
	while (pos)
	{
		const TBSortColumn& sc = src.GetNext(pos);
		dst.AddTail(sc);
	}
	return static_cast<int>(dst.GetCount());
}
