#pragma once
class CDBDoc;
class CCMDlgBase : public CDialog
{
public:
	CCMDlgBase(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CCMDlgBase();

public:
	CDBDoc * m_pDoc;
	virtual void PostNcDestroy();
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	DECLARE_MESSAGE_MAP()
private:
	virtual void OnUpdate(CWnd* pSender, LPARAM lParam, CObject* pHint);
protected:
	afx_msg LRESULT OnUpdateDlg(WPARAM wParam, LPARAM lParam);
};

