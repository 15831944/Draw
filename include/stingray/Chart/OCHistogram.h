///////////////////////////////////////////////////////////////////////////////
// OCHistogram.h
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

//////////////////////////////////////////////////////////////////////////////////
//
// Objective Chart Utility Toolkit (OCUT) 
//
// Written by Bob Powell (www.roguewave.com)
//
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// The text comments in this file are formatted to generate
// a help file on build using Microsoft's free Autoduck tool.
// The help file is available with this source and it is
// recommended that you use this file in conjunction with the
// mfc help files.
//////////////////////////////////////////////////////////////////////////////////
#ifdef _OBJCHART_UT_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OCUT_DATA
#endif

#ifndef __OCUTITEM__
#define __OCUTITEM__

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block block for OCHistogram 


//@doc OCHistogram
//@mfunc virtual void  | OCHistogram | SetDataDivisions | Initializes the number of slots in the histogram<nl>
//Though the count of data items may be very large the number of slots needed may be quite small. For example an image 
//having 1024 * 768 pixels at 24 bits per pixel will have 786,432 pixels. To create a histogram of all the red pixels 
//will require 256 slots (one for each red-pixel brightness level) and a data count of 786,432 for the scan.
//@parm int  | v | The number of slots desired

//@doc OCHistogram
//@mfunc virtual int  | OCHistogram | GetDataDivisions | Returns the number of slots programmed for his histogram.

//@doc OCHistogram
//@mfunc virtual void  | OCHistogram | SetScanCount | Sets the number of data items to be considered in a single scan.
//@parm int  | v | The actual number of items to use

//@doc OCHistogram
//@mfunc virtual int  | OCHistogram | GetScanCount | Returns the number of items programmed for the scan

//@doc OCHistogram
//@mdata CScale  | OCHistogram | m_Scale | This scale is used to determine the full range of data used in the histogram. This scale is divided by 
//the number of slots to give the final value for each slot.

//@doc OCHistogram
//@mdata int  | OCHistogram | m_nScanCount | This data member sets the number of items to be scanned.

//@doc OCHistogram
//@mdata int  | OCHistogram | m_nDataDivisions | This sets the number of slots used in the histogram.

//@doc OCHistogram
//@mfunc CScale  | OCHistogram | GetScan | Returns the range of data values that have been added to scan.

// adinsert AutoDuck insertion point for OCHistogram 
//@doc OCHistogram 
//@class This class allows the simple generation of a histogram for any given set of data.<nl><nl>
//@head2 How to use this class.<nl><nl>|
//After the initial creation of the class SetDataDivisions should be called to initialize the number of slots in the chart.<nl>
//Then use SetScanCount to initialize the number of data items to be scanned. once this is accomplished each data item may be 
//added to the total by calling AddToScan once for each value. This process is used to ascertain the overall range of data in the set.<nl>
//When all data items have been scanned they are then processed by assigning them one by one to thier slots using the AddData function.<nl>
//The chart is drawn by the Paint() function in the base class.
class OCHistogram : public OCutItem 
{
public:
	//@cmember
	/* Removes data items from the scan and cleans the chart */
	CHART_UT_API virtual void Clear();
	//@cmember
	/* Adds the value to the scaling value */
	CHART_UT_API virtual void AddToScan(double d);
	//@cmember
	/* resets the data before the beginning of a scan. Does not reset the chart */
	CHART_UT_API virtual void ResetScan();
	//@cmember
	/* adds one data item to the scan. Data is assigned to the correct slot  */
	CHART_UT_API virtual void AddData(double d);
	//@cmember
	/* Creates the components for the chart. */
	CHART_UT_API virtual void SetupComponents();
	//@cmember
	/* removes data and initializes the correct number of indices */
	CHART_UT_API virtual void InitializeData();
	//@cmember
	/* constructor */
	CHART_UT_API OCHistogram();
	//@cmember
	/* destructor */
	CHART_UT_API virtual ~OCHistogram();
	//@cmember
	/* sets the number of data divisions to use in this histogram  */
	inline virtual void SetDataDivisions(int v){m_nDataDivisions=v;}
	//@cmember
	/* Returns the number of data divisions used in this histogram */
	inline virtual int GetDataDivisions(){return m_nDataDivisions;}
	//@cmember
	/* sets the number of items to be scanned */
	inline virtual void SetScanCount(int v){m_nScanCount=v;}
	//@cmember
	/* Returns the number of items to be scanned */
	inline virtual int GetScanCount(){return m_nScanCount;}
	//@cmember
	/* Expands data limits to "nice" numbers for display */
	CHART_UT_API virtual int FindLimits(CScale* pScale);
	//@cmember
	/* Returns the range of data that have been added to scan */
	inline CScale GetScan(){return m_Scale;}
	
protected:
	//@cmember
	/* The scale to use in determining the slots */
	CScale m_Scale;
	//@cmember
	/* The count of data items to be scanned */
	int m_nScanCount;
	//@cmember
	/* the number of data divisions in the histogram */
	int m_nDataDivisions;
};

#endif

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
