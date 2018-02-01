// MSExcel.h: interface for the CMSExcel class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "excel9.h"
#include "XLEnum.h"

#include "HeaderPre.h"

using namespace Excel9; 

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ ChartData//Chart Wizard parameter
		{
		public:
			ChartData();
			ChartData(ChartData& src);
			virtual ~ChartData();

			ChartData& operator= (const ChartData& src);

		public:
			CStringArray aSeries;//�迭�̸�
			CStringArray aSeriesValue;
			CString      SourceData;//���������� "A1:D10"

			XlChartType  ChartType;//Chart Type : ������ xlLine, xlLineMarkers, �л��� xlXYScatter, xlXYScatterSmooth, xlXYScatterSmoothNoMarkers, xlXYScatterLines, xlXYScatterLinesNoMarkers
			XlRowCol     PlotBy;//xlRows, xlColumns
			XlLegendPosition LegendPosition;//xlLegendPositionBottom, xlLegendPositionCorner, xlLegendPositionLeft, xlLegendPositionRight, xlLegendPositionTop
			XlDataLabelsType  labelsType;
			CString      CategoryLabels;//X�� ����Ÿ
			//CategoryLabels
			//SeriesLabels

			//�л��� ��Ʈ�� ��쿡 ����ϴ� ������
			CStringArray aName;
			CStringArray aXValue;
			CStringArray aYValue;

			CString ChartTitle;//Chart ����
			CString xTitle;//Category
			CString yTitle;//Value
			//ExtraTitle

			CString sFontName;
			CString sFontStyle;
			long   nFontSize;

			bool    bSeriesMaker;
			bool    bLegend;//����
			bool    bXAxis;
			bool    bYAxis;
			bool    bXTitle;
			bool    bYTitle;
			bool    bXMajorGridLine;
			bool    bXMinorGridLine;
			bool    bYMajorGridLine;
			bool    bYMinorGridLine;
			bool    bDataTable;
			bool    bDataLabel;

			long   nXunit;//X�� �ִ���
			long   nYunit;//Y�� �ִ���
			long  color;//xlNone, xlBlack, xlWhite, xlRed, xlGreen, xlBlue
			double dXmax;//X�� �ִ밪
			double dYmax;//Y�� �ִ밪
			double dXmin;//X�� �ּҰ�
			double dYmin;//Y�� �ּҰ�
			long   nStRow;  //���� Row
			long   nStCol;  //���� Col
			long   nEdRow;  //�� Row
			long   nEdCol;  //�� Col
		};

		class __MY_EXT_CLASS__ CMSExcel
		{
		public:
			CMSExcel();
			virtual ~CMSExcel();

		private:
			Excel9::_Application  oApp;
			Excel9::Workbooks     oBooks;
			Excel9::_Workbook     oBook;
			Excel9::Worksheets    oSheets;
			Excel9::_Worksheet    oSheet;
			Excel9::Charts        oCharts;
			Excel9::_Chart        oChart;
			Excel9::ChartObjects  oChartObjs;
			Excel9::ChartObject   oChartObj;
			Excel9::Window        oWindow;
			Excel9::Windows       oWindows;
			Excel9::Styles        oStyles; // Add by GAY. ('07.04.17).
			Excel9::Style         oStyle;  // Add by GAY. ('07.04.17).
			Excel9::Range         oRange;  // Modify by GAY. MNET:XXXX. ('08.01.23).
			Excel9::ExcelFont     oFont;   
			Excel9::Shapes        oShapes;
			Excel9::Shape         oShape;
			Excel9::Hyperlinks    oHypers;
			Excel9::HPageBreaks   oHBreaks;
			Excel9::_Worksheet    oTmpSheet;
			Excel9::Interior      oInterior;
			Excel9::Border        oBorder;
			Excel9::Borders       oBorders;

			COleVariant vTrue;
			COleVariant vFalse;
			COleVariant vOpt;

			BOOL m_bXL;

		public:
			static BOOL GetExistedExcelProcessID(CArray<unsigned int, unsigned int>& arProcID);
			static DWORD KillExcelProcess(CArray<unsigned int, unsigned int>& arProcID);
			static BOOL IsContainsProcessID(CArray<unsigned int, unsigned int>& arProcID, unsigned int procID);

			BOOL IsExcel() { return m_bXL; }
			void Quit();
			void SetWindowState(XlWindowState wdState);
			void Open(CString sFilename);
			void Close(CString sFilename);
			void Close();
			void SaveAs(CString sBookName, CString sFilename);
			void AddBook();
			CString GetBookName();
			void SetVisible(BOOL bVis);
			void SetActiveBook(CString sBookName);

			////////////////////////////////////////////////////////////////////////////////////////////
			//WorkSheet
			void AddSheet(CString sSheetName);
			void AddSheet2(CString sSheetName);
			void DeleteSheet(CString sSheetName);
			void MoveSheet(CString sSheetAfter, CString sSheetName);
			void CopySheet(CString sSheetAfter, CString sSheetName);
			void SetActiveSheet(CString sSheetName);
			void SetSheetName(CString sSheetNameOld, CString sSheetNameNew);
			void GetSheetsName(CStringArray& aSheets);
			CString GetSheetName(long idx);
			void SetHideSheet(CString sSheetName);

			void SetValue(CString sCell, CString sVal);
			void SetValue(CString sCell, double dVal);
			void SetValue(long Row, long Col, CString sVal);
			void SetValue(long Row, long Col, double dVal);

			double GetValue(CString sCell);
			double GetValue(long Row, long Col);

			CString GetValueString(CString sCell);
			CString GetValueString(long Row, long Col);

			void SetCellName(CString sCell, CString sCellName);
			CString GetCellName(CString sCell);
			void SetColumnWidth(CString sCell1, CString sCell2, long newValue);
			void SetColumnWidth(CString sCell1, CString sCell2, double newValue);
			void SetColumnWidth(long Row1, long Col1, long Row2, long Col2, long newValue);
			void SetColumnWidth(long Row1, long Col1, long Row2, long Col2, double newValue);
			void SetRowHeight(CString sCell1, CString sCell2, long newValue);
			void SetRowHeight(long Row1, long Col1, long Row2, long Col2, long newValue);  // Add by GAY.('06.02.01)
			void SetRowHeight(long newValue);  // Add by GAY.('06.02.02)

			void SetMergeCell(CString sCell1, CString sCell2);
			void SetMergeCell(long Row1, long Col1, long Row2, long Col2);

			void SetHorAlign(CString sCell1, CString sCell2, long Align);
			void SetVerAlign(CString sCell1, CString sCell2, long Align);
			void SetHorAlign(long Row1, long Col1, long Row2, long Col2, long Align);
			void SetVerAlign(long Row1, long Col1, long Row2, long Col2, long Align);

			void SetFont(CString sCell1, CString sCell2, long Height=9, COLORREF color=0, CString sType=_T("����ü"), BOOL bBold = FALSE);
			void SetFont(CString sCell1, CString sCell2, long Height, CString sType);
			void SetFont(long Row1, long Col1, long Row2, long Col2, long Height=9, COLORREF color=0, CString sType=_T("����ü"), BOOL bBold = FALSE);

			void SetFontFace(CString sCell1, CString sCell2, CString sFontName);
			void SetFontSize(CString sCell1, CString sCell2, long Height);
			void SetFontBold(CString sCell1, CString sCell2, BOOL bBold);
			void SetFontBold(long Row1, long Col1, long Row2, long Col2, BOOL bBold);  // Add by GAY.('06.02.01)

			void SetTextColor(CString sCell1, CString sCell2, COLORREF color);
			void SetTextColor(long Row1, long Col1, long Row2, long Col2, COLORREF color);  // Add by GAY.('06.06.13)
			void SetBackColor(CString sCell1, CString sCell2, COLORREF color);
			void SetBackColor(long Row1, long Col1, long Row2, long Col2, COLORREF color);  // Add by GAY.('06.06.13)
			void SetBorder(CString sCell1, CString sCell2, long LineStyle=1, long Thick=2);
			void SetBorder(long Row1, long Col1, long Row2, long Col2, long LineStyle=1, long Thick=2);

			void SetNumberFormat(long iRow1, long iCol1, long iRow2, long iCol2, CString sFormat);
			void SetNumberFormat(CString sCell1, CString sCell2, CString sFormat);
			void SetCellInTextFormat(CString sCell1, CString sCell2);
			void SetCellInTextFormat(long iRow1, long iCol1, long iRow2, long iCol2);
			void SetColumnInTextFormat(long iCol1, long iCol2);

			void SetCellInNumber3DotFormat(long iRow1, long iCol1, long iRow2, long iCol2);
			void SetCellInNumber3DotFormat(CString sCell1, CString sCell2);
			void SetCellInNumber2DotFormat(long iRow1, long iCol1, long iRow2, long iCol2);
			void SetCellInNumber2DotFormat(CString sCell1, CString sCell2);

			void SetColumnInNumber2DotFormat(long iCol1, long iCol2);
			void SetColumnInNumber3DotFormat(long iCol1, long iCol2);

			void SetColumnInTextFormat(long iRow1, long iCol1, long iRow2, long iCol2);

			void CellLine(CString sCell1, CString sCell2, long Direction, long LineStyle=1, long Thick=2, long LineColor=1);
			void CellLine(long Row1, long Col1, long Row2, long Col2, long Direction, long LineStyle=1, long Thick=2, long LineColor=1);

			void CellOutLine(CString sCell1, CString sCell2, long LineStyle=1, long Thick=2, long LineColor=1);
			void CellOutLine(long Row1, long Col1, long Row2, long Col2, long LineStyle=1, long Thick=2, long LineColor=1);

			void LineTo(float X1, float Y1, float X2, float Y2);
			void Copy(CString sCell1, CString sCell2, CString sCell3, CString sCell4);
			void CopyRow(CString sCell1, CString sCell2);

			void CopyPicture(CString sCell, CString sBookName, CString sSheetName, CString sPicName);
			void CopyPicture(long Row, long Col, CString sBookName, CString sSheetName, CString sPicName);
			void AddPicture(CString sFilename, float Left, float Top, float Width, float Height);
			void AddPicture(long Row, long Col, float Width, float Height, CString sFilename);		
			void AddPicture_Count(long Row, long Col, long RowCount, long ColCount, CString sFilename);
			void CopyRange(CString sCell, CString sBookName, CString sSheetName, CString sRangeName);
			void CopyRange(long Row, long Col, CString sBookName, CString sSheetName, CString sRangeName);
			void CopyRange(CString sCell, CString sBookName, CString sSheetName, CString sRangeName, int& rowCnt, int& colCnt);   // Add by GAY.('06.02.01)
			void CopyRange(long Row, long Col, CString sBookName, CString sSheetName, CString sRangeName, int& rowCnt, int& colCnt);    // Add by GAY.('06.02.01)


			void InsertCell(CString sCell1, CString sCell2, long iOpt=3);
			void DeletCell(CString sCell1, CString sCell2, long iOpt=3);
			void Clear(CString sCell1, CString sCell2);

			CString GetCell(long Row, long Col);
			CString GetCellOrgExp(long Row, long Col);
			void GetCellSize(long Row1, long Col1, long Row2, long Col2, double& dWidth, double& dHeight, double& dLeft, double& dTop);

			void SetDisplayZeros(bool bZero);
			void SetHPageBreak(long nPageRow, long nPrtRow, long nPrtCol);
			void SetPageSetup(XlPageOrientation pageOrt, XlPaperSize paperSize = xlPaperA4);
			void SetPageNormalView(bool bNormal);
			////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////
			//Chart
			void AddChart(CString sChartName, ChartData data, CString sTargetSheetName=_T(""));
			//	void AddChart(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName="");
			void AddChart(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T("") , long nXAxis=xlCategory, long nYAxis=xlValue);
			void AddChartXYReverse(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T(""));
			void AddChartScatter(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T(""));
			void AddChartLine(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T(""));
			void AddChartLineHBAR(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T(""));
			void MakeChart(ChartData data, CString sSheetName, long nXAxis=xlCategory, long nYAxis=xlValue);
			void MakeChartXYReverse(ChartData data, CString sSheetName);
			void MakeChartScatter(ChartData data, CString sSheetName);
			void MakeChartLine(ChartData data, CString sSheetName);
			void MakeChartLineHBAR(ChartData data, CString sSheetName);
			void MakeEmptyChart(long nRow, long nCol, double Width, double Height, CString sTargetSheetName=_T(""));
			void AddInEmptyChart(ChartData data, CString sTargetSheetName);
			void ChangeChartType(XlChartType eType);
			////////////////////////////////////////////////////////////////////////////////////////////

			// Add by GAY.('06.01.24)
			int GetPropertyCount(IDispatch* pDisp);
			void GetRangeCount(Range range, int& rowCnt, int& colCnt);
			HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);
			void SetHyperLink(CString ancCell, CString lnkCell);
			void SetHyperLink(CString ancCell, CString lnkSheetName, CString lnkCell);
			void SetHPageBreakBeforeActiveCell(CString sCell);
			void SetHPageBreakBeforeActiveCell(long Row, long Col);
			int  GetWorkSheetCount();
			void DeleteDefaultSheet();
			void SetCellInUserFormat(CString sCell1, CString sCell2, CString sFormat);
			void SetValueInUserFormat(CString sCell, CString sVal, CString sFormat);
			void AddPicture(CString sPicName, long Row, long Col, float Width, float Height, int& rowCnt);
			double GetValueFromMilimeterToPoint();
			void SetMargin(double dLeft, double dRight, double dTop, double dBot);  
			void InsertPicture(CString sPicName, long Row, long Col);
			BOOL IsExistSheetName(CString strSheetName);  //('06.03.14). �ش��̸��� ���� Sheet�� �����ϴ����� ����.
			BOOL IsExistSheetNameInclude(CString strSheetName);  //('06.03.15). �ش��̸��� ������ Sheet�� �����ϴ����� ����.
			CString GetMaximumSheetName(CString strSheetName);   //('06.03.15). �ش��̸��� ������ Sheet ��, ���� �� �̸� ��������.
			void SetSheetSelection(CString strSheetName); //!!!


			//==================================================================================================
			// About Styles. [070417, �۾�]
			//==================================================================================================

			// <strStyleName> �̸��� Style �����ϱ�.
			//   strStyleName : ������ Style �̸�.
			//   fontHeight : Font Size. (Default = 9)
			//   fontColor  : Font Color.
			//   sFontType  : Font Name. (Default = "Arial")
			//   bFontBold  : Bold ����. (TRUE = ����, FALSE = ����).
			// �� <strStyleName> �̸��� Style�� �����ϴ� ��쿡��, ���� Style�� �����Ų��.
			void AddStyle(CString strStyleName, long fontHeight=9, COLORREF fontColor=0, CString sFontType=_T("Arial"), BOOL bFontBold = FALSE);

			// <sCell1>~<sCell2> ������ <strStyleName> �̸��� Style �����ϱ�.
			//   sCell1 : ���� ���� ��ġ.
			//   sCell2 : ���� �� ��ġ.
			//   strStyleName : ������ Style�� �̸�.
			void SetStyle(CString sCell1, CString sCell2, CString strStyleName);

			// (Row1, Col1)~(Row2, Col2)�� ������ ���� �ʺ� �����ϱ�.
			//   Row1 : ���� ���� Row Index.
			//   Col1 : ���� ���� Col Index.
			//   Row2 : ���� �� Row Index.
			//   Col2 : ���� �� Col Index.
			//   strStyleName : ������ Style�� �̸�.
			void SetStyle(long Row1, long Col1, long Row2, long Col2, CString strStyleName);

			// ���� Sheet�� ��� ������ <strStyleName> �̸��� Style �����ϱ�.
			//   strStyleName : ������ Style�� �̸�.
			void SetSheetStyle(CString strStyleName);

			// ǥ�� Style �����ϱ�.
			//   fontHeight : Font Size. (Default = 9)
			//   fontColor  : Font Color.
			//   sFontType  : Font Name. (Default = "Arial")
			//   bFontBold  : Bold ����. (TRUE = ����, FALSE = ����)
			void SetDefaultStyle(long fontHeight=9, COLORREF fontColor=0, CString sFontType=_T("Arial"), BOOL bFontBold = FALSE);

		};
	}
}

#include "HeaderPost.h"