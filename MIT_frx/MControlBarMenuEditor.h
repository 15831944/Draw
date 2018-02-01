#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MControlBarMenuEditor
		{
		protected:
			MControlBarMenuEditor()
			{
				s_instance = this;
			}

		private:
			static MControlBarMenuEditor* s_instance;

		public:
			static MControlBarMenuEditor* GetInstance()
			{
				if (!s_instance)
				{
					static MControlBarMenuEditor instance;
					ASSERT(s_instance);
				}
				return s_instance;
			}

		public:
			virtual BOOL EditMenu(CMenu& menu);
			virtual BOOL GetTooltipString(UINT nTooltipResID, CString& strTipText);

		protected:
			BOOL ModifyMenuString(CMenu& menu, UINT id, const CString strItem);

		protected:
			virtual BOOL GetFloatingString(CString& strItem) { return FALSE; }
			virtual BOOL GetDockingString(CString& strItem) { return FALSE; }
			virtual BOOL GetTabbedString(CString& strItem) { return FALSE; }
			virtual BOOL GetAutoHideString(CString& strItem) { return FALSE; }
			virtual BOOL GetHideString(CString& strItem) { return FALSE; }

		protected:
			virtual BOOL GetCloseBarString(CString& strTipText) { return FALSE; }
			virtual BOOL GetAutoHideBarString(CString& strTipText) { return FALSE; }
			virtual BOOL GetAutoHideAllString(CString& strTipText) { return FALSE; }
			virtual BOOL GetMenuString(CString& strTipText) { return FALSE; }
		};
	}
}

#include "HeaderPost.h"
