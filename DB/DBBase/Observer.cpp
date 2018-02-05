#include "stdafx.h"
#include "Observer.h"

CObserver::CObserver()
{
}

CObserver::~CObserver()
{
}

void CObserverMgr::Add(CObserver * pData)
{
	m_pObserver.push_back(pData);
}

size_t CObserverMgr::getsize() const
{
	return m_pObserver.size();
}

CObserver * CObserverMgr::getObserver(size_t i)
{
	return m_pObserver[i];
}
