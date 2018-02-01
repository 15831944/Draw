#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;
		class MRibbonPanel;
		class MRibbonTab;
		class __MY_EXT_CLASS__ MRibbonCategory : public CBCGPRibbonCategory
		{
			friend class MRibbonBar;
			friend class MRibbonTab;
		public:
			MRibbonCategory(void);

			MRibbonCategory(MRibbonBar* pParentRibbonBar, LPCTSTR lpszName, UINT uiSmallImagesResID,
				UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32));

			~MRibbonCategory(void);

		public:
			MRibbonPanel* AddPanel (LPCTSTR lpszPanelName, HICON hIcon = 0,
				CRuntimeClass* pRTI = NULL, BOOL bAutoDestroyIcon = TRUE,
				int nInsertAt = -1);	

		protected:
			virtual void RecalcLayout(CDC* pDC);
		};
	}
}

#include "HeaderPost.h"