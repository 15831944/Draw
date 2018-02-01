#pragma once

#define MIDAS_SDK

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredToolbar : public CBCGPToolBar
		{
			DECLARE_SERIAL(MLayeredToolbar)
		public:
			MLayeredToolbar(void);
			virtual ~MLayeredToolbar(void);

		protected:
			BOOL        m_bTrack;

		public:
			virtual BOOL LoadState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
			virtual BOOL SaveState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

			DECLARE_MESSAGE_MAP()
		public:
			afx_msg LRESULT OnMouseLeave(WPARAM wp,LPARAM lp);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		};
	}
}

#include "HeaderPost.h"

