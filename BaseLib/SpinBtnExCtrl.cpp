#include "stdafx.h"
#include "SpinBtnExCtrl.h"
#include "PL_Parser.h"
using namespace mit::lib;
CFormulaEdit::CFormulaEdit()
{

}

CFormulaEdit::~CFormulaEdit()
{

}

BOOL CFormulaEdit::GetEditValue(int& nIntValue)
{
	CString csText;
	GetWindowText(csText);
	csText.TrimLeft(); csText.TrimRight();
	return GetFormulaValue(csText, nIntValue);
}

BOOL CFormulaEdit::GetFormulaValue(const CString& csFormula, int& nIntValue)
{
	MyParser Parser;
	if (Parser.ParsingINumberArg(csFormula))
	{
		Parser.GetINumberData(nIntValue);
	}
	else
	{
		nIntValue = 0;
		return FALSE;
	}
	return TRUE;
}