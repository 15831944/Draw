#include "stdafx.h"
#include "DocBase.h"
#include "ModelessDlgCtrl.h"
IMPLEMENT_DYNCREATE(CDocBase,CDocument)
CDocBase* CDocBase::m_pDocBase = 0;

CDocBase::CDocBase()
{
	m_pDocBase = this;
	m_pDlgCtrl = new CModelessDlgCtrl;

}

BEGIN_MESSAGE_MAP(CDocBase,CDocument)

END_MESSAGE_MAP()