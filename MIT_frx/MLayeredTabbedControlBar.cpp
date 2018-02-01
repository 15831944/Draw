#include "stdafx.h"
#include "MLayeredTabbedControlBar.h"
#include "MLayeredMiniFrameWnd.h"
#include "MLayeredMultiMiniFrameWnd.h"
#include "MLayeredTabWnd.h"
#include "MLayeredWindow.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_SERIAL(MLayeredTabbedControlBar, CBCGPTabbedControlBar,VERSIONABLE_SCHEMA | 2)
MLayeredTabbedControlBar::MLayeredTabbedControlBar(void)
{
	m_pMiniFrameRTC = RUNTIME_CLASS(MLayeredMiniFrameWnd);
}

MLayeredTabbedControlBar::~MLayeredTabbedControlBar(void)
{

}

BEGIN_MESSAGE_MAP(MLayeredTabbedControlBar, CBCGPTabbedControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL MLayeredTabbedControlBar::Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle, DWORD dwBCGStyle, CCreateContext* pContext)
{
	ASSERT_VALID (this);
	return CreateEx (0, lpszCaption, pParentWnd, rect, 
		bHasGripper, nID, dwStyle, dwTabbedStyle, 
		dwBCGStyle, pContext);
}

BOOL MLayeredTabbedControlBar::CreateEx (DWORD dwStyleEx, 
							  LPCTSTR lpszCaption, 
							  CWnd* pParentWnd, 
							  const RECT& rect, 
							  BOOL bHasGripper, 
							  UINT nID, 
							  DWORD dwStyle, 
							  DWORD dwTabbedStyle, 
							  DWORD dwBCGStyle,
							  CCreateContext* pContext)
{
	ASSERT_VALID (this);

	if (!CBCGPTabbedControlBar::CreateEx (dwStyleEx, lpszCaption, pParentWnd, rect, bHasGripper, nID, dwStyle, dwTabbedStyle,
		dwBCGStyle, pContext))
	{
		return FALSE;
	}

	if (dwStyle & CBRS_FLOAT_MULTI)
	{
		m_pMiniFrameRTC = RUNTIME_CLASS (MLayeredMultiMiniFrameWnd);
	}

	if (dwTabbedStyle & CBRS_BCGP_REGULAR_TABS)
	{
		m_pTabbedControlBarRTC = RUNTIME_CLASS (MLayeredTabbedControlBar);
	}

	return TRUE;
}

CBCGPMiniFrameWnd* MLayeredTabbedControlBar::CreateDefaultMiniframe(CRect rectInitial)
{
	ASSERT_VALID (this);

	CRect rectVirtual = rectInitial;

	CBCGPMiniFrameWnd* pMiniFrame =  
		(CBCGPMiniFrameWnd*) m_pMiniFrameRTC->CreateObject ();

	if (pMiniFrame != NULL)
	{
		// it must have valid BCGFrame window as parent
		CWnd* pParentFrame = BCGPGetParentFrame (this);
		ASSERT_VALID (pParentFrame);

		pMiniFrame->SetDockManager (globalUtils.GetDockManager (GetDockSite ()));

		if (pParentFrame == NULL || !pMiniFrame->Create (NULL, WS_POPUP, rectVirtual, pParentFrame))
		{
			TRACE0 ("Failed to create miniframe");
			delete pMiniFrame;
			return NULL;
		}
	}
	else
	{
		TRACE0 ("Failed to create miniframe using runtime class information \n");
		ASSERT (FALSE);
	}
	return pMiniFrame;
}

CBCGPTabbedControlBar* MLayeredTabbedControlBar::CreateTabbedControlBar ()
{
	ASSERT_VALID (this);
	CRect rectTabBar;
	GetWindowRect (&rectTabBar);
	ASSERT_VALID (GetParent ());
	GetParent ()->ScreenToClient (&rectTabBar);

	CBCGPTabbedControlBar* pTabbedBar = 
		(CBCGPTabbedControlBar*) m_pTabbedControlBarRTC->CreateObject ();
	ASSERT_VALID (pTabbedBar);

	pTabbedBar->SetAutoDestroy (TRUE);

	if (!pTabbedBar->Create (_T (""), 
		GetParent (), 
		rectTabBar, 
		TRUE, 
		(UINT) -1, 
		GetStyle () | CBRS_FLOAT_MULTI))
	{
		TRACE0 ("Failed to create tabbed control bar\n");
		return NULL;
	}

	// override recent floating/docking info

	pTabbedBar->m_recentDockInfo.m_recentMiniFrameInfo.m_rectDockedRect = 
		m_recentDockInfo.m_recentMiniFrameInfo.m_rectDockedRect;
	pTabbedBar->m_recentDockInfo.m_recentSliderInfo.m_rectDockedRect = 
		m_recentDockInfo.m_recentSliderInfo.m_rectDockedRect;
	pTabbedBar->m_recentDockInfo.m_rectRecentFloatingRect = 
		m_recentDockInfo.m_rectRecentFloatingRect;

	return pTabbedBar;
}

int MLayeredTabbedControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	ASSERT_VALID (this);
	if (CBCGPBaseTabbedBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	ASSERT (m_pTabWnd == NULL);
	ASSERT (m_pTabWndRTC != NULL);

	//m_pTabWndRTC 가 static이기 때문에 다른 곳에 영향을 주지 않기 위해 직접 생성한다.
	m_pTabWnd = DYNAMIC_DOWNCAST (MLayeredTabWnd, RUNTIME_CLASS(MLayeredTabWnd)->CreateObject());

	if (m_pTabWnd == NULL)
	{
		TRACE0("Failed to dynamically inatantiate a tab window object\n");
		return -1;      // fail to create
	}

	CBCGPTabWnd* pTabWnd = (CBCGPTabWnd*) m_pTabWnd;

	// Create tabs window:
	if (!pTabWnd->Create (m_StyleTabWnd, rectClient, this, 101, 
		CBCGPTabbedControlBar::m_bTabsAlwaysTop ? CBCGPTabWnd::LOCATION_TOP : CBCGPTabWnd::LOCATION_BOTTOM))
	{
		TRACE0("Failed to create tab window\n");
		delete m_pTabWnd;
		m_pTabWnd = NULL;
		return -1;      // fail to create
	}

	m_pTabWnd->m_bActivateTabOnRightClick = TRUE;

	if (m_bIsTabsAutoColor)
	{
		pTabWnd->EnableAutoColor ();
		pTabWnd->SetAutoColors (m_arTabsAutoColors);
	}

	pTabWnd->AutoDestroyWindow (FALSE);
	pTabWnd->HideSingleTab ();

	//pTabWnd->SetTabBorderSize (CBCGPVisualManager::GetInstance ()->GetDockingTabsBordersSize ());
	// 테두리 선을 없앤다.
	pTabWnd->SetTabBorderSize (0);
	pTabWnd->SetDrawNameInUpperCase(CBCGPVisualManager::GetInstance ()->IsDockingTabUpperCase());

	pTabWnd->m_bEnableWrapping = TRUE;

	m_lstTabbedControlBars.AddTail (GetSafeHwnd ());
	return 0;
}

BOOL MLayeredTabbedControlBar::LoadState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	return CBCGPTabbedControlBar::LoadState (lpszProfileName, nIndex, uiID);
}