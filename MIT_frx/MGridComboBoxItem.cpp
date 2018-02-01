#include "stdafx.h"
#include "MGridComboBoxItem.h"
#include "MGridRow.h"
#include "MTable.h"
#include "MGridColumnsInfo.h"

using namespace mit;
using namespace mit::frx;


//////////////////////////////////////////////////////////////////////////
// class MGridComboBoxItem
IMPLEMENT_SERIAL(MGridComboBoxItem, MGridItem, VERSIONABLE_SCHEMA | 1)
MGridComboBoxItem::MGridComboBoxItem(void) :
	m_bDropList(FALSE)
{

}

MGridComboBoxItem::~MGridComboBoxItem(void)
{

}

void MGridComboBoxItem::SetCurItem(int idx)
{
	int nSize = GetOptionCount();
	if( idx < 0 || nSize <= idx ) { ASSERT(0); return; }

	_variant_t var = GetOption(idx);
	SetValue(var);
}