#pragma once
#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CSectDB
{
	friend class CDBDoc;
public:
	void GetNameList(CArray<CString,CString&>& rarDBNameList);
	void GetSectNameList(const CString& strName,const CString& strShape,CArray<CString,CString&>& rarSectNameList);
	void GetSectData(const CString& strSectName,T_SECT_SECTBASE_D& pSect);
	BOOL GetSectData_Org(const CString& strDBName,const CString& strSectName,T_SECT_SECTBASE_D& pSect);
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
	struct T_SECT_FILE_SDATA
	{
		float Size[8];
		float AREA; float ASY; float ASZ;
		float RXX; float RYY; float RZZ;
		float QYB; float QZB;
		float CYP; float CYM; float CZP; float CZM;
		float BUILT; float PERIOUT; float YBAR; float ZBAR;
		float SYY; float SZZ; float ZYY; float ZZZ;
		float ROY; float ROZ; float CWP; float TANA;
		float ROP; float XO; float RO; float BETA;
		float PERIIN; float RES2;
		void Initialize()
		{
			memset(Size, 0, sizeof(T_SECT_FILE_SDATA));
		}
	};
private:
	void GetRegisteredDBName(CArray<CString,CString&>& rarDBName);
	BOOL ReadDBHead(CString strDBName,CArray<T_SECT_NAME,T_SECT_NAME&>& NameArray);
	BOOL ReadDBHead(CString strDBName,unsigned int nFilePoint,T_SECT_FILE_SDATA& rSectData);
	void MakeFullPath(CString& strDBName);
};

#include "HeaderPost.h"