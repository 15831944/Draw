#pragma once

#include "HeaderPre.h"


class __MY_EXT_CLASS__ CTest : public CDialogEx
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTest();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
#include "HeaderPost.h"
