///////////////////////////////////////////////////////////////////////////////
// SROperator.h
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
// AUTHOR:		Ricky Pearson
// CREATED:		May 18, 2000
//

#ifndef __SROperator_h__
#define __SROperator_h__

#include "SROpStack.h"
#include <StingrayExportDefs.h>

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Mathematical constants
//
//---------*---------*---------*---------*---------*---------*---------*-----
#define SR_PI    3.14159265358979323846
#define SR_EULER 2.71828182845904523536

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Formula type enums
//
//---------*---------*---------*---------*---------*---------*---------*-----
enum
{
	SR_FORMULATYPE_ABS = 1,
	SR_FORMULATYPE_ACOS,
	SR_FORMULATYPE_ACOSH,
	SR_FORMULATYPE_ADD,
	SR_FORMULATYPE_AND,
	SR_FORMULATYPE_ASIN,
	SR_FORMULATYPE_ASINH,
	SR_FORMULATYPE_ATAN,
	SR_FORMULATYPE_ATANH,
	SR_FORMULATYPE_BITWISEAND,
	SR_FORMULATYPE_BITWISENOT,
	SR_FORMULATYPE_BITWISEOR,
	SR_FORMULATYPE_BITWISEXOR,
	SR_FORMULATYPE_CEILING,
	SR_FORMULATYPE_CLEAN,
	SR_FORMULATYPE_COMBINATION,
	SR_FORMULATYPE_COS,
	SR_FORMULATYPE_COSH,
	SR_FORMULATYPE_COT,	  //co-tangent = 1/tan(x)
	SR_FORMULATYPE_CSC,   //co-secant = 1/sin(x)
	SR_FORMULATYPE_DEGREES,
	SR_FORMULATYPE_DIVIDE,
	SR_FORMULATYPE_EQUAL,
	SR_FORMULATYPE_EVEN,
	SR_FORMULATYPE_EXACT,
	SR_FORMULATYPE_EXP,
	SR_FORMULATYPE_FACTORIAL,
	SR_FORMULATYPE_FALSE,
	SR_FORMULATYPE_FLOOR,
	SR_FORMULATYPE_GREATERTHAN,
	SR_FORMULATYPE_IF,
	SR_FORMULATYPE_INT,
	SR_FORMULATYPE_LEFT,
	SR_FORMULATYPE_LEFTSHIFT,
	SR_FORMULATYPE_LESSTHAN,
	SR_FORMULATYPE_LN,
	SR_FORMULATYPE_LOG,
	SR_FORMULATYPE_LOWER,
	SR_FORMULATYPE_MID,
	SR_FORMULATYPE_MODULO,
	SR_FORMULATYPE_MULTIPLY,
	SR_FORMULATYPE_NEAREST,
	SR_FORMULATYPE_NOT,
	SR_FORMULATYPE_NOTEQUAL,
	SR_FORMULATYPE_ODD,
	SR_FORMULATYPE_OR,
	SR_FORMULATYPE_PERMUTATION,
	SR_FORMULATYPE_PI,
	SR_FORMULATYPE_POWER,
	SR_FORMULATYPE_PROPER,
	SR_FORMULATYPE_RADIANS,
	SR_FORMULATYPE_REPLACE,
	SR_FORMULATYPE_RIGHT,
	SR_FORMULATYPE_RIGHTSHIFT,
	SR_FORMULATYPE_ROOT,
	SR_FORMULATYPE_ROUND,
	SR_FORMULATYPE_ROUNDDOWN,
	SR_FORMULATYPE_ROUNDUP,
	SR_FORMULATYPE_SEC,          //SECANT
	SR_FORMULATYPE_SIGN,
	SR_FORMULATYPE_SIN,
	SR_FORMULATYPE_SINH,
	SR_FORMULATYPE_SQRT,
	SR_FORMULATYPE_SUBSTITUTE,
	SR_FORMULATYPE_SUBTRACT,
	SR_FORMULATYPE_TAN,
	SR_FORMULATYPE_TANH,
	SR_FORMULATYPE_TRIM,
	SR_FORMULATYPE_TRUE,
	SR_FORMULATYPE_UPPER,
	SR_FORMULATYPE_XOR
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Abstract Operators
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRAbstractOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRAbstractOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRAbstractOperator(int nType);
	TOOLKIT_API virtual ~SRAbstractOperator();

	// Operations
public:
	TOOLKIT_API virtual void PushOperand(SROperandStackItem* pItem);

	// Overrides
public:
	TOOLKIT_API virtual bool Execute();
	TOOLKIT_API virtual SROperandStackItem* GetResult();

	// Error checking
public:
	TOOLKIT_API UINT GetError();
protected:
	TOOLKIT_API void ClearError();
	TOOLKIT_API void SetError(UINT nErr);

	// Operand retrieval
protected:
	TOOLKIT_API bool PopAsBoolean(bool* p);
	TOOLKIT_API bool PopAsDouble(double* p);
	TOOLKIT_API bool PopAsInteger(int* p);
	TOOLKIT_API bool PopAsString(char ** p, int* n);

	// Helpers
protected:
	TOOLKIT_API bool VerifyOpCount();

	// Data members
protected:
	SROpStack	m_stack;
	UINT		m_nError;
	int			m_nType;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRAbstractLogicalOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRAbstractLogicalOperator : public SRAbstractOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRAbstractLogicalOperator(int nType);
	TOOLKIT_API virtual ~SRAbstractLogicalOperator();

	// Operations
public:
	TOOLKIT_API virtual SROperandStackItem* GetResult();

	// Data members
protected:
	bool m_bValue;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRAbstractNumericalOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRAbstractNumericalOperator : public SRAbstractOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRAbstractNumericalOperator(int nType);
	TOOLKIT_API virtual ~SRAbstractNumericalOperator();

	// Operations
public:
	TOOLKIT_API virtual SROperandStackItem* GetResult();

	// Data members
protected:
	double m_dValue;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRAbstractTextOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRAbstractTextOperator : public SRAbstractOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRAbstractTextOperator(int nType);
	TOOLKIT_API virtual ~SRAbstractTextOperator();

	// Operations
public:
	TOOLKIT_API virtual SROperandStackItem* GetResult();

	// Data members
protected:
	char * m_lpszValue;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Bitwise Operators
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRBitwiseOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRBitwiseOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRBitwiseOperator(int nType);
	TOOLKIT_API virtual ~SRBitwiseOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRShiftOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRShiftOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRShiftOperator(int nType);
	TOOLKIT_API virtual ~SRShiftOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Logical Operators
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRBooleanOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRBooleanOperator : public SRAbstractLogicalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRBooleanOperator(int nType);
	TOOLKIT_API virtual ~SRBooleanOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRComparisonOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRComparisonOperator : public SRAbstractLogicalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRComparisonOperator(int nType);
	TOOLKIT_API virtual ~SRComparisonOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRConditionalOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRConditionalOperator : public SRAbstractOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRConditionalOperator(int nType);
	TOOLKIT_API virtual ~SRConditionalOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
	TOOLKIT_API virtual SROperandStackItem* GetResult();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Math and Trigonometry Operators
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRArithmeticOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRArithmeticOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRArithmeticOperator(int nType);
	TOOLKIT_API virtual ~SRArithmeticOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRLogOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRLogOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRLogOperator(int nType);
	TOOLKIT_API virtual ~SRLogOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

	// Helpers
protected:
	TOOLKIT_API double Log(double num, double base);
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRMathOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRMathOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRMathOperator(int nType);
	TOOLKIT_API virtual ~SRMathOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

	// Helpers
protected:
	TOOLKIT_API double Power(double dBase, double dPower);
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRModuloOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRModuloOperator: public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRModuloOperator();
	TOOLKIT_API virtual ~SRModuloOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRPiOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRPiOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRPiOperator();
	TOOLKIT_API virtual ~SRPiOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRProbabilityOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRProbabilityOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRProbabilityOperator(int nType);
	TOOLKIT_API virtual ~SRProbabilityOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

	// Helpers
protected:
	TOOLKIT_API double Combination(long n, long k);
	TOOLKIT_API double Factorial(long n);
	TOOLKIT_API double Permutation(long n, long k);
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRRoundOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRRoundOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRRoundOperator(int nType);
	TOOLKIT_API virtual ~SRRoundOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

	// Helpers
protected:
	TOOLKIT_API int Ceiling(double dValue, int nSig);
	TOOLKIT_API int Floor(double dValue, int nSig);
	TOOLKIT_API double Round(double dValue, int nSig);
	TOOLKIT_API double RoundDown(double dValue, int nSig);
	TOOLKIT_API double RoundUp(double dValue, int nSig);
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRTrigOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRTrigOperator : public SRAbstractNumericalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRTrigOperator(int nType);
	TOOLKIT_API virtual ~SRTrigOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Text Operators
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRStringCaseOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRStringCaseOperator : public SRAbstractTextOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRStringCaseOperator(int nType);
	TOOLKIT_API virtual ~SRStringCaseOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRStringCompareOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRStringCompareOperator : public SRAbstractLogicalOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRStringCompareOperator();
	TOOLKIT_API virtual ~SRStringCompareOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRStringManipOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRStringManipOperator : public SRAbstractTextOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRStringManipOperator(int nType);
	TOOLKIT_API virtual ~SRStringManipOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();

	// Helpers
protected:
	TOOLKIT_API bool IsPrintable(char c);
	TOOLKIT_API bool IsSpace(char c);
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRSubstringOperator
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRSubstringOperator : public SRAbstractTextOperator
{
	// Construction / destruction
public:
	TOOLKIT_API SRSubstringOperator(int nType);
	TOOLKIT_API virtual ~SRSubstringOperator();

	// Operations
public:
	TOOLKIT_API virtual bool Execute();
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Object Factory
//
//---------*---------*---------*---------*---------*---------*---------*-----

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SROperatorFactory
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SROperatorFactory
{
	// Operations
public:
	TOOLKIT_API SRAbstractOperator* GetOperator(char * lpszToken);

	// Helpers
protected:
	TOOLKIT_API int GetOperatorType(char * lpszToken);

};

#endif //__SROperator_h__
