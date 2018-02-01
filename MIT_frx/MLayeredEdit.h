#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredEdit : public CEdit
		{
			DECLARE_DYNAMIC(MLayeredEdit)
		public:
			MLayeredEdit(void);
			virtual ~MLayeredEdit(void);

		protected:
			BOOL        m_bTrack;

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg void OnMouseLeave();
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		};
	}
}

#include "HeaderPost.h"
