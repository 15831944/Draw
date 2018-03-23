///////////////////////////////////////////////////////////////////////////////
// SRGIsoBarGraph.h
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
//@doc SRGIsoBarGraph
//@module SRGIsoBarGraph.h|  definition of the IsoBar graph display class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGIsoBarGraph.h: definition of the IsoBar graph display class
//
/////////////////////////////////////////////////////////////
#ifndef __SRGIsoBarGraph__
#define __SRGIsoBarGraph__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGIsoBarGraph
//
//@doc SRGIsoBarGraph
// adinsert SRGIsoBarGraph
////////////////////////////////////////////////////////

//@doc SRGIsoBarGraph
//@class Performs data drawing for IsoBar graph type<nl>
//Inherits axis drawing abilities from SRGStageAxisBase, 
//basic graph component functions from SRGDisplayBase, and 
//component and font capabilities from SRGraphTitle
//@base public | SRGStageAxisBase
//@devnote All PrepareXXX, DrawXXXAxis, and DrawXXXLabels routines are defined in SRGClassicAxisBase. 
//This class defines all DrawXXXData functions -- only the DrawIsoBarData function does anything useful.
//@see <c SRGraphDisplay> and <c SRGDisplayBase> for description of functions unused by this class.
class SRGIsoBarGraph : public SRGStageAxisBase
{
	CHART_DECLARE_SERIAL(SRGIsoBarGraph);

//@access Public member functions
public:

	//@cmember Constructor
	CHART_API SRGIsoBarGraph();

	//@cmember Virtual destructor for this class
	CHART_API virtual ~SRGIsoBarGraph();

//@access Protected member functions
protected:

	//@cmember Draws "Manhattan" bars
	CHART_API virtual void DrawIsoBarData();

	//@cmember Draws vertical bar chart data (used to plot data with neg values)
	CHART_API virtual void DrawVBarData();

	// XML Formatter for SRGIsoBarGraph
	friend class SRGIsoBarGraphFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGIsoBarGraph__