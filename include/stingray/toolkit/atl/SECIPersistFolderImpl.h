///////////////////////////////////////////////////////////////////////////////
// SECIPersistFolderImpl.h
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

#if !defined(AFX_SECIPERSISTFOLDERIMPL_H__B8E793A4_B850_49D4_88B3_C6330C8B93D5__INCLUDED_)
#define AFX_SECIPERSISTFOLDERIMPL_H__B8E793A4_B850_49D4_88B3_C6330C8B93D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////
// AutoDuck tag block block for SECIPersistFolderImpl 
// adinsert AutoDuck insertion point for SECIPersistFolderImpl 
//@topic SECIPersistFolderImpl  Class Overview |
//This class is a thin wrapper of IPersistFolder interface. It assumes that
//the template argument class will provide implementation for IUnknown and
//also implemented GetObjectCLSID. It is intended to be derived by ATL COM
//object.

//@doc SECIPersistFolderImpl 
//@class This class is a thin wrapper of IPersistFolder interface. It assumes that
//the template argument class will provide implementation for IUnknown and
//also implemented GetObjectCLSID. It is intended to be derived by ATL COM
//object. <nl>
//<nl>
//For a complete documentation of IPersistFolder, please refer to windows SDK or MSDN from Microsoft.
template<typename T>
class ATL_NO_VTABLE SECIPersistFolderImpl : public IPersistFolder 
{
public:

	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(SECIPersistFolderImpl)

	inline STDMETHOD(GetClassID)(CLSID* pClsID)
	{
		*pClsID = T::GetObjectCLSID();
		return S_OK;
	}
	inline STDMETHOD(Initialize)(LPCITEMIDLIST /*pidl*/)
	{
		return S_OK;
	}
};

#endif // !defined(AFX_SECIPERSISTFOLDERIMPL_H__B8E793A4_B850_49D4_88B3_C6330C8B93D5__INCLUDED_)
