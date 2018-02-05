#include "stdafx.h"
#include "DataObserver.h"


BOOL CDataObserverMgr::NotifyBeforeAddData(const CDataBase * pData)
{
	return NotifyCmdData(1, pData);
}

BOOL CDataObserverMgr::NotifyAfterAddData(const CDataBase * pData)
{
	return NotifyCmdData(2, pData);
}

BOOL CDataObserverMgr::NotifyBeforeDelData(const CDataBase * pData)
{
	return NotifyCmdData(3, pData);
}

BOOL CDataObserverMgr::NotifyAfterDelData(const CDataBase * pData)
{
	return NotifyCmdData(4, pData);
}

BOOL CDataObserverMgr::NotifyBeforeModData(const CDataBase * pNewData, const CDataBase * pOldData)
{
	return NotifyCmdData(5, pNewData,pOldData);
}

BOOL CDataObserverMgr::NotifyAfterModData(const CDataBase * pNewData, const CDataBase * pOldData)
{
	return NotifyCmdData(6, pNewData, pOldData);
}

BOOL CDataObserverMgr::NotifyPrint(const CDataBase * pData)
{
	return NotifyCmdData(7, pData);
}

BOOL CDataObserverMgr::NotifyCmdData(int nCmd, const CDataBase * pNewData, const CDataBase * pOldData)
{
	for (size_t i = 0; i < getsize(); i++)
	{
		auto Observer = dynamic_cast<CDataObserver*>(getObserver(i));
		if(Observer == nullptr)
			continue;
		switch (nCmd)
		{
		case 1:
			if (!Observer->OnBeforeAddData(pNewData))
				return FALSE;
			break;
		case 2:
			if (!Observer->OnAfterAddData(pNewData))
				return FALSE;
			break;
		case 3:
			if (!Observer->OnBeforeDelData(pNewData))
				return FALSE;
			break;
		case 4:
			if (!Observer->OnAfterDelData(pNewData))
				return FALSE;
			break;
		case 5:
			if (!Observer->OnBeforeModData(pNewData, pOldData))
				return FALSE;
			break;
		case 6:
			if (!Observer->OnAfterModData(pNewData, pOldData))
				return FALSE;
			break;
		case 7:
			if (!Observer->PrintData(pNewData))
				return FALSE;
			break;
		default:
			break;
		}
		
	}
	return TRUE;
}

BOOL CDataObserver::OnBeforeAddData(const CDataBase * pData)
{
	return TRUE;
}

BOOL CDataObserver::OnAfterAddData(const CDataBase * pData)
{
	return TRUE;
}

BOOL CDataObserver::OnBeforeDelData(const CDataBase * pData)
{
	return TRUE;
}

BOOL CDataObserver::OnAfterDelData(const CDataBase * pData)
{
	return TRUE;
}

BOOL CDataObserver::OnBeforeModData(const CDataBase * pNewData, const CDataBase * pOldData)
{
	return TRUE;
}

BOOL CDataObserver::OnAfterModData(const CDataBase * pNewData, const CDataBase * pOlddata)
{
	return TRUE;
}

BOOL CDataObserver::PrintData(const CDataBase* pData)
{
	return TRUE;
}
