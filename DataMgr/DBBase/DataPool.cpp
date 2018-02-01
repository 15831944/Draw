#include "stdafx.h"
#include "DataPool.h"

BOOL CDataPool::IsExist(T_KEY nKey)const
{
	return m_pool.find(nKey) != m_pool.end();
}

BOOL CDataPool::Add(const CDataBase * pData)
{
	if (IsExist(pData->m_nKey))
	{
		ASSERT(FALSE);
		return FALSE;
	}
	m_pool.insert(std::pair<T_KEY,CDataBase*>(pData->m_nKey, pData->Duplicate()));
	return TRUE;
}

BOOL CDataPool::Del(const CDataBase * pData)
{
	if (!IsExist(pData->m_nKey))
	{
		ASSERT(FALSE);
		return FALSE;
	}
	m_pool.erase(pData->m_nKey);
	delete pData;
	return TRUE;
}

const CDataBase * CDataPool::GetData(T_KEY nKey) const
{
	if (!IsExist(nKey))
		return nullptr;
	auto it = m_pool.find(nKey);
	//std::map<T_KEY, CDataBase*>::const_iterator  iter = m_pool.find(nKey);
	ASSERT(it->second);
	return it->second;
}

BOOL CDataPool::GetData(T_KEY nKey, CDataBase*& pData) const
{
	if (!IsExist(nKey))
		return FALSE;
	auto it = m_pool.find(nKey);
	pData = it->second;
	ASSERT(pData != nullptr);
	return TRUE;
}

size_t CDataPool::GetSize() const
{
	return m_pool.size();
}

std::map<T_KEY, CDataBase*>::const_iterator CDataPool::begin() const
{
	return m_pool.begin();
}

std::map<T_KEY, CDataBase*>::const_iterator CDataPool::end() const
{
	return m_pool.end();
}
