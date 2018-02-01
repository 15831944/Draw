#include "StdAfx.h"
#include "MLayeredProp.h"
#include "MLayeredComboBox.h"
#include "MLayeredEdit.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredProp, CBCGPProp)
MLayeredProp::MLayeredProp(const CString& strName, const _variant_t& varValue, 
				   LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask,
				   LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars) :
	CBCGPProp(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{
	
}
//******************************************************************************************
MLayeredProp::MLayeredProp(const CString& strName, UINT nID, const _variant_t& varValue, 
				   LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask,
				   LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars) :
	CBCGPProp(strName, nID, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{
	
}
//******************************************************************************************
MLayeredProp::MLayeredProp(const CString& strGroupName, DWORD_PTR dwData,
					 BOOL bIsValueList) :
	CBCGPProp(strGroupName, dwData, bIsValueList)
{
	
}

MLayeredProp::~MLayeredProp(void)
{
}

CComboBox* MLayeredProp::CreateCombo (CWnd* pWndParent, CRect rect)
{
	ASSERT_VALID (this);

	rect.bottom = rect.top + 400;

	MLayeredComboBox* pWndCombo = new MLayeredComboBox;
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL, 
		rect, pWndParent, BCGPROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}

	return pWndCombo;
}

CWnd* MLayeredProp::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	if (NoInplaceEdit())
	{
		return NULL;
	}

	switch (m_varValue.vt)
	{
	case VT_BSTR:
	case VT_R4:
	case VT_R8:
	case VT_UI1:
	case VT_I2:
	case VT_INT:
	case VT_UINT:
	case VT_I4:
	case VT_UI2:
	case VT_UI4:
	case VT_BOOL:
		break;

	default:
		if (!m_bIsValueList)
		{
			return NULL;
		}
	}

	CEdit* pWndEdit = NULL;

	if (!m_strEditMask.IsEmpty () || !m_strEditTempl.IsEmpty () ||
		!m_strValidChars.IsEmpty ())
	{
		CBCGPMaskEdit* pWndEditMask = new CBCGPMaskEdit;
		pWndEditMask->EnableSetMaskedCharsOnly (FALSE);
		pWndEditMask->EnableGetMaskedCharsOnly (FALSE);

		if (!m_strEditMask.IsEmpty () && !m_strEditTempl.IsEmpty ())
		{
			pWndEditMask->EnableMask (m_strEditMask, m_strEditTempl, _T(' '));
		}

		if (!m_strValidChars.IsEmpty ())
		{
			pWndEditMask->SetValidChars (m_strValidChars);
		}

		pWndEdit = pWndEditMask;
	}
	else
	{
		pWndEdit = new MLayeredEdit;
	}

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL;

	if (!m_bEnabled || !m_bAllowEdit)
	{
		dwStyle |= ES_READONLY;
	}

	pWndEdit->Create (dwStyle, rectEdit, m_pWndList, BCGPROPLIST_ID_INPLACE);

	bDefaultFormat = TRUE;
	return pWndEdit;
}
