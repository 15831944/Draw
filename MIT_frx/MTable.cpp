#include "stdafx.h"
#include "MTable.h"

#include "MGridItem.h"
#include "MGridCheckItem.h"
#include "MGridButtonItem.h"
#include "MGridDataMapComboItem.h"
#include "MGridRow.h"
#include "MTBSortDialog.h"
#include "MTBStyleDialog.h"
#include "MTBActiveDialog.h"
#include "MTBClipBoard.h"
#include "MTableExportToExcel.h"

#include "ExtDllInstanceSwitcher.h"
#include "MExportToChartDlg.h"

#include <algorithm>

using namespace std;
using namespace mit;
using namespace mit::frx;

#define TEXT_MARGIN		3
#define TEXT_VMARGIN	3

#ifdef _UNICODE
#define _TCF_TEXT	CF_UNICODETEXT
#else
#define _TCF_TEXT	CF_TEXT
#endif

#define	BCGPGRIDCTRL_ID_INPLACE	1

const int nIdToolTipHeader = 1;

UINT MTable::REG_WM_MTABLE_UPDATE = RegisterWindowMessage(_T("REG_WM_MTABLE_UPDATE"));

//class MPostTableData
IMPLEMENT_DYNAMIC(MDISPINFO_USERDATA, CObject)
	MDISPINFO_USERDATA::MDISPINFO_USERDATA()
{
	Clear();
}

MDISPINFO_USERDATA::~MDISPINFO_USERDATA() 
{
	m_pGridItem = NULL;
}

void MDISPINFO_USERDATA::Clear()
{
	m_bAllowEdit = TRUE;
	m_bEnabled	= TRUE;
	m_bBold		= FALSE;
	m_bItalic	= FALSE;
	m_bUnderline= FALSE;
	m_bStrikeOut= FALSE;
	m_pGridItem = NULL;
	m_dwData    = NULL;
}

// class MRecordMergeInfo
MRecordInfo::MRecordInfo()
{
	Initialize();
}

MRecordInfo::MRecordInfo(int nRow, int nColumn)
{
	Initialize(nRow, nColumn);
}

MRecordInfo::~MRecordInfo()
{
	for(int i=0; i<(int)m_arMerge.GetSize(); ++i )
	{
		_SAFE_DELETE(m_arMerge[i]);
	}
}

void MRecordInfo::Initialize(int nRow, int nColumn)
{
	m_nRow = nRow;
	m_nColumns = nColumn;

	for(int i=0; i<(int)m_arMerge.GetSize(); ++i )
	{
		_SAFE_DELETE(m_arMerge[i]);
	}

	m_arMerge.RemoveAll();
}

int MRecordInfo::AddMergeRange(CBCGPGridRange* range)
{
	return (int)m_arMerge.Add(range);
}

const CBCGPGridRange* MRecordInfo::GetMergeRange(int nIndex)
{
	if( nIndex < 0 || nIndex >= (int)m_arMerge.GetSize() )
	{
		ASSERT(0);
		return NULL;
	}

	return m_arMerge[nIndex];
}

// end of MPostTableData
//////////////////////////////////////////////////////////////////////////

// class MPostTable
IMPLEMENT_DYNAMIC(MTable, CBCGPGridCtrl)
	MTable::MTable() :
	m_bThreeSortToggle(TRUE),
	m_bCreateCheckItem(TRUE),
	m_bCreateComboItem(TRUE),
	m_canAppendRow(FALSE),
	m_canDeleteRow(FALSE),
	n_canDeleteEditingRow(TRUE),
	m_bDeleteSelectedWholeRowOnly(TRUE),
	m_canModifyItem(FALSE),
	m_nEditingRow(-1),
	m_pEditingCachePage(nullptr),
	m_bAppendRowMarker(TRUE),
	m_bEditingRowMarker(TRUE),
	m_bSelectEditingRow(TRUE),
	m_pEndEditItem(nullptr),
	m_bEasyInput(TRUE),
	m_dwEasyInputFlag(EndEdit_Return)
{
	m_pColumnsEx = new MGridColumnsInfo();
	m_pUserData = new MDISPINFO_USERDATA();
	m_pDataRecordInfo = new MRecordInfo();
	m_pExtraTopInfo = new MRecordInfo();
	m_pExtraBottomInfo = new MRecordInfo();
	m_bCallMouseWheel = FALSE;
}

MTable::~MTable()
{
	//ASSERT(!IsEditingRow()); MainFrame ���� �� �ɸ� �� �ۿ� ��� �ּ�ó��
	m_nEditingRow = -1; // ~MGridRow() ���� ���� ���� Row ����Ȯ�� ASSERT �Ȱɸ�����

	if( m_pColumnsEx )
	{
		delete m_pColumnsEx;
		m_pColumnsEx = NULL;
	}

	if( m_pUserData ) 
	{
		delete m_pUserData;
		m_pUserData = NULL;
	}

	_SAFE_DELETE( m_pDataRecordInfo );
	_SAFE_DELETE( m_pExtraTopInfo );
	_SAFE_DELETE( m_pExtraBottomInfo );
}

BEGIN_MESSAGE_MAP(MTable, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(MPostTable)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_KILLFOCUS()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TB_TABBED_DOCUMENT, OnTabbedDocument)
	ON_COMMAND(ID_TB_COPY, OnCopy)
	ON_COMMAND(ID_TB_PASTE, OnPaste)
	ON_COMMAND(ID_TB_FIND, OnFind)
	ON_COMMAND(ID_TB_SORT, OnSort)
	ON_COMMAND(ID_TB_STYLE, OnStyle)
	ON_COMMAND(ID_TB_GRAPH, OnGraph)
	ON_COMMAND(ID_TB_EXPORT_TO_EXCEL, OnExportToExcel)
	ON_COMMAND(ID_TB_ACTIVE_DIALOG, OnActiveDialog)
	ON_BN_CLICKED(ID_TB_BUTTON_ITEM, OnBtnClicked)
	ON_EN_CHANGE(BCGPGRIDCTRL_ID_INPLACE, OnEditChanged)	
	ON_EN_KILLFOCUS(BCGPGRIDCTRL_ID_INPLACE, OnEditKillFocus)
	ON_CBN_KILLFOCUS(BCGPGRIDCTRL_ID_INPLACE, OnComboKillFocus)
	ON_REGISTERED_MESSAGE( MTable::REG_WM_MTABLE_UPDATE, OnUpdate)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_ENDINPLACEEDIT, OnEndLabelEdit)
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

void MTable::UpdateRowCount()
{
	BOOL bLock = LockWindowUpdate();

	ASSERT(!IsEditingRow());
	SetVirtualRows(GetRowCount());

	if( bLock ) UnlockWindowUpdate();

	PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);
}

void MTable::UpdateData()
{
	BOOL bLock = LockWindowUpdate();

	ASSERT(!IsEditingRow());
	SetVirtualRows(GetRowCount());

	if( bLock ) UnlockWindowUpdate();

	PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);
}

void MTable::UpdateSortColumns()
{
	CAtlList<TBSortColumn> lstSortcol;
	GetSort()->GetSortColumns(lstSortcol);

	GetColumnsInfo().RemoveAllSortColumns();
	POSITION pos = lstSortcol.GetHeadPosition();
	while (pos)
	{
		const TBSortColumn& sortColumn = lstSortcol.GetNext(pos);
		GetColumnsInfo().SetSortColumn(sortColumn.nColumn, sortColumn.bAscending, TRUE);
	}

	SetRebuildTerminalItems();
}

void MTable::UpdateAppendRow()
{
	// TODO: Selection �̻�������...
	ASSERT(!IsEditingRow());
	m_CachedItems.CleanUpCache();
	m_nVirtualRows = GetRowCount();
	AdjustLayout();
}

void MTable::UpdateUnit()
{
	ASSERT(!IsEditingRow());

	MTBSchemaBase* pSchema = GetSchema();
	int nColumnCount = pSchema->GetColumnCount();
	for (int nCol = 0; nCol < nColumnCount; nCol++)
	{
		SetColumnName(nCol, pSchema->GetColumn(nCol).GetHeaderName());
	}

	m_CachedItems.CleanUpCache();
	m_nVirtualRows = GetRowCount();
	AdjustLayout();
}

void MTable::RemoveAll()
{
	// virtual �Լ� �ƴ����� ���������.
	ASSERT(!IsEditingRow());
	CBCGPGridCtrl::RemoveAll();
}

void MTable::SetVirtualRows(int nRowsNum)
{
	// virtual �Լ� �ƴ����� ���������.
	ASSERT(!IsEditingRow());
	CBCGPGridCtrl::SetVirtualRows(nRowsNum);
}

int MTable::GetDefaultColumnWidth(MTBColumn::Type type)
{
	switch (type)
	{
	case MTBColumn::TB_KEY: 
	case MTBColumn::TB_MKey: 
	case MTBColumn::TB_UINT: 
	case MTBColumn::TB_int: 
		return MGridColumnsInfo::DEFAULT_WIDTH_INTEGER;
	case MTBColumn::TB_BOOL: 
	case MTBColumn::TB_bool: 
		return MGridColumnsInfo::DEFAULT_WIDTH_BOOLEAN;
	case MTBColumn::TB_float: 
	case MTBColumn::TB_double: 
		return MGridColumnsInfo::DEFAULT_WIDTH_FLOAT;
	case MTBColumn::TB_CString: 
		return MGridColumnsInfo::DEFAULT_WIDTH_STRING;
	case MTBColumn::TB_CArray:
	default:
		ASSERT(0);
		break;
	}

	return MGridColumnsInfo::DEFAULT_WIDTH;
}

void MTable::InitializeColumns()
{
	const MTBSchemaBase* pSchema = GetSchema();
	// Default Width
	for (int i = 0; i < (int)pSchema->GetColumnCount(); i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		MTBColumn::Type type = column.GetDisplayType();
		InsertColumn(i, column.GetHeaderName(), GetDefaultColumnWidth(type));
		GetColumnsInfo().SetHeaderMultiLine(i, TRUE);
	}
	// Default Align
	for (int i = 0; i < (int)pSchema->GetColumnCount(); i++)
	{
		// �ش��� ��� ����
		SetHeaderAlign(i, HDF_CENTER);
		// ���� ���� : CString
		// ��� ���� : BOOL, bool
		// ������ ���� : MKey, int, UINT, double, float
		const MTBColumn& column = pSchema->GetColumn(i);
		MTBColumn::Type type = column.GetDisplayType();
		if (type == MTBColumn::TB_CString) SetColumnAlign(i, HDF_LEFT); 
		else if (type == MTBColumn::TB_BOOL || type == MTBColumn::TB_bool) SetColumnAlign(i, HDF_CENTER);
		else SetColumnAlign(i, HDF_RIGHT);
	}
	// Default Format
	MFormatInfo formatInfo;
	for (int i = 0; i < (int)pSchema->GetColumnCount(); i++)
	{
		const MTBColumn& column = pSchema->GetColumn(i);
		if (column.IsFloatType())
		{
			if (!GetColumnFormat(i, formatInfo)) 
			{
				SetColumnFormat(i, formatInfo);
			}
		}
	}
}

BOOL MTable::InitializeTable()
{
	return TRUE;
}

BOOL MTable::CheckItemType()
{
	if (m_pDefaultItemRTC)
	{
		if (!m_pDefaultItemRTC->IsDerivedFrom(RUNTIME_CLASS(MGridItem)))
		{
			ASSERT(0); // MTable ������ MGridItem �� �� SubClass �鸸 ����
			return FALSE;
		}
	}

	const MTBSchemaBase* pSchema = GetSchema();

	int nColumnCount = pSchema->GetColumnCount();
	for (int nCol = 0; nCol < nColumnCount; nCol++)
	{
		CRuntimeClass* pItemRTC = NULL;
		if (m_mapItemsRTC.Lookup(nCol, pItemRTC))
		{
			if (!pItemRTC->IsDerivedFrom(RUNTIME_CLASS(MGridItem)))
			{
				ASSERT(0); // MTable ������ MGridItem �� �� SubClass �鸸 ����
				return FALSE;
			}
			const MTBColumn& column = pSchema->GetColumn(nCol);
			if (pItemRTC->IsDerivedFrom(RUNTIME_CLASS(MGridCheckItem)))
			{
				// MGridCheckItem �� bool, BOOL Ÿ�Ը� ����
				if (!column.IsBooleanType()) { ASSERT(0); return FALSE; }
			}
			if (pItemRTC->IsDerivedFrom(RUNTIME_CLASS(MGridDataMapComboItem)))
			{
				// TODO
			}
		}
	}

	return TRUE;
}

BOOL CALLBACK MTable::StaticGridCallback(BCGPGRID_DISPINFO* pdi, LPARAM lp)
{
	ASSERT(pdi);
	ASSERT(lp);
	return ((MTable*)lp)->GridCallback(pdi);
}

BOOL MTable::GridCallback(BCGPGRID_DISPINFO* pdi)
{
	ASSERT(pdi);
	if (pdi->item.nRow < GetExtraTopRowCount())
	{
		if (!ExtraTopCallback(pdi)) return FALSE;
		AfterExtraTopCallback(pdi);
	}
	else if (pdi->item.nRow >= GetDataRowEndIndex())
	{
		if (!ExtraBottomCallback(pdi)) return FALSE;
		AfterExtraBottomCallback(pdi);
	}
	else 
	{
		if (!DataCallback(pdi)) return FALSE;
		AfterDataCallback(pdi);
	}
	return TRUE;
}

BOOL MTable::DataCallback(BCGPGRID_DISPINFO* pdi)
{
	ASSERT(pdi);
	int nCol = pdi->item.nCol;	// Column of an item
	if (nCol < 0) return TRUE;  // Row Header�� Pass 
	int nDBRow = GetDBRowIndex(pdi->item.nRow);	// Row of an item
	return GetTableDB()->GetItem(pdi->item.varValue, nDBRow, nCol);	
}

void MTable::SetRowHeight ()
{
	if (m_bIsPrinting)
	{
		ASSERT_VALID (m_pPrintDC);

		// map to printer metrics
		HDC hDCFrom = ::GetDC(NULL);
		int nYMul = m_pPrintDC->GetDeviceCaps(LOGPIXELSY);	// pixels in print dc
		int nYDiv = ::GetDeviceCaps(hDCFrom, LOGPIXELSY);	// pixels in screen dc
		::ReleaseDC(NULL, hDCFrom);

		TEXTMETRIC tm;
		m_pPrintDC->GetTextMetrics (&tm);
		m_PrintParams.m_nBaseHeight = tm.tmHeight + ::MulDiv (2 * TEXT_VMARGIN, nYMul, nYDiv);
		m_PrintParams.m_nRowHeight = m_PrintParams.m_nBaseHeight;
		m_PrintParams.m_nLargeRowHeight = m_PrintParams.m_nBaseHeight;
		m_PrintParams.m_nButtonWidth = m_PrintParams.m_nBaseHeight;
	}
	else
	{
		CClientDC dc (this);
		HFONT hfontOld = SetCurrFont (&dc);

		TEXTMETRIC tm;
		dc.GetTextMetrics (&tm);
		m_nBaseHeight = tm.tmHeight + 2 * TEXT_VMARGIN;
		m_nRowHeight = m_nBaseHeight;
		m_nLargeRowHeight = m_nBaseHeight;
		m_nButtonWidth = m_nBaseHeight;

		::SelectObject (dc.GetSafeHdc (), hfontOld);
	}
}

void MTable::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL || m_bInAdjustLayout)
	{
		return;
	}

	m_bInAdjustLayout = TRUE;

	if (m_bRebuildTerminalItems)
	{
		ReposItems ();
	}

	SetRowHeight ();
	SetRowHeaderWidth ();

	CRect rectClient;
	GetClientRect (rectClient);

	m_nGroupByBoxHeight = OnGetGroupByBoxRect (NULL, rectClient).Height ();
	m_rectHeader = OnGetHeaderRect (NULL, rectClient);
	m_rectFilterBar = OnGetFilterBarRect (NULL, rectClient);
	m_rectRowHeader = OnGetRowHeaderRect (NULL, rectClient);
	m_rectSelectAllArea = OnGetSelectAllAreaRect (NULL, rectClient);
	m_rectList = OnGetGridRect (NULL, rectClient);

	GetColumnsInfo ().Resize (m_rectList.Width ());

	int cxScroll = m_bScrollVert ? ::GetSystemMetrics (SM_CXVSCROLL) : 0;
	int cyScroll = m_bScrollHorz ? ::GetSystemMetrics (SM_CYHSCROLL) : 0;
	SetScrollSizes ();

	CSize szScroll (0, 0);
	CPoint ptScroll (rectClient.left, rectClient.top);
	if (m_nVertScrollTotal > 0)
	{
		m_rectList.right -= cxScroll;
		m_rectHeader.right -= cxScroll;
		szScroll.cy = rectClient.Height ();

		if (GetColumnsInfo ().IsAutoSize ())
		{
			GetColumnsInfo ().Resize (m_rectList.Width ());
		}
	}
	if (m_nHorzScrollTotal > 0 || m_bScrollHorzShowAlways)
	{
		m_rectRowHeader.bottom -= cyScroll;
		m_rectList.bottom -= cyScroll;
		szScroll.cx = max (0, m_rectRowHeader.Width () + m_rectList.Width ());
		szScroll.cy = max (0, szScroll.cy - cyScroll);
	}

	m_wndScrollVert.EnableScrollBar (szScroll.cy > 0 ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);

	// ScrollBar ������ ���� ����ؼ� AdjustProgressBarCtrl() �� �ѱ��.
	CRect rectContents(rectClient);

	if (szScroll.cy > 0)
	{
		m_wndScrollVert.SetWindowPos (NULL, m_rectList.right, ptScroll.y,
			cxScroll, szScroll.cy, SWP_NOZORDER | SWP_NOACTIVATE);
		rectContents.right = m_rectList.right;
	}
	else
	{
		m_wndScrollVert.SetWindowPos (NULL, 0, 0,
			0, 0, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (szScroll.cx > 0)
	{
		m_wndScrollHorz.SetWindowPos (NULL, ptScroll.x, rectClient.bottom - cyScroll,
			szScroll.cx, cyScroll, SWP_NOZORDER | SWP_NOACTIVATE);
		rectContents.bottom = rectClient.bottom - cyScroll;
	}
	else
	{
		m_wndScrollHorz.SetWindowPos (NULL, 0, 0,
			0, 0, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	m_wndProgressCtrl.AdjustLayout(rectContents, m_rectProgressCtrl);
	if (m_rectProgressCtrl.IsRectEmpty()) m_wndMessageCtrl.AdjustLayout(rectContents);
	else m_wndMessageCtrl.AdjustLayout(CRect());

	OnResizeColumns ();

	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		m_pToolTip->SetToolRect (this, nIdToolTipHeader, m_rectHeader);
	}

	ReposItems ();

	OnPosSizeChanged ();
	m_rectTrackSel = OnGetSelectionRect ();

	CBCGPGridRow* pCurSel = GetCurSel ();
	if (pCurSel != NULL)
	{
		pCurSel->AdjustButtonRect ();
	}

	AdjustFilterBarCtrls ();
	RedrawWindow ();

	m_bInAdjustLayout = FALSE;
}

BOOL MTable::PreTranslateMessage(MSG* pMsg)
{
	if (CBCGPGridCtrl::PreTranslateMessage(pMsg)) return TRUE;

	if (pMsg->message == WM_KEYDOWN)
	{		
		switch (pMsg->wParam)
		{
		case VK_TAB:
		case VK_ESCAPE:
		case VK_RETURN:
			// DockingBar �ȿ� �־����� IsDialogMessage() ���� �Ծ������ ���⼭ Event �߻����� �ش�.			
			OnKeyDown((UINT)pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
			PostMessage(WM_CHAR, pMsg->wParam, pMsg->lParam);
			// TODO: �̰ɷ� �� �ذ�ȴٰ� ���� ����...
			for (HWND hWnd = GetSafeHwnd(); hWnd; hWnd = ::GetParent(hWnd))
			{
				CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
				if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CBCGPBaseControlBar))) return TRUE; 
			}
			break;
		case 0x43:// Ctrl + C
			// MainFrame Accelerator �� �Ծ����. ���⼭ ó��
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
			{
				Copy();
				return TRUE;
			}
			break;
		case 0x56:// Ctrl + V
			// MainFrame Accelerator �� �Ծ����. ���⼭ ó��
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
			{
				Paste();
				return TRUE;
			}
			break;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// MTable message handlers

int MTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndProgressCtrl.Create(WS_CHILD | WS_VISIBLE, CRect(), this, WM_USER);
	m_wndMessageCtrl.Create(WS_CHILD | WS_VISIBLE, CRect(), this, WM_USER + 1);
	LOGFONT logFont;
	globalData.fontRegular.GetLogFont(&logFont);
	logFont.lfHeight = -13;
	m_fontMessageCtrl.CreateFontIndirect(&logFont);
	m_wndMessageCtrl.SetFont(&m_fontMessageCtrl);
	
	// Data �ʱ�ȭ
	GetTableDB()->Initialize();
	GetTableDB()->InitRows();

	// Sorting �� Column �� Cell ����� �ٸ� ������ ǥ���ϴ� ���. ����.
	EnableMarkSortedColumn(FALSE, FALSE); 
	// Enter ������ Edit �����Ҷ� Text Clear �� ���ΰ�
	SetClearInplaceEditOnEnter(FALSE);
	// ù Ŭ���� �ٷ� Inplace Edit ����
	SetEditFirstClick(FALSE);
	// 
	EnableInvertSelOnCtrl ();

	// InsertColumn, Align ����. InitializeTable() ���� ȣ��.
	InitializeColumns();
	m_pDataRecordInfo->Initialize(1, GetColumnCount());
	// ���̺� �ʱ�ȭ
	if( !InitializeTable() ) ASSERT(0);
	CheckItemType();

	// VirtualMode ����
	EnableVirtualMode(StaticGridCallback, (LPARAM)this);
	UpdateRowCount();

	//AdjustLayout ();

	return 0;
}

void MTable::OnDestroy() 
{
	CBCGPGridCtrl::OnDestroy();
	GetTableDB()->DestroyRows();
	GetTableDB()->Finalize();
}

void MTable::OnPaint() 
{
	CPaintDC dcPaint(this);

	CRgn rgn;
	if (!m_rectProgressCtrl.IsRectEmpty())
	{
		CRect rectClient;
		CRgn rgnClient;
		CRgn rgnProgress;
		GetClientRect(&rectClient);
		rgnClient.CreateRectRgnIndirect(&rectClient);
		rgnProgress.CreateRectRgnIndirect(&m_rectProgressCtrl);
		rgn.CreateRectRgn(0, 0, 0, 0);
		rgn.CombineRgn(&rgnClient, &rgnProgress, RGN_DIFF);
		dcPaint.SelectClipRgn(&rgn);
	}

	OnDraw(&dcPaint);
}

void MTable::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_DELETE:
		if (!IsReadOnly() && m_canDeleteRow)
		{
			DeleteSelRows();
			return;
		}
		break;
	case VK_ESCAPE:
		if (IsEditingRow())
		{
			MGridRow* pRow = (MGridRow*)GetRow(GetEditingRow());
			ASSERT_VALID(pRow);
			OnCancelEditingRow(pRow);
			return;
		}
		break;
	case VK_HOME:
		if (IsEditingRow())
		{
			// �����߿��� ���� Row �ȿ����� ��� �Ѵ�.
			CBCGPGridItemID idItem(m_nEditingRow, GetColumnsInfo().GetFirstVisibleColumn());
			if (!SetCurSel(idItem, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP)) return;
			EnsureVisible(GetRow(idItem.m_nRow));
			return;
		}
		break;
	case VK_END:
		if (IsEditingRow())
		{
			// �����߿��� ���� Row �ȿ����� ��� �Ѵ�.
			CBCGPGridItemID idItem(m_nEditingRow, GetColumnsInfo().GetLastVisibleColumn());
			if (!SetCurSel(idItem, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP)) return;
			EnsureVisible(GetRow(idItem.m_nRow));
			return;
		}
		break;
	case VK_INSERT:
		// TODO: Append Row �� ����
		break;
	default:
		break;
	}

	CBCGPGridCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

CBCGPDockingControlBar* MTable::GetParentBar() const
{
	CWnd* pParent = GetParent();
	if (pParent->IsKindOf(RUNTIME_CLASS(CBCGPTabWnd))) pParent = pParent->GetParent();
	return DYNAMIC_DOWNCAST(CBCGPDockingControlBar, pParent);
}

BOOL MTable::IsMDITabbed() const
{
	CBCGPDockingControlBar* pBar = GetParentBar();
	if (!pBar) return FALSE;
	return pBar->IsMDITabbed();
}

BOOL MTable::IsSortingMode () const
{
	BOOL bMerge = ( m_pDataRecordInfo->m_arMerge.GetSize() > 0 ) ?  TRUE : FALSE;

	if ( !bMerge ) return FALSE;

	return (GetColumnsInfo ().GetSortColumnCount () > 0);
}

void MTable::MakeContextMenu(CMenu& menu)
{
	BOOL bMerge = ( m_pDataRecordInfo->m_arMerge.GetSize() > 0 ) ?  TRUE : FALSE;

	menu.AppendMenu(MF_STRING, ID_TB_COPY, _T("Copy"));
	menu.AppendMenu(MF_STRING, ID_TB_PASTE, _T("Paste"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_FIND, _T("Find..."));
	if( !bMerge ) menu.AppendMenu(MF_STRING, ID_TB_SORT, _T("Sort..."));
	menu.AppendMenu(MF_STRING, ID_TB_STYLE, _T("Style..."));
	menu.AppendMenu(MF_STRING, ID_TB_ACTIVE_DIALOG, _T("Active Dialog..."));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_GRAPH, _T("Graph..."));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_EXPORT_TO_EXCEL, _T("Export to Excel"));
}

void MTable::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting)
	{
		return;
	}

	SetEndEditReason (EndEdit_Cancel | EndEdit_Layout);
	EndEditItem (FALSE);

	int nPrevOffset = m_nHorzScrollOffset;

	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_TRACKPOS;

	if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
	{
		GetScrollInfo(SB_HORZ, &info);
		nPos = info.nTrackPos;
	}

	switch (nSBCode)
	{
	case SB_LINEUP:
		m_nHorzScrollOffset -= max (1, m_nBaseHeight);
		break;

	case SB_LINEDOWN:
		m_nHorzScrollOffset += max (1, m_nBaseHeight);
		break;

	case SB_TOP:
		m_nHorzScrollOffset = 0;
		break;

	case SB_BOTTOM:
		m_nHorzScrollOffset = m_nHorzScrollTotal;
		break;

	case SB_PAGEUP:
		m_nHorzScrollOffset -= m_nHorzScrollPage;
		break;

	case SB_PAGEDOWN:
		m_nHorzScrollOffset += m_nHorzScrollPage;
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		m_nHorzScrollOffset = nPos;
		break;

	default:
		return;
	}

	m_nHorzScrollOffset = min (max (0, m_nHorzScrollOffset), 
		m_nHorzScrollTotal - m_nHorzScrollPage + 1);

	if (m_nHorzScrollOffset == nPrevOffset)
	{
		return;
	}

	OnUpdateHScrollPos (m_nHorzScrollOffset, nPrevOffset);

	SetScrollPos (SB_HORZ, m_nHorzScrollOffset);

	int dx = nPrevOffset - m_nHorzScrollOffset;

	CRect rectClip = m_rectList;
	if (GetColumnsInfo ().IsFreezeColumnsEnabled ())
	{
		rectClip.left = min (m_rectList.left + GetColumnsInfo ().GetFreezeOffset (), m_rectList.right);
	}

	ShiftItems (dx, 0);
	OnPosSizeChanged ();
	m_rectTrackSel = OnGetSelectionRect ();

	if (m_bFreezeGroups || GetMessageCtrl()->IsShowing())
	{
		InvalidateRect (m_rectList);
	}
	else
	{
		ScrollWindow (dx, 0, m_rectList, rectClip);
	}

	OnAfterHScroll (m_nHorzScrollOffset, nPrevOffset);

	if (!m_rectHeader.IsRectEmpty ())
	{
		RedrawWindow (m_rectHeader);
	}

	if (m_nGridHeaderHeight > 0)
	{
		RedrawWindow (GetGridHeaderRect ());
	}

	if (m_nGridFooterHeight > 0)
	{
		RedrawWindow (GetGridFooterRect ());
	}

	AdjustFilterBarCtrls ();

	if (!m_rectFilterBar.IsRectEmpty ())
	{
		RedrawWindow (m_rectFilterBar);
	}
}

void MTable::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting)
	{
		return;
	}

	CBCGPGridRow* pSel = GetCurSel ();

	if (pSel != NULL && 
		pScrollBar->GetSafeHwnd () != NULL)
	{
		CSpinButtonCtrl* pWndSpin = pSel->GetSpinWnd ();
		if (pWndSpin != NULL && 
			pWndSpin->GetSafeHwnd () == pScrollBar->GetSafeHwnd ())
		{
			return;
		}
	}

	SetEndEditReason (EndEdit_AutoApply | EndEdit_Layout);
	EndEditItem ();

	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_TRACKPOS;

	if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
	{
		GetScrollInfo(SB_VERT, &info);
		nPos = info.nTrackPos;
	}

	int nPrevOffset = m_nVertScrollOffset;

	int nVertScrollPage = m_nVertScrollPage;
	if (m_bVirtualMode)
	{
		int nItemsCount = max (1, m_nVertScrollPage / m_nRowHeight);
		nVertScrollPage = nItemsCount * m_nRowHeight;
	}

	switch (nSBCode)
	{
	case SB_LINEUP:
		m_nVertScrollOffset -= m_nRowHeight;
		break;

	case SB_LINEDOWN:
		m_nVertScrollOffset += m_nRowHeight;
		break;

	case SB_TOP:
		m_nVertScrollOffset = 0;
		break;

	case SB_BOTTOM:
		m_nVertScrollOffset = m_nVertScrollTotal;
		break;

	case SB_PAGEUP:
		m_nVertScrollOffset -= nVertScrollPage;
		break;

	case SB_PAGEDOWN:
		m_nVertScrollOffset += nVertScrollPage;
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		m_nVertScrollOffset = nPos;
		break;

	default:
		return;
	}

	m_nVertScrollOffset = max (0, min (m_nVertScrollOffset, 
		m_nVertScrollTotal - nVertScrollPage + 1));
	if (m_bVirtualMode)
	{
		// row alignment
		int nResidue = m_nVertScrollOffset % m_nRowHeight;
		if (nResidue > 0)
		{
			m_nVertScrollOffset -= nResidue;
			if (m_nVertScrollOffset + m_nVertScrollPage < m_nVertScrollTotal)
			{
				m_nVertScrollOffset += m_nRowHeight;
			}
		}
	}

	if (m_nVertScrollOffset == nPrevOffset)
	{
		return;
	}

	OnUpdateVScrollPos (m_nVertScrollOffset, nPrevOffset);

	SetScrollPos (SB_VERT, m_nVertScrollOffset);

	int dy = nPrevOffset - m_nVertScrollOffset;

	ShiftItems (0, dy);
	OnPosSizeChanged ();
	m_rectTrackSel = OnGetSelectionRect ();
	if (!GetMessageCtrl()->IsShowing())
	{
		// Message �� ����
		ScrollWindow (0, dy, m_rectList, m_rectList);
		ScrollWindow (0, dy, m_rectRowHeader, m_rectRowHeader);
	}

	pSel = GetCurSel ();
	if (pSel != NULL)
	{
		pSel->AdjustButtonRect ();
	}

	OnAfterVScroll (m_nVertScrollOffset, nPrevOffset);

	UpdateWindow ();
}

void MTable::OnKillFocus(CWnd* pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	BOOL bIsParentView =
		pNewWnd != nullptr &&
		pNewWnd->IsKindOf (RUNTIME_CLASS (CBCGPGridView)) &&
		GetParent ()->GetSafeHwnd () == pNewWnd->GetSafeHwnd ();

	ASSERT(m_pColumnChooser == nullptr);
	//HWND hwndColumnChooser = 
	//	(m_pColumnChooser != NULL) ? m_pColumnChooser->GetSafeHwnd () : NULL;

	if (pNewWnd->GetSafeHwnd() == NULL ||
		(pNewWnd != this && !bIsParentView && !IsChild(pNewWnd)))
	{
		if (IsEditingRow())
		{
			MGridRow* pRow = (MGridRow*)GetRow(m_nEditingRow);
			ASSERT_VALID(pRow);
			if (!OnEndEditRow(pRow))
			{
				// TODO: ���� �ٲ�� �� �� ������...
				SetFocus();
				return;
			}
		}
	}
}

void MTable::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (CBCGPPopupMenu::GetActiveMenu () != NULL) return;

	CMenu menu;
	menu.CreatePopupMenu();
	MakeContextMenu(menu);
	if (IsMDITabbed())
	{		
		if (menu.GetMenuItemCount() > 0)
		{
			menu.InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR );
		}
		menu.InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_CHECKED, ID_TB_TABBED_DOCUMENT, _T("Tabbed Document"));
	}
	
	CWnd* pParentOwner = pWnd->GetParentOwner();
	if (pParentOwner && pParentOwner->IsKindOf(RUNTIME_CLASS(CDialog)))
	{
		// �׳� Dialog ������ Context Menu �� ������� �ʱ⸦ ��õ...
		// �� ����Ѵٸ�............ �� ��Ե� �ذ��� �ؾ��ҵ�..
		UINT nID = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, point.x, point.y, pWnd);
		if (nID > 0) SendMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);  
		return;
	}
	HMENU hMenu = menu.Detach ();
	
	CBCGPWorkspace* pWorkspace = GetWorkspace();
	ASSERT(pWorkspace);
	CBCGPContextMenuManager* pContextMenuManager = pWorkspace->GetContextMenuManager();
	ASSERT(pContextMenuManager);
	pContextMenuManager->ShowPopupMenu(hMenu, point.x, point.y, pWnd, TRUE);
	//UINT nID = pContextMenuManager->TrackPopupMenu(hMenu, point.x, point.y, ppppWnd
	//if (nID > 0) SendMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);
}

void MTable::OnTabbedDocument()
{
	CBCGPDockingControlBar* pBar = GetParentBar();
	if (!pBar) { ASSERT(0); return; }
	ASSERT(pBar->IsMDITabbed());

	CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pBar->GetParent());
	if (!pMDIChild) { ASSERT(0); return; }
	CBCGPMDIFrameWnd* pFrame = DYNAMIC_DOWNCAST(CBCGPMDIFrameWnd, pBar->GetDockSite());
	if (!pFrame) { ASSERT(0); return; }
	pFrame->TabbedDocumentToControlBar(pMDIChild);
}

void MTable::OnCopy()
{
	Copy();
}

void MTable::OnPaste()
{
	Paste();
}

void MTable::OnFind()
{
	ShowFindDialog();
}

void MTable::OnSort()
{
	ShowSortDialog();
}

void MTable::OnStyle()
{
	ShowStyleDialog();
}

void MTable::OnActiveDialog()
{
	ShowActiveDialog();
}

void MTable::OnGraph()
{
	ShowGraphDialog();
}

void MTable::OnExportToExcel()
{
	MTableExportToExcel exporter;
	exporter.ExportExcel( this, m_strTableTitle );

	PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);
}

void MTable::OnBtnClicked()
{
	// TODO: �ǽð� Validation Check
	CBCGPGridItem* pItem = GetCurSelItem();
	ASSERT(pItem->GetParentRow());
	if (IsDataRow(pItem->GetGridItemID().m_nRow) || GetDataRowEndIndex() == pItem->GetGridItemID().m_nRow)
	{
		EditItem(pItem->GetParentRow());
	}
	ASSERT(pItem->IsKindOf(RUNTIME_CLASS(MGridItem)));	
	OnButtonClicked((MGridItem*)pItem);
	if (pItem->GetParentRow()) InvalidateRect(pItem->GetParentRow()->GetRect());
}

void MTable::OnEditChanged()
{
	// TODO: �ǽð� Validation Check
}

//////////////////////////////////////////////////////////////////////////
int MTable::CalcRowHeaderWidth (int nRowCount)
{
	CString str;
	str.Format (_T("%d"), nRowCount);

	CClientDC dc (this);
	HFONT hfontOld = SetCurrFont (&dc);

	int nExtent = dc.GetTextExtent (str).cx;
	int nResult = max (30, nExtent + 2 * TEXT_MARGIN);

	::SelectObject (dc.GetSafeHdc (), hfontOld);

	return nResult;
}

void MTable::ShowFindDialog()
{
	if( !OpenFindReplaceDlg(TRUE) )
	{
		ASSERT(0);
	}
}

void MTable::ShowSortDialog()
{
	MTBSortDialog dlg(this);
	dlg.DoModal();
}

void MTable::ShowStyleDialog()
{
	MTBStyleDialog dlg(this);
	dlg.DoModal();
}

void MTable::ShowActiveDialog()
{
	MTBActiveDialog dlg(this);
	dlg.DoModal();
}

void MTable::ShowGraphDialog()
{
	SWITCH_RESOURCE;
	
	MExportToChartDlg dlgExportToChart(this);
	dlgExportToChart.DoModal();
}

int MTable::InsertColumn(int nColumn, LPCTSTR lpszColumn, int nWidth, int iImage, BOOL bHideNameWithImage)
{
	if (CBCGPGridCtrl::InsertColumn(nColumn, lpszColumn, nWidth, iImage, bHideNameWithImage) < 0) return -1;

	CAtlList<TBSortColumn> lstSortcol;
	GetSort()->GetSortColumns(lstSortcol);	
	for (POSITION pos = lstSortcol.GetHeadPosition(); pos; lstSortcol.GetNext(pos))
	{
		if (lstSortcol.GetAt(pos).nColumn >= nColumn)
		{
			lstSortcol.GetAt(pos).nColumn++;
		}
	}
	GetSort()->SetSortColumns(lstSortcol);

	return nColumn;
}

BOOL MTable::DeleteColumn(int nColumn)
{
	if (!CBCGPGridCtrl::DeleteColumn(nColumn)) return FALSE;

	CAtlList<TBSortColumn> lstSortcol;
	GetSort()->GetSortColumns(lstSortcol);	
	for (POSITION pos = lstSortcol.GetHeadPosition(); pos; lstSortcol.GetNext(pos))
	{
		if (lstSortcol.GetAt(pos).nColumn >= nColumn)
		{
			lstSortcol.GetAt(pos).nColumn--;
		}
	}
	GetSort()->SetSortColumns(lstSortcol);

	return TRUE;
}

void MTable::DeleteAllColumns()
{
	CBCGPGridCtrl::DeleteAllColumns();
	GetSort()->RemoveAllSortColumns();
}

void MTable::Sort(int nColumn, BOOL bAscending, BOOL bAdd)
{
	if (!SetCurSel(CBCGPGridItemID(), SM_NONE)) return;
	SetSortColumn(nColumn, bAscending, bAdd);
	if (GetSafeHwnd() != NULL)
	{
		if (GetSort()->Sort())
		{
			MTBSchemaBase* pSchema = GetSchema();
			CAtlList<TBSortColumn> lstSortcol;
			VERIFY(GetSort()->GetSortColumns(lstSortcol) > 0);			
			CString strSortOrder;
			POSITION pos = lstSortcol.GetHeadPosition();
			while (pos)
			{
				TBSortColumn& sc = lstSortcol.GetNext(pos);
				CString strSort;
				if (pos) strSort.Format(_T("%s(%s) - "), pSchema->GetColumn(sc.nColumn).GetDisplayName(), sc.bAscending ? _LSX(��) : _LSX(��));
				else strSort.Format(_T("%s(%s)"), pSchema->GetColumn(sc.nColumn).GetDisplayName(), sc.bAscending ? _LSX(��) : _LSX(��));
				strSortOrder += strSort;
			}
			GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("%d �� �����Ͱ� ���ĵǾ����ϴ�. ���ļ��� : [%s]"), GetDataRowCount(), strSortOrder);
		}
	}
}

void MTable::ToggleSortColumn (int nColumn)
{
	ASSERT_VALID (this);

	if ((m_dwHeaderFlags & BCGP_GRID_HEADER_SORT) == 0)
	{
		return;
	}

	TBSortColumn sortcol(nColumn, FALSE);
	BOOL bSortedCol = GetSort()->GetSortColumn(nColumn, sortcol);

	if (m_bThreeSortToggle)
	{
		if (IsMultipleSort() && bSortedCol && !sortcol.bAscending) // if descending, the third click clears sorting
		{
			RemoveSortColumn(nColumn);
			if (GetSafeHwnd() != NULL)
			{
				SetRebuildTerminalItems();
				ReposItems();
				AdjustLayout();
			}
			return;
		}
	}

	Sort(nColumn, !sortcol.bAscending, IsMultipleSort());
}

void MTable::SetSortColumn(int nColumn, BOOL bAscending, BOOL bAdd)
{
	CBCGPGridCtrl::SetSortColumn(nColumn, bAscending, bAdd);

	if (bAdd)
	{
		GetSort()->AddSortColumn(TBSortColumn(nColumn, bAscending));
	}
	else
	{
		CAtlList<TBSortColumn> lstSortcol;
		lstSortcol.AddTail(TBSortColumn(nColumn, bAscending));
		GetSort()->SetSortColumns(lstSortcol);
	}
}

BOOL MTable::RemoveSortColumn(int nColumn)
{
	CBCGPGridCtrl::RemoveSortColumn(nColumn);
	return GetSort()->RemoveSortColumn(nColumn);
}

void MTable::RemoveAllSortColumns()
{
	// ��� CBCGPGridCtrl���� ���µ� CBCGPGridColumnsInfo �� �־ �������߱������ �־
	// ���� �� ������
	GetColumnsInfo().RemoveAllSortColumns();
	SetRebuildTerminalItems();
	GetSort()->RemoveAllSortColumns();
}

void MTable::EnableMultipleSort(BOOL bEnable)
{
	// ������ MultiSorting �ΰɷ�...
	ASSERT(bEnable);
	CBCGPGridCtrl::EnableMultipleSort(bEnable);
	if (!bEnable)
	{
		GetSort()->RemoveAllSortColumns();
	}
}

CRect MTable::OnGetHeaderRect (CDC* pDC, const CRect& rectDraw)
{
	ASSERT(m_pColumnsEx);

	CRect rect = CBCGPGridCtrl::OnGetHeaderRect (pDC, rectDraw);
	rect.bottom = rect.top + rect.Height () * m_pColumnsEx->GetHeaderLineCount ();

	return rect;
}

void MTable::OnDrawHeader (CDC* pDC)
{
	ASSERT(m_pColumnsEx);
	m_pColumnsEx->PrepareDrawHeader ();

	// BCG ���� Column ���� ClipRgn �� �ϴµ�
	// ���η� Merge �Ǿ� ���� ��� Merge �� ù��° Column �� �׸��� 
	// ClipRgn ������ �� �׷����� �ʰ� �߸���. BCG ����???
	//CBCGPGridCtrl::OnDrawHeader (pDC);

	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	if (m_rectHeader.IsRectEmpty ())
	{
		return;
	}

	CRgn rgnClipHeader;
	rgnClipHeader.CreateRectRgnIndirect (&m_rectHeader);
	pDC->SelectClipRgn (&rgnClipHeader);

	OnFillHeaderBackground (pDC, m_rectHeader);

	const int nFreezeOffset = m_rectList.left + GetColumnsInfo ().GetFreezeOffset ();

	for (int i = 0; i <= GetColumnsInfo ().GetColumnCount(); i++)
	{
		if (i < GetColumnsInfo ().GetColumnCount() &&
			!GetColumnsInfo ().GetColumnVisible (i))
		{
			continue;
		}

		CRect rectColumn;
		GetColumnsInfo ().GetColumnRect (i, rectColumn);
		GetColumnsInfo ().DrawColumn (pDC, i, rectColumn);
	}

	pDC->SelectClipRgn (NULL);
}

void MTable::OnPrintHeader(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pColumnsEx);
	m_pColumnsEx->PreparePrintHeader ();

	CBCGPGridCtrl::OnPrintHeader(pDC, pInfo);
}

void MTable::OnPosSizeChanged ()
{
	CBCGPGridCtrl::OnPosSizeChanged ();

	ASSERT(m_pColumnsEx);
	m_pColumnsEx->ReposHeaderItems ();
}

void MTable::DrawHeaderItem (CDC* pDC, CRect rect, CBCGPHeaderItem* pHeaderItem)
{
	if( pHeaderItem )
	{
		pHeaderItem->m_bMultiLine = m_pColumnsEx->GetHeaderMultiLine(pHeaderItem->m_nColumn);
	}

	CBCGPGridCtrl::DrawHeaderItem( pDC, rect, pHeaderItem );
}

MGridRow* MTable::CreateDummyRow(BOOL bFillDefaultData)
{
	CBCGPGridRow* pRow = CreateRow();
	ASSERT_VALID (pRow);
	ASSERT(pRow->IsKindOf(RUNTIME_CLASS(MGridRow)));
	MGridRow* pGridRow = reinterpret_cast<MGridRow*>(pRow);
	pGridRow->m_pWndList = this;
	
	int nRow = GetExtraTopRowCount(); // DataRow �� ��޹ޱ� ����
	for (int i = 0; i < GetColumnCount() ; i++)
	{
		MGridItem* pItem = reinterpret_cast<MGridItem*>(CreateItem(nRow, i));
		ASSERT_VALID(pItem);
		ASSERT(pItem->IsKindOf(RUNTIME_CLASS(MGridItem)));
		pItem->m_pGridRow = pGridRow;
		pItem->m_nIdColumn = i;
		VERIFY((int)pGridRow->m_arrRowItems.Add(pItem) == i);
	}

	if (bFillDefaultData)
	{
		MTBSchemaBase* pSchema = GetSchema();
		LPCVOID pDefaultData = pSchema->GetDefaultData();
		for (int i = 0; i < pSchema->GetColumnCount(); i++)
		{
			const MTBColumn& column = pSchema->GetColumn(i);
			_variant_t& varValue = const_cast<_variant_t&>(pGridRow->GetItem(i)->GetValue());
			switch (column.GetType())
			{
			case MTBColumn::TB_KEY: varValue = (MKey)0; break;
			case MTBColumn::TB_FOREIGN: ASSERT(0); GetTableDB()->GetForeignItem(varValue, nRow, i); break;
			default: column.GetItem(const_cast<_variant_t&>(pGridRow->GetItem(i)->GetValue()), pDefaultData); break;
			}
		}
	}

	return pGridRow;
}

void MTable::SetEditingRow(int nEditingRow, CBCGPGridRow* pRow)
{
	ASSERT(pRow);
	if (m_nEditingRow == nEditingRow) return;
	ASSERT(m_nEditingRow < 0 || nEditingRow < 0); // �׻� -1 �Ǿ��ٰ� �ٸ� Row �� �����Ѵ�.

	BOOL bEndAppending = IsAppendingRow();
	BOOL bEndModifying = IsModifyingRow();
	m_nEditingRow = nEditingRow;
	if (IsEditingRow())
	{
		m_pEditingCachePage = FindCachePageInfo(m_nEditingRow);
		ASSERT(m_pEditingCachePage);
	}
	else
	{
		m_pEditingCachePage = nullptr;
	}

	if (IsSelectEditingRow())
	{
		if (IsEditingRow())
		{		
			// SetCurSel ���� InPlaceEditing �� ��� EndEdit �ع����Ƿ� �ӽ÷� FALSE �����.
			// MTable::SetCurSel() �� ���� Selection �� ���� ����
			MGridRow* pSel = reinterpret_cast<MGridRow*>(GetCurSel());
			BOOL bInPlaceEditOrg = pSel->m_bInPlaceEdit;
			pSel->m_bInPlaceEdit = FALSE;
			VERIFY(CBCGPGridCtrl::SetCurSel(m_idActive, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP));
			pSel->m_bInPlaceEdit = bInPlaceEditOrg;
			EnsureVisible(pSel);
		}
		else
		{
			// ���� ����
			ASSERT(m_nEditingRow == -1);
			CBCGPGridItemID idItem;
			VERIFY(SetCurSel(m_idActive, SM_NONE));
		}
	}
	
	if (IsAppendingRow())
	{
		m_nVirtualRows = GetRowCount();
		AdjustLayout();
	}
	else if (IsModifyingRow())
	{
		if (IsEditingRowMarkerOnRowHeader())
		{
			// Editing Row Marker �� ǥ���� ���
			// BCG Code ���� Row Header �� Invalidate ������ �ʱ� ������ ����ó��
			// CBCGPGridRow::Redraw() �� non-virtual ��. �Ф�
			CRect rectItem = m_rectRowHeader;
			rectItem.top = pRow->GetRect().top;
			rectItem.bottom = pRow->GetRect().bottom;
			InvalidateRect(rectItem);
		}

		if (!m_bNoUpdateWindow) UpdateWindow();
	}
	else
	{
		// ���� ����
		ASSERT(m_nEditingRow == -1);
		if (bEndAppending)
		{
			m_nVirtualRows = GetRowCount();
			AdjustLayout();
		}
		else if (bEndModifying)
		{
			CRect rectRow = m_rectList;
			rectRow.top = pRow->GetRect().top;
			rectRow.bottom = pRow->GetRect().bottom;
			InvalidateRect(rectRow);

			if (IsEditingRowMarkerOnRowHeader())
			{
				// Editing Row Marker �� ǥ���� ���
				// BCG Code ���� Row Header �� Invalidate ������ �ʱ� ������ ����ó��
				// CBCGPGridRow::Redraw() �� non-virtual ��. �Ф�
				CRect rectItem = m_rectRowHeader;
				rectItem.top = pRow->GetRect().top;
				rectItem.bottom = pRow->GetRect().bottom;
				InvalidateRect(rectItem);
			}

			if (!m_bNoUpdateWindow) UpdateWindow();
		}
		else
		{
			ASSERT(0);
		}
	}
}

CBCGPGridCachePageInfo* MTable::FindCachePageInfo(int nRow)
{
	MTableCache* pCache = reinterpret_cast<MTableCache*>(&m_CachedItems);
	CList<CBCGPGridCachePageInfo, CBCGPGridCachePageInfo&>& lstCache = pCache->m_lstCache;
	for (POSITION pos = lstCache.GetHeadPosition(); pos != NULL; )
	{
		CBCGPGridCachePageInfo& cpi = lstCache.GetNext(pos);
		int nOffset = nRow - cpi.nFirst;
		if (nOffset >= 0 && nOffset < cpi.nSize)
		{
			ASSERT (cpi.nSize == cpi.pArrCachePage->GetSize());
			return &cpi;
		}
	}
	return nullptr;
}

BOOL MTable::OnEditEmptyValue(int nRow, int nColumn, CBCGPGridItem* pItem)
{
	//if (nRow == GetDataRowEndIndex())
	//{
	//	_variant_t varValue;
	//	MTBSchemaBase* pSchema = GetSchema();
	//	const MTBColumn& column = pSchema->GetColumn(nColumn);
	//	switch (column.GetType())
	//	{
	//	case MTBColumn::TB_KEY: ASSERT(0); break; // TODO: Append Row�� Key Column ���� ������
	//	case MTBColumn::TB_FOREIGN: ASSERT(0); break;
	//	default: column.GetItem(varValue, pSchema->GetDefaultData()); break;
	//	}
	//	if (varValue.vt == VT_EMPTY) return FALSE;
	//	pItem->SetValue(varValue, FALSE);	
	//	return TRUE;
	//}

	// �̷��� ó���ؾ��� ��찡 ������ �ʹ�...	
	ASSERT(0);
	if (!IsDataRow(nRow)) return CBCGPGridCtrl::OnEditEmptyValue(nRow, nColumn, pItem);

	_variant_t varValue;
	MTBSchemaBase* pSchema = GetSchema();
	const MTBColumn& column = pSchema->GetColumn(nColumn);
	ASSERT(0); // KEY, FOREIGN
	column.GetItem(varValue, pSchema->GetDefaultData());

	// TODO: GetDefaultData() �� �����͵� DefaultValue �� ä�� �� ���� ��� ���ī�� ������.....
	//       �׳� ������ �ȵǰ�?? 0���� ä���??
	//       ex) CArray 
	if (varValue.vt == VT_EMPTY) return FALSE;
	pItem->SetValue(varValue, FALSE);	

	return TRUE;
}

BOOL MTable::EditItem(CBCGPGridRow* pItem, LPPOINT lptClick)
{
	return CBCGPGridCtrl::EditItem(pItem, lptClick);
}

class CEndEditItem
{ // EndEditItem() ��øȣ�� ����
private: CBCGPGridItem*& m_pEndEditItem;
public: CEndEditItem(CBCGPGridItem*& pEndEditItem, CBCGPGridItem* pCurItem) : m_pEndEditItem(pEndEditItem) { m_pEndEditItem = pCurItem; } 
		~CEndEditItem() { m_pEndEditItem = NULL; }
};

BOOL MTable::EndEditItem(BOOL bUpdateData)
{
	if (m_pEndEditItem) return TRUE;
	CEndEditItem endEditItem(m_pEndEditItem, GetCurSelItem());
	return CBCGPGridCtrl::EndEditItem(bUpdateData);
}

BOOL MTable::ValidateItemData(CBCGPGridRow* pRow)
{
	// ���� GridItem �� Value�� �ٲ��� ���� �����̱� ������
	// ���� Item �� ã�� Item�� m_pWndInPlace �� WindowText�� ���ͼ� Parsing �� ���� Check �ؾ���.
	return TRUE;
}

BOOL MTable::SetCurSel(CBCGPGridItemID idItem, DWORD dwSelMode, BOOL bRedraw)
{
	ASSERT_VALID (this);

	if ( m_idLastSel == idItem && !(dwSelMode == SM_NONE) && 
		!( ((SM_ALL | SM_COLUMN | SM_ROW | SM_SINGLE_ITEM | 
		SM_FIRST_CLICK | SM_SECOND_CLICK | SM_INVERT_SEL) & dwSelMode) != 0) ) return FALSE;

	if (IsEditingRow())
	{
		ASSERT(!m_idActive.IsNull());	// ���� Row �� ���µ� Editing ���ϼ� ����

		const int nLastColumn = GetColumnsInfo ().GetLastVisibleColumn ();
		const int nLastRow = GetTotalItems () - 1;

		// ActiveID �� ����Ǵ��� �̸� �Ǵ��ؼ� ActiveID �ٲ�� ���۸� ���
		// �ٸ� ��� Selection �� ���´�.
		BOOL bChangeActiveID = FALSE;

		if ((dwSelMode & SM_ALL) != 0 || idItem.IsAll ())
		{
			// SelectAll - ActiveID �� �����ȴ�.
		}
		else if ((SM_NONE == dwSelMode) || idItem.IsNull () || nLastColumn < 0 || nLastRow < 0)
		{
			// Remove selection
			bChangeActiveID = TRUE;
			idItem.SetNull();
		}
		else if ((dwSelMode & SM_SET_ACTIVE_ITEM) != 0)
		{
			// ���� Row�� �ٲ�
			if (IsItemSelected (idItem))
			{
				bChangeActiveID = TRUE;
			}
		}
		else if ((dwSelMode & SM_FIRST_CLICK) != 0 ||
			(dwSelMode & SM_SINGLE_ITEM) != 0 ||
			(dwSelMode & SM_INVERT_SEL) != 0)
		{
			if ((dwSelMode & SM_INVERT_SEL) != 0 && IsItemSelected (idItem))
			{
				// Invert Selection - ActiveID �� �����ȴ�.
			}
			else if ((dwSelMode & SM_SINGE_SEL_GROUP) != 0)
			{
				// Remove selection, set active item, add selected block
				bChangeActiveID = TRUE;
			}
			else if ((dwSelMode & SM_CONTINUE_SEL_GROUP) != 0)
			{
				// Store previous active item, modify selected block
				// !m_idActive.IsNull() �̸� ActiveID �� ����
			}
			else if ((dwSelMode & SM_ADD_SEL_GROUP) != 0)
			{
				// Store selection, set new active item, add new selected block
				bChangeActiveID = TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else if ((dwSelMode & SM_SECOND_CLICK) != 0)
		{
			// Store previous active item, modify selected block
			// !m_idActive.IsNull() �̸� ActiveID �� ����
		}
		else
		{
			return FALSE;
		}

		ASSERT(m_idActive.m_nRow == m_nEditingRow);
		if (bChangeActiveID)
		{
			ASSERT(!idItem.IsAll());
			if (m_nEditingRow != idItem.m_nRow)
			{
				MGridRow* pRow = (MGridRow*)GetRow(m_nEditingRow);
				ASSERT_VALID(pRow);
				if (!OnEndEditRow(pRow)) return FALSE;
			}
			else
			{
				// ���� Row �ȿ��� ActiveID ���游 ���
				if (idItem.IsNull()) return FALSE;
				dwSelMode = SM_ROW | SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM;
			}
		}
		else
		{
			MGridRow* pRow = (MGridRow*)GetRow(m_nEditingRow);
			ASSERT_VALID(pRow);
			if (!OnEndEditRow(pRow)) return FALSE;
		}
	}

	return CBCGPGridCtrl::SetCurSel(idItem, dwSelMode, bRedraw);
}

BOOL MTable::ValidateItem(MGridRow* pRow)
{
	// ���� BCG �� �ִ� ValidateItemData() �� Item Value �� �ٲ��� ���� ���¿��� �Ҹ��� ������
	// String ���� ���� �Ǵ��ؾ� �ϴ°��� �����ؼ� Item Value �� �ٲ� �ڿ� Validation Check �� �� �ֵ��� ���� �Լ�
	InvalidateRect(pRow->GetRect()); // TODO : �ӽ�
	return TRUE;
}

BOOL MTable::OnUpdateValue(MGridItem* pItem)
{
	// ValidateItemDataAfterUpdateValue() ����ϸ� �Ҹ���.
	// return ���� Validation Check �� ������ �ǹ��̱� ������ (�ٲ� Value �� ����� ���ΰ�)
	// Modify ������ ��찡 �ƴϸ� return TRUE �Ѵ�.
	if (IsAppendingRow()) return TRUE;

	if (CanModifyItem())
	{
		// Item ���� ������ ������ ���
		// DB �� Modify ���ش�.
		CBCGPGridItemID id = pItem->GetGridItemID();
		int nRow = id.m_nRow;
		int nCol = id.m_nColumn;
		// DB �� Modify �ϸ鼭 DB Notify ���� ���� DB �� �� ������ GridItem �� �ٲ��ִ� �� ���� ó��
		if (!GetTableDB()->ModifyItem( GetDBRowIndex(nRow), nCol, const_cast<_variant_t&>(pItem->GetValue()) )) return FALSE;
	}

	return TRUE;
}

BOOL MTable::OnEdit(MGridRow* pRow)
{
	// Item ���� �����Ҷ� �Ҹ�.
	// return FALSE �� ������ ���۵��� ����.
	// return TRUE �� InPlaceEdit �� �����ǰ� ������ ���۵Ǹ� �ش� Row �� �ٽ� �׸���.
	if (pRow->GetRowId() == GetEditingRow()) return TRUE;
	if (pRow->GetRowId() < GetExtraTopRowCount()) return TRUE;
	if (pRow->GetRowId() > GetDataRowEndIndex()) return TRUE;

	// Append Row �� Default Data �޾ƿͼ� Update
	if (IsAppendingRow(pRow->GetRowId())) 
	{
		const MTBSchemaBase* pSchema = GetSchema();
		ASSERT(pSchema->GetColumnCount() == pRow->GetItemCount());
		int nItemCount = pRow->GetItemCount();

		std::vector<_variant_t*> aNewRowItems;
		aNewRowItems.reserve(nItemCount);
		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			aNewRowItems.push_back( &(const_cast<_variant_t&>(pItem->GetValue())) );
		}

		if (!GetTableDB()->GetNewRowItems(aNewRowItems)) 
		{
			for (int i = 0; i < nItemCount; i++) aNewRowItems[i]->Clear();
			return FALSE;
		}

		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			pItem->SetModifiedFlag();
		}

		MTBNoUpdateWindow noUpdate(m_bNoUpdateWindow);
		SetEditingRow(pRow->GetRowId(), pRow);
	}
	else
	{
		// ������ ���
		if (!CanModifyItem())
		{
			MTBNoUpdateWindow noUpdate(m_bNoUpdateWindow);
			SetEditingRow(pRow->GetRowId(), pRow);
		}
	}

	// TODO: ������ ���� ������ ���� �� �ٲ� ��쿡 ���� ó��

	return TRUE;
}

BOOL MTable::OnEndEdit(MGridRow* pRow)
{
	// Item ���� ������ �Ҹ�.
	// return FALSE �� ������ ������ ����.
	// return TRUE �� InPlaceEdit �� ������ ������ �Ϸ�Ǹ� �ش� Row �� �ٽ� �׸���.
	if (IsEditingRow())
	{
		if (m_dwEndEditResult & EndEdit_Cancel)
		{
			// ���� Cell ������ ����ϱ�. Cancel �� ����
			//OnCancelEditingRow(pRow);
		}
	}

	return TRUE;
}

BOOL MTable::OnEndEditRow(MGridRow* pRow)
{
	// Row ������ ������ (Item �� �� ���̶� ������ �� ���� Row �� �ٲ�)
	ASSERT(IsEditingRow());

	if (IsModifyingRow())
	{
		ASSERT(!CanModifyItem());

		const MTBSchemaBase* pSchema = GetSchema();
		ASSERT(pSchema->GetColumnCount() == pRow->GetItemCount());
		int nItemCount = pRow->GetItemCount();

		std::vector<_variant_t*> aModifiedRowItems;
		aModifiedRowItems.reserve(nItemCount);
		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			ASSERT_VALID(pItem);
			aModifiedRowItems.push_back( &(const_cast<_variant_t&>(pItem->GetValue())) );
		}

		if (!GetTableDB()->ModifyRow(GetDBRowIndex(pRow->GetRowId()), aModifiedRowItems)) { EnsureVisible(pRow); return FALSE; }
		for (int i = 0; i < nItemCount; i++) pRow->GetItem(i)->SetModifiedFlag(); // DB Commit �ϸ鼭 ���� �ٲ���� ���� �ֱ� ����
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_COMMIT, _STR("1���� �����Ͱ� �����Ǿ����ϴ�."));
	}
	else if (IsAppendingRow())
	{
		const MTBSchemaBase* pSchema = GetSchema();
		ASSERT(pSchema->GetColumnCount() == pRow->GetItemCount());
		int nItemCount = pRow->GetItemCount();

		std::vector<_variant_t*> aNewRowItems;
		aNewRowItems.reserve(nItemCount);
		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			ASSERT_VALID(pItem);
			aNewRowItems.push_back( &(const_cast<_variant_t&>(pItem->GetValue())) );
		}

		if (!GetTableDB()->AppendRow(aNewRowItems)) { EnsureVisible(pRow); return FALSE; }
		for (int i = 0; i < nItemCount; i++) pRow->GetItem(i)->SetModifiedFlag(); // DB Commit �ϸ鼭 ���� �ٲ���� ���� �ֱ� ����
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_COMMIT, _STR("1���� �����Ͱ� �߰��Ǿ����ϴ�."));
	}
	else
	{
		ASSERT(0);
	}

	MTBNoUpdateWindow noUpdate(m_bNoUpdateWindow);
	EndEditingRow(pRow);

	return TRUE;
}	

BOOL MTable::OnCancelEditingRow(MGridRow* pRow)
{
	ASSERT(IsEditingRow());

	if (IsModifyingRow())
	{
		ASSERT(!CanModifyItem());

		const MTBSchemaBase* pSchema = GetSchema();
		ASSERT(pSchema->GetColumnCount() == pRow->GetItemCount());
		int nItemCount = pRow->GetItemCount();

		std::vector<_variant_t*> aCanceledItems;
		aCanceledItems.reserve(nItemCount);
		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			aCanceledItems.push_back( &(const_cast<_variant_t&>(pItem->GetValue())) );
		}

		if ( !GetTableDB()->GetRow(aCanceledItems, GetDBRowIndex(pRow->GetRowId())) ) return FALSE;

		for (int i = 0; i < nItemCount; i++)
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			pItem->SetModifiedFlag();
		}

		EndEditingRow(pRow);
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("������ ������ ����Ͽ����ϴ�."));
	}
	else if (IsAppendingRow())
	{
		int nItemCount = pRow->GetItemCount();
		for (int i = 0; i < nItemCount; i++) 
		{
			CBCGPGridItem* pItem = pRow->GetItem(i);
			_variant_t& varValue = const_cast<_variant_t&>(pItem->GetValue());
			varValue.Clear();
			pItem->SetModifiedFlag();
		}
		EndEditingRow(pRow);
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("������ �߰��� ����Ͽ����ϴ�."));
	}
	else 
	{
		ASSERT(0);
	}
	
	return TRUE;
}

void MTable::OnButtonClicked(MGridItem* pItem)
{

}

void MTable::DeleteSelRows()
{
	if (IsEditingRow())
	{
		if (!n_canDeleteEditingRow) return;
		MGridRow* pRow = (MGridRow*)GetRow(GetEditingRow());
		CBCGPGridItemID id = m_idActive;
		if (!OnCancelEditingRow(pRow)) return;
		VERIFY(SetCurSel(id, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP));
	}

	// BCG �� RemoveSelectedRows() �� ������ Virtual Mode ������ ���� ó���������.
	// ������ non-virtual �Լ��� ���� �Լ� �����. 
	// (RemoveSelectedRows() �� Cut() ������ ȣ���ϹǷ� ���� �ȵ�. Cut() �� ��������. ������)
	CRBMap<int, std::pair<int, int>> mapRange;
	CRBMap<int, std::pair<int, int>>::CPair* pPair = NULL;
	std::pair<int, int> range(0, 0);
	std::pair<int, int> oldrange(0, 0);

	// �ߺ� ���� ����
	// ����ڰ� �ߺ��� ���� �ǰ� ������ ���ɼ��� ������ ������
	// ���� Row �� ������ �ߺ����� �����ϸ� ���ɿ� ������ ���� ���̴�.
	// ����ڰ� � ��ģ���� ���� �𸣱� ������ �ߺ� �������ش�.
	// Key �� �ߺ������ϴ� �ͺ��ٴ� Range �� �ߺ������ϴ� ���� �������̴�.
	// ��� �̸� �ߺ������ϰ� TableDB ������ �ѱ��.

	// �˰���
	// RBMap �� ���.
	// Key : Row Index
	// Data : Range �� Top, Bottom Index
	// �� Range ���� Top, Bottom Index �� ������ Data (pair<int, int>) �� �����ؼ�
	// Top, Bottom Index �� Key �� �ؼ� Map �� �߰��Ѵ�.
	// �߰��� �� ���� ������ �߰��� Range Data �� ���Ͽ� �ߺ��� ����.
	const CBCGPGridRange* pRange = NULL;
	POSITION pos = m_lstSel.GetHeadPosition();
	while (pos)
	{
		pRange = m_lstSel.GetNext(pos);
		ASSERT(pRange->m_nTop <= pRange->m_nBottom);
		if (pRange->m_nBottom < GetExtraTopRowCount()) continue;
		if (pRange->m_nTop >= GetDataRowEndIndex()) continue;
		if (m_bDeleteSelectedWholeRowOnly && !(pRange->m_nLeft == 0 && pRange->m_nRight == GetColumnCount() - 1)) continue;

		range.first = pRange->m_nTop;
		range.second = pRange->m_nBottom;
		ASSERT(range.second >= GetExtraTopRowCount() && range.first < GetDataRowEndIndex());
		if (range.first < GetExtraTopRowCount()) range.first = GetExtraTopRowCount();
		if (range.second >= GetDataRowEndIndex()) range.second = GetDataRowEndIndex() - 1;
		range.first = GetDBRowIndex(range.first);
		range.second = GetDBRowIndex(range.second);

		if (mapRange.Lookup(range.first, oldrange))
		{
			range.first = oldrange.first;
			range.second = max(oldrange.second, range.second);
			mapRange.RemoveKey(oldrange.first);
			if (oldrange.first != oldrange.second) mapRange.RemoveKey(oldrange.second);
		}

		if (mapRange.Lookup(range.second, oldrange))
		{
			range.first = min(oldrange.first, range.first);
			range.second = oldrange.second;
			mapRange.RemoveKey(oldrange.first);
			if (oldrange.first != oldrange.second) mapRange.RemoveKey(oldrange.second);
		}

		while (TRUE)
		{
			pPair = static_cast<CRBMap<int, std::pair<int, int>>::CPair*>(mapRange.FindFirstKeyAfter(range.first));
			if (pPair)
			{
				if (pPair->m_key < range.second)
				{
					oldrange = pPair->m_value;
					range.first = min(oldrange.first, range.first);
					range.second = max(oldrange.second, range.second);
					mapRange.RemoveKey(oldrange.first);
					if (oldrange.first != oldrange.second) mapRange.RemoveKey(oldrange.second);
					continue;
				}
				else if (pPair->m_value.first < range.first)
				{
					range.first = -1; // �߰����� ���� ǥ��
				}
			}
			break;
		}

		if (range.first >= 0)
		{
			mapRange.SetAt(range.first, range);
			if (range.first != range.second) mapRange.SetAt(range.second, range);
		}
	}

	// Map -> vector
	// vector �� Size - Min: MapSize/2 ~ Max : MapSize
	std::vector<std::pair<int, int>> aRowRanges;			
	aRowRanges.reserve(mapRange.GetCount()); // ���� �����ְ� reserve		
	pos = mapRange.GetHeadPosition();
	while (pos)
	{
		range = mapRange.GetNext(pos)->m_value;
		aRowRanges.push_back(range);
		if (range.first != range.second) 
		{
			ASSERT(pos && mapRange.GetAt(pos)->m_value == range);
			mapRange.GetNext(pos);
		}
	}

	// Delete
	VERIFY(GetTableDB()->DeleteRows(aRowRanges));
}

void MTable::EnsureVisible(CBCGPGridRow* pItem, BOOL bExpandParents)
{
	// SelCurSel �����ص� ���� �ҳ� �� �Լ��� ȣ���Ѵ�.
	// �� ����� �������ϱ⿡�� ��ġ�� ū �Լ����� ����.
	// ���� ���⼭ Editing Row �� �ƴ� ������ Scroll �Ϸ��ϸ� ���� ������.
	if (IsEditingRow()) 
	{
		CBCGPGridRow* pEditingRow = GetRow(m_nEditingRow);
		ASSERT(pEditingRow);
		if (pItem != pEditingRow) return;
	}
	CBCGPGridCtrl::EnsureVisible(pItem, bExpandParents);
}

BOOL MTable::SelectItems(CPoint ptClient)
{
	if (IsEditingRow()) return FALSE;
	return CBCGPGridCtrl::SelectItems(ptClient);
}

void MTable::OnFilterBarUpdate(int nColumn)
{
	// FilterBar ��� �����Ѵ�.
	// Ȥ�� ���� ����ϰ� �Ǹ� Editing ���¿� ���� ó��
	ASSERT(IsEditingRow());
	CBCGPGridCtrl::OnFilterBarUpdate(nColumn);
}

void MTable::OnEndInplaceEdit(CBCGPGridItem* pItem)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pItem);

	CWnd* pOwner = GetOwner();
	if (!pOwner) return;

	CBCGPGridItemID id = pItem->GetGridItemID();

	memset(&m_CurrentItemInfo, 0, sizeof (BCGPGRID_ITEM_INFO));

	m_CurrentItemInfo.pItem = pItem;
	m_CurrentItemInfo.nRow = id.m_nRow;
	m_CurrentItemInfo.nCol = id.m_nColumn;
	m_CurrentItemInfo.dwResultCode = m_dwEndEditResult;

	ClearBeginEditReason ();
	ClearEndEditReason ();

	// this �� ������
	this->PostMessage(BCGM_GRID_ITEM_ENDINPLACEEDIT, GetDlgCtrlID (), LPARAM (&m_CurrentItemInfo));
}

BOOL MTable::IsAcceleratorKey(UINT nChar, UINT nRepCnt, UINT nFlags) const
{
	if (CBCGPGridCtrl::IsAcceleratorKey(nChar, nRepCnt, nFlags)) return TRUE;
	return FALSE;
}

BOOL MTable::CanBeginInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const
{
	if (IsAcceleratorKey (nChar, nRepCnt, nFlags)) return FALSE;
	if (nChar == VK_ESCAPE) return FALSE;
	if (nChar == VK_TAB) return FALSE;
	return TRUE;
}

BOOL MTable::CanEndInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const
{
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_F4:
		return TRUE;
	case VK_RETURN:
		{
			const BOOL bShift = (::GetAsyncKeyState (VK_SHIFT) & 0x8000) != 0;
			const BOOL bCtrl = (::GetAsyncKeyState (VK_CONTROL) & 0x8000) != 0;
			return (!bShift && !bCtrl); // If SHIFT or CONTROL - continue edit
		}
	}
	return FALSE;
}

BOOL MTable::OnInplaceEditKeyDown(CBCGPGridRow* pSel, MSG* pMsg)
{
	// TODO: OutputDebug �������� ���� �����
	CString str;
	str.Format(_T("OnInplaceEditKeyDown: %d, %d\n"), pMsg->wParam, pMsg->lParam);
	OutputDebugString(str);

	return CBCGPGridCtrl::OnInplaceEditKeyDown(pSel, pMsg);
}

UINT MTable::OnInplaceEditSetSel(CBCGPGridItem* pCurItem, UINT nReason) const
{
	if ((nReason & BeginEdit_Return) != 0) return SetSel_SelectAll;
	if ((nReason & BeginEdit_ComboReturn) != 0) return SetSel_SelectAll;
	return SetSel_CaretAtLeft;
}

void MTable::DoInplaceEditSetSel(UINT nFlags)
{
	CBCGPGridCtrl::DoInplaceEditSetSel(nFlags);
}

void MTable::OnEasyInput(MGridItem* pItem, DWORD_PTR dwResultCode)
{
	ASSERT(m_bEasyInput);
	ASSERT((dwResultCode & EndEdit_KeyMask) == EndEdit_Return); // ���� Return �� ����

	ASSERT_VALID(pItem);
	CBCGPGridItemID id = pItem->GetGridItemID();
	int nLastColumn = GetColumnCount() - 1;
	int nLastRow = GetRowCount() - 1;
	
	if (id.m_nColumn < nLastColumn)
	{
		id.m_nColumn++;
		SetCurSel(id);
	}
	else
	{
		id.m_nRow++;
		id.m_nColumn = 0;
		SetCurSel(id);
	}

	//UINT nDirection = OnGridKeybordNavigation (pii->pItem, pii->dwResultCode);
	//if (nDirection != NoMove)
	//{
	//  GoToNextItem (nDirection);
	//	ContinueInplaceEditing ();
	//}

	ContinueInplaceEditing();
}

void MTable::ContinueInplaceEditing()
{
	CBCGPGridItem* pItem = GetCurSelItem();
	if (pItem && pItem->GetInPlaceWnd() == NULL)
	{
		SendMessage(WM_KEYDOWN, VK_F2);
	}
}

BOOL MTable::SendDispInfoRequest (BCGPGRID_DISPINFO* pdi) const
{
	ASSERT (pdi != NULL);

	pdi->item.varValue.Clear ();

	if( m_pUserData )
	{
		m_pUserData->Clear();
		pdi->item.dwData = (DWORD_PTR)m_pUserData;
	}
	else
		pdi->item.dwData = 0;

	pdi->item.iImage = -1;
	pdi->item.clrBackground = m_ColorData.m_clrBackground;
	pdi->item.clrText = m_ColorData.m_clrText;
	memset (&pdi->item.lfFont, 0, sizeof (LOGFONT));

	if (m_pfnCallback != NULL)
	{
		return m_pfnCallback (pdi, m_lParamCallback);
	}
	else
	{
		// Send the notification message
		pdi->hdr.hwndFrom = m_hWnd;
		pdi->hdr.idFrom   = GetDlgCtrlID();
		pdi->hdr.code     = BCGPGN_GETDISPINFO;

		CWnd* pOwner = GetOwner ();

		if (pOwner != NULL && IsWindow(pOwner->m_hWnd))
		{
			return (BOOL) pOwner->SendMessage (	WM_NOTIFY, 
				pdi->hdr.idFrom, (LPARAM)pdi);
		}
	}

	return FALSE;

}

CBCGPGridRow* MTable::CreateVirtualRow(int nRowIndex)
{
	// EditingRow �� Cache �� ��� �����ǵ��� bReferenced �� ��� TRUE �� ����� �ش�.
	// (Cache ���� ������ �����ǰ� �Ұ����ϰ� BCG �� �����Ǿ� �־ ����� �ذ�å�� �ƴ����� �̷��Զ� �Ѵ�.)
	ASSERT(GetEditingRow() != nRowIndex);
	if (m_pEditingCachePage) 
	{
		MTableCache* pCache = reinterpret_cast<MTableCache*>(&m_CachedItems);
		CList<CBCGPGridCachePageInfo, CBCGPGridCachePageInfo&>& lstCache = pCache->m_lstCache;
		if (m_pEditingCachePage != &lstCache.GetHead())
		{
			lstCache.AddHead(*m_pEditingCachePage);
			POSITION pos = lstCache.GetHeadPosition();
			for (lstCache.GetNext(pos); pos && m_pEditingCachePage != &lstCache.GetAt(pos); lstCache.GetNext(pos));
			ASSERT(pos);
			lstCache.RemoveAt(pos);
			m_pEditingCachePage = &lstCache.GetHead();
			m_pEditingCachePage->bReferenced = TRUE;
		}
	}
	return CBCGPGridCtrl::CreateVirtualRow(nRowIndex);
}

CBCGPGridRow* MTable::OnCreateVirtualRow (BCGPGRID_DISPINFO *pdi)
{
	ASSERT_VALID (this);
	ASSERT (pdi != NULL);

	int nRow = pdi->item.nRow;

	CBCGPGridRow* pRow = CreateRow ();
	ASSERT_VALID (pRow);

	ASSERT(pRow->IsKindOf(RUNTIME_CLASS(MGridRow)));
	MGridRow* pGridRow = reinterpret_cast<MGridRow*>(pRow);

	pGridRow->m_pWndList = this;
	pGridRow->m_nIdRow = nRow;
	pGridRow->m_dwData = pdi->item.dwData;

	return pRow;
}

CBCGPGridItem* MTable::OnCreateVirtualItem (BCGPGRID_DISPINFO *pdi)
{
	ASSERT_VALID (this);
	ASSERT (pdi != NULL);

	// ���� �����Ͱ� Null �̸� ������ �ȵ�. �߸��� ����.
	ASSERT(pdi->item.dwData);	
	MDISPINFO_USERDATA* pUserData = reinterpret_cast<MDISPINFO_USERDATA*>(pdi->item.dwData);
	ASSERT(pUserData);
	
	MGridItem* pItem = NULL;
	if( pUserData->m_pGridItem )
	{
		pItem = pUserData->m_pGridItem;
		ASSERT_VALID (pItem);
		if (!pItem->OnCreate (pdi->item.nRow, pdi->item.nCol))
		{
			delete pItem;
			return NULL;
		}

		pItem->OnEndEdit ();
		if (pItem->m_varValue.vt == VT_EMPTY) pItem->m_varValue = pdi->item.varValue;
		//pItem->Init ();
		//pItem->SetFlags ();

		pItem->m_nIdColumn = pdi->item.nCol;
		pItem->m_dwData = pdi->item.dwData;
		pItem->m_clrBackground = pdi->item.clrBackground;
		pItem->m_clrText = pdi->item.clrText;
		pItem->m_iImage = pdi->item.iImage;
	}
	else
	{
		pItem = DYNAMIC_DOWNCAST(MGridItem, CBCGPGridCtrl::OnCreateVirtualItem (pdi));
	}
	ASSERT(pItem);
	ASSERT(pItem->IsKindOf(RUNTIME_CLASS(MGridItem)));

	pItem->m_bAllowEdit = pUserData->m_bAllowEdit;
	pItem->m_bEnabled = pUserData->m_bEnabled;

	pItem->m_bBold = pUserData->m_bBold;
	pItem->m_bItalic = pUserData->m_bItalic;
	pItem->m_bUnderline = pUserData->m_bUnderline;
	pItem->m_bStrikeOut = pUserData->m_bStrikeOut;

	return pItem;
}

CBCGPGridRow* MTable::CreateRow ()
{
	return new mit::frx::MGridRow (0, 0, GetRowBlockSize ());
}

CBCGPGridItem* MTable::CreateItem (int nRow, int nColumn)
{
	MGridItem* pItem = NULL;

	CRuntimeClass* pItemRTC = NULL;
	if (IsDataRow(nRow) || (m_canAppendRow && nRow >= GetDataRowEndIndex()))
	{
		CRuntimeClass* pItemRTC = NULL;
		if (m_mapItemsRTC.Lookup (nColumn, pItemRTC))
		{
			ASSERT (pItemRTC != NULL);
			pItem = DYNAMIC_DOWNCAST (MGridItem, pItemRTC->CreateObject ());
		}
		else if (m_pDefaultItemRTC != NULL)
		{
			pItem = DYNAMIC_DOWNCAST (MGridItem, m_pDefaultItemRTC->CreateObject ());
		}
		else
		{
			const MTBColumn& column = GetSchema()->GetColumn(nColumn);
			if (m_bCreateCheckItem && column.IsBooleanType())
			{
				pItem = new MGridCheckItem();
			}
			else if (m_bCreateComboItem && column.HasDataMap())
			{
				pItem = new MGridDataMapComboItem(column.GetDataMap());
			}
			else
			{
				pItem = new MGridItem();
			}
		}
	}

	if (!pItem)
	{
		if (m_pDefaultItemRTC != NULL)
		{
			pItem = DYNAMIC_DOWNCAST (MGridItem, m_pDefaultItemRTC->CreateObject ());
		}
		else
		{
			pItem = new MGridItem();
		}
	}

	if (pItem == NULL)
	{
		ASSERT (FALSE);
		return NULL;
	}
	ASSERT(pItem->IsKindOf(RUNTIME_CLASS(MGridItem)));
	ASSERT_VALID (pItem);

	if (!pItem->OnCreate (nRow, nColumn))
	{
		delete pItem;
		return NULL;
	}

	return pItem;
}

BOOL MTable::MergeRecord(int nRow, MRecordInfo* pInfo)
{
	if( !pInfo || pInfo->m_nRow == 0 || pInfo->m_nColumns == 0 ) return FALSE;

	if( nRow < 0 || nRow > GetRowCount() ) return FALSE;

	nRow += 1;

	int nMod = nRow % pInfo->m_nRow;

	if( pInfo == m_pDataRecordInfo )
	{
		nMod = (nRow - GetExtraTopRowCount()) % pInfo->m_nRow;
	}
	else if( pInfo == m_pExtraBottomInfo )
	{
		nMod = (nRow - GetExtraTopRowCount()) % pInfo->m_nRow;
	}

	if( nRow > 0 && nMod == 0 )
	{
		const CArray<CBCGPGridRange*>& arMergeInfo = pInfo->GetMergeInfo();
		for( int i=0; i<(int)arMergeInfo.GetSize(); ++i )
		{
			CBCGPGridRange* pRange = arMergeInfo[i];
			CBCGPGridRange range(pRange->m_nLeft, nRow - pInfo->m_nRow + pRange->m_nTop, pRange->m_nRight, nRow - pInfo->m_nRow + pRange->m_nBottom);
			MergeRange (range, FALSE);
		}
	}

	return TRUE;
}

void MTable::OnDrawLineNumber(CDC* pDC, CBCGPGridRow* pRow, CRect rect, BOOL bSelected, BOOL bPressed)
{
	if (IsAppendRowMarkerOnRowHeader() && pRow->GetRowId() == GetDataRowEndIndex()) return;
	CBCGPGridCtrl::OnDrawLineNumber(pDC, pRow, rect, bSelected, bPressed);
}

void MTable::OnDrawRowHeaderItem(CDC* pDC, CBCGPGridRow* pBCGGridItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBCGGridItem);

	MGridRow* pItem = DYNAMIC_DOWNCAST(MGridRow, pBCGGridItem);
	ASSERT(pItem);

	if (m_rectRowHeader.IsRectEmpty ())
	{
		return;
	}

	CRect rectHeader = m_rectRowHeader;

	// ----------------------------------
	// Draw row header inside rectHeader:
	// ----------------------------------
	{
		CRect rectItem = rectHeader;
		rectItem.top = pItem->m_Rect.top;
		rectItem.bottom = pItem->m_Rect.bottom;

		CBCGPGridHeaderParams params;
		params.m_nHeaderPart = CBCGPGridHeaderParams::HeaderLeft;
		params.m_pRow = pItem;

		CRect rectInnerBorders;
		CRect rectOuterBorders;
		OnGetHeaderBorders (rectInnerBorders, rectOuterBorders, params);

		params.m_rect = rectItem;
		params.m_rectInnerBorders = rectInnerBorders;
		params.m_rectOuterBorders = rectOuterBorders;
		params.m_nItemSelected = (IsRowSelected (pItem->GetRowId ())) ? CBCGPGridHeaderParams::Selected : CBCGPGridHeaderParams::NotSelected;

		CRect rectClipItem = rectItem;
		rectClipItem.InflateRect (params.m_rectOuterBorders);
		rectClipItem.NormalizeRect ();
		if (rectClipItem.IntersectRect (&rectClipItem, &rectHeader))
		{
			CRgn rgnClipRowHeader;
			rgnClipRowHeader.CreateRectRgnIndirect (&rectClipItem);
			pDC->SelectClipRgn (&rgnClipRowHeader);

			FillHeaderPartBackground (pDC, params);
			DrawHeaderPart (pDC, params);

			if (IsEditingRowMarkerOnRowHeader() && pItem->GetRowId() == GetEditingRow())
			{	
				pItem->OnDrawEditingRowMarker (pDC, rectItem);
			}
			else if (IsAppendRowMarkerOnRowHeader() && (pItem->GetRowId() == GetDataRowEndIndex() + (IsAppendingRow() ? 1 : 0)))
			{	
				pItem->OnDrawAppendRowMarker (pDC, rectItem);				
			}
			else if (IsRowMarkerOnRowHeader () && GetCurSel () == pItem)
			{
				pItem->OnDrawRowMarker (pDC, rectItem);
			}

			pDC->SelectClipRgn (&m_rgnClip);
		}
	}
}

bool MTable::GetColumnFormat(int nCol, MFormatInfo& info)
{
	return ((MGridColumnsInfo*)m_pColumnsEx)->GetColumnFormat(nCol, info);
}

void MTable::SetColumnFormat(int nCol, MFormatInfo& info)
{
	((MGridColumnsInfo*)m_pColumnsEx)->SetColumnFormat(nCol, info);
}

void MTable::SetColumnFormat(int nStartCol, int nEndCol, MFormatInfo& info)
{
	((MGridColumnsInfo*)m_pColumnsEx)->SetColumnFormat(nStartCol, nEndCol, info);
}

BOOL MTable::Find (const CString& strFind, DWORD dwFindMask, DWORD dwFindParamsEx)
{
	ASSERT_VALID (this);

	BCGP_GRID_FINDREPLACE_PARAM findParams (strFind);
	OnPrepareFindReplaceParams (findParams, dwFindMask, dwFindParamsEx);

	if ((dwFindMask & FR_REPLACE) != 0)
	{
		return FALSE;
	}
	else if ((dwFindMask & FR_REPLACEALL) != 0)
	{
		return FALSE;
	}
	else
	{
		CWaitCursor wait;
		CBCGPGridItemID id;

		if (!Search (id, id, findParams))
		{
			return FALSE;
		}

		ASSERT (!id.IsNull ());
		OnTextFound (findParams.lpszFind, id);

		return TRUE;
	}
}

BOOL MTable::Search (CBCGPGridItemID &idPos, CBCGPGridItemID idStart, const BCGP_GRID_FINDREPLACE_PARAM &params)
{
	ASSERT_VALID (this);

	if (params.lpszFind == NULL || params.lpszFind [0] == 0)
	{
		return FALSE;
	}

	CBCGPGridItemID idDefault = (GetCurSelItemID ().IsNull ()) ? CBCGPGridItemID (0, 0) : GetCurSelItemID ();

	if (idStart.IsNull ())
	{
		// use current selection
		idStart = idDefault;
	}

	CBCGPGridItemID idStop = idStart;
	idPos = idStart = GetNextItemID (idStart, params.bNext, params.scanOrder);

	if (idStart.m_nRow < 0)
	{
		idPos.m_nRow = idStart.m_nRow = idStop.m_nRow = (params.bNext) ? 0 : GetTotalItems () - 1;
	}

	if (!IsValidID (idStart))
	{
		return FALSE;
	}

	//-------------
	// Scan by rows:
	//-------------
	if (params.scanOrder == BCGP_GRID_FINDREPLACE_PARAM::ByRows)
	{
		BOOL bShowAllItems = (IsSortingMode () && !IsGrouping ());

		for (int i = idStart.m_nRow; (params.bNext) ? i < GetTotalRowCount() : i >= 0; (params.bNext) ? ++i : --i )
		{
			CBCGPGridRow* pOrgRow = GetVirtualRow(i);
			ASSERT_VALID (pOrgRow);

			MGridRow* pRow = reinterpret_cast<MGridRow*>(pOrgRow);
			ASSERT_VALID (pRow);

			if (bShowAllItems ? 
				!pRow->IsItemFiltered () : pRow->IsItemVisible ()) // show item
			{
				//------------
				// Search row:
				//------------
				if ((params.nLookIn & BCGP_GRID_FINDREPLACE_PARAM::FR_LOOKIN_LABELS) != 0)
				{
					idPos.m_nRow = pRow->GetRowId ();
					if (SearchRow (pRow, idPos.m_nColumn, idStart.m_nColumn, params) != NULL)
					{
						return TRUE;
					}

					idStart.m_nColumn = (params.bNext) ? 0 : GetColumnsInfo ().GetLastVisibleColumn ();
				}

				if ((params.nLookIn & BCGP_GRID_FINDREPLACE_PARAM::FR_LOOKIN_PREVIEW) != 0)
				{
					int nPosPreview = -1;
					if (SearchPreview (pRow, nPosPreview, 0, params))
					{
						idPos.m_nRow = pRow->GetRowId ();
						idPos.m_nColumn = -1;
						return TRUE;
					}
				}
			}
		}
	}

	//-----------------
	// Scan by columns:
	//-----------------
	else if (params.scanOrder == BCGP_GRID_FINDREPLACE_PARAM::ByColumns &&
		(params.nLookIn & BCGP_GRID_FINDREPLACE_PARAM::FR_LOOKIN_LABELS) != 0)
	{
		BOOL bInRange = FALSE;

		int nPos = (params.bNext) ? ((MGridColumnsInfo*)m_pColumnsEx)->Begin () : ((MGridColumnsInfo*)m_pColumnsEx)->GetColumnCount (TRUE) - 1;
		while ((params.bNext) ? nPos != ((MGridColumnsInfo*)m_pColumnsEx)->End () : nPos >= 0)
		{
			int iColumn = (params.bNext) ? ((MGridColumnsInfo*)m_pColumnsEx)->Next (nPos) : ((MGridColumnsInfo*)m_pColumnsEx)->OrderToIndex (nPos--); 
			if (iColumn == -1)
			{
				break; // no more visible columns
			}

			BOOL bIsRangeBound = (iColumn == idStart.m_nColumn);

			if (bIsRangeBound || bInRange)
			{
				//---------------
				// Search column:
				//---------------
				idPos.m_nColumn = iColumn;
				if (SearchColumn (iColumn, idPos.m_nRow, idStart.m_nRow, params))
				{
					return TRUE;
				}

				idStart.m_nRow = (params.bNext) ? 0 : GetTotalRowCount () - 1;
			}

			if (bIsRangeBound)
			{
				bInRange = TRUE;
			}
		}
	}

	return FALSE;
}

CBCGPGridItem* MTable::SearchColumn (int nColumn, int &nPos, int nStart,
									 const BCGP_GRID_FINDREPLACE_PARAM &params)
{
	ASSERT_VALID (this);

	if (nColumn < 0 || nColumn >= GetColumnCount ())
	{
		return NULL;
	}

	BOOL bShowAllItems = (IsSortingMode () && !IsGrouping ());

	for (int i = nStart; (params.bNext) ? i < GetTotalRowCount() : i >= 0; (params.bNext) ? ++i : --i )
	{
		CBCGPGridRow* pOrgRow = GetVirtualRow(i);
		ASSERT_VALID (pOrgRow);

		MGridRow* pRow = reinterpret_cast<MGridRow*>(pOrgRow);
		ASSERT_VALID (pRow);

		if (bShowAllItems ? 
			!pRow->IsItemFiltered () : pRow->IsItemVisible ()) // show item
		{
			//-------------
			// Search item:
			//-------------
			CBCGPGridItem* pItem = pRow->GetItem (nColumn);

			if (pItem != NULL)
			{
				nPos = pRow->GetRowId ();
				if (SearchItem (pItem, params))
				{
					return pItem;
				}
			}
		}
	}

	return NULL;
}

void MTable::UpdateMergeCache()
{
	ASSERT_VALID (this);

	if (m_bVirtualMode)
	{
		MTableCache* pCache = reinterpret_cast<MTableCache*>(&m_CachedItems);
		ASSERT(pCache);

		int nExtraTopSize = m_pExtraTopInfo->m_nRow;
		int nExtraBottomSize = m_pExtraBottomInfo->m_nRow;

		for (POSITION pos = pCache->m_lstCache.GetHeadPosition (); pos != NULL; )
		{
			CBCGPGridCachePageInfo& cpi = pCache->m_lstCache.GetNext (pos);
			ASSERT (cpi.pArrCachePage->GetSize() == cpi.nSize);
			for (int i = 0; i < cpi.nSize; i++)
			{
				int nIndex = cpi.nFirst + i;

				if( nIndex < nExtraTopSize )   // Extra Top
					MergeRecord( nIndex, m_pExtraTopInfo );
				else if( nIndex > GetDataRowEndIndex() )  // Extra Bottom
					MergeRecord( nIndex, m_pExtraBottomInfo );
				else  // Data Record
					MergeRecord( nIndex, m_pDataRecordInfo );
			}
		}
	}
}

void MTable::ReposItems ()
{
	UpdateMergeCache();

	CBCGPGridCtrl::ReposItems();
}

void MTable::ShiftItems (int dx, int dy)
{
	UpdateMergeCache();

	CBCGPGridCtrl::ShiftItems(dx, dy);
}

void MTable::OnEditKillFocus()
{
	MGridRow* pSel = (MGridRow*)GetCurSel ();

	if (pSel != NULL && pSel->m_bInPlaceEdit && pSel->m_bEnabled)
	{
		ASSERT_VALID (pSel);

		if (!IsChild (GetFocus()) && pSel->OnEditKillFocus())
		{
			SetEndEditReason (EndEdit_AutoApply | EndEdit_KillFocus);
			if (!EndEditItem ())
			{
				CWnd* pWndInPlace = pSel->GetInPlaceWnd ();
				if (pWndInPlace != NULL)
				{
					pWndInPlace->SetFocus();
				}
			}
			else
			{
				OnKillFocus(GetFocus());
			}
		}
	}
}

void MTable::OnComboKillFocus()
{
	MGridRow* pSel = (MGridRow*)GetCurSel ();

	if (pSel != NULL && pSel->m_bEnabled)
	{
		ASSERT_VALID (pSel);

		CComboBox* pWndCombo = pSel->GetComboWnd ();
		if (pWndCombo != NULL)
		{
			ASSERT_VALID (pWndCombo);

			if (!IsChild (GetFocus()))
			{
				SetEndEditReason (EndEdit_AutoApply | EndEdit_KillFocus);
				if (!EndEditItem ())
				{
					pWndCombo->SetFocus();
				}
				else
				{
					OnKillFocus(GetFocus());
				}
			}
		}
	}
}

LRESULT MTable::OnUpdate(WPARAM wParam, LPARAM lParam)
{
	MTABLE_MSG msg = (MTABLE_MSG)wParam;
	if( msg == MTable::MSG_REDRAW )
	{
		ReposItems ();

		RedrawWindow ();
	}

	return 0L;
}

LRESULT MTable::OnEndLabelEdit(WPARAM wParam, LPARAM lParam)
{
	BCGPGRID_ITEM_INFO* pii = (BCGPGRID_ITEM_INFO*)lParam;
	ASSERT(pii);
	ASSERT_VALID(pii->pItem);

	if (m_bEasyInput && pii->dwResultCode & m_dwEasyInputFlag)
	{
		OnEasyInput((MGridItem*)pii->pItem, pii->dwResultCode);
	}

	return 0;
}

void MTable::OnAfterHScroll (int nHOffset, int nPrevHOffset)
{
	PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);
}

void MTable::OnAfterVScroll (int nVOffset, int nPrevVOffset)
{
	if( !m_bCallMouseWheel )
		PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);
}

BOOL MTable::Copy(DWORD dwFlags)
{
	ASSERT_VALID(this);
	ITBClipboard* pClipboard = GetTableDB()->GetClipboard();
	return pClipboard->Copy(dwFlags);	
}

BOOL MTable::Paste()
{
	ASSERT_VALID(this);
	ITBClipboard* pClipboard = GetTableDB()->GetClipboard();
	return pClipboard->Paste();
}

void MTable::OnDraw(CDC* pDCPaint)
{
	pDCPaint->GetClipBox (m_rectClip);

	if (m_rectClip.IsRectEmpty ())
	{
		m_rectClip = m_rectList;
	}

	m_rectClip.top = max (m_rectClip.top, m_rectList.top);

	CRect rect;
	GetClientRect (rect);
	rect.right = m_rectList.right;
	rect.bottom = m_rectList.bottom + m_nGridFooterHeight;

	CRect rectGripper;
	GetClientRect (rectGripper);
	rectGripper.left = m_rectList.right;
	rectGripper.top = m_rectList.bottom;
	pDCPaint->FillRect (rectGripper, 
		m_bControlBarColors ? &globalData.brBarFace : &globalData.brBtnFace);

	if (rect.IsRectEmpty ())
	{
		return;
	}
	
	CBCGPMemDC memDC (*pDCPaint, rect);
	CDC* pDC = &memDC.GetDC ();

	// jpahn :�׷����°� ���� ������
	//CDC* pDC = pDCPaint;

	m_clrGray = CBCGPVisualManager::GetInstance()->GetGridLeftOffsetColor (this);

	CRect rectClient;
	GetClientRect (rectClient);

	CRect rectFill = rectClient;
	rectFill.top += m_rectHeader.Height () + m_nGroupByBoxHeight;
	rectFill.left += m_rectRowHeader.Width ();

	OnFillBackground (pDC, rectFill);
	OnFillRowHeaderBackground (pDC, m_rectRowHeader);

	if (m_bFilterBar)
	{
		OnFillFilterBar (pDC);
	}

	HFONT hfontOld = SetCurrFont (pDC);
	pDC->SetTextColor (GetTextColor ());
	pDC->SetBkMode (TRANSPARENT);

	CRect rectList = m_rectList;
	rectList.left = m_rectRowHeader.left;
	m_rectClip.NormalizeRect ();
	BOOL bDrawList = m_rectClip.IntersectRect (&rectList, &m_rectClip);

	m_rgnClip.CreateRectRgnIndirect (m_rectClip);
	pDC->SelectClipRgn (&m_rgnClip);

	if (bDrawList)
	{
		OnDrawList (pDC);
		OnDrawSelectionBorder (pDC);

		if (m_bDragDrop || m_bDragEnter)
		{
			OnDrawDragMarker (pDC);
			OnDrawDragFrame (pDC);
		}
	}

	pDC->SelectClipRgn (NULL);

	m_rectClip.SetRectEmpty ();
	m_rgnClip.DeleteObject ();

	OnDrawGridHeader (pDC);
	OnDrawGridFooter (pDC);

	CRect rectGroupByBox = rectClient;
	rectGroupByBox.bottom = min (rectGroupByBox.top + m_nGroupByBoxHeight, rectClient.bottom);
	OnDrawGroupByBox (pDC, rectGroupByBox);

	OnDrawSelectAllArea (pDC);
	OnDrawHeader (pDC);

	::SelectObject (pDC->GetSafeHdc (), hfontOld);

	if (m_pColumnChooser == NULL && m_bColumnChooserVisible)
	{
		ShowColumnsChooser ();
	}

	m_wndMessageCtrl.OnDraw(pDC);
}

void MTable::OnDrawList (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	CPen* pOldPen = pDC->SelectObject (&m_penVLine);
	ASSERT_VALID (pOldPen);

	int nXLeft = m_rectList.left - m_nHorzScrollOffset;
	int nCount = 0;	// count visible columns
	if (m_bGridLines && !IsKindOf (RUNTIME_CLASS (CBCGPReportCtrl)))
	{
		int nPos = ((MGridColumnsInfo*)m_pColumnsEx)->Begin ();
		while (nPos != ((MGridColumnsInfo*)m_pColumnsEx)->End ())
		{
			int iColumn = ((MGridColumnsInfo*)m_pColumnsEx)->Next (nPos);
			if (iColumn == -1)
			{
				break; // no more visible columns
			}

			ASSERT (iColumn >= 0);
			ASSERT (iColumn < GetColumnsInfo ().GetColumnCount ());

			BOOL bIsTreeColumn = (m_nTreeColumn == -1) ? (nCount == 0):
				(m_nTreeColumn == iColumn);

			int nWidth = GetColumnsInfo ().GetColumnWidth (iColumn);
			if (bIsTreeColumn)
			{
				nWidth += GetHierarchyOffset () + GetExtraHierarchyOffset ();
			}

			nXLeft += nWidth;
			nCount ++;

			if (!m_bGridItemBorders)
			{
				// Draw default vertical grid lines
				pDC->MoveTo (nXLeft - 1, m_rectList.top - 1);
				pDC->LineTo (nXLeft - 1, m_rectList.bottom);
			}
		}
	}

	pDC->SelectObject (&m_penHLine);

	if (m_bVirtualMode)
	{
		int nIndex = m_nVertScrollOffset / m_nRowHeight;

		for (; nIndex < m_nVirtualRows; nIndex++)
		{
			//-----------------
			// Get virtual row:
			//-----------------
			CBCGPGridRow* pRow = GetVirtualRow (nIndex);
			if (pRow == NULL)
			{
				break;
			}

			//----------
			// Draw row:
			//----------
			if (!OnDrawItem (pDC, pRow))
			{
				break;
			}
			OnDrawRowHeaderItem (pDC, pRow);
		}
	}
	else
	{
		CList<CBCGPGridRow*, CBCGPGridRow*>& lst =
			m_bVirtualMode || (!IsSortingMode () && !IsGrouping ()) ? 
m_lstItems : m_lstTerminalItems;

		POSITION pos = m_nFirstVisibleItem == -1 ?
			lst.GetHeadPosition () : lst.FindIndex (m_nFirstVisibleItem);

		while (pos != NULL)
		{
			CBCGPGridRow* pItem = lst.GetNext (pos);
			if (pItem == NULL)
			{
				break;
			}

			ASSERT_VALID (pItem);

			if (!OnDrawItem (pDC, pItem))
			{
				break;
			}
			OnDrawRowHeaderItem (pDC, pItem);
		}
	}

	pDC->SelectObject (pOldPen);

	if( m_lstMergedItemsToRedraw.GetCount() > 0 )
	{
		RedrawMergedItems2 (pDC);
	}
}

BOOL MTable::OnDrawItem (CDC* pDC, CBCGPGridRow* pItem)
{
	ASSERT(pItem->IsKindOf(RUNTIME_CLASS(MGridRow)));
	OnPreDrawRow((MGridRow*)pItem);
	return CBCGPGridCtrl::OnDrawItem(pDC, pItem);
}

void MTable::RedrawMergedItems2 (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	const int nFreezeOffset = m_rectList.left + GetColumnsInfo ().GetFreezeOffset ();

	while (!m_lstMergedItemsToRedraw.IsEmpty ())
	{
		CBCGPGridItem* pItem = m_lstMergedItemsToRedraw.RemoveHead ();
		ASSERT_VALID (pItem);

		CBCGPGridMergedCells* pMerged = pItem->GetMergedCells ();
		ASSERT_VALID (pMerged);

		if (pMerged->IsNeedRedraw ())
		{
			CBCGPGridItemID idMain = pMerged->GetMainItemID ();
			if (pItem->GetGridItemID () != idMain)
			{
				CBCGPGridRow* pRow = (idMain.m_nRow != -1) ? GetRow (idMain.m_nRow) : NULL;
				pItem = (pRow != NULL) ? pRow->GetItem (idMain.m_nColumn) : NULL;

				if (pItem == NULL)
				{
					continue;
				}

				ASSERT_VALID (pItem);
			}

			CRect rectValue = pMerged->GetRect ();
			rectValue.NormalizeRect ();

			CRect rectClipItem = rectValue;

			if (m_bIsPrinting)
			{
				const CRect rectClipPage = m_PrintParams.m_pageInfo.m_rectPageItems;
				if (rectClipItem.IntersectRect (&rectClipItem, &rectClipPage))
				{
					pItem->OnPrintValue (pDC, rectValue);
					pItem->OnPrintBorders (pDC, rectValue);
				}

				pMerged->SetNeedRedraw (FALSE);
				continue;
			}

			CRect rectBordersSize (0, 0, 0, 0);
			if (m_bGridItemBorders)
			{
				pItem->OnGetBorders (rectBordersSize);
				rectClipItem.InflateRect (rectBordersSize);
			}

			CRect rectClip = m_rectClip;
			rectClip.left += m_rectRowHeader.Width ();
			rectClipItem.IntersectRect (rectClipItem, rectClip);

			// frozen columns:
			if (GetColumnsInfo ().IsFreezeColumnsEnabled ())
			{
				if (rectValue.right > nFreezeOffset)
				{
					// Do not allow unfrozen area to draw inside the frozen area
					rectClipItem.left = max (nFreezeOffset, rectClipItem.left);
				}

				if (pMerged->GetRange ().m_nLeft >= GetColumnsInfo ().GetFrozenColumnCount ())
				{
					if (rectValue.right <= nFreezeOffset)
					{
						rectClipItem.SetRectEmpty ();
					}
				}
			}

			if (!rectClipItem.IsRectEmpty ())
			{
				m_rgnClipItem.CreateRectRgnIndirect (&rectClipItem);
				pDC->SelectClipRgn (&m_rgnClipItem);

				pItem->OnDrawValue (pDC, rectValue);

				if (m_bGridItemBorders)
				{
					pItem->OnDrawBorders (pDC, rectValue);
				}

				if (!pItem->GetButtonRect().IsRectEmpty ())
				{
					pItem->OnDrawButton (pDC, pItem->GetButtonRect());
				}

				pDC->SelectClipRgn (&m_rgnClip);
				m_rgnClipItem.DeleteObject ();
			}

			pMerged->SetNeedRedraw (FALSE);
		}

	}
}

BOOL MTable::OnMouseWheel(UINT /*nFlags*/, short zDelta, CPoint /*pt*/) 
{
	MouseWheelProcess mwp(this);

#ifndef _BCGPGRID_STANDALONE
	if (CBCGPPopupMenu::GetActiveMenu () != NULL)
	{
		return TRUE;
	}
#endif

	if (m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting)
	{
		return FALSE;
	}

	if (m_nVertScrollTotal <= m_nVertScrollPage)
	{
		return FALSE;
	}

	if ((m_fScrollRemainder > 0) != (zDelta > 0))
	{
		m_fScrollRemainder = 0;
	}

	UINT nLinesToScrollUserSetting;
	if (!::SystemParametersInfo (SPI_GETWHEELSCROLLLINES, 0, &nLinesToScrollUserSetting, 0))
	{
		nLinesToScrollUserSetting = 1;
	}

	if(nLinesToScrollUserSetting == WHEEL_PAGESCROLL) // scroll one page at a time
	{
		OnVScroll (zDelta < 0 ? SB_PAGEDOWN : SB_PAGEUP, 0, NULL);

		return TRUE;
	}

	float fTotalLinesToScroll = ((float)zDelta / WHEEL_DELTA) * nLinesToScrollUserSetting + m_fScrollRemainder;

	int nSteps = abs((int)fTotalLinesToScroll);
	m_fScrollRemainder = fTotalLinesToScroll - (int)fTotalLinesToScroll;

	if (m_nMouseWheelSmoothScrollMaxLimit != -1 && nSteps >= m_nMouseWheelSmoothScrollMaxLimit)
	{
		int nNewVertOffset = (zDelta < 0) ? (m_nVertScrollOffset + m_nRowHeight * nSteps): (m_nVertScrollOffset - m_nRowHeight * nSteps);
		OnVScroll (SB_THUMBPOSITION, nNewVertOffset, NULL);
		return TRUE;
	}

	for (int i = 0; i < nSteps; i++)
	{
		OnVScroll (zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0, NULL);
	}

	PostMessage(REG_WM_MTABLE_UPDATE, (WPARAM)MSG_REDRAW, NULL);

	return TRUE;
}

void MTable::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!(m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting))
	{
		CBCGPGridRow::ClickArea clickArea;
		CBCGPGridItemID id;
		CBCGPGridItem* pHitItem = NULL;
		CBCGPGridRow* pHitRow = HitTest(point, id, pHitItem, &clickArea);
		if (pHitItem && pHitItem->IsKindOf(RUNTIME_CLASS(MGridButtonItem))) 
		{
			if (MGridButtonItem::s_pHighlightedItem != pHitItem)
			{
				MGridButtonItem::s_pHighlightedItem = (MGridButtonItem*)pHitItem;
				Invalidate();
			}
		}
		else
		{
			if (MGridButtonItem::s_pHighlightedItem)
			{
				MGridButtonItem::s_pHighlightedItem = NULL;
				Invalidate();
			}
		}
	}
	CBCGPGridCtrl::OnMouseMove(nFlags, point);
}




