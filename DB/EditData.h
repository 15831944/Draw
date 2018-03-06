#pragma once
#include "HeaderPre.h"

class CDBDoc;
class CDataMemb;
class __MY_EXT_CLASS__ CEditData
{
	friend class CDBDoc;
	friend class CDataCtrl;
private:
	CEditData(CDBDoc* pDoc);
	~CEditData();
	void initialize();

	BOOL AddMatl(T_MATL_K Key, T_MATL_D& rData);
	BOOL AddMatd(T_MATL_K Key, T_MATD_D& rData);
private:
	CDBDoc * m_pDoc;
	CDataMemb* m_pDataMemb;
};




#include "HeaderPost.h"


