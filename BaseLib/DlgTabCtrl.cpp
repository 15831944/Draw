#include "stdafx.h"
#include "DlgTabCtrl.h"

UINT CDlgTabCtrl::WM_CDLGTABCTRL_ACTIVE_TAB = RegisterWindowMessage(_T("WM_CDLGTABCTRL_ATCIVE_TAB"));
UINT CDlgTabCtrl::WM_CDLGTABCTRL_INACTIVE_TAB = RegisterWindowMessage(_T("WM_CDLGTABCTRL_INACTIVE_TAB"));
CDlgTabCtrl::CDlgTabCtrl(void)
{
	m_nCurTab = -1;
}


CDlgTabCtrl::~CDlgTabCtrl(void)
{
}

BOOL CDlgTabCtrl::ShowTab(int nPos)
{
	if(nPos < 0 || nPos >= m_aDialog.GetSize())return FALSE;
	//if(m_nCurTab >= 0)
	SetCurSel(nPos);
	OpenNewTab();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CDlgTabCtrl::OnTcnSelchange)
	END_MESSAGE_MAP()

int CDlgTabCtrl::AddTab(CDialog* pDlg,LPCTSTR szTabName,UINT nIDD)
{
	int nTabCount = static_cast<int>(m_aDialog.GetSize());
	TC_ITEM item;
	memset(&item,0,sizeof(TC_ITEM));
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.pszText = (LPWSTR)szTabName;
	item.lParam = (LPARAM)nIDD;
	if(InsertItem(nTabCount,&item) == -1)return -1;
	m_aDialog.Add(pDlg);
	return nTabCount;

}

void CDlgTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	CloseCurTab();
	OpenNewTab();
	*pResult = 0;
}

void CDlgTabCtrl::CloseCurTab()
{
	/*CDialog* pDialog;
	if(m_nCurTab < 0 || m_nCurTab >= m_aDialog.GetSize())return;
	pDialog = m_aDialog[m_nCurTab];*/

}

void CDlgTabCtrl::OpenNewTab()
{
	CRect rect,rectDlg;
	
	m_nCurTab = GetCurSel();
	TC_ITEM item;
	memset(&item,0,sizeof(TC_ITEM));
	item.mask = TCIF_TEXT | TCIF_PARAM;
	GetItem(m_nCurTab,&item);
	CDialog* pDialog;
	pDialog = m_aDialog[m_nCurTab];
	
	pDialog->UpdateData(FALSE);
	pDialog->ShowWindow(SW_SHOW);
	pDialog->SendMessage(WM_CDLGTABCTRL_ACTIVE_TAB);
}