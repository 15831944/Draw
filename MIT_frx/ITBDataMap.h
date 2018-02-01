#pragma once

#include "HeaderPre.h"

// TODO: 요고 딴곳에 옮기기
// TODO: 각 Template Instance 가 다른 ClassName 가지게 할 수 없을까...
#define IMPLEMENT_RUNTIMECLASS_TEMPLATE(class_name, type_name, base_class_name, wSchema, pfnNew, class_init) \
	template <type_name TYPE> \
	CRuntimeClass* PASCAL class_name<TYPE>::_GetBaseClass() \
	{ return RUNTIME_CLASS(base_class_name); } \
	template <type_name TYPE> \
	const CRuntimeClass class_name<TYPE>::class##class_name = { \
	#class_name, sizeof(class class_name<TYPE>), 0xFFFF, pfnNew, \
	&class_name<TYPE>::_GetBaseClass, NULL, class_init }; \
	template <type_name TYPE> \
	CRuntimeClass* PASCAL class_name<TYPE>::GetThisClass() \
	{ return (CRuntimeClass*)(&class_name<TYPE>::class##class_name); } \
	template <type_name TYPE> \
	CRuntimeClass* class_name<TYPE>::GetRuntimeClass() const \
	{ return (CRuntimeClass*)(&class_name<TYPE>::class##class_name); }

#define IMPLEMENT_DYNCREATE_TEMPLATE(class_name, type_name, base_class_name) \
	template <type_name TYPE> \
	CObject* PASCAL class_name<TYPE>::CreateObject() \
	{ return new class_name<TYPE>(); } \
	IMPLEMENT_RUNTIMECLASS_TEMPLATE(class_name, type_name, base_class_name, 0xFFFF, (class_name<TYPE>::CreateObject), NULL)


#define IMPLEMENT_RUNTIMECLASS_TEMPLATE_2(class_name, type_name1, type_name2, base_class_name, wSchema, pfnNew, class_init) \
	template <type_name1 TYPE1, type_name2 TYPE2> \
	CRuntimeClass* PASCAL class_name<TYPE1, TYPE2>::_GetBaseClass() \
	{ return RUNTIME_CLASS(base_class_name); } \
	template <type_name1 TYPE1, type_name2 TYPE2> \
	const CRuntimeClass class_name<TYPE1, TYPE2>::class##class_name = { \
	#class_name, sizeof(class class_name<TYPE1, TYPE2>), 0xFFFF, pfnNew, \
	&class_name<TYPE1, TYPE2>::_GetBaseClass, NULL, class_init }; \
	template <type_name1 TYPE1, type_name2 TYPE2> \
	CRuntimeClass* PASCAL class_name<TYPE1, TYPE2>::GetThisClass() \
	{ return (CRuntimeClass*)(&class_name<TYPE1, TYPE2>::class##class_name); } \
	template <type_name1 TYPE1, type_name2 TYPE2> \
	CRuntimeClass* class_name<TYPE1, TYPE2>::GetRuntimeClass() const \
	{ return (CRuntimeClass*)(&class_name<TYPE1, TYPE2>::class##class_name); }

#define IMPLEMENT_DYNCREATE_TEMPLATE_2(class_name, type_name1, type_name2, base_class_name) \
	template <type_name1 TYPE1, type_name2 TYPE2> \
	CObject* PASCAL class_name<TYPE1, TYPE2>::CreateObject() \
	{ return new class_name<TYPE1, TYPE2>(); } \
	IMPLEMENT_RUNTIMECLASS_TEMPLATE_2(class_name, type_name1, type_name2, base_class_name, 0xFFFF, (class_name<TYPE1, TYPE2>::CreateObject), NULL)

// 하드코딩. 구현 포함
//protected:
//	static CRuntimeClass* PASCAL _GetBaseClass() { return RUNTIME_CLASS(ITBDataMap); }
//public:
//	static const CRuntimeClass classMTBDataMap;
//	static CRuntimeClass* PASCAL GetThisClass() { return &classMTBDataMap; }
//	virtual CRuntimeClass* GetRuntimeClass() const { return (CRuntimeClass*)&classMTBDataMap; }
//	static CObject* PASCAL CreateObject() { return new MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>(); }

// 하드코딩. 구현 분리
//protected:
//	static CRuntimeClass* PASCAL _GetBaseClass();
//public:
//	static const CRuntimeClass classMTBDataMap;
//	static CRuntimeClass* PASCAL GetThisClass();
//	virtual CRuntimeClass* GetRuntimeClass() const;
//	static CObject* PASCAL CreateObject();

// 하드코딩. 구현
//template <typename VALUE_TYPE, typename DISPLAY_TYPE>
//CRuntimeClass* PASCAL MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::_GetBaseClass() 
//{ return RUNTIME_CLASS(ITBDataMap); }
//template <typename VALUE_TYPE, typename DISPLAY_TYPE>
//const CRuntimeClass MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::classMTBDataMap = {
//	"MTBDataMap", sizeof(class MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>), 0xFFFF, 
//	MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::CreateObject,
//	&MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::_GetBaseClass, NULL, NULL };
//template <typename VALUE_TYPE, typename DISPLAY_TYPE>
//CRuntimeClass* PASCAL MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::GetThisClass() 
//{ return &classMTBDataMap; }
//template <typename VALUE_TYPE, typename DISPLAY_TYPE>
//CRuntimeClass* MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::GetRuntimeClass() const 
//{ return (CRuntimeClass*)&classMTBDataMap; }
//template <typename VALUE_TYPE, typename DISPLAY_TYPE>
//CObject* PASCAL MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>::CreateObject() 
//{ return new MTBDataMap<VALUE_TYPE, DISPLAY_TYPE>(); }

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ITBDataMap : public CObject
		{
			DECLARE_DYNAMIC(ITBDataMap)
		public:
			ITBDataMap() {}
			virtual ~ITBDataMap() {}
		public:
			virtual void SetDefaultValue(_variant_t val) = 0;
			virtual void SetDefaultDisplay(_variant_t display) = 0;
			virtual void ClearDefaultValue() = 0;
			virtual void ClearDefaultDisplay() = 0;
		public:
			virtual BOOL AddItem(_variant_t val, _variant_t display) = 0;
			virtual BOOL AddItem(_variant_t val, const CString& str) { return AddItem(val, _variant_t((LPCTSTR)str)); }
			virtual BOOL RemoveItem(_variant_t val) = 0;
		public:
			virtual LPCVOID GetDisplayItem(LPCVOID pVal) const = 0;
			virtual _variant_t GetValueItem(const _variant_t& display) const = 0;

			// DisplayItem
		public:
			virtual size_t GetCount() const = 0;
			virtual POSITION GetHeadPosition() const = 0;
			virtual POSITION Find(const _variant_t& item) const = 0;
			virtual _variant_t GetNext(POSITION& pos) const = 0;
			virtual _variant_t GetAt(POSITION pos) const = 0;
		};
	}
}

#include "HeaderPost.h"