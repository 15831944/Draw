///////////////////////////////////////////////////////////////////////////////
// Otlbandplugin.h
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

#ifndef __OTLBANDPLUGIN_H__
#define __OTLBANDPLUGIN_H__

#ifndef __OTLBASE_H__
	#error otlbandplugin.h requires otlbase.h to be included first
#endif

#include <atlwin.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL
{

#define CHAIN_OTL_BAND(theClass) CHAIN_MSG_MAP(COtlBandPlugin<theClass>)

/////////////////////////////////////////////////////////////////////////////
// OtlBandPlugin<T>
//
// assumes base class T has access to GetUnknown() and IInputObject* m_pInputObjectSite

template <class T>
class COtlBandPlugin : public CMessageMap
{
public:
	BEGIN_MSG_MAP(COtlBandPlugin)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	END_MSG_MAP()

	inline LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NotifyFocusChange(FALSE);
		bHandled = FALSE;
		return 1;
	}

	inline LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NotifyFocusChange(TRUE);
		bHandled = FALSE;
		return 1;
	}

	virtual void NotifyFocusChange(BOOL bHasFocus)
	{
		T* pT = static_cast<T*>(this);
		pT->m_bHasFocus = bHasFocus;	// declared in OtlIInputObjectImpl
		if(pT->m_pInputObjectSite)		// declared in OtlIObjectWithSiteImpl
			pT->m_pInputObjectSite->OnFocusChangeIS(pT->GetUnknown(), bHasFocus);
	}

};

}; // namespace StingrayOTL

#endif // __OTLBANDPLUGIN_H__
