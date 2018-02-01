#include "stdafx.h"
#include "MCoolButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace mit;
using namespace mit::frx;

////////////////////////////////////////////////////////////////////////////////////
// CCoolButton
MCoolButton::MCoolButton() : m_bSel(FALSE), m_bOnlyImage(TRUE)
{
}

MCoolButton::~MCoolButton()
{
}

MCoolButton::MCoolButton( const MCoolButton &S )
{
	*this = S;
}

MCoolButton& MCoolButton::operator=( const MCoolButton &S )
{ 
	return *this;
}

void MCoolButton::SetOnlyImage(BOOL bSet)
{
	m_bOnlyImage = bSet;
}

BOOL MCoolButton::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return CButton::PreTranslateMessage(pMsg);
		}

		if (pMsg->wParam == VK_ESCAPE)
		{
			return CButton::PreTranslateMessage(pMsg);
		}
	}
	else if( pMsg->message == WM_LBUTTONDOWN )
	{
		CWnd* pParent = GetParent();
		if (pParent != NULL)
		{
			pParent->SetFocus();
		}
	}

	return CBCGPButton::PreTranslateMessage(pMsg);
}

void MCoolButton::SetImage(UINT uImageId)
{
	// Image
	CBCGPButton::SetImage(uImageId);

	// Text
	CString str;
	GetWindowText(str);
	if (!str.IsEmpty())
	{
 		//if (str == _T("...") || str == _T(">") || str == _T(">>") || str == _T("Re") || str == _T("Si") || str == _T("Do"))
		if (m_bOnlyImage) SetWindowText(_T(""));
	}
}

void MCoolButton::SetImageKeepString( UINT uImageId )
{
	m_bOnlyImage = FALSE;
	// Image
	CBCGPButton::SetImage(uImageId);
}

void MCoolButton::PushBtn(LPCTSTR lpszText)
{
	SetWindowText(lpszText);
	PushBtn();
}

void MCoolButton::PushBtn()
{
	ResetSel();
	if (GetCheck() != 1)
		SetCheck(1);
}

void MCoolButton::PopBtn(LPCTSTR lpszText)
{
	PopBtn();
	SetWindowText(lpszText);
}

void MCoolButton::SetImageID(UINT uBmpOff, UINT uBmpOn, UINT uBmpCheck)
{
	m_uBmpCheck = uBmpCheck;
	m_uBmpOff = uBmpOff;
	SetImage(uBmpOff);
	SetCheckedImage(uBmpOn);
}

void MCoolButton::PopBtn()
{
	if (IsSel())
		SetImage(m_uBmpCheck);
	else
		SetImage(m_uBmpOff);

	if (GetCheck() != 0)
		SetCheck(0);
}

void MCoolButton::SetPushButton(CString strText)
{
	PushBtn(strText);
}

void MCoolButton::SetPopButton(CString strText, BOOL bCheck)
{
	SetCheck(bCheck);
	bCheck ? SetSel() : ResetSel();
	PopBtn(strText);
}