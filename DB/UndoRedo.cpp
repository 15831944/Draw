#include "stdafx.h"
#include "UndoRedo.h"

CUndoRedo::CUndoRedo() 
{
	m_nBuffer = 0;
	m_nIndex = 0;
}

CUndoRedo::~CUndoRedo() {}

int CUndoRedo::GetCountidx()const
{
	return static_cast<int>(m_uridx.GetCount());
}
int CUndoRedo::GetCountbuf()const
{
	return static_cast<int>(m_urbuf.GetCount());
}
int CUndoRedo::AddBuffer(int nCmd)
{
	IncreaseBuffer();
	m_buf.nCmd = nCmd;
	m_buf.Index = m_nIndex;
	m_buf.nKey = m_nBuffer;
	m_urbuf.AddTail(m_buf);
	return m_nBuffer;
}
void CUndoRedo::StartCmd(const CString& strCmd,int nCommandType)
{
	IncreaseIndex();
	m_idx.Index = m_nIndex;
	m_idx.nCommandType = nCommandType;
	m_idx.strCmd = strCmd;
	m_uridx.AddTail(m_idx);
}
void CUndoRedo::ClearBuffer()
{
	m_uridx.RemoveAll();
	m_urbuf.RemoveAll();
}