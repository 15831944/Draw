#include "stdafx.h"
#include "MGridColumnsInfo.h"
#include "MTable.h"

using namespace std;
using namespace mit;
using namespace mit::frx;

MFormatInfo MFormatInfo::s_default(D_FMT_FIXED, 2);

class MFriendGridCtrl : public CBCGPGridCtrl
{
	friend class MGridColumnsInfo;
};

//////////////////////////////////////////////////////////////////////////
MGridColumnsInfo::MGridColumnsInfo(void)
{
	// Multi Sort를 지원한다.
	m_bMultipleSort = TRUE;
}

MGridColumnsInfo::~MGridColumnsInfo(void)
{
	map<int, MFormatInfo*>::iterator itr;
	for( itr = m_smColumnFormat.begin(); itr!=m_smColumnFormat.end(); )
	{
		delete itr->second;
		itr = m_smColumnFormat.erase(itr);
	}

	m_smColumnFormat.clear();
}

MTable* MGridColumnsInfo::GetTable() const 
{ 
	ASSERT(m_pWndList->IsKindOf(RUNTIME_CLASS(MTable)));
	return static_cast<MTable*>(m_pWndList); 
}

bool MGridColumnsInfo::AddHeaderItem(CBCGPGridRange& MergeRange, int nColumn, LPCTSTR lpszLabel, int nAlign, int iImage)
{
	CArray<int, int> arrMergeColumns;
	for( int i=MergeRange.m_nLeft; i<=MergeRange.m_nRight; ++i )
	{
		arrMergeColumns.Add (i);
	}
	
	CArray<int, int> arrMergeLines;
	for( int i=MergeRange.m_nTop; i<=MergeRange.m_nBottom; ++i )
	{
		arrMergeLines.Add (i);	
	}
	
	if( !CBCGPGridColumnsInfoEx::AddHeaderItem (&arrMergeColumns, &arrMergeLines, nColumn, lpszLabel, nAlign, iImage) )
		return false;

	return true;
}

bool MGridColumnsInfo::GetMergedHeaderItem (int nColumn, int nLine, CBCGPGridRange& MergeRange, CString& strTitle) const
{
	CBCGPMergedHeaderItem* pItem = CBCGPGridColumnsInfoEx::GetMergedHeaderItem(nColumn, nLine);
	if( !pItem ) return false;

	int nTop = pItem->m_arrHeaderLines[0];
	int nBottom = pItem->m_arrHeaderLines[ (int)pItem->m_arrHeaderLines.GetSize()-1 ];
	int nLeft = pItem->m_arrColumns[0];
	int nRight = pItem->m_arrColumns[ (int)pItem->m_arrColumns.GetSize()-1 ];
	strTitle = pItem->m_strName;

	MergeRange.Set( nLeft, nTop, nRight, nBottom);

	return true;
}

bool MGridColumnsInfo::GetColumnFormat(int nCol, MFormatInfo& info)
{
	map<int, MFormatInfo*>::iterator itr = m_smColumnFormat.find(nCol);

	if( itr == m_smColumnFormat.end() )
	{
		return false;
	}

	info = *(itr->second);

	return true;
}

void MGridColumnsInfo::SetColumnFormat(int nCol, MFormatInfo& info)
{
	map<int, MFormatInfo*>::iterator itr = m_smColumnFormat.find(nCol);

	if( itr == m_smColumnFormat.end() )
	{
		MFormatInfo* pInfo = new MFormatInfo(info);
		m_smColumnFormat.insert( pair<int, MFormatInfo*>(nCol, pInfo) );
	}
	else
	{
		*(itr->second) = info;
	}
}

void MGridColumnsInfo::SetColumnFormat(int nStartCol, int nEndCol, MFormatInfo& info)
{
	for( int i=nStartCol; i<=nEndCol; ++i )
	{
		SetColumnFormat(i, info);
	}	
}