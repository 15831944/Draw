///////////////////////////////////////////////////////////////////////////////
// SRFormulaScanner.h
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
// AUTHOR:		Ricky Pearson
// CREATED:		May 18, 2000
//
//	10.10.00	appropriated for generic formula engine by jimp
//  06.19.06    exported classes with TOOLKIT_API macro by csd
//

#ifndef __SRFormulaScanner_h__
#define __SRFormulaScanner_h__

#include "SROpStack.h"
#include "SROperator.h"
#include <wchar.h>
#include <StingrayExportDefs.h>

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Operator precedence
//
//---------*---------*---------*---------*---------*---------*---------*-----

#define SR_OP_PRECEDENCE_ARRAY					210	// []
#define SR_OP_PRECEDENCE_LOGICALNOT				200	// !
#define SR_OP_PRECEDENCE_BITWISENOT				190	// ~
#define SR_OP_PRECEDENCE_MULTIPLY				180	// *
#define SR_OP_PRECEDENCE_DIVIDE					170	// /
#define SR_OP_PRECEDENCE_MODULO					160	// %
#define SR_OP_PRECEDENCE_ADD					150	// +
#define SR_OP_PRECEDENCE_SUBTRACT				140	// - 
#define SR_OP_PRECEDENCE_LEFTSHIFT				130	// <<
#define SR_OP_PRECEDENCE_RIGHTSHIFT				120	// >>
#define SR_OP_PRECEDENCE_LESSTHAN				110	// <
#define SR_OP_PRECEDENCE_LESSTHANOREQUAL		100	// <=
#define SR_OP_PRECEDENCE_GREATERTHAN			90	// >
#define SR_OP_PRECEDENCE_GREATERTHANOREQUAL		80	// >=
#define SR_OP_PRECEDENCE_EQUAL					70	// ==
#define SR_OP_PRECEDENCE_NOTEQUAL				60	// != or <>
#define SR_OP_PRECEDENCE_BITWISEAND				50	// &
#define SR_OP_PRECEDENCE_BITWISEXOR				40	// ^  
#define SR_OP_PRECEDENCE_BITWISEOR				30	// |
#define SR_OP_PRECEDENCE_LOGICALAND				20	// &&
#define SR_OP_PRECEDENCE_LOGICALOR				10	// ||


//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRFormulaScanner
//
//---------*---------*---------*---------*---------*---------*---------*-----

class SRFormulaScanner
{
	// Construction / destruction
public:
	TOOLKIT_API SRFormulaScanner();
	TOOLKIT_API ~SRFormulaScanner();

	// Operations
public:
	TOOLKIT_API bool PushOperator(char * lpszToken, int ot, int cnt);
	TOOLKIT_API bool PushOperator(SROperatorStackItem* pItem);
	TOOLKIT_API bool PushOperand(char * lpszToken, int ot);
	TOOLKIT_API bool PushOperand(SROperandStackItem* pItem);
	TOOLKIT_API bool Reduce(SROperatorStackItem* pItem);
	TOOLKIT_API void Reset();

	// Return value
public:
	TOOLKIT_API bool IsValid();
	TOOLKIT_API int  lex(_TCHAR *formula);
	TOOLKIT_API bool GetResult(_TCHAR ** lpsz);
	char *input_buffer;
	char *lbuf;
//#ifdef _UNICODE
	wchar_t *formula;
//#else
//	char *formula;
//#endif
	// Error handling
public:
	TOOLKIT_API void GetErrDescription(_TCHAR **);
	TOOLKIT_API UINT GetError();
	TOOLKIT_API void ClearError();
	TOOLKIT_API void SetError(UINT nErr);


	// Helpers
protected:
	TOOLKIT_API bool IsValidDoubleOperator(int nFirst, int nSecond);
	TOOLKIT_API int GetOperatorPrecedence(char * lpsz);
	TOOLKIT_API bool EvalOperator(SROperatorStackItem* pOpItem);
	TOOLKIT_API bool ReduceAll();
	TOOLKIT_API bool ReduceOperators(SROperatorStackItem* pItem = NULL);
	TOOLKIT_API bool ReduceFunction();

	// Data members
protected:
	SROpStack m_operators;
	SROpStack m_operands;
	SROperatorFactory m_OpFactory;
	UINT m_nError;

	enum
	{
		push_start,
		push_operator,
		push_operand
	} m_nLastPush;

	bool m_bReducing;
	int m_nLastOperator;
};

#endif //__SRFormulaScanner_h__
