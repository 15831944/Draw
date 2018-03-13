#pragma once
#include "../DB/DBdoc.h"
#include "afxwin.h"
#include "../BaseLib/base_ControlEx.h"
class CCMatPageItemDlg : public CDialogMove
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
	void SetAutoChangeNameFlag(CString csName);
	int GetTypeIndex(CString strType)const;
	CString GetTypeCode(int nTypeIndex)const;
private:
	CFormulaEdit m_wndID;
	CFormulaEdit m_wndName;
private:
	BOOL m_bAutoChangeName;
	CStatic m_wndStlCodeFrame;
	CComboBox m_wndType;
	CComboBox m_wndSteelCode;
	CComboBox m_wndConcrCode;
	CComboBox m_wndConcName;
	CComboBox m_wndSteelName;
	CArray<UINT, UINT> m_aCtrlThermalSteel, m_aCtrlThermalConc;
private:
	BOOL CheckData();
public:
	afx_msg void OnChangeType();
	afx_msg void OnApply();
	afx_msg void OnBtnOk();
	afx_msg void OnChangeSteelCode();
	afx_msg void OnChangeConcrCode();
	afx_msg void OnChangeSteelName();
	afx_msg void OnChangeID();
	afx_msg void OnChangeName();
	
	

};
