///////////////////////////////////////////////////////////////////////////////
// SRGraphBackground.h
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
//@doc SRGraphComponent
//@module SRGComp.h|  definition of the graph component classes<nl>
//SRGraphComponent, SRGraphRect, SRGraphTitle, SRGraphBackground, SRGraphDisplay, SRGraphLabel, SRGraphLabelBlock, SRGraphLegend<nl>
//and structures GESorter and PointSorter<nl>
//Written by Bob Powell (www.roguewave.com)

/////////////////////////////////////////////////////////////
//
// SRGComp.h: definition of the graph component classes
//
/////////////////////////////////////////////////////////////
#ifndef __SRGRAPHBACKGROUND__
#define __SRGRAPHBACKGROUND__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

////////////////////////////////////////////////////////
// Autoduck comment block for SRGraphBackground
//
//@doc SRGraphBackground

//@doc SRGraphBackground
//@mfunc virtual void  | SRGraphBackground | DrawForeground | Does nothing -- background does not have a foreground

//adinsert SRGraphBackground
//$head Component classes
//$level 1

//@doc SRGraphBackground
//@class Based on SRGraphComponent, this class handles painting of the background.
//@base public | SRGraphComponent
class SRGraphBackground : public SRGraphComponent
{
//@access public member functions
public:
	//@cmember
	/* Constructor*/
	CHART_API SRGraphBackground();
	
#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	
	//@cmember
	/* Reads a line from the template file*/
	CHART_API virtual int ReadTemplateLine(LPCTSTR line);
	//@cmember
	/* Writes the name to the template file.*/
	CHART_API virtual void WriteName(CStdioFile* file);

#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE

	CHART_DECLARE_SERIAL(SRGraphBackground);

//@access protected member functions
protected:
	//@cmember
	/* Overridden from base class -- does nothing because backgrounds don't have foregrounds*/
	CHART_API virtual void DrawForeground();

	// XML Formatter for SRGGraphBackground
	friend class SRGGraphBackgroundFTR;
};

// Reset DLL declaration context
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGRAPHBACKGROUND__

