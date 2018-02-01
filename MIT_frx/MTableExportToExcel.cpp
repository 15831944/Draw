#include "stdafx.h"
#include "Tlhelp32.h"   // To Terminate
#include "MTableExportToExcel.h"

#include "../MIT_lib/MFileCtrl.h"
#include "MTable.h"
#include "MGridItem.h"
#include "MTBProgressCtrlHelper.h"

#include <algorithm>

#define D_COLOR_YELLOW  RGB(255,255,0  )	// Yellow
#define D_COLOR_BLUE    RGB(0  ,  0,255)	// Blue

#define EXPORT_CANCLE    -1
#define EXPORT_FAILED    0
#define EXPORT_COMPLETED 1

using namespace std;
using namespace mit;
using namespace mit::lib;
using namespace mit::frx;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MTableExportToExcel::MTableExportToExcel()
{
	m_pTable = NULL;
	m_strFileFullName = _T("");
	m_szCell          = _T("");
	m_svDelRowArray.clear();
	m_aMergeArray   .RemoveAll();
	m_FirstRow = 0;
	m_FirstCol = 0;
	m_LastRow  = 0;
	m_LastCol  = 0;
	m_nHeaderRowCount = 0;

	m_pExcel = new CMSExcel();
}

MTableExportToExcel::~MTableExportToExcel()
{
	if(m_pExcel)
	{
		delete m_pExcel;
		m_pExcel = NULL;
	}
}

void MTableExportToExcel::ExportExcel(MTable* pGrid, CString strTableName)
{ 
	if (!ConnectGrid(pGrid)) { ASSERT(0); return; }
	int nResult = SaveExcelFile(strTableName);
	if (nResult == EXPORT_FAILED)         { AfxMessageBox(_T("Export Failed!!"),   MB_OK); }
	else if (nResult == EXPORT_COMPLETED) { AfxMessageBox(_T("Export Completed!!"),MB_OK); }
	else if (nResult == EXPORT_CANCLE)    { AfxMessageBox(_T("Export Canceled!!")  ,MB_OK); }
}

int MTableExportToExcel::SaveExcelFile(CString strTableName)
{
	CString csFileName = strTableName + _LSX(.xls);
	LPCTSTR szFileName;
	//if (csFileName.IsEmpty()) szFileName = NULL;
	//else szFileName = csFileName;
	ReplaceSymbolByTempChar(strTableName);

	CFileDialog fd(FALSE, _LSX(.xls), strTableName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, 
		_LSX(EXCEL File(*.xls)|*.xls|All File(*.*)|*.*||), NULL);

	if (fd.DoModal() == IDOK)
	{ 
		m_strFileFullName = fd.GetPathName();
	}
	else
		return EXPORT_CANCLE;

	if (m_strFileFullName.Compare(_T(""))==0) return FALSE;

	szFileName = m_strFileFullName;
	CArray<unsigned int, unsigned int> arProcID;

	// Create Progress Dialog.
// 	CTextProgressDlg* pDlg = CTextProgressDlg::DoModeless();
// 	if (pDlg)
	{ 
		try
		{

			GetExistedExcelProcessID(arProcID);
#if defined(_DEBUG)
			m_pExcel->SetVisible(TRUE);
#endif  
			m_pExcel->AddBook();
			///// add & active new sheet
			if (strTableName.Compare(_T(""))==0) strTableName = _LSX(Sheet1);
			SetSheetPage(strTableName);

			int nCol_Max = m_pTable->GetColumnCount();
			MHashMap<int,int> mapHidecol; mapHidecol.InitHashTable(11);
			int nCol;
			for (nCol=0; nCol < nCol_Max; ++nCol)
			{				
				if(m_pTable->GetColumnVisible(nCol)) continue; // 숨긴 Col은 Export 하지 않는다.
				mapHidecol.SetAt(nCol,nCol);
			}

			int nRow_Max = m_pTable->GetRowCount();
			int nTotal = nCol_Max * nRow_Max + nRow_Max;
			int nCurrent = 0;

			MSimpleProfiler profiler(_T("ExportExcel(%d)"), nTotal);
			MTBProgressCtrlHelper progressBar(m_pTable, 0, nTotal, TRUE, _STR("Export To Excel... %d%%"), TRUE);

			MGridColumnsInfo* pColumnInfoEx = (MGridColumnsInfo*)m_pTable->m_pColumnsEx;
			m_nHeaderRowCount = pColumnInfoEx->GetHeaderLineCount();

			m_pExcel->SetBackColor(1, 0, m_nHeaderRowCount, nCol_Max-1, COLORREF(RGB(224,223,227)));  // header Title 의 배경색 지정
			m_pExcel->SetFontBold(1, 0, m_nHeaderRowCount, nCol_Max-1, TRUE);   // header Title 의 bold        
			
			// Align 1: 오른쪽 정렬 2: 왼쪽 정렬 3: 가운데 정렬   
			// header Title 을 중간에 Align
			m_pExcel->SetHorAlign(1, 0, m_nHeaderRowCount, nCol_Max-1, 3);

			//////////////////////////////////////////////////////////////////////////
			// 헤더 병합처리
			vector<CBCGPGridRange> svHeaderMerge;
			for( int i=0;i<nCol_Max; ++i )
			{
				BOOL bMerge = FALSE;
				for( int j=0;j<m_nHeaderRowCount; ++j)
				{
					CString strName = m_pTable->GetColumnName(i);
					m_pExcel->SetValue(j+1, i, strName);

					CBCGPGridRange MergeRange;
					if( pColumnInfoEx->GetMergedHeaderItem(i, j, MergeRange, strName) )
					{
						bMerge = TRUE;
						vector<CBCGPGridRange>::iterator itr = find( svHeaderMerge.begin(), svHeaderMerge.end(), MergeRange);
						if( itr == svHeaderMerge.end() )
						{	svHeaderMerge.push_back(MergeRange);
							m_pExcel->SetValue( MergeRange.m_nTop+1, MergeRange.m_nLeft, strName);
						}
					}
				}

				if( !bMerge )
				{					
					m_pExcel->SetMergeCell(1, i, m_nHeaderRowCount, i);
				}
			}
			
			for( int i=0;i<(int)svHeaderMerge.size(); ++i )
			{
				CBCGPGridRange range = svHeaderMerge[i];
				m_pExcel->SetMergeCell( range.m_nTop+1, range.m_nLeft, range.m_nBottom+1, range.m_nRight);
			}
			// 여기까지 헤더처리 과정.
			//////////////////////////////////////////////////////////////////////////

			for (nCol=0; nCol < nCol_Max; ++nCol)
			{
				int nColWidth = m_pTable->GetColumnWidth(nCol);
				m_pExcel->SetColumnWidth((long)0, (long)nCol, (long)nRow_Max+m_nHeaderRowCount, (long)nCol, (double)(nColWidth/6));        

				for (int nRow=0; nRow < nRow_Max; ++nRow)
				{
					CBCGPGridRow* pRow = m_pTable->GetRow(nRow);
					if( !pRow ) { ASSERT(0); return EXPORT_FAILED; }

					CBCGPGridItem* pItem = pRow->GetItem(nCol);
					if( !pItem ) { ASSERT(0); return EXPORT_FAILED; }

					m_szCell = pItem->GetLabel();

					SetCellStyle(pItem);      // Cell 의 스타일을 적용

					CollectMergeRange(pItem);           // Merge 된 셀의 range를 수집
					
					SetRowColInFormat(m_szCell,nRow, nCol);  // 셀에  "/" 특수문자가 들어가 있으면 텍스트 포맷으로 변경

// 					if( nRow > m_pTable->GetExtraTopCount() && IsEmptyCurrentRow(nRow) )
// 					{
// 						vector<short>::iterator itr = find(m_svDelRowArray.begin(), m_svDelRowArray.end(), nRow );
// 						if( itr == m_svDelRowArray.end() )
// 							m_svDelRowArray.push_back((short)nRow);
// 					}
					
					m_pExcel->SetValue(nRow+m_nHeaderRowCount+1, nCol, m_szCell);

					//if(CheckInterruption()) throw exception("Export Cancled!!");  // ESC 누르면 Cancle

					// ProgressBar
					progressBar.SetPos(++nCurrent);
				}
			}
			MergeCell(mapHidecol);

			m_pExcel->SetBorder(1, 0, nRow_Max+m_nHeaderRowCount, nCol_Max-1, 1, 2); // 테두리 설정
			m_pExcel->CellOutLine(1, 0, nRow_Max+m_nHeaderRowCount, nCol_Max-1, 1, 3);

			//DeleteEmptyCells();   // Grid에 보이지 않지만 숨겨진 빈 Cell Row들을 지운다.

			if(strTableName.Compare(_LSX(Sheet1))!=0)
				m_pExcel->SetValue(0, 0, strTableName); // 첫번째 Cell에 Table 이름을 적어준다.

			m_pExcel->SaveAs(m_pExcel->GetBookName(), szFileName);
			m_pExcel->Quit();
		}
 		catch(MTBProgressCancel&)
 		{
 			KillExcelProcess(arProcID);
 			//pDlg->DestroyWindow();
 			return EXPORT_CANCLE;
 		}
		catch(...)
		{
			KillExcelProcess(arProcID);
			//pDlg->DestroyWindow();
			return EXPORT_FAILED;
		}

		//Kill Excel Process IDs producted this time.
		KillExcelProcess(arProcID);
		//pDlg->DestroyWindow();
	}
	return EXPORT_COMPLETED;
}

void MTableExportToExcel::SetRowColInFormat(CString strCell, int nRow, int nCol)
{
	if (strCell.FindOneOf(_T("/")) != -1)
	{
		m_pExcel->SetColumnInTextFormat((short)nRow+m_nHeaderRowCount+1, (short)nCol, (short)nRow+m_nHeaderRowCount+1, (short)nCol); 
	}
}

void MTableExportToExcel::CollectMergeRange(const CBCGPGridItem* pItem)
{
	if( !pItem ) { ASSERT(0); return; }

	CBCGPGridItemID id = pItem->GetGridItemID();
	int nRow = id.m_nRow;
	int nCol = id.m_nColumn;

	if( nRow < m_pTable->GetExtraTopRowCount() )   // Extra Top
	{
		MRecordInfo* pTopInfo = m_pTable->GetExtraTopRecordInfo();
		const CArray<CBCGPGridRange*>& arMergeInfo = pTopInfo->GetMergeInfo();

		int nSize = (int)arMergeInfo.GetSize();
		for( int i=0;i<nSize; ++i )
		{
			int nFirstRow = arMergeInfo[i]->m_nTop;
			int nFirstCol = arMergeInfo[i]->m_nLeft;
			int nLastRow  = arMergeInfo[i]->m_nBottom;
			int nLastCol  = arMergeInfo[i]->m_nRight;
			CBCGPGridRange MergeRange(nFirstCol, nFirstRow, nLastCol, nLastRow);

			if (CheckMergeRowCol(nFirstRow, nFirstCol, nLastRow, nLastCol))
			{
				m_aMergeArray.Add(MergeRange);
			}

			m_FirstRow = nFirstRow;
			m_FirstCol = nFirstCol;
			m_LastRow  = nLastRow;
			m_LastCol  = nLastCol; 
		}
	}
	else if( nRow > m_pTable->GetDataRowEndIndex() )  // Extra Bottom
	{
		MRecordInfo* pInfo = m_pTable->GetExtraBottomRecordInfo();
		const CArray<CBCGPGridRange*>& arMergeInfo = pInfo->GetMergeInfo();

		nRow += 1;

		int nMod = (nRow - m_pTable->GetDataRowEndIndex()) % pInfo->m_nRow;

		if( nRow > 0 && nMod == 0 )
		{
			for( int i=0; i<(int)arMergeInfo.GetSize(); ++i )
			{
				int nFirstRow = nRow - pInfo->m_nRow + arMergeInfo[i]->m_nTop;
				int nFirstCol = arMergeInfo[i]->m_nLeft;
				int nLastRow  = nRow - pInfo->m_nRow + arMergeInfo[i]->m_nBottom;
				int nLastCol  = arMergeInfo[i]->m_nRight;
				CBCGPGridRange MergeRange(nFirstCol, nFirstRow, nLastCol, nLastRow);

				if (CheckMergeRowCol(nFirstRow, nFirstCol, nLastRow, nLastCol))
				{
					m_aMergeArray.Add(MergeRange);
				}

				m_FirstRow = nFirstRow;
				m_FirstCol = nFirstCol;
				m_LastRow  = nLastRow;
				m_LastCol  = nLastCol; 
			}
		}
	}
	else  // Data Record
	{
		MRecordInfo* pInfo = m_pTable->GetDataRecordInfo();
		const CArray<CBCGPGridRange*>& arMergeInfo = pInfo->GetMergeInfo();

		nRow += 1;

		int nMod = (nRow - m_pTable->GetExtraTopRowCount()) % pInfo->m_nRow;

		if( nRow > 0 && nMod == 0 )
		{
			for( int i=0; i<(int)arMergeInfo.GetSize(); ++i )
			{
				int nFirstRow = nRow - pInfo->m_nRow + arMergeInfo[i]->m_nTop;
				int nFirstCol = arMergeInfo[i]->m_nLeft;
				int nLastRow  = nRow - pInfo->m_nRow + arMergeInfo[i]->m_nBottom;
				int nLastCol  = arMergeInfo[i]->m_nRight;
				CBCGPGridRange MergeRange(nFirstCol, nFirstRow, nLastCol, nLastRow);

				if (CheckMergeRowCol(nFirstRow, nFirstCol, nLastRow, nLastCol))
				{
					m_aMergeArray.Add(MergeRange);
				}

				m_FirstRow = nFirstRow;
				m_FirstCol = nFirstCol;
				m_LastRow  = nLastRow;
				m_LastCol  = nLastCol; 
			}
		}
	}
}

BOOL MTableExportToExcel::ConnectGrid(MTable* pGrid)
{
	if (!pGrid) { ASSERT(0); return FALSE; }
	else 
	{ 
		m_pTable = pGrid;		
		return TRUE; 
	}
}

void MTableExportToExcel::SetSheetPage(CString strSheet)
{
	CString strNewSteetName = strSheet;
	if(m_pExcel->IsExistSheetName(strSheet))
	{
		m_pExcel->SetActiveSheet(strSheet);
	}
	else
	{
		m_pExcel->SetActiveSheet(_LSX(Sheet1));
		m_pExcel->SetSheetName(_LSX(Sheet1), strSheet);
	}

	int nCol_Max = m_pTable->GetColumnCount();
	m_pExcel->SetColumnWidth(0, 0, 0, nCol_Max-1, 2.0);
}

BOOL MTableExportToExcel::IsEmptyCurrentRow(int nRow)
{
	int nMaxCol = m_pTable->GetColumnCount();
	UINT nCell = 0;

	for (int nCol=0; nCol < nMaxCol; ++nCol)
	{
		CBCGPGridRow* pRow = m_pTable->GetRow(nRow);
		if( !pRow ) { ASSERT(0); return FALSE; }

		CBCGPGridItem* pItem = pRow->GetItem(nCol);
		if( !pItem ) { ASSERT(0); return FALSE; }

		CString strCell = pItem->GetLabel();
		if (strCell.Compare(_T("")) == NULL)
		{
			nCell++;
		}
	}

	if (nCell == nMaxCol) return TRUE;
	else return FALSE;
}

void MTableExportToExcel::DeleteEmptyCells()
{
	int nSize = (int)m_svDelRowArray.size();
	int nMaxCol = m_pTable->GetColumnCount();
	for (int i=nSize-1 ; i>=0; --i)
	{
		CString strFromCell = m_pExcel->GetCell(m_svDelRowArray[i]+m_nHeaderRowCount+1,0);
		CString strToCell   = m_pExcel->GetCell(m_svDelRowArray[i]+m_nHeaderRowCount+1,(short)nMaxCol);
		m_pExcel->DeletCell(strFromCell, strToCell);
	}
}

BOOL MTableExportToExcel::CheckMergeRowCol(int nFirstRow, int nFirstCol, int nLastRow, int nLastCol)
{
	if (m_FirstRow == nFirstRow && m_FirstCol == nFirstCol &&
		m_LastRow  == nLastRow  && m_LastCol  == nLastCol)
	{
		return FALSE;
	}
	else
		return TRUE;
}

void MTableExportToExcel::MergeCell(MHashMap<int,int>& mapHidecol)
{
	if (m_aMergeArray.GetSize() > 0)
	{
		int nSize = (int)m_aMergeArray.GetSize()-1;
		int nFirstRow, nFirstCol, nLastRow, nLastCol;

		for (nSize; nSize>=0; --nSize)
		{
			nFirstRow = m_aMergeArray[nSize].m_nTop;
			nFirstCol = m_aMergeArray[nSize].m_nLeft;
			nLastRow  = m_aMergeArray[nSize].m_nBottom;
			nLastCol  = m_aMergeArray[nSize].m_nRight;

			if(mapHidecol.Exist(nFirstCol) || mapHidecol.Exist(nLastCol)) continue;

			m_pExcel->SetHorAlign((short)nFirstRow+m_nHeaderRowCount+1, (short)nFirstCol, (short)nLastRow+m_nHeaderRowCount+1, (short)nLastCol, 3);
			m_pExcel->SetMergeCell((short)nFirstRow+m_nHeaderRowCount+1, (short)nFirstCol, (short)nLastRow+m_nHeaderRowCount+1, (short)nLastCol);
		}
	}
}

void MTableExportToExcel::SetCellStyle(const CBCGPGridItem* pItem)
{
	if( !pItem ) { ASSERT(0); return; }

	CBCGPGridItemID id = pItem->GetGridItemID();
	int nRow = id.m_nRow;
	int nCol = id.m_nColumn;

	if( pItem->IsKindOf( RUNTIME_CLASS(MGridItem) ) )
	{
		MGridItem* pMItem = (MGridItem*)pItem;
		if( pMItem->IsBold() )
			m_pExcel->SetFontBold(nRow+m_nHeaderRowCount+1, nCol, nRow+m_nHeaderRowCount+1, nCol, TRUE);
	}

	COLORREF bgColor = pItem->GetBackgroundColor();
	if (bgColor != (COLORREF)-1)
	{
		m_pExcel->SetBackColor(nRow+m_nHeaderRowCount+1, nCol, nRow+m_nHeaderRowCount+1, nCol, bgColor);
	}

	COLORREF TextColor =  pItem->GetTextColor();
	if( TextColor != (COLORREF)-1 )
	{
		m_pExcel->SetTextColor(nRow+m_nHeaderRowCount+1, nCol, nRow+m_nHeaderRowCount+1, nCol, TextColor);
	}
}

BOOL MTableExportToExcel::CheckInterruption()
{
	static MSG msg;
	UINT   message = WM_KEYDOWN;
	if (::PeekMessage(&msg, NULL, message, message, PM_NOREMOVE))
	{
		::GetMessage(&msg,NULL, message,message);
		if ((int)msg.wParam == VK_ESCAPE) return TRUE;
	}
	return FALSE;
} 

BOOL MTableExportToExcel::ReplaceSymbolByTempChar(CString &sParam)
{
	sParam.Replace(_T("\""),_T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("\\"),_T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("*"), _T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("?"), _T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("|"), _T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T(":"), _T("_"));// ":"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("/"), _T("_"));// "/"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("<"), _T("_"));// "/"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T(">"), _T("_"));// "/"는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("."), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("%"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("$"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("#"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("@"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("!"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("^"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	sParam.Replace(_T("&"), _T("_"));// "."는 파일이름으로 사용할 수 없다.
	return TRUE; 
}

// Get Existed Excel Process ID
BOOL MTableExportToExcel::GetExistedExcelProcessID(CArray<unsigned int, unsigned int>& arProcID)
{
	HANDLE hProcessSnap = NULL;
	DWORD  wReturn      = 0;
	PROCESSENTRY32 pe32 = {0};

	CString strProcessName = _T("Excel.exe");
	strProcessName.MakeLower();

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if(Process32First(hProcessSnap, &pe32))
	{
		DWORD Code = 0;
		DWORD dwPriorityClass;

		do
		{
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			dwPriorityClass = GetPriorityClass(hProcess);

			CString Temp = pe32.szExeFile;
			Temp.MakeLower();

			if(Temp == strProcessName)
			{
				arProcID.Add(pe32.th32ProcessID);
			}
			CloseHandle(hProcess);

		} while(Process32Next(hProcessSnap, &pe32));
	} 
	CloseHandle(hProcessSnap); 

	return TRUE;
}

// Kill Excel Process used Excel-output.
DWORD MTableExportToExcel::KillExcelProcess(CArray<unsigned int, unsigned int>& arProcID)
{
	HANDLE hProcessSnap = NULL;
	DWORD  dwReturn     = 0;
	PROCESSENTRY32 pe32 = {0};

	CString strProcessName = _T("excel.exe");
	strProcessName.MakeLower();

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return (DWORD)INVALID_HANDLE_VALUE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if(Process32First(hProcessSnap, &pe32))
	{
		DWORD Code = 0;
		DWORD dwPriorityClass;
		do
		{
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			dwPriorityClass = GetPriorityClass(hProcess);

			CString Temp = pe32.szExeFile;
			Temp.MakeLower();

			if(Temp == strProcessName && !IsContainsProcessID(arProcID, pe32.th32ProcessID))
			{
				if(TerminateProcess(hProcess, 0))
				{
					GetExitCodeProcess(hProcess, &Code);
				}          
				else
				{
					return GetLastError();
				}
			}
			CloseHandle(hProcess);
		} while(Process32Next(hProcessSnap, &pe32));
	}

	CloseHandle(hProcessSnap); 

	return dwReturn;
}

// Check Is Contains current Process ID in Existed Process IDs.
BOOL MTableExportToExcel::IsContainsProcessID(CArray<unsigned int, unsigned int>& arProcID, unsigned int procID)
{
	int count = (int)arProcID.GetSize();
	for(int i=0; i<count; i++)
	{
		if(arProcID.GetAt(i) == procID)
		{
			return TRUE;
		}
	}  
	return FALSE;
}

