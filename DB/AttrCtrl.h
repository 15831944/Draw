#pragma once

#include "HeaderPre.h"

class CDataMemb;
class CDBDoc;
class __MY_EXT_CLASS__ CAttrCtrl
{
	friend class CDBDoc;
private:
	CAttrCtrl(CDBDoc* pDoc);
	~CAttrCtrl();
	void initialize();
public:
	T_MATL_K GetStartNumMatl();
	T_SECT_K GetStartNumSect();
	int GetCountMatl();
	POSITION GetStartMatl();
	//POSITION
	void GetNextMatl(POSITION& rNextPostion, T_MATL_K& Key, T_MATL_D& rData);
	BOOL GetMatl(T_MATL_K Key, T_MATL_D& rData);
	BOOL ExistMatl(T_MATL_K Key);
	BOOL ExistSect(T_SECT_K Key);
private:
	CDBDoc * m_pDoc;
	CDataMemb* m_pDataMemb;
};
#include "HeaderPost.h"

