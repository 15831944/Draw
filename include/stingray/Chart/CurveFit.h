///////////////////////////////////////////////////////////////////////////////
// CurveFit.h
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
//
//	CurveFit.h: Interfaces for the curve fitting classes.
//
//    Author:	Steve Brooks
//	    Date:	28 June 2000
//	Revision:	0.99
//
//  File Contents:
//
//	Constants and Definitions:
//
//	Data Structures used in Curve Fitting:
//
//		class CVector
//		class CMatrix
//		class CXYPair
//
//  Curve Fit Abstraction Class:
//
//		class CCurveFit
//
//  Curve Fitting Classes:
//
//		class CFitBase
//		class CFitPolynomial
//		class CFitExponential
//		class CFitLogarithmic
//		class CFitInverse
//		class CFitInverseSquare
//		class CFitPower
//		class CFitNonlinear
//		class CFitSine
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _OBJCHART_UT_DLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA OCUT_DATA
#endif

#if !defined(AFX_CURVEFIT_H__74970E6C_C262_4ACA_BC9D_D0418435D64F__INCLUDED_)
#define AFX_CURVEFIT_H__74970E6C_C262_4ACA_BC9D_D0418435D64F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <StingrayExportDefs.h>

#pragma warning(disable: 4267 4018)

class CFitBase;
class OCCurveFitItem;

///////////////////////////////////////////////////////////////////////////////
//
//	Curve Fit Definitions
//
///////////////////////////////////////////////////////////////////////////////

// Maximum Polynomial Fit Order
const int FIT_ORDER_MAX = 10;

// Enumerated curve fit types
const int FIT_NONE				=  0;
const int FIT_FIRST				=  0;
const int FIT_1ST_ORDER_POLY	=  1;	// y = a0 + a1*x
const int FIT_2ND_ORDER_POLY	=  2;	// y = a0 + a1*x + a2*x^2
const int FIT_3RD_ORDER_POLY	=  3;	// y = a0 + a1*x + a2*x^2 + a3*x^3a
const int FIT_4TH_ORDER_POLY	=  4;	// y = a0 + a1*x + a2*x^2 + ... + a4*x^4
const int FIT_5TH_ORDER_POLY	=  5;	// y = a0 + a1*x + a2*x^2 + ... + a5*x^5
const int FIT_6TH_ORDER_POLY	=  6;	// y = a0 + a1*x + a2*x^2 + ... + a6*x^6
const int FIT_7TH_ORDER_POLY	=  7;	// y = a0 + a1*x + a2*x^2 + ... + a7*x^7
const int FIT_8TH_ORDER_POLY	=  8;	// y = a0 + a1*x + a2*x^2 + ... + a8*x^8
const int FIT_9TH_ORDER_POLY	=  9;	// y = a0 + a1*x + a2*x^2 + ... + a9*x^9
const int FIT_EXPONENTIAL		= 10;	// y = a0*e^(a1*x)
const int FIT_LOGRITHMIC		= 11;	// y = a0*ln(a1*x)
const int FIT_POWER				= 12;	// y = a0*10^(a1*x)
const int FIT_INVERSE			= 13;	// y = a0 + a1*x^(-1)
const int FIT_INVERSE_SQUARE	= 14;	// y = a0 + a1*x^(-2)
const int FIT_SINE				= 15;	// y = a0*sin(a1*x+a2) + a3
const int FIT_LAST				= 16;

// Array of curve fit names
static LPCTSTR lpszFitTypes[] = {
	_T("None"),
	_T("Linear"),
	_T("Quadratic"),
	_T("Cubic"),
	_T("4th Order"),
	_T("5th Order"),
	_T("6th Order"),
	_T("7th Order"),
	_T("8th Order"),
	_T("9th Order"),
	_T("Exponential"),
	_T("Logarithmic"),
	_T("Power"),
	_T("Inverse"),
	_T("Inverse Square"),
	_T("Sine")
};

///////////////////////////////////////////////////////////////////////////////
//
//	Vector and Matrix data structures used 
//  in curve fitting algorithms
//
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// A One Dimensional Vector Template
//
////////////////////////////////////////
template< class T > class CVector : public std::vector< T >
{
public:
	CVector() {};

	CVector(int nElem, T Val = 0)
	{
		SetSize(nElem, Val);
	}

	T& operator[](int nElem)
	{
		ASSERT((-1<nElem) && (nElem < size()));
		return at(nElem);
	}

	void SetSize(int nElem, T Val=0)
	{
		clear();
		resize(nElem);
		iterator it;
		for(it=begin(); it!=end(); it++)
		{
			(*it) = Val;
		}
	}

#ifdef DEBUG
	virtual void Dump(LPCTSTR lpszFormat)
#else
	virtual void Dump(LPCTSTR lpszFormat)
#endif //DEBUG
	{
		ASSERT(lpszFormat != NULL);

		TRACE(_T("[ "));
		iterator it;
		for(it=begin(); it!=end(); it++)
		{
#ifdef DEBUG
			TRACE(_T("\t"));
			TRACE(lpszFormat,(*it));
#endif //DEBUG
		}
		TRACE(_T(" ]\n"));
	}
};

////////////////////////////////////////
//
// A 2 Dimensional Matrix Template
//
////////////////////////////////////////

template< class T > class CMatrix : public std::vector< CVector< T > >
{
public:
	CMatrix() {};

	CMatrix(int nRows, int nCols, T Val=0)
	{
		for(int i=0; i<nRows; i++)
		{
			push_back(CVector<T>(nCols, Val));
		}
	}

	CVector< T >& operator[](int nElem)
	{
		ASSERT((-1<nElem) && (nElem < size()));
		return at(nElem);
	}

	void SetSize(int nRows, int nCols, T Val=0)
	{
		clear();
		resize(nRows);
		iterator it;
		for(it=begin(); it!=end(); it++)
		{
			(*it).SetSize(nCols, Val);
		}
	}

	int Rows()
	{
		return size();
	}

	int Cols()
	{
		iterator it = begin();
		return (*it).size();
	}

	virtual void Dump(LPCTSTR lpszFormat)
	{
		ASSERT(lpszFormat != NULL);
		
		iterator it;
		TRACE(_T("[\n"));
		for(it=begin(); it!=end(); it++)
		{
			(*it).Dump(lpszFormat);
		}
		TRACE(_T("]\n"));
	}
};




///////////////////////////////////////////////////////////////////////////////
//
// Curve Fitting Data Structures
//
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// A single XY data point -
// All data that are used for curve fitting are stored 
// in a vector of this type.
//
////////////////////////////////////////////////////////////
class CXYPair 
{
public:
	double x;	// x Value
	double y;	// y Value
	double dy;	// y Uncertainty

	inline  CXYPair() : 
	  x(0.0), y(0.0), dy(0.0) {}

	inline CXYPair(double x0, double y0, double dy0 = 1)	
	{ 
		x = x0; 
		y = y0; 
		dy = dy0;  
	};
};

////////////////////////////////////////////////////////////
//
// A "data set" of XY pairs
//
////////////////////////////////////////////////////////////
typedef std::vector<CXYPair> XYData;

////////////////////////////////////////////////////////////
//
// CCurveFit Abstraction interface for various curve fits.
// This class provides an abstraction of the curve fit 
// objects so that creating a curve fit for chart data
// requires only a pointer to the chartview, the column 
// indices and an enumerated fit type.
//
////////////////////////////////////////////////////////////
class CCurveFit : public CObject  
{
	CHART_UT_DECLARE_SERIAL(CCurveFit)

public:
	CHART_UT_API CCurveFit();
	CHART_UT_API CCurveFit(OCCurveFitItem* pGraphItem);
	CHART_UT_API virtual ~CCurveFit();

	// Set pointer to graph view
	CHART_UT_API virtual void			SetDataSource(OCCurveFitItem* pGraphItem);

	// Get pointer to the view
	CHART_UT_API virtual OCCurveFitItem* GetDataSource();

	// Select type of curve fit to perform.
	CHART_UT_API virtual void			SetFitType(int nType = FIT_1ST_ORDER_POLY);

	// Get the current curve fit type.
	CHART_UT_API virtual int				GetFitType();

	// Select data -  X and Y groups
	CHART_UT_API virtual void			SetFitData(int nXidx, int nYidx);

	// Get the fit data - X and Y groups
	CHART_UT_API virtual void			GetFitData(int& nXidx, int& nYidx);

	// Copy data from chart to fit data set
	CHART_UT_API virtual void			UpdateFitData();

	// Use fitted equation to calculate X for a given Y
	CHART_UT_API virtual double			PredictX(double Y);

	// Use fitted equation to calculate Y for a given X
	CHART_UT_API virtual double			PredictY(double X);

	// Determine if current fit is valid.
	CHART_UT_API virtual BOOL			IsValidFit();

	// Returns number of defined fit types (including None).
	CHART_UT_API int						GetFitTypeCount();
	
	// Returns text describing fit type
	CHART_UT_API virtual CString			GetFitEquation();
	CHART_UT_API virtual CString			GetFitEquation(int nType);

	// Returns a short string identifying the fit type
	CHART_UT_API virtual CString			GetFitName();
	CHART_UT_API virtual CString			GetFitName(int nType);
	
	// Returns the correlation coefficient of the fit
	CHART_UT_API virtual double			GetCorrelation();

	// Returns the number of coefficients or parameters used in the fit
	CHART_UT_API virtual int				GetNumberOfCoef();

	// Returns the requested coefficient or parameter
	CHART_UT_API virtual double			GetCoefficient(int nIndex);

	CHART_UT_API virtual void			Serialize(CArchive& ar);

protected:
	// Pointer to ChartView that contains the data.
	OCCurveFitItem*			m_pGraphItem;

	// Type of fit to be performed.
	// See Enumerated Curve Fit Types at top of this file
	int						m_nFitType;

	// X and Y data indices to perform fit against
	int						m_nXindex;
	int						m_nYindex;

	// Pointer to curve fit object.  
	// All fit objects derive from CFitBase.
	CFitBase*				m_pFit;
};// class CCurveFit




////////////////////////////////////////////////////////////
//
// Least Squares Fit Base Class
//
// Handles storage and access of data and fit coefficients.
//
////////////////////////////////////////////////////////////
class CFitBase
{
public:
	// Constructor / Destructor
	CHART_UT_API CFitBase();
	CHART_UT_API virtual ~CFitBase();

	// Add an XY pair to the data set
	CHART_UT_API virtual void	AddData(double x, double y);

	// Remove all of the XY pairs from the data set
	CHART_UT_API virtual void	ClearData();

	// Get the number of XY pairs in the data set
	CHART_UT_API virtual int		GetDataCount();

	// Set number of fit coefficients
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Indicate whether fit is valid
	CHART_UT_API virtual BOOL	IsValidFit();

	// Get the number of coefficients associated with the fit
	CHART_UT_API virtual int		GetNumberOfCoef();

	// Get the fit coefficient at index i
	CHART_UT_API virtual double	GetCoefficient(int i);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do a curve fit
	virtual void	Fit() = 0;

	// Predict a "Y" from an "X" using the fit coefficients
	virtual double	PredictY(double x) = 0;

	// Predict an "X" from a "Y" using the fit coefficients
	virtual double	PredictX(double y) = 0;

	// Diagnostics
	virtual void	Dump() = 0;

protected:
	// Vector of XY paired data
	XYData			m_Data;

	// Order of polynomial fit 
	int				m_nFitOrder;

	// Vector of fit coefficients
	CVector<double>	m_FitCoeffs;

	// Correlation Coefficient
	double			m_R2;

	// Indicates whether current fit is valid
	BOOL			m_bFitValid;

	// Indicates whether current correlation is valid
	BOOL			m_bCorrelValid;

	// Utility methods for calculating curve fits

	// Lower / Uppder Decomposition for solving systems of linear equations
	CHART_UT_API virtual BOOL	LUDeComp(CMatrix<double>& A, CVector<double>& Indx, double& d);

	// Lower / Upper Back Substitution for solving systems of linear equations
	CHART_UT_API virtual BOOL	LUBackSub(CMatrix<double>& A, CVector<double>& Indx, CVector<double>& B);	
};




////////////////////////////////////////////////////////////
//
// General Nth Order Least Squares Fit
//
// Determines the coefficients for a polynomial of the form
//
// y = a0*x + a1*x + a2*x^2 + ... + an*x^n
//
// that best fits a set of XY data.  
//
////////////////////////////////////////////////////////////
class CFitPolynomial : public CFitBase
{
public:
	// Constructor / Destructor
	inline CFitPolynomial() {};
	inline virtual	~CFitPolynomial() {};

	// Set polynomial fit order to N
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Do a polynomial fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();

protected:
	
	// Create the system of linear equations that define the fit
	CHART_UT_API virtual BOOL	DefineSystem(CMatrix<double>& A, CVector<double>& B);	

	// Solve the system of linear equations
	CHART_UT_API virtual BOOL	SolveSystem(CMatrix<double>& A, CVector<double>& B);

};// class CFitPolynomial

////////////////////////////////////////////////////////////
//
// Exponential Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0*e^(a1*x)
//
// that best fits a set of XY data.  This equation can be 
// transformed so that it is linear in x:
//
//		ln(y) = ln(a0) + (a1*x)
//
// Therefore, the y data are transformed as they are added 
// in AddData() and the base class Fit() is performed on 
// the transformed data.  The 0th fit coefficient is 
// un-transformed after the fit is performed.
// 
////////////////////////////////////////////////////////////
class CFitExponential : public CFitPolynomial  
{
public:
	inline CFitExponential() {};
	inline virtual ~CFitExponential() {};

	// Add an XY pair to the data set.
	CHART_UT_API virtual void	AddData(double x, double y);

	// Set polynomial fit order to 1 only
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do an exponential fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();
};// class CFitExponential

////////////////////////////////////////////////////////////
//
// Logarithmic Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0*ln(a1*x)
//
// that best fits a set of XY data.  This equation can be 
// transformed so that it is linear in ln(x):
//
//		y = c + a0*ln(x)
//
// Where:
//		c = a0*ln(a1)
// or
//		a1 = e^(c/a0)
//
//
// Therefore, the x data are transformed as they are added 
// in AddData() and the base class Fit() is performed on 
// the transformed data.  The a1 fit coefficient is 
// un-transformed after the fit is performed.
// 
////////////////////////////////////////////////////////////
class CFitLogarithmic : public CFitPolynomial  
{
public:
	inline CFitLogarithmic() {};
	inline virtual ~CFitLogarithmic() {};

	// Add an XY pair to the data set.
	// Transforming y to ln(y)
	CHART_UT_API virtual void	AddData(double x, double y);

	// Set polynomial fit order to 1 only
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do an exponential fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();
};// class CFitLogarithmic

////////////////////////////////////////////////////////////
//
// Inverse Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0 + a1*x^(-1)
//
// that best fits a set of XY data.  This equation can be 
// transformed so that it is linear in x^-1:
//
//		y = a0 + a1* (x^(-1))
//
// Therefore, the x data are transformed as they are added 
// in AddData() and the base class Fit() is performed on 
// the transformed data.  
// 
////////////////////////////////////////////////////////////
class CFitInverse : public CFitPolynomial  
{
public:
	inline CFitInverse() {};
	inline virtual ~CFitInverse() {};

	// Add an XY pair to the data set.
	CHART_UT_API virtual void	AddData(double x, double y);

	// Set polynomial fit order to 1 only
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do an exponential fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();
};//class CFitInverse

////////////////////////////////////////////////////////////
//
// Inverse Square Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0 + a1*x^(-2)
//
// that best fits a set of XY data.  This equation can be 
// transformed so that it is linear in x^-1:
//
//		y = a0 + a1* (x^(-2))
//
// Therefore, the x data are transformed as they are added 
// in AddData() and the base class Fit() is performed on 
// the transformed data.  
// 
////////////////////////////////////////////////////////////
class CFitInverseSquare : public CFitPolynomial  
{
public:
	inline CFitInverseSquare() {};
	inline virtual ~CFitInverseSquare() {};

	// Add an XY pair to the data set.
	CHART_UT_API virtual void	AddData(double x, double y);

	// Set polynomial fit order to 1 only
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do an exponential fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();
};//class CFitInverseSquare

////////////////////////////////////////////////////////////
//
// Power Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0*10^(a1*x)
//
// that best fits a set of XY data.  This equation can be 
// transformed so that it is linear in x:
//
//		log(y) = log(a0) + (a1*x)
//
// Therefore, the y data are transformed as they are added 
// in AddData() and the base class Fit() is performed on 
// the transformed data.  The a0 fit coefficient is 
// un-transformed after the fit is performed.
// 
////////////////////////////////////////////////////////////
class CFitPower : public CFitPolynomial  
{
public:
	inline CFitPower() {};
	inline virtual ~CFitPower() {};

	// Add an XY pair to the data set.
	CHART_UT_API virtual void	AddData(double x, double y);

	// Set polynomial fit order to 1 only
	CHART_UT_API virtual void	SetFitOrder(int N = 1);

	// Get the Correlation Coefficient
	CHART_UT_API virtual double	GetCorrelation();

	// Do an exponential fit
	CHART_UT_API virtual void	Fit();

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();
};//class CFitPower

////////////////////////////////////////////////////////////
//
// NonLinear Least Squares Curve Fit
//
////////////////////////////////////////////////////////////
class CFitNonlinear : public CFitBase  
{
public:
	CHART_UT_API CFitNonlinear();
	CHART_UT_API virtual ~CFitNonlinear();

	// Do a nonlinear fit
	CHART_UT_API virtual void	Fit();

protected:

	// Gauss - Jordan Matrix Reduction
	CHART_UT_API virtual BOOL	GaussJordan(CMatrix<double>& A, CMatrix<double>& B);

	// Levenberg-Marquardt Minimization
	CHART_UT_API virtual BOOL	MarquardtMin(CVector<double>& A, CVector<int>& IA, CMatrix<double>& Covar,
								 CMatrix<double>& Alpha, double& ChiSq, double& FitLamda);

	// Levenberg-Marquardt Evaluation
	CHART_UT_API virtual BOOL	MarquardtEval(CVector<double>& FitCoeffs, CVector<int>& IFitCoeffs, 
								  CMatrix<double>& Alpha, CVector<double>& Beta, double& ChiSq);

	// Sort Covariance Matrix
	CHART_UT_API virtual BOOL	CovarianceSort(CMatrix<double>& Covar, CVector<int>& ICovar);

	// Model that describes a function and it's derivatives 
	CHART_UT_API virtual double	Model(double x, CVector<double>& A, CVector<double>& dydA) = 0;

};//class CFitSine


////////////////////////////////////////////////////////////
//
// Sine Least Squares Curve Fit
//
// Determines the coefficients of an equation of the form
//
//		y = a0*sin(a1*x) + a2
//
// that best fits a set of XY data.  
// 
////////////////////////////////////////////////////////////
class CFitSine : public CFitNonlinear  
{
public:
	CHART_UT_API CFitSine();
	CHART_UT_API virtual ~CFitSine() {};

	// Predict a "Y" from an "X" using the fit coefficients
	CHART_UT_API virtual double	PredictY(double x);

	// Predict an "X" from a "Y" using the fit coefficients
	CHART_UT_API virtual double	PredictX(double y);

	// Diagnostics
	CHART_UT_API virtual void	Dump();

protected:

	// Model that describes a function and it's derivatives
	CHART_UT_API virtual double	Model(double x, CVector<double>& A, CVector<double>& dydA);

};//class CFitSine
#endif // !defined(AFX_CURVEFIT_H__74970E6C_C262_4ACA_BC9D_D0418435D64F__INCLUDED_)

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR