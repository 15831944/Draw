#pragma once
#include <map>
#include "ClassPool.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ IDBMgr
{
public:
	~IDBMgr() {}
public:
	static IDBMgr* Inst();
	static void Clear();
public:
	BOOL Register(ClassPool* pClass);
	BOOL ExistID(T_KEY nKey)const;
	ClassPool* GetDB(T_KEY nKey)const;
	BOOL UnRegister(T_KEY nKey);
private:
	IDBMgr() {}
private:
	static IDBMgr* g_Instance;
	std::map<T_KEY, ClassPool*>m_Pool;
};
#include "HeaderPost.h"
