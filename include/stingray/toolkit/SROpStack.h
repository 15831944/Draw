///////////////////////////////////////////////////////////////////////////////
// SROpStack.h
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
// CREATED:		May 17, 2000
//


#ifndef __Stacks_H__
#define __Stacks_H__

#include "SRFormuladefines.h"
#include <StingrayExportDefs.h>

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SRAbstractStackItem
//
//---------*---------*---------*---------*---------*---------*---------*-----
class SRAbstractStackItem
{
	// Construction / Destruction
public:
	TOOLKIT_API SRAbstractStackItem(char * lpszToken);
	TOOLKIT_API virtual ~SRAbstractStackItem();

	// Accessors
public:
	TOOLKIT_API virtual char * GetToken();
protected:
	TOOLKIT_API void SetToken(char * lpszToken);

	// Data members
public:
	SRAbstractStackItem* m_pNext;
protected:
	char * m_lpszToken;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SROperatorStackItem
//
//---------*---------*---------*---------*---------*---------*---------*-----

#define OPER_UNKNOWN	-1
#define OPER_MIN		 0
#define OPER_FUNCTION	 1
#define OPER_OPERATOR	 2
#define OPER_NOTOPERATOR 3
#define OPER_OPENPAREN	 4
#define OPER_CLOSEPAREN	 5
#define OPER_COMMA		 6
#define OPER_EOF		 7
#define OPER_MAX		 8

class SROperatorStackItem : public SRAbstractStackItem
{
	// Construcion / Destruction
public:
	TOOLKIT_API SROperatorStackItem(char * lpszToken, int ot, int nOpCnt = 0);
	TOOLKIT_API virtual ~SROperatorStackItem();

	// Operations
public:
	TOOLKIT_API int GetOperationType();
	TOOLKIT_API int	GetOperandCount();
	TOOLKIT_API void SetOperandCount(int nCount);
	TOOLKIT_API void IncrementOperandCount();
	TOOLKIT_API void DecrementOperandCount();
protected:
	TOOLKIT_API void SetOperationType(int ot);

	// Data members
protected:
	int m_nType;
	int	m_nOpCount;
};

//---------*---------*---------*---------*---------*---------*---------*-----
//
// SROperandStackItem
//
//---------*---------*---------*---------*---------*---------*---------*-----

// Operand types
#define OPAND_UNKNOWN		-1		// Indicates unknown/uninitialized operand type
#define OPAND_MIN			 0		// Used to verify operand type range
#define OPAND_A1_CELL		 1
#define OPAND_RC_CELL		 2
#define OPAND_A1_CELL_RANGE	 3
#define OPAND_RC_CELL_RANGE	 4
#define OPAND_NAMED_RANGE	 5
#define OPAND_INTEGER		 6
#define OPAND_FLOAT			 7
#define OPAND_EXPONENTIAL	 8
#define OPAND_HEXADECIMAL	 9
#define OPAND_STRING		10
#define OPAND_BOOLEAN		11
#define OPAND_MAX			12		// Used to verify operand type range

class SROperandStackItem : public SRAbstractStackItem
{
	// Construcion / Destruction
public:
	TOOLKIT_API SROperandStackItem(char * lpszToken, int ot);
	TOOLKIT_API virtual ~SROperandStackItem();

	// Operations
public:
	TOOLKIT_API bool GetTokenAsBoolean(bool* p);
	TOOLKIT_API bool GetTokenAsDouble(double* p);
	TOOLKIT_API bool GetTokenAsInteger(int* p);
	TOOLKIT_API bool GetLengthOfTokenAsString(int* p);
	TOOLKIT_API bool GetTokenAsString(char * lpsz, int nSize);

	// Accessors
public:
	TOOLKIT_API int GetOperandType();
protected:
	TOOLKIT_API void SetOperandType(int ot);

	// Helpers
protected:
	TOOLKIT_API double ExpToDouble(char * lpsz);
	TOOLKIT_API int HexToInt(char * lpsz);
	TOOLKIT_API int GetHexDigit(char c);

	// Data members
protected:
	int m_nOpType;
};


//---------*---------*---------*---------*---------*---------*---------*-----
//
// SROpStack
//
//---------*---------*---------*---------*---------*---------*---------*-----
class SROpStack
{
	// Construcion / Destruction
public:
	TOOLKIT_API SROpStack();
	TOOLKIT_API ~SROpStack();

	// Operations
public:
	TOOLKIT_API void Push(SRAbstractStackItem* pItem);
	TOOLKIT_API SRAbstractStackItem* Pop();
	TOOLKIT_API SRAbstractStackItem* Peek();

	TOOLKIT_API int GetStackLength();

	// Data members
protected:
	SRAbstractStackItem* m_pTop;
};

#endif //__Stacks_H__
