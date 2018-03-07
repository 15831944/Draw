#pragma once

class CDB_MATL
{
public:
	CDB_MATL();
	~CDB_MATL();
public:
	T_MATL_K m_nStartNum;
	T_MATL_K m_nLastNum;
public:
	void Add(T_MATL_K Key, T_MATL_D& rData);
	BOOL Get(T_MATL_K Key, T_MATL_D& rData);
	int GetCount();
	void AddDesign(T_MATL_K Key,const T_MATD_D& rData);
	BOOL GetDesign(T_MATL_K Key, T_MATD_D& rData);
	POSITION GetStart() { return m_matl.GetStartPosition(); }
	void GetNext(POSITION& rNextPosition, T_MATL_K& key, T_MATL_D& rData);
private:
	CMap<T_MATL_K, T_MATL_K, T_MATL_D, T_MATL_D&>m_matl;
	CMap<T_MATL_K, T_MATL_K, T_MATD_D, const T_MATD_D&>m_matlDesign;
};

