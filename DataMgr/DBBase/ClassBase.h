#pragma once

#include "DataObserver.h"
#include "DataPool.h"
#include "../common/HeaderPre.h"
class ClassPool;
class __MY_EXT_CLASS__ ClassBase
{
public:
	ClassBase(ClassPool* pDB,const T_KEY type);

	BOOL Add(const CDataBase* pData, BOOL bReplace = FALSE);
	BOOL Del(const CDataBase* pData);
	BOOL Del(T_KEY nKey);
	BOOL Mod(const CDataBase* pData);
	CDataObserverMgr* ObserverMgr()const;
	
	const CDataBase* GetData(T_KEY nKey)const;
	BOOL GetData(T_KEY nKey, CDataBase*& pData)const;
	BOOL Exist(T_KEY nKey)const;
	T_KEY GetID()const;
	BOOL TestData()const;
private:
	BOOL OnBeforeAddData(const CDataBase* pData);
	BOOL OnAfterAddData(const CDataBase* pData);
	BOOL OnBeforeDelData(const CDataBase* pData);
	BOOL OnAfterDelData(const CDataBase* pData);
	BOOL OnBeforeModData(const CDataBase* pData,const CDataBase* pOldData);
	BOOL OnAfterModData(const CDataBase* pData,const CDataBase* pOldData);
	BOOL PrintData(const CDataBase* pData);
private:
	CDataObserverMgr * m_pObserverMgr;
	CDataPool* m_pool;
	ClassPool* m_pDB;
	const T_KEY m_nKey;
};

#include "../common/HeaderPost.h"
