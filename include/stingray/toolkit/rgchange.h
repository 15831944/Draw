///////////////////////////////////////////////////////////////////////////////
// rgchange.h
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

#ifndef __RG_CHNG_H__
#define __RG_CHNG_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "rgbase.h"

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

namespace stingray_ot_rg {

// default implementation to manage dirty state flag
//@doc CRgChange
//@class CRgChange | This class is used by <c CRgProcessor>, <c CRgSubState> and
//<c CRgState> to maintain information about whether their
//states were changed since the last compilation (<mf CRgProcessor::Compile>). If you are
//setting up the scanner statically in the <mf CRgProcessor::Initialize> method 
//as in the deals sample then you do not have to worry about
//checking the flag since you basically need to call Compile only once after you
//have set everything up.
//@xref <c CRgProcessor>
//@base public | CRgChange

// Exported through base class. 
struct CRgChange : public IChange
{
// constructor/destructor	
	inline CRgChange():m_bIsDirty(false){
		 // no implementation
	}

	inline virtual ~CRgChange(){
		// no implementation
	}

// accessor
	//@cmember
	//You can call this function to check if the dirty flag is set.
	inline virtual bool IsDirty() const{
		return m_bIsDirty;
	}

// modifier	
	inline virtual bool SetDirty(bool b = true){
		bool _b = m_bIsDirty; 
		m_bIsDirty = b;
		return _b;
	}

protected:
	bool m_bIsDirty;
};

}; //stingray::namespace ot_rg

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //#if _MSC_VER >= 1200

#endif //__RG_CHNG_H__
