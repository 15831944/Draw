#pragma once

#include "MTableDB.h"
#include "MPreTBSort3G.h"
#include "MTBPreClipboard2G.h"
#include "MTBChangedFromTable.h"
#include "MTBIndexCache.h"

#include <vector>
#include "atlcoll.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MPreTableDB3G : public MTableDB
		{
			friend class MPreTBSort3G;

		public:
			MPreTableDB3G(ITable* pTable, MTBSchemaBase* pSchema);
			virtual ~MPreTableDB3G();

			// Sort
		protected:
			MPreTBSort3G m_sort;
			MTBPreClipboard2G m_clipboard;

			// Container
		protected:
			CAtlList<MIterator> m_rows;
			CAtlMap<MIterator, POSITION> m_map;
			MTBIndex m_index;

			// MTableDB Impl - Row
		public:
			virtual void InitRows();
			virtual void DestroyRows();
			virtual void FillRowAll();
			virtual int GetRowCount() const;

			// ITableDB Impl - Get
		public:
			virtual LPCVOID GetRow(int nRow) const;

			// MTableDB Impl - Edit
		protected:
			TModifiedItem m_modifiedItem;
			TModifiedRow m_modifiedRow;
			TAppendedRow m_appendedRow;
		protected:
			BOOL IsModifiedFromTable() const { return m_modifiedItem.HasModifiedItem() || m_modifiedRow.HasModifiedRow(); }
			BOOL IsAppendedFromTable() const { return m_appendedRow.HasAppendedRow(); }
		public:
			virtual BOOL DeleteRows(const std::vector<std::pair<int, int>>& aRowRanges);
			virtual BOOL ModifyItem(int nRow, int nCol, _variant_t& item);
			virtual BOOL ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems);
			virtual BOOL GetNewRowItems(std::vector<_variant_t*>& aNewRowItems);
			virtual BOOL AppendRow(std::vector<_variant_t*>& aNewRowItems);

			// Sorting
		protected:
			// TODO: RealtimeSort, m_isSorted 미구현
			enum SORT_OPTION { NOT_SORT, SORT_ASCENDING, SORT_DESCENDING };		
			BOOL m_isSorted;
		protected:
			BOOL IsRealtimeSortFromDB() const { return FALSE; }
		public:
			SORT_OPTION GetKeySortOption() const;

		//	// DB 에서 Data 변경 시 호출되어야 하는 함수들
		//	// * Deleted 와 Modified 는 현재 테이블에 없는 Key 는 알아서 필터링이 되지만
		//	//   Added 는 반드시 미리 필터링해서 추가될 Key 만 넘겨야 한다
		//protected:
		//	void OnAddedFromDB(MKey key);
		//	void OnAddedFromDB(const std::vector<MKey>& keys);
		//	void OnDeletedFromDB(MKey key);
		//	void OnDeletedFromDB(const std::vector<MKey>& keys);
		//	void OnModifiedFromDB(MKey key, MKey newkey);
		//	void OnModifiedFromDB(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys);

			// Get Data
		protected:
			virtual MKey GetNewKey() const = 0;
			virtual size_t GetIteratorList(std::vector<MIterator>& keys) const = 0;
			virtual BOOL GetData(MKey key, LPCVOID& pData) const = 0;

			// Set Data
		protected:
			virtual BOOL AddData(MIterator iter)=0;
			virtual BOOL DeleteData(const std::vector<MIterator>& iters)=0;
			virtual BOOL ModifyData(MIterator iter, MIterator newiter)=0;
		};
	}
}

#include "HeaderPost.h"
