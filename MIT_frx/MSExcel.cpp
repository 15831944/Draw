// MSExcel.cpp: implementation of the CMSExcel class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MSExcel.h"
#include "math.h"

#include "Tlhelp32.h"   // To Terminate

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


using namespace mit::lib;
using namespace mit::frx;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ChartData::ChartData()
{
	ChartType = xlXYScatterSmooth;
	PlotBy    = xlColumns;
	bLegend   = TRUE;
	LegendPosition = xlLegendPositionRight;
	color     = 15;
	nXunit    = 0;
	nYunit    = 0;
	dXmax     = 1.0E41;
	dYmax     = 1.0E41;
	dXmin     = -1.0E41;
	dYmin     = -1.0E41;
	nStRow  = 0;  //시작 Row
	nStCol  = 0;  //시작 Col
	nEdRow  = 0;  //끝 Row
	nEdCol  = 0;  //끝 Col

	labelsType = xlDataLabelsShowNone;

	sFontName  = "Arial";
	sFontStyle = "Regular";
	nFontSize       = 9;

	bSeriesMaker    = TRUE;
	bLegend         = TRUE;
	bXAxis          = TRUE;
	bYAxis          = TRUE;
	bXTitle         = TRUE;
	bYTitle         = TRUE;
	bXMajorGridLine = FALSE;
	bXMinorGridLine = FALSE;
	bYMajorGridLine = TRUE;
	bYMinorGridLine = FALSE;
	bDataTable      = FALSE;
	bDataLabel      = TRUE;

	aSeries.RemoveAll();
	aSeriesValue.RemoveAll();
	SourceData = "";
	CategoryLabels = "";
	ChartTitle = "";
	xTitle = "";
	yTitle = "";

	aName.RemoveAll();
	aXValue.RemoveAll();
	aYValue.RemoveAll();
}

ChartData::ChartData(ChartData& src)
{
	this->SourceData     = src.SourceData;
	this->ChartTitle     = src.ChartTitle;
	this->ChartType      = src.ChartType;
	this->PlotBy         = src.PlotBy;

	this->LegendPosition = src.LegendPosition;
	this->color          = src.color;
	this->labelsType     = src.labelsType;
	this->CategoryLabels = src.CategoryLabels;

	this->sFontName      = src.sFontName;
	this->sFontStyle     = src.sFontStyle;
	this->nFontSize      = src.nFontSize;

	this->bSeriesMaker    = src.bSeriesMaker;
	this->bLegend         = src.bLegend;
	this->bXAxis          = src.bXAxis;
	this->bYAxis          = src.bYAxis;
	this->bXTitle         = src.bXTitle;
	this->bYTitle         = src.bYTitle;
	this->bXMajorGridLine = src.bXMajorGridLine;
	this->bXMinorGridLine = src.bXMinorGridLine;
	this->bYMajorGridLine = src.bYMajorGridLine;
	this->bYMinorGridLine = src.bYMinorGridLine;
	this->bDataTable      = src.bDataTable;
	this->bDataLabel      = src.bDataLabel;

	this->xTitle      = src.xTitle;
	this->yTitle      = src.yTitle;
	this->dXmax       = src.dXmax;
	this->dXmin       = src.dXmin;
	this->dYmax       = src.dYmax;
	this->dYmin       = src.dYmin;
	this->nXunit      = src.nXunit;
	this->nYunit      = src.nYunit;

	this->aSeries.Copy(src.aSeries);
	this->aSeriesValue.Copy(src.aSeriesValue);

	nStRow  = src.nStRow;
	nStCol  = src.nStCol;
	nEdRow  = src.nEdRow;
	nEdCol  = src.nEdCol;

	//분산형 차트인 경우에 사용하는 데이터
	this->aName.Copy(src.aName);
	this->aXValue.Copy(src.aXValue);
	this->aYValue.Copy(src.aYValue);
}

ChartData::~ChartData()
{
}

ChartData& ChartData::operator= (const ChartData& src)
{
	this->SourceData     = src.SourceData;
	this->ChartTitle     = src.ChartTitle;
	this->ChartType      = src.ChartType;
	this->PlotBy         = src.PlotBy;

	this->LegendPosition = src.LegendPosition;
	this->color          = src.color;
	this->labelsType     = src.labelsType;
	this->CategoryLabels = src.CategoryLabels;

	this->sFontName      = src.sFontName;
	this->sFontStyle     = src.sFontStyle;
	this->nFontSize      = src.nFontSize;

	this->bSeriesMaker    = src.bSeriesMaker;
	this->bLegend         = src.bLegend;
	this->bXAxis          = src.bXAxis;
	this->bYAxis          = src.bYAxis;
	this->bXTitle         = src.bXTitle;
	this->bYTitle         = src.bYTitle;
	this->bXMajorGridLine = src.bXMajorGridLine;
	this->bXMinorGridLine = src.bXMinorGridLine;
	this->bYMajorGridLine = src.bYMajorGridLine;
	this->bYMinorGridLine = src.bYMinorGridLine;
	this->bDataTable      = src.bDataTable;
	this->bDataLabel      = src.bDataLabel;

	this->xTitle      = src.xTitle;
	this->yTitle      = src.yTitle;
	this->dXmax       = src.dXmax;
	this->dXmin       = src.dXmin;
	this->dYmax       = src.dYmax;
	this->dYmin       = src.dYmin;
	this->nXunit      = src.nXunit;
	this->nYunit      = src.nYunit;

	this->aSeries.Copy(src.aSeries);
	this->aSeriesValue.Copy(src.aSeriesValue);
	this->LegendPosition = src.LegendPosition;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSExcel::CMSExcel()
{
	//    _Application oApp;
	vTrue = COleVariant((long)TRUE);
	vFalse = COleVariant((long)FALSE);
	vOpt = COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	/*Thread로 만들경우 엑셀작업 시작하는 곳에 삽입할 것
	if(!AfxOleInit())
	{
	AfxMessageBox("Could not initialize COM dll");
	return;
	}
	//*/

	if(!oApp.CreateDispatch(_T("Excel.Application"), NULL))
	{       
		m_bXL = FALSE;
		//		AfxMessageBox("Cannot start Excel");	
		return;
	}    
	m_bXL = TRUE;

	////////////////////////////////////////////////////////////////////////////////////
	COleMessageFilter* pFilter = AfxOleGetMessageFilter(); 
	pFilter->SetMessagePendingDelay(10000);      // Default는 5000ms입니다. 
	//pFilter->EnableBusyDialog(FALSE);            // 메세지박스를 화면에 나타나게 하지 않게 합니다.
	//pFilter->EnableNotRespondingDialog(FALSE); 
	////////////////////////////////////////////////////////////////////////////////////

	//Start a new workbook
	LPDISPATCH lpDisp;
	lpDisp = oApp.GetWorkbooks();
	ASSERT(lpDisp);
	oBooks.AttachDispatch(lpDisp);
	ASSERT(lpDisp);
	oApp.SetDisplayAlerts(FALSE);	//확인 대화상자를 열지않고 실행

	lpDisp = oApp.GetWindows();
	ASSERT(lpDisp);
	oWindows.AttachDispatch(lpDisp);
}

CMSExcel::~CMSExcel()
{
	oBooks.Close();
	oApp.Quit();  
}

//  XlWindowState : xlMaximized, xlMinimized, xlNormal
void CMSExcel::SetWindowState(XlWindowState wdState)
{
	oApp.SetWindowState(wdState);
}

void CMSExcel::Quit()
{
	//	oBook.Close(vFalse,vOpt,vOpt);
	//	oApp.ReleaseDispatch();
	oBooks.Close();
	oApp.Quit();
}

//ex) sFilename - C:\\WORK\\test3.xls
void CMSExcel::Open(CString sFilename)
{
	LPDISPATCH lpDisp;
	lpDisp = oBooks.Open(sFilename,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);
	oApp.SetDisplayAlerts(FALSE);	//확인 대화상자를 열지않고 실행
}

void CMSExcel::Close(CString sFilename)
{
	SetActiveBook(sFilename);
	oBook.Close(vOpt, COleVariant(sFilename), vOpt);
}

void CMSExcel::Close()
{
	oBooks.Close();
}

void CMSExcel::SaveAs(CString sBookName, CString sFilename)
{
	oBook = oBooks.GetItem(COleVariant(sBookName));
	oBook.SetSaved(TRUE);

	try
	{
		oBook.SaveAs(COleVariant(sFilename),vOpt,vOpt,vOpt,vOpt,vOpt,0,vOpt,vOpt,vOpt,vOpt);
	}
	catch(CException* e)
	{
		int nF = sFilename.Find(_T("."));
		CString sT = sFilename.Left(nF);

		sFilename = sT + _T("1")+ _T(".xls");

		CString sMsg;
		sMsg = sFilename + _LS(IDS_MIT_FRX_SAVED_FILES);
		AfxMessageBox(sFilename);

		oBook.SaveAs(COleVariant(sFilename),vOpt,vOpt,vOpt,vOpt,vOpt,0,vOpt,vOpt,vOpt,vOpt);

		e->Delete();
	}
	catch(...)
	{
	}

	//SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword,
	//const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, long AccessMode, const VARIANT& ConflictResolution, 
	//const VARIANT& AddToMru, const VARIANT& TextCodepage, const VARIANT& TextVisualLayout)
}

void CMSExcel::AddBook()
{
	LPDISPATCH lpDisp;

	lpDisp = oBooks.Add(vOpt);
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);
}

//Sheet를 맨 앞에 삽입
void CMSExcel::AddSheet(CString sSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.Add(vOpt,vOpt,COleVariant((long)1),vOpt);//수정요망
	oSheet.AttachDispatch(lpDisp);
	oSheet.SetName(sSheetName);
}

//Sheet를 맨 뒤에 삽입
void CMSExcel::AddSheet2(CString sSheetName)
{
	AddSheet(sSheetName);

	long SheetSu = oSheets.GetCount();
	LPDISPATCH lpDisp = oSheets.GetItem(COleVariant((long)SheetSu));
	oSheet.AttachDispatch(lpDisp);
	CString sLastSheet = oSheet.GetName();

	MoveSheet(sLastSheet, sSheetName);
}

void CMSExcel::DeleteSheet(CString sSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);
	oSheet.Delete();
}

//sSheet를 sSheetAfter뒤로
void CMSExcel::MoveSheet(CString sSheetAfter, CString sSheetName)
{
	SetActiveSheet(sSheetName);

	LPDISPATCH lpDisp;
	_Worksheet tempSheet;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	long nSheetSu = oSheets.GetCount();
	long i;
	for(i=1; i<=nSheetSu; i++)
	{
		lpDisp = oSheets.GetItem(COleVariant((long)i));
		ASSERT(lpDisp);
		tempSheet.AttachDispatch(lpDisp);
		CString cs = tempSheet.GetName();
		if(cs==sSheetAfter) break;
	}

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpDisp;
	oSheet.Move(vOpt,Var);

	lpDisp = oSheets.GetItem(COleVariant((long)i));
	oSheet.AttachDispatch(lpDisp);
	oSheet.SetName(sSheetName);
}

//sSheet를 sSheetAfter뒤로
void CMSExcel::CopySheet(CString sSheetAfter, CString sSheetName)
{
	LPDISPATCH lpDisp;
	_Worksheet tempSheet;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	long nSheetSu = oSheets.GetCount();
	long i;
	for(i=1; i<=nSheetSu; i++)
	{
		lpDisp = oSheets.GetItem(COleVariant((long)i));
		ASSERT(lpDisp);
		tempSheet.AttachDispatch(lpDisp);
		CString cs = tempSheet.GetName();
		if(cs==sSheetAfter) break;
	}

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpDisp;
	oSheet.Copy(vOpt,Var);

	long j = i+1;
	lpDisp = oSheets.GetItem(COleVariant((long)j));
	oSheet.AttachDispatch(lpDisp);
	oSheet.SetName(sSheetName);
}

void CMSExcel::SetVisible(BOOL bVis)
{
	oApp.SetVisible(bVis);
}

void CMSExcel::SetActiveBook(CString sBookName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBooks.GetItem(COleVariant(sBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);
}

void CMSExcel::SetActiveSheet(CString sSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);
}

void CMSExcel::SetSheetName(CString sSheetNameOld, CString sSheetNameNew)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetNameOld));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);
	oSheet.SetName(sSheetNameNew);
}

void CMSExcel::GetSheetsName(CStringArray& aSheets)
{
	aSheets.RemoveAll();

	LPDISPATCH lpDisp;
	_Worksheet tempSheet;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	long count = oSheets.GetCount();
	for(long i=1; i<=count; i++)
	{
		lpDisp = oSheets.GetItem(COleVariant((long)i));
		ASSERT(lpDisp);
		tempSheet.AttachDispatch(lpDisp);
		aSheets.Add(tempSheet.GetName());
	}
}

CString CMSExcel::GetSheetName(long idx)
{
	_Worksheet tempSheet = oSheets.GetItem(COleVariant((long)(idx+1)));

	return tempSheet.GetName();
}

void CMSExcel::SetHideSheet(CString sSheetName)
{
	LPDISPATCH lpDisp;
	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);
	oSheet.SetVisible(xlSheetHidden);
}

CString CMSExcel::GetBookName()
{
	CString sName = oBook.GetName();
	return sName;
}

void CMSExcel::SetValue(CString sCell, CString sVal)
{
	LPDISPATCH lpDisp;  
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetValue(COleVariant(sVal));
}

void CMSExcel::SetValue(CString sCell, double dVal)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetValue(COleVariant((double) dVal));
}

void CMSExcel::SetValue(long Row, long Col, CString sVal)
{
	CString sCell = GetCell(Row, Col);
	SetValue(sCell, sVal);
}

void CMSExcel::SetValue(long Row, long Col, double dVal)
{
	CString sCell = GetCell(Row, Col);
	SetValue(sCell, dVal);
}

double CMSExcel::GetValue(CString sCell)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	double dVal = (double)oRange.GetValue().dblVal;

	return dVal;
}

double CMSExcel::GetValue(long Row, long Col)
{
	CString sCell = GetCell(Row, Col);

	return GetValue(sCell);
}

CString CMSExcel::GetValueString(CString sCell)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	CString sVal = (CString)oRange.GetValue().bstrVal;

	return sVal;
}

CString CMSExcel::GetValueString(long Row, long Col)
{
	CString sCell = GetCell(Row, Col);

	return GetValueString(sCell);
}

void CMSExcel::SetCellName(CString sCell, CString sCellName)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetName(COleVariant(sCellName));
}

CString CMSExcel::GetCellName(CString sCell)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	VARIANT var;
	var = oRange.GetName();
	CString sCellName = (CString)var.bstrVal;

	return sCellName;
}

void CMSExcel::SetColumnWidth(CString sCell1, CString sCell2, long newValue)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetColumnWidth(COleVariant((long)newValue));
}

void CMSExcel::SetColumnWidth(CString sCell1, CString sCell2, double newValue)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetColumnWidth(COleVariant((double)newValue));
}

void CMSExcel::SetColumnWidth(long Row1, long Col1, long Row2, long Col2, long newValue)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetColumnWidth(sCell1, sCell2, newValue);
}

void CMSExcel::SetColumnWidth(long Row1, long Col1, long Row2, long Col2, double newValue)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetColumnWidth(sCell1, sCell2, newValue);
}

void CMSExcel::SetRowHeight(CString sCell1, CString sCell2, long newValue)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetRowHeight(COleVariant((long)newValue));
}

// Add By GAY.('06.02.02). Set Row Height in Given Range.
void CMSExcel::SetRowHeight(long Row1, long Col1, long Row2, long Col2, long newValue)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetRowHeight(sCell1, sCell2, newValue);
}

// Add by GAY.('06.02.02). Set Row Height in Whole Sheet.
void CMSExcel::SetRowHeight(long newValue)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetCells();
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetRowHeight(COleVariant((long)newValue));
}

void CMSExcel::SetMergeCell(CString sCell1, CString sCell2)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	VARIANT newValue = oRange.GetHeight();
	oRange.SetMergeCells(newValue);
}

void CMSExcel::SetMergeCell(long Row1, long Col1, long Row2, long Col2)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetMergeCell(sCell1, sCell2);
}

void CMSExcel::SetHorAlign(CString sCell1, CString sCell2, long Align)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetHorizontalAlignment(COleVariant((long)Align));
}

void CMSExcel::SetVerAlign(CString sCell1, CString sCell2, long Align)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetVerticalAlignment(COleVariant((long)Align));
}

void CMSExcel::SetHorAlign(long Row1, long Col1, long Row2, long Col2, long Align)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetHorAlign(sCell1, sCell2, Align);
}

void CMSExcel::SetVerAlign(long Row1, long Col1, long Row2, long Col2, long Align)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetVerAlign(sCell1, sCell2, Align);
}

void CMSExcel::SetFont(CString sCell1, CString sCell2, long Height, COLORREF Color, CString sType, BOOL bBold)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();
	oFont.SetSize(COleVariant((long)Height));
	oFont.SetColor(COleVariant((double)Color));
	oFont.SetName(COleVariant(sType));

	if(bBold)
		oFont.SetBold(vTrue);
	else
		oFont.SetBold(vFalse);
}

void CMSExcel::SetFont(CString sCell1, CString sCell2, long Height, CString sType)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();
	oFont.SetSize(COleVariant((long)Height));
	//	font.SetColorIndex(COleVariant((long)Color));
	oFont.SetName(COleVariant(sType));
	/*
	if(bBold)
	font.SetBold(vTrue);
	else
	font.SetBold(vFalse);
	*/
}

void CMSExcel::SetFont(long Row1, long Col1, long Row2, long Col2, long Height, COLORREF Color, CString sType, BOOL bBold)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetFont(sCell1, sCell2, Height, Color, sType, bBold);
}

void CMSExcel::SetFontFace(CString sCell1, CString sCell2, CString sFontName)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();
	oFont.SetName(COleVariant(sFontName));
}

void CMSExcel::SetFontSize(CString sCell1, CString sCell2, long Height)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();
	oFont.SetSize(COleVariant((long)Height));
}

void CMSExcel::SetFontBold(CString sCell1, CString sCell2, BOOL bBold)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();

	if(bBold)
		oFont.SetBold(vTrue);
	else
		oFont.SetBold(vFalse);
}

void CMSExcel::SetFontBold(long Row1, long Col1, long Row2, long Col2, BOOL bBold)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetFontBold(sCell1, sCell2, bBold);
}

void CMSExcel::SetTextColor(CString sCell1, CString sCell2, COLORREF Color)
{
	LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oFont = oRange.GetFont();
	oFont.SetColor(COleVariant((double)Color));
}

void CMSExcel::SetTextColor(long Row1, long Col1, long Row2, long Col2, COLORREF color)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);
	SetTextColor(sCell1, sCell2, color);
}

void CMSExcel::SetBackColor(CString sCell1, CString sCell2, COLORREF Color)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	Interior interior = oRange.GetInterior();
	interior.SetColor(COleVariant((double)Color));
}

void CMSExcel::SetBackColor(long Row1, long Col1, long Row2, long Col2, COLORREF color)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);
	SetBackColor(sCell1, sCell2, color);
}

void CMSExcel::SetBorder(CString sCell1, CString sCell2, long LineStyle, long Thick)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	Borders borders = oRange.GetBorders();
	borders.SetLineStyle(COleVariant((long)LineStyle));
	borders.SetWeight(COleVariant((long)Thick));
}

void CMSExcel::SetBorder(long Row1, long Col1, long Row2, long Col2, long LineStyle, long Thick)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetBorder(sCell1, sCell2, LineStyle, Thick);
}

void CMSExcel::SetNumberFormat(CString sCell1, CString sCell2, CString sFormat)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetNumberFormat(COleVariant(sFormat));
}

void CMSExcel::SetNumberFormat(long Row1, long Col1, long Row2, long Col2, CString sFormat)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetNumberFormat(sCell1, sCell2, sFormat);
}

//Direction  1: 모든셀의 좌측, 2: 모든셀의 우측, 3: 모든셀의 top, 4: 모든셀의 bottom, 5: 대각선(＼), 6: 대각선(／)
//           7: 선택영역의 맨 좌측, 8: 선택영역의 top, 9: 선택영역의 bottom, 10: 선택영역의 맨 우측, 11: 선택영역의 가운테 선만(가로), 12: 선택영역의 가운테 선만(세로)
void CMSExcel::CellLine(CString sCell1, CString sCell2, long Direction, long LineStyle, long Thick, long LineColor)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	Border border;
	Borders borders;
	lpDisp = oRange.GetBorders();
	borders.AttachDispatch(lpDisp);

	lpDisp = borders.GetItem(Direction);
	border.AttachDispatch(lpDisp);
	border.SetLineStyle(COleVariant((long)LineStyle));
	border.SetWeight(COleVariant((long)Thick));
	border.SetColorIndex(COleVariant((long)LineColor));
}

void CMSExcel::CellLine(long Row1, long Col1, long Row2, long Col2, long Direction, long LineStyle, long Thick, long LineColor)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	CellLine(sCell1, sCell2, Direction, LineStyle, Thick, LineColor);
}

void CMSExcel::CellOutLine(CString sCell1, CString sCell2, long LineStyle, long Thick, long LineColor)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.BorderAround(COleVariant((long)LineStyle),Thick,LineColor,COleVariant((long)1));
}

void CMSExcel::CellOutLine(long Row1, long Col1, long Row2, long Col2, long LineStyle, long Thick, long LineColor)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	CellOutLine(sCell1, sCell2, LineStyle, Thick, LineColor);
}

void CMSExcel::LineTo(float X1, float Y1, float X2, float Y2)
{
	LPDISPATCH lpDisp;
	Shapes shapes;
	lpDisp = oSheet.GetShapes();
	ASSERT(lpDisp);
	shapes.AttachDispatch(lpDisp);

	Line line;
	line = shapes.AddLine(X1,Y1,X2,Y2);
}

//copy:sCell1,sCell2   paste:sCell3,sCell4
void CMSExcel::Copy(CString sCell1, CString sCell2, CString sCell3, CString sCell4)
{
	LPDISPATCH lpDisp, lpPaste;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.Copy(vOpt);

	lpPaste = oSheet.GetRange(COleVariant(sCell3),COleVariant(sCell4));
	ASSERT(lpPaste);
	oRange.AttachDispatch(lpPaste);

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpPaste; 

	oSheet.Paste(Var,vFalse);
}

void CMSExcel::CopyRow(CString sCell1, CString sCell2)
{
	CString sOld1 = sCell1;
	CString sOld2 = sCell2;

	sCell1.Delete(0);
	sCell2.Delete(0);

	int nCell1 = _ttoi(sCell1);
	int nCell2 = _ttoi(sCell2);
	int nSub = nCell2 - nCell1;

	CString sCell3, sCell4;

	//일반화된 식으로 수정할 것.
	sOld2.Format(_T("AP%d"), nCell2);
	sCell3.Format(_T("H%d"), nCell2+1);
	sCell4.Format(_T("AP%d"), nCell2+nSub+1);

	InsertCell(sCell3, sCell4);
	Copy(sOld1, sOld2, sCell3, sCell4);
}

void CMSExcel::CopyPicture(long Row, long Col, CString sBookName, CString sSheetName, CString sPicName)
{
	CString sCell = GetCell(Row, Col);

	CopyPicture(sCell, sBookName, sSheetName, sPicName);
}

void CMSExcel::CopyPicture(CString sCell, CString sBookName, CString sSheetName, CString sPicName)
{
	CString OldBookName = oBook.GetName();
	CString OldSheetName = oSheet.GetName();

	LPDISPATCH lpDisp;

	lpDisp = oBooks.GetItem(COleVariant(sBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	VARIANT vRange;
	vRange = oSheet.Evaluate(COleVariant(sPicName));
	lpDisp = vRange.pdispVal;
	ASSERT(lpDisp);
	Range oRange(lpDisp);

	//	oRange.AttachDispatch(lpDisp);
	oRange.CopyPicture(1,1);

	lpDisp = oBooks.GetItem(COleVariant(OldBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(OldSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	lpDisp = oSheet.GetRange(COleVariant(sCell),COleVariant(sCell));

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpDisp; 

	oSheet.Paste(Var,vFalse);
	//  lpDisp->Release();
}

void CMSExcel::CopyRange(long Row, long Col, CString sBookName, CString sSheetName, CString sRangeName)
{
	CString sCell = GetCell(Row, Col);

	CopyRange(sCell, sBookName, sSheetName, sRangeName);
}

void CMSExcel::CopyRange(CString sCell, CString sBookName, CString sSheetName, CString sRangeName)
{
	CString OldBookName = oBook.GetName();
	CString OldSheetName = oSheet.GetName();

	LPDISPATCH lpDisp;

	lpDisp = oBooks.GetItem(COleVariant(sBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	VARIANT vRange;
	vRange = oSheet.Evaluate(COleVariant(sRangeName));
	lpDisp = vRange.pdispVal;
	ASSERT(lpDisp);
	Range oRange(lpDisp);

	//	oRange.AttachDispatch(lpDisp);  
	oRange.Copy(vOpt);

	lpDisp = oBooks.GetItem(COleVariant(OldBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(OldSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	lpDisp = oSheet.GetRange(COleVariant(sCell),COleVariant(sCell));

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpDisp; 

	oSheet.Paste(Var,vFalse);
	//  lpDisp->Release();
}

// Add by GAY.('06.02.01).
// 현재 Active된 Sheet의 sCell에 sBookName + sSheetName + sRangeName의 Range를 복사하여 붙여넣는다.
// [param] 붙여넣을 위치의 Cell 이름.
// [param] sBookName  : 복사대상의 Range가 위치한 WorkBook의 이름.
// [param] sSheetName : 복사대상의 Range가 위치한 WorkSheet의 이름.
// [param] sRangeName : 복사대상의 Range 이름.
// [param] rowCnt : Range가 차지하는 행수.
// [param] colCnt : Range가 차지하는 열수.
void CMSExcel::CopyRange(CString sCell, CString sBookName, CString sSheetName, CString sRangeName, int& rowCnt, int& colCnt)
{
	CString OldBookName  = oBook.GetName();
	CString OldSheetName = oSheet.GetName();

	LPDISPATCH lpDisp;

	lpDisp = oBooks.GetItem(COleVariant(sBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(sSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	VARIANT vRange;
	vRange = oSheet.Evaluate(COleVariant(sRangeName));
	lpDisp = vRange.pdispVal;
	ASSERT(lpDisp);
	Range oRange(lpDisp);

	oRange.Copy(vOpt);

	lpDisp = oBooks.GetItem(COleVariant(OldBookName));
	ASSERT(lpDisp);
	oBook.AttachDispatch(lpDisp);

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(OldSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);

	lpDisp = oSheet.GetRange(COleVariant(sCell),COleVariant(sCell));

	VARIANT Var;
	Var.vt = VT_DISPATCH;
	Var.pdispVal = lpDisp; 

	oSheet.Paste(Var,vFalse);

	rowCnt = GetPropertyCount(oRange.GetRows());
	colCnt = GetPropertyCount(oRange.GetColumns());   
}

// Add by GAY.('06.02.01).
// 현재 Active된 Sheet의 sCell에 sBookName + sSheetName + sRangeName의 Range를 복사하여 붙여넣는다.
// [param] Row : 붙여넣을 위치의 Row index
// [param] Col : 붙여넣을 위치의 Col index
// [param] sBookName  : 복사대상의 Range가 위치한 WorkBook의 이름.
// [param] sSheetName : 복사대상의 Range가 위치한 WorkSheet의 이름.
// [param] sRangeName : 복사대상의 Range 이름.
// [param] rowCnt : Range가 차지하는 행수.
// [param] colCnt : Range가 차지하는 열수.
void CMSExcel::CopyRange(long Row, long Col, CString sBookName, CString sSheetName, CString sRangeName, int& rowCnt, int& colCnt)
{
	CString strCell = GetCell(Row, Col);
	CopyRange(strCell, sBookName, sSheetName, sRangeName, rowCnt, colCnt);
}

//Left:X, Top:Y 시작좌표,  Width, Heith: 폭과 높이
//File 종류: bmp, jpg, emf, wmf 등
void CMSExcel::AddPicture(CString sFilename, float Left, float Top, float Width, float Height)
{
	LPDISPATCH lpDisp;

	Shapes shapes;
	lpDisp = oSheet.GetShapes();
	ASSERT(lpDisp);
	shapes.AttachDispatch(lpDisp);

	lpDisp = shapes.AddPicture(sFilename, FALSE, TRUE, Left, Top, Width, Height);
	lpDisp->Release();
	//	shapes.ReleaseDispatch();
}

void CMSExcel::AddPicture(long Row, long Col, float Width, float Height, CString sFilename)
{
	LPDISPATCH lpDisp;

	CString sCell;
	sCell.Format(_T("A%d"), Row);

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),COleVariant(sCell));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	float Wi = (float)oRange.GetWidth().dblVal;
	float He = (float)oRange.GetHeight().dblVal;

	Shapes shapes;
	lpDisp = oSheet.GetShapes();	
	ASSERT(lpDisp);
	shapes.AttachDispatch(lpDisp);

	float Left = Wi * Col;
	float Top = He * Row;

	lpDisp = shapes.AddPicture(sFilename, FALSE, TRUE, Left, Top, Width, Height);
	lpDisp->Release();
	//	shapes.ReleaseDispatch();
}

void CMSExcel::AddPicture_Count(long Row, long Col, long RowCount, long ColCount, CString sFilename)
{
	LPDISPATCH lpDisp;

	CString sCell;
	sCell.Format(_T("A%d"), Row);

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),COleVariant(sCell));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	float Wi = (float)oRange.GetWidth().dblVal;
	float He = (float)oRange.GetHeight().dblVal;	

	Shapes shapes;
	lpDisp = oSheet.GetShapes();	
	ASSERT(lpDisp);
	shapes.AttachDispatch(lpDisp);

	float Left = Wi * Col;
	float Top = He * Row;
	float Width = Wi * ColCount;
	float Height = He * RowCount;

	lpDisp = shapes.AddPicture(sFilename, FALSE, TRUE, Left, Top, Width, Height);
	lpDisp->Release();
}

/*iOpt - 1:오른쪽으로 이동 2:아래로 이동 3:행 삽입 4:열 삽입*/
void CMSExcel::InsertCell(CString sCell1, CString sCell2, long iOpt)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.Insert(COleVariant((long)iOpt));
}

/*iOpt - 1:왼쪽으로 이동 2:위로이동 3:행 삭제 4:열 삭제*/
void CMSExcel::DeletCell(CString sCell1, CString sCell2, long iOpt)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.Delete(COleVariant((long)iOpt));
}

void CMSExcel::Clear(CString sCell1, CString sCell2)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.Clear();
}

CString CMSExcel::GetCell(long Row, long Col)
{
	CString sCol, sRow;

	sRow.Format(_T("%d"), Row+1);

	if(Col < 26)
	{
		sCol.Format(_T("%c"), (TCHAR)('A'+Col));
	}
	else if(Col < 255)
	{
		long first, second;
		first = Col / 26 - 1;
		second = Col % 26;
		sCol.Format(_T("%c%c"), (TCHAR)('A'+first), (TCHAR)('A'+second));
	}

	CString sCell = sCol + sRow;

	return sCell;
}

CString CMSExcel::GetCellOrgExp(long Row, long Col)
{
	CString sCol, sRow;

	sRow.Format(_T("%d"), Row+1);

	if(Col < 26)
	{
		sCol.Format(_T("%c"), (TCHAR)('A'+Col));
	}
	else if(Col < 255)
	{
		long first, second;
		first = Col / 26 - 1;
		second = Col % 26;
		sCol.Format(_T("%c%c"), (TCHAR)('A'+first), (TCHAR)('A'+second));
	}

	CString sCell = _T("$") + sCol + _T("$") + sRow;

	return sCell;
}

void CMSExcel::GetCellSize(long Row1, long Col1, long Row2, long Col2, double& dWidth, double& dHeight, double& dLeft, double& dTop)//rsh
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	dWidth = oRange.GetWidth().dblVal;
	dHeight = oRange.GetHeight().dblVal;
	dLeft = oRange.GetLeft().dblVal;
	dTop = oRange.GetTop().dblVal;
}

void CMSExcel::SetCellInTextFormat(CString sCell1, CString sCell2) // rsh
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("@"))); 
}

void CMSExcel::SetCellInTextFormat(long iRow1, long iCol1, long iRow2, long iCol2) // rsh
{
	CString sCell1 = GetCell(iRow1, iCol1);
	CString sCell2 = GetCell(iRow2, iCol2);
	SetCellInTextFormat(sCell1, sCell2);
}

void CMSExcel::SetColumnInTextFormat(long iCol1, long iCol2) // rsh
{
	CString sCell1 = GetCell(0, iCol1);
	CString sCell2 = GetCell((long)65535, iCol2);

	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("@"))); 
}

void CMSExcel::SetCellInNumber3DotFormat(long iRow1, long iCol1, long iRow2, long iCol2) // rsh
{
	CString sCell1 = GetCell(iRow1, iCol1);
	CString sCell2 = GetCell(iRow2, iCol2);
	SetCellInNumber3DotFormat(sCell1, sCell2);
}

void CMSExcel::SetColumnInNumber3DotFormat(long iCol1, long iCol2) // rsh
{
	CString sCell1 = GetCell(0, iCol1);
	CString sCell2 = GetCell((long)65535, iCol2);

	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("0.000_ "))); 
}

void CMSExcel::SetCellInNumber3DotFormat(CString sCell1, CString sCell2) // rsh
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("0.000_ "))); 
}

void CMSExcel::SetCellInNumber2DotFormat(long iRow1, long iCol1, long iRow2, long iCol2) // rsh
{
	CString sCell1 = GetCell(iRow1, iCol1);
	CString sCell2 = GetCell(iRow2, iCol2);
	SetCellInNumber2DotFormat(sCell1, sCell2);
}

void CMSExcel::SetCellInNumber2DotFormat(CString sCell1, CString sCell2) // rsh
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("0.00_ "))); 
}

void CMSExcel::SetColumnInNumber2DotFormat(long iCol1, long iCol2) // rsh
{
	CString sCell1 = GetCell(0, iCol1);
	CString sCell2 = GetCell((long)65535, iCol2);

	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("0.00_ "))); 
}

void CMSExcel::SetColumnInTextFormat(long iRow1, long iCol1, long iRow2, long iCol2) // rsh
{
	CString sCell1 = GetCell(iRow1, iCol1);
	CString sCell2 = GetCell(iRow2, iCol2);

	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetNumberFormatLocal(COleVariant(_T("@")));
}

void CMSExcel::SetDisplayZeros(bool bZero)
{
	oWindow = oApp.GetActiveWindow();
	oWindow.SetDisplayZeros(bZero);
}

///<Function></Function>
///<para:nPageRow>한 페이지의 행 수</para>
void CMSExcel::SetHPageBreak(long nPageRow, long nPrtRow, long nPrtCol)
{
	try
	{
		oSheet.SetDisplayPageBreaks(TRUE);
		oWindow = oApp.GetActiveWindow();
		oWindow.SetView(xlPageBreakPreview);//페이지 나누기 미리보기

		XlPageSetup pageSetup = oSheet.GetPageSetup();
		CString sPrt = _T("A1:") + GetCell(nPrtRow, nPrtCol);

		nPrtRow += 51;//1 Page Default: 51 행

		CString sPrtArea = _T("A1:") + GetCell(nPrtRow, nPrtCol);
		pageSetup.SetPrintArea(sPrtArea);

		HPageBreaks hPBs = oSheet.GetHPageBreaks();
		long count = hPBs.GetCount();
		if(count==0) return;

		for(int i=0; i<count; i++)
		{
			HPageBreak hPB = hPBs.GetItem(i+1);

			CString sCell1;
			sCell1.Format(_T("A%d"), (i+1)*nPageRow+1);

			LPDISPATCH lpDisp = oSheet.GetRange(COleVariant(sCell1),vOpt);
			ASSERT(lpDisp);
			oRange.AttachDispatch(lpDisp);

			hPB.SetRefLocation(lpDisp);

			count = hPBs.GetCount();
		}

		pageSetup.SetPrintArea(sPrt);
		pageSetup.DetachDispatch();
	}
	catch(...)
	{}
}

//XlPageOrientation : xlPortrait, xlLandscape          XlPaperSize : xlPaperA3, xlPaperA4, xlPaperB4, xlPaperB5
void CMSExcel::SetPageSetup(XlPageOrientation pageOrt, XlPaperSize paperSize)
{
	XlPageSetup pageSetup = oSheet.GetPageSetup();
	pageSetup.SetPaperSize(paperSize);
	pageSetup.SetOrientation(pageOrt);
	pageSetup.DetachDispatch();
}

void CMSExcel::SetPageNormalView(bool bNormal)
{
	if(bNormal)
	{
		oWindow = oApp.GetActiveWindow();
		oWindow.SetView(xlNormalView);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
///<summary>Chart Sheet로 만들 때</summary>
///<para>sTargetSheetName: Chart의 원본 데이타가 있는 SheetName</para>
void CMSExcel::AddChart(CString sChartName, ChartData data, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.Add(vOpt,vOpt,COleVariant((long)1), COleVariant((long)xlChart));

	CString sSheetName = oSheet.GetName();

	oChart.AttachDispatch(lpDisp);
	oChart.SetName(sChartName);

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChart(data, sSheetName);
}

///<summary>WorkSheet에 Chart를 만들 때</summary>
///<para>sTargetSheetName: Chart의 원본 데이타가 있는 SheetName</para>
// void CMSExcel::AddChart(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName)
// {
// LPDISPATCH lpDisp;
// 
// lpDisp = oBook.GetSheets();
// ASSERT(lpDisp);
//   oSheets.AttachDispatch(lpDisp);
// 
// CString sSheetName = oSheet.GetName();
// 
// Range oRange;
// lpDisp = oSheet.GetRange(COleVariant("A1"),vOpt);
// ASSERT(lpDisp);
// oRange.AttachDispatch(lpDisp);
// 
// double Left = nCol*oRange.GetWidth().dblVal;
// double Top  = nRow*oRange.GetHeight().dblVal;
// 
// lpDisp = oSheet.ChartObjects(vOpt);
// oChartObjs.AttachDispatch(lpDisp);
// 
// lpDisp = oChartObjs.Add(Left, Top, Width, Height);
// oChartObj.AttachDispatch(lpDisp);
// 
// oChart = oChartObj.GetChart();
// 
// if(sTargetSheetName == "") sTargetSheetName = sSheetName;
// SetActiveSheet(sTargetSheetName);
// 
// MakeChart(data, sSheetName);
// }

// 20071224 응용기술팀 이종협
void CMSExcel::AddChart(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName, long nXAxis, long nYAxis)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChart(data, sSheetName, nXAxis, nYAxis);
}

void CMSExcel::MakeChart(ChartData data, CString sSheetName, long nXAxis, long nYAxis)
{
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetChartType((long)data.ChartType);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);

	//계열이름
	for(int i=0; i<data.aSeries.GetSize(); i++)
	{
		try
		{
			Series oSeries = oChart.SeriesCollection(COleVariant((long)(i+1)));
			oSeries.SetName(data.aSeries[i]);
		}
		catch(...){}
	}

	//범례
	oChart.SetHasLegend(data.bLegend);
	if(data.bLegend)
	{
		Legend oLeg = oChart.GetLegend();
		oLeg.SetPosition(data.LegendPosition);
	}

	//X 축
	Axis oXAxis = oChart.Axes(COleVariant((long)nXAxis), 1);
	oXAxis.SetHasTitle(TRUE);
	oXAxis.SetMaximumScaleIsAuto(TRUE);
	oXAxis.SetMinimumScaleIsAuto(TRUE);

	if(fabs(data.dXmax)<1.0E+21)
	{
		oXAxis.SetMaximumScaleIsAuto(FALSE);
		oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
		oXAxis.SetMinimumScaleIsAuto(FALSE);
		oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
		oXAxis.SetMajorUnit(data.nXunit);
	}

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	oXTitle.SetText(data.xTitle);

	//Y 축
	Axis oYAxis = oChart.Axes(COleVariant((long)nYAxis), 1);
	oYAxis.SetHasTitle(TRUE);

	if(data.ChartType!=xlLine)
	{
		// 	if(fabs(data.dYmax)<1.0E+21)  oYAxis.SetMaximumScale(data.dYmax);
		// 	if(fabs(data.dYmin)<1.0E+21)  oYAxis.SetMinimumScale(data.dYmin);

		oYAxis.SetMaximumScaleIsAuto(TRUE);
		oYAxis.SetMinimumScaleIsAuto(TRUE);
	}

	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	oYTitle.SetText(data.yTitle);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	SetActiveSheet(sSheetName);

}


void CMSExcel::AddChartXYReverse(ChartData data, long nRow, long nCol, 
								 double Width, double Height, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChartXYReverse(data, sSheetName);
}


void CMSExcel::MakeChartXYReverse(ChartData data, CString sSheetName)
{
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetChartType((long)data.ChartType);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);

	//계열이름
	for(int i=1; i<data.aSeries.GetSize(); i++)
	{
		try
		{
			Series oSeries = oChart.SeriesCollection(COleVariant((long)(i+1)));
			oSeries.SetName(data.aSeries[i]);

			// 계열범위지정 
			CString csXRange; 
			CString csYRange; 
			csXRange.Format(_T("\'%s\'!%s:%s"),sSheetName, GetCellOrgExp((long)data.nStRow, (long)data.nStCol+i),GetCellOrgExp((long)data.nEdRow, (long)data.nStCol+i));
			csYRange.Format(_T("\'%s\'!%s:%s"),sSheetName, GetCellOrgExp((long)data.nStRow, (long)data.nStCol),GetCellOrgExp((long)data.nEdRow, (long)data.nStCol));

			CString csFormula2;
			csFormula2.Format(_T("=SERIES(\"%s\",%s,%s,%d)"),data.aSeries[i],csXRange,csYRange,i);

			oSeries.SetFormula(csFormula2);
			oSeries.SetFormulaLocal(csFormula2);
		}
		catch(...){}
	}

	//범례
	oChart.SetHasLegend(data.bLegend);
	if(data.bLegend)
	{
		Legend oLeg = oChart.GetLegend();
		oLeg.SetPosition(data.LegendPosition);
	}

	//X 축
	Axis oXAxis = oChart.Axes(COleVariant((long)xlValue), 1);
	oXAxis.SetHasTitle(TRUE);
	oXAxis.SetMaximumScaleIsAuto(TRUE);
	oXAxis.SetMinimumScaleIsAuto(TRUE);

	if(fabs(data.dXmax)<1.0E+21)
	{
		oXAxis.SetMaximumScaleIsAuto(FALSE);
		oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
		oXAxis.SetMinimumScaleIsAuto(FALSE);
		oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
		oXAxis.SetMajorUnit(data.nXunit);
	}

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	oXTitle.SetText(data.xTitle);

	//Y 축
	Axis oYAxis = oChart.Axes(COleVariant((long)xlCategory), 1);
	oYAxis.SetHasTitle(TRUE);

	if(data.ChartType!=xlLine)
	{
		// 	if(fabs(data.dYmax)<1.0E+21)  oYAxis.SetMaximumScale(data.dYmax);
		// 	if(fabs(data.dYmin)<1.0E+21)  oYAxis.SetMinimumScale(data.dYmin);

		oYAxis.SetMaximumScaleIsAuto(TRUE);
		oYAxis.SetMinimumScaleIsAuto(TRUE);
	}  

	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	oYTitle.SetText(data.yTitle);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	SetActiveSheet(sSheetName);

}


///<summary>WorkSheet에 Chart를 만들 때</summary>
///<para>sTargetSheetName: Chart의 원본 데이타가 있는 SheetName</para>
void CMSExcel::AddChartScatter(ChartData data, long nRow, long nCol, double Width, double Height, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChartScatter(data, sSheetName);
}




void CMSExcel::MakeChartScatter(ChartData data, CString sSheetName)
{
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetChartType((long)data.ChartType);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);

	// 계열이름
	for(int i=0,nSeriesIdx=0; i<data.aSeries.GetSize(); i+=2,nSeriesIdx++)
	{
		try
		{
			Series oSeries = oChart.SeriesCollection(COleVariant((long)(nSeriesIdx+1)));
			oSeries.SetName(data.aSeries[i+1]);

			// 계열범위지정 
			CString csXRange; 
			CString csYRange; 
			csXRange.Format(_T("\'%s\'!%s:%s"),sSheetName, GetCellOrgExp((long)data.nStRow, (long)data.nStCol+i),  GetCellOrgExp((long)data.nEdRow, (long)data.nStCol+i));
			csYRange.Format(_T("\'%s\'!%s:%s"),sSheetName, GetCellOrgExp((long)data.nStRow, (long)data.nStCol+i+1),GetCellOrgExp((long)data.nEdRow, (long)data.nStCol+i+1));

			CString csFormula2;
			csFormula2.Format(_T("=SERIES(\"%s\",%s,%s,%d)"),data.aSeries[i+1],csXRange,csYRange,nSeriesIdx+1);

			oSeries.SetFormula(csFormula2);
			oSeries.SetFormulaLocal(csFormula2);
		}
		catch(...){}
	}

	//범례
	oChart.SetHasLegend(data.bLegend);
	if(data.bLegend)
	{
		Legend oLeg = oChart.GetLegend();
		oLeg.SetPosition(data.LegendPosition);
	}

	//X 축
	Axis oXAxis = oChart.Axes(COleVariant((long)xlCategory), 1);
	oXAxis.SetHasTitle(TRUE);
	oXAxis.SetMaximumScaleIsAuto(TRUE);
	oXAxis.SetMinimumScaleIsAuto(TRUE);

	if(fabs(data.dXmax)<1.0E+21)
	{
		oXAxis.SetMaximumScaleIsAuto(FALSE);
		oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
		oXAxis.SetMinimumScaleIsAuto(FALSE);
		oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
		oXAxis.SetMajorUnit(data.nXunit);
	}

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	oXTitle.SetText(data.xTitle);

	//Y 축
	Axis oYAxis = oChart.Axes(COleVariant((long)xlValue), 1);
	oYAxis.SetHasTitle(TRUE);

	oYAxis.SetMaximumScaleIsAuto(TRUE);
	oYAxis.SetMinimumScaleIsAuto(TRUE);

	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	oYTitle.SetText(data.yTitle);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	SetActiveSheet(sSheetName);
}


///<summary>WorkSheet에 Chart를 만들 때</summary>
///<para>sTargetSheetName: Chart의 원본 데이타가 있는 SheetName</para>
void CMSExcel::AddChartLine(ChartData data, long nRow, long nCol, 
							double Width, double Height, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChartLine(data, sSheetName);
}

void CMSExcel::MakeChartLine(ChartData data, CString sSheetName)
{
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetChartType((long)data.ChartType);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);

	//계열이름
	for(int i=0; i<data.aSeries.GetSize(); i++)
	{
		try
		{
			Series oSeries = oChart.SeriesCollection(COleVariant((long)(i+1)));
			oSeries.SetName(data.aSeries[i]);
		}
		catch(...){}
	}

	//범례
	oChart.SetHasLegend(data.bLegend);
	if(data.bLegend)
	{
		Legend oLeg = oChart.GetLegend();
		oLeg.SetPosition(data.LegendPosition);
	}

	//X 축
	Axis oXAxis = oChart.Axes(COleVariant((long)xlCategory), 1);
	oXAxis.SetHasTitle(TRUE);
	//oXAxis.SetMaximumScaleIsAuto(TRUE);
	//oXAxis.SetMinimumScaleIsAuto(TRUE);

	/*
	if(fabs(data.dXmax)<1.0E+21)
	{
	oXAxis.SetMaximumScaleIsAuto(FALSE);
	oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
	oXAxis.SetMinimumScaleIsAuto(FALSE);
	oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
	oXAxis.SetMajorUnit(data.nXunit);
	}
	*/

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	oXTitle.SetText(data.xTitle);

	//Y 축
	Axis oYAxis = oChart.Axes(COleVariant((long)xlValue), 1);
	oYAxis.SetHasTitle(TRUE);

	//	if(fabs(data.dYmax)<1.0E+21)  oYAxis.SetMaximumScale(data.dYmax);
	//	if(fabs(data.dYmin)<1.0E+21)  oYAxis.SetMinimumScale(data.dYmin);

	oYAxis.SetMaximumScaleIsAuto(TRUE);
	oYAxis.SetMinimumScaleIsAuto(TRUE);

	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	oYTitle.SetText(data.yTitle);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	SetActiveSheet(sSheetName);
}


///<summary>WorkSheet에 Chart를 만들 때</summary>
///Stringrey의 HBAR 타입으로 그린 Graph를 Excel로 그릴때 사용. // MNET:XXXX-이종협-20081028
void CMSExcel::AddChartLineHBAR(ChartData data, long nRow, long nCol, 
								double Width, double Height, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);

	MakeChartLineHBAR(data, sSheetName);
}

void CMSExcel::MakeChartLineHBAR(ChartData data, CString sSheetName)
{
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetChartType((long)data.ChartType);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);

	//계열이름
	for(int i=1; i<data.aSeries.GetSize(); i++)
	{
		try
		{
			Series oSeries = oChart.SeriesCollection(COleVariant((long)i));
			oSeries.SetName(data.aSeries[i]);
		}
		catch(...){}
	}

	//범례
	oChart.SetHasLegend(data.bLegend);
	if(data.bLegend)
	{
		Legend oLeg = oChart.GetLegend();
		oLeg.SetPosition(data.LegendPosition);
	}

	//X 축
	Axis oXAxis = oChart.Axes(COleVariant((long)xlCategory), 1);
	oXAxis.SetHasTitle(TRUE);
	//oXAxis.SetMaximumScaleIsAuto(TRUE);
	//oXAxis.SetMinimumScaleIsAuto(TRUE);

	/*
	if(fabs(data.dXmax)<1.0E+21)
	{
	oXAxis.SetMaximumScaleIsAuto(FALSE);
	oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
	oXAxis.SetMinimumScaleIsAuto(FALSE);
	oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
	oXAxis.SetMajorUnit(data.nXunit);
	}
	*/

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	oXTitle.SetText(data.yTitle);

	//Y 축
	Axis oYAxis = oChart.Axes(COleVariant((long)xlValue), 1);
	oYAxis.SetHasTitle(TRUE);

	//	if(fabs(data.dYmax)<1.0E+21)  oYAxis.SetMaximumScale(data.dYmax);
	//	if(fabs(data.dYmin)<1.0E+21)  oYAxis.SetMinimumScale(data.dYmin);

	oYAxis.SetMaximumScaleIsAuto(TRUE);
	oYAxis.SetMinimumScaleIsAuto(TRUE);

	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	oYTitle.SetText(data.xTitle);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	SetActiveSheet(sSheetName);
}

// Add by GAY.('06.02.01) Helper Method
// pDisp 의 크기 또는 개수를 얻는 함수
int CMSExcel::GetPropertyCount(IDispatch* pDisp)
{
	int count = 0;

	if(pDisp != NULL)
	{
		VARIANT result;
		VariantInit(&result);

		HRESULT hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pDisp, L"Count", 0);
		if(FAILED(hr))
		{
			::MessageBox(NULL, _T("IDispatch Count Not Found"), _T("Error"), MB_SETFOREGROUND | MB_OK);
			return count;
		}
		count = (int)result.lVal;
	}
	return count;
}

// Add by GAY.('06.02.01) Range 영역의 행과 열의 개수
// [param] 크기를 알고자 하는 Range
// [param] Range의 행수
// [param] Range의 열수
void CMSExcel::GetRangeCount(Range range, int& rowCnt, int& colCnt)
{
	rowCnt = GetPropertyCount(range.GetRows());
	colCnt = GetPropertyCount(range.GetColumns());
}


// Add by GAY.('06.02.01) Helper Method
// "http://support.microsoft.com/kb/216686/" 참고
// AutoWrap() 함수는 직접 IDispatch를 사용하는 것과 관련된 대부분의 하위 수준 세부 사항을 단순화합니다.
HRESULT CMSExcel::AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...)
{
	// Begin variable-argument list...
	va_list marker;
	va_start(marker, cArgs);

	if(!pDisp) {
		::MessageBox(NULL, _T("NULL IDispatch passed to AutoWrap()"), _T("Error"), 0x10010);
		_exit(0);
	}

	// Variables used...
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;
	//TCHAR buf[200];
	char szName[200];

	// Convert down to ANSI
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

	// Get DISPID for name passed...
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if(FAILED(hr)) {
		//        sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
		//		::MessageBox(NULL, buf, "AutoWrap()", 0x10010);
		//        _exit(0);
		return hr;
	}

	// Allocate memory for arguments...
	VARIANT *pArgs = new VARIANT[cArgs+1];
	// Extract arguments...
	for(int i=0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts!
	if(autoType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call!
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
	if(FAILED(hr)) {
		//        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
		//		::MessageBox(NULL, buf, "AutoWrap()", 0x10010);
		//        _exit(0);
		return hr;
	}

	// End variable-argument section...
	va_end(marker);

	delete [] pArgs;

	return hr;
}

// Add by GAY.('06.02.01) 같은 Sheet 내의 Hyper Link 설정하기
// [param] ancCell : HyperLink의 Anchor Cell
// [param] lnkCell : HyperLink로 연결할 Cell
void CMSExcel::SetHyperLink(CString ancCell, CString lnkCell)
{  
	LPDISPATCH lpDisp;
	Hyperlinks oHypers;
	lpDisp = oSheet.GetHyperlinks();
	ASSERT(lpDisp);
	oHypers.AttachDispatch(lpDisp);
	oHypers.Add(oSheet.GetRange(COleVariant(ancCell), COleVariant(ancCell)), _T(""), COleVariant(lnkCell), vOpt, vOpt);
}

// Add by GAY.('06.02.01) 다른 Sheet 내의 Hyper Link 설정하기
// [param] ancCell : HyperLink의 Anchor Cell
// [param] lnkSheetName : HyperLink로 연결할 Cell이 위치한 Sheet 이름
// [param] lnkCell : HyperLink로 연결할 Cell
void CMSExcel::SetHyperLink(CString ancCell, CString lnkSheetName, CString lnkCell)
{
	LPDISPATCH lpDisp;
	Hyperlinks oHypers;  
	lpDisp = oSheet.GetHyperlinks();
	ASSERT(lpDisp);
	oHypers.AttachDispatch(lpDisp);
	CString strCell;
	strCell.Format(_T("%s!%s"), lnkSheetName, lnkCell);
	oHypers.Add(oSheet.GetRange(COleVariant(ancCell), COleVariant(ancCell)), _T(""), COleVariant(strCell), vOpt, vOpt);
}

// Add by GAY.('06.02.01) 현재 주어진 Cell의 바로 앞에서 Page 나누기.
// [param] Page가 나뉘어지는 시작 Cell 이름.
void CMSExcel::SetHPageBreakBeforeActiveCell(CString sCell)
{
	LPDISPATCH lpDisp;
	HPageBreaks oHBreaks;
	lpDisp = oSheet.GetHPageBreaks();
	ASSERT(lpDisp);
	oHBreaks.AttachDispatch(lpDisp);
	oHBreaks.Add(oSheet.GetRange(COleVariant(sCell), COleVariant(sCell)));  
}

// 현재 주어진 Cell의 바로 앞에서 Page 나누기.
// [param] Page가 나뉘어지는 시작 Cell Index.
void CMSExcel::SetHPageBreakBeforeActiveCell(long Row, long Col)
{
	CString strCell = GetCell(Row, Col);
	SetHPageBreakBeforeActiveCell(strCell);
}

// Add by GAY.('06.02.01) 현재 WorkBook에 존재하는 WorkSheet의 개수 얻기.
int CMSExcel::GetWorkSheetCount()
{
	LPDISPATCH lpDisp;
	lpDisp = oBook.GetSheets();

	return GetPropertyCount(lpDisp);
}

// Add by GAY.('06.02.01) Default Sheet 를 삭제 (다른 Sheet가 존재하는 경우)
void CMSExcel::DeleteDefaultSheet()
{
	CString strDefaultSheet[3] = { _T("Sheet1"), _T("Sheet2"), _T("Sheet3") };

	for(int i=0; i<3; i++)
	{
		if(IsExistSheetName(strDefaultSheet[i]))
		{
			DeleteSheet(strDefaultSheet[i]);
		}
	}

	/*
	if(GetWorkSheetCount() > 3)
	{
	DeleteSheet("Sheet1");
	DeleteSheet("Sheet2");
	DeleteSheet("Sheet3");
	}
	*/
}

// 해당 Cell을 사용자 지정 Format으로 설정.
void CMSExcel::SetCellInUserFormat(CString sCell1, CString sCell2, CString sFormat)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetNumberFormatLocal(COleVariant(sFormat)); 
}


// 해당 Cell을 사용자 지정 Format으로 출력.
void CMSExcel::SetValueInUserFormat(CString sCell, CString sVal, CString sFormat)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(sCell),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.SetValue(COleVariant(sVal));
	oRange.SetNumberFormatLocal(COleVariant(sFormat));
}


// 그림파일을 해당 Cell에 붙이기.
void CMSExcel::AddPicture(CString sPicName, long Row, long Col, float Width, float Height, int& rowCnt)
{
	LPDISPATCH lpDisp;

	Range oRange;
	CString sCell = GetCell(Row, Col);
	lpDisp = oSheet.GetRange(COleVariant(sCell), vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	float Wi = (float)oRange.GetWidth().dblVal;
	float He = (float)oRange.GetHeight().dblVal;

	Shapes shapes;
	lpDisp = oSheet.GetShapes();	
	ASSERT(lpDisp);
	shapes.AttachDispatch(lpDisp);

	float Left = Wi * Col;
	float Top  = He * Row;

	Width  *= (float)GetValueFromMilimeterToPoint();
	Height *= (float)GetValueFromMilimeterToPoint();

	lpDisp = shapes.AddPicture(sPicName, FALSE, TRUE, Left, Top, Width, Height);
	lpDisp->Release();

	rowCnt = (int)(Height / He - 0.5) + 1;  
}

// 그림 크기를 Excel 내의 크기로 변환하기 위한 Factor.
double CMSExcel::GetValueFromMilimeterToPoint()
{
	return 72.0 / 25.4;   // 1inch = 2.54cm = 72point
}

// Set Page Margin.
void CMSExcel::SetMargin(double dLeft, double dRight, double dTop, double dBot)
{  
	XlPageSetup pageSetup = oSheet.GetPageSetup();
	pageSetup.SetLeftMargin(dLeft * GetValueFromMilimeterToPoint());
	pageSetup.SetRightMargin(dRight * GetValueFromMilimeterToPoint());
	pageSetup.SetTopMargin(dTop * GetValueFromMilimeterToPoint());
	pageSetup.SetBottomMargin(dBot * GetValueFromMilimeterToPoint());
	pageSetup.DetachDispatch();
}

// Insert Picture at Selected Cell.
void CMSExcel::InsertPicture(CString sPicName, long Row, long Col)
{
	LPDISPATCH lpDisp;

	Range oRange;
	CString sCell = GetCell(Row, Col);
	lpDisp = oSheet.GetRange(COleVariant(sCell), vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);
	oRange.Select();

	Pictures oPictures;
	lpDisp = oSheet.GetPictures();
	ASSERT(lpDisp);
	oPictures.AttachDispatch(lpDisp);

	lpDisp = oPictures.Insert(sPicName, vOpt);  
	lpDisp->Release();
}

// ('06.03.14). Change by GAY. 해당이름을 가진 Sheet가 존재하는지의 여부.
BOOL CMSExcel::IsExistSheetName(CString strSheetName)
{
	CStringArray arSheetNames;
	GetSheetsName(arSheetNames);

	int count = (int)arSheetNames.GetSize();
	for(int i=0; i<count; i++)
	{
		if(arSheetNames.GetAt(i) == strSheetName)
		{
			return TRUE;
		}
	}  
	return FALSE;
}

// ('06.03.15). 해당이름을 포함한 Sheet가 존재하는지의 여부.
BOOL CMSExcel::IsExistSheetNameInclude(CString strSheetName)
{
	CStringArray arSheetNames;
	GetSheetsName(arSheetNames);

	int count = (int)arSheetNames.GetSize();
	for(int i=0; i<count; i++)
	{
		if(arSheetNames.GetAt(i).Find(strSheetName) > -1)
		{
			return TRUE;
		}
	}  
	return FALSE;
}

//('06.03.15). 해당이름을 포함한 Sheet 중, 가장 긴 이름 가져오기.
CString CMSExcel::GetMaximumSheetName(CString strSheetName)
{
	CStringArray arSheetNames;
	GetSheetsName(arSheetNames);

	CString result = _T("");
	int count = (int)arSheetNames.GetSize();
	for(int i=0; i<count; i++)
	{
		if(arSheetNames.GetAt(i).Find(strSheetName) > -1)
		{
			if(result.GetLength() < arSheetNames.GetAt(i).GetLength())
			{
				result = arSheetNames.GetAt(i);
			}
		}
	}  
	return result;
}

void CMSExcel::SetSheetSelection(CString strSheetName) //!!!
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	lpDisp = oSheets.GetItem(COleVariant(strSheetName));
	ASSERT(lpDisp);
	oSheet.AttachDispatch(lpDisp);
	oSheet.Select(vOpt);
}

void CMSExcel::AddStyle(CString strStyleName, long fontHeight, COLORREF fontColor, CString sFontType, BOOL bFontBold)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetStyles();
	ASSERT(lpDisp);
	oStyles.AttachDispatch(lpDisp);

	try
	{
		lpDisp = oStyles.GetItem(COleVariant(strStyleName));
	}
	catch(CException* e)
	{
		lpDisp = oStyles.Add(strStyleName, vOpt);
		e->Delete(); 
	}
	catch(...)
	{
	}

	ASSERT(lpDisp);
	oStyle.AttachDispatch(lpDisp);

	oStyle.SetIncludeFont(TRUE);
	oStyle.SetIncludeNumber(TRUE);
	oStyle.SetIncludeBorder(TRUE);

	oFont = oStyle.GetFont();
	oFont.SetSize(COleVariant((long)fontHeight));
	oFont.SetColor(COleVariant((double)fontColor));
	oFont.SetName(COleVariant(sFontType));

	if(bFontBold)
		oFont.SetBold(vTrue);
	else
		oFont.SetBold(vFalse);
}

void CMSExcel::SetStyle(CString sCell1, CString sCell2, CString strStyleName)
{
	LPDISPATCH lpDisp;

	Range oRange;  
	lpDisp = oSheet.GetRange(COleVariant(sCell1),COleVariant(sCell2));
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetStyle(COleVariant(strStyleName));
}

void CMSExcel::SetStyle(long Row1, long Col1, long Row2, long Col2, CString strStyleName)
{
	CString sCell1 = GetCell(Row1, Col1);
	CString sCell2 = GetCell(Row2, Col2);

	SetStyle(sCell1, sCell2, strStyleName);
}

void CMSExcel::SetSheetStyle(CString strStyleName)
{
	LPDISPATCH lpDisp;
	Range oRange;
	lpDisp = oSheet.GetCells();
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	oRange.SetStyle(COleVariant(strStyleName));
}


void CMSExcel::SetDefaultStyle(long fontHeight, COLORREF fontColor, CString sFontType, BOOL bFontBold)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetStyles();
	ASSERT(lpDisp);
	oStyles.AttachDispatch(lpDisp);

	try
	{
		lpDisp = oStyles.GetItem(COleVariant(_T("Normal")));
		ASSERT(lpDisp);
		oStyle.AttachDispatch(lpDisp);

		oFont = oStyle.GetFont();
		oFont.SetSize(COleVariant((long)fontHeight));
		oFont.SetColor(COleVariant((double)fontColor));
		oFont.SetName(COleVariant(sFontType));

		if(bFontBold)
			oFont.SetBold(vTrue);
		else
			oFont.SetBold(vFalse);
	}  
	catch(...)
	{
	}  
}

////////////////////////////////////////////////////////////////////////////
// SeriesCollection의 NewSeries가 안되는 관계로 그래프를 미리 만들고 타입을 변경하는 방법으로 전환
void CMSExcel::AddInEmptyChart(ChartData data, CString sTargetSheetName)
{
	int i;
	LPDISPATCH lpDisp;
	VARIANT var;
	Series oSeries;
	COleVariant m_vTrue  = COleVariant((long)TRUE);

	oChart.SetChartType((long)xlLineMarkers);
	Range oRange = oSheet.GetRange(COleVariant(data.SourceData), vOpt);
	oChart.SetSourceData(oRange, COleVariant((long)data.PlotBy));

	//Chart 제목
	oChart.SetHasTitle(TRUE);
	ChartTitle oChTitle = oChart.GetChartTitle();
	oChTitle.SetText(data.ChartTitle);    

	oChart.SetChartType((long)xlXYScatterSmooth);

	int nXValue=(int)data.aXValue.GetSize();
	for(i=0;i<nXValue;i++)
	{
		int nIdx = i+1;
		Series oSeries = oChart.SeriesCollection(COleVariant((long)nIdx));

		// 범례의 갯수는 그래프의 갯수와 같아야 한다. 
		// 아니면 첨부터 데이터가 없다면 범례를 그리지 않기 위함이다. 
		if(data.aName.GetSize()==nXValue)
		{
			oSeries.SetName(data.aName[i]);
		}

		lpDisp = oSheet.GetRange(COleVariant(data.aXValue[i]), vOpt);
		var.vt = VT_DISPATCH;
		var.pdispVal = lpDisp;
		oSeries.SetXValues(var);

		lpDisp = oSheet.GetRange(COleVariant(data.aYValue[i]), vOpt);
		var.vt = VT_DISPATCH;
		var.pdispVal = lpDisp;
		oSeries.SetValues(var);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//X 축
	oChart.SetHasAxis(COleVariant((long)xlCategory), COleVariant((long)xlPrimary), COleVariant((long)data.bXAxis));
	Axis oXAxis = oChart.Axes(COleVariant((long)xlCategory), 1);
	oXAxis.SetHasTitle(data.bXTitle);
	oXAxis.SetHasMajorGridlines(data.bXMajorGridLine);
	oXAxis.SetHasMinorGridlines(data.bXMinorGridLine);

	if(fabs(data.dXmax)<1.0E+21)
	{
		oXAxis.SetMaximumScaleIsAuto(FALSE);
		oXAxis.SetMaximumScale(data.dXmax);
	}

	if(fabs(data.dXmin)<1.0E+21)
	{
		oXAxis.SetMinimumScaleIsAuto(FALSE);
		oXAxis.SetMinimumScale(data.dXmin);
	}

	if(data.nXunit>0)
	{
		oXAxis.SetMajorUnit(data.nXunit);
	}

	AxisTitle oXTitle = oXAxis.GetAxisTitle();
	if(data.bXTitle)
		oXTitle.SetText(data.xTitle);

	//Y 축
	oChart.SetHasAxis(COleVariant((long)xlValue), COleVariant((long)xlPrimary), COleVariant((long)data.bYAxis));
	Axis oYAxis = oChart.Axes(COleVariant((long)xlValue), 1);
	oYAxis.SetHasTitle(data.bYTitle);
	oYAxis.SetHasMajorGridlines(data.bYMajorGridLine);
	oYAxis.SetHasMinorGridlines(data.bYMinorGridLine);

	//	if(fabs(data.dYmax)<1.0E+21)  oYAxis.SetMaximumScale(data.dYmax);
	//	if(fabs(data.dYmin)<1.0E+21)  oYAxis.SetMinimumScale(data.dYmin);

	oYAxis.SetMaximumScaleIsAuto(TRUE);
	if(data.nYunit>0)
		oYAxis.SetMajorUnit(data.nYunit);

	AxisTitle oYTitle = oYAxis.GetAxisTitle();
	if(data.bYTitle)
		oYTitle.SetText(data.yTitle);

	//범례
	oChart.SetHasLegend(data.bLegend);
	Legend oLeg = oChart.GetLegend();
	if(data.bLegend)
		oLeg.SetPosition(data.LegendPosition);

	//Data Lable
	oChart.ApplyDataLabels(data.labelsType, vFalse, vTrue, vFalse);

	//Data Table
	oChart.SetHasDataTable(data.bDataTable);

	//Interior Color
	PlotArea plot = oChart.GetPlotArea();
	Interior itr = plot.GetInterior();
	itr.SetColorIndex(COleVariant(data.color));

	ChartArea area = oChart.GetChartArea();
	ExcelFont font = area.GetFont();
	font.SetSize(COleVariant((long)data.nFontSize));
	font.SetName(COleVariant(data.sFontName));
	font.SetFontStyle(COleVariant(data.sFontStyle));

	//SetActiveSheet(sSheetName);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//데이터가 하나인 경우나 서브타이틀을 정하지 않은 경우는 범례가 있을 이유가 없다.
	if(data.aName.GetSize() == 0 || data.aXValue.GetSize() == 1)
	{
		Legend oRegend = oChart.GetLegend();
		oRegend.Delete();
	}
}

void CMSExcel::MakeEmptyChart(long nRow, long nCol, double Width, double Height, CString sTargetSheetName)
{
	LPDISPATCH lpDisp;

	lpDisp = oBook.GetSheets();
	ASSERT(lpDisp);
	oSheets.AttachDispatch(lpDisp);

	CString sSheetName = oSheet.GetName();

	Range oRange;
	lpDisp = oSheet.GetRange(COleVariant(_T("A1")),vOpt);
	ASSERT(lpDisp);
	oRange.AttachDispatch(lpDisp);

	double Left = nCol*oRange.GetWidth().dblVal;
	double Top  = nRow*oRange.GetHeight().dblVal;

	lpDisp = oSheet.ChartObjects(vOpt);
	oChartObjs.AttachDispatch(lpDisp);

	lpDisp = oChartObjs.Add(Left, Top, Width, Height);
	oChartObj.AttachDispatch(lpDisp);

	oChartObj.Select(vOpt);
	oChart = oChartObj.GetChart();

	if(sTargetSheetName == "") sTargetSheetName = sSheetName;
	SetActiveSheet(sTargetSheetName);
}

void CMSExcel::ChangeChartType(XlChartType eType)
{
	try
	{
		oChart.SetChartType(eType);
	}
	catch(COleDispatchException* e)
	{
		CString strCause = _T("Error in executing Excel Automation:\n");
		strCause += e->m_strDescription;
	}
}

//////////////////////////////////////////////////////////////////////////
// Member Function이 아님. 
// Get Existed Excel Process ID
BOOL CMSExcel::GetExistedExcelProcessID(CArray<unsigned int, unsigned int>& arProcID)
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
DWORD CMSExcel::KillExcelProcess(CArray<unsigned int, unsigned int>& arProcID)
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
BOOL CMSExcel::IsContainsProcessID(CArray<unsigned int, unsigned int>& arProcID, unsigned int procID)
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