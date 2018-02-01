#pragma once

#include "BCGPRibbonBar.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MRibbonMainButton : public CBCGPRibbonMainButton
		{
			friend class MVisualManager;

			DECLARE_DYNCREATE(MRibbonMainButton)
		public:
			MRibbonMainButton();
			virtual ~MRibbonMainButton();

		protected:
			virtual void OnShowPopupMenu ();

		protected:
			virtual BOOL OnKey (BOOL bIsMenuKey);
			virtual void OnLButtonDown (CPoint point);
		};
	}
}

#include "HeaderPost.h"
