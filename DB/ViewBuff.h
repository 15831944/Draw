#include "HeaderPre.h"
class CDBDoc;
class __MY_EXT_CLASS__ CViewBuff
{
	//friend class CDBDoc;
public:
	int GetCount();
	POSITION GetStartBuffer();
	T_UDRD_BUFFER GetNextBuffer(POSITION& pos);
	void GetMatl(int nKey, T_MATL_K& rKey, T_MATL_D& rData);
//private:
	CViewBuff(CDBDoc* pDoc);
	~CViewBuff();
	void initialize();
private:

	const CDBDoc* m_pDoc;
};

#include "HeaderPost.h"

