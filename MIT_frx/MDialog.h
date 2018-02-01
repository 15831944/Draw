#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MDialog : public CDialog
		{
			DECLARE_DYNAMIC(MDialog)

			// Construction
		public:
			MDialog();
			MDialog(UINT nIDTemplate, CWnd *pParent= NULL);
			virtual ~MDialog();

		protected:
			void Initialize();

			// Attributes:
		public:
			// Visualization:
			void EnableVisualManagerStyle (BOOL bEnable = TRUE, BOOL bNCArea = FALSE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);
			BOOL IsVisualManagerStyle () const;
			BOOL IsVisualManagerNCArea () const;
			BOOL IsBackstageMode() const;

			enum EN_BACKGR_Location
			{
				BACKGR_TILE,
				BACKGR_TOPLEFT,
				BACKGR_TOPRIGHT,
				BACKGR_BOTTOMLEFT,
				BACKGR_BOTTOMRIGHT,
			};

			BOOL EnableAero (int cxLeftWidth, int cxRightWidth, int cyTopHeight, int cyBottomHeight);
			void GetAeroMargins (int& cxLeftWidth, int& cxRightWidth, int& cyTopHeight, int& cyBottomHeight) const;
			BOOL HasAeroMargins () const;

			// Layout:
			void EnableLayout(BOOL bEnable = TRUE, CRuntimeClass* pRTC = NULL, BOOL bResizeBox = TRUE);
			BOOL IsLayoutEnabled() const;

			virtual void AdjustControlsLayout();

			void UpdateCaptionButtons ();
			void EnableLoadWindowPlacement(BOOL bEnable = TRUE);
			BOOL IsWindowPlacementEnabled() const;

		protected:
			HBITMAP				m_hBkgrBitmap;
			CSize				m_sizeBkgrBitmap;
			CBrush				m_brBkgr;
			EN_BACKGR_Location	m_BkgrLocation;
			BOOL				m_bAutoDestroyBmp;
			BOOL				m_bWasMaximized;
			BOOL				m_bIsLocal;

			void*				m_pImpl;
			CList<UINT,UINT>    m_lstNonSubclassedItems;

			// Operations:
		public:
			void SetBackgroundColor (COLORREF color, BOOL bRepaint = TRUE);
			void SetBackgroundImage (HBITMAP hBitmap, 
				EN_BACKGR_Location location = BACKGR_TILE,
				BOOL bAutoDestroy = TRUE,
				BOOL bRepaint = TRUE);
			BOOL SetBackgroundImage (UINT uiBmpResId,
				EN_BACKGR_Location location = BACKGR_TILE,
				BOOL bRepaint = TRUE);

			// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(MDialog)
		public:
			virtual BOOL PreTranslateMessage(MSG* pMsg);

		protected:
			virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
			//}}AFX_VIRTUAL

			virtual void OnOK()
			{
				if (!IsBackstageMode())
				{
					CDialog::OnOK();
				}
			}

			virtual void OnCancel()
			{
				if (!IsBackstageMode())
				{
					CDialog::OnCancel();
				}
				else
				{
					CWnd* pParent = GetParent();
					if (pParent->GetSafeHwnd() != NULL)
					{
						pParent->SendMessage(WM_CLOSE);
					}
				}
			}

			// Implementation
		protected:

			//{{AFX_MSG(MDialog)
			afx_msg void OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized);
			afx_msg BOOL OnNcActivate(BOOL bActive);
			afx_msg void OnEnable(BOOL bEnable);
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			afx_msg void OnDestroy();
			afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
			afx_msg void OnSysColorChange();
			afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
			virtual BOOL OnInitDialog();
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnNcPaint();
			afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			afx_msg LRESULT OnNcHitTest(CPoint point);
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
			afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
			//}}AFX_MSG
			afx_msg LRESULT OnDWMCompositionChanged(WPARAM,LPARAM);
			afx_msg LRESULT OnChangeVisualManager (WPARAM, LPARAM);
			afx_msg LRESULT OnSetText(WPARAM, LPARAM);
			afx_msg LRESULT OnPowerBroadcast(WPARAM wp, LPARAM);
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"