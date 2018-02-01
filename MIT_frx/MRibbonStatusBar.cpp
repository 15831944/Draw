#include "StdAfx.h"
#include "MRibbonStatusBar.h"

using namespace mit::frx;

MRibbonStatusBar::MRibbonStatusBar(void)
{
	m_pWnd = new CBCGPRibbonStatusBar();
}

MRibbonStatusBar::~MRibbonStatusBar(void)
{
	m_pWnd = NULL;
}

BOOL MRibbonStatusBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	ASSERT( m_pWnd );

	CBCGPRibbonStatusBar* pStatusBar = reinterpret_cast<CBCGPRibbonStatusBar*>(m_pWnd);
	ASSERT( pStatusBar );

	if( !pStatusBar ) return FALSE;

	return pStatusBar->Create( pParentWnd, dwStyle, nID );
}

BOOL MRibbonStatusBar::CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle, DWORD dwStyle, UINT nID)
{
	ASSERT( m_pWnd );

	CBCGPRibbonStatusBar* pStatusBar = reinterpret_cast<CBCGPRibbonStatusBar*>(m_pWnd);
	ASSERT( pStatusBar );

	if( !pStatusBar ) return FALSE;

	return pStatusBar->CreateEx( pParentWnd, dwCtrlStyle, dwStyle, nID );
}

BOOL MRibbonStatusBar::LoadFromXML (LPCTSTR lpszXMLResID)
{
	ASSERT( m_pWnd );

	CBCGPRibbonStatusBar* pStatusBar = reinterpret_cast<CBCGPRibbonStatusBar*>(m_pWnd);
	ASSERT( pStatusBar );

	if( !pStatusBar ) return FALSE;

	return pStatusBar->LoadFromXML(lpszXMLResID);
}

BOOL MRibbonStatusBar::LoadFromBuffer (LPCTSTR lpszXMLBuffer)
{
	ASSERT( m_pWnd );

	CBCGPRibbonStatusBar* pStatusBar = reinterpret_cast<CBCGPRibbonStatusBar*>(m_pWnd);
	ASSERT( pStatusBar );

	if( !pStatusBar ) return FALSE;

	return pStatusBar->LoadFromBuffer(lpszXMLBuffer);
}