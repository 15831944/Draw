#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;

		class __MY_EXT_CLASS__ MRibbonContextCaption : public CBCGPRibbonContextCaption
		{
			DECLARE_DYNCREATE (MRibbonContextCaption)

			friend class MRibbonBar;
			friend class MRibbonConstructor;

		protected:
			MRibbonContextCaption(LPCTSTR lpszName, UINT uiID, BCGPRibbonCategoryColor clrContext);
			MRibbonContextCaption();
			
		protected:
			virtual void OnDraw (CDC* pDC);

		};
	}
}

#include "HeaderPost.h"

