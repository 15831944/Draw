///////////////////////////////////////////////////////////////////////////////
// SRGIndexBar.h
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

#if !defined(AFX_SRGINDEXBAR_H__8319F186_C754_11D2_B341_006008AF1D5D__INCLUDED_)
#define AFX_SRGINDEXBAR_H__8319F186_C754_11D2_B341_006008AF1D5D__INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//$head Specialized scale classes
//$level 2

/////////////////////////////
// AutoDuck tag block block for SRGIndexBar 
//@doc SRGIndexBar
//@mdata BOOL  | SRGIndexBar | m_bNodeAdjust | When TRUE the bar will place its nodes according to the line-chart pattern. When FALSE nodes will be places according to bar-chart patterns.

//@doc SRGIndexBar
//@mfunc void  | SRGIndexBar | SetNodeAdjust | Sets the <md SRGIndexBar::m_bNodeAdjust> variable. See the definition of this variable for full details. 
//@parm BOOL  | b | TRUE to turn on node adjustment.

//@doc SRGIndexBar
//@mfunc BOOL  | SRGIndexBar | GetNodeAdjust | Gets the <md SRGIndexBar::m_bNodeAdjust> variable. See the definition of this variable for full details. 

//@topic SRGIndexBar Class Overview |
//This class is a scale-bar object that displays data index text. See <c SRGScaleBar> for more details.

// adinsert AutoDuck insertion point for SRGIndexBar 
//@doc SRGIndexBar 
//@class SRGIndexBar is a scale-bar based class that displays axis scale information seperately from the display. It may be used to add multiple independant axis scales to displays.
//@base public | SRGScaleBar
class SRGIndexBar : public SRGScaleBar 
{
	CHART_DECLARE_SERIAL(SRGIndexBar)

	//@cmember
	/* The node adjustment variable */
	BOOL m_bNodeAdjust; 

public:
	//@cmember
	/* Create axis labels and tick marks position */
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Do the final setting for this axis before drawing */
	CHART_API virtual void BeforeDraw();
	//@cmember
	/* Sets the node adjustment variable */
	inline void SetNodeAdjust(BOOL b = TRUE) { m_bNodeAdjust = b; }
	//@cmember
	/* Returns the node adjustment setting */
	inline BOOL GetNodeAdjust() { return m_bNodeAdjust; }
	//@cmember
	/* Constructor */
	CHART_API SRGIndexBar();
	//@cmember
	/* Virtual destructor */
	CHART_API virtual ~SRGIndexBar();

	// XML Formatter for SRGIndexBar
	friend class SRGIndexBar;
};


/////////////////////////////
// AutoDuck tag block block for SRGGroupBar 

//@topic SRGGroupBar Class Overview |
//The SRGGroupBar object is a component that can be used to add a scale bar which displays group annotations. The base class (<c SRGScaleBar>) has details of the basic operations of this family of objects.


// adinsert AutoDuck insertion point for SRGGroupBar 
//@doc SRGGroupBar 
//@class The SRGGroupBar is a scale-bar object used to display group annotations.
class SRGGroupBar : public SRGIndexBar
{
	CHART_DECLARE_SERIAL(SRGGroupBar)

public:
	//@cmember
	/* Create axis labels and tick marks position */
	CHART_API virtual void CreateLabels();
	//@cmember
	/* Constructor */
	CHART_API SRGGroupBar();
	//@cmember
	/* Virtual destructor. */
	CHART_API virtual ~SRGGroupBar();

	// XML Formatter for SRGGroupBar
	friend class SRGGroupBar;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(AFX_SRGINDEXBAR_H__8319F186_C754_11D2_B341_006008AF1D5D__INCLUDED_)
