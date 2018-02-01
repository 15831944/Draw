#include "stdafx.h"
#include "MLayeredMiniFrameWnd.h"
#include "MLayeredSliderCtrl.h"
#include "MLayeredWindow.h"
#include "MVisualManager.h"

#include "RegPath.h"
#include "BCGPRegistry.h"

#include "MTableBar.h"
#include "MChartBar.h"

#include <afxregpath.h>

using namespace mit;
using namespace mit::frx;

class MFriendMDIFrameWnd : public CBCGPMDIFrameWnd
{
	friend class MLayeredMiniFrameWnd;
};

static const CString strMLayeredMiniFrameWndProfile = _T ("MLayeredMiniFrameWnds");

#define REG_SECTION_FMT					_T("%sMLayeredMiniFrameWnd")
#define REG_SECTION_FMT_EX				_T("%sMLayeredMiniFrameWnd-%x")

// private 멤버 접근용
class MInplaceToolTipCtrl : public CBCGPInplaceToolTipCtrl
{
	friend class MLayeredMiniFrameWnd;
	DECLARE_DYNAMIC(MInplaceToolTipCtrl)
};

IMPLEMENT_SERIAL(MLayeredMiniFrameWnd, CBCGPMiniFrameWnd,VERSIONABLE_SCHEMA | 2)
MLayeredMiniFrameWnd::MLayeredMiniFrameWnd(void)
{
	m_pSlider = NULL;
	m_bTrack = FALSE;
	m_alpha = 0xFF;
	m_bLoadState = FALSE;
	m_ptMouse.SetPoint(-1,-1);
	m_fade.SetFadeStep(5);
}

MLayeredMiniFrameWnd::~MLayeredMiniFrameWnd(void)
{
	m_pSlider = NULL;
}

BEGIN_MESSAGE_MAP(MLayeredMiniFrameWnd, CBCGPMiniFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_NCPAINT()
	ON_WM_SIZE()	
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCCREATE()
	ON_WM_NCHITTEST()
	ON_WM_NCMOUSELEAVE()
END_MESSAGE_MAP()

void MLayeredMiniFrameWnd::RecalcCaptionHeight ()
{
	CBCGPMiniFrameWnd::RecalcCaptionHeight();
}

void MLayeredMiniFrameWnd::OnBarRecalcLayout ()
{
	CBCGPMiniFrameWnd::OnBarRecalcLayout();

	if( m_pSlider )
	{
		CRect rectCaption;
		GetCaptionRect (rectCaption);

		CSize btnSize = CBCGPCaptionButton::GetSize ();

		CRect rect = rectCaption;
		rect.right -= (btnSize.cx + 10);
		rect.left = rect.right - m_pSlider->GetWidth();

		m_pSlider->SetRect(rect);
	}
}

int MLayeredMiniFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// jpahn: CBCGPMiniFrameWnd 생성자에서 호출해서 오버라이딩한게 호출되지 않음.
	//        또한 생성자에서 호출하면 MVisualManager 가 아닐수도 있을거 같아 여기서 부른다.
	RecalcCaptionHeight();

	LONG lExStyle = GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, lExStyle | WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, MFadeEffect::FADE_MAX, LWA_ALPHA);

	SetTimer(IDT_MOUSE_TRACK, MFadeEffect::ELAPSE_DEFAULT * 4, NULL);
	m_fade.Create(this);

	return 0;
}

void MLayeredMiniFrameWnd::OnDestroy()
{
	CBCGPMiniFrameWnd::OnDestroy();

	KillTimer(IDT_MOUSE_TRACK);
	m_fade.Destroy();
}

void MLayeredMiniFrameWnd::OnTimer(UINT_PTR nIDEvent)
{
	CBCGPMiniFrameWnd::OnTimer(nIDEvent);
	if (nIDEvent == IDT_MOUSE_TRACK)
	{   
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);
		if (m_ptMouse == ptMouse) return;
		m_ptMouse = ptMouse;
		UpdateFade();
	}
}

void MLayeredMiniFrameWnd::OnNcPaint()
{
	CBCGPDockManager* pDockManager = m_pDockManager != NULL ? m_pDockManager : globalUtils.GetDockManager (GetParent ());
	if (pDockManager == NULL)
	{
		return;
	}

	ASSERT_VALID (pDockManager);

	if (pDockManager->m_bLockUpdate)
	{
		return;
	}


	CWindowDC dc(this); // device context for painting

	CDC*		pDC = &dc;
	BOOL		m_bMemDC = FALSE;
	CDC			dcMem;
	CBitmap		bmp;
	CBitmap*	pOldBmp = NULL;

	CRect rectWindow;
	GetWindowRect (rectWindow);
	CRect rect;
	rect.SetRect (0, 0, rectWindow.Width(), rectWindow.Height());

	if (dcMem.CreateCompatibleDC (&dc) &&
		bmp.CreateCompatibleBitmap (&dc, rect.Width (),
		rect.Height ()))
	{
		//-------------------------------------------------------------
		// Off-screen DC successfully created. Better paint to it then!
		//-------------------------------------------------------------
		m_bMemDC = TRUE;
		pOldBmp = dcMem.SelectObject (&bmp);
		pDC = &dcMem;
	}

	// client area is not our bussiness :)
	CRect rcClient, rcBar;
	GetWindowRect(rcBar);

	GetClientRect(rcClient);
	ClientToScreen(rcClient);
	rcClient.OffsetRect(-rcBar.TopLeft());

	dc.ExcludeClipRect (rcClient);

	CRgn rgn;
	if (!m_rectRedraw.IsRectEmpty ())
	{
		rgn.CreateRectRgnIndirect (m_rectRedraw);
		dc.SelectClipRgn (&rgn);
	}

	// draw border
	OnDrawBorder (pDC);

	CRect rectCaption;
	GetCaptionRect (rectCaption);

	pDockManager = m_pDockManager != NULL ? m_pDockManager : globalUtils.GetDockManager (GetParent ());
	ASSERT_VALID (pDockManager);	
	if (pDockManager->m_bLockUpdate)
	{
		rectCaption.SetRectEmpty ();	
	}

	// draw caption:
	GetCaptionRect (rectCaption);

	COLORREF clrText = CBCGPVisualManager::GetInstance ()->OnFillMiniFrameCaption (
		pDC, rectCaption, this, m_bActive && !m_bHostsToolbar);

	int xBtnsLeft = -1;
	int xBtnsRight = -1;
	for (POSITION pos = m_lstCaptionButtons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPCaptionButton* pBtn = (CBCGPCaptionButton*) m_lstCaptionButtons.GetNext (pos);
		ASSERT_VALID (pBtn);

		pBtn->m_clrForeground = clrText;

		if (!pBtn->m_bHidden)
		{
			if (pBtn->m_bLeftAlign)
			{
				if (xBtnsRight == -1)
				{
					xBtnsRight = pBtn->GetRect ().right + 2;
				}
				else
				{
					xBtnsRight = max (xBtnsRight, pBtn->GetRect ().right + 2);
				}
			}
			else
			{
				if (xBtnsLeft == -1)
				{
					xBtnsLeft = pBtn->GetRect ().left;
				}
				else
				{
					xBtnsLeft = min (xBtnsLeft, pBtn->GetRect ().left);
				}
			}
		}
	}

	// Paint caption text:
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (clrText);

	CFont* pOldFont = pDC->SelectObject(
		CBCGPVisualManager::GetInstance()->UseLargeCaptionFontInDockingCaptions() ?
		&globalData.fontCaption :
	CBCGPVisualManager::GetInstance ()->IsMinFrameCaptionBold(this) ? &globalData.fontBold : &globalData.fontRegular);
	ASSERT_VALID (pOldFont);

	CString strCaption = GetCaptionText ();

	CRect rectText = rectCaption;
	if (xBtnsLeft != -1)
	{
		rectText.right = xBtnsLeft;
	}
	if (xBtnsRight != -1)
	{
		rectText.left = xBtnsRight;
	}

	rectText.DeflateRect (2, 0);

	if (CBCGPVisualManager::GetInstance ()->IsDockingTabUpperCase())
	{
		strCaption.MakeUpper();
	}

	CBCGPVisualManager::GetInstance ()->OnDrawControlBarCaptionText (pDC, DYNAMIC_DOWNCAST (CBCGPDockingControlBar, GetFirstVisibleBar ()), m_bActive && !m_bHostsToolbar, strCaption, rectText);

	pDC->SelectObject (pOldFont);
	pDC->SelectClipRgn (NULL);

	// Paint caption buttons:
	OnDrawCaptionButtons (pDC);

	if (m_bMemDC)
	{
		//--------------------------------------
		// Copy the results to the on-screen DC:
		//-------------------------------------- 
		CRect rectClip;
		int nClipType = dc.GetClipBox (rectClip);
		if (nClipType != NULLREGION)
		{
			if (nClipType != SIMPLEREGION)
			{
				rectClip = rect;
			}

			dc.BitBlt (rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(),
				&dcMem, rectClip.left, rectClip.top, SRCCOPY);
		}

		dcMem.SelectObject(pOldBmp);
	}

	CWnd::OnNcPaint ();
}

void MLayeredMiniFrameWnd::OnSize(UINT nType, int cx, int cy)
{
	CBCGPMiniFrameWnd::OnSize(nType, cx, cy);
}

void MLayeredMiniFrameWnd::AddControlBar (CBCGPBaseControlBar* pWnd)
{
	ASSERT_VALID (pWnd);

	m_bHostsToolbar = pWnd->IsKindOf(RUNTIME_CLASS (CBCGPToolBar));
	if (m_hEmbeddedBar != pWnd->GetSafeHwnd ())
	{
		m_hEmbeddedBar = pWnd->GetSafeHwnd ();

		CString strText;
		pWnd->GetWindowText (strText);
		SetWindowText (strText);

		SetIcon (pWnd->GetIcon (FALSE), FALSE);
		SetIcon (pWnd->GetIcon (TRUE), TRUE);

		AddRemoveBarFromGlobalList (pWnd, TRUE);
		if (pWnd->CanBeClosed ())
		{
			if (m_bHostsToolbar)
			{
				CBCGPToolBar* pWndToolBar = (CBCGPToolBar*)pWnd;
				if(pWndToolBar->IsExistCustomizeButton() && pWndToolBar->IsAddRemoveQuickCustomize())
				{
					SetCaptionButtons (BCGP_CAPTION_BTN_CLOSE|BCGP_CAPTION_BTN_CUSTOMIZE);
				}
				else
				{
					SetCaptionButtons (BCGP_CAPTION_BTN_CLOSE); 
				}

			}
			else
			{
				SetCaptionButtons (BCGP_CAPTION_BTN_CLOSE); 
			}
		}
		else
		{
			SetCaptionSlider(pWnd);
		}

		if(pWnd->IsKindOf(RUNTIME_CLASS (CBCGPMenuBar)))
		{
			CBCGPToolBar* pWndToolBar = (CBCGPToolBar*)pWnd;
			if(pWndToolBar->IsExistCustomizeButton())
			{
				SetCaptionButtons (BCGP_CAPTION_BTN_CUSTOMIZE);
			}

		}
		OnSetRollUpTimer ();
	}
}

void MLayeredMiniFrameWnd::SetCaptionSlider (CBCGPBaseControlBar* pWnd)
{
	ASSERT_VALID (this);
	RemoveAllCaptionButtons ();

	m_dwCaptionButtons = 0;

	//////////////////////////////////////////////////////////////////////////
	if( !m_bLoadState )
	{
		CBCGPWorkspace* pWorkspace = GetWorkspace();
		CString strSection = pWorkspace->GetRegSectionPath ();
		LoadState(strSection);

		//CString controlBarsReg(REGISTRY_PROFILES);
		//controlBarsReg += _T("\\");
		//CString curProfileName;
		//IcadSharedGlobals::GetCurrentProfileName(curProfileName);
		//controlBarsReg += curProfileName;
		//controlBarsReg += REGISTRY_CTRLBARS_CTRLBAR;
		//controlBarsReg += _T("\\");
		//CString strSection = ::AFXGetRegPath(controlBarsReg);
		//LoadState(strSection);

		m_bLoadState = TRUE;
	}
	//////////////////////////////////////////////////////////////////////////

	//ASSERT(!m_pSlider);

	//////////////////////////////////////////////////////////////////////////
	m_pSlider = new MLayeredSliderCtrl(30);
	m_pSlider->SetRange(1, 255);

	CRect rectCaption;
	GetCaptionRect (rectCaption);

	CRect rect = rectCaption;
	rect.right -= 10;
	rect.left = rect.right - m_pSlider->GetWidth();

	m_pSlider->SetRect(rect);

	m_pSlider->SetPos(m_alpha);
	m_pSlider->SetParentMiniFrame(this);

	m_lstCaptionButtons.AddHead (m_pSlider);
	//////////////////////////////////////////////////////////////////////////

	SetCaptionButtonsToolTips ();
	ArrangeCaptionButtons ();
	SendMessage (WM_NCPAINT);

	UpdateFade();
}

void MLayeredMiniFrameWnd::SetCaptionButtons (DWORD dwButtons)
{
	ASSERT_VALID (this);
	RemoveAllCaptionButtons ();

	if (dwButtons & BCGP_CAPTION_BTN_CLOSE)
	{
		CBCGPBaseControlBar* pBar = DYNAMIC_DOWNCAST (CBCGPBaseControlBar, GetControlBar ());
		if (pBar != NULL && pBar->CanBeClosed ())
		{
			AddButton (HTCLOSE);
		}
	}

	if (dwButtons & BCGP_CAPTION_BTN_PIN)
	{
		AddButton (HTMAXBUTTON);
	}

	if (dwButtons & BCGP_CAPTION_BTN_MENU)
	{
		AddButton (HTMINBUTTON);
	}

	if(dwButtons & BCGP_CAPTION_BTN_CUSTOMIZE)
	{
		AddButton(HTMENU_BCG); 
	}

	m_dwCaptionButtons = dwButtons;

	//////////////////////////////////////////////////////////////////////////
	if( !m_bLoadState )
	{
		CBCGPWorkspace* pWorkspace = GetWorkspace();
		CString strSection = pWorkspace->GetRegSectionPath ();
		LoadState(strSection);

		//CString controlBarsReg(REGISTRY_PROFILES);
		//controlBarsReg += _T("\\");
		//CString curProfileName;
		//IcadSharedGlobals::GetCurrentProfileName(curProfileName);
		//controlBarsReg += curProfileName;
		//controlBarsReg += REGISTRY_CTRLBARS_CTRLBAR;
		//controlBarsReg += _T("\\");
		//CString strSection = ::AFXGetRegPath(controlBarsReg);
		//LoadState(strSection);

		m_bLoadState = TRUE;
	}
	//////////////////////////////////////////////////////////////////////////

	//ASSERT(!m_pSlider);

	//////////////////////////////////////////////////////////////////////////
	m_pSlider = new MLayeredSliderCtrl(30);
	m_pSlider->SetRange(1, 255);

	CRect rectCaption;
	GetCaptionRect (rectCaption);

	CSize btnSize = CBCGPCaptionButton::GetSize ();

	CRect rect = rectCaption;
	rect.right -= (btnSize.cx + 10);
	rect.left = rect.right - m_pSlider->GetWidth();

	m_pSlider->SetRect(rect);

	m_pSlider->SetPos(m_alpha);
	m_pSlider->SetParentMiniFrame(this);

	m_lstCaptionButtons.AddHead (m_pSlider);
	//////////////////////////////////////////////////////////////////////////

	SetCaptionButtonsToolTips ();
	ArrangeCaptionButtons ();
	SendMessage (WM_NCPAINT);

	UpdateFade();
}

void MLayeredMiniFrameWnd::OnDrawCaptionButtons (CDC* pDC)
{
	ASSERT_VALID (pDC);

	// Paint caption buttons:
	for (POSITION pos = m_lstCaptionButtons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPCaptionButton* pBtn = (CBCGPCaptionButton*) m_lstCaptionButtons.GetNext (pos);
		ASSERT_VALID (pBtn);

		BOOL bMaximized = TRUE;
		if (pBtn->GetHit () == HTMAXBUTTON && m_bPinned)
		{
			bMaximized = FALSE;
		}

		BOOL bEnabled = TRUE;
		if(CBCGPToolBar::IsCustomizeMode())
		{
			if ((pBtn->GetHit () == HTCLOSE) || (pBtn->GetHit () == HTCLOSE_BCG))
			{
				bEnabled = TRUE;
			}
			pBtn->m_bEnabled = bEnabled;
		}

		pBtn->OnDraw (pDC, m_bActive && !m_bHostsToolbar, TRUE, bMaximized, !bEnabled);

		pBtn->m_clrForeground = (COLORREF)-1;
	}
}

void MLayeredMiniFrameWnd::StartFade(BYTE bAlpha)
{
	BYTE bCurrentAlpha;
	GetLayeredWindowAttributes(NULL, &bCurrentAlpha, NULL);
	if (!m_fade.StartFade((int)bCurrentAlpha, (int)bAlpha)) return;
}

void MLayeredMiniFrameWnd::OnFade(MFadeEffect* pFade)
{
	BYTE bCurrentAlpha;
	GetLayeredWindowAttributes(NULL, &bCurrentAlpha, NULL);
	m_fade.OnFade(bCurrentAlpha);
	SetLayeredWindowAttributes(0, (BYTE)m_fade.GetFade(), LWA_ALPHA);
}

BOOL MLayeredMiniFrameWnd::IsMouseOver(const CPoint& pt)
{
	// WindowRect 를 Check 하면 ComboBox의 ListCtrl이 밖으로 벗어날때를 처리 못함.
	const BOOL bCheckWindowRectRect = FALSE; 
	if (bCheckWindowRectRect)
	{
		CRect rectWnd;
		GetWindowRect(rectWnd);
		if (!rectWnd.PtInRect(pt)) return FALSE;
	}

	HWND hWnd = ::WindowFromPoint(pt);
	if (hWnd == NULL) return FALSE;
	CWnd* pWnd = CWnd::FromHandle(hWnd);
	if (pWnd == NULL) return FALSE;

	// ComboBox의 List 예외처리
	TCHAR buf[MAX_PATH];
	::GetClassName(hWnd, buf, MAX_PATH);
	CString strClassName(buf);
	if (strClassName == _T("ComboLBox") && pWnd->GetSafeOwner() == this) return TRUE;

	// ToolTip 예외처리
	if (pWnd->IsKindOf(RUNTIME_CLASS(CBCGPInplaceToolTipCtrl)))
	{
		MInplaceToolTipCtrl* pToolTip = (MInplaceToolTipCtrl*)pWnd;
		pWnd = pToolTip->m_pWndParent;
	}

	return (pWnd->GetParentOwner() == this);
}

void MLayeredMiniFrameWnd::UpdateFade()
{
	if (m_pSlider->IsPressed()) return;
	if (IsMouseOver(m_ptMouse)) StartFade(MFadeEffect::FADE_MAX);
	else StartFade(GetAlpha());
}

void MLayeredMiniFrameWnd::ScreenToWindow(LPPOINT lpPoint)
{
	CRect rectBorderSize;
	rectBorderSize.SetRectEmpty (); 
	CalcBorderSize(rectBorderSize);
	lpPoint->x += rectBorderSize.left;
	lpPoint->y += rectBorderSize.top + m_nCaptionHeight;
	ScreenToClient(lpPoint);
}

void MLayeredMiniFrameWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	CPoint pt = point;	
	if( nHitTest == HTOBJECT )
	{
		if( m_pSlider )
		{
			ScreenToWindow(&pt);

			m_pSlider->OnLButtonDown(pt);
			m_pSlider->m_bIsPressed = TRUE;

			SendMessage(WM_NCPAINT);

			return;
		}
	}

	CBCGPMiniFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void MLayeredMiniFrameWnd::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CPoint pt = point;	
	if( nHitTest == HTOBJECT )
	{
		if( m_pSlider )
		{
			ScreenToWindow(&pt);

			m_pSlider->OnLButtonUp(pt);
			m_pSlider->m_bIsPressed = FALSE;

			SendMessage(WM_NCPAINT);

			return;

		}
	}

	if( m_pSlider )
	{
		m_pSlider->m_bIsPressed = FALSE;

		SendMessage(WM_NCPAINT);
	}

	CBCGPMiniFrameWnd::OnNcLButtonUp(nHitTest, point);
}

void MLayeredMiniFrameWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPoint pt = point;

	if (GetCapture() == this)
	{
		if (m_pSlider && m_pSlider->IsPressed())
		{
			ClientToScreen(&pt);
			ScreenToWindow(&pt);

			m_pSlider->OnLButtonUp(pt);
			m_pSlider->m_bIsPressed = FALSE;

			SendMessage(WM_NCPAINT);

			return;
		}
	}

	CBCGPMiniFrameWnd::OnLButtonUp(nFlags, point);
}

void MLayeredMiniFrameWnd::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if( m_bTrack == FALSE )
	{
		TRACKMOUSEEVENT MouseEvent;

		::ZeroMemory( &MouseEvent, sizeof( MouseEvent ) );

		// 최초 변수 생성 후 ZeroMemory를 사용해 초기화
		// cbSize에 sizeof를 사용해 크기 저장
		MouseEvent.cbSize       = sizeof( MouseEvent );

		// dwFlag는 TME_LEAVE, WM_MOUSELEAVE 메시지를 수신,
		MouseEvent.dwFlags      = TME_LEAVE | TME_NONCLIENT;

		// CWnd의 핸들 m_hWnd를 넣어 준다.
		MouseEvent.hwndTrack    = m_hWnd;

		// 마우스 커서가 현재 윈도우에 존재하면 TRUE
		m_bTrack = ::_TrackMouseEvent( &MouseEvent );
	}

	CPoint pt = point;
	if( nHitTest == HTOBJECT )
	{
		if( m_pSlider )
		{
			ScreenToWindow(&pt);

			if (!m_pSlider->IsHighlighted() )
			{
				m_pSlider->m_bIsHighlighted = TRUE;
			}

			m_pSlider->OnMouseMove(pt);
			SendMessage(WM_NCPAINT);
			return;
		}
	}
	else
	{
		if( m_pSlider )
		{
			if (m_pSlider->IsHighlighted())
			{
				m_pSlider->m_bIsHighlighted = FALSE;
				SendMessage(WM_NCPAINT);
			}
		}
	}

	CBCGPMiniFrameWnd::OnNcMouseMove(nHitTest, point);
}

void MLayeredMiniFrameWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pt = point;

	if (GetCapture() == this)
	{
		if (m_pSlider && m_pSlider->IsPressed())
		{
			ClientToScreen(&pt);
			ScreenToWindow(&pt);

			m_pSlider->OnMouseMove(pt);

			SendMessage(WM_NCPAINT);

			return;
		}
	}

	MFriendMDIFrameWnd* pMainFrame = NULL;
	BOOL bOldCanCovertControlBarToMDIChild = FALSE;

	CWnd* pWnd = AfxGetMainWnd();
	if( pWnd && pWnd->GetSafeHwnd() && pWnd->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)) )
	{
		pMainFrame = reinterpret_cast<MFriendMDIFrameWnd*>(pWnd);
		ASSERT_VALID(pMainFrame);

		bOldCanCovertControlBarToMDIChild = pMainFrame->m_bCanCovertControlBarToMDIChild;

		CWnd* pBar = GetControlBar();
		if( pBar && pBar->GetSafeHwnd() && (pBar->IsKindOf(RUNTIME_CLASS(MTableBar)) || pBar->IsKindOf(RUNTIME_CLASS(MChartBar))) )
		{
			pMainFrame->m_bCanCovertControlBarToMDIChild = TRUE;
		}
	}

	CBCGPMiniFrameWnd::OnMouseMove(nFlags, point);

	if( pMainFrame && pMainFrame->GetSafeHwnd() )
		pMainFrame->m_bCanCovertControlBarToMDIChild = bOldCanCovertControlBarToMDIChild;
}


void MLayeredMiniFrameWnd::OnNcMouseLeave()
{
	m_bTrack = FALSE;

	if (GetCapture() != this)
	{
		if ( m_pSlider )
		{
			m_pSlider->m_bIsHighlighted = FALSE;
			m_pSlider->m_bIsPressed = FALSE;
			SendMessage(WM_NCPAINT);
		}
	}


	CBCGPMiniFrameWnd::OnNcMouseLeave();
}

void MLayeredMiniFrameWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CBCGPMiniFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

BOOL MLayeredMiniFrameWnd::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CBCGPMiniFrameWnd::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return TRUE;
}

LRESULT MLayeredMiniFrameWnd::OnNcHitTest(CPoint point)
{
	CPoint pt = point;
	ScreenToWindow(&pt);

	CRect rectCaption;
	GetCaptionRect(rectCaption);

	if( rectCaption.PtInRect(pt) )
	{
		if( m_pSlider )
		{
			if( m_pSlider->GetHitTest(pt) >= 0 )
				return HTOBJECT;
		}
	}

	return CBCGPMiniFrameWnd::OnNcHitTest(point);
}

BOOL MLayeredMiniFrameWnd::OnBeforeDock ()
{
	//CString controlBarsReg(REGISTRY_PROFILES);
	//controlBarsReg += _T("\\");
	//CString curProfileName;
	//IcadSharedGlobals::GetCurrentProfileName(curProfileName);
	//controlBarsReg += curProfileName;
	//controlBarsReg += REGISTRY_CTRLBARS_CTRLBAR;
	//controlBarsReg += _T("\\");
	//CString strSection = ::AFXGetRegPath(controlBarsReg);
	CBCGPWorkspace* pWorkspace = GetWorkspace();
	CString strSection = pWorkspace->GetRegSectionPath ();

	SaveState(strSection);

	return CBCGPMiniFrameWnd::OnBeforeDock();
}

BOOL MLayeredMiniFrameWnd::SaveState (LPCTSTR lpszProfileName, UINT uiID)
{
	CString strProfileName = ::BCGPGetRegPath (strMLayeredMiniFrameWndProfile, lpszProfileName);

	CString strSection;
	if (uiID == (UINT) -1)
	{
		CWnd* pWnd = GetFirstVisibleBar();
		if( pWnd && pWnd->GetSafeHwnd() && pWnd->IsKindOf(RUNTIME_CLASS(CBCGPTabbedControlBar)) )
		{
			CBCGPTabbedControlBar* pTabbedBar = (CBCGPTabbedControlBar*)pWnd;

			int nFirstTab = 0;
			pWnd = pTabbedBar->GetFirstVisibleTab(nFirstTab);
		}

		if( pWnd && pWnd->GetSafeHwnd()  )
		{
			uiID = pWnd->GetDlgCtrlID();
			strSection.Format (REG_SECTION_FMT_EX, strProfileName, uiID);
		}
		else
			strSection.Format (REG_SECTION_FMT, strProfileName);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, strProfileName, uiID);
	}

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	int factor = m_pSlider->GetPos();

	if (reg.CreateKey (strSection))
	{
		reg.Write (_T ("Alpha"), (int&)factor);
	}

	return CBCGPMiniFrameWnd::SaveState(lpszProfileName, uiID);
}

BOOL MLayeredMiniFrameWnd::LoadState (LPCTSTR lpszProfileName, UINT uiID)
{
	CString strProfileName = ::BCGPGetRegPath (strMLayeredMiniFrameWndProfile, lpszProfileName);

	CString strSection;
	if (uiID == (UINT) -1)
	{
		CWnd* pWnd = GetFirstVisibleBar();
		if( pWnd && pWnd->GetSafeHwnd() && pWnd->IsKindOf(RUNTIME_CLASS(CBCGPTabbedControlBar)) )
		{
			CBCGPTabbedControlBar* pTabbedBar = (CBCGPTabbedControlBar*)pWnd;

			int nFirstTab = 0;
			pWnd = pTabbedBar->GetFirstVisibleTab(nFirstTab);
		}

		if( pWnd && pWnd->GetSafeHwnd()  )
		{
			uiID = pWnd->GetDlgCtrlID();
			strSection.Format (REG_SECTION_FMT_EX, strProfileName, uiID);
		}
		else
			strSection.Format (REG_SECTION_FMT, strProfileName);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, strProfileName, uiID);
	}

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	if (!reg.Open (strSection))
	{
		return FALSE;
	}

	int factor = 0;
	reg.Read (_T ("Alpha"), (int&) factor);
	m_alpha = (BYTE)factor;

	return  CBCGPMiniFrameWnd::LoadState(lpszProfileName, uiID);
}

int	MLayeredMiniFrameWnd::GetAlpha()
{
	if( m_pSlider )
		return m_pSlider->GetPos();

	return MFadeEffect::FADE_MAX;
}