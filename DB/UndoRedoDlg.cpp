// CMatPageItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "UndoRedoDlg.h"

IMPLEMENT_DYNAMIC(CUndoRedoDlg, CDialog)

CUndoRedoDlg::CUndoRedoDlg(CDBDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DB_UDRD_LIST_DLG, pParent)
{
	m_pDoc = pDoc;
}

CUndoRedoDlg::~CUndoRedoDlg()
{
}

void CUndoRedoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUndoRedoDlg, CDialog)
END_MESSAGE_MAP()


// CUndoRedoDlg ��Ϣ�������


void CUndoRedoDlg::OnOK()
{
	CDialog::OnOK();
}

void CUndoRedoDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CUndoRedoDlg::Create()
{
	CDialog::Create(IDD);
}

BOOL CUndoRedoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
