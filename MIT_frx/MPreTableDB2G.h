#pragma once

#include "MTableDB.h"
#include "MPreTBSort2G.h"
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
		//// TODO: Key와 Iterator 타입을 어떻게 할까 고민
		////       DB 상관없이 쓰게 하고 싶다.
		////       현재는 Key-Data 기반으로 해뒀음.
		////     1. Template 으로 Key Type 받는다.
		////        2세대용DB용 3세대DB용 자식 클래스 만든다.
		////        2세대 DB 용은 <UINT> 3세대 DB용은 <long> 범용은 <int> (배열의 index로 쓰라고..)
		////        m_data는 제거하고 2세대 DB용 Class 로 내린다.
		////        m_iterators 는 제거하고 3세대 DB용 Class 로 내린다.(혹은 m_keys 까지 없애고 Iterator 로 모두 해결??)
		////     2. 어차피 4byte인데 뭐... 20억개는 안 넘을거 아냐
		////        그냥 long 쓴다.
		////     3. 더 좋은 방법?
		////     * Key List 는 무조건 받자. Default 가 키정렬인 테이블이 많을 거임


		// !!!! 일단 무조건 Key - Data로 간다.
		//      Key는 MKey 쓴다.

		// 크기타입은 size_t 로 해뒀지만 BCGgrid에서 row 인덱스로 int 를 사용함.
		// Atl : List, Map 사용
		// Stl : vector 사용
		class __MY_EXT_CLASS__ MPreTableDB2G : public MTableDB
		{
			friend class MPreTBSort2G;
			friend class MTBPreClipboard2G;

		public:
			// TODO: class 로 빼고 Getter 에서 Lazy Evaluation 처리???
			struct ITEM
			{
				MKey key;
				LPCVOID data;

				ITEM(MKey k, LPCVOID d) : key(k), data(d) {}
				ITEM(MKey k) : key(k), data(NULL) {}
			};

		public:
			MPreTableDB2G(ITable* pTable, MTBSchemaBase* pSchema);
			virtual ~MPreTableDB2G();

			// Sort
		protected:
			MPreTBSort2G m_sort;
			MTBPreClipboard2G m_clipboard;

			// Container
		protected:
			CAtlList<ITEM*> m_rows;
			CAtlMap<MKey, POSITION> m_map;
			mutable MTBIndex m_index;

			// MTableDB Impl - Get
		protected:
			ITEM* GetItem(int nRow, BOOL bMakeCacheIndex = TRUE) const;
			ITEM* GetAtItem(POSITION pos) const;
			ITEM* GetNextItem(POSITION& pos) const;
		public:
			virtual BOOL GetForeignItem(_variant_t& varValue, int nRow, int nCol) const;
			virtual MKey GetKey(int nRow) const;
			virtual LPCVOID GetRow(int nRow) const;
		protected:
			virtual int GetKeyLange(std::vector<MKey>& aKeys, int nStartRow, int nEndRow) const;
			virtual int GetRowLange(std::vector<LPCVOID>& aRows, int nStartRow, int nEndRow) const;

			// MTableDB Impl - Row
		public:
			virtual void InitRows();
			virtual void DestroyRows();
			virtual void FillRowAll();
			virtual int GetRowCount() const;

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

			// DB 에서 Data 변경 시 호출되어야 하는 함수들
			// * Deleted 와 Modified 는 현재 테이블에 없는 Key 는 알아서 필터링이 되지만
			//   Added 는 반드시 미리 필터링해서 추가될 Key 만 넘겨야 한다
		protected:
			void OnAddedFromDB(MKey key) { OnAddedFromDB(std::vector<MKey>(1, key)); }
			void OnAddedFromDB(const std::vector<MKey>& keys);
			void OnDeletedFromDB(MKey key) { OnDeletedFromDB(std::vector<MKey>(1, key)); }
			void OnDeletedFromDB(const std::vector<MKey>& keys);
			void OnModifiedFromDB(MKey key, MKey newkey) { OnModifiedFromDB(std::vector<MKey>(1, key), std::vector<MKey>(1, newkey)); }
			void OnModifiedFromDB(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys);
			
			// Sorting 관련 
		protected:
			// TODO: RealtimeSort, m_isSorted 미구현
			enum SORT_OPTION { NOT_SORT, SORT_ASCENDING, SORT_DESCENDING };		
			BOOL m_isSorted;
		protected:
			BOOL IsRealtimeSortFromDB() const { return FALSE; }
		public:
			SORT_OPTION GetKeySortOption() const;

		private:
			size_t GetKeyList(std::vector<MKey>& keys, SORT_OPTION so) const;

			// Get Data
		protected:
			// so == NOT_SORT : keys 가 정렬되어 있을 필요없음. bSorted 값 상관없음,
			// so == SORT_ASCEDING or SORT_DESCENDING : 
			//   key 를 정렬된 상태로 가지고 있었다면 오름차순 or 내림차순으로 key 를 채워주고 bSorted = TRUE 해줄것
			//   key 를 정렬되지 않은 상태로 가지고 있었다면 그냥 채우고 bSorted = FALSE 로 둘것
			virtual MKey GetNewKey() const = 0;
			virtual size_t GetKeyList(std::vector<MKey>& keys, SORT_OPTION so, BOOL& bSorted) const = 0;
			virtual BOOL GetData(MKey key, LPCVOID& pData) const = 0;
			virtual BOOL GetForeignData(_variant_t& data, MKey key, int nCol) const { ASSERT(0); return FALSE; }

			// Set Data
		protected:
			virtual BOOL AddData(const std::vector<MKey>& keys, const std::vector<LPCVOID>& aData) = 0;
			virtual BOOL AddData(const std::vector<LPCVOID>& aData) = 0;
			virtual BOOL DeleteData(const std::vector<MKey>& keys) = 0;
			virtual BOOL ModifyData(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys, const std::vector<LPCVOID>& aData) = 0;
		};

		inline MPreTableDB2G::ITEM* MPreTableDB2G::GetItem(int nRow, BOOL bMakeCacheIndex) const
		{
			ASSERT(m_rows.GetCount() <= INT_MAX);
			ASSERT(nRow >= 0 && nRow < (int)m_rows.GetCount());
			return GetAtItem(m_index.RowToPosition(nRow, bMakeCacheIndex));
		}

		inline MPreTableDB2G::ITEM* MPreTableDB2G::GetAtItem(POSITION pos) const
		{
			ASSERT(pos);
			ITEM* pItem = m_rows.GetAt(pos);
			LPCVOID& pRow = pItem->data;
			if (!pRow)
			{
				if (!GetData(pItem->key, pRow)) { ASSERT(0); return NULL; }
				ASSERT(pRow);
			}
			return pItem;
		}

		inline MPreTableDB2G::ITEM* MPreTableDB2G::GetNextItem(POSITION& pos) const
		{
			ASSERT(pos);
			ITEM* pItem = m_rows.GetNext(pos);
			LPCVOID& pRow = pItem->data;
			if (!pRow)
			{
				if (!GetData(pItem->key, pRow)) { ASSERT(0); return NULL; }
				ASSERT(pRow);
			}
			return pItem;
		}
	}
}

#include "HeaderPost.h"
