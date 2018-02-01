
#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MFadeEffect;

		// jpahn
		// OnFade 직접 제어할때 사용.
		// 갱신될때 Invalidate 외에 해줘야할 작업이 있을 때 사용.
		// OnFade() 직접 호출해야 함.
		// Create(CFadeEffectCtrl* pCtrl) 를 사용해야 효력있음.
		class __MY_EXT_CLASS__ MFadeEffectCtrl
		{
			friend MFadeEffect;
		protected:
			virtual void OnFade(MFadeEffect* pFade) = 0;
		};


		// Control에 Fade In/Out, Animation 효과를 지원
		class __MY_EXT_CLASS__ MFadeEffect
		{
		public:
			MFadeEffect();
			virtual ~MFadeEffect();

		public:
			// 모니터 주사율이 보통 60Hz 이므로
			// 초당 60 번 갱신하고 싶을때 Elapse 로 사용
			static const UINT ELAPSE_DEFAULT = 1000 / 60;
			// 최고값으로 추천 (GetFade()해서 Alpha 값으로 바로 쓰면 됨)
			// 꼭 이걸로 하지는 않아도 됨
			static const int FADE_MAX = 0xFF;

		protected:
			// hWnd, pCtrl 둘 중 하나만 사용함
			HWND m_hWnd;
			MFadeEffectCtrl* m_pCtrl;
			UINT_PTR m_nTimerID;

		protected:
			UINT m_nFadeStep; // Fade 가 몇 단계 만에 종료될 것인가. 0일 경우 Timer 안돌리고 끝남. (Timer 몇 번 돌릴건가)
			int m_nFadeCur;   // 현재 Fade 값. (Fade 중 : 현재 Fade 값. Fade 끝 : 마지막 Fade 종료값)
			int m_nFadeEnd;   // Fade 종료값.  (Fade 중 : Fade 종료값.  Fade 끝 : 마지막 Fade 종료값)
			int m_nFadeInc;   // Fade 증가값.  (Fade 중 : 단계별 m_nFadeCur 증가치  Fade 끝 : 0)

		public:
			// !! 꼭 OnDestroy()에서 Destory() 호출해주귀
			// Fade 중에 컨트롤이 Destroy되면 이상 동작함.
			void Create(MFadeEffectCtrl* pCtrl);
			void Create(HWND hWnd);
			void Destroy();

		protected:
			static CMap<UINT_PTR, UINT_PTR, MFadeEffect*, MFadeEffect*> s_map;
			static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

		public:
			UINT GetFadeStep() const { return m_nFadeStep; }
			// Fade 중일 경우 실시간 반영되지는 않음.
			// 다음 Fade 부터 적용.
			void SetFadeStep(UINT nFadeStep) { m_nFadeStep = nFadeStep; }
			BOOL IsFading() const { return (m_nFadeInc != 0); }
			BOOL IsFadeEnded() const { return !IsFading(); }
			int GetFade() const { return m_nFadeCur; }
			double GetFadeDouble(int nFadeMax) const { return m_nFadeCur / nFadeMax; }
			int GetFadeEnd() const { return m_nFadeEnd; }
			UINT_PTR GetTimerID() const { return m_nTimerID; }

		public:
			// (nFadeCur == nFadeEnd) 될 때까지 Timer를 m_nFadeStep회 돌린다.
			// - return
			//  TRUE : Fade 시작.
			//         (nFadeCur == nFadeEnd) 인데 Fade 중이어서 Timer 종료시킴.
			//  FALSE : Fade 중이었는데 nFadeEnd가 현재 m_nFadeEnd와 동일해서 호출 무시하고 이전 Fade를 계속 진행.
			//          (nFadeCur == nFadeEnd) 이고 Fade 중 아님. 아무것도 안함.
			//  (아무것도 안하고 return 할 경우 FALSE)
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