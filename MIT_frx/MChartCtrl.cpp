#include "stdafx.h"

#include "MChartCtrl.h"

#define EXPORT_CANCEL -1
#define EXPORT_FAILED 0
#define EXPORT_SUCCESS 1

using namespace mit::frx;

IMPLEMENT_DYNAMIC(MChartCtrl, CBCGPChartCtrl)
MChartCtrl::MChartCtrl()
{
	//m_pChart = NULL;
	m_bTooltipTrackingMode = TRUE;
}

MChartCtrl::~MChartCtrl()
{

}

BEGIN_MESSAGE_MAP(MChartCtrl, CBCGPChartCtrl)
	ON_WM_CREATE()
	/*ON_WM_CONTEXTMENU()*/
// 	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_TRACK, OnMouseTrack)
// 	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_AFTER_DRAW, OnAfterDraw)
// 	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_AFTER_RECALC_LAYOUT, OnAfterRecalcLayout)
	ON_COMMAND(ID_CHT_TABBED_DOCUMENT, OnTabbedDocument)
	ON_COMMAND(ID_CHT_EXPORT_TO_IMAGE, OnExportToImage)
END_MESSAGE_MAP()

void MChartCtrl::SetChart(CHART_CATEGORY category, CHART_TYPE type /* = tSIMPLE */, BOOL bRedraw /* = TRUE */, BOOL bResetAxesDisplayRange /* = TRUE */)
{
	CBCGPChartVisualObject* pChart = GetChart();

	switch (category)
	{
	case cDEFAULT:
		pChart->SetChartType(BCGPChartCategory::BCGPChartDefault, (BCGPChartType)type, bRedraw, bResetAxesDisplayRange);
		break;
	case cLINE:
		pChart->SetChartType(BCGPChartCategory::BCGPChartLine, (BCGPChartType)type, bRedraw, bResetAxesDisplayRange);
		break;
	case cCOLUMN:
		pChart->SetChartType(BCGPChartCategory::BCGPChartColumn, (BCGPChartType)type, bRedraw, bResetAxesDisplayRange);
		break;
	case cBAR:
		pChart->SetChartType(BCGPChartCategory::BCGPChartBar, (BCGPChartType)type, bRedraw, bResetAxesDisplayRange);
		break;
	case cLARGEDATA:
		pChart->SetChartType(BCGPChartCategory::BCGPChartLongData, (BCGPChartType)type, bRedraw, bResetAxesDisplayRange);
	default:
		return;
		break;
	}
}

// void MChartCtrl::SetChartDataLabelDataFormat(CString strFormat)
// {
// 	int nSerisCount = m_pChart->GetSeriesCount();
// 
// 	for(int i = 0; i < nSerisCount; i++)
// 	{
// 		CBCGPChartSeries* pSeries = m_pChart->GetSeries(i);
// 		pSeries->SetDataLabelDataFormat(strFormat);
// 	}
// }

void MChartCtrl::AddData(int nSeriesIndex, double dXValue, double dYValue)
{
	CBCGPChartVisualObject* pChart = GetChart();

	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		pSeries = pChart->CreateSeries(_T(""));
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	pSeries->AddDataPoint(dYValue, dXValue);
	
	/*Redraw();*/
}

void MChartCtrl::AddData(int nSeriesIndex, CString strXValue, double dYValue)
{
	CBCGPChartVisualObject* pChart = GetChart();

	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

//	CBCGPChartBarSeries* pSeries;
	CBCGPChartSeries* pSeries;

// 	if(nNumOfSeries <= nSeriesIndex)
// 		pSeries = DYNAMIC_DOWNCAST(CBCGPChartBarSeries, pChart->CreateSeries(_T("")));
// 	else
// 		pSeries = DYNAMIC_DOWNCAST(CBCGPChartBarSeries, pChart->GetSeries(nSeriesIndex));

	if(nNumOfSeries <= nSeriesIndex)
		pSeries = pChart->CreateSeries(_T(""));
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	if(strXValue != _T(""))
		pSeries->AddDataPoint(strXValue, dYValue);
	else
		pSeries->AddDataPoint(dYValue);
	
	/*Redraw();*/
}

void MChartCtrl::AddData(int nSeriesIndex, CString dXValue, CString dYValue)
{
	double dX = 0.0;
	double dY = 0.0;

	// Y 값은 항상 숫자 여야 함... 숫자 표시 방법?!
	/*
	if(Y != 숫자) return;

	if(X == 숫자) AddData(숫자X, 숫자Y);
	else series->AddDataPoint(스트링X, 숫자Y);
	*/
	
}

BOOL MChartCtrl::IsEnableMarker(int nSeriesIndex)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	if(nNumOfSeries <= nSeriesIndex)
	{
		ASSERT(0);
		return FALSE;
	}

	CBCGPChartSeries* pSeries = pChart->GetSeries(nSeriesIndex);
	return pSeries->GetSeriesFormat().m_markerFormat.m_options.m_bShowMarker;
}

void MChartCtrl::EnableMarker(BOOL bEnable /* = TRUE */, int nSeriesIndes /* = -1 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	if(nSeriesIndes == -1)
	{
		EnableMarkerAll(bEnable);
	}
	else
	{
		if(nNumOfSeries <= nSeriesIndes) return;

		CBCGPChartSeries* pSeries = pChart->GetSeries(nSeriesIndes);

		pSeries->ShowMarker(bEnable);
		
		/*Redraw();*/
	}
}

void MChartCtrl::EnableMarkerAll(BOOL bEnable)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->ShowDataMarkers(bEnable);

	/*Redraw();*/
}

void MChartCtrl::SetTitle(CString strTitle /* = _T */, BOOL bVisible /* = TRUE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartTitle(strTitle);
	pChart->ShowChartTitle(bVisible);
}

CString MChartCtrl::GetTitle()
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	return pChart->GetChartTitle();
}

void MChartCtrl::SetChartTitle(LPCTSTR lpcszText, BCGPChartFormatLabel* pTitleFormat /* = NULL */, BOOL bAdjustLayout /* = FALSE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartTitle(lpcszText, pTitleFormat, bAdjustLayout);
}

void MChartCtrl::ShowChartTitle(BOOL bShow /* = TRUE */, BOOL bTitleOverlapsChart /* = FALSE */, BOOL bRedraw /* = FALSE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->ShowChartTitle(bShow, bTitleOverlapsChart, bRedraw);
}

void MChartCtrl::SetTitleColor(COLORREF rgbTitle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	BCGPChartFormatLabel titleFormat = pChart->GetTitleLabelFormat();
	titleFormat.m_brTextColor = CBCGPBrush(rgbTitle, 1);

	pChart->SetChartTitle(pChart->GetChartTitle(), &titleFormat);
}

void MChartCtrl::SetTitleAlign(TITLE_ALIGN align, TITLE_ALIGN verticalAlign)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	BCGPChartFormatLabel titleFormat = pChart->GetTitleLabelFormat();
	titleFormat.m_textFormat.SetTextAlignment((CBCGPTextFormat::BCGP_TEXT_ALIGNMENT)align);
	titleFormat.m_textFormat.SetTextVerticalAlignment((CBCGPTextFormat::BCGP_TEXT_ALIGNMENT)verticalAlign);

	pChart->SetChartTitle(pChart->GetChartTitle(), &titleFormat);
}

void MChartCtrl::SetTitleSize(float fFontSize)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	BCGPChartFormatLabel titleFormat = pChart->GetTitleLabelFormat();
	titleFormat.m_textFormat.SetFontSize(fFontSize);
	
	pChart->SetChartTitle(pChart->GetChartTitle(), &titleFormat);
}

double MChartCtrl::GetMinValueOfChart(AXIS axisType /* = AXIS::Y_1 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPChartData::ComponentIndex ci;
	switch (axisType)
	{
	case MChartCtrl::X_1:
	case MChartCtrl::X_2:
		ci = CBCGPChartData::CI_X;
		break;
	case MChartCtrl::Y_1:
	case MChartCtrl::Y_2:
		ci = CBCGPChartData::CI_Y;
		break;
	default:
		ci = CBCGPChartData::CI_Y;
		break;
	}

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries = pChart->GetSeries(0);
	CBCGPChartValue minValue = pSeries->GetMinValue(ci);
	double dMin = minValue.GetValue();

	for(int i = 1; i < nNumOfSeries; i++)
	{
		pSeries = pChart->GetSeries(i);
		minValue = pSeries->GetMinValue(ci);
		if(dMin > minValue.GetValue())
		{
			dMin = minValue.GetValue();
		}
	}

	return dMin;
}

double MChartCtrl::GetMaxValueOfChart(AXIS axisType /* = AXIS::Y_1 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPChartData::ComponentIndex ci;
	switch (axisType)
	{
	case MChartCtrl::X_1:
	case MChartCtrl::X_2:
		ci = CBCGPChartData::CI_X;
		break;
	case MChartCtrl::Y_1:
	case MChartCtrl::Y_2:
		ci = CBCGPChartData::CI_Y;
		break;
	default:
		ci = CBCGPChartData::CI_Y;
		break;
	}

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries = pChart->GetSeries(0);
	CBCGPChartValue maxValue = pSeries->GetMaxValue(ci);
	double dMax = maxValue.GetValue();

	for(int i = 1; i < nNumOfSeries; i++)
	{
		pSeries = pChart->GetSeries(i);
		maxValue = pSeries->GetMaxValue(ci);
		if(dMax < maxValue.GetValue())
		{
			dMax = maxValue.GetValue();
		}
	}

	return dMax;
}

void MChartCtrl::RemoveData(int nSeriesIndex)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPChartSeries* pSeries = pChart->GetSeries(nSeriesIndex);

	pSeries->RemoveAllDataPoints();

	//pChart->RemoveSeriesData(nSeriesIndex);
}

void MChartCtrl::RemoveDataAll()
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->CleanUpChartData();

	if(((MChartVisualObject*)pChart)->GetLegendType())
		((MChartVisualObject*)pChart)->SetLegendType(FALSE);
	/*
	int nNumOfSeries = m_pChart->GetSeriesCount();

	for(int i = 0; i < nNumOfSeries; i++)
	{
		RemoveData(i);
	}
	*/
}

void MChartCtrl::RemoveLegendAll()
{
// 	m_pChart->RemoveAllChartEffects();
// 	m_pChart->legend
// 	CBCGPChartLegendVisualObject* pLegend = m_pChart->GetRelatedLegend();
// 	if(pLegend == NULL)
// 		return;
// 	pLegend->RemoveAllEntries();
}

void MChartCtrl::ShowSummary(BOOL bShowSummary)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	MChartVisualObject* pMChart = (MChartVisualObject*)pChart;

	pMChart->ShowSummary(bShowSummary);
}

void MChartCtrl::AxisVisible(AXIS axisType, BOOL bVisible /* = TRUE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	if(axisType == X_1)
	{
		pChart->ShowAxis(BCGP_CHART_X_PRIMARY_AXIS, bVisible);
	}
	else if(axisType == Y_1)
	{
		pChart->ShowAxis(BCGP_CHART_Y_PRIMARY_AXIS, bVisible);
	}
	else if(axisType == X_2)
	{
		pChart->ShowAxis(BCGP_CHART_X_SECONDARY_AXIS, bVisible);
	}
	else if(axisType == Y_2)
	{
		pChart->ShowAxis(BCGP_CHART_Y_SECONDARY_AXIS, bVisible);
	}
	else
	{
		return;
	}

	/*Redraw();*/
}

void MChartCtrl::SetSecondaryAxis(BOOL bSecondaryX, BOOL bSecondaryY, int nSeriesIndex /* = 1 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeires = pChart->GetSeriesCount();

	if(nSeriesIndex >= nNumOfSeires) return;

	CBCGPChartSeries* pSeries = pChart->GetSeries(nSeriesIndex);

	pSeries->SetRelatedAxes(pChart->GetChartAxis(bSecondaryX ? BCGP_CHART_X_SECONDARY_AXIS : BCGP_CHART_X_PRIMARY_AXIS), 
							pChart->GetChartAxis(bSecondaryY ? BCGP_CHART_Y_SECONDARY_AXIS : BCGP_CHART_Y_PRIMARY_AXIS));
	
}

void MChartCtrl::SetAxisTitle(AXIS axisType, LPCTSTR strAxisTitle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	if(axisType == X_1)
	{
		pChart->SetAxisName(BCGP_CHART_X_PRIMARY_AXIS, strAxisTitle);
	}
	else if(axisType == Y_1)
	{
		pChart->SetAxisName(BCGP_CHART_Y_PRIMARY_AXIS, strAxisTitle);
	}
	else if(axisType == X_2)
	{
		pChart->SetAxisName(BCGP_CHART_X_SECONDARY_AXIS, strAxisTitle);
	}
	else if(axisType == Y_2)
	{
		pChart->SetAxisName(BCGP_CHART_Y_SECONDARY_AXIS, strAxisTitle);
	}
	else
	{
		return;
	}
	
	ShowAxisTitle(axisType, TRUE);
	/*Redraw();*/
}

void MChartCtrl::ShowAxisTitle(AXIS axisType, BOOL bVisible /* = TRUE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	if(axisType == X_1)
	{
		pChart->ShowAxisName(BCGP_CHART_X_PRIMARY_AXIS, bVisible);
	}
	else if(axisType == Y_1)
	{
		pChart->ShowAxisName(BCGP_CHART_Y_PRIMARY_AXIS, bVisible);
	}
	else if(axisType == X_2)
	{
		pChart->ShowAxisName(BCGP_CHART_X_SECONDARY_AXIS, bVisible);
	}
	else if(axisType == Y_2)
	{
		pChart->ShowAxisName(BCGP_CHART_Y_SECONDARY_AXIS, bVisible);
	}
	else
	{
		return;
	}

	/*Redraw();*/
}

void MChartCtrl::SetAxisTitleColor(AXIS axisType, COLORREF rgbTitle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	if(axisType == X_1)
	{
		pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS)->m_axisNameFormat.m_brTextColor = CBCGPBrush(rgbTitle, 1);
	}
	else if(axisType == Y_1)
	{
		pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS)->m_axisNameFormat.m_brTextColor = CBCGPBrush(rgbTitle, 1);
	}
	else if(axisType == X_2)
	{
		pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS)->m_axisNameFormat.m_brTextColor = CBCGPBrush(rgbTitle, 1);
	}
	else if(axisType == Y_2)
	{
		pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS)->m_axisNameFormat.m_brTextColor = CBCGPBrush(rgbTitle, 1);
	}
	else
	{
		return;
	}

	/*Redraw();*/
}

void MChartCtrl::SetAxisTitleSize(AXIS axisType, float fFontSize)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	if(axisType == X_1)
	{
		pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS)->m_axisNameFormat.m_textFormat.SetFontSize(fFontSize);
	}
	else if(axisType == Y_1)
	{
		pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS)->m_axisNameFormat.m_textFormat.SetFontSize(fFontSize);
	}
	else if(axisType == X_2)
	{
		pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS)->m_axisNameFormat.m_textFormat.SetFontSize(fFontSize);
	}
	else if(axisType == Y_2)
	{
		pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS)->m_axisNameFormat.m_textFormat.SetFontSize(fFontSize);
	}
	else
	{
		return;
	}

	/*Redraw();*/
}

void MChartCtrl::SetAxisLabelAngle(AXIS axisType, double dAngle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		CBCGPChartAxis* pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		CBCGPChartAxis* pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		CBCGPChartAxis* pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		CBCGPChartAxis* pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->m_axisLabelsFormat.m_textFormat.SetDrawingAngle(dAngle);
	/*Redraw();*/
}

void MChartCtrl::SetAxisAutoDisplayRange(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pChart->SetAutoDisplayRange(TRUE, TRUE);
	SetDirty();
	Redraw();
	//pAxis->SetAutoDisplayRange();
}

void MChartCtrl::SetAxisRange(AXIS axisType, double dMin, double dMax, double dUnit /* = 0.0 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->SetFixedDisplayRange(dMin, dMax, dUnit);

// 	SetDirty();
// 	Redraw();
}

void MChartCtrl::SetAxisMinValue(AXIS axisType, double dMin)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->SetFixedMinimumDisplayValue(dMin);
}

void MChartCtrl::SetAxisMaxValue(AXIS axisType, double dMax)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->SetFixedMaximumDisplayValue(dMax);
}

void MChartCtrl::SetAxisUnit(AXIS axisType, double dUnit)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}
	pAxis->SetFixedMajorUnit(dUnit);
}

void MChartCtrl::SetAxisInterval(AXIS axisType, double dInterval)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}
}

void MChartCtrl::SetAxisDataFormat(AXIS axisType, CString strFormat)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->m_strDataFormat = strFormat;
}

int MChartCtrl::GetAxisDirection(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return -1;
	}

	// -1 : 그런 축 나는 몰라요
	//  0 : 가로 
	//  1 : 세로
	return (int)(pAxis->IsVertical());
}

void MChartCtrl::SwapAxisDirection(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	else
	{
		return;
	}

	pAxis->SwapDirection(TRUE);
}

void MChartCtrl::SwapAllAxisDirection()
{
	SwapAxisDirection(MChartCtrl::X_1);
	SwapAxisDirection(MChartCtrl::Y_1);
	SwapAxisDirection(MChartCtrl::X_2);
	SwapAxisDirection(MChartCtrl::Y_2);
}

double MChartCtrl::GetAxisMinValue(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
// 	else
// 	{
// 		return;
// 	}

	double dMin = pAxis->GetMinDisplayedValue();

	return dMin;
}

double MChartCtrl::GetAxisMaxValue(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
// 	else
// 	{
// 		return;
// 	}

	double dMax = pAxis->GetMaxDisplayedValue();

	return dMax;
}

double MChartCtrl::GetAxisIntervalUnit(AXIS axisType)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	//-_- 구려..
	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	}
	else if(axisType == Y_1)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	}
	else if(axisType == X_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	}
	else if(axisType == Y_2)
	{
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	}
	
	double dInterval = pAxis->GetMajorUnit();
	return dInterval;
}

void MChartCtrl::SetSeriesName(LPCTSTR strSeriesName, int nSeriesIndex /* = 0 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		pSeries = pChart->CreateSeries(_T(""));
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	pSeries->m_strSeriesName = strSeriesName;
}

void MChartCtrl::SetSeriesColor(int nSeriesIndex, COLORREF rgbColor)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPSeriesColorsPtr psc;
	pSeries->GetColors(psc, 0);

	psc.m_pBrElementLineColor->SetColor(rgbColor);
	psc.m_pBrMarkerFillColor->SetColor(rgbColor);
	psc.m_pBrMarkerLineColor->SetColor(rgbColor);
}

CBCGPColor MChartCtrl::GetSeriesColor(int nSeriesIndex)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return -1;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPSeriesColorsPtr psc;
	pSeries->GetColors(psc, 0);
	
	return psc.m_pBrElementLineColor->GetColor();
}

void MChartCtrl::SetSeriesLineType(int nSeriesIndex, DASH_STYLE dashStyle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

	style.SetSeriesOutlineDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)dashStyle);

	pSeries->SetSeriesFormat(style);
}

MChartCtrl::DASH_STYLE MChartCtrl::GetSeriesLineType(int nSeriesIndex)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return dsSOLID;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

	return (MChartCtrl::DASH_STYLE)(style.m_seriesElementFormat.m_outlineFormat.m_strokeStyle.GetDashStyle());
}

void MChartCtrl::SetSeriesLineWidth(int nSeriesIndex, double dLineWidth)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

	style.SetSeriesLineWidth(dLineWidth);

	pSeries->SetSeriesFormat(style);
}

double MChartCtrl::GetSeriesLineWidth(int nSeriesIndex)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	int nNumOfSeries = pChart->GetSeriesCount();

	CBCGPChartSeries* pSeries;

	if(nNumOfSeries <= nSeriesIndex)
		return -1;
	else
		pSeries = pChart->GetSeries(nSeriesIndex);

	BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

	return style.m_seriesElementFormat.m_outlineFormat.m_dblWidth;
}

void MChartCtrl::AddExtraLine(double dValue, BOOL bHorz /* = TRUE */, COLORREF color /* = RGB */, double dWidth, DASH_STYLE dashStyle)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPBrush brush = CBCGPBrush(color);
	CBCGPStrokeStyle strokeStyle;
	strokeStyle.SetDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)dashStyle);

	pChart->AddChartLineObject(dValue, bHorz, brush, dWidth, &strokeStyle);
}

void MChartCtrl::AddScaleBreak(double dStart, double dEnd, BREAK_STYLE breakeStyle /* = BREAK_STYLE::bsWAVE */, int nGap /* = 7 */, AXIS axisType /*= AXIS::Y_1*/, double dOffSetPercent /* = 50 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPChartScaleBreakOptions sbOptions;
	sbOptions.m_bAutomatic = FALSE;
	sbOptions.m_style = (CBCGPChartAxisScaleBreak::AxisScaleBreakStyle)breakeStyle;

	CBCGPChartAxisScaleBreak sb;
	sb.m_nGap = nGap;
	sb.m_dblOffsetPercent = dOffSetPercent;
	sb.m_scaleBreakStyle = (CBCGPChartAxisScaleBreak::AxisScaleBreakStyle)breakeStyle;
	sb.m_dblStart = dStart;
	sb.m_dblEnd = dEnd;

	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	else if(axisType == X_2)
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	else if(axisType == Y_1)
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	else if(axisType == Y_2)
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	else
		return;

	pAxis->EnableScaleBreaks(TRUE, &sbOptions, FALSE);
	pAxis->AddScaleBreak(sb, TRUE);
}

void MChartCtrl::SetLogScale(BOOL bSet, double dLogBase, AXIS axisType /* = AXIS::Y_1 */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	CBCGPChartAxis* pAxis = NULL;
	if(axisType == X_1)
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	else if(axisType == X_2)
		pAxis = pChart->GetChartAxis(BCGP_CHART_X_SECONDARY_AXIS);
	else if(axisType == Y_1)
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	else if(axisType == Y_2)
		pAxis = pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
	else
		return;

	pAxis->SetLogScale(bSet, dLogBase);
}

void MChartCtrl::SetLegendPosition(LEGEND_POSITION legendPosition, BOOL bLegendOverlapsChart /* = FALSE */, BOOL bRedraw /* = FALSE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->SetLegendPosition((BCGPChartLayout::LegendPosition)legendPosition, bLegendOverlapsChart, bRedraw);
}

void MChartCtrl::SetDirty(BOOL bSet /* = TRUE */, BOOL bRedraw /* = FALSE */)
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->SetDirty(bSet, bRedraw);
}

int MChartCtrl::SaveToImage(CString strChartName)
{
	CString strFileFullName;
	CString csFileName = strChartName + _T(".bmp");
	//LPCTSTR szFileName;

	CFileDialog fd(FALSE, _LSX(.bmp), strChartName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES, 
		_LSX(IMAGE File(*.bmp)|*.bmp|All File(*.*)|*.*||), NULL);

	if(fd.DoModal() == IDOK)
	{
		strFileFullName = fd.GetPathName();
	}
	else
	{
		return EXPORT_CANCEL;
	}

	if(strFileFullName.Compare(_T("")) == 0) return FALSE;
	
	if(ExportToFile(strFileFullName))
	{
		return EXPORT_SUCCESS;
	}
	else
	{
		return EXPORT_FAILED;
	}
	
}

void MChartCtrl::ResetAxis()
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->ResetAxes();
}

void MChartCtrl::Redraw()
{
	CBCGPChartVisualObject* pChart = GetChart();
	ASSERT_VALID(pChart);

	pChart->Redraw();
}

CBCGPDockingControlBar* MChartCtrl::GetParentBar() const
{
	CWnd* pParent = GetParent();
	if(pParent->IsKindOf(RUNTIME_CLASS(CBCGPTabWnd))) pParent = pParent->GetParent();
	return DYNAMIC_DOWNCAST(CBCGPDockingControlBar, pParent);
}

BOOL MChartCtrl::IsMDITabbed() const
{
	CBCGPDockingControlBar* pBar = GetParentBar();
	if (!pBar) return FALSE;
	return pBar->IsMDITabbed();
}

void MChartCtrl::MakeContextMenu(CMenu& menu)
{
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, ID_CHT_EXPORT_TO_IMAGE, _T("Export to Image"));
}

int MChartCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CBCGPChartCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	if(!m_SumWnd.Create(_T("MChartSummaryWnd"), _T("SumWnd"), WS_CHILD|WS_VISIBLE, CRect(10,10,10,10), this, ID_CHT_SUMMARY_WINDOW, NULL)) 
// 	{	
// 		return -1;
// 	}

	return 0;
}

void MChartCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(CBCGPPopupMenu::GetActiveMenu() != NULL) return;

	CMenu menu;
	menu.CreatePopupMenu();
	MakeContextMenu(menu);
	if(IsMDITabbed())
	{
		if(menu.GetMenuItemCount() > 0)
		{
			menu.InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR);
		}
		menu.InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_CHECKED, ID_CHT_TABBED_DOCUMENT, _T("Tabbed Document"));
	}
	HMENU hMenu = menu.Detach();

	CBCGPWorkspace* pWorkspace = GetWorkspace();
	ASSERT(pWorkspace);
	CBCGPContextMenuManager* pContextMenuManager = pWorkspace->GetContextMenuManager();
	ASSERT(pContextMenuManager);
	pContextMenuManager->ShowPopupMenu(hMenu, point.x, point.y, this, TRUE);
}

void MChartCtrl::OnExportToImage()
{
	int nResult = SaveToImage(GetTitle());
	if (nResult == EXPORT_FAILED)         { AfxMessageBox(_T("Export Failed!!"),   MB_OK); }
	else if (nResult == EXPORT_SUCCESS) { AfxMessageBox(_T("Export Success!!"),MB_OK); }
	else if (nResult == EXPORT_CANCEL)    { AfxMessageBox(_T("Export Canceled!!")  ,MB_OK); }
}

BOOL MChartCtrl::OnMouseDown(int nButton, const CBCGPPoint& pt)
{
	CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
	if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
	{
		return pVisualObject->OnMouseDown(nButton, pt);
	}

	return FALSE;
}

void MChartCtrl::OnLegendMouseDown(CBCGPPoint ptHit)
{
	CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
	((MChartVisualObject*)pVisualObject)->UpDownHitTest(ptHit, FALSE);
}

void MChartCtrl::OnLegendMouseUp(CBCGPPoint ptHit)
{
	CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
	((MChartVisualObject*)pVisualObject)->UpDownHitTest(ptHit, TRUE);
}

void MChartCtrl::OnTabbedDocument()
{
	CBCGPDockingControlBar* pBar = GetParentBar();
	if (!pBar) { ASSERT(0); return; }
	ASSERT(pBar->IsMDITabbed());

	CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pBar->GetParent());
	if (!pMDIChild) { ASSERT(0); return; }
	CBCGPMDIFrameWnd* pFrame = DYNAMIC_DOWNCAST(CBCGPMDIFrameWnd, pBar->GetDockSite());
	if (!pFrame) { ASSERT(0); return; }
	pFrame->TabbedDocumentToControlBar(pMDIChild);
}

void MChartCtrl::OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip)
{
	CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
	if (pVisualObject != NULL)
	{
		pVisualObject->OnDraw(pGM, rectClip, BCGP_DRAW_STATIC);
		pVisualObject->OnDraw(pGM, rectClip, BCGP_DRAW_DYNAMIC);
	}
}

double MChartCtrl::Rand(double s, double f)
{
	double minVal = min(s, f);
	double maxVal = max(s, f);

	return (maxVal - minVal) * (double)rand() / (RAND_MAX + 1) + minVal;
}