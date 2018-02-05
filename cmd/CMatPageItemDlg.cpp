// CMatPageItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CMatPageItemDlg.h"
#include "afxdialogex.h"


// CCMatPageItemDlg 对话框

IMPLEMENT_DYNAMIC(CCMatPageItemDlg, CDialog)

CCMatPageItemDlg::CCMatPageItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_MP_ITEM_DLG, pParent)
{
	m_bModify = FALSE;
}

CCMatPageItemDlg::~CCMatPageItemDlg()
{
}

void CCMatPageItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCMatPageItemDlg, CDialog)
END_MESSAGE_MAP()


// CCMatPageItemDlg 消息处理程序


void CCMatPageItemDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}


void CCMatPageItemDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}


BOOL CCMatPageItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  
}
