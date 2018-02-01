#pragma once

#include "MSExcel.h"

#include "HeaderPre.h"
#include <vector>

namespace mit
{
	namespace frx
	{
		class MTable;
		class __MY_EXT_CLASS__ MTableExportToExcel : public CWnd
		{
		public:
			MTableExportToExcel();
			virtual ~MTableExportToExcel();

		public:
			CMSExcel*     m_pExcel;
			MTable*		  m_pTable;
			std::vector<short> m_svDelRowArray;
			CArray<CBCGPGridRange, CBCGPGridRange&> m_aMergeArray;

			CString			m_strFileFullName;
			CString			m_szCell;
			int				m_FirstRow;
			int				m_FirstCol;
			int				m_LastRow;
			int				m_LastCol;
			int				m_nHeaderRowCount;

		public:
			void ExportExcel(mit::frx::MTable* pGrid , CString strTableName);
			BOOL ConnectGrid(mit::frx::MTable* pGrid);

		protected:
			int SaveExcelFile(CString strTableName);            // Export to Excel File for Table...
			// Get Existed Excel Process ID.
			// arProcID : process id list existed.
			BOOL GetExistedExcelProcessID(CArray<unsigned int, unsigned int>& arProcID);
			
			// About Delete Used Excel Process.
			// arProcID : process id list to kill.
			DWORD KillExcelProcess(CArray<unsigned int, unsigned int>& arProcID);
			
			// Check Is Contains current Process ID in Existed Process IDs.
			// [param] arProcID : process id list.
			// [param] procID : process id to check whether contained in the list.
			BOOL IsContainsProcessID(CArray<unsigned int, unsigned int>& arProcID, unsigned int procID);

			void SetSheetPage(CString strSheet);
			BOOL IsEmptyCurrentRow(int nRow);
			void DeleteEmptyCells();
			void MergeCell(MHashMap<int,int>& mapHidecol);
			void SetCellStyle(const CBCGPGridItem* pItem);
			BOOL CheckMergeRowCol(int nFirstRow, int nFirstCol, int nLastRow, int nLastCol);
			void CollectMergeRange(const CBCGPGridItem* pItem);
			void SetRowColInFormat(CString strCell, int nRow, int nCol);
			BOOL CheckInterruption();			
			virtual BOOL ReplaceSymbolByTempChar(CString &sParam);
		};
	}
}

#include "HeaderPost.h"
