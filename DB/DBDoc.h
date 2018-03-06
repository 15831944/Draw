#pragma once
#include "HeaderPre.h"
class CDataMemb;
class CMatlDB;
class CAttrCtrl;
class CDataCtrl;
class CEditData;
class CUndoCtrl;
class __MY_EXT_CLASS__ CDBDoc : public CDocument
{
	friend class CEditData;
	DECLARE_DYNCREATE(CDBDoc)
protected:
	CDBDoc();
	static CDBDoc* m_pDBDoc;
public:
	CEditData * m_pEditData;
	CUndoCtrl * m_pUndoCtrl;
public:
	CAttrCtrl * m_pAttrCtrl;
	CDataCtrl* m_pDataCtrl;
	CMatlDB* m_pMatlDB;
	CDataMemb* m_memb;
	static CDBDoc* GetDocPoint();
public:
	void UpdateViews(LPARAM lUpdateType);
	DECLARE_MESSAGE_MAP()
};
#include "HeaderPost.h"
