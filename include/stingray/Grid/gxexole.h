///////////////////////////////////////////////////////////////////////////////
// gxexole.h
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


#ifndef _GX_EX_OLE_H__
#define _GX_EX_OLE_H__

#ifndef __ATLBASE_H__
#include <atlbase.h>
#endif // __ATLBASE_H__

// #include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// IDataObject and IEnumFORMATETC for clipboard support

class CGXEnumFormatEtc : public IEnumFORMATETC    
{    
 public: 
        GRID_API CGXEnumFormatEtc(ULONG, LPFORMATETC); 
        GRID_API ~CGXEnumFormatEtc(void);  
        
		//IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *); 
        STDMETHODIMP_(ULONG) AddRef(void); 
        STDMETHODIMP_(ULONG) Release(void);          //IEnumFORMATETC members 
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG *); 
        STDMETHODIMP Skip(ULONG);         STDMETHODIMP Reset(void); 
        STDMETHODIMP Clone(IEnumFORMATETC **);     

protected: 
        ULONG           m_cRef;     //Object reference count 
        ULONG           m_iCur;     //Current element 
        ULONG           m_cfe;      //Number of FORMATETCs we hold
        LPFORMATETC     m_prgfe;    //Source of FORMATETCs     
};  

//////////////////////////////////////////////////////////////////////////////
// CGXDataObjectImpl
// 
class CGXDataObjectImpl : public IDataObject
{
public:
	GRID_API CGXDataObjectImpl(IStorage* pStorage, HGLOBAL hG);
	GRID_API ~CGXDataObjectImpl();

	// IUnknown
	//
	GRID_API virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject);
	GRID_API virtual ULONG STDMETHODCALLTYPE AddRef( void);
    GRID_API virtual ULONG STDMETHODCALLTYPE Release( void);

	// IDataObject
	//
	STDMETHOD(GetData)(FORMATETC *pformatetcIn, STGMEDIUM *pmedium);
	STDMETHOD(GetDataHere)(FORMATETC* /* pformatetc */, STGMEDIUM* /* pmedium */);
	STDMETHOD(QueryGetData)(FORMATETC* /* pformatetc */);
	STDMETHOD(GetCanonicalFormatEtc)(FORMATETC* /* pformatectIn */,FORMATETC* /* pformatetcOut */);
	STDMETHOD(SetData)(FORMATETC* /* pformatetc */, STGMEDIUM* /* pmedium */, BOOL /* fRelease */);
	STDMETHOD(EnumFormatEtc)(DWORD dwDirection, IEnumFORMATETC**  ppenumFormatEtc);
	STDMETHOD(DAdvise)(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
		DWORD *pdwConnection);
	STDMETHOD(DUnadvise)(DWORD dwConnection);
	STDMETHOD(EnumDAdvise)(IEnumSTATDATA **ppenumAdvise);
	
protected:
	CComPtr<IDataAdviseHolder> m_spDataAdviseHolder;
	ULONG m_cRef;
	
	IStorage* m_pStorage;
	HGLOBAL m_hGlobal;

	CGXEnumFormatEtc* pEnumFormatEtc;
};

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif //_GX_EX_OLE_H__
