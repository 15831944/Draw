#pragma once



#include "HeaderPre.h"

class __MY_EXT_CLASS__ CDlgTabCtrl : public CTabCtrl
{
public:
	static UINT WM_CDLGTABCTRL_ACTIVE_TAB;
	static UINT WM_CDLGTABCTRL_INACTIVE_TAB;
public:
	CDlgTabCtrl(void);
	~CDlgTabCtrl(void);

private:
	CArray<CDialog*,CDialog*> m_aDialog;
	int m_nCurTab;
	CWnd* m_pPlaceHolderWnd;
	CRect m_rPlaceHolder;
private:
	void CloseCurTab();
	void OpenNewTab();
	void GetDialogPos(CRect& rect);
public:
	BOOL SetPlaceHolder(CWnd* pPlaceHolder, BOOL bResize = TRUE);
	int AddTab(CDialog* pDlg,LPCTSTR szTabName,UINT nIDD);
	BOOL ShowTab(int nPos);
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};
#include "HeaderPost.h"

