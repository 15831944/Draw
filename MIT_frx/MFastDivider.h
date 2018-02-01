#pragma once

#include "HeaderPre.h"

// jpahn
// 2�� ���������� ���� ������ ����� ��Ʈ�������� ������ �ϱ� ���� Ŭ���� ����
// TODO: ���߿� lib�� �ű��.
// TODO: MFastDivider �� �׳� ��� ���Ͱ� �����ؾ� ��. ����� �м��ؼ� Ȯ���غ���. 
namespace mit
{
	namespace frx
	{
		template<typename TYPE, int N>
		class MFastDivider
		{
			static_assert(N > 0, "0�� ���ǹ�");
			static_assert(N < (int)(sizeof(TYPE) * 8), "TYPE �� Bit �� ���� Ŭ ���� ����");
		public:
			static const int BIT_COUNT = N;
			static const TYPE REMAINDER_MASK = (0x01 << BIT_COUNT) - 1;
			static const TYPE DEVIDE_BY = 0x01 << BIT_COUNT;
		public:
			static BOOL Divide(TYPE val) { return val >> BIT_COUNT; }
			static TYPE Multiple(TYPE val) { return val << BIT_COUNT; }
			static void SelfDivide(TYPE& val) { val >>= BIT_COUNT; }
			static void SelfMultiple(TYPE& val) { val <<= BIT_COUNT; }
			static TYPE Remainder(TYPE val) { return val & REMAINDER_MASK; }
			static BOOL IsDivisible(TYPE val) { return !Remainder(val); }
		};
		
		template<typename TYPE>
		class MFastDividerN
		{
		public:
			MFastDividerN(int nBitCount) :
				m_nBitCount(nBitCount),
				m_nReminderMask((0x01 << nBitCount) - 1),
				m_nDevideBy(0x01 << nBitCount) { ASSERT(nBitCount >= 0); }
		private:
			const int m_nBitCount;
			const TYPE m_nReminderMask;
			const TYPE m_nDevideBy;
		public:
			int GetBitCount() const { return m_nBitCount; }
			TYPE GetDevideBy() const { return m_nDevideBy; }
		public:
			TYPE Divide(TYPE val) const { return val >> m_nBitCount; }
			TYPE Multiple(TYPE val) const { return val << m_nBitCount; }
			void SelfDivide(TYPE& val) const { val >>= m_nBitCount; }
			void SelfMultiple(TYPE& val) const { val <<= m_nBitCount; }
			TYPE Remainder(TYPE val) const { return val & m_nReminderMask; }
			BOOL IsDivisible(TYPE val) const { return !Remainder(val); }
		public:
			static int GetBitCount(TYPE val) { return val == 0 ? 0 : (int)(std::log(val) / std::log(2)); }
		};
	}
}

#include "HeaderPost.h"
