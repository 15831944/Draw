#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// TODO: �̰� Table ���� �ƴ�. �ű��
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
