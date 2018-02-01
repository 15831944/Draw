#include "stdafx.h"
#include "MPropList.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MPropList, MLayeredPropList)
MPropList::MPropList(void)
{
	m_nValueAlign = DT_RIGHT;
}


MPropList::~MPropList(void)
{
}

BOOL MPropList::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if( !MLayeredPropList::Create(dwStyle, rect, pParentWnd, nID ) )
	{
		ASSERT(NULL);
		TRACE(_T("[Error] Fail to MPropList::Create!!\n"));

		return FALSE;
	}

	// ����� ������� �ʴ� �ɷ�...
	EnableHeaderCtrl (FALSE);

	// DescriptionArea �� ����Ѵ�.
	EnableDesciptionArea ();

	// Toolbar Setup 
	SetupToolbar();

	// Menu Button Setup
	SetupMenuButton();

	// SearchBox ���.
	EnableSearchBox(TRUE, _STR("Search"));
	SetVSDotNetLook(TRUE);
	SetAlphabeticMode (FALSE);
	SetShowDragContext (TRUE);
	MarkModifiedProperties(FALSE);

	if( !CreatePropItems() )
	{
		ASSERT(0);
		TRACE(_T("[Error] Item ���� ����!\n"));

		return FALSE;
	}

	return TRUE;
}

void MPropList::SetupToolbar(BOOL bShowStandardButtons, BOOL bToolbarCustomButton, UINT uiToolbarID, UINT uiBitmapID)
{
	UpdateData();

	EnableToolBar(bShowStandardButtons, 
		bToolbarCustomButton ? uiToolbarID : 0, 
		bToolbarCustomButton ? uiBitmapID : 0);
}

void MPropList::SetupMenuButton()
{
	EnableContextMenu(FALSE, 
		TRUE ? BCGP_PROPLIST_MENU_ALL : (BCGP_PROPLIST_MENU_COMMANDS | BCGP_PROPLIST_MENU_DESCRIPTION | BCGP_PROPLIST_MENU_RESET | BCGP_PROPLIST_MENU_EDIT));
}

void MPropList::SetValueAlign(int nValueAlign, BOOL bRedraw )
{
	m_nValueAlign = nValueAlign;

	if (GetHeaderCtrl().GetSafeHwnd() != NULL)
	{
		HDITEM hdItem;
		hdItem.mask = HDI_FORMAT;
		hdItem.fmt = (m_nValueAlign == DT_LEFT) ? HDF_LEFT : (m_nValueAlign == DT_CENTER) ? HDF_CENTER : HDF_RIGHT;
		hdItem.fmt |= HDF_STRING;

		GetHeaderCtrl().SetItem(1, &hdItem);
	}

	if (bRedraw && GetSafeHwnd () != NULL)
	{
		RedrawWindow ();
	}
}

void MPropList::OnPropertyChanged (CBCGPProp* pProp) const
{
	// ������Ƽ�� ���� �����ϸ� ���� ����. �������ؼ� ����ϼ���.
}

void MPropList::OnPropertyClickButton (CBCGPProp* pProp, CPoint point) const
{
	// ��ư Ŭ������ �� �̺�Ʈ�� ���� ����. �������ؼ� ����ϼ���.
}