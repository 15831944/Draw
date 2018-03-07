#include "HeaderPre.h"
#include "DB_MATLU.h"
//class CDB_MATLU;
class __MY_EXT_CLASS__ CUndoRedo
{
public:
	CUndoRedo();
	~CUndoRedo();
	int GetCount()const;
	int AddBuffer(int nCmd);
	CList<T_UDRD_BUFFER, T_UDRD_BUFFER&>m_urbuf;
	CDB_MATLU m_matl;
private:
	int m_nBuffer;
	int m_nIndex;
	T_UDRD_INDEX m_idx;
	T_UDRD_BUFFER m_buf;
	CList<T_UDRD_INDEX, T_UDRD_INDEX&>m_uridx;
	void IncreaseBuffer() { m_nBuffer++; }
	void IncreaseIndex() { m_nIndex++; }
};

#include "HeaderPost.h"
