///////////////////////////////////////////////////////////////////////////////
// SECTNDC.h
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
//  Description:	Declarations for SECTNDC the ThumbNail DC class
//  Created:		Tue Jul 25 23:13:22 1995
//

#ifndef __SECTNDC_H__
#define __SECTNDC_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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

/////////////////////////////
// AutoDuck tag block block for SECTNDC 
// adinsert AutoDuck insertion point for SECTNDC 
//@doc SECTNDC 
//@class SECTNDC is a CDC derivative that creates a memory DC with an SECTNBitmap into which an 
// SECTNView draws a thumbnail of the view.  
//@comm
// SECTNView::<mf SECTNView::GetThumbNailBitmap> automatically creates a SECTNDC object and passes 
// it to your <c SECTNView> derivative’s <mf SECTNView::OnThumbNail> member function.
//
// The use of SECTNDC is transparent, and in most cases the user does not need to directly
// call any of the SECTNDC members.
//
// The THUMBNL sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\THUMBNL directory demonstrates how to use SECTNDC and 
// the other Objective Toolkit thumbnail support classes.
//@xref<c SECTNBitmap> <c SECTNDocument> <c SECTNFileDialog> <c SECTNView> <c SECTNWinApp>
//@BASE public|CDC
class SECTNDC : public CDC
{
    TOOLKIT_DECLARE_DYNAMIC(SECTNDC);
    
// Constructors
public:
    TOOLKIT_API SECTNDC(); 
    TOOLKIT_API void Create(CSize * pSize); //The size of the bitmap
    
// Operations
    inline BOOL IsThumbNailing() { return TRUE;}; //This DC is a thumbnailing machine.
    
// Attributes
public:
    SECTNBitmap * m_pTNBitmap;   //A serializeable thumbnail bitmap, kicks ass!
    CBitmap     * m_pOldBitmap;  //Store any old bitmap from select
    
// Implementation
public:
    TOOLKIT_API virtual ~SECTNDC();
#ifdef _DEBUG
    TOOLKIT_API virtual void AssertValid() const;
    TOOLKIT_API virtual void Dump(CDumpContext& dc) const;
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


#endif // __SECTNDC_H__
