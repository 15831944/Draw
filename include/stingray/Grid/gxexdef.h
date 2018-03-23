///////////////////////////////////////////////////////////////////////////////
// gxexdef.h
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

#ifndef _GX_EX_TBL_RECSIZE_H__
#define	_GX_EX_TBL_RECSIZE_H__

// #include <StingrayExportDefs.h>

#define GX_EX_FIXEDHEADER							4 // The fixed stream header for all records

#define GXEX_SIZEOF_XF								24 //The length of the XF record in bytes

#define GX_EX_MAXFONTRECSIZE						20 + 2*255 // For the font record

#define GX_EX_FONTRECSIZE							20

#define GX_EX_SIZEOF_RK								14 // The RK record

#define GX_EX_SIZEOF_NUMBER							18 // The RK record

#define GX_EX_SIZEOF_LABEL							13 // Label fixed size

#define	GX_EX_SIZEOF_COLINFO						15 // ColInfo size

#define GX_EX_SIZEOF_ROWINFO						20 // Row information size

#define GX_EXCEL_WIDTHFACTOR						1

#define GX_EX_FIXEDOFFSET							4

#define GX_EX_FIXED_BSHEET							4 + 2 + 2 //lbplyPos+grBit+cch

#define GX_EX_SIZE_EOF								4

#define GX_EX_NUM_DEFAULTXF							15

#define GX_EX_SIZEOF_BLANK							10

#define GX_EX_COLOR_OFFSET							0x08

#define GX_EX_SIZEOF_DIMENSION						18

#define GX_EX_DEFAULTSIZEINCREASECOL				10 // number of columns added to cols got from dimension

#define GX_EX_DEFAULTSIZEINCREASEROW				100 // number of rows added to rows got from dimension

#define GX_EX_DEFAULTSIZECOL						257 // number of columns added to cols got from dimension

#define GX_EX_DEFAULTSIZEROW						65535 // number of rows added to rows got from dimension

#define GX_RK_FIXEDBLOCK							10 

#define GX_EX_SIZE_BUILTINSTYLE						8
 
#define GX_EX_SIZEOF_WRITEBUFFER					500

#define GX_EX_SIZEOF_BOF							20

#define GX_EX_SIZEOF_FORMULA						26

#define GX_EX_SIZEMAX_FORMULA						512

#define GX_EX_SIZEOF_WINDOW2						22

#define GX_EX_NEW_FILE								GX_INVALID

#define GXEXNOPATTERN								63  // same as GXNOPATTERN

#define GX_EX_BASESTYLEMAX							256 // maximum number of base styles

#define GX_EX_DEFNUMTABS							3   // Default number of tabs

#define GX_EX_DEFEXTSIZE							3   // default extension size for files

#define GX_EX_WCHARSIZE								2   // number of bytes in a wide char

#define GX_EX_NUMPALCOLORS							56  // Number of colors in a palette

#define GX_EX_SIZEOF_MERGEDCELL						14  // size of a merged cell record with one set of values 

#define GX_EX_SIZEOF_CONTINUE						5	// size of the continue field header that is to be ignored

#define	GX_EX_SIZEOFRUNSSST							4	

#define GX_EX_MAXRECSIZE							8224

#define GX_EX_SIZEOF_VALBUF							8

#define GX_EX_FIXED_STRING							3							


struct GRID_API formulaStruct
{
		WORD rw; //2
		WORD col; //2
		short ixfe; //2
		BYTE num[8]; //8
		WORD grbit; //2
		DWORD chn; //4
		WORD cce; //2
		BYTE* pVarParsed; 
};

#endif //_GX_EX_TBL_RECSIZE_H__
