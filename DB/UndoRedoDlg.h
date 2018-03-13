#pragma once
#include "HeaderPre.h"
#include "resource.h"
class CDBDoc;
class CListBoxForUR : public CListBox
{
public:
	CListBoxForUR();
	~CListBoxForUR();
private:
	BOOL m_bMouseDown;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSelchange();
};
class __MY_EXT_CLASS__ CUndoRedoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUndoRedoDlg)

public:
	CUndoRedoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUndoRedoDlg();

	enum {IDD = IDD_DB_UDRD_LIST_DLG};

private:
	BOOL m_bModify;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CDBDoc * m_pDoc;
	int m_xPos;
	int m_yPos;
	BOOL m_bIsUndo;
public:
	void SetDlgMode(CDBDoc* pDoc,BOOL bIsUndo,int xPos,int yPos);
private:
	void AddUndoCommands();
	void AddRedoCommands();
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnUndoRedo();
	afx_msg void OnCancel();
	CListBoxForUR m_List;
	CButton m_btnUDRD;
	virtual void PostNcDestroy();
public:
	afx_msg void OnSelchangeList1();
	
};
#include "HeaderPost.h"
#include "afxwin.h"
