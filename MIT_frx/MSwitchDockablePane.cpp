#include "StdAfx.h"
#include "MSwitchDockablePane.h"
#include "MBaseDockWnd.h"

using namespace mit;
using namespace mit::frx;

MSwitchDockablePane::MSwitchDockablePane()
{
	m_pRuntimeClass = NULL;
	m_uiID = 0xFFFF;
	m_pCurPaneWnd = NULL;
	m_pDefaultPane = NULL;
}

MSwitchDockablePane::~MSwitchDockablePane()
{
	pane_map::iterator itr;
	for( itr = m_mapPane.begin(); itr != m_mapPane.end(); ++itr)
	{
		MBaseDockWnd* pWnd = itr->second;
		pWnd->DestroyWindow();		
		m_mapPane.erase(itr);
		delete pWnd;
	}
	m_mapPane.clear();

	if( m_pDefaultPane ) {
		m_pDefaultPane->DestroyWindow();
		delete m_pDefaultPane;
	}
}


BEGIN_MESSAGE_MAP(MSwitchDockablePane, MLayeredDockingControlBar)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CSwitchDockablePane message handlers


void MSwitchDockablePane::RegisterPane( CRuntimeClass* pRuntimeClass, UINT uiID )
{
	m_pRuntimeClass = pRuntimeClass;
	m_uiID = uiID;

	m_pDefaultPane = (MBaseDockWnd*)m_pRuntimeClass->CreateObject();
	CRect rectClient;
	GetClientRect(&rectClient);
	m_pDefaultPane->Create(this, m_uiID, NULL, WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN, rectClient);
	m_pCurPaneWnd = m_pDefaultPane;
}

void MSwitchDockablePane::AddDocument( CDocument* pDoc )
{
	if( m_pRuntimeClass == NULL ) return;

	MBaseDockWnd* pWnd = (MBaseDockWnd*)m_pRuntimeClass->CreateObject();

	CRect rectClient;
	GetClientRect(&rectClient);
	pWnd->Create(this, m_uiID, pDoc, WS_CHILD|WS_CLIPCHILDREN, rectClient);

	m_mapPane.insert(pane_map::value_type(pDoc,pWnd));

}

void MSwitchDockablePane::RemoveDocument( CDocument* pDoc )
{
	pane_map::iterator itr = m_mapPane.find(pDoc);
	if( itr != m_mapPane.end() ) {

		CWnd* pWnd = itr->second;
		pWnd->DestroyWindow();		
		m_mapPane.erase(itr);
		delete pWnd;

		if( pWnd == m_pCurPaneWnd ) {
			m_pDefaultPane->ShowWindow(SW_SHOW);
			m_pCurPaneWnd = m_pDefaultPane;
		}
	}
	if( m_mapPane.empty() ) {
		m_pDefaultPane->ShowWindow(SW_SHOW);
		m_pCurPaneWnd = m_pDefaultPane;
	}
}

void MSwitchDockablePane::SetCurrentDocument( CDocument* pDoc )
{
	MBaseDockWnd* pWndFind = GetPaneWnd(pDoc);

	if( pWndFind != m_pCurPaneWnd ) 
	{
		if( pWndFind != NULL && pWndFind->GetSafeHwnd() )
			pWndFind->ShowWindow(SW_SHOW);

		if( m_pCurPaneWnd != NULL && m_pCurPaneWnd->GetSafeHwnd() )
			m_pCurPaneWnd->ShowWindow(SW_HIDE);

		m_pCurPaneWnd = pWndFind;
	}
}

MBaseDockWnd* MSwitchDockablePane::GetDefaultPaneWnd()
{
	return m_pDefaultPane;
}

MBaseDockWnd* MSwitchDockablePane::GetCurPaneWnd()
{
	return m_pCurPaneWnd;
}

MBaseDockWnd* MSwitchDockablePane::GetPaneWnd( CDocument* pDoc )
{
	pane_map::iterator itr = m_mapPane.find(pDoc);
	if( itr != m_mapPane.end() ) {
		MBaseDockWnd* pWnd = itr->second;
		return pWnd;
	}
	return NULL;
}

long MSwitchDockablePane::GetPaneList(mit::MList<MBaseDockWnd*>& lPane)
{
	if( m_mapPane.empty() ) return 0;
	lPane.RemoveAll();

	pane_map::iterator itr;
	for( itr = m_mapPane.begin(); itr != m_mapPane.end(); ++itr)
	{
		MBaseDockWnd* pWnd = itr->second;
		lPane.AddTail( pWnd );
	}

	return (long)lPane.GetSize();
}

void MSwitchDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	pane_map::iterator itr;
	for( itr = m_mapPane.begin(); itr != m_mapPane.end(); ++itr)
	{
		CWnd* pWnd = itr->second;
		if( pWnd && pWnd->GetSafeHwnd() )
		{
			pWnd->MoveWindow(0,0,cx,cy);
		}
	}
	if( m_pDefaultPane && m_pDefaultPane->GetSafeHwnd() )
	{
		m_pDefaultPane->MoveWindow(0,0,cx,cy);
	}
}

BOOL MSwitchDockablePane::OnEraseBkgnd(CDC* pDC)
{
	if( m_mapPane.size() > 0 )
		return FALSE;
	return CWnd::OnEraseBkgnd(pDC);
}

void MSwitchDockablePane::OnSlide(BOOL bSlideOut)
{
	MLayeredDockingControlBar::OnSlide(bSlideOut);
}