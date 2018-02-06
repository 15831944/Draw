#pragma once


#include "Observer.h"
#include "DataBase.h"
#include "HeaderPre.h"


class __MY_EXT_CLASS__ CDataObserver : public CObserver
{
public:
	virtual BOOL OnBeforeAddData(const CDataBase* pData);
	virtual BOOL OnAfterAddData(const CDataBase* pData);
	virtual BOOL OnBeforeDelData(const CDataBase* pData);
	virtual BOOL OnAfterDelData(const CDataBase* pData);
	virtual BOOL OnBeforeModData(const CDataBase* pNewData,const CDataBase* pOldData);
	virtual BOOL OnAfterModData(const CDataBase* pNewData,const CDataBase* pOlddata);
	virtual BOOL PrintData(const CDataBase* pData);
};
class __MY_EXT_CLASS__ CDataObserverMgr : public CObserverMgr
{
public:
	BOOL NotifyBeforeAddData(const CDataBase* pData);
	BOOL NotifyAfterAddData(const CDataBase* pData);
	BOOL NotifyBeforeDelData(const CDataBase* pData);
	BOOL NotifyAfterDelData(const CDataBase* pData);
	BOOL NotifyBeforeModData(const CDataBase* pNewData,const CDataBase* pOldData);
	BOOL NotifyAfterModData(const CDataBase* pNewData,const CDataBase* pOldData);
	BOOL NotifyPrint(const CDataBase* pData);
private:
	BOOL NotifyCmdData(int nCmd, const CDataBase* pNewData, const CDataBase* pOldData = nullptr);
};
#include "HeaderPost.h"
