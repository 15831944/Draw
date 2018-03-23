///////////////////////////////////////////////////////////////////////////////
// gxclsite.h
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
// Author: Daniel Jebaraj
//

#ifndef _GX_CL_SITE__H__
#define _GX_CL_SITE__H__

#ifndef __IOleClientSite_INTERFACE_DEFINED__
#include "oleidl.h"
#endif

#if _MFC_VER >= 0x0400

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXOleViewer;

// very simple client site implementation. We do not use MFC client site implementation
class CGXClientSite : public IOleClientSite
{
public:
	GRID_API CGXClientSite(CGXOleViewer* pViewer);

	GRID_API virtual ~CGXClientSite();

// IUnknown
	GRID_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
    
	GRID_API virtual ULONG STDMETHODCALLTYPE AddRef( void);
    
	GRID_API virtual ULONG STDMETHODCALLTYPE Release( void);
	
// IOleClientSite
	STDMETHOD(SaveObject)(void);

	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

	STDMETHOD(GetContainer)(IOleContainer **ppContainer);

	STDMETHOD(ShowObject)(void);

	STDMETHOD(OnShowWindow)(BOOL fShow);

	STDMETHOD(RequestNewObjectLayout)(void);

	// access
	GRID_API CGXOleViewer* GetViewer();

protected:
// data
	ULONG m_cRef;
	CGXOleViewer* m_pViewer;
};


class CGXAdviseSink : public IAdviseSink
{
public:
	GRID_API CGXAdviseSink(CGXOleViewer* pViewer);
	GRID_API virtual ~CGXAdviseSink();

// IUnknown
	GRID_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
    
	GRID_API virtual ULONG STDMETHODCALLTYPE AddRef( void);
    
	GRID_API virtual ULONG STDMETHODCALLTYPE Release( void);

	GRID_API virtual void STDMETHODCALLTYPE OnDataChange( 
             FORMATETC __RPC_FAR *pFormatetc,
            STGMEDIUM __RPC_FAR *pStgmed);
        
    GRID_API virtual void STDMETHODCALLTYPE OnViewChange( 
            DWORD dwAspect,
            LONG lindex);
        
    GRID_API virtual void STDMETHODCALLTYPE OnRename( 
            IMoniker __RPC_FAR *pmk);
        
    GRID_API virtual void STDMETHODCALLTYPE OnSave( void);
        
    GRID_API virtual void STDMETHODCALLTYPE OnClose( void);

//access
	GRID_API CGXOleViewer* GetViewer();

	protected:
// data
	ULONG m_cRef;
	CGXOleViewer* m_pViewer;
	
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_GX_CL_SITE__H__

#endif
