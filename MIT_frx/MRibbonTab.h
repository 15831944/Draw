#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;

		class __MY_EXT_CLASS__ MRibbonTab : public CBCGPRibbonTab
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;

			MRibbonTab ();

		protected:
			virtual void OnDraw(CDC* pDC);
			virtual void CopyFrom (const CBCGPBaseRibbonElement& src);
		};
	}
}

#include "HeaderPost.h"

