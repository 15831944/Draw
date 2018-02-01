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
		//// TODO: Key�� Iterator Ÿ���� ��� �ұ� ���
		////       DB ������� ���� �ϰ� �ʹ�.
		////       ����� Key-Data ������� �ص���.
		////     1. Template ���� Key Type �޴´�.
		////        2�����DB�� 3����DB�� �ڽ� Ŭ���� �����.
		////        2���� DB ���� <UINT> 3���� DB���� <long> ������ <int> (�迭�� index�� �����..)
		////        m_data�� �����ϰ� 2���� DB�� Class �� ������.
		////        m_iterators �� �����ϰ� 3���� DB�� Class �� ������.(Ȥ�� m_keys ���� ���ְ� Iterator �� ��� �ذ�??)
		////     2. ������ 4byte�ε� ��... 20�ﰳ�� �� ������ �Ƴ�
		////        �׳� long ����.
		////     3. �� ���� ���?
		////     * Key List �� ������ ����. Default �� Ű������ ���̺��� ���� ����


		// !!!! �ϴ� ������ Key - Data�� ����.
		//      Key�� MKey ����.

		// ũ��Ÿ���� size_t �� �ص����� BCGgrid���� row �ε����� int �� �����.
		// Atl : List, Map ���
		// Stl : vector ���
		class __MY_EXT_CLASS__ MPreTableDB2G : public MTableDB
		{
			friend class MPreTBSort2G;
			friend class MTBPreClipboard2G;

		public:
			// TODO: class �� ���� Getter ���� Lazy Evaluation ó��???
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

			// DB ���� Data ���� �� ȣ��Ǿ�� �ϴ� �Լ���
			// * Deleted �� Modified �� ���� ���̺� ���� Key �� �˾Ƽ� ���͸��� ������
			//   Added �� �ݵ�� �̸� ���͸��ؼ� �߰��� Key �� �Ѱܾ� �Ѵ�
		protected:
			void OnAddedFromDB(MKey key) { OnAddedFromDB(std::vector<MKey>(1, key)); }
			void OnAddedFromDB(const std::vector<MKey>& keys);
			void OnDeletedFromDB(MKey key) { OnDeletedFromDB(std::vector<MKey>(1, key)); }
			void OnDeletedFromDB(const std::vector<MKey>& keys);
			void OnModifiedFromDB(MKey key, MKey newkey) { OnModifiedFromDB(std::vector<MKey>(1, key), std::vector<MKey>(1, newkey)); }
			void OnModifiedFromDB(const std::vector<MKey>& keys, const std::vector<MKey>& newkeys);
			
			// Sorting ���� 
		protected:
			// TODO: RealtimeSort, m_isSorted �̱���
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
			// so == NOT_SORT : keys �� ���ĵǾ� ���� �ʿ����. bSorted �� �������,
			// so == SORT_ASCEDING or SORT_DESCENDING : 
			//   key �� ���ĵ� ���·� ������ �־��ٸ� �������� or ������������ key �� ä���ְ� bSorted = TRUE ���ٰ�
			//   key �� ���ĵ��� ���� ���·� ������ �־��ٸ� �׳� ä��� bSorted = FALSE �� �Ѱ�
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
