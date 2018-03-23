///////////////////////////////////////////////////////////////////////////////
// rgsubstate.h
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

#ifndef __RG_SUB_STATE_H__
#define __RG_SUB_STATE_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "rgbase.h"
#include "rgchange.h"
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

namespace stingray_ot_rg	{

// Exception declaration

struct SubStateErrors
{
	enum eTypeRgSubStateError
	{
		eInvalidExpr,
	};
};

typedef CRgDefProvideDetail<SubStateErrors::eTypeRgSubStateError>	_CSubStateProvideDetail;

class CSubStateProvideDetail : public _CSubStateProvideDetail
{
public:
	inline CSubStateProvideDetail(){
		this->AddDetail(SubStateErrors::eInvalidExpr, _T("Regular expression is invalid"));
	}
};

typedef CRgDefException<SubStateErrors::eTypeRgSubStateError>	CRgSubStateException;



//@doc CRgSubState 
//@class 
//Class that defines the component parts of a state.
//Each state in the scanner is composed of several
//sub states. Each sub state is nothing but a regular expression
//with some additional state information. 
//
//You can add any number of sub states within each state.
//Each of these sub states will be OR'd (combined) with 
//the others to create a composite expression for that state. 
//Inherits from CRgChange for dirty state management
// 
//Operations on this class may cause a CRgSubStateException
//exception to be thrown. This class derives from exception.
//@base public | CRgChange
class CRgSubState :		public CRgChange, 
						public IClean,
						public IValid
{

public:
	rg_class()

/* SPECIAL CONST FLAGS*/	
	
	//@cmember,menum
	/* Standard state/token flags*/
	enum
	{
		//@@emem
		/*	This is a special state that denotes that no state
			change should take place if this sub expression is
			matched when processing
		*/
		stateContinue = -1,
	
		//@@emem
		/*	
			This value indicates that there
			is no state after this. This will have the effect
			of cutting short the traversal.
		*/
		stateNoNext = -2,

		//@@emem
		/*
		This token indicates that there is no feedback token
		even if a match takes place. This token value is often used for
		matches that are points on the path to the actual match.
		These matches have to occur for the final match to take place
		but they do not generate any tokens as such.
		*/
		tokenNone = -1,
	};
	
	
/* END SPECIAL CONST FLAGS*/	

	// constructor
	//@access Creation/Initialization

	//@cmember
	/* Constructs a CRgSubState object. Usually created with the rg_sub_state macro.*/
	TOOLKIT_API CRgSubState(RGTOKENID tokenid, LPCTSTR lpszExpression, RGSTATEID stateid = -1);
	
// destructor
	TOOLKIT_API virtual ~CRgSubState();

// accessors
	TOOLKIT_API bool ShouldChangeState() const;
	TOOLKIT_API bool ShouldBreak() const;
	TOOLKIT_API bool IsTokenNull() const;

	TOOLKIT_API RGSTATEID	GetNextState() const;
	TOOLKIT_API LPCTSTR GetExpression() const;
	TOOLKIT_API RGTOKENID	GetTokenId() const;

// modifiers
	
	TOOLKIT_API void SetNextState(RGSTATEID stateId);
	TOOLKIT_API void SetExpression(LPCTSTR pszExpression);
	TOOLKIT_API void SetTokenId(RGTOKENID tokenId);

// operations
	
	// overrides
	
	// IValid
	TOOLKIT_API bool IsValid() const;
	
	// IClean
	TOOLKIT_API virtual void Cleanup();
	TOOLKIT_API virtual void Destroy();

protected:
// data
	
	// the token that corresponds to this match
	RGTOKENID	m_tokenId; 
	
	// the next state ID to be used
	RGSTATEID	m_nextId; 
	
	// the expression in use
	CRgString m_strExpression; 

// implementation
	
	TOOLKIT_API void _Init(RGTOKENID tokenid, LPCTSTR lpszExpression, RGSTATEID stateid);
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

#endif //__RG_SUB_STATE_H__
