#pragma once

#include "ITBSort.h"
#include "ITable.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTBSchemaBase;
		class __MY_EXT_CLASS__ MTBSort : public ITBSort
		{
		public:
			MTBSort(ITableDB* pTableDB);
			virtual ~MTBSort();

			// TableDB
		private:
			ITableDB* m_pTableDB;
			MTBSchemaBase* m_pSchema;
		protected:
			ITableDB* GetTableDB() const { ASSERT(m_pTableDB); return m_pTableDB; }
			ITable* GetTable() const { ASSERT(m_pTableDB); return m_pTableDB->GetTable(); }
			MTBSchemaBase* GetSchema() const { ASSERT(m_pSchema); return m_pSchema; }
			
			// Sort Column
		protected:
			CAtlList<TBSortColumn> m_lstSortCol; // Map & List 로 성능향상 가능하나 의미없음

			// Option
		protected:
			BOOL m_bCanCancel; // TODO: 객체마다 가지고 있을 필요없음

			// Temp Variable (Sorting 하는 동안만 사용됨)
		protected:
			static MTBSort* s_sort;
			int m_nGroupCount; // 미구현
			int m_nProgressPos;
			POSITION m_posProgressHelper;
			DWORD m_mainThreadID;
			
			// ITBSort Impl - Sort Column
		public:
			virtual void SetSortColumns(const CAtlList<TBSortColumn>& lstSortCol);
			virtual void AddSortColumn(const TBSortColumn& sortcol);
			virtual BOOL RemoveSortColumn(int nColumn);
			virtual void RemoveAllSortColumns();
			virtual int GetSortColumns(CAtlList<TBSortColumn>& lstSortCol) const;
			virtual BOOL GetSortColumn(int nColumn, TBSortColumn& sortcol) const;
		protected:
			POSITION FindSortColumn(int nColumn) const;
			void PrivateSetSortColumns(const CAtlList<TBSortColumn>& lstSortCol);
			void PrivateAddSortColumn(const TBSortColumn& sortcol);
			BOOL PrivateRemoveSortColumn(int nColumn);
			void PrivateRemoveAllSortColumns();

			// Sort
		public:
			virtual BOOL Sort();
		protected:
			virtual BOOL PrivateSort() = 0;
			BOOL Sort(std::vector<LPCVOID>& data, BOOL bRestoreCancel = TRUE);
			void StlSort(std::vector<LPCVOID>& data);
			void QSort(std::vector<LPCVOID>& data);
			void ParallelSort(std::vector<LPCVOID>& data);
			void ParallelBufferedSort(std::vector<LPCVOID>& data);

			// Compare
		protected:
			static int GetApproximateCompareCount(int n) { return (int)(n * (std::log(n)/std::log(2.0))); }
			static bool StlCompareStatic(LPCVOID pRow1, LPCVOID pRow2);
			static int QCompareStatic(LPCVOID pRow1, LPCVOID pRow2);
			static bool ParallelCompareStatic(LPCVOID pRow1, LPCVOID pRow2);
			int Compare(LPCVOID pRow1, LPCVOID pRow2);
			int ParallelCompare(LPCVOID pRow1, LPCVOID pRow2);
			virtual int CompareGroup(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol);
			virtual int CompareItem(LPCVOID pRow1, LPCVOID pRow2, const TBSortColumn& sortcol);
			
		protected:
			static int CopyList(CAtlList<TBSortColumn>& dst, const CAtlList<TBSortColumn>& src);
		};
	}
}

#include "HeaderPost.h"