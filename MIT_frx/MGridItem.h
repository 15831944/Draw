#pragma once

#include <vector>

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// InplaceEdit 필요없는 Item 도
		// OnUpdateValue() 등 동일한 콜스택 타도록 하기 위한 녀석
		class __MY_EXT_CLASS__ MInplaceWnd : public CWnd
		{
			DECLARE_DYNAMIC(MInplaceWnd)
		public:
			_variant_t m_varValue;
		public:
			MInplaceWnd();
			BOOL Create(DWORD dwStyle, CWnd* pParent, UINT nID);
		};

		class __MY_EXT_CLASS__ MGridItem : public CBCGPGridItem
		{
			DECLARE_SERIAL(MGridItem)

			friend class MTable;
			friend class MGridRow;

		public:
			MGridItem(void);
			MGridItem(const _variant_t& varValue, DWORD_PTR dwData = 0,
				LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
				LPCTSTR lpszValidChars = NULL);
			virtual ~MGridItem(void); 

		protected:
			BOOL m_bBold;
			BOOL m_bItalic;
			BOOL m_bUnderline;
			BOOL m_bStrikeOut;
		public:
			BOOL IsBold() { return m_bBold; }
			void SetBold(BOOL bBold=TRUE) { m_bBold = bBold; }
			BOOL IsItalic() { return m_bItalic; }
			void SetItalic(BOOL bItalic=TRUE) { m_bItalic = bItalic; }
			BOOL IsUnderline() { return m_bUnderline; }
			void SetUnderline(BOOL bUnderline=TRUE) { m_bUnderline = bUnderline; }
			BOOL IsStrikeOut() { return m_bStrikeOut; }
			void SetStrikeOut(BOOL bStrikeOut=TRUE) { m_bStrikeOut = bStrikeOut; }

		protected:
			BOOL m_bShowValue;
		public:
			void ShowValue(BOOL bShow);
			
		public:
			CString FloatFormatItem(const _variant_t& var);
			void AppendFloatFormat(CString& strText, const _variant_t& var);

		public:
			virtual COLORREF OnFillBackground (CDC* pDC, CRect rect);
			virtual void OnDrawValue (CDC* pDC, CRect rect);
			virtual CString FormatItem();
			virtual void AppendFormatItem(CString& strText);
			virtual BOOL OnUpdateValue();
			virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);

		protected:
			virtual HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor);
		};
	}
}

#include "HeaderPost.h"