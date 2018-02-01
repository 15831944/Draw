#include "StdAfx.h"
#include "MRibbonButton.h"
#include "ConvertAccelIDToString.h"

using namespace mit::frx;

const int nLargeButtonMarginX = 5;
const int nLargeButtonMarginY = 1;

const int nSmallButtonMarginX = 3;
const int nSmallButtonMarginY = 3;

const int nDefaultPaneButtonMargin = 2;

static const CString strDummyAmpSeq = _T("\001\001");


//////////////////////////////////////////////////////////////////////////
// clss MRibbonPanel
MRibbonPanel::MRibbonPanel(LPCTSTR lpszName, HICON hIcon, BOOL bAutoDestroyIcon)
: CBCGPRibbonPanel( lpszName, hIcon, bAutoDestroyIcon )
{
	m_nYMargin = 2;
}

MRibbonPanel::MRibbonPanel(CBCGPRibbonPaletteButton* pPaletteButton)
: CBCGPRibbonPanel( pPaletteButton )
{
	m_nYMargin = 2;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// class MRibbonComboBox
MRibbonComboBox::MRibbonComboBox()
{

}

MRibbonComboBox::MRibbonComboBox(UINT nID, BOOL bHasEditBox, int nWidth, LPCTSTR lpszLabel, int nImage)
: CBCGPRibbonComboBox( nID, bHasEditBox, nWidth, lpszLabel, nImage )
{

}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// class MRibbonFontComboBox
MRibbonFontComboBox::MRibbonFontComboBox() 
: CBCGPRibbonFontComboBox() 
{

}

MRibbonFontComboBox::MRibbonFontComboBox(UINT nID, int nFontType, BYTE nCharSet, BYTE nPitchAndFamily, int nWidth)
: CBCGPRibbonFontComboBox( nID, nFontType, nCharSet, nPitchAndFamily, nWidth )
{

}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// class MRibbonButton

IMPLEMENT_DYNCREATE(MRibbonButton, CBCGPRibbonButton)

MRibbonButton::MRibbonButton()
: CBCGPRibbonButton()
{

}

MRibbonButton::MRibbonButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex, int nLargeImageIndex, BOOL bAlwaysShowDescription)
: CBCGPRibbonButton( nID, lpszText, nSmallImageIndex, nLargeImageIndex, bAlwaysShowDescription)
{
#if (defined(_MGEN) && (defined(_CH) || defined(_JP))) || ( defined(_CIVIL) && ( defined(_ORG) || defined(_JP) || defined(_RUS)) )
  SetToolTipText(lpszText);
#endif
}

MRibbonButton::MRibbonButton( UINT nID, LPCTSTR lpszText, HICON hIcon, BOOL bAlwaysShowDescription, HICON hIconSmall, BOOL bAutoDestroyIcon, BOOL bAlphaBlendIcon)
: CBCGPRibbonButton( nID, lpszText, hIcon, bAlwaysShowDescription, hIconSmall, bAutoDestroyIcon, bAlphaBlendIcon )
{
#if (defined(_MGEN) && (defined(_CH) || defined(_JP))) || ( defined(_CIVIL) && ( defined(_ORG) || defined(_JP) || defined(_RUS)) )
  SetToolTipText(lpszText);
#endif

}

MRibbonButton::~MRibbonButton()
{

}

void MRibbonButton::AddAccelToText()
{
  CString strAccel;
  CConvertAccelIDToString::GetInstance()->GetStringByID(m_nID, strAccel);

  CString strPostfix;
  strPostfix.Format("   \t   %s  ", strAccel);
  m_strText += strPostfix;
};

void MRibbonButton::RestoreText()
{
  int iTabOffset = m_strText.Find (_T('\t'));
  if (iTabOffset >= 0)
  {
    m_strText = m_strText.Left (iTabOffset-3);
  }
}

void MRibbonButton::OnDraw(CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	if (m_rect.IsRectEmpty ())
	{
		return;
	}

  BOOL isPopup = FALSE;
  if (m_pParentMenu && m_pParentMenu->IsKindOf(RUNTIME_CLASS(CBCGPRibbonPanelMenuBar)))
  {
    isPopup = TRUE;
  }

	if (IsDefaultMenuLook () && !IsQATMode () && !m_bIsLargeImage && !IsSearchResultMode ())
	{
		MToolBarMenuButton dummy;

		dummy.m_strText = m_strText;
		dummy.m_nID = m_nID;
		dummy.m_bMenuMode = TRUE;
		dummy.m_pWndParent = GetParentWnd ();
		dummy.m_bIsRadio = m_bIsRadio;

		if (IsChecked ())
		{
			dummy.m_nStyle |= TBBS_CHECKED;
		}

		if (HasMenu ())
		{
			dummy.m_bDrawDownArrow = TRUE;
		}

		BOOL bIsHighlighted = m_bIsHighlighted;

		if (IsDisabled ())
		{
			dummy.m_nStyle |= TBBS_DISABLED;

			bIsHighlighted = IsFocused ();
		}

		dummy.OnDraw (pDC, m_rect, NULL, TRUE, FALSE, bIsHighlighted || m_bIsFocused);
		return;
	}

	BOOL bIsDisabled = m_bIsDisabled;
	BOOL bIsDroppedDown = m_bIsDroppedDown;
	BOOL bIsHighlighted = m_bIsHighlighted;
	BOOL bMenuHighlighted = m_bIsMenuHighlighted;
	BOOL bCommandHighlighted = m_bIsCommandHighlighted;

	const int cxDropDown = GetDropDownImageWidth ();

	if (m_bIsDisabled && (HasMenu () || HasPin()))
	{
		if (m_bIsDefaultCommand || 
			(!m_bIsDefaultCommand && !(m_nID == 0 || m_nID == (UINT)-1)))
		{
			m_bIsHighlighted = FALSE;
		}
		else
		{
			m_bIsDisabled = FALSE;
		}
	}

	if (m_bToBeClosed)
	{
		m_bIsDroppedDown = FALSE;
	}

	if (m_bIsFocused)
	{
		m_bIsHighlighted = TRUE;
		m_bIsMenuHighlighted = TRUE;
		m_bIsCommandHighlighted = TRUE;
	}

	CRect rectMenuArrow;
	rectMenuArrow.SetRectEmpty ();

	if (HasMenu () || HasPin())
	{
		rectMenuArrow = m_rect;

		rectMenuArrow.left = rectMenuArrow.right - cxDropDown - m_nMenuArrowMargin;
		if (m_sizeTextRight.cx == 0 && !m_bQuickAccessMode)
		{
			rectMenuArrow.left -= 2;
		}

		rectMenuArrow.bottom -= m_nMenuArrowMargin;

		if (m_bIsDefaultCommand)
		{
			m_rectMenu = m_rect;

			m_rectMenu.left = m_rectMenu.right - cxDropDown - m_nMenuArrowMargin - 1;

			m_rectCommand = m_rect;
			m_rectCommand.right = m_rectMenu.left;

			m_bMenuOnBottom = FALSE;
		}
	}

	CSize sizeImageLarge = GetImageSize (RibbonImageLarge);
	CSize sizeImageSmall = GetImageSize (RibbonImageSmall);

	CRect rectText = m_rect;
	BOOL bDrawText = !IsMainRibbonButton () && !m_bQuickAccessMode && !m_bFloatyMode;

	if (m_bQuickAccessMode || m_bFloatyMode)
	{
		bDrawText = FALSE;
	}
	else if (m_bCompactMode)
	{
		bDrawText = FALSE;
	}
	else if (sizeImageLarge != CSize (0, 0) && !m_bMenuOnBottom && m_bIsLargeImage)
	{
		if (!m_rectMenu.IsRectEmpty ())
		{
			m_rectMenu.left -= cxDropDown;
			m_rectCommand.right = m_rectMenu.left;
		}

		rectMenuArrow.OffsetRect (-cxDropDown / 2, 0);
	}

	const RibbonImageType imageType = 
		m_bIsLargeImage ? RibbonImageLarge : RibbonImageSmall;

	CSize sizeImage = GetImageSize (imageType);
	BOOL bDrawDefaultImage = FALSE;

	if ((m_bQuickAccessMode || m_bFloatyMode || m_bSearchResultMode) && sizeImage == CSize (0, 0))
	{
		// Use default image:
		sizeImage = CSize (16, 16);

		if (globalData.GetRibbonImageScale () != 1.)
		{
			sizeImage.cx = (int) (.5 + globalData.GetRibbonImageScale () * sizeImage.cx);
			sizeImage.cy = (int) (.5 + globalData.GetRibbonImageScale () * sizeImage.cy);
		}

		bDrawDefaultImage = TRUE;
	}

	CRect rectImage = m_rect;
	rectImage.DeflateRect (m_szMargin);

	if (IsMainRibbonButton ())
	{
		if (globalData.GetRibbonImageScale () != 1.)
		{
			sizeImage.cx = (int) (.8 * globalData.GetRibbonImageScale () * sizeImage.cx);
			sizeImage.cy = (int) (.8 * globalData.GetRibbonImageScale () * sizeImage.cy);
		}

		rectImage.left += (rectImage.Width () - sizeImage.cx) / 2;
		rectImage.top  += (rectImage.Height () - sizeImage.cy) / 2;

		rectImage.OffsetRect (CBCGPVisualManager::GetInstance ()->GetRibbonMainImageOffset ());
	}
	else if (m_bIsLargeImage && !m_bTextAlwaysOnRight)
	{
		rectImage.left = rectImage.CenterPoint ().x - sizeImage.cx / 2;
		rectImage.top += m_szMargin.cy + 1;

		if (!bDrawText)
		{
			rectImage.top = rectImage.CenterPoint ().y - sizeImage.cy / 2;
		}
	}
	else
	{
		rectImage.top = rectImage.CenterPoint ().y - sizeImage.cy / 2;
	}

	rectImage.right = rectImage.left + sizeImage.cx;
	rectImage.bottom = rectImage.top + sizeImage.cy;

	if (m_bIsLargeImage && !m_bTextAlwaysOnRight && (HasMenu () || HasPin()) && m_bIsDefaultCommand)
	{
		m_rectMenu = m_rect;
		m_rectMenu.top = rectImage.bottom + 3;

		m_rectCommand = m_rect;
		m_rectCommand.bottom = m_rectMenu.top;

		m_bMenuOnBottom = TRUE;
	}

	COLORREF clrText = (COLORREF)-1;

	if (!IsMainRibbonButton ())
	{
		clrText = OnFillBackground (pDC);
	}

	if (IsMenuMode () && IsChecked () && sizeImage != CSize (0, 0))
	{
		CBCGPVisualManager::GetInstance ()->OnDrawRibbonMenuCheckFrame (pDC,
			this, rectImage);

		if (bDrawDefaultImage && IsSearchResultMode ())
		{
			CBCGPToolbarMenuButton dummy;
			CBCGPVisualManager::GetInstance ()->OnDrawMenuCheck (pDC, &dummy, 
				rectImage, m_bIsHighlighted, m_bIsRadio);
		}
	}

	//------------
	// Draw image:
	//------------
	if (bDrawDefaultImage)
	{
		if (!IsSearchResultMode ())
		{
			CBCGPVisualManager::GetInstance ()->OnDrawDefaultRibbonImage (
				pDC, rectImage, m_bIsDisabled, m_bIsPressed, m_bIsHighlighted);
		}
	}
	else
	{
		BOOL bIsRibbonImageScale = globalData.IsRibbonImageScaleEnabled ();

		if (IsMenuMode () && !m_bIsLargeImage)
		{
			if (m_pParentMenu == NULL || !m_pParentMenu->IsMainPanel ())
			{
				globalData.EnableRibbonImageScale (FALSE);
			}
		}

		DrawImage (pDC, imageType, rectImage);
		globalData.EnableRibbonImageScale (bIsRibbonImageScale);
	}

	//-----------
	// Draw text:
	//-----------
	if (bDrawText)
	{
		CFont* pOldFont = NULL;

		CRect rectText = m_rect;
		UINT uiDTFlags = 0;

		COLORREF clrTextOld = (COLORREF)-1;

		if (bIsDisabled && 
			(m_bIsDefaultCommand ||
			(!m_bIsDefaultCommand && !(m_nID == 0 || m_nID == (UINT)-1))))
		{
			if (m_bQuickAccessMode)
			{
				clrText = CBCGPVisualManager::GetInstance ()->GetRibbonQATTextColor (TRUE);
			}
			else
			{
				clrTextOld = pDC->SetTextColor (
					clrText == (COLORREF)-1 ? 
					CBCGPVisualManager::GetInstance ()->GetRibbonBarTextColor (TRUE) : clrText);
			}
		}
		else if (clrText != (COLORREF)-1)
		{
			clrTextOld = pDC->SetTextColor (clrText);
		}

		if (m_bIsLargeImage && !m_bTextAlwaysOnRight)
		{
			DrawBottomText (pDC, FALSE);
			rectMenuArrow.SetRectEmpty ();
		}
		else
		{
			rectText.left = rectImage.right;

			if (m_nImageOffset > 0)
			{
				rectText.left = m_rect.left + m_nImageOffset + 3 * m_szMargin.cx;
			}
			else if (sizeImage.cx != 0)
			{
				rectText.left += GetTextOffset ();
			}

      if (isPopup)
      {
        int nGutterWidth = m_pParentMenu->GetGutterWidth() + m_szMargin.cx;
        rectText.left = max(rectText.left, nGutterWidth);
      }

			uiDTFlags = DT_SINGLELINE | DT_END_ELLIPSIS;

			if (!m_bAlwaysShowDescription || m_strDescription.IsEmpty ())
			{
				uiDTFlags |= DT_VCENTER;
			}
			else
			{
				pOldFont = pDC->SelectObject (&globalData.fontBold);
				ASSERT (pOldFont != NULL);

				rectText.top += max (0, (m_rect.Height () - m_sizeTextRight.cy) / 2);
			}

			if (m_bIsTabElement)
			{
				rectText.OffsetRect (0, 2);
			}

			int nTextHeight = DoDrawText (pDC, m_strText, rectText, uiDTFlags, 
				(bIsDisabled && CBCGPToolBarImages::m_bIsDrawOnGlass)
				? (m_bQuickAccessMode
				? CBCGPVisualManager::GetInstance ()->GetRibbonQATTextColor (TRUE)
				: CBCGPVisualManager::GetInstance ()->GetToolbarDisabledTextColor ())
				: -1);

			if (pOldFont != NULL)
			{
				pDC->SelectObject (pOldFont);
			}

			if (m_bAlwaysShowDescription && !m_strDescription.IsEmpty ())
			{
				rectText.top += nTextHeight + m_szMargin.cy;
				rectText.right = m_rect.right - m_szMargin.cx;

				pDC->DrawText (m_strDescription, rectText, DT_WORDBREAK | DT_END_ELLIPSIS);
			}

			if (nTextHeight == m_sizeTextRight.cy &&
				m_bIsLargeImage && (HasMenu () || HasPin()))
			{
				rectMenuArrow = m_rect;
				rectMenuArrow.DeflateRect (m_nMenuArrowMargin, m_nMenuArrowMargin * 2);
				rectMenuArrow.right -= 2;

				int cyMenu = CBCGPMenuImages::Size ().cy;

				rectMenuArrow.top = rectMenuArrow.bottom - cyMenu;
				rectMenuArrow.bottom = rectMenuArrow.top + CBCGPMenuImages::Size ().cy;
			}
		}

		if (clrTextOld != (COLORREF)-1)
		{
			pDC->SetTextColor (clrTextOld);
		}
	}

	if (!IsMainRibbonButton ())
	{
		if (!rectMenuArrow.IsRectEmpty ())
		{
			OnDrawMenuArrow(pDC, rectMenuArrow);
		}

		OnDrawBorder (pDC);
	}

	m_bIsDisabled = bIsDisabled;
	m_bIsDroppedDown = bIsDroppedDown;
	m_bIsHighlighted = bIsHighlighted;
	m_bIsMenuHighlighted = bMenuHighlighted;
	m_bIsCommandHighlighted = bCommandHighlighted;
}

CSize MRibbonButton::DrawBottomText(CDC* pDC, BOOL bCalcOnly)
{
	ASSERT_VALID (this);

	if (m_pParent == NULL)
	{
		return CSize (0, 0);
	}

	if (m_strText.IsEmpty ())
	{
		return CSize (0, 0);
	}

	ASSERT_VALID (m_pParent);

	const CSize sizeImageLarge = m_pParent->GetImageSize (TRUE);
	if (sizeImageLarge == CSize (0, 0))
	{
		ASSERT (FALSE);
		return CSize (0, 0);
	}

	CSize sizeText = pDC->GetTextExtent (m_strText);

	const int nTextLineHeight = sizeText.cy;
	int nMenuArrowWidth = (HasMenu () || IsDefaultPanelButton ()) ? (CBCGPMenuImages::Size ().cx) : 0;

	if (nMenuArrowWidth != 0 && globalData.GetRibbonImageScale () > 1.)
	{
		nMenuArrowWidth = (int)(.5 + globalData.GetRibbonImageScale () * nMenuArrowWidth);
	}

	if (bCalcOnly)
	{
		m_nWrapIndex = -1;
		int nTextWidth = 0;

		if (m_arWordIndexes.GetSize () == 0) // 1 word
		{
			nTextWidth = sizeText.cx;
		}
		else
		{
			nTextWidth = 32767;

			for (int i = 0; i < m_arWordIndexes.GetSize (); i++)
			{
				int nIndex = m_arWordIndexes [i];

				CString strLineOne = m_strText.Left (nIndex);

				if (!IsDefaultPanelButton ())
				{
					strLineOne.Replace (_T("&&"), strDummyAmpSeq);
					strLineOne.Remove (_T('&'));
					strLineOne.Replace (strDummyAmpSeq, _T("&"));
				}

				const int cx1 = pDC->GetTextExtent (strLineOne).cx;

				CString strLineTwo = m_strText.Mid (nIndex + 1);

				if (!IsDefaultPanelButton ())
				{
					strLineTwo.Replace (_T("&&"), strDummyAmpSeq);
					strLineTwo.Remove (_T('&'));
					strLineTwo.Replace (strDummyAmpSeq, _T("&"));
				}

				const int cx2 = pDC->GetTextExtent (strLineTwo).cx + nMenuArrowWidth;

				int nWidth = max (cx1, cx2);

				if (nWidth < nTextWidth)
				{
					nTextWidth = nWidth;
					m_nWrapIndex = nIndex;
				}
			}
		}

		if (nTextWidth % 2)
		{
			nTextWidth--;
		}

		CSize size (nTextWidth, nTextLineHeight * 2);
		return size;
	}

	int y = m_rect.top + nLargeButtonMarginY + sizeImageLarge.cy + 5;
	CRect rectMenuArrow (0, 0, 0, 0);

	if (IsDefaultPanelButton ())
	{
		y += nDefaultPaneButtonMargin;
	}

	CRect rectText = m_rect;
	rectText.top = y;

	UINT uiDTFlags = DT_SINGLELINE | DT_CENTER;
	if (IsDefaultPanelButton ())
	{
		uiDTFlags |= DT_NOPREFIX;
	}

	if (m_nWrapIndex == -1)
	{
		// Single line text

		//////////////////////////////////////////////////////////////////////////
		// Impact 위해 배경으로 살짝 깔았다.
		COLORREF clrText = (COLORREF)-1;
		COLORREF clrTextMask = RGB(230,240,255);
		if(m_bAlwaysShowDescription==TRUE)  // 오른쪽 상단 메뉴의 글자색을 다르게 하기 위해, 원래는 다른 변수로 추가해야 하는데 헤더파일에 변수를 추가하면 실행에러가 나 이 변수를 사용함. 20120322 KIMJM
		{
			clrTextMask = RGB(28,28,28);
			clrText     = RGB(221,221,221);
		}
		pDC->SetTextColor (clrTextMask);
		CRect rectTabMask = rectText;
		rectTabMask.top += 1;
		rectTabMask.bottom += 1;
		pDC->DrawText (m_strText, rectTabMask, uiDTFlags);

		if (m_bIsDisabled && m_bIsDefaultCommand)
		{
			pDC->SetTextColor (clrText == (COLORREF)-1 ? globalData.clrGrayedText : clrText);
		}
		else
		{
			pDC->SetTextColor (clrText);
		}
		//////////////////////////////////////////////////////////////////////////

		pDC->DrawText (m_strText, rectText, uiDTFlags);

		if (HasMenu () || IsDefaultPanelButton ())
		{
			rectMenuArrow = m_rect;

			rectMenuArrow.top = y + nTextLineHeight + 2;
			rectMenuArrow.left = m_rect.CenterPoint ().x - CBCGPMenuImages::Size ().cx / 2 - 1;
		}
	}
	else
	{
		CString strLineOne = m_strText.Left (m_nWrapIndex);

		//////////////////////////////////////////////////////////////////////////
		// Impact 위해 배경으로 살짝 깔았다.
		COLORREF clrText = (COLORREF)-1;
		COLORREF clrTextMask = RGB(230,240,255);
		if(m_bAlwaysShowDescription==TRUE)  // 오른쪽 상단 메뉴의 글자색을 다르게 하기 위해, 원래는 다른 변수로 추가해야 하는데 헤더파일에 변수를 추가하면 실행에러가 나 이 변수를 사용함. 20120322 KIMJM
		{
			clrTextMask = RGB(28,28,28);
			clrText     = RGB(221,221,221);
		}
		pDC->SetTextColor (clrTextMask);
		CRect rectTabMask = rectText;
		rectTabMask.top += 1;
		rectTabMask.bottom += 1;
		pDC->DrawText (strLineOne, rectTabMask, uiDTFlags);

		if (m_bIsDisabled && m_bIsDefaultCommand)
		{
			pDC->SetTextColor (clrText == (COLORREF)-1 ? globalData.clrGrayedText : clrText);
		}
		else
		{
			pDC->SetTextColor (clrText);
		}
		//////////////////////////////////////////////////////////////////////////

		pDC->DrawText (strLineOne, rectText, uiDTFlags);

		rectText.top = y + nTextLineHeight;
		rectText.right -= nMenuArrowWidth;

		if (globalData.GetRibbonImageScale () > 1.)
		{
			rectText.top -= 4;
		}

		// 두번째 라인...
		CString strLineTwo = m_strText.Mid (m_nWrapIndex + 1);

		pDC->SetTextColor (clrTextMask);
		rectTabMask = rectText;
		rectTabMask.top += 1;
		rectTabMask.bottom += 1;
		pDC->DrawText (strLineTwo, rectTabMask, uiDTFlags);

		if (m_bIsDisabled && m_bIsDefaultCommand)
		{
			pDC->SetTextColor (clrText == (COLORREF)-1 ? globalData.clrGrayedText : clrText);
		}
		else
		{
			pDC->SetTextColor (clrText);
		}

		pDC->DrawText (strLineTwo, rectText, uiDTFlags);

		if (HasMenu () || IsDefaultPanelButton ())
		{
			rectMenuArrow = rectText;

			rectMenuArrow.top += 2;
			rectMenuArrow.left = rectText.right - (rectText.Width () - pDC->GetTextExtent (strLineTwo).cx) / 2;
		}
	}

	if (!rectMenuArrow.IsRectEmpty ())
	{
		int nMenuArrowHeight = CBCGPMenuImages::Size ().cy;

		rectMenuArrow.bottom = rectMenuArrow.top + nMenuArrowHeight;
		rectMenuArrow.right = rectMenuArrow.left + nMenuArrowWidth;

		CRect rectWhite = rectMenuArrow;
		rectWhite.OffsetRect (0, 1);

		CBCGPMenuImages::IMAGES_IDS id = 
			globalData.GetRibbonImageScale () > 1. ? 
			CBCGPMenuImages::IdArowDownLarge : CBCGPMenuImages::IdArowDown;

		CBCGPMenuImages::Draw (pDC, id, rectWhite, CBCGPMenuImages::ImageWhite);
		CBCGPMenuImages::Draw (pDC, id, rectMenuArrow, 
			m_bIsDisabled ? CBCGPMenuImages::ImageGray : CBCGPMenuImages::ImageBlack);
	}

	return CSize (0, 0);
}

int MRibbonButton::DoDrawText (CDC* pDC, const CString& strText, CRect rectText, UINT uiDTFlags,
										COLORREF clrText)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

  // \t을 찾아서 메뉴의 이름과 단축키 문자열을 분리
  BOOL isPopup = FALSE;
  if (m_pParentMenu && m_pParentMenu->IsKindOf(RUNTIME_CLASS(CBCGPRibbonPanelMenuBar)))
  {
    isPopup = TRUE;
  }

  CString strName=strText,strAccel;  
  int iTabOffset = m_strText.Find (_T('\t'));
  if (iTabOffset >= 0 && isPopup)
  {
    strName  = strText.Left (iTabOffset);
    strAccel = strText.Mid (iTabOffset + 1);
  }

	if (CBCGPToolBarImages::m_bIsDrawOnGlass)
	{
		const BOOL bIsZoomed = GetParentRibbonBar ()->GetSafeHwnd () != NULL &&
			GetParentRibbonBar ()->GetParent ()->IsZoomed ();

		CBCGPVisualManager::GetInstance ()->DrawTextOnGlass (pDC, strName, rectText, uiDTFlags, m_nTextGlassGlowSize, 
			bIsZoomed && !globalData.bIsWindows7 ? RGB (255, 255, 255) : clrText);

		return pDC->GetTextExtent (strName).cy;
	}

	COLORREF clrTextOld = (COLORREF)-1;
	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor (clrText);
	}

	int nRes = 0;

	if (m_bSearchResultMode)
	{
		CString strWithoutAmp = strName;
		strWithoutAmp.Replace (_T("&&"), strDummyAmpSeq);
		strWithoutAmp.Remove (_T('&'));
		strWithoutAmp.Replace (strDummyAmpSeq, _T("&"));

		/////////////////////////////////////////////////////////////////////////
		// Impact 위해 배경으로 살짝 깔았다.
		COLORREF clrText = (COLORREF)-1;
		COLORREF clrTextMask = RGB(230,240,255);
		if(m_bAlwaysShowDescription==TRUE)  // 오른쪽 상단 메뉴의 글자색을 다르게 하기 위해, 원래는 다른 변수로 추가해야 하는데 헤더파일에 변수를 추가하면 실행에러가 나 이 변수를 사용함. 20120322 KIMJM
		{
			clrTextMask = RGB(28,28,28);
			clrText     = RGB(221,221,221);
		}
		pDC->SetTextColor (clrTextMask);
		CRect rectTabMask = rectText;
		rectTabMask.top += 1;
		rectTabMask.bottom += 1;
		pDC->DrawText (strWithoutAmp, rectTabMask, uiDTFlags);

		if (m_bIsDisabled && m_bIsDefaultCommand)
		{
			pDC->SetTextColor (clrText == (COLORREF)-1 ? globalData.clrGrayedText : clrText);
		}
		else
		{
			pDC->SetTextColor (clrText);
		}
		//////////////////////////////////////////////////////////////////////////

		nRes = pDC->DrawText (strWithoutAmp, rectText, uiDTFlags);
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		// Impact 위해 배경으로 살짝 깔았다.
		COLORREF clrText = (COLORREF)-1;
		COLORREF clrTextMask = RGB(230,240,255);
		if(m_bAlwaysShowDescription==TRUE)  // 오른쪽 상단 메뉴의 글자색을 다르게 하기 위해, 원래는 다른 변수로 추가해야 하는데 헤더파일에 변수를 추가하면 실행에러가 나 이 변수를 사용함. 20120322 KIMJM
		{
			clrTextMask = RGB(28,28,28);
			clrText     = RGB(221,221,221);
		}
		pDC->SetTextColor (clrTextMask);
		CRect rectTabMask = rectText;
		rectTabMask.top += 1;
		rectTabMask.bottom += 1;
		pDC->DrawText (strName, rectTabMask, uiDTFlags);

		if (m_bIsDisabled && m_bIsDefaultCommand)
		{
			pDC->SetTextColor (clrText == (COLORREF)-1 ? globalData.clrGrayedText : clrText);
		}
		else
		{
			pDC->SetTextColor (clrText);
		}
		//////////////////////////////////////////////////////////////////////////

		nRes = pDC->DrawText (strName, rectText, uiDTFlags);
    
    // 단축키 정보는 오른쪽 정렬로 그림
    if(isPopup && strAccel.GetLength()>0)
      pDC->DrawText (strAccel, rectText, uiDTFlags | DT_RIGHT);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor (clrTextOld);
	}

	return nRes;
}

void MRibbonButton::OnShowPopupMenu ()
{
  ASSERT_VALID (this);

  CWnd* pWndParent = GetParentWnd ();
  if (pWndParent->GetSafeHwnd () == NULL)
  {
    ASSERT (FALSE);
    return;
  }

  CBCGPRibbonBar* pTopLevelRibbon = GetTopLevelRibbonBar ();
  if (pTopLevelRibbon->GetSafeHwnd () == NULL)
  {
    ASSERT (FALSE);
    return;
  }

  CBCGPBaseRibbonElement::OnShowPopupMenu ();

  const BOOL bIsRTL = (pTopLevelRibbon->GetExStyle () & WS_EX_LAYOUTRTL);

  CWnd* pWndOwner = pTopLevelRibbon->GetTopLevelOwner();

  if (pTopLevelRibbon->GetParentFrame()->GetSafeHwnd() != AfxGetMainWnd()->GetSafeHwnd())
  {
    pWndOwner = pTopLevelRibbon->GetParentFrame();
  }

  if (m_arSubItems.GetSize () > 0)
  {
    if (m_bIsWindowsMenu)
    {
      FillWindowList ();
    }
    
    //--------------------------------
    // Build popup menu from subitems:
    //--------------------------------
    
    // 팝업메뉴에 Accelerator를 추가
    for(int i=0; i<m_arSubItems.GetSize(); i++)
    {
      // MRibbonButton일 경우, 단축키를 m_strText에 추가해준다
      if(m_arSubItems[i]->IsKindOf(RUNTIME_CLASS(MRibbonButton)))
      {
        dynamic_cast<MRibbonButton*>(m_arSubItems[i])->AddAccelToText();
      }
    }

    CBCGPRibbonPanelMenu* pMenu = new CBCGPRibbonPanelMenu
      (pTopLevelRibbon, m_arSubItems);

    // 팝업메뉴에서 Accelerator를 제거
    for(int i=0; i<m_arSubItems.GetSize(); i++)
    {
      if(m_arSubItems[i]->IsKindOf(RUNTIME_CLASS(MRibbonButton)))
      {
        dynamic_cast<MRibbonButton*>(m_arSubItems[i])->RestoreText();
      }
    }

    // 팝업메뉴의 왼쪽 부분에 항상 음영을 그리도록 처리
    pMenu->GetMenuBar()->m_bDisableSideBarInXPMode = FALSE;

    pMenu->SetParentRibbonElement (this);

    pMenu->SetMenuMode ();

    BOOL bIsPopupDefaultMenuLook = IsPopupDefaultMenuLook ();

    for (int i = 0; bIsPopupDefaultMenuLook && i < m_arSubItems.GetSize (); i++)
    {
      ASSERT_VALID (m_arSubItems [i]);

      if (!m_arSubItems [i]->IsDefaultMenuLook ())
      {
        bIsPopupDefaultMenuLook = FALSE;
      }
    }

    pMenu->SetDefaultMenuLook (bIsPopupDefaultMenuLook);

    if (m_pOriginal != NULL && m_pOriginal->GetParentPanel () != NULL &&
      m_pOriginal->GetParentPanel ()->IsMainPanel ())
    {
      pMenu->SetDefaultMenuLook (FALSE);
    }

    CRect rectBtn = GetRect ();
    pWndParent->ClientToScreen (&rectBtn);

    int x = m_bRightAlignMenu || bIsRTL ? rectBtn.right : rectBtn.left;

    int y = rectBtn.bottom;

    if (m_bCreatedFromMenu && m_bRightAlignMenu && !bIsRTL)
    {
      pMenu->SetRightAlign ();
    }

    if (IsMenuMode ())
    {
      x = bIsRTL ? rectBtn.left : rectBtn.right;
      y = rectBtn.top;
    }

    CRect rectMenuLocation;
    rectMenuLocation.SetRectEmpty ();

    CBCGPRibbonPanel* pPanel = GetParentPanel ();

    if (pPanel != NULL && 
      pPanel->GetPreferedMenuLocation (rectMenuLocation))
    {
      pWndParent->ClientToScreen (&rectMenuLocation);

      x = bIsRTL ? rectMenuLocation.right : rectMenuLocation.left;
      y = rectMenuLocation.top;

      pMenu->SetPreferedSize (rectMenuLocation.Size ());
      pMenu->SetDefaultMenuLook (FALSE);
    }

    pMenu->Create (pWndOwner, x, y, (HMENU) NULL);

    SetDroppedDown (pMenu);
    return;
  }

  HMENU hPopupMenu = GetMenu ();
  if (hPopupMenu == NULL)
  {
    return;
  }

  CRect rectBtn = GetRect ();
  pWndParent->ClientToScreen (&rectBtn);

  CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;

  pPopupMenu->SetAutoDestroy (FALSE);
  pPopupMenu->SetRightAlign (m_bRightAlignMenu && !bIsRTL);

  pPopupMenu->SetParentRibbonElement (this);

  CBCGPPopupMenu* pMenuActive = CBCGPPopupMenu::GetActiveMenu ();
  if (pMenuActive != NULL &&
    pMenuActive->GetSafeHwnd () != pWndParent->GetParent ()->GetSafeHwnd ())
  {
    pMenuActive->SendMessage (WM_CLOSE);
  }

  int x = m_bRightAlignMenu || bIsRTL ? rectBtn.right : rectBtn.left;
  int y = rectBtn.bottom;

  pPopupMenu->Create (pWndOwner, x, y, hPopupMenu, FALSE);

  SetDroppedDown (pPopupMenu);
}


void MRibbonButton::CopyFrom(const CBCGPBaseRibbonElement& src)
{
  CBCGPRibbonButton::CopyFrom(src);
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// class MToolBarMenuButton
MToolBarMenuButton::MToolBarMenuButton()
: CBCGPToolbarMenuButton()
{

}

MToolBarMenuButton::MToolBarMenuButton(const MToolBarMenuButton& src)
{
	m_nID = src.m_nID;
	m_nStyle = src.m_nStyle;
	m_bUserButton = src.m_bUserButton;

	SetImage(src.GetImage());
	m_strText = src.m_strText;
	m_bDragFromCollection = FALSE;
	m_bText = src.m_bText;
	m_bImage = src.m_bImage;
	m_bDrawDownArrow = src.m_bDrawDownArrow;
	m_bMenuMode = src.m_bMenuMode;
	m_bDefault = src.m_bDefault;
	m_bMenuOnly = src.m_bMenuOnly;
	m_bIsRadio = src.m_bIsRadio;

	SetTearOff(src.m_uiTearOffBarID);

	HMENU hmenu = src.CreateMenu();
	ENSURE(hmenu != NULL);

	CreateFromMenu(hmenu);
	::DestroyMenu(hmenu);

	m_rect.SetRectEmpty();

	m_pPopupMenu = NULL;
	m_pWndParent = NULL;

	m_bClickedOnMenu = FALSE;
	m_bHorz = TRUE;

	m_bMenuPaletteMode = src.m_bMenuPaletteMode;
	m_nPaletteRows = src.m_nPaletteRows;
	m_bQuickCustomMode = src.m_bQuickCustomMode;
	m_bShowAtRightSide = src.m_bShowAtRightSide;
}

MToolBarMenuButton::MToolBarMenuButton(UINT uiID, HMENU hMenu, int iImage, LPCTSTR lpszText, BOOL bUserButton)
: CBCGPToolbarMenuButton( uiID, hMenu, iImage, lpszText, bUserButton )
{

}

MToolBarMenuButton::~MToolBarMenuButton()
{

}
