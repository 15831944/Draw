#pragma once

#include "ITable.h"
#include "../MIT_lib/IUnitListener.h"
#include "MTBClipBoard.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// MTableDB 하위클래스는 크게 
		// 1. 자료구조와
		// 2. Data 지정 방법 (Index, Key, Iterator)
		// 에 의해 나눠진다.
		class __MY_EXT_CLASS__ MTableDB : public ITableDB, public mit::lib::IUnitListener
		{
		public:
			MTableDB(ITable* pTable, MTBSchemaBase* pSchema, ITBSort* pSort, ITBClipboard* pClipboard);
			virtual ~MTableDB();

			// ITable Impl
		protected:
			ITable* m_pTable;
			MTBSchemaBase* m_pSchema;
			MUnitCtrl* m_pUnitCtrl;
			ITBSort* m_pSort;
			ITBClipboard* m_pClipboard;
		public:
			virtual ITable* GetTable() const { ASSERT(m_pTable); return m_pTable; }
			virtual MTBSchemaBase* GetSchema() const { ASSERT(m_pSchema); return m_pSchema; }
			virtual MUnitCtrl* GetUnitCtrl() const { ASSERT(m_pUnitCtrl); return m_pUnitCtrl; }
			virtual ITBSort* GetSort() const { ASSERT(m_pSort); return m_pSort; }
			virtual ITBClipboard* GetClipboard() const { ASSERT(m_pClipboard); return m_pClipboard; }

			// ITable Impl - Initialize
		protected:
			CDocument* m_pDoc;
		public:
			virtual void SetDocument(CDocument* pDoc) { m_pDoc = pDoc; }
			virtual void Initialize() {}
			virtual void Finalize() {}
					
			// ITable Impl - Get
		public:
			virtual BOOL GetItem(_variant_t& varValue, int nRow, int nCol) const;
			virtual BOOL GetForeignItem(_variant_t& varValue, int nRow, int nCol) const { ASSERT(0); return 0; } // 필요한 경우 Override
			virtual BOOL GetRow(std::vector<_variant_t*>& aItems, int nRow) const;			
			virtual MKey GetKey(int nRow) const { ASSERT(0); return 0; }  // * Key 따로 관리해야 하는 (Data 에 Key 가 포함되어 있지 않은) Table 만 Override 
			virtual LPCVOID GetRow(int nRow) const = 0;

			// ITable - Row
		public:
			virtual void InitRows() = 0;
			virtual void DestroyRows() = 0;
			virtual void FillRowAll() = 0;
			virtual int GetRowCount() const = 0;

			// ITable - Edit * 수정 가능한 Table 만 Override
		public:
			virtual BOOL DeleteRows(const std::vector<std::pair<int, int>>& aRowRanges) { ASSERT(0); return FALSE; }
			virtual BOOL ModifyItem(int nRow, int nCol, _variant_t& item) { ASSERT(0); return FALSE; }
			virtual BOOL ModifyRow(int nRow, std::vector<_variant_t*>& aModifiedRowItems) { ASSERT(0); return FALSE; }
			virtual BOOL GetNewRowItems(std::vector<_variant_t*>& aNewRowItems) { ASSERT(0); return FALSE; }
			virtual BOOL AppendRow(std::vector<_variant_t*>& aNewRowItems) { ASSERT(0); return FALSE; }

			// IUnitListener - Impl
		public:
			virtual const CDocument* GetUnitListenerDoc();
			virtual void OnUnitChanged();
		};
	}
}

#include "HeaderPost.h"
