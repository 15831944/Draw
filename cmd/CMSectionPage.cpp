// CMSectionPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMSectionPage.h"
#include "afxdialogex.h"


// CCMSectionPage �Ի���

IMPLEMENT_DYNAMIC(CCMSectionPage, CDialog)

CCMSectionPage::CCMSectionPage(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_SECTION_PAGE, pParent)
{

}

CCMSectionPage::~CCMSectionPage()
{
}

void CCMSectionPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCMSectionPage, CDialog)
END_MESSAGE_MAP()


// CCMSectionPage ��Ϣ�������
