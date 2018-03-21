#include "stdafx.h"
#include "CobxAutoFill.h"


CCobxAutoFill::CCobxAutoFill(void)
{
	m_nMode = 1;
	m_nDefaultSel = -1;
	m_nCurSel = -1;
	m_bAutoFill = TRUE;
}
CCobxAutoFill::~CCobxAutoFill(void)
{
}
void CCobxAutoFill::SetActionWhenKillFocus(int nMode, int nDefaultSel/* =-1 */)
{
	m_nMode = nMode;
	if(m_nMode == 1)m_nDefaultSel = nDefaultSel;
	else m_nDefaultSel = -1;
}
BEGIN_MESSAGE_MAP(CCobxAutoFill, CComboBox)
	ON_CONTROL_REFLECT_EX(CBN_EDITUPDATE, OnCbnEditupdate)
	ON_CONTROL_REFLECT_EX(CBN_KILLFOCUS, &CCobxAutoFill::OnCbnKillfocus)
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, &CCobxAutoFill::OnCbnSelchange)
	//ON_CONTROL_REFLECT_EX(CBN_SETFOCUS, &CCobxAutoFill::OnCbnSetfocus)
END_MESSAGE_MAP()


void CCobxAutoFill::SendMsgSelChange(int nNewSel)
{
	SetCurSel(nNewSel);//���ѡ�е�Ӱ�쵽����
	WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(),CBN_SELCHANGE);
	LPARAM lParam = (LPARAM)GetSafeHwnd();
	CWnd* pParent = GetParent();
	if(pParent && pParent->GetSafeHwnd() && IsWindow(pParent->GetSafeHwnd()))
		pParent->SendMessage(WM_COMMAND,wParam,lParam);
}
BOOL CCobxAutoFill::OnCbnEditupdate()
{
	CString str;
	GetWindowText(str);
	int nLength = str.GetLength();
	DWORD dwCurSel = GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd = HIWORD(dwCurSel);
	int nIndex = FindStringExact(-1,str);
	if(nIndex == CB_ERR)
	{
		if(!m_bAutoFill)return FALSE;
		int nNewSel;
		if((nNewSel = SelectString(-1,str)) == CB_ERR)
		{
			str.Delete(nLength-1);
			SelectString(-1,str);
			nLength = str.GetLength();
			//SelectString(-1,str);
			SetEditSel(nLength-1,-1);
		}
		else
		{
			if(m_nCurSel != nNewSel)
				SendMsgSelChange(nNewSel);
		}
	}
	else
	{
		if(m_nCurSel != nIndex)
			SendMsgSelChange(nIndex);
	}
	if(dEnd < nLength && dwCurSel != CB_ERR)SetEditSel(dStart,dEnd);
	else SetEditSel(nLength,-1);
	return FALSE;
}
BOOL CCobxAutoFill::OnCbnKillfocus()
{
	/*if(m_nMode == 0)return FALSE;
	CString csText;
	GetWindowText(csText);
	int nSel = FindStringExact(-1,csText);
	BOOL bMatch = FALSE;
	if(nSel != CB_ERR)
	{
	CString csFound;
	GetLBText(nSel,csFound);
	if(csText == csFound)bMatch = TRUE;
	}
	if(!bMatch)
	{
	SetCurSel(-1);
	SendMsgSelChange(-1);
	}*/
	return FALSE;
}
BOOL CCobxAutoFill::OnCbnSelchange()
{
	int nSel = GetCurSel();
	if(nSel != -1)
	{
		CString csText;
		GetLBText(nSel,csText);
		SetWindowText(csText);
	}
	else SetWindowText(_T(""));
	m_nCurSel = nSel;
	return FALSE;
}
BOOL CCobxAutoFill::OnCbnSetfocus()
{
	//m_nCurSel = GetCurSel();	//Ӧ�ò���~
	return FALSE;
}
BOOL CCobxAutoFill::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		m_bAutoFill = TRUE;
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoFill = FALSE;
		if(nVirtKey == 96)
			m_bAutoFill = TRUE;
	}
	return CComboBox::PreTranslateMessage(pMsg);
}






//#include "stdafx.h"
//#include "CobxAutoFill.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
///////////////////////////////////////////////////////////////////////////////
//// CCobxAutoFill
//
//CCobxAutoFill::CCobxAutoFill()
//{
//	m_bAutoFill = TRUE;
//	m_nDefaultSel = -1;  // default selection : none
//	m_nMode = 1;  // select default value
//	m_nCurSel = -1;
//	m_bIMEDisabled = FALSE;
//}
//
//CCobxAutoFill::~CCobxAutoFill()
//{
//}
//
///////////////////////////////////////////////////////////////////////////////
//// Interface
///////////////////////////////////////////////////////////////////////////////
//void CCobxAutoFill::SetActionWhenKillFocus(int nMode, int nDefaultSel)
//{
//	m_nMode = nMode;
//	if (nMode == 1) m_nDefaultSel = nDefaultSel;
//	else m_nDefaultSel = -1;
//}
//
//BOOL CCobxAutoFill::GetCurrentComboText(CString &str)
//{
//	// ���� combo edit�� string�� ���ͼ�..
//	GetWindowText(str);
//	// ���� str�� list�߿� ��ġ�ϴ� ���� �ִٸ� TRUE
//	if (SelectString(-1, str) == CB_ERR) return FALSE;
//	else return TRUE;
//}
//
//void CCobxAutoFill::SendMsgSelChange(int nNewSel)
//{
//	SetCurSel(nNewSel);
//	WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), CBN_SELCHANGE);
//	LPARAM lParam = (LPARAM)GetSafeHwnd();
//	CWnd* pParent = GetParent();
//	if (pParent && pParent->GetSafeHwnd() && IsWindow(pParent->GetSafeHwnd()))
//		pParent->SendMessage(WM_COMMAND, wParam, lParam);
//}
//
//BEGIN_MESSAGE_MAP(CCobxAutoFill, CComboBox)
//	//{{AFX_MSG_MAP(CCobxAutoFill)
//	ON_CONTROL_REFLECT_EX(CBN_EDITUPDATE, OnEditUpdate)
//	ON_CONTROL_REFLECT_EX(CBN_KILLFOCUS, OnKillfocus)
//	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, OnSelchange)
//	ON_CONTROL_REFLECT_EX(CBN_SETFOCUS, OnSetfocus)
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CCobxAutoFill message handlers
//
//BOOL CCobxAutoFill::PreTranslateMessage(MSG* pMsg)
//{
//	// Need to check for backspace/delete. These will modify the text in
//	// the edit box, causing the auto complete to just add back the text
//	// the user has just tried to delete. 
//
//	if (pMsg->message == WM_KEYDOWN)
//	{
//		m_bAutoFill = TRUE;
//		int nVirtKey = (int) pMsg->wParam;
//		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
//			m_bAutoFill = FALSE;
//	}
//	return CComboBox::PreTranslateMessage(pMsg);
//}
//
//BOOL CCobxAutoFill::OnEditUpdate() 
//{
//	// if we are not to auto update the text, get outta here
//	// Back, Delete�� ������ ���� PreTranslateMessage�Լ����� m_bAutoFill�� FALSE��
//	// �Ѵ�. ���� �� ���� ��Ȯ�ϰ� ��ġ�Ǵ� ��츸 ó���� �ֵ��� �Ѵ�.
//	//if (!m_bAutoFill) return FALSE;
//
//	// Get the text in the edit box
//	CString str;
//	GetWindowText(str);
//	int nLength = str.GetLength();
//
//	// combo edit �� ���õǾ� �ִ� sel(�Ķ��� ���õ� �κ�)�� ��ġ�� ��� �´�. 
//	DWORD dwCurSel = GetEditSel();
//	WORD dStart = LOWORD(dwCurSel);
//	WORD dEnd   = HIWORD(dwCurSel);
//
//	// -1 �ε������� ���� ��� ����� str�� ���Ͽ� ������ selection
//	// �׷��� ������ CB_ERR
//
//	int nIndex = FindStringExact(-1, str);
//	if (nIndex == CB_ERR)
//	{
//		if (!m_bAutoFill) return FALSE; // Back, DeleteŰ ������ ���
//		int nNewSel;
//		if ((nNewSel = SelectString(-1, str)) == CB_ERR)
//		{
//			// �߸� �� ���ڸ� �����. 
//			str.Delete(nLength-1);
//			// �� ���¿��� selection �ϸ� CB_ERR�� ��ȯ���� ���� ���̴�. 
//			SelectString(-1, str);  
//			nLength = str.GetLength();
//			SetEditSel(nLength-1, -1);
//		}
//		else
//		{
//			if (m_nCurSel != nNewSel)
//			{
//				//m_nCurSel = nNewSel;
//				SendMsgSelChange(nNewSel);
//			}
//		}
//	}
//	else
//	{
//		if (m_nCurSel != nIndex)
//			SendMsgSelChange(nIndex);
//	}
//	// Set the text selection as the additional text that we have added
//	if (dEnd < nLength && dwCurSel != CB_ERR) SetEditSel(dStart, dEnd);
//	else SetEditSel(nLength, -1);
//
//	return FALSE;
//}
//
//BOOL CCobxAutoFill::OnKillfocus() 
//{
//	// TODO: Add your control notification handler code here
//	if (m_nMode == 0) return FALSE;
//
//	CString csText;
//	GetWindowText(csText);
//	//int nSel = FindString(-1, csText);
//	int nSel = FindStringExact(-1, csText);
//
//	BOOL bMatch = FALSE;
//	if (nSel != CB_ERR)
//	{
//		CString csFound;
//		GetLBText(nSel, csFound);
//		if (csText == csFound) bMatch = TRUE;
//	}
//
//	if (!bMatch)
//	{
//		if (m_nMode == 1) // select partial match else if no match, select default
//		{
//			if (nSel != CB_ERR) // partial match
//				SelectString(-1, csText);
//			else  // No match, select default
//			{
//				if (m_nDefaultSel >= GetCount()) SetCurSel(-1);
//				else SetCurSel(m_nDefaultSel);
//			}
//		}
//		else if (m_nMode == 2)  // clear selection
//		{
//			SetCurSel(-1);
//		}
//		int nSel = GetCurSel();
//		SendMsgSelChange(nSel);
//	}	
//	return FALSE;
//}
//
//BOOL CCobxAutoFill::OnSelchange() 
//{
//	// TODO: Add your control notification handler code here
//	int nSel = GetCurSel();
//	if (nSel != -1)
//	{
//		CString csText;
//		GetLBText(nSel, csText);
//		SetWindowText(csText);
//	}
//	else SetWindowText(_T(""));
//	m_nCurSel = nSel;
//	return FALSE;
//}
//
//#include "Imm.h"
//#pragma comment(lib, "Imm32.lib")
//BOOL CCobxAutoFill::OnSetfocus() 
//{
//	// TODO: Add your control notification handler code here
//	m_nCurSel = GetCurSel();
//
//	if (!m_bIMEDisabled)
//	{
//		CEdit* pCobxEdit = (CEdit*)GetWindow(GW_CHILD);
//		ImmAssociateContext(pCobxEdit->GetSafeHwnd(), NULL);
//		m_bIMEDisabled = TRUE;
//	}
//	return FALSE;
//}
//
//void CCobxAutoFill::PostNcDestroy() 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	m_bIMEDisabled = FALSE;
//	CComboBox::PostNcDestroy();
//}

