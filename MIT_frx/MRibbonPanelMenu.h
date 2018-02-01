#pragma once

#include "BCGPRibbonPanelMenu.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MRibbonPanelMenuBar;

		class __MY_EXT_CLASS__ MRibbonPanelMenu : public CBCGPRibbonPanelMenu
		{
			DECLARE_DYNCREATE(MRibbonPanelMenu)

		protected:
			MRibbonPanelMenu() {}
		public:
			MRibbonPanelMenu (CBCGPRibbonPanel* pPanel) : CBCGPRibbonPanelMenu(pPanel) {}

		public:
			virtual ~MRibbonPanelMenu() {}

		protected:
			virtual void RecalcLayout(BOOL bNotify = TRUE);

		private: // jpahn: CBCGPRibbonPanelMenuBar에 있는 함수인데 오버라이딩하기 힘든 조건땜에 통째로 옮겨버림
			CSize CalcSize(MRibbonPanelMenuBar* pMenuBar, BOOL bVertDock);
		};
	}
}

#include "HeaderPost.h"
