#pragma once

#include "BCGPVisualManager2007.h"
#include <vector>
#include <algorithm>

#include "HeaderPre.h"

class CBCGPTagManager;

namespace mit
{
	namespace frx
	{
		class MCoolButton;
		class MLayeredSliderCtrl;

		class __MY_EXT_CLASS__ MBitmapCache
		{
		public:
			class __MY_EXT_CLASS__ MBitmapCacheItem
			{
			public:

				MBitmapCacheItem();
				virtual ~MBitmapCacheItem();

				void AddImage (HBITMAP hBmp);
				void Cache (const CSize& size, CBCGPControlRenderer& renderer);

				void Draw (CDC* pDC, CRect rect, int iImageIndex = 0, BYTE alphaSrc = 255);
				void DrawY (CDC* pDC, CRect rect, CSize sides, int iImageIndex = 0, BYTE alphaSrc = 255);

			protected:
				CBCGPToolBarImages m_Images;
				BOOL m_bMirror;
			};

			typedef CArray<MBitmapCacheItem*, MBitmapCacheItem*> XCache;
			typedef CArray<CSize, CSize> XSizes;

		public:

			MBitmapCache();
			virtual ~MBitmapCache();

			void Clear ();

			int Cache (const CSize& size, CBCGPControlRenderer& renderer);
			int CacheY (int height, CBCGPControlRenderer& renderer);
			BOOL IsCached (const CSize& size) const;

			int FindIndex (const CSize& size) const;

			MBitmapCacheItem* Get (const CSize& size);
			MBitmapCacheItem* Get (int nIndex);

		protected:
			XCache	m_Cache;
			XSizes  m_Sizes;
		};



		class __MY_EXT_CLASS__ MVisualManager : public CBCGPVisualManager2007  
		{
			DECLARE_DYNCREATE(MVisualManager)

		protected:
			MVisualManager();
			virtual ~MVisualManager();

		public:
			virtual void CleanUp ();

		public:
			virtual BOOL OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw);
			virtual BOOL OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow);
			virtual void OnDrawDlgSizeBox (CDC* pDC, CWnd* pDlg, CRect rectSizeBox);

			// Tab 버튼 달기 위해서... 이종협 
			virtual void OnDrawTab (CDC* pDC, CRect rectTab,
				int iTab, BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd);

			virtual void OnDrawTabContent (CDC* pDC, CRect rectTab,
				int iTab, BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd,
				COLORREF clrText);

			// For Tree
			virtual COLORREF GetTreeBKColor();
			virtual COLORREF GetTreeTextColor();
			virtual COLORREF GetTreeGridColor();
			virtual COLORREF GetTreeDisabledColor();
			virtual COLORREF GetTreeStatusColor();
			virtual COLORREF GetTreeGrayTextColor();
			virtual COLORREF GetTreeHightLightColor();
			virtual COLORREF GetTreeHightLightTextColor();
			virtual DWORD	 GetTreeDCRop();			

			// Tree Extend Button 
			virtual COLORREF GetTreeExtButtonTextColor();
			virtual COLORREF GetTreeExtButtonDescriptionTextColor();
			virtual BOOL HasExpandingBoxImage() { return FALSE; }
			
			// Chart 
			virtual void OnDrawChartAreaEmptyStatus( CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea );

			//////////////////////////////////////////////////////////////////////////
			// MLayeredSliderCtrl 용으로 별도 생성.
			virtual void OnDrawRibbonSliderZoomButton (
				CDC* pDC, 
				CRect rect, BOOL bIsZoomOut, 
				BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled);

			virtual void OnDrawRibbonSliderChannel (
				CDC* pDC, mit::frx::MLayeredSliderCtrl* pSlider, 
				CRect rect);

			virtual void OnDrawRibbonSliderThumb (
				CDC* pDC, mit::frx::MLayeredSliderCtrl* pSlider, 
				CRect rect, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled);
			//////////////////////////////////////////////////////////////////////////

			// Push button: 이종협
			virtual BOOL OnDrawPushButton (CDC* pDC, CRect rect, CBCGPButton* pButton, COLORREF& clrText);

			virtual BOOL IsEnableMDITabButton() { return (m_pTabButton!=NULL) ? TRUE : FALSE; }

			// Main Button
			virtual void OnDrawRibbonMainButton (
				CDC* pDC, 
				CBCGPRibbonButton* pButton);

			virtual HBITMAP GetRibbonMainBtnIcon();

			virtual void OnAfterQATChangeRect(CBCGPRibbonQuickAccessToolbar* pQAT);

		protected:
			// Enable Tab Button 이종협
			BOOL					m_bEnableMDITabButton;
			UINT					m_uiTabButtonID;

			// MDI Tab 버튼
			BOOL						m_bRedrawMDITabButton;
			CRect						m_rectLastTabButton;
			CButton*					m_pTabButton;
			std::vector<CRuntimeClass*> m_svEnableTabButtonViews;

			// Ribbon
			MBitmapCache		m_cacheRibbonBtnGroup_S;
			MBitmapCache		m_cacheRibbonBtnGroup_F;
			MBitmapCache		m_cacheRibbonBtnGroup_M;
			MBitmapCache		m_cacheRibbonBtnGroup_L;
			mit::frx::MBitmapCache		m_cacheRibbonBtnGroupMenu_F[2];
			mit::frx::MBitmapCache		m_cacheRibbonBtnGroupMenu_M[2];
			mit::frx::MBitmapCache		m_cacheRibbonBtnGroupMenu_L[2];

			CBCGPToolBarImages	m_RibbonBtnMainIcon;

		public:
			const CButton*  GetMDITabButton() { return m_pTabButton; }
			void EnableMDITabButton(CButton* pTabButton, UINT uiResID, std::vector<CRuntimeClass*>& svEableViews);
			BOOL IsEnableMDITabButtonView();
			void SetRedrawMDITabButton(BOOL bRedraw = TRUE){ m_bRedrawMDITabButton = bRedraw; }			


		protected:
			virtual BOOL ParseStyleXMLVersion (const CString& strItem);
			virtual BOOL ParseStyleXMLRibbon (const CString& strItem);
		};
	}
}

#include "headerPost.h"