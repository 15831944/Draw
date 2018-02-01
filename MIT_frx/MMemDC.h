#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		// CBCGPMemDC �� Alpha ���� �� �Ծ ���� MemDC
		// ���������� uxthema.dll �� BufferedPaintSetAlpha �� ���µ� �װ� �� �Դ���
		// �� �׷��� �𸣰���. �Ф�
		// Alpha �� ���� ���� �ٸ��� ���ư����� ����
		// �׶�� Scale �̶� Alpha �� ���ÿ� �� ������...
		// �׽�Ʈ�� ���غôµ� �ڵ尡 �� �׷��� ������.
		// ���߿� �ʿ����� ��� �����Ѵ�.
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