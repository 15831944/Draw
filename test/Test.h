#pragma once

#include "HeaderPre.h"
#include "resource.h"

// MTest �Ի���
class __MY_EXT_CLASS__ MTest : public CDialog
{
	DECLARE_DYNAMIC(MTest)

public:
	MTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MTest();

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
};
#include "HeaderPost.h"
