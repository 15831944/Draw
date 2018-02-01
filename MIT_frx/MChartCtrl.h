#pragma once

#include "MChartVisualObject.h"
//#include "MChartSummaryWnd.h"

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
// 		class __MY_EXT_CLASS__ MLegendVisualObject : public CBCGPChartLegendVisualObject
// 		{
// 			DECLARE_DYNCREATE(MLegendVisualObject)
// 		public:
// 			MLegendVisualObject(CBCGPVisualContainer* pContainer = NULL);
// 			virtual ~MLegendVisualObject();
// 
// 		public:
// 			virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip, DWORD dwFlags = BCGP_DRAW_STATIC | BCGP_DRAW_DYNAMIC );
// 		};

		class __MY_EXT_CLASS__ MChartCtrl : public CBCGPChartCtrl
		{
			DECLARE_DYNAMIC(MChartCtrl)
		public:
			enum CHART_CATEGORY
			{
				cDEFAULT,
				cLINE,
				cCOLUMN,
				cBAR,
				cLARGEDATA,
			};

			enum CHART_TYPE
			{
				tDEFAULT,
				tSIMPLE,
				tSTACKED,
				t100STACKED,
				tRANGE
			};

			enum LEGEND_POSITION
			{
				lpNONE,
				lpTOP,
				lpBOTTOM,
				lpLEFT,
				lpRIGHT,
				lpTOPRIGHT
			};

			enum TITLE_ALIGN
			{
				LEADING,
				TRAILING,
				CENTER
			};

			enum AXIS
			{
				X_1,
				Y_1,
				X_2,
				Y_2
			};

			enum DASH_STYLE
			{
				dsSOLID,
				dsDASH,
				dsDOT,
				dsDASH_DOT,
				dsDASH_DOT_DOT
			};

			enum BREAK_STYLE
			{
				bsCONTINUOUS,
				bsEMPTY,
				bsLINE,
				bsBOX,
				bsWAVE,
				bsSAWTOOTH
			};

		public:
			MChartCtrl();
			virtual ~MChartCtrl();

		public:
			virtual CBCGPChartVisualObject* GetChart()
			{
				if (m_pChart == NULL)
				{
					m_pChart = new MChartVisualObject();
				}

				return m_pChart;
			}

			virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip);
			virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt);

		public:
			void SetChart(CHART_CATEGORY category, CHART_TYPE type = tSIMPLE, BOOL bRedraw = TRUE, BOOL bResetAxesDisplayRange = TRUE);
			//void SetChartDataLabelDataFormat(CString strFormat);

			void AddData(int nSeriesIndex, double dXValue, double dYValue);
			void AddData(int nSeriesIndex, CString strXValue, double dYValue);
			void AddData(int nSeriesIndex, CString dXValue, CString dYValue);

			void RemoveData(int nSeriesIndex);
			void RemoveDataAll();
			void RemoveLegendAll();

			void ShowSummary(BOOL bShowSummary);

			BOOL IsEnableMarker(int nSeriesIndex);
			void EnableMarker(BOOL bEnable = TRUE, int nSeriesIndes = -1);
			void EnableMarkerAll(BOOL bEnable = TRUE);

			void SetTitle(CString strTitle = _T(""), BOOL bVisible = TRUE);
			CString GetTitle();
			void SetChartTitle(LPCTSTR lpcszText, BCGPChartFormatLabel* pTitleFormat = NULL, BOOL bAdjustLayout = FALSE);
			void ShowChartTitle(BOOL bShow = TRUE, BOOL bTitleOverlapsChart = FALSE, BOOL bRedraw = FALSE);
			void SetTitleColor(COLORREF rgbTitle);
			void SetTitleAlign(TITLE_ALIGN align, TITLE_ALIGN verticalAlign);
			void SetTitleSize(float fFontSize);
			double GetMinValueOfChart(AXIS axisType = AXIS::Y_1);
			double GetMaxValueOfChart(AXIS axisType = AXIS::Y_1);

			void AxisVisible(AXIS axisType, BOOL bVisible = TRUE);
			void SetSecondaryAxis(BOOL bSecondaryX, BOOL bSecondaryY, int nSeriesIndex = 1);
			void SetAxisTitle(AXIS axisType, LPCTSTR strAxisTitle);
			void ShowAxisTitle(AXIS axisType, BOOL bVisible = TRUE);
			void SetAxisTitleColor(AXIS axisType, COLORREF rgbTitle);
			void SetAxisTitleSize(AXIS axisType, float fFontSize);
			void SetAxisLabelAngle(AXIS axisType, double dAngle);
			void SetAxisAutoDisplayRange(AXIS axisType);
			void SetAxisRange(AXIS axisType, double dMin, double dMax, double dUnit = 0.0);
			void SetAxisMinValue(AXIS axisType, double dMin);
			void SetAxisMaxValue(AXIS axisType, double dMax);
			void SetAxisUnit(AXIS axisType, double dUnit);
			void SetAxisInterval(AXIS axisType, double dInterval);
			void SetAxisDataFormat(AXIS axisType, CString strFormat);
			int GetAxisDirection(AXIS axisType);
			void SwapAxisDirection(AXIS axisType);
			void SwapAllAxisDirection();
			
			double GetAxisMinValue(AXIS axisType);
			double GetAxisMaxValue(AXIS axisType);
			double GetAxisIntervalUnit(AXIS axisType);

			void SetSeriesName(LPCTSTR strSeriesName, int nSeriesIndex = 0);
			void SetSeriesColor(int nSeriesIndex, COLORREF rgbColor);
			CBCGPColor GetSeriesColor(int nSeriesIndex = 0);
			void SetSeriesLineType(int nSeriesIndex, DASH_STYLE dashStyle);
			MChartCtrl::DASH_STYLE GetSeriesLineType(int nSeriesIndex);
			void SetSeriesLineWidth(int nSeriesIndex, double dLineWidth);
			double GetSeriesLineWidth(int nSeriesIndex);

			void AddExtraLine(double dValue, BOOL bHorz = TRUE, COLORREF color = 0, double dWidth = 2, DASH_STYLE dashStyle = DASH_STYLE::dsSOLID);

			void AddScaleBreak(double dStart, double dEnd, BREAK_STYLE breakeStyle = BREAK_STYLE::bsWAVE, int nGap = 7, AXIS axisType = AXIS::Y_1, double dOffSetPercent = 50);

			void SetLogScale(BOOL bSet, double dLogBase, AXIS axisType = AXIS::Y_1);

			void SetLegendPosition(LEGEND_POSITION legendPosition, BOOL bLegendOverlapsChart = FALSE, BOOL bRedraw = FALSE);

			void SetDirty(BOOL bSet = TRUE, BOOL bRedraw = FALSE);

			int SaveToImage(CString strChartName);

			void ResetAxis();

			void Redraw();

			void OnLegendMouseDown(CBCGPPoint ptHit);
			void OnLegendMouseUp(CBCGPPoint ptHit);

			void LegendHitTest(CBCGPPoint ptHit);

			double Rand(double s, double f);

		protected:
			enum 
			{
				ID_CHT_TABBED_DOCUMENT = 1,
				ID_CHT_EXPORT_TO_IMAGE,
				ID_CHT_SUMMARY_WINDOW,
				NEXT_ID_CHT
			};
			CBCGPDockingControlBar* GetParentBar() const;
			BOOL IsMDITabbed() const;
			virtual void MakeContextMenu(CMenu& menu);

		protected:
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnTabbedDocument();
			afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
			afx_msg void OnExportToImage();

			
			//Zoom
// 				afx_msg LRESULT OnAfterDraw(WPARAM wp, LPARAM lp);
// 				afx_msg LRESULT OnAfterRecalcLayout(WPARAM wp, LPARAM lp); 
			DECLARE_MESSAGE_MAP()

		protected:
			//MChartSummaryWnd m_SumWnd;
		};
	}
}

#include "HeaderPost.h"