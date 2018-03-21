#include "stdafx.h"
#include "SectDB.h"
#include "DBDoc.h"

void CSectDB::GetNameList(CArray<CString, CString &>& rarDBNameList)
{
	rarDBNameList.RemoveAll();
	rarDBNameList.Copy(m_arSectDBList);
}
void CSectDB::GetSectNameList(const CString& strName,const CString& strShape,CArray<CString, CString &>& rarSectNameList)
{
	rarSectNameList.RemoveAll();
	int nDBName=static_cast<int>(m_arSectDBList.GetSize());
	for(int i = 0;i<nDBName;i++)
	{
		if(strName == m_arSectDBList[i])
		{
			PNAMELIST pNameList = m_arSectDBNameList[i];
			int nCount = static_cast<int>(pNameList->GetSize());
			for(int j = 0;j<nCount;j++)
				if(pNameList->GetAt(j).SectShape == strShape)
				{
					//CString strjjj = pNameList->GetAt(j).SectName;
					rarSectNameList.Add(pNameList->GetAt(j).SectName);
				}
		}
	}
}
void CSectDB::GetSectData(const CString& strSectName,T_SECT_SECTBASE_D& pSect)
{

}
BOOL CSectDB::GetSectData_Org(const CString& strDBName,const CString& strSectName,T_SECT_SECTBASE_D& rSect)
{
	rSect.initialize();
	int nDBName = static_cast<int>(m_arSectDBList.GetSize());
	PNAMELIST parSectNameList = 0;
	for(int i = 0;i<nDBName;i++)
	{
		if(strDBName.CompareNoCase(m_arSectDBList[i]) == 0 && m_arSectDBNameList[i] != NULL)
		{
			parSectNameList = m_arSectDBNameList[i];
		}
	}
	int nCount = static_cast<int>(parSectNameList->GetSize());
	T_SECT_FILE_SDATA SData;
	for(int i = 0;i<nCount;i++)
	{
		CString tmpName = parSectNameList->GetAt(i).SectName;
		if(tmpName == strSectName)
		{
			ReadDBHead(strDBName,parSectNameList->GetAt(i).nFilePoint,SData);
			rSect.DBName = strSectName;
			rSect.SName = parSectNameList->GetAt(i).SectName;
			rSect.Shape = parSectNameList->GetAt(i).SectShape;
			int nArraySize = sizeof(SData.Size)/sizeof(float);
			for(int i = 0;i<nArraySize;i++)
				rSect.dSize[i] = SData.Size[i];
			rSect.BuiltUpFlag = D_SECT_BUILT_BUILTUP;
			if(SData.BUILT == 0)rSect.BuiltUpFlag = D_SECT_BUILT_ROLLED;
			return TRUE; 
		}
	}
	return FALSE;
}


CSectDB::CSectDB(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
	m_strSectShape[0] = D_SECT_SHAPE_REG_L_S;
	m_strSectShape[1] = D_SECT_SHAPE_REG_C_S;
	m_strSectShape[2] = D_SECT_SHAPE_REG_H_S;
	m_strSectShape[3] = D_SECT_SHAPE_REG_T_S;
	m_strSectShape[4] = D_SECT_SHAPE_REG_B_S;
	m_strSectShape[5] = D_SECT_SHAPE_REG_P_S;
	m_strSectShape[6] = D_SECT_SHAPE_REG_2L_S;
	m_strSectShape[7] = D_SECT_SHAPE_REG_2C_S;
	m_strSectShape[8] = D_SECT_SHAPE_REG_SB_S;
	m_strSectShape[9] = D_SECT_SHAPE_REG_SR_S;
	for(int i =10;i<25;i++)
		m_strSectShape[i] = _T("111");
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
		PNAMELIST pNameList= new CArray<T_SECT_NAME, T_SECT_NAME &>;
		m_arSectDBNameList.Add(pNameList);
		ReadDBHead(m_arSectDBList[i],*pNameList);
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
BOOL CSectDB::ReadDBHead(CString strDBName,CArray<T_SECT_NAME, T_SECT_NAME &>& NameArray)
{
	MakeFullPath(strDBName);
	NameArray.RemoveAll();
	T_SECT_NAME SectName;
	T_SECT_FILE_HEAD DBHead;
	T_SECT_FILE_NAME DBSName;
	BOOL bError = FALSE;
	TRY 
	{
		unsigned int nByte,nSeekByte,nResultByte;
		unsigned int nRecSize1 = 608,nRecSize2 = 32,nRecSize3 = 38*4;
		CFile File(strDBName,CFile::modeRead | CFile::typeBinary);
		nByte = File.Read(&DBHead,sizeof(DBHead));
		if(memcmp(DBHead.FileID, "MDSW-SDB", 8) || DBHead.VERHIGH != 2 || DBHead.VERLOW !=0)
			return bError;
		unsigned int nTotalRecord = (unsigned int)DBHead.NTSREC;
		for(unsigned int i = 0;i<nTotalRecord;i++)
		{
			nSeekByte = i*nRecSize1;
			nResultByte = (unsigned int)File.Seek(nSeekByte,CFile::begin);
			nByte = File.Read(&DBHead,sizeof(DBHead));
			int nStart = (int)DBHead.NSTREC;
			int nEnd = (int)DBHead.NENREC;
			for(int j = nStart;j<=nEnd;j++)
			{
				nSeekByte = i*nRecSize1+(j-1)*nRecSize2;
				nResultByte = (unsigned int)File.Seek(nSeekByte,CFile::begin);
				nByte = File.Read(&DBSName,sizeof(DBSName));
				ConverCharStr(DBSName.NAME,SectName.SectName,sizeof(DBSName.NAME));
				SectName.SectShape = m_strSectShape[DBSName.SHAPE_ID - 1];
				if(SectName.SectShape == _T("SR"))
				{
					break;
				}
				SectName.nFilePoint = (DBSName.NREC - 1)*nRecSize1+(DBSName.NOFFSET - 1)*nRecSize3;
				NameArray.Add(SectName);
			}
		}
	}
	CATCH (CFileException, e)
	{
		AfxMessageBox(_T("111111"));
		bError = TRUE;
	}
	END_CATCH
		return !bError;
}
BOOL CSectDB::ReadDBHead(CString strDBName,unsigned int nFilePoint,T_SECT_FILE_SDATA& rSectData)
{
	MakeFullPath(strDBName);
	BOOL bError = FALSE;
	TRY 
	{
		unsigned int nByte,nResultByte;
		CFile File(strDBName,CFile::modeRead | CFile::typeBinary);
		nResultByte = (unsigned int)File.Seek(nFilePoint,CFile::begin);
		nByte = File.Read(&rSectData,sizeof(rSectData));
		File.Close();
	}
	CATCH (CFileException, e)
	{
		AfxMessageBox(_T("111111"));
		bError = TRUE;
	}
	END_CATCH
		return !bError;
}
void CSectDB::MakeFullPath(CString& strDBName)
{
	strDBName = m_pDoc->GetProgramPath()+_T("DBASE\\")+strDBName+_T(".SDB");
}