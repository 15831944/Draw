#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredComboBoxButton : public CBCGPToolbarComboBoxButton
		{
			DECLARE_DYNAMIC(MLayeredComboBoxButton)
			friend class MLayeredComboBox;

		public:
			MLayeredComboBoxButton(void) {}
			virtual ~MLayeredComboBoxButton() {}
		};

		class __MY_EXT_CLASS__ MLayeredComboBox : public CBCGPComboBox
		{
			DECLARE_DYNAMIC(MLayeredComboBox)
		public:
			MLayeredComboBox(void);
			virtual ~MLayeredComboBox(void);

		protected:
			CBrush m_brush;
			int m_nHeight;
			BOOL m_bTrack;

		public:
			// ComboBox�� SetWindowPos �ص� Height �� ��Ʈ�� ���� �����Ǿ� ������. ��...
			// ��Ʈ�� ������� Height�� ������Ű�� ������ ����.
			// ����: SetHeight() ���� ȣ���ϰ� SetWindowPos() ȣ��
			void SetHeight(int nHeight) { m_nHeight = nHeight; }

			DECLARE_MESSAGE_MAP()
		public:
			virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
			afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
			afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
			afx_msg void OnPaint();
			afx_msg void OnMouseLeave();
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnSetFocus(CWnd* pOldWnd);
		};
	}
}

#include "HeaderPost.h"

