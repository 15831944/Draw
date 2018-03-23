///////////////////////////////////////////////////////////////////////////////
// TIF_FAX3.h
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

/*
 *  
 * Copyright (c) 1991, 1992 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

#ifndef __TIF_FAX3_H__
#define	__TIF_FAX3_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

/*
 * CCITT Group 3 compression/decompression definitions.
 */
#define	FAX3_CLASSF	TIFF_OPT0	/* use Class F protocol */

/* The following are for use by Compression=2, 32771, and 4 (T.6) algorithms */
#define	FAX3_NOEOL	    TIFF_OPT1	/* no EOL code at end of row */
#define	FAX3_BYTEALIGN	TIFF_OPT2	/* force byte alignment at end of row */
#define	FAX3_WORDALIGN	TIFF_OPT3	/* force word alignment at end of row */

/*
 * Compression+decompression state blocks are
 * derived from this ``base state'' block.
 */
typedef struct {
	short	data;			     /* current i/o byte */
	short	bit;			     /* current i/o bit in byte */
	short	white;			   /* value of the color ``white'' */
	DWORD	rowbytes;		   /* XXX maybe should be a long? */
	DWORD	rowpixels;		 /* XXX maybe should be a long? */
	enum mode{ 				   /* decoding/encoding mode */
	    G3_1D,			     /* basic 1-d mode */
	    G3_2D			       /* optional 2-d mode */
	} tag;
	const BYTE *bitmap;  /* bit reversal table */
	BYTE *refline;		   /* reference line for 2d decoding */
} Fax3BaseState;

#define	Fax3FlushBits(tif, sp) {			\
	if ((tif)->tif_rawcc >= (tif)->tif_rawdatasize)	\
		(void) TIFFFlushData1(tif);		\
	*(tif)->tif_rawcp++ = (sp)->bitmap[(sp)->data];	\
	(tif)->tif_rawcc++;				\
	(sp)->data = 0;					\
	(sp)->bit = 8;					\
}

#endif /* __TIF_FAX3_H__ */
