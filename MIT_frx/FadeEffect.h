
#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MFadeEffect;

		// jpahn
		// OnFade ���� �����Ҷ� ���.
		// ���ŵɶ� Invalidate �ܿ� ������� �۾��� ���� �� ���.
		// OnFade() ���� ȣ���ؾ� ��.
		// Create(CFadeEffectCtrl* pCtrl) �� ����ؾ� ȿ������.
		class __MY_EXT_CLASS__ MFadeEffectCtrl
		{
			friend MFadeEffect;
		protected:
			virtual void OnFade(MFadeEffect* pFade) = 0;
		};


		// Control�� Fade In/Out, Animation ȿ���� ����
		class __MY_EXT_CLASS__ MFadeEffect
		{
		public:
			MFadeEffect();
			virtual ~MFadeEffect();

		public:
			// ����� �ֻ����� ���� 60Hz �̹Ƿ�
			// �ʴ� 60 �� �����ϰ� ������ Elapse �� ���
			static const UINT ELAPSE_DEFAULT = 1000 / 60;
			// �ְ����� ��õ (GetFade()�ؼ� Alpha ������ �ٷ� ���� ��)
			// �� �̰ɷ� ������ �ʾƵ� ��
			static const int FADE_MAX = 0xFF;

		protected:
			// hWnd, pCtrl �� �� �ϳ��� �����
			HWND m_hWnd;
			MFadeEffectCtrl* m_pCtrl;
			UINT_PTR m_nTimerID;

		protected:
			UINT m_nFadeStep; // Fade �� �� �ܰ� ���� ����� ���ΰ�. 0�� ��� Timer �ȵ����� ����. (Timer �� �� �����ǰ�)
			int m_nFadeCur;   // ���� Fade ��. (Fade �� : ���� Fade ��. Fade �� : ������ Fade ���ᰪ)
			int m_nFadeEnd;   // Fade ���ᰪ.  (Fade �� : Fade ���ᰪ.  Fade �� : ������ Fade ���ᰪ)
			int m_nFadeInc;   // Fade ������.  (Fade �� : �ܰ躰 m_nFadeCur ����ġ  Fade �� : 0)

		public:
			// !! �� OnDestroy()���� Destory() ȣ�����ֱ�
			// Fade �߿� ��Ʈ���� Destroy�Ǹ� �̻� ������.
			void Create(MFadeEffectCtrl* pCtrl);
			void Create(HWND hWnd);
			void Destroy();

		protected:
			static CMap<UINT_PTR, UINT_PTR, MFadeEffect*, MFadeEffect*> s_map;
			static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

		public:
			UINT GetFadeStep() const { return m_nFadeStep; }
			// Fade ���� ��� �ǽð� �ݿ������� ����.
			// ���� Fade ���� ����.
			void SetFadeStep(UINT nFadeStep) { m_nFadeStep = nFadeStep; }
			BOOL IsFading() const { return (m_nFadeInc != 0); }
			BOOL IsFadeEnded() const { return !IsFading(); }
			int GetFade() const { return m_nFadeCur; }
			double GetFadeDouble(int nFadeMax) const { return m_nFadeCur / nFadeMax; }
			int GetFadeEnd() const { return m_nFadeEnd; }
			UINT_PTR GetTimerID() const { return m_nTimerID; }

		public:
			// (nFadeCur == nFadeEnd) �� ������ Timer�� m_nFadeStepȸ ������.
			// - return
			//  TRUE : Fade ����.
			//         (nFadeCur == nFadeEnd) �ε� Fade ���̾ Timer �����Ŵ.
			//  FALSE : Fade ���̾��µ� nFadeEnd�� ���� m_nFadeEnd�� �����ؼ� ȣ�� �����ϰ� ���� Fade�� ��� ����.
			//          (nFadeCur == nFadeEnd) �̰� Fade �� �ƴ�. �ƹ��͵� ����.
			//  (�ƹ��͵� ���ϰ� return �� ��� FALSE)
			BOOL StartFade(int nFadeCur, int nFadeEnd);
			BOOL StartFade(int nFadeEnd) { return StartFade(m_nFadeCur, nFadeEnd); }
			int OnFade(int nFadeCur);
			int OnFade() { return OnFade(m_nFadeCur); }

		protected:
			BOOL EndFade();
		};
	}
}

#include "HeaderPost.h"