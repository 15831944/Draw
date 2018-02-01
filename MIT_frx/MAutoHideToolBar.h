#pragma once

#include "BCGPAutoHideToolBar.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MAutoHideToolBar : public CBCGPAutoHideToolBar
		{
			DECLARE_DYNCREATE(MAutoHideToolBar)
		public:
			MAutoHideToolBar() {}
			virtual ~MAutoHideToolBar() {}

		public:
			virtual CSize StretchControlBar (int nLength, BOOL bVert);
			virtual void PrepareToDock(CBCGPDockBar* pDockBar, BCGP_DOCK_METHOD dockMethod);
		};
	}
}

#include "HeaderPost.h"
