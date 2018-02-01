#include "StdAfx.h"
#include "MSwitchDockablePaneManager.h"
#include "MSwitchDockablePane.h"

using namespace mit;
using namespace mit::frx;

MSwitchDockablePaneManager::MSwitchDockablePaneManager()
{
}

MSwitchDockablePaneManager::~MSwitchDockablePaneManager()
{
}

MSwitchDockablePaneManager& MSwitchDockablePaneManager::Instance()
{
	static MSwitchDockablePaneManager singleton;
	return singleton;	
}

void MSwitchDockablePaneManager::AddDocument( CDocument* pDoc )
{
	pane_list::iterator itr;
	for(itr = m_listPane.begin();itr!=m_listPane.end();++itr) {
		(*itr)->AddDocument(pDoc);
	}
}

void MSwitchDockablePaneManager::RemoveDocument( CDocument* pDoc )
{
	pane_list::iterator itr;
	for(itr = m_listPane.begin();itr!=m_listPane.end();++itr) {
		(*itr)->RemoveDocument(pDoc);
	}
}

void MSwitchDockablePaneManager::RegisterSwitchDockPane( MSwitchDockablePane* pPane )
{
	m_listPane.push_back(pPane);
}

void MSwitchDockablePaneManager::SetCurrentDocument( CDocument* pDoc )
{
	pane_list::iterator itr;
	for(itr = m_listPane.begin();itr!=m_listPane.end();++itr) {
		(*itr)->SetCurrentDocument(pDoc);
	}
}