///////////////////////////////////////////////////////////////////////////////
// SECTNDLG.h
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
//  Description:	Declaration for old-style Thumbnail dialog
//  Created:		Fri Jun 30 16:19:42 1995

#ifndef __SECTNFILEDLG_H__
#define __SECTNFILEDLG_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#if !defined(WIN32) && !defined(_INC_TOOLHELP)
#include /* */ "toolhelp.h"
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

#ifndef WIN32
typedef UINT (CALLBACK *LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
#endif //WIN32

// Forward declarations
class SECTNBitmap; 

/////////////////////////////
// AutoDuck tag block block for SECTNFileDialog 
// adinsert AutoDuck insertion point for SECTNFileDialog 
//@doc SECTNFileDialog 
//@class SECTNFileDialog adds the thumbnailing area to the common ‘open file’ dialog.  
// In addition, it automatically reads in a saved thumbnail image and displays it in the thumbnail 
// preview area when the user selects the file name.
//@comm
// If no preview is available, it displays ‘no preview’. 
//
// All of the SECTNFileDialog operations happen transparently. In most cases the developer does not 
// ever have to know about SECTNFileDialog, since <c SECTNWinApp> will automatically create,
// display and destroy the dialog.
// 
// If you currently have your own template or hook procedure for CFileDialog, you will
// need to reconcile your specializations with those made by SECTNFileDialog.
// 
//The THUMBNL sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\THUMBNL directory demonstrates how to use SECTNFileDialog and the other 
// Objective Toolkit thumbnail support classes.
//
// The SECTNFileDialog can also display a thumbnail of the image files supported by OT (.bmp, .dib,
// .gif, .jpg, .tif, .tga, .pcx) provided these formats are currently selected in the build-config.
// To turn on this feature call the following static function in say your apps InitInstance:
// SECTNFileDialog::SetDisplaySECImages(TRUE);
// If you need only the thumbnail of the image files to be displayed in the preview area then all
// you have to do is derive your app class from SECTNWinApp, set the handler for ID_FILE_OPEN to be
// SECTNWinApp::OnFileOpen and call SetDisplaySECImages.
//
// The IMAGETST sample in the \SAMPLES\TOOLKIT\STANDARD\IMAGE\IMAGETST directory demonstrates how to use SECTNFileDialog 
// to display thumbnail views of image files in the File/Open dialog.
//
//@xref<c SECTNBitmap> <c SECTNDC> <c SECTNDocument> <c SECTNView> <c SECTNWinApp>
//@BASE public|CFileDialog
class SECTNFileDialog : public CFileDialog
{
    TOOLKIT_DECLARE_DYNAMIC(SECTNFileDialog);
   
// Construction
public:
    TOOLKIT_API SECTNFileDialog(BOOL bOpenFileDialog,
		    LPCTSTR lpszDefExt = NULL,
		    LPCTSTR lpszFileName= NULL,
		    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		    LPCTSTR lpszFilter = NULL,
		    CWnd * pParentWnd = NULL);
    
// Attributes
// Operations
// Implementation    
public:
    TCHAR		m_szCurrentFile[MAX_PATH+1];//For paints
    CStatic*	m_pStatic;					//Pointer to our static where TN displayed.
    BOOL		m_bExplorerStyle;
	BOOL		m_bDisplaySECImages;		//Display SECImage files in the TN view.

private:
    BOOL        m_bFolderChanged;

#ifdef WIN32
#if (_MFC_VER >= 0x0800 && defined _UNICODE && !defined _NATIVE_WCHAR_T_DEFINED)
    TOOLKIT_API void SetCurrentFile(const unsigned short* lpszNewFile)
#else
    inline void SetCurrentFile(LPCTSTR lpszNewFile)
#endif
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(m_szCurrentFile, lpszNewFile);
	}
#else
	// 16-bit
    inline void SetCurrentFile(const char * lpszNewFile) { strcpy(m_szCurrentFile,lpszNewFile); }   
#endif

    // Load the thumbnail from a filename
#ifdef WIN32    
    TOOLKIT_API SECTNBitmap* LoadThumbnail(LPCTSTR);	
	TOOLKIT_API stingray::foundation::SECImage * LoadSECImage(LPCTSTR);
#else //WIN16
    TOOLKIT_API SECTNBitmap* LoadThumbnail(const TCHAR *);
	TOOLKIT_API stingray::foundation::SECImage* LoadSECImage(const TCHAR *);
#endif //WIN32
    
    // Thumbnail drawing routines
    TOOLKIT_API void ClearThumbnail(CDC *,CRect *);
    TOOLKIT_API void DisplayNoThumbnail(CDC *,CRect *);
    TOOLKIT_API void DisplayThumbnail(CDC *,CRect *, SECTNBitmap *);
	TOOLKIT_API void DisplaySECImage(CDC *, CRect *, stingray::foundation::SECImage *);
    TOOLKIT_API void UpdateThumbnail();
    TOOLKIT_API void OnNewFile(LPTSTR lpszFileName);

    // Hooks - only needed/used for Win32 commdlgs.
#ifdef WIN32    
    TOOLKIT_API static BOOL CALLBACK TNFileDlgHookProc(HWND,UINT,WPARAM,LPARAM);
    TOOLKIT_API static SECTNFileDialog* StaticGetPointer(HWND);
#endif //WIN32

//Overrides
public:
    TOOLKIT_API virtual ~SECTNFileDialog(void);
    TOOLKIT_API virtual void OnLBSelChangedNotify(UINT,UINT,UINT);
    TOOLKIT_API virtual BOOL OnInitDialog();
    TOOLKIT_API virtual SEC_INT DoModal();
    TOOLKIT_API void ResizeDialog();
    
#if _MFC_VER >= 0x400
    TOOLKIT_API void OnFileNameChange();
    TOOLKIT_API void OnFolderChange();
#endif //_MFC_VER >= 0x400 
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECTNFILEDLG_H__
