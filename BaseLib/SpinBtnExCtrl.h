#pragma once
#include "HeaderPre.h"
class __MY_EXT_CLASS__ CFormulaEdit : public CEdit
{
public:
	CFormulaEdit();
	~CFormulaEdit();
	BOOL GetEditValue(int& nIntValue);
private:
	static BOOL GetFormulaValue(const CString& csFormula, int& nIntValue);
};





#include "HeaderPost.h"
