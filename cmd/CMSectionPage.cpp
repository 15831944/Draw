// CMSectionPage.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMSectionPage.h"
#include "afxdialogex.h"
#include "CMSectPageItemDlg.h"

// CCMSectionPage 对话框

IMPLEMENT_DYNAMIC(CCMSectionPage, CDialog)

CCMSectionPage::CCMSectionPage(CDBDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_SECTION_PAGE, pParent)
{
	m_pDoc = pDoc;
}
CCMSectionPage::~CCMSectionPage()
{
}
void CCMSectionPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CMD_SP_PREVIEW, m_wndSectView);
	DDX_Control(pDX, IDC_CMD_SP_SEC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CCMSectionPage, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CMD_SP_SEC_LIST, &CCMSectionPage::OnItemchanged)
	ON_BN_CLICKED(IDC_CMD_SP_BTN_ADD, &CCMSectionPage::OnAdd)
END_MESSAGE_MAP()

// CCMSectionPage 消息处理程序
BOOL CCMSectionPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWnd* pWnd = GetDlgItem(IDC_CMD_SP_PREVIEW);
	m_wndSectView.Init(pWnd);

	return TRUE;
}
void CCMSectionPage::OnAdd()
{
	CCMSectPageItemDlg dlg(m_pDoc);
	dlg.DoModal();
}

void CCMSectionPage::OnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iItem = m_List.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
	if(iItem == -1)
		m_Data.initialize();
	else
	{
		//m_Key = _wtol(m_List.GetItemText(iItem,0));
		m_Key = _ttoi(m_List.GetItemText(iItem,0));
	}
	//m_wndSectView.SetDataSource(&m_Data);
	//m_wndSectView.Invalidate();
}
void CCMSectionPage::OnUpdate()
{

}

BOOL CCMSectionPage::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_ESCAPE)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
