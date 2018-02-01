#pragma once

#include "MGridItem.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MGridCheckItem : public MGridItem
		{
			DECLARE_SERIAL(MGridCheckItem)

		public:
			MGridCheckItem();
			virtual ~MGridCheckItem();

			void SetLabel(const CString& strLabel);
			const CString& GetLabel() const
			{
				return m_strCheckLabel;
			}
			MInplaceWnd* GetInPlaceWnd()
			{
				if (!m_pWndInPlace) return NULL;
				ASSERT_VALID(m_pWndInPlace);
				ASSERT(m_pWndInPlace->IsKindOf(RUNTIME_CLASS(MInplaceWnd)));
				return (MInplaceWnd*)m_pWndInPlace;
			}

		private:
			BOOL m_bToggleValue;
		protected:
			BOOL ToggleValue();
		protected:
			virtual void Init();
			virtual void SetFlags();
		public:
			virtual BOOL OnEdit (LPPOINT lptClick);
			virtual BOOL OnEndEdit ();
			virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
			virtual void AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectSpin);
			virtual BOOL OnUpdateValue ();
			virtual void OnDrawValue (CDC* pDC, CRect rect);
			virtual void OnPrintValue (CDC* pDC, CRect rect);
			virtual BOOL PushChar (UINT nChar);
			virtual CString FormatItem ()	{	return _T("");	}
			virtual BOOL OnClickValue (UINT uiMsg, CPoint point);
			virtual BOOL OnDblClick (CPoint point);

			virtual BOOL ReadFromArchive(CArchive& ar, BOOL bTestMode = FALSE);
			virtual void WriteToArchive(CArchive& ar);

			virtual BOOL SetACCData (CWnd* pParent, CBCGPAccessibilityData& data);

		protected:
			CString	m_strCheckLabel;
		};
	}
}

#include "HeaderPost.h"