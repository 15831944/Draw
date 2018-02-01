#pragma once

#include "MGridItem.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MGridButtonItem : public MGridItem
		{
			DECLARE_SERIAL(MGridButtonItem)

		public:
			MGridButtonItem();
			MGridButtonItem(UINT id);

		protected:
			UINT m_id;
			BOOL m_bPressed;

		public:
			static MGridButtonItem* s_pHighlightedItem;
			
		protected:
			virtual CWnd* CreateInPlaceEdit(CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
			{
				return NULL;
			}

			virtual BOOL OnSetCursor() const
			{
				return FALSE; /* Use default */	
			}

			virtual void OnDrawValue(CDC* pDC, CRect rect);
			virtual BOOL OnClickValue(UINT uiMsg, CPoint point);

		};
	}
}

#include "HeaderPost.h"