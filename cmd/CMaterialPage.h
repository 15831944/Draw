#pragma once


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
};
