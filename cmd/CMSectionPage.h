#pragma once


// CCMSectionPage �Ի���

class CCMSectionPage : public CDialog
{
	DECLARE_DYNAMIC(CCMSectionPage)

public:
	CCMSectionPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMSectionPage();

//// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMD_SECTION_PAGE };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
