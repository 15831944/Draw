#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;

		class __MY_EXT_CLASS__ MRibbonCaptionButton : public CBCGPRibbonCaptionButton
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;

			MRibbonCaptionButton();
			virtual ~MRibbonCaptionButton();
		};
	}
}

#include "HeaderPost.h"

