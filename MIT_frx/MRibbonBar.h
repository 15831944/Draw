#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"
namespace mit
{
	namespace frx
	{
		class MFrameBase;
		class MRibbonCategory;
		class MRibbonButtonsGroup;
		class __MY_EXT_CLASS__ MRibbonBar : public CBCGPRibbonBar
		{
			friend class MFrameBase;
			friend class MRibbonCategory;

		public:
			MRibbonBar();
			virtual ~MRibbonBar();
			// Operations
		public:
			virtual void RecalcLayout();
			virtual CBCGPBaseRibbonElement* HitTest(CPoint point, BOOL bCheckActiveCategory = FALSE, BOOL bCheckPanelCaption = FALSE);

		protected:
			virtual void CreateTitleBarMenu() { ASSERT(0); };

		protected:
			virtual void OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

		public:
			MRibbonButtonsGroup* GetTitleBarMenu() { return m_pTitleBarMenu; }
			void SetTitleBarMenu( MRibbonButtonsGroup* pGroup ) { m_pTitleBarMenu = pGroup; }

			MRibbonCategory* AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
				CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);
			MRibbonCategory* AddContextCategory(LPCTSTR lpszName, LPCTSTR lpszContextName, UINT uiContextID, BCGPRibbonCategoryColor clrContext,
				UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);
			MRibbonCategory* AddQATOnlyCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, CSize sizeSmallImage = CSize(16, 16));
      UINT GetMenuIDFromText(MRibbonBar* pRibbonBar, CString strCategory, CString strPanel, CString strElem1, CString strElem2, CString strElem3);
      CString MakeFilteredText(CString str);

		protected:
			MRibbonButtonsGroup* m_pTitleBarMenu;

		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg void OnPaint();
		};
	}
}

#include "HeaderPost.h"
