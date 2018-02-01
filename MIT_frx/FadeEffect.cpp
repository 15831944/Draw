#include "stdafx.h"
#include "FadeEffect.h"

#include <math.h>

using namespace mit::frx;

CMap<UINT_PTR, UINT_PTR, MFadeEffect*, MFadeEffect*> MFadeEffect::s_map;

MFadeEffect::MFadeEffect()
: m_hWnd(NULL),
m_pCtrl(NULL),
m_nTimerID(0),
m_nFadeStep(6),
m_nFadeCur(0),
m_nFadeEnd(-1),
m_nFadeInc(0)
{
}

MFadeEffect::~MFadeEffect()
{
	Destroy();
}

void MFadeEffect::Create(MFadeEffectCtrl* pCtrl)
{
	ASSERT(!m_hWnd && !m_pCtrl);
	ASSERT(pCtrl);
	m_pCtrl = pCtrl;
}

void MFadeEffect::Create(HWND hWnd)
{
	ASSERT(!m_hWnd && !m_pCtrl);
	ASSERT(hWnd);
	m_hWnd = hWnd;
}

void MFadeEffect::Destroy()
{
	m_hWnd = NULL;
	m_pCtrl = NULL;
	if (m_nTimerID)
	{
		// Fade 중일 경우
		KillTimer(NULL, m_nTimerID);
		s_map.RemoveKey(m_nTimerID);
		m_nTimerID = 0;
	}
}

void CALLBACK MFadeEffect::TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	ASSERT(hWnd == NULL && uMsg == WM_TIMER);

	MFadeEffect* pFade = NULL;
	if (!s_map.Lookup(idEvent, pFade)) { ASSERT(FALSE); return; }
	ASSERT(pFade->m_hWnd || pFade->m_pCtrl);

	if (pFade->m_hWnd)
	{
		pFade->OnFade();
		if (IsWindow(pFade->m_hWnd))
		{
			CWnd* pWnd = CWnd::FromHandle(pFade->m_hWnd);
			ASSERT(pWnd);
			pWnd->Invalidate(FALSE);
		}
	}
	else if (pFade->m_pCtrl)
	{
		pFade->m_pCtrl->OnFade(pFade);
	}
}

BOOL MFadeEffect::StartFade(int nFadeCur, int nFadeEnd)
{
	ASSERT(m_hWnd || m_pCtrl); // Create() 먼저 호출해야함!

	if (IsFading() && m_nFadeEnd == nFadeEnd) return FALSE;

	int nDiff = nFadeEnd - nFadeCur;
	if (nDiff == 0) return EndFade();
	if (m_nFadeStep == 0) return EndFade();

	m_nFadeCur = nFadeCur;
	m_nFadeEnd = nFadeEnd;
	double dFadeInc = (double)nDiff / (double)m_nFadeStep;
	if (dFadeInc >= 0.0) m_nFadeInc = (int)ceil(dFadeInc);
	else m_nFadeInc = (int)floor(dFadeInc);
	ASSERT(m_nFadeInc != 0);

	// * SetTimer *
	// Return : hWnd 가 NULL 일 경우 ID임. 0 이면 실패
	// nIDEvent : hWnd 가 NULL 일 경우 
	//                 존재하는 ID면 대체
	//                 존재하지 않으면 무시하고 new ID 사용
	m_nTimerID = SetTimer(NULL, m_nTimerID, ELAPSE_DEFAULT, TimerProc);
	ASSERT(m_nTimerID);
	s_map.SetAt(m_nTimerID, this);

	return TRUE;
}

int MFadeEffect::OnFade(int nFadeCur)
{
	m_nFadeCur = nFadeCur + m_nFadeInc;
	if (m_nFadeInc > 0 && m_nFadeCur > m_nFadeEnd) m_nFadeCur = m_nFadeEnd;
	else if (m_nFadeInc < 0 && m_nFadeCur < m_nFadeEnd) m_nFadeCur = m_nFadeEnd;

	if (m_nFadeCur == m_nFadeEnd)
	{
		VERIFY(EndFade());
	}

	return m_nFadeCur;
}

BOOL MFadeEffect::EndFade()
{
	if (!IsFading()) { ASSERT(!m_nTimerID); return FALSE; }

	m_nFadeInc = 0;
	if (m_nTimerID)
	{
		KillTimer(NULL, m_nTimerID);
		s_map.RemoveKey(m_nTimerID);
		m_nTimerID = 0;
	}

	return TRUE;
}