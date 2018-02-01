#pragma once

#include "MLayeredPropList.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MPropList : public mit::frx::MLayeredPropList
		{
			DECLARE_DYNAMIC(MPropList)

		public:
			MPropList(void);
			virtual ~MPropList(void);

		public:
			virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
			virtual void SetupToolbar(BOOL bShowStandardButtons = TRUE, BOOL bToolbarCustomButton = FALSE, UINT uiToolbarID = 0, UINT uiBitmapID = 0);
			virtual void SetupMenuButton();

			virtual void OnPropertyChanged (CBCGPProp* pProp) const;
			virtual void OnPropertyClickButton (CBCGPProp* pProp, CPoint point) const;

		protected:
			virtual BOOL CreatePropItems() = 0;

		protected:
			int		m_nValueAlign;

		public:
			int GetValueAlign() { return m_nValueAlign; }
			void SetValueAlign(int nValueAlign, BOOL bRedraw = TRUE);
		};
	}
}

#include "HeaderPost.h"