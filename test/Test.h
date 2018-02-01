#pragma once

#include "HeaderPre.h"
#include "resource.h"

// MTest 对话框
class __MY_EXT_CLASS__ MTest : public CDialog
{
	DECLARE_DYNAMIC(MTest)

public:
	MTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MTest();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
};
#include "HeaderPost.h"
