#pragma once
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CMatlDB
{
	friend class CDBDoc;
private:
	CMatlDB(CDBDoc* pDoc);
	~CMatlDB();
public:
	void GetDesignCodeList(const CString& MatlType, CArray<CString, CString&>& DesignCodeList);

	void GetSteelNameList(const CString& csCode, CArray<CString, CString&>& SteelNameList);
private://CDBDoc
	void initialize();
private:
	struct T_MATL_LIST_DESIGNCODE
	{
		CString DesignCode;
		int nCodeType;
	};
	struct T_MATL_LIST_STEEL
	{
		CString CodeName;
		CString MatlName;
		T_MATL_STEEL Steel;
	};
	CArray<T_MATL_LIST_STEEL, T_MATL_LIST_STEEL&> m_SteelData;
	CArray<T_MATL_LIST_DESIGNCODE, T_MATL_LIST_DESIGNCODE&>m_DesignCodeList;
	CMap<CString, LPCTSTR, CString, CString&>m_MatlType;
	CDBDoc* m_pDoc;

private:
	BOOL GetMatlType(const CString& DesignCode, CString& MatlType);
	void MakeMatlData();
private:
	int GetSteelList_JGJ2015(OUT CArray<T_MATL_LIST_STEEL, T_MATL_LIST_STEEL&> &raSteelList);

};

#include "HeaderPost.h"
