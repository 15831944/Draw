///////////////////////////////////////////////////////////////////////////////
// SRGraphDisplay.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc SRGraphDisplay
//@module SRGraphDisplay.h|  definition of the graph display class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGraphDisplay.h: definition of the graph display class
//
/////////////////////////////////////////////////////////////
#ifndef __SRGRAPHDISPLAY__
#define __SRGRAPHDISPLAY__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphDisplay
//
//@doc SRGraphDisplay

// adinsert SRGraphDisplay
//$head Component classes
//$level 1
////////////////////////////////////////////////////////

//@doc SRGraphDisplay
//@class The graph display component -- inherits font abilities from SRGraphTitle
//@base public | SRGDisplayBase
//@devnote Note that v 1.2 has modified the ancestry of this class so that the <c SRGDisplayBase> abstract class
// contains all data members and defines the member functions.
class SRGraphDisplay : public SRGDisplayBase
{
	CHART_DECLARE_SERIAL(SRGraphDisplay);

	
//@access public member functions
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGraphDisplay();

	//@cmember
	/* Virtual destructor for this class*/
	CHART_API virtual ~SRGraphDisplay();

//@access Protected member functions
protected:
	//@cmember
	/* This function actually draw the vector chart*/
	CHART_API virtual void DrawVectorData();
	//@cmember
	/* This function prepare the axis scale for vector chart before the drawing*/
	CHART_API virtual void PrepareVector();
	//@cmember
	/* Draw the bubble chart*/
	CHART_API virtual void DrawBubbleData();
	//@cmember
	/* Prepare the axis scale for bubble chart before the drawing*/
	CHART_API virtual void PrepareBubble();
	//@cmember
	/* Draws the data for the step charts*/
	CHART_API virtual void DrawStepData();

	//@cmember
	/* Draws Gantt labels*/
	CHART_API virtual void DrawGanttLabels();
	//@cmember
	/* Draws Gantt data*/
	CHART_API virtual void DrawGanttData();

	//@cmember
	/* Draws polar chart labels*/
	CHART_API virtual void DrawPolarLabels();
	//@cmember
	/* Draws polar chart axes*/
	CHART_API virtual void DrawPolarAxis();
	//@cmember
	/* Prepares the display for drawing polar data*/
	CHART_API virtual void PreparePolar();
	//@cmember
	/* Draws polar chart data*/
	CHART_API virtual void DrawPolarData();
	//@cmember
	/* Draws area chart data*/

	//@cmember
	/* Draws candle chart labels*/
	CHART_API virtual void DrawCandleData();

	//@cmember
	/* Draws area charts*/
	CHART_API virtual void DrawAreaData();

	//@cmember
	/* Draws the pseudo 3D axis*/
	CHART_API virtual void DrawIsoClassicAxis();

	//@cmember
	/* Draws the data components of FreeStyle graphs*/
	CHART_API virtual void DrawFreeStyleData();

	//@cmember
	/* Prepares displays for the drawing of Manhattan type graphs*/
	CHART_API virtual void PrepareIsoBar();

	//@cmember
	/* Prepares the display component for drawing*/
	CHART_API virtual void PrepareDisplay();

	//@cmember
	/* Calculates scale ranges for most simple graph types*/
	CHART_API virtual void PrepareYScale();

	//@cmember
	/* Calculates X and Y scale information for scatter graphs*/
	CHART_API virtual void PrepareScatter();

	//@cmember
	/* Draws Web char data*/
	CHART_API virtual void DrawWebData();
	//@cmember
	/* Draws Web chart labels*/
	CHART_API virtual void DrawWebLabels();
	//@cmember
	/* Draws Web chart axes*/
	CHART_API virtual void DrawWebAxis();

	//@cmember
	/* Draws X,Y scatter data*/
	CHART_API virtual void DrawScatterData();
	//@cmember
	/* Draws X,Y scatter labels*/
	CHART_API virtual void DrawScatterLabels();
	//@cmember
	/* Draws X,Y scatter axes */
	CHART_API virtual void DrawScatterAxis();

	//@cmember
	/* Called to draw stock quote hi-lo-close graphs*/
	CHART_API virtual void DrawStockData();

	//@cmember
	/* Called to draw labels for the YX graphs*/
	CHART_API virtual void DrawYXLabels();

	//@cmember
	/* Draws strata graphs*/
	CHART_API virtual void DrawStrataData();

	//@cmember
	/* Draws the 3D pie chart*/
	CHART_API virtual void DrawIsoPieData();

	//@cmember
	/* Draws the YX axis for use with horizontal bar charts*/
	CHART_API virtual void DrawYXAxis();

	//@cmember
	/* Draws horizontal bar data*/
	CHART_API virtual void DrawHBarData();

	//@cmember
	/* Draws vertical stacked bars*/
	CHART_API virtual void DrawStackVBarData();

	//@cmember
	/* Draws horizontal stacked bars*/
	CHART_API virtual void DrawStackHBarData();

	//@cmember
	/* Calculates the size of a stage or platform axis*/
	CHART_API virtual int StageCalcSize(CRect *BackPlane);
	//@cmember
	/* Draws labels and annotations on the stage or platform graphs*/
	CHART_API virtual void DrawStageLabels();

	//@cmember
	/* Draws "Rooftop" objects*/
	CHART_API virtual void DrawIsoAreaData();

	//@cmember
	/* Draws "Manhattan" bars*/
	CHART_API virtual void DrawIsoBarData();

	//@cmember
	/* Draws the "stage" type axis*/
	CHART_API virtual void DrawStageAxis();

	//@cmember
	/* Draws pie chart labels*/
	CHART_API virtual void DrawPieLabels();
	//@cmember
	/* Draws pie chart data*/
	CHART_API virtual void DrawPieData();

	//@cmember
	/* Called to draw standard X,Y labels*/
	CHART_API virtual void DrawClassicLabels();
	//@cmember
	/* Called to draw standard X,Y axes*/
	CHART_API virtual void DrawClassicAxis();

	//@cmember
	/* Called to draw a line plot of the data*/
	CHART_API virtual void DrawLineData();

	//@cmember
	/* Draws vertical bar chart data*/
	CHART_API virtual void DrawVBarData();

	//@cmember
	/* Pre-display preparation for strata graphs*/
	CHART_API virtual void PrepareStrata();
	//@cmember
	/* Draw a strata hbar label with the group header as the label text of each bar*/
	CHART_API virtual void DrawStrataHBarGLabels();
	//@cmember
	/* Draw a strata vbar label with the group header as the label text of each bar*/
	CHART_API virtual void DrawStrataVBarGLabels();
	//@cmember
	/* Draw a strata hbar with each group on one bar*/
	CHART_API virtual void DrawStrataHBarGData();
	//@cmember
	/* Draw a strata vbar with each group on one bar*/
	CHART_API virtual void DrawStrataVBarGData();
	//@cmember
	/* Do some pre-initialization for the strata bar( one group/ per bar )*/
	CHART_API virtual void PrepareStrataBarG();
	//@cmember
	/* Do some pre-initialization for the strata bar( one index/per bar )*/
	CHART_API virtual void PrepareStrataBar();
	//@cmember
	/* Draw strata hbar(data with the same index of different group on the same bar)*/
	CHART_API virtual void DrawStrataHBarData();
	//@cmember
	/* Draw strata vbar(data with the same index of different group on the same bar)*/
	CHART_API virtual void DrawStrataVBarData();

	// XML Formatter for SRGGraphDisplay
	friend class SRGGraphDisplayFTR;
};



// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SRGRAPHDISPLAY__

