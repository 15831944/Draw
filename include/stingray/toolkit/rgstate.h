///////////////////////////////////////////////////////////////////////////////
// rgstate.h
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

#ifndef __RG_STATE_H__
#define __RG_STATE_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "rgbase.h"
#include "rgchange.h"
#include "rgattr.h"
#include "rgsubstate.h"
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

namespace stingray_ot_rg
{

// Exception declaration

struct StateErrors
{
	enum eTypeRgStateError
	{
		eInvalidState,
		eInvalidSubState,
		eCompileFailed,
		eDirty,
	};
};


typedef CRgDefProvideDetail<StateErrors::eTypeRgStateError>	_CStateProvideDetail;

class CStateProvideDetail : public _CStateProvideDetail
{
public:
	inline CStateProvideDetail(){
		this->AddDetail(StateErrors::eInvalidState, _T("State is invalid"));
		this->AddDetail(StateErrors::eInvalidSubState, _T("Sub State is invalid."));
		this->AddDetail(StateErrors::eCompileFailed, _T("Compilation of expressions failed"));
		this->AddDetail(StateErrors::eDirty, _T("State is dirty. Compile first..."));
	}
};

typedef CRgDefException<StateErrors::eTypeRgStateError>	CRgStateException;

// This class holds all the state information that is required by the parser
// This class holds a list of compiled subexpressions.

enum eTypeRgStateFlags
{
	eCleanSubStates = 1,
	eDestSubStates = eCleanSubStates << 1,
};


//@doc CRgState 
//@class 
//Each state holds one or more substates (these are
//basically regular expressions). Each state also holds
//information on the identifier that it is associated with.
//
//Inherits from CRgChange for dirty state management
//
//Operations on this class may cause a CRgStateException
//exception to be thrown. This class derives from exception.
//@base public | CRgChange
class CRgState :	public CRgChange,
					public IValid, 
					public IClean,
					public CRgAttribute_T<eTypeRgStateFlags>

{
	rg_class()

public:
	// Nested struct: State of compilation
	struct CompileState
	{
		friend class CRgState;

		// constructors	
		inline CompileState(){
			m_pSubState = NULL;
			m_dwValue = 0;
		}

		inline CompileState(const CRgSubState* pSubState, DWORD dwValue){
			m_pSubState = pSubState;
			m_dwValue = dwValue;
		}

		inline CompileState(const CompileState& cs){
			m_pSubState = cs.m_pSubState;
			m_dwValue = cs.m_dwValue;
		}
		
		// destructor
		inline ~CompileState() {  // Intentional non-virtual???
			// no implementation
		}

		// operations / operators
		
		inline bool operator == (const CompileState& cs){
			return (m_pSubState == cs.m_pSubState) && (m_dwValue == cs.m_dwValue);
		}
		
		// data
	protected:
		const CRgSubState* m_pSubState;
		DWORD m_dwValue;	
	};

/* 
	TYPEDEFS
*/	
	// map that holds the compiled slots
	typedef std::map<DWORD, CompileState*>	CRgCompileMap; 


// constructor/destructor
	// constructor
	//@access Creation/Initialization

	//@cmember
	/*Constructs a CRgState object.*/
	TOOLKIT_API CRgState(RGSTATEID stateID, match_flags f = match_default);

	TOOLKIT_API virtual ~CRgState();

// accessors
	TOOLKIT_API RGSTATEID GetStateID() const;
	
	TOOLKIT_API const CRgSubStateList& GetSubStateList() const;
	
	TOOLKIT_API CRgSubStateList& GetSubStateListRef();
	
	TOOLKIT_API match_flags GetMatchFlags() const;
		
// modifiers
	TOOLKIT_API void AddSubState(CRgSubState* pSubState);
	TOOLKIT_API void SetMatchFlags(match_flags m);

// operations
	TOOLKIT_API virtual bool Compile();
	
	TOOLKIT_API const CRgSubState* Match(CRgString::const_iterator it, CRgString::const_iterator ite, CRgString::const_iterator& citbegin,
			CRgString::const_iterator& citend, DWORD& dwOffset, CRgMatch& match) const;

	TOOLKIT_API virtual const CRgSubState* GetMatchedSubExpression(const CRgMatch* pMatch, DWORD& dwIndex, DWORD& dwOffset) const;

// overrides	
	// IClean
		TOOLKIT_API virtual void Cleanup();
		TOOLKIT_API virtual void Destroy();

	// IValid
		TOOLKIT_API virtual bool IsValid() const;

protected:
	
	TOOLKIT_API CRgCompileMap& GetCompileMapRef();
	
	TOOLKIT_API const CRgCompileMap& GetCompileMap() const;
	
	TOOLKIT_API CRgString& GetCompiledExpressionRef();

	TOOLKIT_API const CRgString& GetCompiledExpression() const;

	TOOLKIT_API void CleanCompileState();

	// compile map
	CRgCompileMap	m_compileMap;
	
	// state expression
	CRgString		m_strExpression;

	// list of sub states
	CRgSubStateList	m_substateList;

	// the ID of this state
	RGSTATEID m_stateID;

	// match flags to be used
	match_flags m_matchFlags;
};

// useful typedefs

// map that holds all possible states
typedef std::map<RGSTATEID, CRgState*>	CRgStateMap; 

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

#endif //__RG_STATE_H__
