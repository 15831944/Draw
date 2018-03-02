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

BOOL CDlgUtil::CobxGetItemDataByCurSel(CComboBox & cobx, DWORD & nItemData)
{
	int nCurSel = cobx.GetCurSel();
	if (nCurSel == CB_ERR)return FALSE;
	nItemData = (DWORD)cobx.GetItemData(nCurSel);
	return TRUE;
}

void CDlgUtil::CtrlShowHide(CWnd * pParent, const CArray<UINT, UINT>& aCtrlID, BOOL bShow)
{
	CWnd* pWnd;
	for (int i = 0; i < aCtrlID.GetSize(); i++)
	{
		pWnd = pParent->GetDlgItem(aCtrlID[i]);
		if(pWnd == 0 || pWnd->GetSafeHwnd() == 0)
			continue;
		if (bShow)pWnd->ShowWindow(SW_SHOW);
		else pWnd->ShowWindow(SW_HIDE);
	}
}

void CDlgUtil::CtrlEnableDisable(CWnd * pParent, const CArray<UINT, UINT>& aCtrlID, BOOL bShow)
{
	CWnd* pWnd;
	for (int i = 0; i < aCtrlID.GetSize(); i++)
	{
		pWnd = pParent->GetDlgItem(aCtrlID[i]);
		if (pWnd == 0 || pWnd->GetSafeHwnd() == 0)
			continue;
		if (bShow)pWnd->EnableWindow(SW_SHOW);
		else pWnd->EnableWindow(SW_HIDE);
	}
}
