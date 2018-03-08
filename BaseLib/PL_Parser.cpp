#include "stdafx.h"
#include "PL_Parser.h"
using namespace mit;
using namespace mit::lib;

Parser::Parser()
{
	m_nValue = 0;
}

Parser::~Parser()
{

}

BOOL Parser::ParsingINumberArg(CString str)
{
	CString strTemp = str.SpanIncluding(_T("0123456789"));
	BOOL bRet = str.GetLength() == strTemp.GetLength();
	if (bRet)
		m_nValue = _ttoi(str);
	return bRet;
}

BOOL Parser::GetINumberData(int& Data)
{
	Data = m_nValue;
	return Data;
}

MyParser::MyParser()
{
	m_pParser = new Parser;
}

MyParser::~MyParser()
{
	delete m_pParser;
}

BOOL MyParser::ParsingINumberArg(CString str)
{
	return m_pParser->ParsingINumberArg(str);
}

BOOL MyParser::GetINumberData(int& Data)
{
	return m_pParser->GetINumberData(Data);
}