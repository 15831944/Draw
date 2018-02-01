#pragma once

#include "ITBProgressCtrl.h"
#include "MProgressCtrl.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTable;
		class __MY_EXT_CLASS__ MTBProgressCtrl : public CBCGPWnd, public ITBProgressCtrl
		{
			DECLARE_DYNAMIC(MTBProgressCtrl)
		public:
			MTBProgressCtrl();
			virtual ~MTBProgressCtrl();

			// Table
		private:
			MTable* m_pTable;
		protected:
			MTable* GetTable() const { ASSERT(m_pTable); return m_pTable; }

		public:
			virtual BOOL Create(DWORD dwStyle, const RECT& rect, MTable* pTable, UINT nID);
						
		protected:
			Align m_align;
			BOOL m_bShow;
			BOOL m_bShowCancelBtn;
			int m_nThickness;
			int m_nCancelBtnLength;
			MProgressCtrl m_wndProgressBar;
			CBCGPButton m_wndCancelBtn;

			// ITBProgressCtrl Impl - Progress
		public:
			virtual void Show(BOOL bShow, BOOL bShowCancelBtn = FALSE);
			virtual void SetText(const CString& strText) { ASSERT(m_wndProgressBar.GetSafeHwnd()); m_wndProgressBar.SetWindowText(strText); }
			virtual void SetRange(int nLower, int nUpper) { ASSERT(m_wndProgressBar.GetSafeHwnd()); m_wndProgressBar.SetRange32(nLower, nUpper); }
			virtual void SetPos(int nPos) { ASSERT(m_wndProgressBar.GetSafeHwnd()); m_wndProgressBar.SetPos(nPos); }

			// ITBProgressCtrl Impl - CancelBtn
		public:
			virtual HWND GetCancelBtn() const { return m_wndCancelBtn.GetSafeHwnd(); }

			// ITBProgressCtrl Impl - Layout
		public:
			virtual void SetAlign(Align align);
			virtual void AdjustLayout(const CRect& rect, CRect& rectProgress);

		protected:
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"