#pragma once

#include "DB_ST_DT.h"
#include "HeaderPre.h"

class CDataMemb;
class CDBDoc;
class __MY_EXT_CLASS__ CAttrCtrl
{
	friend class CDBDoc;
private:
	CAttrCtrl(CDBDoc* pDoc);
	~CAttrCtrl();
private:
	
	CDataMemb* m_pDataMemb;
	CDBDoc* m_pDoc;
	void initialize();
public:
	T_MATL_K GetStartNumMatl();
};

#include "HeaderPost.h"
