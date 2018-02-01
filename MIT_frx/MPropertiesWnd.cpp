#include "stdafx.h"
#include "MPropertiesWnd.h"
#include "MCustomproperties.h"
#include "IPropertySet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace mit;
using namespace mit::lib;
using namespace mit::frx;
//////////////////////////////////////////////////////////////////////////
// CApplyButton
unsigned int MApplyButton::WM_APPLYBUTTON_CLICKED = RegisterWindowMessage(_T("WM_APPLYBUTTON_CLICKED"));

BEGIN_MESSAGE_MAP(MApplyButton, MCoolButton)
//{{AFX_MSG_MAP(CApplyButton)
	ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
MApplyButton::MApplyButton()
{
}

MApplyButton::~MApplyButton()
{
}

void MApplyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	GetParent()->PostMessage(WM_APPLYBUTTON_CLICKED, 0, 0);

	CBCGPButton::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
// CPropGridCtrl
MPropListCtrl::MPropListCtrl()
{
	ResetInfo();
	m_pPropertySet  = NULL;
}

MPropListCtrl::~MPropListCtrl()
{
	ResetInfo();
	m_pPropertySet  = NULL;
}

void MPropListCtrl::ResetInfo()
{
	m_dwpType		= 0;
	m_itr			= NULL;
	m_usDataType	= 0;
}

void MPropListCtrl::SetInfo( DWORD_PTR dwpType, const MIterator itr, const USHORT usDataType )
{
	m_dwpType		= dwpType;
	m_itr			= itr;
	m_usDataType	= usDataType;
}

MIterator MPropListCtrl::GetIterator()
{
	ASSERT( m_itr );
	return m_itr;
}

void MPropListCtrl::SetPropertySet( IPropertySet* pSet )
{
	m_pPropertySet = pSet;
}

void MPropListCtrl::OnPropertyChanged(CBCGPProp* pProp) const
{
	DWORD_PTR dwData = pProp->GetData();

	if( m_pPropertySet )
		m_pPropertySet->OnPropertyChanged( pProp, dwData );
}

BOOL MPropListCtrl::EditItem(CBCGPProp* pProp, LPPOINT lptClick)
{
	if( m_pPropertySet )
		m_pPropertySet->CalProp();
	return 	MLayeredPropList::EditItem(pProp, lptClick);
}

//////////////////////////////////////////////////////////////////////////
// CPropertiesWnd
IMPLEMENT_DYNCREATE(MPropertiesWnd, MBaseDockWnd)
MPropertiesWnd::MPropertiesWnd() : m_nMode(-1), m_pPropertySet(NULL)
{
}

MPropertiesWnd::~MPropertiesWnd()
{
	ASSERT( !m_pPropertySet ); // 이미 지워져 있어야 한다. CPropertiesWnd -> window handle 사라지기 전에
}

BEGIN_MESSAGE_MAP(MPropertiesWnd, MBaseDockWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

void MPropertiesWnd::SetPropertySet( IPropertySet* pSet )
{
	if( m_pPropertySet ) delete m_pPropertySet;
	m_pPropertySet = pSet;
	m_wndPropList.SetPropertySet( m_pPropertySet );
}

LRESULT MPropertiesWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == MApplyButton::WM_APPLYBUTTON_CLICKED)
	{
		if( m_pPropertySet ) m_pPropertySet->ApplyProperty();
	}

	return MBaseDockWnd::WindowProc(message, wParam, lParam);
}

void MPropertiesWnd::SetMode( int nMode )
{
	if( m_nMode == nMode ) return;

	m_nMode = nMode;
	AdjustLayout();

	switch( nMode )
	{
	case 0:
		m_wndObjectCombo.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_wndObjectCombo.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_wndObjectCombo.ShowWindow(SW_SHOWNORMAL);
		break;
	default:
		ASSERT(0);
		break;
	}
}

void MPropertiesWnd::OnChangeLanguage()
{
	DefaultProperties();
	
	if( m_pPropertySet ) m_pPropertySet->ShowProperty();
}

void MPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)	return;

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);

	int cyCmb = 0;
	if( m_nMode != 0 )
	{
		m_wndObjectCombo.GetWindowRect(&rectCombo);
		cyCmb = rectCombo.Size().cy;
	}

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top+cyCmb, rectClient.Width(), rectClient.Height()-cyCmb, SWP_NOACTIVATE | SWP_NOZORDER);
}

int MPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (MBaseDockWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if( !CreatePropList() )
	{
		TRACE0("Failed to create a Property List. \n");
		return -1;      // 만들지 못했습니다.
	}	

	SetPropListFont();

	ResetProperty();
	return 0;
}

BOOL MPropertiesWnd::CreatePropList()
{
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		return FALSE;      // fail to create
	}

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		return FALSE;
	}

	m_wndPropList.EnableHeaderCtrl(FALSE);	
	m_wndPropList.EnableDescriptionArea(FALSE); // Properties View 하단에 설명영역 show/hide
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	return TRUE;
}

void MPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	MBaseDockWnd::OnSize(nType, cx, cy);
	AdjustLayout();
}

void MPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	MBaseDockWnd::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void MPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	MBaseDockWnd::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void MPropertiesWnd::SetPropListFont()
{
	static BOOL sCreated = FALSE;
	if (sCreated) return;
	sCreated = TRUE;
	m_fntPropList.CreateFont(
		14,                        // nHeight,
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_ROMAN,  // nPitchAndFamily
		_T("Tahoma"));

	//m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetFont(&m_fntPropList);	
	m_wndPropList.SetFont(&m_fntPropList);
}

void MPropertiesWnd::DefaultProperties()
{
	GetPropList()->RemoveAll();
	GetPropList()->ResetInfo();
	AddTitle( NULL, _LS(IDS_MIT_FRX_GENERAL) );
}

void MPropertiesWnd::RemoveAllProperties()
{
	GetPropList()->RemoveAll();
	GetPropList()->ResetInfo();
}

void MPropertiesWnd::ResetProperty()
{
	SetMode( 0 );
	DefaultProperties();
}

CBCGPProp* MPropertiesWnd::AddTitle( CBCGPProp* pParent, LPCTSTR lpszTitle )
{
	CBCGPProp* pTitle = new CBCGPProp( lpszTitle );
	ASSERT( pTitle );

	if( pParent == NULL )
		GetPropList()->AddProperty( pTitle );
	else
		pParent->AddSubItem( pTitle );

	return pTitle;
}

CBCGPProp* MPropertiesWnd::AddGeneralProperty
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 _variant_t var,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData,
											 BOOL       bEditable
										 )
{
	CBCGPProp* pProp = new CBCGPProp( lpszName, var, lpszComment );
	pProp->m_strFormatDouble = _T("%lg");
	pProp->SetData( dwData );
	pProp->AllowEdit( bEditable );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddGeneralPropertyWithOption
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 int		nNumberOfOption,
											 LPCTSTR*	pOptions,
											 int        nInitialIdx,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )
{
	ASSERT( nInitialIdx < nNumberOfOption );
	if( nNumberOfOption == 0 ) { ASSERT(0); return NULL; }

	CBCGPProp* pProp = new CBCGPProp( lpszName, pOptions[nInitialIdx], lpszComment );
	pProp->SetData( dwData );
	pProp->AllowEdit(FALSE);
	for( int i=0 ; i<nNumberOfOption; ++i )
		pProp->AddOption( pOptions[i] );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddBooleanProperty
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 bool       bInitialValue,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )
{
	CBCGPProp* pProp = new CBCGPProp( lpszName, (_variant_t)bInitialValue, lpszComment );  
	pProp->SetData( dwData );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddColorProperty
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 COLORREF&	cInitialColor,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )
{
	CBCGPColorProp* pProp = new CBCGPColorProp( lpszName, cInitialColor, NULL, lpszComment );
	pProp->SetData( dwData );
	CString strOther = _LS(IDS_MIT_FRX_OTHER);
	strOther += _T("...");
	pProp->EnableOtherButton( strOther );
	pProp->EnableAutomaticButton( _LS(IDS_MIT_FRX_DEFAULT), ::GetSysColor(COLOR_3DFACE) );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddButtonProperty
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 LPCTSTR	lpszButtonName,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )
{
	MButtonProp* pProp = new MButtonProp( lpszName, lpszButtonName, lpszComment );
	pProp->SetData( dwData );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddSpinProperty
										 (
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 _variant_t var,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData,
											 int min,
											 int max
										)
{
	CBCGPProp* pProp = new CBCGPProp( lpszName, var, lpszComment );
	pProp->SetData( dwData );
	pProp->EnableSpinControl( TRUE, min, max );

	if( pParent == NULL )
		GetPropList()->AddProperty( pProp );
	else
		pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddCheckBoxProperty
										(
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 bool		bCheck,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )										 
{
	if( pParent == NULL ) { ASSERT(0); return NULL; }

	MCheckBoxProp* pProp = new MCheckBoxProp( lpszName, bCheck, lpszComment );
	pProp->SetData( dwData );
	pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddCheckEditBoxProperty
										(
											 CBCGPProp*  pParent,
											 LPCTSTR	lpszName,
											 bool		bCheck,
											 _variant_t var,
											 LPCTSTR	lpszComment,
											 DWORD_PTR  dwData
										 )										 
{
	if( pParent == NULL ) { ASSERT(0); return NULL; }

	MCheckEditBoxProp* pProp = new MCheckEditBoxProp( lpszName, bCheck, var, lpszComment );
	pProp->SetData( dwData );
	pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}

CBCGPProp* MPropertiesWnd::AddIconListProperty
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
	if( pParent == NULL ) { ASSERT(0); return NULL; }

	MIconListProp* pProp = new MIconListProp( lpszName, imgList, initList, &titleList, lpszComment );
	pProp->SetData( dwData );
	pParent->AddSubItem( pProp );

	ASSERT( pProp );
	return pProp;
}