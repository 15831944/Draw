#include "stdafx.h"
#include "MChartManager.h"
#include "MChartBar.h"
#include "MChartCtrl.h"

using namespace mit::frx;

MChartManager::MChartManager(void)
{
	m_hmChartMar.SetHashSize(101);
}

MChartManager::~MChartManager(void)
{
	MIterator itr = m_hmChartMar.GetHeadPosition();
	while (itr)
	{
		MChartBar* pBar = m_hmChartMar.GetNext(itr);
		_SAFE_DELETE(pBar);
	}

	m_hmChartMar.RemoveAll();
}

MChartManager* MChartManager::GetInstance()
{
	static MChartManager instance;

	return &instance;
}

MChartBar* MChartManager::GetChartBar(CRuntimeClass* pBar, CDocument* pDoc)
{
	if( !pBar || !pDoc ) return NULL;

	MIterator itr = m_hmChartMar.Find( pBar, pDoc );
	if( itr )
	{
		MChartBar* pChartBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MChartBar*, itr);
		return pChartBar;
	}

	return NULL;
}

BOOL MChartManager::RemoveChartBar(CRuntimeClass* pBar, CDocument* pDoc)
{
	if( !pBar || !pDoc ) return FALSE;

	MIterator itr = m_hmChartMar.Find( pBar, pDoc );
	if( itr )
	{
		MChartBar* pChartBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MChartBar*, itr);
		_SAFE_DELETE(pChartBar);

		return m_hmChartMar.Remove( itr );
	}

	return TRUE;
}

void MChartManager::ShowChartBar(UINT uiID, CString strName, CRuntimeClass* pBar, CDocument* pDoc)
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

	MIterator itr = m_hmChartMar.Find( pBar, pDoc );
	if( itr )
	{
		MChartBar* pChartBar = M_2SET_ITR_TO_DATA(CRuntimeClass*, CDocument*, MChartBar*, itr);
		ASSERT_VALID(pChartBar);

		if( !pChartBar->IsVisible() )
		{
			// 사실상 닫으면 무조건 새로 만들어져야 하기 때문에 이리로 들어오면 잘못된거임.
			ASSERT(0);
		}

		CFrameWnd* pWnd = pChartBar->GetParentFrame();
		if( pWnd->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)) )
		{
			pChartBar->SendMessage(WM_ACTIVATE, MAKEWPARAM(WA_ACTIVE, 0), NULL);
		}
		else
		{
			if( pWnd && pWnd->GetSafeHwnd() )
				pWnd->SendMessage(WM_ACTIVATE, MAKEWPARAM(WA_ACTIVE, 0), NULL);
		}
	}
	else
	{
		MChartBar* pNewBar = DYNAMIC_DOWNCAST (MChartBar, pBar->CreateObject ());

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

		m_hmChartMar.Insert(pBar, pDoc, pNewBar);

		pNewBar->SetMDITabbed(TRUE);
		pNewBar->EnableDocking(CBRS_ALIGN_ANY);
		pMainWnd->DockControlBar (pNewBar);

		pMainWnd->ShowControlBar(pNewBar, TRUE, FALSE, TRUE);
	}

	pMainWnd->RecalcLayout();
}

void MChartManager::ExportToImage()
{
// 	MExportToChartDlg dlg;
// 	dlg.DoModal();
}