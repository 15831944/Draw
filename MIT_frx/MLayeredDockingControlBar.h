#pragma once

#define MIDAS_SDK

#include "BCGPDockingControlBar.h"

#include "HeaderPre.h"

class CBCGPMiniFrameWnd;
class CBCGPTabbedControlBar;

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredDockingControlBar : public CBCGPDockingControlBar
		{
			DECLARE_SERIAL(MLayeredDockingControlBar);

		public:
			MLayeredDockingControlBar(void);
			~MLayeredDockingControlBar(void);

		protected:
			BOOL m_bCleanScreenVisible;

		public:
			virtual int GetCaptionHeight () const;

		public:
			int GetAlpha();
			void UpdateFrame(BOOL bActive = TRUE);

		protected:
			virtual BOOL OnBeforeShowControlBarMenu(CMenu& menu);

		public:
			virtual BOOL Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS, DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle, CCreateContext* pContext = NULL);
			virtual BOOL CreateEx(DWORD dwStyleEx, LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS, DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle, CCreateContext* pContext = NULL);
			virtual CBCGPMiniFrameWnd* CreateDefaultMiniframe	 (CRect rectInitial);
			virtual CBCGPTabbedControlBar* CreateTabbedControlBar ();

			virtual BOOL LoadState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
			virtual BOOL SaveState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
			afx_msg void OnNcPaint();
			afx_msg BOOL OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult);
		};

	}
}

#include "HeaderPost.h"
