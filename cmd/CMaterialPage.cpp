// CMaterialPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "CMaterialPage.h"
#include "afxdialogex.h"
#include "CMatPageItemDlg.h"


// CCMaterialPage �Ի���

IMPLEMENT_DYNAMIC(CCMaterialPage, CDialog)

CCMaterialPage::CCMaterialPage(CDBDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_MATERIAL_PAGE, pParent)
{
	m_pDoc = pDoc;
}

CCMaterialPage::~CCMaterialPage()
{
}

void CCMaterialPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMD_MP_MAT_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCMaterialPage, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_CMD_MP_MAT_LIST, &CCMaterialPage::OnNMDblclkCmdMpMatList)
	ON_BN_CLICKED(IDC_CMD_MP_BTN_MOD, &CCMaterialPage::OnModify)
	ON_BN_CLICKED(IDC_CMD_MP_BTN_ADD, &CCMaterialPage::OnAdd)
	ON_BN_CLICKED(IDC_CMD_MP_BTN_DEL, &CCMaterialPage::OnDelete)
END_MESSAGE_MAP()


// CCMaterialPage ��Ϣ�������


void CCMaterialPage::OnNMDblclkCmdMpMatList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnModify();
	*pResult = 0;
}


void CCMaterialPage::OnModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCMaterialPage::OnAdd()
{
	CCMatPageItemDlg dlg(m_pDoc);
	dlg.DoModal();
}


void CCMaterialPage::OnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
