#include "stdafx.h"
#include "CMDlgBase.h"

#include "../DB/DBDoc.h"

CCMDlgBase::CCMDlgBase(UINT nIDTemplate, CWnd * pParent)
	: CDialog(nIDTemplate,pParent)
{
	m_pDoc = 0;
}

CCMDlgBase::~CCMDlgBase()
{
}


BEGIN_MESSAGE_MAP(CCMDlgBase, CDialog)
	
END_MESSAGE_MAP()

BOOL CCMDlgBase::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	if (m_pDoc == 0)
	{
		m_pDoc = CDBDoc::GetDocPoint();
		ASSERT(m_pDoc);
	}
	int nResult = CDialog::Create(nIDTemplate, pParentWnd);
	
	return nResult;
}


void CCMDlgBase::PostNcDestroy()
{
	delete this;
}
