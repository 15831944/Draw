#include "stdafx.h"
#include "CMDlgBase.h"

#include "../DB/DBDoc.h"
#include "../Baselib/ModelessDlgCtrl.h"
CCMDlgBase::CCMDlgBase(UINT nIDTemplate, CWnd * pParent)
	: CDialog(nIDTemplate,pParent)
{
	m_pDoc = 0;
}

CCMDlgBase::~CCMDlgBase()
{
}


BEGIN_MESSAGE_MAP(CCMDlgBase, CDialog)
	
	ON_MESSAGE(WM_UPDATE_MODELESS_DLG, &CCMDlgBase::OnUpdateDlg)
END_MESSAGE_MAP()

BOOL CCMDlgBase::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	if (m_pDoc == 0)
	{
		m_pDoc = CDBDoc::GetDocPoint();
		ASSERT(m_pDoc);
	}
	int bResult = CDialog::Create(nIDTemplate, pParentWnd);
	if (bResult)
		m_pDoc->m_pDlgCtrl->Add(nIDTemplate, this);
	return bResult;
}


void CCMDlgBase::PostNcDestroy()
{
	delete this;
}

void CCMDlgBase::OnUpdate(CWnd* pSender, LPARAM lParam, CObject* pHint)
{
	//virtual;override this member function
}

afx_msg LRESULT CCMDlgBase::OnUpdateDlg(WPARAM wParam, LPARAM lParam)
{
	SDlgCtrlUpdateArg* pArg;
	pArg = (SDlgCtrlUpdateArg*)lParam;
	OnUpdate(pArg->pSender, pArg->lHint, pArg->pHint);
	return 0;
}
