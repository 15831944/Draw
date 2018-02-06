#include "stdafx.h"
#include "DlgUtil.h"


CDlgUtil::CDlgUtil()
{
}


CDlgUtil::~CDlgUtil()
{
}

int CDlgUtil::CobxAddItem(CComboBox & combox, LPCTSTR lpszName, DWORD nItemData)
{
	int nIndex = combox.AddString(lpszName);
	if (nIndex == CB_ERR)return nIndex;
	return combox.SetItemData(nIndex,nItemData);
}

int CDlgUtil::CobxSetCurSelItemData(CComboBox & cobo, DWORD nItemData)
{
	int nCount = cobo.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		if (cobo.GetItemData(i) == nItemData)
		{
			cobo.SetCurSel(i);
			return i;
		}
	}
	cobo.SetCurSel(-1);
	return CB_ERR;
	return 0;
}
