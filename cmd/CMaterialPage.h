#pragma once
#include "afxcmn.h"


// CCMaterialPage �Ի���
#include "../DB/DBDoc.h"

class CCMaterialPage : public CDialog
{
	DECLARE_DYNAMIC(CCMaterialPage)

public:
	CCMaterialPage(CDBDoc* pDoc, CWnd* pParent = NULL);   // ��׼���캯��
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
	CDBDoc* m_pDoc;
private:
	void InsertItem(T_MATL_K Key, const T_MATL_D& rData);
public:
	afx_msg void OnNMDblclkCmdMpMatList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnModify();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	void OnUpdate();
	void SetHeaderTitle(BOOL bInit = TRUE);
	void MakeItemEx();
	virtual BOOL OnInitDialog();
	CString DataToStr(int i, T_MATL_K Key, const T_MATL_D& rData);
};
