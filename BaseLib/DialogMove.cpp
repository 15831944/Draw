#include "stdafx.h"
#include "DialogMove.h"
CDialogMove::CDialogMove(UINT nResID, CWnd* pParent)
	:CDialog(nResID,pParent)
{
	m_nInitPos = D_INIT_POS_DEF;
	m_nLeftMargin = 0;
	m_nTopMargin = 0;
}

CDialogMove::~CDialogMove() {}

void CDialogMove::SetInitPos(ENUM_CDIALOG_MOVE nPos /* = D_INIT_POS_DEF */, int nLeftMargin /* = 0 */, int nTopMargin /* = 0 */)
{
	m_nInitPos = nPos;
	m_nLeftMargin = nLeftMargin;
	m_nTopMargin = nTopMargin;
}

void CDialogMove::MoveDlgToInitPos()
{
	CWnd* pParent = GetParent();
	//if (!pParent) pParent = AfxGetMainWnd();
	//if (!pParent || !pParent->GetSafeHwnd()
	//	|| !IsWindow(pParent->GetSafeHwnd())) return;
	if (m_nInitPos == D_INIT_POS_DEF)return;
	CRect rtDlg, rtParent;
	int w, h;
	GetWindowRect(rtDlg);
	pParent->GetWindowRect(rtParent);
	w = rtDlg.Width();
	h = rtDlg.Height();
	switch (m_nInitPos)
	{
	case D_INIT_POS_LT://left top
		rtDlg.left = rtParent.left + m_nLeftMargin;
		rtDlg.top = rtParent.top + m_nTopMargin;
		rtDlg.right = rtDlg.left + w;
		rtDlg.bottom = rtDlg.top + h;
		break;
	case D_INIT_POS_LB://left bottom
		rtDlg.left = rtParent.left + m_nLeftMargin;
		rtDlg.bottom = rtParent.bottom + m_nTopMargin;
		rtDlg.right = rtDlg.left + w;
		rtDlg.top = rtDlg.bottom - h;
		break;
	case D_INIT_POS_RT://right top
		rtDlg.left = rtParent.right + m_nLeftMargin;
		rtDlg.top = rtParent.top + m_nTopMargin;
		rtDlg.right = rtDlg.left + w;
		rtDlg.bottom = rtDlg.top + h;
		break;
	case D_INIT_POS_RB://right bottom
		rtDlg.left = rtParent.right + m_nLeftMargin;
		rtDlg.bottom = rtParent.bottom + m_nTopMargin;
		rtDlg.right = rtDlg.left + w;
		rtDlg.top = rtDlg.bottom - h;
		break;
	}
	/*if (rtDlg.left < 0)rtDlg.left = 0;
	if (rtDlg.top < 0)rtDlg.top = 0;*/
	MoveWindow(rtDlg);
}

BOOL CDialogMove::OnInitDialog()
{
	CDialog::OnInitDialog();
	MoveDlgToInitPos();
	return TRUE;
}
