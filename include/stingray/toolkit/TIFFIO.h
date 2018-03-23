///////////////////////////////////////////////////////////////////////////////
// TIFFIO.h
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

#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

#ifndef __TIFFIO_H__
#define	__TIFFIO_H__

/*
 * TIFF I/O Library Definitions.
 */
#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef __TIFF_H__
#include "toolkit\tiff.h"
#endif

#include <StingrayExportDefs.h>

/*
 * TIFF is defined as an incomplete type to hide the
 * library's internal data structures from clients.
 */
typedef	struct tiff TIFF;

/*
 * The following typedefs define the intrinsic size of
 * data types used in the *exported* interfaces.  These
 * definitions depend on the proper definition of types
 * in tiff.h.  Note also that the varargs interface used
 * pass tag types and values uses the types defined in
 * tiff.h directly.
 *
 * NB: ttag_t is unsigned int and not unsigned short because
 *     ANSI C requires that the type before the ellipsis be a
 *     promoted type (i.e. one of int, unsigned int, pointer,
 *     or double).
 * NB: tsize_t is int32 and not uint32 because some functions
 *     return -1.
 * NB: toff_t is not off_t for many reasons; TIFFs max out at
 *     32-bit file offsets being the most important
 */
typedef	unsigned int ttag_t;	/* directory tag */
typedef	short tdir_t;		/* directory index */
typedef	WORD tsample_t;	/* sample number */
typedef	long tstrip_t;	/* strip number */
typedef DWORD ttile_t;		/* tile number */
typedef	SEC_LONG tsize_t;		/* i/o size in bytes */
#ifdef WIN32
typedef	void* tdata_t;		/* image data ref */
#else
// typedef	void FAR* tdata_t;		/* image data ref */ 
typedef void huge * tdata_t;  // AAB 12/10
// typedef	void FAR* thandle_t;	/* client data handle */
#endif
typedef HFILE thandle_t;
typedef	long toff_t;		/* file offset */

#ifndef NULL
#define	NULL	0
#endif

/*
 * Flags to pass to TIFFPrintDirectory to control
 * printing of data structures that are potentially
 * very large.   Bit-or these flags to enable printing
 * multiple items.
 */
#define	TIFFPRINT_NONE		0x0		/* no extra info */
#define	TIFFPRINT_STRIPS	0x1		/* strips/tiles info */
#define	TIFFPRINT_CURVES	0x2		/* color/gray response curves */
#define	TIFFPRINT_COLORMAP	0x4		/* colormap */
#define	TIFFPRINT_JPEGQTABLES	0x100		/* JPEG Q matrices */
#define	TIFFPRINT_JPEGACTABLES	0x200		/* JPEG AC tables */
#define	TIFFPRINT_JPEGDCTABLES	0x200		/* JPEG DC tables */

/*
 * Macros for extracting components from the
 * packed ABGR form returned by TIFFReadRGBAImage.
 */
#define	TIFFGetR(abgr)	((abgr) & 0xff)
#define	TIFFGetG(abgr)	(((abgr) >> 8) & 0xff)
#define	TIFFGetB(abgr)	(((abgr) >> 16) & 0xff)
#define	TIFFGetA(abgr)	(((abgr) >> 24) & 0xff)

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _INC_STDARG
#include <stdarg.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif
typedef	void (*TIFFErrorHandler)(const TCHAR* module, const _TCHAR* fmt, va_list);
typedef	tsize_t (*TIFFReadWriteProc)(thandle_t, tdata_t, tsize_t);
typedef	toff_t (*TIFFSeekProc)(thandle_t, toff_t, short);
//AAB typedef	long (*TIFFCloseProc)(thandle_t);
typedef	thandle_t (*TIFFCloseProc)(thandle_t);
typedef	toff_t (*TIFFSizeProc)(thandle_t);
typedef	long (*TIFFMapFileProc)(thandle_t, tdata_t*, toff_t*);
typedef	void (*TIFFUnmapFileProc)(thandle_t, tdata_t, toff_t);

extern	TOOLKIT_API const char* TIFFGetVersion(void);

extern	TOOLKIT_API void TIFFClose(TIFF*);
extern	TOOLKIT_API long TIFFFlush(TIFF*);
extern	TOOLKIT_API long TIFFFlushData(TIFF*);
extern	TOOLKIT_API long TIFFGetField(TIFF*, ttag_t, ...);
extern	TOOLKIT_API long TIFFVGetField(TIFF*, ttag_t, va_list);
extern	TOOLKIT_API long TIFFGetFieldDefaulted(TIFF*, ttag_t, ...);
extern	TOOLKIT_API long TIFFVGetFieldDefaulted(TIFF*, ttag_t, va_list);
extern	TOOLKIT_API long TIFFReadDirectory(TIFF*);
extern	TOOLKIT_API tsize_t TIFFScanlineSize(TIFF*);
extern	TOOLKIT_API tsize_t TIFFStripSize(TIFF*);
extern	TOOLKIT_API tsize_t TIFFVStripSize(TIFF*, DWORD);
extern	TOOLKIT_API tsize_t TIFFTileRowSize(TIFF*);
extern	TOOLKIT_API tsize_t TIFFTileSize(TIFF*);
extern	TOOLKIT_API tsize_t TIFFVTileSize(TIFF*, DWORD);
extern	TOOLKIT_API long TIFFFileno(TIFF*);
extern	TOOLKIT_API UINT TIFFGetMode(TIFF*);
//AAB extern	TOOLKIT_API long TIFFGetMode(TIFF*);
extern	TOOLKIT_API long TIFFIsTiled(TIFF*);
extern	TOOLKIT_API long TIFFIsByteSwapped(TIFF*);
extern	TOOLKIT_API DWORD TIFFCurrentRow(TIFF*);
extern	TOOLKIT_API tdir_t TIFFCurrentDirectory(TIFF*);
extern	TOOLKIT_API tstrip_t TIFFCurrentStrip(TIFF*);
extern	TOOLKIT_API ttile_t TIFFCurrentTile(TIFF*);
extern	TOOLKIT_API long TIFFReadBufferSetup(TIFF*, tdata_t, tsize_t);
extern	TOOLKIT_API long TIFFLastDirectory(TIFF*);
extern	TOOLKIT_API long TIFFSetDirectory(TIFF*, tdir_t);
extern	TOOLKIT_API long TIFFSetField(TIFF*, ttag_t, ...);
extern	TOOLKIT_API long TIFFVSetField(TIFF*, ttag_t, va_list);
extern	TOOLKIT_API long TIFFWriteDirectory(TIFF *);
#if defined(c_plusplus) || defined(__cplusplus)
extern	TOOLKIT_API void TIFFPrintDirectory(TIFF*, FILE*, long = 0);
extern	TOOLKIT_API long TIFFReadScanline(TIFF*, tdata_t, DWORD, tsample_t = 0);
extern	TOOLKIT_API long TIFFWriteScanline(TIFF*, tdata_t, DWORD, tsample_t = 0);
//AAB extern	TOOLKIT_API long TIFFReadRGBAImage(TIFF*,
//AAB	                                           unsigned long, unsigned long, 
//AAB                                            unsigned long*, long stop = 0);
extern	TOOLKIT_API long TIFFReadRGBAImage(TIFF*, DWORD, DWORD, LPDWORD, long stop = 0);
#else
extern	TOOLKIT_API void TIFFPrintDirectory(TIFF*, FILE*, long);
extern	TOOLKIT_API long TIFFReadScanline(TIFF*, tdata_t, DWORD, tsample_t);
extern	TOOLKIT_API long TIFFWriteScanline(TIFF*, tdata_t, DWORD, tsample_t);
extern	TOOLKIT_API long TIFFReadRGBAImage(TIFF*, DWORD, DWORD, LPDWORD, long stop);
#endif
extern	TOOLKIT_API TIFF* TIFFOpen(const TCHAR*, const TCHAR*);
extern	TOOLKIT_API TIFF* TIFFFdOpen(thandle_t, const char*, const char*);
extern	TOOLKIT_API TIFF* TIFFClientOpen(const TCHAR* name, const TCHAR* mode,
	                                        thandle_t clientdata,
	                                        TIFFReadWriteProc readproc, TIFFReadWriteProc writeproc,
	                                        TIFFSeekProc seekproc, TIFFCloseProc closeproc,
	                                        TIFFSizeProc sizeproc,
	                                        TIFFMapFileProc mapproc, TIFFUnmapFileProc unmapproc);
extern	TOOLKIT_API const TCHAR* TIFFFileName(TIFF*);
extern	TOOLKIT_API void TIFFError(const _TCHAR*, const TCHAR*, ...);
extern	TOOLKIT_API void TIFFWarning(const TCHAR*, const TCHAR*, ...);
extern	TOOLKIT_API TIFFErrorHandler TIFFSetErrorHandler(TIFFErrorHandler handler);
extern	TOOLKIT_API TIFFErrorHandler TIFFSetWarningHandler(TIFFErrorHandler handler);
extern	TOOLKIT_API ttile_t TIFFComputeTile(TIFF*, DWORD, DWORD, DWORD, tsample_t);
extern	TOOLKIT_API long TIFFCheckTile(TIFF*, DWORD, DWORD, DWORD, tsample_t);
extern	TOOLKIT_API ttile_t TIFFNumberOfTiles(TIFF*);
extern	TOOLKIT_API tsize_t TIFFReadTile(TIFF*, tdata_t, DWORD, DWORD, DWORD, tsample_t);
extern	TOOLKIT_API tsize_t TIFFWriteTile(TIFF*, tdata_t, DWORD, DWORD, DWORD, tsample_t);
extern	TOOLKIT_API tstrip_t TIFFComputeStrip(TIFF*, DWORD, tsample_t);
extern	TOOLKIT_API tstrip_t TIFFNumberOfStrips(TIFF*);
extern	TOOLKIT_API tsize_t TIFFReadEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFReadRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFReadEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFReadRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFWriteEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFWriteRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFWriteEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	TOOLKIT_API tsize_t TIFFWriteRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	TOOLKIT_API void TIFFSetWriteOffset(TIFF*, toff_t);
extern	TOOLKIT_API void TIFFSwabShort(LPWORD);
extern	TOOLKIT_API void TIFFSwabLong(LPDWORD);
extern	TOOLKIT_API void TIFFSwabArrayOfShort(LPWORD, unsigned long);
extern	TOOLKIT_API void TIFFSwabArrayOfLong(LPDWORD, unsigned long);
//AAB extern	TOOLKIT_API void TIFFReverseBits(unsigned char *, unsigned long);
extern	TOOLKIT_API void TIFFReverseBits(LPBYTE, DWORD);
extern	TOOLKIT_API const unsigned char* TIFFGetBitRevTable(long);
extern	TOOLKIT_API void TIFFModeCCITTFax3(TIFF* tif, long isClassF);	/* XXX */
#if defined(__cplusplus)
}
#endif

#endif /* __TIFFIO_H__ */
