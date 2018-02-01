#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTabbedChildFrame : public CBCGPMDIChildWnd
		{
			DECLARE_DYNCREATE(MTabbedChildFrame)
		public:
			MTabbedChildFrame();
			virtual ~MTabbedChildFrame();

			// Ư���Դϴ�.
		public:
			BOOL IsMaximized() { return m_bWasMaximized; }
			// �۾��Դϴ�.
		public:

			// �������Դϴ�.
			virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
			virtual void ActivateFrame(int nCmdShow);

			// �����Դϴ�.
#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
#endif

			// ������ �޽��� �� �Լ�
		protected:
			afx_msg void OnClose();
			afx_msg void OnDestroy();
			afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
			afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
			afx_msg void OnFilePrint();
			afx_msg void OnFilePrintPreview();
			afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
			afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"
