///////////////////////////////////////////////////////////////////////////////
// SECIMAGE.h
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
// SECImage Abstract Base Class (ABC)
//
// Description
//  
//  Right now SECImage uses a DIB structure to 
//  store image data in.  This will most likely change
//  in the future, so depending on any of the member
//  data staying the same is very dangerous at this point.
//  We recommend sticking to the member functions instead,
//  this interface will not be changing.
//
// CHANGELOG: 
//
//    AAB	6/22/95	Started
//    MSW	8/01/95 tweaks
//    MSW   9/30/95 Code review
//

#ifndef __SFL_SECIMAGE_H__
#define __SFL_SECIMAGE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

//
// CMN Extension DLL
// Initialize declaration context
//

#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

/////////////////////////////
// AutoDuck tag block block for SECImage

//@doc SECImage
//@mfunc BOOL  | SECImage  | DoSaveImage | Saves image data to a file.
//@comm Derivatives of SECImage must define this.

//@doc SECImage
//@mfunc BOOL  | SECImage  | DoLoadImage | Loads image data from a file.
//@comm Derivatives of SECImage must define this.

//@doc SECImage
//@mdata int  | SECImage  | m_nSrcBitsPerPixel | Number fo bits per pixel in the image.

//@doc SECImage
//@mdata int  | SECImage | m_nSysBitsPerPixel | Number of bits per pixel in the current display.

//@doc SECImage
//@mdata int  | SECImage | m_nBitPlanes | Number of bit planes.

//@doc SECImage
//@mdata BOOL  | SECImage | m_bIsPadded | Indicates that the right margin has been padded to the nearest DWORD.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwPadWidth | The width of the image after padding.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwWidth | The width of the image in pixels.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwHeight | The height of the image in pixels.

//@doc SECImage
//@mdata WORD  | SECImage | m_wColors | The number of colors in the image.

//@doc SECImage
//@mdata WORD  | SECImage | m_wSysColors | The number of colors in the current display.

//@doc SECImage
//@mdata LPCTSTR  | SECImage | m_lpszFileName | The filename used for the source of the image.

//@doc SECImage
//@mdata CPalette * | SECImage | m_pPalette | A pointer to the palette for the image.

//@doc SECImage
//@mdata CFile * | SECImage | m_pFile | The file object used to load and save the image.

//@doc SECImage
//@mdata LPBYTE  | SECImage | m_lpSrcBits | The image data (a flat buffer)

//@doc SECImage
//@mdata LPBITMAPINFO  | SECImage | m_lpBMI | A pointer to the BITMAPINFO for this image.

//@doc SECImage
//@mdata LPRGBQUAD  | SECImage | m_lpRGB | A pointer to an array of RGBQUAD data types 
// that define the colors in the bitmap. 
    
//@doc SECImage
//@mdata BOOL  | SECImage  | m_bUseHalftone | Indicates to use half tones.

//@doc SECImage
//@mdata int  | SECImage | m_nBitHolder | Used for conversion of 4 or 1 bit 
// per pixel images to 8 bpp.

//@doc SECImage
//@mdata DWORD  | SECImage  | m_dwBitCount | Used for conversion of 4 or 1 bit per 
// pixel images to 8 bpp and greater.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwError | Error message.

//@doc SECImage
//@mdata BOOL  | SECImage | m_bSwapOnWrite | Flag to swap monochrome bytes when writing out. 
// Default is TRUE;

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwCacheMax | Maximum number of bytes in file cache.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwCacheSize | Size of current file cache in bytes.

//@doc SECImage
//@mdata DWORD  | SECImage | m_dwCachePos | Current file cache position.

//@doc SECImage
//@mdata LPBYTE  | SECImage | m_lpCache | The actual file cache array.

// adinsert AutoDuck insertion point for SECImage
//@doc SECImage
//@class SECImage is the abstract base class to the image classes.  SECImage 
// provides a common interface to access and manipulate image data which are 
// maintained as unique file formats in the derived image classes.  Using a 
// common base class for the image format offers an advantage in being able 
// to provide functionality for all image formats including image loading and 
// saving, conversion between derived base classes, and image manipulation.
//
// See the IMAGETST sample in the \OT\SAMPLES\STANDARD\IMAGES\IMAGETST directory for a 
//demonstration of this class.
//@xref <c SECDib> <c SECGif> <c SECJpeg> <c SECPcx> <c SECTarga> <c SECTiff>
//@base public | CObject
class SECImage : public CObject
{

	//@access Creation/Initialization
public:
	
	//@cmember
	/* Constructs a SECImage object.*/
     FOUNDATION_API SECImage();
	
protected:

	//@cmember
	/* Creates the image palette.*/
     FOUNDATION_API virtual BOOL CreatePalette();

	//@access Attributes
public:
	
	//@cmember
	/* Returns the width of the current image.*/
     FOUNDATION_API DWORD dwGetWidth() const;

	//@cmember
	/* Returns the height of the current image.*/
     FOUNDATION_API DWORD dwGetHeight() const;
    
	//@access Operations
public:    

	//@cmember
	/* Creates a duplicate of the current image.*/
     FOUNDATION_API BOOL CopyImage(SECImage *pSrc);
	
	//@cmember
	/* Converts from one derived image class to another.*/
     FOUNDATION_API BOOL ConvertImage(SECImage *pSrc);
    
	//@cmember
	/* Creates a CBitmap from the current image data.*/
     FOUNDATION_API CBitmap* MakeBitmap(CDC *pDC, const TCHAR *lpszFileName);
	
	//@cmember
	/* Creates a CBitmap from the current image data.*/
     FOUNDATION_API CBitmap* MakeBitmap(CDC *pDC); // MSW
    
	//@cmember
	/* Loads image data from an image file.*/
     FOUNDATION_API virtual BOOL LoadImage(CFile* pFile);
	
	//@cmember
	/* Loads image data from an image file.*/
     FOUNDATION_API virtual BOOL LoadImage(LPCTSTR lpszFileName);
	
	//@cmember
	/* Saves the current image to a file in the format of the derived image class.*/
     FOUNDATION_API virtual BOOL SaveImage(CFile* pFile);
	
	//@cmember
	/* Saves the current image to a file in the format of the derived image class.*/
     FOUNDATION_API virtual BOOL SaveImage(LPCTSTR lpszFileName);
    

	//@cmember
	/* Flips the image vertically.*/
     FOUNDATION_API BOOL FlipHorz();
	
	//@cmember
	/* Flips the image horizontally.*/
     FOUNDATION_API BOOL FlipVert();
	
	//@cmember
	/* Rotates the image 90 degrees and swaps the width and height parameters.*/
     FOUNDATION_API BOOL Rotate90(BOOL bClockwise=TRUE);
	
	//@cmember
	/* Modifies the contrast of an image.*/
     FOUNDATION_API void ContrastImage(short nSharpen);
	
	//@cmember
	/* Crops an image to the specified dimensions.*/
     FOUNDATION_API BOOL Crop(long nLeft, long nTop, long nWidth, long nHeight);
	
	//@cmember
	/* Calculates number of bytes based on bits per pixel.*/
    FOUNDATION_API DWORD NumBytes() const;
	
	//@cmember
	/* Calculates number of colors in bitmap based on bit count.*/
     FOUNDATION_API WORD NumColors() const;
	
	//@cmember
	/* Encapsulates the ::StretchDIBits() call.*/
	 FOUNDATION_API int StretchDIBits(CDC *pDC, int XDest, int YDest, int cxDest, int cyDest,
									 int XSrc, int YSrc, int cxSrc, int cySrc, const void FAR* lpvBits,
									 LPBITMAPINFO lpbmi, UINT fuColorUse, DWORD fdwRop);
	
	//@cmember
	/* Fills in an SECImage instance with DIB info.*/
	 FOUNDATION_API BOOL CreateFromBitmap(CDC *pDC, CBitmap *pSrcBitmap);  

	//@cmember
	/* Static utility function that loads an image file into its appropriate SECImage class and returns the SECImage object.*/
	 FOUNDATION_API static SECImage* ParseImage(LPCTSTR lpszPathName);
	//@cmember
	/* Static utility function that loads an image file into its appropriate SECImage class and returns the SECImage object.*/
	 FOUNDATION_API static SECImage* ParseImage(CFile* pFile);

	//@access Overridable

protected:
	
	//@cmember
	/* Called before an image is loaded.*/
     FOUNDATION_API virtual BOOL PreLoadImage();
	
	//@cmember
	/* Called after an image is loaded.*/
    FOUNDATION_API virtual BOOL PostLoadImage();
	
	//@cmember
	/* Called before an image is saved.*/
     FOUNDATION_API virtual BOOL PreSaveImage();
	
	//@cmember
	/* Called after an image is saved.*/
     FOUNDATION_API virtual BOOL PostSaveImage();

    // SECImage derivatives *must* define these.
	
	//@cmember
	/* Saves the image to a file.*/
     FOUNDATION_API virtual BOOL DoSaveImage(CFile* pFile)=0;
	
	//@cmember
	/* Loads an image from a file.*/
     FOUNDATION_API virtual BOOL DoLoadImage(CFile* pFile)=0;

	   FOUNDATION_API virtual void OnCleanupAllocFiles();

// Implementation
public:

	//@access Public data members

	//@cmember
	/* Number fo bits per pixel in the image.*/
    int m_nSrcBitsPerPixel;
	
	//@cmember
	/* Number of bits per pixel in the current display.*/
	int m_nSysBitsPerPixel;
	
	//@cmember
	/* Number of bit planes.*/
    int m_nBitPlanes;
	
	//@cmember
	/* Indicates that the right margin has been padded to the nearest DWORD.*/
    BOOL m_bIsPadded;
	
	// for calculating DWORD boundary of scan line
	//@cmember
	/* The width of the image after padding.*/
    DWORD m_dwPadWidth; 
	
	//@cmember
	/* The width of the image in pixels.*/
    DWORD m_dwWidth;
	
	//@cmember
	/* The height of the image in pixels.*/
    DWORD m_dwHeight;
	
	//@cmember
	/* The number of colors in the image.*/
    WORD m_wColors;
	
	//@cmember
	/* The number of colors in the current display.*/
    WORD m_wSysColors;
	
	//@cmember
	/* A pointer to the palette for the image.*/
    CPalette* m_pPalette;
	
	//@cmember
	/* The file object used to load and save the image.*/
    CFile* m_pFile;

#ifdef WIN32

	//@cmember
	/* The image data (a flat buffer)*/
    LPBYTE m_lpSrcBits;

#else

    BYTE huge * m_lpSrcBits;

#endif

	//@cmember
	/* A pointer to the BITMAPINFO for this image.*/
    LPBITMAPINFO m_lpBMI;
	
	//@cmember
	/* A pointer to an array of RGBQUAD data types that define the colors in the bitmap. */
    LPRGBQUAD m_lpRGB;
	
	//@cmember
	/* Indicates to use half tones.*/
	BOOL m_bUseHalftone;
	
	//@cmember
	/* Used for conversion of 4 or 1 bit per pixel images to 8 bpp.*/
	int m_nBitHolder;
	
	//@cmember
	/* Used for conversion of 4 or 1 bit per pixel images to 8 bpp and greater.*/
	DWORD m_dwBitCount; 
	
	//@cmember
	/* Error message.*/
	DWORD m_dwError;
	
	//@cmember
	/* Flag to swap monochrome bytes when writing out. Default is TRUE;*/
	BOOL m_bSwapOnWrite;

protected:

	//@access Protected data members

	//@cmember
	/* Maximum number of bytes in file cache.*/
    DWORD m_dwCacheMax;		
	
	//@cmember
	/* Size of current file cache in bytes.*/
    DWORD m_dwCacheSize;	
	
	//@cmember
	/* Current file cache position.*/
    DWORD m_dwCachePos;		
	
	CPtrList m_listFileAlloc;

#ifdef WIN32

	//@cmember
	/* The actual file cache array*/
    LPBYTE m_lpCache;	

#else

    BYTE huge *m_lpCache;	// the actual file cache array

#endif

protected:

	// Calculates the padding width for the image
	 FOUNDATION_API DWORD CalcPadding(DWORD dwBitsPerPixel, DWORD dwPixels) const;
	
	// Calculates the position of the last byte of image data on a padded line.
	 FOUNDATION_API DWORD LastByte(DWORD dwBitsPerPixel, DWORD dwPixels) const;
	
	// Calculates the number of bytes required for a line of the image.
	 FOUNDATION_API DWORD CalcBytesPerLine(DWORD dwBitsPerPixel, DWORD dwWidth) const;
	
	// Pads the image to the nearest DWORD boundary consistent with DIB format
     FOUNDATION_API BOOL PadBits();  
	
	// Unpads the image bits back to sequential data
     FOUNDATION_API BOOL UnPadBits();
    
	// Cache convenience functions
	
	// Initializes a cache
     FOUNDATION_API BOOL InitCache(DWORD dwBytes, WORD wMode); 
	
	// Fills in a cache from a file
     FOUNDATION_API DWORD LoadCache();  
	
	// Retrieves cache bytes
     FOUNDATION_API DWORD GetCache(void *pBuf, DWORD dwBytes);  
	
	// Puts bytes in the cache.
     FOUNDATION_API DWORD PutCache(void *pBuf, DWORD dwBytes);  
	
	// Writes current cache out to file.
      FOUNDATION_API void FlushCache(); 
	
	// Disposes of the current cache.
     FOUNDATION_API void FreeCache();   
	
	// Used to serialize/load intermediate file format.
     FOUNDATION_API BOOL SECLoadDib(CFile *pFile); 
	
	// Used to serialize/load intermediate file format.
     FOUNDATION_API BOOL SECLoadDibArchive(CArchive& ar); 
    
public:
     FOUNDATION_API void Serialize(CArchive &ar);
     FOUNDATION_API virtual ~SECImage();
    
#ifdef _DEBUG
	   FOUNDATION_API void AssertValid() const;
#endif //_DEBUG
};

// Macros - These help with padding and also define
// the BMP file marker.

#define PADWIDTH(x)	(((x)*8 + 31)  & (~31))/8
#define DIB_HEADER_MARKER	((WORD) ('M' << 8) | 'B')
#define SEC_READ_CACHE 0x01
#define SEC_WRITE_CACHE 0x02

// iteration used for converting 1bpp and 4bpp images over to 8bpp.
#define NEXT_IMAGE_PIXEL(bDest, lpSrc) \
switch(m_nSrcBitsPerPixel) { \
case 1: \
		if (m_nBitHolder > 7) { \
			m_nBitHolder = 0; \
			lpSrc++; \
		} \
		if (m_bSwapOnWrite ==TRUE)\
			bDest = (BYTE)((*lpSrc >> (7-m_nBitHolder)) & (BYTE)0x01);\
		else\
			bDest = (BYTE)((*lpSrc >> m_nBitHolder) & (BYTE)0x01);\
		m_nBitHolder ++; \
		if (++m_dwBitCount >= m_dwWidth) { \
			m_dwBitCount = 0; \
			m_nBitHolder = 0; \
			lpSrc++; \
			} \
		break; \
case 4: \
		if (m_nBitHolder ==1) { \
			m_nBitHolder = 0; \
			bDest = (BYTE)(*lpSrc & (BYTE)0xf); \
			lpSrc++; \
			m_dwBitCount++; \
			if (m_dwBitCount >= m_dwWidth) \
				m_dwBitCount = 0; \
} \
		else {\
			bDest = (BYTE)(*lpSrc >> 4); \
			if (++m_dwBitCount >= m_dwWidth) { \
				lpSrc++; \
				m_dwBitCount = 0; \
				} \
			else \
				m_nBitHolder=1; \
} \
		bDest = (BYTE)(bDest & (BYTE)0x0f); \
		break; \
default : \
		bDest = *lpSrc++; \
}

};  // namespace stingray::foundation
};  // namespace stingray


//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SFL_SECIMAGE_H__



