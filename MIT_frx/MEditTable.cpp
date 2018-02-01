#include "stdafx.h"
#include "MEditTable.h"

#include "MGridRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MEditTable, MTable)

BEGIN_MESSAGE_MAP(MEditTable, MTable)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

MEditTable::MEditTable()
{	
	m_canAppendRow = FALSE;
}

MEditTable::~MEditTable()
{
}

int MEditTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (MTable::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSingleSel(FALSE);
	EnableHeader(TRUE, 0);
	EnableRowHeader(TRUE, BCGP_GRID_HEADER_SELECT);
	EnableInvertSelOnCtrl();

	SetEditFirstClick(FALSE);

	AdjustLayout ();

	return 0;
}

void MEditTable::OnDestroy() 
{
	MTable::OnDestroy();	
}