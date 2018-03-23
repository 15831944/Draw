///////////////////////////////////////////////////////////////////////////////
// Otlsimpleframe.h
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

#ifndef __OTLSIMPLEFRAME_H__
#define __OTLSIMPLEFRAME_H__

#ifndef __OTLBASE_H__
	#error otlsimpleframe.h requires otlbase.h to be included first
#endif

#include <atlcom.h>
#include <StingrayExportDefs.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

////////////////////////////////////////////////////////////////////////////
// Replace BEGIN_MSG_MAP with BEGIN_MSG_MAP_SIMPLEFRAME
//
// This will pass messages along to the simple frame site to give it a
// chance to process the messages
//
#define BEGIN_MSG_MAP_SIMPLEFRAME(theClass)\
	public:\
	ISimpleFrameSite* m_pSimpleFrameSite;\
	BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam,\
		LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)\
	{\
		HRESULT hr=S_OK;\
	    LRESULT lr;\
		DWORD   dwCookie=0;\
		if(m_pSimpleFrameSite)\
		{\
			if(AllowPreMessageFilter(uMsg))\
            hr = m_pSimpleFrameSite->PreMessageFilter(hWnd, uMsg, wParam, lParam, &lr, &dwCookie);\
			if( hr == S_FALSE && !IgnorePreMessageFilterReturn(uMsg)){return TRUE;}\
		}\
        BOOL bProcessed = ProcessWindowMessageEx(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);\
        if(m_pSimpleFrameSite && hr == S_OK)\
			m_pSimpleFrameSite->PostMessageFilter(hWnd, uMsg, wParam, lParam, &lr, dwCookie);\
       return bProcessed;\
	}\
	public:\
		BOOL ProcessWindowMessageEx(HWND hWnd, UINT uMsg, WPARAM wParam,\
			LPARAM lParam, LRESULT& lResult,\
			DWORD dwMsgMapID = 0)\
        {\
			BOOL bHandled = TRUE;\
			hWnd;\
            switch(dwMsgMapID)\
            {\
               case 0:

////////////////////////////////////////////////////////////////////////////
// Replase IOleObjectImpl with OtlIOleObjectWithSimpleFrameImpl in 
// inheritence chain
//
template <class T>
class OtlIOleObjectWithSimpleFrameImpl : public IOleObjectImpl<T>
{
public:
   // constructor
	inline OtlIOleObjectWithSimpleFrameImpl()
	{
      T* pT = static_cast<T*>(this);
		pT->m_pSimpleFrameSite = NULL;
	}

   // destructor
	inline ~OtlIOleObjectWithSimpleFrameImpl()
	{
      T* pT = static_cast<T*>(this);
		if (pT->m_pSimpleFrameSite)
			pT->m_pSimpleFrameSite->Release();
	}

	// SetClientSite override
	inline STDMETHOD(SetClientSite)(IOleClientSite *pClientSite) 
	{
      HRESULT hr = IOleObjectImpl<T>::SetClientSite(pClientSite);

		// Release the simple frame
      T* pT = static_cast<T*>(this);
		if (pT->m_pSimpleFrameSite)
		{
			pT->m_pSimpleFrameSite->Release();
         pT->m_pSimpleFrameSite = NULL;
		}

      if( pClientSite != NULL )
      {
		   hr = pClientSite->QueryInterface(IID_ISimpleFrameSite, (void **)&pT->m_pSimpleFrameSite);
      }
      return hr; 
	}

   // Implementation
   virtual BOOL AllowPreMessageFilter(UINT nMsg) 
   { 
      if (nMsg == WM_PAINT)
         return FALSE;
      else
         return TRUE; 
   }

   virtual BOOL IgnorePreMessageFilterReturn(UINT nMsg) 
   { 
      UINT arMsg[] = { WM_PARENTNOTIFY, WM_PAINT, WM_NOTIFY, WM_LBUTTONDOWN,
         WM_MOUSEMOVE, WM_LBUTTONUP, WM_SETCURSOR, WM_COMMAND, WM_CTLCOLOREDIT,
         WM_CTLCOLORSTATIC,WM_CTLCOLORBTN };
      int num = sizeof(arMsg)/sizeof(UINT);

      for (int i=0; i<num; i++)
      {
         if (arMsg[i] == nMsg)
            return TRUE;
      }
      return FALSE; 
   }

};

////////////////////////////////////////////////////////////////////////////
//	And finally, OR in 0x10000 for the value of MiscStatus in the .rgs
//	file.  For instance, change: 
//		'MiscStatus' = s '0'{   '1' = s '131473'}
//	to:
//		'MiscStatus' = s '0'{   '1' = s '197009'}
//
//
// Also, the SimpleFrame can not be windowless.  Make sure the following
// statement is in your object's constructor:
//
//	m_bWindowOnly = TRUE; 
// 

};	// namespace StingrayOTL

#endif // __OTLSIMPLEFRAME_H__
