#pragma once
#include "afxcmn.h"


// CCMaterialPage �Ի���

class CCMaterialPage : public CDialog
{
	DECLARE_DYNAMIC(CCMaterialPage)

public:
	CCMaterialPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMaterialPage();

//// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMD_MATERIAL_PAGE };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_List;
public:
	afx_msg void OnNMDblclkCmdMpMatList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnModify();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
};
