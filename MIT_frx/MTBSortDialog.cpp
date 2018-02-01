#include "stdafx.h"
#include "MTBSortDialog.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBSortDialog, MTBDialogBase)

BEGIN_MESSAGE_MAP(MTBSortDialog, MTBDialogBase)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_SORT, OnBtnSort)
	ON_BN_CLICKED(IDC_BTN_ADD, OnColAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnColDel)
	ON_BN_CLICKED(IDC_BTN_UP, OnPrioUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnPrioDown)
	ON_LBN_DBLCLK(IDC_LISTBOX_TABLE_COLS, OnDblClickColsItem)
	ON_LBN_DBLCLK(IDC_LISTBOX_SORT_COLS, OnDblClickSortColsItem)
	ON_CLBN_CHKCHANGE(IDC_LISTBOX_SORT_COLS, OnChkChangeSortColsItem)
	//ON_MESSAGE(IDC_LISTBOX_SORT_COLS, OnScrollAddString)
END_MESSAGE_MAP()


	/////////////////////////////////////////////////////////////////////////////
// CTBSortDlg dialog
MTBSortDialog::MTBSortDialog()
{
	ASSERT(0);
	// 아직 모달리스는 안됨
}

MTBSortDialog::MTBSortDialog(MTable* pTable) :
	MTBDialogBase(pTable),
	m_pSort(pTable->GetTableDB()->GetSort())
{
}

MTBSortDialog::~MTBSortDialog()
{
}

BOOL MTBSortDialog::Create(MTable* pTable)
{
	ASSERT(0);
	// 아직 모달리스는 안됨
	m_pSort = pTable->GetTableDB()->GetSort();
	return MTBDialogBase::Create(pTable);
}

void MTBSortDialog::SetHorizontalScroll(CListBox& lstbox)
{
	// 이거 왜 하는거임??
	// 원 소스에 있길래 놔둬본다.
	int nTextWidth;
	int dx = 0;
	CString str;
	CClientDC dc(&lstbox);
	for (int i = 0; i < lstbox.GetCount(); i++)
	{
		lstbox.GetText(i, str);
		nTextWidth = dc.GetTextExtent(str).cx;
		if (nTextWidth > dx)
			dx = nTextWidth;
	}
	lstbox.SetHorizontalExtent(dx);
}

CString MTBSortDialog::GetSortColName(const TBSortColumn& sortcol)
{
	const MTBColumn& column = GetSchema()->GetColumn(sortcol.nColumn);
	CString strSortColumn;
	if (sortcol.bAscending)
	{
		strSortColumn.Format(_T("Asc | %s"), column.GetDisplayName());
	}
	else
	{
		strSortColumn.Format(_T("Desc | %s"), column.GetDisplayName());
	}
	return strSortColumn;
}

void MTBSortDialog::InitTableCols()
{
	CAtlList<TBSortColumn> lstSortinfo;
	GetSort()->GetSortColumns(lstSortinfo);
		
	int nColumnCount = GetSchema()->GetColumnCount();

	int nItemIndex = 0;
	BOOL bFind = FALSE;
	for (int i = 0; i < nColumnCount; i++)
	{
		bFind = FALSE;
		POSITION pos = lstSortinfo.GetHeadPosition();
		while (pos)
		{
			if (lstSortinfo.GetNext(pos).nColumn == i) { bFind = TRUE; break; }
		}
		if (bFind) continue;
		const MTBColumn& column = GetSchema()->GetColumn(i);
		nItemIndex = m_lbCols.AddString(column.GetDisplayName());
		m_lbCols.SetItemData(nItemIndex, (DWORD_PTR)i);
	}

	SetHorizontalScroll(m_lbCols);
}

void MTBSortDialog::InitSortCols()
{
	CAtlList<TBSortColumn> lstSortinfo;
	GetSort()->GetSortColumns(lstSortinfo);

	int nItemIndex = 0;
	POSITION pos = lstSortinfo.GetHeadPosition();
	while (pos)
	{
		const TBSortColumn& sc = lstSortinfo.GetNext(pos);
		nItemIndex = m_lbSortCols.AddString(GetSortColName(sc));
		m_lbSortCols.SetItemData(nItemIndex, (DWORD_PTR)sc.nColumn);
		m_lbSortCols.SetCheck(nItemIndex, sc.bAscending ? BST_CHECKED : BST_UNCHECKED);
	}
	
	SetHorizontalScroll(m_lbSortCols);
}

BOOL MTBSortDialog::CreateControls()
{
	const DWORD dwListBoxStyle = LBS_HASSTRINGS | LBS_MULTIPLESEL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_EXTENDEDSEL | WS_VSCROLL;
	if (!m_sttTableCols.Create(_T("Table Columns"), WS_VISIBLE | WS_CHILD, CRect(10, 10, 130, 30), this, IDC_STT_TABLE_COLS)) return FALSE;
	if (!m_sttSortCols.Create(_T("Sort Key Columns"), WS_VISIBLE | WS_CHILD, CRect(200, 10, 320, 30), this, IDC_STT_SORT_COLS)) return FALSE;
	if (!m_lbCols.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | dwListBoxStyle, CRect(10, 30, 130, 180), this, IDC_LISTBOX_TABLE_COLS)) return FALSE;
	if (!m_lbSortCols.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | dwListBoxStyle, CRect(200, 30, 320, 180), this, IDC_LISTBOX_SORT_COLS)) return FALSE;
	if (!m_btnAdd.Create(_T("->"), WS_VISIBLE | WS_CHILD, CRect(145, 30, 185, 50), this, IDC_BTN_ADD)) return FALSE;
	if (!m_btnDel.Create(_T("<-"), WS_VISIBLE | WS_CHILD, CRect(145, 60, 185, 80), this, IDC_BTN_DEL)) return FALSE;
	if (!m_groupPriority.Create(_T("Priority"), WS_VISIBLE | WS_CHILD | BS_GROUPBOX, CRect(135, 100, 195, 180), this, IDC_GRP_PRIORITY)) return FALSE;
	if (!m_btnUp.Create(_T("Up"), WS_VISIBLE | WS_CHILD, CRect(145, 120, 185, 140), this, IDC_BTN_UP)) return FALSE;
	if (!m_btnDown.Create(_T("Down"), WS_VISIBLE | WS_CHILD, CRect(145, 150, 185, 170), this, IDC_BTN_DOWN)) return FALSE;
	if (!m_btnSort.Create(_T("Sort"), WS_VISIBLE | WS_CHILD, CRect(175, 190, 245, 210), this, IDC_BTN_SORT)) return FALSE;
	if (!m_btnClose.Create(_T("Close"), WS_VISIBLE | WS_CHILD, CRect(250, 190, 320, 210), this, IDC_BTN_CLOSE)) return FALSE;
	
	CFont* pFont = GetFont();
	m_sttTableCols.SetFont(pFont);
	m_sttSortCols.SetFont(pFont);
	m_lbCols.SetFont(pFont);
	m_lbSortCols.SetFont(pFont);
	m_btnAdd.SetFont(pFont);
	m_btnDel.SetFont(pFont);
	m_groupPriority.SetFont(pFont);
	m_btnUp.SetFont(pFont);
	m_btnDown.SetFont(pFont);
	m_btnSort.SetFont(pFont);
	m_btnClose.SetFont(pFont);

	return TRUE;
}

BOOL MTBSortDialog::OnInitDialog() 
{
	if (!MTBDialogBase::OnInitDialog()) return FALSE;
	if (!SetWindowPos(NULL, 0, 0, 335, 240, SWP_NOMOVE | SWP_NOZORDER)) return FALSE;
	SetWindowText(_T(" Sort Dialog"));

	InitTableCols();
	InitSortCols();
	
	UpdateData(FALSE);
	return TRUE; 
}

void MTBSortDialog::OnBtnClose() 
{
	OnOK();

	//// TODO: Add your control notification handler code here
	//if (m_bModal) MDialog::OnOK();
	//else DestroyWindow();
}

void MTBSortDialog::OnBtnSort() 
{
	int nCount = m_lbSortCols.GetCount();
	if (nCount == 0) 
	{
		AfxMessageBox(_STR("선택된 열이 없어서 소팅을 못 한다능..."), MB_OK);
		return;
	}

	CAtlList<TBSortColumn> lstSortcol;
	for (int i = 0; i < nCount; i++)
	{
		lstSortcol.AddTail(TBSortColumn((int)m_lbSortCols.GetItemData(i), (BOOL)m_lbSortCols.GetCheck(i)));
	}

	GetSort()->SetSortColumns(lstSortcol);
	GetSort()->Sort();

	// TODO: ?
	if (GetTable()->GetSafeHwnd())
		GetTable()->PostMessage(MTable::REG_WM_MTABLE_UPDATE, (WPARAM)MTable::MSG_REDRAW, NULL);
}

void MTBSortDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	MTBDialogBase::PostNcDestroy();
	//if (!m_bModal) delete this;
}

void MTBSortDialog::OnColAdd() 
{
	int nCount = m_lbCols.GetSelCount();
	if (nCount <= 0) return;

	int nItemIndex = 0;
	TBSortColumn sc(0, TRUE);
	std::vector<int> aIndex;
	aIndex.resize(nCount);
	m_lbCols.GetSelItems(nCount, aIndex.data());
	for (int i = 0; i < nCount; i++)
	{
		sc.nColumn = (int)m_lbCols.GetItemData(aIndex[i]);
		nItemIndex = m_lbSortCols.AddString(GetSortColName(sc));
		m_lbSortCols.SetItemData(nItemIndex, (DWORD_PTR)sc.nColumn);
		m_lbSortCols.SetCheck(nItemIndex, sc.bAscending ? BST_CHECKED : BST_UNCHECKED);
	}

	for (int i = nCount - 1; i >= 0; i--) 
	{
		m_lbCols.DeleteString(aIndex[i]);
	}

	SetHorizontalScroll(m_lbCols);
	SetHorizontalScroll(m_lbSortCols);
}

void MTBSortDialog::OnColDel() 
{
	int nCount = m_lbSortCols.GetSelCount();
	if (nCount <= 0) return;

	int nItemIndex = 0;
	int nIndex = 0;
	int nColumn = 0;
	std::vector<int> aIndex;
	aIndex.resize(nCount);
	m_lbSortCols.GetSelItems(nCount, aIndex.data());
	for (int i = 0; i < nCount; i++)
	{
		nColumn = (int)m_lbSortCols.GetItemData(aIndex[i]);
		for (nIndex = 0; nIndex < m_lbCols.GetCount(); nIndex++)
		{
			if ((int)m_lbCols.GetItemData(nIndex) > nColumn) break;
		}
		const MTBColumn& column = GetSchema()->GetColumn(nColumn);		
		nItemIndex = m_lbCols.InsertString(nIndex, column.GetDisplayName());
		m_lbCols.SetItemData(nItemIndex, (DWORD_PTR)nColumn);
	}

	for (int i = nCount - 1; i >= 0; i--) 
	{
		m_lbSortCols.DeleteString(aIndex[i]);
	}

	SetHorizontalScroll(m_lbCols);
	SetHorizontalScroll(m_lbSortCols);
}

void MTBSortDialog::OnPrioUp() 
{
	int nCount = m_lbSortCols.GetSelCount();
	if (nCount <= 0) return;

	int nItemIndex = 0;
	TBSortColumn sc(0, TRUE);
	std::vector<int> aIndex;
	aIndex.resize(nCount);
	m_lbSortCols.GetSelItems(nCount, aIndex.data());
	for (int i = 0; i < nCount; i++)
	{
		if (aIndex[i] == i) continue;
		sc.nColumn = (int)m_lbSortCols.GetItemData(aIndex[i]);
		sc.bAscending = (BOOL)m_lbSortCols.GetCheck(aIndex[i]);
		m_lbSortCols.DeleteString(aIndex[i]);
		nItemIndex = m_lbSortCols.InsertString(aIndex[i]-1, GetSortColName(sc));
		m_lbSortCols.SetItemData(nItemIndex, (DWORD_PTR)sc.nColumn);
		m_lbSortCols.SetCheck(nItemIndex, sc.bAscending ? BST_CHECKED : BST_UNCHECKED);
		m_lbSortCols.SetSel(nItemIndex, TRUE);
	}
}

void MTBSortDialog::OnPrioDown() 
{
	int nCount = m_lbSortCols.GetSelCount();
	if (nCount <= 0) return;

	int nItemIndex = 0;
	TBSortColumn sc(0, TRUE);
	std::vector<int> aIndex;
	aIndex.resize(nCount);
	m_lbSortCols.GetSelItems(nCount, aIndex.data());
	for (int i = nCount-1, j=0; i >= 0; i--,j++)
	{
		if (aIndex[i] == m_lbSortCols.GetCount()-1-j) continue;
		sc.nColumn = (int)m_lbSortCols.GetItemData(aIndex[i]);
		sc.bAscending = (BOOL)m_lbSortCols.GetCheck(aIndex[i]);
		m_lbSortCols.DeleteString(aIndex[i]);
		nItemIndex = m_lbSortCols.InsertString(aIndex[i]+1, GetSortColName(sc));
		m_lbSortCols.SetItemData(nItemIndex, (DWORD_PTR)sc.nColumn);
		m_lbSortCols.SetCheck(nItemIndex, sc.bAscending ? BST_CHECKED : BST_UNCHECKED);
		m_lbSortCols.SetSel(nItemIndex, TRUE);
	}
}

void MTBSortDialog::OnDblClickColsItem() 
{
	OnColAdd();
}

void MTBSortDialog::OnDblClickSortColsItem() 
{
	OnColDel();
}

void MTBSortDialog::OnChkChangeSortColsItem()
{
	// TODO: Vertical Scroll 생겼을 경우 이 함수 땜에 이상동작한다.
	//       ListBox에 Item 을 다 지우고 새로 추가하기 때문.
	//       근데 그냥 String 만 바꾸는 방법이 없다.
	//       Drawing 코드를 Customizing 해야 한다. 씨빠...

	int nCount = m_lbSortCols.GetCount();
	if (nCount == 0) return;

	int nSelCount = m_lbSortCols.GetSelCount();
	std::vector<int> aIndex;
	aIndex.resize(nSelCount);
	m_lbSortCols.GetSelItems(nSelCount, aIndex.data());

	std::vector<TBSortColumn> aSortcol;
	aSortcol.reserve(nCount);
	for (int i = 0; i < nCount; i++)
	{
		aSortcol.push_back(TBSortColumn((int)m_lbSortCols.GetItemData(i), (BOOL)m_lbSortCols.GetCheck(i)));
	}

	m_lbSortCols.ResetContent();

	int nItemIndex = 0;
	for (int i = 0; i < nCount; i++)
	{
		nItemIndex = m_lbSortCols.AddString(GetSortColName(aSortcol[i]));
		m_lbSortCols.SetItemData(nItemIndex, (DWORD_PTR)aSortcol[i].nColumn);
		m_lbSortCols.SetCheck(nItemIndex, aSortcol[i].bAscending ? BST_CHECKED : BST_UNCHECKED);
	}

	for (int i = 0; i < nSelCount; i++)
	{
		m_lbSortCols.SetSel(aIndex[i]);
	}
}