#pragma once


// CCMatPageItemDlg �Ի���

class CCMatPageItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMatPageItemDlg)

public:
	CCMatPageItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMatPageItemDlg();

	enum { IDD = IDD_CMD_MP_ITEM_DLG };

private:
	BOOL m_bModify;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
};