#pragma once


#include "CMDlgBase.h"
#include "resource.h"

#include "HeaderPre.h"
class CCMaterialPage;
class CCMSectionPage;
class __MY_EXT_CLASS__ CCMPropertiesDlg : public CCMDlgBase
{

public:
	CCMPropertiesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMPropertiesDlg();

//// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_CMD_PROPERTIES_DLG
	};
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetActivePage(int SelectPage);
private:
	CDlgTabCtrl m_wndTab;
//private:
	CCMaterialPage * m_pMaterial;
	CCMSectionPage * m_pSection;
	int m_nActivePage;
	virtual BOOL OnInitDialog();
	virtual void OnUpdate(CWnd* pSender, LPARAM lParam, CObject* pHint);
	//virtual void OnCancel();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
#include "HeaderPost.h"
#include "afxcmn.h"
