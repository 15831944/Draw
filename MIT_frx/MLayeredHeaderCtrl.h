#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredHeaderCtrl : public CBCGPHeaderCtrl
		{
			DECLARE_DYNAMIC(MLayeredHeaderCtrl)
		public:
			MLayeredHeaderCtrl(void);
			virtual ~MLayeredHeaderCtrl(void);

		protected:
			BOOL        m_bTrack;

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg LRESULT OnMouseLeave(WPARAM wp, LPARAM lp);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		};

	}
}

#include "HeaderPost.h"
