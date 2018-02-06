// CMPropertiesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMPropertiesDlg.h"
#include "afxdialogex.h"


#include "CMaterialPage.h"
#include "CMSectionPage.h"


IMPLEMENT_DYNAMIC(CCMPropertiesDlg, CDialog)

CCMPropertiesDlg::CCMPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_PROPERTIES_DLG, pParent)
{

}

CCMPropertiesDlg::~CCMPropertiesDlg()
{
}

void CCMPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMD_PROP_TAB, m_wndTab);
}

void CCMPropertiesDlg::SetActivePage(int SelectPage)
{
	m_nActivePage = SelectPage;
}


BEGIN_MESSAGE_MAP(CCMPropertiesDlg, CDialog)
END_MESSAGE_MAP()


// CCMPropertiesDlg ��Ϣ�������


BOOL CCMPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pMaterial = new CCMaterialPage(this);
	m_pSection = new CCMSectionPage(this);
	m_wndTab.AddTab(m_pMaterial, _LS(IDS_CMD_PJST_Material), CCMaterialPage::IDD);
	m_wndTab.AddTab(m_pSection, _LS(IDS_CMD_PJST_Section), CCMSectionPage::IDD);
	m_wndTab.SetPlaceHolder(GetDlgItem(IDC_CMD_PLACEHOLDER));
	m_wndTab.ShowTab(m_nActivePage);
	return TRUE; 
}
