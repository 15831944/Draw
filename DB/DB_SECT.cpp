#include "stdafx.h"
#include "DB_SECT.h"


CDB_SECT::CDB_SECT(void)
{
	m_nStartNum = 1;
}


CDB_SECT::~CDB_SECT(void)
{
}
void CDB_SECT::Add(T_SECT_K Key, T_SECT_D& rData)
{
	m_sect.SetAt(Key,rData);
}
BOOL CDB_SECT::Get(T_SECT_K Key, T_SECT_D& rData)
{
	return m_sect.Lookup(Key,rData);
}
BOOL CDB_SECT::Del(T_SECT_K Key)
{
	return m_sect.RemoveKey(Key);
}
int CDB_SECT::GetCount()
{
	return static_cast<int>(m_sect.GetCount());
}