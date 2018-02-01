#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonBar;

		class __MY_EXT_CLASS__ MRibbonButtonsGroup : public CBCGPRibbonButtonsGroup
		{
			friend class MRibbonBar;
			friend class MRibbonConstructor;

		public:
			MRibbonButtonsGroup();
			virtual ~MRibbonButtonsGroup();
		};
	}
}

#include "HeaderPost.h"

