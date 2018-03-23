///////////////////////////////////////////////////////////////////////////////
// SRGStrataVBarGraph.h
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
//@doc SRGStrataVBarGraph
//@module SRGStrataVBarGraph.h | definition of the Strata VBar graph display class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGStrataVBarGraph.h: definition of the Strata VBar graph display class
//
/////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGStrataVBarGraph__
#define __SRGStrataVBarGraph__

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGStrataVBarGraph
//
//@doc SRGStrataVBarGraph
// adinsert SRGStrataVBarGraph
////////////////////////////////////////////////////////

//@doc SRGStrataVBarGraph
//@class Performs data drawing for Strata Vertical Bar and Strata Vertical Bar Group graph types<nl>
//Inherits axis drawing abilities from SRGVBarAxisBase, 
//basic graph component functions from SRGDisplayBase, and 
//component and font capabilities from SRGraphTitle
//@base public | SRGVBarAxisBase
//@devnote All PrepareXXX, DrawXXXAxis, and DrawXXXLabels routines are defined in SRGVBarAxisBase. 
//This class defines all DrawXXXData functions -- only the DrawStrataVBarData, DrawStrataVBarGData, and DrawVBarData do anything useful.
//It also overrides PrepareDisplay, PrepareStrataBar, and PrepareStrataBarG functions.
//@see <c SRGraphDisplay> and <c SRGDisplayBase> for description of functions unused by this class
class SRGStrataVBarGraph : public SRGVBarAxisBase
{
	CHART_DECLARE_SERIAL(SRGStrataVBarGraph);

//@access Public member functions
public:

	//@cmember Constructor
	CHART_API SRGStrataVBarGraph();

	//@cmember Virtual destructor for this class
	CHART_API virtual ~SRGStrataVBarGraph();

//@access Protected member functions
protected:
	//@cmember Prepares the display component for drawing
	CHART_API virtual void PrepareDisplay();//

	//@cmember Do some pre-initialization for the strata bar( one index/per bar )
	CHART_API virtual void PrepareStrataBar();//

	//@cmember Do some pre-initialization for the strata bar( one group/ per bar )
	CHART_API virtual void PrepareStrataBarG();//

	//@cmember Draw a strata vbar label with the group header as the label text of each bar
	CHART_API virtual void DrawStrataVBarGLabels();//

	//@cmember Draw strata vbar(data with the same index of different group on the same bar)
	CHART_API virtual void DrawStrataVBarData();//

	//@cmember Draw a strata vbar with each group on one bar
	CHART_API virtual void DrawStrataVBarGData();//

	//@cmember Draws vertical bar chart data - used if data contains neg values
	CHART_API virtual void DrawVBarData();//

	// XML Formatter for SRGStrataVBarGraph
	friend class SRGStrataVBarGraphFTR;
};

#endif //__SRGStrataVBarGraph__

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
