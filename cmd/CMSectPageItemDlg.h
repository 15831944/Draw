#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CCMSectPageItemDlg 对话框
class CDBDoc;
class CCMSectPageItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMSectPageItemDlg)

public:
	CCMSectPageItemDlg(CDBDoc* pDoc,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMSectPageItemDlg();

// 对话框数据
	enum { IDD = IDD_CMD_SP_ITEM_DLG };
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	CEdit m_wndID;
	DECLARE_MESSAGE_MAP()
	T_SECT_K m_Key;
	T_SECT_D m_Data;
	CDBDoc* m_pDoc;
private:
	CImageList* m_pImageList;
	CComboBoxEx m_cboType;
	CComboBox m_wndDB;
	CButton m_wndBuiltUp;
	CComboBox m_wndFirstName;
	CEdit m_wndFirstSize[8];

	CArray<UINT,UINT>	m_aCtrlDB;
	CArray<UINT,UINT> m_aCtrlDBUser;
	CArray<UINT,UINT> m_aCtrlDBUser2;
	
private:
	void InitControls();
	void SetSectionShapeCombo();
	void SetDBNameList();
	void ShowDataToDlg();
	void SetFirstSectData();
	void SetFirstNameCombo();
	void ChangeBitmap();
public:
	virtual void OnOk();
	afx_msg void OnApply();
	afx_msg void OnRadio();
	afx_msg void OnChangeShape();
	afx_msg void OnChangeDB();
};
