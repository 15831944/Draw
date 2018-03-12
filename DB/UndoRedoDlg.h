#pragma once
#include "HeaderPre.h"
#include "resource.h"
class CDBDoc;
class __MY_EXT_CLASS__ CUndoRedoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUndoRedoDlg)

public:
	CUndoRedoDlg(CDBDoc* pDoc, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUndoRedoDlg();

	enum {IDD = IDD_DB_UDRD_LIST_DLG};

private:
	BOOL m_bModify;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	void Create();
	virtual BOOL OnInitDialog();
private:
	CDBDoc * m_pDoc;
private:
public:

};
#include "HeaderPost.h"