///////////////////////////////////////////////////////////////////////////////
// SCutAccl.h
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
//  Author:			Jim Beveridge
//  Description:	Apply shortcuts classes - Implementation
//  Created:		Sun Jan 28 10:10:29 1996
//
//

#ifndef __SCUTACCL_H__
#define __SCUTACCL_H__

#pragma warning( push )
#pragma warning( disable : 4786 )

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif
#ifdef WIN32

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // __AFXTEMPL_H__

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


//
// This number should not have to change as long
//	as the Win32 ACCEL structure remains constant.
const WORD kShortcutTableVersion = 1;

	// kShortcutTableFileChars really is char, not TCHAR.  Do this so
	// that big endian does not look funny in the file.
const char kShortcutTableFileChars[] = { 'M','A','C','R' };
const DWORD kShortcutTableFileTag = *(DWORD*)kShortcutTableFileChars;


/************************************************************************
 *
 *		SECCommandList
 *
 *	@class	Maintain the list of command ID's that may be accelerated.
 *			The accelerator keys themselves are not kept in this
 *			structure because it is a one-to-many relationship.
 *
 */

/////////////////////////////
// AutoDuck tag block block for SECShortcutTable 

// adinsert AutoDuck insertion point for SECShortcutTable 
//@doc SECShortcutTable 
//@class The shortcut classes provide an easy way to allow users to redefine the keyboard for an application.
// SECShortcutTable stores the shortcut key bindings in an array of ACCELs.  A user can load a default set of
// key bindings from a given file, or override the loading of the bindings with their own logic.
//@comm See the SHORTCUT sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\SHORTCUT directory for a demonstration of this class.
//@BASE public|CArray<lt>ACCEL,ACCEL&<gt>
//@xref<c SECCommandList> <c SECShortcutDlg>
class SECShortcutTable : public CArray<ACCEL,ACCEL&>
{
public:
	// These enums are used by GetDataFileName
	enum ENameType {
		// Returns the path+filename to store the
		// data in the same place as the EXE.
		MAIN_NAME,
		// Returns the path+filename to store the
		// data in the Windows dir (for those with
		// the EXE on a read-only server)
		ALTERNATE_NAME
	};

//@access Public Members

	// If the mainframe has a table, load it.  Otherwise
	// start out empty.
	//@cmember
	/* Creates an SECShortcutTable instance.*/
	TOOLKIT_API SECShortcutTable();

	TOOLKIT_API virtual ~SECShortcutTable();

	// Walk all menus and update their descriptions.
	//@cmember
	/* Updates the descriptions for all menus.*/
	TOOLKIT_API virtual BOOL ApplyAcceleratorsToMenus();

	// Return the full path and name of the data file.
	//@cmember
	/* Retrieves the data file where the ACCELs are stored.*/
	TOOLKIT_API virtual void GetDataFileName(CString& str, ENameType type);

	// Load the user defined accels (override this to use
	// the registry or some other archive)
	//@cmember
	/* Loads the user defined ACCELs*/
	TOOLKIT_API virtual BOOL Load();

	// Save the user defined accels (override this to use
	// the registry or some other archive)
	//@cmember
	/* Saves the user define ACCELs*/
	TOOLKIT_API virtual BOOL Save();

	// Create a new accel table for the mainframe from the
	// local table and update the menus.
	//@cmember
	/* Creates the new ACCEL table for the mainframe.*/
	TOOLKIT_API virtual BOOL Apply();

	// Revert this structure and the persistent table
	// back to the accel table in the resource file.
	// This function calls LoadDefaultTable().
	//@cmember
	/* Restores the default ACCEL table.*/
	TOOLKIT_API void ResetAll();

	// Reload this table with the accel table
	// from the resource file.
	//@cmember
	/* Loads the current ACCEL table with the default table.*/
	TOOLKIT_API void LoadDefaultTable();

protected:

// Attributes
public:
	TOOLKIT_API static HACCEL mg_hOriginalAccelTable;

	// Operations
public:

// Overrides

// Implementation
public:
	// Associate the given hotkey with the given id.  The hotkey
	// is translated into an accelerator value first.
	TOOLKIT_API void AssignAccel( DWORD hotkey, UINT id );

protected:

	// Load this structure with the mainframe's accel table
	TOOLKIT_API virtual BOOL LoadFromFrame();

	// Given a string from a menu item, replace the accelerator
	// description with "desc"
	TOOLKIT_API virtual void UpdateMenuItem( LPTSTR szItem, const CString& desc,BOOL bNoDesc=FALSE);

	// Update an entire menu tree with the accelerator
	// descriptions from this table.
	TOOLKIT_API virtual void ApplyAcceleratorsToMenu( HMENU hBarMenu, BOOL bTopLevelMenu=TRUE);
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //WIN32

#pragma warning( pop )

#endif	// __SCUTACCL_H__

