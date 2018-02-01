#pragma once

#include "BCGPAutoHideButton.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MAutoHideButton : public CBCGPAutoHideButton
		{
			DECLARE_DYNCREATE(MAutoHideButton)
		public:
			MAutoHideButton() {}
			virtual ~MAutoHideButton() {}

		public:
			CSize GetSize (BOOL bIgnoreOthersInRow = FALSE) const;

		public:
			virtual BOOL Create (CBCGPAutoHideToolBar* pParentBar, 
				CBCGPDockingControlBar* pAutoHideWnd, DWORD dwAlignment);
			virtual void OnDraw (CDC* pDC);
		};
	}
}

#include "HeaderPost.h"
