#pragma once

#include <vector>
#include "../common/HeaderPre.h"

class __MY_EXT_CLASS__ CObserver
{
public:
	CObserver();
	virtual ~CObserver();
//	void test(int i) { m_i = i; }
//	int gettest()const { return m_i; }
//private:
//	int m_i;
};

class __MY_EXT_CLASS__ CObserverMgr
{
public:
	void Add( CObserver*const pData);
	size_t getsize()const;
	CObserver* getObserver(size_t i);
private:
	std::vector<CObserver*> m_pObserver;
};
#include "../common/HeaderPost.h"
