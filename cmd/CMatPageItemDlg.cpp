// CMatPageItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMatPageItemDlg.h"
#include "afxdialogex.h"


// CCMatPageItemDlg �Ի���

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


// CCMatPageItemDlg ��Ϣ�������


void CCMatPageItemDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}


void CCMatPageItemDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}


BOOL CCMatPageItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  
}
