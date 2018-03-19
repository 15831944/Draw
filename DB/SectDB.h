#pragma once
#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CSectDB
{
	friend class CDBDoc;
public:
	void GetNameList(CArray<CString,CString&>& rarDBNameList);
	void GetSectNameList(const CString& strName,const CString& strShape,CArray<CString,CString&>& rarSectNameList);
private:
	CSectDB(CDBDoc* pDoc);
	~CSectDB(void);
	
	void initialize();
	void MakeSectData();

private:
	CDBDoc* m_pDoc;
	CArray<CString,CString&> m_arSectDBList;
	CString m_strSectShape[25];
	struct T_SECT_NAME
	{
		CString SectName;
		CString SectShape;
		unsigned int nFilePoint;
	};
	typedef CArray<T_SECT_NAME,T_SECT_NAME&>* PNAMELIST;
	CArray<PNAMELIST,PNAMELIST&> m_arSectDBNameList;

	struct T_SECT_FILE_HEAD
	{
		char FileID[8];
		short int VERHIGH;
		short int VERLOW;
		short int UNIT;
		short int RESERVED[6];
		short int NTSREC;
		short int NSTREC;
		short int NENREC;
	};
	struct T_SECT_FILE_NAME
	{
		char NAME[24];
		short int SHAPE_ID;
		short int NREC;
		short int NOFFSET ;
		short int RESERVED;
	};
private:
	void GetRegisteredDBName(CArray<CString,CString&>& rarDBName);
	BOOL ReadDBHead(CString strDBName,CArray<T_SECT_NAME,T_SECT_NAME&>& NameArray);
	void MakeFullPath(CString& strDBName);
};

#include "HeaderPost.h"