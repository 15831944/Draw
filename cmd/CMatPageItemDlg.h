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
	T_MATL_D m_Data;
	CDBDoc * m_pDoc;
	CBitmap* m_pBitmap;
private:
	void GetDefaultCode();
	void ShowDataToDlg();
	void SetTypeCombo();
	void SetCode(CComboBox* pCombo, const CString& strType);
	void SetNameCombo(CComboBox* pCombo, const CString& strType, const CString& strCode);
	void SetSteelCode(int nTypeIndex);
	void SetConcrCode(int nTypeIndex);
	void SetFrameName(int nTypeIndex);
	void ChangeBitmap(int nBitmap);
	void ChangeDlgCtrls();

	int GetTypeIndex(CString strType)const;
	CString GetTypeCode(int nTypeIndex)const;
private:
	CEdit m_wndID;
public:
	afx_msg void OnChangeType();
	
private:
	CStatic m_wndStlCodeFrame;
	CComboBox m_wndType;
	CComboBox m_wndSteelCode;
	CComboBox m_wndConcrCode;
	CComboBox m_wndSteelName;
	CArray<UINT, UINT> m_aCtrlThermalSteel, m_aCtrlThermalConc;
public:
	afx_msg void OnBtnOk();
	afx_msg void OnChangeSteelCode();
};
