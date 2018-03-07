#pragma once
#include "../BaseLib/DocBase.h"
#include "HeaderPre.h"
class CDataMemb;
class CMatlDB;
class CAttrCtrl;
class CDataCtrl;
class CEditData;
class CUndoCtrl;
class CModelessDlgCtrl;
class CViewBuff;
class CUndoRedo;
class __MY_EXT_CLASS__ CDBDoc : public CDocBase
{
	//friend class CEditData;
	friend class CViewBuff;

	friend class CUndoCtrl;
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
	CViewBuff* m_pViewBuff;
	static CDBDoc* GetDocPoint();
private:
	CUndoRedo * m_undo;				//undo buffer
	CUndoRedo * m_vbuff;			//update view buffer
public:
	void UpdateViews(LPARAM lUpdataType);
	void UpdateAllViews(CView* pSender, LPARAM lHint, CObject* pHint = NULL);
	DECLARE_MESSAGE_MAP()
};
#include "HeaderPost.h"
