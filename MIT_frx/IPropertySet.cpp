#include "StdAfx.h"
#include "IPropertySet.h"
//#include "MFrameBase.h"
//#include "MDocBase.h"
#include "MPropertiesWnd.h"
//#include "../MIT_lib/PL_StrParser.h"

// 일단 빌드에러만 안나게 만들어서 추가한 것임. 
// 나중에 소스 옮길 때 이 파일은 덮어쓰면 안됨. 

using namespace mit;
using namespace mit::lib;
using namespace mit::frx;

IPropertySet::IPropertySet( mit::frx::MDocBase* pDoc, MIterator itr, USHORT usDataType )
: /*m_pDoc( pDoc ),*/ m_itr( itr ), m_usDataType( usDataType )
{
	//ASSERT( m_pDoc );
	m_pPropWnd = GetPropWnd();
	ASSERT( m_pPropWnd );
	m_pPropWnd->SetPropertySet( this );
}

IPropertySet::~IPropertySet()
{
	RemoveAllProperties();
}

const CDocument* IPropertySet::GetUnitListenerDoc()
{
	//ASSERT( m_pDoc );
	//return m_pDoc;
	return NULL;
}

void IPropertySet::OnUnitChanged()
{
	ShowProperty();
}

MPropertiesWnd* IPropertySet::GetPropWnd()
{
// 	MFrameBase* pMainWnd = (MFrameBase*)AfxGetMainWnd();
// 	ASSERT( pMainWnd != (MFrameBase*)NULL );
//  	ASSERT( pMainWnd->IsKindOf(RUNTIME_CLASS(MFrameBase)) );
//  	
// 	return pMainWnd->GetPropertiesWnd();
	return NULL;
}

MPropListCtrl* IPropertySet::GetPropList()
{
	return m_pPropWnd->GetPropList();
}

void IPropertySet::RemoveAllProperties()
{
	m_pPropWnd->RemoveAllProperties();
}

void IPropertySet::ResetProperty()
{
	m_pPropWnd->ResetProperty();
}

void IPropertySet::AdjustLayout()
{
	GetPropList()->AdjustLayout();
}

void IPropertySet::SetInfo( DWORD_PTR dwpType )
{
	GetPropList()->SetInfo( dwpType, m_itr, m_usDataType );
}

CBCGPProp* IPropertySet::AddTitle( CBCGPProp* pParent, LPCTSTR lpszTitle )
{
	return m_pPropWnd->AddTitle( pParent, lpszTitle );
}

CBCGPProp* IPropertySet::AddGeneralProperty
					(
					 CBCGPProp*  pParent,
					 LPCTSTR	lpszName,
					 _variant_t var,
					 LPCTSTR	lpszComment,
					 BOOL       bEditable,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddGeneralProperty(pParent, lpszName, var, lpszComment, dwData, bEditable);	
}

CBCGPProp* IPropertySet::AddGeneralPropertyWithOption
					(
					 CBCGPProp*	pParent,
					 LPCTSTR	lpszName,
					 int		nNumberOfOption,
					 LPCTSTR*	pOptions,
					 int        nInitialIdx,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddGeneralPropertyWithOption(pParent, lpszName, nNumberOfOption, pOptions, nInitialIdx, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddBooleanProperty
					(
					 CBCGPProp*  pParent,
					 LPCTSTR	lpszName,
					 bool       bInitialValue,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddBooleanProperty(pParent, lpszName, bInitialValue, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddColorProperty
					(
					 CBCGPProp*  pParent,
					 LPCTSTR	lpszName,
					 COLORREF&	cInitialColor,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddColorProperty(pParent, lpszName, cInitialColor, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddButtonProperty
					(
					 CBCGPProp*  pParent,
					 LPCTSTR	lpszName,
					 LPCTSTR	lpszButtonName,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddButtonProperty(pParent, lpszName, lpszButtonName, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddSpinProperty
					(
					 CBCGPProp*  pParent,
					 LPCTSTR	lpszName,
					 _variant_t var,
					 LPCTSTR	lpszComment,
					 int		min,
					 int		max,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddSpinProperty(pParent, lpszName, var, lpszComment, dwData, min, max);
}

CBCGPProp* IPropertySet::AddCheckBoxProperty
					(
					 CBCGPProp*	pParent,
					 LPCTSTR	lpszName,
					 bool		bCheck,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddCheckBoxProperty(pParent, lpszName, bCheck, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddCheckEditBoxProperty
					(
					 CBCGPProp*	pParent,
					 LPCTSTR	lpszName,
					 bool		bCheck,
					 _variant_t var,
					 LPCTSTR	lpszComment,
					 DWORD_PTR  dwData
					 )
{
	return m_pPropWnd->AddCheckEditBoxProperty(pParent, lpszName, bCheck, var, lpszComment, dwData);
}

CBCGPProp* IPropertySet::AddIconListProperty
					(
					 CBCGPProp*		pParent,
					 LPCTSTR		lpszName,
					 CImageList&	imgList,
					 int			initList,
					 CStringList&	titleList,
					 LPCTSTR		lpszComment,
					 DWORD_PTR		dwData
					 )
{
	return m_pPropWnd->AddIconListProperty(pParent, lpszName, imgList, initList, titleList, lpszComment, dwData);
}

void IPropertySet::ExtractInt(CBCGPProp* pSrc, int& nDest)
{
	_variant_t t = pSrc->GetValue();
	nDest = long(t);
}

void IPropertySet::ExtractUINT(CBCGPProp* pSrc, UINT& unDest)
{
	CString strDest;
	ExtractString(pSrc, strDest);
//	int nDest;
// 	if (!CStrParser::GetINumber(strDest, nDest))
// 	{
// 		unDest = 0;
// 	}
// 	else
// 	{
// 		unDest = (UINT)nDest;
// 	}
}

void IPropertySet::ExtractColor(CBCGPProp* pSrc, COLORREF& cDest)
{
	CString strDest;
	ExtractString(pSrc, strDest);
//	int nDest;
// 	if (!CStrParser::GetINumber(strDest, nDest))
// 	{
// 		cDest = 0;
// 	}
// 	else
// 	{
// 		cDest = (COLORREF)nDest;
// 	}
}

void IPropertySet::ExtractBoolean(CBCGPProp* pSrc, BOOL& bDest)
{
	_variant_t t = pSrc->GetValue();
	bDest = bool(t);
}

void IPropertySet::ExtractDouble(CBCGPProp* pSrc, double& dDest)
{
	_variant_t t = pSrc->GetValue();
	dDest = double(t);
}

void IPropertySet::ExtractString(CBCGPProp* pSrc, CString& strDest)
{
	_variant_t t = pSrc->GetValue();
	strDest = (wchar_t*)(_bstr_t(t));
}

void IPropertySet::ExtractOption(CBCGPProp* Src, int& iDest)
{
	CString strType;
	ExtractString( Src, strType );
	_stscanf( strType, _T("%ld"), &iDest );
}

void IPropertySet::ExtractKey(CBCGPProp* Src, MKey& kDest)
{
	CString strKey;
	ExtractString( Src, strKey );
	_stscanf( strKey, _T("%ld"), &kDest );
}

void IPropertySet::ShowApplyBtn(BOOL bShow)
{
	m_pPropWnd->ShowApplyBtn( bShow );
}