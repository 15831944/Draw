#pragma once
#include "DataBase.h"
#include <map>
class CDataPool
{
	friend class ClassBase; 
private:
	BOOL IsExist(T_KEY nKey)const;
	BOOL Add(const CDataBase* pData);
	BOOL Del(const CDataBase* pData);
	const CDataBase* GetData(T_KEY nKey)const;
	BOOL GetData(T_KEY, CDataBase*& pData)const;
	size_t GetSize()const;
	std::map<T_KEY,CDataBase*>::const_iterator begin()const;
	std::map<T_KEY, CDataBase*>::const_iterator end()const;
private:
	std::map<T_KEY, CDataBase*>m_pool;
};