#pragma once
typedef UINT T_KEY;
class CTest : public CDataBase
{
public:
	CTest(const T_KEY nKey);
	CTest(const T_KEY nKey,int nData);
	virtual CTest* Duplicate() const;
public:
	int m_nData;

};