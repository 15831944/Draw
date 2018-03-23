///////////////////////////////////////////////////////////////////////////////
// OCCurveFit.h : interface for the OCCurveFit class.
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

#ifdef _OBJCHART_UT_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OCUT_DATA
#endif

#if !defined(AFX_OCCurveFit_H__027FBE84_FC77_11D1_B2DB_006008AF1D5D__INCLUDED_)
#define AFX_OCCurveFit_H__027FBE84_FC77_11D1_B2DB_006008AF1D5D__INCLUDED_

#include <StingrayExportDefs.h>

//@doc OCCurveFitChart
//@mdata int  | OCCurveFitChart | m_nFitType | Fit type (0 to 15)
//@mdata double  | OCCurveFitChart | m_dMaxX | Upper limit of X range to be used by curve fit
//@mdata double  | OCCurveFitChart | m_dMinX | Lower limit of X range to be used by curve fit
//@mdata BOOL  | OCCurveFitChart | m_bShowEquation | Flag set to show equation of fit in a title component
//@mdata CCurveFit  | OCCurveFitChart | m_CurveFit | Instance of CCurveFit class that contains code for computing the fits

/////////////////////////////
// AutoDuck tag block for OCCurveFitItem 

//@doc OCCurveFitItem 
//@class This class is part of Objective Chart's Utility Toolkit.  
//It accepts two buffers containing X and Y data, 
//computes a least squares curve fit of a specified form,
//and creates a chart plotting the raw data along with the fitted curve.
//The range of X values used to determine the fit can be specified.
//The equation and correlation coefficient of the fit can be optionally 
//display in a title component of the chart.  The title can be repositioned
//by dragging it with the right mouse button.
class OCCurveFitItem: public OCutItem  
{
public:
	//@cmember 
	/* Selects logarithmic or linear scaling for the X axis */
	CHART_UT_API void SetLogX(BOOL bLog);
	//@cmember 
	/* Selects logarithmic or linear scaling for the Y axis */
	CHART_UT_API void SetLogY(BOOL bLog);
	//@cmember 
	/* Returns the equation of the specified fit type */
	CHART_UT_API CString GetFitEquation(int nType);
	//@cmember 
	/* Returns a string describing the specified fit type */
	CHART_UT_API CString GetFitName(int nType);
	//@cmember 
	/* Returns the number of supported fit types */
	CHART_UT_API int GetFitTypeCount();
	
	//@cmember 
	/* Upper limit of X values to be considered when computing the fit */
	double	m_dMaxX;
	//@cmember 
	/* Lower limit of X values to be considered when computing the fit */
	double	m_dMinX;
	//@cmember 
	/* Desired fit type */
	int		m_nFitType;
	//@cmember 
	/* Flag to show the equation and correlation of the fit on the chart */
	BOOL	m_bShowEquation;
	//@cmember 
	/* Instance of CCurveFit class which actually computes the fits */
	CCurveFit m_CurveFit;
	
	//@cmember 
	/* Setup the component for the graph to plot the raw data and curve fit. */
	CHART_UT_API virtual void SetupComponents();

	//@cmember 
	/* Set the raw data to be fitted */
	CHART_UT_API virtual BOOL SetData( int size, double* pInX, double *pInY);

	//@cmember
	/* Set the range of X variable to be used in calculating the curve fit */
	CHART_UT_API void SetXRange(double dMinX, double dMaxX);

	//@cmember
	/* Retrieve range of X variable used in calculating the curve fit */
	CHART_UT_API void GetXRange(double &dMinX, double &dMaxX);

	//@cmember
	/* Select the functional form of curve fit (0<nType=15) */
	CHART_UT_API void SetFitType(int nType);

	//@cmember
	/* Get the functional form of curve fit */
	CHART_UT_API int GetFitType();

	//@cmember 
	/* Process the input data to obtain the output data. */
	CHART_UT_API virtual void ProcessData();

	//@cmember
	/* Set flag to display curve fit equation */
	CHART_UT_API void SetShowEquation(BOOL bShow);

	//@cmember
	/* Get flag to display curve fit equation */
	CHART_UT_API BOOL GetShowEquation();

	//@cmember 
	/* Not used. */
	CHART_UT_API virtual void InitializeData();

	//@cmember 
	/* Only kill the data item and free the responsible memory. */
	CHART_UT_API virtual void ClearData();

	//@cmember 
	/* Kill the component list, the data list, and frees allocated memory. */
	CHART_UT_API virtual void Clear();

	//@cmember 
	/* Constructor */
	CHART_UT_API OCCurveFitItem();

	//@cmember 
	/* Destructor */
	CHART_UT_API virtual ~OCCurveFitItem();
};

#endif // !defined(AFX_OCCurveFit_H__027FBE84_FC77_11D1_B2DB_006008AF1D5D__INCLUDED_)

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
