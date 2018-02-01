#include "stdafx.h"
#include "MTabbedChildFrm.h"

#include "MTableBar.h"
#include "MChartBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace mit::frx;

// MTableChildFrame
IMPLEMENT_DYNCREATE(MTabbedChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(MTabbedChildFrame, CBCGPMDIChildWnd)
	ON_COMMAND(ID_FILE_PRINT, &MTabbedChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &MTabbedChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MTabbedChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &MTabbedChildFrame::OnUpdateFilePrintPreview)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_NCCALCSIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// MTableChildFrame ����/�Ҹ�

MTabbedChildFrame::MTabbedChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

MTabbedChildFrame::~MTabbedChildFrame()
{
}


BOOL MTabbedChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

void MTabbedChildFrame::ActivateFrame(int nCmdShow)
{
	if(GetParent()->GetWindow(GW_CHILD) == this)
	{
		nCmdShow = SW_SHOWMAXIMIZED;
	}

	//////////////////////////////////////////////////////////////////////////
	// Who-Soon Hwang
	// translate default nCmdShow (-1)
	if( nCmdShow == -1 )
	{
		if( !IsWindowVisible() )
			nCmdShow = SW_SHOWNORMAL;
		else if( IsIconic() )
			nCmdShow = SW_RESTORE;
	}

	// �̳� ���⼭�� �θ��� View �ִ�ȭ�� �߰��ܰ迡�� ���� ������ �̻��ϴ�.
	// bring to top before showing
	//BringToTop(nCmdShow);

	if( nCmdShow != -1 )
	{
		// show the window as specified
		ShowWindow( nCmdShow );

		// and finally, bring to top after showing
		BringToTop( nCmdShow );
	}

	// �̳� �θ��� ���ι��ȴ�!!
	//CNSChildFrame::ActivateFrame(nCmdShow);
}

// MTableChildFrame ����

#ifdef _DEBUG
void MTabbedChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void MTabbedChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// MTableChildFrame �޽��� ó����

void MTabbedChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void MTabbedChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // �μ� �̸� ���� ��带 �ݽ��ϴ�.
	}
}

void MTabbedChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}


void MTabbedChildFrame::OnClose()
{
	CBCGPMDIChildWnd::OnClose();
}

void MTabbedChildFrame::OnDestroy() 
{
	UnregisterTaskbarTab();

	if (m_pMDIFrame != NULL && m_pMDIFrame->IsPrintPreview ())
	{
		m_pMDIFrame->SendMessage (WM_CLOSE);
	}

	if (m_pTabbedControlBar != NULL && CWnd::FromHandlePermanent (m_pTabbedControlBar->GetSafeHwnd ()) != NULL)
	{
		CWnd* pParent = m_pTabbedControlBar->GetParent ();

		if (pParent == this && m_pMDIFrame != NULL && !m_pMDIFrame->IsClosing())
		{
			// Table �� ���ϵ��������� ������ ����°� �ƴ϶� ���� Destroy�ǰ� ��.
			m_pTabbedControlBar->SendMessage(WM_CLOSE);
		}
		m_pTabbedControlBar = NULL;
	}

	CBCGPFrameImpl::RemoveFrame (this);

	POSITION pos = NULL;

	for (pos = m_dockManager.GetMiniFrames().GetHeadPosition (); pos != NULL;)
	{
		CBCGPMiniFrameWnd* pNextFrame = DYNAMIC_DOWNCAST (CBCGPMiniFrameWnd,
			m_dockManager.GetMiniFrames().GetNext (pos));
		if (pNextFrame != NULL)
		{
			pNextFrame->DestroyWindow ();
		}
	}

	CList<HWND, HWND> lstChildren;
	CWnd* pNextWnd = GetTopWindow ();
	while (pNextWnd != NULL)
	{
		lstChildren.AddTail (pNextWnd->m_hWnd);
		pNextWnd = pNextWnd->GetNextWindow ();
	}

	for (pos = lstChildren.GetHeadPosition (); pos != NULL;)
	{
		HWND hwndNext = lstChildren.GetNext (pos);
		if (IsWindow (hwndNext) && ::GetParent (hwndNext) == m_hWnd)
		{
			::DestroyWindow (hwndNext);
		}
	}

	// CBCGPMainClientArea::OnMDIDestroy will take care about removing from the tabs.
	m_pRelatedTabGroup = NULL;

	CMDIChildWnd::OnDestroy();
}

void MTabbedChildFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CBCGPMDIChildWnd::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void MTabbedChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	if (m_pTabbedControlBar)
	{
		if (m_pTabbedControlBar->IsKindOf(RUNTIME_CLASS(MTableBar)))
		{
			CDocument* pDoc = ((MTableBar*)m_pTabbedControlBar)->GetDocument();
			ASSERT(pDoc);

		}
	}

	CBCGPMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void MTabbedChildFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// ���̺� ��Ʈ ���� CASCADE �ϰų��ϸ� ���Ʒ��� 2 pixel�� ����ְ� �Ǵµ� �װ��� �������ؼ� 
	// NC ��������� �����Ѵ�.
	if (!m_bWasMaximized )
	{
		lpncsp->rgrc[0].top -= 2;
		lpncsp->rgrc[0].bottom += 1;
	}

	CBCGPMDIChildWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}