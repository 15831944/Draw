#include "stdafx.h"
#include "UndoRedoDlg.h"
#include "DBDoc.h"
#include "UndoRedo.h"
IMPLEMENT_DYNAMIC(CUndoRedoDlg, CDialog)

CUndoRedoDlg::CUndoRedoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DB_UDRD_LIST_DLG, pParent)
{
	m_pDoc = 0;
	m_xPos = 0;
	m_yPos = 0;
	m_bIsUndo = FALSE;
}
CUndoRedoDlg::~CUndoRedoDlg()
{
}
void CUndoRedoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DB_UDRD_BTN, m_btnUDRD);
}

BEGIN_MESSAGE_MAP(CUndoRedoDlg, CDialog)
	ON_BN_CLICKED(IDC_DB_UDRD_BTN, &CUndoRedoDlg::OnUndoRedo)
	ON_BN_CLICKED(IDC_DB_UDRD_CANCEL, &CUndoRedoDlg::OnCancel)
END_MESSAGE_MAP()

void CUndoRedoDlg::AddUndoCommands()
{
	T_UDRD_INDEX data;
	CString strTemp,strData;
	int nCount = 0;
	POSITION pos = m_pDoc->m_undo->m_uridx.GetTailPosition();
	while(pos != NULL)
	{
		data = m_pDoc->m_undo->m_uridx.GetPrev(pos);
		nCount++;
		strTemp.Format(_T("%d. "),nCount);
		strData = strTemp + data.strCmd;
		m_List.AddString(strData);
	}
}
void CUndoRedoDlg::AddRedoCommands()
{
	
}

// CUndoRedoDlg 消息处理程序
BOOL CUndoRedoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(NULL,m_xPos,m_yPos,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);  
	if(m_bIsUndo)
	{
		m_btnUDRD.SetWindowTextW(_LS(IDS_DB_UNDOREDO__Undo));
		AddUndoCommands();
	}
	else
	{
		m_btnUDRD.SetWindowTextW(_LS(IDS_DB_UNDOREDO__Redo));
		AddRedoCommands();
	}
	return TRUE;
}
void CUndoRedoDlg::SetDlgMode(CDBDoc* pDoc,BOOL bIsUndo,int xPos,int yPos)
{
	m_pDoc = pDoc;
	m_xPos = xPos;
	m_yPos = yPos;
	m_bIsUndo = bIsUndo;
}
void CUndoRedoDlg::OnUndoRedo()
{
	DestroyWindow();
}
void CUndoRedoDlg::OnCancel()
{
	DestroyWindow();
}

void CUndoRedoDlg::PostNcDestroy()
{
	m_pDoc->CloseUDRDVisible();
	delete this;
}
