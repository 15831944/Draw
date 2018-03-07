#include "HeaderPre.h"
class CModelessDlgCtrl;
class __MY_EXT_CLASS__ CDocBase : public CDocument
{
	DECLARE_DYNCREATE(CDocBase)
protected:
	CDocBase();
	static CDocBase*m_pDocBase;
public:
	CModelessDlgCtrl * m_pDlgCtrl;
	virtual ~CDocBase() {}
	DECLARE_MESSAGE_MAP()
};


#include "HeaderPost.h"
