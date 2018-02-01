#include "stdafx.h"
#include "ClassBase.h"

ClassBase::ClassBase(ClassPool * pDB, const T_KEY type) :m_nKey(type)
{
	m_pObserverMgr = new CDataObserverMgr();
	m_pool = new CDataPool();
}

BOOL ClassBase::Add(const CDataBase * pData, BOOL bReplace)
{
	if (pData == nullptr)
		return FALSE;
	if (Exist(pData->m_nKey))
	{
		if (bReplace)
			return Mod(pData);
		else
			return FALSE;
	}
	if (!OnBeforeAddData(pData))
		return FALSE;
	if (!m_pool->Add(pData))
		return FALSE;
	if (!OnAfterAddData(pData))
		return FALSE;
	return TRUE;
}

BOOL ClassBase::Del(const CDataBase * pData)
{
	if (pData == nullptr)
		return FALSE;
	if (!Exist(pData->m_nKey))
		return FALSE;
	if (!OnBeforeDelData(pData))
		return FALSE;
	CDataBase* pBackUp = pData->Duplicate();
	if (!m_pool->Del(pData))
	{
		delete pBackUp;
		return FALSE;
	}
	BOOL bSuccess = OnAfterDelData(pBackUp);
	delete pBackUp;
	return bSuccess;
}

BOOL ClassBase::Del(T_KEY nKey)
{
	return Del(m_pool->GetData(nKey));
}

BOOL ClassBase::Mod(const CDataBase * pData)
{
	if (!Exist(pData->m_nKey))
		return FALSE;
	const CDataBase* pOldData = GetData(pData->m_nKey);
	if (!OnBeforeModData(pData, pOldData))
		return FALSE;
	const CDataBase* pBackUp = pOldData->Duplicate();
	if (!m_pool->Del(pOldData))
	{
		delete pBackUp;
		return FALSE;
	}
	if (!m_pool->Add(pData))
	{
		delete pBackUp;
		return FALSE;
	}
	BOOL bSuccess = OnAfterModData(pBackUp, pData);
	return bSuccess;
}

CDataObserverMgr * ClassBase::ObserverMgr() const
{
	return m_pObserverMgr;
}

const CDataBase * ClassBase::GetData(T_KEY nKey) const
{
	return m_pool->GetData(nKey);
}

BOOL ClassBase::GetData(T_KEY nKey, CDataBase *& pData) const
{
	return m_pool->GetData(nKey, pData);
}

BOOL ClassBase::Exist(T_KEY nKey) const
{
	return m_pool->IsExist(nKey);
}

T_KEY ClassBase::GetID() const
{
	return m_nKey;
}

BOOL ClassBase::TestData() const
{
	for (auto it = m_pool->begin(); it != m_pool->end(); it++)
	{
		if (!m_pObserverMgr->NotifyPrint(it->second))
			return FALSE;
	}
	return 0;
}

BOOL ClassBase::OnBeforeAddData(const CDataBase * pData)
{
	return m_pObserverMgr->NotifyBeforeAddData(pData);
}

BOOL ClassBase::OnAfterAddData(const CDataBase * pData)
{
	return m_pObserverMgr->NotifyAfterAddData(pData);
}

BOOL ClassBase::OnBeforeDelData(const CDataBase * pData)
{
	return m_pObserverMgr->NotifyBeforeDelData(pData);
}

BOOL ClassBase::OnAfterDelData(const CDataBase * pData)
{
	return m_pObserverMgr->NotifyAfterDelData(pData);
}

BOOL ClassBase::OnBeforeModData(const CDataBase * pData, const CDataBase * pOldData)
{
	return m_pObserverMgr->NotifyBeforeModData(pData, pOldData);
}

BOOL ClassBase::OnAfterModData(const CDataBase * pData, const CDataBase * pOldData)
{
	return m_pObserverMgr->NotifyAfterModData(pOldData, pOldData);
}

BOOL ClassBase::PrintData(const CDataBase * pData)
{
	return m_pObserverMgr->NotifyPrint(pData);
}
