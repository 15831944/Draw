#include "stdafx.h"
#include "MSGInfo.h"
#include "MSGFunction.h"

#define BASELIB			_T("BaseLib")
#define DATAMGR			_T("DataMgr")
#define DRAW			  _T("DRAW")
#define TEST			  _T("TEST")
#define _CTRL			  _T("ctrl_")
#define CMD				  _T("cmd")
#define DB					_T("db")
#define _INI_			  _T(".ini")
const CString strLangRoot = _T("Language\\");
//CMSGInfo* CMSGInfo::m_pInstance = 0;
//using namespace lib;
CMSGInfo::CMSGInfo(void)
{
	_file.clear();
	_file.push_back(file_vect::value_type(BASELIB));
	_file.push_back(file_vect::value_type(DATAMGR));
	_file.push_back(file_vect::value_type(TEST));
	_file.push_back(file_vect::value_type(DRAW));
	_file.push_back(file_vect::value_type(CMD));
	_file.push_back(file_vect::value_type(DB));
	LoadMessage();
}

//CMSGInfo * CMSGInfo::Instance()
//{
//	if (m_pInstance == nullptr)
//		m_pInstance = new CMSGInfo;
//	return m_pInstance;
//}

CMSGInfo::~CMSGInfo(void)
{
	_file.clear();
	CMSGFunction::Clear();
}

void CMSGInfo::LoadMessage()
{
	CString strRoot = GetProgramPath();
	CString strPath = strRoot + strLangRoot;
	int size = (int)_file.size();
	CMSGFunction::Reset();
	CString strCtrl = _CTRL;
	CString strIni = _INI_;
	CString strFileName;
	for(int i=0;i<size;i++)
	{
		strFileName = strPath + strCtrl + _file[i] + strIni;
		CMSGFunction::AddFile(strFileName);
	}
	CMSGFunction::LoadFile();
}

CString CMSGInfo::GetProgramPath()
{
	CString ProgramPath;
	::GetModuleFileName(NULL, ProgramPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	ProgramPath.ReleaseBuffer();
	int nFind=ProgramPath.ReverseFind('\\');
	ASSERT(nFind != -1);
	if(nFind != -1)ProgramPath=ProgramPath.Left(nFind+1);
	/*ProgramPath = ProgramPath.Left(ProgramPath.ReverseFind('\\'));
	ProgramPath = ProgramPath.Left(ProgramPath.ReverseFind('\\'));
	ProgramPath = ProgramPath.Left(ProgramPath.ReverseFind('\\'));
	ProgramPath += _T("\\Debug\\x64\\");*/
	return ProgramPath;
}