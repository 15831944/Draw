#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// CBCGPTabInfo 에 있는 protected 멤버 접근용
		class __MY_EXT_CLASS__ CMITTabInfo : public CBCGPTabInfo
		{
			friend class MLayeredTabWnd;
		};

		class __MY_EXT_CLASS__ MLayeredTabWnd : public CBCGPTabWnd
		{
			DECLARE_DYNCREATE(MLayeredTabWnd)
		public:
			MLayeredTabWnd(void);
			~MLayeredTabWnd(void);

		protected:
			virtual void AdjustTabs();

		public:
			virtual void RecalcLayout();
			virtual void OnDraw(CDC* pDC);
			virtual void Draw3DTab(CDC* pDC, CBCGPTabInfo* pTab, BOOL bActive);

		protected:
			BOOL        m_bTrack;

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg void OnMouseLeave();
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		};
	}
}

#include "HeaderPost.h"

