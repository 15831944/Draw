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
	void AddDesign(T_MATL_K Key,const T_MATD_D& rData);
	BOOL GetDesign(T_MATL_K Key, T_MATD_D& rData);
private:
	CMap<T_MATL_K, T_MATL_K, T_MATD_D, const T_MATD_D&>m_matlDesign;
};

