///////////////////////////////////////////////////////////////////////////////
// gxexhdr.h : Excel field constants
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

#ifndef _GXEX_HDR_H__
#define _GXEX_HDR_H__

#define typeIndex		0x000B
#define typeFilePass	0x002F
#define typeBOF			0x0809
#define typeEOF			0x000A
#define typeRow			0x0208
#define typeLabel		0x0204
#define typeRk			0x027E
#define typeMulRk		0x00BD
#define typeXF			0x00E0
#define typeFont		0x0031
#define typeStyle		0x0293
#define typePalette		0x0092
#define typeColInfo		0x007d
#define typeFormat		0x041e
#define typeFormula		0x0006
#define typeBoundSheet	0x0085
#define typeNumber		0x0203
#define typeBlank		0x0201
#define typeMulBlank	0x00BE
#define typeSST			0x00FC
#define typeSSLabel		0x00FD
#define typeDimension	0x0200
#define typeWindow2		0x023e
#define typeMergedCell	0x00E5
#define typeWindow1		0x003D
#define typegxString	0x0207
#define typeSF			0x04BC // Shared formula support

#define ixfNULL			0x0FFF

////////////////////////////////
//  Formula ptg defines																
////////////////////////////////

#define	ptgAdd			0x03
#define	ptgSub			0x04
#define	ptgMul			0x05
#define	ptgDiv			0x06
#define	ptgPower		0x07
#define	ptgConcat		0x08
#define	ptgLT			0x09
#define	ptgLE			0x0a
#define	ptgEQ			0x0b
#define	ptgGE			0x0c
#define	ptgGT			0x0d
#define	ptgNE			0x0e
#define	ptgIsect		0x0f
#define	ptgRange		0x11
#define	ptgUplus		0x12
#define	ptgUminus		0x13
#define	ptgPercent		0x14
#define	ptgParen		0x15
#define	ptgStr			0x17
#define	ptgAttr			0x19
#define	ptgErr			0x1c
#define	ptgBool			0x1d
#define	ptgInt			0x1e
#define	ptgNum			0x1f

#define	ptgArray		0x20
#define	ptgFunc			0x21
#define	ptgFuncVar		0x22
#define	ptgName			0x23
#define	ptgRef			0x24
#define	ptgArea			0x25
#define	ptgMemArea		0x26
#define	ptgMemErr		0x27
#define	ptgMemNoMem		0x28
#define	ptgMemFunc		0x29
#define	ptgRefErr		0x2a
#define	ptgAreaErr		0x2b
#define	ptgRefN			0x2c
#define	ptgAreaN		0x2d
#define	ptgMemAreaN		0x2e
#define	ptgMemNoMemN	0x2f
#define ptgNameX		0x39
#define ptgRef3d		0x3a
#define ptgArea3d		0x3b
#define ptgRefErr3d		0x3c
#define ptgAreaErr3d	0x3d

#define ptgArrayV		0x40
#define ptgFuncV		0x41
#define ptgFuncVarV		0x42
#define ptgNameV		0x43
#define ptgRefV			0x44
#define ptgAreaV		0x45
#define ptgMemAreaV		0x46
#define ptgMemErrV		0x47
#define ptgMemNoMemV	0x48
#define ptgMemFuncV		0x49
#define ptgRefErrV		0x4a
#define ptgAreaErrV		0x4b
#define ptgRefNV		0x4c
#define ptgAreaNV		0x4d
#define ptgMemAreaNV	0x4e
#define ptgMemNoMemNV	0x4f
#define ptgFuncCEV		0x58
#define ptgNameXV		0x59
#define ptgRef3dV		0x5a
#define ptgArea3dV		0x5b
#define ptgRefErr3dV	0x5c
#define ptgAreaErr3dV	0x5d

#define ptgArrayA		0x60
#define ptgFuncA		0x61
#define ptgFuncVarA		0x62
#define ptgNameA		0x63
#define ptgRefA			0x64
#define ptgAreaA		0x65
#define ptgMemAreaA		0x66
#define ptgMemErrA		0x67
#define ptgMemNoMemA	0x68
#define ptgMemFuncA		0x69
#define ptgRefErrA		0x6a
#define ptgAreaErrA		0x6b
#define ptgRefNA		0x6c
#define ptgAreaNA		0x6d
#define ptgMemAreaNA	0x6e
#define ptgMemNoMemNA	0x6f
#define ptgFuncCEA		0x78
#define ptgNameXA		0x79
#define ptgRef3dA		0x7a
#define ptgArea3dA		0x7b
#define ptgRefErr3dA	0x7c
#define ptgAreaErr3dA	0x7d

#define	xlfAnd			36
#define	xlfOr			37
#define	xlfNot			38
#define	xlfMod			39

#define	xlfOffset		78

typedef struct rkrec
		{
	SHORT ixfe;		// index to XF record 
	long RK;		// RK number 
		}
	RKREC;

#endif
