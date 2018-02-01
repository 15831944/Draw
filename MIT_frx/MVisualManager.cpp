#include "stdafx.h"
#include "MIT_frx.h"
#include "ExtDllInstanceSwitcher.h"
#include "bcgcbpro.h"
#include "BCGPGlobalUtils.h"
#include "MVisualManager.h"
#include "BCGPToolBar.h"
#include "BCGPDrawManager.h"
#include "BCGPPopupMenuBar.h"
#include "BCGPMenuBar.h"
#include "bcgglobals.h"
#include "BCGPToolbarMenuButton.h"
#include "CustomizeButton.h"
#include "MenuImages.h"
#include "BCGPCaptionBar.h"
#include "BCGPBaseTabWnd.h"
#include "BCGPColorBar.h"
#include "BCGPCalculator.h"
#include "BCGPCalendarBar.h"
#include "BCGPTabWnd.h"
#include "BCGPTasksPane.h"
#include "BCGPStatusBar.h"
#include "BCGPAutoHideButton.h"
#include "BCGPHeaderCtrl.h"
#include "BCGPReBar.h"
#include "BCGPToolBox.h"
#include "BCGPPopupWindow.h"
#include "BCGPCalendarBar.h"
#include "BCGPDropDown.h"
#include "BCGPTagManager.h"
#include "BCGPFrameWnd.h"
#include "BCGPMDIFrameWnd.h"
#include "BCGPDockingControlBar.h"
#include "BCGPOutlookWnd.h"
#include "BCGPGridCtrl.h"
#include "BCGPToolbarComboBoxButton.h"
#include "BCGCBProVer.h"
#include "BCGPGroup.h"
#include "BCGPDialog.h"
#include "BCGPPropertySheet.h"
#include "BCGPMath.h"

#include "BCGPRibbonBar.h"
#include "BCGPRibbonPanel.h"
#include "BCGPRibbonCategory.h"
#include "BCGPRibbonButton.h"
#include "BCGPRibbonQuickAccessToolbar.h"
#include "BCGPRibbonComboBox.h"
#include "BCGPRibbonMainPanel.h"
#include "BCGPRibbonPanelMenu.h"
#include "BCGPRibbonLabel.h"
#include "BCGPRibbonPaletteButton.h"
#include "BCGPRibbonStatusBar.h"
#include "BCGPRibbonStatusBarPane.h"
#include "BCGPRibbonProgressBar.h"
#include "BCGPRibbonHyperlink.h"
#include "BCGPRibbonSlider.h"

#include "BCGPPlannerViewDay.h"
#include "BCGPPlannerViewMonth.h"

#include "BCGPGanttChart.h"

#include "MTable.h"
#include "MLayeredSliderCtrl.h"
#include "MDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int xMargin = 2;
static const int yMargin = 2;

using namespace std;
using namespace mit::frx;

static COLORREF CalculateHourLineColor (COLORREF clrBase, BOOL bWorkingHours, BOOL bHour)
{
	double H, S, V;
	CBCGPDrawManager::RGBtoHSV (clrBase, &H, &S, &V);

	if (bHour)
	{
		S = S * 0.77;
		V = min (V * 1.03, 1.0);
	}
	else
	{
		if (bWorkingHours)
		{
			S = S * 0.2;
			V = min (V * 1.14, 1.0);
		}
		else
		{
			S = S * 0.34;
			V = min (V * 1.12, 1.0);
		}
	}

	return CBCGPDrawManager::HSVtoRGB (H, S, V);
}

static COLORREF CalculateWorkingColor (COLORREF /*clrBase*/)
{
	return RGB (255, 255, 255);
}

static COLORREF CalculateNonWorkingColor (COLORREF clrBase, BOOL bLight)
{
	if (bLight)
	{
		return CalculateHourLineColor (clrBase, TRUE, FALSE);
	}

	return CalculateHourLineColor (clrBase, FALSE, TRUE);
}

static COLORREF CalculateSelectionColor (COLORREF clrBase)
{
	double H, S, V;
	CBCGPDrawManager::RGBtoHSV (clrBase, &H, &S, &V);

	return CBCGPDrawManager::HSVtoRGB (H, min (S * 1.88, 1.0), V * 0.56);
}

static COLORREF CalculateSeparatorColor (COLORREF clrBase)
{
	double H, S, V;
	CBCGPDrawManager::RGBtoHSV (clrBase, &H, &S, &V);

	return CBCGPDrawManager::HSVtoRGB (H, min (S * 1.6, 1.0), V * 0.85);
}

MBitmapCache::MBitmapCacheItem::MBitmapCacheItem()
{
	m_bMirror = FALSE;
}

MBitmapCache::MBitmapCacheItem::~MBitmapCacheItem()
{
}

void MBitmapCache::MBitmapCacheItem::AddImage (HBITMAP hBmp)
{
	m_Images.AddImage (hBmp, TRUE);
}

void MBitmapCache::MBitmapCacheItem::Cache (const CSize& size, CBCGPControlRenderer& renderer)
{
	m_Images.Clear ();

	const int nCount = renderer.GetImageCount ();

	if (nCount > 0)
	{
		m_Images.SetImageSize (size);
		m_Images.SetTransparentColor ((COLORREF)-1);

		for (int i = 0; i < nCount; i++)
		{
			BITMAPINFO bi;
			memset(&bi, 0, sizeof(BITMAPINFO));

			// Fill in the BITMAPINFOHEADER
			bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
			bi.bmiHeader.biWidth       = size.cx;
			bi.bmiHeader.biHeight      = size.cy;
			bi.bmiHeader.biPlanes      = 1;
			bi.bmiHeader.biBitCount    = 32;
			bi.bmiHeader.biCompression = BI_RGB;
			bi.bmiHeader.biSizeImage   = size.cy * size.cx * 4;

			LPBYTE pBits = NULL;
			HBITMAP hDib = ::CreateDIBSection (
				NULL, &bi, DIB_RGB_COLORS, (void **)&pBits,
				NULL, NULL);

			if (hDib == NULL || pBits == NULL)
			{
				ASSERT (FALSE);
				break;
			}

			CDC dc;
			dc.CreateCompatibleDC (NULL);

			HBITMAP hOldDib = (HBITMAP)::SelectObject (dc.GetSafeHdc (), hDib);

			m_bMirror = renderer.IsMirror ();
			if (m_bMirror)
			{
				renderer.Mirror ();
			}

			renderer.Draw (&dc, CRect (0, 0, size.cx, size.cy), i);

			if (m_bMirror)
			{
				renderer.Mirror ();
			}

			::SelectObject (dc.GetSafeHdc (), hOldDib);

			AddImage (hDib);
			
			::DeleteObject (hDib);
		}
	}
}

void MBitmapCache::MBitmapCacheItem::Draw (CDC* pDC, CRect rect, int iImageIndex/* = 0*/,
										   BYTE alphaSrc/* = 255*/)
{
	m_Images.DrawEx (pDC, CRect (rect.TopLeft (), m_Images.GetImageSize ()), 
		iImageIndex, CBCGPToolBarImages::ImageAlignHorzLeft, 
		CBCGPToolBarImages::ImageAlignVertTop, CRect (0, 0, 0, 0), alphaSrc);
}

void MBitmapCache::MBitmapCacheItem::DrawY (CDC* pDC, CRect rect, CSize sides, 
											int iImageIndex/* = 0*/, BYTE alphaSrc/* = 255*/)
{
	CRect rectImage (CPoint (0, 0), m_Images.GetImageSize ());

	ASSERT (rect.Height () == rectImage.Height ());

	if (sides.cx > 0)
	{
		CRect rt (rectImage);
		if (m_bMirror)
		{
			rt.left = rectImage.right - sides.cx;
			rectImage.right = rt.left;
		}
		else
		{
			rt.right = rt.left + sides.cx;
			rectImage.left = rt.right;
		}

		m_Images.DrawEx (pDC, rect, iImageIndex, CBCGPToolBarImages::ImageAlignHorzLeft,
			CBCGPToolBarImages::ImageAlignVertTop, rt, alphaSrc);
	}

	if (sides.cy > 0)
	{
		CRect rt (rectImage);
		if (m_bMirror)
		{
			rt.right = rectImage.left + sides.cy;
			rectImage.left = rt.right;
		}
		else
		{
			rt.left = rectImage.right - sides.cy;
			rectImage.right = rt.left;
		}

		m_Images.DrawEx (pDC, rect, iImageIndex, CBCGPToolBarImages::ImageAlignHorzRight,
			CBCGPToolBarImages::ImageAlignVertTop, rt, alphaSrc);
	}

	if (rectImage.Width () > 0)
	{
		rect.DeflateRect (sides.cx, 0, sides.cy, 0);
		m_Images.DrawEx (pDC, rect, iImageIndex, CBCGPToolBarImages::ImageAlignHorzStretch,
			CBCGPToolBarImages::ImageAlignVertTop, rectImage, alphaSrc);
	}
}

MBitmapCache::MBitmapCache()
{
}

MBitmapCache::~MBitmapCache()
{
	Clear ();
}

void MBitmapCache::Clear ()
{
	for (int i = 0; i < m_Cache.GetSize (); i++)
	{
		if (m_Cache[i] != NULL)
		{
			delete m_Cache[i];
		}
	}

	m_Cache.RemoveAll ();
	m_Sizes.RemoveAll ();
}

int MBitmapCache::Cache (const CSize& size, CBCGPControlRenderer& renderer)
{
	if (FindIndex (size) != -1)
	{
		ASSERT (FALSE);
		return -1;
	}

	MBitmapCacheItem* pItem = new MBitmapCacheItem;
	pItem->Cache (size, renderer);

	int nCache = (int) m_Cache.Add (pItem);

#ifdef _DEBUG
	int nSize = (int) m_Sizes.Add (size);
	ASSERT (nCache == nSize);
#else
	m_Sizes.Add (size);
#endif

	return nCache;
}

int MBitmapCache::CacheY (int height, CBCGPControlRenderer& renderer)
{
	CSize size (renderer.GetParams ().m_rectImage.Width (), height);

	return Cache (size, renderer);
}

BOOL MBitmapCache::IsCached (const CSize& size) const
{
	return FindIndex (size) != -1;
}

int MBitmapCache::FindIndex (const CSize& size) const
{
	int nRes = -1;
	for (int i = 0; i < m_Sizes.GetSize (); i++)
	{
		if (size == m_Sizes[i])
		{
			nRes = i;
			break;
		}
	}

	return nRes;
}

MBitmapCache::MBitmapCacheItem* MBitmapCache::Get (const CSize& size)
{
	int nIndex = FindIndex (size);

	if (nIndex != -1)
	{
		return m_Cache[nIndex];
	}

	return NULL;
}

MBitmapCache::MBitmapCacheItem* MBitmapCache::Get (int nIndex)
{
	if (0 <= nIndex && nIndex < m_Cache.GetSize ())
	{
		return m_Cache[nIndex];
	}

	return NULL;
}


IMPLEMENT_DYNCREATE(MVisualManager, CBCGPVisualManager2007)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MVisualManager::MVisualManager()
{
	m_szNcBtnSize[0]    = CSize (0, 0);
	m_szNcBtnSize[1]    = CSize (0, 0);

	m_ptRibbonMainImageOffset = CPoint (0, -1);

	m_clrEditBorder                = (COLORREF)(-1);
	m_clrEditBorderDisabled        = (COLORREF)(-1);
	m_clrEditBorderHighlighted     = (COLORREF)(-1);
	m_clrEditSelection             = (COLORREF)(-1);
	m_clrComboBorder               = (COLORREF)(-1);
	m_clrComboBorderDisabled       = (COLORREF)(-1);
    m_clrComboBorderPressed        = (COLORREF)(-1);
	m_clrComboBorderHighlighted    = (COLORREF)(-1);
	m_clrComboBtnStart             = (COLORREF)(-1);
	m_clrComboBtnFinish            = (COLORREF)(-1);
	m_clrComboBtnBorder            = (COLORREF)(-1);
	m_clrComboBtnDisabledStart     = (COLORREF)(-1);
	m_clrComboBtnDisabledFinish    = (COLORREF)(-1);
	m_clrComboBtnBorderDisabled    = (COLORREF)(-1);
	m_clrComboBtnPressedStart      = (COLORREF)(-1);
	m_clrComboBtnPressedFinish     = (COLORREF)(-1);
	m_clrComboBtnBorderPressed     = (COLORREF)(-1);
	m_clrComboBtnHighlightedStart  = (COLORREF)(-1);
	m_clrComboBtnHighlightedFinish = (COLORREF)(-1);
	m_clrComboBtnBorderHighlighted = (COLORREF)(-1);
	m_clrComboSelection            = (COLORREF)(-1);

	m_clrGroupText = (COLORREF)-1;

	m_clrHeaderNormalText      = (COLORREF)-1;
	m_clrHeaderHighlightedText = (COLORREF)-1;
	m_clrHeaderPressedText     = (COLORREF)-1;

	m_clrTabTextActive = (COLORREF)-1;
	m_clrTabTextInactive = (COLORREF)-1;
	m_clrTabTextHighlighted = (COLORREF)-1;
	m_clrTab3DTextActive = (COLORREF)-1;
	m_clrTab3DTextInactive = (COLORREF)-1;
	m_clrTab3DTextHighlighted = (COLORREF)-1;
	m_clrTabFlatTextActive = (COLORREF)-1;
	m_clrTabFlatTextInactive = (COLORREF)-1;
	m_clrTabFlatTextHighlighted = (COLORREF)-1;
	m_clrTab3DFace = CLR_DEFAULT;
	m_clrTab3DBlack = CLR_DEFAULT;
	m_clrTab3DDark = CLR_DEFAULT;
	m_clrTab3DDarkShadow = CLR_DEFAULT;
	m_clrTab3DLight = CLR_DEFAULT;
	m_clrTab3DHighlight = CLR_DEFAULT;
	m_clrTabFlatFace = CLR_DEFAULT;
	m_clrTabFlatBlack = CLR_DEFAULT;
	m_clrTabFlatDark = CLR_DEFAULT;
	m_clrTabFlatDarkShadow = CLR_DEFAULT;
	m_clrTabFlatLight = CLR_DEFAULT;
	m_clrTabFlatHighlight = CLR_DEFAULT;

	m_clrRibbonMainPanelBkgnd = CLR_DEFAULT;

	m_clrRibbonKeyTipTextNormal   = (COLORREF)(-1);
	m_clrRibbonKeyTipTextDisabled = (COLORREF)(-1);

	m_clrRibbonCategoryTextActive = (COLORREF)-1;

	m_clrRibbonHyperlinkInactive = (COLORREF)-1;
	m_clrRibbonHyperlinkActive = (COLORREF)-1;
	m_clrRibbonStatusbarHyperlinkInactive = (COLORREF)-1;
	m_clrRibbonStatusbarHyperlinkActive = (COLORREF)-1;

	m_clrDlgBackground  = (COLORREF)-1;
	m_clrDlgButtonsArea = (COLORREF)-1;

	m_clrAppCaptionActiveStart = (COLORREF)-1;
	m_clrAppCaptionActiveFinish = (COLORREF)-1;

	m_pTabButton = NULL;
	m_uiTabButtonID = -1;
	m_bRedrawMDITabButton = FALSE;
	m_svEnableTabButtonViews.clear();
}
//*****************************************************************************
MVisualManager::~MVisualManager()
{
	Style style = m_Style;
	CleanStyle ();
	m_Style = style;

	CBCGPMenuImages::SetColor (CBCGPMenuImages::ImageBlack, (COLORREF)-1);

	m_pTabButton = NULL;
}

void MVisualManager::CleanUp ()
{
	m_cacheRibbonBtnGroup_S.Clear ();
	m_cacheRibbonBtnGroup_F.Clear ();
	m_cacheRibbonBtnGroup_M.Clear ();
	m_cacheRibbonBtnGroup_L.Clear ();
	m_cacheRibbonBtnGroupMenu_F[0].Clear ();
	m_cacheRibbonBtnGroupMenu_M[0].Clear ();
	m_cacheRibbonBtnGroupMenu_L[0].Clear ();
	m_cacheRibbonBtnGroupMenu_F[1].Clear ();
	m_cacheRibbonBtnGroupMenu_M[1].Clear ();
	m_cacheRibbonBtnGroupMenu_L[1].Clear ();
}

BOOL MVisualManager::ParseStyleXMLVersion(const CString& strItem)
{
	if (strItem.IsEmpty ())
	{
		return FALSE;
	}

	BOOL bLoaded = FALSE;
	int nVersion = 0;

	CBCGPTagManager tmItem (strItem);

	tmItem.ReadInt (_T("NUMBER"), nVersion);

	if (nVersion == 2014)
	{
		tmItem.ReadInt (_T("TYPE"), m_nType);

		if (m_nType < 10)
		{
			m_nType *= 20;
		}

		bLoaded = TRUE;
	}

	if (bLoaded)
	{
		CString strPrefix;
		if (tmItem.ExcludeTag (_T("ID_PREFIX"), strPrefix))
		{
			strPrefix.TrimLeft ();
			strPrefix.TrimRight ();
			m_strStylePrefix = strPrefix;
		}
	}

	return bLoaded;
}
//*****************************************************************************
BOOL MVisualManager::ParseStyleXMLRibbon(const CString& strItem)
{
	if (strItem.IsEmpty ())
	{
		return FALSE;
	}

	CBCGPTagManager tmItem (strItem);

	CString str;

	if (tmItem.ExcludeTag (_T("CATEGORY"), str))
	{
		CBCGPTagManager tmCategory (str);
		tmCategory.ReadControlRenderer(_T("BACK"), m_ctrlRibbonCategoryBack, MakeResourceID(_T("RB_CAT_BACK")));

		CString strTab;
		if (tmCategory.ExcludeTag (_T("TAB"), strTab))
		{
			CBCGPTagManager tmTab (strTab);
			tmTab.ReadControlRenderer(_T("BUTTON"), m_ctrlRibbonCategoryTab, MakeResourceID(_T("RB_CAT_TAB")));

			tmTab.ReadColor (_T("TextNormal"), m_clrRibbonCategoryText);
			tmTab.ReadColor (_T("TextHighlighted"), m_clrRibbonCategoryTextHighlighted);
			tmTab.ReadColor (_T("TextActive"), m_clrRibbonCategoryTextActive);
			tmTab.ReadColor (_T("TextDisabled"), m_clrRibbonCategoryTextDisabled);
		}

		tmCategory.ReadControlRenderer (_T("TAB_SEPARATOR"), m_ctrlRibbonCategoryTabSep, MakeResourceID(_T("RB_CAT_TAB_SEP")));

		tmCategory.ReadControlRenderer (_T("BUTTON_PAGE_L"), m_ctrlRibbonCategoryBtnPage[0], MakeResourceID(_T("RB_BTN_PAGE_L")));
		tmCategory.ReadControlRenderer (_T("BUTTON_PAGE_R"), m_ctrlRibbonCategoryBtnPage[1], MakeResourceID(_T("RB_BTN_PAGE_R")));
	}

	if (tmItem.ExcludeTag (_T("PANEL"), str))
	{
		CBCGPTagManager tmPanel (str);

		{
			CString strBack;
			if (tmPanel.ExcludeTag (_T("BACK"), strBack))
			{
				CBCGPTagManager tmBack (strBack);

				tmBack.ReadControlRenderer(_T("TOP"), m_ctrlRibbonPanelBack_T, MakeResourceID(_T("RB_PNL_BACK_T")));
				tmBack.ReadControlRenderer(_T("BOTTOM"), m_ctrlRibbonPanelBack_B, MakeResourceID(_T("RB_PNL_BACK_B")));
			}
		}

		{
			CString strCaption;
			if (tmPanel.ExcludeTag (_T("CAPTION"), strCaption))
			{
				CBCGPTagManager tmCaption (strCaption);

				tmCaption.ReadControlRenderer (_T("LAUNCH_BTN"), m_ctrlRibbonBtnLaunch, MakeResourceID(_T("RB_BTN_LAUNCH")));
				tmCaption.ReadToolBarImages (_T("LAUNCH_ICON"), m_RibbonBtnLaunchIcon, MakeResourceID(_T("RB_BTN_LAUNCH_ICON")));
				tmCaption.ReadColor (_T("TextNormal"), m_clrRibbonPanelCaptionText);
				tmCaption.ReadColor (_T("TextHighlighted"), m_clrRibbonPanelCaptionTextHighlighted);

				m_RibbonBtnLaunchIcon.SmoothResize (globalData.GetRibbonImageScale ());
			}
		}

		tmPanel.ReadToolBarImages (_T("SEPARATOR"), m_RibbonPanelSeparator, MakeResourceID(_T("RB_PNL_SEPARATOR")));

		tmPanel.ReadControlRenderer (_T("QAT"), m_ctrlRibbonPanelQAT, MakeResourceID(_T("RB_PNL_QAT")));

		{
			CString strButtons;
			if (tmPanel.ExcludeTag (_T("BUTTONS"), strButtons))
			{
				CBCGPTagManager tmButtons (strButtons);

				tmButtons.ReadControlRenderer (_T("BUTTON_GROUP_F"), m_ctrlRibbonBtnGroup_F, MakeResourceID(_T("RB_BTN_GRP_F")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUP_M"), m_ctrlRibbonBtnGroup_M, MakeResourceID(_T("RB_BTN_GRP_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUP_L"), m_ctrlRibbonBtnGroup_L, MakeResourceID(_T("RB_BTN_GRP_L")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUP_S"), m_ctrlRibbonBtnGroup_S, MakeResourceID(_T("RB_BTN_GRP_S")));

				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_F_C"), m_ctrlRibbonBtnGroupMenu_F[0], MakeResourceID(_T("RB_BTN_GRPMENU_F_C")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_F_M"), m_ctrlRibbonBtnGroupMenu_F[1], MakeResourceID(_T("RB_BTN_GRPMENU_F_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_M_C"), m_ctrlRibbonBtnGroupMenu_M[0], MakeResourceID(_T("RB_BTN_GRPMENU_M_C")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_M_M"), m_ctrlRibbonBtnGroupMenu_M[1], MakeResourceID(_T("RB_BTN_GRPMENU_M_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_L_C"), m_ctrlRibbonBtnGroupMenu_L[0], MakeResourceID(_T("RB_BTN_GRPMENU_L_C")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUPMENU_L_M"), m_ctrlRibbonBtnGroupMenu_L[1], MakeResourceID(_T("RB_BTN_GRPMENU_L_M")));

				tmButtons.ReadControlRenderer (_T("BUTTON_NORMAL_S"), m_ctrlRibbonBtn[0], MakeResourceID(_T("RB_BTN_NORMAL_S")));
				tmButtons.ReadControlRenderer (_T("BUTTON_NORMAL_B"), m_ctrlRibbonBtn[1], MakeResourceID(_T("RB_BTN_NORMAL_B")));

				tmButtons.ReadControlRenderer (_T("BUTTON_DEFAULT"), m_ctrlRibbonBtnDefault, MakeResourceID(_T("RB_BTN_DEF")));
				tmButtons.ReadControlRenderer (_T("BUTTON_DEFAULT_ICON"), m_ctrlRibbonBtnDefaultIcon, MakeResourceID(_T("RB_BTN_DEF_ICON")));
				tmButtons.ReadToolBarImages (_T("BUTTON_DEFAULT_IMAGE"), m_RibbonBtnDefaultImage, MakeResourceID(_T("RB_BTN_DEF_IMAGE")));
				tmButtons.ReadControlRenderer (_T("BUTTON_DEFAULT_QAT"), m_ctrlRibbonBtnDefaultQAT, MakeResourceID(_T("RB_BTN_DEF_QAT")));

				if (!m_ctrlRibbonBtnDefaultQAT.IsValid ())
				{
					tmButtons.ReadControlRenderer (_T("BUTTON_DEFAULT_QAT_ICON"), m_ctrlRibbonBtnDefaultQATIcon, MakeResourceID(_T("RB_BTN_DEF_QAT_ICON")));
				}

				tmButtons.ReadControlRenderer (_T("BUTTON_MENU_H_C"), m_ctrlRibbonBtnMenuH[0], MakeResourceID(_T("RB_BTN_MENU_H_C")));
				tmButtons.ReadControlRenderer (_T("BUTTON_MENU_H_M"), m_ctrlRibbonBtnMenuH[1], MakeResourceID(_T("RB_BTN_MENU_H_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_MENU_V_C"), m_ctrlRibbonBtnMenuV[0], MakeResourceID(_T("RB_BTN_MENU_V_C")));
				tmButtons.ReadControlRenderer (_T("BUTTON_MENU_V_M"), m_ctrlRibbonBtnMenuV[1], MakeResourceID(_T("RB_BTN_MENU_V_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_CHECK"), m_ctrlRibbonBtnCheck, MakeResourceID(_T("RB_BTN_CHECK")));
				tmButtons.ReadControlRenderer (_T("BUTTON_RADIO"), m_ctrlRibbonBtnRadio, MakeResourceID(_T("RB_BTN_RADIO")));
				tmButtons.ReadControlRenderer (_T("BUTTON_PUSH"), m_ctrlRibbonBtnPush, MakeResourceID(_T("RB_BTN_PUSH")));
				tmButtons.ReadControlRenderer (_T("BUTTON_GROUP"), m_ctrlRibbonBtnGroup, MakeResourceID(_T("RB_BTN_GRP")));

				m_ctrlRibbonBtnCheck.SmoothResize (globalData.GetRibbonImageScale ());
				m_ctrlRibbonBtnRadio.SmoothResize (globalData.GetRibbonImageScale ());

				tmButtons.ReadControlRenderer (_T("BUTTON_PNL_T"), m_ctrlRibbonBtnPalette[0], MakeResourceID(_T("RB_BTN_PALETTE_T")));
				tmButtons.ReadControlRenderer (_T("BUTTON_PNL_M"), m_ctrlRibbonBtnPalette[1], MakeResourceID(_T("RB_BTN_PALETTE_M")));
				tmButtons.ReadControlRenderer (_T("BUTTON_PNL_B"), m_ctrlRibbonBtnPalette[2], MakeResourceID(_T("RB_BTN_PALETTE_B")));

				tmButtons.ReadColor (_T("TextNormal"), m_clrRibbonBarBtnText);
				tmButtons.ReadColor (_T("TextHighlighted"), m_clrRibbonBarBtnTextHighlighted);
				tmButtons.ReadColor (_T("TextDisabled"), m_clrRibbonBarBtnTextDisabled);
			}
		}

		{
			CString strEdit;
			if (tmPanel.ExcludeTag (_T("EDIT"), strEdit))
			{
				CBCGPTagManager tmEdit (strEdit);

				tmEdit.ReadColor (_T("Normal"), m_clrRibbonEdit);
				tmEdit.ReadColor (_T("Highlighted"), m_clrRibbonEditHighlighted);
				tmEdit.ReadColor (_T("Disabled"), m_clrRibbonEditDisabled);
				tmEdit.ReadColor (_T("Pressed"), m_clrRibbonEditPressed);

				tmEdit.ReadColor (_T("BorderNormal"), m_clrRibbonEditBorder);
				tmEdit.ReadColor (_T("BorderHighlighted"), m_clrRibbonEditBorderHighlighted);
				tmEdit.ReadColor (_T("BorderDisabled"), m_clrRibbonEditBorderDisabled);
				tmEdit.ReadColor (_T("BorderPressed"), m_clrRibbonEditBorderPressed);
				tmEdit.ReadColor (_T("Selection"), m_clrRibbonEditSelection);

				CString strButton;
				if (tmEdit.ExcludeTag (_T("BUTTON"), strButton))
				{
					CBCGPTagManager tmButton (strButton);

					tmButton.ReadColor (_T("GradientStartNormal"), m_clrRibbonComboBtnStart);
					tmButton.ReadColor (_T("GradientFinishNormal"), m_clrRibbonComboBtnFinish);
					tmButton.ReadColor (_T("BtnBorderNormal"), m_clrRibbonComboBtnBorder);

					if (!tmButton.ReadControlRenderer (_T("IMAGE"), m_ctrlRibbonComboBoxBtn, MakeResourceID(_T("COMBOBOX_BTN"))))
					{
						tmButton.ReadColor (_T("GradientStartHighlighted"), m_clrRibbonComboBtnHighlightedStart);
						tmButton.ReadColor (_T("GradientFinishHighlighted"), m_clrRibbonComboBtnHighlightedFinish);
						tmButton.ReadColor (_T("GradientStartDisabled"), m_clrRibbonComboBtnDisabledStart);
						tmButton.ReadColor (_T("GradientFinishDisabled"), m_clrRibbonComboBtnDisabledFinish);
						tmButton.ReadColor (_T("GradientStartPressed"), m_clrRibbonComboBtnPressedStart);
						tmButton.ReadColor (_T("GradientFinishPressed"), m_clrRibbonComboBtnPressedFinish);

						tmButton.ReadColor (_T("BtnBorderHighlighted"), m_clrRibbonComboBtnBorderHighlighted);
						tmButton.ReadColor (_T("BtnBorderDisabled"), m_clrRibbonComboBtnBorderDisabled);

						m_clrRibbonComboBtnBorderPressed = m_clrRibbonComboBtnBorderHighlighted;
						tmButton.ReadColor (_T("BtnBorderPressed"), m_clrRibbonComboBtnBorderPressed);
					}
				}
			}
		}

		tmPanel.ReadColor (_T("TextNormal"), m_clrRibbonPanelText);
		tmPanel.ReadColor (_T("TextHighlighted"), m_clrRibbonPanelTextHighlighted);
	}

	m_clrRibbonContextPanelText = m_clrRibbonPanelText;
	m_clrRibbonContextPanelTextHighlighted = m_clrRibbonPanelTextHighlighted;
	m_clrRibbonContextPanelCaptionText = m_clrRibbonPanelCaptionText;
	m_clrRibbonContextPanelCaptionTextHighlighted = m_clrRibbonPanelCaptionTextHighlighted;

	if (tmItem.ExcludeTag (_T("CONTEXT"), str))
	{
		CBCGPTagManager tmContext (str);

		CString strCategory;
		if (tmContext.ExcludeTag (_T("CATEGORY"), strCategory))
		{
			CBCGPTagManager tmCategory (strCategory);

			CBCGPControlRendererParams prBack;
			CBCGPControlRendererParams prCaption;
			CBCGPControlRendererParams prTab;
			CBCGPControlRendererParams prDefault;
			COLORREF clrText = m_clrRibbonCategoryText;
			COLORREF clrTextHighlighted = m_clrRibbonCategoryTextHighlighted;
			COLORREF clrTextActive = m_clrRibbonCategoryTextActive;
			COLORREF clrCaptionText = clrText;

			tmCategory.ReadControlRendererParams (_T("BACK"), prBack);

			CString strTab;
			if (tmCategory.ExcludeTag (_T("TAB"), strTab))
			{
				CBCGPTagManager tmTab (strTab);

				tmTab.ReadControlRendererParams(_T("BUTTON"), prTab);
				tmTab.ReadColor (_T("TextNormal"), clrText);
				tmTab.ReadColor (_T("TextHighlighted"), clrTextHighlighted);
				tmTab.ReadColor (_T("TextActive"), clrTextActive);
			}

			CString strCaption;
			if (tmCategory.ExcludeTag (_T("CAPTION"), strCaption))
			{
				CBCGPTagManager tmCaption (strCaption);

				tmCaption.ReadControlRendererParams(_T("BACK"), prCaption);
				tmCaption.ReadColor (_T("TextNormal"), clrCaptionText);
			}

			tmCategory.ReadControlRendererParams(_T("BUTTON_DEFAULT"), prDefault);

			CString strID[BCGPRibbonCategoryColorCount] = 
			{
				MakeResourceID(_T("RB_CTX_R_")),
				MakeResourceID(_T("RB_CTX_O_")),
				MakeResourceID(_T("RB_CTX_Y_")),
				MakeResourceID(_T("RB_CTX_G_")),
				MakeResourceID(_T("RB_CTX_B_")),
				MakeResourceID(_T("RB_CTX_I_")),
				MakeResourceID(_T("RB_CTX_V_"))
			};

			for (int i = 0; i < BCGPRibbonCategoryColorCount; i++)
			{
				XRibbonContextCategory& cat = m_ctrlRibbonContextCategory[i];

				prDefault.m_strBmpResID = strID[i] + _T("BTN_DEF");
				prTab.m_strBmpResID     = strID[i] + _T("CAT_TAB");
				prCaption.m_strBmpResID = strID[i] + _T("CAT_CAPTION");
				prBack.m_strBmpResID    = strID[i] + _T("CAT_BACK");

				cat.m_ctrlBtnDefault.Create (prDefault);
				cat.m_ctrlCaption.Create (prCaption);
				cat.m_ctrlTab.Create (prTab);
				cat.m_ctrlBack.Create (prBack);
				cat.m_clrText            = clrText;
				cat.m_clrTextHighlighted = clrTextHighlighted;
				cat.m_clrTextActive      = clrTextActive;
				cat.m_clrCaptionText     = clrCaptionText;
			}
		}

		CString strPanel;
		if (tmContext.ExcludeTag (_T("PANEL"), strPanel))
		{
			CBCGPTagManager tmPanel (strPanel);

			CString strBack;
			if (tmPanel.ExcludeTag (_T("BACK"), strBack))
			{
				CBCGPTagManager tmBack (strBack);

				tmBack.ReadControlRenderer(_T("TOP"), m_ctrlRibbonContextPanelBack_T, MakeResourceID(_T("RB_CTX_PNL_BACK_T")));
				tmBack.ReadControlRenderer(_T("BOTTOM"), m_ctrlRibbonContextPanelBack_B, MakeResourceID(_T("RB_CTX_PNL_BACK_B")));
			}

			CString strCaption;
			if (tmPanel.ExcludeTag (_T("CAPTION"), strCaption))
			{
				CBCGPTagManager tmCaption (strCaption);

				tmCaption.ReadColor (_T("TextNormal"), m_clrRibbonContextPanelCaptionText);
				tmCaption.ReadColor (_T("TextHighlighted"), m_clrRibbonContextPanelCaptionTextHighlighted);
			}

			tmPanel.ReadColor (_T("TextNormal"), m_clrRibbonContextPanelText);
			tmPanel.ReadColor (_T("TextHighlighted"), m_clrRibbonContextPanelTextHighlighted);
		}

		tmContext.ReadControlRenderer (_T("SEPARATOR"), m_ctrlRibbonContextSeparator, MakeResourceID(_T("RB_CTX_SEPARATOR")));
	}

	if (tmItem.ExcludeTag (_T("MAIN_BUTTON"), str))
	{
		CBCGPTagManager tmMainBtn (str);
		tmMainBtn.ReadToolBarImages (_T("ICON"), m_RibbonBtnMainIcon, MakeResourceID(_T("RB_BTN_MAINBTN_ICON")));
		tmMainBtn.ReadControlRenderer (_T("BACK"), m_RibbonBtnMain, MakeResourceID(_T("RB_BTN_MAINBTN_BACK")));
		if (m_RibbonBtnMain.IsValid ())
		{
			m_RibbonBtnMain.SmoothResize (globalData.GetRibbonImageScale ());
		}
	}

	if (tmItem.ExcludeTag (_T("MAIN"), str))
	{
		CBCGPTagManager tmMain (str);
		tmMain.ReadColor (_T("Bkgnd"), m_clrRibbonMainPanelBkgnd);
		tmMain.ReadControlRenderer (_T("BACK"), m_ctrlRibbonMainPanel, MakeResourceID(_T("RB_PNL_MAIN")));
		tmMain.ReadControlRenderer (_T("BORDER"), m_ctrlRibbonMainPanelBorder, MakeResourceID(_T("RB_PNL_MAIN_BRD")));
		tmMain.ReadControlRenderer (_T("BUTTON"), m_ctrlRibbonBtnMainPanel, MakeResourceID(_T("RB_BTN_PNL_MAIN")));
	}

	if (tmItem.ExcludeTag (_T("CAPTION"), str))
	{
		CBCGPTagManager tmCaption (str);
		tmCaption.ReadControlRenderer(_T("QA"), m_ctrlRibbonCaptionQA, MakeResourceID(_T("RB_CAPTION_QA")));
		tmCaption.ReadControlRenderer(_T("QA_GLASS"), m_ctrlRibbonCaptionQA_Glass, MakeResourceID(_T("RB_CAPTION_QA_GLASS")));
	}

	if (tmItem.ExcludeTag (_T("STATUS"), str))
	{
		CBCGPTagManager tmStatus (str);
		tmStatus.ReadControlRenderer(_T("PANE_BUTTON"), m_ctrlRibbonBtnStatusPane, MakeResourceID(_T("RB_BTN_STATUS_PANE")));

		CString strSlider;
		if (tmStatus.ExcludeTag (_T("SLIDER"), strSlider))
		{
			CBCGPTagManager tmSlider (strSlider);

			tmSlider.ReadControlRenderer(_T("THUMB"), m_ctrlRibbonSliderThumb, MakeResourceID(_T("RB_SLIDER_THUMB")));
			tmSlider.ReadControlRenderer(_T("THUMB_H"), m_ctrlRibbonSliderThumbA[0], MakeResourceID(_T("RB_SLIDER_THUMB_H")));
			tmSlider.ReadControlRenderer(_T("THUMB_T"), m_ctrlRibbonSliderThumbA[1], MakeResourceID(_T("RB_SLIDER_THUMB_T")));
			tmSlider.ReadControlRenderer(_T("THUMB_R"), m_ctrlRibbonSliderThumbA[2], MakeResourceID(_T("RB_SLIDER_THUMB_R")));
			tmSlider.ReadControlRenderer(_T("THUMB_V"), m_ctrlRibbonSliderThumbA[3], MakeResourceID(_T("RB_SLIDER_THUMB_V")));
			tmSlider.ReadControlRenderer(_T("THUMB_L"), m_ctrlRibbonSliderThumbA[4], MakeResourceID(_T("RB_SLIDER_THUMB_L")));

			tmSlider.ReadControlRenderer(_T("PLUS"), m_ctrlRibbonSliderBtnPlus, MakeResourceID(_T("RB_SLIDER_BTN_PLUS")));
			tmSlider.ReadControlRenderer(_T("MINUS"), m_ctrlRibbonSliderBtnMinus, MakeResourceID(_T("RB_SLIDER_BTN_MINUS")));

			m_ctrlRibbonSliderThumb.SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderThumbA[0].SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderThumbA[1].SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderThumbA[2].SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderThumbA[3].SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderThumbA[4].SmoothResize (globalData.GetRibbonImageScale ());

			m_ctrlRibbonSliderBtnMinus.SmoothResize (globalData.GetRibbonImageScale ());
			m_ctrlRibbonSliderBtnPlus.SmoothResize (globalData.GetRibbonImageScale ());
		}

		CString strProgress;
		if (tmStatus.ExcludeTag (_T("PROGRESS"), strProgress))
		{
			CBCGPTagManager tmProgress (strProgress);

			tmProgress.ReadControlRenderer(_T("BACK"), m_ctrlRibbonProgressBack, MakeResourceID(_T("RB_PROGRESS_BACK")));
			tmProgress.ReadControlRenderer(_T("NORMAL"), m_ctrlRibbonProgressNormal, MakeResourceID(_T("RB_PROGRESS_NORMAL")));
			tmProgress.ReadControlRenderer(_T("NORMAL_EXT"), m_ctrlRibbonProgressNormalExt, MakeResourceID(_T("RB_PROGRESS_NORMAL_EXT")));
			tmProgress.ReadControlRenderer(_T("INFINITY"), m_ctrlRibbonProgressInfinity, MakeResourceID(_T("RB_PROGRESS_INFINITY")));

			tmProgress.ReadControlRenderer(_T("BACK_V"), m_ctrlRibbonProgressBackV, MakeResourceID(_T("RB_PROGRESS_BACK_V")));
			if (!m_ctrlRibbonProgressBackV.IsValid())
			{
				m_ctrlRibbonProgressBackV.Create(m_ctrlRibbonProgressBack.GetParams());
				m_ctrlRibbonProgressBackV.Rotate(FALSE);
			}
			tmProgress.ReadControlRenderer(_T("NORMAL_V"), m_ctrlRibbonProgressNormalV, MakeResourceID(_T("RB_PROGRESS_NORMAL_V")));
			if (!m_ctrlRibbonProgressNormalV.IsValid())
			{
				m_ctrlRibbonProgressNormalV.Create(m_ctrlRibbonProgressNormal.GetParams());
				m_ctrlRibbonProgressNormalV.Rotate(FALSE);
			}

			tmProgress.ReadControlRenderer(_T("NORMAL_EXT_V"), m_ctrlRibbonProgressNormalExtV, MakeResourceID(_T("RB_PROGRESS_NORMAL_EXT_V")));
			if (!m_ctrlRibbonProgressNormalExtV.IsValid())
			{
				m_ctrlRibbonProgressNormalExtV.Create(m_ctrlRibbonProgressNormalExt.GetParams());
				m_ctrlRibbonProgressNormalExtV.Rotate(FALSE);
			}

			tmProgress.ReadControlRenderer(_T("INFINITY_V"), m_ctrlRibbonProgressInfinityV, MakeResourceID(_T("RB_PROGRESS_INFINITY_V")));
			if (!m_ctrlRibbonProgressInfinityV.IsValid())
			{
				m_ctrlRibbonProgressInfinityV.Create(m_ctrlRibbonProgressInfinity.GetParams());
				m_ctrlRibbonProgressInfinityV.Rotate(FALSE);
			}
		}
	}

	if (tmItem.ExcludeTag (_T("BORDERS"), str))
	{
		CBCGPTagManager tmBorders (str);

		tmBorders.ReadControlRenderer (_T("QAT"), m_ctrlRibbonBorder_QAT, MakeResourceID(_T("RB_BRD_QAT")));
		tmBorders.ReadControlRenderer (_T("FLOATY"), m_ctrlRibbonBorder_Floaty, MakeResourceID(_T("RB_BRD_FLOATY")));
		tmBorders.ReadControlRenderer (_T("PANEL"), m_ctrlRibbonBorder_Panel, MakeResourceID(_T("RB_BRD_PNL")));
	}

	if (tmItem.ExcludeTag (_T("KEYTIP"), str))
	{
		CBCGPTagManager tmKeyTip (str);

		tmKeyTip.ReadControlRenderer(_T("BACK"), m_ctrlRibbonKeyTip, MakeResourceID(_T("RB_KEYTIP_BACK")));

		tmKeyTip.ReadColor (_T("TextNormal"), m_clrRibbonKeyTipTextNormal);

		BOOL bSystem = FALSE;
		if (m_clrRibbonKeyTipTextNormal == (COLORREF) (-1))
		{
			if (m_bToolTipParams && m_ToolTipParams.m_clrText != (COLORREF) (-1))
			{
				m_clrRibbonKeyTipTextNormal = m_ToolTipParams.m_clrText;
			}
			else
			{
				bSystem = TRUE;
				m_clrRibbonKeyTipTextNormal = ::GetSysColor (COLOR_INFOTEXT);
			}
		}

		tmKeyTip.ReadColor (_T("TextDisabled"), m_clrRibbonKeyTipTextDisabled);

		if (m_clrRibbonKeyTipTextDisabled == (COLORREF) (-1))
		{
			if (bSystem)
			{
				m_clrRibbonKeyTipTextDisabled = globalData.clrGrayedText;
			}
			else
			{
				m_clrRibbonKeyTipTextDisabled = CBCGPDrawManager::PixelAlpha (
					m_clrRibbonKeyTipTextNormal, globalData.clrWindow, 50);
			}
		}
	}

	if (tmItem.ExcludeTag (_T("HYPERLINK"), str))
	{
		CBCGPTagManager tmHyperlink (str);

		tmHyperlink.ReadColor (_T("Inactive"),			m_clrRibbonHyperlinkInactive);
		tmHyperlink.ReadColor (_T("Active"),			m_clrRibbonHyperlinkActive);
		tmHyperlink.ReadColor (_T("StatusbarInactive"),	m_clrRibbonStatusbarHyperlinkInactive);
		tmHyperlink.ReadColor (_T("StatusbarActive"),	m_clrRibbonStatusbarHyperlinkActive);
	}

	return TRUE;
}

//*****************************************************************************
void MVisualManager::OnDrawTab (CDC* pDC, CRect rectTab,
						int iTab, BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd)
{
	ASSERT_VALID (pTabWnd);
	ASSERT_VALID (pDC);

	if (!CanDrawImage ())
	{
		CBCGPVisualManager2007::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);
		return;
	}

	if(pTabWnd->IsOneNoteStyle () ||
	   pTabWnd->IsColored () ||
	   pTabWnd->IsVS2005Style () ||
	   pTabWnd->IsLeftRightRounded ())
	{

		if( IsEnableMDITabButton() && pTabWnd->GetActiveTab() == iTab )
		{
			if( IsEnableMDITabButtonView() )
				rectTab.right+=20;
			else
			{
				// 일단 이곳에서 이런 작업을 하게 된 것에 대해 매우 유감이다.
				// 그림을 그리는 곳에서 Window을 Show/Hide하거나 생성하거하 하는 짓은 절대로 하면 안된다.
				// 그러나 BCG소스를 수정하지 않고 기능을 구현하기 위해 부득이 하게 
				// 이곳에서 문제가 되지 않게끔 일정 코드를 구현하였다.
				// 코드를 이해하지 못한 분들은 절대 이 코드를 보고 따라하면 안됩니다. 
				// - 융합기술개발팀 이종협
				if( m_bRedrawMDITabButton )
					m_pTabButton->ShowWindow(SW_HIDE);
			}
		}
		
		CBCGPVisualManager2007::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);
		return;
	}

	const BOOL bBottom = pTabWnd->GetLocation () == CBCGPTabWnd::LOCATION_BOTTOM;
	const BOOL bIsHighlight = iTab == pTabWnd->GetHighlightedTab ();

	COLORREF clrText = pTabWnd->GetTabTextColor (iTab);
	
	if (pTabWnd->IsFlatTab ())
	{
		int nImage = (bIsActive || bIsHighlight) ? 2 : 1;

		CRgn rgn;

		POINT pts[4];

		if (bBottom)
		{
			rectTab.bottom++;

			pts[0].x = rectTab.left;
			pts[0].y = rectTab.bottom + 1;
			pts[1].x = rectTab.left;
			pts[1].y = rectTab.top;
			pts[2].x = rectTab.right + 1;
			pts[2].y = rectTab.top;
			pts[3].x = rectTab.right - rectTab.Height () + 1;
			pts[3].y = rectTab.bottom + 1;

			rectTab.top++;
		}
		else
		{
			pts[0].x = rectTab.left;
			pts[0].y = rectTab.bottom + 1;
			pts[1].x = rectTab.left;
			pts[1].y = rectTab.top;
			pts[2].x = rectTab.right - rectTab.Height () + 1;
			pts[2].y = rectTab.top;
			pts[3].x = rectTab.right + 1;
			pts[3].y = rectTab.bottom + 1;
		}

		rgn.CreatePolygonRgn (pts, 4, WINDING);

		int isave = pDC->SaveDC ();

		pDC->SelectClipRgn (&rgn, RGN_AND);

		m_ctrlTabFlat[bBottom ? 1 : 0].Draw (pDC, rectTab, nImage);

		CPen* pOldPen = pDC->SelectObject (&m_penTabFlatOuter[bIsActive ? 1 : 0]);

		if (bBottom)
		{
			pDC->MoveTo (pts[2].x, pts[2].y);
			pDC->LineTo (pts[3].x, pts[3].y - 1);
		}
		else
		{
			pDC->MoveTo (pts[2].x - 1, pts[2].y);
			pDC->LineTo (pts[3].x - 1, pts[3].y - 1);
		}

		pDC->SelectObject (&m_penTabFlatInner[bIsActive ? 1 : 0]);

		if (bBottom)
		{
			pDC->MoveTo (pts[2].x - 2, pts[2].y + 1);
			pDC->LineTo (pts[3].x, pts[3].y - 2);
		}
		else
		{
			pDC->MoveTo (pts[2].x - 1, pts[2].y + 1);
			pDC->LineTo (pts[3].x - 2, pts[3].y - 1);
		}

		pDC->SelectObject (pOldPen);

		pDC->SelectClipRgn (NULL);

		if (clrText == (COLORREF)-1)
		{
			clrText = bIsActive
						? m_clrTabFlatTextActive
						: bIsHighlight
							? m_clrTabFlatTextHighlighted
							: m_clrTabFlatTextInactive;
		}

		if(clrText == (COLORREF)-1)
		{
			clrText = globalData.clrBarText;
		}

		pDC->RestoreDC (isave);
	}
	else
	{
		if(clrText == (COLORREF)-1)
		{
			clrText = bIsActive
						? m_clrTab3DTextActive
						: bIsHighlight
							? m_clrTab3DTextHighlighted
							: m_clrTab3DTextInactive;
		}

		int nImage = bIsActive ? 3 : 0;
		if(bIsHighlight)
		{
			nImage += 1;
		}

		m_ctrlTab3D[bBottom ? 1 : 0].Draw (pDC, rectTab, nImage);

		if (pTabWnd->IsDialogControl ())
		{
			clrText = globalData.clrBtnText;
		}
	}

	COLORREF clrTextOld = (COLORREF)-1;
	if (pTabWnd->IsFlatTab ())
	{
		if (clrText != (COLORREF)-1)
		{
			clrTextOld = pDC->SetTextColor (clrText);
		}
	}

	if (!bBottom && pTabWnd->IsFlatTab ())
	{
		rectTab.right -= rectTab.Height() / 2;
	}

	OnDrawTabContent (pDC, rectTab, iTab, bIsActive, pTabWnd, clrText);

	if (pTabWnd->IsFlatTab ())
	{
		if (clrText != (COLORREF)-1)
		{
			pDC->SetTextColor (clrTextOld);
		}
	}
}

void MVisualManager::OnDrawTabContent (CDC* pDC, CRect rectTab, int iTab, BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd, COLORREF clrText)
{
	ASSERT_VALID (pTabWnd);
	ASSERT_VALID (pDC);

	if( !IsEnableMDITabButton() || !IsEnableMDITabButtonView() )
	{
		CBCGPVisualManager2007::OnDrawTabContent( pDC, rectTab, iTab, bIsActive, pTabWnd, clrText );
		return;
	}
	
	m_nCurrDrawedTab = iTab;

	CRect rectText = rectTab;

	if (pTabWnd->IsTabCloseButton())
	{
		CRect rectClose; rectClose.SetRectEmpty();
		BOOL bIsHighlighted = FALSE;
		BOOL bIsPressed = FALSE;

		if (pTabWnd->GetTabCloseButtonRect(iTab, rectClose, &bIsHighlighted, &bIsPressed) && !rectClose.IsRectEmpty())
		{
			rectTab.right = rectClose.left;

			OnDrawTabCloseButton (pDC, rectClose, pTabWnd, bIsHighlighted, bIsPressed, FALSE /* Disabled */);
		}
	}

	if (pTabWnd->IsFlatTab ())
	{
		//---------------
		// Draw tab text:
		//---------------
		UINT nFormat = DT_SINGLELINE | DT_CENTER | DT_VCENTER;
		if (pTabWnd->IsDrawNoPrefix ())
		{
			nFormat |= DT_NOPREFIX;
		}

		CString strText;
		pTabWnd->GetTabLabel (iTab, strText);

		if (pTabWnd->IsDrawNameInUpperCase())
		{
			strText.MakeUpper();
		}

		if( pTabWnd->GetActiveTab() == iTab ) rectText.right-=20;

		pDC->DrawText (strText, rectText, nFormat);
	}
	else
	{
		CSize sizeImage = pTabWnd->GetImageSize ();
		UINT uiIcon = pTabWnd->GetTabIcon (iTab);
		HICON hIcon = pTabWnd->GetTabHicon (iTab);

		if (uiIcon == (UINT)-1 && hIcon == NULL)
		{
			sizeImage.cx = 0;
		}

		if (sizeImage.cx + 2 * CBCGPBaseTabWnd::TAB_IMAGE_MARGIN <= rectTab.Width ())
		{
			if (hIcon != NULL)
			{
				//---------------------
				// Draw the tab's icon:
				//---------------------
				CRect rectImage = rectTab;

				rectImage.top += (rectTab.Height () - sizeImage.cy) / 2;
				rectImage.bottom = rectImage.top + sizeImage.cy;

				rectImage.left += IMAGE_MARGIN;
				rectImage.right = rectImage.left + sizeImage.cx;

				::DrawIconEx (pDC->GetSafeHdc (),
					rectImage.left, rectImage.top, hIcon,
					0, 0, 0, NULL, DI_NORMAL);
			}
			else
			{
				const CImageList* pImageList = pTabWnd->GetImageList ();
				if (pImageList != NULL && uiIcon != (UINT)-1)
				{
					//----------------------
					// Draw the tab's image:
					//----------------------
					CRect rectImage = rectTab;

					rectImage.top += (rectTab.Height () - sizeImage.cy) / 2;
					rectImage.bottom = rectImage.top + sizeImage.cy;

					rectImage.left += IMAGE_MARGIN;
					rectImage.right = rectImage.left + sizeImage.cx;

					ASSERT_VALID (pImageList);
					((CImageList*) pImageList)->Draw (pDC, uiIcon, rectImage.TopLeft (), ILD_TRANSPARENT);
				}
			}

			//------------------------------
			// Finally, draw the tab's text:
			//------------------------------
			CRect rcText = rectTab;
			rcText.left += sizeImage.cx + 2 * TEXT_MARGIN;

			if (rcText.Width () < sizeImage.cx * 2 && 
				!pTabWnd->IsLeftRightRounded ())
			{
				rcText.right -= TEXT_MARGIN;
			}

			if (clrText == (COLORREF)-1)
			{
				clrText = GetTabTextColor (pTabWnd, iTab, bIsActive);
			}

			if (clrText != (COLORREF)-1)
			{
				pDC->SetTextColor (clrText);
			}

			CString strText;
			pTabWnd->GetTabLabel (iTab, strText);

			if (pTabWnd->IsDrawNameInUpperCase())
			{
				strText.MakeUpper();
			}

			UINT nFormat = DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
			if (pTabWnd->IsDrawNoPrefix ())
			{
				nFormat |= DT_NOPREFIX;
			}

			if (pTabWnd->IsOneNoteStyle () || pTabWnd->IsVS2005Style ())
			{
				nFormat |= DT_CENTER;
			}
			else
			{
				nFormat |= DT_LEFT;
			}

			rectText = rcText;
			if( pTabWnd->GetActiveTab() == iTab ) 
				rectText.right-=20;
			
			pDC->DrawText (strText, rectText, nFormat);
		}
	}

	if( m_pTabButton )
	{
		BOOL bShow = FALSE;
		CFont* pFont = pDC->GetCurrentFont();
		if( pFont )
		{
			CString strText;
			pTabWnd->GetTabLabel (iTab, strText);
			pDC->SelectObject( pFont );

			SIZE size;
			GetTextExtentPoint(pDC->GetSafeHdc(), strText, strText.GetLength(), &size);

			bShow = ( rectText.Width() >= size.cx ) ? TRUE : FALSE;
		}
		

		// 일단 이곳에서 이런 작업을 하게 된 것에 대해 매우 유감이다.
		// 그림을 그리는 곳에서 Window을 Show/Hide하거나 생성하거하 하는 짓은 절대로 하면 안된다.
		// 그러나 BCG소스를 수정하지 않고 기능을 구현하기 위해 부득이 하게 
		// 이곳에서 문제가 되지 않게끔 일정 코드를 구현하였다.
		// 코드를 이해하지 못한 분들은 절대 이 코드를 보고 따라하면 안됩니다. 
		// - 융합기술개발팀 이종협
		if( pTabWnd->GetActiveTab() == iTab && bShow )
		{
			CRect rectBtn(rectTab);
			rectBtn.top     += 1;
			rectBtn.bottom  -= 1;
			rectBtn.left    = rectText.right;
			rectBtn.right   = rectText.right+18;

			if( !m_pTabButton->GetSafeHwnd() )
			{
				if( !m_pTabButton->Create(NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, rectBtn, (CWnd*)pTabWnd, m_uiTabButtonID) ) 
				{
					// 생성 실패.
					ASSERT(0);
					return;
				}
			}
			else
			{
				CRect rect;
				m_pTabButton->GetWindowRect(&rect);
				pTabWnd->ScreenToClient(&rect);

				if( rect != rectBtn || m_bRedrawMDITabButton )
				{
					m_pTabButton->SetWindowPos(NULL, rectBtn.left, rectBtn.top, rectBtn.right, rectBtn.bottom, SWP_NOSIZE | SWP_SHOWWINDOW);
					m_rectLastTabButton = rectBtn;

					m_bRedrawMDITabButton = FALSE;
				}
			}
		}
	}

	m_nCurrDrawedTab = -1;
}


//**************************************************************************************
BOOL MVisualManager::OnDrawPushButton (CDC* pDC, CRect rect, CBCGPButton* pButton, COLORREF& clrText)
{
	if (!CanDrawImage ())
	{
		return CBCGPVisualManager2007::OnDrawPushButton (pDC, rect, pButton, clrText);
	}

	ASSERT_VALID (pDC);

	int index = 0;

	BOOL bDisabled    = pButton->GetSafeHwnd() && !pButton->IsWindowEnabled ();
	BOOL bFocused     = pButton->GetSafeHwnd() && pButton->GetSafeHwnd () == ::GetFocus ();
	BOOL bDefault     = pButton->IsDefaultButton ();
	BOOL bPressed     = pButton->IsPressed ();
	BOOL bChecked     = pButton->IsChecked ();
	BOOL bHighlighted = pButton->IsHighlighted ();

	// 대화상자의 첫번째 버튼이 무조건 focus가 먹는 문제 해결.
	//bHighlighted |= bFocused;

	if (bDisabled)
	{
		index = 6;
	}
	else
	{
		if (bChecked)
		{
			index = 3;
		}
		else
		{
			if (bDefault && !bHighlighted)
			{
				index = 5;
			}
		}

		if (bPressed)
		{
			if (bHighlighted)
			{
				index = 2;
			}
		}
		else if (bHighlighted)
		{
			index++;
		}
	}

	globalData.DrawParentBackground (pButton, pDC);
	m_ctrlRibbonBtnPush.Draw (pDC, rect, index);

	clrText = globalData.clrBarText;

	if (bDisabled)
	{
		clrText = m_clrRibbonBarBtnTextDisabled;
	}
	else if (bHighlighted)
	{
		clrText = m_clrRibbonBarBtnTextHighlighted;
	}

	return TRUE;
}
//**************************************************************************************

//////////////////////////////////////////////////////////////////////////
// MDI Tab button 을 위해서...
void MVisualManager::EnableMDITabButton(CButton* pTabButton, UINT uiResID, std::vector<CRuntimeClass*>& svEableViews)
{ 
	m_pTabButton = pTabButton; 
	m_uiTabButtonID = uiResID;
	m_svEnableTabButtonViews.resize( svEableViews.size() );
	copy(svEableViews.begin(), svEableViews.end(), m_svEnableTabButtonViews.begin());
}

BOOL MVisualManager::IsEnableMDITabButtonView()
{
	CMDIFrameWnd* pMainfrm = (CMDIFrameWnd*)AfxGetMainWnd();
	if( !pMainfrm ) return FALSE;

	if( pMainfrm )
	{
		CMDIChildWnd* pChild = (CMDIChildWnd*)pMainfrm->GetActiveFrame();
		if (!pChild) return FALSE;

		CView* pActiveView = pChild->GetActiveView();
		if( !pActiveView ) return FALSE;

		std::vector<CRuntimeClass*>::iterator itr;
		for( itr=m_svEnableTabButtonViews.begin(); itr!=m_svEnableTabButtonViews.end(); ++itr )
		{
			CRuntimeClass* pRuntimeClass = pActiveView->GetRuntimeClass();
			if( *itr == pRuntimeClass ) return TRUE;
		}

	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
// Layered Window를 위해서... 이종협
void MVisualManager::OnDrawRibbonSliderZoomButton (
	CDC* pDC, 
	CRect rect, BOOL bIsZoomOut, 
	BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled)
{
	ASSERT_VALID (pDC);

	CBCGPControlRenderer* pRenderer = bIsZoomOut 
		? &m_ctrlRibbonSliderBtnMinus
		: &m_ctrlRibbonSliderBtnPlus;

	int index = 0;
	if (bIsDisabled)
	{
		index = 3;
	}
	else
	{
		if (bIsPressed)
		{
			if (bIsHighlighted)
			{
				index = 2;
			}
		}
		else if (bIsHighlighted)
		{
			index = 1;
		}
	}

	pRenderer->FillInterior (pDC, rect, 
		CBCGPToolBarImages::ImageAlignHorzCenter, 
		CBCGPToolBarImages::ImageAlignVertCenter,
		index);
}
//********************************************************************************
void MVisualManager::OnDrawRibbonSliderChannel (
	CDC* pDC, MLayeredSliderCtrl* pSlider, 
	CRect rect)
{
	ASSERT_VALID (pDC);

	DrawSeparator (pDC, rect, m_penSeparatorDark, m_penSeparator2, !pSlider->IsVert ());

	if (pSlider->IsVert ())
	{
		rect.top += rect.Height () / 2 - 1;
		rect.bottom = rect.top + 2;

		rect.InflateRect (2, 0);
	}
	else
	{
		rect.left += rect.Width () / 2 - 1;
		rect.right = rect.left + 2;

		rect.InflateRect (0, 2);
	}

	DrawSeparator (pDC, rect, m_penSeparatorDark, m_penSeparator2, pSlider->IsVert ());
}
//********************************************************************************
void MVisualManager::OnDrawRibbonSliderThumb (
	CDC* pDC, MLayeredSliderCtrl* pSlider, 
	CRect rect, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled)
{
	ASSERT_VALID (pDC);

	BOOL bIsVert = FALSE;
	BOOL bLeftTop = FALSE;
	BOOL bRightBottom = FALSE;

	if (pSlider != NULL)
	{
		ASSERT_VALID (pSlider);

		bIsVert = pSlider->IsVert ();
		bLeftTop = pSlider->IsThumbLeftTop ();
		bRightBottom = pSlider->IsThumbRightBottom ();
	}

	int indexRen = 0;

	if (bLeftTop && bRightBottom)
	{
		indexRen = 1;
	}
	else if (bLeftTop)
	{
		indexRen = 2;
	}

	if (bIsVert)
	{
		indexRen += 3;
	}

	CBCGPControlRenderer* pRenderer = NULL;

	if (indexRen == 0)
	{
		pRenderer = &m_ctrlRibbonSliderThumb;
	}
	else
	{
		pRenderer = &m_ctrlRibbonSliderThumbA[indexRen - 1];
	}

	if (pRenderer != NULL)
	{
		int index = 0;

		if (bIsDisabled)
		{
			index = 3;
		}
		else
		{
			if (bIsPressed)
			{
				index = 2;
			}
			else if (bIsHighlighted)
			{
				index = 1;
			}
		}

		pRenderer->FillInterior (pDC, rect, 
			CBCGPToolBarImages::ImageAlignHorzCenter, 
			CBCGPToolBarImages::ImageAlignVertCenter,
			index);
	}
}

// for Tree
COLORREF MVisualManager::GetTreeBKColor()
{
	return ::GetSysColor(COLOR_WINDOW);
}

COLORREF MVisualManager::GetTreeTextColor()
{
	return ::GetSysColor(COLOR_WINDOWTEXT);
}

COLORREF MVisualManager::GetTreeGridColor()
{
	return ::GetSysColor(COLOR_WINDOWTEXT);
}

COLORREF MVisualManager::GetTreeDisabledColor()
{
	return ::GetSysColor(COLOR_3DFACE);
}

COLORREF MVisualManager::GetTreeStatusColor()
{
	return ::GetSysColor(COLOR_WINDOWTEXT);
}

COLORREF MVisualManager::GetTreeGrayTextColor()
{
	return ::GetSysColor(COLOR_GRAYTEXT);
}

COLORREF MVisualManager::GetTreeHightLightColor()
{
	return ::GetSysColor(COLOR_HIGHLIGHT);
}

COLORREF MVisualManager::GetTreeHightLightTextColor()
{
	return ::GetSysColor(COLOR_HIGHLIGHTTEXT);
}

DWORD MVisualManager::GetTreeDCRop()
{
	return WHITENESS;
}

COLORREF MVisualManager::GetTreeExtButtonTextColor()
{
	return RGB(232, 232, 232);
}

COLORREF MVisualManager::GetTreeExtButtonDescriptionTextColor()
{
	return RGB(132, 132, 132);
}

void MVisualManager::OnDrawChartAreaEmptyStatus( CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea )
{
	SWITCH_RESOURCE;

	CBitmap bitmap;
	if( !bitmap.LoadBitmap(IDB_CHART_EMPTY) ) return;

	HBITMAP hBmp = (HBITMAP)bitmap;
	if( hBmp != NULL )
	{
		BITMAP bm;
		bitmap.GetBitmap(&bm);

		long width = bm.bmWidth;
		long height= bm.bmHeight;

		CBCGPImage image(hBmp);
		CBCGPPoint center = rectChartArea.CenterPoint();
		center.x -= (width/2);
		center.y -= (height/2);

		pGM->DrawImage( image, center);
	}
}

BOOL MVisualManager::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
{
	if (!CanDrawImage ())
	{
		return CBCGPVisualManager2007::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
	}

	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	CWindowDC dc (pWnd);

	if (dc.GetSafeHdc () != NULL)
	{
		CRgn rgn;
		if (!rectRedraw.IsRectEmpty ())
		{
			rgn.CreateRectRgnIndirect (rectRedraw);
			dc.SelectClipRgn (&rgn);
		}

#ifndef BCGP_EXCLUDE_RIBBON
		CBCGPRibbonBar* pBar = GetRibbonBar (pWnd);
		BOOL bRibbonCaption  = pBar != NULL && 
							   pBar->IsWindowVisible () &&
							   pBar->IsReplaceFrameCaption ();
#else
		BOOL bRibbonCaption = FALSE;
#endif

		CRect rtWindow;
		pWnd->GetWindowRect (rtWindow);
		pWnd->ScreenToClient (rtWindow);

		CRect rtClient;
		pWnd->GetClientRect (rtClient);

		rtClient.OffsetRect (-rtWindow.TopLeft ());
		dc.ExcludeClipRect (rtClient);

		rtWindow.OffsetRect (-rtWindow.TopLeft ());

        BOOL bActive = IsWindowActive (pWnd);

		const DWORD dwStyle = pWnd->GetStyle ();
		CRect rectCaption (rtWindow);
		CSize szSysBorder (globalUtils.GetSystemBorders (dwStyle));

		BOOL bDialog = pWnd->IsKindOf (RUNTIME_CLASS (CBCGPDialog)) 
			|| pWnd->IsKindOf(RUNTIME_CLASS (MDialog)) 
			|| pWnd->IsKindOf (RUNTIME_CLASS (CBCGPPropertySheet));

		if (!pWnd->IsIconic ())
		{
			rectCaption.bottom = rectCaption.top + szSysBorder.cy;
		}

		BOOL bMaximized = (dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE;

		if (!bRibbonCaption)
		{
			const DWORD dwStyleEx = pWnd->GetExStyle ();
			const BOOL bIsSmallCaption = (dwStyleEx & WS_EX_TOOLWINDOW) != 0;
			const BOOL bIsIconic = pWnd->IsIconic();

			if (!bIsIconic)
			{
				rectCaption.bottom += bIsSmallCaption ? ::GetSystemMetrics (SM_CYSMCAPTION) : ::GetSystemMetrics (SM_CYCAPTION);
			}
			else
			{
				rectCaption.bottom -= 1;
			}

			BOOL bDestroyIcon = FALSE;
			HICON hIcon = globalUtils.GetWndIcon (pWnd, &bDestroyIcon, FALSE);

			CString strText;
			pWnd->GetWindowText (strText);

			CString strTitle (strText);
			CString strDocument;

			BOOL bPrefix = FALSE;
			if ((dwStyle & FWS_ADDTOTITLE) == FWS_ADDTOTITLE)
			{
				bPrefix = (dwStyle & FWS_PREFIXTITLE) == FWS_PREFIXTITLE;
				CFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);

				if (pFrameWnd != NULL)
				{
					strTitle = pFrameWnd->GetTitle();

					if (!strTitle.IsEmpty ())
					{
						if (strText.GetLength () >= strTitle.GetLength ())
						{
							if (bPrefix)
							{
								int pos = strText.Find (strTitle, strText.GetLength () - strTitle.GetLength ());
								if (pos != -1)
								{
									strTitle = strText.Right (strTitle.GetLength () + 3);
									strDocument = strText.Left (strText.GetLength () - strTitle.GetLength ());
								}
							}
							else
							{
								int pos = strText.Find (strTitle);
								if (pos != -1)
								{
									strTitle = strText.Left (strTitle.GetLength () + 3);
									strDocument = strText.Right (strText.GetLength () - strTitle.GetLength ());
								}	
							}
						}
					}
					else
					{
						strDocument = strText;
					}
				}
			}

			if (!bIsIconic && rtClient.top <= szSysBorder.cy)
			{
				rectCaption.bottom = rectCaption.top + szSysBorder.cy;
			}

			if (bMaximized)
			{
				rectCaption.InflateRect (szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);
			}

			DrawNcCaption (&dc, rectCaption, dwStyle, dwStyleEx, 
							strTitle, strDocument, hIcon, bPrefix, bActive, m_bNcTextCenter,
							lstSysButtons);

			if (bDestroyIcon)
			{
				::DestroyIcon (hIcon);
			}

			if (bMaximized)
			{
				return TRUE;
			}
		}
#ifndef BCGP_EXCLUDE_RIBBON
		else
		{
			if (bMaximized)
			{
				return TRUE;
			}

			rectCaption.bottom += pBar->GetCaptionHeight ();

			if (IsBeta ())
			{
				CRect rectBorder (m_ctrlMainBorderCaption.GetParams ().m_rectSides);

				COLORREF clr1  = bActive 
									? m_clrAppCaptionActiveStart 
									: m_clrAppCaptionInactiveStart;
				COLORREF clr2  = bActive 
									? m_clrAppCaptionActiveFinish 
									: m_clrAppCaptionInactiveFinish;

				CRect rectCaption2 (rectCaption);
				rectCaption2.DeflateRect (rectBorder.left, rectBorder.top, 
					rectBorder.right, rectBorder.bottom);

				{
					CBCGPDrawManager dm (dc);
					dm.Fill4ColorsGradient (rectCaption2, clr1, clr2, clr2, clr1, FALSE);
				}

				m_ctrlMainBorderCaption.DrawFrame (&dc, rectCaption, bActive ? 0 : 1);
			}
			else
			{
				m_ctrlMainBorderCaption.Draw (&dc, rectCaption, bActive ? 0 : 1);
			}
		}
#endif // BCGP_EXCLUDE_RIBBON

		rtWindow.top = rectCaption.bottom;

		dc.ExcludeClipRect (rectCaption);

		if (pWnd->IsKindOf (RUNTIME_CLASS (CMDIChildWnd)) ||
			(bDialog && !m_ctrlDialogBorder.IsValid ()))
		{
			if (bDialog)
			{
				CRect rtDialog (rtWindow);
				rtDialog.DeflateRect (1, 0, 1, 1);
				dc.FillRect (rtDialog, &GetDlgBackBrush (pWnd));

				dc.ExcludeClipRect (rtDialog);
			}

			m_ctrlMDIChildBorder.DrawFrame (&dc, rtWindow, bActive ? 0 : 1);
		}
		else if (bDialog)
		{
			m_ctrlDialogBorder.DrawFrame (&dc, rtWindow, bActive ? 0 : 1);
		}
		else
		{
			m_ctrlMainBorder.DrawFrame (&dc, rtWindow, bActive ? 0 : 1);
		}

		if (bDialog)
		{
			dc.SelectClipRgn (NULL);
			return TRUE;
		}

		//-------------------------------
		// Find status bar extended area:
		//-------------------------------
		CRect rectExt (0, 0, 0, 0);
		BOOL bExtended    = FALSE;
		BOOL bBottomFrame = FALSE;
		BOOL bIsStatusBar = FALSE;

		CWnd* pStatusBar = pWnd->GetDescendantWindow (AFX_IDW_STATUS_BAR, TRUE);

		if (pStatusBar->GetSafeHwnd () != NULL && pStatusBar->IsWindowVisible ())
		{
			CBCGPStatusBar* pClassicStatusBar = DYNAMIC_DOWNCAST (
				CBCGPStatusBar, pStatusBar);
			if (pClassicStatusBar != NULL)
			{
				bExtended = pClassicStatusBar->GetExtendedArea (rectExt);
				bIsStatusBar = TRUE;
			}
#ifndef BCGP_EXCLUDE_RIBBON
			else
			{
				CBCGPRibbonStatusBar* pRibbonStatusBar = DYNAMIC_DOWNCAST (
					CBCGPRibbonStatusBar, pStatusBar);
				if (pRibbonStatusBar != NULL)
				{
					bExtended    = pRibbonStatusBar->GetExtendedArea (rectExt);
					bBottomFrame = pRibbonStatusBar->IsBottomFrame ();
					bIsStatusBar = TRUE;
				}
			}
#endif // BCGP_EXCLUDE_RIBBON
		}

		if (bIsStatusBar)
		{
			CRect rectStatus;
			pStatusBar->GetClientRect (rectStatus);

			int nHeight = rectStatus.Height ();
			rectStatus.bottom = rtWindow.bottom;
			rectStatus.top    = rectStatus.bottom - nHeight - (bBottomFrame ? 0 : szSysBorder.cy);
			rectStatus.left   = rtWindow.left;
			rectStatus.right  = rtWindow.right;

			if (bExtended)
			{
				rectExt.left   = rectStatus.right - rectExt.Width () - szSysBorder.cx;
				rectExt.top    = rectStatus.top;
				rectExt.bottom = rectStatus.bottom;
				rectExt.right  = rtWindow.right;
			}

			m_ctrlStatusBarBack.Draw (&dc, rectStatus, bActive ? 0 : 1);

			if (bExtended)
			{
				rectExt.left -= m_ctrlStatusBarBack_Ext.GetParams ().m_rectCorners.left;

				m_ctrlStatusBarBack_Ext.Draw (&dc, rectExt, bActive ? 0 : 1);
			}
		}

		dc.SelectClipRgn (NULL);

		return TRUE;
	}

	return CBCGPVisualManager2007::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
}
//*****************************************************************************
BOOL MVisualManager::OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow)
{
	ASSERT_VALID (pWnd);

	if (globalData.m_nBitsPerPixel <= 8 || globalData.IsHighContastMode ())
	{
		return CBCGPVisualManager2003::OnSetWindowRegion(pWnd, sizeWindow);
	}
	
	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	if (!CanDrawImage ())
	{
		return FALSE;
	}

	if (globalData.DwmIsCompositionEnabled () && IsDWMCaptionSupported())
	{
		return FALSE;
	}

    CSize sz (0, 0);

	BOOL bMainWnd = FALSE;

	if (DYNAMIC_DOWNCAST (CBCGPPopupMenu, pWnd) != NULL)
	{
		sz  = CSize (3, 3);
	}
#ifndef BCGP_EXCLUDE_RIBBON
	else if (DYNAMIC_DOWNCAST (CBCGPRibbonBar, pWnd) != NULL)
	{
		return FALSE;
	}
#endif
	else
	{
		if (pWnd->IsZoomed ())
		{
			pWnd->SetWindowRgn (NULL, TRUE);
			return TRUE;
		}

		sz  = CSize (9, 9);

		bMainWnd = TRUE;
	}

	if (sz != CSize (0, 0))
	{
        CRgn rgn;
		BOOL bCreated = FALSE;

		bCreated = rgn.CreateRoundRectRgn (0, 0, sizeWindow.cx + 1, sizeWindow.cy + 1, sz.cx, sz.cy);

		if (bCreated)
		{
			if (pWnd->IsKindOf (RUNTIME_CLASS (CMDIChildWnd)) ||
				pWnd->IsKindOf (RUNTIME_CLASS (CBCGPDialog)) ||
				pWnd->IsKindOf (RUNTIME_CLASS (MDialog))     ||
				pWnd->IsKindOf (RUNTIME_CLASS (CBCGPPropertySheet)))
			{
				CRgn rgnWindow;
				rgnWindow.CreateRectRgn (0, sz.cy, sizeWindow.cx, sizeWindow.cy);

				rgn.CombineRgn (&rgn, &rgnWindow, RGN_OR);
			}

			pWnd->SetWindowRgn ((HRGN)rgn.Detach (), TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

void MVisualManager::OnDrawDlgSizeBox (CDC* pDC, CWnd* pDlg, CRect rectSizeBox)
{
	CBCGPDialog* pDialog = DYNAMIC_DOWNCAST(CBCGPDialog, pDlg);
	if (!CanDrawImage () || pDialog == NULL || !pDialog->IsVisualManagerStyle ())
	{
		CBCGPVisualManager2003::OnDrawStatusBarSizeBox (pDC, NULL, rectSizeBox);
		return;
	}

	MDialog* pMDialog = DYNAMIC_DOWNCAST(MDialog, pDlg);
	if (!CanDrawImage () || pMDialog == NULL || !pMDialog->IsVisualManagerStyle ())
	{
		CBCGPVisualManager2003::OnDrawStatusBarSizeBox (pDC, NULL, rectSizeBox);
		return;
	}

	OnDrawStatusBarSizeBox (pDC, NULL, rectSizeBox);
}

HBITMAP MVisualManager::GetRibbonMainBtnIcon()
{
	return m_RibbonBtnMainIcon.GetImageWell();
}

void MVisualManager::OnDrawRibbonMainButton (
	CDC* pDC, 
	CBCGPRibbonButton* pButton)
{
	if (!CanDrawImage ())
	{
		CBCGPVisualManager2007::OnDrawRibbonMainButton (pDC, pButton);
		return;
	}

	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	BOOL bHighlighted = pButton->IsHighlighted () || pButton->IsFocused ();
	BOOL bPressed = pButton->IsPressed ();

	if (pButton->IsDroppedDown ())
	{
		bPressed = TRUE;
		bHighlighted = TRUE;
	}

	CRect rect = pButton->GetRect ();

	int index = 0;
	if (bPressed)
	{
		if (bHighlighted)
		{
			index = 2;
		}
	}
	else if (bHighlighted)
	{
		index = 1;
	}

	if (!pButton->GetParentRibbonBar ()->IsScenicLook ())
	{
		CRect rectImage (m_RibbonBtnMain.GetParams ().m_rectImage);

		CBCGPToolBarImages::ImageAlignHorz horz = CBCGPToolBarImages::ImageAlignHorzStretch;
		CBCGPToolBarImages::ImageAlignVert vert = CBCGPToolBarImages::ImageAlignVertStretch;

		if (rect.Width () >= rectImage.Width () &&
			rect.Height () >= rectImage.Height () &&
			(globalData.GetRibbonImageScale () == 1. || m_RibbonBtnMain.IsScaled ()))
		{
			horz = CBCGPToolBarImages::ImageAlignHorzCenter;
			vert = CBCGPToolBarImages::ImageAlignVertCenter;
		}

		rect.OffsetRect (0, -1);
		m_RibbonBtnMain.FillInterior (pDC, rect, horz, vert, index);
	}
	else
	{
		m_ctrlRibbonBtnGroup_S.Draw (pDC, rect, index);
	}
}

void MVisualManager::OnAfterQATChangeRect(CBCGPRibbonQuickAccessToolbar* pQAT)
{
	CRect rect = pQAT->GetRect();
	rect.OffsetRect(-xMargin, 0);
	pQAT->SetRect( rect );
}