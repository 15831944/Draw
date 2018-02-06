#pragma once
#include "../DB/DBdoc.h"
#include "afxwin.h"

class CCMatPageItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMatPageItemDlg)

public:
	CCMatPageItemDlg(CDBDoc* pDoc, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMatPageItemDlg();

	enum { IDD = IDD_CMD_MP_ITEM_DLG };

private:
	BOOL m_bModify;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
private:
	T_MATL_K m_Key;
	CDBDoc * m_pDoc;
	void GetDefaultCode();
	void ShowDataToDlg();
	void SetTypeCombo();
private:
	CEdit m_wndID;
public:
	afx_msg void OnChangeType();
	CComboBox m_wndType;
};
