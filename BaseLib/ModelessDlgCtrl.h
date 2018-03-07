#include "HeaderPre.h"
struct SDlgCtrlNode
{
	UINT nIDTemplate;
	CDialog* pDlg;
};
struct SDlgCtrlUpdateArg
{
	CWnd* pSender;
	LPARAM lHint;
	CObject* pHint;
};
#define WM_UPDATE_MODELESS_DLG (WM_APP+100)
class __MY_EXT_CLASS__ CModelessDlgCtrl
{
public:
	CModelessDlgCtrl();
	~CModelessDlgCtrl();
	void Add(UINT nIDTemplate, CDialog* pDlg);
	void UpdateAllDlgs(CWnd* pWnd, LPARAM lHint, CObject* pHint);
private:
	CArray<SDlgCtrlNode, SDlgCtrlNode&>m_aDlgList;

};

#include "HeaderPost.h"
