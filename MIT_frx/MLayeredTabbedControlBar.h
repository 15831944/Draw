#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredTabbedControlBar : public CBCGPTabbedControlBar
		{
			friend class MVisualManager;

			DECLARE_SERIAL(MLayeredTabbedControlBar)

		public:
			MLayeredTabbedControlBar(void);
			virtual ~MLayeredTabbedControlBar(void);	

		public:
			virtual BOOL Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS, DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle, CCreateContext* pContext = NULL);
			virtual BOOL CreateEx(DWORD dwStyleEx, LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS, DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle, CCreateContext* pContext = NULL);
			virtual CBCGPMiniFrameWnd* CreateDefaultMiniframe	 (CRect rectInitial);
			virtual CBCGPTabbedControlBar* CreateTabbedControlBar ();

			virtual BOOL LoadState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		};

	}
}

#include "HeaderPost.h"

