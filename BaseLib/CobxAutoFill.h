#pragma once
#include "HeaderPre.h"
class __MY_EXT_CLASS__ CCobxAutoFill : public CComboBox
{
public:
	CCobxAutoFill(void);
	~CCobxAutoFill(void);

	//interface
	// nMode : 0 -> same as general combo
	//         1 -> not match : select partial match, else select default
	//         2 -> not match : clear selection and edit box
	void  SetActionWhenKillFocus(int nMode, int nDefaultSel=-1) ;
	
private:
	int m_nMode;
	int m_nDefaultSel;
	int m_nCurSel;
	BOOL m_bAutoFill;
	void SendMsgSelChange(int nNewSel);
private:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnCbnEditupdate();
	afx_msg BOOL OnCbnKillfocus();
	afx_msg BOOL OnCbnSelchange();
	afx_msg BOOL OnCbnSetfocus();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


#include "HeaderPost.h"


//#pragma once
//
//#include "HeaderPre.h"
//class __MY_EXT_CLASS__ CCobxAutoFill : public CComboBox
//{
//	// Construction
//public:
//	CCobxAutoFill();
//	virtual ~CCobxAutoFill();
//
//	// Attributes
//public:
//
//	// Operations
//public:
//	// Interface
//	// nMode : 0 -> same as general combo
//	//         1 -> not match : select partial match, else select default
//	//         2 -> not match : clear selection and edit box
//	void  SetActionWhenKillFocus(int nMode, int nDefaultSel=-1) ;
//	// 현재의 문장이 어떤 것인지와 그 문장이 항목에 있는지를 얻어오는 함수 
//	BOOL  GetCurrentComboText(CString &str);
//
//	// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CCobxAutoFill)
//public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//protected:
//	virtual void PostNcDestroy();
//	//}}AFX_VIRTUAL
//
//	// Implementation
//protected:
//	BOOL    m_bAutoFill;
//	int     m_nMode;
//	int     m_nDefaultSel;
//	int     m_nCurSel;
//	BOOL    m_bIMEDisabled;
//
//protected:
//	void SendMsgSelChange(int nNewSel);
//
//	// Generated message map functions
//protected:
//	//{{AFX_MSG(CCobxAutoFill)
//	afx_msg BOOL OnEditUpdate();
//	afx_msg BOOL OnKillfocus();
//	afx_msg BOOL OnSelchange();
//	afx_msg BOOL OnSetfocus();
//	//}}AFX_MSG
//
//	DECLARE_MESSAGE_MAP()
//};
//#include "HeaderPost.h"
