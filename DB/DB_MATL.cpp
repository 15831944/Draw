#include "stdafx.h"
#include "DB_MATL.h"


CDB_MATL::CDB_MATL()
{
	m_nStartNum = 1;
	m_matlDesign.InitHashTable(HASHSIZEMATL);
}

CDB_MATL::~CDB_MATL()
{
}

void CDB_MATL::AddDesign(T_MATL_K Key, const T_MATD_D& rData)
{
	m_matlDesign.SetAt(Key, rData);
}

BOOL CDB_MATL::GetDesign(T_MATL_K Key, T_MATD_D& rData)
{
	return m_matlDesign.Lookup(Key, rData);
}
