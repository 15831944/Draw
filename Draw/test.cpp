#include "stdafx.h"
#include "test.h"

CTest::CTest(const T_KEY nKey) :CDataBase(nKey)
{
}

CTest::CTest(const T_KEY nKey, int nData):CDataBase(nKey)
{
	//m_nKey = nKey;
	m_nData = nData;
}

CTest * CTest::Duplicate() const
{
	return new CTest(*this);
}
