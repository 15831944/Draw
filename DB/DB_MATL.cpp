#include "stdafx.h"
#include "DB_MATL.h"


CDB_MATL::CDB_MATL()
{
	m_nStartNum = 1;
	m_matl.InitHashTable(HASHSIZEMATL);
	m_matlDesign.InitHashTable(HASHSIZEMATL);
}

CDB_MATL::~CDB_MATL()
{
}

void CDB_MATL::Add(T_MATL_K Key, T_MATL_D& rData)
{
	T_MATL_D data;
	m_matl.SetAt(Key, rData);
	if (Key == m_nStartNum)
	{
		while (1)
		{
			m_nStartNum++;
			if (!Get(m_nStartNum, data))break;
		}
	}
	//if (Key > m_nStartNum)m_nStartNum = Key;
}

BOOL CDB_MATL::Get(T_MATL_K Key, T_MATL_D& rData)
{
	BOOL bRet = m_matl.Lookup(Key, rData);
	return bRet;
}
BOOL CDB_MATL::Del(T_MATL_K Key)
{
	BOOL bRet = m_matl.RemoveKey(Key);
	if(bRet)
		if(Key < m_nStartNum)
			m_nStartNum = Key;
	return bRet;
}

int CDB_MATL::GetCount()
{
	return (int)m_matl.GetCount();
}

void CDB_MATL::AddDesign(T_MATL_K Key, const T_MATD_D& rData)
{
	m_matlDesign.SetAt(Key, rData);
}

BOOL CDB_MATL::GetDesign(T_MATL_K Key, T_MATD_D& rData)
{
	return m_matlDesign.Lookup(Key, rData);
}

void CDB_MATL::GetNext(POSITION& rNextPosition, T_MATL_K& key, T_MATL_D& rData)
{
	m_matl.GetNextAssoc(rNextPosition, key, rData);
}
