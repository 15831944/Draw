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
private:
	CDBDoc * m_pDoc;
};



#include "HeaderPost.h"

