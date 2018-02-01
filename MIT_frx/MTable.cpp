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
	//ASSERT(!IsEditingRow()); MainFrame 닫을 때 걸릴 수 밖에 없어서 주석처리
	m_nEditingRow = -1; // ~MGridRow() 에서 편집 중인 Row 해제확인 ASSERT 안걸리도록

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
	// TODO: Selection 이상해질듯...
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
	// virtual 함수 아니지만 덮어버린다.
	ASSERT(!IsEditingRow());
	CBCGPGridCtrl::RemoveAll();
}

void MTable::SetVirtualRows(int nRowsNum)
{
	// virtual 함수 아니지만 덮어버린다.
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
		// 해더는 가운데 정렬
		SetHeaderAlign(i, HDF_CENTER);
		// 왼쪽 정렬 : CString
		// 가운데 정렬 : BOOL, bool
		// 오른쪽 정렬 : MKey, int, UINT, double, float
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
			ASSERT(0); // MTable 에서는 MGridItem 과 그 SubClass 들만 지원
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
				ASSERT(0); // MTable 에서는 MGridItem 과 그 SubClass 들만 지원
				return FALSE;
			}
			const MTBColumn& column = pSchema->GetColumn(nCol);
			if (pItemRTC->IsDerivedFrom(RUNTIME_CLASS(MGridCheckItem)))
			{
				// MGridCheckItem 은 bool, BOOL 타입만 지원
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
	if (nCol < 0) return TRUE;  // Row Header는 Pass 
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

	// ScrollBar 제외한 영역 계산해서 AdjustProgressBarCtrl() 에 넘긴다.
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
			// DockingBar 안에 넣었을때 IsDialogMessage() 에서 먹어버려서 여기서 Event 발생시켜 준다.			
			OnKeyDown((UINT)pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
			PostMessage(WM_CHAR, pMsg->wParam, pMsg->lParam);
			// TODO: 이걸로 다 해결된다고 볼순 없고...
			for (HWND hWnd = GetSafeHwnd(); hWnd; hWnd = ::GetParent(hWnd))
			{
				CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
				if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CBCGPBaseControlBar))) return TRUE; 
			}
			break;
		case 0x43:// Ctrl + C
			// MainFrame Accelerator 가 먹어버림. 여기서 처리
			if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
			{
				Copy();
				return TRUE;
			}
			break;
		case 0x56:// Ctrl + V
			// MainFrame Accelerator 가 먹어버림. 여기서 처리
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
	
	// Data 초기화
	GetTableDB()->Initialize();
	GetTableDB()->InitRows();

	// Sorting 된 Column 의 Cell 배경을 다른 색으로 표시하는 기능. 끈다.
	EnableMarkSortedColumn(FALSE, FALSE); 
	// Enter 눌러서 Edit 시작할때 Text Clear 할 것인가
	SetClearInplaceEditOnEnter(FALSE);
	// 첫 클릭시 바로 Inplace Edit 생성
	SetEditFirstClick(FALSE);
	// 
	EnableInvertSelOnCtrl ();

	// InsertColumn, Align 설정. InitializeTable() 전에 호출.
	InitializeColumns();
	m_pDataRecordInfo->Initialize(1, GetColumnCount());
	// 테이블 초기화
	if( !InitializeTable() ) ASSERT(0);
	CheckItemType();

	// VirtualMode 설정
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
			// 편집중에는 현재 Row 안에서만 놀도록 한다.
			CBCGPGridItemID idItem(m_nEditingRow, GetColumnsInfo().GetFirstVisibleColumn());
			if (!SetCurSel(idItem, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP)) return;
			EnsureVisible(GetRow(idItem.m_nRow));
			return;
		}
		break;
	case VK_END:
		if (IsEditingRow())
		{
			// 편집중에는 현재 Row 안에서만 놀도록 한다.
			CBCGPGridItemID idItem(m_nEditingRow, GetColumnsInfo().GetLastVisibleColumn());
			if (!SetCurSel(idItem, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP)) return;
			EnsureVisible(GetRow(idItem.m_nRow));
			return;
		}
		break;
	case VK_INSERT:
		// TODO: Append Row 로 연결
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
		// Message 를 동일
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
				// TODO: 탭이 바뀌는 건 못 막더라...
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
		// 그냥 Dialog 에서는 Context Menu 를 사용하지 않기를 추천...
		// 꼭 써야한다면............ 뭐 어떻게든 해결을 해야할듯..
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
	// TODO: 실시간 Validation Check
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
	// TODO: 실시간 Validation Check
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
				if (pos) strSort.Format(_T("%s(%s) - "), pSchema->GetColumn(sc.nColumn).GetDisplayName(), sc.bAscending ? _LSX(▲) : _LSX(▼));
				else strSort.Format(_T("%s(%s)"), pSchema->GetColumn(sc.nColumn).GetDisplayName(), sc.bAscending ? _LSX(▲) : _LSX(▼));
				strSortOrder += strSort;
			}
			GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("%d 개 데이터가 정렬되었습니다. 정렬순서 : [%s]"), GetDataRowCount(), strSortOrder);
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
	// 얘는 CBCGPGridCtrl에는 없는데 CBCGPGridColumnsInfo 에 있어서 구색맞추기용으로 넣어봄
	// 쓰일 일 있을듯
	GetColumnsInfo().RemoveAllSortColumns();
	SetRebuildTerminalItems();
	GetSort()->RemoveAllSortColumns();
}

void MTable::EnableMultipleSort(BOOL bEnable)
{
	// 무조건 MultiSorting 인걸로...
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

	// BCG 에서 Column 별로 ClipRgn 을 하는데
	// 가로로 Merge 되어 있을 경우 Merge 된 첫번째 Column 을 그릴때 
	// ClipRgn 때문에 다 그려지지 않고 잘린다. BCG 버그???
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
	
	int nRow = GetExtraTopRowCount(); // DataRow 로 취급받기 위해
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
	ASSERT(m_nEditingRow < 0 || nEditingRow < 0); // 항상 -1 되었다가 다른 Row 로 설정한다.

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
			// SetCurSel 에서 InPlaceEditing 일 경우 EndEdit 해버리므로 임시로 FALSE 만든다.
			// MTable::SetCurSel() 은 벌써 Selection 이 막힌 상태
			MGridRow* pSel = reinterpret_cast<MGridRow*>(GetCurSel());
			BOOL bInPlaceEditOrg = pSel->m_bInPlaceEdit;
			pSel->m_bInPlaceEdit = FALSE;
			VERIFY(CBCGPGridCtrl::SetCurSel(m_idActive, SM_ROW | SM_SINGLE_ITEM | SM_SINGE_SEL_GROUP));
			pSel->m_bInPlaceEdit = bInPlaceEditOrg;
			EnsureVisible(pSel);
		}
		else
		{
			// 편집 종료
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
			// Editing Row Marker 를 표시할 경우
			// BCG Code 에서 Row Header 는 Invalidate 해주지 않기 때문에 직접처리
			// CBCGPGridRow::Redraw() 가 non-virtual 임. ㅠㅜ
			CRect rectItem = m_rectRowHeader;
			rectItem.top = pRow->GetRect().top;
			rectItem.bottom = pRow->GetRect().bottom;
			InvalidateRect(rectItem);
		}

		if (!m_bNoUpdateWindow) UpdateWindow();
	}
	else
	{
		// 편집 종료
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
				// Editing Row Marker 를 표시할 경우
				// BCG Code 에서 Row Header 는 Invalidate 해주지 않기 때문에 직접처리
				// CBCGPGridRow::Redraw() 가 non-virtual 임. ㅠㅜ
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
	//	case MTBColumn::TB_KEY: ASSERT(0); break; // TODO: Append Row를 Key Column 으로 했을때
	//	case MTBColumn::TB_FOREIGN: ASSERT(0); break;
	//	default: column.GetItem(varValue, pSchema->GetDefaultData()); break;
	//	}
	//	if (varValue.vt == VT_EMPTY) return FALSE;
	//	pItem->SetValue(varValue, FALSE);	
	//	return TRUE;
	//}

	// 이렇게 처리해야할 경우가 있을까 싶다...	
	ASSERT(0);
	if (!IsDataRow(nRow)) return CBCGPGridCtrl::OnEditEmptyValue(nRow, nColumn, pItem);

	_variant_t varValue;
	MTBSchemaBase* pSchema = GetSchema();
	const MTBColumn& column = pSchema->GetColumn(nColumn);
	ASSERT(0); // KEY, FOREIGN
	column.GetItem(varValue, pSchema->GetDefaultData());

	// TODO: GetDefaultData() 로 가져와도 DefaultValue 를 채울 수 없는 경우 어뜨카면 좋을꼬.....
	//       그냥 편집이 안되게?? 0으로 채우기??
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
{ // EndEditItem() 중첩호출 방지
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
	// 아직 GridItem 의 Value가 바뀌지 않은 상태이기 때문에
	// 편집 Item 을 찾고 Item의 m_pWndInPlace 의 WindowText를 얻어와서 Parsing 한 다음 Check 해야함.
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
		ASSERT(!m_idActive.IsNull());	// 현재 Row 도 없는데 Editing 중일수 없음

		const int nLastColumn = GetColumnsInfo ().GetLastVisibleColumn ();
		const int nLastRow = GetTotalItems () - 1;

		// ActiveID 가 변경되는지 미리 판단해서 ActiveID 바뀌는 동작만 허용
		// 다른 모든 Selection 은 막는다.
		BOOL bChangeActiveID = FALSE;

		if ((dwSelMode & SM_ALL) != 0 || idItem.IsAll ())
		{
			// SelectAll - ActiveID 는 유지된다.
		}
		else if ((SM_NONE == dwSelMode) || idItem.IsNull () || nLastColumn < 0 || nLastRow < 0)
		{
			// Remove selection
			bChangeActiveID = TRUE;
			idItem.SetNull();
		}
		else if ((dwSelMode & SM_SET_ACTIVE_ITEM) != 0)
		{
			// 현재 Row만 바꿈
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
				// Invert Selection - ActiveID 는 유지된다.
			}
			else if ((dwSelMode & SM_SINGE_SEL_GROUP) != 0)
			{
				// Remove selection, set active item, add selected block
				bChangeActiveID = TRUE;
			}
			else if ((dwSelMode & SM_CONTINUE_SEL_GROUP) != 0)
			{
				// Store previous active item, modify selected block
				// !m_idActive.IsNull() 이면 ActiveID 는 유지
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
			// !m_idActive.IsNull() 이면 ActiveID 는 유지
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
				// 현재 Row 안에서 ActiveID 변경만 허용
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
	// 원래 BCG 에 있는 ValidateItemData() 가 Item Value 가 바뀌지 않은 상태에서 불리기 때문에
	// String 으로 직접 판단해야 하는것이 불편해서 Item Value 가 바뀐 뒤에 Validation Check 할 수 있도록 만든 함수
	InvalidateRect(pRow->GetRect()); // TODO : 임시
	return TRUE;
}

BOOL MTable::OnUpdateValue(MGridItem* pItem)
{
	// ValidateItemDataAfterUpdateValue() 통과하면 불린다.
	// return 값이 Validation Check 와 동일한 의미이기 때문에 (바뀐 Value 를 허용할 것인가)
	// Modify 실패한 경우가 아니면 return TRUE 한다.
	if (IsAppendingRow()) return TRUE;

	if (CanModifyItem())
	{
		// Item 단위 수정이 가능할 경우
		// DB 에 Modify 해준다.
		CBCGPGridItemID id = pItem->GetGridItemID();
		int nRow = id.m_nRow;
		int nCol = id.m_nColumn;
		// DB 에 Modify 하면서 DB Notify 에서 실제 DB 에 들어간 값으로 GridItem 값 바꿔주는 것 까지 처리
		if (!GetTableDB()->ModifyItem( GetDBRowIndex(nRow), nCol, const_cast<_variant_t&>(pItem->GetValue()) )) return FALSE;
	}

	return TRUE;
}

BOOL MTable::OnEdit(MGridRow* pRow)
{
	// Item 편집 시작할때 불림.
	// return FALSE 시 편집이 시작되지 않음.
	// return TRUE 시 InPlaceEdit 이 생성되고 편집이 시작되며 해당 Row 를 다시 그린다.
	if (pRow->GetRowId() == GetEditingRow()) return TRUE;
	if (pRow->GetRowId() < GetExtraTopRowCount()) return TRUE;
	if (pRow->GetRowId() > GetDataRowEndIndex()) return TRUE;

	// Append Row 시 Default Data 받아와서 Update
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
		// 편집일 경우
		if (!CanModifyItem())
		{
			MTBNoUpdateWindow noUpdate(m_bNoUpdateWindow);
			SetEditingRow(pRow->GetRowId(), pRow);
		}
	}

	// TODO: 편집은 시작 했지만 값을 안 바꾼 경우에 대한 처리

	return TRUE;
}

BOOL MTable::OnEndEdit(MGridRow* pRow)
{
	// Item 편집 끝날때 불림.
	// return FALSE 시 편집이 끝나지 않음.
	// return TRUE 시 InPlaceEdit 을 날리고 편집이 완료되며 해당 Row 를 다시 그린다.
	if (IsEditingRow())
	{
		if (m_dwEndEditResult & EndEdit_Cancel)
		{
			// 현재 Cell 편집만 취소하기. Cancel 은 안함
			//OnCancelEditingRow(pRow);
		}
	}

	return TRUE;
}

BOOL MTable::OnEndEditRow(MGridRow* pRow)
{
	// Row 편집이 끝날때 (Item 을 한 번이라도 수정한 뒤 현재 Row 가 바뀔때)
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
		for (int i = 0; i < nItemCount; i++) pRow->GetItem(i)->SetModifiedFlag(); // DB Commit 하면서 값이 바뀌었을 수도 있기 때문
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_COMMIT, _STR("1개의 데이터가 수정되었습니다."));
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
		for (int i = 0; i < nItemCount; i++) pRow->GetItem(i)->SetModifiedFlag(); // DB Commit 하면서 값이 바뀌었을 수도 있기 때문
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_COMMIT, _STR("1개의 데이터가 추가되었습니다."));
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
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("데이터 수정을 취소하였습니다."));
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
		GetMessageCtrl()->Show(ITBMessageCtrl::MT_MESSAGE, _STR("데이터 추가를 취소하였습니다."));
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

	// BCG 에 RemoveSelectedRows() 가 있지만 Virtual Mode 에서는 따로 처리해줘야함.
	// 심지어 non-virtual 함수라 따로 함수 만든다. 
	// (RemoveSelectedRows() 는 Cut() 에서만 호출하므로 문제 안됨. Cut() 은 지원안함. 막았음)
	CRBMap<int, std::pair<int, int>> mapRange;
	CRBMap<int, std::pair<int, int>>::CPair* pPair = NULL;
	std::pair<int, int> range(0, 0);
	std::pair<int, int> oldrange(0, 0);

	// 중복 선택 제거
	// 사용자가 중복이 많이 되게 선택할 가능성이 굉장히 낮지만
	// 많은 Row 를 여러번 중복으로 선택하면 성능에 영향이 있을 것이다.
	// 사용자가 어떤 미친짓을 할지 모르기 때문에 중복 제거해준다.
	// Key 로 중복제거하는 것보다는 Range 로 중복제거하는 것이 빠를것이다.
	// 고로 미리 중복제거하고 TableDB 쪽으로 넘긴다.

	// 알고리즘
	// RBMap 을 사용.
	// Key : Row Index
	// Data : Range 의 Top, Bottom Index
	// 각 Range 마다 Top, Bottom Index 를 가지는 Data (pair<int, int>) 를 생성해서
	// Top, Bottom Index 를 Key 로 해서 Map 에 추가한다.
	// 추가할 때 마다 이전에 추가된 Range Data 와 비교하여 중복을 제거.
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
					range.first = -1; // 추가하지 말란 표시
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
	// vector 의 Size - Min: MapSize/2 ~ Max : MapSize
	std::vector<std::pair<int, int>> aRowRanges;			
	aRowRanges.reserve(mapRange.GetCount()); // 조금 여유있게 reserve		
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
	// SelCurSel 실패해도 개나 소나 이 함수를 호출한다.
	// 그 놈들을 재정의하기에는 덩치가 큰 함수들이 많다.
	// 차라리 여기서 Editing Row 가 아닌 곳으로 Scroll 하려하면 막아 버린다.
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
	// FilterBar 기능 사용안한다.
	// 혹시 추후 사용하게 되면 Editing 상태에 대한 처리
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

	// this 로 보낸다
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
	// TODO: OutputDebug 가변인자 버전 만들기
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
	ASSERT((dwResultCode & EndEdit_KeyMask) == EndEdit_Return); // 아직 Return 만 지원

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
	// EditingRow 가 Cache 에 계속 유지되도록 bReferenced 를 계속 TRUE 로 만들어 준다.
	// (Cache 관련 동작은 재정의가 불가능하게 BCG 에 구현되어 있어서 깔끔한 해결책은 아니지만 이렇게라도 한다.)
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

	// 유저 데이터가 Null 이면 무조건 안됨. 잘못된 거임.
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

	// jpahn :그려지는거 보고 싶을때
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




