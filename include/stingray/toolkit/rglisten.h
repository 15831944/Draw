///////////////////////////////////////////////////////////////////////////////
// rglisten.h
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

#ifndef __RG_LISTEN_H__
#define __RG_LISTEN_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "rgbase.h"
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

namespace stingray_ot_rg {

// Forward declarations
class CRgProcessor;

//@doc CRgDefListener 
//@class | This class is added to <c CRgProcessor> class' internal
//list of listeners using the <mf CRgProcessor::AddListener>
//function. Listeners will be notified when a match takes place.
//You will have to derive from this class to listen to the events.
//Usually you will only override OnMatch. Please refer to the deals
//sample for typical usage.
//@xref <c CRgProcessor>
//@base public | CRgChange
struct CRgDefListener : public IClean
{
	//@cmember
	//This method will be called when the processor starts the token scanning process.
	inline virtual void OnMatchStart(){
		// no implementation
	}
	
	//@cmember
	//This method will be called when the processor finds a match.
	//Please refer to the deals sample for typical usage.
	inline virtual void OnMatch(RGTOKENID /*tokenid*/, 
		CRgString::const_iterator /*citbegin*/, 
		CRgString::const_iterator /*citend*/,
		DWORD /*dwOffset*/, 
		const CRgMatch& /*actualMatch*/, 
		CRgProcessor* /*pProcess*/)
	{
		// no implementation
	}

	//@cmember
	//This method will be called when the scanning process ends.
	inline virtual void OnMatchEnd(){
		// no implementation
	}

	//@cmember
	//This method will be called when the state used for scanning changes as a result
	//of a match
	inline virtual void OnChangeState(const CRgState* /*pOldState*/, 
		const CRgState* /*pNewState*/,
		CRgString::const_iterator /*citbegin*/, 
		CRgString::const_iterator /*citend*/, 
		CRgProcessor* /*pProcess*/)
	{
		// no implementation
	}

	inline virtual void Cleanup(){
		// no implementation
	}

	inline virtual void Destroy(){
		delete this;
	}
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

#endif //__RG_LISTEN_H__
