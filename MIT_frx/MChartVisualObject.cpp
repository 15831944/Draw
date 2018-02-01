#include "stdafx.h"

#include "MVisualManager.h"
#include "MChartVisualObject.h"

using namespace mit::frx;

IMPLEMENT_DYNCREATE(MChartVisualObject, CBCGPChartVisualObject)

MChartVisualObject::MChartVisualObject() :
	CBCGPChartVisualObject(NULL)
{
	m_bBigLegend = FALSE;
	m_bShowSummary = FALSE;
}

MChartVisualObject::~MChartVisualObject()
{

}

void MChartVisualObject::RemoveSeriesData(int nSeriesIndex)
{
	if(m_arData.GetSize() < 1) return;
	m_arData.RemoveAt(nSeriesIndex);
}

void MChartVisualObject::OnDraw(CBCGPGraphicsManager* pGMSrc, const CBCGPRect& rectClip, DWORD dwFlags /* = BCGP_DRAW_STATIC | BCGP_DRAW_DYNAMIC */ )
{
	ASSERT_VALID(this);
	ASSERT_VALID(pGMSrc);

	if ((dwFlags & BCGP_DRAW_STATIC) == 0)
	{
		if (m_pWndOwner != NULL && m_pWndOwner->GetOwner()->GetSafeHwnd() != NULL)
		{
			WPARAM wParam = MAKEWPARAM(GetID(), dwFlags);
			m_pWndOwner->GetOwner()->SendMessage(BCGM_ON_CHART_AFTER_DRAW, wParam, (LPARAM)(LPVOID)pGMSrc);
		}
		return;
	}

	BOOL bCacheImage = m_bCacheImage;

	if (pGMSrc->IsOffscreen())
	{
		bCacheImage = FALSE;
	}

	CBCGPGraphicsManager* pGM = pGMSrc;
	CBCGPGraphicsManager* pGMMem = NULL;

	CBCGPRect rectSaved;

	if (bCacheImage)
	{	
		if (m_ImageCache.GetHandle() == NULL)
		{
			SetDirty();
		}

		if (m_ImageCache.GetHandle() != NULL && !IsDirty() && (dwFlags & BCGP_DRAW_STATIC))
		{
			pGMSrc->DrawImage(m_ImageCache, m_rect.TopLeft());
			dwFlags &= ~BCGP_DRAW_STATIC;

			if (dwFlags == 0)
			{
				return;
			}
		}

		if (dwFlags & BCGP_DRAW_STATIC)
		{
			pGMMem = pGM->CreateOffScreenManager(m_rect, &m_ImageCache);

			if (pGMMem != NULL)
			{
				pGM = pGMMem;

				rectSaved = m_rect;
				m_rect = m_rect - m_rect.TopLeft();
			}
		}
	}

	BOOL bWasDirty = IsDirty();
	if (bWasDirty)
	{
		ArrangeStackedSeries();
		InvalidateTrendFormulaSeries();
		if(!m_bBigLegend)
		AdjustLayout(pGM);
	}

	if (CalcScreenPositions(pGM, bWasDirty))
	{
		SetDirty(TRUE);
		AdjustLayout(pGM);
		CalcScreenPositions(pGM, TRUE);
	}

	CBCGPColor clrClear = m_plotAreaFormat.m_brFillColor.GetColor();

	if (clrClear.IsNull())
	{
		clrClear = m_currentTheme.m_brPlotFillColor.GetColor();
	}

	CBCGPChartDiagram3D* pDiagram3D = GetDiagram3D();

	if (pDiagram3D == NULL)
	{
		TRACE0("3D diagram manager is NULL.\n");
		return;
	}

	CBCGPEngine3D* pEngine3D = pDiagram3D->GetEngine3D();

	if (pEngine3D == NULL)
	{
		TRACE0("3D Graphics engine is NULL.\n");
		return;
	}

	ASSERT_VALID(pEngine3D);

	pEngine3D->SetClearColor(clrClear);
	pDiagram3D->OnBegin3DDraw(pGM);

	BOOL bPrevAA = pEngine3D->EnableAntialiasing(m_bAAEnabled);

	OnFillBackground (pGM);

	CBCGPRect rectPlotArea;
	OnGetPlotAreaRect(rectPlotArea);

	OnDrawChartArea(pGM, m_rect);

	if (m_rectDiagramArea.Width() > 2 && m_rectDiagramArea.Height() > 2)
	{
		OnDrawPlotArea(pGM, rectPlotArea, m_rectDiagramArea);

		if (pGM->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI && !m_bIsThumbnailMode)
		{
			OnDrawSelection(pGM);
		}

		OnDrawPlotAreaItems(pGM, rectPlotArea, m_rectDiagramArea);	
	}

	if (!m_bIsThumbnailMode)
	{
		CBCGPRect rectChartTitle;
		OnGetTitleAreaRect(rectChartTitle);
		OnDrawChartTitle(pGM, m_strChartTitle, rectChartTitle, m_titleAreaFormat);

		CBCGPRect rectLegend = m_rectLegendArea;

		OnDrawChartLegend(pGM, rectLegend, m_legendAreaFormat);
		OnDrawChartObjects(pGM, TRUE);

		if (pGM->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_D2D)
		{
			OnDrawSelection(pGM);
		}
	}

	if (pGMMem != NULL)
	{
		delete pGMMem;
		pGM = pGMSrc;

		m_rect = rectSaved;

		pGMSrc->DrawImage(m_ImageCache, m_rect.TopLeft());
	}

	if ((dwFlags & BCGP_DRAW_DYNAMIC) == BCGP_DRAW_DYNAMIC)
	{
		if (m_pWndOwner != NULL && m_pWndOwner->GetOwner()->GetSafeHwnd() != NULL)
		{
			WPARAM wParam = MAKEWPARAM(GetID(), dwFlags);
			m_pWndOwner->GetOwner()->SendMessage(BCGM_ON_CHART_AFTER_DRAW, wParam, (LPARAM)(LPVOID)pGM);
		}
	}

	pEngine3D->EnableAntialiasing(bPrevAA);
}

void MChartVisualObject::OnDrawChartLegend(CBCGPGraphicsManager* pGM, CBCGPRect& rectLegend, BCGPChartFormatArea& legendStyle)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pGM);



	if (rectLegend.Width() < 2 || rectLegend.Height() < 2 || 
		m_chartLayout.m_legendPosition == BCGPChartLayout::LP_NONE || GetVisibleSeriesCount() == 0 ||
		m_bIsThumbnailMode)
	{
		return;
	}

	CBCGPRect rectLegendOrigin, rectBigLegend;
	CBCGPRect rectChart = GetRect();
	if(rectLegend.top < rectChart.top + 45 || rectLegend.bottom > rectChart.bottom - 38)
	{
		rectBigLegend = rectLegend;

		m_bBigLegend = TRUE;

		if(!m_bShowSummary)
		{
			rectLegend.top = rectChart.top+45;
			rectLegend.bottom = rectChart.bottom-38;
		}
		else
		{
			rectLegend.top = rectChart.top+45;
			rectLegend.bottom = rectChart.bottom-138;
		}

		rectLegendOrigin = rectLegend;
	}
	else
	{
		m_bBigLegend = FALSE;
	}

	OnDrawChartElement(pGM, rectLegend, legendStyle, CBCGPChartVisualObject::CE_LEGEND, 
		!m_chartLayout.m_bDrawLegendShape, !m_chartLayout.m_bDrawLegendShape);

	rectLegend.DeflateRect(m_legendAreaFormat.GetContentPadding(TRUE));

	if (IsShowSurfaceMapInLegend())
	{
		for (int i = 0; i < m_arData.GetSize(); i++)
		{
			CBCGPChartSurfaceSeries* pSurfaceSeries = DYNAMIC_DOWNCAST(CBCGPChartSurfaceSeries, GetSeries(i, FALSE));

			if (pSurfaceSeries == NULL || !pSurfaceSeries->m_bVisible)
			{
				continue;
			}

			const BCGPChartFormatSeries* pFormat = &pSurfaceSeries->GetSeriesFormat();

			for (int j = 0; j < pSurfaceSeries->GetLegendElementCount(); j++) 
			{
				CBCGPRect rectKey; 
				CBCGPRect rectLabel;
				CString strLabel;

				pSurfaceSeries->GetLegendElementRects(j, rectKey, rectLabel);
				pSurfaceSeries->GetLegendElementLabel(j, strLabel);

				rectKey.OffsetRect(rectLegend.TopLeft());
				rectLabel.OffsetRect(rectLegend.TopLeft());

				OnDrawChartLegendKey(pGM, rectKey, pFormat, pSurfaceSeries, j);
				OnDrawChartLegendLabel(pGM, strLabel, rectLabel, pFormat->m_legendLabelFormat, pSurfaceSeries, -1);
			}

			break;
		}
	}
	else
	{
		for (int i = 0; i < m_arData.GetSize(); i++)
		{
			CBCGPChartSeries* pSeries = GetSeries(i, FALSE);

			if (pSeries == NULL || !pSeries->IsLegendEntryVisible())
			{
				continue;
			}

			if (pSeries->m_bIncludeDataPointLabelsToLegend)
			{
				for (int j = 0; j < pSeries->GetLegendElementCount(); j++)
				{
					CBCGPChartDataPoint* pDp = (CBCGPChartDataPoint*) pSeries->GetDataPointAt(j);
					if (pSeries->m_bIncludeDataPointLabelsToLegend && pSeries->CanIncludeDataPointToLegend(j))
					{
						OnDrawLegendEntry(pGM, rectLegend, pSeries, pDp, j);
					}
				}
			}
			else
			{
				if(m_bBigLegend) 
				{
					m_rectLegend = rectLegend;
					OnDrawLegendScrollArrow(pGM, rectLegendOrigin, legendStyle);
				}
				OnDrawLegendEntry(pGM, rectLegend, pSeries, NULL, -1);
			}
		}
	}
}

// void MChartVisualObject::OnDrawChartRect(CBCGPGraphicsManager* pGM, const CBCGPRect& rect, const CBCGPBrush* pBrFill, const CBCGPBrush* pBrLine, double dblLineWidth, const CBCGPStrokeStyle* pStrokeStyle, BOOL bNoFill /* = FALSE  */, BOOL bNoLine /* = FALSE */ )
// {
// 
// }

// void MChartVisualObject::OnDrawChartLegendKey(CBCGPGraphicsManager* pGM, const CBCGPRect& rectLegendKey, const BCGPChartFormatSeries* pSeriesStyle, CBCGPChartSeries* pSeries, int nDataPointIndex)
// {
// 
// }

void MChartVisualObject::OnDrawLegendScrollArrow(CBCGPGraphicsManager* pGM, CBCGPRect& rectLegend, BCGPChartFormatArea& legendStyle)
{
	if(pGM->GetPrintInfo() != NULL)
	{
		return;
	}

	if(!rectLegend.IsRectEmpty())
	{
		CBCGPBrush brFill = legendStyle.m_edgeStyle.m_color;
		CBCGPBrush brArrow = RGB(0,0,0);

		if (brFill.GetColor().IsDark())
		{
			brFill.MakeLighter(0.4);
		}

		CBCGPBrush brBorder = brFill;
		brBorder.MakeDarker(0.15);

		CBCGPRect rectUpperBounds(rectLegend.left, rectLegend.top, rectLegend.right, rectLegend.top+10);
		m_rectUpperBound = rectUpperBounds;
		CBCGPRect rectLowerBounds(rectLegend.left, rectLegend.bottom-10, rectLegend.right, rectLegend.bottom);
		m_rectLowerBound = rectLowerBounds;

		pGM->FillRectangle(rectUpperBounds, brFill);
		pGM->DrawRectangle(rectUpperBounds, brBorder);

		pGM->FillRectangle(rectLowerBounds, brFill);
		pGM->DrawRectangle(rectLowerBounds, brBorder);

		CBCGPRect rectUpperArrow = rectUpperBounds;
		CBCGPRect rectLowerArrow = rectLowerBounds;

		CBCGPPointsArray arPoints;

		//upper
		arPoints.Add(CBCGPPoint(rectUpperArrow.CenterPoint().x, rectUpperArrow.top));
		arPoints.Add(CBCGPPoint(rectUpperArrow.CenterPoint().x-5, rectUpperArrow.bottom));
		arPoints.Add(CBCGPPoint(rectUpperArrow.CenterPoint().x+5, rectUpperArrow.bottom));	

		pGM->FillGeometry(CBCGPPolygonGeometry(arPoints), brArrow);

		arPoints.RemoveAll();
		//lower
		arPoints.Add(CBCGPPoint(rectLowerArrow.CenterPoint().x, rectLowerArrow.bottom));
		arPoints.Add(CBCGPPoint(rectLowerArrow.CenterPoint().x-5, rectLowerArrow.top));
		arPoints.Add(CBCGPPoint(rectLowerArrow.CenterPoint().x+5, rectLowerArrow.top));

		pGM->FillGeometry(CBCGPPolygonGeometry(arPoints), brArrow);

	}
}

void MChartVisualObject::OnDrawLegendEntry(CBCGPGraphicsManager* pGM, const CRect& rectLegend, CBCGPChartSeries* pSeries, CBCGPChartDataPoint* pDataPoint, int nDataPointIndex)
{
	CBCGPRect rectKey = pSeries->m_rectLegendKey;
	CBCGPRect rectLabel = pSeries->m_rectLegendLabel;
	CString strLabel = pSeries->m_strSeriesName;
	const BCGPChartFormatSeries* pFormat = &pSeries->GetSeriesFormat();

	if (pDataPoint != NULL && !pDataPoint->m_rectLegendKey.IsRectNull() && pDataPoint->m_bIncludeLabelToLegend)
	{
		rectKey = pDataPoint->m_rectLegendKey;
		rectLabel = pDataPoint->m_rectLegendLabel;

		pSeries->OnGetDataPointLegendLabel(nDataPointIndex, strLabel);
		pFormat = pSeries->GetDataPointFormat(nDataPointIndex, FALSE);
	}

	rectKey.OffsetRect(rectLegend.TopLeft());
	rectLabel.OffsetRect(rectLegend.TopLeft());

	if(rectKey.top >= rectLegend.bottom || rectKey.top < rectLegend.top)
	{
		return; // 범례박스의 범위 넘어가는 것 안그림
	}

	OnDrawChartLegendKey(pGM, rectKey, pFormat, pSeries, nDataPointIndex);
	OnDrawChartLegendLabel(pGM, strLabel, rectLabel, pFormat->m_legendLabelFormat, pSeries, nDataPointIndex);
}

BOOL MChartVisualObject::OnMouseDown(int nButton, const CBCGPPoint& pt)
{
	ASSERT_VALID(this);

	CBCGPBaseVisualObject::OnMouseDown(nButton, pt);

	if (m_pWndOwner->GetSafeHwnd() == NULL)
	{
		return FALSE;
	}

	if (FireMouseMessage(BCGM_ON_CHART_MOUSE_DOWN, nButton, pt))
	{
		return FALSE;
	}

	if (m_bIsThumbnailMode)
	{
		return FALSE;
	}

	if (IsScrollEnabled() && nButton == 0)
	{
		BCGPChartHitInfo hitInfo;
		HitTest(pt, &hitInfo);

		if ((hitInfo.m_hitInfo & BCGPChartHitInfo::HIT_AXIS_SCROLL_BAR) != 0)
		{
			CBCGPChartAxis* pAxis = GetChartAxis(hitInfo.m_nIndex1);
			if (pAxis != NULL)
			{
				ASSERT_VALID(pAxis);
				if (pAxis->ScrollTo(pAxis->ValueFromPointByScrollRange(pt)))
				{
					RecalcMinMaxValues();
					SetDirty(TRUE, TRUE);
				}

				return TRUE;
			}
		}
		else if ((hitInfo.m_hitInfo & BCGPChartHitInfo::HIT_AXIS_THUMB) != 0)
		{
			if (hitInfo.m_nIndex2 == -1 && BeginThumbTrack(hitInfo.m_nIndex1))
			{
				return TRUE;
			}

			BOOL bLeftGrip = hitInfo.m_nIndex2 == 0;
			if (BeginThumbSize(hitInfo.m_nIndex1, bLeftGrip, pt, hitInfo.m_dblVal1))
			{
				return TRUE;
			}

			return FALSE;
		}
	}

	if (IsResizeAxesEnabled() && nButton == 0)
	{
		BCGPChartHitInfo hitInfo;
		HitTest(pt, &hitInfo, BCGPChartHitInfo::HIT_AXIS_RESIZE_BAND);

		if ((hitInfo.m_hitInfo & BCGPChartHitInfo::HIT_AXIS_RESIZE_BAND) != 0)
		{
			if (BeginResizeAxis(hitInfo.m_nIndex1, hitInfo.m_nIndex2, pt))
			{
				return TRUE;
			}
		}
	}

	if (m_bSelectionMode || m_bEnableMagnifier && m_mouseConfig.m_nMagnifierInModifier == 0 ||
		!NeedDisplayAxes())
	{
		return FALSE;
	}

	if (nButton == m_mouseConfig.m_nZoomButton || nButton == m_mouseConfig.m_nPanButton || 
		nButton == m_mouseConfig.m_nSelectionButton)
	{
		BOOL bSelect = (GetAsyncKeyState(m_mouseConfig.m_nZoomInModifier) & 0x8000 || 
			GetAsyncKeyState(m_mouseConfig.m_nZoomOutModifier) & 0x8000 || 
			GetAsyncKeyState(m_mouseConfig.m_nSelectionModifier) & 0x8000 ||
			m_mouseConfig.m_nZoomInModifier == 0 && m_bEnableZoom || 
			m_mouseConfig.m_nSelectionModifier == 0 && m_bEnableSelection);

		BOOL bPan = (GetAsyncKeyState(m_mouseConfig.m_nPanModifier) & 0x8000 ||
			m_mouseConfig.m_nPanModifier == 0) && m_bEnablePan;

		if (bSelect && (nButton == m_mouseConfig.m_nZoomButton || nButton == m_mouseConfig.m_nSelectionButton))
		{
			BeginSelection(pt);
			return TRUE;
		}
		else if (bPan && nButton == m_mouseConfig.m_nPanButton)
		{
			BeginPan(pt);
			return TRUE;
		}
	}

	return FALSE;
}

void MChartVisualObject::UpDownHitTest(CBCGPPoint ptHit, BOOL bUpDown)
{
	if(!m_bBigLegend) return;

	if(bUpDown)
	{
		//Redraw();
		//SetDirty(FALSE);
	}
	else
	{
		if(ptHit.x > m_rectLowerBound.left && ptHit.x < m_rectLowerBound.right)
		{
			if(ptHit.y > m_rectUpperBound.top && ptHit.y < m_rectUpperBound.bottom)
			{
				//upp
				//AfxMessageBox(_T("up"));
				ReposBigLegendEntry(TRUE);
				//RedrawRect(m_rectLegend);
			}
			else if(ptHit.y > m_rectLowerBound.top && ptHit.y < m_rectLowerBound.bottom)
			{
				//low
				//AfxMessageBox(_T("down"));
				ReposBigLegendEntry(FALSE);
				//RedrawRect(m_rectLegend);
			}
		}
	}
}

void MChartVisualObject::ReposBigLegendEntry(BOOL bUpDown)
{
	if(bUpDown)
	{
		for(int i = 0; i < m_arData.GetCount(); i++)
		{
			CBCGPChartSeries* pSeries = GetSeries(i, FALSE);

			if(i == 0)
			{
				CBCGPRect rectKey = pSeries->m_rectLegendKey;
				rectKey.OffsetRect(m_rectLegend.TopLeft());

				if(rectKey.top > m_rectLegend.top)
					return;
			}

			pSeries->m_rectLegendKey.top += 30;
			pSeries->m_rectLegendKey.bottom += 30;

			pSeries->m_rectLegendLabel.top += 30;
			pSeries->m_rectLegendLabel.bottom += 30;
		}
	}
	else
	{
		for(int i = (int)m_arData.GetCount()-1; i >= 0; i--)
		{
			CBCGPChartSeries* pSeries = GetSeries(i, FALSE);

			if(i == m_arData.GetCount()-1)
			{
				CBCGPRect rectKey = pSeries->m_rectLegendKey;
				rectKey.OffsetRect(m_rectLegend.TopLeft());

				if(rectKey.bottom < m_rectLegend.bottom)
					return;
			}

			pSeries->m_rectLegendKey.top -= 30;
			pSeries->m_rectLegendKey.bottom -= 30;

			pSeries->m_rectLegendLabel.top -= 30;
			pSeries->m_rectLegendLabel.bottom -= 30;
		}
	}
}

void MChartVisualObject::OnDrawChartArea (CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pGM);

	OnDrawChartElement(pGM, rectChartArea, m_chartAreaFormat, CBCGPChartVisualObject::CE_CHART_AREA, FALSE, FALSE);

	OnDrawEmptyStatus( pGM, rectChartArea );
}

void MChartVisualObject::OnDrawEmptyStatus ( CBCGPGraphicsManager* pGM, const CBCGPRect& rectChartArea )
{
	// Series가 존재하면 그리지 않는다.
	if( m_arData.GetSize() > 0 ) return;

	CBCGPVisualManager* pVisualManger = CBCGPVisualManager::GetInstance();
	ASSERT(pVisualManger);

	if( !pVisualManger->IsKindOf(RUNTIME_CLASS(MVisualManager)) ) return;

	MVisualManager* pMVisualMgr = (MVisualManager*)pVisualManger;
	pMVisualMgr->OnDrawChartAreaEmptyStatus( pGM, rectChartArea );
}

void MChartVisualObject::OnDrawAxisLabel(CBCGPGraphicsManager* pGM, double dblCurrValue, CString& strLabel, CBCGPChartAxis* pAxis, const CBCGPRect& rectLabel, const CBCGPRect& rectLabels, const CBCGPRect& rectDiagram)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pAxis);
	ASSERT(pGM != NULL);

	if (pGM == NULL || pAxis == NULL)
	{
		return;
	}

	UNREFERENCED_PARAMETER(dblCurrValue);
	UNREFERENCED_PARAMETER(rectDiagram);
	UNREFERENCED_PARAMETER(rectLabels);

	OnDrawChartElement(pGM, rectLabel, pAxis->m_axisLabelsFormat, CBCGPChartVisualObject::CE_AXIS_LABEL, FALSE, FALSE);

	const CBCGPBrush& brText = pAxis->m_axisLabelsFormat.m_brTextColor.IsEmpty() ? 
		m_currentTheme.m_brAxisLabelTextColor : pAxis->m_axisLabelsFormat.m_brTextColor;

	CBCGPRect rectText = rectLabel;
	CBCGPSize szPadding = pAxis->m_axisLabelsFormat.GetContentPadding(TRUE);

	if (pAxis->IsVertical())
	{
		rectText.DeflateRect(0, szPadding.cy);
	}
	else
	{
		rectText.DeflateRect(szPadding.cx, 0);
	}

	pGM->DrawText(strLabel, rectText, pAxis->m_axisLabelsFormat.m_textFormat, brText);
}