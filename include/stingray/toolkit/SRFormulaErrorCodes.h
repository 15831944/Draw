///////////////////////////////////////////////////////////////////////////////
// ErrorCodes.h
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
// MODIFIED:	
//		XXX00	MM.DD.YY	<BUG#> - Description.
//
//				10.10.00	appropriated for generic formula engine by jimp
//

#ifndef __ErrorCodes_h__
#define __ErrorCodes_h__


//---------*---------*---------*---------*---------*---------*---------*-----
//
// Base errors
//
//---------*---------*---------*---------*---------*---------*---------*-----
#define SRERR_NONE					  0x0000
#define SRERR_SCAN_BASE				0x0000
#define SRERR_OPER_BASE				0x1000

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Scanner errors
//
//---------*---------*---------*---------*---------*---------*---------*-----
#define SRERR_SCAN_NONE				  SRERR_NONE
#define SRERR_SCAN_INTERNAL			SRERR_SCAN_BASE + 0x01
#define SRERR_SCAN_INVALIDEXPR	SRERR_SCAN_BASE + 0x02
#define SRERR_SCAN_			        SRERR_SCAN_BASE + 0x01
#define SRERR_SCAN_			        SRERR_SCAN_BASE + 0x01
#define SRERR_SCAN_			        SRERR_SCAN_BASE + 0x01

//---------*---------*---------*---------*---------*---------*---------*-----
//
// Operator errors
//
//---------*---------*---------*---------*---------*---------*---------*-----
#define SRERR_OPER_NONE				      SRERR_NONE
#define SRERR_OPER_INTERNAL			    SRERR_OPER_BASE + 0x01
#define SRERR_OPER_ARGCOUNT			    SRERR_OPER_BASE + 0x02
#define SRERR_OPER_ARGTYPE			    SRERR_OPER_BASE + 0x03
#define SRERR_OPER_ARGOUTOFRANGE	  SRERR_OPER_BASE + 0x04
#define SRERR_OPER_DIVIDEBYZERO		  SRERR_OPER_BASE + 0x05
#define SRERR_OPER_MISSING_OPER		  SRERR_OPER_BASE + 0x06
#define SRERR_OPER_MISMATCH_PARENS  SRERR_OPER_BASE + 0x07

//---------*---------*---------*---------*---------*---------*---------*-----
//
//Error Literal Descriptions
//
//---------*---------*---------*---------*---------*---------*---------*-----
#define SRERR_DESC_MISMATCH_PARENS		 _T("Mismatched Parens.")
#define SRERR_DESC_DIV_BY_ZERO			   _T("Divide By Zero.")
#define SRERR_DESC_INVALID_EXPRESSION	 _T("Invalid Expression.")
#define SRERR_DESC_MISSING_OPER		     _T("Missing Operator.")

#endif // __ErrorCodes_h__
