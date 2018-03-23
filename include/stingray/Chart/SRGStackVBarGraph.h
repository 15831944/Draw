///////////////////////////////////////////////////////////////////////////////
// SRGStackVBarGraph.h
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
//@doc SRGStackVBarGraph
//@module SRGStackVBarGraph.h|  definition of the Stacked Vertical Bar graph display class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGStackVBarGraph.h: definition of the Stacked Vertical Bar graph display class
//
/////////////////////////////////////////////////////////////

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#ifndef __SRGStackVBarGraph__
#define __SRGStackVBarGraph__

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGStackVBarGraph
//
//@doc SRGStackVBarGraph
// adinsert SRGStackVBarGraph
////////////////////////////////////////////////////////

//@doc SRGStackVBarGraph
//@class Performs data drawing for Stacked Vertical Bar graph type<nl>
//Inherits axis drawing abilities from SRGVBarAxisBase, 
//basic graph component functions from SRGDisplayBase, and 
//component and font capabilities from SRGraphTitle
//@base public | SRGVBarAxisBase
//@devnote All PrepareXXX, DrawXXXAxis, and DrawXXXLabels routines are defined in SRGClassicAxisBase. 
//This class defines all DrawXXXData functions -- only the DrawStackVBarData function does anything useful.
//@see <c SRGraphDisplay> and <c SRGDisplayBase> for description of functions unused by this class.
class SRGStackVBarGraph : public SRGVBarAxisBase
{
	CHART_DECLARE_SERIAL(SRGStackVBarGraph);

//@access Public member functions
public:

	//@cmember Constructor
	CHART_API SRGStackVBarGraph();

	//@cmember Virtual destructor for this class
	CHART_API virtual ~SRGStackVBarGraph();

//@access Protected member functions
protected:

	//@cmember Draws vertical stacked bars
	CHART_API virtual void DrawStackVBarData();

	// XML Formatter for SRGStackVBarGraph
	friend class SRGStackVBarGraphFTR;
};

#endif //__SRGStackVBarGraph__

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
