///////////////////////////////////////////////////////////////////////////////
// SECBand.h
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

#if !defined(AFX_SECBAND_H__33BCDFDD_A899_48B9_867C_89BCD1F85497__INCLUDED_)
#define AFX_SECBAND_H__33BCDFDD_A899_48B9_867C_89BCD1F85497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <shlguid.h>
#include <comdef.h>
#include <shlobj.h>

/////////////////////////////
// AutoDuck tag block block for SECBandImpl 
////////////////////////////////////////////////////////////////////////////////////////////////
//SECBandImpl<class T, const CLSID* pclsid>
//@doc SECBandImpl
//@mfunc WCHAR* | SECBandImpl | GetBandTitle | This function allows you to change the titile string for your band object. which is called from
//inside the GetBandInfo method of IDeskBand.
//@rdesc WCHAR* Pointer to the title string.

//@doc SECBandImpl
//@mfunc DWORD | SECBandImpl | GetBandModeFlag | This function allows you to decide what band mode flag to return when Explorer requests for band 
//mode from by calling GetBandInfo method of IDeskBand. Refer to DESKBANDINFO structure in Win32 SDK
//for the possible value you can use.<nl>
//@rdesc DWORD The band mode flag you want to be used.

//@doc SECBandImpl
//@mfunc SIZE | SECBandImpl | GetBandSize | This function allows you to controls the band size. GetBandInfo method of IDeskBand interface will
//call this funtion to negotiate the size for the band.  Refer to DESKBANDINFO structure
//in Win32 SDK for details of these values. 
//@rdesc SIZE The suggest size to be used.
//@parm DWORD | wFlags | wFlags can be one of the following values defined
//in Win32 SDK: DBIM_MINSIZE, DBIM_MAXSIZE, DBIM_INTEGRAL, DBIM_ACTUAL.
//@parm  DWORD | dwBandID | The same value as that of GetBandInfo method of IDeskBand. See IDeskBand::GetBandInfo in
//Win32 SDK for details.
//@parm  DWORD | dwViewMode | The same value as that of GetBandInfo method of IDeskBand. See IDeskBand::GetBandInfo in 
//Win32 SDK for details.

// IOleWindow methods
//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | GetWindow | See IOleWindow::GetWindow in Win32 SDK for details. Default implementation assigns the 
//window handle m_hWnd of the derived class to *phWnd argument and return S_OK.
//@rdesc HRESULT 
//@parm HWND* | phWnd |

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | ShowDW | See IDockingWindow::ShowDW in Win32 SDK for details. The default implementation shows or hide
//the derived class window if the derived class has a valid window.
//@rdesc HRESULT Return S_OK.
//@parm BOOL | fShow | Flags to show or to hide the window of the derived class.

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | CloseDW | See IDockingWindow::CloseDW in Win32 SDK for details. The default implementation first calls
//ShowDW(FALSE) and then destroy the window object of the derived class if the derived class window is
//valid.
//@rdesc HRESULT Return S_OK.
//@parm DWORD | dwReserved | Not used.

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | GetBandInfo | See IDeskBand::GetBandInfo in Win32 SDK for details. The default implementation
//calls GetBandSize method to get the proper request size of the band and
//calls GetBandTitle method to get a title string and calls GetBandModeFlag method
//to get the band mode flag and then place all this information in the given
//pointer to DESKBANDINFO structure pdbi according to the dwMask information in the
//pdbi argument.
//@rdesc HRESULT Return S_OK if pdbi is not NULL, otherwise return E_INVALIDARG.
//@parm DWORD | dwBandID | Band ID assigned by the site of the band. It is not saved in this
//method. If you need to use it, you should override this method.
//@parm  DWORD | dwViewMode | The view mode of the band. It is not saved in this method.
//If you need to use it, you should override this method.
//@parm  DESKBANDINFO* | pdbi | Structure to obtain requested information of the band.

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | SetSite | See IObjectWithSite::SetSite in Win32 SDK for details. Default implementation in this
//class does three things. First it obtains the window handle from the given site interface and
//store the handle in the m_hParentWnd member if succeeded. Then it call the create method of
//the derived class to create the window object for the derived class if it is not alread created.
//So the dervived class must contain a method Create(HWND, cont RECT&). Finally, it calls
//QueryInterface of the given site object to obtains IInputObjectSite interface to store it
//in the m_pSite member for later use. If all three are succeeded, return S_OK, otherwise return E_FAIL.
//@rdesc HRESULT If succeeded return S_OK, otherwise return E_FAIL.
//@parm IUnknown* | pUnkSite | The site this band will be lived in.

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | GetSite | See IObjectWithSite::GetSite in Win32 SDK for details. Default implementation 
//calls QueryInterface method of the m_pSite member if it is valid. If m_pSite member is
//not valid, the method return E_FAIL.
//@rdesc HRESULT 
//@parm REFIID | riid |
//@parm  LPVOID* | ppObj |

//@doc SECBandImpl
//@mfunc HRESULT | SECBandImpl | GetClassID | See IPersistStream::GetClassID in Win32 SDK for details. Default implementation assigns
//the CLSID given in the second template argument to the CLSID pointer in the arguments and return S_OK.
//@rdesc HRESULT 
//@parm LPCLSID | pClsID |

// adinsert AutoDuck insertion point for SECBandImpl 

//@doc SECBandImpl 
//@class SECBandImpl
//@comm This class implements IDeskBand, IObjectWithSite and IPerisitStream interfaces that
//are required by IE band object and Deskband object. This class provide default 
//implementation for all four band object, i.e. Verical Explorer band, Horizontal
//Expplorer band, Explorer Toolbar band and Desk band object. By combining this 
//implementation and our IE Band Wizard, we don't need to add any code to get full
//functional band object of the four kind. 
//This class requires two template arguments, the class in the first template argument 
//is required to implement Create function and have a window handle member variable m_hWnd, 
//which is typically done by inheriting from CWindowImpl or similar window class in the ATL.
//The second template argument is a pointer to the CLSID of your COM object that implement this band
//object.
//To use this object, you generally use our IE band Wizard to generate a skeleton Band object.
//You can then handle the window message to create child controls or draw on the band window.
//You can also use our IContextMenu implementation class OtlIContextMenuImpl to simplify the
//context menu implementation for your band object. Other than the methods in the interfaces
//IDeskBand, IObjectWithSite and IPersistStream, this class provide a few virtual functions
//to simplify this implementation.
//<nl>
//<nl>
//From a development perspective, the difference among the four type of band object are minor.
//In fact, the only difference among types is the registry category. However, our band wizard
//automatically generated the required registration code for you. That why we recommend you to
//start from our IE Band Wizard. 
//<nl>
//<nl>
//Note that the Band object requires IE 4.01 SP1 or higher, while the Toolbar Band object 
//requires IE 5.0 or higher. After registration, the Deskband object can be accessed from the 
//toolbars menu by right click the taskbar, the Vertial and Horizontal IE Band can be accessed
//from "View->Explorer Bar" menu of IE, the toolbar band can be accessed from "View->toolbars"
//menu of IE.
//@tcarg class | T | The derived class
//@tcarg const CLSID* | pclsid | A pointer to the CLSSS ID of the derived class
//@base public | IDeskBand
//@base public | IObjectWithSite
//@base public | IPersistStream
template <typename T, const CLSID* pclsid>
class SECBandImpl :	public IDeskBand,
									public IObjectWithSite,
									public IPersistStream
{
protected:
	HWND	m_hParentWnd;

	CComQIPtr<IInputObjectSite, &IID_IInputObjectSite> m_pSite;

public:
	inline SECBandImpl()
	{
		m_hParentWnd = NULL;
	}	
	//@cmember
	/* Get band title string */
	virtual WCHAR* GetBandTitle()
	{
		return L"Your Band";
	}
	//@cmember
	/* Get band mode flag */
	virtual DWORD GetBandModeFlag()
	{
		return DBIMF_VARIABLEHEIGHT;
	}
	//@cmember
	/* Get band size */
	virtual SIZE GetBandSize(DWORD wFlags, DWORD dwBandID, DWORD dwViewMode)
	{
		SIZE sz;
		switch( wFlags )
		{
		case DBIM_MINSIZE:
			sz.cx = 15;
			sz.cy = 15;
			break;
		case DBIM_MAXSIZE:
			sz.cx = -1;
			sz.cy = -1;
			break;
		case DBIM_INTEGRAL:
			sz.cx = 1;
			sz.cy = 1;
			break;
		case DBIM_ACTUAL:
			sz.cx = 0;
			sz.cy = 0;
			break;
		default:
			ATLASSERT(FALSE); // Wrong flags
		}
		return sz;
	}

	// IOleWindow methods
	inline STDMETHOD (GetWindow) (HWND* phWnd)
	{
		T* pT = static_cast<T*>(this);
	   *phWnd = pT->m_hWnd;
	   return S_OK;
	}
	inline STDMETHOD (ContextSensitiveHelp) (BOOL)
	{
	   return E_NOTIMPL;
	}

	//IDockingWindow methods
	inline STDMETHOD (ShowDW) (BOOL fShow)
	{
		T* pT = static_cast<T*>(this);
	   if( pT->m_hWnd != NULL )
	   {
		   ::ShowWindow(pT->m_hWnd, fShow ? SW_SHOW : SW_HIDE);
	   }
	   return S_OK;
	}
	inline STDMETHOD (CloseDW) (DWORD dwReserved)
	{
		T* pT = static_cast<T*>(this);
		ShowDW(FALSE);
		if( ::IsWindow(pT->m_hWnd) )
			::DestroyWindow(pT->m_hWnd);
	    pT->m_hWnd = NULL;
	    return S_OK;
	}
	inline STDMETHOD (ResizeBorderDW) (LPCRECT prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
	{
		return E_NOTIMPL;
	}

	//IDeskBand methods
	inline STDMETHOD(GetBandInfo)(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
	{
		if(pdbi)
		{
			if(pdbi->dwMask & DBIM_MINSIZE)
			{
				SIZE sz = GetBandSize(DBIM_MINSIZE, dwBandID, dwViewMode);
				pdbi->ptMinSize.x = sz.cx;
				pdbi->ptMinSize.y = sz.cy;
			}

			if(pdbi->dwMask & DBIM_MAXSIZE)
			{
				SIZE sz = GetBandSize(DBIM_MAXSIZE, dwBandID, dwViewMode);
				pdbi->ptMaxSize.x = sz.cx;
				pdbi->ptMaxSize.y = sz.cy;
			}

			if(pdbi->dwMask & DBIM_INTEGRAL)
			{
				SIZE sz = GetBandSize(DBIM_INTEGRAL, dwBandID, dwViewMode);
				pdbi->ptIntegral.x = sz.cx;
				pdbi->ptIntegral.y = sz.cy;
			}

			if(pdbi->dwMask & DBIM_ACTUAL)
			{
				SIZE sz = GetBandSize(DBIM_ACTUAL, dwBandID, dwViewMode);
				pdbi->ptActual.x = sz.cx;
				pdbi->ptActual.y = sz.cy;
			}

			if(pdbi->dwMask & DBIM_TITLE)
				lstrcpynW(pdbi->wszTitle, GetBandTitle(), 256);

			if(pdbi->dwMask & DBIM_MODEFLAGS)
				pdbi->dwModeFlags = GetBandModeFlag();

			if( pdbi->dwMask & DBIM_BKCOLOR )
			{
				//Use the default background color by removing this flag.
				pdbi->dwMask &= ~DBIM_BKCOLOR;
			}
			return S_OK;
		}
		return E_INVALIDARG;
	}

	//IObjectWithSite methods
	inline STDMETHOD (SetSite) (IUnknown* pUnkSite)
	{
	   m_pSite = (IUnknown*)NULL;
	   if( pUnkSite == NULL )
		   return E_FAIL;
		CComPtr<IOleWindow> spOleWnd;
		m_hParentWnd = NULL;
		if( SUCCEEDED(pUnkSite->QueryInterface(&spOleWnd)) )
			spOleWnd->GetWindow(&m_hParentWnd);
		if( m_hParentWnd == NULL )
			return E_FAIL;

		T* pT = static_cast<T*>(this);
		if( pT->m_hWnd == NULL )
		{
			RECT rc;
			::GetClientRect(m_hParentWnd, &rc);
			if( !pT->Create(m_hParentWnd, rc) )
				return E_FAIL;
		}
		if( SUCCEEDED(pUnkSite->QueryInterface(&m_pSite) ) )
			return S_OK;
		return E_FAIL;
	}
	inline STDMETHOD (GetSite) (REFIID riid, LPVOID* ppObj)
	{
	   *ppObj = NULL;
	   if( m_pSite )
		   return m_pSite->QueryInterface(riid, ppObj);
	   return E_FAIL;
	}

	//IPersistStream methods
	inline STDMETHOD (GetClassID) (LPCLSID pClsID)
	{
		*pClsID = *pclsid; // In the template argument
		return S_OK;
	}

	inline STDMETHOD (IsDirty)()
	{
	   return S_FALSE;
	}
	inline STDMETHOD (Load) (LPSTREAM)
	{
	   return S_OK;
	}
	inline STDMETHOD (Save) (LPSTREAM, BOOL)
	{
	   return S_OK;
	}
	inline STDMETHOD (GetSizeMax) (ULARGE_INTEGER*)
	{
	   return E_NOTIMPL;
	}

};

#endif // !defined(AFX_SECBAND_H__33BCDFDD_A899_48B9_867C_89BCD1F85497__INCLUDED_)
