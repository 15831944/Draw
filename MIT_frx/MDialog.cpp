#include "stdafx.h"

#include "MDialog.h"

#include "./bcg/BCGCBPro.h"
#include "./bcg/BCGPDlgImpl.h"
#include "./bcg/BCGPVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit::frx;

class mitDlgImpl : public CBCGPDlgImpl
{
	friend class MDialog;

	mitDlgImpl(CWnd& dlg) : CBCGPDlgImpl( dlg ) {}
	virtual ~mitDlgImpl() {}

  void EnableVisualManagerStyle (BOOL bEnable, BOOL bNCArea, const CList<UINT,UINT>* plstNonSubclassedItems);

  HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
  {
    // hslee : 대화상자 색상 태두리 색상 변경 대화상자 안의 색도 변경하는 문제가 있어서 이를 수정하기 위한 처리
    return NULL;
// #define MAX_CLASS_NAME	255
// #define STATIC_CLASS	_T("Static")
// #define BUTTON_CLASS	_T("Button")
// 
//     if (m_bVisualManagerStyle && !m_lstNonSubclassedItems.IsEmpty() && m_lstNonSubclassedItems.Find (pWnd->GetDlgCtrlID ()) != NULL)
//     {
//       return NULL;
//     }
// 
//     if (nCtlColor == CTLCOLOR_STATIC)
//     {
//       TCHAR lpszClassName [MAX_CLASS_NAME + 1];
// 
//       ::GetClassName (pWnd->GetSafeHwnd (), lpszClassName, MAX_CLASS_NAME);
//       CString strClass = lpszClassName;
// 
//       if (m_lstNonSubclassedWndClasses.Find(strClass) != NULL)
//       {
//         return NULL;
//       }
// 
//       if (strClass == STATIC_CLASS)
//       {
//         pDC->SetBkMode(TRANSPARENT);
// 
//         if (m_bVisualManagerStyle)
//         {
//           pDC->SetTextColor (visualManager->GetDlgTextColor(&m_Dlg));
//         }
// 
//         if (m_bTransparentStaticCtrls && (pWnd->GetStyle () & SS_ICON) != SS_ICON)
//         {
//           return (HBRUSH) ::GetStockObject (HOLLOW_BRUSH);
//         }
// 
//         if (m_bIsWhiteBackground && !globalData.IsHighContastMode() && !visualManager->IsDarkTheme())
//         {
//           return (HBRUSH) ::GetStockObject (WHITE_BRUSH);
//         }
// 
//         return (HBRUSH) visualManager->GetDlgBackBrush (&m_Dlg).GetSafeHandle ();
//       }
// 
//       if (strClass == BUTTON_CLASS)
//       {
//         DWORD dwStyle = pWnd->GetStyle ();
// 
//         if (dwStyle & BS_GROUPBOX)
//         {
//           if (m_bVisualManagerStyle)
//           {
//             pDC->SetTextColor (globalData.clrBarText);
//             pDC->SetBkMode(TRANSPARENT);
//             return (HBRUSH) visualManager->GetDlgBackBrush (&m_Dlg).GetSafeHandle ();
//           }
//         }
// 
//         if ((dwStyle & BS_CHECKBOX) == 0)
//         {
//           pDC->SetBkMode(TRANSPARENT);
//         }
// 
//         return (HBRUSH) ::GetStockObject (m_bIsWhiteBackground && !globalData.IsHighContastMode() && !visualManager->IsDarkTheme() ? WHITE_BRUSH : HOLLOW_BRUSH);
//       }
//     }

    return NULL;
  }

};


void mitDlgImpl::EnableVisualManagerStyle( BOOL bEnable, BOOL bNCArea, const CList<UINT,UINT>* plstNonSubclassedItems )
{  
  m_bVisualManagerStyle = bEnable;
  m_bVisualManagerNCArea = bNCArea;

  if (m_lstNonSubclassedItems.IsEmpty() && plstNonSubclassedItems != NULL)
  {
    m_lstNonSubclassedItems.AddTail((CList<UINT,UINT>*)plstNonSubclassedItems);
  }

  if (m_Dlg.GetSafeHwnd () == NULL)
  {
    return;
  }

  // hslee : 대화상자 컨트럴들은 CInternationalDlg 의 생성자에서 EnableVisualManagerStyle() 를 TRUE로 세팅하더라도 MFC 기본 대화상자처럼 그리도록 수정 함
  /*
  CWnd* pWndChild = m_Dlg.GetWindow (GW_CHILD);

  while (pWndChild != NULL)
  {
    ASSERT_VALID (pWndChild);

    if (plstNonSubclassedItems != NULL && plstNonSubclassedItems->Find (pWndChild->GetDlgCtrlID ()) != NULL)
    {
      pWndChild = pWndChild->GetNextWindow ();
      continue;
    }

    if (m_lstNonSubclassedItems.Find (pWndChild->GetDlgCtrlID ()) != NULL)
    {
      pWndChild = pWndChild->GetNextWindow ();
      continue;
    }

    CBCGPButton* pButton = DYNAMIC_DOWNCAST(CBCGPButton, pWndChild);
    if (pButton != NULL)
    {
      ASSERT_VALID (pButton);
      pButton->m_bVisualManagerStyle = m_bVisualManagerStyle;
    }

    if (m_bVisualManagerStyle &&
      CWnd::FromHandlePermanent (pWndChild->GetSafeHwnd ()) == NULL)
    {
#define MAX_CLASS_NAME		255
#define STATIC_CLASS		_T("Static")
#define BUTTON_CLASS		_T("Button")
#define EDIT_CLASS			_T("Edit")
#define	COMBOBOX_CLASS		_T("ComboBox")
#define SCROLLBAR_CLASS		_T("ScrollBar")

      TCHAR lpszClassName [MAX_CLASS_NAME + 1];

      ::GetClassName (pWndChild->GetSafeHwnd (), lpszClassName, MAX_CLASS_NAME);
      CString strClass = lpszClassName;

      CWnd* pWndSubclassedCtrl = NULL;

      if (m_lstNonSubclassedWndClasses.Find(strClass) != NULL)
      {
        pWndChild = pWndChild->GetNextWindow ();
        continue;
      }

      if (strClass == STATIC_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPStatic;
      }
      else if (strClass == BUTTON_CLASS)
      {
        if ((pWndChild->GetStyle () & 0xF) == BS_GROUPBOX)
        {
          pWndSubclassedCtrl = new CBCGPGroup;
        }
        else
        {
          pWndSubclassedCtrl = new CBCGPButton;
        }
      }
      else if (strClass == PROGRESS_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPProgressCtrl;
      }
      else if (strClass == TRACKBAR_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPSliderCtrl;
      }
      else if (strClass == EDIT_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPEdit;
      }
      else if (strClass == COMBOBOX_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPComboBox;
      }
      else if (strClass == SCROLLBAR_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPScrollBar;
      }
      else if (strClass == UPDOWN_CLASS)
      {
        pWndSubclassedCtrl = new CBCGPSpinButtonCtrl;
      }

      if (pWndSubclassedCtrl != NULL)
      {
        m_arSubclassedCtrls.Add (pWndSubclassedCtrl);
        pWndSubclassedCtrl->SubclassWindow (pWndChild->GetSafeHwnd ());
      }
    }

    pWndChild->SendMessage (BCGM_ONSETCONTROLVMMODE, (WPARAM) bEnable);
    pWndChild = pWndChild->GetNextWindow ();
  }
  */
  OnChangeVisualManager ();

  if (m_Dlg.IsWindowVisible ())
  {
    m_Dlg.RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
  }
}


#define  M_CAST_DLG_IMPL(pObj)	\
	mitDlgImpl* pImpl = reinterpret_cast<mitDlgImpl*>((mitDlgImpl*)pObj);\
	ASSERT(pImpl)


IMPLEMENT_DYNAMIC(MDialog, CDialog)

/////////////////////////////////////////////////////////////////////////////
// MDialog dialog

#pragma warning (disable : 4355)

MDialog::MDialog()
{
	m_pImpl = new mitDlgImpl( *this );
	Initialize ();
}
//*************************************************************************************
MDialog::MDialog (UINT nIDTemplate, CWnd *pParent/*= NULL*/) : 
				CDialog (nIDTemplate, pParent)
{
	m_pImpl = new mitDlgImpl( *this );
	Initialize ();
}

MDialog::~MDialog()
{
	M_CAST_DLG_IMPL( m_pImpl );

	_SAFE_DELETE( pImpl );
}

#pragma warning (default : 4355)

//*************************************************************************************
void MDialog::Initialize ()
{
	m_hBkgrBitmap = NULL;
	m_sizeBkgrBitmap = CSize (0, 0);
	m_BkgrLocation = (EN_BACKGR_Location) -1;
	m_bAutoDestroyBmp = FALSE;
	m_bIsLocal = FALSE;
	m_bWasMaximized = FALSE;
}

BOOL MDialog::IsVisualManagerStyle () const
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->m_bVisualManagerStyle;
}

BOOL MDialog::IsVisualManagerNCArea () const
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->m_bVisualManagerNCArea;
}

BOOL MDialog::IsBackstageMode() const
{
// 	M_CAST_DLG_IMPL( m_pImpl );
// 
// 	return pImpl->m_bBackstageMode;

	// 지원 안함.
	return FALSE;
}

//*************************************************************************************
void MDialog::SetBackgroundColor (COLORREF color, BOOL bRepaint)
{
	if (m_brBkgr.GetSafeHandle () != NULL)
	{
		m_brBkgr.DeleteObject ();
	}

	if (color != (COLORREF)-1)
	{
		m_brBkgr.CreateSolidBrush (color);
	}

	if (bRepaint && GetSafeHwnd () != NULL)
	{
		Invalidate ();
		UpdateWindow ();
	}
}
//*************************************************************************************
void MDialog::SetBackgroundImage (HBITMAP hBitmap, 
								EN_BACKGR_Location location,
								BOOL bAutoDestroy,
								BOOL bRepaint)
{
	if (m_bAutoDestroyBmp && m_hBkgrBitmap != NULL)
	{
		::DeleteObject (m_hBkgrBitmap);
	}

	m_hBkgrBitmap = hBitmap;
	m_BkgrLocation = location;
	m_bAutoDestroyBmp = bAutoDestroy;

	if (hBitmap != NULL)
	{
		BITMAP bmp;
		::GetObject (hBitmap, sizeof (BITMAP), (LPVOID) &bmp);

		m_sizeBkgrBitmap = CSize (bmp.bmWidth, bmp.bmHeight);
	}
	else
	{
		m_sizeBkgrBitmap = CSize (0, 0);
	}

	if (bRepaint && GetSafeHwnd () != NULL)
	{
		Invalidate ();
		UpdateWindow ();
	}
}
//*************************************************************************************
BOOL MDialog::SetBackgroundImage (UINT uiBmpResId,
									EN_BACKGR_Location location,
									BOOL bRepaint)
{
	HBITMAP hBitmap = NULL;

	if (uiBmpResId != 0)
	{
		//-----------------------------
		// Try to load PNG image first:
		//-----------------------------
		CBCGPPngImage pngImage;
		if (pngImage.Load (MAKEINTRESOURCE (uiBmpResId)))
		{
			hBitmap = (HBITMAP) pngImage.Detach ();
		}
		else
		{
			hBitmap = ::LoadBitmap (AfxGetResourceHandle (), MAKEINTRESOURCE (uiBmpResId));
		}

		if (hBitmap == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}
	}

	SetBackgroundImage (hBitmap, location, TRUE /* Autodestroy */, bRepaint);
	return TRUE;
}

BEGIN_MESSAGE_MAP(MDialog, CDialog)
	//{{AFX_MSG_MAP(MDialog)
	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_WM_ENABLE()	
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SETTINGCHANGE()
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DWMCOMPOSITIONCHANGED, OnDWMCompositionChanged)
	ON_REGISTERED_MESSAGE(BCGM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_POWERBROADCAST, OnPowerBroadcast)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MDialog message handlers

void MDialog::OnActivate(UINT nState, CWnd *pWndOther, BOOL /*bMinimized*/) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	Default();

	pImpl->OnActivate (nState, pWndOther);
}
//*************************************************************************************
BOOL MDialog::OnNcActivate(BOOL bActive) 
{
	//-----------------------------------------------------------
	// Do not call the base class because it will call Default()
	// and we may have changed bActive.
	//-----------------------------------------------------------
	M_CAST_DLG_IMPL( m_pImpl );

	BOOL bRes = (BOOL)DefWindowProc (WM_NCACTIVATE, bActive, 0L);

	if (bRes)
	{
		pImpl->OnNcActivate (bActive);
	}

	return bRes;
}

void MDialog::OnEnable(BOOL bEnable) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	CDialog::OnEnable (bEnable);
	
	pImpl->OnNcActivate (bEnable);
}

//**************************************************************************************
BOOL MDialog::OnEraseBkgnd(CDC* pDC) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	BOOL bRes = TRUE;

  // hslee :  대화상자 색상 태두리 색상 변경 대화상자 안의 색도 변경하는 문제가 있어서 이를 수정하기 위한 처리
  //if (m_brBkgr.GetSafeHandle () == NULL && m_hBkgrBitmap == NULL &&
  //	!IsVisualManagerStyle ())
	{
		bRes = CDialog::OnEraseBkgnd (pDC);
	}
	//else
	//{
	//	ASSERT_VALID (pDC);
  //
	//	CRect rectClient;
	//	GetClientRect (rectClient);
  //
	//	if (m_BkgrLocation != BACKGR_TILE || m_hBkgrBitmap == NULL)
	//	{
	//		if (m_brBkgr.GetSafeHandle () != NULL)
	//		{
	//			pDC->FillRect (rectClient, &m_brBkgr);
	//		}
	//		else if (IsVisualManagerStyle ())
	//		{
	//			if (!CBCGPVisualManager::GetInstance ()->OnFillDialog (pDC, this, rectClient))
	//			{
	//				CDialog::OnEraseBkgnd (pDC);
	//			}
	//		}
	//		else
	//		{
	//			CDialog::OnEraseBkgnd (pDC);
	//		}
	//	}
  //
	//	if (m_hBkgrBitmap != NULL)
	//	{
	//		ASSERT (m_sizeBkgrBitmap != CSize (0, 0));
  //
	//		if (m_BkgrLocation != BACKGR_TILE)
	//		{
	//			CPoint ptImage = rectClient.TopLeft ();
  //
	//			switch (m_BkgrLocation)
	//			{
	//			case BACKGR_TOPLEFT:
	//				break;
  //
	//			case BACKGR_TOPRIGHT:
	//				ptImage.x = rectClient.right - m_sizeBkgrBitmap.cx;
	//				break;
  //
	//			case BACKGR_BOTTOMLEFT:
	//				ptImage.y = rectClient.bottom - m_sizeBkgrBitmap.cy;
	//				break;
  //
	//			case BACKGR_BOTTOMRIGHT:
	//				ptImage.x = rectClient.right - m_sizeBkgrBitmap.cx;
	//				ptImage.y = rectClient.bottom - m_sizeBkgrBitmap.cy;
	//				break;
	//			}
  //
	//			pDC->DrawState (ptImage, m_sizeBkgrBitmap, m_hBkgrBitmap, DSS_NORMAL);
	//		}
	//		else
	//		{
	//			// Tile background image:
	//			for (int x = rectClient.left; x < rectClient.Width (); x += m_sizeBkgrBitmap.cx)
	//			{
	//				for (int y = rectClient.top; y < rectClient.Height (); y += m_sizeBkgrBitmap.cy)
	//				{
	//					pDC->DrawState (CPoint (x, y), m_sizeBkgrBitmap, m_hBkgrBitmap, DSS_NORMAL);
	//				}
	//			}
	//		}
	//	}
	//}

	pImpl->DrawResizeBox(pDC);
	pImpl->ClearAeroAreas (pDC);

	return bRes;
}
//**********************************************************************************
void MDialog::OnDestroy() 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (m_bAutoDestroyBmp && m_hBkgrBitmap != NULL)
	{
		::DeleteObject (m_hBkgrBitmap);
		m_hBkgrBitmap = NULL;
	}

	pImpl->OnDestroy ();

	CDialog::OnDestroy();
}
//***************************************************************************************
HBRUSH MDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (m_brBkgr.GetSafeHandle () != NULL || m_hBkgrBitmap != NULL ||
		IsVisualManagerStyle ())
	{
		HBRUSH hbr = pImpl->OnCtlColor (pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
//**************************************************************************************
BOOL MDialog::PreTranslateMessage(MSG* pMsg) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (pImpl->PreTranslateMessage (pMsg))
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//*************************************************************************************
BOOL MDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (pImpl->OnCommand (wParam, lParam))
	{
		return TRUE;
	}

	return CDialog::OnCommand(wParam, lParam);
}

//*************************************************************************************
void MDialog::OnSysColorChange() 
{
	CDialog::OnSysColorChange();
	
	if (AfxGetMainWnd () == this)
	{
		globalData.UpdateSysColors ();
	}
}
//*************************************************************************************
void MDialog::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CDialog::OnSettingChange(uFlags, lpszSection);
	
	if (AfxGetMainWnd () == this)
	{
		globalData.OnSettingChange ();
	}
}
//*************************************************************************************
void MDialog::EnableVisualManagerStyle (BOOL bEnable, BOOL bNCArea, const CList<UINT,UINT>* plstNonSubclassedItems)
{
	M_CAST_DLG_IMPL( m_pImpl );

	ASSERT_VALID (this);

	pImpl->EnableVisualManagerStyle (bEnable, bEnable && bNCArea, plstNonSubclassedItems);

	if (bEnable && bNCArea)
	{
		pImpl->OnChangeVisualManager ();
	}
}
//*************************************************************************************
BOOL MDialog::OnInitDialog() 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (AfxGetMainWnd() == this)
	{
		globalData.m_bIsRTL = (GetExStyle() & WS_EX_LAYOUTRTL);
		CBCGPToolBarImages::EnableRTL(globalData.m_bIsRTL);
	}

	CDialog::OnInitDialog();
	
	DWORD dwStyle = GetStyle();

	pImpl->m_bHasBorder = (dwStyle & WS_BORDER) != 0;
	pImpl->m_bHasCaption = (dwStyle & WS_CHILD) == 0 && (dwStyle & WS_CAPTION) != 0;

	if (IsVisualManagerStyle ())
	{
		pImpl->EnableVisualManagerStyle (TRUE, IsVisualManagerNCArea (), &m_lstNonSubclassedItems);
	}

	if (pImpl->HasAeroMargins ())
	{
		pImpl->EnableAero (pImpl->m_AeroMargins);
	}

	if (IsBackstageMode())
	{
		pImpl->EnableBackstageMode();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//*************************************************************************************
BOOL MDialog::EnableAero (int cxLeftWidth, int cxRightWidth, int cyTopHeight, int cyBottomHeight)
{
	M_CAST_DLG_IMPL( m_pImpl );

	BCGPMARGINS margins;
	margins.cxLeftWidth = cxLeftWidth;
	margins.cxRightWidth = cxRightWidth;
	margins.cyTopHeight  = cyTopHeight;
	margins.cyBottomHeight = cyBottomHeight;

	return pImpl->EnableAero (margins);
}
//*************************************************************************************
void MDialog::GetAeroMargins (int& cxLeftWidth, int& cxRightWidth, int& cyTopHeight, int& cyBottomHeight) const
{
	M_CAST_DLG_IMPL( m_pImpl );

	BCGPMARGINS margins;
	pImpl->GetAeroMargins (margins);

	cxLeftWidth = margins.cxLeftWidth;
	cxRightWidth = margins.cxRightWidth;
	cyTopHeight  = margins.cyTopHeight;
	cyBottomHeight = margins.cyBottomHeight;
}

BOOL MDialog::HasAeroMargins () const
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->HasAeroMargins ();
}

//***************************************************************************
LRESULT MDialog::OnDWMCompositionChanged(WPARAM,LPARAM)
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnDWMCompositionChanged ();
	return 0;
}
//***************************************************************************
void MDialog::OnSize(UINT nType, int cx, int cy) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	BOOL bIsMinimized = (nType == SIZE_MINIMIZED);

	if (pImpl->IsOwnerDrawCaption ())
	{
		CRect rectWindow;
		GetWindowRect (rectWindow);

		WINDOWPOS wndpos;
		wndpos.flags = SWP_FRAMECHANGED;
		wndpos.x     = rectWindow.left;
		wndpos.y     = rectWindow.top;
		wndpos.cx    = rectWindow.Width ();
		wndpos.cy    = rectWindow.Height ();

		pImpl->OnWindowPosChanged (&wndpos);
	}

	pImpl->UpdateCaption ();

	if (!bIsMinimized && nType != SIZE_MAXIMIZED && !m_bWasMaximized)
	{
		AdjustControlsLayout();
		return;
	}

	CDialog::OnSize(nType, cx, cy);

	m_bWasMaximized = (nType == SIZE_MAXIMIZED);

	AdjustControlsLayout();
}
//**************************************************************************
void MDialog::OnNcPaint() 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (!pImpl->OnNcPaint ())
	{
		Default ();
	}
}
//**************************************************************************
void MDialog::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnNcMouseMove (nHitTest, point);
	CDialog::OnNcMouseMove(nHitTest, point);
}
//**************************************************************************
void MDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnLButtonUp (point);
	CDialog::OnLButtonUp(nFlags, point);
}
//**************************************************************************
void MDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnLButtonDown (point);
	CDialog::OnLButtonDown(nFlags, point);
}
//**************************************************************************
LRESULT MDialog::OnNcHitTest(CPoint point) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	LRESULT nHit = pImpl->OnNcHitTest (point);
	if (nHit != HTNOWHERE)
	{
		return nHit;
	}

	return CDialog::OnNcHitTest(point);
}
//**************************************************************************
void MDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (!pImpl->OnNcCalcSize (bCalcValidRects, lpncsp))
	{
		CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}
//**************************************************************************
void MDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnMouseMove (point);
	CDialog::OnMouseMove(nFlags, point);
}
//**************************************************************************
void MDialog::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED)
	{
		pImpl->OnWindowPosChanged (lpwndpos);
	}

	CDialog::OnWindowPosChanged(lpwndpos);
}
//**************************************************************************
LRESULT MDialog::OnChangeVisualManager (WPARAM, LPARAM)
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnChangeVisualManager ();
	return 0;
}
//**************************************************************************
void MDialog::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->OnGetMinMaxInfo (lpMMI);
	CDialog::OnGetMinMaxInfo(lpMMI);
}
//****************************************************************************
LRESULT MDialog::OnSetText(WPARAM, LPARAM) 
{
	LRESULT	lRes = Default();

	if (lRes && IsVisualManagerStyle () && IsVisualManagerNCArea ())
	{
		RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	return lRes;
}
//****************************************************************************
int MDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	M_CAST_DLG_IMPL( m_pImpl );

	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	DWORD dwStyle = (DWORD)lpCreateStruct->style;

	pImpl->m_bHasBorder = (dwStyle & WS_BORDER) != 0;
	pImpl->m_bHasCaption = (dwStyle & WS_CHILD) == 0 && (dwStyle & WS_CAPTION) != 0;

    return pImpl->OnCreate();
}
//****************************************************************************
void MDialog::EnableLayout(BOOL bEnable, CRuntimeClass* pRTC, BOOL bResizeBox)
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->EnableLayout(bEnable, pRTC, bResizeBox);
}

BOOL MDialog::IsLayoutEnabled() const
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->IsLayoutEnabled();
}

void MDialog::AdjustControlsLayout()
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->AdjustControlsLayout();
}

void MDialog::UpdateCaptionButtons ()
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->UpdateCaptionButtons();
}

void MDialog::EnableLoadWindowPlacement(BOOL bEnable)
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->m_bLoadWindowPlacement = bEnable;
}

BOOL MDialog::IsWindowPlacementEnabled() const
{
	M_CAST_DLG_IMPL( m_pImpl );

	return pImpl->m_bLoadWindowPlacement;
}

//****************************************************************************
void MDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	M_CAST_DLG_IMPL( m_pImpl );

	pImpl->LoadPlacement();
	CDialog::OnShowWindow(bShow, nStatus);
}

LRESULT MDialog::OnPowerBroadcast(WPARAM wp, LPARAM)
{
	LRESULT lres = Default ();

	if (wp == PBT_APMRESUMESUSPEND && AfxGetMainWnd()->GetSafeHwnd() == GetSafeHwnd())
	{
		globalData.Resume ();
#ifdef _BCGSUITE_
		bcgpGestureManager.Resume();
#endif
	}

	return lres;
}