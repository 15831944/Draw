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
	m_matl.SetAt(Key, rData);
	m_nStartNum++;
}

BOOL CDB_MATL::Get(T_MATL_K Key, T_MATL_D& rData)
{
	BOOL bRet = m_matl.Lookup(Key, rData);
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
