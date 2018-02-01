#pragma once

#include "../MIT_lib/MTypeDef.h"
#include "MTBColumn.h"

#include <vector>

#include "HeaderPre.h"

using namespace mit;

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTBSchemaBase
		{
		public:
			MTBSchemaBase() {}
			virtual ~MTBSchemaBase() 
			{
				for (const MTBColumn* pColumn : m_aColumn) 
				{
					ASSERT(pColumn); 
					delete pColumn; 
				} 
			}

		private:
			std::vector<MTBColumn*> m_aColumn;
			CAtlMap<int, int> m_mapColumnIndex;	// Key: ColumnID, Data: m_aColumn �� Index

		public:
			const std::vector<MTBColumn*>& GetColumns() const
			{
				return m_aColumn;
			}

			void AddColumn(const MTBColumn& column)
			{
				m_mapColumnIndex.SetAt(column.GetID(), (int)m_aColumn.size());
				m_aColumn.push_back(new MTBColumn(column));
			}

			int GetColumnCount() const
			{
				return (int)m_aColumn.size();
			}
			
			const MTBColumn& GetColumn(int nCol) const
			{
				return *m_aColumn[nCol];
			}

			MTBColumn& GetColumn(int nCol)
			{
				return *m_aColumn[nCol];
			}

			const MTBColumn& GetColumnByID(int nID) const
			{
				return *m_aColumn[m_mapColumnIndex.Lookup(nID)->m_value];
			}

			MTBColumn& GetColumnByID(int nID)
			{
				return *m_aColumn[m_mapColumnIndex.Lookup(nID)->m_value];
			}

			virtual int GetDataSize() const = 0;
			virtual LPVOID GetDefaultData() = 0;
			virtual LPVOID GetCopyData(LPCVOID pRow) = 0;
			virtual LPVOID CreateDefaultData() = 0;
			virtual LPVOID CreateCopyData(LPCVOID pRow) = 0;
			virtual void DeleteData(LPCVOID pRow) = 0;
		};

		template<typename TYPE>
		class MTBSchema : public MTBSchemaBase
		{
		public:
			MTBSchema() : m_pDefaultData(nullptr), m_pTempData(nullptr) {}
			virtual ~MTBSchema() 
			{
				if (m_pDefaultData) delete m_pDefaultData;
				if (m_pTempData) delete m_pTempData;
			}

		private:
			TYPE* m_pDefaultData;
			TYPE* m_pTempData;

		public:
			virtual int GetDataSize() const
			{
				return sizeof(TYPE);
			}

			// ! ����: ��ü �ϳ� ����� �ΰ� ȣ���� ������ ���� ���� �����Ѵ�.
			virtual LPVOID GetDefaultData()
			{
				// ���������� Table �� SetDefaultData() ȣ������� �Ѵ�.
				ASSERT(m_pDefaultData && m_pTempData);
				*m_pTempData = *m_pDefaultData;
				return m_pTempData;
			}

			// ! ����: ��ü �ϳ� ����� �ΰ� ȣ���� ������ ���� ���� �����Ѵ�.
			virtual LPVOID GetCopyData(LPCVOID pRow)
			{
				// ���������� Table �� SetDefaultData() ȣ������� �Ѵ�.
				ASSERT(m_pTempData);
				*m_pTempData = *((TYPE*)pRow);
				return m_pTempData;
			}

			// ! ����: �ݵ�� DeleteData �Ѵ�.
			virtual LPVOID CreateDefaultData()
			{
				// ���������� Table �� SetDefaultData() ȣ������� �Ѵ�.
				ASSERT(m_pDefaultData);
				return new TYPE(*m_pDefaultData);
			}

			// ! ����: �ݵ�� DeleteData �Ѵ�.
			virtual LPVOID CreateCopyData(LPCVOID pRow)
			{
				ASSERT(pRow);
				return new TYPE(*((TYPE*)pRow));
			}

			virtual void DeleteData(LPCVOID pRow)
			{
				ASSERT(pRow);
				delete (TYPE*)pRow;
			}
			
			// Table �� ����ü�� ��� ��������� ���Ե��� ���� ��� �� ������� ������ ���δ�.
			// ���� �Ұ����� Table �� ȣ�� ���ص� �ȴ�.
			void SetDefaultData(const TYPE& defaultData)
			{
				// �ʱ�ȭ�Ҷ� �ѹ��� Set �ϸ� �ȴ�.
				ASSERT(!m_pDefaultData && !m_pTempData);
				m_pDefaultData = new TYPE(defaultData);
				m_pTempData = new TYPE(defaultData);
			}
		};

		// BOOL, int ���� Type �˻�� �� �Ѵ�.
		// typedef int BOOL; �̱� ����
		template<typename TYPE>
		class MTBTypeChecker
		{
		public:
			static void TypeCheck(TYPE& item) { }
		};
	}
}

// offset���� 32bit �� �Ѿ ���� ���� �ɷ�...
#define MOffsetOf(s,m) static_cast<int>(offsetof(s,m))

#define MBeginAddTBColumn(schema) \
	{ MTBSchemaBase* _pSchema_ = &schema;
#define MEndAddTBColumn() \
	for (mit::frx::MTBColumn* pColumn : _pSchema_->GetColumns()) \
	{ pColumn->SetUnitCtrl(this->GetUnitCtrl()); pColumn->UpdateUnitConvertCurrent(); }\
	_pSchema_ = nullptr; }

// TypeCheck �κ��� ������� �����Ͻ� ����ȭ�Ǽ� �������. (Ÿ�� �߸� ������ �����Ͽ��� ��°��� ����)
#define MTBTypeCheck(datatype, vartype, varname) \
	{ datatype _data_; mit::frx::MTBTypeChecker<vartype>::TypeCheck(_data_.##varname); }

// Unit ��Ʈ���� �Ǽ� �������� Unit ��� ������ 0�� �־���� �Ѵ�. �̰� �����Ͽ����ε� ASSERT �ε� ������ ���� ����.
#define MAddTBColumn(nID, strName, strMsgID, datatype, vartype, varname, nUnit) \
	MTBTypeCheck(datatype, vartype, varname) \
	_pSchema_->AddColumn( mit::frx::MTBColumn(nID, strName, strMsgID, mit::frx::MTBColumn::TB_##vartype, MOffsetOf(datatype, varname), nUnit, mit::frx::MTBColumn::TB_NONE, -1) );

#define MAddTBKEYColumn(nID, strName, strMsgID) \
	_pSchema_->AddColumn( mit::frx::MTBColumn(nID, strName, strMsgID, mit::frx::MTBColumn::TB_KEY, -1, 0, mit::frx::MTBColumn::TB_NONE, -1) );
//
//#define MAddTBFOREIGNColumn(nID, strName, strMsgID) \
//	_pSchema_->AddColumn( mit::frx::MTBColumn(nID, strName, strMsgID, mit::frx::MTBColumn::TB_KEY, -1, 0, mit::frx::MTBColumn::TB_NONE, -1) );

#define MAddTBCArrayColumn(nID, strName, strMsgID, datatype, itemtype, varname, nIndex, nUnit) \
	MTBTypeCheck(datatype, CArray<itemtype>, varname) \
	_pSchema_->AddColumn( mit::frx::MTBColumn(nID, strName, strMsgID, mit::frx::MTBColumn::TB_CArray, MOffsetOf(datatype, varname), nUnit, mit::frx::MTBColumn::TB_##itemtype, nIndex) );

#include "HeaderPost.h"