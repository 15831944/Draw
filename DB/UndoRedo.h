#include "HeaderPre.h"
#include "DB_MATLU.h"
//class CDB_MATLU;
class __MY_EXT_CLASS__ CUndoRedo
{
public:
	CUndoRedo();
	~CUndoRedo();
	int GetCountidx()const;
	int GetCountbuf()const;
	int AddBuffer(int nCmd);
	void StartCmd(const CString& strCmd,int nCommandType);
	void ClearBuffer();

public:
	CList<T_UDRD_BUFFER, T_UDRD_BUFFER&>m_urbuf;
	CList<T_UDRD_INDEX, T_UDRD_INDEX&>m_uridx;
	CDB_MATLU m_matl;
	void DecreaseBuffer(){m_nBuffer--;}
private:
	int m_nBuffer;
	int m_nIndex;
	T_UDRD_INDEX m_idx;
	T_UDRD_BUFFER m_buf;

	void IncreaseBuffer() { m_nBuffer++; }
	void IncreaseIndex() { m_nIndex++; }
};

#include "HeaderPost.h"
