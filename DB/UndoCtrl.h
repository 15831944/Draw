#include "HeaderPre.h"
class CDBDoc;
class CUndoRedo;
class CDataMemb;
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
	void UndoRedo(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbf,CDataMemb* pMemb,BOOL bCancel = FALSE,int nUndoCount = 1);
private:
	int CmdRever(int nCmd);
	void UndoRedoCase(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbuf,CDataMemb* pDataMemb,int nCmd,int nKey);
	void DoUndoMatl(CUndoRedo* pUndo,CUndoRedo* pRedo,CUndoRedo* pViewbuf,CDataMemb* pMemb,int nCmd,int nKey);
private:
	CDBDoc * m_pDoc;
};



#include "HeaderPost.h"

