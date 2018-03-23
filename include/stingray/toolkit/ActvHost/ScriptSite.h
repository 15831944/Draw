///////////////////////////////////////////////////////////////////////////////
// ScriptSite.h
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

#ifndef _SEC_SCRIPTSITE_H_
#define _SEC_SCRIPTSITE_H_

#ifdef _WIN64
	#include <..\src\mfc\occimpl.h>
#else
	#if ( _MFC_VER < 0x0700 )
		#include <transact.h>
		#include <..\src\occimpl.h>
	#else
		#include <ocdb.h>
		#include <..\src\mfc\occimpl.h>
		#include <afxocc.h>
	#endif //_MFC_VER < 0x0700)
#endif	//_WIN64

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
// CScriptOleControlSite

class SECAOleScriptControlSite : public COleControlSite
{
	TOOLKIT_DECLARE_DYNCREATE(SECAOleScriptControlSite)
	
public:
	TOOLKIT_API SECAOleScriptControlSite();
	TOOLKIT_API SECAOleScriptControlSite(COleControlContainer* pCtrlCont);

	TOOLKIT_API HRESULT CreateControl( CWnd* pWndCtrl, REFCLSID clsid,
	                                   LPCTSTR lpszWindowName, DWORD dwStyle, 
	                                   const RECT& rect, UINT nID,
		                                 CFile* pPersist=NULL, BOOL bStorage=FALSE, 
		                                 BSTR bstrLicKey=NULL );

	TOOLKIT_API void Cleanup();

#if( _MFC_VER >= 0x0700 ) 

	BEGIN_INTERFACE_PART(AltOleIPSite, IOleInPlaceSiteWindowless)
		INIT_INTERFACE_PART(SECAOleScriptControlSite, AltOleIPSite)
		STDMETHOD(GetWindow)(HWND*);
		STDMETHOD(ContextSensitiveHelp)(BOOL);

		STDMETHOD(CanInPlaceActivate)();
		STDMETHOD(OnInPlaceActivate)();
		STDMETHOD(OnUIActivate)();
		STDMETHOD(GetWindowContext)( LPOLEINPLACEFRAME*,
			                           LPOLEINPLACEUIWINDOW*, 
			                           LPRECT, LPRECT, 
			                           LPOLEINPLACEFRAMEINFO );
		STDMETHOD(Scroll)(SIZE);
		STDMETHOD(OnUIDeactivate)(BOOL);
		STDMETHOD(OnInPlaceDeactivate)();
		STDMETHOD(DiscardUndoState)();
		STDMETHOD(DeactivateAndUndo)();
		STDMETHOD(OnPosRectChange)(LPCRECT);

	  STDMETHOD(OnInPlaceActivateEx)( BOOL* ptNoRedraw, DWORD dwFlags );
	  STDMETHOD(OnInPlaceDeactivateEx)( BOOL tNoRedraw );
	  STDMETHOD(RequestUIActivate)();

	  STDMETHOD(AdjustRect)( LPRECT prect );
	  STDMETHOD(CanWindowlessActivate)();
	  STDMETHOD(GetCapture)();
	  STDMETHOD(GetDC)( LPCRECT prect, DWORD dwFlags, HDC* phDC );
	  STDMETHOD(GetFocus)();
	  STDMETHOD(InvalidateRect)( LPCRECT prect, BOOL tErase );
	  STDMETHOD(InvalidateRgn)( HRGN hRgn, BOOL tErase );
	  STDMETHOD(OnDefWindowMessage)( UINT nMessage, WPARAM wParam,
		                               LPARAM lParam, LRESULT* plResult );
	  STDMETHOD(ReleaseDC)( HDC hDC );
	  STDMETHOD(ScrollRect)( int dx, int dy, LPCRECT prectScroll,
		 LPCRECT prectClip );
	  STDMETHOD(SetCapture)( BOOL tCapture );
	  STDMETHOD(SetFocus)( BOOL tFocus );
	END_INTERFACE_PART(AltOleIPSite)

	DECLARE_INTERFACE_MAP()

#endif //( _MFC_VER >= 0x0700 ) 

};


class TOOLKIT_API SECAOleScriptControlContainer : public COleControlContainer
{
public:
	virtual void OnUIActivate(COleControlSite* pSite);
	virtual void OnUIDeactivate(COleControlSite* pSite);

	SECAOleScriptControlContainer(CWnd*  pWnd);
	virtual ~SECAOleScriptControlContainer();
};

/////////////////////////////////////////////////////////////////////////////
// OLE control container manager

class TOOLKIT_API SECAScriptOccManager : public COccManager
{
public:
	virtual COleControlContainer* CreateContainer(CWnd* pWnd);
	virtual COleControlSite* CreateSite(COleControlContainer* pCtrlCont);
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif		// _SEC_SCRIPTSITE_H_
