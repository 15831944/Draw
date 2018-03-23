///////////////////////////////////////////////////////////////////////////////
// SECDIB.h
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
//    MSW       9/30/95 Code review
//
//

#ifndef __SFL_SECDIB_H__
#define __SFL_SECDIB_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SFL_SECIMAGE_H__
#include "Foundation\Image\MFC\secimage.h"
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
// AutoDuck tag block block for SECDib
// adinsert AutoDuck insertion point for SECDib
//@doc SECDib
//@class SECDib derives from <c SECImage> and supports the Windows DIB (device 
// independent bitmap) format, often stored as ".dib" or ".bmp" files.   
//@comm Currently, SECDib only supports Windows version 3 bitmaps which do not include encoding.
// Numerous Windows reference manuals document the format of DIB files, as well as 
// APIs used to manipulate DIB images.
//
// See the IMAGETST sample in the \OT\SAMPLES\STANDARD\IMAGES\IMAGETST directory for a 
// demonstration of this class.
//@base public | SECImage

class SECDib : public SECImage
{
    FOUNDATION_DECLARE_SERIAL(SECDib)
	
// Construction
public:
	//@cmember
	/* Constructs a SECDib object.*/
    FOUNDATION_API SECDib();

// Implementation
protected:
    LPBITMAPFILEHEADER  m_lpbmfHdr;

    FOUNDATION_API virtual BOOL DoSaveImage(CFile* pFile);
    FOUNDATION_API virtual BOOL DoLoadImage(CFile* pFile);

public:    
    FOUNDATION_API void Serialize(CArchive& ar);
    FOUNDATION_API virtual  ~SECDib();
#ifdef _DEBUG
    FOUNDATION_API void AssertValid() const;
#endif
};

};  // namespace stingray::foundation
};  // namespace stingray

//////////////////////////////////////////////////////
// Promote the operator>> symbol declared by the
// DECLARE_SERIAL macro to the global namespace.
using stingray::foundation::operator>>;
//////////////////////////////////////////////////////

//
// CMN Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SFL_SECDIB_H__


