///////////////////////////////////////////////////////////////////////////////
// SECTNBMP.h
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
//  Author:		Scot Wingo
//  Description:	Declarations for SECTNBitmap
//  Created:		Thu Jul 20 21:08:46 1995
//

#ifndef __SECTNBITMAP_H__
#define __SECTNBITMAP_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <StingrayExportDefs.h>

// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL



//SECTMBitmap = SECBitmap + Serialization.

/////////////////////////////
// AutoDuck tag block block for SECTNBitmap 
// adinsert AutoDuck insertion point for SECTNBitmap 
//@doc SECTNBitmap 
//@class SECTNBitmap encapsulates a thumbnail bitmap.  A thumbnail bitmap is basically an in-memory 
// DIB that knows how to serialize itself to an archive through the MFC standard Serialize() member 
// function.
//@comm
// When an SECTNDocument is serialized, it first creates an SECTNBitmap from the current view and 
// serializes that.  After the thumbnail, the document continues to serialize application-specific 
// data as normal.  <c SECTNView> takes care of creating the SECTNBitmap and <c SECTNFileDialog>
// handles reading in and displaying the SECTNBitmap in the thumbnail-enabled open file common 
// dialog.
//
// One side effect of Objective Toolkit using the DIB format to store the thumbnail is that the 
// Windows 95 Explorer will automatically display a thumbnail of the thumbnail in the Explorer and 
// common dialogs.  To turn off this feature, change the signature of the first two bytes from DIB 
// (0x4d42) to another non-DIB value.  This signature is written and checked in the 
// <mf SECTNBitmap::Serialize> member funtion.
//
// In most cases the application will never have to deal directly with SECTNBitmap.
//
// The THUMBNL sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\THUMBNL directory demonstrates how to use SECTNBitmap and the other Objective Toolkit
// thumbnail support classes.
//@xref<c SECTNDC> <c SECTNDocument> <c SECTNFileDialog> <c SECTNView> <c SECTNWinApp>
//@BASE public|CBitmap
class SECTNBitmap : public CBitmap
{

protected: //Create from serialization only.
    TOOLKIT_DECLARE_DYNCREATE(SECTNBitmap) 
    TOOLKIT_API SECTNBitmap();
    
// Implementation
public:
    TOOLKIT_API virtual ~SECTNBitmap();
    TOOLKIT_API virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;    
#endif

// DIB Helper functions
public:
    TOOLKIT_API HANDLE CreateDIB(void);
    TOOLKIT_API HBITMAP CreateDDBFromDIB(HANDLE);
    TOOLKIT_API WORD FAR PaletteSize(LPSTR lpDIB);
    TOOLKIT_API WORD FAR DIBNumColors(LPSTR lpDIB);
    TOOLKIT_API LPSTR FAR FindDIBBits(LPSTR lpDIB);
    TOOLKIT_API BOOL CreateDIBPalette(HANDLE,CPalette*);
    TOOLKIT_API void PaintDIB(HANDLE); 
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __SECTNBITMAP_H__
