// Test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "afxdialogex.h"
#include "../BaseLib/MSGFunction.h"


// MTest �Ի���

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


// MTest ��Ϣ�������
//INT_PTR MTest::DoModal()
//{
//	INT_PTR nResult = CDialog::DoModal();
//	return nResult;
//}

void MTest::OnBnClickedOk()
{
	::MessageBox(NULL, _LS(IDS_TEST_LPTEXT), _LS(IDS_TEST_LPCAPTION), MB_OK);
}

