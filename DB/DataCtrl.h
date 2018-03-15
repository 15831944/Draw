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
	BOOL AddMatl(T_MATL_K Key, const T_MATL_D& rData);
	BOOL AddMatl(CArray<T_MATL_K, T_MATL_K>& rKey, CArray<T_MATL_D, const T_MATL_D&>& rData);
	BOOL DelMatl(T_MATL_K Key);
	BOOL DelMatl(CArray<T_MATL_K, T_MATL_K>& rKey);
	BOOL AddSect(T_SECT_K Key, const T_SECT_D& rData);
	BOOL AddSect(CArray<T_SECT_K, T_SECT_K>& rKey, CArray<T_SECT_D, const T_SECT_D&>& rData);
	BOOL DelSect(T_SECT_K Key);
	BOOL DelSect(CArray<T_SECT_K, T_SECT_K>& rKey);
private:
	CDataCtrl(CDBDoc* pDoc);
	~CDataCtrl();
	void initialize();
	BOOL StartEdit(const CString& strCmd,int nCmdType);
	BOOL EndEdit(BOOL bEnd = TRUE);
private:
	CDBDoc * m_pDoc;
	CEditData * m_pEditData;
	CUndoCtrl* m_pUndoCtrl;
	CAttrCtrl* m_pAttrCtrl;
};

#include "HeaderPost.h"
