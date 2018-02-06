// CMatPageItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMatPageItemDlg.h"
#include "../BaseLib/DlgUtil.h"

//#include "afxdialogex.h"

#define CCM_STEEL       _LS(IDS_WG_CMD__ADDD__Steel)
#define CCM_CONCR       _LS(IDS_WG_CMD__ADDD__Concrete)
#define CCM_SRC         _LS(IDS_WG_CMD__ADDD__SRC)
#define CCM_USER        _LS(IDS_WG_CMD__ADDD__User)
#define CCM_ALUMINIUM   _LS(IDS_WG_CMD__ADDD__Aluminium)

#define CCM_TYPE_STEEL_I  0
#define CCM_TYPE_CONCR_I  1
#define CCM_TYPE_SRC_I    2
#define CCM_TYPE_ALUMI_I  3
#define CCM_TYPE_USER_I   4

IMPLEMENT_DYNAMIC(CCMatPageItemDlg, CDialog)

CCMatPageItemDlg::CCMatPageItemDlg(CDBDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_MP_ITEM_DLG, pParent)
{
	m_pDoc = pDoc;
	m_bModify = FALSE;
}

CCMatPageItemDlg::~CCMatPageItemDlg()
{
}

void CCMatPageItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_wndID);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CODE, m_wndType);
}


BEGIN_MESSAGE_MAP(CCMatPageItemDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_CODE, &CCMatPageItemDlg::OnChangeType)
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
	//GetDefaultCode();
	SetTypeCombo();
	m_Key = m_pDoc->m_pAttrCtrl->GetStartNumMatl();
	ShowDataToDlg();
	return TRUE;  
}

void CCMatPageItemDlg::GetDefaultCode()
{
	CArray<CString, CString&> aConcrCodeList;
	m_pDoc->m_pMatlDB->GetDesignCodeList(CString("C"), aConcrCodeList);
}

void CCMatPageItemDlg::ShowDataToDlg()
{
	CString csValue;
	csValue.Format(_T("%d"), m_Key);
	m_wndID.SetWindowTextW(csValue);
}

void CCMatPageItemDlg::SetTypeCombo()
{
	CDlgUtil::CobxAddItem(m_wndType, CCM_STEEL, CCM_TYPE_SRC_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_CONCR, CCM_TYPE_CONCR_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_SRC, CCM_TYPE_SRC_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_ALUMINIUM, CCM_TYPE_ALUMI_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_USER, CCM_TYPE_USER_I);
	CDlgUtil::CobxSetCurSelItemData(m_wndType, CCM_TYPE_SRC_I);
}


void CCMatPageItemDlg::OnChangeType()
{
	// TODO: 在此添加控件通知处理程序代码
}
