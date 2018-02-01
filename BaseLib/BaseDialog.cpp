#include "stdafx.h"
#include "BaseDialog.h"

using namespace dlg;
IMPLEMENT_DYNAMIC(CBaseDialog, CDialog)
CBaseDialog::CBaseDialog(CWnd* pParent):CDialog(-1,pParent)
{
	m_hResInstance = 0;
}

CBaseDialog::CBaseDialog(UINT resID, CWnd* pParent):CDialog(resID,pParent) 
{
	m_nDlgTemplateResID = resID;
}

CBaseDialog::~CBaseDialog(void)
{
	m_hResInstance = 0;
}

INT_PTR CBaseDialog::DoModal()
{
	HINSTANCE old_hInstance = AfxGetResourceHandle();

	//AFX_MODULE_STATE* pModuleState = AfxGetStaticModuleState();
	//HINSTANCE hInstTemp = pModuleState->m_hCurrentInstanceHandle;
	//LPCTSTR lpszTemplateName = MAKEINTRESOURCE(m_nDlgTemplateResID);


	HINSTANCE hInst = AfxFindResourceHandle(m_lpszTemplateName, RT_DIALOG);

	
	AfxSetResourceHandle(hInst);
	INT_PTR nResult = CDialog::DoModal();
	AfxSetResourceHandle(old_hInstance);
	return nResult;
}
//BEGIN_MESSAGE_MAP(CBaseDialog, CDialog)
//END_MESSAGE_MAP()



