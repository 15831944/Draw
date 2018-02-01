#pragma once

#include "MTableDB.h"
#include "MPostTBSort.h"
#include "MTBPostClipboard.h"
#include "MTBChangedFromTable.h"

#include <vector>

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MPostTableDB : public MTableDB
		{
			friend class MPostTBSort;
			friend class MTBPostClipboard;

		public:
			MPostTableDB(ITable* pTable, MTBSchemaBase* pSchema);
			virtual ~MPostTableDB();

			// Sort
		protected:
			MPostTBSort m_sort;
			MTBPostClipboard m_clipboard;

			// Container
		protected:
			mutable std::vector<LPCVOID> m_records;

			// MTableDB Impl - Get
		public:
			virtual LPCVOID GetRow(int nRow) const;

			// MTableDB Impl - Row
		public:
			virtual void InitRows();
			virtual void DestroyRows();
			virtual void FillRowAll();
			virtual int GetRowCount() const;

			// MTableDB Impl - Edit (Modify ¸¸ Çã¿ë)
		protected:
			TModifiedItem m_modifiedItem;
			TModifiedRow m_modifiedRow;
		public:
			virtual BOOL ModifyItem(int nRow, int nCol, _variant_t& item);
			virtual BOOL ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems);

			// Get Data
		protected:
			virtual size_t GetDataCount() const = 0;
			virtual BOOL GetData(int nRow, LPCVOID& pData) const = 0;

			// Set Data
		protected:
			virtual BOOL ModifyData(int nRow, int nCol, LPCVOID pData) { ASSERT(0); return FALSE; }
			virtual BOOL ModifyData(const std::vector<int>& aRow, const std::vector<LPCVOID>& aData) { ASSERT(0); return FALSE; }
		};
	}
}

#include "HeaderPost.h"
