// CMPropertiesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMPropertiesDlg.h"
#include "afxdialogex.h"


#include "CMaterialPage.h"
#include "CMSectionPage.h"

#define CDialog CCMDlgBase

//IMPLEMENT_DYNAMIC(CCMPropertiesDlg, CDialog)

CCMPropertiesDlg::CCMPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_PROPERTIES_DLG, pParent)
{
	m_nActivePage = 0;
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


// CCMPropertiesDlg 消息处理程序


BOOL CCMPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pMaterial = new CCMaterialPage(m_pDoc,this);
	m_pSection = new CCMSectionPage(m_pDoc,this);
	m_wndTab.AddTab(m_pMaterial, _LS(IDS_CMD_PJST_Material), CCMaterialPage::IDD);
	m_wndTab.AddTab(m_pSection, _LS(IDS_CMD_PJST_Section), CCMSectionPage::IDD);
	m_wndTab.SetPlaceHolder(GetDlgItem(IDC_CMD_PLACEHOLDER));
	m_wndTab.ShowTab(m_nActivePage);
	return TRUE; 
}

void CCMPropertiesDlg::OnUpdate(CWnd* pSender, LPARAM lParam, CObject* pHint)
{
	switch (lParam)
	{
	case D_UPDATE_BUFFER_AFTER:
	case D_UPDATE_BUFFER_BEFFORE:
		break;
	default:
		break;
	}
	m_pMaterial->OnUpdate();
	m_pSection->OnUpdate();
}


void CCMPropertiesDlg::OnCancel()
{
	DestroyWindow();
}
