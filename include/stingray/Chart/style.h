///////////////////////////////////////////////////////////////////////////////
// style.h
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
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//@doc Styles
//@module Styles.h | Style flag description file<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////////
//
// Styles.h: Objective Chart Style flags
//
/////////////////////////////////////////////////////////////////

// Autoduck comments for creating help topics listing available style settings
// These lists were previously in SRGDat.h.
// Compare with lists in ochart.h for completeness.

//@topic ComDoc commands | Subcodes for SEC_DOC_UPDATE handled by CGraphDoc
//See <c CGraphDoc>
//SRG_NOOP <tab> No Operation
//SRG_SET_TEXT <tab> used to update headers and annotations
//SRG_SET_VALUE	 <tab> updates data values
//SRG_SET_TITLE	 <tab> updates graph titles. Use with care because it updates all titles in all connected graphs
//SRG_SET_HEADER <tab> changes header text
//SRG_DYNAMIC_SETVALUE <tab> pokes dynamic graphs
//SRG_SET_HIGHLIGHT	<tab> Turns on highlighting as a certain group[index]
//SRG_RESET_HIGHLIGHT <tab> Turns on highlighting as a certain group[index]
//SRG_SET_DISPLAY_MINGROUP <tab> Sets the minimum group in a display
//SRG_SET_DISPLAY_MAXGROUP <tab> Sets the maximum group in a display
//SRG_SET_DISPLAY_MININDEX <tab> Sets the minimum index in a display
//SRG_SET_DISPLAY_MAXINDEX <tab> Sets the maximum index in a display
//SRG_SET_LEGEND_MINGROUP <tab> As above but for legends
//SRG_SET_LEGEND_MAXGROUP <tab> Probably redundant now because legends link to displays automatically
//SRG_SET_LEGEND_MININDEX <tab> Note that these definitions may be removed in a later version.
//SRG_SET_LEGEND_MAXINDEX <tab> 

//@topic Frame styles | Define the type of frame drawn around bars, etc.<nl>
//Use <mf SRGraphStyle::GetFrameStyle> and <mf SRGraphStyle::SetFrameStyle>.<nl>
//See <md SRGraphStyle::m_dwStyle>.
//
//CX_FRAME_NONE<nl> <tab>No frame is drawn.<nl>
//CX_FRAME_AUTOMATIC<nl> <tab>A frame is chosen by the drawing system depending on context.<nl>
//CX_FRAME_LINE<nl> <tab>The frame is a simple line.<nl>
//CX_FRAME_PATTERN<nl> <tab>A pattern is used to paint a frame.<nl>
//CX_FRAME_COLOR<nl> <tab>The m_RGBFrameColor member has an RGB color to be used when drawing the frame.<nl>
//CX_FRAME_DASH<nl> <tab>The frame is a dashed line.<nl>
//CX_FRAME_DOT<nl> <tab>The frame is a dotted line.<nl>
//CX_FRAME_DASHDOT<nl> <tab>The frame is a line of alternating dashes and dots.<nl>
//CX_FRAME_DASHDOTDOT<nl> <tab>The frame is a line of alternating dashes and two dots.<nl>
//CX_FRAME_USER<nl> <tab>The frame is user defined.<nl>

//@topic Interior styles | Define how an object is filled<nl>
//Use <mf SRGraphStyle::GetInteriorStyle> and <mf SRGraphStyle::SetInteriorStyle>.<nl><nl>
//See <md SRGraphStyle::m_dwStyle>.
//
//CX_INTERIOR_NONE<nl> <tab>The interior is not filled.<nl>
//CX_INTERIOR_AUTOMATIC<nl> <tab>The interior is chosen using an automatic process. <nl>
//CX_INTERIOR_COLOR<nl> <tab>The fill is made using a solid color as defined in m_colorA.<nl>
//CX_INTERIOR_VSHADE<nl> <tab>A shaded vertical vignette is created which begins with the value in m_colorA and ends with the value in m_colorB.<nl>
//CX_INTERIOR_HSHADE<nl> <tab>A shaded horizontal vignette is created starting with m_colorA and ending with m_colorB.<nl>
//CX_INTERIOR_ASHADE<nl> <tab>A shaded vignette is angled using m_dAngle and spanning the colors from m_colorA to m_colorB. 
//Note that colors within the polygon are not guaranteed to lie in this range 
//because the span of colors is actually calculated within a bounding box 
//which may or may not allow the color range end points to be seen.<nl>
//CX_INTERIOR_RESOURCE<nl> <tab>The name held in m_strImageName is used to load a resource bitmap which may be stretched or tiled over the surface of the object.<nl>
//CX_INTERIOR_IMAGE<nl> <tab>Not currently used (reserved)<nl>
//CX_INTERIOR_PATTERN<nl> <tab>Not currently used (reserved)<nl>
//CX_INTERIOR_USER<nl> <tab>User defined<nl>

//@topic Object styles | Define the type of object used for a particular data item<nl>
//Use <mf SRGraphStyle::SetObjectStyle> and <mf SRGraphStyle::GetObjectStyle>.<nl>
//See <md SRGraphStyle::m_dwStyle>, <mf SRGraphComponent::DrawPointObject>.
//
//CX_OBJECT_NONE<nl> <tab>The object is not represented.<nl>
//CX_OBJECT_AUTOMATIC<nl> <tab>An object is chosen in context with the data type or graph style.<nl>
//CX_OBJECT_POINT<nl> <tab>The object is a point which is covered by a wiget.<nl>
//CX_OBJECT_EXPOINT<nl> <tab>The object is a point covered by a wiget with connecting lines.<nl>
//CX_OBJECT_LINE<nl> <tab>The object is a line.<nl>
//CX_OBJECT_BAR<nl> <tab>A bar is used.<nl>
//CX_OBJECT_EXBAR<nl> <tab>A bar or polygon is used.<nl>
//CX_OBJECT_POLYGON<nl> <tab>A polygonal shape whose definition is described in m_strObjectName is drawn.<nl>
//CX_OBJECT_EXLINE<nl>	<tab>Pseudo 3D line.<nl> 
//CX_OBJECT_DOT<nl> <tab>The object is a tiny circle.<nl>
//CX_OBJECT_SQUARE<nl> <tab>The object is a square.<nl>
//CX_OBJECT_TRIANGLE<nl> <tab>The object is a triangle.<nl>
//CX_OBJECT_INVERT_TRIANGLE<nl> <tab>The object is an upside-down triangle.<nl>
//CX_OBJECT_DIAMOND<nl> <tab>The object is a diamond.<nl>
//CX_OBJECT_BUBBLE<nl> <tab>For bubble charts.
//CX_OBJECT_VECTOR<nl> <tab>For vector charts
//CX_OBJECT_VSTICK<nl> <tab>NEW 6.01 for "stick" bars
//CX_OBJECT_HSTICK<nl> <tab> NEW 6.01 for "stick" bars
//CX_OBJECT_USER<nl> <tab>User defined object styles lie in the range xxxxc0xx to xxxxffxx. All other values are reserved.<nl>

//@topic Graph styles | Define the type of graph display<nl>
//Use <mf SRGraphStyle::SetGraphStyle> and <mf SRGraphStyle::GetGraphStyle>.<nl>
//See <md SRGraphStyle::m_dwStyle>, <mf SRGraphDisplay::DrawScatterData>, <mf SRGraphDisplay::DrawStrataData>, 
//<mf SRGraphDisplay::DrawCandleData>.
//
//CX_GRAPH_NONE<nl> <tab>No graph.<nl>
//CX_GRAPH_LINE<nl> <tab>Simple line plot<nl>
//CX_GRAPH_HBAR<nl> <tab>Horizontal bar chart<nl>
//CX_GRAPH_VBAR<nl> <tab>Vertical bar chart<nl>
//CX_GRAPH_PIE<nl> <tab>Standard pie chart<nl>
//CX_GRAPH_HISTOGRAM<nl> <tab>Histogram or frequency spectrum (not yet implemented)<nl>
//CX_GRAPH_AREA<nl> <tab>Area under a curve<nl>
//CX_GRAPH_STOCK<nl> <tab>Stock control chart with highest and lowest value history<nl>
//CX_GRAPH_OSCILLOSCOPE<nl> <tab>Dynamic multiple plots (not yet implemented)<nl>
//CX_GRAPH_ISO_BAR<nl> <tab>3D Bar chart or "Manhattan" chart<nl>
//CX_GRAPH_ISO_AREA<nl> <tab>3D Area chart or "Rooftop" graph<nl>
//CX_GRAPH_STACK_VBAR<nl> <tab>2D Stacked vertical bar chart<nl>
//CX_GRAPH_STACK_HBAR<nl> <tab>2D Stacked horizontal bar chart<nl>
//CX_GRAPH_ISO_PIE<nl> <tab>3D Isographic pie chart<nl>
//CX_GRAPH_STRATA<nl> <tab>Strata graph -- the topmost point of the data shows overall value 
//and the layers within show the contribution each set makes to the total<nl>
//CX_GRAPH_EX_VBAR<nl> <tab>Extended VBar (pseudo 3D, vertical bars)<nl>
//CX_GRAPH_EX_HBAR<nl> <tab>Extended HBar (pseudo 3D, horizontal bars)<nl>
//CX_GRAPH_RIBBON<nl> <tab>3D Ribbon graphs (rooftop without sides or ends) for use on stage and platform axes<nl>
//CX_GRAPH_WEB<nl>	Web chart (polar or radar)<nl>
//CX_GRAPH_XYSCATTERA<nl> <tab>XY Scatter plot using alternate X and Y values<nl>
//CX_GRAPH_XYSCATTERI<nl> <tab>XY Scatter plot using the index as the X's and the index+1 as the Y's<nl>
//CX_GRAPH_XYSCATTERG<nl> <tab>XY Scatter plot using the groups as the X's and group+1 as the Y's<nl>
//CX_GRAPH_TIMESPAN<nl> <tab>Horizontal time-span bars (not yet implemented)<nl>
//CX_GRAPH_AREAWEB<nl> <tab>Polar shart with area display<nl>
//CX_GRAPH_AREASTOCK<nl> <tab>Area style stock quote (hi-lo)<nl>
//CX_GRAPH_FREESTYLE<nl> <tab>Classic graph with free style objects<nl>
//CX_GRAPH_POLAR<nl> <tab>Polar chart with phase and magnitude<nl>
//CX_GRAPH_AREAPOLAR<nl> <tab>Polar chart with filled areas<nl>
//CX_GRAPH_CANDLE<nl> <tab>Candle chart style<nl>
//CX_GRAPH_HILO_OPENCLOSE<nl> <tab>Hi Lo Open Close chart<nl>
//CX_GRAPH_GANTT<nl> <tab>Gantt chart<nl>
//CX_GRAPH_LINEONLY<nl> <tab>Line only (no wigets)<nl>
//CX_GRAPH_XYSCATTERA_EX<nl> <tab>Scatter charts with log/lin axis differentiation<nl>
//CX_GRAPH_XYSCATTERI_EX<nl> <tab>Scatter charts with log/lin axis differentiation<nl>
//CX_GRAPH_XYSCATTERG_EX<nl> <tab>Scatter charts with log/lin axis differentiation<nl>
//CX_GRAPH_STEP<nl> <tab>Step chart<nl>
//CX_GRAPH_STEPLO<nl> <tab>Step chart, line only<nl>
//CX_GRAPH_STRATAVBAR<nl> <tab>Strata vertical bar (one bar per index, group values are totaled)
//CX_GRAPH_STRATAHBAR<nl> <tab>Strata horizontal bar (one bar per index,  group values are totaled)
//CX_GRAPH_STRATAVBARG<nl> <tab>Strata vertical bar (one bar per group, index values are totaled)
//CX_GRAPH_STRATAHBARG<nl> <tab>Strata horizontal bar (one bar per group, index values are totaled)
//CX_GRAPH_BUBBLE_R <nl> <tab>Bubble chart with size (value) as Radius
//CX_GRAPH_BUBBLE_A <nl> <tab>Bubble chart with size (value) as Area
//CX_GRAPH_VECTOR_E <nl> <tab>Vectors which are anchored at the start end
//CX_GRAPH_VECTOR_C <nl> <tab>Vectors which are anchored at the center
//CX_GRAPH_VECTOR_G <nl> <tab>Vectors described by two sets of points, one point for each end.
//CX_GRAPH_SHADED_CANDLE <nl> <tab>NEW 6.01 candle charts that shade from light to dark depending on open and close value.
//CX_GRAPH_STRATAVBAR100 <nl> <tab>NEW 6.01 100% STRATA VBAR (one index/per bar)
//CX_GRAPH_STRATAHBAR100 <nl> <tab>NEW 6.01 100% Strata hBar (one index/per bar)
//CX_GRAPH_STRATAVBARG100 <nl> <tab>NEW 6.01 100% Strata vbar (one group/per bar)
//CX_GRAPH_STRATAHBARG100 <nl> <tab>NEW 6.01 100% Strata hbar (one group/per bar)
//CX_GRAPH_USER<nl> <tab>User graph styles are in the range xxc0xxxx to xxffxxxx. All other values are reserved.

//@topic Axis styles | Each graph data display needs an axis upon which data is projected. 
//Use <mf SRGraphStyle::SetAxisStyle> and <mf SRGraphStyle::GetAxisStyle>.<nl>
//See <md SRGraphStyle::m_dwStyle>.
//
//CX_AXIS_NONE<nl> <tab>No axis.<nl>
//CX_AXIS_AUTOMATIC<nl> <tab>An axis type is chosen in context with the graph type.<nl>
//CX_AXIS_CLASSIC<nl> <tab>The classic X-Y plot axis<nl>
//CX_AXIS_OSCILLOSCOPE<nl> <tab>+-X, +-Y for 2D plots<nl>
//CX_AXIS_PLATFORM_SE<nl> <tab>A 3/4 view platform seen from the "south-east"<nl>
//CX_AXIS_PLATFORM_SW<nl> <tab>A 3/4 view platform seen from the "south-west"<nl>
//CX_AXIS_STAGE_SE<nl> <tab>A 3/4 view stage seen from the "south-east"	<nl>
//CX_AXIS_STAGE_SW<nl> <tab>A 3/4 view stage seen from the "south-west"<nl>
//CX_AXIS_H_FRAME<nl> <tab>Rugby or American football goal posts (not yet implemented)<nl>
//CX_AXIS_PIE<nl> <tab>Circular display axis for standard or 3D pie charts<nl>
//CX_AXIS_YX<nl> <tab>Similar to the classic X-Y axis but with axes reversed so that the Y axis extends across the window<nl>
//CX_AXIS_ISO_CLASSIC<nl> <tab>Classic axis with pseudo 3D effect<nl>
//CX_AXIS_CLASSIC_RIGHT<nl> <tab>Classic axis with Y on the right<nl>
//CX_AXIS_ISO_CLASSIC_R<nl> <tab>Classic axis, pseudo 3D, Y axis on right<nl>
//CX_AXIS_WEB<nl> <tab>Web chart axis<nl>
//CX_AXIS_XYSCATTER<nl> <tab>Scatter graph axis<nl>
//CX_AXIS_ISO_CLASSIC_YX<nl> <tab>Iso classic for horizontal graphs<nl>
//CX_AXIS_POLAR<nl> <tab>Polar chart axes<nl>
//CX_AXIS_DATE<nl> <tab>Classic axis with date scale<nl>  
//CX_AXIS_DATE_R<nl> <tab>Classic axis with date scale on the right<nl>
//CX_AXIS_ISO_DATE<nl> <tab>Iso classic axis with date scale<nl>
//CX_AXIS_ISO_DATE_R<nl> <tab>Iso classic axis with date scale on the right<nl>
//CX_AXIS_ISO_DATE_YX<nl> <tab>Iso classic axis with date scale on a YX axis<nl>
//CX_AXIS_DATE_YX<nl> <tab>Classic axis with date scale on YX axis<nl>  
//CX_AXIS_GANTT_VALUE<nl> <tab>Gantt chart axis, value scale<nl>
//CX_AXIS_GANTT_DATE<nl> <tab>Gantt chart axis, date scale<nl>
//CX_AXIS_SCATTER_DATEX<nl> <tab>Scatter axis with a date scale on the X axis<nl>
//CX_AXIS_SCATTER_DATEY<nl> <tab>Scatter axis with a date scale on the Y axis<nl>
//CX_AXIS_USER<nl> <tab>User defined axis styles lie in the range c0xxxxxx to ffxxxxxx. All other values are reserved.

//@topic Feature masks | Select various chart features <nl>
//Settings are all single bit semaphores.<nl>
//See <md SRGraphStyle::m_dwStyleA>, <md SRGraphStyle::m_dwStyleB>.
//
//m_dwStyleA:
//CX_AUTO_ORIENTATION_MASK =0x80000000<nl>	Determines if labels of an axis in compound component are set perpendicular to axis line
//CX_SIZE_MASK			=	0x40000000<nl>	Determines if the maximum object size is to be used <mf SRGraphStyle::SetUseMaxSize> <mf SRGraphStyle::GetUseMaxSize><nl>
//CX_FILL_AXIS_MASK		=	0x20000000<nl>	Enables or disables the filling of the areas covered by axes <mf SRGraphStyle::SetAxisFillStyle> <mf SRGraphStyle::GetAxisFillStyle><nl>
//CX_SHADE_OBJECT_MASK	=	0x10000000<nl>	Sets or resets the shading semaphore for certain objects or graph types <mf SRGraphStyle::SetObjectShadeStyle> <mf SRGraphStyle::GetObjectShadeStyle><nl>
//CX_LOG_SCALE_MASK		=	0x08000000<nl>	Enables the logarithmic scale conversions <mf SRGraphStyle::SetLog> <mf SRGraphStyle::GetLog><nl>
//CX_MAX_SCALE_MASK		=	0x04000000<nl>	(Display specific) If enabled the graph will not auto-scale. <mf SRGraphStyle::SetUseMaxScale> <mf SRGraphStyle::GetUseMaxScale><nl>
//CX_EMPTY_GRAPH_MASK	=	0x02000000<nl>	When enabled and the graph holds either no or null data, a symbol is shown signifying an empty graph. <mf SRGraphStyle::SetUseEmptyGraph> <mf SRGraphStyle::GetUseEmptyGraph><nl>
//CX_HIDE_NUMERALS_MASK	=	0x01000000<nl>	Show or hide the numeric scale on a graph axis <mf SRGraphStyle::SetShowNumerals> <mf SRGraphStyle::GetShowNumerals><nl>
//CX_HIDE_INDICES_MASK	=	0x00800000<nl>	Show or hide the indices on a graph axis <mf SRGraphStyle::SetShowIndices> <mf SRGraphStyle::GetShowIndices><nl>
//CX_HIDE_GROUPS_MASK	=	0x00400000<nl>	Show or hide the groups on a graph axis <mf SRGraphStyle::SetShowGroups> <mf SRGraphStyle::GetShowGroups><nl>
//CX_LEGEND_LINE_MASK	=	0x00020000<nl>	Switches between line keys and filled box keys on legends <mf SRGraphStyle::SetLegendLine> <mf SRGraphStyle::SetLegendLine><nl>
//CX_HIDE_XGRID_MASK	=	0x00010000<nl>	When TRUE no X gridlines are shown <nl>
//CX_HIDE_YGRID_MASK	=	0x00008000<nl>	When TRUE no Y gridlines are shown <nl>
//CX_HIDE_ZGRID_MASK	=	0x00004000<nl>	When TRUE no Z gridlines are shown <nl>
//CX_HIDE_ZERO_MASK		=	0x00002000<nl>	If set the zero will only be visible if it is within the minimum and maximum range<nl>
//CX_HIDE_XTICKS_MASK	=	0x00001000<nl>	When TRUE no x tick marks are shown<nl>
//CX_HIDE_YTICKS_MASK	=	0x00000800<nl>	When TRUE no y tick marks are shown<nl> 
//CX_HIDE_ZTICKS_MASK	=	0x00000400<nl>	When TRUE no z tick marks are shown<nl> 
//CX_SORT_VALUES_MASK	=	0x00000200<nl>	When TRUE the group in Manhattan and Rooftop graphs are sorted by average group value <mf SRGraphStyle::SetSort><nl>
//CX_OVERLAY_GRID_MASK	=	0x00000100<nl>	When TRUE the grid will overlay the drawn data<nl>
//CX_DISPLAYLOCK_MASK	=	0x00000080<nl>	When TRUE the m_DisplayRect rectangle of the owning SRGraphDisplay will never automatcally resize<nl> 
//CX_MINORTICKS_MASK	=	0x00000040<nl>	When TRUE minor tick marks are drawn<nl>
//CX_TIER_XLABELS_MASK	=	0x00000020<nl>	When TRUE X axis labels are "tiered" to prevent overlap<nl>
//CX_TIER_YLABELS_MASK	=	0x00000010<nl>	When TRUE Y axis labels are "tiered" to prevent overlap<nl>
//CX_LEGEND_KEYFIRST_MASK	=	0x00000008<nl>	When TRUE legend keys are placed to left of text<nl>
//CX_SCALE_LIMIT_MASK	=	0x00000004<nl>	When TRUE the axis range is limited<nl>
//CX_LEGEND_LOCK_RC_MASK	=	0x00000002<nl>	When TRUE the legend rectangle is locked<nl>
//CX_DEFER_DRAW_MASK	=	0x00000001<nl>	When TRUE drawing of object is deferred until after other objects<nl>
//
//m_dwStyleB:
//CX_LOG_SCALE_X_MASK	=	0x80000000<nl>	Differentiates between log/log and log/lin charts<nl>
//CX_XLCOMP_MASK		=	0x40000000<nl>	Displays xlabels in a compatible style to those in OC 1.01<nl> 
//CX_HGRAPH_MASK		=	0x20000000<nl>	Defines compound charts as YX types and swaps the axis usage<nl>
//CX_CULLPOINTS_MASK	=	0x10000000<nl>	Signifies that points may be culled to speed drawing<nl>
//
// Stingray reserves all other bits in the m_dwStyleB variable.<nl>

//@topic Legend styles | Determine which data is displayed in the legend<nl>
//Use <mf SRGraphStyle::SetLegendStyle> and <mf SRGraphStyle::GetLegendStyle>.<nl>
//See <md SRGraphStyle::m_dwStyleB>.
//
//CX_LEGEND_NONE<nl> <tab>No legend.<nl>
//CX_LEGEND_AUTOMATIC<nl> <tab>Legend style is chosen according to graph context.<nl>
//CX_LEGEND_BY_INDEX<nl> <tab>Uses index headers to annotate legend<nl>
//CX_LEGEND_BY_GROUP<nl> <tab>Uses group headers to annotate legend<nl>
//CX_LEGEND_BY_RECTANGLE<nl> <tab>Uses individual annotations<nl>
//CX_LEGEND_HEAD_GROUP<nl> <tab>Titles the legend by group and uses indices to annotate<nl>
//CX_LEGEND_HEAD_INDEX<nl> <tab>Titles the legend by index and uses groups to annotate<nl>
//CX_LEGEND_USER<nl> <tab>User legend styleslie in the range xxxxxxc0 to xxxxxxff.  All other values are reserved.<nl>

//@topic Legend key styles | Determine the appearance of legend keys<nl>
//Use <mf SRGraphStyle::SetLegendKeyStyle> and <mf SRGraphStyle::GetLegendKeyStyle>.<nl>
//See <md SRGraphStyle::m_dwStyleC>.
//
//CX_KEY_NONE<nl>
//CX_KEY_AUTOMATIC<nl>
//CX_KEY_LINE<nl>
//CX_KEY_BOX<nl>
//CX_KEY_WIGET<nl>
//CX_KEY_DATA<nl>
//CX_KEY_CUSTOM<nl>

//@topic Border styles | Determine the appearance of the border drawn around the component rectangle<nl>
//Use <mf SRGraphStyle::SetComponentBorderStyle> and <mf SRGraphStyle::GetComponentBorderStyle><nl>
//See <md SRGraphStyle::m_dwComponentStyle>
//
//CX_NO_BORDER<nl>
//CX_THIN_RAISED_BORDER<nl>
//CX_THIN_SUNKEN_BORDER<nl>
//CX_THIN_3D_BORDER<nl>
//CX_THICK_RAISED_BORDER<nl>
//CX_THICK_SUNKEN_BORDER<nl>
//CX_THICK_3D_BORDER<nl>
//CX_LINE_BORDER<nl>
//CX_USER_BORDER<nl><nl>

//@topic Shadow styles | Determine the shadow drawn around the component rectangle<nl>
//Use <mf SRGraphStyle::SetComponentShadowStyle> and <mf SRGraphStyle::GetComponentShadowStyle>.<nl>
//See <md SRGraphStyle::m_dwComponentStyle>.
//
//CX_NO_SHADOW<nl>
//CX_THIN_SHADOW<nl>
//CX_MEDIUM_SHADOW<nl>
//CX_THICK_SHADOW<nl>
//CX_USER_SHADOW<nl><nl>

//@topic Background styles | Determine how the interior of the component retangle is filled<nl>
//Use <mf SRGraphStyle::GetComponentFillStyle> and <mf SRGraphStyle::SetComponentFillStyle>.<nl>
//See <md SRGraphStyle::m_dwComponentStyle>.
//
//CX_NO_FILL<nl>
//CX_SOLID_FILL<nl>
//CX_VERTICAL_FILL<nl>
//CX_HORIZONTAL_FILL<nl>
//CX_ANGLE_FILL<nl>
//CX_RESOURCE_FILL<nl>
//CX_IMAGE_FILL (not currently implemented)<nl>
//CX_USER_FILL<nl><nl> 

//@topic Component types | Identify the type of object which owns the SRGraphStyle variable <nl>
//Use <mf SRGraphStyle::GetType> and <mf SRGraphStyle::SetType>.<nl>
//See <md SRGraphStyle::m_dwStyleC>.
//
//CX_TYPE_NONE<nl>		
//CX_TYPE_COMPONENT<nl>	
//CX_TYPE_OBJECT<nl>			
//CX_TYPE_GRAPH<nl>			
//CX_TYPE_DISPLAY<nl>		
//CX_TYPE_LEGEND<nl>		
//CX_TYPE_TITLE<nl>
//CX_TYPE_LABEL<nl>
//CX_TYPE_LABELBLOCK<nl>
//CX_TYPE_DSCALE<nl>
//CX_TYPE_LOGSCALE<nl>
//CX_TYPE_DATESCALE<nl><nl>

//@topic Component type strings | Identify the type of object <nl>
//Set by component constructor and returned by <mf SRGraphComponent:GetType><nl>
//
//IDS_SRG_COMPONENTTYPE <tab>Component
//IDS_SRG_BACKGROUNDTYPE <tab>Background
//IDS_SRG_DISPLAYTYPE <tab>Display
//IDS_SRG_TITLETYPE <tab>Title
//IDS_SRG_LEGENDTYPE <tab>Legend
//IDS_SRG_LABELTYPE <tab>Label
//IDS_SRG_LABELBLOCKTYPE <tab>Label block
//IDS_SRG_TEXTPANELTYPE <tab>Text panel
//IDS_SRG_DATAWATCHERTYPE <tab>Data watcher
//IDS_SRG_COMPOUNDCOMPONENTTYPE <tab>Compound component
//IDS_SRG_COMPOUNDDISPLAYTYPE <tab>Compound display
//IDS_SRG_AXISMANAGERTYPE <tab>Axis manager
//IDS_SRG_GRIDLINETYPE <tab>Grid lines
//IDS_SRG_TICKMARKTYPE <tab>Tick marks
//IDS_SRG_DECIMALSCALETYPE <tab>Decimal scale
//IDS_SRG_LOGSCALETYPE <tab>Log scale
//IDS_SRG_INDEXSCALETYPE <tab>Index scale
//IDS_SRG_GROUPSCALETYPE <tab>Group scale
//IDS_SRG_DATESCALETYPE <tab>Date scale
 
//@topic Label styles | Particularly used on pie charts to show information normally shown on the axes of other graphs<nl>
//Use <mf SRGraphStyle::SetLabelStyle> and <mf SRGraphStyle::GetLabelStyle>.<nl>
//See <md SRGraphStyle::m_dwStyleC>.
//
//CX_LABEL_NONE<nl> <tab>No labels<nl>				
//CX_LABEL_AUTOMATIC<nl> <tab>Label style is chosen in context with the graph type.<nl>			
//CX_LABEL_VALUE<nl> <tab>The label is the numeric value.<nl>			
//CX_LABEL_PERCENT<nl> <tab>The label is the percentage of the current value in relation to the sum of all values in the graph.<nl>		
//CX_LABEL_VALUE_PERCENT<nl> <tab>Combination of LABEL_VALUE and LABEL_PERCENT<nl>
//CX_LABEL_TEXT<nl> <tab>The label is the annotation from the data item.<nl>		
//CX_LABEL_TEXT_VALUE<nl> <tab>Combination of LABEL_VALUE and LABEL_TEXT<nl>	
//CX_LABEL_TEXT_VALUE_PERCENT<nl> <tab>Combination of LABEL_TEXT, LABEL_VALUE, and LABEL_PERCENT<nl>
//CX_LABEL_TEXT_PERCENT<nl> <tab>Combination of LABEL_TEXT and LABEL_PERCENT<nl><nl>	
//CX_LABELBLOCK_HIDELABELS<nl> <tab>Used on label blocks to hide labels which would otherwise overprint another (quickest method for lots of labels)<nl>
//CX_LABELBLOCK_MOVELABELS<nl> <tab>Used on label blocks to stack labels in a multi-tier fashion (slower but neat and with all the labels shown)<nl>

//@topic Highlight styles for pie wedges | A highlight setting will "explode" the wedge from the pie.<nl> 
//Use <mf SRGraphStyle::SetHighlight> and  <mf SRGraphStyle::GetHighlight>.<nl>
//See <md SRGraphStyle::m_dwStyleC>.
//
//CX_HIGHLIGHT_NONE<nl><nl>		
//CX_HIGHLIGHT_AUTOMATIC<nl> <tab>A highlight is chosen in context with the graph style.<nl>	
//CX_HIGHLIGHT_SMALL<nl> <tab>The wedge is exploded 5% of the radius of the pie.<nl>		
//CX_HIGHLIGHT_MEDIUM<nl> <tab>The wedge is exploded 10% of the radius of the pie.<nl>		
//CX_HIGHLIGHT_LARGE<nl> <tab>The wedge is exploded 20% of the radius of the pie.<nl>
//CX_HIGHLIGHT_CUSTOM<nl> <tab>See <mf SRGraphDisplay::DrawIsoPieData> routine for handling methods<nl><nl>

//@topic Alignment codes for printing | Sets up pagination of the graph
//See <md SRGraph::m_dwAlignInDC>.
//
//Vertical alignment codes are...<nl>
//		CX_ALIGN_NONE<nl>
//		CX_ALIGN_VTOP<nl>
//		CX_ALIGN_VCENTER<nl>
//		CX_ALIGN_VBOTTOM<nl>
//		CX_ALIGN_VCUSTOM<nl> 
//Horizontal alignment codes are...<nl>
//		CX_ALIGN_NONE<nl>
//		CX_ALIGN_HLEFT<nl>
//		CX_ALIGN_HCENTER<nl>
//		CX_ALIGN_HRIGHT<nl>
//		CX_ALIGN_HCUSTOM<nl> 


