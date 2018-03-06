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

void CMatlDB::GetSteelNameList(const CString& csCode, CArray<CString, CString &>& SteelNameList)
{
	SteelNameList.RemoveAll();
	T_MATL_LIST_STEEL SteelList;
	for (int i = 0; i < m_SteelData.GetCount(); i++)
	{
		SteelList = m_SteelData[i];
		if (csCode == SteelList.CodeName)SteelNameList.Add(SteelList.MatlName);
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

#pragma region InitSteel Matl
	GetSteelList_JGJ2015(m_SteelData);
#pragma endregion InitSteel Matl
}

int CMatlDB::GetSteelList_JGJ2015(OUT CArray<T_MATL_LIST_STEEL, T_MATL_LIST_STEEL&> &raSteelList)
{
	T_MATL_LIST_STEEL SteelList;
	SteelList.CodeName = _T("JGJ2015(S)");

	const int nSTL = 5;
	CString STL_Name[nSTL] = { _T("Q235"), _T("Q345"), _T("Q390"), _T("Q420"), _T("Q345GJ") };
	double  STL_Fu[nSTL] = { 370.0,  470.0,  490.0,  520.0,  490.0 };
	double  STL_Fy1[nSTL] = { 235.0,  345.0,  390.0,  420.0,  345.0 };
	double	STL_Fy2[nSTL] = { 225.0,  335.0,  370.0,  400.0,  335.0 };
	double	STL_Fy3[nSTL] = { 215.0,  325.0,  350.0,  380.0,  335.0 };
	double	STL_Fy4[nSTL] = { 215.0,  315.0,	330.0,  360.0,  335.0 };
	double	STL_Fy5[nSTL] = { 215.0,  305.0,  330.0,  360.0,  335.0 };

	for (int i = 0; i < nSTL; ++i)
	{
		SteelList.MatlName = STL_Name[i];
		SteelList.Steel.S_Fu = STL_Fu[i];
		SteelList.Steel.S_Fy1 = STL_Fy1[i];
		SteelList.Steel.S_Fy2 = STL_Fy2[i];
		SteelList.Steel.S_Fy3 = STL_Fy3[i];
		SteelList.Steel.S_Fy4 = STL_Fy4[i];
		SteelList.Steel.S_Fy5 = STL_Fy5[i];
		raSteelList.Add(SteelList);
	}

	return nSTL;
}
