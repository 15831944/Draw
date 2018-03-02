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
	if (MatlType != "S" && MatlType != "C" && MatlType!= "U" && MatlType != "A")ASSERT(FALSE);
	int nCount = (int)m_DesignCodeList.GetSize();
	T_MATL_LIST_DESIGNCODE dcode;
	CString MType;
	for (int i = 0; i < nCount; i++)
	{
		dcode = m_DesignCodeList[i];
		if (GetMatlType(dcode.DesignCode, MType) && MType == MatlType)
			DesignCodeList.Add(dcode.DesignCode);
	}
}

void CMatlDB::initialize()
{
	MakeMatlData();
}

BOOL CMatlDB::GetMatlType(const CString & DesignCode, CString & MatlType)
{
	MatlType.Empty();
	return m_MatlType.Lookup(DesignCode, MatlType);
}

void CMatlDB::MakeMatlData()
{
	enum 
	{
		is_GB50018_02, is_JGJ2015,
		is_GB,
	};
	const int nDC = 2 + 1 + 0;//Steel+RC+AlU
	CArray<int, int>arSeq;
	arSeq.Add(is_GB50018_02);
	arSeq.Add(is_JGJ2015);
	arSeq.Add(is_GB);
	CString DesignCode[nDC] = 
	{
		_T("GB50018-02(S)"),_T("JGJ2015(S)"),
		_T("GB10(RC)")
	};
	CString MatlType[nDC] = 
	{
		_T("S"),_T("S"),
		_T("C"),
	};
	T_MATL_LIST_DESIGNCODE dcode;
	CString strTemp("");
	if (arSeq.GetSize() > nDC)ASSERT(0);
	for (int i = 0; i < arSeq.GetSize(); i++)
	{
		strTemp = MatlType[arSeq[i]];
		dcode.DesignCode = DesignCode[arSeq[i]];
		dcode.nCodeType = 0;
		m_DesignCodeList.Add(dcode);
		m_MatlType.SetAt(dcode.DesignCode, strTemp);
	}
}
