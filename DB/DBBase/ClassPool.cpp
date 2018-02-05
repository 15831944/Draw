#include "stdafx.h"
#include "ClassPool.h"

ClassPool::ClassPool(const T_KEY nKey):m_nKey(nKey)
{
}

T_KEY ClassPool::GetID() const
{
	return m_nKey;
}

BOOL ClassPool::Register(ClassBase * pClass)
{
	if (ExistID(pClass->GetID()))
		return FALSE;
	m_pool.insert(std::make_pair(pClass->GetID(), pClass));
	return TRUE;
}

BOOL ClassPool::UnRegister(ClassBase * pClass)
{
	if (!ExistID(pClass->GetID()))
		return TRUE;
	m_pool.erase(pClass->GetID());
	return TRUE;
}

BOOL ClassPool::ExistID(T_KEY nKey) const
{
	return m_pool.find(nKey) != m_pool.end();
}

ClassBase * ClassPool::GetClass(T_KEY nKey) const
{
	if (!ExistID(nKey))
		return nullptr;
	auto it = m_pool.find(nKey);
	ASSERT(it->second);
	return it->second;
}
