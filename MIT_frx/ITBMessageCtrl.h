#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ITBMessageCtrl
		{
			// TODO: Type 세분화 or 용도 구체화
			// TODO: Message 우선순위
		public:
			enum MSG_TYPE
			{
				MT_MESSAGE,		// 일반 메세지
				MT_VALIDATE,	// Validate
				MT_ERROR,		// 에러 (주로 작업 실패시)
				MT_COMMIT,		// Data 변경됨
				MT_HELP,		// 도움말 내지 안내 메세지
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
