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

			// 특성입니다.
		public:
			BOOL IsMaximized() { return m_bWasMaximized; }
			// 작업입니다.
		public:

			// 재정의입니다.
			virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
			virtual void ActivateFrame(int nCmdShow);

			// 구현입니다.
#ifdef _DEBUG
			virtual void AssertValid() const;
			virtual void Dump(CDumpContext& dc) const;
#endif

			// 생성된 메시지 맵 함수
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
