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
		
		// �۾��Լ������� ���������� ����ϴ� ���� ��õ��.
		// (CWaitCursor ó��...)
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
			// ProgressBar Range �� �ʹ� ū �� �ѱ�� ����� ����� ���Ѵ�. 
			// Range�� �׻� 0~100 ������ ���߱� ���� ����ϱ� ���� ��.
			MFastDividerN<int> m_divider;  
			DWORD m_tick;
			static const DWORD PEEK_INTERVAL = 100;
			void (MTBProgressCtrlHelper::*m_pfPeekMessage)();

		public:
			// nLower, nUpper ��� ���� ���� (����� ��� ������)
			// �׳� ������ ������� ȣ���ϱ�.
			// ���������� �˾Ƽ� 100 �ܰ������� �ɰ��� ProgressBar �����Ų��.
			MTBProgressCtrlHelper(ITable* pTable, int nLower, int nUpper, 
				BOOL bCanCancel = FALSE, const CString& strText = CString(), BOOL bDrawPercentage = FALSE, 
				POSITION* pMyInstancePos = NULL);
			~MTBProgressCtrlHelper();

		public:
			int GetPercentage() const;
			CString GetPercentageText() const;

		public:
			void SetText(const CString& strText);
			// �� ���� ���� 1�� ���ϸ鼭 Upper �� ������ ȣ���ϸ� ��.
			// �Ϻη� ����� ����ϰų� ���� ���� �׳� ȣ���ϴ� ���� ����.
			void SetPos(int nPos);

		private:
			void CheckButtonCancel(const MSG& msg);
			void CheckEscapeKeyCancel(const MSG& msg);

		public:
			// SetPos() ���� ȣ���������� �����̰� ������ ��� ������ �󵵷� ���� ȣ��.
			// (�� ���� ������ �ʹ� �� SetProgressPos() ȣ���� ���ϰ� �̷��� ��� ������ ������ �� �ִ�)
			// (���ɿ� ū ���� �����鼭 ����ڰ� �����̸� ũ�� ������ �������� �󵵷� ȣ��)
			void PeekMessage();
			// ESC �� Cancel ��ư���� ��Ҹ� �����ϰ� �ٸ� ����� �� �� ����.
			// �ٸ���麸�� ������ ����
			void PeekMessageCancelOnly();
			// Progress �� Table �� ��� ����.
			// �����ؼ� ���� ������ ����.
			void PeekMessageWithoutTable();
			// Progress �� ��� �ٸ� �۾� ����.
			// �� �����ؼ� ���� ������ ����.
			void PeekMessageAll();
			
		private:
			static CAtlMap<ITable*, MTBProgressCtrlHelper*> s_mapHelper;
		public:
			// �Լ����� ���������� Helper �� �����ߴ�.
			// �׷��� �۾��� �� �Լ� �ȿ��� �̷����� �ʴ´�. 
			// Helper�� ���ڷ� �ް� �ٴϰų� ��� �����صα�� �δ㽺����.
			// �̷��� Table �� �ּҷ� �����ߴ� Helper �� �ٽ� �� �� �ִ�.
			//  ! ����: ��ü�� ������� �翬�� Map ������ ������.
			static MTBProgressCtrlHelper* LookupInstance(ITable* pTable);
			// ������ �ʹ� �߿��� ����̶� Lookup() ������帶�� �δ㽺����.
			// �׷��� �����ڿ��� POSITION �޾ư��� ��� �����ϴٰ� �� �Լ� ����.
			//  ! ����: �� �Լ����� ��ü ���翩�� Ȯ�� �� ��.
			//          �׷��� ��ü ������� �޾ư� POSITION �� NULL �� ���� �ٲ� ������.
			static MTBProgressCtrlHelper* GetInstance(POSITION pos);
		};



		inline int MTBProgressCtrlHelper::GetPercentage() const
		{
			return (int)((double)(m_nPos - m_nLower) / (double)(m_nUpper - m_nLower) * 100.0);
		}

		inline CString MTBProgressCtrlHelper::GetPercentageText() const
		{
			// Percent ����� �ڸ��� %d �� �־�� ��.
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
			// ������ ���� ���� üũ�ؼ� ȣ���ϱ��...
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
			// ������ ���� ���� üũ�ؼ� ȣ���ϱ��...
			ASSERT(msg.message == WM_KEYDOWN);
			// TODO: Exception ���� ����°ɷ�..
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
			ASSERT(s_mapHelper.Lookup(pTable)); // ��ü�� �̹� �������
			return s_mapHelper.Lookup(pTable)->m_value;
		}

		inline MTBProgressCtrlHelper* MTBProgressCtrlHelper::GetInstance(POSITION pos)
		{
			return s_mapHelper.GetAt(pos)->m_value;
		}
	}
}

#include "HeaderPost.h"
