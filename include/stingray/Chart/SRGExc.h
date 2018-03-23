///////////////////////////////////////////////////////////////////////////////
// SRGExc.h
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
//@doc SRGraphException
//@module SRGExc.h | SRGraphException header file<nl>
//Written by Bob Powell (www.roguewave.com)

////////////////////////////////////////////////////////////////
//
// SRGExc.h: Declaration of the SRGraphException class
//
////////////////////////////////////////////////////////////////
#ifndef __SRGRAPHEXCEPTION__
#define __SRGRAPHEXCEPTION__

#ifdef _OBJCHART_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OC_DATA
#endif

#include <StingrayExportDefs.h>

//@doc SRGraphException

//@mdata int | SRGraphException | m_nCause | Holds the cause of the current exception<nl>
//May be one of...<nl>
//none				No cause was given<nl>
//generic			An undefined error occurred.<nl>
//group				An attempt was made to access a non-existent group.<nl>
//index				An attempt was made to access a non-existent index.<nl>
//null				A required data item was marked as null data.<nl>
//dynamic			A dynamic data error occurred.<nl>
//dynamicType		An attempt to use a data type not consistent with other dynamic data was attempted.<nl>
//dynamicNotready	An attempt was made to send data to an un-initialized dynamic data store.<nl>
//component			A component error occurred.<nl>
//fillstyle			An error occurred while reading a fill style from a template.<nl>
//font				An error occurred while reading a font descriptor from a template.<nl>
//legend			An error occurred while reading a legend descriptor from a template<nl>
//data				An error occurred while reading a data descriptor from a template.<nl>
//command			A template command was not recognized.<nl>
//border			An error occurred while reading a border descriptor from a template.<nl>
//type				An unknown type has been found in a component.<nl>
//syntax			A syntax error occurred while reading a template.<nl>
//label				The placement of a label has reduced the drawing surface to zero.<nl>
//drawing			A function requiring a valid m-pCWnd or m_pDC was called while the graph was not drawing.<nl>
//polygon			An error occurred while loading a polygon resource.<nl>
//wiget				An error occurred while loading a wiget resource.<nl>
//graphtype			A graph type was used that is not suitable for the type or range of data.<nl>
//logscale			The data in the graph were not suitable for use on a logarithmic scale.<nl>
//odd				An odd number of data items exists, but an even number is required.<nl>

CHART_API void SRThrowGraphException(int cause);

//$head The chart exception class
//$level 1

//@class Exception class for SRGraph
//@base public | CException
class SRGraphException : public CException
{
public:
	//@cmember
	/* Called to allow user exception handling*/
	CHART_API virtual UINT UserExceptionID();

	//@cmember
	/* Construction*/
	CHART_API SRGraphException(int cause=0);

	CHART_DECLARE_DYNCREATE(SRGraphException);

	//@cmember
	/* Displays the message associated with the current exception code*/
	CHART_API void ShowErrorMessage();
	
	//@cmember
	/* Override of the CException::GetErrorMessage function -- uses strings defined in the SRGraphResource (SRGRES.RC) file*/
	CHART_API virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext=NULL);

	enum {
		none=0,
		genericException,
		// data access exceptions
		group,
		index,
		dynamic,
		dynamicType,
		dynamicNotready,
		null,
		// template exceptions
		component,
		fillstyle,
		font,
		legend,
		data,
		command,
		border,
		type,
		syntax,
		//drawing eceptions
		label,
		drawing,
		//resource exceptions
		polygon,
		wiget,
		//configuration exceptions
		graphtype,
		//range exceptions
		logscale,
		odd
	}  ;

	//@cmember
	/* Cause of the exception*/
	int m_nCause;

//@access protected member functions
protected:
	//@cmember
	/* Fetches the correct resource ID for the error*/
	CHART_API virtual UINT GetErrorID();
};

// Reset DLL declaration context

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif //__SRGRAPHEXCEPTION__
