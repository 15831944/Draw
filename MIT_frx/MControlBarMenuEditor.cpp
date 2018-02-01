#include "stdafx.h"
#include "MControlBarMenuEditor.h"

using namespace mit::frx;

MControlBarMenuEditor* MControlBarMenuEditor::s_instance = NULL;

BOOL MControlBarMenuEditor::EditMenu(CMenu& menu)
{
	const UINT idFloating	= (UINT) -102;
	const UINT idDocking	= (UINT) -103;
	const UINT idAutoHide	= (UINT) -104;
	const UINT idHide		= (UINT) -105;
	const UINT idTabbed		= (UINT) -106;

	CString strItem;
	if (GetFloatingString(strItem)) 
	{
		ModifyMenuString(menu, idFloating, strItem);
	}
	if (GetDockingString(strItem)) 
	{
		ModifyMenuString(menu, idDocking, strItem);
	}
	if (GetTabbedString(strItem)) 
	{
		ModifyMenuString(menu, idTabbed, strItem);
	}
	if (GetAutoHideString(strItem)) 
	{
		ModifyMenuString(menu, idAutoHide, strItem);
	}
	if (GetHideString(strItem)) 
	{
		ModifyMenuString(menu, idHide, strItem);
	}

	return TRUE;
}

BOOL MControlBarMenuEditor::GetTooltipString(UINT nTooltipResID, CString& strTipText)
{
	switch (nTooltipResID)
	{
	case IDS_BCGBARRES_CLOSEBAR:
		return GetCloseBarString(strTipText);
	case IDS_BCGBARRES_AUTOHIDEBAR:
		return GetAutoHideBarString(strTipText);
	case IDS_BCGBARRES_AUTOHIDE_ALL:
		return GetAutoHideAllString(strTipText);
	case IDS_BCGBARRES_MENU:
		return GetMenuString(strTipText);
	default:
		break;
	}
	return FALSE;
}

BOOL MControlBarMenuEditor::ModifyMenuString(CMenu& menu, UINT id, const CString strItem)
{
	MENUITEMINFO item;
	ZeroMemory(&item, sizeof(item));
	item.cbSize = sizeof(item);
	item.fMask = MIIM_STRING;
	if (!menu.GetMenuItemInfo(id, &item)) return FALSE;
	item.dwTypeData = (LPTSTR)(LPCTSTR)strItem;
	if (!menu.SetMenuItemInfo(id, &item)) return FALSE;
	return TRUE;
}