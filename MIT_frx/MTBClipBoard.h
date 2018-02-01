#pragma once

#include "ITable.h"
#include "ITBClipboard.h"
#include "MGridRow.h"
#include "MGridItem.h"

#include <vector>

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class MTable;
		class MTBSchemaBase;
		class MGridRow;

		// 기본적으로 TableDB 종속적이지만
		// MTable 에 대한 종속도 있다.
		// 파싱할때 MGridRow 를 사용하기 때문
		// 즉, BCG 말고 다른 Library 를 Base 로 사용하면 이 녀석도 못 쓴다.
		class __MY_EXT_CLASS__ MTBClipboard : public ITBClipboard
		{
			friend class CInitTempVariable;
		public:
			MTBClipboard(ITableDB* pTableDB);
			virtual ~MTBClipboard();

			// Table
		private:
			ITableDB* m_pTableDB;
			MTBSchemaBase* m_pSchema;
			MTable* m_pTable;
		protected:
			ITableDB* GetTableDB() const { ASSERT(m_pTableDB); return m_pTableDB; }
			MTBSchemaBase* GetSchema() const { ASSERT(m_pSchema); return m_pSchema; }
			MTable* GetTable() const { ASSERT(m_pTable); return m_pTable; }
			
			// Temp Variable (Copy/Paste 하는 동안만 사용됨)
		protected:
			BOOL m_bVisibleColumnOnly;
			BOOL m_hasKeyColumn;
			MGridRow* m_pGridRow;
			std::vector<int> m_aColumnOrder;	
		protected: // Copy
			DWORD m_dwFlags; // dwFlags - Format_CSV, Format_TabSV, Format_Html
			CBCGPGridRange m_range;		
		protected: // Paste
			CBCGPGridItemID m_idPasteTo;
			BOOL m_bPasteAppendRow;
			CAtlList<LPCVOID> m_lstPasteRow;
		protected:
			void InitTempVariable();
			BOOL IsFormatCSV() { return m_dwFlags & CBCGPGridCtrl::Format_CSV; }
			BOOL IsFormatTabSV() { return m_dwFlags & CBCGPGridCtrl::Format_TabSV; }
			int GetRowCount() const { return m_range.m_nBottom - m_range.m_nTop + 1; }
			int GetColCount() const { return m_range.m_nRight - m_range.m_nLeft + 1; }
			int CopyPasteRowToVector(std::vector<LPCVOID>& aPasteRow);
			void ClearPasteRow();
			
			// Separator
		protected:
			static CString s_strTabSVColumnSeparator;
			static CString s_strTabSVRowSeparator;
			static CString s_strCSVColumnSeparator;
			static CString s_strCSVRowSeparator;
			CString m_strColumnSeparator;
			CString m_strRowSeparator;

			// AllocateLength
		protected:
			static const int SAMPLE_ROW_COUNT = 16;
		protected:
			virtual int GetApproximateRowLength(const std::vector<MKey>& aKey, const std::vector<LPCVOID>& aRow) = 0;
			virtual int GetPreAllocateLength(int nApproximateRowLength);
			
			// Export
		protected:
			virtual void Export(CString& strText) = 0;
			virtual void ParallelExport(int nTaskCount, CString* aText) = 0;
		protected:
			void ExportRowToText(CString& strText, MKey nKey, LPCVOID pRow, MGridRow* pGridRow);

			// Copy
		public:
			virtual BOOL Copy(DWORD dwFlags);
		protected:
			virtual int GetCopyRange(CBCGPGridRange& rangeData, CBCGPGridRange& rangeTop, CBCGPGridRange& rangeBottom);
			BOOL CopyTextToClipboard(const CStringArray& aText) const;
			HGLOBAL CopyTextToClipboardInternal(const CStringArray& aText) const;

			// Import
		protected:
			virtual BOOL Import(const CString& strText);
			virtual int ImportAppend(const CString& strText) = 0;
			virtual int ImportModify(const CString& strText) = 0;
		protected:
			void TokenizeText(CString& strToken, int& nCurIndex, const CString& strText, const CString& strSeparator);

			// Paste
		protected:
			static const int MAX_ITEM_STRING_LENGTH = 128;
		public:
			virtual BOOL Paste();
		protected:
			BOOL CheckTextFormat(const CString& strText);
			BOOL PasteTextFromClipboard();
			BOOL GetNextRowText(const CString& strText, CString& strRow, int& nCurIndex);
		};

		inline void MTBClipboard::ExportRowToText(CString& strText, MKey nKey, LPCVOID pRow, MGridRow* pGridRow)
		{
			for (int i = m_range.m_nLeft; i < m_range.m_nRight; i++)
			{
				ASSERT(i < (int)m_aColumnOrder.size());
				int nCol = m_aColumnOrder[i];
				const MTBColumn& column = GetSchema()->GetColumn(nCol);
				MGridItem* pItem = (MGridItem*)pGridRow->GetItem(nCol);
				_variant_t& varValue = const_cast<_variant_t&>(pItem->GetValue());
				switch (column.GetType())
				{
				case MTBColumn::TB_KEY: varValue = nKey; break;
				case MTBColumn::TB_FOREIGN: ASSERT(0); GetTableDB()->GetForeignItem(varValue, 0, nCol); break;
				default: column.GetItem(varValue, pRow); break;
				}
				pItem->AppendFormatItem(strText);

				strText.Append(m_strColumnSeparator);
			}

			ASSERT(m_range.m_nRight < (int)m_aColumnOrder.size());
			int nCol = m_aColumnOrder[m_range.m_nRight];
			const MTBColumn& column = GetSchema()->GetColumn(nCol);
			MGridItem* pItem = (MGridItem*)pGridRow->GetItem(nCol);
			_variant_t& varValue = const_cast<_variant_t&>(pItem->GetValue());
			switch (column.GetType())
			{
			case MTBColumn::TB_KEY: varValue = nKey; break;
			case MTBColumn::TB_FOREIGN: ASSERT(0); GetTableDB()->GetForeignItem(varValue, 0, nCol); break;
			default: column.GetItem(varValue, pRow); break;
			}
			pItem->AppendFormatItem(strText);
		}

		inline void MTBClipboard::TokenizeText(CString& strToken, int& nCurIndex, const CString& strText, const CString& strSeparator)
		{
			int nFindIndex = strText.Find(strSeparator, nCurIndex);
			strToken = (nFindIndex < 0) ? strText.Right(strText.GetLength() - nCurIndex) : strText.Mid(nCurIndex, nFindIndex - nCurIndex);
			nCurIndex = (nFindIndex < 0) ? strText.GetLength() : nFindIndex + strSeparator.GetLength();
		}

		class __MY_EXT_CLASS__ CInitTempVariable
		{
		private:
			MTBClipboard* m_pClipboard;
		public:
			CInitTempVariable(MTBClipboard* pClipboard) : m_pClipboard(pClipboard) { ASSERT(m_pClipboard); }
			~CInitTempVariable() { m_pClipboard->InitTempVariable(); }
		};
	}
}

#include "HeaderPost.h"