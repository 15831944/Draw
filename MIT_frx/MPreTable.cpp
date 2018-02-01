#include "stdafx.h"
#include "MPreTable.h"

#include "MGridRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MPreTable, MTable)

BEGIN_MESSAGE_MAP(MPreTable, MTable)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

MPreTable::MPreTable()
{	
	m_canAppendRow = TRUE;
	m_canDeleteRow = TRUE;
}

MPreTable::~MPreTable()
{
}

int MPreTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MTable::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	SetSingleSel(FALSE);
	EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_HIDE_ITEMS | BCGP_GRID_HEADER_SORT);
	EnableRowHeader(TRUE, BCGP_GRID_HEADER_SELECT);
	
	AdjustLayout ();
	
	return 0;
}

void MPreTable::OnDestroy() 
{
	MTable::OnDestroy();	
}