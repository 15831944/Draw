///////////////////////////////////////////////////////////////////////////////
// SECRAND.h
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
// CHANGELOG:
//
//    AAB	9/3/95	Started
//    MSW   9/30/95  Code Review
//
//

#ifndef __SECRAND_H__
#define __SECRAND_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL


#define SECRANDOM_MIN	0
#define SECRANDOM_MAX	32767

/////////////////////////////
// AutoDuck tag block block for SECRandom 

//@doc SECRandom
//@mdata unsigned int  | SECRandom | m_nMin | Minimum value.
//@xref <c SECRandom> <mf SECRandom::SetLBound> <mf SECRandom::GetLBound>
// <mf SECRandom::GetRange>

//@doc SECRandom
//@mdata unsigned int  | SECRandom | m_nMax | Maximum value.
//@xref <c SECRandom> <mf SECRandom::SetUBound> <mf SECRandom::GetLBound>
// <mf SECRandom::GetRange>

//@doc SECRandom
//@mdata unsigned int  | SECRandom | m_nSeed | Seed used for Knuth operations.
//@xref <c SECRandom> <mf SECRandom::GetSeed>

//@doc SECRandom
//@mdata double  | SECRandom | m_dMultiplier | Bounds multiplier.
//@xref <c SECRandom>

//@doc SECRandom
//@mdata unsigned int  | SECRandom | m_nWeights | Number of weight values.
//@xref <c SECRandom> <mf SECRandom::AddWeight>

//@doc SECRandom
//@mdata unsigned int  | SECRandom | m_pWeights | Pointer to weight array itself.
//@xref <c SECRandom> <mf SECRandom::AddWeight>

// adinsert AutoDuck insertion point for SECRandom 
//@doc SECRandom 
//@class SECRandom is a utility class for the generation of random numbers.
// 
//@comm An instance of SECRandom is initialized with an integer seed value from 
// which random numbers are derived.  If a seed of 0 is provided, a seed 
// based on the current system time will be used.
// 
// SECRandom can provide a random value within a range by specifying an 
// upper and lower bound for the range.  SECRandom can also generate a 
// skewed random result based on an array of weights specified by the user.
//
// Each entry of the weighted array specifies an unsigned integer value 
// (the weight) of what probability a random number will be generated for 
// the entry.  A higher number skews the probability that a random number 
// will be generated for that position.  Thus for a weighted array of 4 
// weights with the following layout:
//
//Position		Weight<nl>
//	0			1<nl>
//	1			7<nl>
//	2			0<nl>
//	3			2
//
//There is a 10 percent chance that a random number 0 will be generated, a 
// 70 percent chance that a random number of 1 will be generated, no chance 
// for a number of 2 being generated, and a 20 percent chance that a value of 
// 3 will be generated if the user calls <mf SECRandom::GetRandomWeighted>.
class SECRandom : public CObject
{
    TOOLKIT_DECLARE_SERIAL(SECRandom)
        
	//@access Creation/Initialization
public:
	//@cmember
	/* Constructs and seeds an SECRandom object.*/
	TOOLKIT_API SECRandom(unsigned int nSeed=0);
    
	//@cmember
	/* Initializes an empty weight array.*/
    TOOLKIT_API BOOL InitWeights(unsigned int);
    
	//@access Attributes
public:
	//@cmember
	/* Add an individual weight to an existing weight array.*/
   TOOLKIT_API  BOOL AddWeight(unsigned int, unsigned int);
	
	//@cmember
	/* Retrieves the current seed value.*/
    TOOLKIT_API unsigned int GetSeed();
	
	//@cmember
	/* Sets the lower bound of the range.*/
    TOOLKIT_API BOOL SetLBound(unsigned int);
	
	//@cmember
	/* Retrieves the current lower bound of the range.*/
    TOOLKIT_API unsigned int GetLBound();
	
	//@cmember
	/* Sets the upper bound of the range.*/
    TOOLKIT_API BOOL SetUBound(unsigned int);
	
	//@cmember
	/* Retrieves the current upper bound of the range.*/
    TOOLKIT_API unsigned int GetUBound();
    
	//@cmember
	/* Sets the upper and lower bounds of the range.*/
    TOOLKIT_API BOOL SetBounds(unsigned int, unsigned int);
	
    
	//@access Operations
public:
	
	//@cmember
	/* Returns a random value; no range is used in the calculation.*/
    TOOLKIT_API unsigned int GetRandom();
	
	//@cmember
	/* Returns a weighted random value based on the current weight array.*/
    TOOLKIT_API unsigned int GetRandomWeighted();
	
	//@cmember
	/* Returns a random value within the current range.*/
    TOOLKIT_API unsigned int GetRange();
	
	//@cmember
	/* Returns a random value within the current range.*/
    TOOLKIT_API unsigned int GetRange(unsigned int nMin, unsigned int nMax);
	
	//@cmember
	/* Sets the multiplier.*/
    TOOLKIT_API void SetMultiplier();

	//@access Protected data members
protected:
	
	//@cmember
	/* 	Minimum value.*/
	unsigned int m_nMin;
	
	//@cmember
	/* Maximum value.*/
	unsigned int m_nMax;
	
	//@cmember
	/* Seed used for Knuth operations.*/
	unsigned int m_nSeed;
	
	//@cmember
	/* Bounds multiplier*/
	double m_dMultiplier;
	
	//@cmember
	/* Number of weight values*/
	unsigned int m_nWeights;
	
	//@cmember
	/* Pointer to weight array itself.*/
	unsigned int* m_pWeights;

public:
    TOOLKIT_API virtual ~SECRandom();
#ifdef _DEBUG
	TOOLKIT_API void AssertValid() const;
#endif
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECRAND_H__


