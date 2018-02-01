#pragma once

#include "ITBMessageCtrl.h"
#include "FadeEffect.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTable;
		class __MY_EXT_CLASS__ MTBMessageCtrl : public CBCGPWnd, public ITBMessageCtrl, public MFadeEffectCtrl
		{
			DECLARE_DYNAMIC(MTBMessageCtrl)
		public:
			MTBMessageCtrl();
			virtual ~MTBMessageCtrl();

		private:
			enum { ID_TIMER_HIDE = 1 };

			// Table
		private:
			MTable* m_pTable;
		protected:
			MTable* GetTable() const { ASSERT(m_pTable); return m_pTable; }

		public:
			virtual BOOL Create(DWORD dwStyle, const RECT& rect, MTable* pTable, UINT nID);

		protected:
			BOOL m_bDrawOnPaint;	// OnPaint 안에서 그릴것인가 / 부모에서 OnDraw 호출할 것인가
			CRect m_rect;
			BOOL m_bShow;
			int m_nHeight;
			int m_nHorizontalPadding;
			int m_nVerticalPadding;
			CString m_strMessage;
			MSG_TYPE m_nMsgType;
			BOOL m_bMultiLine; 
			int m_nHideElapse; 
			int m_nShowFadeStep;
			int m_nHideFadeStep;
			int m_nFastHideFadeStep;
			HFONT m_hFont;
			MFadeEffect m_fade;
			BOOL m_aIsMessageOn[MT_COUNT];
			COLORREF m_aForeColor[MT_COUNT];
			COLORREF m_aBackColor[MT_COUNT];
			
			// ITBMessageCtrl Impl - On/Off
		public:
			virtual void MessageOnAll();
			virtual void MessageOffAll();
			virtual void MessageOn(MSG_TYPE nMsgType);
			virtual void MessageOff(MSG_TYPE nMsgType);

			// ITBMessageCtrl Impl - Show/Hide
		protected:
			void Show(MSG_TYPE nMsgType, int nElapse, const CString& strMessage, va_list args);
			void Hide(int nStep);
		public:
			virtual BOOL IsShowing() { return m_bShow || m_fade.IsFading(); }
			virtual void Show(MSG_TYPE nMsgType, const CString& strMessage, ...);
			virtual void ShowConstant(MSG_TYPE nMsgType, const CString& strMessage, ...);
			virtual void Hide();

			// ITBMessageCtrl Impl - Layout
		protected:
			UINT GetDrawTextFormat();
			void CalcHeight(int nWidth);
			void CalcPadding();
		public:
			virtual void AdjustLayout(const CRect& rect);

			// ITBMessageCtrl Impl - Draw
		protected:
			virtual void OnDraw(CDC* pDC, const CRect& rect);
		public:
			virtual void OnDraw(CDC* pDC);

			// MFadeEffectCtrl Impl
		protected:
			virtual void OnFade(MFadeEffect* pFade);

		protected:
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnDestroy();
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			afx_msg void OnPaint();
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			afx_msg void OnTimer(UINT_PTR nIDEvent);
			afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"