#pragma once
class CCMSecPageStiffDlgGrid : public CGXGridWnd
{

};

// CCMStiffDlg �Ի���
class CDBDoc;
class CCMStiffDlg : public CDialog
{
	DECLARE_DYNAMIC(CCMStiffDlg)

public:
	CCMStiffDlg(CDBDoc* pDoc,T_SECT_D* pData,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMStiffDlg();

// �Ի�������
	enum { IDD = IDD_CMD_SP_VIEW_STIFF };
private:
	CDBDoc* m_pDoc;
	T_SECT_D* m_pData;
	CCMSecPageStiffDlgGrid m_wndGrid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
