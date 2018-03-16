#pragma once
#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CSectDB
{
	friend class CDBDoc;
public:
	void GetNameList(CArray<CString,CString&>& rarDBNameList);
	void GetSectNameList(const CString& strShape,CArray<CString,CString&>& rarSectNameList);
private:
	CSectDB(CDBDoc* pDoc);
	~CSectDB(void);

	void initialize();
	void MakeSectData();

private:
	CDBDoc* m_pDoc;
	CArray<CString,CString&> m_arSectDBList;
	struct T_SECT_NAME
	{
		CString SectName;
	};
private:
	void GetRegisteredDBName(CArray<CString,CString&>& rarDBName);
	void ReadDBHead(CString strDBName,CArray<T_SECT_NAME,T_SECT_NAME&>& NameArray);
	void MakeFullPath(CString& strDBName);
};

#include "HeaderPost.h"