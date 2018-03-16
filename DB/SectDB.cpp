#include "stdafx.h"
#include "SectDB.h"
#include "DBDoc.h"

void CSectDB::GetNameList(CArray<CString, CString &>& rarDBNameList)
{
	rarDBNameList.RemoveAll();
	rarDBNameList.Copy(m_arSectDBList);
}
void CSectDB::GetSectNameList(const CString& strShape,CArray<CString, CString &>& rarSectNameList)
{

}


CSectDB::CSectDB(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}
CSectDB::~CSectDB(void)
{
}
void CSectDB::initialize()
{
	MakeSectData();
}
void CSectDB::MakeSectData()
{
	GetRegisteredDBName(m_arSectDBList);
	for(int i = 0;i<m_arSectDBList.GetCount();i++)
	{
		CArray<T_SECT_NAME,T_SECT_NAME&> NameArray;
		ReadDBHead(m_arSectDBList[i],NameArray);
	}
}

void CSectDB::GetRegisteredDBName(CArray<CString, CString &>& rarDBName)
{
	CString asDBName[] =
	{
		_T("GB-YB"),
		_T("GB50018-02"),
	};
	rarDBName.RemoveAll();
	rarDBName.Add(asDBName[0]);
	rarDBName.Add(asDBName[1]);
}
void CSectDB::ReadDBHead(CString strDBName,CArray<T_SECT_NAME, T_SECT_NAME &>& NameArray)
{
	MakeFullPath(strDBName);
	NameArray.RemoveAll();
	TRY 
	{
	}
	CATCH (CFileException, e)
	{
		AfxMessageBox(_T("111111"));
		return;
	}
	END_CATCH
}
void CSectDB::MakeFullPath(CString& strDBName)
{
	strDBName = m_pDoc->GetProgramPath()+_T("DBASE\\")+strDBName+_T(".SDB");
}