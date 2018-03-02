// CMatPageItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMatPageItemDlg.h"
#include "../BaseLib/DlgUtil.h"

//#include "afxdialogex.h"

#define CCM_TYPE_STEEL  _ULS(S)
#define CCM_TYPE_CONCR  _ULS(C)
#define CCM_TYPE_SRC    _ULS(SRC)
#define CCM_TYPE_USER   _ULS(U)
#define CCM_TYPE_ALUMNI _ULS(A)

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
	m_pBitmap = 0;
	m_bModify = FALSE;

	m_aCtrlThermalConc.Add(IDC_CMD_MP_ITEM_CODE);
	m_aCtrlThermalConc.Add(IDC_CMD_MP_ITEM_CBO);
	m_aCtrlThermalSteel.Add(IDC_CMD_MP_ITEM_CBO2);
	m_aCtrlThermalSteel.Add(IDC_CMD_MP_ITEM_CODE2);
}

CCMatPageItemDlg::~CCMatPageItemDlg()
{
}

void CCMatPageItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_wndID);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_TYPE, m_wndType);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CODE, m_wndSteelCode);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CODE2, m_wndConcrCode);
	DDX_Control(pDX, IDC_CMD_FRAME, m_wndStlCodeFrame);
	
}


BEGIN_MESSAGE_MAP(CCMatPageItemDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_TYPE, &CCMatPageItemDlg::OnChangeType)
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

	m_Key = m_pDoc->m_pAttrCtrl->GetStartNumMatl();
	m_Data.initialize();
	m_Data.Type = CCM_TYPE_STEEL;

	//GetDefaultCode();
	SetTypeCombo();
	
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
	ChangeDlgCtrls();
}

void CCMatPageItemDlg::SetTypeCombo()
{
	CDlgUtil::CobxAddItem(m_wndType, CCM_STEEL, CCM_TYPE_STEEL_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_CONCR, CCM_TYPE_CONCR_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_SRC, CCM_TYPE_SRC_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_ALUMINIUM, CCM_TYPE_ALUMI_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_USER, CCM_TYPE_USER_I);
	CDlgUtil::CobxSetCurSelItemData(m_wndType, CCM_TYPE_STEEL_I);
}

void CCMatPageItemDlg::SetCode(CComboBox* pCombo, const CString & strType)
{
	pCombo->ResetContent();
	CArray<CString, CString&>aDesignCodeList;
	m_pDoc->m_pMatlDB->GetDesignCodeList(strType, aDesignCodeList);
	int nSize = (int)aDesignCodeList.GetSize();
	for (int i = 0; i < nSize; i++)
		pCombo->AddString(aDesignCodeList[i]);
}

void CCMatPageItemDlg::SetSteelCode(int nTypeIndex)
{
	if (nTypeIndex == CCM_TYPE_STEEL_I || nTypeIndex == CCM_TYPE_SRC_I)SetCode(&m_wndConcrCode, CCM_TYPE_STEEL);
	else if (nTypeIndex == CCM_TYPE_ALUMI_I)SetCode(&m_wndConcrCode, CCM_TYPE_ALUMNI);
	else if (nTypeIndex == CCM_TYPE_USER_I)SetCode(&m_wndConcrCode, CCM_TYPE_USER);
	else if (nTypeIndex == CCM_TYPE_CONCR_I)m_wndSteelCode.ResetContent();
	else ASSERT(FALSE);
}

void CCMatPageItemDlg::SetConcrCode(int nTypeIndex)
{
	if (nTypeIndex == CCM_TYPE_CONCR_I || nTypeIndex == CCM_TYPE_SRC_I)SetCode(&m_wndConcrCode, CCM_TYPE_CONCR);
	else if (nTypeIndex == CCM_TYPE_USER_I || nTypeIndex == CCM_TYPE_ALUMI_I || nTypeIndex == CCM_TYPE_STEEL_I)
		m_wndConcrCode.ResetContent();
	else ASSERT(FALSE);
}

void CCMatPageItemDlg::SetFrameName(int nTypeIndex)
{
	CString strTitle = CCM_STEEL;
	if (nTypeIndex == CCM_TYPE_ALUMI_I)
		strTitle = CCM_ALUMINIUM;
	else if (nTypeIndex == CCM_TYPE_USER_I)
		strTitle = CCM_USER;
	m_wndStlCodeFrame.SetWindowTextW(strTitle);
}

void CCMatPageItemDlg::ChangeBitmap(int nBitmap)
{
	UINT aBitmap[] = { IDB_CMD_BITMAP1,IDB_CMD_BITMAP2,IDB_CMD_BITMAP3,IDB_CMD_BITMAP4,IDB_CMD_BITMAP5 };
	if (m_pBitmap) delete m_pBitmap;
	m_pBitmap = new CBitmap;
	CStatic* pImage = (CStatic*)GetDlgItem(IDC_CMD_PICTURE);
	m_pBitmap->LoadBitmap(aBitmap[nBitmap]);
	pImage->SetBitmap(HBITMAP(*m_pBitmap));
}

void CCMatPageItemDlg::ChangeDlgCtrls()
{
	int nTypeIndex = GetTypeIndex(m_Data.Type);
	//m_wndSteelCode.ResetContent();
	SetFrameName(nTypeIndex);
	SetConcrCode(nTypeIndex);
	SetSteelCode(nTypeIndex);
	BOOL bThermalSteel = FALSE;
	BOOL bThermalConc = FALSE;
	if (nTypeIndex == CCM_TYPE_STEEL_I)
	{
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_CONCR_I)
	{
		bThermalConc = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_SRC_I)
	{
		bThermalConc = TRUE;
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_ALUMI_I)
	{
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_USER_I)
	{
		bThermalConc = TRUE;
		bThermalSteel = TRUE;
	}
	else ASSERT(0);
#pragma region 22
	CDlgUtil::CtrlEnableDisable(this, m_aCtrlThermalSteel, bThermalSteel);
	CDlgUtil::CtrlEnableDisable(this, m_aCtrlThermalConc, bThermalConc);
#pragma endregion 22
}

int CCMatPageItemDlg::GetTypeIndex(CString strType) const
{
	if (strType == CCM_TYPE_STEEL) return CCM_TYPE_STEEL_I;
	if (strType == CCM_TYPE_ALUMNI) return CCM_TYPE_ALUMI_I;
	if (strType == CCM_TYPE_CONCR) return CCM_TYPE_CONCR_I;
	if (strType == CCM_TYPE_USER) return CCM_TYPE_USER_I;
	if (strType == CCM_TYPE_SRC) return CCM_TYPE_SRC_I;
	ASSERT(0);
	return 0;
}

CString CCMatPageItemDlg::GetTypeCode(int nTypeIndex) const
{
	if (nTypeIndex == CCM_TYPE_STEEL_I) return CCM_TYPE_STEEL;
	if (nTypeIndex == CCM_TYPE_ALUMI_I) return CCM_TYPE_ALUMNI;
	if (nTypeIndex == CCM_TYPE_CONCR_I) return CCM_TYPE_CONCR;
	if (nTypeIndex == CCM_TYPE_USER_I) return CCM_TYPE_USER;
	if (nTypeIndex == CCM_TYPE_SRC_I) return CCM_TYPE_SRC;
	ASSERT(0);
	return  _T("");
}


void CCMatPageItemDlg::OnChangeType()
{
	DWORD dwType;
	if (!CDlgUtil::CobxGetItemDataByCurSel(m_wndType, dwType))dwType = -1;
	int nTypeIndex = dwType;
	ChangeBitmap(nTypeIndex);
	m_Data.Type = GetTypeCode(nTypeIndex);
	ShowDataToDlg();
}
