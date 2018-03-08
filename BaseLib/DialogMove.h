#pragma once
enum ENUM_CDIALOG_MOVE
{
	D_INIT_POS_DEF,
	D_INIT_POS_LT,
	D_INIT_POS_LB,
	D_INIT_POS_RT,
	D_INIT_POS_RB,
};
#include "HeaderPre.h"
class __MY_EXT_CLASS__ CDialogMove : public CDialog
{
public:
	CDialogMove(UINT nResID,CWnd* pParent);
	virtual ~CDialogMove();
	ENUM_CDIALOG_MOVE m_nInitPos;
	int m_nLeftMargin;
	int m_nTopMargin;
	void SetInitPos(ENUM_CDIALOG_MOVE nPos = D_INIT_POS_DEF, int nLeftMargin = 0, int nTopMargin = 0);
protected:
	virtual BOOL OnInitDialog();
private:
	void MoveDlgToInitPos();
};


#include "HeaderPost.h"