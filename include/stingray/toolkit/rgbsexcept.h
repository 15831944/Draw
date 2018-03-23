///////////////////////////////////////////////////////////////////////////////
// rgbsexcept.h
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

#ifndef __BASE_EXCEPT_H__
#define __BASE_EXCEPT_H__

#if _MSC_VER >= 1200

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include <foundation\stwarn.h>

#include <map>
#include <string>
#include <foundation\stwarnp.h>
//#include <include\exception.h>
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

namespace stingray_ot_rg
{

template<typename e>
class IRgProvideDetail
{	
public:
	virtual bool ProvideDetail(e nReason, CRgString& strReason) const = 0;
};

template<typename eType>
class CRgDefProvideDetail : public IRgProvideDetail<eType>
{	
protected:
	CRgDefProvideDetail(){
		// no implementation		
	}

public:
	typedef std::map<eType, CRgString>	CMapReasons;

	virtual bool ProvideDetail(eType nReason, CRgString& strReason) const{
		
		CMapReasons::const_iterator cit;
		cit = m_reasonsMap.find(nReason);
		if(cit == m_reasonsMap.end())
			return false;
		else
			strReason = (*cit).second;
		
		return true;
	};

// modifiers
	void AddDetail(eType nReason, LPCTSTR lpszReason){
		m_reasonsMap[nReason] = lpszReason;
	}

	bool RemoveDetail(eType eReason)
	{
		CMapReasons::iterator it;
		it = m_reasonsMap.find(eReason);
		if(it == m_reasonsMap.end())
			return false;
		else
			m_reasonsMap.erase(it);
	
		return true;
	}

protected:
	CMapReasons		m_reasonsMap;

};

// common characteristics
class CBaseException : public std::exception //
{
public:
	virtual LPCTSTR GetLineInfo() const = 0;
	virtual LPCTSTR GetFileInfo() const = 0;
	virtual DWORD GetErrorCode() const = 0;
	virtual CRgString GetFormattedMessage() const = 0;
	virtual DWORD GetCustErrorCodeDW() const = 0;
};

template<typename e>
class TOOLKIT_API CRgDefException : public CBaseException
{
public:
	typedef e	error_type;
	typedef std::map<error_type, CRgString>	CReasonMap;
	typedef IRgProvideDetail<error_type>	IErrorProvider;

	CRgDefException(error_type err, 
		LPCTSTR pszFileInfo = _T("Unspecified"),
		int nLineInfo = -1, LPCTSTR lpszModule = _T("System/Unknown")){
		
		m_dwOpCode = ::GetLastError();
		m_strOpError = _T("Unknown");

		m_eError = err;
		m_strFileInfo = pszFileInfo;
		
		TCHAR pszLine[255];
		// QA: 31989 - #if Secure Code Cleanup.
		_itot(nLineInfo, pszLine, 10);
		
		m_strLineInfo = pszLine;
		m_strModuleName = lpszModule;
		
		if(m_dwOpCode != 0)
		{
			LPVOID lpMsgBuf;
			DWORD dwRet = ::FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_HMODULE,
			(lpszModule == NULL)?NULL:(LPCVOID)::GetModuleHandle(lpszModule),
			m_dwOpCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL );
		
			if(dwRet)
			{
				m_strOpError = (LPCTSTR)lpMsgBuf; 
				::LocalFree(lpMsgBuf);
			
#ifdef _UNICODE
				{
					USES_CONVERSION;
					m_strOpError_ = W2A(m_strOpError.c_str());
				}
#endif //_UNICODE
			}
		}
	}
	
// accessors
	LPCTSTR GetLineInfo() const{
		return m_strLineInfo.c_str();
	}

	LPCTSTR GetFileInfo() const{
		return m_strFileInfo.c_str();
	}

	DWORD GetErrorCode() const{
		return m_dwOpCode;
	}

	error_type GetCustErrorCode() const{
		return m_eError;
	}

	virtual DWORD GetCustErrorCodeDW() const{
		return (DWORD) GetCustErrorCode();
	}

// exception overrides
	virtual const char* what() const
	{
		if(m_pDetail == NULL)
			return exception::what();
		else
#ifdef _UNICODE
			return m_strOpError_.c_str();
#else
			return m_strOpError.c_str();
#endif //_UNICODE
	}
//

	CRgString GetFormattedMessage() const
	{ const DWORD BUFSIZE(1024);
		
		TCHAR	pszBuffer[BUFSIZE];
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(pszBuffer, _T("INFO: Exception details: Module %s, ")
		_T("Error Description: %s, Error code: %x\n"), m_strModuleName.c_str(), m_strOpError.c_str(), m_dwOpCode);
		
		CRgString retstr = pszBuffer;
		
		retstr+= _T("File name: ");
		retstr+= m_strFileInfo;
		retstr+= _T(" Line no: ");
		retstr+= m_strLineInfo;
		retstr+= _T('\n');

		return retstr;
	}

protected:
	static IRgProvideDetail<error_type>* m_pDetail;
	
	// the filename (source that caused the error)
	CRgString	m_strFileInfo;
	// the source line
	CRgString	m_strLineInfo;
	// the name of the module to be used with FormatMessage
	CRgString m_strModuleName;

	// the error enum value
	error_type	m_eError;
	
	// the formatted error message as returned by FormatMessage
	CRgString	m_strOpError;
#ifdef _UNICODE
	std::string	m_strOpError_;
#endif //_UNICODE
	
	// the actual error returned by a system call that failed
	// this may or may not be available.
	DWORD m_dwOpCode;
};

} //stingray::namespace ot_rg

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //#if _MSC_VER >= 1200

#endif //__BASE_EXCEPT_H__