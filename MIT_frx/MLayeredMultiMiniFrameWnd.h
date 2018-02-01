#pragma once

#include "FadeEffect.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MLayeredSliderCtrl;
		class __MY_EXT_CLASS__ MLayeredMultiMiniFrameWnd : public CBCGPMultiMiniFrameWnd, MFadeEffectCtrl
		{
			friend class MVisualManager2007;

			DECLARE_SERIAL(MLayeredMultiMiniFrameWnd)

		public:
			MLayeredMultiMiniFrameWnd(void);
			virtual ~MLayeredMultiMiniFrameWnd(void);

		public:
			void UpdateTransParent(BOOL) {}
			int	 GetAlpha();

		public:
			virtual void RecalcCaptionHeight();
			virtual void OnBarRecalcLayout ();

			virtual BOOL OnBeforeDock ();

			virtual void AddControlBar     (CBCGPBaseControlBar* pWnd);

			virtual BOOL SaveState (LPCTSTR lpszProfileName = NULL, UINT uiID = (UINT) -1);
			virtual BOOL LoadState (LPCTSTR lpszProfileName = NULL, UINT uiID = (UINT) -1);

		protected:
			virtual void SetCaptionButtons (DWORD dwButtons);
			virtual void SetCaptionSlider (CBCGPBaseControlBar* pWnd);
			virtual void OnDrawCaptionButtons (CDC* pDC);

		protected:
			void StartFade(BYTE bAlpha);
			virtual void OnFade(MFadeEffect* pFade);
			BOOL IsMouseOver(const CPoint& pt);
			void UpdateFade();

		protected:
			void ScreenToWindow(LPPOINT lpPoint);

		protected:
			enum { IDT_MOUSE_TRACK  = 1};
			MFadeEffect m_fade;
			CPoint m_ptMouse;
			MLayeredSliderCtrl*	 m_pSlider;
			BOOL        m_bTrack;
			BYTE		m_alpha;
			BOOL		m_bLoadState;

		protected:
			DECLARE_MESSAGE_MAP()
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg void OnTimer(UINT_PTR nIDEvent);
			afx_msg void OnNcPaint();
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
			afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnNcMouseLeave();
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
			afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg LRESULT OnNcHitTest(CPoint point);
		};

	}
}

#include "HeaderPost.h"

