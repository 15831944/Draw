// CMatPageItemDlg.cpp : 实现文件
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


// CUndoRedoDlg 消息处理程序


void CUndoRedoDlg::OnOK()
{
	CDialog::OnOK();
}

void CUndoRedoDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

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
