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
	static BOOL CobxGetItemDataByCurSel(CComboBox& cobx, DWORD& nItemData);
	static void CtrlShowHide(CWnd* pParent, const CArray<UINT, UINT>& aCtrlID, BOOL bShow);
	static void CtrlEnableDisable(CWnd* pParent, const CArray<UINT, UINT>& aCtrlID, BOOL bShow);
};


#include "HeaderPost.h"
