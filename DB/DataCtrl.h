#pragma once

#include "DB_ST_DT.h"
#include "HeaderPre.h"

class CDataMemb;
class CDBDoc;
class CEditData;
class CUndoCtrl;
class __MY_EXT_CLASS__ CDataCtrl
{
	friend class CDBDoc;
public:
	BOOL AddMatl(T_MATL_K, const T_MATL_D& rData);
	BOOL AddMatl(CArray<T_MATL_K, T_MATL_K>& rKey, CArray<T_MATL_D, const T_MATL_D&>& rData);
private:
	CDataCtrl(CDBDoc* pDoc);
	~CDataCtrl();
	void initialize();
	BOOL EndEdit(BOOL bEnd = TRUE);
private:
	CDBDoc * m_pDoc;
	CEditData * m_pEditData;
	CUndoCtrl* m_pUndoCtrl;
};

#include "HeaderPost.h"
