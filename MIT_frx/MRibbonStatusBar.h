#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MRibbonStatusBar
		{
		public:
			MRibbonStatusBar(void);
			virtual ~MRibbonStatusBar(void);

			BOOL Create(CWnd* pParentWnd,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
				UINT nID = AFX_IDW_STATUS_BAR);
			BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = 0,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
				UINT nID = AFX_IDW_STATUS_BAR);

			virtual BOOL LoadFromXML (LPCTSTR lpszXMLResID);
			virtual BOOL LoadFromBuffer (LPCTSTR lpszXMLBuffer);

		protected:
			CWnd* m_pWnd;
		};
	}
}

#include "headerPost.h"