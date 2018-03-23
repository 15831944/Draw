///////////////////////////////////////////////////////////////////////////////
// OCFTChart.h : interface for the OCFTChart class.
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

#if !defined(AFX_OCFTCHART_H_INCLUDED_)
#define AFX_OCFTCHART_H_INCLUDED_

#include <StingrayExportDefs.h>

/////////////////////////////
// AutoDuck tag block block for OCFTStructData 


//@doc OCFTStructData
//@mdata CString  | OCFTStructData | m_strAnnotation | The annotation text

//@doc OCFTStructData
//@mdata int  | OCFTStructData | m_nGroup | The grous number this structure is dealing with.

// adinsert AutoDuck insertion point for OCFTStructData 
//@doc OCFTStructData 
//@class Structure data class for Fourier Transformation. It allow user to 
// indicating the group number this structure will be added to, so by overriding
// the GetAnnotation function user can give the annotation to a dynamic graph on
// the fly.
class OCFTStructData : public SRGDoubleStructData  
{
public:
	inline OCFTStructData(int nGroup)
	{
		m_nGroup = nGroup;
	}
	inline virtual ~OCFTStructData(){};

	//@cmember Feed the annotation for the data with given index and group and 
	// the language code
	CHART_UT_API virtual CString& GetAnnotation(int code, int nIndex, int nGroup);

protected:
	inline OCFTStructData()
	{
		m_nGroup = -1;
	}
	//@cmember This function delegate the call to the other version of 
	// GetAnnotation function.
	CHART_UT_API virtual CString& GetAnnotation(int code);
	//@cmember Annotation string.
	CString m_strAnnotation;
	//@cmember The group number this structure is dealing with.
	int m_nGroup;
};

/////////////////////////////
// AutoDuck tag block block for OCFTChart 

//@doc OCFTChart
//@mdata int  | OCFTChart | m_nDataSize | Data sample size

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bShowReIn | Flag indicating whether displaying real part of input

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bShowImIn | Flag indicating whether displaying imaginary part of input
//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bShowReOut | Flag indicating whether displaying real part of output

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bShowImOut | Flag indicating whether displaying imaginary part of output

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bShowPS | Flag indicating whether displaying power spectrum of output

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bOwnReOut | Flagging whether the class own the memory of the real part of the output

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bOwnReIn | Flagging whether the class own the memory of the real part of the input

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bOwnImOut | Flagging whether the class own the memory of the imaginary part of the output

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bOwnImIn | Flagging whether the class own the memory of the imaginary part of the input

//@doc OCFTChart
//@mdata BOOL  | OCFTChart | m_bOwnPS | Flagging whether the class own the memory of the power spectrum data

//@doc OCFTChart
//@mdata double*  | OCFTChart | m_pPS | Pointer to the data buffer of power spectrum

//@doc OCFTChart
//@mdata double*  | OCFTChart | m_pImOut | Pointer to the data buffer of the imaginary part of output

//@doc OCFTChart
//@mdata double*  | OCFTChart | m_pReOut | Pointer to the data buffer of the real part of the output

//@doc OCFTChart
//@mdata double*  | OCFTChart | m_pImIn | Pointer to the data buffer of the imaginary part of the input

//@doc OCFTChart
//@mdata double*  | OCFTChart | m_pReIn | Pointer to the data buffer of the real part of the input

//@doc OCFTChart
//@mdata SRGraphDisplay*  | OCFTChart | m_pReInD | Pointer to the display for the real input data

//@doc OCFTChart
//@mdata SRGraphDisplay*  | OCFTChart | m_pImInD | Pointer to the display for the imaginary input data

//@doc OCFTChart
//@mdata SRGraphDisplay*  | OCFTChart | m_pReOutD | Pointer to the display for the real output data

//@doc OCFTChart
//@mdata SRGraphDisplay*  | OCFTChart | m_pImOutD | Pointer to the display for the imaginary output data

//@doc OCFTChart
//@mdata SRGraphDisplay*  | OCFTChart | m_pPSD | Pointer to the display for the power spectrum data

// adinsert AutoDuck insertion point for OCFTChart 
//@doc OCFTChart 
//@class This class encaptulate the Fourier Transformation and graphically represent 
// the result of the Fourier Transformation. 
class OCFTChart : public OCutItem  
{	
public:
	enum {RE_IN, IM_IN, RE_OUT, IM_OUT, POWER_SPECTRUM};
	enum Direction { FOREWARD = 1, BACKWARD = -1};

	//@cmember Clear all the memory used by the components
	CHART_UT_API virtual void ClearComponents();
	//@cmember Remove the given components from the component list of the graph. Memory is not freed.
	CHART_UT_API virtual void RemoveComponent(SRGraphComponent* pC);
	//@cmember Perform the fourier transformation on the given data
	CHART_UT_API virtual void DoFourierTransform(Direction nDir);
	//@cmember Create some default components for to the graph.
	CHART_UT_API virtual void SetupComponents();
	//@cmember Check if a given part is current shown.
	CHART_UT_API BOOL GetShowPart(int nWhichPart);
	//@cmember Dynamically hide and show a given part of the data
	CHART_UT_API void SetShowPart(int nWhichPart, BOOL bShow);
	//@cmember Get hold of the data buffer of the given part
	CHART_UT_API double* GetData(int nWhichPart);
	//@cmember Set the data buffer of the given part
	CHART_UT_API virtual void SetData(int nWhichPart, int nSize, double* pDataBuf = NULL);
	//@cmember Set the data buffers. 
	CHART_UT_API virtual void SetData(int nSize, double* pReIn, double* pImIn, double* pReOut = NULL, double* pImOut = NULL, double* pPowerSpectrum = NULL);
	//@cmember Get hold the display of the given part
	CHART_UT_API SRGraphDisplay* GetDisplay(int nWhichPart);

	//@cmember Add a display for the given part of the data
	CHART_UT_API virtual SRGraphDisplay* AddDisplay(int nWhichPart, SRGraphDisplay* pD = NULL);

	//@cmember Setup the dynamic data structure for the diffent part of the data. The data buffer is 
	// not set yet inside this function
	CHART_UT_API virtual void InitializeData();
	//@cmember Erase the components and the data
	CHART_UT_API virtual void Clear();
	//@cmember Erase all the data
	CHART_UT_API virtual void ClearData();
	//@cmember Set the data size
	inline void SetDataSize(int nSize){m_nDataSize=nSize;}
	//@cmember Get the data size
	inline int GetDataSize(){return m_nDataSize;}

	//@cmember Constructor
	CHART_UT_API OCFTChart();
	//@cmember Clear all the responsible memroy
	CHART_UT_API virtual ~OCFTChart();

protected:
	//@cmember Check the memory ownership of the data buffer of the given part
	CHART_UT_API BOOL GetOwnership(int nWhichPart);
	//@cmember Set the ownership of the data buffer of the given part
	CHART_UT_API void SetOwnership(int nWhichPart, BOOL bOwn);
	//@cmember Set up the dynamic data structure for the given group
	CHART_UT_API virtual void AddStructData(int nGroup);
	//@cmember Data size of input data.
	int m_nDataSize;

	//@cmember Flagging whether display the real part of the input
	BOOL m_bShowReIn;
	//@cmember Flagging whether displaying the imaginary part of the input
	BOOL m_bShowImIn;
	//@cmember Flagging whether displaying the real part of the output data
	BOOL m_bShowReOut;
	//@cmember Flagging whether displaying the imaginary part of the output data
	BOOL m_bShowImOut;
	//@cmember Flagging whether displaying the power spectrum data
	BOOL m_bShowPS;

	//@cmember Flagging whether this class own the memory of the real part of the output
	BOOL m_bOwnReOut;
	//@cmember Flagging whether this class own the memory of the real part of the input
	BOOL m_bOwnReIn;
	//@cmember Flagging whether this class own the memory of the imaginary part of the output
	BOOL m_bOwnImOut;
	//@cmember Flagging whether this class own the memory of the imaginary part of the input
	BOOL m_bOwnImIn;
	//@cmember Flagging whether this class own the memory of the power spectrum data
	BOOL m_bOwnPS;


	//@cmember Pointer to the data buffer of the power spectrum
	double* m_pPS;
	//@cmember Pointer to the data buffer of the imginary part of output
	double* m_pImOut;
	//@cmember Pointer to the data buffer of the real part of the output
	double* m_pReOut;
	//@cmember Pointer to the data buffer of the imaginary part of the input
	double* m_pImIn;
	//@cmember Pointer to the data buffer of the real part of the input
	double* m_pReIn;

	//@cmember Pointer to the display for the real part of input
	SRGraphDisplay* m_pReInD;
	//@cmember Pointer to the display for the imaginary part of the input
	SRGraphDisplay* m_pImInD;
	//@cmember Pointer to the display for the real part of the output
	SRGraphDisplay* m_pReOutD;
	//@cmember Pointer to the display for the imaginary part of the output
	SRGraphDisplay* m_pImOutD;
	//@cmember Pointer to the display for the power spectrum
	SRGraphDisplay* m_pPSD;
};

#endif // !defined(AFX_OCFTCHART_H_INCLUDED_)

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
