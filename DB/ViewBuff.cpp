#include "stdafx.h"
#include "DBDoc.h"
#include "UndoRedo.h"
#include "ViewBuff.h"


CViewBuff::CViewBuff(CDBDoc* pDoc)
{
	m_pDoc = pDoc;
}

CViewBuff::~CViewBuff()
{}

int CViewBuff::GetCount()
{
	return m_pDoc->m_vbuff->GetCount();
}

POSITION CViewBuff::GetStartBuffer()
{
	return m_pDoc->m_vbuff->m_urbuf.GetHeadPosition();
}

T_UDRD_BUFFER CViewBuff::GetNextBuffer(POSITION& pos)
{
	return m_pDoc->m_vbuff->m_urbuf.GetNext(pos);
}

void CViewBuff::GetMatl(int nKey, T_MATL_K& rKey, T_MATL_D& rData)
{
	T_MATL_UDRD_D udata;
	ASSERT(m_pDoc->m_vbuff->m_matl.Get(nKey, udata));
	rKey = udata.Key;
	rData = udata.data;
}

void CViewBuff::initialize()
{

}