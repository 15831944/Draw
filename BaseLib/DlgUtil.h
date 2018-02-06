#pragma once
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CDlgUtil
{
public:
	CDlgUtil();
	~CDlgUtil();

public:
	static int CobxAddItem(CComboBox& combox, LPCTSTR lpszName, DWORD nItemData);
	static int CobxSetCurSelItemData(CComboBox& cobo, DWORD nItemData);
};


#include "HeaderPost.h"
