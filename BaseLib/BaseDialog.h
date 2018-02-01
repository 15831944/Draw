#pragma once
#include "HeaderPre.h"
namespace dlg
{
	class __MY_EXT_CLASS__ CBaseDialog :
		public CDialog
	{
		DECLARE_DYNAMIC(CBaseDialog);
	protected:
		int m_nDlgTemplateResID;
		/*const*/ HINSTANCE m_hResInstance;
	public:
		virtual ~CBaseDialog(void);
		CBaseDialog(UINT resID, CWnd* pParent = NULL);
		CBaseDialog(CWnd* pParent = NULL); 
		virtual INT_PTR DoModal();
		#define AFX_GET_HINSTANCE m_hResInstance = AfxGetStaticModuleState()->m_hCurrentInstanceHandle;
	};
}
#include "HeaderPost.h"
