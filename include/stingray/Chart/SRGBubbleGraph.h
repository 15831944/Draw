///////////////////////////////////////////////////////////////////////////////
// SRGBubbleGraph.h
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
//@doc SRGBubbleGraph
//@module SRGBubbleGraph.h|  definition of the Bubble Graph display class<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGBubbleGraph.h: definition of the Bubble Graph display class
//
/////////////////////////////////////////////////////////////
#ifndef __SRGBubbleGraph__
#define __SRGBubbleGraph__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGBubbleGraph
//
//@doc SRGBubbleGraph
// adinsert SRGBubbleGraph
////////////////////////////////////////////////////////

//@doc SRGBubbleGraph
//@class The graph display component specialized for Bubble charts<nl> 
//Bubble charts use the same axis drawing system as XY scatter charts.<nl> 
//Inherits basic graph component functions from SRGDisplayBase, and 
//component and font capabilities from SRGraphTitle
//@base public | SRGDisplayBase
//@devnote This class defines all of SRGDisplayBase's PrepareXXX, DrawXXXAxis, DrawXXXLabels, 
//and DrawXXXData functions, but only the Bubble chart functions do anything useful.
//@see <c SRGraphDisplay> and <c SRGDisplayBase> for description of functions unused by this class.
class SRGBubbleGraph : public SRGDisplayBase
{
	CHART_DECLARE_SERIAL(SRGBubbleGraph);

	
//@access Public member functions
public:

	//@cmember Constructor
	CHART_API SRGBubbleGraph();

	//@cmember Virtual destructor for this class
	CHART_API virtual ~SRGBubbleGraph();

//@access Protected member functions
protected:

	//@cmember Prepares the display component for drawing
	CHART_API virtual void PrepareDisplay();//

	//@cmember Calculates X and Y scale information for Bubble graphs
	CHART_API virtual void PrepareBubble();//

	//@cmember Draws Bubble data
	CHART_API virtual void DrawBubbleData();//

	//@cmember Draws X,Y scatter labels
	CHART_API virtual void DrawScatterLabels();//

	//@cmember Draws X,Y scatter axes 
	CHART_API virtual void DrawScatterAxis();//
	
	//@cmember Called to draw standard X,Y axes - called by DrawScatter Axis
	CHART_API virtual void DrawClassicAxis();//

	// XML Formatter for SRGBubbleGraph
	friend class SRGBubbleGraphFTR;

};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGBubbleGraph_