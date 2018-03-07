#include "stdafx.h"
#include "ModelessDlgCtrl.h"

CModelessDlgCtrl::CModelessDlgCtrl()
{
}

CModelessDlgCtrl::~CModelessDlgCtrl()
{
}

void CModelessDlgCtrl::Add(UINT nIDTemplate, CDialog* pDlg)
{
	SDlgCtrlNode tmp;
	tmp.nIDTemplate = nIDTemplate;
	tmp.pDlg = pDlg;
	m_aDlgList.Add(tmp);
}

void CModelessDlgCtrl::UpdateAllDlgs(CWnd* pWnd, LPARAM lHint, CObject* pHint)
{
	if (m_aDlgList.GetSize() <= 0)return;
	SDlgCtrlUpdateArg param;
	param.pSender = pWnd;
	param.lHint = lHint;
	param.pHint = pHint;
	WPARAM wParam = 0;
	LPARAM lParam;
	lParam = (LPARAM)(&lParam);
	for (int i = 0; i < m_aDlgList.GetSize(); i++)
		m_aDlgList[i].pDlg->SendMessage(WM_UPDATE_MODELESS_DLG,wParam, lParam);
}