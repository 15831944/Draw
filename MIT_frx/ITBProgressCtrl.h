#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ITBProgressCtrl
		{
		public:
			// Progress
			virtual void Show(BOOL bShow, BOOL bShowCancelBtn = FALSE) = 0;
			virtual void SetText(const CString& strText) = 0;
			virtual void SetRange(int nLower, int nUpper) = 0;
			virtual void SetPos(int nPos) = 0;

			// CancelBtn
			virtual HWND GetCancelBtn() const = 0;

			// Layout
			enum Align { PCA_LEFT, PCA_TOP, PCA_RIGHT, PCA_BOTTOM, PCA_CENTER };
			virtual void SetAlign(Align align) = 0;
			virtual void AdjustLayout(const CRect& rect, CRect& rectProgress) = 0;
		};
	}
}

#include "HeaderPost.h"
