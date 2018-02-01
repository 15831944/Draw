#include "stdafx.h"
#include "MTBColumn.h"

using namespace mit::frx;

CString MTBColumn::GetTypeName(Type nType)
{
	switch (nType)
	{
	case TB_KEY:
	case TB_MKey: return _T("Key");
	case TB_BOOL:
	case TB_bool: return _T("Boolean");
	case TB_int:
	case TB_UINT: return _T("Integer");
	case TB_float:
	case TB_double: return _T("Real");
	case TB_CString: return _T("String");
	case TB_FOREIGN:
	case TB_CArray:
	default:
		// 얘네는 이름없다
		ASSERT(0);
		break;
	}
	return _T("");
}

ITBDataMap* MTBColumn::CreateDataMap(Type displayType)
{
	ASSERT(m_displayType == TB_NONE && !m_pDataMap); // Create 은 무조건 한 번만 한다.

	switch (displayType)
	{
	case TB_MKey: m_pDataMap = CreateDataMap<MKey>(); break;
	case TB_BOOL: m_pDataMap = CreateDataMap<BOOL>(); break;
	case TB_bool: m_pDataMap = CreateDataMap<BOOL>(); break;
	case TB_int: m_pDataMap = CreateDataMap<int>(); break;
	case TB_UINT: m_pDataMap = CreateDataMap<UINT>(); break;
	case TB_float: m_pDataMap = CreateDataMap<float>(); break;
	case TB_double: m_pDataMap = CreateDataMap<double>(); break;
	case TB_CString: m_pDataMap = CreateDataMap<CString>(); break;
	case TB_KEY:
	case TB_FOREIGN: 
	case TB_CArray:
		// 얘네들 안된다. 당연한거 아니겠나
	default:
		ASSERT(0);
		break;
	}

	m_displayType = displayType;
	ASSERT(m_pDataMap);

	return m_pDataMap;
}

ITBDataMap* MTBColumn::CreateDataMap(Type displayType, CRuntimeClass* pRuntimeClass)
{
	ASSERT(m_displayType == TB_NONE && !m_pDataMap);

	if (!pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(ITBDataMap))) return nullptr;
	m_pDataMap = DYNAMIC_DOWNCAST(ITBDataMap, pRuntimeClass->CreateObject());

	m_displayType = displayType;
	ASSERT(m_pDataMap);

	return m_pDataMap;
}