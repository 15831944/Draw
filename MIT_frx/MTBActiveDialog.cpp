#include "stdafx.h"
#include "MTBActiveDialog.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBActiveDialog, MTBDialogBase)

BEGIN_MESSAGE_MAP(MTBActiveDialog, MTBDialogBase)
	ON_BN_CLICKED(IDC_BTN_OK    , OnBtnOK)
	ON_BN_CLICKED(IDC_BTN_APPLY , OnBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTBSortDlg dialog
MTBActiveDialog::MTBActiveDialog() :
	m_pTable(NULL)
{
	ASSERT(0);
	// 아직 모달리스는 안됨
}

MTBActiveDialog::MTBActiveDialog(MTable* pTable) :
	MTBDialogBase(pTable),
	m_pTable(pTable)
{
}

MTBActiveDialog::~MTBActiveDialog()
{
}

BOOL MTBActiveDialog::Create(MTable* pTable)
{
	m_pTable = pTable;
	// TODO: m_table 
	ASSERT(0);
	// 아직 모달리스는 안됨
	return MTBDialogBase::Create(pTable);
}

BOOL MTBActiveDialog::AddActiveColumn(int nColumn)
{
	MTBSchemaBase* pSchema = m_pTable->GetSchema();
	const MTBColumn& column = pSchema->GetColumn(nColumn);
	if (!column.HasDataMap()) return FALSE;
	ITBDataMap* pDataMap = column.GetDataMap();
	//pDataMap->
	return FALSE;
}

BOOL MTBActiveDialog::AddActiveDialog(CDialog* pDialog)
{
	return FALSE;
}

BOOL MTBActiveDialog::CreateControls()
{
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER;

	if (!m_btnOK.Create(_T("확인"), WS_VISIBLE | WS_CHILD, CRect(269, 275, 339, 295), this, IDC_BTN_OK)) return FALSE;
	if (!m_btnCancel.Create(_T("취소"), WS_VISIBLE | WS_CHILD, CRect(344, 275, 414, 295), this, IDC_BTN_CANCEL)) return FALSE;
	if (!m_btnApply.Create(_T("적용"), WS_VISIBLE | WS_CHILD, CRect(419, 275, 489, 295), this, IDC_BTN_APPLY)) return FALSE;

	CFont* pFont = GetFont();
	m_btnOK.SetFont(pFont);
	m_btnCancel.SetFont(pFont);
	m_btnApply.SetFont(pFont);

	return TRUE;
}

BOOL MTBActiveDialog::OnInitDialog() 
{
	if (!MTBDialogBase::OnInitDialog()) return FALSE;
	if (!SetWindowPos(NULL, 0, 0, 500, 325, SWP_NOMOVE | SWP_NOZORDER)) return FALSE;
	SetWindowText(_T(" 형식"));		
	UpdateData(FALSE);
	return TRUE; 
}

void MTBActiveDialog::OnBtnOK() 
{
	//if (!Apply()) return;
	MDialog::OnOK();
}

void MTBActiveDialog::OnBtnApply() 
{
	//Apply();
}

void MTBActiveDialog::OnBtnCancel() 
{
	EndDialog(IDCLOSE);
	MDialog::OnClose();
}

void MTBActiveDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	MTBDialogBase::PostNcDestroy();
}