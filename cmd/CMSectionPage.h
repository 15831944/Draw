#pragma once


// CCMSectionPage 对话框

class CCMSectionPage : public CDialog
{
	DECLARE_DYNAMIC(CCMSectionPage)

public:
	CCMSectionPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMSectionPage();

//// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMD_SECTION_PAGE };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
