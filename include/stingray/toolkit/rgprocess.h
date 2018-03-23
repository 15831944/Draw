///////////////////////////////////////////////////////////////////////////////
// rgprocess.h
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

#ifndef __RG_PROCESS_H__
#define __RG_PROCESS_H__

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
#include "rgstate.h"
#include "rglisten.h"
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


struct ProcessErrors
{
	enum eTypeRgProcessError
	{
		eNoOp,
		eInvalidState,
		eInvalidStartState,
		eNotSavedPos,
	};
};

typedef CRgDefProvideDetail<ProcessErrors::eTypeRgProcessError>	_CProcessProvideDetail;

class CProcessProvideDetail : public _CProcessProvideDetail
{
public:
	inline CProcessProvideDetail(){
		this->AddDetail(ProcessErrors::eNoOp, _T("No op"));
		this->AddDetail(ProcessErrors::eInvalidState, _T("State is invalid"));
		this->AddDetail(ProcessErrors::eInvalidStartState, _T("Start State is invalid"));
		this->AddDetail(ProcessErrors::eNotSavedPos, _T("This is not a saved position"));
	}
};

typedef CRgDefException<ProcessErrors::eTypeRgProcessError>	CRgProcessException;


// flags the control some behavior of CRgProcessor
enum eTypeRgProcessFlags
{
	eCleanStates = 1,
	eDestStates = eCleanStates << 1,
	eCleanListen = eDestStates << 1,
	eDestListen = eCleanListen << 1,
};


//@doc CRgProcessor 
//@class 
//Class that contains the scan states. This class
//also drives the compilation and the scanning
//of tokens.
//Operations on this class may cause a CRgProcessException
//exception to be thrown. This class derives from exception.
//@base public | CRgChange
class CRgProcessor :	private CRgChange, 
						public IValid, 
						public IClean, 
						public CRgAttribute_T<eTypeRgProcessFlags>
{
// debugging information
	rg_class();

public:
	struct PosHolder
	{
		inline PosHolder(){
			bValid = false;
		}

		inline void SetActivePos(CRgString::const_iterator _citpos){
			citpos = _citpos;
			bValid =  true;
		}

		inline bool CanUseActivePos() const{
			return bValid;
		}
		
		inline CRgString::const_iterator UseActivePos()
		{
			if(bValid == false)
				rg_throw(CRgProcessException, ProcessErrors::eNotSavedPos);

			bValid = false;
			return citpos;
		}

		bool bValid;
		CRgString::const_iterator citpos;
	};

/* USEFUL TYPEDEFS */

	typedef std::list<CRgDefListener*>	CRgListenList;
	typedef std::map<CRgString, CRgString::const_iterator>	CRgSavePosMap;

/* END USEFUL TYPEDEFS */

// constructor
	// constructor
	//@access Creation/Initialization

	//@cmember
	/*Constructs a CRgProcessor object*/
	TOOLKIT_API CRgProcessor(CRgState* pState = NULL);

// destructor
	virtual ~CRgProcessor();

// accessors
	TOOLKIT_API const CRgState* GetState(RGSTATEID id) const;

	TOOLKIT_API CRgState* GetStateRef(RGSTATEID id);

// state
	TOOLKIT_API bool IsValid()	const;

// modifiers
	TOOLKIT_API void AddState(CRgState* pState);
	TOOLKIT_API void SetStartState(CRgState* pState);

	// constructor
	//@access public

	//@cmember
	/*Call this function to add a <c CRgDefListener> derived listener class that will
	receive notifications about the scan process.*/
	TOOLKIT_API bool AddListener(CRgDefListener* pListener);
	//@cmember
	/*Call this function to remove a previously added <c CRgDefListener> derived listener class*/
	TOOLKIT_API bool RemoveListener(CRgDefListener* pListener);
	//@cmember
	/*Call this function to remove all previously added <c CRgDefListener> derived listener classes*/
	TOOLKIT_API bool RemoveAllListeners();

//operations
	
	// compilation
	//@cmember
	/*Calling this function performs a simple compilation step that speeds up operations
	when scanning for tokens. This is a required call before <mf CRgProcessor::ProcessData>
	can be called.*/
	TOOLKIT_API virtual bool Compile();

	
	//@cmember
	/*Call this function to process the supplied data (strData) and extract the tokens specified
	previously*/
	TOOLKIT_API virtual bool ProcessData(const CRgString& strData);

	// operations to deal with saved positions
	//@cmember
	//Save any position that you can return to later
	TOOLKIT_API void SavePos(LPCTSTR pszStateName, CRgString::const_iterator citpos);
	//@cmember
	//Remove a previously saved position
	TOOLKIT_API void RemovePos(LPCTSTR pszStateName);
	//@cmember
	//Remove all previously saved positions
	TOOLKIT_API void RemoveAllPos();
	//@cmember
	//Sets the active position to be the position
	//saved under strPosName
	//This will be where the next scan starts.
	TOOLKIT_API void SetActivePosName(LPCTSTR pszPosName);
	//@cmember
	//Sets the active position to be the specified one.
	//This will be where the next scan starts.
	TOOLKIT_API void SetActivePos(CRgString::const_iterator citpos);
	
	TOOLKIT_API bool CanUseActivePos() const;
	TOOLKIT_API CRgString::const_iterator UseActivePos();

// must override
	//@cmember	
	//You must override this function and add in all the states/substates that
	//this processor is responsible for. Use macros such as rg_start_processor
	//to add the states and the substate. Please refer to the deals sample for 
	//information on how this is usually done.
	virtual void Initialize() = 0;

// IClean implementation
	TOOLKIT_API 	virtual void Cleanup();

	TOOLKIT_API 	virtual void Destroy();

protected:
	TOOLKIT_API virtual void OnMatch(RGTOKENID tokenid, CRgString::const_iterator citbegin, CRgString::const_iterator citend,
		DWORD dwOffset, const CRgMatch& actualMatch);

	TOOLKIT_API virtual void OnMatchStart();
	TOOLKIT_API virtual void OnMatchEnd();

	TOOLKIT_API virtual void OnChangeState(const CRgState* pOldState, const CRgState* pNewState,
		CRgString::const_iterator citbegin, CRgString::const_iterator citend);
	
// protected access	
	TOOLKIT_API const CRgStateMap& GetStateMap() const;
	TOOLKIT_API CRgStateMap& GetStateMapRef();

	TOOLKIT_API const CRgState* GetStartState() const;
	TOOLKIT_API CRgState* GetStartStateRef();
	
	TOOLKIT_API const CRgListenList& GetListenerList()	const;
	TOOLKIT_API CRgListenList& GetListenerListRef();

	TOOLKIT_API const CRgSavePosMap& GetSaveMap()	const;
	TOOLKIT_API CRgSavePosMap& GetSaveMapRef();


// data
	// state map
	CRgStateMap	m_stateMap;

	// data
	CRgState* m_pStartState;

	// listeners
	CRgListenList	m_listenList;

	// saved positions
	CRgSavePosMap	m_saveMap;

	// the saved position that is to be used
	PosHolder	m_posToUse;
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

#endif //__RG_PROCESS_H__
