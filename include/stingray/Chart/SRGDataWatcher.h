///////////////////////////////////////////////////////////////////////////////
// SRGDataWatcher.h
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
//@doc SRGDataWatcher
//@module SRGDataWatcher.h | SRGDataWatcher header file<nl>
//Written by Bob Powell (www.roguewave.com)

////////////////////////////////////////////////////////////////
//
// SRGDataWatcher.h: interface for the SRGDataWatcher class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_SRGDATAWATCHER_H_INCLUDED_)
#define _SRGDATAWATCHER_H_INCLUDED_

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block for SRGDataWatcher 

//@doc SRGDataWatcher
//@mfunc void  | SRGDataWatcher | SetScanType | Sets the type of scan to be used 
//@parm int  | n | Scan type...<nl>
//0 = above limit <nl>
//1 = below limit <nl>
//2 = average above limit <nl>
//3 = average below limit <nl>
//4 = out of bracket <nl>
//5 = in bracket <nl>
//6 = average out of bracket <nl>
//7 = average in bracket <nl>

//@mfunc int  | SRGDataWatcher | GetScanType | Returns the scan type

//@mfunc void  | SRGDataWatcher | SetLinkToDisplay | Sets a flag linking the watcher to the next display 
//component in the list
//@parm BOOL  | b | TRUE to set the link
//@rem This only applies to items on the main component list -- 
//data watchers in the compound display are handled by their respective axis managers.

//@mfunc BOOL  | SRGDataWatcher | GetLinkToDisplay | Returns the display linking flag

//@mfunc void  | SRGDataWatcher | SetHighLimit | Sets the value of the high limit 
//@parm double | d | Number for the upper limit

//@mfunc void  | SRGDataWatcher | SetLowLimit | Sets the value for the lower limit
//@parm double | d | Number for the lower limit

//@mfunc double  | SRGDataWatcher | GetHighLimit | Returns the value for the high limit

//@mfunc double  | SRGDataWatcher | GetLowLimit | Returns the value for the low limit

//@mfunc void  | SRGDataWatcher | SetVisible | Sets the visibility of this data watcher<nl>
//If visible (TRUE) then the data watcher will draw a control limit line in the m_DisplayRect rectangle.
//@parm BOOL  | v | TRUE to make this watcher visible

//@mfunc BOOL  | SRGDataWatcher | GetVisible | Returns the visibility flag

//@mdata BOOL  | SRGDataWatcher | m_bVisible | Visibility flag<nl>
//When TRUE, line is drawn to indicate the control limit.

//@mdata BOOL  | SRGDataWatcher | m_bLinkToDisplay | Display link flag<nl>
//When TRUE this watcher will link its scope to the next available display.

//@mdata double  | SRGDataWatcher | m_dHighLimit | High limit value

//@mdata double  | SRGDataWatcher | m_dLowLimit | Low limit value

//@mdata int  | SRGDataWatcher | m_nScanType | Scan type -- see <mf SRGDataWatcher::SetScanType>

// adinsert AutoDuck insertion point for SRGDataWatcher 

//$head Component classes
//$level 1

//@doc SRGDataWatcher 
//@class The SRGDataWatcher class provides a simple method for monitoring data levels and 
//triggering events or highlighting data should the scanned items exceed certain preset limits.
//@base public | SRGGridLines
class SRGDataWatcher : public SRGGridLines  
{
public:
	CHART_API void DrawExtra(); //To be added for 6.1 to draw watchers on displays.
	//@cmember
	/* Overridden to prevent the base class function from effecting this object*/
	CHART_API virtual void SetptrTickPointerList(CPtrList *p);
	//@cmember
	/* Saves or retrieves this data watcher via the archive*/
	CHART_API virtual void Serialize(CArchive &ar);
	//@cmember
	/* Removes the highlight from a data object if it no longer causes an excursion*/
	CHART_API virtual void UnmarkExcursion(int index,int group);
	//@cmember
	/* Flags an excursion for a particular data object -- must be overridden by your application if used*/
	CHART_API virtual void FlagExcursion(int index, int group);
#ifndef _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Writes the datawatcher parameters to a template*/
	CHART_API virtual void WriteSpecificParameters(CStdioFile *pFile);
	//@cmember
	/* Writes the name of this object to a template*/
	CHART_API virtual void WriteName(CStdioFile *pFile);
#endif	// _OC_DONT_SUPPORT_TEXT_TEMPLATE
	//@cmember
	/* Scans the data scope applying the current criteria and calls either DataInRange or DataExcursion*/
	CHART_API virtual void Draw(CDC *pDC,CWnd *pCWnd);
	CHART_DECLARE_SERIAL(SRGDataWatcher)
	//@cmember
	/* Construction*/
	CHART_API SRGDataWatcher();
	//@cmember
	/* Destruction*/
	CHART_API virtual ~SRGDataWatcher();
	//@cmember
	/* Sets the type of scan to be used */
	CHART_API virtual void SetScanType(int n);
	//@cmember
	/* Returns the scan type*/
	CHART_API virtual int GetScanType();
	//@cmember
	/* Set flag linking the watcher to the next display component in the list*/
	CHART_API virtual void SetLinkToDisplay(BOOL b);
	//@cmember
	/* Returns flag linking the watcher to a display component*/
	CHART_API virtual BOOL GetLinkToDisplay();
	//@cmember
	/* Sets the value of the high limit */
	CHART_API virtual void SetHighLimit(double d);
	//@cmember
	/* Sets the value of the low limit */
	CHART_API virtual void SetLowLimit(double d);
	//@cmember
	/* Returns the value of the high limit */
	CHART_API virtual double GetHighLimit();
	//@cmember
	/* Returns the value of the low limit */
	CHART_API virtual double GetLowLimit();
	//@cmember
	/* Sets the visibility flag*/
	CHART_API virtual void SetVisible(BOOL v);
	//@cmember
	/* Returns the visibility flag*/
	CHART_API virtual BOOL GetVisible();

protected:
	//@cmember
	/* Sets scan levels according to your own custom system*/
	CHART_API virtual void SetCustomScanLevels();
	//@cmember
	/* Draws a control limit line or lines on the chart -- if this object is a subcomponent */
	CHART_API virtual void DrawForeground();

	//@cmember
	/* Gets data scope from linked display component if m_bLinkToDisplay is set*/
	CHART_API virtual void GetWorkingScope();
	//@cmember
	/* Sets the highlight style of the data object that caused the excursion*/
	CHART_API virtual void MarkExcursion(int index, int group);
	//@cmember
	/* Override to signal an out-of-range event*/
	CHART_API virtual void DataExcursion();
	//@cmember
	/* Override to signal an in-range event*/
	CHART_API virtual void DataInRange();
	//@cmember
	/* Performs a data scan over the scope */
	CHART_API virtual void DataScan();

	//@cmember
	/* Performs data checking for "above limit" scan type*/
	CHART_API virtual BOOL ScanAboveLimit();
	//@cmember
	/* Performs data checking for "below limit" scan type*/
	CHART_API virtual BOOL ScanBelowLimit();
	//@cmember
	/* Performs data checking for "average above limit" scan type*/
	CHART_API virtual BOOL ScanAverageAboveLimit();
	//@cmember
	/* Performs data checking for "average below limit" scan type*/
	CHART_API virtual BOOL ScanAverageBelowLimit();
	//@cmember
	/* Performs data checking for "in bracket" scan type*/
	CHART_API virtual BOOL ScanInBracket();
	//@cmember
	/* Performs data checking for "out of bracket" scan type*/
	CHART_API virtual BOOL ScanOutOfBracket();
	//@cmember
	/* Performs data checking for "average in bracket" scan type*/
	CHART_API virtual BOOL ScanAverageInBracket();
	//@cmember
	/* Performs data checking for "average out of bracket" scan type*/
	CHART_API virtual BOOL ScanAverageOutOfBracket();
	//@cmember
	/* Performs data checking for custom scan types -- must be overriden if used*/
	CHART_API virtual BOOL ScanCustom();

	// data members
	//@cmember
	/* Visibility flag*/
	BOOL m_bVisible;
	//@cmember
	/* Flag linking the watcher to the next display component in the list*/
	BOOL m_bLinkToDisplay;
	//@cmember
	/* High limit value*/
	double m_dHighLimit;
	//@cmember
	/* Low limit value*/
	double m_dLowLimit;
	//@cmember
	/* Type of data checking to do*/
	int m_nScanType;

	// XML Formatter for SRGDataWatcher
	friend class SRGDataWatcherFTR;
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif // !defined(_SRGDATAWATCHER_H_INCLUDED_)
