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
			CAtlMap<int, int> m_mapColumnIndex;	// Key: ColumnID, Data: m_aColumn 의 Index

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

			// ! 주의: 객체 하나 만들어 두고 호출할 때마다 같은 놈을 리턴한다.
			virtual LPVOID GetDefaultData()
			{
				// 편집가능한 Table 은 SetDefaultData() 호출해줘야 한다.
				ASSERT(m_pDefaultData && m_pTempData);
				*m_pTempData = *m_pDefaultData;
				return m_pTempData;
			}

			// ! 주의: 객체 하나 만들어 두고 호출할 때마다 같은 놈을 리턴한다.
			virtual LPVOID GetCopyData(LPCVOID pRow)
			{
				// 편집가능한 Table 은 SetDefaultData() 호출해줘야 한다.
				ASSERT(m_pTempData);
				*m_pTempData = *((TYPE*)pRow);
				return m_pTempData;
			}

			// ! 주의: 반드시 DeleteData 한다.
			virtual LPVOID CreateDefaultData()
			{
				// 편집가능한 Table 은 SetDefaultData() 호출해줘야 한다.
				ASSERT(m_pDefaultData);
				return new TYPE(*m_pDefaultData);
			}

			// ! 주의: 반드시 DeleteData 한다.
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
			
			// Table 에 구조체의 모든 멤버변수가 포함되지 않을 경우 그 멤버들의 값으로 쓰인다.
			// 편집 불가능한 Table 은 호출 안해도 된다.
			void SetDefaultData(const TYPE& defaultData)
			{
				// 초기화할때 한번만 Set 하면 된다.
				ASSERT(!m_pDefaultData && !m_pTempData);
				m_pDefaultData = new TYPE(defaultData);
				m_pTempData = new TYPE(defaultData);
			}
		};

		// BOOL, int 간의 Type 검사는 못 한다.
		// typedef int BOOL; 이기 때문
		template<typename TYPE>
		class MTBTypeChecker
		{
		public:
			static void TypeCheck(TYPE& item) { }
		};
	}
}

// offset값이 32bit 를 넘어갈 일은 없는 걸로...
#define MOffsetOf(s,m) static_cast<int>(offsetof(s,m))

#define MBeginAddTBColumn(schema) \
	{ MTBSchemaBase* _pSchema_ = &schema;
#define MEndAddTBColumn() \
	for (mit::frx::MTBColumn* pColumn : _pSchema_->GetColumns()) \
	{ pColumn->SetUnitCtrl(this->GetUnitCtrl()); pColumn->UpdateUnitConvertCurrent(); }\
	_pSchema_ = nullptr; }

// TypeCheck 부분은 릴리즈에서 컴파일시 최적화되서 사라진다. (타입 잘못 썼을때 컴파일에러 뱉는것은 동일)
#define MTBTypeCheck(datatype, vartype, varname) \
	{ datatype _data_; mit::frx::MTBTypeChecker<vartype>::TypeCheck(_data_.##varname); }

// Unit 빠트리는 실수 방지위해 Unit 없어도 무조건 0로 넣어줘야 한다. 이건 컴파일에러로도 ASSERT 로도 잡을수 없기 때문.
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