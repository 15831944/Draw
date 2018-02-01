#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// TODO: 이건 Table 전용 아님. 옮기기
		class __MY_EXT_CLASS__ MProgressCtrl : public CBCGPProgressCtrl
		{
			DECLARE_DYNAMIC(MProgressCtrl)
		protected:
			afx_msg void OnPaint();
			DECLARE_MESSAGE_MAP()
		};
	}
}

#include "HeaderPost.h"
