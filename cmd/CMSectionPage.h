#pragma once
#include "../DB/DBDoc.h"
#include "afxwin.h"
#include "CMSectViewWnd.h"
#include "afxcmn.h"
class CCMSectViewWnd;
class CCMSectionPage : public CDialog
{
	DECLARE_DYNAMIC(CCMSectionPage)

public:
	CCMSectionPage(CDBDoc* pDoc, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMSectionPage();

//// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMD_SECTION_PAGE };
//#endif
private:
	CDBDoc * m_pDoc;
	CListCtrl m_List;
	T_SECT_K m_Key;
	T_SECT_D m_Data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
private:
	CCMSectViewWnd m_wndSectView;
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAdd();
public:
	void OnUpdate();
	
};
