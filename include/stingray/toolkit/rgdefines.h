///////////////////////////////////////////////////////////////////////////////
// rgdefines.h
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

#ifndef __RG_DEF_H__
#define __RG_DEF_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#pragma warning(disable: 4101)

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

// a few useful typedefs

// string class that we use
#ifndef _UNICODE
typedef std::string CRgString; 
#else
typedef std::wstring CRgString; 
#endif //!_UNICODE

// a few useful typedefs

// the ID associated with each state that the scanner can be in
typedef int RGSTATEID; 

// the ID associated with each token that will be sent along with the token data
typedef int RGTOKENID; 

// map that holds the expression data
typedef std::map<DWORD, CRgString> CRgExpMap; 

// list that holds all the sub states
// that pertain to a given state

class CRgSubState; //forward decl for CRgSubState

typedef std::list<CRgSubState*>	CRgSubStateList; 

#ifdef _UNICODE
typedef wregex ot_regex;
#else
typedef regex ot_regex;
#endif //_UNICODE

// used with Regex++
typedef reg_match< CRgString::const_iterator, ot_regex::alloc_type > CRgMatch; 

// generic Cleanup interface
struct IClean
{
	virtual void Cleanup() = 0;
	virtual void Destroy() = 0;
};

// generic interface that checks for validity
struct IValid
{
	virtual bool IsValid() const = 0;
};

// interface to manage dirty state flag
struct IChange
{
	virtual bool IsDirty() const = 0;
	virtual bool SetDirty(bool b) = 0;
};

} // namespace stingray_ot_rg


#define rg_class()\
	TCHAR* __cfname;

#define rg_class_name(name)\
	__cfname = _T(## #name##);

#define rg_fn(name)\
	static TCHAR* __fname = _T(## #name##);


#ifdef _DEBUG
#define rg_trace_fn()\
ATLTRACE(_T(##"RGLIB: %s::%s: "), __cfname, __fname);	
#else
#define rg_trace_fn()\
;
#endif



#define rg_catch(ex, code)\
	catch(ex##& rg)\
		{\
			code\
			ATLTRACE(_T(##"RGLIB: %s::%s...Exception: %s\n"), __cfname, __fname, rg.what());\
			ATLTRACE(_T(##"RGLIB More info: File %s, Line %s\n"), rg.GetFileInfo(), rg.GetLineInfo());\
			throw;\
		}


#define rg_basic_catch(code)\
	catch(std::exception& ex)\
		{\
			code\
			ATLTRACE(_T(##"RGLIB: %s::%s...Exception: %s\n"), __cfname, __fname, ex.what());\
			throw;\
		}\
		catch(...)\
		{\
			code\
			ATLTRACE(_T(##"RGLIB: %s::%s...Unknown exception\n"), __cfname, __fname);\
			throw;\
		}



#define rg_start_processor(val)\
{\
CRgProcessor* ____p = val;

#define rg_start_state(name, id)\
CRgState*	name = new CRgState(id);\
{\
	CRgState*	____state = name;

#define rg_end_state()\
____p->AddState(____state);\
}

#define rg_sub_state(token, expr, state)\
{\
CRgSubState* psubstate =  new CRgSubState(token, expr, state);\
____state->AddSubState(psubstate);\
}

#define rg_end_processor(val)\
	____p->SetStartState(val);\
}

#define rg_match(fl)\
	____state->SetMatchFlags(fl);



#define rg_start_token(tokenid)\
	switch (tokenid)\
		{

#define rg_end_token()\
		}


#define rg_assign_string(token, string, index)\
	case token:\
			{\
				CRgString strSubString;\
				strSubString.assign(actualMatch[dwOffset + index + 1].first, actualMatch[dwOffset + index + 1].second);\
				string = strSubString;\
				break;\
			}


#define rg_assign_code(token, code, index)\
	case token:\
			{\
				code\
				break;\
			}

#define rg_decl_assign(name, toassign, index)\
CRgString name;\
name.assign(actualMatch[dwOffset + index + 1].first, actualMatch[dwOffset + index + 1].second);\
toassign = name;


#define rg_nodecl_assign(name, index)\
name.assign(actualMatch[dwOffset + index + 1].first, actualMatch[dwOffset + index + 1].second);\


#ifdef _DEBUG
#define rg_throw(name, error)\
	throw name##(##error##, _T(##__FILE__##), __LINE__);
#else
#define rg_throw(name, error)\
	throw name##(##error##);
#endif //_DEBUG

#ifdef _DEBUG
#define rg_throw_mod(name, error, mod)\
	throw name##(##error##, _T(##__FILE__##), __LINE__, _T(##mod##),);
#else
#define rg_throw_mod(name, error, mod)\
	throw name##(##error##);
#endif //_DEBUG

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //#if _MSC_VER >= 1200

#endif //__RG_DEF_H__
