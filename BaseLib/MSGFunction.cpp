#include "stdafx.h"
#include "MSGFunction.h"
#include "MSGParser.h"
//using namespace lib;
CMSGParser* pg_parse = NULL;
CMSGFunction::CMSGFunction(void)
{
}


CMSGFunction::~CMSGFunction(void)
{
	if(pg_parse != NULL){delete pg_parse;pg_parse = NULL;}
}

void CMSGFunction::AddFile(LPCTSTR filePath)
{
	//CString strFilePath = filePath;
	pg_parse->AddPath(filePath);
}

bool CMSGFunction::LoadFile()
{
	return pg_parse->Load();
}

CString CMSGFunction::GetValue(LPCTSTR lpszID)
{
	CString strID = lpszID;
	return pg_parse->GetValue( strID );
}

void CMSGFunction::Reset()
{
	if(pg_parse == NULL) pg_parse = new CMSGParser();
	pg_parse->Clear();
}

void CMSGFunction::Clear()
{
	if (pg_parse)
	{
		delete pg_parse;
		pg_parse = nullptr;
	}
}
