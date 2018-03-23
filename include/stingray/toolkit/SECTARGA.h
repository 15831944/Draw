///////////////////////////////////////////////////////////////////////////////
// SECTARGA.h
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


#ifndef __SECTARGA_H__
#define __SECTARGA_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SFL_SECIMAGE_H__
#include "Foundation\Image\MFC\secimage.h"
#endif

#include <StingrayExportDefs.h>

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

//  TGA File Header
typedef struct _TgaHeader
{                           
    BYTE   IdLength;            /* Image ID Field Length      */
    BYTE   CmapType;            /* Color Map Type             */
    BYTE   ImageType;           /* Image Type                 */
	//
    // Color Map Specification
	//
    WORD   CmapIndex;           /* First Entry Index          */
    WORD   CmapLength;          /* Color Map Length           */
    BYTE   CmapEntrySize;       /* Color Map Entry Size       */
    /*
    ** Image Specification
    */
    WORD   X_Origin;            /* X-origin of Image          */
    WORD   Y_Origin;            /* Y-origin of Image          */
    WORD   ImageWidth;          /* Image Width                */
    WORD   ImageHeight;         /* Image Height               */
    BYTE   PixelDepth;          /* Pixel Depth                */
    BYTE   ImagDesc;            /* Image Descriptor           */
} TGAHEADER;


/*
**  Image/Color Map Data
*/
typedef struct _TgaColorMap
{
    char  *IdField;             /* Image ID Field             */
    BYTE  *CmapData;            /* Color Map Data             */
} TGACMAP;
              

/*
**  Developer Area Tag Structure
*/
typedef struct _TgaTag
{
    WORD    TagNumber;           /* Number of the Tag          */
    DWORD   TagOffset;           /* Offset of the Tag Data     */
    DWORD   TagSize;             /* Size of the Tag Data       */
    BYTE   *TagData;             /* Pointer to the Tag Data    */
    struct _TgaTag *Next;        /* Link to next Tag           */
} TGATAG;


/*
**  Developer Area
*/
typedef struct _TgaDeveloper
{
    WORD    NumberOfTags;     /* Number of Tags in Directory  */
    TGATAG *TagList;          /* Link to list of Tags         */
} TGADEVELOPER;


/*
**  Extension Area
*/
typedef struct _TgaExtension        
{
    WORD   Size;                /* Extension Size             */
    char   AuthorName[41];      /* Author Name                */
    char   AuthorComment[324];  /* Author Comment             */
    WORD   StampMonth;          /* Date/Time Stamp: Month     */
    WORD   StampDay;            /* Date/Time Stamp: Day       */
    WORD   StampYear;           /* Date/Time Stamp: Year      */
    WORD   StampHour;           /* Date/Time Stamp: Hour      */
    WORD   StampMinute;         /* Date/Time Stamp: Minute    */
    WORD   StampSecond;         /* Date/Time Stamp: Second    */
    char   JobName[41];         /* Job Name/ID                */
    WORD   JobHour;             /* Job Time: Hours            */
    WORD   JobMinute;           /* Job Time: Minutes          */
    WORD   JobSecond;           /* Job Time: Seconds          */
    char   SoftwareId[41];      /* Software ID                */
    WORD   VersionNumber;       /* Software Version Number    */
    BYTE   VersionLetter;       /* Software Version Letter    */     
#ifndef WIN32
    BYTE   pad;  //FOR 16-bit warnings.
#endif //WIN32    
    DWORD  KeyColor;            /* Key Color                  */
    WORD   PixelNumerator;      /* Pixel Aspect Ratio Numerator   */
    WORD   PixelDenominator;    /* Pixel Aspect Ratio Denominator */
    WORD   GammaNumerator;      /* Gamma Value                */
    WORD   GammaDenominator;    /* Gamma Value                */
    DWORD  ColorOffset;         /* Color Correction Offset    */
    DWORD  StampOffset;         /* Postage Stamp Offset       */
    DWORD  ScanOffset;          /* Scan Line Table Offset     */
    BYTE   AttributesType;      /* Attributes Types           */   
#ifndef WIN32
    BYTE   padtwo;                  //For 16-bit byte alignment
#endif //WIN32
    DWORD *ScanLineTable;       /* Scan Line Table            */
    BYTE   StampWidth;          /* Width of postage stamp image */
    BYTE   StampHeight;         /* Height of postage stamp image */
    BYTE  *StampImage;          /* Postage Stamp Image        */
    WORD   ColorTable[1024];    /* Color Correction Table     */
} TGAEXTENSION;                                  
                                    
                                    
/*                                  
**  TGA File Footer
*/
typedef struct _TgaFooter
{
    DWORD ExtensionOffset;      /* Extension Area Offset      */
    DWORD DeveloperOffset;      /* Developer Directory Offset */
    char  Signature[18];        /* Signature, dot, and NULL   */
} TGAFOOTER;
                            

/*
**  Complete TGA File Format
*/
typedef struct _TgaFormat
{
    TGAHEADER      Head;            /* Header Area                          */
    TGACMAP        Cmap;            /* Image/Color Map Area                 */
    TGADEVELOPER   Developer;       /* Developer Area                       */
    TGAEXTENSION   Extension;       /* Extension Area                       */
    TGAFOOTER      Foot;            /* File Footer Area                     */
    BOOL           NewTgaFormat;    /* TRUE if file is v2.0 TGA format      */
    DWORD          TgaDataOffset;   /* Offset of the image data in the file */ 
} TGA;

typedef enum _ImgType
{
    NONE = 0,
    COLORED_MAPPED = 1,
    TRUE_COLOR = 2,
    BLACK_WHITE_NO_MAP = 3,
    RLE_COLOR_MAPPED = 9,
    RLE_TRUE_COLOR = 10,
    RLE_BLACK_WHITE = 11
} IMAGETYPE;


#define TGASIGNATURE   "TRUEVISION-XFILE.\0"
#define TGA_BPP ((m_TgaHead.Head.PixelDepth + 7) >> 3)


/////////////////////////////
// AutoDuck tag block block for SECTarga

// adinsert AutoDuck insertion point for SECTarga
//@doc SECTarga
//@class SECTarga is a <c SECImage> derived class which supports the TGA (Targa image file) 
// file standard.  TGA was developed by Truevision for use with its graphic adaptors, and is 
// popular for use with still images captured from video sources.
//
//@comm TGA was one of the first formats which supported 24-bit images.  SECTarga only supports 
// TGA images with the 24 bits per pixel mode.
// 
// SECTarga supports version 1 and version 2 TGA files, but only uses information contained 
// in version 1.
// 
// See the IMAGETST samples in the \SAMPLES\TOOLKIT\STANDARD\IMAGE\IMAGETST directory for a 
// demonstration of this class.
//@xref <c SECImage>
//@base public | SECImage
class SECTarga : public stingray::foundation::SECImage
{
    TOOLKIT_DECLARE_SERIAL(SECTarga);

	//@access Construction
public:
	
	//@cmember
	/* Constructs a SECTarga object.*/
    TOOLKIT_API SECTarga();

// Overrides
protected:
    TOOLKIT_API virtual BOOL DoLoadImage(CFile* pFile);
    TOOLKIT_API virtual BOOL DoSaveImage(CFile* pFile);

// Implementation
protected:
    TGA m_TgaHead;
    TOOLKIT_API short ReadTgaHeader();
    TOOLKIT_API short CheckTgaHeader();
    TOOLKIT_API VOID  WriteTgaFile();
#ifdef WIN32
    TOOLKIT_API short TgaDecodeScanLine(BYTE *, WORD, WORD, LPBYTE);
    TOOLKIT_API short TgaEncodeScanLine(BYTE *, WORD, WORD, WORD, LPBYTE);
#else
    TOOLKIT_API short TgaDecodeScanLine(BYTE *, WORD, WORD, BYTE huge *);
    TOOLKIT_API short TgaEncodeScanLine(BYTE *, WORD, WORD, WORD, BYTE huge *);
#endif
    TOOLKIT_API void MakeBMI();
    
public:
    TOOLKIT_API virtual ~SECTarga();
    TOOLKIT_API virtual void Serialize(CArchive& ar);
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

#endif // __SECTARGA_H__

