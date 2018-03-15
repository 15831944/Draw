#pragma once
#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CSectDB
{
	friend class CDBDoc;
public:
	void GetNameList(CArray<CString,CString&>& rarDBNameList);
private:
	CSectDB(CDBDoc* pDoc);
	~CSectDB(void);

	void initialize();
	void MakeSectData();
private:
	CDBDoc* m_pDoc;
	CArray<CString,CString&> m_arSectDBList;
};

#include "HeaderPost.h"