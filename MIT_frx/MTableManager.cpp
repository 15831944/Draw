#include "stdafx.h"
#include "MTableManager.h"
#include "MTableBar.h"
#include "MTable.h"

using namespace mit::frx;

MTableManager::MTableManager(void)
{
	m_hmTableBar.SetHashSize(101);
}


MTableManager::~MTableManager(void)
{
	MIterator itr = m_hmTableBar.GetHeadPosition();
	while ( itr )
	{
		MTableBar* pBar = m_hmTableBar.GetNext(itr);
		_SAFE_DELETE(pBar);
	}

	m_hmTableBar.RemoveAll();
}

MTableManager* MTableManager::GetInstance()
{
	static MTableManager instance;

	return &instance;
}

MTableBar* MTableManager::GetTableBar(CRuntimeClass* pBar, CDocument* pDoc)
{
	if( !pBar || !pDoc ) return NULL;

	MIterator itr = m_hmTableBar.Find( pBar, pDoc );
	if( itr )
	{
		MTableBar* pTableBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MTableBar*, itr);
		return pTableBar;
	}

	return NULL;
}

BOOL MTableManager::RemoveTableBar(CRuntimeClass* pBar, CDocument* pDoc)
{
	if( !pBar || !pDoc ) return FALSE;

	MIterator itr = m_hmTableBar.Find( pBar, pDoc );
	if( itr )
	{
		MTableBar* pTableBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MTableBar*, itr);
		_SAFE_DELETE(pTableBar);

		return m_hmTableBar.Remove( itr );
	}

	return TRUE;
}

void MTableManager::ShowTableBar(UINT uiID, CString strName, CRuntimeClass* pBar, CDocument* pDoc)
{
	ASSERT(pBar);
	ASSERT(pDoc);

	if( !pBar || !pDoc ) return;

	CBCGPMDIFrameWnd* pMainWnd = (CBCGPMDIFrameWnd*)AfxGetMainWnd();
	if( !pMainWnd || !pMainWnd->GetSafeHwnd() ) 
	{
		ASSERT(FALSE);
		return;
	}

	MIterator itr = m_hmTableBar.Find( pBar, pDoc );
	if( itr )
	{
		MTableBar* pTableBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MTableBar*, itr);
		ASSERT_VALID(pTableBar);
		
		if( !pTableBar->IsVisible() )
		{
			// 사실상 닫으면 무조건 새로 만들어져야 하기 때문에 이리로 들어오면 잘못된거임.
			ASSERT(0);
		}

		CFrameWnd* pWnd = pTableBar->GetParentFrame();
		if( pWnd->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)) )
		{
			pTableBar->SendMessage(WM_ACTIVATE, MAKEWPARAM(WA_ACTIVE, 0), NULL);
		}
		else
		{
			if( pWnd && pWnd->GetSafeHwnd() )
				pWnd->SendMessage(WM_ACTIVATE, MAKEWPARAM(WA_ACTIVE, 0), NULL);
		}
	}
	else
	{
		MTableBar* pNewBar = DYNAMIC_DOWNCAST (MTableBar, pBar->CreateObject ());

		if (pNewBar == NULL)
		{
			// 여기 들어왔으면 MTableBar의 RuntimeClass가 아니거나 
			// Dynamic Create를 사용하지 않았거나 임... 확인 바람.
			ASSERT (FALSE);
			return;
		}

		pNewBar->SetDocument( pDoc );

		if (!pNewBar->Create (strName, pMainWnd, CRect (0, 0, 200, 200),
			TRUE, uiID,
			WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
		{
			TRACE0("Failed to create Workspace bar\n");
			return;      // fail to create
		}

		m_hmTableBar.Insert(pBar, pDoc, pNewBar);

		pNewBar->SetMDITabbed(TRUE);
		pNewBar->EnableDocking(CBRS_ALIGN_ANY);
		pMainWnd->DockControlBar (pNewBar);

		pMainWnd->ShowControlBar(pNewBar, TRUE, FALSE, TRUE);
	}

	pMainWnd->RecalcLayout();
}