#include "HeaderPre.h"
class CDBDoc;
class CUndoRedo;
class __MY_EXT_CLASS__ CUndoCtrl
{
	friend class CDBDoc;
private:
	CUndoCtrl(CDBDoc* pDoc);
	~CUndoCtrl();
	void initialize();
public:
	BOOL StartEditDB(const CString& strCmd,int nCommandType);
	void CloseEditDB();
	void AddUndoMatl(int nCmd, T_MATL_K Key, T_MATL_D& rData);
	void UndoRedo(CUndoRedo* pUndo,CUndoRedo* pViewbf);
private:
	CDBDoc * m_pDoc;
};



#include "HeaderPost.h"

