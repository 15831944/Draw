#pragma once

#include <map>

#define D_FMT_DEFAULT		0
#define D_FMT_SCIENTIFIC	1
#define D_FMT_FIXED			2
#define D_FMT_GENERAL		3

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MFormatInfo
		{
		public:
			MFormatInfo() {	 Initialize(); }
			MFormatInfo(int nType, int nDigit) :
				m_nType(nType),
				m_nPrecision(nDigit)
			{
				UpdateFormat();
			}
			MFormatInfo(MFormatInfo& rSrc)
			{
				*this = rSrc;
			}

			MFormatInfo& operator=(const MFormatInfo& rData )
			{
				if( this == &rData ) return *this;

				m_nType			= rData.m_nType;
				m_nPrecision	= rData.m_nPrecision;
				m_strFormat		= rData.m_strFormat;

				return *this;
			}
			
		private:
			int m_nType;  // 일반, 지수, 고정...
			int m_nPrecision; // 지수, 고정 일 경우 자리수 지정.
			CString m_strFormat;
			static MFormatInfo s_default; // TODO: 이걸론 뭔가 부족한 느낌
			
		public:
			void Initialize() 
			{
				m_nType = D_FMT_DEFAULT;
				m_nPrecision = 6;
				m_strFormat.Empty();
			}
		public:
			int GetRawType() const { return m_nType; }
			int GetRawPrecision() const { return m_nPrecision; }
			const CString& GetRawFormat() const { return m_strFormat; }
			int GetType() const { return m_nType == D_FMT_DEFAULT ? s_default.m_nType : m_nType; }
			int GetPrecision() const { return m_nType == D_FMT_DEFAULT ? s_default.m_nPrecision : m_nPrecision; }
			const CString& GetFormat() const { return m_nType == D_FMT_DEFAULT ? s_default.m_strFormat : m_strFormat; }
		public:
			void SetFormatInfo(int nType, int nPrecision)
			{
				m_nType = nType;
				m_nPrecision = nPrecision;
				UpdateFormat();
			}
		private:
			void UpdateFormat()
			{
				switch (m_nType)
				{
				case D_FMT_FIXED: m_strFormat.Format(_T("%%.%df"), m_nPrecision); break;
				case D_FMT_SCIENTIFIC: m_strFormat.Format(_T("%%.%de"), m_nPrecision); break;
				case D_FMT_GENERAL: m_strFormat.Format(_T("%%.%dg"), m_nPrecision); break;
				case D_FMT_DEFAULT: m_strFormat.Empty(); break;
				default: ASSERT(0); 
				}
			}
		};

		class MTable;
		class __MY_EXT_CLASS__ MGridColumnsInfo : public CBCGPGridColumnsInfoEx
		{
			friend class MTable;
			friend class MTableExportToExcel;

		public:
			static const int DEFAULT_WIDTH = 60;
			static const int DEFAULT_WIDTH_INTEGER = 70;
			static const int DEFAULT_WIDTH_FLOAT = 80;
			static const int DEFAULT_WIDTH_BOOLEAN = 50;
			static const int DEFAULT_WIDTH_STRING = 70;

		public:
			MTable* GetTable() const;

		public:
			MGridColumnsInfo(void);
			virtual ~MGridColumnsInfo(void);

			std::map<int, MFormatInfo*>   m_smColumnFormat;  // 일반, 지수, 고정...

			bool AddHeaderItem(CBCGPGridRange& MergeRange, int nColumn = 0, LPCTSTR lpszLabel = NULL, int nAlign = HDF_LEFT, int iImage = -1); 
			bool GetMergedHeaderItem (int nColumn, int nLine, CBCGPGridRange& MergeRange, CString& strTitle) const;
			bool GetColumnFormat(int nCol, MFormatInfo& info);
			void SetColumnFormat(int nCol, MFormatInfo& info);
			void SetColumnFormat(int nStartCol, int nEndCol, MFormatInfo& info);
		};
	}

}

#include "HeaderPost.h"