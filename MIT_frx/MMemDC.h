#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// CBCGPMemDC 에 Alpha 값이 안 먹어서 만든 MemDC
		// 내부적으로 uxthema.dll 의 BufferedPaintSetAlpha 를 쓰는데 그게 안 먹더라
		// 왜 그런지 모르겠음. ㅠㅜ
		// Alpha 값 있을 때만 다르게 돌아가도록 구현
		// 그라고 Scale 이랑 Alpha 랑 동시에 안 먹을듯...
		// 테스트는 안해봤는데 코드가 딱 그렇게 생겼음.
		// 나중에 필요해질 경우 구현한다.
		class __MY_EXT_CLASS__ MMemDC
		{
		public:
			static BOOL	m_bUseMemoryDC;

			MMemDC(CDC& dc, CWnd* pWnd, BYTE alpha = 0, double dblScale = 1.0);
			MMemDC(CDC& dc, const CRect& rect, BYTE alpha = 0, double dblScale = 1.0);

			virtual ~MMemDC();

			CDC& GetDC ()			{	return m_bMemDC ? m_dcMem : m_dc;	}
			BOOL IsMemDC () const	{	return m_bMemDC;					}
			BOOL IsVistaDC () const	{	return m_hBufferedPaint != NULL;	}

		protected:
			CDC&		m_dc;
			BOOL		m_bMemDC;
			HANDLE		m_hBufferedPaint;
			CDC			m_dcMem;
			CBitmap		m_bmp;
			CBitmap*	m_pOldBmp;
			CRect		m_rect;
			BYTE		m_alpha;	// Buffered Paint only!
			double		m_dblScale;
		};
	}
};

#include "HeaderPost.h"