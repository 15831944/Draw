#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MLayeredProp : public CBCGPProp
		{
			DECLARE_DYNAMIC(MLayeredProp)
		public:
			MLayeredProp(const CString& strGroupName, DWORD_PTR dwData = 0,
				BOOL bIsValueList = FALSE);

			// Simple property
			MLayeredProp(const CString& strName, const _variant_t& varValue, 
				LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
				LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
				LPCTSTR lpszValidChars = NULL);

			MLayeredProp(const CString& strName, UINT nID, const _variant_t& varValue, 
				LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
				LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
				LPCTSTR lpszValidChars = NULL);

			virtual ~MLayeredProp(void);

		protected:
			virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
			virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
		};
	}
}

#include "HeaderPost.h"
