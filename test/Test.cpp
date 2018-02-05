// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
#include "../BaseLib/MSGFunction.h"


// MTest 对话框

IMPLEMENT_DYNAMIC(MTest, CDialog)

MTest::MTest(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{
	int n = 3;
}

MTest::~MTest()
{
}

void MTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MTest, CDialog)
	ON_BN_CLICKED(IDOK, &MTest::OnBnClickedOk)
END_MESSAGE_MAP()


// MTest 消息处理程序
//INT_PTR MTest::DoModal()
//{
//	INT_PTR nResult = CDialog::DoModal();
//	return nResult;
//}

void MTest::OnBnClickedOk()
{
	::MessageBox(NULL, _LS(IDS_TEST_LPTEXT), _LS(IDS_TEST_LPCAPTION), MB_OK);
}

