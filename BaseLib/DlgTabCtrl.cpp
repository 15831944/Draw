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
	if (m_nCurTab >= 0) CloseCurTab();
	SetCurSel(nPos);
	OpenNewTab();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CDlgTabCtrl::OnTcnSelchange)
	END_MESSAGE_MAP()

BOOL CDlgTabCtrl::SetPlaceHolder(CWnd * pPlaceHolder, BOOL bResize)
{
	ASSERT(pPlaceHolder);
	pPlaceHolder->ShowWindow(SW_HIDE);
	m_pPlaceHolderWnd = pPlaceHolder;
	m_pPlaceHolderWnd->GetWindowRect(&m_rPlaceHolder);
	ScreenToClient(&m_rPlaceHolder);
	return 0;
}

int CDlgTabCtrl::AddTab(CDialog* pDlg,LPCTSTR szTabName,UINT nIDD)
{
	int nTabCount = static_cast<int>(m_aDialog.GetSize());
	TC_ITEM item;
	memset(&item,0,sizeof(TC_ITEM));
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.pszText = (LPSTR)szTabName;
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
	CDialog* pDialog;
	if (m_nCurTab < 0 || m_nCurTab >= m_aDialog.GetSize())return;
	pDialog = m_aDialog[m_nCurTab];
	if (!pDialog || !pDialog->GetSafeHwnd() || !IsWindow(pDialog->GetSafeHwnd()))
	{
		m_nCurTab = -1;
		return;
	}
	pDialog->UpdateData(TRUE);
	pDialog->SendMessage(WM_CDLGTABCTRL_INACTIVE_TAB);
	pDialog->DestroyWindow();
	m_nCurTab = -1;
}

void CDlgTabCtrl::OpenNewTab()
{
	CRect rect,rectDlg;
	GetDialogPos(rect);
	m_nCurTab = GetCurSel();
	TC_ITEM item;
	memset(&item,0,sizeof(TC_ITEM));
	item.mask = TCIF_TEXT | TCIF_PARAM;
	GetItem(m_nCurTab,&item);
	CDialog* pDialog;
	pDialog = m_aDialog[m_nCurTab];
	pDialog->Create((UINT)item.lParam, this);
	pDialog->MoveWindow(rect);
	pDialog->UpdateData(FALSE);
	pDialog->ShowWindow(SW_SHOW);
	pDialog->SendMessage(WM_CDLGTABCTRL_ACTIVE_TAB);
}

void CDlgTabCtrl::GetDialogPos(CRect & rect)
{
	/*GetClientRect(rect);
	rect.top += 30;
	rect.left += 10;
	rect.bottom -= 10;
	rect.right -= 10;*/
	rect = m_rPlaceHolder;
}
