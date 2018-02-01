#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ITBMessageCtrl
		{
			// TODO: Type ����ȭ or �뵵 ��üȭ
			// TODO: Message �켱����
		public:
			enum MSG_TYPE
			{
				MT_MESSAGE,		// �Ϲ� �޼���
				MT_VALIDATE,	// Validate
				MT_ERROR,		// ���� (�ַ� �۾� ���н�)
				MT_COMMIT,		// Data �����
				MT_HELP,		// ���� ���� �ȳ� �޼���
				MT_COUNT
			};

			// On/Off
			virtual void MessageOnAll() = 0;
			virtual void MessageOffAll() = 0;
			virtual void MessageOn(MSG_TYPE nMsgType) = 0;
			virtual void MessageOff(MSG_TYPE nMsgType) = 0;

			// Show/Hide
			virtual BOOL IsShowing() = 0;
			virtual void Show(MSG_TYPE nMsgType, const CString& strMessage, ...) = 0;
			virtual void ShowConstant(MSG_TYPE nMsgType, const CString& strMessage, ...) = 0;
			virtual void Hide() = 0;

			// Layout
			virtual void AdjustLayout(const CRect& rect) = 0;

			// Draw
			virtual void OnDraw(CDC* pDC) = 0;
		};
	}
}

#include "HeaderPost.h"
