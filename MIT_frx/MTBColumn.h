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
		// ��ӱ����� �θ�Ŭ����
		class __MY_EXT_CLASS__ MTBNonInheritance
		{
		protected:
			MTBNonInheritance() {}
			MTBNonInheritance(const MTBNonInheritance& src) {}
		};

		// ��ӱ���
		class __MY_EXT_CLASS__ MTBColumn : private virtual MTBNonInheritance
		{
			friend class MTBSchemaBase; // ����� MTBSchemaBase �������� ���

		public:
			// TB_ �ڿ� ���� Type �̸��� �����ϰ� ����. ��ҹ��ڱ��� �����ؾ� �Ѵ�.
			//   TB_NONE, TB_KEY, TB_FOREIGN �� ����
			enum Type
			{
				TB_NONE,	// itemType �ʿ������ ���. ���� ������ ����.
				TB_KEY,		// TableDB���� Ű����Ʈ ���� ������ ���. Ű����Ʈ�� �ִ� ���� ���. offset �Ⱦ�. 
				TB_FOREIGN,	// TODO: �̱���. Data �� ����ü�� ���� ������ (�ٸ� ����ü�� �ְų�, ��¶�� Data �ּҿ� offset ���� ������ �� ���� ��)
				TB_MKey,
				TB_BOOL,
				TB_bool,
				TB_int,
				TB_UINT,
				TB_float,
				TB_double,
				TB_CString,
				TB_CArray
				// TODO : Struct �߰��ϱ� (�׳� ����� ������ ������ �ʿ���� ���� ������, CArray �ȿ� ����ü ���� ��� �������)
				//TB_Struct,
				// �׸� �߰��� ��� ���� �ڵ� �� ã�Ƽ� �߰����ֱ�		
			};

		public:
			MTBColumn(int nID, const CString& strName, const CString& strMsgID, Type type, int nOffset, int nUnit, Type itemType, int nIndex) :
				m_nID(nID), m_strName(strName), m_strMsgID(strMsgID), m_type(type), m_nOffset(nOffset), m_nUnit(nUnit), m_itemType(itemType), m_nIndex(nIndex),
				m_displayType(TB_NONE), m_pDataMap(nullptr), // m_displayType, Map �� �׻� ���� ���̸� �ʱ�ȭ�� �׻� None, NULL ���� �صд�.
				m_pUnitCtrl(nullptr), m_dUnitConvertCurrent(0.0)
			{
				// �Ǽ� ���� ���� ASSERT �ִ��� ���� �ɾ�д�.

				// Type �� None �� �� �� ����.
				ASSERT(m_type != TB_NONE);
				// KEY�� ItemType ���� �� ����. Foreign �� Foreign ������ ����. ��ø�� CArray �������Ѵ�.
				ASSERT(m_itemType != TB_KEY && m_itemType != TB_FOREIGN && m_itemType != TB_CArray);
				// Foreign �̳� CArray �� ��츸 ���� ItemType �� �ʿ��ϴ�.
				ASSERT(m_type == TB_FOREIGN || m_type == TB_CArray ? m_itemType != TB_NONE : m_itemType == TB_NONE);
				// Key, Foreign �� �ƴϸ� Offset �� �� �־�� �Ѵ�.
				ASSERT(m_type != TB_KEY && m_itemType != TB_FOREIGN ? m_nOffset >= 0 : TRUE);
				// Key �� ����ü�� ��������� �ƴҶ��� ����. TableDB ���� ���� �����Ѵ�. Offset ���� ������� �翬�� ����.
				ASSERT(m_type == TB_KEY ? m_nOffset == -1 && m_nUnit == D_UNITSYS_NONE : TRUE);
				// Foreign �� ����ü�� ���� ���� �����Ѵ�. �翬�� Offset ����.
				ASSERT(m_type == TB_FOREIGN ? m_nOffset == -1 : TRUE);
				// CArray �� Index �� �־�� �Ѵ�.
				ASSERT(m_type == TB_CArray ? m_nIndex >= 0 : m_nIndex == -1);
				// ������� �Ǽ��� ������ ���� �� �ִ�.
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
				m_displayType(TB_NONE), m_pDataMap(nullptr), // m_displayType, Map �� �׻� ���� ���̸� �ʱ�ȭ�� �׻� None, NULL ���� �صд�.
				m_pUnitCtrl(src.m_pUnitCtrl), m_dUnitConvertCurrent(src.m_dUnitConvertCurrent)
			{
				// DataMap �� Schema �� �߰��Ŀ� �����ؾ���.
				ASSERT(src.m_displayType == TB_NONE);
				ASSERT(!src.m_pDataMap);
			}
			MTBColumn& operator=(const MTBColumn& src)
			{
				// ���� ����
				ASSERT(0);
				return *this;
			}

		private:
			const int m_nID;			// Schema ������ ������ id. MTBSchema::GetColumnByID() �� ��� �� �ҰŸ� ���� �����൵ �ȴ�.
			const CString m_strName;	// m_msgID ������ ��ü������ ���. TODO: ���ٱ� �������...
			const CString m_strMsgID;	// message ID. �ٱ���������
			const Type m_type;		// Column �� Data Type			
			const int m_nOffset;		// ����ü�� �����ּҺ��� �ش� ��������� offset. ����ü����� �ƴϸ� -1. (offset���� 32bit �� �Ѿ ���� ���� �ɷ�...)
			const int m_nUnit;		// �����谡 ���� ��� ������ ID. ������ ������ 0
			const Type m_itemType;	// m_type �� TB_CArray, TB_FOREIGN �� ��� ���� Data�� Type
			const int m_nIndex;		// T_CArray �� ��� Index. T_CArray �� �ƴϸ� -1
		private: // ����� Column ���鶧 ���� ���� �� ��.
			Type m_displayType; // ���� Table ���� ��Ÿ�� Data �� ����ü�� ��������� Type �� �ٸ� ���. Type ���Ƶ� ���� �޶��� ���. ������ ���Ƶ� �Է°��� ������ ���
			ITBDataMap* m_pDataMap; // m_displayType �� TB_NONE �� �ƴҶ� ���. ���� Data <-> Table Data ���� ��ȯ�� ���
			mit::lib::MUnitCtrl* m_pUnitCtrl;
			double m_dUnitConvertCurrent; // TODO: ������ �ٲ� ���� ��������� ��
			
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
			CString GetHeaderName() const // ��������� ����
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
				// CString ���� ���� ��찡 ���� ��κ��� ��. Create ���ϰ� ȣ��� CString ���� �ڵ� ����
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

			// TODO: 2 �޸��͵� ����
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
				// KEY Column ���� DisplayMap ���Ұ���
			case TB_FOREIGN: 
			case TB_CArray:
				// ��״� ���� �� ����.
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
				// ��״� m_itemType ���� �� �� ���� ���.
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
				// ��״� m_itemType ���� �� �� ���� ���.
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� m_itemType ���� �� �� ���� ���.
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� m_itemType ���� �� �� ���� ���.
			default:
				ASSERT(0);
				return 0;
			}
		}

		inline int MTBColumn::CompareItemOld(LPCVOID pRow1, LPCVOID pRow2) const
		{
			// TODO: �̰� ���� �����ؼ� Convertor �� ���ø� ���� �ζ��� �Ǿ�� �Ѵ�. Ȯ���� ����
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
				// ��״� ���� ó������� �Ѵ�.
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
				// ��״� ���� ó������� �Ѵ�.
			default:
				ASSERT(0);
				return 0;
			}				
		}
	}
}

#include "HeaderPost.h"