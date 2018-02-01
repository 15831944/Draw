#pragma once

#include "MIT_frx.h"

#include "MDialog.h"
#include "MTable.h"
#include "MChartCtrl.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		
// 		struct __MY_EXT_CLASS__ MMYDLGTEMPLATE : public DLGTEMPLATE
// 		{
// 			WORD menu;
// 			WORD windowClass;
// 			WCHAR wszTitle[1];
// 		};

		class __MY_EXT_CLASS__ MExportToChartDlg : public mit::frx::MDialog
		{
			DECLARE_DYNCREATE(MExportToChartDlg)

		public:
			MExportToChartDlg();
			MExportToChartDlg(MTable* pTable);
			virtual ~MExportToChartDlg();

			virtual BOOL Create();

			enum { IDD = IDD_EXPORT_TO_CHART_DLG };

		private:
			MChartCtrl m_Chart;
			CBCGPEdit m_editTitle;
			CBCGPEdit m_editXTitle;
			CBCGPEdit m_editYTitle;
			CBCGPEdit m_editXPoint;
			CBCGPEdit m_editYPoint;
			CBCGPEdit m_editXMin;
			CBCGPEdit m_editYMin;
			CBCGPEdit m_editXMax;
			CBCGPEdit m_editYMax;
			CBCGPEdit m_editXInterval;
			CBCGPEdit m_editYInterval;
			CBCGPEdit m_editLineWidth; //
			CBCGPButton m_chkXPoint;
			CBCGPButton m_chkYPoint;
			CBCGPButton m_chkAxisChange;
			CBCGPButton m_chkSummary;
			CBCGPButton m_chkConsiderMinMax;
			CBCGPButton m_chkVisibleMark;
			CBCGPButton m_btnExportToImage;
			CBCGPButton m_btnExportToView; //
			CBCGPButton m_btnDrawChart;
			CBCGPButton m_btnNoConsiderMinMax;
			CCheckListBox m_chklistY;
			CBCGPComboBox m_comboX;
			CBCGPComboBox m_comboLineType;
			CBCGPSpinButtonCtrl m_spinLineWidth; //
			CBCGPColorButton m_ColorPicker;
			CStatic m_staticSelColName;

//			MMYDLGTEMPLATE m_dlgTemplate;
			
			MTable* m_pTable;
			//std::vector<const MTBColumn*> m_vecSelColumn;
			CArray<int, int> m_arSelCol;
			CArray<int, int> m_arLastDrawedCol;

			BOOL m_bChartCreated;
			BOOL m_bChangedMinMax;
			BOOL m_bXExponent;
			BOOL m_bYExponent;
//			BOOL m_bAxisChange;
			BOOL m_bIsStrVal_X;

			int m_nSelColIndex;
			int m_nLastDrawedSeriesNum;

			double m_dXMinOrigin;
			double m_dXMaxOrigin;
			double m_dXUnitOrigin;
			double m_dYMinOrigin;
			double m_dYMaxOrigin;
			double m_dYUnitOrigin;

			double m_dXMinChanged;
			double m_dXMaxChanged;
			double m_dXUnitChanged;
			double m_dYMinChanged;
			double m_dYMaxChanged;
			double m_dYUnitChanged;

			double m_dMinForFit;
			double m_dMaxForFit;

		protected:
			BOOL CreateChart();
			void CalMinMaxInterval();

		protected:
			void OnBnClickedDrawChart();
			void OnBnClickedExportImage();
			void OnBnClickedExportView();
			void OnChkChangeYList();
			void OnSelItemYList();
			void OnComboChangeXList();
			void OnComboChangeLineType();
			void OnColorPickerClicked();
			void OnEditChangeChartTitle();
			void OnEditChangeXTitle();
			void OnEditChangeYTitle();
			void OnBnClickedXExponent();
			void OnBnClickedYExponent();
			void OnBnClickedAxisChange();
			void OnBnClickedShowSummary();
			void OnBnClickedVisibleMark();
			void OnBnClickedConsiderMinMax();
 			void OnEditChangeXRangeMin();
 			void OnEditChangeXRangeMax();
 			void OnEditChangeXInterval();
			void OnEditChangeYRangeMin();
			void OnEditChangeYRangeMax();
 			void OnEditChangeYInterval();
			void OnEditChangeXPoint();
			void OnEditChangeYPoint();
			void OnDeltaposSpinLdSet(NMHDR *pNMHDR, LRESULT *pResult);
			void OnBnclickedFullZoom();

		protected:
			virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
			virtual BOOL OnInitDialog();
			
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg LRESULT OnLegendMouseDown(WPARAM wp, LPARAM lp);
			afx_msg LRESULT OnLegendMouseUp(WPARAM wp, LPARAM lp);
			
			DECLARE_MESSAGE_MAP()
		};

// 		class SelectExportMethodDlg : public mit::frx::MDialog
// 		{
// 			DECLARE_DYNCREATE(SelectExportMethodDlg)
// 
// 		public:
// 			SelectExportMethodDlg();
// 			virtual ~SelectExportMethodDlg();
// 
// 		private:
// 			enum 
// 			{
// 				IDC_EXPMETHOD_BTN_IMAGE = 1,
// 				IDC_EXPMETHOD_BTN_VIEW,
// 
// 				IDC_EXPMETHOD_STATIC_STRING,
// 			};
// 
// 			CBCGPButton m_btnImage;
// 			CBCGPButton m_btnView;
// 			CStatic m_staticString;
// 
// 			MMYDLGTEMPLATE m_dlgTemplate;
// 
// 		protected:
// 			void OnBnClickedImage();
// 			void OnBnClickedView();
// 		};
	}
}

#include "HeaderPost.h"