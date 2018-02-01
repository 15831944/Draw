#pragma once

#include "MTBSchema.h"
#include "ITBSort.h"
#include "ITBClipboard.h"
#include "ITBProgressCtrl.h"
#include "ITBMessageCtrl.h"

#include <vector>
#include "atlcoll.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class ITable;
		class __MY_EXT_CLASS__ ITableDB
		{
		public:
			virtual ITable* GetTable() const = 0;
			virtual MTBSchemaBase* GetSchema() const = 0;
			virtual MUnitCtrl* GetUnitCtrl() const = 0;
			virtual ITBSort* GetSort() const = 0;
			virtual ITBClipboard* GetClipboard() const = 0;

			// Initialize ( SetDocument - Initialize 순으로 호출 )
			virtual void SetDocument(CDocument* pDoc) = 0;
			virtual void Initialize() = 0;
			virtual void Finalize() = 0;

			// Get
			virtual BOOL GetItem(_variant_t& varValue, int nRow, int nCol) const = 0;
			virtual BOOL GetForeignItem(_variant_t& varValue, int nRow, int nCol) const = 0;
			virtual BOOL GetRow(std::vector<_variant_t*>& aItems, int nRow) const = 0;	
			virtual MKey GetKey(int nRow) const = 0;
			virtual LPCVOID GetRow(int nRow) const = 0;

			// Row
			virtual void InitRows() = 0;
			virtual void DestroyRows() = 0;
			virtual void FillRowAll() = 0;
			virtual int GetRowCount() const = 0;

			// Edit
			virtual BOOL DeleteRows(const std::vector<std::pair<int, int>>& aRowRanges) = 0;
			virtual BOOL ModifyItem(int nRow, int nCol, _variant_t& item) = 0;
			virtual BOOL ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems) = 0;
			virtual BOOL GetNewRowItems(std::vector<_variant_t*>& aNewRowItems) = 0;
			virtual BOOL AppendRow(std::vector<_variant_t*>& aNewRowItems) = 0;
		};

		class __MY_EXT_CLASS__ ITable
		{
		public:
			virtual ITableDB* GetTableDB() const = 0;
			virtual ITBProgressCtrl* GetProgressCtrl() const = 0; 
			virtual ITBMessageCtrl* GetMessageCtrl() const = 0;

			// Update
			virtual void UpdateRowCount() = 0;
			virtual void UpdateData() = 0;
			virtual void UpdateSortColumns() = 0;
			// TODO: 임시. (아직 Update 관련 미흡한 부분 있음)
			virtual void UpdateAppendRow() = 0;
			virtual void UpdateUnit() = 0;
		};
	}
}

#include "HeaderPost.h"
