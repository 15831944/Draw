///////////////////////////////////////////////////////////////////////////////
// Ochart.h
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


#ifndef __OCHART_H__
#define __OCHART_H__


//Remove warnings about automatic inline expansion of functions ('cos we know)
#pragma warning (disable : 4711) 

// Unreferenced fromal parameter
#pragma warning (disable : 4100)

#ifndef _SFL_MFC_SUPPORT
#define _SFL_MFC_SUPPORT
#endif//_SFL_MFC_SUPPORT

#ifndef _USE_COMMON_
#define _USE_COMMON_
#endif//_USE_COMMON_

#ifndef _OCHART_ACTIVEX_
#include /* */ "ocver.h"
#else
#include /* */ "ocx_ver.h"
#endif //_OCHART_ACTIVEX_

#ifndef _OCHART_ACTIVEX_
#include /* */ "bwdef.h"
#else
#include /* */ "ocx_bwdef.h"
#endif //_OCHART_ACTIVEX_

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _OCCE_
// dll support
#ifndef __OCDLL_H__
#include /* */ "OCdll.h"
#endif //__OCDLL_H__
#endif //_OCCE_

#ifdef _OCCE_
#define _TCHAR WCHAR
#define sscanf swscanf
#endif //_OCCE_

// Exclude some of the file for SFL library!!!
//#define WINVER 0x0400
#ifndef _SFL_MFC_SUPPORT
#define _SFL_MFC_SUPPORT
#endif//_SFL_MFC_SUPPORT
/*
//#define IGraphicsContext CDC
//#define CGraphicsContext CDC

/// end of SFL related
*/

#include <StingrayExportDefs.h>

class SRGDataManager;
	class SRGDynamicDataManager;

//Graph classes
class SRGraph;

//class SRGModel;
//class SRGViewportController;

#ifndef _OCHART_ACTIVEX_
	class SRDynamicGraph;
#endif //_OCHART_ACTIVEX_

//Component classes
class SRGraphComponent;
	class SRGraphBackground;
	class SRGraphTitle;
		class SRGraphLegend;
		class SRGDisplayBase;
			class SRGraphDisplay;

#ifndef _OCHART_ACTIVEX_

#ifdef _OC_DISCRETE
			class SRGClassicAxisBase;
				class SRGLineGraph;
#ifdef _STOCK_GRAPH_
				class SRGStockGraph;
#endif
#ifdef _CANDLE_GRAPH_
				class SRGCandleGraph;
#endif
#ifdef _FREESTYLE_GRAPH_
				class SRGFreestyleGraph;
#endif
#ifdef _AREA_GRAPH_
				class SRGAreaGraph;
#endif
#ifdef _STEP_GRAPH_
				class SRGStepGraph;
#endif
#ifdef _STRATA_GRAPH_
				class SRGStrataGraph;
#endif
#if defined(_VBAR_GRAPH_) || defined(_STACKVBAR_GRAPH_) || defined(_STRATAVBAR_GRAPH_)
			class SRGVBarAxisBase;
#endif
#ifdef _VBAR_GRAPH_
				class SRGVBarGraph;
#endif
#ifdef _STACKVBAR_GRAPH_
				class SRGStackVBarGraph;
#endif
#ifdef _STRATAVBAR_GRAPH_
				class SRGStrataVBarGraph;
#endif
#if defined(_HBAR_GRAPH_) || defined(_STACKHBAR_GRAPH_) || defined(_STRATAHBAR_GRAPH_)
			class SRGHBarAxisBase;
#endif
#ifdef _HBAR_GRAPH_
				class SRGHBarGraph;
#endif
#ifdef _STACKHBAR_GRAPH_
				class SRGStackHBarGraph;
#endif
#ifdef _STRATAHBAR_GRAPH_
				class SRGStrataHBarGraph;
#endif
#if defined(_ISOBAR_GRAPH_) || defined(_ISOAREA_GRAPH_)
			class SRGStageAxisBase;
#endif
#ifdef _ISOBAR_GRAPH_
				class SRGIsoBarGraph;
#endif
#ifdef _ISOAREA_GRAPH_
				class SRGIsoAreaGraph;
#endif
#ifdef _POLAR_GRAPH_
			class SRGPolarGraph;
#endif
#ifdef _SCATTER_GRAPH_
			class SRGScatterGraph;
#endif
#ifdef _BUBBLE_GRAPH_
			class SRGBubbleGraph;
#endif
#ifdef _VECTOR_GRAPH_
			class SRGVectorGraph;
#endif
#ifdef _PIE_GRAPH_
			class SRGPieGraph;
#endif
#ifdef _WEB_GRAPH_
			class SRGWebGraph;
#endif
#ifdef _GANTT_GRAPH_
			class SRGGanttGraph;
#endif
#endif //_OCHART_ACTIVEX_

#endif	// _OC_DISCRETE


		class  SRGraphLabel;
			class  SRGraphLabelBlock;
				class  SRGDecimalScale;
					class  SRGLogScale;
					class  SRGDateScale;
					class  SRGIndexScale;
						class  SRGGroupScale;
					class  SRGScaleBar;
						class  SRGLogBar;
						class  SRGDateBar;
						class  SRGIndexBar;
							class  SRGGroupBar;

		class  SRGTextPanel;
	class  SRGDataWatcher;
	class  SRGTickMarks;
	class  SRGGridLines;

#ifndef _OCHART_ACTIVEX_
#ifndef _OCCE_
	class  SRGCompoundComponent;
		class  SRGCompoundDisplay;
		class  SRGAxisManager;
#endif //_OCCE_
#endif //_OCHART_ACTIVEX_

//Data storage classes
class  SRGraphData;

#ifndef _OCHART_ACTIVEX_
	class  SRGraphDynamicData;
		class  SRGStructureData;
			class  SRGShortStructData;
			class  SRGIntStructData;
			class  SRGFloatStructData;
			class  SRGDoubleStructData;
			class  SRGCharStructData;
#endif //_OCHART_ACTIVEX_

//Multi language annotation class
class  SRGraphAnnotation;

//List classes
class  SRGraphDataList;
class  SRGraphAnnotationList;

//Exception class
class  SRGraphException;

//helper classes
class  SRGraphRect; 
class  CScale;
class  SRGraphFeedback;
class  SRGCoordinate;
class  SRGCompiledPolygon;
class  SRGraphPosition;
class  SRGZoom;

#ifndef _OCHART_ACTIVEX_
//View classes
class  SRGraphView;
class  SRGScrollView;
#endif //_OCHART_ACTIVEX_


// MFC extension classes
class  CObStack;


// definitions useful to the graphics process
#ifndef PI
#define PI	3.1415926  
#endif

#ifndef TWO_PI
#define TWO_PI	(PI*2)
#endif

#ifndef ROOT_TWO
#define ROOT_TWO 1.41421356237
#endif

// some useful macro's

#ifndef DEGREES
#define DEGREES(radians) \
	((double)(radians)*(double)180/(double)PI)
#endif

#ifndef RADIANS
#define RADIANS(degrees) \
	((double)(degrees)/(double)180*(double)PI)
#endif

// To get rid of misspelled "indices" So.. Lysdexia snur in the falimy

#define GetShowIndeces GetShowIndices
#define SetShowIndeces SetShowIndices

// Apparently so do typo's
#define GetPolgonSize GetPolygonSize;

//Definitions for the communications systems used in SRGraph

#define SRG_NOOP					0x00000000	// No Operation
#define SRG_SET_TEXT				0x00000001	// used to update headers and annotations
#define SRG_SET_VALUE				0x00000002	// updates data values
#define SRG_SET_TITLE				0x00000003	// updates graph titles. Use with care because it updates all titles in all connected graphs
#define SRG_SET_HEADER				0x00000004	// changes header text
#define SRG_DYNAMIC_SETVALUE		0x00000005	// pokes dynamic graphs
#define SRG_SET_HIGHLIGHT			0x00000006	// Turns on highlighting as a certain group[index]
#define SRG_RESET_HIGHLIGHT			0x00000007	// Turns on highlighting as a certain group[index]
#define SRG_SET_DISPLAY_MINGROUP	0x00000008	// Sets the minimum group in a display
#define SRG_SET_DISPLAY_MAXGROUP	0x00000009	// Sets the maximum group in a display
#define SRG_SET_DISPLAY_MININDEX	0x0000000a	// Sets the minimum index in a display
#define SRG_SET_DISPLAY_MAXINDEX	0x0000000b	// Sets the maximum index in a display
#define SRG_SET_LEGEND_MINGROUP		0x0000000c	// As above but for legends
#define SRG_SET_LEGEND_MAXGROUP		0x0000000d	// Probably redundant now because legends link to displays automatically
#define SRG_SET_LEGEND_MININDEX		0x0000000e	// Note that these definitions may be removed in a later version.
#define SRG_SET_LEGEND_MAXINDEX		0x0000000f

// typedefs for helper structures
//@doc Structures

//@struct SRGTextBlock | Structure used by CGraphDoc to pass data annotations and group header text 
//between documents updating graph data
typedef struct SRG_TEXT_BLOCK {
	UINT group;	//@field Group of data item or group to which the text string is associated
	UINT index;	//@field Index of data item to which the text string is associated
	UINT textsize;	//@field Length of text string
	_TCHAR text;	//@field Text string 
} SRGTextBlock;

//@struct SRGValueBlock | Structure used by CGraphDoc to pass data items 
//between documents updating graph data
typedef struct SRG_VALUE_BLOCK {
	UINT group;	//@field Group of data item to be updated
	UINT index;	//@field Index of data item to be updated
	double value;	//@field New value for the updated data item
	BOOL bNullFlag;	//@field Null flag for the updated data item
} SRGValueBlock;

//@struct SRGScope | Structure containing the range of data items 
//on which a component is to act (A -1 in any field indicates that 
//all the available data items in that direction should be used.)
typedef struct SRG_SCOPE {
	int nMinIndex;	//@field Lowest index to use
	int nMaxIndex;	//@field Highest index to use
	int nMinGroup;	//@field Lowest group to use
	int nMaxGroup;	//@field Highest group to use
} SRGScope;

enum SRGScaleType { VERTICAL, HORIZONTAL, ANGLE };

/////////////////////////////////////////////////////////////////
//	Definitions for the SRGraph alignment codes
//

#define CX_ALIGN_NONE		0x00000000
#define CX_ALIGN_VTOP		0x00000001
#define CX_ALIGN_VCENTER	0x00000002
#define CX_ALIGN_VBOTTOM	0x00000003
#define CX_ALIGN_VCUSTOM	0x00000004
#define CX_ALIGN_HLEFT		0x00000010
#define CX_ALIGN_HCENTER	0x00000020
#define CX_ALIGN_HRIGHT		0x00000030
#define CX_ALIGN_HCUSTOM	0x00000040

////////////////////////////////////////////////////////////
//	Definitions for the SRGraphStyle object
//

// Note that from 1.1 certain storage has different 
// meaning for different contexts.

// style masks for m_dwStyle

#define CX_FRAME_STYLE_MASK		0x0000000f
#define CX_INTERIOR_STYLE_MASK	0x000000f0
#define CX_OBJECT_STYLE_MASK	0x0000ff00
#define CX_GRAPH_STYLE_MASK		0x00ff0000
#define CX_AXIS_STYLE_MASK		0xff000000


// shift values
#define CX_AXIS_SHIFT			24
#define CX_GRAPH_SHIFT			16
#define CX_LEGEND_SHIFT			0
#define CX_INTERIOR_SHIFT		4
#define CX_OBJECT_SHIFT			8
#define CX_FRAME_SHIFT			0

// frame styles
#define CX_FRAME_NONE			0x00000000
#define CX_FRAME_AUTOMATIC		0x00000001
#define CX_FRAME_LINE			0x00000002
#define CX_FRAME_PATTERN		0x00000003
#define CX_FRAME_COLOR			0x00000004
#define CX_FRAME_DASH			0x00000005
#define CX_FRAME_DOT			0x00000006
#define CX_FRAME_DASHDOT		0x00000007
#define CX_FRAME_DASHDOTDOT		0x00000008
#define CX_FRAME_USER			0x0000000c
								
//interior styles
#define CX_INTERIOR_NONE		0x00000000
#define CX_INTERIOR_AUTOMATIC	0x00000010
#define CX_INTERIOR_COLOR		0x00000020
#define CX_INTERIOR_VSHADE		0x00000030
#define CX_INTERIOR_HSHADE		0x00000040
#define CX_INTERIOR_ASHADE		0x00000050
#define CX_INTERIOR_RESOURCE	0x00000060
#define CX_INTERIOR_IMAGE		0x00000070
#define CX_INTERIOR_PATTERN		0x00000080
#define CX_INTERIOR_USER		0x000000c0

//Object styles
#define CX_OBJECT_NONE			0x00000000
#define CX_OBJECT_AUTOMATIC		0x00000100
#define CX_OBJECT_POINT			0x00000200
#define CX_OBJECT_EXPOINT		0x00000300
#define CX_OBJECT_LINE			0x00000400
#define CX_OBJECT_BAR			0x00000500
#define CX_OBJECT_EXBAR			0x00000600
#define CX_OBJECT_ROD			0x00000700	// unused
#define CX_OBJECT_AREA			0x00000800	// unused
#define CX_OBJECT_SLICE			0x00000900	// unused
#define CX_OBJECT_POLYGON		0x00000a00
#define CX_OBJECT_EXLINE		0x00000b00
#define CX_OBJECT_DOT			0x00000c00
#define CX_OBJECT_SQUARE		0x00000d00
#define CX_OBJECT_TRIANGLE		0x00000e00
//#define CX_OBJECT_INVERT_TRIANGLE	0x00000e10
//#define CX_OBJECT_DIAMOND		0x00000e20

#define CX_OBJECT_INVERT_TRIANGLE	0x00001500
#define CX_OBJECT_DIAMOND			0x00001600

#define CX_OBJECT_VBAR          0x00000f00  // unused
#define CX_OBJECT_HBAR          0x00001000  // unused
#define CX_OBJECT_BUBBLE		0x00001100	// For bubble charts.
#define CX_OBJECT_VECTOR		0x00001200	// For vector charts
#define CX_OBJECT_VSTICK		0x00001300	// NEW 6.01 for "stick" bars
#define CX_OBJECT_HSTICK		0x00001400	// 
#define CX_OBJECT_USER			0x0000c000  // User objects must lie in the range 0000c000 to 0000ff00 All other values are reserved

//Graph styles
#define CX_GRAPH_NONE			0x00000000	//No style defined
#define CX_GRAPH_LINE			0x00010000	//Simple line plot
#define CX_GRAPH_HBAR			0x00020000	//simple horizontal bar chart
#define CX_GRAPH_VBAR			0x00030000	//simple vertical bar chart
#define CX_GRAPH_PIE			0x00040000	//pie chart
#define CX_GRAPH_HISTOGRAM		0x00050000	//Histogram or frequency spectrum (not yet implemented)
#define CX_GRAPH_AREA			0x00060000	//area under a curve
#define CX_GRAPH_STOCK			0x00070000	//Highs Lows and now (or close) dynamic
#define CX_GRAPH_OSCILLOSCOPE	0x00080000	//dynamic multiple plots (not yet implemented)
#define CX_GRAPH_ISO_BAR		0x00090000	//3D "manhattan" graph
#define CX_GRAPH_ISO_AREA		0x000a0000	//3D "Rooftop" graph
#define CX_GRAPH_STACK_VBAR		0x000b0000	//2D stacked vertical bars
#define CX_GRAPH_STACK_HBAR		0x000c0000	//2d stacked horizontal bars
#define CX_GRAPH_ISO_PIE		0x000d0000	//3D isographic pie chart
#define CX_GRAPH_STRATA			0x000e0000	//Strata graph
#define CX_GRAPH_EX_VBAR		0x000f0000	//Extended VBar (Pseudo 3D)
#define CX_GRAPH_EX_HBAR		0x00100000	//Extended HBar (pseudo 3D horizontal bars)
#define CX_GRAPH_RIBBON			0x00110000	//Ribbon graphs are rooftop graphs without sides or ends
#define CX_GRAPH_WEB			0x00120000  //Web charts are polar or radar graphs
#define CX_GRAPH_XYSCATTERA		0x00130000	//XY scatter plot using alternate x and y values
#define CX_GRAPH_XYSCATTERI		0x00140000  //XY Scatter plot using the index as the X's and the index+1 as the Y's
#define CX_GRAPH_XYSCATTERG		0x00150000  //XY Scatter plot using the groups as the x's and group+1 as the y's
#define CX_GRAPH_TIMESPAN		0x00160000	//Horizontal time-span bars (not yet implemented)
#define CX_GRAPH_AREAWEB		0x00170000	//Polar shart with area display
#define CX_GRAPH_AREASTOCK		0x00180000	//Area style stock quote (hi-lo)
#define CX_GRAPH_FREESTYLE		0x00190000	//Classic graph with free style objects
#define CX_GRAPH_POLAR			0x001a0000	//Polar chart with phase and magnitude.
#define CX_GRAPH_AREAPOLAR		0x001b0000	//Polar chart with filled areas
#define CX_GRAPH_CANDLE			0x001c0000	//Candle chart style
#define CX_GRAPH_HILO_OPENCLOSE	0x001d0000	//Hi Lo Open Close chart
#define CX_GRAPH_GANTT			0x001e0000	//Gantt chart
#define CX_GRAPH_LINEONLY		0x001f0000	//Line only (no wigets)
#define CX_GRAPH_XYSCATTERA_EX	0x00200000	//scatter charts with log/lin axis differentiation
#define CX_GRAPH_XYSCATTERI_EX	0x00210000	//scatter charts with log/lin axis differentiation
#define CX_GRAPH_XYSCATTERG_EX	0x00220000	//scatter charts with log/lin axis differentiation
#define CX_GRAPH_STEP			0x00230000	//step chart
#define CX_GRAPH_STEPLO			0x00240000	//step chart line only 
#define CX_GRAPH_STRATAVBAR		0x00250000  //STRATA VBAR (one index/per bar)
#define CX_GRAPH_STRATAHBAR		0x00260000  //Starta  hBar chart (one index/per bar)
#define CX_GRAPH_STRATAVBARG	0x00270000  //Starta vbar (one group/per bar)
#define CX_GRAPH_STRATAHBARG	0x00280000  //Strata hbar (one group/per bar)
#define CX_GRAPH_BUBBLE_R       0x00290000  //Bubble and size is Radius
#define CX_GRAPH_BUBBLE_A       0x002a0000  //Bubble and size is Area
#define CX_GRAPH_VECTOR_E       0x002b0000  //Anchor at start end
#define CX_GRAPH_VECTOR_C       0x002c0000  //Anchor at the center
#define CX_GRAPH_VECTOR_G       0x002d0000  //Vector discribed by points
#define CX_GRAPH_SHADED_CANDLE	0x002e0000	//NEW 6.01 candle charts that shade from light to dark depending on open and close value.
#define CX_GRAPH_STRATAVBAR100	0x002f0000  //NEW 6.01 100% STRATA VBAR (one index/per bar)
#define CX_GRAPH_STRATAHBAR100	0x00300000  //NEW 6.01 100% Strata hBar (one index/per bar)
#define CX_GRAPH_STRATAVBARG100	0x00310000  //NEW 6.01 100% Strata vbar (one group/per bar)
#define CX_GRAPH_STRATAHBARG100	0x00320000  //NEW 6.01 100% Strata hbar (one group/per bar)

#define CX_GRAPH_USER			0x00C00000	//User styles are in the range 00c00000 to 00ff0000 all other values are reserved

//axis styles
#define CX_AXIS_NONE			0x00000000	//No style defined
#define CX_AXIS_AUTOMATIC		0x01000000  //Style chosen from graph
#define CX_AXIS_CLASSIC			0x02000000	//Automatic XY axes with automatic negative Y
#define CX_AXIS_OSCILLOSCOPE	0x03000000	//+-X +-Y for 2D plots.
#define CX_AXIS_PLATFORM_SE		0x04000000	//Isographic ribbon viewed from south east
#define CX_AXIS_PLATFORM_SW		0x05000000	//Viewed from south west
#define CX_AXIS_STAGE_SE		0x06000000	// 3/4 stage views from south east
#define CX_AXIS_STAGE_SW		0x07000000	// 3/4 stage from south west
#define CX_AXIS_H_FRAME			0x08000000	// "Rugby" (American football?) goal posts
#define CX_AXIS_PIE				0x09000000	// Pie chart labelling
#define CX_AXIS_YX				0x0a000000	// Classic axis but with x extending upward
#define CX_AXIS_ISO_CLASSIC		0x0b000000	// Classic axis but with pseudo 3D effect
#define CX_AXIS_CLASSIC_RIGHT	0x0c000000	// Classic axis with Y on the right
#define CX_AXIS_ISO_CLASSIC_R	0x0d000000	// classic axis, pseudo 3D, y axis on right
#define CX_AXIS_WEB				0x0e000000	// Web chart axis
#define CX_AXIS_XYSCATTER		0x0f000000	// Scatter graph axis.
#define CX_AXIS_ISO_CLASSIC_YX	0x10000000	// Iso classic for horizontal graphs
#define CX_AXIS_POLAR			0x11000000	// Polar chart axes.
#define CX_AXIS_DATE			0x12000000	// Classic axis with date scale  
#define CX_AXIS_DATE_R			0x13000000	// Classic axis with date scale on the right
#define CX_AXIS_ISO_DATE		0x14000000	// Iso classic axis with date scale
#define CX_AXIS_ISO_DATE_R		0x15000000	// Iso classic axis with date scale on the right
#define CX_AXIS_ISO_DATE_YX		0x16000000	// Iso classic axis with date scale on a YX axis
#define CX_AXIS_DATE_YX			0x17000000	// Classic axis with date scale  
#define CX_AXIS_GANTT_VALUE		0x18000000	// Gantt chart axis, value scale
#define CX_AXIS_GANTT_DATE		0x19000000	// Gantt chart axis, date scale
#define CX_AXIS_SCATTER_DATEX	0x1a000000	// Scatter axis with a date scale on the X axis
#define CX_AXIS_SCATTER_DATEY	0x1b000000	// Scatter axis with a date scale on the Y axis
#define CX_AXIS_USER			0xc0000000  // User styles are in the range c0000000 to ff000000 All other values are reserved

// Used in m_dwStyleB
#define CX_LEGEND_STYLE_MASK	0x000000ff
//Legending styles
#define CX_LEGEND_NONE			0x00000000	//No style defined
#define CX_LEGEND_AUTOMATIC		0x00000001	//Automatic
#define CX_LEGEND_BY_INDEX		0x00000002	//Uses index headers to annotate legend
#define CX_LEGEND_BY_GROUP		0x00000003	//Uses Group headers to annotate legend
#define CX_LEGEND_BY_RECTANGLE	0x00000004	//uses individual annotations
#define CX_LEGEND_HEAD_GROUP	0X00000005	//titles legend by group and uses indices to annotate
#define CX_LEGEND_HEAD_INDEX	0x00000006	//titles legend by index and uses groups to annotate
#define CX_LEGEND_USER			0x000000c0  //User legend styles. 0x000000c0 to 0x000000ff All other values are reserved.

//Also used in m_dwStyle B are certain new semaphores added in v 1.1

#define CX_LOG_SCALE_X_MASK		0x80000000	// Used to differentiate between log/log and log/lin charts
#define CX_XLCOMP_MASK			0x40000000	// Used to display xlabels in a compatible style to those in OC 1.01 
#define CX_HGRAPH_MASK			0x20000000	// Defines compound charts as YX types and swops the axis usage
#define CX_CULLPOINTS_MASK		0x10000000	// Signifies that points may be culled to speed drawing.
#define CX_RELINDEX_MASK		0x08000000	// Used to keep index headers relative to the component scope
#define CX_LINKTAGS_MASK		0x04000000	// Allows tags to be linked to the data item that generated them
#define CX_OBJECT_INSIDE_MASK   0x02000000  // Used for Bubble and vector chart to adjust scale to make object inside view area
#define CX_IMAGE_LOADED_MASK	0x01000000  // Used for external image fill
// component and object styles styles

#define	CX_NO_BORDER			0x00000000
#define	CX_THIN_RAISED_BORDER	0x00000001
#define	CX_THIN_SUNKEN_BORDER	0x00000002
#define	CX_THIN_3D_BORDER		0x00000003
#define	CX_THICK_RAISED_BORDER	0x00000004
#define	CX_THICK_SUNKEN_BORDER	0x00000005
#define	CX_THICK_3D_BORDER		0x00000006
#define CX_LINE_BORDER			0x00000007
#define CX_USER_BORDER			0x0000000c	
								
#define CX_NO_SHADOW			0x00000000
#define	CX_THIN_SHADOW			0x00000010
#define	CX_MEDIUM_SHADOW		0x00000020
#define	CX_THICK_SHADOW			0x00000030
#define CX_USER_SHADOW			0x000000c0

#define	CX_NO_FILL				0x00000000
#define	CX_SOLID_FILL			0x00000100
#define	CX_VERTICAL_FILL		0x00000200
#define	CX_HORIZONTAL_FILL		0x00000300
#define CX_ANGLE_FILL			0x00000400
#define	CX_RESOURCE_FILL		0x00000500
#define	CX_IMAGE_FILL			0x00000600
#define CX_USER_FILL			0x00000c00

#define CX_BORDER_MASK			0x0000000f
#define CX_BORDER_SHIFT			0
#define CX_SHADOW_MASK			0x000000f0
#define CX_SHADOW_SHIFT			4
#define CX_FILL_MASK			0x00000f00
#define CX_FILL_SHIFT			8
#define CX_FOREGROUND_MASK		0x0000f000
#define CX_FOREGROUND_SHIFT		12
#define CX_STRETCH_MASK			0x80000000

// Defines used for semaphores in the m_dwStyleA member

#define CX_AUTO_ORIENTATION_MASK	0x80000000
#define CX_SIZE_MASK				0x40000000
#define CX_FILL_AXIS_MASK			0x20000000
#define CX_SHADE_OBJECT_MASK		0x10000000
#define CX_LOG_SCALE_MASK			0x08000000
#define CX_MAX_SCALE_MASK			0x04000000
#define CX_EMPTY_GRAPH_MASK			0x02000000
#define CX_HIDE_NUMERALS_MASK		0x01000000
#define CX_HIDE_INDICES_MASK		0x00800000
#define CX_HIDE_GROUPS_MASK			0x00400000
#define CX_USE_SAME_XYSCALE_MASK	0x00200000
#define CX_USE_MAX_XSCALE_MASK		0x00100000
#define CX_USE_MAX_YSCALE_MASK		0x00080000
#define CX_BREAK_LINES_ON_NULL		0x00040000
#define CX_LEGEND_LINE_MASK			0x00020000
#define CX_HIDE_XGRID_MASK			0x00010000
#define CX_HIDE_YGRID_MASK			0x00008000
#define CX_HIDE_ZGRID_MASK			0x00004000
#define CX_HIDE_ZERO_MASK			0x00002000
#define CX_HIDE_XTICKS_MASK			0x00001000
#define CX_HIDE_YTICKS_MASK			0x00000800
#define CX_HIDE_ZTICKS_MASK			0x00000400
#define CX_SORT_VALUES_MASK			0x00000200
#define CX_OVERLAY_GRID_MASK		0x00000100
#define CX_DISPLAYLOCK_MASK			0x00000080
#define CX_MINORTICKS_MASK			0x00000040
#define CX_TIER_XLABELS_MASK		0x00000020
#define CX_TIER_YLABELS_MASK		0x00000010
#define CX_LEGEND_KEYFIRST_MASK		0x00000008
#define CX_SCALE_LIMIT_MASK			0x00000004
#define CX_LEGEND_LOCK_RC_MASK		0x00000002
#define CX_DISPLAY_INFO_ONLY_MASK	0x00000002 //NEW 6.01 NOTE this option is context sensitive
#define CX_DEFER_DRAW_MASK			0x00000001


// defines used in the m_dwStyleC member

#define CX_TYPE_MASK					0x0000000f
#define CX_TYPE_SHIFT					0
										
#define CX_TYPE_NONE					0x00000000
#define CX_TYPE_COMPONENT				0x00000001
#define CX_TYPE_OBJECT					0x00000002
#define CX_TYPE_GRAPH					0x00000003
#define CX_TYPE_DISPLAY					0x00000004
#define CX_TYPE_LEGEND					0x00000005
#define CX_TYPE_TITLE					0x00000006
#define CX_TYPE_LABEL					0x00000007
#define CX_TYPE_LABELBLOCK				0x00000008
#define CD_TYPE_DSCALE					0x00000009
#define CX_TYPE_LOGSCALE				0x0000000a
#define CX_TYPE_DATESCALE				0x0000000b
										
										
										
#define CX_LABEL_MASK					0x000000f0
#define CX_LABEL_SHIFT					4
										
#define CX_LABEL_NONE					0x00000000
#define CX_LABEL_AUTOMATIC				0x00000010
#define CX_LABEL_VALUE					0x00000020
#define CX_LABEL_PERCENT				0x00000030
#define CX_LABEL_VALUE_PERCENT			0x00000040
#define CX_LABEL_TEXT					0x00000050
#define CX_LABEL_TEXT_VALUE				0x00000060
#define CX_LABEL_TEXT_VALUE_PERCENT		0x00000070
#define CX_LABEL_TEXT_PERCENT			0x00000080
#define CX_LABELBLOCK_HIDELABELS		0x00000090
#define CX_LABELBLOCK_MOVELABELS		0x000000a0
										
#define CX_HIGHLIGHT_MASK				0x00000f00
#define CX_HIGHLIGHT_SHIFT				8
										
#define CX_HIGHLIGHT_NONE				0x00000000
#define CX_HIGHLIGHT_AUTOMATIC			0x00000100
#define CX_HIGHLIGHT_SMALL				0x00000200
#define CX_HIGHLIGHT_MEDIUM				0x00000300
#define CX_HIGHLIGHT_LARGE				0x00000400
#define CX_HIGHLIGHT_CUSTOM				0x00000c00
										
#define CX_KEY_STYLE_MASK				0x0000f000
#define CX_KEY_SHIFT					12
										
#define CX_KEY_NONE						0x00000000
#define CX_KEY_AUTOMATIC				0x00001000
#define CX_KEY_LINE						0x00002000
#define CX_KEY_BOX						0x00003000
#define CX_KEY_WIGET					0x00004000
#define CX_KEY_DATA						0x00005000
#define CX_KEY_CUSTOM					0x0000c000
										
#define CX_TAG_OUTLINE_MASK				0x000f0000
#define CX_TAG_OUTLINE_SHIFT			16
										
#define CX_TAG_OUTLINE_NONE				0x00000000
#define CX_TAG_OUTLINE_AUTOMATIC		0x00010000
#define CX_TAG_OUTLINE_BOX				0x00020000
#define CX_TAG_OUTLINE_ELLIPSE			0x00030000
#define CX_TAG_OUTLINE_FLASH			0x00040000
#define CX_TAG_OUTLINE_POLYGON			0x00050000
#define CX_TAG_OUTLINE_CUSTOM			0x000c0000

	
#define CX_TAG_POSITION_MASK			0x00f00000
#define CX_TAG_POSITION_SHIFT			24

#define CX_TAG_POSITION_LEFT			0x00000000
#define CX_TAG_POSITION_LEFTABOVE		0x00100000
#define CX_TAG_POSITION_ABOVE			0x00200000	
#define CX_TAG_POSITION_RIGHTABOVE		0x00300000
#define CX_TAG_POSITION_RIGHT			0x00400000
#define CX_TAG_POSITION_RIGHTBELOW		0x00500000
#define CX_TAG_POSITION_BELOW			0x00600000
#define CX_TAG_POSITION_LEFTBELOW		0x00700000
#define CX_TAG_POSITION_CENTERED		0x00800000


#define CX_TAG_ORIENTATION_MASK		0x0f000000
#define CX_TAG_ORIENTATION_SHIFT	28
										
#define CX_TAG_ORIENTATION_ZERO		0x00000000
#define CX_TAG_ORIENTATION_45		0x01000000
#define CX_TAG_ORIENTATION_90		0x02000000
#define CX_TAG_ORIENTATION_135		0x03000000
#define CX_TAG_ORIENTATION_180		0x04000000
#define CX_TAG_ORIENTATION_225		0x05000000
#define CX_TAG_ORIENTATION_270		0x06000000
#define CX_TAG_ORIENTATION_315		0x07000000
										
#define CX_TAG_MODEL_MASK			0x30000000
									
#define CX_TAG_MODEL_AUTOMATIC		0x00000000
#define CX_TAG_MODEL_LOCAL			0x10000000
#define CX_TAG_MODEL_PERSISTENT		0x20000000
#define CX_TAG_MODEL_BLOCKED		0x30000000

#define CX_TAG_FONT_MASK			0xc0000000

#define CX_TAG_FONT_NORMAL			0x00000000
#define CX_TAG_FONT_SMALL			0x40000000
#define CX_TAG_FONT_LARGE			0x80000000
#define CX_TAG_FONT_CUSTOM			0xc0000000


/////////////////////////////////////////////////////
//	Definitions for the SRGraphPosition class
//

#define CX_POSITION_MASK		0x0000000f

#define CX_POSITION_NONE		0x00000000	
#define CX_POSITION_SINGLE		0x00000001	// position is for a single component
#define CX_POSITION_LIST		0x00000002	// for a list of components

#define CX_POSITION_VALUEY		0x00000010	// The Y value is known
#define CX_POSITION_VALUEX		0x00000020	// The X value is known
#define CX_POSITION_GROUP		0x00000040	// The group is known
#define CX_POSITION_INDEX		0x00000080	// The index is known

#define CX_POSITION_SELECT_MASK	0x000f0000
#define CX_POSITION_SELECT_H	0x00000000	// Selection is horizontal (classic)
#define CX_POSITION_SELECT_V	0x00010000	// selection is vertical (yx)
#define CX_POSITION_SELECT_B	0x00020000	// selection is both (x,y scatter)
#define CX_POSITION_SELECT_C	0x00030000	// Selection is circular (webs)
#define CX_POSITION_SELECT_R	0x00040000	// Selection is radial (polar)


/////////////////////////////////////////////////////
// various colors to use in filling and framing

#define CXCLR_WHITE		RGB(255,255,255)
#define CXCLR_BLACK		RGB(0,0,0)
#define CXCLR_RED		RGB(255,0,0)
#define CXCLR_LTRED		RGB(255,92,92)
#define CXCLR_ROSE		RGB(255,128,128)
#define CXCLR_PINK		RGB(255,192,192)
#define CXCLR_CORAL		RGB(255,0,128)
#define CXCLR_MAROON	RGB(128,0,0)
#define CXCLR_OLIVE		RGB(128,128,0)
#define CXCLR_TEAL		RGB(0,128,128)
#define CXCLR_GREEN		RGB(0,128,0)
#define CXCLR_SEAGREEN	RGB(0,255,128)
#define CXCLR_LIME		RGB(0,255,0)
#define CXCLR_LTGREEN	RGB(128,255,0)
#define CXCLR_BLUE		RGB(0,0,255)
#define CXCLR_MIDNIGHT	RGB(0,0,128)
#define CXCLR_SKY		RGB(0,128,255)
#define CXCLR_PURPLE	RGB(128,0,128)
#define CXCLR_VIOLET	RGB(128,0,255)
#define CXCLR_BEIGE		RGB(255,128,0)
#define CXCLR_CYAN		RGB(0,255,255)
#define CXCLR_MAGENTA	RGB(255,0,255)
#define CXCLR_YELLOW	RGB(255,255,0)
#define CXCLR_GRAY10	RGB(230,230,230)
#define	CXCLR_GRAY20	RGB(205,205,205)
#define CXCLR_GRAY30	RGB(179,179,179)
#define CXCLR_GRAY40	RGB(152,152,152)
#define CXCLR_GRAY50	RGB(128,128,128)
#define CXCLR_GRAY60	RGB(102,102,102)
#define CXCLR_GRAY70	RGB(76,76,76)
#define CXCLR_GRAY80	RGB(51,51,51)
#define CXCLR_GRAY90	RGB(25,25,25)


//////////////////////////////////////////////////////////
// Data scan definitions

#define CX_SCAN_ABOVELIMIT			0
#define CX_SCAN_BELOWLIMIT			1
#define CX_SCAN_AVERAGEABOVELIMIT	2
#define CX_SCAN_AVERAGEBELOWLIMIT	3
#define CX_SCAN_INBRACKET			4
#define CX_SCAN_OUTOFBRACKET		5
#define CX_SCAN_AVERAGEINBRACKET	6
#define CX_SCAN_AVERAGEOUTOFBRACKET	7

#define CX_SCAN_CUSTOM				256
// NOTE that although any scan value apart from the pre-defined ones
// will generate a custom scan it is recommended that you use the 
// provided custom scan value or above for your own functions.

///////////////////////////////////////////////////////////
// Miscellaneous definitions

#define CX_PIXEL			0
#define CX_MILLIMETER		1
#define CX_INCH				2
#define CX_PERCENT			3

#define CX_FONT_BOLD		0x00000001
#define CX_FONT_ITALIC		0x00000002
#define CX_FONT_UNDERLINE	0x00000004
#define CX_FONT_STRIKEOUT	0x00000008
#define CX_FONT_AUTOSIZE	0x00000010
#define CX_FONT_EMBOSS		0x00000020
#define CX_FONT_RELIEF		0x00000040
#define CX_FONT_NOWRAP		0x00000080

// Definitions for label location points.

#define CX_MID_LEFT			0
#define CX_TOP_LEFT			1
#define CX_TOP_CENTER		2
#define CX_TOP_RIGHT		3
#define CX_MID_RIGHT		4
#define CX_BOTTOM_RIGHT		5
#define CX_BOTTOM_CENTER	6
#define CX_BOTTOM_LEFT		7
#define CX_MID_CENTER		8

///////////////////////////////////////////////////////////
//
// Standard inclusions
//
#include  "obstack.h"


#ifndef _OCCE_

#ifndef _OCHART_ACTIVEX_
#include  "comdoc.h"
#endif //_OCHART_ACTIVEX_

#include  "SRGRes.h"
#else // if _OCCE_
#include "srgceres.h"
#endif //_OCCE_

#include  "DataMgr.h"
#include  "SRGraph.h"

//#include "SRGModel.h"
//#include "SRGVpCtlr.h"


#include "unknwn.h"
#include  "SRGExc.h"
#include  "SRGDat.h"

#ifndef _OCHART_ACTIVEX_
#include  "SRGStructureData.h"
#endif //_OCHART_ACTIVEX

#include  "SRGFbck.h"
#include  "SRGCPly.h"
#include  "SRGraphRect.h"
#include  "SRGComp.h"
#include  "SRGraphTitle.h"
#include  "SRGraphBackground.h" 
#include  "SRGraphLabel.h"
#include  "SRGraphLabelBlock.h"
#include  "SRGraphLegend.h"
#include  "SRGDisplayBase.h"
#ifndef _OC_NO_STANDARD_DISPLAY
#include  "SRGraphDisplay.h"
#endif //_OC_NO_STANDARD_DISPLAY
#include  "DScale.h"
#include  "srgposn.h"

#include "SRGScaleBar.h"
#include "SRGIndexBar.h"

#ifndef _OCHART_ACTIVEX_
#ifndef _OCCE_
#include  "docmngr.h"
#include  "graphdoc.h"
#else // if _OCCE_
#include "CEGraphDoc.h"
#endif //_OCCE_
#include  "grphtip.h"
#include  "graphvw.h"
#include  "SRGScrollView.h"
#endif //_OCHART_ACTIVEX_

#ifndef _OCCE_
#include  "SRGTextPanel.h"
#endif //_OCCE_

#include  "SRGTickMarks.h"
#include  "SRGGridLines.h"
#include  "SRGDataWatcher.h"

#ifndef _OCHART_ACTIVEX_
#ifndef _OCCE_
#include  "SRGCompoundComponent.h"
#include  "SRGCompoundDisplay.h"
#include  "SRGAxisManager.h"

#endif //_OCCE_
#endif //_OCHART_ACTIVEX_

#include  "SRGZoom.h"

#ifndef _OCHART_ACTIVEX_

// Discrete display classes
#ifdef _OC_DISCRETE
#include  "SRGClassicAxisBase.h"
#include  "SRGLineGraph.h"
#ifdef _STOCK_GRAPH_
#include  "SRGStockGraph.h"
#endif
#ifdef _CANDLE_GRAPH_
#include  "SRGCandleGraph.h"
#endif
#ifdef _FREESTYLE_GRAPH_
#include  "SRGFreestyleGraph.h"
#endif
#ifdef _AREA_GRAPH_
#include  "SRGAreaGraph.h"
#endif
#ifdef _STEP_GRAPH_
#include  "SRGStepGraph.h"
#endif
#ifdef _STRATA_GRAPH_
#include  "SRGStrataGraph.h"
#endif
#if defined(_VBAR_GRAPH_)||defined(_STACKVBAR_GRAPH_)||defined(_STRATAVBAR_GRAPH_)
#include  "SRGVBarAxisBase.h"
#endif
#ifdef _VBAR_GRAPH_
#include  "SRGVBarGraph.h"
#endif
#ifdef _STACKVBAR_GRAPH_
#include  "SRGStackVBarGraph.h"
#endif
#ifdef _STRATAVBAR_GRAPH_
#include  "SRGStrataVBarGraph.h"
#endif
#if defined(_HBAR_GRAPH_)||defined(_STACKHBAR_GRAPH_)||defined(_STRATAHBAR_GRAPH)
#include  "SRGHBarAxisBase.h"
#endif
#ifdef _HBAR_GRAPH_
#include  "SRGHBarGraph.h"
#endif
#ifdef _STACKHBAR_GRAPH_
#include  "SRGStackHBarGraph.h"
#endif
#ifdef _STRATAHBAR_GRAPH_
#include  "SRGStrataHBarGraph.h"
#endif
#if defined(_ISOBAR_GRAPH_)||defined(_ISOAREA_GRAPH_)
#include  "SRGStageAxisBase.h"
#endif
#ifdef _ISOBAR_GRAPH_
#include  "SRGIsoBarGraph.h"
#endif
#ifdef _ISOAREA_GRAPH_
#include  "SRGIsoAreaGraph.h"
#endif
#ifdef _POLAR_GRAPH_
#include  "SRGPolarGraph.h"
#endif
#ifdef _SCATTER_GRAPH_
#include  "SRGScatterGraph.h"
#endif
#ifdef _BUBBLE_GRAPH_
#include  "SRGBubbleGraph.h"
#endif
#ifdef _VECTOR_GRAPH_
#include  "SRGVectorGraph.h"
#endif
#ifdef _PIE_GRAPH_
#include  "SRGPieGraph.h"
#endif
#ifdef _WEB_GRAPH_
#include  "SRGWebGraph.h"
#endif
#ifdef _GANTT_GRAPH_
#include  "SRGGanttGraph.h"
#endif

#endif	// _OC_DISCRETE

#endif //_OCHART_ACTIVEX_




#ifndef _OCHART_ACTIVEX_

// Includes for XML Serialization
#ifdef _OC_XMLSERIALIZE_

#include "foundation\xmlserialize.h"

using namespace stingray::foundation;

#include "SRGCommonFTR.h"
#ifdef _OC_DISCRETE
#include "SRGDiscreteFTR.h"
#endif	// _OC_DISCRETE

#endif	// _OC_XMLSERIALIZE_

#endif //_OCHART_ACTIVEX_


#ifndef _OCHART_ACTIVEX_

#include "SREScrollView.h"
#include "SREGraphView.h"
#ifndef _OCCE_
#include "SRGComboBox.h"
#endif //_OCCE_

#endif //_OCHART_ACTIVEX_




#ifndef _OCCE_
#ifndef _OCHART_ACTIVEX_
// Chart wizard includes
#ifndef _OC_DISCRETE
#include "SRGRectTracker.h"
#include "SRGWizView.h"
#include "SRGWzDisplay.h"
#include "WizSheet.h"
#endif // _OC_DISCRETE

#endif //_OCHART_ACTIVEX_
#endif //_OCCE_

#endif // __OCHART_H__
