#pragma once
#include "AttrCtrl.h"
#include "DataMemb.h"



#include "MatlDB.h"


#include "HeaderPre.h"

class __MY_EXT_CLASS__ CDBDoc : public CDocument
{
	DECLARE_DYNCREATE(CDBDoc)
protected:
	CDBDoc();
	static CDBDoc* m_pDBDoc;
public:
	CAttrCtrl * m_pAttrCtrl;
	CMatlDB* m_pMatlDB;
	CDataMemb* m_memb;
	static CDBDoc* GetDocPoint();
	DECLARE_MESSAGE_MAP()
};
#include "HeaderPost.h"
