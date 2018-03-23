#include "stdafx.h"
#include "resource.h"
#include "CMStiffDlg.h"
#include "afxdialogex.h"
#include "../DB/DBDoc.h"


#pragma region CCMSecPageStiffDlgGrid

#pragma endregion CCMSecPageStiffDlgGrid



// CCMStiffDlg ¶Ô»°¿ò
IMPLEMENT_DYNAMIC(CCMStiffDlg, CDialog)
CCMStiffDlg::CCMStiffDlg(CDBDoc* pDoc,T_SECT_D* pData,CWnd* pParent /*=NULL*/)
	: CDialog(CCMStiffDlg::IDD, pParent)
{
	m_pDoc = pDoc;
	m_pData = pData;
}
CCMStiffDlg::~CCMStiffDlg()
{
}
void CCMStiffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CCMStiffDlg, CDialog)
END_MESSAGE_MAP()
BOOL CCMStiffDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_wndGrid.SubclassDlgItem(IDC_CMD_SP_ID_BTN_CALC,this);
	return TRUE;
}
