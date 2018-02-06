#include "stdafx.h"
#include "DBDoc.h"

#include "MatlDB.h"


CMatlDB::CMatlDB(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}


CMatlDB::~CMatlDB()
{
}

void CMatlDB::GetDesignCodeList(const CString & MatlType, CArray<CString, CString&>& DesignCodeList)
{
	DesignCodeList.RemoveAll();
	if (MatlType != "S" && MatlType != "C")ASSERT(FALSE);
	int nCount = (int)m_DesignCodeList.GetSize();
	T_MATL_LIST_DESIGNCODE dcode;
	CString MType;
	for (int i = 0; i < nCount; i++)
	{
		dcode = m_DesignCodeList[0];
		if (GetMatlType(dcode.DesignCode, MType) && MType == MatlType)
			DesignCodeList.Add(dcode.DesignCode);
	}
}

BOOL CMatlDB::GetMatlType(const CString & DesignCode, CString & MatlType)
{
	MatlType.Empty();
	return m_MatlType.Lookup(DesignCode, MatlType);
}
