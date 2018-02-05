#pragma once


// CCMaterialPage 对话框

class CCMaterialPage : public CDialog
{
	DECLARE_DYNAMIC(CCMaterialPage)

public:
	CCMaterialPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMaterialPage();

//// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMD_MATERIAL_PAGE };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
