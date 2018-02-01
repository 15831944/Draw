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
	// 1000������ 2�� 4õ���� ���� Compare
	ASSERT(data.size() <= INT_MAX);
	int nDataCount = (int)data.size();
	int nUpper = MTBSort::GetApproximateCompareCount(nDataCount);
	MTBProgressCtrlHelper progressBar(GetTableDB()->GetTable(), 0, nUpper, m_bCanCancel, _STR("Sorting..."), FALSE, &m_posProgressHelper);
	m_nProgressPos = 0;

	// TODO: ������ �ܵ� ������ ��� RadixSort

	// 1000���� double �� �ϳ��� ���Ľ� 
	// ParallelBufferedSort : �� 5.5sec, ���Ļ��·� �� ����� 3.8sec
	// StlSort : �� 14sec, ���Ļ��·� �� ����� 7sec
	// QSort : �� 12sec, ���Ļ��·� �� ����� 6sec
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
				// ��ٸ��� ����߳�...
				// �̾��ϴ�. �� ������ ����� ����...
				s_sort = NULL;
				m_mainThreadID = 0;
				std::copy(org.begin(), org.end(), data.begin());
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("������ ��ҵǾ����ϴ�."));
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
				GetTable()->GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("������ ��ҵǾ����ϴ�."));
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
	// ����� less than (STL sort)
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
	// ����� less than (STL sort)
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
		// Group ��� �̱���
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
	// m_nProgressPos ����� ����ó���� �־� ������ ���� �κ� ����.
	// int, �������� ++ ������ ���ڼ� ���� ������ m_nProgressPos �� ������.
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
	// ���ɻ� ������ ���д�
	ASSERT(0);
	return 0;
}

int MTBSort::CompareItem(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol)
{	
	const MTBColumn& column = GetSchema()->GetColumn(sortcol.nColumn);
	// TODO: DisplayMap �ִ� ��� Radix �� ����
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
