///////////////////////////////////////////////////////////////////////////////
// SECPCX.h
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
//    AAB	7/22/95	Started
//    MSW       9/30/95 Code Review
//
//

#ifndef __SECPCX_H__
#define __SECPCX_H__

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

#define PCX_COLORMAP	0x0c
#define SEC_PCX_CACHE_SIZE 60000

typedef struct _PcxHeader
{
	BYTE cIdentifier;		// PCX Id Number (Always 0x0a)
	BYTE cVersion;			// Version number
	BYTE cEncoding;			// Encoding format
	BYTE cBitsPerPixel;		// Bits per pixel
	WORD wXStart;			// Left of image
	WORD wYStart;			// Top of Image
	WORD wXEnd;				// right of image
	WORD wYEnd;				// bottom of image
	WORD wHorzRes;			// horizontal resolution
	WORD wVertRes;			// vertical resolution
	BYTE Palette[48];		// 16 color EGA palette
	BYTE Reserved1;			// (always 0)
	BYTE cNumBitPlanes;		// number of bit planes
	WORD wBytesPerLine;		// bytes per scan line
	WORD wPaletteType;		// palette type
	WORD wHorzScreenSize;	// horizontal screen size
	WORD wVertScreenSize;	// vertical screen size
	BYTE Reserved2[54];		// always 0
} PCXHDR;


/////////////////////////////
// AutoDuck tag block block for SECPcx

// adinsert AutoDuck insertion point for SECPcx
//@doc SECPcx
//@class SECPcx is a <c SECImage> derived class which supports the PCX (PC Paintbrush) 
// file format.  PCX is a file format originated by ZSoft and Microsoft from the PC 
// Paintbrush and more commonly the Microsoft Paintbrush for Windows applications.  
// The popularity of Windows naturally spread the popularity of the PCX format.  
// PCX is also a common image file format in DOS applications.
//
//@comm PCX uses a simple run length encoding scheme to compress its images.
//
// SECPcx supports PCX files which store up to 256 colors.
//
// See the IMAGETST sample in the \SAMPLES\TOOLKIT\STANDARD\IMAGE\IMAGETST directory for a 
// demonstration of this class.
//@xref <c SECImage>
//@base public | SECImage
class SECPcx : public stingray::foundation::SECImage
{
    TOOLKIT_DECLARE_SERIAL(SECPcx);

	//@access Construction
public:

	//@cmember
	/* Constructs a SECPcx object.*/
    TOOLKIT_API SECPcx();

// Overrides
protected:
    TOOLKIT_API virtual BOOL DoLoadImage(CFile* pFile);
    TOOLKIT_API virtual BOOL DoSaveImage(CFile* pFile);

// Implementation
protected:
    PCXHDR	m_PcxHdr;
    
    TOOLKIT_API void LoadImageBits();
    TOOLKIT_API void WriteImageBits();
    TOOLKIT_API void LoadColorMap();
    TOOLKIT_API void WriteColorMap();
    
public:
    TOOLKIT_API virtual ~SECPcx();
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

#endif // __SECPCX_H__


