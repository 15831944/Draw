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

		private: // jpahn: CBCGPRibbonPanelMenuBar�� �ִ� �Լ��ε� �������̵��ϱ� ���� ���Ƕ��� ��°�� �Űܹ���
			CSize CalcSize(MRibbonPanelMenuBar* pMenuBar, BOOL bVertDock);
		};
	}
}

#include "HeaderPost.h"
