#include "stdafx.h"
#include "MTBDialogBase.h"

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MTBDialogBase, MDialog)

MTBDialogBase::MTBDialogBase()
	: m_pTable(NULL)
{
	m_dlgTemplate.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	m_dlgTemplate.exStyle = WS_EX_TOOLWINDOW;
	m_lpDialogTemplate = (LPCDLGTEMPLATE)&m_dlgTemplate;
}

MTBDialogBase::MTBDialogBase(MTable* pTable) :
	m_pTable(pTable),
	m_pTableDB(pTable->GetTableDB()),
	m_pSchema(pTable->GetTableDB()->GetSchema())
{
	m_dlgTemplate.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	m_dlgTemplate.exStyle = WS_EX_TOOLWINDOW;
	m_lpDialogTemplate = (LPCDLGTEMPLATE)&m_dlgTemplate;
	m_pParentWnd = pTable;
}

MTBDialogBase::~MTBDialogBase()
{
}

BOOL MTBDialogBase::Create(MTable* pTable)
{
	m_pTable = pTable;
	m_pTableDB = pTable->GetTableDB();
	m_pSchema = m_pTableDB->GetSchema();
	return CreateIndirect(m_lpDialogTemplate, pTable);
}

BOOL MTBDialogBase::CreateFont()
{
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	if (!SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0)) return FALSE;
	if (!m_font.CreateFontIndirect(&ncm.lfMessageFont)) return FALSE;
	return TRUE;
}

BOOL MTBDialogBase::CreateControls()
{
	return TRUE;
}

BOOL MTBDialogBase::OnInitDialog() 
{
	ASSERT(m_pTable);
	ASSERT(m_pTableDB);
	ASSERT(m_pSchema);
	if (!MDialog::OnInitDialog()) return FALSE;
	if (CreateFont()) SetFont(&m_font);
	if (!CreateControls()) return FALSE;
	return TRUE; 
}