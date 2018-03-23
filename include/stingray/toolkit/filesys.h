///////////////////////////////////////////////////////////////////////////////
// filesys.h
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
// CHANGELOG:
//
//    SPL       11/30/95 Started
//	  SCB		07/30/99 Added GetTotalSpaceEx and GetFreeSpaceEx for drives over 2GB.
//				These APIs are not availble when compiling under VC 5 or lower.
//

#ifndef __SECFILESYSTEM_H__
#define __SECFILESYSTEM_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

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

#ifdef WIN32

#ifndef UNDER_CE

#ifndef _INC_DOS
#include <dos.h>
#endif

#ifndef _INC_DIRECT
#include <direct.h>
#endif

#endif  //UNDER_CE (WindowsCE)

// winbase.h defines this to be (0x100000L) for some reason.
#ifdef GetFreeSpace
#undef GetFreeSpace
#endif

#else

#include "dos.h"
#include "direct.h"

#endif

#include <StingrayExportDefs.h>

//***************************************************************************
// Definitions
//***************************************************************************
#define DRIVE_UNDETERMINED 0


/////////////////////////////
// AutoDuck tag block block for SECFileSystem 

// adinsert AutoDuck insertion point for SECFileSystem 
//@doc SECFileSystem 
//@class SECFileSystem is a class designed to provide access to common filesystem 
// functions such as reading a directory or copying a file.  You can also access
// parsing, GUI, and CStringList functions.
// 
// See the FILEDEMO sample in the \SAMPLES\TOOLKIT\STANDARD\UTILITY\FILEDEMO directory for a 
// demonstration of this class.
//@base public | CObject
class SECFileSystem : public CObject
{

// Constructors
public:
	
	//@access Creation/Initialization

	//@cmember
	/* Constructs a SECFileSystem object.*/
	TOOLKIT_API SECFileSystem();

	//@access Attributes

private:

#ifdef WIN32

	WIN32_FIND_DATA  m_FileInfo;
	HANDLE           m_hFind;

#else

	struct _find_t	m_FileInfo;

#endif

	int   m_nMaxFileNameLength;


// Implementation
public:
  TOOLKIT_API virtual ~SECFileSystem();        // Destructor

  // File/Directory Attributes

#ifndef WIN32
#define FILE_ATTRIBUTE_NORMAL CFile::normal
#endif

	//@cmember,menum
	/* File attributes*/
  enum Attribute {
    normal    = FILE_ATTRIBUTE_NORMAL,  //@@emem Normal Files (Win32 API version 0x80)
    readOnly  = CFile::readOnly,        //@@emem Read-Only Files
    hidden    = CFile::hidden,          //@@emem Hidden Files
    system    = CFile::system,          //@@emem System Files
    volume    = CFile::volume,          //@@emem Volume Label
    directory  = CFile::directory,      //@@emem Subdirectory Entry
    archive    = CFile::archive,        //@@emem Archive File
    allfiles  = 0xFFFFFFFF				//@@emem All files
  } ;


	//@access File Operations

	//@cmember
	/* Compares the contents of one file with another.*/
	TOOLKIT_API BOOL CompareFiles(const CString& FileName1, const CString& FileName2, const unsigned long lBuffSize = 10240);
	
	//@cmember
	/* Copies the contents of one file to another.*/
	TOOLKIT_API BOOL CopyFile(const CString& SourceFileName, const CString& DestFileName, const unsigned long lBuffSize = 10240);
	
	//@cmember
	/* Copies more than one file to another subdirectory.*/
	TOOLKIT_API BOOL CopyFiles(const CString& FileSpec, const CString& DestPath, const BOOL bIgnoreErrors = FALSE, const unsigned long eFileAttrib = normal);

	//@cmember
	/* Deletes a files.*/
	TOOLKIT_API BOOL DeleteFile(const CString& FileName);
	
	//@cmember
	/* Deletes specified files (i.e., *.txt).*/
	TOOLKIT_API BOOL DeleteFiles(const CString& FileSpec, const unsigned long eFileAttrib = normal);

	//@cmember
	/* Determines if a file exists.*/
	TOOLKIT_API BOOL FileExists(const CString& PathAndFileName);
	
	//@cmember
	/* Returns the time and date the file was last accessed.*/
	TOOLKIT_API BOOL GetFileAccessTime(const CString& FileName, CTime& time);
	
	//@cmember
	/* Returns the attribute bits for the file.*/
	TOOLKIT_API BOOL GetFileAttribute(const CString& FileName, BYTE& Attribute);

	//@cmember
	/* Returns the time and date the file was created.*/
	TOOLKIT_API BOOL GetFileCreateTime(const CString& FileName, CTime& time);
	
	//@cmember
	/* Returns the time and date the file was last modified.*/
	TOOLKIT_API BOOL GetFileModifyTime(const CString& FileName, CTime& time);
	
	//@cmember
	/* Returns the size of the file in bytes.*/
	TOOLKIT_API BOOL GetFileSize(const CString& FileName, unsigned long& lSize);
	
	//@cmember
	/* Returns the file status.*/
	TOOLKIT_API BOOL GetFileStatus(const CString& FileName, CFileStatus& FileStatus);
	
	//@cmember
	/* Renames a file.*/
	TOOLKIT_API BOOL RenameFile(const CString& OldFileName, const CString& NewFileName);
	

	//@cmember
	/* Returns the time and date the file was created.*/
	TOOLKIT_API BOOL GetFileCreateTime(const CString& FileName, COleDateTime& time);

	//@cmember
	/* Returns the time and date the file was last accessed.*/
	TOOLKIT_API BOOL GetFileAccessTime(const CString& FileName, COleDateTime& time);

	//@cmember
	/* Returns the time and date the file was last modified.*/
	TOOLKIT_API BOOL GetFileModifyTime(const CString& FileName, COleDateTime& time);
	
	//@access Parsing Operations

	//@cmember
	/* Appends a wildcard to a path.*/
	TOOLKIT_API CString AppendWildcard(const CString& Path, const CString& Wildcard);

	//@cmember
	/* Returns the filename without path or extension.*/
	TOOLKIT_API CString GetBaseFileName(const CString& PathAndFileName);

	//@cmember
	/* Returns the extension of the filename.*/
	TOOLKIT_API CString GetExtension(const CString& PathAndFileName);
	
	//@cmember
	/* Returns the filename and extension of a filespec.*/
	TOOLKIT_API CString GetFileName(const CString& PathAndFileName);
	
	//@cmember
	/* Returns the filesystem of the specified filespec.*/
	TOOLKIT_API CString GetFileSystem(const CString& PathAndFileName);
	
	//@cmember
	/* Expands the specified filespec into a full path.*/
	TOOLKIT_API CString GetFullPathName(const CString& PathAndFileName);
	
	//@cmember
	/* Returns the path of the specified filespec.*/
	TOOLKIT_API CString GetPath(const CString& PathAndFileName, const BOOL bIncludeFileSystem = TRUE);
	

	
	//@access Directory Reading Operations

	//@cmember
	/* Returns a list of files based on a filespec.*/
	TOOLKIT_API CStringList* GetDirectory(const CString& SearchString, const unsigned long eFileAttrib, const BOOL bRecurseSubDirs=FALSE, CStringList *pStringList = NULL);

	//@cmember
	/* Returns a single directory entry.*/
	TOOLKIT_API CString* GetDirectoryEntry(const CString& Wildcard = _T(""), const unsigned long eFileAttrib = normal);

	//@cmember
	/* Returns a list of files in the specified directory.*/
	TOOLKIT_API CStringList* GetFileList(const CString& SearchString, const unsigned long eFileAttrib);

	//@cmember
	/* Returns a list of directories in the specified directory.*/
	TOOLKIT_API CStringList* GetSubdirList(const CString& SearchDir, const BOOL bPathInName = TRUE);
	

	
	
	//@access Directory Operations

	//@cmember
	/* Compares the file names, sizes, and contents of two directories.*/
	TOOLKIT_API BOOL CompareDirectories(const CString& PathName1, const CString& PathName2, const BOOL bRecurseSubdirs = FALSE, const BOOL bCompareFileContents = FALSE, const unsigned long eFileAttrib = normal);

	//@cmember
	/* Changes the current working directory.*/
	TOOLKIT_API BOOL ChangeDirectory(const CString& NewDirectory);
	
	//@cmember
	/* Deletes a directory and all its files and subdirectories.*/
	TOOLKIT_API BOOL DeleteDirectory(const CString& Directory, const BOOL bDeleteFilesAndDirs = FALSE);

	//@cmember
	/* Determines if the specified directory exists.*/
	TOOLKIT_API BOOL DirectoryExists(const CString& Path);

	//@cmember
	/* Returns the current directory name.*/
	TOOLKIT_API CString GetCurrentDirectory(const CString& FileSystem = _T(""));

	//@cmember
	/* Returns the number of bytes in all the files in a directory.*/
	TOOLKIT_API LONG GetDirectorySize(const CString& Directory = _T(""), const CString& WildCard = _T("*.*"), const BOOL bRecurseSubdirs = FALSE);

	//@cmember
	/* Creates a subdirectory.*/
	TOOLKIT_API BOOL MakeDirectory(const CString& NewDirectory);
	
	//@cmember
	/* Makes a subdirectory (including all intervening dirs necessary).*/
	TOOLKIT_API BOOL MakePath(const CString& NewDirectory);
	
	//@cmember
	/* Renames a directory.*/
	TOOLKIT_API BOOL RenameDirectory(const CString& OldName, const CString& NewName);
	



	//@access File System Operations

	//@cmember
	/* Changes the current filesystem.*/
	TOOLKIT_API BOOL ChangeFileSystem(const CString& FileSystem);
	
	//@cmember
	/* Returns the current filesystem.*/
	TOOLKIT_API CString GetCurrentFileSystem();
	
	//@cmember
	/* Returns a list of available filesystems.*/
	TOOLKIT_API CStringList* GetFileSystemList();
	
	//@cmember
	/* Returns the type of the specified filesystem.*/
	TOOLKIT_API LONG GetFileSystemType(const CString& FileSystem);
	
	//@cmember
	/* Returns the number of available bytes on the specified filesystem.*/
	TOOLKIT_API LONG GetFreeSpace(const CString& FileSystem);

#if _MSC_VER >= 1200
	//@cmember
	/* Returns the number of available bytes on the specified filesystem.*/
#ifndef UNDER_CE
	TOOLKIT_API LONG64 GetFreeSpaceEx(const CString& FileSystem);
#else
	TOOLKIT_API ULONG GetFreeSpaceEx(const CString& FileSystem);
#endif  //UNDER_CE (WindowsCE)
#endif // #_MSC_VER >= 1200

	//@cmember
	/* Returns whether the specified file system exists.*/
	TOOLKIT_API BOOL FileSystemExists(const CString& FileSystemName);
	
	//@cmember
	/* Returns the number of bytes (used and unused) on the specified filesystem.*/
	TOOLKIT_API LONG GetTotalSpace(const CString& FileSystem);

#if _MSC_VER >= 1200
	//@cmember
	/* Returns the number of bytes (used and unused) on the specified filesystem.*/
#ifndef UNDER_CE
	TOOLKIT_API LONG64 GetTotalSpaceEx(const CString& FileSystem);
#else
	TOOLKIT_API ULONG GetTotalSpaceEx(const CString& FileSystem);
#endif  //UNDER_CE (WindowsCE)
#endif //_MSC_VER >= 1200

	//@cmember
	/* Returns the volume label of the specified filesystem.*/
	TOOLKIT_API CString GetVolumeLabel(const CString& FileSystem);
	
	//@cmember
	/* Determines if the specified filesystem is writeable.*/
	TOOLKIT_API BOOL IsReadOnlyFileSystem(const CString& FileSystem);
	
	
	
	
	//@access MFC GUI Operations

	//@cmember
	/* Insert the members of a CStringList into a combo box.*/
	TOOLKIT_API static void LoadComboBox(CComboBox *pComboBox, const CStringList * pStringList);

	//@cmember
	/* Insert the members of a CStringList into a list box.*/
	TOOLKIT_API static void LoadListBox(CListBox *pListBox, const CStringList * pStringList);
	

	
	//@access MFC StringList Operations

	//@cmember
	/* Sort a CStringList.*/
	TOOLKIT_API static void Sort(CStringList *pStringList, BOOL bCase = TRUE);

	// Overridable


	// Implementation

protected:
	TOOLKIT_API BOOL ChangeFileSystem(const char cFileSystem);
    TOOLKIT_API BOOL CloseFile(CFile *pFile) const;
    TOOLKIT_API BOOL GetADirectoryEntry(CString &fileName, const CString& Wildcard = _T(""), const unsigned long eFileAttrib = normal);

}; // SECFileSystem


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _SECFILESYSTEM_H_


