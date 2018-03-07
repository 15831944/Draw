#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CUndoCtrl
{
	friend class CDBDoc;
private:
	CUndoCtrl(CDBDoc* pDoc);
	~CUndoCtrl();
	void initialize();
public:
	void CloseEditDB();
	void AddUndoMatl(int nCmd, T_MATL_K Key, T_MATL_D& rData);
private:
	CDBDoc * m_pDoc;
};



#include "HeaderPost.h"

