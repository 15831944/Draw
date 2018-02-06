#include "stdafx.h"
#include "DBMgr.h"

IDBMgr* IDBMgr::g_Instance = nullptr;
IDBMgr * IDBMgr::Inst()
{
	/*static IDBMgr gInstance;
	return &gInstance;*/
	if (g_Instance == nullptr)
		g_Instance = new IDBMgr();
	return g_Instance;
}

void IDBMgr::Clear()
{
	if (g_Instance)
	{
		delete g_Instance;
		g_Instance = nullptr;
	}
}

BOOL IDBMgr::Register(ClassPool * pClass)
{
	if (ExistID(pClass->GetID()))
		return FALSE;
	m_Pool.insert(std::make_pair(pClass->GetID(), pClass));
	return TRUE;
}

BOOL IDBMgr::ExistID(T_KEY nKey) const
{
	return m_Pool.find(nKey) != m_Pool.end();
}

ClassPool * IDBMgr::GetDB(T_KEY nKey) const
{
	if (ExistID(nKey) == FALSE)
		return nullptr;
	auto it = m_Pool.find(nKey);
	//std::map<T_KEY, ClassPool*>::const_iterator iter = m_Pool.find(nKey);
	ASSERT(it->second);
	return it->second;
}

BOOL IDBMgr::UnRegister(T_KEY nKey)
{
	if (!ExistID(nKey))
		return TRUE;
	m_Pool.erase(nKey);
	return TRUE;
}
