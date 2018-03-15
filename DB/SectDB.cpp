#include "stdafx.h"
#include "SectDB.h"
#include "DBDoc.h"

void CSectDB::GetNameList(CArray<CString, CString &>& rarDBNameList)
{
	rarDBNameList.RemoveAll();
	rarDBNameList.Copy(m_arSectDBList);
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
	CString asDBName[] =
	{
		_T("GB-YB"),
		_T("GB50018-02"),
	};
	m_arSectDBList.RemoveAll();
	m_arSectDBList.Add(asDBName[0]);
	m_arSectDBList.Add(asDBName[1]);
}
