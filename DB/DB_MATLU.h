#pragma once
#include <afxtempl.h>
#include "DB_ST_DT.h"
class CDB_MATLU
{
public:
	CDB_MATLU() { m_matl.InitHashTable(HASHSIZEMATL); }
	~CDB_MATLU() {}
public:
	void Add(T_UDRD_KEY Key, T_MATL_UDRD_D& rData) { m_matl.SetAt(Key, rData); }
	BOOL Get(T_UDRD_KEY Key, T_MATL_UDRD_D& rData) { return m_matl.Lookup(Key, rData); }
	int GetCount() { return static_cast<int>(m_matl.GetCount()); }
	void AddDesign(T_UDRD_KEY Key, const T_MATD_UDRD_D& rData) { m_matlDesign.SetAt(Key, rData); }
	BOOL GetDesign(T_UDRD_KEY Key, T_MATD_UDRD_D& rData) { return m_matlDesign.Lookup(Key, rData); }
	//POSITION GetStart() { return m_matl.GetStartPosition(); }
	//void GetNext(POSITION& rNextPosition, T_MATL_K& key, T_MATL_D& rData);
private:
	CMap<T_UDRD_KEY, T_UDRD_KEY, T_MATL_UDRD_D, T_MATL_UDRD_D&>m_matl;
	CMap<T_UDRD_KEY, T_UDRD_KEY, T_MATD_UDRD_D, const T_MATD_UDRD_D&>m_matlDesign;
};

