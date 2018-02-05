#pragma once


// CCMatPageItemDlg 对话框

class CCMatPageItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMatPageItemDlg)

public:
	CCMatPageItemDlg(CWnd* pParent = NULL);   // 标准构造函数
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
};
