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

// MTableChildFrame 생성/소멸

MTabbedChildFrame::MTabbedChildFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

MTabbedChildFrame::~MTabbedChildFrame()
{
}


BOOL MTabbedChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
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

	// 이놈 여기서도 부르면 View 최대화시 중간단계에서 모델이 보여서 이상하다.
	// bring to top before showing
	//BringToTop(nCmdShow);

	if( nCmdShow != -1 )
	{
		// show the window as specified
		ShowWindow( nCmdShow );

		// and finally, bring to top after showing
		BringToTop( nCmdShow );
	}

	// 이놈 부르면 도로묵된다!!
	//CNSChildFrame::ActivateFrame(nCmdShow);
}

// MTableChildFrame 진단

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

// MTableChildFrame 메시지 처리기

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
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 인쇄 미리 보기 모드를 닫습니다.
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
			// Table 은 차일드프레임이 닫히면 숨기는게 아니라 아주 Destroy되게 함.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	// 테이블 차트 등을 CASCADE 하거나하면 위아래로 2 pixel이 비어있게 되는데 그것을 막기위해서 
	// NC 영역사이즈를 조정한다.
	if (!m_bWasMaximized )
	{
		lpncsp->rgrc[0].top -= 2;
		lpncsp->rgrc[0].bottom += 1;
	}

	CBCGPMDIChildWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}