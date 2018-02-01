#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MLayeredProp;
		class __MY_EXT_CLASS__ MLayeredPropList : public CBCGPPropList
		{
			DECLARE_DYNAMIC(MLayeredPropList)

		public:
			MLayeredPropList(void);
			virtual ~MLayeredPropList(void);

		protected:
			BOOL        m_bTrack;

		public:
			void MakeTransparent(BOOL bMake);
			mit::frx::MLayeredProp* GetProperty (int nIndex) const;

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg LRESULT OnMouseLeave(WPARAM wp,LPARAM lp);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		};
	}
}

#include "HeaderPost.h"
