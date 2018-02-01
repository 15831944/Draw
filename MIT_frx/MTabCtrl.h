#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTabCtrl : public CTabCtrl
		{
			DECLARE_DYNCREATE(MTabCtrl)
		public:
			MTabCtrl(void);
			virtual ~MTabCtrl(void);

		public:
			void SetBkgndColor(COLORREF color);

		protected:
			CSize FormatText(CString& sText, CDC* pDC, int nWidth);

		protected:
			COLORREF  m_clrBackground;

		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnPaint();			
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);

		protected:
			virtual void DrawMainBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
			virtual void DrawItemBorder(LPDRAWITEMSTRUCT lpDrawItemStruct);
			virtual COLORREF GetTabColor(BOOL bSelected = FALSE);
			virtual COLORREF GetTabTextColor(BOOL bSelected = FALSE);
			virtual void PreSubclassWindow();
		};
	}
}

#include "HeaderPost.h"