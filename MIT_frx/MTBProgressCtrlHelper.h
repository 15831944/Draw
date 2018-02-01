#pragma once

#include "ITable.h"
#include "ITBProgressCtrl.h"
#include "MFastDivider.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MTBProgressCancel
		{
		public:
			enum Reason { CANCEL_BTN, ESC_KEY };
			Reason reason;
			MTBProgressCancel(Reason r) : reason(r) {}
			static MTBProgressCancel CancelBtn;
			static MTBProgressCancel EscKey;
		};
		
		// 작업함수내에서 지역변수로 사용하는 것을 추천함.
		// (CWaitCursor 처럼...)
		class __MY_EXT_CLASS__ MTBProgressCtrlHelper
		{
		private:
			ITable* m_pTable;
			ITBProgressCtrl* m_pProgressCtrl;
			HWND m_hTable;
			HWND m_hCancelBtn;
			int m_nLower;
			int m_nUpper;
			int m_nPos;
			CString m_strText;
			POSITION* m_pMyInstancePos;
			BOOL m_bDrawPercentage;
			// ProgressBar Range 로 너무 큰 값 넘기면 제대로 계산을 못한다. 
			// Range를 항상 0~100 정도로 맞추기 위해 계산하기 위한 놈.
			MFastDividerN<int> m_divider;  
			DWORD m_tick;
			static const DWORD PEEK_INTERVAL = 100;
			void (MTBProgressCtrlHelper::*m_pfPeekMessage)();

		public:
			// nLower, nUpper 계산 하지 말고 (백분율 계산 같은거)
			// 그냥 데이터 갯수대로 호출하기.
			// 내부적으로 알아서 100 단계정도로 쪼개서 ProgressBar 진행시킨다.
			MTBProgressCtrlHelper(ITable* pTable, int nLower, int nUpper, 
				BOOL bCanCancel = FALSE, const CString& strText = CString(), BOOL bDrawPercentage = FALSE, 
				POSITION* pMyInstancePos = NULL);
			~MTBProgressCtrlHelper();

		public:
			int GetPercentage() const;
			CString GetPercentageText() const;

		public:
			void SetText(const CString& strText);
			// 매 루프 마다 1씩 더하면서 Upper 될 때까지 호출하면 됨.
			// 일부러 백분율 계산하거나 하지 말고 그냥 호출하는 것이 빠름.
			void SetPos(int nPos);

		private:
			void CheckButtonCancel(const MSG& msg);
			void CheckEscapeKeyCancel(const MSG& msg);

		public:
			// SetPos() 에서 호출해주지만 딜레이가 느껴질 경우 적당한 빈도로 직접 호출.
			// (한 번의 루프가 너무 길어서 SetProgressPos() 호출이 뜸하게 이뤄질 경우 딜레이 느껴질 수 있다)
			// (성능에 큰 영향 없으면서 사용자가 딜레이를 크게 느끼지 않을만한 빈도로 호출)
			void PeekMessage();
			// ESC 와 Cancel 버튼으로 취소만 가능하고 다른 기능은 쓸 수 없다.
			// 다른놈들보다 안전한 버전
			void PeekMessageCancelOnly();
			// Progress 중 Table 만 사용 못함.
			// 주의해서 쓰지 않으면 조땜.
			void PeekMessageWithoutTable();
			// Progress 중 모든 다른 작업 가능.
			// 단 주의해서 쓰지 않으면 조땜.
			void PeekMessageAll();
			
		private:
			static CAtlMap<ITable*, MTBProgressCtrlHelper*> s_mapHelper;
		public:
			// 함수에서 지역변수로 Helper 를 생성했다.
			// 그런데 작업이 한 함수 안에서 이뤄지지 않는다. 
			// Helper를 인자로 달고 다니거나 어딘가 저장해두기는 부담스럽다.
			// 이럴때 Table 의 주소로 생성했던 Helper 를 다시 얻어갈 수 있다.
			//  ! 주의: 객체가 사라질때 당연히 Map 에서도 삭제함.
			static MTBProgressCtrlHelper* LookupInstance(ITable* pTable);
			// 성능이 너무 중요한 기능이라서 Lookup() 오버헤드마저 부담스럽다.
			// 그러면 생성자에서 POSITION 받아가서 어딘가 보관하다가 이 함수 쓴다.
			//  ! 주의: 이 함수에선 객체 존재여부 확인 못 함.
			//          그래서 객체 사라질때 받아간 POSITION 값 NULL 로 직접 바꿔 버린다.
			static MTBProgressCtrlHelper* GetInstance(POSITION pos);
		};



		inline int MTBProgressCtrlHelper::GetPercentage() const
		{
			return (int)((double)(m_nPos - m_nLower) / (double)(m_nUpper - m_nLower) * 100.0);
		}

		inline CString MTBProgressCtrlHelper::GetPercentageText() const
		{
			// Percent 출력할 자리에 %d 가 있어야 함.
			ASSERT(m_strText.Find(_LSX(%d)) >= 0);
			CString strPercentageText;
			strPercentageText.Format(m_strText, GetPercentage());
			return strPercentageText;
		}

		inline void MTBProgressCtrlHelper::SetText(const CString& strText)
		{
			if (m_bDrawPercentage)
			{
				m_strText = strText;
				m_pProgressCtrl->SetText(GetPercentageText());
			}
			else
			{
				m_pProgressCtrl->SetText(strText);
			}
		}

		inline void MTBProgressCtrlHelper::SetPos(int nPos)
		{
			if (GetTickCount() - m_tick < PEEK_INTERVAL) return;
			m_tick = GetTickCount();
			PeekMessage();
			m_nPos = m_divider.Divide(nPos);
			m_pProgressCtrl->SetPos(m_nPos);
			if (m_bDrawPercentage) m_pProgressCtrl->SetText(GetPercentageText());
		}

		inline void MTBProgressCtrlHelper::CheckButtonCancel(const MSG& msg)
		{
			// 성능을 위해 먼저 체크해서 호출하기로...
			ASSERT(msg.hwnd == m_hCancelBtn);
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				::SetCapture(m_hCancelBtn);
				break;
			case WM_LBUTTONUP:
				if (::GetCapture() == m_hCancelBtn)
				{
					::ReleaseCapture();

					CPoint pt;
					pt.x = GET_X_LPARAM(msg.lParam);
					pt.y = GET_Y_LPARAM(msg.lParam);
					CRect rect;
					GetClientRect(m_hCancelBtn, &rect);
					if (rect.PtInRect(pt))
					{
						throw MTBProgressCancel::CancelBtn;
					}
				}
				break;
			default:
				break;
			}
		}

		inline void MTBProgressCtrlHelper::CheckEscapeKeyCancel(const MSG& msg)
		{
			// 성능을 위해 먼저 체크해서 호출하기로...
			ASSERT(msg.message == WM_KEYDOWN);
			// TODO: Exception 따로 만드는걸로..
			if (msg.wParam == VK_ESCAPE) throw MTBProgressCancel::EscKey;
		}
		
		inline void MTBProgressCtrlHelper::PeekMessage()
		{
			if (m_pfPeekMessage) (this->*m_pfPeekMessage)();
		}

		inline void MTBProgressCtrlHelper::PeekMessageCancelOnly()
		{
			static MSG msg;
			if (::PeekMessage(&msg, m_hCancelBtn, NULL, NULL, PM_REMOVE))
			{
				if (msg.message != WM_SETCURSOR)
				{
					CheckButtonCancel(msg);
					if (msg.message == WM_KEYDOWN) CheckEscapeKeyCancel(msg);
					::TranslateMessage(&msg);  
					::DispatchMessage(&msg);
				}
			}
			if (::PeekMessage(&msg, NULL, WM_KEYDOWN, WM_KEYDOWN, PM_REMOVE))
			{
				CheckEscapeKeyCancel(msg);
			}
		}

		inline void MTBProgressCtrlHelper::PeekMessageWithoutTable()
		{
			static MSG msg;
			while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_SETCURSOR) continue;					
				if (msg.hwnd == m_hTable) continue;
				if (msg.hwnd == m_hCancelBtn) CheckButtonCancel(msg);
				if (msg.message == WM_KEYDOWN) CheckEscapeKeyCancel(msg);
				{
					::TranslateMessage(&msg);  
					::DispatchMessage(&msg);
				}
			}
		}

		inline void MTBProgressCtrlHelper::PeekMessageAll()
		{
			static MSG msg;
			while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_SETCURSOR) continue;
				if (msg.hwnd == m_hCancelBtn) CheckButtonCancel(msg);
				if (msg.message == WM_KEYDOWN) CheckEscapeKeyCancel(msg);
				::TranslateMessage(&msg);  
				::DispatchMessage(&msg);
			}
		}

		inline MTBProgressCtrlHelper* MTBProgressCtrlHelper::LookupInstance(ITable* pTable)
		{
			ASSERT(s_mapHelper.Lookup(pTable)); // 객체가 이미 사라졌음
			return s_mapHelper.Lookup(pTable)->m_value;
		}

		inline MTBProgressCtrlHelper* MTBProgressCtrlHelper::GetInstance(POSITION pos)
		{
			return s_mapHelper.GetAt(pos)->m_value;
		}
	}
}

#include "HeaderPost.h"
