#include "stdafx.h"
#include "UndoRedoDlg.h"
#include "DBDoc.h"
#include "UndoRedo.h"

#pragma region CListBoxForUR
CListBoxForUR::CListBoxForUR()
{
}
CListBoxForUR::~CListBoxForUR()
{
	
}
BEGIN_MESSAGE_MAP(CListBoxForUR,CListBox)
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_REFLECT_EX(LBN_SELCHANGE, OnSelchange)
END_MESSAGE_MAP()
void CListBoxForUR::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListBox::OnLButtonDown(nFlags, point);
	m_bMouseDown = TRUE;
	//SetSel2(GetCurSel());
	GetParent()->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),LBN_SELCHANGE),(LPARAM)m_hWnd);
	//SelItemRange(FALSE,nCount+1,GetCount());
}
BOOL CListBoxForUR::OnSelchange()
{
	if(GetCurSel() > 0)
		SelItemRange(TRUE,0,GetCurSel());
	SelItemRange(FALSE,GetCurSel()+1,GetCount());
	return FALSE;
}
#pragma endregion CListBoxForUR


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
	ON_LBN_SELCHANGE(IDC_LIST1, &CUndoRedoDlg::OnSelchangeList1)
	ON_WM_ACTIVATE()
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
	T_UDRD_INDEX data;
	CString strTemp,strData;
	int nCount = 0;
	POSITION pos = m_pDoc->m_redo->m_uridx.GetTailPosition();
	while(pos != NULL)
	{
		data = m_pDoc->m_redo->m_uridx.GetPrev(pos);
		nCount++;
		strTemp.Format(_T("%d. "),nCount);
		strData = strTemp + data.strCmd;
		m_List.AddString(strData);
	}
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
	if(m_List.GetCount() > 0)
	{
		m_List.SetSel(0);
		m_btnUDRD.EnableWindow(TRUE);
	}
	else
		m_btnUDRD.EnableWindow(FALSE);
	return TRUE;
}
void CUndoRedoDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	if(nState == WA_INACTIVE)DestroyWindow();
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
	int nCount = m_List.GetSelCount();
	if(nCount == 0)return;//ASSERT(nCount!=0);
	if(m_bIsUndo)
	{
		int nUndoCount = static_cast<int>(m_pDoc->m_undo->GetCountidx());
		for(int i = 0;i < nCount;i++)
		{
			m_pDoc->DoUndo();
			if(m_pDoc->m_undo->GetCountidx() == nUndoCount)break;
		}
	}
	else
	{
		int nUndoCount = m_pDoc->m_redo->GetCountidx();
		for(int i = 0;i < nCount;i++)
		{
			m_pDoc->DoRedo();
			if(m_pDoc->m_redo->GetCountidx() == nUndoCount)break;
		}
	}
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

void CUndoRedoDlg::OnSelchangeList1()
{
	if(m_List.GetSelCount() == 0)
		m_btnUDRD.EnableWindow(FALSE);
	else
		m_btnUDRD.EnableWindow(TRUE);
}


