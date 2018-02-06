#include "stdafx.h"
#include "ExportFunc.h"
#include "../DB/DBDoc.h"
#include "CMPropertiesDlg.h"


void * CreateOrActivateDlg(CDBDoc * pDoc, UINT nIDTemplate, CWnd * pParent, void * pExtData)
{
	//CCMDlgBase* pDlg = (CCMDlgBase*)pDoc->m_pDlgCtrl->Get;
	CCMDlgBase* pDlg = 0;
	DWORD dwLastError = NO_ERROR;
	switch (nIDTemplate)
	{
	case CCMPropertiesDlg::IDD:
		pDlg = new CCMPropertiesDlg(pParent);
		break;
	default:
		break;
	}
	pDlg->m_pDoc = pDoc;
	pDlg->Create(nIDTemplate,pParent);
	dwLastError = ::GetLastError();
	if (::GetLastError() == NO_ERROR)
		::SetLastError(dwLastError);
	pDlg->ShowWindow(SW_SHOW);
	return pDlg;
}
