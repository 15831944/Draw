#include "stdafx.h"

#include "BCGPMiniFrameWnd.h"
#include "BCGPTabbedControlBar.h"

#include "MVisualManager.h"

#include "MControlBarMenuEditor.h"
#include "MLayeredDockingControlBar.h"
#include "MLayeredMiniFrameWnd.h"
#include "MLayeredMultiMiniFrameWnd.h"
#include "MLayeredTabbedControlBar.h"

#include "RegPath.h"


using namespace mit;
using namespace mit::frx;

static const CString strControlBarProfile = _T ("MLayeredDockingControlBar");

#define REG_SECTION_FMT					_T("%sMLayeredDockingControlBar-%d")
#define REG_SECTION_FMT_EX				_T("%sMLayeredDockingControlBar-%d%x")

static int g_nCloseButtonMargin = 1;
static int g_nCaptionVertMargin = 2;
static int g_nCaptionHorzMargin = 2;

IMPLEMENT_SERIAL(MLayeredDockingControlBar, CBCGPDockingControlBar, VERSIONABLE_SCHEMA | 2)

BEGIN_MESSAGE_MAP(MLayeredDockingControlBar, CBCGPDockingControlBar)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnNeedTipText)
END_MESSAGE_MAP()

MLayeredDockingControlBar::MLayeredDockingControlBar(void)
{
	m_bCleanScreenVisible = FALSE;
	m_pMiniFrameRTC = RUNTIME_CLASS(MLayeredMiniFrameWnd);
}

MLayeredDockingControlBar::~MLayeredDockingControlBar(void)
{
}

//**************************************************************************
int MLayeredDockingControlBar::GetCaptionHeight () const
{
	return CBCGPDockingControlBar::GetCaptionHeight();
}

BOOL MLayeredDockingControlBar::Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle, DWORD dwBCGStyle, CCreateContext* pContext)
{
	ASSERT_VALID (this);
	return CreateEx (0, lpszCaption, pParentWnd, rect, 
		bHasGripper, nID, dwStyle, dwTabbedStyle, 
		dwBCGStyle, pContext);
}

BOOL MLayeredDockingControlBar::CreateEx (DWORD dwStyleEx, 
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

	if (!CBCGPDockingControlBar::CreateEx (dwStyleEx, lpszCaption, pParentWnd, rect, bHasGripper, nID, dwStyle, dwTabbedStyle,
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

CBCGPMiniFrameWnd* MLayeredDockingControlBar::CreateDefaultMiniframe(CRect rectInitial)
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

CBCGPTabbedControlBar* MLayeredDockingControlBar::CreateTabbedControlBar ()
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

BOOL MLayeredDockingControlBar::LoadState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	CString strProfileName = ::BCGPGetRegPath (strControlBarProfile, lpszProfileName);

	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, strProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, strProfileName, nIndex, uiID);
	}

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	if (!reg.Open (strSection))
	{
		return FALSE;
	}

	reg.Read (_T ("CleanScreenVisible"), m_bCleanScreenVisible);

	return CBCGPDockingControlBar::LoadState (lpszProfileName, nIndex, uiID);
}

BOOL MLayeredDockingControlBar::SaveState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	CString strProfileName = ::BCGPGetRegPath (strControlBarProfile, lpszProfileName);

	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, strProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, strProfileName, nIndex, uiID);
	}

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	if (reg.CreateKey (strSection))
	{
		reg.Write (_T ("CleanScreenVisible"), m_bCleanScreenVisible);
	}

	return CBCGPDockingControlBar::SaveState (lpszProfileName, nIndex, uiID);
}

int MLayeredDockingControlBar::GetAlpha()
{
	CBCGPMiniFrameWnd* pParent = GetParentMiniFrame();

	if( pParent && pParent->GetSafeHwnd() )
	{
		
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredMultiMiniFrameWnd)) )
		{
			MLayeredMultiMiniFrameWnd* pMiniFrame = dynamic_cast<MLayeredMultiMiniFrameWnd*>(pParent);
			return pMiniFrame->GetAlpha();
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredMiniFrameWnd)) )
		{
			MLayeredMiniFrameWnd* pMiniFrame = dynamic_cast<MLayeredMiniFrameWnd*>(pParent);
			return pMiniFrame->GetAlpha();
		}
	}

	return (int)0xFF;
}

BOOL MLayeredDockingControlBar::OnBeforeShowControlBarMenu(CMenu& menu)
{
	return MControlBarMenuEditor::GetInstance()->EditMenu(menu);
}

void MLayeredDockingControlBar::UpdateFrame(BOOL bActive)
{
	CBCGPMiniFrameWnd* pParent = GetParentMiniFrame();

	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredMultiMiniFrameWnd)) )
		{
			MLayeredMultiMiniFrameWnd* pMiniFrame = dynamic_cast<MLayeredMultiMiniFrameWnd*>(pParent);
			return pMiniFrame->UpdateTransParent(bActive);
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredMiniFrameWnd)) )
		{
			MLayeredMiniFrameWnd* pMiniFrame = dynamic_cast<MLayeredMiniFrameWnd*>(pParent);
			return pMiniFrame->UpdateTransParent(bActive);
		}
	}
}

//***********************************************************************
void MLayeredDockingControlBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CBCGPDockingControlBar::OnNcCalcSize(bCalcValidRects, lpncsp);
}

//***********************************************************************
void MLayeredDockingControlBar::OnNcPaint() 
{
	CBCGPDockingControlBar::OnNcPaint();
}

BOOL MLayeredDockingControlBar::OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult)
{
	static CString strTipText;

	if (m_pToolTip->GetSafeHwnd () == NULL || 
		pNMH->hwndFrom != m_pToolTip->GetSafeHwnd ())
	{
		return FALSE;
	}

	LPNMTTDISPINFO	pTTDispInfo	= (LPNMTTDISPINFO) pNMH;
	ASSERT((pTTDispInfo->uFlags & TTF_IDISHWND) == 0);

	int nIndex = (int)pNMH->idFrom - 1;
	if (nIndex >= 0 && nIndex < (int) m_arrButtons.GetSize ())
	{
		CBCGPCaptionButton* pbtn = m_arrButtons [nIndex];
		ASSERT_VALID (pbtn);

		if (pbtn->GetCustomToolTip (strTipText))
		{
			pTTDispInfo->lpszText = const_cast<LPTSTR> ((LPCTSTR) strTipText);
			return TRUE;
		}
	}

	UINT nTooltipResID = 0;

	switch (pNMH->idFrom)
	{
	case 1:
		nTooltipResID = IDS_BCGBARRES_CLOSEBAR;
		break;

	case 2:
		{
			SHORT state = GetAsyncKeyState (VK_CONTROL);
			nTooltipResID = IDS_BCGBARRES_AUTOHIDEBAR;

			if ((state & 0x8000) && IsAutohideAllEnabled ())
			{
				nTooltipResID = IDS_BCGBARRES_AUTOHIDE_ALL;
			}
		}
		break;

	case 3:
		nTooltipResID = IDS_BCGBARRES_MENU;
		break;
	}

	if (nTooltipResID == 0)
	{
		return FALSE;
	}

	if (!MControlBarMenuEditor::GetInstance()->GetTooltipString(nTooltipResID, strTipText))
	{
		return CBCGPDockingControlBar::OnNeedTipText(id, pNMH, pResult);
	}

	pTTDispInfo->lpszText = const_cast<LPTSTR> ((LPCTSTR) strTipText);
	return TRUE;
}