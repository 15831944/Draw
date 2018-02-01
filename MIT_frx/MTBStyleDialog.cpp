#include "stdafx.h"
#include "MTBStyleDialog.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBStyleDialog, MTBDialogBase)

BEGIN_MESSAGE_MAP(MTBStyleDialog, MTBDialogBase)
	ON_BN_CLICKED(IDC_BTN_OK    , OnBtnOK)
	ON_BN_CLICKED(IDC_BTN_APPLY , OnBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
END_MESSAGE_MAP()


	/////////////////////////////////////////////////////////////////////////////
// CTBSortDlg dialog
MTBStyleDialog::MTBStyleDialog() :
	m_pObjTable(NULL),
	m_table(NULL)
{
	ASSERT(0);
	// 아직 모달리스는 안됨
}

MTBStyleDialog::MTBStyleDialog(MTable* pObjTable) :
	MTBDialogBase(pObjTable),
	m_pObjTable(pObjTable),
	m_table(pObjTable)
{
}

MTBStyleDialog::~MTBStyleDialog()
{
}

BOOL MTBStyleDialog::Create(MTable* pObjTable)
{
	m_pObjTable = pObjTable;
	// TODO: m_table 
	ASSERT(0);
	// 아직 모달리스는 안됨
	return MTBDialogBase::Create(pObjTable);
}

BOOL MTBStyleDialog::CreateControls()
{
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER;
	
	if (!m_table.Create( dwStyle, CRect(5, 2, 510, 270), this, IDC_GRID)) return FALSE;
	if (!m_btnOK.Create(_T("확인"), WS_VISIBLE | WS_CHILD, CRect(269, 275, 339, 295), this, IDC_BTN_OK)) return FALSE;
	if (!m_btnCancel.Create(_T("취소"), WS_VISIBLE | WS_CHILD, CRect(344, 275, 414, 295), this, IDC_BTN_CANCEL)) return FALSE;
	if (!m_btnApply.Create(_T("적용"), WS_VISIBLE | WS_CHILD, CRect(419, 275, 489, 295), this, IDC_BTN_APPLY)) return FALSE;
	
	CFont* pFont = GetFont();
	m_table.SetFont(pFont);
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_btnApply.SetFont(pFont);

	return TRUE;
}

BOOL MTBStyleDialog::Apply()
{
	ITableDB* pTableDB = m_table.GetTableDB();
	int nCount = pTableDB->GetRowCount();
	for (int i = 0; i < nCount; i++)
	{
		const MTBStyleTableData* pData = (const MTBStyleTableData*)pTableDB->GetRow(i);
		if (!m_pObjTable->PGetColumnsInfo()->SetColumnWidth(i, pData->nWidth)) return FALSE;
		if (!m_pObjTable->PGetColumnsInfo()->SetColumnAlign(i, pData->nAlign)) return FALSE;
		if (!m_pObjTable->GetSchema()->GetColumn(i).IsFloatType()) continue;
		ASSERT(pData->nFormat >= 0);
		MFormatInfo formatInfo;
		formatInfo.SetFormatInfo(pData->nFormat, pData->nPrecision);
		((MGridColumnsInfo*)m_pObjTable->PGetColumnsInfo())->SetColumnFormat(i, formatInfo);
	}
	m_pObjTable->UpdateData();

	return TRUE;
}

BOOL MTBStyleDialog::OnInitDialog() 
{
	if (!MTBDialogBase::OnInitDialog()) return FALSE;
	if (!SetWindowPos(NULL, 0, 0, 530, 325, SWP_NOMOVE | SWP_NOZORDER)) return FALSE;
	SetWindowText(_T(" 형식"));		
	UpdateData(FALSE);
	return TRUE; 
}

void MTBStyleDialog::OnBtnOK() 
{
	if (!Apply()) return;
	MDialog::OnOK();
}

void MTBStyleDialog::OnBtnApply() 
{
	Apply();
}

void MTBStyleDialog::OnBtnCancel() 
{
	EndDialog(IDCLOSE);
	MDialog::OnClose();
}

void MTBStyleDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	MTBDialogBase::PostNcDestroy();
}