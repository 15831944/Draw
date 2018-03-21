// CMaterialPage.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMaterialPage.h"
#include "afxdialogex.h"
#include "CMatPageItemDlg.h"
#include "../DB/DBDoc.h"
#include "../DB/DataCtrl.h"

#include "../DB/ViewBuff.h"
#include "../BaseLib/CompFunc.h"
#include "../DB/AttrCtrl.h"

// CCMaterialPage 对话框

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

void CCMaterialPage::InsertItem(T_MATL_K Key, const T_MATL_D& rData)
{
	const int COLCOUNT = 5;
	LVITEM lvitem;
	CString str;
	int ItemTemp = m_List.GetItemCount();
	for (int i = 0; i < COLCOUNT; i++)
	{
		lvitem.iItem = ItemTemp;
		lvitem.iSubItem = i;
		str = DataToStr(i, Key, rData);
		lvitem.pszText = str.GetBuffer(0);
		lvitem.mask = LVIF_TEXT;
		if (i == 0)
			ItemTemp = m_List.InsertItem(&lvitem);
		else
			m_List.SetItem(&lvitem);
		str.ReleaseBuffer();
	}
}
void CCMaterialPage::DeleteItem(T_MATL_K Key)
{
	CString str;
	str.Format(_T("%6d"),Key);
	LVFINDINFO FindInfo;
	FindInfo.flags = LVFI_STRING;
	FindInfo.psz = str.GetBuffer(0);
	int nItem = m_List.FindItem(&FindInfo);
	if(nItem != -1)m_List.DeleteItem(nItem);
	str.ReleaseBuffer();
}
// CCMaterialPage 消息处理程序
void CCMaterialPage::OnNMDblclkCmdMpMatList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnModify();
	*pResult = 0;
}

void CCMaterialPage::OnModify()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCMaterialPage::OnAdd()
{
	CCMatPageItemDlg dlg(m_pDoc);
	dlg.SetInitPos(D_INIT_POS_RT);
	dlg.DoModal();
}

void CCMaterialPage::OnDelete()
{
	T_MATL_K Key;
	int item = m_List.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
	Key = _wtol(m_List.GetItemText(item,0));
	m_pDoc->m_pDataCtrl->DelMatl(Key);
}

void CCMaterialPage::OnUpdate()
{
	CViewBuff* pViewBuff = m_pDoc->m_pViewBuff;
	int nCount = pViewBuff->GetCount();
	if (nCount == 0)return;
	ASSERT(nCount == 1);
	T_UDRD_BUFFER buffer_ur;
	POSITION pos = pViewBuff->GetStartBuffer();
	T_MATL_K Key;
	T_MATL_D Data;
	while (pos != NULL)
	{
		buffer_ur = pViewBuff->GetNextBuffer(pos);
		int nCmd = buffer_ur.nCmd;
		int nKey = buffer_ur.nKey;
		pViewBuff->GetMatl(nKey, Key, Data);
		switch (nCmd)
		{
		case UR_MATL_ADD:
			InsertItem(Key, Data);
			break;
		case UR_MATL_DEL:
			DeleteItem(Key);
			break;
		default:
			break;
		}
	}
}

void CCMaterialPage::SetHeaderTitle(BOOL bInit)
{
	CString aTitle[] = { _LS(IDS_CMD_MATERIAL_id), _LS(IDS_CMD_MATERIAL_name), _LS(IDS_CMD_MATERIAL_type),
		_LS(IDS_CMD_MATERIAL_standard), _LS(IDS_CMD_MATERIAL_db) }; 
	const int COLCOUNT = 5;
	int nColWidth[COLCOUNT];
	nColWidth[0] = 50; nColWidth[1] = 50; nColWidth[2] = 60;
	nColWidth[3] = 60; nColWidth[4] = 50;
	if (bInit)
	{
		DWORD dwStyle = ListView_GetExtendedListViewStyle(m_List.GetSafeHwnd());
		dwStyle |= LVS_EX_FULLROWSELECT;
		ListView_SetExtendedListViewStyle(m_List.GetSafeHwnd(), dwStyle);
	}
	LV_COLUMN lvcolumn;
	for (int i = 0; i < COLCOUNT; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		if (i == 0)lvcolumn.fmt = LVCFMT_RIGHT;
		else lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.iSubItem = i;
		lvcolumn.cx = nColWidth[i];
		lvcolumn.pszText = aTitle[i].GetBuffer(0);
		m_List.InsertColumn(i, &lvcolumn);
		m_List.SetColumn(i, &lvcolumn);
	}
}

void CCMaterialPage::MakeItemEx()
{
	const int COLCOUNT = 5;
	int nItemCount = m_pDoc->m_pAttrCtrl->GetCountMatl();
	if (nItemCount == 0)return;
	T_MATL_K Key;
	T_MATL_D Data;
	int* KeyBuffer = new int[nItemCount];
	POSITION pos = m_pDoc->m_pAttrCtrl->GetStartMatl();
	int nCount = 0;
	while (pos != NULL)
	{
		m_pDoc->m_pAttrCtrl->GetNextMatl(pos, Key, Data);
		KeyBuffer[nCount++] = Key;
	}
	//qsort(KeyBuffer, nItemCount, sizeof(T_MATL_K), CCompFunc::UINTAsc);
	for (nCount = 0; nCount < nItemCount; nCount++)
	{
		Key = KeyBuffer[nCount];
		m_pDoc->m_pAttrCtrl->GetMatl(Key, Data);
		InsertItem(Key, Data);
	}
	delete KeyBuffer;
}

BOOL CCMaterialPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetHeaderTitle();
	MakeItemEx();
	return TRUE;
}

CString CCMaterialPage::DataToStr(int i, T_MATL_K Key, const T_MATL_D& rData)
{
	CString str;
	if (i == 0)str.Format(_T("%6d"), Key);
	else if (i == 1)str = rData.Name;
	else if (i == 2)
	{
		if (rData.Type == _T("S")) str = _LS(IDS_WG_CMD__ADDD__Steel);
		else if (rData.Type == _T("C")) str = _LS(IDS_WG_CMD__ADDD__Concrete);
		else if (rData.Type == _T("U")) str = _LS(IDS_WG_CMD__ADDD__User);
		else if (rData.Type == _T("SRC")) str = _LS(IDS_WG_CMD__ADDD__SRC);
		else if (rData.Type == _T("A")) str = _LS(IDS_WG_CMD__ADDD__Aluminium);
	}
	else if (i == 3) str = rData.Data1.CodeName;
	else if (i == 4) str = rData.Data1.CodeMatlName;
	return str;
}

BOOL CCMaterialPage::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_ESCAPE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}