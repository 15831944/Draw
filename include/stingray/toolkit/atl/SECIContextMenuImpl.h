///////////////////////////////////////////////////////////////////////////////
// SECIContextMenuImpl.h
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

#if !defined(AFX_SECICONTEXTMENUIMPL_H__2C8C408F_20BA_4A05_B736_8238D2CC0D13__INCLUDED_)
#define AFX_SECICONTEXTMENUIMPL_H__2C8C408F_20BA_4A05_B736_8238D2CC0D13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <foundation\stwarn.h>
#include <vector>
#include <foundation\stwarnp.h>
using namespace std;

#define SEC_CMDSTR_LEN 80

struct SECContextMenuItem
{
	TCHAR strName[SEC_CMDSTR_LEN];
	TCHAR strHelp[SEC_CMDSTR_LEN];
	UINT nCommandID;
};

#define SEC_BEGIN_COMMAND_MAP() void SEC_LoadCommands() {

#define SEC_COMMAND_ID(nameID, helpID) AddCommand(nameID, helpID);

#define SEC_COMMAND(strName, strHelp, nCommandID) AddCommand(strName, strHelp, nCommandID);

#define SEC_END_COMMAND_MAP() };

/////////////////////////////
// AutoDuck tag block block for SECIContextMenuImpl 

//@doc SECIContextMenuImpl
//@mdata HWND      | SECIContextMenuImpl | m_hwndOwner | A window handle to the owner of this interface.

//@doc SECIContextMenuImpl
//@mdata LPITEMIDLIST    | SECIContextMenuImpl | m_pPidl | A copy of the PIDL the instance of this class is attached to.

//@doc SECIContextMenuImpl
//@mdata TPidlMgr*     | SECIContextMenuImpl | m_pPidlMgr | A PIDL manager to help manage the PIDL.

//@doc SECIContextMenuImpl
//@mdata vector lt; SECContextMenuItem* gt;  | SECIContextMenuImpl | m_commands | A vector that stores pointers to SECContextMenuItem structure.

//@doc SECIContextMenuImpl
//@mfunc | SECIContextMenuImpl | SECIContextMenuImpl | Contructor. It creates a valid instance of PIDL manager class indicated in our template arguments. 
//Application can always assume the PIDL manager is valid.
//It also sets reference count to one and increases the lock count of _Module by one. In addition, the contructor
//will make a copy of the given PIDL and store the given owner window handle for later use. If application need 
//to access the IShellFolder in the namespace development, then application should derive from this class.
//@parm HWND | hwndOwner | A handle to the owner window. During the menu command handling, applicaion should use
//this handle to popup message box or dialog box.
//@parm  LPCITEMIDLIST | pidl | The PIDL the instance of this class is attached to.

//@doc SECIContextMenuImpl
//@mfunc HRESULT | SECIContextMenuImpl | AddCommand | This method adds a context menu command to the list of commands that will be added to the context menu. 
//Commands can either be added from resources or literal strings. As an alternative, you can use the Command 
//Map Macros, which call this method internally.
//@rdesc HRESULT Return S_OK if all the command are successfully loaded, otherwise return E_FAIL.
//@parm UINT | nIDName | The resource ID of the string to be used as context menu text.
//@parm  UINT | nIDHelpString | The resource ID of the string to be used as the help string for this context menu item.

//@doc SECIContextMenuImpl
//@mfunc HRESULT | SECIContextMenuImpl | AddCommand | This method adds a context menu command to the list of commands that will be added to the context menu. 
//Commands can either be added from resources or literal strings. As an alternative, you can use the Command 
//Map Macros, which call this method internally.
//@rdesc HRESULT Return S_OK if all the command are successfully loaded, otherwise return E_FAIL.
//@parm LPCTSTR | strName | The string to be used as context menu text.
//@parm  LPCTSTR | strHelp | The string to be used as help string for this context menu item
//@parm  UINT | nCommandID | The Command ID to identify this context menu item. You can check the nID argument of
//CommandHandler method to look for this command ID.

//@doc SECIContextMenuImpl
//@mfunc void | SECIContextMenuImpl | RemoveAllCommands | Removes all commands form the internal command map.
//@rdesc void 

//@doc SECIContextMenuImpl
//@mfunc void | SECIContextMenuImpl | CommandHandler | This function handle all the command for this context menu object. Derived class should override
//this function to do special handling depending one the given command ID. Default implementation just
//popup a message box telling you the context menu ID you just clicked.
//@rdesc void 
//@parm HWND | hwndOwner | The window handle to the window that own this object. It should be used when
//you need to popup message box or dialog box.
//@parm  UINT | nID | The ID for the selected context menu item.

// adinsert AutoDuck insertion point for SECIContextMenuImpl 
//@doc SECIContextMenuImpl 
//@class This class is a thin wrapper class of IContextMenu interface. It only implemented the
//methods in the IUnknown interface and the reference counting logic. It can only be used in 
//an ATL base project. Since its reference counting makes use of the lock count in CComModule
//class of ATL, i.e. a global CComModule instanace _Module. This class must be derived before 
//it can be used. The derived class should contain command map no matter there is any command 
//inside or not as shown in Example One.
//To use this class, you just add the proper menu item into the command map in your derived
//class using the provided marcos. You then override the CommandHandler virtual function is
//your derived class as shown in the Example Two.
//This template class requires two template arguments. The first one is
//your derived class and the second one is an PIDL
//management class derived from SECPidlMgr<T> template class. This implementation is majorly 
//targeted for namespace or shell extension. The constructor need two arguments, a window handle 
//and a PIDL. The window handle is usually the owner window of this interface. The constructor will 
//save the window handle and make a copy of the PIDL.
//For a complete documentation of IContextMenu interface, please refer to windows SDK or MSDN from Microsoft.
//
//@ex |
//  One:
//	class CMyContextMenu : public SECIContextMenuImpl<CMyContextMenu, SECPidlManager> 
//	{ 
//      CMyContextMenu(HWND hwndOwner, LPCITEMIDLIST pidl) 
//           : SECIContextMenuImpl<CMyContextMenu, SECPidlManager>(hwndOwner, pidl) 
//      {} 
//    SEC_BEGIN_COMMAND_MAP() 
//    SEC_END_COMMAND_MAP() 
//   }; 
//
//  Two: 
//	class CMyContextMenu : public SECIContextMenuImpl<CMyContextMenu, SECPidlManager> 
//	{ 
//  public:
//      CMyContextMenu(HWND hwndOwner, LPCITEMIDLIST pidl) 
//           : SECIContextMenuImpl<CMyContextMenu, SECPidlManager>(hwndOwner, pidl) 
//      {} 
//    #define ID_MYMENUITEM 101 
//    SEC_BEGIN_COMMAND_MAP() 
//       SEC_COMMAND(_T("Menu Text"), _T("Help string"), ID_MYMENUITEM) 
//    SEC_END_COMMAND_MAP() 
//    
//        virtual void CommandHandler(HWND hwndOwner, UINT nID) 
//        { 
//             if( nID == ID_MYMENUITEM) 
//                ::MessageBox(hwndOwner, _T("Message"), _T("Title"), MB_OK); 
//        } 
//   }; 
//@end
//@tcarg class | T | The derived class
//@tcarg class | TPidlMgr | SECPidlMgr derived class
//@base public | IContextMenu
template<typename T, typename TPidlMgr>
class SECIContextMenuImpl : public IContextMenu
{
protected:
	DWORD					m_nRefCount;
	//@cmember
	/* The window handle of the owener of this interface */
	HWND					m_hwndOwner;
	//@cmember
	/* PIDL of the current item */
	LPITEMIDLIST			m_pPidl;
	//@cmember
	/* A pointer to PIDL mananger */
	TPidlMgr*				m_pPidlMgr;
	//@cmember
	/* A vector to store the context menu items */
	vector<SECContextMenuItem*>	m_commands;

public:

	//@cmember
	/* Constructor */
	inline SECIContextMenuImpl(HWND hwndOwner, LPCITEMIDLIST pidl)
	{
		m_pPidlMgr = new TPidlMgr;
		if( m_pPidlMgr == NULL )
		{
			delete this;
			return;
		}
		m_pPidl = m_pPidlMgr->Copy(pidl);
		m_hwndOwner = hwndOwner;

		m_nRefCount = 1;

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt++;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt++;
		_pAtlModule->Unlock();
#endif
	}
	virtual ~SECIContextMenuImpl()
	{
		if( m_pPidl != NULL )
			m_pPidlMgr->Delete(m_pPidl);
		if( m_pPidlMgr != NULL )
			delete m_pPidlMgr;

		RemoveAllCommands();

#if (_ATL_VER < 0x0700)
		_Module.Lock();
		_Module.m_nLockCnt--;
		_Module.Unlock();
#else
		_pAtlModule->Lock();
		_pAtlModule->m_nLockCnt--;
		_pAtlModule->Unlock();
#endif
	}

	// IUnknown
	inline STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
	{
		*ppvObj = NULL;

		//IUnknown
		if(IsEqualIID(riid, IID_IUnknown))
			*ppvObj = this;
		else if(IsEqualIID(riid, IID_IContextMenu))
			*ppvObj = (IContextMenu*)this;

		if(*ppvObj)
		{
		   (*(LPUNKNOWN*)ppvObj)->AddRef();
		   return S_OK;
		}
		return E_NOINTERFACE;
	}

	inline STDMETHOD_ (DWORD, AddRef)()
	{
	   m_nRefCount++;

	   return m_nRefCount;
	}
	inline STDMETHOD_ (DWORD, Release)()
	{
	   m_nRefCount--;
	   if( 0 == m_nRefCount )
	   {
		   delete this;
		   return 0;
	   }
	   return m_nRefCount;
	}

	// IContextMenu
	inline STDMETHOD(QueryContextMenu)(HMENU hMenu,
                                UINT indexMenu,
                                UINT idCmdFirst,
                                UINT /*idCmdLast*/,
                                UINT uFlags)
	{
		if(!(CMF_DEFAULTONLY & uFlags))
		{
			RemoveAllCommands();

			static_cast<T*>(this)->SEC_LoadCommands();
			// insert in reverse order, to keep the same as array entries
			for (int i = (int)m_commands.size()-1; i >= 0; i--)
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

		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(idCmdFirst));
	}

	inline STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpcmi)
	{
		if(HIWORD(lpcmi->lpVerb) == 0 )
		{
			int nCmd = LOWORD(lpcmi->lpVerb);
			if(nCmd >=0 && (static_cast<unsigned int>(nCmd)) < m_commands.size() && m_commands[nCmd])
			{
				CommandHandler(lpcmi->hwnd, m_commands[nCmd]->nCommandID);
				return NOERROR;
			}
		}
		return E_INVALIDARG;
	}


	inline STDMETHOD(GetCommandString)( SEC_UINT idCommand,
								        UINT uFlags,
								        LPUINT /*lpReserved*/,
								        LPSTR lpszName,
								        UINT /*uMaxNameLen*/)
	{
		USES_CONVERSION;
		HRESULT  hr = E_INVALIDARG;

		switch(uFlags)
		   {
		   case GCS_HELPTEXT:
		   		if(idCommand >=0 && idCommand < m_commands.size() && m_commands[idCommand])
				{
					strcpy(lpszName, T2A(m_commands[idCommand]->strHelp));
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
	//@cmember
	/* Add one menu item */
	virtual HRESULT AddCommand(UINT nIDName, UINT nIDHelpString)
	{
		SECContextMenuItem* pCommand = new SECContextMenuItem;
		if(pCommand)
		{
#if (_ATL_VER < 0x0700)
			if(!::LoadString(_Module.GetResourceInstance(),	nIDName, 
									pCommand->strName,
									SEC_CMDSTR_LEN))
#else
			if(!::LoadString(_AtlBaseModule.GetResourceInstance(),	nIDName, 
									pCommand->strName,
									SEC_CMDSTR_LEN))
#endif
			{
				delete pCommand;
				return E_FAIL;
			}
			

#if (_ATL_VER < 0x0700)
			if(!::LoadString(_Module.GetResourceInstance(),	nIDHelpString, 
									pCommand->strHelp,
									SEC_CMDSTR_LEN))
#else
			if(!::LoadString(_AtlBaseModule.GetResourceInstance(),	nIDHelpString, 
									pCommand->strHelp,
									SEC_CMDSTR_LEN))
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

	//@cmember
	/* Add one menu item */
	virtual HRESULT AddCommand(LPCTSTR strName, LPCTSTR strHelp, UINT nCommandID)
	{
		SECContextMenuItem* pCommand = new SECContextMenuItem;
		if(pCommand)
		{
			_tcsncpy(pCommand->strName, strName, SEC_CMDSTR_LEN);
			_tcsncpy(pCommand->strHelp, strHelp, SEC_CMDSTR_LEN);
			pCommand->nCommandID = nCommandID;	// command handler sent with this ID
			m_commands.push_back(pCommand);
			return S_OK;
		}
		return E_FAIL;
	}

	//@cmember
	/* Remove all the menu items */
	virtual void RemoveAllCommands()
	{
		for (UINT i = 0; i < m_commands.size(); i++)
		{
			if(m_commands[i])
				delete m_commands[i];
		}
		m_commands.erase(m_commands.begin(),m_commands.end() );
	}

	//@cmember
	/* A menu command handler */
	virtual void CommandHandler(HWND hwndOwner, UINT nID)
	{
		TCHAR buf[200] = {0};
		_stprintf(buf, _T("You selected contextmenu with ID = %d"), nID);

		::MessageBox(hwndOwner, buf, _T("Information"), MB_OK | MB_ICONINFORMATION);
	}

};

#endif // !defined(AFX_SECICONTEXTMENUIMPL_H__2C8C408F_20BA_4A05_B736_8238D2CC0D13__INCLUDED_)
