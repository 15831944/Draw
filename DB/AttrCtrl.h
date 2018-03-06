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
private:
	T_MATL_K GetStartNumMatl();
private:
	CDBDoc * m_pDoc;
	CDataMemb* m_pDataMemb;
};
#include "HeaderPost.h"

