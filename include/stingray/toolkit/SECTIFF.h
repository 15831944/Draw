///////////////////////////////////////////////////////////////////////////////
// SECTIFF.h
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
//    AAB	6/22/95	Started
//    MSW       9/30/95 Code Review
//

#ifndef __SECTIFF_H__
#define __SECTIFF_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

#ifndef WIN32
#pragma warning(disable : 4103)
#endif 

#ifndef __SFL_SECIMAGE_H__
#include "Foundation\Image\MFC\secimage.h"
#endif

#ifndef __TIFFIO_H__
#include "toolkit\tiffio.h"
#endif

#ifndef __TIFFIOP_H__
#include "toolkit\tiffiop.h"
#endif

#ifndef __TIFF_H__
#include "toolkit\tiff.h"
#endif

#ifndef __T4_H__
#include "toolkit\t4.h"
#endif

#include <StingrayExportDefs.h>

      
#ifdef WIN32
typedef LPBYTE* LPPBYTE;
typedef LPBYTE LPBITS;
#else
typedef LPBYTE FAR* LPPBYTE;
typedef BYTE huge * LPBITS;
#endif


typedef void (SECTiff::*tileSeparateRoutine)
	(LPBYTE, LPBYTE, LPBYTE, LPBYTE, LPBYTE, DWORD, DWORD, int, int);

typedef void (SECTiff::*tileContigRoutine)
    (LPBITS, LPBYTE, LPBYTE, DWORD, DWORD, int, int);

typedef void (SECTiff::*geti_tileSeparateRoutine)
	(LPDWORD, LPBYTE, LPBYTE, LPBYTE, LPRGBvalue, DWORD, DWORD, long, long);

typedef void (SECTiff::*geti_tileContigRoutine)
    (LPDWORD, LPBYTE, LPRGBvalue, DWORD, DWORD, long, long);
	 
/////////////////////////////
// AutoDuck tag block block for SECTiff
// adinsert AutoDuck insertion point for SECTiff
//@doc SECTiff
//@class SECTiff is a <c SECImage> derived class which supports the TIFF (Tagged Image File Format) 
// released by Aldus Corporation and commonly used in scanning and desktop publishing applications.  
// SECTiff is based on the version 6.0 of the TIFF specification.
//
//@comm The TIFF file format supports image resolutions from 1 bit per pixel images to 24 bits per 
// pixel images.  Compression schemes which can be used in TIFF can include 
//
//·	Uncompressed<nl>
//·	RLE (run length encoded)<nl>
//·	CCITT Group 3 and 4<nl>
//·	LZW (see discussion below)<nl>
//·	JPEG (see discussion below)<nl>
//
// Currently SECTiff supports uncompressed, RLE and (optionally) LZW compression.   Although 
// version 6 specifies JPEG compression support, the current specification of JPEG support 
// is actually being redesigned, and many caution against the use of supporting JPEG compression.  
// An excellent discussion of the issues of JPEG support can be found in the text "Encyclopedia of 
// Graphic File Formats" published by O’Reilly & Associates, Inc.  For this reason, SECTiff 
// does not currently support JPEG compression in TIFF files.
//
// Another issue for TIFF users concerns the use of LZW compression.  Similar to GIF files, 
// LZW compression uses a compression scheme patented by Unisys.  Users wishing to support use 
// of TIFF images using LZW compression must license the technology from Unisys (see <c SECGif> for 
// full details).  By default, SECTiff disables LZW support.   If you wish to enable 
// LZW support, compile SECTiff with the SEC_TIFF_LZW_SUPPORTED value #defined in the 
// application project.
//
// See the IMAGETST samples in the \SAMPLES\TOOLKIT\STANDARD\IMAGETST directory for a demonstration of 
// this class.
//@xref <c SECImage> <c SECGif>
//@base public | SECImage
class SECTiff : public stingray::foundation::SECImage
{
    TOOLKIT_DECLARE_SERIAL(SECTiff);

// Construction
    TOOLKIT_API SECTiff();

// Operations
public:
    TOOLKIT_API virtual BOOL LoadImage (LPCTSTR lpszFileName); /* Load native format & convert to DIB */
    TOOLKIT_API virtual BOOL SaveImage (LPCTSTR lpszFileName); /* Save as native format */

// Overrides
protected:
    TOOLKIT_API virtual BOOL DoLoadImage(CFile* pFile);
    TOOLKIT_API virtual BOOL DoSaveImage(CFile* pFile);

// Implementation
public:
    int    m_nCompression;

protected:
    TIFF * m_lpTif;
    WORD	 m_wOrientation;
	WORD	m_wExtraSamples;
	WORD	m_wPlanarConfig;
    WORD   m_wBPS; // bits per sample
    WORD   m_wSPP;	// samples per pixel
    WORD   m_wPhoto;
    WORD   m_wBPP;
    LPBYTE m_lpPic;
    WORD   m_wColType;	// 8==8bit data, 24==true colors
    LPBYTE *m_lpBWmap;
	LPDWORD	*m_lpgetiBWmap;
    LPBYTE *m_lpPALmap;
	LPDWORD *m_lpgetiPALmap;
    LPBYTE m_lpMap;
    int	 m_nStopOnErr;
    WORD   m_wYCbCrHorizSampling;
    WORD   m_wYCbCrVertSampling;
    float *m_lpYCbCrCoeffs;
    float *m_lpRefBlackWhite;
	LPWORD	redcmap;
	LPWORD	greencmap;
	LPWORD 	bluecmap;
	float	m_D1, m_D2, m_D3, m_D4;	//used in packed RGB routines in tif_get.cpp

	//in use for 
	WORD wYCbCrVertSampling;
	WORD wYCbCrHorizSampling;
	float *lpRefBlackWhite;
	TOOLKIT_API void pack1(int *pnByte, DWORD *pdwWdith, DWORD *pdwTotalBytes, LPBITS *cp, LPBYTE *bw, DWORD wMax, DWORD dwBytesInLine);
	LPPBYTE lppBWmap;
	LPPBYTE lppPALmap;

	TOOLKIT_API tileSeparateRoutine SECpickTileSeparateCase(LPBYTE);
	TOOLKIT_API geti_tileSeparateRoutine geti_pickTileSeparateCase(TIFF*, LPRGBvalue);

	tileSeparateRoutine m_fpTileSeparate;
	geti_tileSeparateRoutine m_fpgetiTileSeparate;

	TOOLKIT_API tileContigRoutine SECpickTileContigCase(LPBYTE);
	TOOLKIT_API geti_tileContigRoutine geti_pickTileContigCase(TIFF*, LPRGBvalue);

	tileContigRoutine m_fpContigRoutine;
	geti_tileContigRoutine m_fpgetiContigRoutine;

	TOOLKIT_API void geti_initYCbCrConversion(void);

	TOOLKIT_API void SECput8bitcmaptile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput4bitcmaptile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput2bitcmaptile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput1bitcmaptile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputgreytile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput1bitbwtile(LPBITS cp, LPBYTE pp, LPBYTE pMap, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput2bitbwtile(LPBITS cp, LPBYTE pp, LPBYTE pMap, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECput4bitbwtile(LPBITS cp, LPBYTE pp, LPBYTE pMap, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputRGBcontig8bittile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputRGBcontig16bittile(LPBITS cp, LPBYTE tpp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputRGBseparate8bittile(LPBYTE cp, LPBYTE r, LPBYTE g, LPBYTE b, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputRGBseparate16bittile(LPBYTE cp, LPBYTE pr, LPBYTE pg, LPBYTE pb, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);
	TOOLKIT_API void SECputRGBContigYCbCrClump(LPBYTE cp, LPBYTE pp, WORD cw, WORD ch, DWORD w, int n, int fromskew, int toskew);
	TOOLKIT_API void SECputcontig8bitYCbCrtile(LPBITS cp, LPBYTE pp, LPBYTE Map, DWORD w, DWORD h, int fromskew, int toskew);

	TOOLKIT_API void geti_put8bitcmaptile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put4bitcmaptile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put2bitcmaptile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put1bitcmaptile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putgreytile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put1bitbwtile(LPDWORD cp, LPBYTE pp, LPRGBvalue pMap, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put2bitbwtile(LPDWORD cp, LPBYTE pp, LPRGBvalue pMap, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_put4bitbwtile(LPDWORD cp, LPBYTE pp, LPRGBvalue pMap, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBcontig8bittile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBcontig16bittile(LPDWORD cp, LPBYTE tpp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBseparate8bittile(LPDWORD cp, LPBYTE r, LPBYTE g, LPBYTE b, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBseparate16bittile(LPDWORD cp, LPBYTE pr, LPBYTE pg, LPBYTE pb, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBContigYCbCrClump(LPDWORD cp, LPBYTE pp, DWORD cw, DWORD ch, DWORD w, int n, long fromskew, long toskew);
	TOOLKIT_API void geti_putcontig8bitYCbCrtile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	TOOLKIT_API void geti_putRGBcontig8bitCMYKtile(LPDWORD cp, LPBYTE pp, LPRGBvalue Map, DWORD w, DWORD h, long fromskew, long toskew);
	
    TOOLKIT_API BOOL loadPalette();
    TOOLKIT_API BOOL loadColors();
    TOOLKIT_API WORD loadImageData();
    TOOLKIT_API void ConvertRGB();
    TOOLKIT_API WORD checkcmap(int, LPWORD, LPWORD, LPWORD);
    TOOLKIT_API WORD gt();
    TOOLKIT_API int gtTileContig();
    TOOLKIT_API int gtTileSeparate();
    TOOLKIT_API int gtStripContig();
    TOOLKIT_API int gtStripSeparate();
    TOOLKIT_API int makebwmap();
    TOOLKIT_API int makecmap();
    TOOLKIT_API void setupColormap(TIFF *, LPBYTE, LPBYTE, LPBYTE);
    TOOLKIT_API int WriteTIFF(FILE *, LPBYTE, int, LPBYTE, LPBYTE, LPBYTE, int, int, const TCHAR *, TCHAR *);
    TOOLKIT_API void SECinitYCbCrConversion();
    TOOLKIT_API DWORD setorientation(DWORD);
    TOOLKIT_API virtual void Serialize(CArchive& ar);
public:   
    TOOLKIT_API LPVOID _TIFFmalloc(size_t);
    TOOLKIT_API LPVOID _TIFFrealloc(LPVOID, size_t);
    TOOLKIT_API void _TIFFfree(LPVOID);
    TOOLKIT_API UINT _TIFFgetMode(const TCHAR* mode, const TCHAR* module);
    TOOLKIT_API const TIFFFieldInfo *TIFFFindFieldInfo(ttag_t, TIFFDataType);
    TOOLKIT_API const TIFFFieldInfo *TIFFFieldWithTag(ttag_t);
    TOOLKIT_API void _TIFFgetfield(TIFFDirectory*, ttag_t, ...);
    TOOLKIT_API long TIFFNoRowEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long TIFFNoStripEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long TIFFNoTileEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long TIFFNoRowDecode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long TIFFNoStripDecode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long TIFFNoTileDecode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API void TIFFNoPostDecode(TIFF*, tidata_t, tsize_t);
    TOOLKIT_API void TIFFSwab16BitData(TIFF*, tidata_t, tsize_t);
    TOOLKIT_API void TIFFSwab32BitData(TIFF*, tidata_t, tsize_t);
    TOOLKIT_API long TIFFFlushData1(TIFF*);
    TOOLKIT_API void TIFFFreeDirectory(TIFF*);
    TOOLKIT_API long TIFFDefaultDirectory(TIFF*);
    TOOLKIT_API long TIFFSetCompressionScheme(TIFF *, long);
    TOOLKIT_API void TIFFClose(TIFF*);
    TOOLKIT_API long TIFFFlush(TIFF*);
    TOOLKIT_API long TIFFFlushData(TIFF*);
    TOOLKIT_API long TIFFGetField(TIFF*, ttag_t, ...);
    TOOLKIT_API long TIFFVGetField(TIFF*, ttag_t, va_list);
    TOOLKIT_API long TIFFGetFieldDefaulted(TIFF*, ttag_t, ...);
    TOOLKIT_API long TIFFVGetFieldDefaulted(TIFF*, ttag_t, va_list);
    TOOLKIT_API long TIFFReadDirectory(TIFF*);
    TOOLKIT_API tsize_t TIFFScanlineSize(TIFF*);
    TOOLKIT_API tsize_t TIFFStripSize(TIFF*);
    TOOLKIT_API tsize_t TIFFVStripSize(TIFF*, DWORD);
    TOOLKIT_API tsize_t TIFFTileRowSize(TIFF*);
    TOOLKIT_API tsize_t TIFFTileSize(TIFF*);
    TOOLKIT_API tsize_t TIFFVTileSize(TIFF*, DWORD);
    TOOLKIT_API long TIFFFileno(TIFF*);
    TOOLKIT_API UINT TIFFGetMode(TIFF*);
    TOOLKIT_API long TIFFIsTiled(TIFF*);
    TOOLKIT_API long TIFFIsByteSwapped(TIFF*);
    TOOLKIT_API DWORD TIFFCurrentRow(TIFF*);
    TOOLKIT_API tdir_t TIFFCurrentDirectory(TIFF*);
    TOOLKIT_API tstrip_t TIFFCurrentStrip(TIFF*);
    TOOLKIT_API ttile_t TIFFCurrentTile(TIFF*);
    TOOLKIT_API long TIFFReadBufferSetup(TIFF*, tdata_t, tsize_t);
    TOOLKIT_API long TIFFLastDirectory(TIFF*);
    TOOLKIT_API long TIFFSetDirectory(TIFF*, tdir_t);
    TOOLKIT_API long TIFFSetField(TIFF*, ttag_t, ...);
    TOOLKIT_API long TIFFVSetField(TIFF*, ttag_t, va_list);
    TOOLKIT_API long TIFFWriteDirectory(TIFF *);
    TOOLKIT_API void TIFFPrintDirectory(TIFF*, FILE*, long = 0);
    TOOLKIT_API long TIFFReadScanline(TIFF*, tdata_t, DWORD, tsample_t = 0);
    TOOLKIT_API long TIFFWriteScanline(TIFF*, tdata_t, DWORD, tsample_t = 0);
    TOOLKIT_API long TIFFReadRGBAImage(TIFF*,
			   DWORD, DWORD, LPDWORD, long stop = 0);
    TOOLKIT_API TIFF* TIFFOpen(const TCHAR*, const TCHAR*);
    TOOLKIT_API TIFF* TIFFFdOpen(thandle_t, const TCHAR*, const TCHAR*);
    TOOLKIT_API TIFF* TIFFClientOpen(const TCHAR* name, const TCHAR* mode,
			 thandle_t clientdata,
			 TIFFReadWriteProc readproc, TIFFReadWriteProc writeproc,
			 TIFFSeekProc seekproc, TIFFCloseProc closeproc,
			 TIFFSizeProc sizeproc,
			 TIFFMapFileProc mapproc, TIFFUnmapFileProc unmapproc);
    TOOLKIT_API const TCHAR* TIFFFileName(TIFF*);
    TOOLKIT_API void TIFFError(const _TCHAR*, const TCHAR*, ...);
    TOOLKIT_API void TIFFWarning(const TCHAR*, const TCHAR*, ...);
    TOOLKIT_API TIFFErrorHandler TIFFSetErrorHandler(TIFFErrorHandler handler);
    TOOLKIT_API TIFFErrorHandler TIFFSetWarningHandler(TIFFErrorHandler handler);
    TOOLKIT_API ttile_t TIFFComputeTile(TIFF*, DWORD, DWORD, DWORD, tsample_t);
    TOOLKIT_API long TIFFCheckTile(TIFF*, DWORD, DWORD, DWORD, tsample_t);
    TOOLKIT_API ttile_t TIFFNumberOfTiles(TIFF*);
    TOOLKIT_API tsize_t TIFFReadTile(TIFF*,
			 tdata_t, DWORD, DWORD, DWORD, tsample_t);
    TOOLKIT_API tsize_t TIFFWriteTile(TIFF*,
			  tdata_t, DWORD, DWORD, DWORD, tsample_t);
    TOOLKIT_API tstrip_t TIFFComputeStrip(TIFF*, DWORD, tsample_t);
    TOOLKIT_API tstrip_t TIFFNumberOfStrips(TIFF*);
    TOOLKIT_API tsize_t TIFFReadEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFReadRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFReadEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFReadRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFWriteEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFWriteRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFWriteEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
    TOOLKIT_API tsize_t TIFFWriteRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
    TOOLKIT_API void TIFFSetWriteOffset(TIFF*, toff_t);
    TOOLKIT_API void TIFFSwabShort(LPWORD);
    TOOLKIT_API void TIFFSwabLong(LPDWORD);
    TOOLKIT_API void TIFFSwabArrayOfShort(LPWORD, unsigned long);
    TOOLKIT_API void TIFFSwabArrayOfLong(LPDWORD, unsigned long);
    TOOLKIT_API void TIFFReverseBits(LPBYTE, DWORD);
   TOOLKIT_API  const unsigned char* TIFFGetBitRevTable(long);
    
//AABTEST #ifdef WIN32
    TOOLKIT_API void TIFFModeCCITTFax3(TIFF* tif, long isClassF);	
    TOOLKIT_API long Fax3Decode2DRow(TIFF*, BYTE*, DWORD);
    TOOLKIT_API long Fax3Encode2DRow(TIFF*, BYTE*, BYTE*, DWORD);
    TOOLKIT_API long Fax3Encode1DRow(TIFF*, BYTE*, long);
    TOOLKIT_API long Fax3Decode1DRow(TIFF*, BYTE*, long);
    TOOLKIT_API void Fax3PutBits(TIFF*, DWORD, long);
    TOOLKIT_API void Fax3PutEOL(TIFF*);
    TOOLKIT_API void *Fax3SetupState(TIFF*, long);
    TOOLKIT_API long Fax3PreDecode(TIFF*);
    TOOLKIT_API long Fax3PreEncode(TIFF*);
    TOOLKIT_API long Fax3Decode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API void fax3_putcode(TIFF*, const tableentry *);
    TOOLKIT_API void fax3_putspan(TIFF*, long, const tableentry *);
    TOOLKIT_API long Fax3Encode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long Fax3PostEncode(TIFF*);
    TOOLKIT_API void Fax3Close(TIFF*);
    TOOLKIT_API void Fax3Cleanup(TIFF*);
    TOOLKIT_API long Fax4Decode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long Fax4Encode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long Fax4PostEncode(TIFF*);
//AABTEST #endif
    
    TOOLKIT_API long TIFFInitDumpMode(TIFF*);
#ifdef PACKBITS_SUPPORT
    TOOLKIT_API long TIFFInitPackBits(TIFF*);
#endif //PACKBITS_SUPPORT
//AABTEST #ifdef CCITT_SUPPORT
    TOOLKIT_API long TIFFInitCCITTRLE(TIFF*);
	TOOLKIT_API long TIFFInitCCITTRLEW(TIFF*);
    TOOLKIT_API long TIFFInitCCITTFax3(TIFF*);
    TOOLKIT_API long TIFFInitCCITTFax4(TIFF*);
//AABTEST #endif //CCITT_SUPPORT   
#ifdef THUNDER_SUPPORT
    TOOLKIT_API long TIFFInitThunderScan(TIFF*);
#endif //THUNDER_SUPPORT
#ifdef NEXT_SUPPORT
    TOOLKIT_API long TIFFInitNeXT(TIFF*);
#endif //NEXT_SUPPORT
#ifdef LZW_SUPPORT
    TOOLKIT_API long TIFFInitLZW(TIFF*);
#endif //LZW_SUPPORT
#ifdef JPEG_SUPPORT
    TOOLKIT_API long TIFFInitJPEG(TIFF*);
#endif //JPEG_SUPPORT
    
//AAB holders for typedef pointer fxns
    TIFFVoidMethod m_fpVoid;
    TIFFBoolMethod m_fpBool;
    TIFFCodeMethod m_fpCode;
    TIFFSeekMethod m_fpSeek;
    TIFFPostMethod m_fpPost;
    decodeFunc m_fpDecode;
    
// void (SECTiff::*m_fpVoid)(TIFF *);
    
//AAB converted these from statics since they call member fxns...
//from tif_aux.cpp
    TOOLKIT_API void TIFFDefaultTransferFunction(TIFFDirectory *);
    TOOLKIT_API void TIFFDefaultRefBlackWhite(TIFFDirectory *);
//from tif_comp.cpp
    TOOLKIT_API const cscheme_t *compfindScheme(long);
    TOOLKIT_API long TIFFNoDecode(TIFF*, TCHAR*);
    TOOLKIT_API long TIFFNoEncode(TIFF*, TCHAR*);
//from tif_dir.cpp
    TOOLKIT_API void setShortArray(LPPWORD, LPWORD, long);
    TOOLKIT_API void setLongArray(LPPDWORD, LPDWORD, long);
    TOOLKIT_API void setFloatArray(LPPFLOAT, LPFLOAT, long);
#ifdef JPEG_SUPPORT
    TOOLKIT_API void setJPEGQTable(LPPPBYTE, LPPBYTE, long);
    TOOLKIT_API void setJPEGCTable(LPPPBYTE, LPPBYTE, long);
#endif
    TOOLKIT_API long setExtraSamples(TIFFDirectory *, va_list, LPWORD);
    TOOLKIT_API long TIFFSetField1(TIFF*, ttag_t, va_list);
    TOOLKIT_API long OkToChangeTag(TIFF*, ttag_t);
    TOOLKIT_API void TIFFGetField1(TIFFDirectory *, ttag_t, va_list);
//from tif_dirr.cpp
    TOOLKIT_API LPBYTE CheckMalloc(TIFF*, size_t, const char *);
    TOOLKIT_API void EstimateStripByteCounts(TIFF*, TIFFDirEntry FAR*, WORD);
    TOOLKIT_API void MissingRequired(TIFF*, const char *);
    TOOLKIT_API long CheckDirCount(TIFF*, TIFFDirEntry FAR*, DWORD);
    TOOLKIT_API tsize_t TIFFFetchData(TIFF*, TIFFDirEntry FAR*, LPBYTE);
    TOOLKIT_API tsize_t TIFFFetchString(TIFF*, TIFFDirEntry FAR*, LPBYTE);
    TOOLKIT_API float TIFFFetchRational(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchNormalTag(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchPerSampleShorts(TIFF*, TIFFDirEntry FAR*, long FAR*);
    TOOLKIT_API long TIFFFetchShortArray(TIFF*, TIFFDirEntry FAR*, LPWORD);
    TOOLKIT_API long TIFFFetchShortPair(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchStripThing(TIFF*, TIFFDirEntry FAR*, long, LPPDWORD);
    TOOLKIT_API long TIFFFetchExtraSamples(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchRefBlackWhite(TIFF*, TIFFDirEntry FAR*);
#ifdef JPEG_SUPPORT
    TOOLKIT_API long TIFFFetchJPEGQTables(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchJPEGCTables(TIFF*, TIFFDirEntry FAR*, LPPPBYTE);
#endif
    TOOLKIT_API long TIFFFetchFloatArray(TIFF*, TIFFDirEntry FAR*, LPFLOAT);
    TOOLKIT_API float TIFFFetchFloat(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFFetchByteArray(TIFF*, TIFFDirEntry FAR*, LPWORD);
    TOOLKIT_API long TIFFFetchLongArray(TIFF*, TIFFDirEntry FAR*, LPDWORD);
    TOOLKIT_API long TIFFFetchRationalArray(TIFF*, TIFFDirEntry FAR*, LPFLOAT);
#ifdef STRIPCHOP_SUPPORT
    TOOLKIT_API void ChopUpSingleUncompressedStrip(TIFF*);
#endif
    TOOLKIT_API long cvtRational(TIFF*, TIFFDirEntry FAR*, DWORD, DWORD, LPFLOAT);
    
//from tif_dirw.cpp
    TOOLKIT_API long TIFFWriteNormalTag(TIFF*, TIFFDirEntry FAR*, const TIFFFieldInfo *);
    TOOLKIT_API void TIFFSetupShortLong(TIFF*, ttag_t, TIFFDirEntry FAR*, DWORD);
    TOOLKIT_API long TIFFWriteRational(TIFF*, TIFFDataType, ttag_t, TIFFDirEntry FAR*, float);
    TOOLKIT_API long TIFFWritePerSampleShorts(TIFF*, ttag_t, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFSetupShortPair(TIFF*, ttag_t, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFWriteShortTable(TIFF*, ttag_t, TIFFDirEntry FAR*, DWORD, LPPWORD);
    TOOLKIT_API long TIFFWriteString(TIFF*, ttag_t, TIFFDirEntry FAR*, TCHAR*);
    TOOLKIT_API long TIFFWriteShortArray(TIFF*, TIFFDataType, ttag_t, TIFFDirEntry FAR*, DWORD, LPWORD);
    TOOLKIT_API long TIFFWriteLongArray(TIFF*, TIFFDataType, ttag_t, TIFFDirEntry FAR*, DWORD, LPDWORD);
    TOOLKIT_API long TIFFWriteRationalArray(TIFF*, TIFFDataType, ttag_t, TIFFDirEntry FAR*, DWORD, LPFLOAT);
    TOOLKIT_API long TIFFWriteFloatArray(TIFF*, TIFFDataType, ttag_t, TIFFDirEntry FAR*, DWORD, LPFLOAT);
#ifdef JPEG_SUPPORT
    TOOLKIT_API long TIFFWriteJPEGQTables(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFWriteJPEGCTables(TIFF*, ttag_t, TIFFDirEntry FAR*, LPPBYTE);
#endif
    TOOLKIT_API long TIFFWriteTransferFunction(TIFF*, TIFFDirEntry FAR*);
    TOOLKIT_API long TIFFWriteData(TIFF*, TIFFDirEntry FAR*, LPBYTE);
    TOOLKIT_API long TIFFLinkDirectory(TIFF*);

//from tif_dump.cpp
    TOOLKIT_API int DumpModeEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int DumpModeDecode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int DumpModeSeek(TIFF*, DWORD);
    
//from tif_geti.cpp
    TOOLKIT_API int geti_gt(TIFF*,DWORD,DWORD,LPDWORD);
    TOOLKIT_API int geti_gtTileContig(TIFF*, LPDWORD, LPRGBvalue, DWORD, DWORD);
    TOOLKIT_API int geti_gtTileSeparate(TIFF*, LPDWORD, LPRGBvalue, DWORD, DWORD);
    TOOLKIT_API int geti_gtStripContig(TIFF*, LPDWORD, LPRGBvalue, DWORD, DWORD);
    TOOLKIT_API int geti_gtStripSeparate(TIFF*, LPDWORD, LPRGBvalue, DWORD, DWORD);
    TOOLKIT_API int geti_makebwmap(TIFF*, LPRGBvalue);
    TOOLKIT_API int geti_makecmap(TIFF*, LPWORD, LPWORD, LPWORD);
    TOOLKIT_API WORD geti_checkcmap(int, LPWORD, LPWORD, LPWORD);
    TOOLKIT_API DWORD geti_setorientation(TIFF*, DWORD);
    TOOLKIT_API int geti_setupMap(TIFF*, WORD, WORD, LPPRGBvalue);

//from tif_lzw.cpp
    TOOLKIT_API long LZWEncodePredRow(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long LZWEncodePredTile(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long LZWDecode(TIFF*, tidata_t, tsize_t, tsample_t);
#ifdef LZW_COMPAT
    TOOLKIT_API long LZWDecodeCompat(TIFF*, tidata_t, tsize_t, tsample_t);
#endif
    TOOLKIT_API long LZWDecodePredRow(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API long LZWDecodePredTile(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int LZWCheckPredictor(TIFF*, LZWState FAR*, predictorFunc, predictorFunc);
    TOOLKIT_API void codeLoop(TIFF*);
    TOOLKIT_API void LZWCleanup(TIFF*);
    TOOLKIT_API int LZWPreDecode(TIFF*);
    TOOLKIT_API long LZWDecodeCompat(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int LZWPreEncode(TIFF*);
    TOOLKIT_API int LZWEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int LZWPostEncode(TIFF*);
    
//include tif_pack.cpp
    TOOLKIT_API int PackBitsPreEncode(TIFF *);
    TOOLKIT_API int PackBitsEncode(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int PackBitsEncodeChunk(TIFF*, tidata_t, tsize_t, tsample_t);
    TOOLKIT_API int PackBitsDecode(TIFF*, tidata_t, tsize_t, tsample_t);
    
//tif_read.cpp
    TOOLKIT_API int TIFFSeek(TIFF*, DWORD, tsample_t);
    TOOLKIT_API void TIFFInitOrder(register TIFF*, long, long);
    TOOLKIT_API int TIFFFillStrip(TIFF*, tstrip_t);
    TOOLKIT_API int TIFFFillTile(TIFF*, ttile_t);
    TOOLKIT_API int TIFFStartTile(TIFF*, ttile_t);
    TOOLKIT_API int TIFFCheckRead(TIFF*, int);
    TOOLKIT_API int TIFFStartStrip(TIFF*, tstrip_t);
    TOOLKIT_API tsize_t TIFFReadRawStrip1(TIFF*, tstrip_t, tdata_t, tsize_t, const TCHAR*);
    TOOLKIT_API tsize_t TIFFReadRawTile1(TIFF*, ttile_t, tdata_t, tsize_t, const TCHAR*);
    
//tif_vers.cpp
    TOOLKIT_API const char* TIFFGetVersion(void);
    
//tif_writ.cpp
    TOOLKIT_API long TIFFWriteCheck(TIFF*, long, const TCHAR*);
    TOOLKIT_API long TIFFBufferSetup(TIFF*, const TCHAR*);
    TOOLKIT_API long TIFFGrowStrips(TIFF*, long, const TCHAR*);
    TOOLKIT_API long TIFFAppendToStrip(TIFF*, tstrip_t, tidata_t, tsize_t);
    TOOLKIT_API long TIFFSetupStrips(TIFF*);
    
//tif_thun.cpp
    TOOLKIT_API long ThunderDecode(TIFF*, tidata_t, tsize_t);
    TOOLKIT_API long ThunderDecodeRow(TIFF*, tidata_t, tsize_t, tsample_t);

public:
    TOOLKIT_API ~SECTiff();
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

#endif // __SECTIFF_H__
