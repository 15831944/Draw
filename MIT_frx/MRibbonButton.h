#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;
		class MRibbonCategory;
		class MRibbonButtonsGroup;

		class MRibbonPanel : public CBCGPRibbonPanel
		{
			friend class MRibbonBar;
			friend class MRibbonCategory;
			friend class MRibbonConstructor;

		protected:
			MRibbonPanel(LPCTSTR lpszName = NULL, HICON hIcon = NULL, BOOL bAutoDestroyIcon = TRUE);
			MRibbonPanel(CBCGPRibbonPaletteButton* pPaletteButton);
		};

		class MRibbonLaunchButton : public CBCGPRibbonLaunchButton
		{
			friend class MRibbonBar;
			friend class MRibbonCategory;
		};

		class MRibbonDefaultPanelButton : public CBCGPRibbonDefaultPanelButton
		{
			friend class MRibbonBar;
			friend class MRibbonCategory;
		};

		class MRibbonApplicationButton : public CBCGPRibbonMainButton
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;
		};

		class MRibbonEdit : public CBCGPRibbonEdit
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;	
		};

		class MRibbonColorButton : public CBCGPRibbonColorButton
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;	
		};

		class MRibbonComboBox : public CBCGPRibbonComboBox
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;
		public:
			MRibbonComboBox();
			MRibbonComboBox(UINT nID, BOOL bHasEditBox = TRUE, int nWidth = -1, LPCTSTR lpszLabel = NULL, int nImage = -1);
			virtual ~MRibbonComboBox(){}
		};

		class MRibbonFontComboBox : public CBCGPRibbonFontComboBox
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;
		public:
			MRibbonFontComboBox();
			MRibbonFontComboBox(UINT nID, int nFontType = DEVICE_FONTTYPE | RASTER_FONTTYPE | TRUETYPE_FONTTYPE,
				BYTE nCharSet = DEFAULT_CHARSET, BYTE nPitchAndFamily = DEFAULT_PITCH, int nWidth = -1);
			virtual ~MRibbonFontComboBox(){}
		};

		class MRibbonQuickAccessToolBar : public CBCGPRibbonQuickAccessToolbar
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;
		};

		class __MY_EXT_CLASS__ MToolBarMenuButton : public CBCGPToolbarMenuButton
		{
			friend class MRibbonButton;
			friend class MRibbonConstructor;

		public:
			MToolBarMenuButton();
			MToolBarMenuButton(const MToolBarMenuButton& src);
			MToolBarMenuButton(UINT uiID, HMENU hMenu, int iImage, LPCTSTR lpszText = NULL, BOOL bUserButton = FALSE);
			virtual ~MToolBarMenuButton();
		};

		class __MY_EXT_CLASS__ MRibbonButton : public CBCGPRibbonButton
		{	
      DECLARE_DYNCREATE(MRibbonButton)

			friend class MRibbonBar;
			friend class MRibbonPanel;
			friend class MRibbonCategory;
			friend class MRibbonButtonsGroup;
			friend class MRibbonConstructor;

		public:
			MRibbonButton();
			MRibbonButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex = -1, int nLargeImageIndex = -1, BOOL bAlwaysShowDescription = FALSE);
			MRibbonButton(UINT nID, LPCTSTR lpszText, HICON hIcon, BOOL bAlwaysShowDescription = FALSE, HICON hIconSmall = NULL, BOOL bAutoDestroyIcon = FALSE, BOOL bAlphaBlendIcon = FALSE);
			virtual ~MRibbonButton();

		protected:
			virtual void OnDraw(CDC* pDC);
			virtual CSize DrawBottomText(CDC* pDC, BOOL bCalcOnly);

			virtual int DoDrawText (CDC* pDC, const CString& strText, CRect rectText, UINT uiDTFlags,
				COLORREF clrText = (COLORREF)-1);

      virtual void OnShowPopupMenu ();

      virtual void CopyFrom(const CBCGPBaseRibbonElement& src);

    protected:
      void AddAccelToText();
      void RestoreText();
		};
	}
}

#include "HeaderPost.h"