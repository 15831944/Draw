#pragma once

#include "../MIT_lib/MTypeDef.h"
#include "../MIT_lib/MUnitCtrl.h"
#include "MTBConvertor.h"
#include "MTBDataMap.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// 상속금지용 부모클래스
		class __MY_EXT_CLASS__ MTBNonInheritance
		{
		protected:
			MTBNonInheritance() {}
			MTBNonInheritance(const MTBNonInheritance& src) {}
		};

		// 상속금지
		class __MY_EXT_CLASS__ MTBColumn : private virtual MTBNonInheritance
		{
			friend class MTBSchemaBase; // 복사는 MTBSchemaBase 내에서만 허용

		public:
			// TB_ 뒤에 실제 Type 이름과 동일하게 맞춤. 대소문자까지 구분해야 한다.
			//   TB_NONE, TB_KEY, TB_FOREIGN 는 제외
			enum Type
			{
				TB_NONE,	// itemType 필요없을때 사용. 직접 쓸일은 없음.
				TB_KEY,		// TableDB에서 키리스트 따로 관리할 경우. 키리스트에 있는 값을 사용. offset 안씀. 
				TB_FOREIGN,	// TODO: 미구현. Data 가 구조체에 있지 않을때 (다른 구조체에 있거나, 어쨋든 Data 주소와 offset 으로 접근할 수 없을 때)
				TB_MKey,
				TB_BOOL,
				TB_bool,
				TB_int,
				TB_UINT,
				TB_float,
				TB_double,
				TB_CString,
				TB_CArray
				// TODO : Struct 추가하기 (그냥 멤버로 가지고 있으면 필요없을 수도 있으나, CArray 안에 구조체 있을 경우 곤란해짐)
				//TB_Struct,
				// 항목 추가시 요거 쓰는 코드 다 찾아서 추가해주기		
			};

		public:
			MTBColumn(int nID, const CString& strName, const CString& strMsgID, Type type, int nOffset, int nUnit, Type itemType, int nIndex) :
				m_nID(nID), m_strName(strName), m_strMsgID(strMsgID), m_type(type), m_nOffset(nOffset), m_nUnit(nUnit), m_itemType(itemType), m_nIndex(nIndex),
				m_displayType(TB_NONE), m_pDataMap(nullptr), // m_displayType, Map 은 항상 같이 쓰이며 초기화는 항상 None, NULL 으로 해둔다.
				m_pUnitCtrl(nullptr), m_dUnitConvertCurrent(0.0)
			{
				// 실수 방지 위해 ASSERT 최대한 많이 걸어둔다.

				// Type 은 None 이 될 수 없다.
				ASSERT(m_type != TB_NONE);
				// KEY는 ItemType 으로 못 쓴다. Foreign 의 Foreign 같은거 없다. 중첩된 CArray 지원안한다.
				ASSERT(m_itemType != TB_KEY && m_itemType != TB_FOREIGN && m_itemType != TB_CArray);
				// Foreign 이나 CArray 일 경우만 실제 ItemType 이 필요하다.
				ASSERT(m_type == TB_FOREIGN || m_type == TB_CArray ? m_itemType != TB_NONE : m_itemType == TB_NONE);
				// Key, Foreign 가 아니면 Offset 이 꼭 있어야 한다.
				ASSERT(m_type != TB_KEY && m_itemType != TB_FOREIGN ? m_nOffset >= 0 : TRUE);
				// Key 는 구조체의 멤버번수가 아닐때만 쓴다. TableDB 에서 따로 관리한다. Offset 없고 단위계는 당연히 없다.
				ASSERT(m_type == TB_KEY ? m_nOffset == -1 && m_nUnit == D_UNITSYS_NONE : TRUE);
				// Foreign 은 구조체에 없는 값을 지정한다. 당연히 Offset 없다.
				ASSERT(m_type == TB_FOREIGN ? m_nOffset == -1 : TRUE);
				// CArray 면 Index 가 있어야 한다.
				ASSERT(m_type == TB_CArray ? m_nIndex >= 0 : m_nIndex == -1);
				// 단위계는 실수형 변수만 가질 수 있다.
				ASSERT(nUnit != D_UNITSYS_NONE ? m_type == TB_float || m_type == TB_double || ((m_type == TB_FOREIGN || m_type == TB_CArray) && (m_itemType == TB_float || m_itemType == TB_double)) : TRUE);
			}

			~MTBColumn()
			{
				if (m_pDataMap) delete m_pDataMap;
			}

		private:
			MTBColumn(const MTBColumn& src) :
				m_nID(src.m_nID), m_strName(src.m_strName), m_strMsgID(src.m_strMsgID), m_type(src.m_type), 
				m_nOffset(src.m_nOffset), m_nUnit(src.m_nUnit), m_itemType(src.m_itemType), m_nIndex(src.m_nIndex),
				m_displayType(TB_NONE), m_pDataMap(nullptr), // m_displayType, Map 은 항상 같이 쓰이며 초기화는 항상 None, NULL 으로 해둔다.
				m_pUnitCtrl(src.m_pUnitCtrl), m_dUnitConvertCurrent(src.m_dUnitConvertCurrent)
			{
				// DataMap 은 Schema 에 추가후에 생성해야함.
				ASSERT(src.m_displayType == TB_NONE);
				ASSERT(!src.m_pDataMap);
			}
			MTBColumn& operator=(const MTBColumn& src)
			{
				// 복사 금지
				ASSERT(0);
				return *this;
			}

		private:
			const int m_nID;			// Schema 내에서 유일한 id. MTBSchema::GetColumnByID() 만 사용 안 할거면 지정 안해줘도 된다.
			const CString m_strName;	// m_msgID 없을때 대체값으로 사용. TODO: 없앨까 고민중임...
			const CString m_strMsgID;	// message ID. 다국어지원용
			const Type m_type;		// Column 의 Data Type			
			const int m_nOffset;		// 구조체의 시작주소부터 해당 멤버까지의 offset. 구조체멤버가 아니면 -1. (offset값이 32bit 를 넘어갈 일은 없는 걸로...)
			const int m_nUnit;		// 단위계가 있을 경우 단위계 ID. 단위계 없으면 0
			const Type m_itemType;	// m_type 이 TB_CArray, TB_FOREIGN 일 경우 실제 Data의 Type
			const int m_nIndex;		// T_CArray 일 경우 Index. T_CArray 가 아니면 -1
		private: // 얘들은 Column 만들때 직접 지정 못 함.
			Type m_displayType; // 실제 Table 에서 나타낼 Data 와 구조체의 멤버변수와 Type 이 다를 경우. Type 같아도 값이 달라질 경우. 값까지 같아도 입력값을 제한할 경우
			ITBDataMap* m_pDataMap; // m_displayType 이 TB_NONE 이 아닐때 사용. 실제 Data <-> Table Data 간의 변환을 담당
			mit::lib::MUnitCtrl* m_pUnitCtrl;
			double m_dUnitConvertCurrent; // TODO: 단위계 바뀔때 마다 갱신해줘야 함
			
			// Getter
		public:
			int GetID() const { return m_nID; }
			const CString& GetName() const { return m_strName; }
			Type GetType() const { return m_type; }
			int GetOffset() const { return m_nOffset; }
			int GetUnit() const { return m_nUnit; }
			BOOL HasUnit() const { return m_nUnit != D_UNITSYS_NONE; }
			Type GetItemType() const { return m_itemType; }
			int GetIndex() const { return m_nIndex; }
			CString GetDisplayName() const
			{
				return m_strMsgID.IsEmpty() ? m_strName : mit::lib::MMSGFunction::GetValue(m_strMsgID);
			}
			CString GetHeaderName() const // 단위계까지 포함
			{
				if (HasUnit())
				{
					CString strName, strUnit;
					m_pUnitCtrl->GetUnitSystem(m_nUnit, strUnit);
					strName.Format(_T("%s\n(%s)"), GetDisplayName(), strUnit);
					return strName;
				}
				return GetDisplayName();
			}
			Type GetDisplayType() const
			{
				return (m_displayType != TB_NONE) ? m_displayType : 
					( (m_type == TB_FOREIGN || m_type == TB_CArray) ? m_itemType : m_type );
			}

			// Type
		public:
			BOOL IsKeyType() const { return m_type == TB_KEY; }
			BOOL IsForeignType() const { return m_type == TB_FOREIGN; }
			BOOL IsBooleanType() const { return GetDisplayType() == TB_BOOL || GetDisplayType() == TB_bool; }
			BOOL IsIntegerType() const { return GetDisplayType() == TB_int || GetDisplayType() == TB_UINT; }
			BOOL IsFloatType() const { return GetDisplayType() == TB_float || GetDisplayType() == TB_double; }
			static CString GetTypeName(Type nType);
			CString GetTypeName() const { return GetTypeName(GetDisplayType()); }

			// Display Map
		private:
			template<typename DISPLAY_TYPE>
			ITBDataMap* CreateDataMap();
		public:
			BOOL HasDataMap() const { return m_pDataMap != nullptr; }
			ITBDataMap* CreateDataMap(Type displayType, CRuntimeClass* pRuntimeClass);
			ITBDataMap* CreateDataMap(Type displayType);
			ITBDataMap* GetDataMap() const
			{
				// CString 으로 쓰는 경우가 거의 대부분일 것. Create 안하고 호출시 CString 으로 자동 생성
				if (m_pDataMap) return m_pDataMap; 				
				return (const_cast<MTBColumn*>(this))->CreateDataMap(TB_CString);
			}
			LPCVOID GetDisplayItem(LPCVOID pItem) const { return m_pDataMap ? m_pDataMap->GetDisplayItem(pItem) : pItem; }
			_variant_t GetValueItem(const _variant_t& varValue) const { return m_pDataMap ? m_pDataMap->GetValueItem(varValue) : varValue; }

			// Unit
		private:
			float ConvertUnitIn(float val) const { ASSERT(IsFloatType()); return HasUnit() ? (float)(val * m_dUnitConvertCurrent) : val; }
			double ConvertUnitIn(double val) const { ASSERT(IsFloatType()); return HasUnit() ? val * m_dUnitConvertCurrent : val; }
			float ConvertUnitOut(float val) const { ASSERT(IsFloatType()); return HasUnit() ? (float)(val / m_dUnitConvertCurrent) : val; }
			double ConvertUnitOut(double val) const { ASSERT(IsFloatType()); return HasUnit() ? val / m_dUnitConvertCurrent : val; }
		public:
			void SetUnitCtrl(mit::lib::MUnitCtrl* pUnitCtrl) { m_pUnitCtrl = pUnitCtrl; }
			void UpdateUnitConvertCurrent() { HasUnit() ? m_dUnitConvertCurrent = m_pUnitCtrl->GetConvertFactorCurrent(m_nUnit) : 0.0; }

			// GetItem
		private:
			LPCVOID GetItem(LPCVOID pRow) const { ASSERT(m_type != TB_KEY && m_type != TB_FOREIGN); return static_cast<const BYTE*>(pRow) + m_nOffset; }
			LPVOID GetItemW(LPVOID pRow) const { ASSERT(m_type != TB_KEY && m_type != TB_FOREIGN); return static_cast<BYTE*>(pRow) + m_nOffset; }
		private:
			void GetArrayItem(_variant_t& varValue, const CArray<LPCVOID>* paItem) const;
		public:
			void GetItemOld(_variant_t& varValue, LPCVOID pRow) const;

			// TODO: 2 달린것들 정리
			// GetItem New
		private:
			LPCVOID GetArrayItem2(const CArray<LPCVOID>* paItem) const;
			LPCVOID GetItem2(LPCVOID pRow) const;
		public:
			void GetItem(_variant_t& varValue, LPCVOID pRow) const;

			// SetItem
		private:
			void SetArrayItem(CArray<LPVOID>* paItem, const _variant_t& varValue) const;
		public:
			void SetItemOld(LPVOID pRow, const _variant_t& varValue) const;

			// SetItem New
		public:
			void SetItem(LPVOID pRow, const _variant_t& varValue) const;

			// Compare
		private:
			int CompareArrayItem(const CArray<LPCVOID>* paItem1, const CArray<LPCVOID>* paItem2) const;
		public:
			int CompareItemOld(LPCVOID pRow1, LPCVOID pRow2) const;

			// Compare New
		public:
			int CompareItem(LPCVOID pRow1, LPCVOID pRow2) const;
		};

		template<typename DISPLAY_TYPE>
		inline ITBDataMap* MTBColumn::CreateDataMap()
		{
			ASSERT(m_displayType == TB_NONE);
			switch (GetDisplayType())
			{
			case TB_MKey: return new MTBDataMap<MKey, DISPLAY_TYPE>(); break;
			case TB_BOOL: return new MTBDataMap<BOOL, DISPLAY_TYPE>(); break;
			case TB_bool: return new MTBDataMap<bool, DISPLAY_TYPE>(); break;
			case TB_int: return new MTBDataMap<int, DISPLAY_TYPE>(); break;
			case TB_UINT: return new MTBDataMap<UINT, DISPLAY_TYPE>(); break;
			case TB_float: return new MTBDataMap<float, DISPLAY_TYPE>(); break;
			case TB_double: return new MTBDataMap<double, DISPLAY_TYPE>(); break;
			case TB_CString: return new MTBDataMap<CString, DISPLAY_TYPE>(); break;
			case TB_KEY:
				// KEY Column 에는 DisplayMap 사용불가능
			case TB_FOREIGN: 
			case TB_CArray:
				// 얘네는 나올 수 없다.
			default: 
				ASSERT(0); 
				break;
			}
			return nullptr;
		}

		inline void MTBColumn::GetArrayItem(_variant_t& varValue, const CArray<LPCVOID>* paItem) const
		{								
			switch (m_itemType)
			{
			case TB_MKey: varValue = MTBConvertor<CArray<MKey>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_BOOL: varValue = MTBConvertor<CArray<BOOL>>::Convert(paItem).GetAt(m_nIndex) ? true : false; break;
			case TB_bool: varValue = MTBConvertor<CArray<bool>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_int: varValue = MTBConvertor<CArray<int>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_UINT: varValue = MTBConvertor<CArray<UINT>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_float: varValue = MTBConvertor<CArray<float>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_double: varValue = MTBConvertor<CArray<double>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_CString: varValue = MTBConvertor<CArray<CString>>::Convert(paItem).GetAt(m_nIndex); break;
			case TB_KEY:
			case TB_FOREIGN: 
			case TB_CArray:
				// 얘네는 m_itemType 으로 쓸 수 없는 놈들.
			default:
				ASSERT(0);
				break;
			}
		}

		inline LPCVOID MTBColumn::GetArrayItem2(const CArray<LPCVOID>* paItem) const
		{							
			switch (m_itemType)
			{
			case TB_MKey: return &MTBConvertor<CArray<MKey>>::Convert(paItem).GetAt(m_nIndex);
			case TB_BOOL: return &MTBConvertor<CArray<BOOL>>::Convert(paItem).GetAt(m_nIndex);
			case TB_bool: return &MTBConvertor<CArray<bool>>::Convert(paItem).GetAt(m_nIndex);
			case TB_int: return &MTBConvertor<CArray<int>>::Convert(paItem).GetAt(m_nIndex);
			case TB_UINT: return &MTBConvertor<CArray<UINT>>::Convert(paItem).GetAt(m_nIndex);
			case TB_float: return &MTBConvertor<CArray<float>>::Convert(paItem).GetAt(m_nIndex);
			case TB_double: return &MTBConvertor<CArray<double>>::Convert(paItem).GetAt(m_nIndex);
			case TB_CString: return &MTBConvertor<CArray<CString>>::Convert(paItem).GetAt(m_nIndex);
			case TB_KEY:
			case TB_FOREIGN: 
			case TB_CArray:
				// 얘네는 m_itemType 으로 쓸 수 없는 놈들.
			default:
				ASSERT(0);
				break;
			}
			return nullptr;
		}

		inline LPCVOID MTBColumn::GetItem2(LPCVOID pRow) const
		{
			switch (m_type)
			{
			case TB_MKey:
			case TB_BOOL:
			case TB_bool:
			case TB_int:
			case TB_UINT:
			case TB_float:
			case TB_double:
			case TB_CString:
				return GetDisplayItem(GetItem(pRow));
			case TB_CArray: 
				{
					const CArray<LPCVOID>* paItem = MTBConvertor<CArray<LPCVOID>>::PConvert(GetItem(pRow));
					if (m_nIndex < paItem->GetSize()) return GetDisplayItem(GetArrayItem2(paItem));
					else return nullptr;
				}
				break;
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				break;
			}	
			return nullptr;
		}

		inline void MTBColumn::GetItem(_variant_t& varValue, LPCVOID pRow) const
		{
			LPCVOID pItem = GetItem2(pRow);
			if (!pItem) { varValue.Clear(); return; }

			switch (GetDisplayType())
			{
			case TB_MKey: varValue = MTBConvertor<MKey>::Convert(pItem); break;
			case TB_BOOL: varValue = MTBConvertor<BOOL>::Convert(pItem) ? true : false; break;
			case TB_bool: varValue = MTBConvertor<bool>::Convert(pItem); break;
			case TB_int: varValue = MTBConvertor<int>::Convert(pItem); break;
			case TB_UINT: varValue = MTBConvertor<UINT>::Convert(pItem); break;
			case TB_float: varValue = ConvertUnitOut(MTBConvertor<float>::Convert(pItem)); break;
			case TB_double: varValue = ConvertUnitOut(MTBConvertor<double>::Convert(pItem)); break;
			case TB_CString: varValue = MTBConvertor<CString>::Convert(pItem); break;
			case TB_CArray: 
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				break;
			}	
		}

		inline void MTBColumn::GetItemOld(_variant_t& varValue, LPCVOID pRow) const 
		{
			switch (m_type)
			{
			case TB_MKey: varValue = MTBConvertor<MKey>::Convert(GetItem(pRow)); break;
			case TB_BOOL: varValue = MTBConvertor<BOOL>::Convert(GetItem(pRow)) ? true : false; break;
			case TB_bool: varValue = MTBConvertor<bool>::Convert(GetItem(pRow)); break;
			case TB_int: varValue = MTBConvertor<int>::Convert(GetItem(pRow)); break;
			case TB_UINT: varValue = MTBConvertor<UINT>::Convert(GetItem(pRow)); break;
			case TB_float: varValue = MTBConvertor<float>::Convert(GetItem(pRow)); break;
			case TB_double: varValue = MTBConvertor<double>::Convert(GetItem(pRow)); break;
			case TB_CString: varValue = MTBConvertor<CString>::Convert(GetItem(pRow)); break;
			case TB_CArray: 
				{
					const CArray<LPCVOID>* paItem = MTBConvertor<CArray<LPCVOID>>::PConvert(GetItem(pRow));
					if (m_nIndex < paItem->GetSize()) GetArrayItem(varValue, paItem);
					else varValue.Clear();
				}
				break;
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				break;
			}	
		}

		inline void MTBColumn::SetArrayItem(CArray<LPVOID>* paItem, const _variant_t& varValue) const
		{					
			switch (m_itemType)
			{
			case TB_MKey: MTBConvertor<CArray<MKey>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_BOOL: MTBConvertor<CArray<BOOL>>::ConvertW(paItem).SetAtGrow(m_nIndex, (bool)varValue ? TRUE : FALSE); break;
			case TB_bool: MTBConvertor<CArray<bool>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_int: MTBConvertor<CArray<int>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_UINT: MTBConvertor<CArray<UINT>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_float: MTBConvertor<CArray<float>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_double: MTBConvertor<CArray<double>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_CString: MTBConvertor<CArray<CString>>::ConvertW(paItem).SetAtGrow(m_nIndex, varValue); break;
			case TB_KEY:
			case TB_FOREIGN: 
			case TB_CArray:
				// 얘네는 m_itemType 으로 쓸 수 없는 놈들.
			default:
				ASSERT(0);
				break;
			}
		}

		inline void MTBColumn::SetItemOld(LPVOID pRow, const _variant_t& varValue) const 
		{
			if (varValue.vt == VT_EMPTY) return;
			switch (m_type)
			{
			case TB_MKey: MTBConvertor<MKey>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_BOOL: MTBConvertor<BOOL>::ConvertW(GetItemW(pRow)) = (bool)varValue ? TRUE : FALSE; break;
			case TB_bool: MTBConvertor<bool>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_int: MTBConvertor<int>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_UINT: MTBConvertor<UINT>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_float: MTBConvertor<float>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_double: MTBConvertor<double>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_CString: MTBConvertor<CString>::ConvertW(GetItemW(pRow)) = varValue; break;
			case TB_CArray: 
				{
					CArray<LPVOID>* paItem = MTBConvertor<CArray<LPVOID>>::PConvertW(GetItemW(pRow));
					SetArrayItem(paItem, varValue);
				}
				break;
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				break;
			}	
		}

		inline void MTBColumn::SetItem(LPVOID pRow, const _variant_t& varValue) const
		{
			if (varValue.vt == VT_EMPTY) return;

			_variant_t varValueItem = GetValueItem(varValue);
			if (varValueItem.vt == VT_EMPTY) return;

			switch (m_type)
			{
			case TB_MKey: MTBConvertor<MKey>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_BOOL: MTBConvertor<BOOL>::ConvertW(GetItemW(pRow)) = (bool)varValueItem ? TRUE : FALSE; break;
			case TB_bool: MTBConvertor<bool>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_int: MTBConvertor<int>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_UINT: MTBConvertor<UINT>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_float: MTBConvertor<float>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_double: MTBConvertor<double>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_CString: MTBConvertor<CString>::ConvertW(GetItemW(pRow)) = varValueItem; break;
			case TB_CArray: 
				{
					CArray<LPVOID>* paItem = MTBConvertor<CArray<LPVOID>>::PConvertW(GetItemW(pRow));
					SetArrayItem(paItem, varValueItem);
				}
				break;
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				break;
			}	
		}

		inline int MTBColumn::CompareArrayItem(const CArray<LPCVOID>* paItem1, const CArray<LPCVOID>* paItem2) const
		{				
			switch (m_itemType)
			{
			case TB_MKey: return MTBArrayCompare<MKey>::Subtract(paItem1, paItem2, m_nIndex);
			case TB_BOOL: return MTBArrayCompare<BOOL>::Compare(paItem1, paItem2, m_nIndex);
			case TB_bool: return MTBArrayCompare<bool>::Compare(paItem1, paItem2, m_nIndex);
			case TB_int: return MTBArrayCompare<int>::Subtract(paItem1, paItem2, m_nIndex);
			case TB_UINT: return MTBArrayCompare<UINT>::Subtract(paItem1, paItem2, m_nIndex);
			case TB_float: return MTBArrayCompare<float>::Compare(paItem1, paItem2, m_nIndex);
			case TB_double: return MTBArrayCompare<double>::Compare(paItem1, paItem2, m_nIndex);
			case TB_CString: return MTBStringArrayCompare(paItem1, paItem2, m_nIndex);
			case TB_KEY:
			case TB_FOREIGN: 
			case TB_CArray:
				// 얘네는 m_itemType 으로 쓸 수 없는 놈들.
			default:
				ASSERT(0);
				return 0;
			}
		}

		inline int MTBColumn::CompareItemOld(LPCVOID pRow1, LPCVOID pRow2) const
		{
			// TODO: 이거 부터 시작해서 Convertor 쪽 템플릿 몽땅 인라인 되어야 한다. 확인해 보기
			switch (m_type)
			{				
			case TB_MKey: return MTBCompare<MKey>::Subtract(GetItem(pRow1), GetItem(pRow2));	
			case TB_BOOL: return MTBCompare<BOOL>::Compare(GetItem(pRow1), GetItem(pRow2));
			case TB_bool: return MTBCompare<bool>::Compare(GetItem(pRow1), GetItem(pRow2));
			case TB_int: return MTBCompare<int>::Subtract(GetItem(pRow1), GetItem(pRow2));
			case TB_UINT: return MTBCompare<UINT>::Subtract(GetItem(pRow1), GetItem(pRow2));
			case TB_float: return MTBCompare<float>::Compare(GetItem(pRow1), GetItem(pRow2));
			case TB_double: return MTBCompare<double>::Compare(GetItem(pRow1), GetItem(pRow2));
			case TB_CString: return MTBStringCompare(GetItem(pRow1), GetItem(pRow2));
			case TB_CArray: 
				{
					const CArray<LPCVOID>* paItem1 = MTBConvertor<CArray<LPCVOID>>::PConvert(GetItem(pRow1));
					const CArray<LPCVOID>* paItem2 = MTBConvertor<CArray<LPCVOID>>::PConvert(GetItem(pRow2));
					return ( m_nIndex < paItem1->GetSize() ) ?
						( m_nIndex < paItem2->GetSize() ? CompareArrayItem(paItem1, paItem2) : 1 ) :
						( m_nIndex < paItem2->GetSize() ? -1 : 0 );
				}
				break;
			case TB_KEY: 
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				return 0;
			}	
		}

		inline int MTBColumn::CompareItem(LPCVOID pRow1, LPCVOID pRow2) const
		{
			LPCVOID pItem1 = GetItem2(pRow1);
			LPCVOID pItem2 = GetItem2(pRow2);
			if (!pItem1 || !pItem2) return pItem1 ? 1 : (pItem2 ? -1 : 0);

			switch (GetDisplayType())
			{
			case TB_MKey: return MTBCompare<MKey>::Subtract(pItem1, pItem2);
			case TB_BOOL: return MTBCompare<BOOL>::Compare(pItem1, pItem2);
			case TB_bool: return MTBCompare<bool>::Compare(pItem1, pItem2);
			case TB_int: return MTBCompare<int>::Subtract(pItem1, pItem2);
			case TB_UINT: return MTBCompare<UINT>::Subtract(pItem1, pItem2);
			case TB_float: return MTBCompare<float>::Compare(pItem1, pItem2);
			case TB_double: return MTBCompare<double>::Compare(pItem1, pItem2);
			case TB_CString: return MTBStringCompare(pItem1, pItem2);
			case TB_CArray: 
			case TB_KEY:
			case TB_FOREIGN: 
				// 얘네는 따로 처리해줘야 한다.
			default:
				ASSERT(0);
				return 0;
			}				
		}
	}
}

#include "HeaderPost.h"