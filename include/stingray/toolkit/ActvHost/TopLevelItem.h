///////////////////////////////////////////////////////////////////////////////
// TopLevelItem.h
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
//  UPDATE LOG:
//
//     06.19.06  exported classes/methods with TOOLKIT_API macro by csd
//

#ifndef _TOP_LEVEL_ITEM_H
#define _TOP_LEVEL_ITEM_H

#include "toolkit\ActvHost\MultInfo.h"
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

class SECATopLevelItem : public CCmdTarget
{
public:
	TOOLKIT_API SECATopLevelItem( LPUNKNOWN pControlUnknown );

protected:
	TOOLKIT_API virtual ~SECATopLevelItem();

	DECLARE_INTERFACE_MAP()

	//for IProvideMultipleClassInfo
	BEGIN_INTERFACE_PART(ProvideMultipleClassInfo, IProvideMultipleClassInfo)
		INIT_INTERFACE_PART(ProvideMultipleClassInfo, IProvideMultipleClassInfo)
		STDMETHOD(GetMultiTypeInfoCount)(ULONG *pcti);
		STDMETHOD(GetInfoOfIndex)(ULONG iti, DWORD dwFlags, ITypeInfo** pptiCoClass, DWORD* pdwTIFlags, ULONG* pcdispidReserved, IID* piidPrimary, IID* piidSource);
		STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID* pGUID);
		STDMETHOD(GetClassInfo)(ITypeInfo** pptinfoOut);
	END_INTERFACE_PART(ProvideMultipleClassInfo)

	LPUNKNOWN m_pControlUnknown;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif
