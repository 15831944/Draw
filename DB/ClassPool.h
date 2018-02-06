#pragma once
#include "ClassBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ ClassPool
{
public:
	ClassPool(const T_KEY nKey);
	T_KEY GetID()const;
	BOOL Register(ClassBase* pClass);
	BOOL UnRegister(ClassBase* pClass);
	BOOL ExistID(T_KEY nKey)const;
	ClassBase* GetClass(T_KEY nKey)const;
private:
	std::map<T_KEY, ClassBase*>m_pool;
	const T_KEY m_nKey;
};

#include "HeaderPost.h"
