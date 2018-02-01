#pragma once

#include "BCGPRibbonMainPanel.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MRibbonRecentFilesList : public CBCGPRibbonRecentFilesList
		{
			DECLARE_DYNCREATE(MRibbonRecentFilesList)

		public:
			MRibbonRecentFilesList(LPCTSTR lpszLabel = NULL, BOOL bShowPins = FALSE)
				: CBCGPRibbonRecentFilesList(lpszLabel, bShowPins) {}
			virtual ~MRibbonRecentFilesList() {}

		public:
			virtual void OnAfterChangeRect (CDC* pDC);
			virtual CSize GetRegularSize (CDC* pDC);

		protected:
			virtual void OnDraw (CDC* pDC);
		};


		class __MY_EXT_CLASS__ MRibbonMainPanel : public CBCGPRibbonMainPanel
		{
			DECLARE_DYNCREATE(MRibbonMainPanel)

			friend class MRibbonMainButton;

		public:
			MRibbonMainPanel() {}
			virtual ~MRibbonMainPanel() {}

		public:
			void AddMRecentFilesList (LPCTSTR lpszLabel, int nWidth = 300, BOOL bShowPins = FALSE);

		protected:
			virtual void Repos (CDC* pDC, const CRect& rect);
		};
	}
}

#include "HeaderPost.h"
