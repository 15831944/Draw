#pragma once

#include "MPostTableDB.h"
#include "MTable.h"
#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		struct __MY_EXT_CLASS__ MTBStyleTableData
		{
			CString strName;
			int nType;
			int nWidth;
			int nAlign;
			int nFormat;
			int nPrecision;
			MTBStyleTableData() : strName(_T("")), nType(0), nWidth(0), nAlign(0), nFormat(-1), nPrecision(0) { }
		};

		class __MY_EXT_CLASS__ MTBStyleTableDB : public MPostTableDB
		{

		public:
			MTBStyleTableDB(ITable* pTable, ITableDB* pObjTableDB);
			virtual ~MTBStyleTableDB();

			// ObjTable
		private:
			ITableDB* const m_pObjTableDB;
			MTable* const m_pObjTable;
		public:
			ITableDB* GetObjTableDB() const { return m_pObjTableDB; }
			MTBSchemaBase* GetObjSchema() const { return GetObjTableDB()->GetSchema(); }
			MTable* GetObjTable() const { return m_pObjTable; }

			// Schema
		public:
			enum ColumnID { CID_Name, CID_Type, CID_Width, CID_Align, CID_Format, CID_Precision };
		private:
			mit::frx::MTBSchema<MTBStyleTableData> m_schema;
		private:
			void MakeSchema();
			
			// Data
		private:
			std::vector<MTBStyleTableData> m_data;
		private:
			void MakeData();

			// Get Data
		protected:
			virtual size_t GetDataCount() const;
			virtual BOOL GetData(int nRow, LPCVOID& pData) const;

			// Set Data
		protected:
			virtual BOOL ModifyData(int nRow, int nCol, LPCVOID pData);
			virtual BOOL ModifyData(const std::vector<int>& aRow, const std::vector<LPCVOID>& aData);
		};

		class __MY_EXT_CLASS__ MTBStyleTable : public mit::frx::MTable
		{
			DECLARE_DYNAMIC(MTBStyleTable)

		public:
			MTBStyleTable(MTable* pObjTable);
			virtual ~MTBStyleTable();

			// ObjTable
		private:
			MTable* const m_pObjTable;
		public:
			MTable* GetObjTable() const { return m_pObjTable; }

			// TableDB
		private:
			mutable MTBStyleTableDB m_tableDB;
		public:
			virtual ITableDB* GetTableDB() const { return &m_tableDB; }

		protected:
			virtual BOOL InitializeTable();
			virtual void OnPreDrawRow(mit::frx::MGridRow* pRow);
		protected:
			virtual void MakeContextMenu(CMenu& menu);

			// Event Handler
		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		};
	}
}

#include "HeaderPost.h"
