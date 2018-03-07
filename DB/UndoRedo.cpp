#include "stdafx.h"
#include "UndoRedo.h"

CUndoRedo::CUndoRedo() 
{
	m_nBuffer = 0;
	m_nIndex = 0;
}

CUndoRedo::~CUndoRedo() {}

int CUndoRedo::GetCount()const
{
	return static_cast<int>(m_uridx.GetCount());
}

int CUndoRedo::AddBuffer(int nCmd)
{
	IncreaseBuffer();
	IncreaseIndex();
	m_idx.Index = m_nIndex;
	m_idx.nCommandType = nCmd;
	m_idx.strCmd = _T("Ìí¼Ó²ÄÁÏ");
	m_buf.nCmd = nCmd;
	m_buf.Index = m_nIndex;
	m_buf.nKey = m_nBuffer;
	m_urbuf.AddTail(m_buf);
	m_uridx.AddTail(m_idx);
	return m_nBuffer;
}