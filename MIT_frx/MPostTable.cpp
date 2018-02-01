#include "stdafx.h"
#include "MPostTable.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MPostTable, MTable)

BEGIN_MESSAGE_MAP(MPostTable, MTable)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

MPostTable::MPostTable()
{
}

MPostTable::~MPostTable()
{
}

int MPostTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MTable::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����� Sort ��ɸ� �ش�. Drag �̵��̳� ��Ÿ ����� ��ó�� ���̺� �ʿ����.
	EnableHeader (TRUE, BCGP_GRID_HEADER_SELECT );  
	EnableRowHeader (TRUE);

#ifdef _DEBUG
	EnableLineNumbers(TRUE);
#endif

	SetReadOnly();

	AdjustLayout ();

	return 0;
}

void MPostTable::OnDestroy() 
{
	MTable::OnDestroy();
}

void MPostTable::OnContextMenu(CWnd* pWnd, CPoint point)
{
	MTable::OnContextMenu(pWnd, point);
	//CWnd* pParent = GetParent();
	//if (!pParent->IsKindOf(RUNTIME_CLASS(MTableBar))) 
	//{
	//	MTable::OnContextMenu(pWnd, point);
	//	return;
	//}

	//MTableBar* pTableBar = (MTableBar*)pParent;
	//pTableBar->

	Default();
}

void MPostTable::MakeContextMenu(CMenu& menu)
{
	BOOL bMerge = ( m_pDataRecordInfo->GetMergeInfo().GetSize() > 0 ) ?  TRUE : FALSE;

	menu.AppendMenu(MF_STRING, ID_TB_COPY, _T("Copy"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_FIND, _T("Find..."));

	// Merge ������ ������ Sort �� �� ���� ����.
	if( !bMerge )
		menu.AppendMenu(MF_STRING, ID_TB_SORT, _T("Sort..."));

	menu.AppendMenu(MF_STRING, ID_TB_STYLE, _T("Style..."));
	menu.AppendMenu(MF_STRING, ID_TB_ACTIVE_DIALOG, _T("Active Dialog..."));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_GRAPH, _T("Graph..."));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_TB_EXPORT_TO_EXCEL, _T("Export to Excel"));
}