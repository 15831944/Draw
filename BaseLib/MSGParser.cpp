#include "stdafx.h"
#include "MSGParser.h"
#define _LINE_BUFFER_SIZE	1024
#define UNREGISTERED_STR	_T("%s : Not Registered String")
using namespace std;
//using namespace std::tr1;
CMSGParser::CMSGParser(void)
{
}


CMSGParser::~CMSGParser(void)
{
}

void CMSGParser::AddPath(LPCTSTR lpszPath)
{
	m_svFile.push_back( file_vect::value_type(lpszPath) );
}

bool CMSGParser::Load()
{
	wchar_t cLine[_LINE_BUFFER_SIZE];
	CStringW line, left, id, temp, value;
	int length,find;
	int size = (int)m_svFile.size();
	for(int i = 0; i < size; i++)
	{
		CString filepath = m_svFile[i];
		FILE* fp;
		_wfopen_s(&fp,CStringW(m_svFile[i]),L"rt,ccs=UNICODE");
		if(fp == NULL)
			continue;
		else
		{
			int nPosd = filepath.ReverseFind('\\');
			CString sPathData = filepath.Mid(nPosd+1, filepath.GetLength());
			while(fgetws(cLine,_LINE_BUFFER_SIZE,fp))
			{
				line.Format(L"%s",cLine);
				line.Trim();//È¥µô/n
				if( line != L"" && line[0] != L';' && line != L"/*" && line != L"*/")
				{
					left = line.Left( line.Find(L"="));
					find = left.Find(L"/**/");
					id = left;
					length = left.GetLength();
					if( find != -1 )
						id = left.Mid( find+4, length-find-2 );
					id.Trim();
					temp = line.Right( line.GetLength() - id.GetLength()-1 );
					length = temp.GetLength();
					find = temp.Find(L'"');
					int end = temp.ReverseFind(L'"');
					if(end == find) end = temp.GetLength();
					value = temp.Mid( find+1, end - find -1);
					value.Replace(L"\\n",L"\r\n");
					
					CString valComp(value);
					

					if(id.IsEmpty() || value.IsEmpty())
					{
						continue;
					}
					m_smMsg.insert(make_pair((CString)id,(CString)value));
					//m_FilePathMap.insert(make_pair((CString)id,(CString)sPathData));
					//m_msgProj_KR.SetAt(CString(id), i);
				}
			}
			fclose(fp);
		}
	}
	return true;
}

CString CMSGParser::GetValue(const CString& id)
{
	CString rValue = _T("");
	msg_map::iterator pMsg;
	pMsg = m_smMsg.find(id);
	if(pMsg == m_smMsg.end())
		rValue.Format(UNREGISTERED_STR,id);
	else
		rValue = pMsg->second;
	return rValue;
}

void CMSGParser::Clear()
{
	if(m_svFile.size() > 0)m_svFile.clear();
}