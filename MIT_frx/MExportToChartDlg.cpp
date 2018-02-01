#include "stdafx.h"
#include "MExportToChartDlg.h"

#include "MChartBar.h"
#include "MChartManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mit::lib;
using namespace mit::frx;

IMPLEMENT_DYNCREATE(MExportToChartDlg, MDialog)

MExportToChartDlg::MExportToChartDlg() :
	MDialog(IDD),
	m_pTable(NULL)
{
	m_bChartCreated = FALSE;
	m_bChangedMinMax = FALSE;
	m_bXExponent = FALSE;
	m_bYExponent = FALSE;

	m_bIsStrVal_X = FALSE;
	m_nLastDrawedSeriesNum = 0;
}

MExportToChartDlg::MExportToChartDlg(MTable* pTable) :
	MDialog(IDD)
{
	m_pTable = pTable;
	m_bChartCreated = FALSE;
	m_bChangedMinMax = FALSE;
	m_bXExponent = FALSE;
	m_bYExponent = FALSE;

	m_bIsStrVal_X = FALSE;

	m_nLastDrawedSeriesNum = 0;
}

MExportToChartDlg::~MExportToChartDlg()
{

}

void MExportToChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_CHART_CTRL, m_Chart);
	DDX_Control(pDX, IDC_EDIT_CHART_NAME, m_editTitle);
	DDX_Control(pDX, IDC_EDIT_XAXIS_NAME, m_editXTitle);
	DDX_Control(pDX, IDC_EDIT_YAXIS_NAME, m_editYTitle);
	DDX_Control(pDX, IDC_EDIT_X_LABEL_POINT, m_editXPoint);
	DDX_Control(pDX, IDC_EDIT_Y_LABEL_POINT, m_editYPoint);
	DDX_Control(pDX, IDC_EDIT_XAXIS_MIN, m_editXMin);
	DDX_Control(pDX, IDC_EDIT_XAXIS_MAX, m_editXMax);
	DDX_Control(pDX, IDC_EDIT_XAXIS_UNIT, m_editXInterval);
	DDX_Control(pDX, IDC_EDIT_YAXIS_MIN, m_editYMin);
	DDX_Control(pDX, IDC_EDIT_YAXIS_MAX, m_editYMax);
	DDX_Control(pDX, IDC_EDIT_YAXIS_UNIT, m_editYInterval);
	DDX_Control(pDX, IDC_EDIT_LINEWIDTH, m_editLineWidth); // linewidth edit??
	DDX_Control(pDX, IDC_SPIN_LINEWIDTH, m_spinLineWidth);
	DDX_Control(pDX, IDC_CHECK_X_EXPONENT, m_chkXPoint);
	DDX_Control(pDX, IDC_CHECK_Y_EXPONENT, m_chkYPoint);
	DDX_Control(pDX, IDC_CHECK_VERTICAL_TO_XAXIS, m_chkAxisChange);
	DDX_Control(pDX, IDC_CHECK_USE_SUMMARY, m_chkSummary);
	DDX_Control(pDX, IDC_CHECK_CONSIDER_MIN_MAX, m_chkConsiderMinMax);
	DDX_Control(pDX, IDC_CHECK_VISIBLE_MARK, m_chkVisibleMark);
	DDX_Control(pDX, IDC_BUTTON_EXPORT_TO_IMAGE, m_btnExportToImage);
	DDX_Control(pDX, IDC_BTN_MAKE_PREVIEW, m_btnDrawChart);
	DDX_Control(pDX, IDC_BUTTON_ZOOM_FIT, m_btnNoConsiderMinMax);
	DDX_Control(pDX, IDC_LIST_COL_FOR_YAXIS, m_chklistY);
	DDX_Control(pDX, IDC_COMBO_COL_FOR_XAXIS, m_comboX);
	DDX_Control(pDX, IDC_COMBO_LINETYPE, m_comboLineType);
	DDX_Control(pDX, IDC_BUTTON_COLORPICKER, m_ColorPicker);
	DDX_Control(pDX, IDC_STATIC_SEL_SERIES_NAME, m_staticSelColName);
}

BEGIN_MESSAGE_MAP(MExportToChartDlg, MDialog)
	//{{AFX_MSG_MAP(MAutoDestroyBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_MAKE_PREVIEW, OnBnClickedDrawChart)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_TO_IMAGE, OnBnClickedExportImage)
//	ON_BN_CLICKED(IDC_EXPTOCHART_BTN_VIEW, OnBnClickedExportView)
	ON_CLBN_CHKCHANGE(IDC_LIST_COL_FOR_YAXIS, OnChkChangeYList)
	ON_LBN_SELCHANGE(IDC_LIST_COL_FOR_YAXIS, OnSelItemYList)
	ON_CBN_SELENDOK(IDC_COMBO_COL_FOR_XAXIS, OnComboChangeXList)
 	ON_CBN_SELENDOK(IDC_COMBO_LINETYPE, OnComboChangeLineType)
 	ON_BN_CLICKED(IDC_BUTTON_COLORPICKER, OnColorPickerClicked)
	ON_EN_CHANGE(IDC_EDIT_CHART_NAME, OnEditChangeChartTitle)
	ON_EN_CHANGE(IDC_EDIT_XAXIS_NAME, OnEditChangeXTitle)
	ON_EN_CHANGE(IDC_EDIT_YAXIS_NAME, OnEditChangeYTitle)
	ON_BN_CLICKED(IDC_CHECK_X_EXPONENT, OnBnClickedXExponent)
	ON_BN_CLICKED(IDC_CHECK_Y_EXPONENT, OnBnClickedYExponent)
	ON_BN_CLICKED(IDC_CHECK_VERTICAL_TO_XAXIS, OnBnClickedAxisChange)
//	ON_BN_CLICKED(IDC_EXPTOCHART_CHKBOX_SUMMARY, OnBnClickedShowSummary)
	ON_BN_CLICKED(IDC_CHECK_VISIBLE_MARK, OnBnClickedVisibleMark)
	ON_BN_CLICKED(IDC_CHECK_CONSIDER_MIN_MAX, OnBnClickedConsiderMinMax)
 	ON_EN_CHANGE(IDC_EDIT_XAXIS_MIN, OnEditChangeXRangeMin)
 	ON_EN_CHANGE(IDC_EDIT_XAXIS_MAX, OnEditChangeXRangeMax)
 	ON_EN_CHANGE(IDC_EDIT_XAXIS_UNIT, OnEditChangeXInterval)
	ON_EN_CHANGE(IDC_EDIT_YAXIS_MIN, OnEditChangeYRangeMin)
	ON_EN_CHANGE(IDC_EDIT_YAXIS_MAX, OnEditChangeYRangeMax)
 	ON_EN_CHANGE(IDC_EDIT_YAXIS_UNIT, OnEditChangeYInterval)
	ON_EN_CHANGE(IDC_EDIT_X_LABEL_POINT, OnEditChangeXPoint)
	ON_EN_CHANGE(IDC_EDIT_Y_LABEL_POINT, OnEditChangeYPoint)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LINEWIDTH, OnDeltaposSpinLdSet)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_FIT, OnBnclickedFullZoom)

	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_DOWN, OnLegendMouseDown)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_UP, OnLegendMouseUp)
END_MESSAGE_MAP()

LRESULT MExportToChartDlg::OnLegendMouseDown(WPARAM wp, LPARAM lp)
{
	BCGPChartHitInfo* pt = (BCGPChartHitInfo*)lp;

	m_Chart.OnLegendMouseDown(pt->m_ptHit);
	//AfxMessageBox(_T("click"));
	return 0;
}

LRESULT MExportToChartDlg::OnLegendMouseUp(WPARAM wp, LPARAM lp)
{
	BCGPChartHitInfo* pt = (BCGPChartHitInfo*)lp;

	m_Chart.OnLegendMouseUp(pt->m_ptHit);
	//AfxMessageBox(_T("mouse up"));
	return 0;
}

BOOL MExportToChartDlg::Create()
{
	return CreateIndirect(m_lpDialogTemplate);
}

int MExportToChartDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
 	return 0;
}

BOOL MExportToChartDlg::OnInitDialog()
{
	if(!MDialog::OnInitDialog()) return FALSE;

	CString strChartTitle = _T("New Chart");
	CString strXTitle = _T("X");
	CString strYTitle = _T("Y");

	m_editTitle.SetWindowText(strChartTitle);
	m_Chart.SetChartTitle(strChartTitle);
	
	//테이블의 컬럼 이름 넣기
	const MTBSchemaBase* pSchema = m_pTable->GetSchema();
	for(int i = 0; i < pSchema->GetColumnCount(); i++)
	{
		const MTBColumn& Column = pSchema->GetColumn(i);
		CString strColName = Column.GetDisplayName();
		m_comboX.AddString(strColName);
		m_chklistY.AddString(strColName);
	}
	
	m_comboX.SetCurSel(0);
	m_comboX.GetLBText(m_comboX.GetCurSel(), strXTitle);
	m_editXTitle.SetWindowText(strXTitle);

	m_editYTitle.SetWindowText(strYTitle);

	m_editXPoint.SetWindowText(_T("4"));
	m_editYPoint.SetWindowText(_T("4"));

	m_chkVisibleMark.SetCheck(FALSE);
	m_chkVisibleMark.EnableWindow(FALSE);
	m_chkConsiderMinMax.SetCheck(FALSE);
	m_chkConsiderMinMax.EnableWindow(FALSE);
	m_btnNoConsiderMinMax.EnableWindow(FALSE);
	m_editXMin.SetWindowText(_T("0"));
	m_editXMin.EnableWindow(FALSE);
	m_editXMax.SetWindowText(_T("0"));
	m_editXMax.EnableWindow(FALSE);
	m_editXInterval.SetWindowText(_T("1"));
	m_editXInterval.EnableWindow(FALSE);
	m_editYMin.SetWindowText(_T("0"));
	m_editYMin.EnableWindow(FALSE);
	m_editYMax.SetWindowText(_T("0"));
	m_editYMax.EnableWindow(FALSE);
	m_editYInterval.SetWindowText(_T("1"));
	m_editYInterval.EnableWindow(FALSE);
	m_ColorPicker.EnableWindow(FALSE);
	m_editLineWidth.EnableWindow(FALSE);
	m_spinLineWidth.EnableWindow(FALSE);
	m_comboLineType.AddString(_T("Solid")); m_comboLineType.AddString(_T("Dash")); m_comboLineType.AddString(_T("Dot")); 
	m_comboLineType.AddString(_T("Dash Dot")); m_comboLineType.AddString(_T("Dash Dot Dot")); 
	m_comboLineType.EnableWindow(FALSE);	
	m_btnExportToImage.EnableWindow(FALSE);
	//m_btnExportToView.EnableWindow(FALSE);

	m_spinLineWidth.SetBuddy(&m_editLineWidth);
	m_spinLineWidth.SetRange(0,50);


	m_ColorPicker.EnableOtherButton(_T("Other"));
	m_ColorPicker.SetColor((COLORREF)-1);
	m_ColorPicker.SetColors(CBCGPColor::GetRGBArray());
	m_ColorPicker.SetColumnsNumber(10);

	m_nSelColIndex = -1;

	UpdateData(FALSE);
	return TRUE;
}

void MExportToChartDlg::OnBnClickedDrawChart()
{
	if(!CreateChart()) return;

	m_chkConsiderMinMax.EnableWindow(TRUE);
	//m_chkVisibleMark.EnableWindow(TRUE);

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChartCreated = TRUE;

	m_btnExportToImage.EnableWindow(TRUE);
	//m_btnExportToView.EnableWindow(TRUE);

	CalMinMaxInterval();
	OnBnClickedXExponent();
	OnBnClickedYExponent();
	OnBnClickedVisibleMark();
// 	m_dXMinOrigin = m_dXMinChanged = m_Chart.GetAxisMinValue(MChartCtrl::X_1);
// 	m_dXMaxOrigin = m_dXMaxChanged = m_Chart.GetAxisMaxValue(MChartCtrl::X_1);
// 	m_dXUnitOrigin = m_dXUnitChanged = m_Chart.GetAxisIntervalUnit(MChartCtrl::X_1);
// 
// 	m_dYMinOrigin = m_dYMinChanged = m_Chart.GetAxisMinValue(MChartCtrl::Y_1);
// 	m_dYMaxOrigin = m_dYMaxChanged = m_Chart.GetAxisMaxValue(MChartCtrl::Y_1);
// 	m_dYUnitOrigin = m_dYUnitChanged = m_Chart.GetAxisIntervalUnit(MChartCtrl::Y_1);
// 
// 	m_Chart.SetAxisRange(MChartCtrl::X_1, m_dXMinOrigin, m_dXMaxOrigin, m_dXUnitOrigin);
// 	m_Chart.SetAxisRange(MChartCtrl::Y_1, m_dYMinOrigin, m_dYMaxOrigin, m_dYUnitOrigin);
}

void MExportToChartDlg::OnBnClickedExportImage()
{
	if(!m_bChartCreated) return;

	m_Chart.SaveToImage(m_Chart.GetTitle());
}

void MExportToChartDlg::OnBnClickedExportView()
{
	if(!m_bChartCreated) return;

	//MChartManager::GetInstance()->ShowChartBar(32777, m_Chart.GetTitle(), RUNTIME_CLASS(MChartBar), NULL)
}

void MExportToChartDlg::OnChkChangeYList()
{
	int nSelIndex = m_chklistY.GetCurSel();
	const MTBSchemaBase* pSchema = m_pTable->GetSchema();
	const MTBColumn& SelColumn = pSchema->GetColumn(nSelIndex);


	if(m_chklistY.GetCheck(nSelIndex) == BST_CHECKED)
	{
		//m_vecSelColumn.push_back(&SelColumn);

		m_arSelCol.Add(nSelIndex);
	}
	else if(m_chklistY.GetCheck(nSelIndex) == BST_UNCHECKED)
	{
		int nIndex = 0;
// 		for(std::vector<const MTBColumn*>::iterator itr = m_vecSelColumn.begin(); itr != m_vecSelColumn.end(); nIndex++)
// 		{
// 			if((*itr)->GetDisplayName() == SelColumn.GetDisplayName())
// 			{
// 				itr = m_vecSelColumn.erase(itr);
// 				break;
// 			}
// 			else
// 			{
// 				++itr;
// 			}
// 		}
		for(nIndex = 0; nIndex < m_arSelCol.GetSize(); nIndex++)
		{
			if(m_arSelCol[nIndex] == nSelIndex)
				break;
		}
				
		m_arSelCol.RemoveAt(nIndex);
	}
}

void MExportToChartDlg::OnSelItemYList()
{
	if(!m_bChartCreated) return;

	int nSelIndex = m_chklistY.GetCurSel();
	const MTBSchemaBase* pSchema = m_pTable->GetSchema();
	const MTBColumn& SelColumn = pSchema->GetColumn(m_chklistY.GetCurSel());

	BOOL bFind = FALSE;
	int nIndex = 0;
	CString strSelColName = SelColumn.GetDisplayName();
	m_staticSelColName.SetWindowText(strSelColName);

// 	for(std::vector<const MTBColumn*>::iterator itr = m_vecSelColumn.begin(); itr != m_vecSelColumn.end(); itr++, nIndex++)
// 	{
// 		if((*itr)->GetDisplayName() == strSelColName)
// 		{
// 			bFind = TRUE;
// 			break;
// 		}
// 	}

	for(nIndex = 0; nIndex < m_arLastDrawedCol.GetSize(); nIndex++)
	{
		if(m_arLastDrawedCol[nIndex] == nSelIndex)
		{
			bFind = TRUE;
			break;
		}
	}

	if(!bFind) 
	{
		m_nSelColIndex = -1;
		m_ColorPicker.EnableWindow(FALSE);
		m_editLineWidth.EnableWindow(FALSE);
		m_spinLineWidth.EnableWindow(FALSE);
		m_comboLineType.EnableWindow(FALSE);
		m_chkVisibleMark.EnableWindow(FALSE);
		m_chkVisibleMark.SetCheck(BST_UNCHECKED);
		return;
	}

	BOOL bRightSelection = FALSE;
	if(nIndex < m_nLastDrawedSeriesNum)
	{
		m_nSelColIndex = nIndex;
		bRightSelection = TRUE;

		if(m_Chart.IsEnableMarker(m_nSelColIndex))
		{
			m_chkVisibleMark.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkVisibleMark.SetCheck(BST_UNCHECKED);
		}
	}
	else
	{
		m_nSelColIndex = -1;

		m_chkVisibleMark.SetCheck(BST_UNCHECKED);
	}

	m_ColorPicker.EnableWindow(bRightSelection);
	m_editLineWidth.EnableWindow(bRightSelection);
	m_spinLineWidth.EnableWindow(bRightSelection);
	m_comboLineType.EnableWindow(bRightSelection);
	m_chkVisibleMark.EnableWindow(bRightSelection);

	COLORREF rgbSelCol = m_Chart.GetSeriesColor(m_nSelColIndex);
	m_ColorPicker.SetColor(rgbSelCol);

	m_comboLineType.SetCurSel((int)(m_Chart.GetSeriesLineType(m_nSelColIndex)));

	CString strValue;
	strValue.Format(_T("%.2f"), m_Chart.GetSeriesLineWidth(m_nSelColIndex));
	m_editLineWidth.SetWindowText(strValue);
}

void MExportToChartDlg::OnComboChangeXList()
{
	const MTBSchemaBase* pSchema = m_pTable->GetSchema();
	const MTBColumn& SelColumn = pSchema->GetColumn(m_comboX.GetCurSel());
}

void MExportToChartDlg::OnComboChangeLineType()
{
	if(m_nSelColIndex == -1 || !m_bChartCreated) return;

	m_Chart.SetSeriesLineType(m_nSelColIndex, (MChartCtrl::DASH_STYLE)m_comboLineType.GetCurSel());

	m_Chart.Redraw();
}

void MExportToChartDlg::OnColorPickerClicked()
{
	if(m_nSelColIndex == -1 || !m_bChartCreated) return;

	COLORREF rgbSelCol = m_ColorPicker.GetColor();
	m_Chart.SetSeriesColor(m_nSelColIndex, rgbSelCol);

	m_Chart.Redraw();
}

void MExportToChartDlg::OnEditChangeChartTitle()
{
	CString strChartTitle;
	m_editTitle.GetWindowText(strChartTitle);
	
	m_Chart.SetTitle(strChartTitle);
	m_Chart.Redraw();
}

void MExportToChartDlg::OnEditChangeXTitle()
{
	if(!m_bChartCreated) return;

	CString strXTitle;
	m_editXTitle.GetWindowText(strXTitle);

	m_Chart.SetAxisTitle(MChartCtrl::X_1, strXTitle);
	m_Chart.Redraw();
}

void MExportToChartDlg::OnEditChangeYTitle()
{
	if(!m_bChartCreated) return;

	CString strYTitle;
	m_editYTitle.GetWindowText(strYTitle);

	m_Chart.SetAxisTitle(MChartCtrl::Y_1, strYTitle);
	m_Chart.Redraw();
}

void MExportToChartDlg::OnBnClickedXExponent()
{
	if(m_chkXPoint.GetCheck() == BST_CHECKED)
	{
		m_bXExponent = TRUE;
	}
	else if(m_chkXPoint.GetCheck() == BST_UNCHECKED)
	{
		m_bXExponent = FALSE;
	}

	OnEditChangeXPoint();
}

void MExportToChartDlg::OnBnClickedYExponent()
{
	if(m_chkYPoint.GetCheck() == BST_CHECKED)
	{
		m_bYExponent = TRUE;
	}
	else if(m_chkYPoint.GetCheck() == BST_UNCHECKED)
	{
		m_bYExponent = FALSE;
	}

	OnEditChangeYPoint();
}

void MExportToChartDlg::OnBnClickedAxisChange()
{
	if(!m_bChartCreated) return;

	m_Chart.SwapAllAxisDirection();
	m_Chart.SetDirty();
	m_Chart.Redraw();
}

void MExportToChartDlg::OnBnClickedShowSummary()
{
	if(m_chkSummary.GetCheck() == BST_CHECKED)
	{
		m_Chart.ShowSummary(TRUE);
	}
	else if(m_chkSummary.GetCheck() == BST_UNCHECKED)
	{
		m_Chart.ShowSummary(FALSE);
	}

	m_Chart.Redraw();
}

void MExportToChartDlg::OnBnClickedVisibleMark()
{
	if(!m_bChartCreated) return;

	if(m_chkVisibleMark.GetCheck() == BST_CHECKED)
	{
		//m_Chart.EnableMarkerAll(TRUE);
		m_Chart.EnableMarker(TRUE, m_nSelColIndex);
	}
	else if(m_chkVisibleMark.GetCheck() == BST_UNCHECKED)
	{
		m_Chart.EnableMarker(FALSE, m_nSelColIndex);
		//m_Chart.EnableMarkerAll(FALSE);
	}
	m_Chart.SetDirty();
	m_Chart.Redraw();
}

void MExportToChartDlg::OnBnClickedConsiderMinMax()
{
	if(!m_bChartCreated) return;

	if(m_chkConsiderMinMax.GetCheck() == BST_CHECKED)
	{
		m_btnNoConsiderMinMax.EnableWindow(TRUE);

		if(!m_bIsStrVal_X)
		{
			m_editXMin.EnableWindow(TRUE); m_editXMax.EnableWindow(TRUE); m_editXInterval.EnableWindow(TRUE);
		}

		m_editYMin.EnableWindow(TRUE); m_editYMax.EnableWindow(TRUE); m_editYInterval.EnableWindow(TRUE);

		//각각 민맥스 인터벌 이런거 가져와서 세팅!
		if(!m_bChangedMinMax)
		{
			CString strValue;

			if(!m_bIsStrVal_X)
			{
				strValue.Format(_T("%.4f"), m_dXMinOrigin); m_editXMin.SetWindowText(strValue);
				strValue.Format(_T("%.4f"), m_dXMaxOrigin); m_editXMax.SetWindowText(strValue);
				strValue.Format(_T("%.4f"), /*m_dXMaxOrigin/*/m_dXUnitOrigin); m_editXInterval.SetWindowText(strValue);
			}

			strValue.Format(_T("%.4f"), m_dYMinOrigin); m_editYMin.SetWindowText(strValue);
			strValue.Format(_T("%.4f"), m_dYMaxOrigin); m_editYMax.SetWindowText(strValue);
			strValue.Format(_T("%.4f"), /*m_dYMaxOrigin/*/m_dYUnitOrigin); m_editYInterval.SetWindowText(strValue);
		}
		else
		{
			CString strValue;

			if(!m_bIsStrVal_X)
			{
				strValue.Format(_T("%.4f"), m_dXMinChanged); m_editXMin.SetWindowText(strValue);
				strValue.Format(_T("%.4f"), m_dXMaxChanged); m_editXMax.SetWindowText(strValue);
				strValue.Format(_T("%.4f"), /*m_dXMaxChanged/*/m_dXUnitChanged); m_editXInterval.SetWindowText(strValue);

				m_Chart.SetAxisRange(MChartCtrl::X_1, m_dXMinChanged, m_dXMaxChanged, m_dXUnitChanged);
			}

			strValue.Format(_T("%.4f"), m_dYMinChanged); m_editYMin.SetWindowText(strValue);
			strValue.Format(_T("%.4f"), m_dYMaxChanged); m_editYMax.SetWindowText(strValue);
			strValue.Format(_T("%.4f"), /*m_dYMaxChanged/*/m_dYUnitChanged); m_editYInterval.SetWindowText(strValue);
			
			m_Chart.SetAxisRange(MChartCtrl::Y_1, m_dYMinChanged, m_dYMaxChanged, m_dYUnitChanged);

			m_Chart.SetDirty();
			m_Chart.Redraw();
		}
	}
	else if(m_chkConsiderMinMax.GetCheck() == BST_UNCHECKED)
	{
		m_btnNoConsiderMinMax.EnableWindow(FALSE);

		if(!m_bIsStrVal_X)
		{
			m_editXMin.EnableWindow(FALSE); m_editXMax.EnableWindow(FALSE); m_editXInterval.EnableWindow(FALSE);
		
			m_Chart.SetAxisRange(MChartCtrl::X_1, m_dXMinOrigin, m_dXMaxOrigin, m_dXUnitOrigin);
		}

		m_editYMin.EnableWindow(FALSE); m_editYMax.EnableWindow(FALSE); m_editYInterval.EnableWindow(FALSE);
		
		m_Chart.SetAxisRange(MChartCtrl::Y_1, m_dYMinOrigin, m_dYMaxOrigin, m_dYUnitOrigin);

		m_Chart.SetDirty();
		m_Chart.Redraw();
	}
}

void MExportToChartDlg::OnEditChangeXRangeMin()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editXMin.GetWindowText(strValue);
	
	m_Chart.SetAxisMinValue(MChartCtrl::X_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dXMinChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeXRangeMax()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editXMax.GetWindowText(strValue);

	m_Chart.SetAxisMaxValue(MChartCtrl::X_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dXMaxChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeXInterval()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editXInterval.GetWindowText(strValue);

	m_Chart.SetAxisUnit(MChartCtrl::X_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dXUnitChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeYRangeMin()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editYMin.GetWindowText(strValue);

	m_Chart.SetAxisMinValue(MChartCtrl::Y_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dYMinChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeYRangeMax()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editYMax.GetWindowText(strValue);

	m_Chart.SetAxisMaxValue(MChartCtrl::Y_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dYMaxChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeYInterval()
{
	if(!m_bChartCreated) return;

	CString strValue;
	m_editYInterval.GetWindowText(strValue);

	m_Chart.SetAxisUnit(MChartCtrl::Y_1, _ttof(strValue));

	m_Chart.SetDirty();
	m_Chart.Redraw();

	m_bChangedMinMax = TRUE;
	m_dYUnitChanged = _ttof(strValue);
}

void MExportToChartDlg::OnEditChangeXPoint()
{
	if(!m_bChartCreated) return;

	if(m_bIsStrVal_X) return;

	CString strValue, strFormat;
	m_editXPoint.GetWindowText(strValue);

	if(_ttoi(strValue) > 5) return;

	if(m_bXExponent)
		strFormat.Format(_T("%%.")+strValue+_T("le"));
	else
		strFormat.Format(_T("%%.")+strValue+_T("f"));

	m_Chart.SetAxisDataFormat(MChartCtrl::X_1, strFormat);

	m_Chart.SetDirty();
	m_Chart.Redraw();
}

void MExportToChartDlg::OnEditChangeYPoint()
{
	if(!m_bChartCreated) return;

	CString strValue, strFormat;
	m_editYPoint.GetWindowText(strValue);

	if(_ttoi(strValue) > 5) return;

	if(m_bYExponent)
		strFormat.Format(_T("%%.")+strValue+_T("le"));
	else
		strFormat.Format(_T("%%.")+strValue+_T("f"));

	m_Chart.SetAxisDataFormat(MChartCtrl::Y_1, strFormat);

	m_Chart.SetDirty();
	m_Chart.Redraw();
}

void MExportToChartDlg::OnDeltaposSpinLdSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(!m_bChartCreated) return;

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	double m_nDur = 0;
	CString get_value, set_value;
	//GetDlgItemTextA(IDC_EXPTOCHART_EDIT_LINEWIDTH,get_value);
	m_editLineWidth.GetWindowText(get_value);
	UpdateData(TRUE);
	m_nDur = _ttof(get_value);
	if(pNMUpDown->iDelta>0) // Click Up button
	{    
		m_nDur += 0.25;
		if(m_nDur > 50)
		{
			m_nDur = 4.0f;
		}
	}
	else                    // Click Down button
	{
		m_nDur -= 0.25;
		if(m_nDur < 0)
		{
			m_nDur = 0.0f;
		}
	}

	if(m_nSelColIndex == -1 || !m_bChartCreated) return;

	m_Chart.SetSeriesLineWidth(m_nSelColIndex, m_nDur);
	m_Chart.Redraw();

	set_value.Format(_T("%.2f"),m_nDur);
	//SetDlgItemText(IDC_EDIT_IPROG_VALUE,set_value);
	m_editLineWidth.SetWindowText(set_value);
	UpdateData(FALSE);

	*pResult = 0;
}

void MExportToChartDlg::OnBnclickedFullZoom()
{
	//민맥스값찾아서 각 축의 최대최소값바꾸자
	double dYMin = m_Chart.GetMinValueOfChart(MChartCtrl::Y_1);
	double dYMax = m_Chart.GetMaxValueOfChart(MChartCtrl::Y_1);
	double dXMin = m_Chart.GetMinValueOfChart(MChartCtrl::X_1);
	double dXMax = m_Chart.GetMaxValueOfChart(MChartCtrl::X_1);

	if(!m_bChangedMinMax)
	{
		if(!m_bIsStrVal_X)
		{
			m_Chart.SetAxisRange(MChartCtrl::X_1, dXMin, dXMax, m_dXUnitOrigin);
		}
		m_Chart.SetAxisRange(MChartCtrl::Y_1, dYMin, dYMax, m_dYUnitOrigin);
	}
	else
	{
		if(!m_bIsStrVal_X)
		{
			m_Chart.SetAxisRange(MChartCtrl::X_1, dXMin, dXMax, m_dXUnitChanged);
		}
		m_Chart.SetAxisRange(MChartCtrl::Y_1, dYMin, dYMax, m_dYUnitChanged);
	}

	CString strValue;
	if(!m_bIsStrVal_X)
	{
		strValue.Format(_T("%.4f"), dXMin);	m_editXMin.SetWindowText(strValue);
		strValue.Format(_T("%.4f"), dXMax);	m_editXMax.SetWindowText(strValue);
	}
	strValue.Format(_T("%.4f"), dYMin);	m_editYMin.SetWindowText(strValue);
	strValue.Format(_T("%.4f"), dYMax);	m_editYMax.SetWindowText(strValue);

	m_Chart.SetDirty();
	m_Chart.Redraw();
}

BOOL MExportToChartDlg::CreateChart()
{
	m_Chart.RemoveDataAll();
	//m_Chart.RemoveLegendAll();

	CString strChartTitle;
	CString strXTitle, strYTitle;
	CString strSeriesName;

	m_editTitle.GetWindowText(strChartTitle);
	m_Chart.SetChartTitle(strChartTitle);
	
	m_editXTitle.GetWindowText(strXTitle);
	m_editYTitle.GetWindowText(strYTitle);

	m_Chart.SetAxisTitle(MChartCtrl::X_1, strXTitle);
	m_Chart.SetAxisTitle(MChartCtrl::Y_1, strYTitle);

	m_Chart.EnableMarkerAll(FALSE);

	const MTBSchemaBase* pSchema = m_pTable->GetSchema();
	ITableDB* pDb = m_pTable->GetTableDB();
	int nRowNum = pDb->GetRowCount();
	int nColX = m_comboX.GetCurSel();
	const MTBColumn& colXAxis = pSchema->GetColumn(m_comboX.GetCurSel());

	m_nLastDrawedSeriesNum = (int)m_arSelCol.GetSize();
	for(int i = 0; i < m_arSelCol.GetSize(); i++)
	{
		const MTBColumn& colY = pSchema->GetColumn(m_arSelCol[i]);
		//type check
		if(colY.GetType() == MTBColumn::TB_NONE
// 			|| colY.GetType() == MTBColumn::TB_KEY
// 			|| colY.GetType() == MTBColumn::TB_FOREIGN
// 			|| colY.GetType() == MTBColumn::TB_MKey
			|| colY.GetType() == MTBColumn::TB_BOOL 
			|| colY.GetType() == MTBColumn::TB_bool)
		{
			//key, mkey 도 이래야하는가??
			AfxMessageBox(_T("Y축으로 그릴 수 있는 형식이 아닙니다."));
			return FALSE;
		}
		else if(colY.GetType() == MTBColumn::TB_CArray)
		{
			//어레이를 어쩌지!!!!!!!!!!!!!!!
		}
		else
		{
			strSeriesName = colY.GetDisplayName();
			m_Chart.SetSeriesName(strSeriesName, i);

			for(int j = 0; j < nRowNum; j++)
			{
				_variant_t valueX, valueY;

				pDb->GetItem(valueX, j, nColX);
				pDb->GetItem(valueY, j, m_arSelCol[i]);

				if(valueY.vt == VT_BSTR)
				{
					AfxMessageBox(_T("Y축 값은 문자열이 될 수 없습니다."));
					return FALSE;
				}

				if(valueX.vt == VT_BSTR)
				{
					if(!m_bIsStrVal_X) m_bIsStrVal_X = TRUE;
					m_Chart.AddData(i, (CString)valueX, (double)valueY);
				}
				else if(valueX.vt == VT_I2 || valueX.vt == VT_I4 || valueX.vt == VT_R4 || valueX.vt == VT_R8)
				{
					if(m_bIsStrVal_X) m_bIsStrVal_X = FALSE;
					m_Chart.AddData(i, (double)valueX, (double)valueY);
				}
			}
		}
	}

	m_arLastDrawedCol.RemoveAll();
	m_arLastDrawedCol.Copy(m_arSelCol);

	if(!m_bIsStrVal_X)
	{
		m_editXPoint.EnableWindow(TRUE);
		m_chkXPoint.EnableWindow(TRUE);
	}
	else
	{
		m_editXPoint.EnableWindow(FALSE);
		m_chkXPoint.EnableWindow(FALSE);
	}
// 	m_Chart.SetLogScale(TRUE, 10, MChartCtrl::X_1);
// 	m_Chart.SetLogScale(TRUE, 10, MChartCtrl::Y_1);
	//CalMinMaxInterval();
	return TRUE;
}

void MExportToChartDlg::CalMinMaxInterval()
{
	m_dXMinOrigin = m_dXMinChanged = m_Chart.GetAxisMinValue(MChartCtrl::X_1);
	m_dXMaxOrigin = m_dXMaxChanged = m_Chart.GetAxisMaxValue(MChartCtrl::X_1);
	m_dXUnitOrigin = m_dXUnitChanged = m_Chart.GetAxisIntervalUnit(MChartCtrl::X_1);

	m_dYMinOrigin = m_dYMinChanged = m_Chart.GetAxisMinValue(MChartCtrl::Y_1);
	m_dYMaxOrigin = m_dYMaxChanged = m_Chart.GetAxisMaxValue(MChartCtrl::Y_1);
	m_dYUnitOrigin = m_dYUnitChanged = m_Chart.GetAxisIntervalUnit(MChartCtrl::Y_1);

	m_Chart.SetAxisRange(MChartCtrl::X_1, m_dXMinOrigin, m_dXMaxOrigin, m_dXUnitOrigin);
	m_Chart.SetAxisRange(MChartCtrl::Y_1, m_dYMinOrigin, m_dYMaxOrigin, m_dYUnitOrigin);
}