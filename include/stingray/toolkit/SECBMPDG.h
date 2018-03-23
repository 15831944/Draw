///////////////////////////////////////////////////////////////////////////////
// SECBMPDG.h
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
//  Description:	SECBitmapDialog definition
//  Created:		Sun Jun 25 22:54:12 1995
// CHANGELOG: 

#ifndef __SECBMPDG_H__
#define __SECBMPDG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SFL_SECDIB_H__
#include "Foundation\Image\MFC\secdib.h"
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

/////////////////////////////////////////////////////////////////////////////
// SECBitmapDialog 
#define SEC_BITMAP_TILE 	0
#define SEC_BITMAP_CENTER	1
#define SEC_BITMAP_FILL     2

/////////////////////////////
// AutoDuck tag block block for SECBitmapDialog 

// adinsert AutoDuck insertion point for SECBitmapDialog 
//@doc SECBitmapDialog 
//@class The SECBitmapDialog class is derived from CDialog. It implements a dialogue with a bitmap in the background.
// SECBitmapDialog supports three different bitmap modes.
//@flag SEC_BITMAP_TILE | The bitmap is tiled in the dialog background.
//@flag SEC_BITMAP_CENTER | The bitmap is placed in the center of the dialog background.
//@flag SEC_BITMAP_FILL | The bitmap is sized so that it completely fills the dialog background.
//@comm The BMPDIALOG32 sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\BMPDIALOG32\ directory demonstrates how to create
// SECBitmapDialogs with all three display options.
//@ex Create a tiled brickwall bitmap|The example shows how to create a dialog with a brickwall bitmap tiled in the background.
//SECBitmapDialog bmpDlg(IDD_MODAL_BMPDLG);
//bmpDlg.SetBitmap(IDB_BRICKWALL, SEC_BITMAP_TILE);
//bmpDlg.DoModal();
//@BASE public|CDialog
class SECBitmapDialog : public CDialog
{
	TOOLKIT_DECLARE_DYNAMIC(SECBitmapDialog)

// Construction
//@access Public Members
public:
	//@cmember
	/* Creates a modal dialogue*/
	TOOLKIT_API SECBitmapDialog(UINT nDialogID, CWnd* pParent = NULL);
	//@cmember
	/* Creates a modal dialogue*/
	TOOLKIT_API SECBitmapDialog(LPCTSTR lpcDialogName, CWnd* pParent = NULL);

	//@cmember
	/* Sets the specified bitmap in the dialogue*/
	TOOLKIT_API BOOL SetBitmap(UINT nResBitmapID, int nType = SEC_BITMAP_TILE);
	//@cmember
	/* Sets the specified bitmap in the dialogue*/
    TOOLKIT_API BOOL SetBitmap(LPCTSTR lpcResBitmapName, int nType = SEC_BITMAP_TILE);
	//@cmember
	/* Sets the specified bitmap in the dialogue*/
	TOOLKIT_API BOOL SetBitmap(stingray::foundation::SECImage* pImage, int nType = SEC_BITMAP_TILE);

// Attributes

public:
	
	TOOLKIT_API void SetNullBitmap();
	TOOLKIT_API virtual ~SECBitmapDialog();

protected:
	stingray::foundation::SECDib*	m_pDib;
	CBrush		m_hollowBrush;
	int			m_nType; //Tiled, centered or filled?
	CPalette* SetPalette(CPalette* pPalette);
	CPalette* m_pPalette;
	
	TOOLKIT_API virtual HBRUSH OnStaticCtlColor(CDC* pDC, CWnd* pWnd);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SECBitmapDialog)
	//}}AFX_VIRTUAL

protected:
	TOOLKIT_API virtual void UseHalftonePalette(BOOL bHalftone = TRUE);
	TOOLKIT_API virtual HBRUSH GetHollowBrush();
	//{{AFX_MSG(SECBitmapDialog)
	TOOLKIT_API afx_msg BOOL OnQueryNewPalette();
	TOOLKIT_API afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	TOOLKIT_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // __SECBMPDG_H__

