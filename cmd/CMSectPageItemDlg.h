#pragma once
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../BaseLib/ControlEx.h"
#include "CMSectViewWnd.h"
// CCMSectPageItemDlg �Ի���
class CDBDoc;
class CCobxAutoFill;
class CCMSectPageItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMSectPageItemDlg)

public:
	CCMSectPageItemDlg(CDBDoc* pDoc,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMSectPageItemDlg();

// �Ի�������
	enum { IDD = IDD_CMD_SP_ITEM_DLG };
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	CBitmap m_Bitmap;
	CButton m_wndBuiltUp;
	CCobxAutoFill m_wndFirstName;
	CCMSectViewWnd m_wndSectView;
	CEdit m_wndFirstSize[8];
	CStatic m_wndFirstTitle[8];
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
	afx_msg void OnChangeFirstName();
	afx_msg void OnBtnCalculate();
};
