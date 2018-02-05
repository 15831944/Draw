// CMaterialPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CMaterialPage.h"
#include "afxdialogex.h"


// CCMaterialPage 对话框

IMPLEMENT_DYNAMIC(CCMaterialPage, CDialog)

CCMaterialPage::CCMaterialPage(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_MATERIAL_PAGE, pParent)
{

}

CCMaterialPage::~CCMaterialPage()
{
}

void CCMaterialPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCMaterialPage, CDialog)
END_MESSAGE_MAP()


// CCMaterialPage 消息处理程序
