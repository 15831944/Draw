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

private:
	struct T_MATL_LIST_DESIGNCODE
	{
		CString DesignCode;
		int nCodeType;
	};
	CArray<T_MATL_LIST_DESIGNCODE, T_MATL_LIST_DESIGNCODE&>m_DesignCodeList;
	CMap<CString, LPCTSTR, CString, CString&>m_MatlType;


private:
	BOOL GetMatlType(const CString& DesignCode, CString& MatlType);
	CDBDoc* m_pDoc;
};

#include "HeaderPost.h"
