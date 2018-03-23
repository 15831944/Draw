///////////////////////////////////////////////////////////////////////////////
// gxhexbyte.h
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


#ifndef _HEX2BYTE_H_
#define _HEX2BYTE_H_
// Use these routine for testing if you are 
// implementing write for additional fields

// Call the right function depending on
// whether we are using UNICODE.

#ifdef UNICODE
	#define Hex2Bytes	Hex2BytesW
	#define Char2Hex	Char2HexW
#else
	#define Hex2Bytes	Hex2BytesA
	#define Char2Hex	Char2HexA
#endif

// Function Prototypes

LONG WINAPI Hex2BytesW(LPWSTR szRecord, 
                       PBYTE pBuf);

LONG WINAPI Hex2BytesA(LPSTR szRecord, 
                       PBYTE pBuf);

BYTE WINAPI Char2HexW(WCHAR wch);

BYTE WINAPI Char2HexA(CHAR ch);

#endif
