///////////////////////////////////////////////////////////////////////////////
// gxcole.h
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

#ifndef _GXCOLE_H__
#define _GXCOLE_H__

#ifndef _GXCTRLI_H_
#include "gxctrli.h"
#endif


#ifndef _WIN64
#ifndef _GXDAO_H_
#include "gxdao.h"
#endif
#endif	// _WIN64

#ifndef _GX_MAN_H__
#include "gxman.h"
#endif

#include <afxole.h>

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

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

// CGXOleViewer creator
class CGXViewerFactory
{	
public:
// construction
	GRID_API CGXViewerFactory();
	
	GRID_API ~CGXViewerFactory();

	// creation helper
	GRID_API CGXOleViewer* CreateViewer(SEC_DWORD dw);
};


// Simple garbage collection support. Will use CGXViewerFactory to
// create the objects
class CGXViewerManager: CGXNodeManager<CGXOleViewer>
{
public:
	GRID_API CGXViewerManager(CGXViewerFactory* pFactory);
	
	GRID_API virtual ~CGXViewerManager();
	GRID_API virtual CGXOleViewer* CreateObject(SEC_DWORD dw);

// simply a wrapper for CreateObject
	GRID_API virtual CGXOleViewer* CreateViewer(SEC_DWORD dw);

//access
	GRID_API CGXViewerFactory* GetViewerFactory();

// simple diagnostics
	GRID_API void InternalCheck() const;

protected:
	CGXViewerFactory* m_pFactory;
};	

class CGXOlePreview;


// Generic viewer implementation for all kinds of objects
// You can have more specialized viewers for particular kinds of data
class CGXGenericViewerImpl: public CGXOleViewer
{
public:
// construction
	GRID_API CGXGenericViewerImpl();
	
	GRID_API virtual ~CGXGenericViewerImpl();

	// Creation
	
	// Create an IOleClientSite Impl. Override if you want to use another client site
	// implementation
	GRID_API virtual IOleClientSite* GetClientSite();

	// Create an IAdviseSink Impl.
	GRID_API virtual IAdviseSink* GetAdviseSink();


// overrides:
	// This can spawn an external viewer etc
	GRID_API virtual void Render(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl, BOOL bShow = TRUE);

	// activate an existing viewer. Use the stored IOleObject etc
	GRID_API virtual void ActivateExisting();

	GRID_API virtual BOOL CreateNew(CGXGridCore* pGrid);

	// no rendering...simply return data
	GRID_API virtual HGLOBAL AccessData(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl);

	// This should close any external viewer etc
	GRID_API virtual void Close();

	// clear any data held
	GRID_API virtual void Clear();
	
	// save from the contained storage object
	GRID_API virtual void SaveFromStorage();

	// the verb that is to be sent as part of the DoVerb call
	GRID_API virtual long GetVerb();

	// spawn the external viewer
	GRID_API virtual BOOL SpawnViewer(HGLOBAL hReadData, CGXGridCore* pGrid,  BOOL bShow);
//access
	// get the stored data
	GRID_API virtual COleVariant& GetData();

	// access the storage 
	GRID_API virtual LPSTORAGE GetStorage();

	// access the IOleObject pointer
	GRID_API virtual LPOLEOBJECT GetOleObject();
	
	// access the interface manager
	GRID_API virtual CGXInterfaceManager<IUnknown>& GetInterfaceManager();

// clipboard support
	GRID_API virtual BOOL CanPaste();

	GRID_API virtual COleVariant* Paste();

	GRID_API virtual BOOL CanCopy();
	
	GRID_API virtual IDataObject* Copy(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl);
	
	GRID_API virtual BOOL CanCut();
	
	GRID_API virtual IDataObject* Cut(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl);

	GRID_API virtual BOOL CanCopyCanCutHelper();

// data
	enum eViewerFlags
	{
		eBlankImage,
		eInvalidData,
		eDataAllocFails,
		eInvalidOleStreamData,
		eStreamAllocFails,
		eNoClientSite,
		eDataWriteFails,
	};

protected:
	// variant to hold the data (SAFEARRAY data in this viewer)
	COleVariant m_oleVariant;

	// The interface manager
	// We do not have member variables for all the interfaces that we have to retain as members
	// We have the interface manager that can hold exactly one interface pointer of each type of
	// interface IID.
	CGXInterfaceManager<IUnknown> m_InterfaceMgr;
	
	// advise cookie for IAdviseSink
	DWORD m_dwAdviseCookie;
};


// CGXOlePreview
class CGXOlePreview : public CGXStatic
{
	GRID_DECLARE_CONTROL(CGXOlePreview)

// Construction
public:
	// Constructor & Destructor
	GRID_API CGXOlePreview(CGXBrowserGrid* pGrid, CGXViewerFactory* pFactory = NULL);
	GRID_API virtual ~CGXOlePreview();

// CGXControl overrides
	GRID_API virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);
	
	GRID_API virtual void SetModify(BOOL bModified);
	GRID_API virtual BOOL GetModify();
	
	GRID_API virtual BOOL IsActive();
	GRID_API virtual void SetActive(BOOL bActive);

	GRID_API void Init(ROWCOL nRow, ROWCOL nCol);
	GRID_API virtual BOOL Store();

	GRID_API virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	GRID_API virtual CSize AddBorders(CSize size, const CGXStyle& style);
	
	GRID_API virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
	GRID_API virtual void OnClickedButton(CGXChild* pChild);

	GRID_API virtual BOOL CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL);
	
	GRID_API virtual BOOL OnLeftCell(ROWCOL nNewRow, ROWCOL nNewCol);

	GRID_API virtual BOOL OnCancelEditing();

	GRID_API virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);
	GRID_API virtual void SetCurrentText(const CString& str);

	GRID_API virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
// clipboard support
	GRID_API virtual BOOL Paste();

	GRID_API virtual BOOL CanPaste();

	GRID_API virtual BOOL CanCopy();
	
	GRID_API virtual BOOL Copy();
	
	GRID_API virtual BOOL CanCut();
	
	GRID_API virtual BOOL Cut();

	GRID_API virtual BOOL CanCopyCanCutHelper();

// new overrides
	GRID_API virtual HWND PreRender();
	
	GRID_API virtual void PostRender(HWND hWndFocus);
	
	GRID_API virtual void PostDoVerb();
	
	GRID_API virtual void PreDoVerb();

	// will be called when there is a viewer present and the user attempts a 
	// clipboard operation
	GRID_API virtual void OnActiveViewerPresent();

//access
	GRID_API void SetActiveViewer(CGXOleViewer* pViewer);
	GRID_API CGXOleViewer* GetActiveViewer() const;

	GRID_API CGXViewerManager* GetViewerManager() const;

	GRID_API virtual CGXOleViewer* GetOleViewer();

// data;
	CGXOleViewer*		m_pActiveViewer;
	CGXViewerManager*	m_pViewerManager;
// for the modified state
	BOOL				m_bModified;
// for the active state
	BOOL				m_bActive;
// for the Discard NC Activate state
	BOOL				m_bDiscardActivate;
// CGXChild for the button
	CGXHotSpotButton*	m_pHotSpot;
};

/*
Access specific declarations

Access writes an OLE object to a LONG_BINARY field as follows

	1. write the header
	2. write the name				GetUserType( USERCLASSTYPE_SHORT )
	3. write the class				ProgIDFromCLSID
	4. write the storage			OleConvertIStorageToOLESTREAM 

////////////////////////////////////////////////////////////////////////////
One remaining item is that before Access actually writes out the storage, 
it adds a stream to it that contains information that is lost in the process 
of OleConvertIStorageToOLESTREAM/OleConvertOLESTREAMToIStorage. However, 
if this stream isn't there, Access just uses the defaults so it isn't fatal.
////////////////////////////////////////////////////////////////////////////

This means that to read an object back in the following steps have to
be taken:

	1. read the header
	2. read the name				(ignore)
	3. read the class				CLSIDFromProgID
	4. read the storage				OleConvertOLESTREAMToIStorage 
	
////////////////////////////////////////////////////////////////////////////
For completelness, the special stream that was saved when the object was 
written (if it's there) could be read in and some properties of the object 
could be set based on that.
////////////////////////////////////////////////////////////////////////////

*/

//#include "stdafx.h"

#define MAX_PROGID	128

/////////////////////////////////////////////////////////////////////////////
// struct OLEOBJHDR: defined how ACCESS stores OLE objects

typedef struct _oleobjhdr 
{
	WORD typ;				// Type signature (Always 'OC' == 0x1c15)
	WORD cbHdr;				// Size of header
	union {
		OLE_OBJTYPE oot;	// OLE Object type code (OT_LINK, OT_EMBEDDED, OT_STATIC)
		LONG lobjTyp;		// in our case: OT_EMBEDDED
	};
	WORD cchName;			// Count of characters in object name
	WORD cchClass;			// Count of characters in class name
	WORD ibName;			// Offset of object name in stream
	WORD ibClass;			// Offset of class name in stream
	POINTS ptSize;			// Original size of object --- NOTE:
							// ptSize was not being used for its intended purpose, 
							// so for Access 2.0 and later, these should be set 
							// ptSize.x = ptSize.y = -1.  Access uses this to 
							// determine what version saved the object to the 
							// database (Access <= 1.1 uses positive values).
} OLEOBJHDR;
typedef OLEOBJHDR* POLEOBJHDR;

/////////////////////////////////////////////////////////////////////////////
// helper functions to read ACCESS header

GRID_API int				ReadAccessHeader(HGLOBAL hgMemSource, LPCLSID lpclsid );
GRID_API int				WriteAccessHeader(HGLOBAL hgMemSource, IOleObject* pObject );
GRID_API HGLOBAL			SkipAccessHeader(HGLOBAL hgMemSource, DWORD* pdwObjectLength );


/////////////////////////////////////////////////////////////////////////////
// struct OLE1STREAM : OLESTREAM struct w/ knowledge of IStream

typedef struct _ole1stream
{
	LPOLESTREAMVTBL pvt;		// OLESTREAMVTBL pointer
	LPSTREAM		lpStream;	// Pointer obtained by CreateStreamOnHGlobal()
	DWORD			dwSize;		// OLESTREAM length (relative to position)
} OLE1STREAM;
typedef OLE1STREAM* LPOLE1STREAM;	


/////////////////////////////////////////////////////////////////////////////
// helper functions to read OLESTREAM

GRID_API LPOLE1STREAM	 _GXCreateOle1Stream(LPSTREAM pStm, DWORD dwSize );
GRID_API void			 _GXDeleteOleStream(LPOLE1STREAM pStream );
GRID_API DWORD FAR PASCAL _GXGet(LPOLESTREAM pstm, void FAR* pb, DWORD cb );
GRID_API DWORD FAR PASCAL _GXPut(LPOLESTREAM pstm, const void FAR* pb, DWORD cb );

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
//

#endif
