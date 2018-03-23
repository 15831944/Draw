///////////////////////////////////////////////////////////////////////////////
// OtlIContextMenuImpl.h
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

#ifndef __OTLCONTEXTMENU_H__
#define __OTLCONTEXTMENU_H__

#ifndef __OTLBASE_H__
	#error otlicontextmenuimpl.h requires otlbase.h to be included first
#endif

#include <shlobj.h>
#if _ATL_VER < 0x0300
	#include <foundation\stwarn.h>
	#include <vector>
	#include <foundation\stwarnp.h>
#else
	#include <Toolkit\atl\otlcollection.h>
#endif

#include <atlconv.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{

struct OtlContextMenuItem
{
	TCHAR strName[80];
	TCHAR strHelp[80];
	UINT nCommandID;
};

#define OTL_STRLEN(x) sizeof(x)*sizeof(TCHAR)

// macros for building a context menu
#define OTL_BEGIN_COMMAND_MAP() void OtlLoadCommands() {
// add a command using string resource id's
#define OTL_COMMAND_ID(nameID, helpID) AddCommand(nameID, helpID);
// add a command using string constants, and specifying the command ID
#define OTL_COMMAND(strName, strHelp, nCommandID) AddCommand(strName, strHelp, nCommandID);
#define OTL_END_COMMAND_MAP() };

/////////////////////////////////////////////////////////////////////////////
// OtlIContextMenuImpl<T>
//
template <class T>
class ATL_NO_VTABLE OtlIContextMenuImpl : public IContextMenu
{
public:
#if _ATL_VER < 0x0300	// use a vector
	typedef std::vector<OtlContextMenuItem*> CommandSet;
#else					// use a CSimpleArray derivative
	typedef COtlSimpleVector<OtlContextMenuItem*> CommandSet;
#endif

	CommandSet m_commands;

	virtual ~OtlIContextMenuImpl()
	{
		RemoveAllCommands();
	}


public:

	// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(OtlIContextMenuImpl)

	// IContextMenu
	inline STDMETHOD(QueryContextMenu)(HMENU hMenu,
                                          UINT indexMenu,
                                          UINT idCmdFirst,
                                          UINT idCmdLast,
                                          UINT uFlags)
	{
		if(!(CMF_DEFAULTONLY & uFlags))
		{
			RemoveAllCommands();
			static_cast<T*>(this)->OtlLoadCommands();
			// insert in reverse order, to keep the same as array entries
			for (int i = m_commands.size()-1; i >= 0; i--)
			{
				if(m_commands[i])
				{
					::InsertMenu( hMenu, 
							   indexMenu, 
							   MF_STRING | MF_BYPOSITION, 
							   idCmdFirst + i, 
							   m_commands[i]->strName);
				}

			}
			return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(m_commands.size()));
		}

		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
	}

	inline STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpcmi)
	{
		if(HIWORD(lpcmi->lpVerb) == 0 )
		{
			int nCmd = LOWORD(lpcmi->lpVerb);
			if(FireCommand(nCmd))
				return NOERROR;
		}

		return E_INVALIDARG;
	}	

	inline STDMETHOD(GetCommandString)( SEC_UINT idCommand,
											  UINT uFlags,
											  LPUINT lpReserved,
											  LPSTR lpszName,
											  UINT uMaxNameLen)
	{
		USES_CONVERSION;
		HRESULT  hr = E_INVALIDARG;

		switch(uFlags)
		   {
		   case GCS_HELPTEXT:
		   		if(idCommand >=0 && idCommand < m_commands.size() && m_commands[(int)idCommand])
				{
					strcpy(lpszName, T2A(m_commands[(int)idCommand]->strHelp));
					hr = NOERROR;
					break;
				}
			  break;
   
		   case GCS_VERB:
				strcpy(lpszName, "command");
				hr = NOERROR;
				break;
   
		   case GCS_VALIDATE:
			  hr = NOERROR;
			  break;
		   }

		return hr;
	}

public:
	virtual HRESULT AddCommand(UINT nIDName, UINT nIDHelpString)
	{
		OtlContextMenuItem* pCommand = new OtlContextMenuItem;
		if(pCommand)
		{
#if (_ATL_VER < 0x0700)
			if(!::LoadString(_Module.GetResourceInstance(),	nIDName, 
									pCommand->strName,
									OTL_STRLEN(pCommand->strName)))
#else
			if(!::LoadString(_AtlBaseModule.GetResourceInstance(),	nIDName, 
									pCommand->strName,
									OTL_STRLEN(pCommand->strName)))
#endif
			{
				delete pCommand;
				return E_FAIL;
			}
			

#if (_ATL_VER < 0x0700)
			if(!::LoadString(_Module.GetResourceInstance(),	nIDHelpString, 
									pCommand->strHelp,
									OTL_STRLEN(pCommand->strHelp)))
#else
			if(!::LoadString(_AtlBaseModule.GetResourceInstance(),	nIDHelpString, 
									pCommand->strHelp,
									OTL_STRLEN(pCommand->strHelp)))
#endif
			{
				_tcscpy(pCommand->strHelp, _T(""));
			}
			pCommand->nCommandID = nIDName;	// command handler sent with this ID
			m_commands.push_back(pCommand);
			return S_OK;
		}
		return E_FAIL;
	}

	virtual HRESULT AddCommand(LPCTSTR strName, LPCTSTR strHelp, UINT nCommandID)
	{
		OtlContextMenuItem* pCommand = new OtlContextMenuItem;
		if(pCommand)
		{
			OTLASSERT(strName);
			OTLASSERT(strHelp);
			_tcscpy(pCommand->strName, strName);
			_tcscpy(pCommand->strHelp, strHelp);
			pCommand->nCommandID = nCommandID;	// command handler sent with this ID
			m_commands.push_back(pCommand);
			return S_OK;
		}
		return E_FAIL;
	}

	virtual void RemoveAllCommands()
	{
		for (UINT i = 0; i < m_commands.size(); i++)
		{
			if(m_commands[i])
				delete m_commands[i];
		}
		m_commands.erase(m_commands.begin(),m_commands.end() );
	}


	virtual BOOL FireCommand(UINT uCommand)
	{
		// override to handle the context menu command.
		// uCommand is an index into the array of OtlContextMenuItem structs
		if(uCommand >=0 && uCommand < m_commands.size() && m_commands[uCommand])
		{
		   OtlContextMenuItem* pItem = m_commands[uCommand];
		   pItem; // do nothing
		   return TRUE;
		}
		return FALSE;
	}
};


/////////////////////////////////////////////////////////////////////////////
// OtlIContextMenuWndImpl<T>

template <class T>
class ATL_NO_VTABLE OtlIContextMenuMsgImpl : public OtlIContextMenuImpl<T>
{
public:
	virtual BOOL FireCommand( UINT uCommand )
	{
		// convert a command to a WM_COMMAND message
		if(uCommand >=0 && uCommand < m_commands.size() && m_commands[uCommand])
		{
		   ::PostMessage(static_cast<T*>(this)->m_hWnd, 
			   WM_COMMAND, 
			   MAKEWPARAM(0, m_commands[uCommand]->nCommandID),
			   0);
		   return TRUE;
		}
		return FALSE;
	}

};

}; // namespace StingrayOTL 

#endif // __OTLCONTEXTMENU_H__
