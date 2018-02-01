#pragma once

#include "HeaderPre.h"

namespace mit
{
	namespace frx
	{
		class __MY_EXT_CLASS__ MChartVisualObject : public CBCGPChartVisualObject
		{
			DECLARE_DYNCREATE(MChartVisualObject)		
		public:
			MChartVisualObject();
			virtual ~MChartVisualObject();

		public:
			void RemoveSeriesData(int nSeriesIndex);
			void UpDownHitTest(CBCGPPoint ptHit, BOOL bUpDown);
			void SetLegendType(BOOL bBigLegend) { m_bBigLegend = bBigLegend; }
			BOOL GetLegendType() { return m_bBigLegend; }
			void ShowSummary(BOOL bShow) { m_bShowSummary = bShow; }

		public:
			virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip, DWORD dwFlags = BCGP_DRAW_STATIC | BCGP_DRAW_DYNAMIC );
			virtual void OnDrawChartLegend(CBCGPGraphicsManager* pGM, CBCGPRect& rectLegend, BCGPChartFormatArea& legendStyle);
			virtual void OnDrawLegendEntry(CBCGPGraphicsManager* pGM, const CRect& rectLegend, 
				CBCGPChartSeries* pSeries, CBCGPChartDataPoint* pDataPoint, int nDataPointIndex);
			void OnDrawLegendScrollArrow(CBCGPGraphicsManager* pGM, CBCGPRect& rectLegend, BCGPChartFormatArea& legendStyle);
			virtual void OnDrawChartArea (CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea);
			virtual void OnDrawEmptyStatus ( CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea );
			virtual void OnDrawAxisLabel(CBCGPGraphicsManager* pGM, double dblCurrValue, CString& strLabel, CBCGPChartAxis* pAxis, 
				const CBCGPRect& rectLabel, const CBCGPRect& rectLabels, const CBCGPRect& rectDiagram);

			virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt);

		private:
			void ReposBigLegendEntry(BOOL bUpDown);

		protected:
			BOOL m_bBigLegend;
			BOOL m_bShowSummary;
			CBCGPRect m_rectLegend;
			CBCGPRect m_rectUpperBound;
			CBCGPRect m_rectLowerBound;
		};
	}
}

#include "HeaderPost.h"