#pragma once
class CDB_SECT
{
public:
	CDB_SECT();
	~CDB_SECT();
public:
	T_SECT_K m_nStartNum;
	T_SECT_K m_nLastNum;
public:
	void Add(T_SECT_K Key, T_SECT_D& rData);
	BOOL Get(T_SECT_K Key, T_SECT_D& rData);
	BOOL Del(T_SECT_K Key);
	int GetCount();
	//void AddDesign(T_SECT_K Key,const T_MATD_D& rData);
	//BOOL GetDesign(T_SECT_K Key, T_MATD_D& rData);
	//POSITION GetStart() { return m_matl.GetStartPosition(); }
	//void GetNext(POSITION& rNextPosition, T_SECT_K& key, T_SECT_D& rData);
private:
	CMap<T_SECT_K, T_SECT_K, T_SECT_D, T_SECT_D&>m_sect;
};

