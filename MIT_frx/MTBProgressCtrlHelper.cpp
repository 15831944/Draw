#include "stdafx.h"
#include "MTBProgressCtrlHelper.h"

using namespace mit::frx;

MTBProgressCancel MTBProgressCancel::CancelBtn(MTBProgressCancel::CANCEL_BTN);
MTBProgressCancel MTBProgressCancel::EscKey(MTBProgressCancel::ESC_KEY);

CAtlMap<ITable*, MTBProgressCtrlHelper*> MTBProgressCtrlHelper::s_mapHelper;

MTBProgressCtrlHelper::MTBProgressCtrlHelper(ITable* pTable, int nLower, int nUpper, BOOL bCanCancel, const CString& strText, BOOL bDrawPercentage, POSITION* pMyInstancePos) :
	m_pTable(pTable),
	m_pProgressCtrl(pTable->GetProgressCtrl()),
	m_hTable(NULL),
	m_hCancelBtn(NULL),
	m_nLower(nLower),
	m_nUpper(nUpper),
	m_nPos(nLower),
	m_strText(strText),
	m_pMyInstancePos(pMyInstancePos),
	m_bDrawPercentage(bDrawPercentage),
	m_divider((int)(MFastDividerN<int>::GetBitCount( (int)((nUpper - nLower) * 0.01) ))),
	m_tick(GetTickCount()),
	m_pfPeekMessage(NULL)
{
	ASSERT(m_pTable);
	ASSERT(nLower <= nUpper);

	CWnd* pWndTable = dynamic_cast<CWnd*>(pTable);
	ASSERT_VALID(pWndTable); // ITable 은 윈도우여야 한다.
	m_hTable = pWndTable->GetSafeHwnd();
	ASSERT(m_hTable);

	if (bCanCancel)
	{
		m_hCancelBtn = m_pProgressCtrl->GetCancelBtn();
		ASSERT(m_hCancelBtn);
		m_pfPeekMessage = &MTBProgressCtrlHelper::PeekMessageCancelOnly; // TODO: 일단 취소만 가능하도록 고정
		::SetCursor(::LoadCursor(NULL, IDC_APPSTARTING));
	}
	else
	{			
		::AfxGetApp()->BeginWaitCursor();
	}
	
	m_divider.SelfDivide(m_nLower);
	m_divider.SelfDivide(m_nUpper);
	m_divider.SelfDivide(m_nPos);

	m_pProgressCtrl->SetRange(m_nLower, m_nUpper); 
	m_pProgressCtrl->SetPos(m_nPos);
	if (m_bDrawPercentage) m_pProgressCtrl->SetText(GetPercentageText());
	else m_pProgressCtrl->SetText(m_strText);
	m_pProgressCtrl->Show(TRUE, bCanCancel); 
	
	// 이미 진행중인 Progress Bar 가 있는지 확인
	ASSERT(!s_mapHelper.Lookup(m_pTable));
	if (m_pMyInstancePos) *m_pMyInstancePos = s_mapHelper.SetAt(m_pTable, this);
	else s_mapHelper.SetAt(m_pTable, this);
}

MTBProgressCtrlHelper::~MTBProgressCtrlHelper() 
{
	m_pProgressCtrl->Show(FALSE); 

	s_mapHelper.RemoveKey(m_pTable);
	if (m_pMyInstancePos) *m_pMyInstancePos = NULL;

	if (m_hCancelBtn) 
	{
		::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	}
	else
	{
		::AfxGetApp()->EndWaitCursor();
	}

	::AfxGetApp()->RestoreWaitCursor();
}